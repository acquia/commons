<?php

/**
 * @file
 *   Provides default Rules.
 */

/**
 * Implementation of hook_rules_defaults().
 */
function activity_log_rules_defaults() {
  $rules = array();
  if (module_exists('facebook_status_rules')) {
    $rules += activity_log_rules_defaults_facebook_status_insert_user_self();
    $rules += activity_log_rules_defaults_facebook_status_insert_user_other();
  }
  return array('rules' => $rules);
}

/**
 * When a user updates their own status, display the themed status on their
 * profile, their followers' profiles, and @mentioned users' profiles.
 */
function activity_log_rules_defaults_facebook_status_insert_user_self() {
  return array (
    'rules_activity_log_facebook_status_insert_user_self' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_facebook_status_save',
      '#label' => 'Log activity when a user saves a personal status update',
      '#active' => 1,
      '#weight' => '0',
      '#categories' => 
      array (
        0 => 'activity_log',
        1 => 'facebook_status',
      ),
      '#status' => 'custom',
      '#conditions' => 
      array (
        0 => 
        array (
          '#type' => 'condition',
          '#settings' => 
          array (
            '#argument map' => 
            array (
              'status' => 'status',
            ),
          ),
          '#name' => 'fbss_rules_is_self',
          '#info' => 
          array (
            'label' => 'Status was posted to own profile',
            'arguments' => 
            array (
              'status' => 
              array (
                'type' => 'facebook_status',
                'label' => 'The status',
              ),
            ),
            'module' => 'Facebook-style Statuses',
          ),
          '#weight' => 0,
        ),
      ),
      '#actions' => 
      array (
        0 => 
        array (
          '#weight' => 0,
          '#info' => 
          array (
            'label' => 'Log activity',
            'module' => 'Activity Log',
            'eval input' => 
            array (
              0 => 'placeholder',
              1 => 'grouping|group_summary',
              2 => 'visibility|stream_owner_id',
              3 => 'visibility|viewer_id',
              4 => 'acting_uid',
              5 => 'templates|en|template',
              6 => 'grouping|templates|en|template',
            ),
          ),
          '#name' => 'activity_log_log_action',
          '#settings' => 
          array (
            'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
            'public_name' => '',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '[status:status-themed]',
              ),
            ),
            'grouping' => 
            array (
              'group_method' => 'none',
              'group_interval' => '86400',
              'group_max' => '100',
              'group_summary' => '',
              'collapse_method' => 'activity_log_collapse_inline',
              'templates' => 
              array (
                'en' => 
                array (
                  'template' => '',
                ),
              ),
            ),
            'visibility' => 
            array (
              'stream_owner_entity_group' => 
              array (
                'mentioned users' => 'mentioned users',
                'acting user' => 'acting user',
                'acting user relationships' => 'acting user relationships',
                'active groups relationships 1 custom user' => 0,
                'active groups relationships 1 acting user' => 0,
                'active groups relationships custom user' => 0,
                'node terms' => 0,
                'status commenters' => 0,
                'hashtag terms' => 0,
                'active groups relationships acting user' => 0,
                'custom user relationships 1' => 0,
                'active groups' => 0,
                'target entity' => 0,
                'active groups members' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships' => 0,
                'custom' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'active groups relationships 1 acting user' => 0,
                'active groups relationships custom user' => 0,
                'active groups relationships 1 custom user' => 0,
                'status commenters' => 0,
                'mentioned users' => 0,
                'active groups relationships acting user' => 0,
                'custom user relationships 1' => 0,
                'target entity' => 0,
                'acting user' => 0,
                'active groups members' => 0,
                'acting user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships' => 0,
                'custom' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '[status:sender-uid]',
            'tid' => '2',
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'placeholder' => 
                array (
                  0 => ':global',
                ),
                'grouping|group_summary' => 
                array (
                  0 => ':global',
                ),
                'visibility|stream_owner_id' => 
                array (
                  0 => ':global',
                ),
                'visibility|viewer_id' => 
                array (
                  0 => ':global',
                ),
                'acting_uid' => 
                array (
                  0 => 'status',
                  1 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'status',
                  1 => ':global',
                ),
                'grouping|templates|en|template' => 
                array (
                  0 => ':global',
                ),
              ),
              'activity_log_input_evaluator_process' => 
              array (
                'placeholder' => true,
                'grouping|group_summary' => true,
                'visibility|stream_owner_id' => true,
                'visibility|viewer_id' => true,
                'acting_uid' => true,
                'templates|en|template' => true,
                'grouping|templates|en|template' => true,
              ),
            ),
          ),
          '#type' => 'action',
        ),
      ),
      '#version' => 6003,
    ),
  );
}

