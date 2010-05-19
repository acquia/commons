<?php
// $Id: panels_mini.inc,v 1.1.2.4 2009/07/13 19:51:23 merlinofchaos Exp $

/**
 * @file
 * Contains the content type plugin for a mini panel. While this does not
 * need to be broken out into a .inc file, it's convenient that we do so
 * that we don't load code unneccessarily. Plus it demonstrates plugins
 * in modules other than Panels itself.
 * 
 */

/**
 * Specially named hook. for .inc file. This looks a little silly due to the
 * redundancy, but that's really just because the content type shares a
 * name with the module.
 */
function panels_mini_panels_mini_ctools_content_types() {
  return array(
    'title' => t('Mini panels'),
  );
}

/**
 * Return each available mini panel available as a subtype.
 */
function panels_mini_panels_mini_content_type_content_types($plugin) {
  $types = array();
  foreach (panels_mini_load_all() as $mini) {
    if (!empty($mini->disabled)) {
      continue;
    }

    $types[$mini->name] = array(
      'title' => filter_xss_admin($mini->title),
      // For now mini panels will just use the contrib block icon.
      'icon' => 'icon_mini_panel.png',
      'description' => filter_xss_admin($mini->title),
      'category' => !empty($mini->category) ? filter_xss_admin($mini->category) : t('Mini panel'),
    );
    if (!empty($mini->requiredcontexts)) {
      $types[$mini->name]['required context'] = array();
      foreach ($mini->requiredcontexts as $context) {
        $info = ctools_get_context($context['name']);
        // TODO: allow an optional setting
        $types[$mini->name]['required context'][] = new ctools_context_required($context['identifier'], $info['context name']);
      }
    }
  }
  return $types;
}


/**
 * Render a mini panel called from a panels display.
 */
function panels_mini_panels_mini_content_type_render($subtype, $conf, $panel_args, &$contexts) {
  static $viewing = array();
  $mini = panels_mini_load($subtype);
  if (!$mini) {
    return FALSE;
  }
  if (!empty($viewing[$mini->name])) {
    return FALSE;
  }

  // Load up any contexts we might be using.
  $context = ctools_context_match_required_contexts($mini->requiredcontexts, $contexts);
  $mini->context = $mini->display->context = ctools_context_load_contexts($mini, FALSE, $context);

  if (empty($mini) || !empty($mini->disabled)) {
    return;
  }
  $viewing[$mini->name] = TRUE;

  $mini->display->args = $panel_args;
  $mini->display->css_id = panels_mini_get_id($subtype);
  $mini->display->owner = $mini;
  // unique ID of this mini.
  $mini->display->owner->id = $mini->name;

  $block = new stdClass();
  $block->module  = 'panels_mini';
  $block->delta   = $subtype;
  $block->title = filter_xss_admin($mini->title);
  $block->content = panels_render_display($mini->display);

  unset($viewing[$mini->name]);
  return $block;
}

/**
 * Edit form for the mini panel content type.
 */
function panels_mini_panels_mini_content_type_edit_form(&$form, &$form_state) {
  // Empty form to ensure we have the override title + context gadgets.
}

/**
 * Provide the administrative title of a mini panel.
 */
function panels_mini_panels_mini_content_type_admin_title($subtype, $conf) {
  $mini = panels_mini_load($subtype);
  if (!$mini) {
    return t('Deleted/missing mini panel @name', array('@name' => $subtype));
  }

  $title = filter_xss_admin($mini->title);
  if (empty($title)) {
    $title = t('Untitled mini panel');
  }
  return $title;
}

