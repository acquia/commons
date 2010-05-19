<?php
// $Id: display-render.inc,v 1.5.2.15 2009/10/28 16:55:34 merlinofchaos Exp $

/**
 * @file
 *
 * Contains Panels display rendering functions.
 */

/**
 * Render a display by loading the content into an appropriate
 * array and then passing through to panels_render_layout.
 *
 * if $incoming_content is NULL, default content will be applied. Use
 * an empty string to indicate no content.
 * @render
 * @ingroup hook_invocations
 */
function _panels_render_display(&$display) {
  $layout = panels_get_layout($display->layout);
  if (!$layout) {
    return NULL;
  }

  // TODO: This may not be necessary now. Check this.
  panels_sanitize_display($display);

  $output = '';

  // Let modules act just prior to render.
  foreach (module_implements('panels_pre_render') as $module) {
    $function = $module . '_panels_pre_render';
    $output .= $function($display);
  }

  $output .= panels_render_layout($layout, $display, $display->css_id, $display->layout_settings);

  // Let modules act just after render.
  foreach (module_implements('panels_post_render') as $module) {
    $function = $module . '_panels_post_render';
    $output .= $function($display);
  }
  return $output;
}

/**
 * For external use: Given a layout ID and a $content array, return the
 * panel display. The content array is filled in based upon the content
 * available in the layout. If it's a two column with a content
 * array defined like array('left' => t('Left side'), 'right' =>
 * t('Right side')), then the $content array should be array('left' =>
 * $output_left, 'right' => $output_right)
 * @render
 */
function _panels_print_layout($id, $content) {
  $layout = panels_get_layout($id);
  if (!$layout) {
    return;
  }

  return panels_render_layout($layout, $content);
}

/**
 * Given a full layout structure and a content array, render a panel display.
 * @render
 */
function panels_render_layout($layout, $content, $css_id = NULL, $settings = array(), $display = NULL) {
  if (!empty($layout['css'])) {
    if (file_exists(path_to_theme() . '/' . $layout['css'])) {
      drupal_add_css(path_to_theme() . '/' . $layout['css']);
    }
    else {
      drupal_add_css($layout['path'] . '/' . $layout['css']);
    }
  }
  // This now comes after the CSS is added, because panels-within-panels must
  // have their CSS added in the right order; inner content before outer content.

  // If $content is an object, it's a $display and we have to render its panes.
  if (is_object($content)) {
    $display = $content;
    if (empty($display->cache['method'])) {
      $content = panels_render_panes($display);
    }
    else {
      $cache = panels_get_cached_content($display, $display->args, $display->context);
      if ($cache === FALSE) {
        $cache = new panels_cache_object();
        $cache->set_content(panels_render_panes($display));
        panels_set_cached_content($cache, $display, $display->args, $display->context);
      }
      $content = $cache->content;
    }
  }

  $output = theme($layout['theme'], check_plain($css_id), $content, $settings, $display);

  return $output;
}

/**
 * Render the administrative layout of a display.
 *
 * This is used for the edit version, so that layouts can have different
 * modes, such as the flexible layout designer mode.
 */
function panels_render_layout_admin($layout, $content, $display) {
  // @todo This should be abstracted.
  if (!empty($layout['css'])) {
    if (file_exists(path_to_theme() . '/' . $layout['css'])) {
      drupal_add_css(path_to_theme() . '/' . $layout['css']);
    }
    else {
      drupal_add_css($layout['path'] . '/' . $layout['css']);
    }
  }

  if (isset($layout['admin css'])) {
    drupal_add_css($layout['path'] . '/' . $layout['admin css']);
  }

  $theme = isset($layout['admin theme']) ? $layout['admin theme'] : $layout['theme'];
  return theme($theme, isset($display->css_id) ? $display->css_id : '', $content, $display->layout_settings, $display);
}

/**
 * Render all the panes in a display into a $content array to be used by
 * the display theme function.
 */
function panels_render_panes(&$display) {
  ctools_include('content');

  $keywords = array();

  // First, render all the panes into little boxes. We do this here because
  // some panes request to be rendered after other panes (primarily so they
  // can do the leftovers of forms).
  $panes = array();
  $later = array();

  foreach ((array) $display->content as $pid => $pane) {
    $pane->shown = !empty($pane->shown); // guarantee this field exists.
    // If the user can't see this pane, do not render it.
    if (!$pane->shown || !panels_pane_access($pane, $display)) {
      continue;
    }

    // If this pane wants to render last, add it to the $later array.
    $content_type = ctools_get_content_type($pane->type);

    if (!empty($content_type['render last'])) {
      $later[$pid] = $pane;
      continue;
    }

    $panes[$pid] = panels_render_pane_content($display, $pane, $keywords);
  }

  foreach ($later as $pid => $pane) {
    $panes[$pid] = panels_render_pane_content($display, $pane, $keywords);
  }

  // Loop through all panels, put all panes that belong to the current panel
  // in an array, then render the panel. Primarily this ensures that the
  // panes are in the proper order.
  $content = array();
  foreach ($display->panels as $panel_name => $pids) {
    $panel = array();
    foreach ($pids as $pid) {
      if (!empty($panes[$pid])) {
        $panel[$pid] = $panes[$pid];
      }
    }
    $content[$panel_name] = panels_render_panel($display, $panel_name, $panel);
  }

  // Prevent notices by making sure that all panels at least have an entry:
  $layout = panels_get_layout($display->layout);
  $panels = panels_get_panels($layout, $display);
  foreach ($panels as $id => $panel) {
    if (!isset($content[$id])) {
      $content[$id] = NULL;
    }
  }

  return $content;
}

