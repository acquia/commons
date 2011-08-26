<?php

/**
 * @file
 *   Defines API hooks for the Facebook-style Statuses module.
 */

/**
 * React to a status being saved.
 *
 * @param $status
 *   The status object that was just saved.
 * @param $context
 *   The stream context array.
 * @param $edit
 *   TRUE if the incoming status was just edited; FALSE if the status is
 *   entirely new. Note that editing can mean either saving the edit form or
 *   overwriting a previous status by timed override.
 * @param $options
 *   An associative array containing:
 *   - discard duplicates: Whether a new status containing exactly the same
 *     message as the previous status will be saved or discarded.
 *   - timed override: Whether a status update will be overwritten if a new one
 *     is submitted within FACEBOOK_STATUS_OVERRIDE_TIMER seconds.
 *   - discard blank statuses: Whether blank status messages will be discarded.
 * @see facebook_status_save_status()
 * @see facebook_status_edit_submit()
 */
function hook_facebook_status_save($status, $context, $edit, $options) {
  if ($edit) {
    drupal_set_message(t('The status message has been saved.'));
  }
  else {
    drupal_set_message(t('The status message has been updated.'));
  }
}

/**
 * React to a status being deleted.
 *
 * @param $status
 *   The status object to delete.
 * @param $meta
 *   An array of metadata that affects what behaviors are triggered from this
 *   function. There are no default options, but other modules may use them.
 *   For example, the Facebook-style Micropublisher module makes use of a
 *   "has attachment" option, which denotes whether the status that is being
 *   deleted has attached media.
 * @see facebook_status_delete_status()
 */
function hook_facebook_status_delete($status, $meta = array()) {
  if (module_exists('facebook_status_tags')) {
    db_query("DELETE FROM {facebook_status_tags} WHERE sid = %d", $status->sid);
  }
}

/**
 * Describe default values for stream context types.
 *
 * @return
 *   An associative array of associative arrays. The outer array keys indicate
 *   the context type (machine name). Inner arrays have these elements:
 *   - title: The "friendly" name of the context type.
 *   - description (optional): An explanation of who owns the recipient stream
 *     if this context is used. This will be displayed in a "title" attribute,
 *     so do not use double quotes.
 *   - handler: The name of a class that extends facebook_status_context (and
 *     thus defines useful methods to describe the context).
 *   - parent (optional): The name of the parent context type (not the
 *     parent handler).
 *   - dependencies (optional): An array containing the names of modules that
 *     must be enabled for that context type to be used.
 *   - selectors (optional): A string containing CSS selectors separated by
 *     newlines. Each selector will be automatically updated via AJAX when a
 *     new status of the relevant type is saved. Do not include selectors that
 *     include the status update form.
 *   - view (optional): The default view to use as the context stream.
 *   - visibility (optional): Flag to indicate how to apply contexts on pages.
 *     - -1: Use module default settings
 *     - 0: Show on all pages except listed pages
 *     - 1: Show only on listed pages
 *     - 2: Use custom PHP code to determine visibility
 *     - 3: Use the conditions from a Context from the Context module
 *   - pages (optional): Either a list of paths on which to include/exclude the
 *     context or PHP code, depending on "visibility" setting. Visibility and
 *     pages provide a user-facing way of overriding the is_applicable()
 *     function of the context handler.
 *   - context (optional): A Context defined by the Context module whose
 *     conditions should be used to determine whether the stream context
 *     applies on this page if the "visibility" flag is set appropriately.
 *     Overrides the is_applicable() function of the context handler.
 *   - weight (optional): The default precedence of the context type.
 *   - file (optional): A file to load before loading the context handler.
 * @see facebook_status_all_contexts()
 */
function hook_facebook_status_context_info() {
  $path = drupal_get_path('module', 'facebook_status');
  return array(
    'user' => array(
      'title' => t('User profiles'),
      'description' => t('If a profile is currently being viewed, then the stream belongs to the owner of that profile.') .' '.
        t('Otherwise, the stream belongs to the current user.'),
      'handler' => 'facebook_status_user_context',
      'view' => 'facebook_status_user_stream',
      'weight' => 9999,
      'file' => $path .'/includes/utility/facebook_status.contexts.inc',
    ),
    'node' => array(
      'title' => t('Nodes'),
      'description' => t('The stream belongs to the currently viewed node, if applicable.'),
      'handler' => 'facebook_status_node_context',
      'view' => 'facebook_status_node_stream',
      'weight' => 0,
      'file' => $path .'/includes/utility/facebook_status.contexts.inc',
    ),
  );
}

/**
 * Return a list of DOM selectors whose contents FBSS should automatically
 * update via AJAX when a new status is submitted from a status update form on
 * the same page. Do not select a region which includes the status update form.
 *
 * @param $recipient
 *   An object representing the recipient of the status message.
 * @param $type
 *   The context stream type.
 * @return
 *   An array of DOM selector expressions.
 * @see theme_facebook_status_form_display()
 * @see hook_facebook_status_refresh_selectors_alter()
 */
