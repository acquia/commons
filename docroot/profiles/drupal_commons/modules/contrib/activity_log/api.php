<?php

/**
 * @file
 *   Hook documentation for the Activity Log module.
 */

/**
 * Implementation of hook_activity_log_collapse_methods().
 *
 * Specifies available options for combining an array of strings into a single
 * string. These options are exposed on the "Log activity" Rules action form
 * and are used to collapse an array of evaluated items into the [collection]
 * token in the group template.
 *
 * @return
 *   An associative array of options where the key is the name of the
 *   function for collapsing an array and the value is the human-friendly name
 *   of the option. The available functions should take a $collection array and
 *   an integral $count of the number of items in that collection as parameters
 *   and return a string summarizing the items in the $collection. The
 *   $collection will always have at least 2 items.
 */
function hook_activity_log_collapse_methods() {
  return array(
    'activity_log_collapse_inline' => t('Inline (A, B, and 3 others)'),
    'activity_log_collapse_list_horizontal' => t('Horizontal list (A B C D)'),
    'activity_log_collapse_list_vertical' => t('Vertical list (each item on its own line)'),
  );
}

/**
 * Implementation of hook_activity_log_event().
 *
 * Invoked when an activity is logged; allows taking action when this happens.
 *
 * @param $event
 *   The activity event object (properties correspond with the columns in the
 *   {activity_log_events} table).
 * @param $group
 *   The activity message object (properties correspond with the columns in the
 *   {activity_log_messages} table).
 * @param $settings
 *   An array containing the evaluated settings for the executed Activity Log
 *   Rules action.
 */
function hook_activity_log_event($event, $group, $settings) {
  if (module_exists('radioactivity')) {
    module_load_include('inc', 'radioactivity');
    $aids = explode(',', $group->aids);
    if (count($aids) > 1) {
      radioactivity_add_energy($group->mid, 'act_log', 'group:'. $record->tid);
    }
    else {
      radioactivity_add_energy($group->mid, 'act_log', 'event:'. $record->tid);
    }
  }
}

/**
 * Implementation of hook_activity_log_entity_groups().
 *
 * Defines groups of potential stream owners and message viewers for an action.
 *
 * @param $stream_owner
 *   If TRUE, the groups returned are valid for stream owners -- that is, all
 *   entity types, but "everyone" is not valid. If FALSE, the groups returned
 *   are only for users, and so are valid for message viewers.
 * @return
 *   An associative array of group definitions keyed by the machine name.
 *   Values are also associative arrays that can have the following elements:
 *   - items callback: A function that returns an associative array where the
 *     keys are valid stream owner types (node, user, taxonomy_term) and the
 *     values are arrays of stream owner IDs of that type.
 *   - title: A translated, human-friendly name of the group.
 *   - weight: (Optional) The group's weight in an ordering of all groups.
 *     Lighter weights float to the top. Defaults to 0.
 *   - expose fields: (Optional) An array of which additional fields should be
 *     exposed if this group is selected. Valid values for this array are "id,"
 *     "type," and (if you know what you're doing) "acting_uid." Defaults to
 *     array().
 *   - additional arguments: (Optional) Extra arguments to pass to the items
 *     callback.
 *   - file: (Optional) The file where the items callback exists.
 */
function hook_activity_log_entity_groups($stream_owner = TRUE) {
  module_load_include('inc', 'activity_log', 'activity_log.entity_groups');
  return activity_log_entity_groups($stream_owner);
}

/**
 * Implementation of hook_activity_log_token_resources().
 *
 * Maps tokens to CSS and JS resources they require. The specified resources
 * will be loaded for cached messages that use the relevant tokens.
 */
function hook_activity_log_token_resources() {
  return array(
    '[:global:token]' => array(
      'css' => array(
        drupal_get_path('module', 'hook') .'/hook.css';
      ),
      'js' => array(
        drupal_get_path('module', 'hook') .'/hook.js';
      ),
    ),
  );
}

/**
 * Implementation of hook_activity_log_uncacheable_tokens().
 *
 * Returns an array of tokens that cannot be cached. Messages generated from
 * templates that use these tokens will never be cached.
 */
function hook_activity_log_uncacheable_tokens() {
  return array(
    '[:global:user-id]',
    '[:global:user-mail]',
    '[:global:user-name]',
    ':userpoints]',
  );
}
