<?php
// $Id: realname_theme.inc,v 1.2.4.23 2010/10/30 17:25:37 davereid Exp $

/**
 * @file
 *   This include file intercepts the theme('username'... function
 *   and uses the RealName instead of the username.
 */

/**
 * Format a username.  (copied from theme.inc)
 *
 * @param $object
 *   The user object to format, usually returned from user_load().
 * @param $options
 *   An associative array of theme options.
 *     'plain' => whether or not to make the name a link (default: FALSE)
 *     'picture' => whether or not to include the user's picture (default: FALSE)
 *        will not be done if 'plain' = TRUE.
 *     'homepage' => link may be to the user's homepage (default: TRUE)
 *     'levels' => include user level marking (default: FALSE)
 *     'max_length' => maximum name length to show (default: from settings page)
 *     'not_ver' => whether to show "not verified" (default: from settings page)
 *     'allowed_tags' => an array of HTML tags that are allowed to remain in the name
 *       if 'plain' is TRUE (default: 'em', 'i', 'u', 'strong', 'b')
 *
 * @return
 *   A string containing an HTML link to the user's page if the passed object
 *   suggests that this is a site user. Otherwise, only the username is returned.
 */
function realname_username($object, $options = array()) {
  static $roles = array();

  $defaults = array(
    'plain' => FALSE,
    'picture' => FALSE,
    'homepage' => TRUE,
    'levels' => FALSE,
    'max_length' => variable_get('realname_max_username', 20),
    'not_ver' => variable_get('realname_notver', TRUE),
//    'allowed_tags' => array('em', 'i', 'u', 'strong', 'b'),
    );
  $options = array_merge($defaults, (array)$options);

  // If we have a user id but no realname, then make one.
  if ($object->uid && !isset($object->realname) && user_access('use realname')) {
    $object->realname = realname_make_name($object);
  }

  if ($object->uid && (!empty($object->realname) || !empty($object->name))) {
    $name = !empty($object->realname) ? $object->realname : $object->name;

    // Shorten the name when it is too long or it will break many tables.
    $max_name = $options['max_length'];
    if (drupal_strlen($name) > $max_name) {
      $name = drupal_substr($name, 0, $max_name - 3) .'...';
    }

    if (user_access('access user profiles') && !$options['plain']) {
      $l_opts = array('absolute' => TRUE);
      if ($options['levels']) {
        // If there are no roles in this object (e.g. a node), go get them.
        if (!isset($object->roles)) {
          $object->roles = array();
          $result = db_query("SELECT r.rid, r.name FROM {users_roles} ur JOIN {role} r USING(rid) WHERE ur.uid = %d", $object->uid);
          while ($row = db_fetch_object($result)) {
            $object->roles[$row->rid] = $row->name;
          }
        }
        // Format user levels here.
        foreach ($object->roles as $rid => $role) {
          if (!isset($roles[$rid])) {
            // Use empty here because NULL is not set.
            $pic = variable_get('realname_user_level_'. $rid, '');
            $roles[$rid] = empty($pic) ? '' : file_create_url($pic);
            // Make a nice css value out of the role title
            $l_opts['attributes']['class'][] = form_clean_id(strtolower($role));
          }
          if ($roles[$rid]) {
            $name .= '<img src="'. $roles[$rid] .'" alt="'. $role .'" title="'. $role .'" />';
            $l_opts['html'] = TRUE;
          }
        }
      }
      if (!empty($object->homepage) && $options['homepage']) {
        $url = $object->homepage;
        $title = t("View user's home page.");
        if (variable_get('realname_nofollow', FALSE)) {
          $l_opts['attributes']['rel'] = 'nofollow';
        }
      }
      else {
        $url = 'user/'. $object->uid;
        $title = t('View user profile.');
      }
      $l_opts['attributes']['title'] = $title;

      // Convert the class attributes to a space-delimited string.
      if (!empty($l_opts['attributes']['class'])) {
        $l_opts['attributes']['class'] = implode(' ',  $l_opts['attributes']['class']);
      }
      else {
        unset($l_opts['attributes']['class']);
      }

      $output = l($name, $url, $l_opts);
      if ($options['picture']) {
        $output .= theme('user_picture', $object);
      }
    }
    else {
      $output = check_plain($name);
//      $output = drupal_validate_utf8($name) ? strip_tags($name, $options['allowed_tags']) : '';
    }
  }
  elseif ($object->name) {
    // Sometimes modules display content composed by people who are not registered
    // members of the site (e.g. mailing list or news aggregator modules).
    // This clause enables modules to display the true author of the content.
    if (!empty($object->homepage) && $options['homepage'] && !$options['plain']) {
      $output = l($object->name, $object->homepage, array('attributes' => array('title' => t("View user's home page."))));
    }
    else {
      $output = check_plain($object->name);
//      $output = drupal_validate_utf8($name) ? strip_tags($name, $options['allowed_tags']) : '';
    }

    if ($options['not_ver']) {
      $output .= ' ('. t('not verified') .')';
    }
  }
  else {
    $output = variable_get('anonymous', t('Anonymous'));
  }

  return $output;
}

/**
 * Theme the new-role form (copied from user.admin.inc.
 */
function theme_realname_new_role($form) {
  $header = array(t('Name'), t('User level'), array('data' => t('Operations'), 'colspan' => 2));
  foreach (user_roles() as $rid => $name) {
    $pic = variable_get('realname_user_level_'. $rid, '');
    $level = empty($pic) ? '' : '<img src="'. file_create_url($pic) .'" />';
    $edit_permissions = l(t('edit permissions'), 'admin/user/permissions/'. $rid);
    if (!in_array($rid, array(DRUPAL_ANONYMOUS_RID, DRUPAL_AUTHENTICATED_RID))) {
      $rows[] = array($name, $level, l(t('edit role'), 'admin/user/roles/edit/'. $rid), $edit_permissions);
    }
    else {
      $rows[] = array($name, $level, t('locked'), $edit_permissions);
    }
  }
  $rows[] = array(drupal_render($form['name']), array('data' => drupal_render($form['submit']), 'colspan' => 3));

  $output = drupal_render($form);
  $output .= theme('table', $header, $rows);

  return $output;
}
