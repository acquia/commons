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
      radioactivity_add_energy($group->mid, 'act_log', 'group:'. $event->tid);
    }
    else {
      radioactivity_add_energy($group->mid, 'act_log', 'event:'. $event->tid);
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
 *   - data types: (Optional) An array containing names of Rules data types for
 *     which this group is valid. If not specified, this group is assumed to be
 *     valid for all Rules data types. Valid data types that can be specified
 *     here include anything returned by
 *     activity_log_get_rules_data_types(array('stream owner types' => 'all)).
 *   - file: (Optional) The file where the items callback exists.
 */
function hook_activity_log_entity_groups($stream_owner = TRUE) {
  module_load_include('inc', 'activity_log', 'activity_log.entity_groups');
  return activity_log_entity_groups($stream_owner);
}

/**
 * Implementation of hook_activity_log_regenerate_info().
 *
 * Returns an associative array describing Rules events for which we support
 * regenerating activity messages. The keys are the Rules event machine name
 * (valid values can be found using array_keys(rules_get_events())) and the
 * values are associative arrays with the following elements:
 *
 * - callback: A function that triggers the relevant event once for each
 *   relevant entity.
 * - arguments: An array of additional arguments to pass to the count and
 *   generate callbacks. Useful for events with conditional names.
 * - file: (Optional) A file to include before the callbacks are executed.
 * - target_type: (Optional) The Rules data type of the entity for which your
 *   event regenerates activity messages. Existing activity messages that use
 *   this data type will be deleted before activity is regenerated to avoid
 *   duplicates.
 *
 * The callback's parameters include:
 *
 * - $age: Content created after this timestamp should have activity messages
 *   generated.
 * - $context: The return value of the previous time that callback was invoked.
 *   The first time the callback is invoked, the value of this argument is
 *   FALSE. You can use the last return value to keep track of an "offset,"
 *   e.g. so you can only process a limited number of entities in one batch
 *   request and you know where to pick up on the next request.
 * - Any arguments passed via the "arguments" key.
 *
 * The callback will be invoked repeatedly until it returns something that
 * evaluates to FALSE.
 */
function hook_activity_log_regenerate_info() {
  $path = drupal_get_path('module', 'activity_log') .'/activity_log.generate.inc';
  $items = array(
    'comment_insert' => array(
      'callback' => 'activity_log_regenerate_comments',
      'file' => $path,
      'target_type' => 'comment',
    ),
    'node_insert' => array(
      'callback' => 'activity_log_regenerate_nodes',
      'file' => $path,
      'target_type' => 'node',
    ),
    'taxonomy_term_insert' => array(
      'callback' => 'activity_log_regenerate_taxonomy_terms',
      'file' => $path,
      'target_type' => 'taxonomy_term',
    ),
    'user_insert' => array(
      'callback' => 'activity_log_regenerate_users',
      'file' => $path,
      'target_type' => 'user',
    ),
  );
  return $items;
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
        drupal_get_path('module', 'hook') .'/hook.css',
      ),
      'js' => array(
        drupal_get_path('module', 'hook') .'/hook.js',
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

/**
 * Implementation of hook_activity_log_display_types().
 *
 * Returns an associative array of locations where activity messages can be
 * displayed. The keys are the machine names and the values are the translated
 * human-friendly names of the destinations.
 */
function hook_activity_log_display_types() {
  return array(
    'web' => t('Web stream'),
  );
}
