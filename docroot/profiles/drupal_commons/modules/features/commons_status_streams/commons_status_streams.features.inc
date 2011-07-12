<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function commons_status_streams_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_rules_defaults().
 */
function commons_status_streams_rules_defaults() {
  return array(
    'rules' => array(
      'rules_cc_activity_comment_insert' => array(
        '#type' => 'rule',
        '#set' => 'event_comment_insert',
        '#label' => 'Log activity when adding a comment',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'commons_core',
          '1' => 'activity_log',
          'commons_status_streams' => 'commons_status_streams',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Log activity for active group',
              'label callback' => FALSE,
              'module' => 'Activity Log',
              'eval input' => array(
                '0' => 'placeholder',
                '1' => 'grouping|group_summary',
                '2' => 'visibility|stream_owner_id',
                '3' => 'visibility|viewer_id',
                '4' => 'acting_uid',
                '5' => 'templates|en|template',
                '6' => 'grouping|templates|en|template',
              ),
            ),
            '#name' => 'activity_log_log_action',
            '#settings' => array(
              'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
              'public_name' => 'User comments on a content in a group',
              'templates' => array(
                'en' => array(
                  'template' => '[comment_author:user] commented on the [node:type-name] [node:title-link]',
                ),
              ),
              'grouping' => array(
                'group_method' => 'action',
                'group_interval' => '86400',
                'group_max' => '10',
                'group_summary' => '[node:title-link]',
                'collapse_method' => 'activity_log_collapse_inline',
                'templates' => array(
                  'en' => array(
                    'template' => '[names] commented on [collection]',
                  ),
                ),
              ),
              'visibility' => array(
                'stream_owner_entity_group' => array(
                  'active groups' => 'active groups',
                  'active groups relationships 1 custom user' => 0,
                  'active groups relationships 1 acting user' => 0,
                  'active groups relationships custom user' => 0,
                  'node terms' => 0,
                  'status commenters' => 0,
                  'hashtag terms' => 0,
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
                'stream_owner_id' => '',
                'stream_owner_type' => 'user',
                'viewer_entity_group' => array(
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
              'cache' => array(
                'cache' => 1,
                'resources' => '',
              ),
              'acting_uid' => '',
              'tid' => '5',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'placeholder' => array(
                    '0' => ':global',
                  ),
                  'grouping|group_summary' => array(
                    '0' => 'node',
                    '1' => ':global',
                  ),
                  'visibility|stream_owner_id' => array(
                    '0' => ':global',
                  ),
                  'visibility|viewer_id' => array(
                    '0' => ':global',
                  ),
                  'acting_uid' => array(
                    '0' => ':global',
                  ),
                  'templates|en|template' => array(
                    '0' => 'comment_author',
                    '1' => 'node',
                    '2' => ':global',
                  ),
                  'grouping|templates|en|template' => array(
                    '0' => ':global',
                  ),
                ),
                'activity_log_input_evaluator_process' => array(
                  'placeholder' => TRUE,
                  'grouping|group_summary' => TRUE,
                  'visibility|stream_owner_id' => TRUE,
                  'visibility|viewer_id' => TRUE,
                  'acting_uid' => TRUE,
                  'templates|en|template' => TRUE,
                  'grouping|templates|en|template' => TRUE,
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_cc_activity_fbss_insert' => array(
        '#type' => 'rule',
        '#set' => 'event_facebook_status_save',
        '#label' => 'Log activity when a user saves a status',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'commons_core',
          '1' => 'activity_log',
          '2' => 'facebook_status',
          'commons_status_streams' => 'commons_status_streams',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Log activity',
              'module' => 'Activity Log',
              'eval input' => array(
                '0' => 'placeholder',
                '1' => 'grouping|group_summary',
                '2' => 'visibility|stream_owner_id',
                '3' => 'visibility|viewer_id',
                '4' => 'acting_uid',
                '5' => 'templates|en|template',
                '6' => 'grouping|templates|en|template',
              ),
            ),
            '#name' => 'activity_log_log_action',
            '#settings' => array(
              'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
              'public_name' => 'Status update',
              'templates' => array(
                'en' => array(
                  'template' => '[status:status-themed]',
                ),
              ),
              'grouping' => array(
                'group_method' => 'none',
                'group_interval' => '86400',
                'group_max' => '100',
                'group_summary' => '',
                'collapse_method' => 'activity_log_collapse_inline',
                'templates' => array(
                  'en' => array(
                    'template' => '',
                  ),
                ),
              ),
              'visibility' => array(
                'stream_owner_entity_group' => array(
                  'mentioned users' => 'mentioned users',
                  'target entity' => 'target entity',
                  'acting user' => 'acting user',
                  'active groups relationships 1 custom user' => 0,
                  'active groups relationships 1 acting user' => 0,
                  'active groups relationships custom user' => 0,
                  'node terms' => 0,
                  'status commenters' => 0,
                  'hashtag terms' => 0,
                  'active groups relationships acting user' => 0,
                  'custom user relationships 1' => 0,
                  'active groups' => 'active groups',
                  'active groups members' => 0,
                  'acting user relationships' => 0,
                  'acting user relationships 1' => 0,
                  'custom user relationships' => 0,
                  'custom' => 0,
                ),
                'stream_owner_id' => '',
                'stream_owner_type' => 'user',
                'viewer_entity_group' => array(
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
              'cache' => array(
                'cache' => 1,
                'resources' => '',
              ),
              'acting_uid' => '[status:sender-uid]',
              'tid' => '14',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'placeholder' => array(
                    '0' => ':global',
                  ),
                  'grouping|group_summary' => array(
                    '0' => ':global',
                  ),
                  'visibility|stream_owner_id' => array(
                    '0' => ':global',
                  ),
                  'visibility|viewer_id' => array(
                    '0' => ':global',
                  ),
                  'acting_uid' => array(
                    '0' => 'status',
                    '1' => ':global',
                  ),
                  'templates|en|template' => array(
                    '0' => 'status',
                    '1' => ':global',
                  ),
                  'grouping|templates|en|template' => array(
                    '0' => ':global',
                  ),
                ),
                'activity_log_input_evaluator_process' => array(
                  'placeholder' => TRUE,
                  'grouping|group_summary' => TRUE,
                  'visibility|stream_owner_id' => TRUE,
                  'visibility|viewer_id' => TRUE,
                  'acting_uid' => TRUE,
                  'templates|en|template' => TRUE,
                  'grouping|templates|en|template' => TRUE,
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_cc_activity_flag_bookmark_node' => array(
        '#type' => 'rule',
        '#set' => 'event_flag_flagged_bookmarks',
        '#label' => 'Log activity when a user bookmarks a node',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'commons_core',
          '1' => 'activity_log',
          'commons_status_streams' => 'commons_status_streams',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Bookmarked node is published',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_published',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
              'public_name' => 'User bookmarks content',
              'templates' => array(
                'en' => array(
                  'template' => 'You bookmarked the [node:type-name] [node:title-link]',
                ),
              ),
              'grouping' => array(
                'group_method' => 'none',
                'group_interval' => '86400',
                'group_max' => '100',
                'group_summary' => '',
                'collapse_method' => 'activity_log_collapse_inline',
                'templates' => array(
                  'en' => array(
                    'template' => '',
                  ),
                ),
              ),
              'visibility' => array(
                'stream_owner_entity_group' => array(
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
                'viewer_entity_group' => array(
                  'acting user' => 'acting user',
                  'active groups relationships 1 acting user' => 0,
                  'active groups relationships custom user' => 0,
                  'active groups relationships 1 custom user' => 0,
                  'status commenters' => 0,
                  'everyone' => 0,
                  'mentioned users' => 0,
                  'active groups relationships acting user' => 0,
                  'custom user relationships 1' => 0,
                  'target entity' => 0,
                  'active groups members' => 0,
                  'acting user relationships' => 0,
                  'acting user relationships 1' => 0,
                  'custom user relationships' => 0,
                  'custom' => 0,
                ),
                'viewer_id' => '',
              ),
              'cache' => array(
                'cache' => 1,
                'resources' => '',
              ),
              'acting_uid' => '[flagging_user:uid]',
              'tid' => '2',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'placeholder' => array(
                    '0' => ':global',
                  ),
                  'grouping|group_summary' => array(
                    '0' => ':global',
                  ),
                  'visibility|stream_owner_id' => array(
                    '0' => ':global',
                  ),
                  'visibility|viewer_id' => array(
                    '0' => ':global',
                  ),
                  'acting_uid' => array(
                    '0' => 'flagging_user',
                    '1' => ':global',
                  ),
                  'templates|en|template' => array(
                    '0' => 'node',
                    '1' => ':global',
                  ),
                  'grouping|templates|en|template' => array(
                    '0' => ':global',
                  ),
                ),
                'activity_log_input_evaluator_process' => array(
                  'placeholder' => TRUE,
                  'grouping|group_summary' => TRUE,
                  'visibility|stream_owner_id' => TRUE,
                  'visibility|viewer_id' => TRUE,
                  'acting_uid' => TRUE,
                  'templates|en|template' => TRUE,
                  'grouping|templates|en|template' => TRUE,
                ),
              ),
            ),
            '#name' => 'activity_log_log_action',
            '#info' => array(
              'label' => 'Log activity for the flagging user',
              'label callback' => FALSE,
              'module' => 'Activity Log',
              'eval input' => array(
                '0' => 'placeholder',
                '1' => 'grouping|group_summary',
                '2' => 'visibility|stream_owner_id',
                '3' => 'visibility|viewer_id',
                '4' => 'acting_uid',
                '5' => 'templates|en|template',
                '6' => 'grouping|templates|en|template',
              ),
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'rules_cc_activity_node_insert' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Log activity when a user adds a node',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'commons_core',
          '1' => 'activity_log',
          'commons_status_streams' => 'commons_status_streams',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_published',
            '#info' => array(
              'label' => 'Created content is published',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Log activity',
              'module' => 'Activity Log',
              'eval input' => array(
                '0' => 'placeholder',
                '1' => 'grouping|group_summary',
                '2' => 'visibility|stream_owner_id',
                '3' => 'visibility|viewer_id',
                '4' => 'acting_uid',
                '5' => 'templates|en|template',
                '6' => 'grouping|templates|en|template',
              ),
            ),
            '#name' => 'activity_log_log_action',
            '#settings' => array(
              'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
              'public_name' => 'User creates content',
              'templates' => array(
                'en' => array(
                  'template' => '[author:user] created the [node:type-name] [node:title-link]',
                ),
              ),
              'grouping' => array(
                'group_method' => 'none',
                'group_interval' => '86400',
                'group_max' => '100',
                'group_summary' => '',
                'collapse_method' => 'activity_log_collapse_inline',
                'templates' => array(
                  'en' => array(
                    'template' => '',
                  ),
                ),
              ),
              'visibility' => array(
                'stream_owner_entity_group' => array(
                  'active groups' => 'active groups',
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
                  'target entity' => 0,
                  'active groups members' => 0,
                  'acting user relationships' => 0,
                  'acting user relationships 1' => 0,
                  'custom user relationships' => 0,
                  'custom' => 0,
                ),
                'stream_owner_id' => '',
                'stream_owner_type' => 'user',
                'viewer_entity_group' => array(
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
              'cache' => array(
                'cache' => 1,
                'resources' => '',
              ),
              'acting_uid' => '[author:uid]',
              'tid' => '13',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'placeholder' => array(
                    '0' => ':global',
                  ),
                  'grouping|group_summary' => array(
                    '0' => ':global',
                  ),
                  'visibility|stream_owner_id' => array(
                    '0' => ':global',
                  ),
                  'visibility|viewer_id' => array(
                    '0' => ':global',
                  ),
                  'acting_uid' => array(
                    '0' => 'author',
                    '1' => ':global',
                  ),
                  'templates|en|template' => array(
                    '0' => 'node',
                    '1' => 'author',
                    '2' => ':global',
                  ),
                  'grouping|templates|en|template' => array(
                    '0' => ':global',
                  ),
                ),
                'activity_log_input_evaluator_process' => array(
                  'placeholder' => TRUE,
                  'grouping|group_summary' => TRUE,
                  'visibility|stream_owner_id' => TRUE,
                  'visibility|viewer_id' => TRUE,
                  'acting_uid' => TRUE,
                  'templates|en|template' => TRUE,
                  'grouping|templates|en|template' => TRUE,
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_cc_activity_node_wiki_edit' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Log activity when a user edits a wiki page',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'commons_core',
          '1' => 'activity_log',
          'commons_status_streams' => 'commons_status_streams',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '1' => array(
            '#weight' => -1,
            '#info' => array(
              'label' => 'Edited content is a wiki page',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_type',
            '#settings' => array(
              'type' => array(
                'wiki' => 'wiki',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_published',
            '#info' => array(
              'label' => 'Edited wiki page is published',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
              'public_name' => 'User edits a wiki page',
              'templates' => array(
                'en' => array(
                  'template' => '[user:user] edited the wiki page [node:title-link]',
                ),
              ),
              'grouping' => array(
                'group_method' => 'target_action',
                'group_interval' => '86400',
                'group_max' => '100',
                'group_summary' => '[node:title-link]',
                'collapse_method' => 'activity_log_collapse_inline',
                'templates' => array(
                  'en' => array(
                    'template' => '[names] edited the wiki page [node:title-link]',
                  ),
                ),
              ),
              'visibility' => array(
                'stream_owner_entity_group' => array(
                  'active groups' => 'active groups',
                  'active groups relationships 1 custom user' => 0,
                  'active groups relationships 1 acting user' => 0,
                  'active groups relationships custom user' => 0,
                  'node terms' => 0,
                  'status commenters' => 0,
                  'hashtag terms' => 0,
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
                'stream_owner_id' => '',
                'stream_owner_type' => 'user',
                'viewer_entity_group' => array(
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
              'cache' => array(
                'cache' => 1,
                'resources' => '',
              ),
              'acting_uid' => '',
              'tid' => '7',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'placeholder' => array(
                    '0' => ':global',
                  ),
                  'grouping|group_summary' => array(
                    '0' => 'node',
                    '1' => ':global',
                  ),
                  'visibility|stream_owner_id' => array(
                    '0' => ':global',
                  ),
                  'visibility|viewer_id' => array(
                    '0' => ':global',
                  ),
                  'acting_uid' => array(
                    '0' => ':global',
                  ),
                  'templates|en|template' => array(
                    '0' => 'node',
                    '1' => 'user',
                    '2' => ':global',
                  ),
                  'grouping|templates|en|template' => array(
                    '0' => 'node',
                    '1' => ':global',
                  ),
                ),
                'activity_log_input_evaluator_process' => array(
                  'placeholder' => TRUE,
                  'grouping|group_summary' => TRUE,
                  'visibility|stream_owner_id' => TRUE,
                  'visibility|viewer_id' => TRUE,
                  'acting_uid' => TRUE,
                  'templates|en|template' => TRUE,
                  'grouping|templates|en|template' => TRUE,
                ),
              ),
            ),
            '#name' => 'activity_log_log_action',
            '#info' => array(
              'label' => 'Log activity for active group',
              'label callback' => FALSE,
              'module' => 'Activity Log',
              'eval input' => array(
                '0' => 'placeholder',
                '1' => 'grouping|group_summary',
                '2' => 'visibility|stream_owner_id',
                '3' => 'visibility|viewer_id',
                '4' => 'acting_uid',
                '5' => 'templates|en|template',
                '6' => 'grouping|templates|en|template',
              ),
            ),
          ),
          '1' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
              'public_name' => 'User edits a wiki page',
              'templates' => array(
                'en' => array(
                  'template' => '[user:user] edited the wiki page [node:title-link]',
                ),
              ),
              'grouping' => array(
                'group_method' => 'none',
                'group_interval' => '86400',
                'group_max' => '100',
                'group_summary' => '',
                'collapse_method' => 'activity_log_collapse_inline',
                'templates' => array(
                  'en' => array(
                    'template' => '',
                  ),
                ),
              ),
              'visibility' => array(
                'stream_owner_entity_group' => array(
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
                'viewer_entity_group' => array(
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
              'cache' => array(
                'cache' => 1,
                'resources' => '',
              ),
              'acting_uid' => '[user:uid]',
              'tid' => '11',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'placeholder' => array(
                    '0' => ':global',
                  ),
                  'grouping|group_summary' => array(
                    '0' => ':global',
                  ),
                  'visibility|stream_owner_id' => array(
                    '0' => ':global',
                  ),
                  'visibility|viewer_id' => array(
                    '0' => ':global',
                  ),
                  'acting_uid' => array(
                    '0' => 'user',
                    '1' => ':global',
                  ),
                  'templates|en|template' => array(
                    '0' => 'node',
                    '1' => 'user',
                    '2' => ':global',
                  ),
                  'grouping|templates|en|template' => array(
                    '0' => ':global',
                  ),
                ),
                'activity_log_input_evaluator_process' => array(
                  'placeholder' => TRUE,
                  'grouping|group_summary' => TRUE,
                  'visibility|stream_owner_id' => TRUE,
                  'visibility|viewer_id' => TRUE,
                  'acting_uid' => TRUE,
                  'templates|en|template' => TRUE,
                  'grouping|templates|en|template' => TRUE,
                ),
              ),
            ),
            '#name' => 'activity_log_log_action',
            '#info' => array(
              'label' => 'Log activity for the acting user',
              'label callback' => FALSE,
              'module' => 'Activity Log',
              'eval input' => array(
                '0' => 'placeholder',
                '1' => 'grouping|group_summary',
                '2' => 'visibility|stream_owner_id',
                '3' => 'visibility|viewer_id',
                '4' => 'acting_uid',
                '5' => 'templates|en|template',
                '6' => 'grouping|templates|en|template',
              ),
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'rules_cc_activity_og_join' => array(
        '#type' => 'rule',
        '#set' => 'event_og_user_insert',
        '#label' => 'Log activity when a user joins a group',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'commons_core',
          '1' => 'activity_log',
          'commons_status_streams' => 'commons_status_streams',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#type' => 'action',
            '#settings' => array(
              'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
              'public_name' => 'User joins a group',
              'templates' => array(
                'en' => array(
                  'template' => '[account:user] joined the group [group:title-link]',
                ),
              ),
              'grouping' => array(
                'group_method' => 'target_action',
                'group_interval' => '86400',
                'group_max' => '100',
                'group_summary' => '[group:title-link]',
                'collapse_method' => 'activity_log_collapse_inline',
                'templates' => array(
                  'en' => array(
                    'template' => '[names] joined the group [collection]',
                  ),
                ),
              ),
              'visibility' => array(
                'stream_owner_entity_group' => array(
                  'active groups' => 'active groups',
                  'active groups relationships 1 custom user' => 0,
                  'active groups relationships 1 acting user' => 0,
                  'active groups relationships custom user' => 0,
                  'node terms' => 0,
                  'status commenters' => 0,
                  'hashtag terms' => 0,
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
                'stream_owner_id' => '',
                'stream_owner_type' => 'user',
                'viewer_entity_group' => array(
                  'active groups members' => 'active groups members',
                  'active groups relationships 1 acting user' => 0,
                  'active groups relationships custom user' => 0,
                  'active groups relationships 1 custom user' => 0,
                  'status commenters' => 0,
                  'everyone' => 0,
                  'mentioned users' => 0,
                  'active groups relationships acting user' => 0,
                  'custom user relationships 1' => 0,
                  'target entity' => 0,
                  'acting user' => 0,
                  'acting user relationships' => 0,
                  'acting user relationships 1' => 0,
                  'custom user relationships' => 0,
                  'custom' => 0,
                ),
                'viewer_id' => '',
              ),
              'cache' => array(
                'cache' => 1,
                'resources' => '',
              ),
              'acting_uid' => '',
              'tid' => '3',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'placeholder' => array(
                    '0' => ':global',
                  ),
                  'grouping|group_summary' => array(
                    '0' => 'group',
                    '1' => ':global',
                  ),
                  'visibility|stream_owner_id' => array(
                    '0' => ':global',
                  ),
                  'visibility|viewer_id' => array(
                    '0' => ':global',
                  ),
                  'acting_uid' => array(
                    '0' => ':global',
                  ),
                  'templates|en|template' => array(
                    '0' => 'account',
                    '1' => 'group',
                    '2' => ':global',
                  ),
                  'grouping|templates|en|template' => array(
                    '0' => ':global',
                  ),
                ),
                'activity_log_input_evaluator_process' => array(
                  'placeholder' => TRUE,
                  'grouping|group_summary' => TRUE,
                  'visibility|stream_owner_id' => TRUE,
                  'visibility|viewer_id' => TRUE,
                  'acting_uid' => TRUE,
                  'templates|en|template' => TRUE,
                  'grouping|templates|en|template' => TRUE,
                ),
              ),
            ),
            '#name' => 'activity_log_log_action',
            '#info' => array(
              'label' => 'Log activity for group members',
              'label callback' => FALSE,
              'module' => 'Activity Log',
              'eval input' => array(
                '0' => 'placeholder',
                '1' => 'grouping|group_summary',
                '2' => 'visibility|stream_owner_id',
                '3' => 'visibility|viewer_id',
                '4' => 'acting_uid',
                '5' => 'templates|en|template',
                '6' => 'grouping|templates|en|template',
              ),
            ),
            '#weight' => 0,
          ),
          '1' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Log activity for the joining user',
              'label callback' => FALSE,
              'module' => 'Activity Log',
              'eval input' => array(
                '0' => 'placeholder',
                '1' => 'grouping|group_summary',
                '2' => 'visibility|stream_owner_id',
                '3' => 'visibility|viewer_id',
                '4' => 'acting_uid',
                '5' => 'templates|en|template',
                '6' => 'grouping|templates|en|template',
              ),
            ),
            '#name' => 'activity_log_log_action',
            '#settings' => array(
              'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
              'public_name' => 'User joins a group',
              'templates' => array(
                'en' => array(
                  'template' => 'You joined the group [group:title-link]',
                ),
              ),
              'grouping' => array(
                'group_method' => 'user_action',
                'group_interval' => '86400',
                'group_max' => '10',
                'group_summary' => '[group:title-link]',
                'collapse_method' => 'activity_log_collapse_inline',
                'templates' => array(
                  'en' => array(
                    'template' => 'You joined the groups [collection]',
                  ),
                ),
              ),
              'visibility' => array(
                'stream_owner_entity_group' => array(
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
                'viewer_entity_group' => array(
                  'acting user' => 'acting user',
                  'active groups relationships 1 acting user' => 0,
                  'active groups relationships custom user' => 0,
                  'active groups relationships 1 custom user' => 0,
                  'status commenters' => 0,
                  'everyone' => 0,
                  'mentioned users' => 0,
                  'active groups relationships acting user' => 0,
                  'custom user relationships 1' => 0,
                  'target entity' => 0,
                  'active groups members' => 0,
                  'acting user relationships' => 0,
                  'acting user relationships 1' => 0,
                  'custom user relationships' => 0,
                  'custom' => 0,
                ),
                'viewer_id' => '',
              ),
              'cache' => array(
                'cache' => 1,
                'resources' => '',
              ),
              'acting_uid' => '[account:uid]',
              'tid' => '4',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'placeholder' => array(
                    '0' => ':global',
                  ),
                  'grouping|group_summary' => array(
                    '0' => 'group',
                    '1' => ':global',
                  ),
                  'visibility|stream_owner_id' => array(
                    '0' => ':global',
                  ),
                  'visibility|viewer_id' => array(
                    '0' => ':global',
                  ),
                  'acting_uid' => array(
                    '0' => 'account',
                    '1' => ':global',
                  ),
                  'templates|en|template' => array(
                    '0' => 'group',
                    '1' => ':global',
                  ),
                  'grouping|templates|en|template' => array(
                    '0' => ':global',
                  ),
                ),
                'activity_log_input_evaluator_process' => array(
                  'placeholder' => TRUE,
                  'grouping|group_summary' => TRUE,
                  'visibility|stream_owner_id' => TRUE,
                  'visibility|viewer_id' => TRUE,
                  'acting_uid' => TRUE,
                  'templates|en|template' => TRUE,
                  'grouping|templates|en|template' => TRUE,
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_cc_activity_ur_follow' => array(
        '#type' => 'rule',
        '#set' => 'event_user_relationships_approve',
        '#label' => 'Log activity when a user follows someone',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'commons_core',
          '1' => 'activity_log',
          'commons_status_streams' => 'commons_status_streams',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#info' => array(
              'label' => 'Log activity for the following user',
              'label callback' => FALSE,
              'module' => 'Activity Log',
              'eval input' => array(
                '0' => 'placeholder',
                '1' => 'grouping|group_summary',
                '2' => 'visibility|stream_owner_id',
                '3' => 'visibility|viewer_id',
                '4' => 'acting_uid',
                '5' => 'templates|en|template',
                '6' => 'grouping|templates|en|template',
              ),
            ),
            '#name' => 'activity_log_log_action',
            '#settings' => array(
              'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
              'public_name' => 'User follows someone',
              'templates' => array(
                'en' => array(
                  'template' => '[requester:user] followed [requestee:user]',
                ),
              ),
              'grouping' => array(
                'group_method' => 'user_action',
                'group_interval' => '86400',
                'group_max' => '100',
                'group_summary' => '[requestee:user]',
                'collapse_method' => 'activity_log_collapse_inline',
                'templates' => array(
                  'en' => array(
                    'template' => '[requester:user] followed [collection]',
                  ),
                ),
              ),
              'visibility' => array(
                'stream_owner_entity_group' => array(
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
                'viewer_entity_group' => array(
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
              'cache' => array(
                'cache' => 1,
                'resources' => '',
              ),
              'acting_uid' => '[requester:uid]',
              'tid' => '10',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'placeholder' => array(
                    '0' => ':global',
                  ),
                  'grouping|group_summary' => array(
                    '0' => 'requestee',
                    '1' => ':global',
                  ),
                  'visibility|stream_owner_id' => array(
                    '0' => ':global',
                  ),
                  'visibility|viewer_id' => array(
                    '0' => ':global',
                  ),
                  'acting_uid' => array(
                    '0' => 'requester',
                    '1' => ':global',
                  ),
                  'templates|en|template' => array(
                    '0' => 'requester',
                    '1' => 'requestee',
                    '2' => ':global',
                  ),
                  'grouping|templates|en|template' => array(
                    '0' => 'requester',
                    '1' => ':global',
                  ),
                ),
                'activity_log_input_evaluator_process' => array(
                  'placeholder' => TRUE,
                  'grouping|group_summary' => TRUE,
                  'visibility|stream_owner_id' => TRUE,
                  'visibility|viewer_id' => TRUE,
                  'acting_uid' => TRUE,
                  'templates|en|template' => TRUE,
                  'grouping|templates|en|template' => TRUE,
                ),
              ),
            ),
            '#type' => 'action',
            '#weight' => 0,
          ),
          '1' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Log activity for the followed user',
              'label callback' => FALSE,
              'module' => 'Activity Log',
              'eval input' => array(
                '0' => 'placeholder',
                '1' => 'grouping|group_summary',
                '2' => 'visibility|stream_owner_id',
                '3' => 'visibility|viewer_id',
                '4' => 'acting_uid',
                '5' => 'templates|en|template',
                '6' => 'grouping|templates|en|template',
              ),
            ),
            '#name' => 'activity_log_log_action',
            '#settings' => array(
              'placeholder' => '#!ACTIVITY_LOG_DELIMITER:',
              'public_name' => 'User is followed',
              'templates' => array(
                'en' => array(
                  'template' => '[requester:user] followed [requestee:user]',
                ),
              ),
              'grouping' => array(
                'group_method' => 'target_action',
                'group_interval' => '86400',
                'group_max' => '100',
                'group_summary' => '[requester:user]',
                'collapse_method' => 'activity_log_collapse_inline',
                'templates' => array(
                  'en' => array(
                    'template' => '[names] followed [requestee:user]',
                  ),
                ),
              ),
              'visibility' => array(
                'stream_owner_entity_group' => array(
                  'custom' => 'custom',
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
                  'acting user' => 0,
                  'active groups members' => 0,
                  'acting user relationships' => 0,
                  'acting user relationships 1' => 0,
                  'custom user relationships' => 0,
                ),
                'stream_owner_id' => '[requestee:uid]',
                'stream_owner_type' => 'user',
                'viewer_entity_group' => array(
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
              'cache' => array(
                'cache' => 1,
                'resources' => '',
              ),
              'acting_uid' => '',
              'tid' => '12',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'placeholder' => array(
                    '0' => ':global',
                  ),
                  'grouping|group_summary' => array(
                    '0' => 'requester',
                    '1' => ':global',
                  ),
                  'visibility|stream_owner_id' => array(
                    '0' => 'requestee',
                    '1' => ':global',
                  ),
                  'visibility|viewer_id' => array(
                    '0' => ':global',
                  ),
                  'acting_uid' => array(
                    '0' => ':global',
                  ),
                  'templates|en|template' => array(
                    '0' => 'requester',
                    '1' => 'requestee',
                    '2' => ':global',
                  ),
                  'grouping|templates|en|template' => array(
                    '0' => 'requestee',
                    '1' => ':global',
                  ),
                ),
                'activity_log_input_evaluator_process' => array(
                  'placeholder' => TRUE,
                  'grouping|group_summary' => TRUE,
                  'visibility|stream_owner_id' => TRUE,
                  'visibility|viewer_id' => TRUE,
                  'acting_uid' => TRUE,
                  'templates|en|template' => TRUE,
                  'grouping|templates|en|template' => TRUE,
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}