function hook_facebook_status_refresh_selectors($recipient, $type) {
  //Automatically update all instances of the view that is displayed for this context.
  $context = facebook_status_determine_context($type);
  return array('.view-id-'. $context['view']);
}

/**
 * hook_link() is invoked with parameters 'facebook_status' and $status.
 * Implement it just like you would implement hook_link() with nodes.
 *
 * @param $type
 *   The type of link being processed.
 * @param $status
 *   The status object.
 * @return
 *   A structured array which will be run through drupal_render() to produce
 *   links that will be displayed with themed statuses.
 * @see facebook_status_link()
 * @see _facebook_status_show()
 */
if (!function_exists('hook_link')) {
  function hook_link($type, $object, $teaser = FALSE) {
    $links = array();
    if ($type == 'facebook_status') {
      $status = $object;
      $links['permalink'] = array(
        'href' => 'statuses/'. $status->sid,
        'title' => t('Permalink'),
      );
    }
    return $links;
  }
}

/**
 * Alter status links.
 *
 * @param $links
 *   A structured array as returned by implementations of hook_link().
 * @param $status
 *   A status object.
 * @see _facebook_status_show()
 */
function hook_facebook_status_link_alter(&$links, $status) {
  //Capitalize the first letter of every link.
  foreach ($links as $type => $data) {
    $links[$type]['title'] = drupal_ucfirst($links[$type]['title']);
  }
}

/**
 * Alter status save options.
 *
 * @param $options
 *   An associative array containing:
 *   - discard duplicates: Whether a new status containing exactly the same
 *     message as the previous status will be saved or discarded.
 *   - timed override: Whether a status update will be overwritten if a new one
 *     is submitted within FACEBOOK_STATUS_OVERRIDE_TIMER seconds.
 *   - discard blank statuses: Whether blank status messages will be discarded.
 * @param $edit
 *   TRUE if the status is being edited; FALSE if it is being created.
 * @see facebook_status_save_status()
 */
function hook_facebook_status_save_options_alter(&$options, $edit) {
  //If we allow saving attachments with statuses, then we could have different
  //attachments with the same message, so we need to allow saving statuses with
  //duplicate messages.
  if (module_exists('fbsmp')) {
    $options['discard duplicates'] = FALSE;
  }
}

/**
 * Alter user access.
 *
 * @param $allow
 *   Whether the action is permitted to be taken. Change this only if you can
 *   decide conclusively that the action is definitely (not) permitted.
 * @param $op
 *   The action being taken. One of add, converse, delete, edit, view,
 *   view_stream, generate.
 * @param $args
 *   An array of additional arguments. Varies depending on $op.
 * @see facebook_status_user_access()
 */
function hook_facebook_status_user_access_alter(&$allow, $op, $args) {
  global $user;
  switch ($op) {
    case 'add':
      $recipient = isset($args[0]) ? $args[0] : $user;
      $type = isset($args[1]) ? $args[1] : 'user';
      $sender = isset($args[2]) ? $args[2] : $user;
      $context = facebook_status_determine_context($type);
      //Updating one's own status should ALWAYS be allowed.
      if ($type == 'user' && $context['handler']->recipient_id($recipient) == $sender->uid) {
        $allow = TRUE;
      }
      break;
  }
}

/**
 * Add items to the AHAH-refreshed form.
 *
 * Anything on the old form that needs to remain on the new form needs to be
 * moved.
 *
 * @param $new_form
 *   The FAPI array representing the form that will replace the existing one
 *   via AHAH.
 * @param $old_form
 *   The FAPI array representing the form that will be replaced via AHAH.
 * @see facebook_status_save_js()
 */
function hook_facebook_status_form_ahah_alter(&$new_form, $old_form) {
  $new_form['slider']      = $form['slider'];
  $new_form['fbss-status'] = $form['fbss-status'];
  $new_form['chars']       = $form['chars'];
  $new_form['fbss-submit'] = $form['fbss-submit'];
  $new_form['sdefault']    = $form['sdefault'];
}

/**
 * Alter the refresh selectors.
 *
 * Refresh selectors are DOM paths that specify regions of the page that should
 * be automatically refreshed via AHAH when a status is submitted.
 *
 * @param $selectors
 *   An array of DOM paths.
 * @param $recipient
 *   The entity which would receive a status message if one were posted on the
 *   current page.
 * @param
 *   The type of recipient.
 * @see theme_facebook_status_form_display()
 * @see hook_facebook_status_refresh_selectors()
 */
function hook_facebook_status_refresh_selectors_alter(&$selectors, $recipient, $type) {
  $selectors[] = '.view-facebook_status-all';
}
