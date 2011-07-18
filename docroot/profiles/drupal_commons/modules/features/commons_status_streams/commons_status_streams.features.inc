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
  $rules = array();
  if (module_exists('commons_wiki')) {
    $rules += commons_status_streams_activity_log_rules_defaults_edit_wiki();
  }
  if (module_exists('commons_document')) {
    $rules += commons_status_streams_activity_log_rules_defaults_change_document();
  }
  return array('rules' => $rules);
}

function commons_status_streams_activity_log_rules_defaults_edit_wiki() {
  return array (
    'rules_commons_activity_log_edit_wiki' =>
    array (
      '#type' => 'rule',
      '#set' => 'event_node_update',
      '#label' => 'Log activity when a user edits a wiki page',
      '#active' => 1,
      '#weight' => '0',
      '#categories' => 
      array (
        0 => 'commons',
        1 => 'activity_log',
        2 => 'node',
      ),
      '#status' => 'custom',
      '#conditions' => 
      array (
        0 => 
        array (
          '#type' => 'condition',
          '#settings' => 
          array (
            'type' => 
            array (
              'wiki' => 'wiki',
            ),
            '#argument map' => 
            array (
              'node' => 'node',
            ),
          ),
          '#name' => 'rules_condition_content_is_type',
          '#info' => 
          array (
            'label' => 'Edited content is a wiki page',
            'label callback' => false,
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
          '#weight' => 0,
        ),
        1 => 
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
        2 => 
        array (
          '#weight' => 0,
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
          '#name' => 'og_rules_condition_content_is_group_post',
          '#settings' => 
          array (
            '#argument map' => 
            array (
              'group' => 'node',
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
            'public_name' => 'Wiki page edits',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '<div class="activity-log-content">[user:user] edited the [node:type-name] [node:title-link] in [node:ogname-title-link]</div>
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
            'acting_uid' => '[user:uid]',
            'tid' => '15',
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
                  0 => 'user',
                  1 => ':global',
                ),
                'templates|en|template' => 
                array (
                  0 => 'node',
                  1 => 'user',
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
            'label' => 'Log activity for the active group',
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
            'public_name' => 'Wiki page edits',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '<div class="activity-log-content">[user:user] edited the [node:type-name] [node:title-link]</div>
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
            'tid' => '16',
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
                  1 => 'user',
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
            'public_name' => 'Wiki page edits',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '<div class="activity-log-content">[user:user] edited the [node:type-name] [node:title-link] in [node:ogname-title-link]</div>
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
            'tid' => '17',
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
                  1 => 'user',
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
}

function commons_status_streams_activity_log_rules_defaults_change_document() {
  return array (
    'rules_commons_activity_log_edit_document' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_node_update',
      '#label' => 'Log activity when the attachments in a Document change',
      '#active' => 0,
      '#weight' => '0',
      '#categories' => 
      array (
        0 => 'commons',
        1 => 'activity_log',
        2 => 'node',
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
            'type' => 
            array (
              'document' => 'document',
            ),
            '#argument map' => 
            array (
              'node' => 'node',
            ),
          ),
          '#name' => 'rules_condition_content_is_type',
          '#info' => 
          array (
            'label' => 'Edited content is a Document',
            'label callback' => false,
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
          '#weight' => 0,
        ),
        2 => 
        array (
          '#info' => 
          array (
            'label' => 'File attachments changed',
            'label callback' => false,
            'arguments' => 
            array (
              'node' => 
              array (
                'type' => 'node',
                'label' => 'Content containing changes',
              ),
              'node_unchanged' => 
              array (
                'type' => 'node',
                'label' => 'Content not containing changes',
              ),
            ),
            'module' => 'CCK',
          ),
          '#name' => 'content_rules_field_changed',
          '#settings' => 
          array (
            'field_name' => 'field_file',
            '#argument map' => 
            array (
              'node' => 'node',
              'node_unchanged' => 'node_unchanged',
            ),
          ),
          '#type' => 'condition',
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
            'label' => 'Log activity for the active group',
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
            'public_name' => 'Document revisions',
            'templates' => 
            array (
              'en' => 
              array (
                'template' => '<div class="activity-log-content">[user:user] edited the [node:type-name] [node:title-link]</div>
<div class="activity-log-teaser">[node:field_file-filefield-view]</div>
<div class="activity-log-time"><a href="[node:node-url]">[node:mod-since] ago</a></div>',
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
            'tid' => '18',
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
                  1 => 'user',
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
}
