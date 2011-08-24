<?php

/**
 * @file
 *   Cron tasks for the Activity Log Digests module.
 */

//============
// PROCESSING
//============

/**
 * Send digest emails.
 */
function _digests_cron() {
  $default_tz = variable_get('date_default_timezone', 0);
  $now = time();
  $send_time = gmmktime(variable_get('digests_send_time', 18), 0, 0);

  // Step 1: Get users for whom it is after 6PM in their timezone but who have not had a digest sent for this interval.
  $default = $now > $send_time + $default_tz || $now < $send_time + $default_tz - 43200; // whether it's past send_time in the site's default timezone
  $query = "
    SELECT d.*, u.* /* We need the digests table first here, otherwise users with no digests row have uid = NULL in the results */
    FROM {users} u
    LEFT JOIN {digests} d
      ON u.uid = d.uid
    WHERE
      status = 1 AND (                                                  /* user is not blocked */
        send_interval IS NULL OR                                        /* user has not set their interval */
        send_interval = 86400                                           /* user's interval is daily */
        ". (date('w') == 0 ? 'OR send_interval = 604800' : '') ."       /* user's interval is weekly, and it's Sunday */
      ) AND
      %d > COALESCE(last_sent, created) + (COALESCE(send_interval, 86400) - 43200) /* it's been at least (interval - 12 hours) since the last digest email */
  ";
  if (variable_get('digests_local', 'local') == 'local') {
    $query .= " AND (
        %d /* NOW */ > %d /* SEND */ + timezone OR      /* it's after send_time today */
        %d /* NOW */ < %d /* SEND */ + timezone - 43200 /* it's more than 12hrs before send_time today, i.e. less than 12hrs since send_time yesterday */
    ";
    if ($default) {
      $query .= "    OR timezone IS NULL /* the user has not set a timezone, fall back to the site default */";
    }
    $query .= "\n      )";
    if (variable_get('digests_limit', 250)) {
      $result = db_query_range($query, $now, $now, $send_time, $now, $send_time, 0, variable_get('digests_limit', 250));
    }
    else {
      $result = db_query($query, $now, $now, $send_time, $now, $send_time);
    }
  }
  elseif ($default) {
    if (variable_get('digests_limit', 250)) {
      $result = db_query_range($query, $now, 0, variable_get('digests_limit', 250));
    }
    else {
      $result = db_query($query, $now);
    }
  }

  // Step 2: For each selected user, collect all activity that has been updated between 6PM 2 days ago and 6PM yesterday
  while ($account = db_fetch_object($result)) {
    if (empty($account) || empty($account->uid) || !valid_email_address($account->mail)) {
      continue;
    }
    $account = drupal_unpack($account);
    $account->roles = array();
    $account->roles[DRUPAL_AUTHENTICATED_RID] = 'authenticated user';
    $rresult = db_query('SELECT r.rid, r.name FROM {role} r INNER JOIN {users_roles} ur ON ur.rid = r.rid WHERE ur.uid = %d', $account->uid);
    while ($role = db_fetch_object($rresult)) {
      $account->roles[$role->rid] = $role->name;
    }
    if (!user_access('receive digests', $account)) {
      continue;
    }
    $account_tz = $default_tz;
    if (isset($account->timezone) && !is_null($account->timezone)) {
      $account_tz = $account->timezone;
    }
    $interval = 86400;
    if (isset($account->send_interval) && !is_null($account->send_interval)) {
      $interval = $account->send_interval;
    }
    $send_time_account = $send_time + $account_tz;
    $send_time_two_days_ago = $send_time_account - (86400 + $interval);
    $send_time_one_day_ago = $send_time_account - 86400;
    $mresult = db_query("
      SELECT *
      FROM {activity_log_messages} m
      LEFT JOIN {activity_log_templates} t
        ON m.tid = t.tid
      WHERE
        display_type = 'email' AND
        stream_owner_type = 'user' AND
        stream_owner_id = %d AND
        last_updated > %d /* 2 days ago */ AND
        last_updated < %d /* 1 day ago */ AND (
          viewer_id = %d /* account */ OR
          viewer_id = 0 /* everyone */ OR
          (viewer_id < 0 AND viewer_id <> -%d) /* everyone except account */
        ) AND
        t.pid NOT IN (
          SELECT pid FROM {activity_log_disabled_types} WHERE uid = %d
        )
      ORDER BY last_updated DESC
    ", $account->uid, $send_time_two_days_ago, $send_time_one_day_ago, $account->uid, $account->uid, $account->uid);

    // Step 3: Render the collected activity messages as HTML
    $messages = array();
    while ($record = db_fetch_object($mresult)) {
      $messages[] = $record;
    }
    // Remove activity from $messages if the viewing user doesn't have permission to view the associated node.
    // We use db_rewrite_sql() instead of running node_access() on each node for performance.
    if (!empty($messages)) {
      $aids = array();
      $aid_to_result_key_map = array();
      foreach ($messages as $key => $result) {
        if ($result->target_type == 'node') {
          $result_aids = array_filter(explode(',', $result->aids));
          $aids = array_merge($aids, $result_aids);
          foreach ($result_aids as $aid) {
            $aid_to_result_key_map[$aid] = $key;
          }
        }
      }
      if (empty($aids)) {
        continue;
      }
      $nids_result = db_query("SELECT aid, target_id AS nid FROM {activity_log_events} WHERE aid IN (". db_placeholders($aids) .")", $aids);
      $nids = array();
      while ($node = db_fetch_object($nids_result)) {
        $nids[$node->aid] = $node->nid;
      }
      // If we're not dealing with any nodes, we don't need to check node access.
      if (empty($nids)) {
        continue;
      }
      // Reduce the list of nids returned by the view to those which the user has permission to view.
      $nids_visible = array();
      $query_restricted = db_query(db_rewrite_sql("SELECT DISTINCT(n.nid) FROM {node} n WHERE n.nid IN (". db_placeholders($nids) .")"), array_values($nids));
      while ($result_restricted = db_fetch_object($query_restricted)) {
        $nids_visible[$result_restricted->nid] = $result_restricted->nid;
      }
      $nids_to_remove = array_diff($nids, $nids_visible); // preserves keys
      // Remove the activity from $messages that use events related to restricted nodes.
      $result_keys_to_remove = array();
      foreach ($nids_to_remove as $aid => $nid) {
        $key = $aid_to_result_key_map[$aid];
        $result_keys_to_remove[$key] = $key;
      }
      $messages = array_diff_key($messages, $result_keys_to_remove);
    }
    if (empty($messages)) {
      continue;
    }
    $output = theme('digests_email', $account, $messages, $now);

    // Step 4: Pass the rendered activity stream to the Mime Mail module for delivery
    if ($interval == 86400) {
      $subject = t('Your @site activity for @date', array(
        '@site' => variable_get('site_name', 'Drupal'),
        '@date' => date('l, F j', $now - $interval),
      ));
    }
    elseif ($interval == 604800) {
      $subject = t('Your @site activity for the week of @date', array(
        '@site' => variable_get('site_name', 'Drupal'),
        '@date' => date('F j', $now - $interval),
      ));
    }
    mimemail(
      variable_get('site_mail', ini_get('sendmail_from')), //sender
      $account, // recipient
      $subject, // subject
      $output,  // HTML for body
      NULL,     // force plaintext only
      array(),  // headers
      NULL,     // custom plaintext version
      array(),  // attachments
      'digests' // mailkey
    );

    // Step 5: Update the "last sent" time for each processed user
    db_query("UPDATE {digests} SET last_sent = %d WHERE uid = %d", $now, $account->uid);
    if (db_affected_rows() <= 0) {
      $insert = (object) array(
        'uid' => $account->uid,
        'last_sent' => $now,
        'send_interval' => 86400,
      );
      drupal_write_record('digests', $insert);
    }
  }
}

/**
 * Preprocess the digest email template variables.
 */
function template_preprocess_digests_email(&$vars) {
  $output = '';
  $count = 0;
  foreach ($vars['messages'] as $message) {
    $count++;
    activity_log_record_unpack($message);
    $html_message = theme('activity_log_item', $message);
    $output .= '<tr><td class="digests-message" style="border-bottom:1px solid #f0f0f0;'. ($count === 1 ? ' border-top: 1px solid #f0f0f0; ' : ' ') .'padding-top:12px;padding-bottom:12px;">'. $html_message ."</td></tr>\n";
  }
  $vars['stream'] = $output;
  $account = $vars['account'];
  $vars['name'] = check_plain($account->name);
  $vars['name_link'] = l(check_plain($account->name), 'user/'. $account->uid);
  $now = $vars['now'];
  $vars['date_small'] = format_date($now, 'small');
  $vars['date_medium'] = format_date($now, 'medium');
  $vars['date_large'] = format_date($now, 'large');
  $vars['logo'] = _digests_get_logo();
  $header = variable_get('digests_header', '');
  $footer = variable_get('digests_footer', '');
  if (module_exists('token')) {
    $types = array('global' => NULL, 'user' => $account);
    $header = token_replace_multiple($header, $types);
    $footer = token_replace_multiple($footer, $types);
  }
  $vars['header'] = filter_xss_admin($header);
  $vars['footer'] = filter_xss_admin($footer);
  $vars['unsubscribe'] = t('<a href="!unsub">Edit your settings</a> to unsubscribe from activity emails from @site.', array(
    '!unsub' => url('user/'. $account->uid .'/edit', array('absolute' => TRUE)),
    '@site' => variable_get('site_name', 'Drupal'),
  ));
}

/**
 * Helper function to generate a logo for the digest email
 */
function _digests_get_logo() {
  $theme = variable_get('theme_default', NULL);
  $path = '';
  
  // Use the theme's logo
  if (variable_get('digests_logo_use_theme', TRUE)) {
    // Fetch the theme settings
    $settings = theme_get_settings($theme);
    // We don't use theme_get_setting('logo') because if the logo
    // is disabled for the site, it will return empty
    if ($settings['default_logo']) {
      $path = drupal_get_path('theme', $theme) . '/logo.png';
    }
    elseif ($settings['logo_path']) {
      $path = $settings['logo_path'];
    }
  }
  // Use a custom logo provided
  else {
    $path = variable_get('digests_logo', '');
  }
  
  if ($path) {
    return theme(
      'image',
      url($path, array('absolute' => TRUE)),
      variable_get('site_name', 'Drupal'),
      variable_get('site_name', 'Drupal'),
      NULL,
      FALSE
    );
  }
  
  return NULL;
}
