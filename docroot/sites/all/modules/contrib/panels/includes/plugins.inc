<?php
// $Id: plugins.inc,v 1.13.2.15 2010/01/12 23:18:44 merlinofchaos Exp $

/**
 * @file
 *
 * Contains helper code for plugins and contexts.
 */

/**
 * Determine if a pane is visible.
 *
 * @param $pane
 *   The pane object to test for access.
 * @param $display
 *   The display object containing the pane object to be tested.
 */
function panels_pane_access($pane, $display) {
  ctools_include('context');
  return ctools_access($pane->access, $display->context);
}

/**
 * Get a list of panels available in the layout.
 */
function panels_get_panels($layout, $display) {
  if (!empty($layout['panels function']) && function_exists($layout['panels function'])) {
    return $layout['panels function']($display, $display->layout_settings);
  }
  if (!empty($layout['panels'])) {
    return $layout['panels'];
  }
  return array();
}

/**
 * Get the content from a given pane.
 *
 * @param $pane
 *   The pane to retrieve content from.
 * @param $args
 *   The arguments sent to the display.
 * @param $context
 *   The panels context.
 * @param $incoming_content
 *   Any incoming content if this display is a wrapper.
 */
function panels_get_pane_content($display, $pane, $keywords, $args = array(), $context = array(), $incoming_content = '') {
  ctools_include('context');
  if (!is_array($context)) {
    $context = array();
  }

  if (!$incoming_content === '') {
    $incoming_content = t('Incoming content will be displayed here.');
  }

  $content = FALSE;
  $caching = !empty($pane->cache['method']) ? TRUE : FALSE;
  if ($caching && ($cache = panels_get_cached_content($display, $args, $context, $pane))) {
    $content = $cache->content;
  }
  else {
    $content = ctools_content_render($pane->type, $pane->subtype, $pane->configuration, $keywords, $args, $context, $incoming_content);
    foreach (module_implements('panels_pane_content_alter') as $module) {
      $function = $module . '_panels_pane_content_alter';
      $function($content, $pane, $args, $context);
    }
    if ($caching) {
      $cache = new panels_cache_object();
      $cache->set_content($content);
      panels_set_cached_content($cache, $display, $args, $context, $pane);
      $content->content = $cache->content;
    }
  }

  return $content;
}

/**
 * Get cached content for a given display and possibly pane.
 *
 * @return
 *   The cached content, or FALSE to indicate no cached content exists.
 */
function panels_get_cached_content($display, $args, $context, $pane = NULL) {
  // Never use cache on a POST
  if (!empty($_POST)) {
    return FALSE;
  }

  $method = $pane ? $pane->cache['method'] : $display->cache['method'];
  $function = panels_plugin_get_function('cache', $method, 'cache get');

  if (!$function) {
    return FALSE;
  }

  $conf = $pane ? $pane->cache['settings'] : $display->cache['settings'];
  $cache = $function($conf, $display, $args, $context, $pane);
  if (empty($cache)) {
    return FALSE;
  }

  // restore it.
  $cache->restore();
  return $cache;
}

/**
 * Store cached content for a given display and possibly pane.
 */
function panels_set_cached_content($cache, $display, $args, $context, $pane = NULL) {
  // Never use cache on a POST
  if (!empty($_POST)) {
    return FALSE;
  }

  $method = $pane ? $pane->cache['method'] : $display->cache['method'];
  $function = panels_plugin_get_function('cache', $method, 'cache set');

  if (!$function) {
    return FALSE;
  }

  $conf = $pane ? $pane->cache['settings'] : $display->cache['settings'];

  // snapshot it.
  $cache->cache();
  return $function($conf, $cache, $display, $args, $context, $pane);
}

/**
 * Clear all cached content for a display.
 */
function panels_clear_cached_content($display) {
  // Figure out every method we might be using to cache content in this display:
  $methods = array();
  if (!empty($display->cache['method'])) {
    $methods[$display->cache['method']] = TRUE;
  }

  foreach ($display->content as $pane) {
    if (!empty($pane->cache['method'])) {
      $methods[$pane->cache['method']] = TRUE;
    }
  }

  foreach (array_keys($methods) as $method) {
    $function = panels_plugin_get_function('cache', $method, 'cache clear');
    if ($function) {
      $function($display);
    }
  }
}

/**
 * An object to hold caching information while it is happening.
 */
class panels_cache_object {
  var $content = '';
  var $head = NULL;
  var $css = NULL;
  var $js = NULL;
  var $tokens = NULL;
  var $ready = FALSE;

  /**
   * When constructed, take a snapshot of our existing out of band data.
   */
  function panels_cache_object() {
    $this->head = drupal_set_html_head();
    $this->css = drupal_add_css();
    $this->tokens = ctools_set_page_token();

    foreach (array('header', 'footer') as $scope) {
      $this->js[$scope] = drupal_add_js(NULL, NULL, $scope);
    }
  }

  /**
   * Add content to the cache. This assumes a pure stream;
   * use set_content() if it's something else.
   */
  function add_content($content) {
    $this->content .= $content;
  }

  function set_content($content) {
    $this->content = $content;
  }