/**
 * Render a single pane, identifying its context, and put it into
 * the $panes array.
 */
function panels_render_pane_content(&$display, &$pane, $keywords) {
  $content = panels_get_pane_content($display, $pane, $keywords, $display->args, $display->context, $display->incoming_content);

  // Pass long the css_id that is usually available.
  if (!empty($pane->css['css_id'])) {
    $content->css_id = $pane->css['css_id'];
  }

  // Pass long the css_class that is usually available.
  if (!empty($pane->css['css_class'])) {
    $content->css_class = $pane->css['css_class'];
  }

  return $content;
}

/**
 * Render a pane using the appropriate style.
 *
 * $content
 *   The already rendered content via panels_render_pane_content()
 * $pane
 *   The $pane information from the display
 * $display
 *   The display.
 */
function panels_render_pane($content, $pane, &$display) {
  if ($display->hide_title == PANELS_TITLE_PANE && !empty($display->title_pane) && $display->title_pane == $pane->pid) {

    // If the user selected to override the title with nothing, and selected
    // this as the title pane, assume the user actually wanted the original
    // title to bubble up to the top but not actually be used on the pane.
    if (empty($content->title) && !empty($content->original_title)) {
      $display->stored_pane_title = $content->original_title;
    }
    else {
      $display->stored_pane_title = !empty($content->title) ? $content->title : '';
    }
  }

  if (!empty($pane->style['style'])) {
    $style = panels_get_style($pane->style['style']);

    if (isset($style) && isset($style['render pane'])) {
      $output = theme($style['render pane'], $content, $pane, $display);

      // This could be null if no theme function existed.
      if (isset($output)) {
        return $output;
      }
    }
  }

  if (!empty($content->content)) {
    // fallback
    return theme('panels_pane', $content, $pane, $display);
  }
}

/**
 * Given a display and the id of a panel, get the style in which to render
 * that panel.
 */
function panels_get_panel_style_and_settings($panel_settings, $panel) {
  if (empty($panel_settings)) {
    return array(panels_get_style('default'), array());
  }

  if (empty($panel_settings[$panel]['style']) || $panel_settings[$panel]['style'] == -1) {
    if (empty($panel_settings['style'])) {
      return array(panels_get_style('default'), array());
    }

    $style = panels_get_style($panel_settings['style']);
    $style_settings = isset($panel_settings['style_settings']['default']) ? $panel_settings['style_settings']['default'] : array();
  }
  else {
    $style = panels_get_style($panel_settings[$panel]['style']);
    $style_settings = isset($panel_settings['style_settings'][$panel]) ? $panel_settings['style_settings'][$panel] : array();
  }

  return array($style, $style_settings);
}

/**
 * Render a panel, by storing the content of each pane in an appropriate array
 * and then passing through to the theme function that will render the panel
 * in the configured panel style.
 *
 * @param $display
 *   A display object.
 * @param $panel
 *   The ID of the panel being rendered
 * @param $panes
 *   An array of panes that are assigned to the panel that's being rendered.
 *
 * @return
 *   The rendered HTML for a panel.
 * @render
 */
function panels_render_panel($display, $panel, $panes) {
  list($style, $style_settings) = panels_get_panel_style_and_settings($display->panel_settings, $panel);

  // Retrieve the pid (can be a panel page id, a mini panel id, etc.), this
  // might be used (or even necessary) for some panel display styles.
  // TODO: Got to fix this to use panel page name instead of pid, since pid is
  // no longer guaranteed. This needs an API to be able to set the final id.
  $owner_id = 0;
  if (isset($display->owner) && is_object($display->owner) && isset($display->owner->id)) {
    $owner_id = $display->owner->id;
  }

  return theme($style['render panel'], $display, $owner_id, $panes, $style_settings, $panel);
}

/**
 * Get the title from a display.
 *
 * The display must have already been rendered, or the setting to set the display's title
 * from a pane's title will not have worked.
 *
 * @param $display
 *   The display to get the title from.
 *
 * @return
 *   The title to use. If NULL, this means to let any default title that may be in use
 *   pass through. i.e, do not actually set the title.
 */
function panels_display_get_title($display) {
  switch ($display->hide_title) {
    case PANELS_TITLE_NONE:
      return '';

    case PANELS_TITLE_PANE:
      return isset($display->stored_pane_title) ? $display->stored_pane_title : '';

    case PANELS_TITLE_FIXED:
    case FALSE; // For old exported panels that are not in the database.
      if (!empty($display->title)) {
        return filter_xss_admin(ctools_context_keyword_substitute($display->title, array(), $display->context));
      }
      return NULL;
  }
}