/**
 * When a user posts a status message to another user, display the themed
 * status on the recipient's profile and @mentioned users' profiles, and
 * display a message that this activity occurred on the sender's profile.
 */
function activity_log_rules_defaults_facebook_status_insert_user_other() {
  return array (
    'rules_activity_log_facebook_status_insert_user_other' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_facebook_status_save',
      '#label' => 'Log activity when a user saves a status message to another user',
      '#active' => 1,
      '#weight' => '0',
      '#categories' => 
      array (
        0 => 'activity_log',
        1 => 'facebook_status',
      ),
      '#status' => 'custom',
      '#conditions' => 
      array (
        0 => 
        array (
          '#type' => 'condition',
          '#settings' => 
          array (
            'types' => 
            array (
              'user' => 'user',
              'node' => 0,
              'og' => 0,
              'term' => 0,
            ),
            '#argument map' => 
            array (
              'status' => 'status',
            ),
          ),
          '#name' => 'fbss_rules_rules_condition_is_type',
          '#info' => 
          array (
            'label' => 'Status is sent to a user',
            'label callback' => false,
            'arguments' => 
            array (
              'status' => 
              array (
                'type' => 'facebook_status',
                'label' => 'The status',
              ),
            ),
            'module' => 'Facebook-style Statuses',
          ),
          '#weight' => 0,
        ),
        1 => 
        array (
          '#negate' => 1,
          '#weight' => 0,
          '#info' => 
          array (
            'label' => 'User updated their own status',
            'label callback' => false,
            'arguments' => 
            array (
              'status' => 
              array (
                'type' => 'facebook_status',
                'label' => 'The status',
              ),
            ),
            'module' => 'Facebook-style Statuses',
          ),
          '#name' => 'fbss_rules_is_self',
          '#settings' => 
          array (
            '#argument map' => 
            array (
              'status' => 'status',
            ),
          ),
          '#type' => 'condition',
        ),
      ),
      '#actions' => 
      array (
        0 => 
        array (
          '#info' => 
          array (
            'label' => 'Log activity for the acting user',
            'label callback' => false,
            'module' => 'Activity Log',
            'eval input' => 
            array (
              0 => 'placeholder',
              1 => 'grouping|group_summary',
              2 => 'visibility|stream_owner_id',
              3 => 'visibility|viewer_id',
              4 => 'acting_uid',
              5 => 'templates|en|template',
              6 => 'grouping|templates|en|template',
            ),
          ),
          '#name' => 'activity_log_log_action',
          '#settings' => 
          array (
            'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
            'public_name' => '',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '[status:sender-themed] wrote a message to [status:recipient-link]',
              ),
            ),
            'grouping' => 
            array (
              'group_method' => 'none',
              'group_interval' => '86400',
              'group_max' => '100',
              'group_summary' => '',
              'collapse_method' => 'activity_log_collapse_inline',
              'templates' => 
              array (
                'en' => 
                array (
                  'template' => '',
                ),
              ),
            ),
            'visibility' => 
            array (
              'stream_owner_entity_group' => 
              array (
                'acting user' => 'acting user',
                'active groups relationships 1 custom user' => 0,
                'active groups relationships 1 acting user' => 0,
                'active groups relationships custom user' => 0,
                'node terms' => 0,
                'status commenters' => 0,
                'hashtag terms' => 0,
                'mentioned users' => 0,
                'active groups relationships acting user' => 0,
                'custom user relationships 1' => 0,
                'active groups' => 0,
                'target entity' => 0,
                'active groups members' => 0,
                'acting user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships' => 0,
                'custom' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'active groups relationships 1 acting user' => 0,
                'active groups relationships custom user' => 0,
                'active groups relationships 1 custom user' => 0,
                'status commenters' => 0,
                'mentioned users' => 0,
                'active groups relationships acting user' => 0,
                'custom user relationships 1' => 0,
                'target entity' => 0,
                'acting user' => 0,
                'active groups members' => 0,
                'acting user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships' => 0,
                'custom' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '[status:sender-uid]',
            'tid' => '3',
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'placeholder' => 
                array (
                  0 => ':global',
                ),
                'grouping|group_summary' => 
                array (
                  0 => ':global',
                ),
                'visibility|stream_owner_id' => 
                array (
                  0 => ':global',
                ),
                'visibility|viewer_id' => 
                array (
                  0 => ':global',
                ),
                'acting_uid' => 
                array (
                  0 => 'status',
                  1 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'status',
                  1 => ':global',
                ),
                'grouping|templates|en|template' => 
                array (
                  0 => ':global',
                ),
              ),
              'activity_log_input_evaluator_process' => 
              array (
                'placeholder' => true,
                'grouping|group_summary' => true,
                'visibility|stream_owner_id' => true,
                'visibility|viewer_id' => true,
                'acting_uid' => true,
                'templates|en|template' => true,
                'grouping|templates|en|template' => true,
              ),
            ),
          ),
          '#type' => 'action',
          '#weight' => 0,
        ),
        1 => 
        array (
          '#weight' => 0,
          '#info' => 
          array (
            'label' => 'Log activity for the recipient and @mentioned users',
            'label callback' => false,
            'module' => 'Activity Log',
            'eval input' => 
            array (
              0 => 'placeholder',
              1 => 'grouping|group_summary',
              2 => 'visibility|stream_owner_id',
              3 => 'visibility|viewer_id',
              4 => 'acting_uid',
              5 => 'templates|en|template',
              6 => 'grouping|templates|en|template',
            ),
          ),
          '#name' => 'activity_log_log_action',
          '#settings' => 
          array (
            'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
            'public_name' => '',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '[status:status-themed]',
              ),
            ),
            'grouping' => 
            array (
              'group_method' => 'none',
              'group_interval' => '86400',
              'group_max' => '100',
              'group_summary' => '',
              'collapse_method' => 'activity_log_collapse_inline',
              'templates' => 
              array (
                'en' => 
                array (
                  'template' => '',
                ),
              ),
            ),
            'visibility' => 
            array (
              'stream_owner_entity_group' => 
              array (
                'mentioned users' => 'mentioned users',
                'custom' => 'custom',
                'active groups relationships 1 custom user' => 0,
                'active groups relationships 1 acting user' => 0,
                'active groups relationships custom user' => 0,
                'node terms' => 0,
                'status commenters' => 0,
                'hashtag terms' => 0,
                'active groups relationships acting user' => 0,
                'custom user relationships 1' => 0,
                'active groups' => 0,
                'target entity' => 0,
                'acting user' => 0,
                'active groups members' => 0,
                'acting user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships' => 0,
              ),
              'stream_owner_id' => '[status:recipient-id]',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'active groups relationships 1 acting user' => 0,
                'active groups relationships custom user' => 0,
                'active groups relationships 1 custom user' => 0,
                'status commenters' => 0,
                'mentioned users' => 0,
                'active groups relationships acting user' => 0,
                'custom user relationships 1' => 0,
                'target entity' => 0,
                'acting user' => 0,
                'active groups members' => 0,
                'acting user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships' => 0,
                'custom' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '',
            'tid' => '4',
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'placeholder' => 
                array (
                  0 => ':global',
                ),
                'grouping|group_summary' => 
                array (
                  0 => ':global',
                ),
                'visibility|stream_owner_id' => 
                array (
                  0 => 'status',
                  1 => ':global',
                ),
                'visibility|viewer_id' => 
                array (
                  0 => ':global',
                ),
                'acting_uid' => 
                array (
                  0 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'status',
                  1 => ':global',
                ),
                'grouping|templates|en|template' => 
                array (
                  0 => ':global',
                ),
              ),
              'activity_log_input_evaluator_process' => 
              array (
                'placeholder' => true,
                'grouping|group_summary' => true,
                'visibility|stream_owner_id' => true,
                'visibility|viewer_id' => true,
                'acting_uid' => true,
                'templates|en|template' => true,
                'grouping|templates|en|template' => true,
              ),
            ),
          ),
          '#type' => 'action',
        ),
      ),
      '#version' => 6003,
    ),
  );
}


