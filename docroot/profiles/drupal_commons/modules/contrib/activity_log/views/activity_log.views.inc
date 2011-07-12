<?php

/**
 * @file
 *   Views integration for Activity Log.
 */

/**
 * Implementation of hook_views_query_alter().
 */
function activity_log_views_query_alter(&$view, &$query) {
  if ($query->base_table == 'activity_log_messages') {
    global $user;
    $query->ensure_table('activity_log_templates');
    // Don't show disabled activity types.
    $query->add_where(0, db_prefix_tables("{activity_log_templates}.pid NOT IN (SELECT pid FROM {activity_log_disabled_types} WHERE uid = %d)"), $user->uid);
    // Only show activity where the viewer is "everyone" or the current user.
    $query->add_where(0, "viewer_id = 0 OR viewer_id = %d", $user->uid);
  }
}

/**
 * Implementation of hook_views_handlers().
 */
function activity_log_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'activity_log') .'/views',
    ),
    'handlers' => array(
      'activity_log_views_handler_argument_owner_id' => array(
        'parent' => 'views_handler_argument_numeric',
      ),
      'activity_log_views_handler_field_message' => array(
        'parent' => 'views_handler_field',
      ),
      'activity_log_views_handler_filter_owner_type' => array(
        'parent' => 'views_handler_filter',
      ),
      'activity_log_views_handler_sort_radioactivity' => array(
        'parent' => 'views_handler_sort',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_plugins().
 */
function activity_log_views_plugins() {
  return array(
    'argument validator' => array(
      'activity_log_validate_stream_owner_type' => array(
        'title' => t('Stream type'),
        'path' => drupal_get_path('module', 'activity_log') .'/views',
        'handler' => 'activity_log_stream_owner_type_argument_validate',
      ),
    ),
    'argument default' => array(
      'activity_log_default_stream_owner_type' => array(
        'title' => t('Stream type'),
        'path' => drupal_get_path('module', 'activity_log') .'/views',
        'handler' => 'activity_log_stream_owner_type_argument_default',
        'parent' => 'fixed',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data().
 */
function activity_log_views_data() {

  // The messages table.

  $data['activity_log_messages']['table']['group'] = t('Activity Log');

  $data['activity_log_messages']['table']['base'] = array(
    'field' => 'mid',
    'title' => t('Activity Log'),
    'help' => t('Activities logged by the Activity log module'),
    'weight' => -10,
  );

  $data['activity_log_messages']['mid'] = array(
    'title' => t('Activity Log message id'),
    'help' => t('The numeric id of the recorded message'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['activity_log_messages']['message'] = array(
    'title' => t('Activity Log message'),
    'help' => t('The evaluated template from the event'),
    'field' => array(
      'field' => 'mid',
      'handler' => 'activity_log_views_handler_field_message',
    ),
  );

  $data['activity_log_messages']['stream_owner_id'] = array(
    'title' => t('Stream owner'),
    'help' => t('The entity in whose activity stream the messages are intended to appear'),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'activity_log_views_handler_argument_owner_id',
    ),
  );

  $data['activity_log_messages']['stream_owner_type'] = array(
    'title' => t('Stream owner type'),
    'help' => t('The type of entity in whose activity stream the messages are intended to appear'),
    'filter' => array(
      'handler' => 'activity_log_views_handler_filter_owner_type',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['activity_log_messages']['created'] = array(
    'title' => t('Created time'),
    'help' => t('The time at which the message (or first message if grouping is enabled) was recorded'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  $data['activity_log_messages']['last_updated'] = array(
    'title' => t('Updated time'),
    'help' => t('The time at which the most recent message was added to a grouped message'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  // The templates table

  $data['activity_log_templates']['table']['group'] = t('Activity Log');
  
  $data['activity_log_templates']['table']['join'] = array(
    'activity_log_messages' => array(
      'left_field' => 'tid',
      'field' => 'tid',
    ),
  );

  $data['activity_log_templates']['rule'] = array(
    'title' => t('Rule name'),
    'help' => t('The machine name of the rule that triggered the message'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => 'true',
    ),
  );

  $data['activity_log_templates']['action_label'] = array(
    'title' => t('Action label'),
    'help' => t('The the label of the action that triggered the message'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => 'true',
    ),
  );

  // Radioactivity integration. TODO: Move this into al_radioactivity

  if (module_exists('al_radioactivity')) {
    foreach (radioactivity_get_decay_profiles() as $dpid => $decay_profile) {
      $data['radioactivity']['table']['group'] = t('Radioactivity (@profile)', array('@profile' => $decay_profile['label']));
      $data['radioactivity']['table']['title'] = t('Activity energy');
      $data['radioactivity']['table']['help'] = t('Activity radioactive energy in decay profile @profile.', array('@profile' => $decay_profile['label']));
  
      $data['radioactivity']['table']['join']['activity_log_messages'] = array(
        'left_field' => 'nid',
        'field' => 'id',
        'table' => 'radioactivity',
        'extra' => array(
          array(
            'field' => 'class',
            'value' => 'act_log',
          ),
          array(
            'field' => 'decay_profile',
            'value' => $dpid,
            'numeric' => TRUE,
          ),
        ),
      );
  
      $data['radioactivity']['energy'] = array(
        'title' => t('Node energy'),
        'help' => t('The radioactive energy of the node.'),
        'sort' => array(
          'handler' => 'activity_log_views_handler_sort_radioactivity',
        ),
      );
    }
  }

  return $data;
}