  /**
   * Set the object for storing. This overwrites.
   */
  function cache() {
    if ($this->ready) {
      return;
    }

    $this->ready = TRUE;

    // Simple replacement for head
    $this->head = str_replace($this->head, '', drupal_set_html_head());

    // Slightly less simple for CSS:
    $css = drupal_add_css();
    $start = $this->css;
    $this->css = array();

    foreach ($css as $media => $medias) {
      foreach ($medias as $type => $types) {
        foreach ($types as $path => $preprocess) {
          if (!isset($start[$media][$type][$path])) {
            $this->css[] = array($path, $type, $media, $preprocess);
          }
        }
      }
    }

    $js = array();
    // A little less simple for js
    foreach (array('header', 'footer') as $scope) {
      $js[$scope] = drupal_add_js(NULL, NULL, $scope);
    }

    $start = $this->js;
    $this->js = array();

    foreach ($js as $scope => $scopes) {
      foreach ($scopes as $type => $types) {
        foreach ($types as $id => $info) {
          if (!isset($start[$scope][$type][$id])) {
            switch ($type) {
              case 'setting':
                $this->js[] = array($info, $type, $scope);
                break;

              case 'inline':
                $this->js[] = array($info['code'], $type, $scope, $info['defer']);
                break;

              default:
                $this->js[] = array($id, $type, $scope, $info['defer'], $info['cache']);
            }
          }
        }
      }
    }

    // And for tokens:
    $tokens = ctools_set_page_token();
    foreach ($this->tokens as $token => $argument) {
      if (isset($tokens[$token])) {
        unset($tokens);
      }
    }

    $this->tokens = $tokens;
  }

  /**
   * Restore out of band data saved to cache.
   */
  function restore() {
    if (!empty($this->head)) {
      drupal_set_html_head($this->head);
    }
    if (!empty($this->css)) {
      foreach ($this->css as $args) {
        call_user_func_array('drupal_add_css', $args);
      }
    }
    if (!empty($this->js)) {
      foreach ($this->js as $args) {
        call_user_func_array('drupal_add_js', $args);
      }
    }

    if (!empty($this->tokens)) {
      foreach ($this->tokens as $token => $key) {
        list($type, $argument) = $key;
        ctools_set_page_token($token, $type, $argument);
      }
    }
  }
}

/**
 * Get the title of a pane.
 *
 * @param $pane
 *   The $pane object.
 */
function panels_get_pane_title(&$pane, $context = array(), $incoming_content = NULL) {
  ctools_include('content');
  return ctools_content_admin_title($pane->type, $pane->subtype, $pane->configuration, $context);
}

/**
 * Select a context for a pane.
 *
 * @param $pane
 *   A fully populated pane.
 * @param $contexts
 *   A keyed array of available contexts.
 *
 * @return
 *   The matching contexts or NULL if none or necessary, or FALSE if
 *   requirements can't be met.
 */
function panels_pane_select_context($pane, $contexts) {
  return ctools_content_select_context($pane->type, $pane->subtype, $pane->configuration, $contexts);
}

/**
 * Fetch metadata on a specific layout plugin.
 *
 * @param $layout
 *   Name of a panel layout.
 *
 * @return
 *   An array with information about the requested panel layout.
 */
function panels_get_layout($layout) {
  ctools_include('plugins');
  return ctools_get_plugins('panels', 'layouts', $layout);
}

/**
 * Fetch metadata for all layout plugins.
 *
 * @return
 *   An array of arrays with information about all available panel layouts.
 */
function panels_get_layouts() {
  ctools_include('plugins');
  return ctools_get_plugins('panels', 'layouts');
}

/**
 * Fetch metadata on a specific style plugin.
 *
 * @param $style
 *   Name of a panel style.
 *
 * @return
 *   An array with information about the requested panel style.
 */
function panels_get_style($style) {
  ctools_include('plugins');
  return ctools_get_plugins('panels', 'styles', $style);
}

/**
 * Fetch metadata for all style plugins.
 *
 * @return
 *   An array of arrays with information about all available panel styles.
 */
function panels_get_styles() {
  ctools_include('plugins');
  return ctools_get_plugins('panels', 'styles');
}

/**
 * Fetch metadata on a specific caching plugin.
 *
 * @param $cache
 *   Name of a panel cache.
 *
 * @return
 *   An array with information about the requested panel cache.
 */
function panels_get_cache($cache) {
  ctools_include('plugins');
  return ctools_get_plugins('panels', 'cache', $cache);
}

/**
 * Fetch metadata for all context plugins.
 *
 * @return
 *   An array of arrays with information about all available panel caches.
 */
function panels_get_caches() {
  ctools_include('plugins');
  return ctools_get_plugins('panels', 'cache');
}

/**
 * Get a function from a plugin, if it exists.
 *
 * @param $plugin
 *   The type of plugin
 * @param $which
 *   Either the loaded plugin object (or the same data in array form)
 *   or a string with the name of the desired the specific plugin.
 * @param $function_name
 *   The identifier of the function. For example, 'settings form'.
 *
 * @return
 *   The actual name of the function to call, or NULL if the function
 *   does not exist.
 */
function panels_plugin_get_function($plugin, $which, $function_name) {
  ctools_include('plugins');
  if (is_object($which) || is_array($which)) {
    return ctools_plugin_get_function($which, $function_name);
  }
  else {
    return ctools_plugin_load_function('panels', $plugin, $which, $function_name);
  }

}

// These are placeholders to prevent crashes from the former plugins
class panels_required_context { function filter() { } };
class panels_optional_context extends panels_required_context {};
