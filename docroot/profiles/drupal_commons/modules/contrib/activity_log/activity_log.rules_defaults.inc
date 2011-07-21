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
  $rules += activity_log_rules_defaults_node_insert();
  if (module_exists('og')) {
    $rules += activity_log_rules_defaults_node_insert_og();
    $rules += activity_log_rules_defaults_og_join();
  }
  if (module_exists('fbss_rules')) {
    $rules += activity_log_rules_defaults_facebook_status_insert_user_self();
    $rules += activity_log_rules_defaults_facebook_status_insert_other();
    if (module_exists('fbsmp')) {
      $rules += activity_log_rules_defaults_fbsmp_insert_user_self();
      $rules += activity_log_rules_defaults_fbsmp_insert_other();
    }
  }
  if (module_exists('user_relationships_rules')) {
    $rules += activity_log_rules_defaults_ur_request();
  }
  return array('rules' => $rules);
}

/**
 * Node creation
 *
 * Modified from export: #label, #conditions
 */
function activity_log_rules_defaults_node_insert() {
  $ret = array(
    'rules_activity_log_node_insert' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_node_insert',
      '#label' => 'Log activity when a node is created'. (module_exists('og') ? ' (not in a group)' : ''),
      '#active' => 1,
      '#weight' => '0',
      '#categories' => 
      array (
        0 => 'activity_log',
        1 => 'node',
      ),
      '#status' => 'custom',
      '#conditions' =>
      array (
        0 => 
        array (
          '#weight' => 0,
          '#info' => 
          array (
            'label' => 'Updated content is published',
            'arguments' => 
            array (
              'node' => 
              array (
                'type' => 'node',
                'label' => 'Content',
              ),
            ),
            'module' => 'Node',
          ),
          '#name' => 'rules_condition_content_is_published',
          '#settings' => 
          array (
            '#argument map' => 
            array (
              'node' => 'node',
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
                'template' => '<div class="activity-log-content">[author:user] added the [node:type-name] [node:title-link]</div>
<div class="activity-log-time"><a href="[node:node-url]">[node:since] ago</a></div>',
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
                'custom' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'node terms' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'stream_owner' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '[author:uid]',
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
                  0 => ':global',
                ),
                'visibility|viewer_id' => 
                array (
                  0 => ':global',
                ),
                'acting_uid' => 
                array (
                  0 => 'author',
                  1 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'node',
                  1 => 'author',
                  2 => ':global',
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
          '#type' => 'action',
          '#settings' => 
          array (
            'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
            'public_name' => '',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '<div class="activity-log-content">[author:user] added the [node:type-name] [node:title-link]</div>
<div class="activity-log-time"><a href="[node:node-url]">[node:since] ago</a></div>',
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
                'node terms' => 'node terms',
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'stream_owner' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '',
            'tid' => '8',
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
                  0 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'node',
                  1 => 'author',
                  2 => ':global',
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
          '#name' => 'activity_log_log_action',
          '#info' => 
          array (
            'label' => 'Log activity for related taxonomy terms',
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
          '#weight' => 0,
        ),
        2 => 
        array (
          '#weight' => 0,
          '#info' => 
          array (
            'label' => 'Log activity for the acting user\'s relationships',
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
                'template' => '<div class="activity-log-content">[author:user] added the [node:type-name] [node:title-link]</div>
<div class="activity-log-time"><a href="[node:node-url]">[node:since] ago</a></div>',
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
                'acting user relationships' => 'acting user relationships',
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'node terms' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'stream_owner' => 'stream_owner',
                'everyone' => 0,
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '',
            'tid' => '9',
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
                  0 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'node',
                  1 => 'author',
                  2 => ':global',
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
  if (module_exists('og')) {
    $ret['rules_activity_log_node_insert']['#conditions'][] = array (
      '#type' => 'condition',
      '#settings' => 
      array (
        '#argument map' => 
        array (
          'group' => 'node',
        ),
      ),
      '#name' => 'og_rules_condition_content_is_group_post',
      '#info' => 
      array (
        'label' => 'Content is a group post',
        'arguments' => 
        array (
          'group' => 
          array (
            'type' => 'node',
            'label' => 'Group post',
          ),
        ),
        'module' => 'Organic groups',
      ),
      '#negate' => 1,
      '#weight' => 0,
    );
  }
  return $ret;
}

/**
 * Node creation in a group
 */
function activity_log_rules_defaults_node_insert_og() {
  return array(
    'rules_activity_log_node_insert_og' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_node_insert',
      '#label' => 'Log activity when a node is created in a group',
      '#active' => 1,
      '#weight' => '0',
      '#categories' => 
      array (
        0 => 'activity_log',
        1 => 'node',
        2 => 'og',
      ),
      '#status' => 'custom',
      '#conditions' => 
      array (
        0 => 
        array (
          '#weight' => 0,
          '#info' => 
          array (
            'label' => 'Updated content is published',
            'arguments' => 
            array (
              'node' => 
              array (
                'type' => 'node',
                'label' => 'Content',
              ),
            ),
            'module' => 'Node',
          ),
          '#name' => 'rules_condition_content_is_published',
          '#settings' => 
          array (
            '#argument map' => 
            array (
              'node' => 'node',
            ),
          ),
          '#type' => 'condition',
        ),
        1 => 
        array (
          '#type' => 'condition',
          '#settings' => 
          array (
            '#argument map' => 
            array (
              'group' => 'node',
            ),
          ),
          '#name' => 'og_rules_condition_content_is_group_post',
          '#info' => 
          array (
            'label' => 'Content is a group post',
            'arguments' => 
            array (
              'group' => 
              array (
                'type' => 'node',
                'label' => 'Group post',
              ),
            ),
            'module' => 'Organic groups',
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
                'template' => '<div class="activity-log-content">[author:user] added the [node:type-name] [node:title-link] in [node:ogname-title-link]</div>
<div class="activity-log-time"><a href="[node:node-url]">[node:since] ago</a></div>',
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
                'custom' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'node terms' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'stream_owner' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '[author:uid]',
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
                  0 => ':global',
                ),
                'visibility|viewer_id' => 
                array (
                  0 => ':global',
                ),
                'acting_uid' => 
                array (
                  0 => 'author',
                  1 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'node',
                  1 => 'author',
                  2 => ':global',
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
        1 => 
        array (
          '#info' => 
          array (
            'label' => 'Log activity for active group',
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
                'template' => '<div class="activity-log-content">[author:user] added the [node:type-name] [node:title-link]</div>
<div class="activity-log-time"><a href="[node:node-url]">[node:since] ago</a></div>',
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
                'active group' => 'active group',
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'node terms' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'stream_owner' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '',
            'tid' => '5',
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
                  0 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'node',
                  1 => 'author',
                  2 => ':global',
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
        2 => 
        array (
          '#weight' => 0,
          '#type' => 'action',
          '#settings' => 
          array (
            'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
            'public_name' => '',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '<div class="activity-log-content">[author:user] added the [node:type-name] [node:title-link] in [node:ogname-title-link]</div>
<div class="activity-log-time"><a href="[node:node-url]">[node:since] ago</a></div>',
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
                'active group members' => 'active group members',
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'node terms' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'stream_owner' => 'stream_owner',
                'everyone' => 0,
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '',
            'tid' => '6',
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
                  0 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'node',
                  1 => 'author',
                  2 => ':global',
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
          '#name' => 'activity_log_log_action',
          '#info' => 
          array (
            'label' => 'Log activity for members of the active group',
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
        ),
        3 => 
        array (
          '#info' => 
          array (
            'label' => 'Log activity for related taxonomy terms',
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
                'template' => '<div class="activity-log-content">[author:user] added the [node:type-name] [node:title-link] in [node:ogname-title-link]</div>
<div class="activity-log-time"><a href="[node:node-url]">[node:since] ago</a></div>',
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
                'node terms' => 'node terms',
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'stream_owner' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '',
            'tid' => '7',
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
                  0 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'node',
                  1 => 'author',
                  2 => ':global',
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
      ),
      '#version' => 6003,
    ),
  );
}

/**
 * Self status update
 */
function activity_log_rules_defaults_facebook_status_insert_user_self() {
  return array(
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
          '#type' => 'action',
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
                'acting user' => 'acting user',
                'mentioned users' => 'mentioned users',
                'hashtag terms' => 'hashtag terms',
                'custom' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'status recipient' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'stream_owner' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'mentioned users' => 0,
                'status recipient' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '[status:sender-uid]',
            'tid' => '1',
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
          '#name' => 'activity_log_log_action',
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
          '#weight' => 0,
        ),
        1 => 
        array (
          '#weight' => 0,
          '#info' => 
          array (
            'label' => 'Log activity for the acting user\'s relationships',
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
                'acting user relationships' => 'acting user relationships',
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'mentioned users' => 0,
                'hashtag terms' => 0,
                'status recipient' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'stream_owner' => 'stream_owner',
                'everyone' => 0,
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'mentioned users' => 0,
                'status recipient' => 0,
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
 * Other status update
 */
function activity_log_rules_defaults_facebook_status_insert_other() {
  return array (
    'rules_activity_log_facebook_status_insert_other' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_facebook_status_save',
      '#label' => 'Log activity when a user sends a status message',
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
          '#negate' => 1,
          '#weight' => 0,
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
        ),
      ),
      '#actions' => 
      array (
        0 => 
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
                'hashtag terms' => 'hashtag terms',
                'status recipient' => 'status recipient',
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'stream_owner_id' => '[status:recipient-id]',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'stream_owner' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'mentioned users' => 0,
                'status recipient' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '[status:sender-uid]',
            'tid' => '1',
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
        1 => 
        array (
          '#weight' => 0,
          '#type' => 'action',
          '#settings' => 
          array (
            'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
            'public_name' => '',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '<div class="activity-log-content">[status:sender-themed] wrote a message to [status:recipient-link]</div>
<div class="activity-log-time"><a href="[status:status-url]">[status:created]</a></div>',
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
                'custom' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'mentioned users' => 0,
                'hashtag terms' => 0,
                'status recipient' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'stream_owner' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'mentioned users' => 0,
                'status recipient' => 0,
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
          '#name' => 'activity_log_log_action',
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
        ),
        2 => 
        array (
          '#weight' => 0,
          '#info' => 
          array (
            'label' => 'Log activity for members of the active group',
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
                'active group members' => 'active group members',
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'mentioned users' => 0,
                'hashtag terms' => 0,
                'status recipient' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'stream_owner' => 'stream_owner',
                'everyone' => 0,
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'mentioned users' => 0,
                'status recipient' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '',
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

/**
 * Self status update with attachment
 */
function activity_log_rules_defaults_fbsmp_insert_user_self() {
  return array(
    'rules_activity_log_fbsmp_insert_user_self' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_fbsmp_add_status',
      '#label' => 'Log activity when a user saves a personal status update with an attachment',
      '#active' => 1,
      '#weight' => '0',
      '#categories' => 
      array (
        0 => 'activity_log',
        1 => 'fbsmp',
      ),
      '#status' => 'custom',
      '#conditions' => 
      array (
        0 => 
        array (
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
          '#type' => 'action',
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
                'acting user' => 'acting user',
                'custom' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'stream_owner' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '[status:sender-uid]',
            'tid' => '1',
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
          '#name' => 'activity_log_log_action',
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
          '#weight' => 0,
        ),
        1 => 
        array (
          '#weight' => 0,
          '#info' => 
          array (
            'label' => 'Log activity for the acting user\'s relationships',
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
                'acting user relationships' => 'acting user relationships',
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'stream_owner' => 'stream_owner',
                'everyone' => 0,
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
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
 * Other status update with attachment
 */
function activity_log_rules_defaults_fbsmp_insert_other() {
  return array(
    'rules_activity_log_fbsmp_insert_other' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_fbsmp_add_status',
      '#label' => 'Log activity when a user sends a status message with an attachment',
      '#active' => 1,
      '#weight' => '0',
      '#categories' => 
      array (
        0 => 'activity_log',
        1 => 'fbsmp',
      ),
      '#status' => 'custom',
      '#conditions' => 
      array (
        0 => 
        array (
          '#name' => 'fbss_rules_is_self',
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
          '#settings' => 
          array (
            '#argument map' => 
            array (
              'status' => 'status',
            ),
          ),
          '#type' => 'condition',
          '#weight' => 0,
          '#negate' => 1,
        ),
      ),
      '#actions' => 
      array (
        0 => 
        array (
          '#type' => 'action',
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
                'hashtag terms' => 'hashtag terms',
                'status recipient' => 'status recipient',
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'stream_owner_id' => '[status:recipient-id]',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'stream_owner' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'mentioned users' => 0,
                'status recipient' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '[status:sender-uid]',
            'tid' => '1',
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
          '#name' => 'activity_log_log_action',
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
          '#weight' => 0,
        ),
        1 => 
        array (
          '#weight' => 0,
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
                'template' => '<div class="activity-log-content">[status:sender-themed] sent a [attachment:attachment-type] to [status:recipient-link]</div>
<div class="activity-log-time"><a href="[status:status-url]">[status:created]</a></div>',
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
                'custom' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'stream_owner' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
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
                  1 => 'attachment',
                  2 => ':global',
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
        2 => 
        array (
          '#type' => 'action',
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
                'active group members' => 'active group members',
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'mentioned users' => 0,
                'hashtag terms' => 0,
                'status recipient' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'stream_owner' => 'stream_owner',
                'everyone' => 0,
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'mentioned users' => 0,
                'status recipient' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '',
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
          '#name' => 'activity_log_log_action',
          '#info' => 
          array (
            'label' => 'Log activity for members of the active group',
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
          '#weight' => 0,
        ),
      ),
      '#version' => 6003,
    ),
  );
}

/**
 * Join group
 */
function activity_log_rules_defaults_og_join() {
  return array(
    'rules_activity_log_og_join' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_og_user_insert',
      '#label' => 'Log activity when a user joins a group',
      '#active' => 1,
      '#weight' => '0',
      '#categories' => 
      array (
        0 => 'activity_log',
        1 => 'og',
      ),
      '#status' => 'custom',
      '#conditions' => 
      array (
      ),
      '#actions' => 
      array (
        0 => 
        array (
          '#type' => 'action',
          '#settings' => 
          array (
            'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
            'public_name' => 'Joining a group',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '<div class="activity-log-content">[account:user] joined the group [group:title-link]</div>',
              ),
            ),
            'grouping' => 
            array (
              'group_method' => 'user_action',
              'group_interval' => '259200',
              'group_max' => '10',
              'group_summary' => '[group:title-link]',
              'collapse_method' => 'activity_log_collapse_inline',
              'templates' => 
              array (
                'en' => 
                array (
                  'template' => '<div class="activity-log-content">[account:user] joined the groups [collection]</div>',
                ),
              ),
            ),
            'visibility' => 
            array (
              'stream_owner_entity_group' => 
              array (
                'acting user' => 'acting user',
                'custom' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'node terms' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'stream_owner' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '[account:uid]',
            'tid' => '10',
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
                  0 => 'group',
                  1 => ':global',
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
                  0 => 'account',
                  1 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'account',
                  1 => 'group',
                  2 => ':global',
                ),
                'grouping|templates|en|template' => 
                array (
                  0 => 'account',
                  1 => ':global',
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
          '#name' => 'activity_log_log_action',
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
          '#weight' => 0,
        ),
        1 => 
        array (
          '#info' => 
          array (
            'label' => 'Log activity for the acting user\'s relationships',
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
            'public_name' => 'Joining a group',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '<div class="activity-log-content">[account:user] joined the group [group:title-link]</div>',
              ),
            ),
            'grouping' => 
            array (
              'group_method' => 'user_action',
              'group_interval' => '259200',
              'group_max' => '10',
              'group_summary' => '[group:title-link]',
              'collapse_method' => 'activity_log_collapse_inline',
              'templates' => 
              array (
                'en' => 
                array (
                  'template' => '<div class="activity-log-content">[account:user] joined the groups [collection]</div>',
                ),
              ),
            ),
            'visibility' => 
            array (
              'stream_owner_entity_group' => 
              array (
                'acting user relationships' => 'acting user relationships',
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'node terms' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'stream_owner' => 'stream_owner',
                'everyone' => 0,
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '[account:uid]',
            'tid' => '11',
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
                  0 => 'group',
                  1 => ':global',
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
                  0 => 'account',
                  1 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'account',
                  1 => 'group',
                  2 => ':global',
                ),
                'grouping|templates|en|template' => 
                array (
                  0 => 'account',
                  1 => ':global',
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
        2 => 
        array (
          '#weight' => 0,
          '#info' => 
          array (
            'label' => 'Log activity for the joined group',
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
            'public_name' => 'Joining a group',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '<div class="activity-log-content">[account:user] joined the group</div>',
              ),
            ),
            'grouping' => 
            array (
              'group_method' => 'target_action',
              'group_interval' => '86400',
              'group_max' => '100',
              'group_summary' => '',
              'collapse_method' => 'activity_log_collapse_inline',
              'templates' => 
              array (
                'en' => 
                array (
                  'template' => '<div class="activity-log-content">[names] joined the group</div>',
                ),
              ),
            ),
            'visibility' => 
            array (
              'stream_owner_entity_group' => 
              array (
                'active group' => 'active group',
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
                'node terms' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'stream_owner' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '',
            'tid' => '12',
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
                  0 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'account',
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
 * Request relationship
 */
function activity_log_rules_defaults_ur_request() {
  return array(
    'rules_activity_log_ur_request' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_user_relationships_request',
      '#label' => 'Log activity when a user creates a relationship',
      '#active' => 1,
      '#weight' => '0',
      '#categories' => 
      array (
        0 => 'activity_log',
        1 => 'user_relationships',
      ),
      '#status' => 'custom',
      '#conditions' => 
      array (
      ),
      '#actions' => 
      array (
        0 => 
        array (
          '#type' => 'action',
          '#settings' => 
          array (
            'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
            'public_name' => 'New user relationships',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '<div class="activity-log-content">[requester:user] [relationship:relationship-name]ed [requestee:user]</div>',
              ),
            ),
            'grouping' => 
            array (
              'group_method' => 'user_action',
              'group_interval' => '86400',
              'group_max' => '10',
              'group_summary' => '[requestee:user]',
              'collapse_method' => 'activity_log_collapse_inline',
              'templates' => 
              array (
                'en' => 
                array (
                  'template' => '<div class="activity-log-content">[requester:user] [relationship:relationship-name]ed [collection]</div>',
                ),
              ),
            ),
            'visibility' => 
            array (
              'stream_owner_entity_group' => 
              array (
                'acting user' => 'acting user',
                'custom' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'everyone' => 'everyone',
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'stream_owner' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '[requester:uid]',
            'tid' => '13',
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
                  0 => 'requestee',
                  1 => ':global',
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
                  0 => 'requester',
                  1 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'requester',
                  1 => 'requestee',
                  2 => 'relationship',
                  3 => ':global',
                ),
                'grouping|templates|en|template' => 
                array (
                  0 => 'requester',
                  1 => 'relationship',
                  2 => ':global',
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
          '#name' => 'activity_log_log_action',
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
          '#weight' => 0,
        ),
        1 => 
        array (
          '#weight' => 0,
          '#info' => 
          array (
            'label' => 'Log activity for the acting user\'s relationships',
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
            'public_name' => 'New user relationships',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '<div class="activity-log-content">[requester:user] [relationship:relationship-name]ed [requestee:user]</div>',
              ),
            ),
            'grouping' => 
            array (
              'group_method' => 'user_action',
              'group_interval' => '86400',
              'group_max' => '10',
              'group_summary' => '[requestee:user]',
              'collapse_method' => 'activity_log_collapse_inline',
              'templates' => 
              array (
                'en' => 
                array (
                  'template' => '<div class="activity-log-content">[requester:user] [relationship:relationship-name]ed [collection]</div>',
                ),
              ),
            ),
            'visibility' => 
            array (
              'stream_owner_entity_group' => 
              array (
                'acting user relationships' => 'acting user relationships',
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'active group' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'stream_owner_id' => '',
              'stream_owner_type' => 'user',
              'viewer_entity_group' => 
              array (
                'stream_owner' => 'stream_owner',
                'everyone' => 0,
                'everyone_except_active' => 0,
                'everyone_except_custom' => 0,
                'custom' => 0,
                'acting user' => 0,
                'target entity' => 0,
                'not_stream_owner' => 0,
                'active group members' => 0,
                'active group admin' => 0,
                'acting user relationships' => 0,
                'custom user relationships' => 0,
                'acting user relationships 1' => 0,
                'custom user relationships 1' => 0,
                'active group relationships acting user' => 0,
                'active group relationships custom user' => 0,
                'active group relationships 1 acting user' => 0,
                'active group relationships 1 custom user' => 0,
              ),
              'viewer_id' => '',
            ),
            'cache' => 
            array (
              'cache' => 1,
              'resources' => '',
            ),
            'acting_uid' => '[requester:uid]',
            'tid' => '14',
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
                  0 => 'requestee',
                  1 => ':global',
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
                  0 => 'requester',
                  1 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'requester',
                  1 => 'requestee',
                  2 => 'relationship',
                  3 => ':global',
                ),
                'grouping|templates|en|template' => 
                array (
                  0 => 'requester',
                  1 => 'relationship',
                  2 => ':global',
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
