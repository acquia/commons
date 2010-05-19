<?php
// $Id: flexible.inc,v 1.1.2.18 2010/01/13 06:25:15 merlinofchaos Exp $

/**
 * Implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Flexible'),
  'icon' => 'flexible.png',
  'theme' => 'panels_flexible',
  'admin theme' => 'panels_flexible_admin',
  'css' => 'flexible.css',
  'admin css' => 'flexible-admin.css',
  'settings form' => 'panels_flexible_settings_form',
  'settings submit' => 'panels_flexible_settings_submit',
  'settings validate' => 'panels_flexible_settings_validate',
  'panels function' => 'panels_flexible_panels',
  'hook menu' => 'panels_flexible_menu',
);

/**
 * Delegated implementation of hook_menu().
 */
function panels_flexible_menu(&$items, &$info) {
  $base = array(
    'access arguments' => array('access content'),
    'page arguments' => array(4),
    'type' => MENU_CALLBACK,
    'file' => $info['file'],
    'file path' => $info['path'],
  );

  $items['panels/ajax/flexible/settings/%panels_edit_cache'] = array(
    'page callback' => 'panels_ajax_flexible_edit_settings',
  ) + $base;
  $items['panels/ajax/flexible/add/%panels_edit_cache'] = array(
    'page callback' => 'panels_ajax_flexible_edit_add',
  ) + $base;
  $items['panels/ajax/flexible/remove/%panels_edit_cache'] = array(
    'page callback' => 'panels_ajax_flexible_edit_remove',
  ) + $base;
  $items['panels/ajax/flexible/resize/%panels_edit_cache'] = array(
    'page callback' => 'panels_ajax_flexible_edit_resize',
  ) + $base;
}

/**
 * Convert settings from old style to new, or provide defaults for
 * empty settings.
 * @param <type> $settings
 */
function panels_flexible_convert_settings(&$settings) {
  if (empty($settings)) {
    // set up a default
    $settings = array(
      'items' => array(
        // The 'canvas' is a special row that does not get rendered
        // normally, but is used to contain the columns.
        'canvas' => array(
          'type' => 'row',
          'contains' => 'column',
          'children' => array('main'),
          'parent' => NULL,
        ),
        'main' => array(
          'type' => 'column',
          'width' => 100,
          'width_type' => '%',
          'children' => array('main-row'),
          'parent' => 'canvas',
        ),
        'main-row' => array(
          'type' => 'row',
          'contains' => 'region',
          'children' => array('center'),
          'parent' => 'main',
        ),
        'center' => array(
          'type' => 'region',
          'title' => t('Center'),
          'width' => 100,
          'width_type' => '%',
          'parent' => 'main-row',
        ),
      ),
    );
  }
  else if (!isset($settings['items'])) {
    // Convert an old style flexible to a new style flexible.
    $old = $settings;
    $settings = array();
    $settings['items']['canvas'] = array(
      'type' => 'row',
      'contains' => 'column',
      'children' => array(),
      'parent' => NULL,
    );
    // add the left sidebar column, row and region if it exists.
    if (!empty($old['sidebars']['left'])) {
      $settings['items']['canvas']['children'][] = 'sidebar-left';
      $settings['items']['sidebar-left'] = array(
        'type' => 'column',
        'width' => $old['sidebars']['left_width'],
        'width_type' => $old['sidebars']['width_type'],
        'children' => array('sidebar-left-row'),
        'parent' => 'canvas',
      );
      $settings['items']['sidebar-left-row'] = array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array('sidebar_left'),
        'parent' => 'sidebar-left',
      );
      $settings['items']['sidebar_left'] = array(
        'type' => 'region',
        'title' => t('Left sidebar'),
        'width' => 100,
        'width_type' => '%',
        'parent' => 'sidebar-left-row',
      );
    }

    $settings['items']['canvas']['children'][] = 'main';

    if (!empty($old['sidebars']['right'])) {
      $settings['items']['canvas']['children'][] = 'sidebar-right';
      $settings['items']['sidebar-right'] = array(
        'type' => 'column',
        'width' => $old['sidebars']['right_width'],
        'width_type' => $old['sidebars']['width_type'],
        'children' => array('sidebar-right-row'),
        'parent' => 'canvas',
      );
      $settings['items']['sidebar-right-row'] = array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array('sidebar_right'),
        'parent' => 'sidebar-right',
      );
      $settings['items']['sidebar_right'] = array(
        'type' => 'region',
        'title' => t('Right sidebar'),
        'width' => 100,
        'width_type' => '%',
        'parent' => 'sidebar-right-row',
      );
    }

    // Add the main column.
    $settings['items']['main'] = array(
      'type' => 'column',
      'width' => 100,
      'width_type' => '%',
      'children' => array(),
      'parent' => 'canvas',
    );

    // Add rows and regions.
    for ($row = 1; $row <= intval($old['rows']); $row++) {
      // Create entry for the row
      $settings['items']["row_$row"] = array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(),
        'parent' => 'main',
      );
      // Add the row to the parent's children
      $settings['items']['main']['children'][] = "row_$row";

      for ($col = 1; $col <= intval($old["row_$row"]['columns']); $col++) {
        // Create entry for the region
        $settings['items']["row_${row}_$col"] = array(
          'type' => 'region',
          'width' => $old["row_$row"]["width_$col"],
          'width_type' => '%',
          'parent' => "row_$row",
        );
        // Add entry for the region to the row's children
        $settings['items']["row_$row"]['children'][] = "row_${row}_$col";

        // Apply the proper title to the region
        if (!empty($old["row_$row"]['names'][$col - 1])) {
          $settings['items']["row_${row}_$col"]['title'] = $old["row_$row"]['names'][$col - 1];
        }
        else {
          $settings['items']["row_${row}_$col"]['title'] = t("Row @row, Column @col", array('@row' => $row, '@col' => $col));
        }
      }
    }
  }
  else if (isset($settings['canvas'])) {
    // Convert the old 'canvas' to the new canvas row.
    $settings['items']['canvas'] = array(
      'type' => 'row',
      'contains' => 'column',
      'children' => $settings['canvas'],
      'parent' => NULL,
    );
    unset($settings['canvas']);
  }
}

/**
 * Define the actual list of columns and rows for this flexible panel.
 */
function panels_flexible_panels($display, $settings) {
  $items = array();
  panels_flexible_convert_settings($settings);
  foreach ($settings['items'] as $id => $item) {
    if ($item['type'] == 'region') {
      $items[$id] = $item['title'];
    }
  }

  return $items;
}

/**
 * Draw the flexible layout.
 */
function theme_panels_flexible($id, $content, $settings, $display) {
  panels_flexible_convert_settings($settings);

  $renderer = new stdClass;
  $renderer->settings = $settings;
  $renderer->content = $content;
  $renderer->css_id = $id;
  $renderer->did = $display->did;
  $renderer->id_str = $id ? 'id="' . $id . '"' : '';
  $renderer->admin = FALSE;

  // CSS must be generated because it reports back left/middle/right
  // positions.
  $css = panels_flexible_render_css($renderer);

  if ($display->did && $display->did != 'new') {
    ctools_include('css');
    // Generate an id based upon rows + columns:
    $css_id = 'flexible:' . $display->did;
    $filename = ctools_css_retrieve($css_id);
    if (!$filename) {
      $filename = ctools_css_store($css_id, $css, FALSE);
    }
    drupal_add_css($filename, 'module', 'all', FALSE);
  }
  else {
    // If the id is 'new' we can't reliably cache the CSS in the filesystem
    // because the display does not truly exist, so we'll stick it in the
    // head tag.
    drupal_set_html_head("<style type=\"text/css\">\n$css</style>\n");
  }

  $output = "<div class=\"panel-flexible panel-flexible-$renderer->did clear-block\" $renderer->id_str>\n";
  $output .= "<div class=\"panel-flexible-inside panel-flexible-$renderer->did-inside\">\n";

  $output .= panels_flexible_render_items($renderer, $settings['items']['canvas']['children'], 'panel-flexible-' . $renderer->did);

  // Wrap the whole thing up nice and snug
  $output .= "</div>\n</div>\n";

  return $output;
}

/**
 * Draw the flexible layout.
 */
function theme_panels_flexible_admin($id, $content, $settings, $display) {
  panels_flexible_convert_settings($settings);

  $renderer = new stdClass;
  $renderer->settings = $settings;
  $renderer->content = $content;
  $renderer->css_id = $id;
  $renderer->did = $display->did;
  $renderer->cache_key = $display->cache_key;
  $renderer->id_str = $id ? 'id="' . $id . '"' : '';
  $renderer->admin = TRUE;

  if ($display->did && $display->did != 'new') {
    // Automatically remove any cached CSS for this display since it's
    // being edited. The next time it's viewed CSS will be auto generated
    // if necessary.
    $css_id = 'flexible:' . $display->did;
    ctools_include('css');
    ctools_css_clear($css_id);
  }
  $css = panels_flexible_render_css($renderer);

  // For the administrative view, add CSS directly to head.
  drupal_set_html_head("<style type=\"text/css\">\n$css</style>\n");

  $output = '<input type="submit" id="panels-flexible-toggle-layout" value ="' .
    t('Show layout designer') . '">';
  $output .= "<div class=\"panel-flexible panel-flexible-$renderer->did clear-block panel-flexible-admin panel-flexible-no-edit-layout\" $renderer->id_str>\n";
  $output .= "<div class=\"panel-flexible-inside panel-flexible-$renderer->did-inside \">\n";

  $content = panels_flexible_render_items($renderer, $settings['items']['canvas']['children'], 'panels-flexible-row-' . $renderer->did . '-canvas');
  $output .= panels_flexible_render_item($renderer, $settings['items']['canvas'], 'panels-flexible-row', $content, 'canvas', 0, 0, TRUE);

  // Wrap the whole thing up nice and snug
  $output .= "</div>\n</div>\n";

  drupal_add_js(panels_get_path('plugins/layouts/flexible/flexible-admin.js'));
  drupal_add_js(array('flexible' => array('resize' => url('panels/ajax/flexible/resize/' . $display->cache_key, array('absolute' => TRUE)))), 'setting');
  return $output;
}

/**
 * Render a piece of a flexible layout.
 */
function panels_flexible_render_items($renderer, $list, $owner_id) {
  $output = '';
  $groups = array('left' => '', 'middle' => '', 'right' => '');
  $max = count($list) - 1;
  $prev = NULL;

  foreach ($list as $position => $id) {
    $item = $renderer->settings['items'][$id];
    $location = isset($renderer->positions[$id]) ? $renderer->positions[$id] : 'middle';

    if ($renderer->admin && $item['type'] != 'row' && $prev ) {
      $groups[$location] .= panels_flexible_render_splitter($renderer, $prev, $id);
    }

    switch ($item['type']) {
      case 'column':
        $content = panels_flexible_render_items($renderer, $item['children'], 'panels-flexible-column-' . $renderer->did . '-' . $id);
        $groups[$location] .= panels_flexible_render_item($renderer, $item, 'panels-flexible-column', $content, $id, $position, $max);
        break;
      case 'row':
        $content = panels_flexible_render_items($renderer, $item['children'], 'panels-flexible-row-' . $renderer->did . '-' . $id);
        $groups[$location] .= panels_flexible_render_item($renderer, $item, 'panels-flexible-row', $content, $id, $position, $max, TRUE);
        break;
      case 'region':
        $content = isset($renderer->content[$id]) ? $renderer->content[$id] : "&nbsp;";
        $groups[$location] .= panels_flexible_render_item($renderer, $item, 'panels-flexible-region', $content, $id, $position, $max);
        break;
    }

    // If all items are fixed then we have a special splitter on the right to
    // control the overall width.
    if (!empty($renderer->admin) && $max == $position && $location == 'left') {
      $groups[$location] .= panels_flexible_render_splitter($renderer, $id, NULL);
    }
    $prev = $id;
  }

  foreach ($groups as $position => $content) {
    if (!empty($content) || $renderer->admin) {
      $output .= '<div class="' . $owner_id . '-' . $position . '">' . $content . '</div>';
    }
  }

  return $output;
}

/**
 * Render a column in the flexible layout.
 */
function panels_flexible_render_item($renderer, $item, $base, $content, $id, $position, $max, $clear = FALSE) {
  $output = '<div class="' . $base . ' ' . $base . '-' . $renderer->did . '-' . $id;
  if ($position == 0) {
    $output .= ' ' . $base . '-first';
  }
  if ($position == $max) {
    $output .= ' ' . $base . '-last';
  }
  if ($clear) {
    $output .= ' clear-block';
  }

  if (isset($item['class'])) {
    $output .= ' ' . check_plain($item['class']);
  }

  $output .= '">' . "\n";

  if (!empty($renderer->admin)) {
    $output .= panels_flexible_render_item_links($renderer, $id, $item);
  }

  $output .= '  <div class="inside ' . $base . '-inside ' . $base . '-' . $renderer->did . '-' . $id . '-inside';
  if ($position == 0) {
    $output .= ' ' . $base . '-inside-first';
  }
  if ($position == $max) {
    $output .= ' ' . $base . '-inside-last';
  }
  if ($clear) {
    $output .= ' clear-block';
  }

  $output .= "\">\n";
  $output .= $content;
  $output .= '  </div>' . "\n";
  $output .= '</div>' . "\n";

  return $output;
}
/**
 * Render a splitter div to place between the $left and $right items.
 *
 * If the right ID is NULL that means there isn't actually a box to the
 * right, but we need a splitter anyway. We'll mostly use info about the
 * left, but pretend it's 'fluid' so that the javascript won't actually
 * modify the right item.
 */
function panels_flexible_render_splitter($renderer, $left_id, $right_id) {
  $left = $renderer->settings['items'][$left_id];

  $left_class = 'panels-flexible-' . $left['type'] . '-' . $renderer->did . '-' . $left_id;
  if ($right_id) {
    $right = $renderer->settings['items'][$right_id];
    $right_class = 'panels-flexible-' . $right['type'] . '-' . $renderer->did . '-' . $right_id;
  }
  else {
    $right = $left;
    $right_class = $left_class;
  }

  $output = '<div class="panels-flexible-splitter flexible-splitter-for-' . $left_class . '">';

  // Name the left object
  $output .= '<span class="panels-flexible-splitter-left">';
  $output .= '.' . $left_class;
  $output .= '</span>';

  $output .= '<span class="panels-flexible-splitter-left-id">';
  $output .= $left_id;
  $output .= '</span>';

  $output .= '<span class="panels-flexible-splitter-left-width ' . $left_class . '-width">';
  $output .= $left['width'];
  $output .= '</span>';

  $output .= '<span class="panels-flexible-splitter-left-scale">';
  $output .= isset($renderer->scale[$left_id]) ? $renderer->scale[$left_id] : 1;
  $output .= '</span>';

  $output .= '<span class="panels-flexible-splitter-left-width-type">';
  $output .= $left['width_type'];
  $output .= '</span>';

  // Name the right object
  $output .= '<span class="panels-flexible-splitter-right">';
  $output .= '.' . $right_class;
  $output .= '</span>';

  $output .= '<span class="panels-flexible-splitter-right-id">';
  $output .= $right_id;
  $output .= '</span>';

  $output .= '<span class="panels-flexible-splitter-right-width ' . $right_class . '-width">';
  $output .= $right['width'];
  $output .= '</span>';

  $output .= '<span class="panels-flexible-splitter-right-scale">';
  $output .= isset($renderer->scale[$right_id]) ? $renderer->scale[$right_id] : 1;
  $output .= '</span>';

  $output .= '<span class="panels-flexible-splitter-right-width-type">';
  // If there is no right, make it fluid.
  $output .= $right_id ? $right['width_type'] : '%';
  $output .= '</span>';

  $output .= '</div>';
  return $output;
}

/**
 * Render the dropdown links for an item.
 */
function panels_flexible_render_item_links($renderer, $id, $item) {
  $links = array();
  $remove = '';
  $add = '';
  if ($item['type'] == 'column') {
    $title = t('Column');
    $settings = t('Column settings');
    if (empty($item['children'])) {
      $remove = t('Remove column');
      $add = t('Add row');
    }
    else {
      $add = t('Add row to top');
      $add2 = t('Add row to bottom');
    }
  }
  else if ($item['type'] == 'row') {
    if ($id == 'canvas') {
      $title = t('Canvas');
    }
    else {
      $title = t('Row');
      $settings = t('Row settings');
    }
    if (empty($item['children'])) {
      if ($item != 'canvas') {
        $remove = t('Remove row');
      }
      $add = $item['contains'] == 'region' ? t('Add region') : t('Add column');
    }
    else {
      $add = $item['contains'] == 'region' ? t('Add region to left') : t('Add column to left');
      $add2 = $item['contains'] == 'region' ? t('Add region to right') : t('Add column to right');
    }
  }
  else if ($item['type'] == 'region') {
    $title = t('Region');
    $settings = t('Region settings');
    $remove = t('Remove region');
  }

  if (!empty($settings)) {
    $links[] = array(
      'title' => $settings,
      'href' => 'panels/ajax/flexible/settings/' . $renderer->cache_key . '/' . $id,
      'attributes' => array('class' => 'ctools-use-modal'),
    );
  }
  if ($add) {
    $links[] = array(
      'title' => $add,
      'href' => 'panels/ajax/flexible/add/' . $renderer->cache_key . '/' . $id,
      'attributes' => array('class' => 'ctools-use-modal'),
    );
  }
  if (isset($add2)) {
    $links[] = array(
      'title' => $add2,
      'href' => 'panels/ajax/flexible/add/' . $renderer->cache_key . '/' . $id . '/right',
      'attributes' => array('class' => 'ctools-use-modal'),
    );
  }
  if ($remove) {
    $links[] = array(
      'title' => $remove,
      'href' => 'panels/ajax/flexible/remove/' . $renderer->cache_key . '/' . $id,
      'attributes' => array('class' => 'ctools-use-ajax'),
    );
  }

  return theme('ctools_dropdown', $title, $links, FALSE,
      'flexible-layout-only flexible-links flexible-title flexible-links-' . $id);
}
/**
 * Provide CSS for a flexible layout.
 */
function panels_flexible_render_css($renderer) {
  $parent_class = $renderer->admin ? '.panels-flexible-row-' . $renderer->did . '-canvas' : '.panel-flexible-' . $renderer->did;
  return panels_flexible_render_css_group($renderer, $renderer->settings['items']['canvas']['children'], $parent_class, 'column');
}

/**
 * Render the CSS for a group of items to be displayed together.
 *
 * Columns and regions, when displayed as a group, need to cooperate in
 * order to share margins and make sure that percent widths add up
 * to the right total.
 */
function panels_flexible_render_css_group($renderer, $list, $owner_id, $type) {
  $css = array();
  panels_flexible_get_css_group($css, $renderer, $list, $owner_id, $type);

  ctools_include('css');
  return ctools_css_assemble($css);
}

/**
 * Construct an array with all of the CSS properties for a group.
 *
 * This will parse down into children and produce all of the CSS needed if you
 * start from the top.
 */
function panels_flexible_get_css_group(&$css, $renderer, $list, $owner_id, $type) {
  if ($type != 'row') {
    // Go through our items and break up into right/center/right groups so we
    // can figure out our offsets.

    // right == any items on the right that are 'fixed'.
    // middle == all fluid items.
    // right == any items on the right that are 'fixed'.
    $left = $middle = $right = array();
    $left_total = $right_total = $middle_total = 0;
    $current = 'left';
    foreach ($list as $id) {
      if ($renderer->settings['items'][$id]['width_type'] == 'px') {
        // fixed
        if ($current == 'left') {
          $left[] = $id;
          $renderer->positions[$id] = 'left';
          $left_total += $renderer->settings['items'][$id]['width'];
        }
        else {
          $current = 'right';
          $right[] = $id;
          $renderer->positions[$id] = 'right';
          $right_total += $renderer->settings['items'][$id]['width'];
        }
      }
      else {
        // fluid
        if ($current != 'right') {
          $current = 'middle';
          $middle[] = $id;
          $renderer->positions[$id] = 'middle';
          $middle_total += $renderer->settings['items'][$id]['width'];
        }
        // fall through: if current is 'right' and we ran into a 'fluid' then
        // it gets *dropped* because that is invalid.
      }
    }

    // Go through our right sides and create CSS.
    foreach ($left as $id) {
      $class = ".panels-flexible-$type-" . $renderer->did . "-$id";
      $css[$class] = array(
        'position' => 'relative',
        'float' => 'left',
        'background-color' => 'transparent',
        'width' => $renderer->settings['items'][$id]['width'] . "px",
      );
    }

    // Do the same for right.
    $right_pixels = 0;

    foreach ($right as $id) {
      $class = ".panels-flexible-$type-" . $renderer->did . "-$id";
      $css[$class] = array(
        'float' => 'left',
        'width' => $renderer->settings['items'][$id]['width'] . "px",
      );
    }

    $max = count($middle) - 1;

    if ($middle_total) {
      // Because we love IE so much, auto scale everything to 99%. This
      // means adding up the actual widths and then providing a multiplier
      // to each so that the total is 99%.
      $scale = 99.0 / $middle_total;
      foreach ($middle as $position => $id) {
        $class = ".panels-flexible-$type-" . $renderer->did . "-$id";
        $css[$class] = array(
          'float' => 'left',
          'width' => ($renderer->settings['items'][$id]['width'] * $scale) . "%",
        );

        // Store this so we can use it later.
        // @todo: Store the scale, not the new width, so .js can adjust
        // bi-directionally.
        $renderer->scale[$id] = $scale;
      }
    }

    // If there is any total remaining, we need to offset the splitter
    // by this much too.
    if ($left_total) {
      $css["$owner_id-left"]['margin-left'] = '-' . $left_total . 'px';
      // IE hack
      $css["* html $owner_id-left"]['left'] = $left_total . "px";
    }
    // Add this even if it's 0 so we can handle removals.
    $css["$owner_id-inside"]['padding-left'] = $left_total . 'px';
    if ($right_total) {
      $css["$owner_id-right"]['margin-right'] = '-' . $right_total . 'px';
    }
    $css["$owner_id-inside"]['padding-right'] = $right_total . 'px';

  }

  // Go through each item and process children.
  foreach ($list as $id) {
    $item = $renderer->settings['items'][$id];
    if (empty($item['children'])) {
      continue;
    }

    if ($type == 'column') {
      // Columns can only contain rows.
      $child_type = 'row';
    }
    else {
      $child_type = isset($item['contains']) ? $item['contains'] : 'region';
    }

    $class = ".panels-flexible-$type-" . $renderer->did . "-$id";
    panels_flexible_get_css_group($css, $renderer, $item['children'], $class, $child_type);
  }
}

/**
 * AJAX responder to edit flexible settings for an item.
 */
function panels_ajax_flexible_edit_settings($cache, $id) {
  $settings = &$cache->display->layout_settings;
  panels_flexible_convert_settings($settings);

  if (empty($settings['items'][$id])) {
    ctools_modal_render(t('Error'), t('Invalid item id.'));
  }

  $item = &$settings['items'][$id];
  $siblings = $settings['items'][$item['parent']]['children'];

  switch ($item['type']) {
    case 'column':
      $title = t('Configure column');
      break;
    case 'row':
      $title = t('Configure row');
      break;
    case 'region':
      $title = t('Configure region');
      break;
  }

  $form_state = array(
    'display' => &$cache->display,
    'item' => &$item,
    'id' => $id,
    'siblings' => $siblings,
    'settings' => &$settings,
    'ajax' => TRUE,
    'title' => $title,
    'op' => 'edit',
  );

  $output = ctools_modal_form_wrapper('panels_flexible_config_item_form', $form_state);
  if (empty($output)) {
    // If the width type changed then other nearby items will have
    // to have their widths adjusted.
    panels_load_include('display-edit');
    panels_edit_cache_set($cache);
    $output = array();
    // If the item is a region, replace the title.
    $class = 'panels-flexible-' . $item['type'] . '-' . $cache->display->did . '-' . $id;
    if ($item['type'] == 'region') {
      $output[] = ctools_ajax_command_replace(".$class h2.label",
        '<h2 class="label">' . check_plain($item['title']) . '</h2>');
    }
    // If not a row, reset the css width if necessary.

    $output[] = ctools_modal_command_dismiss();
  }

  ctools_ajax_render($output);
}

/**
 * Configure a row, column or region on the flexible page.
 *
 * @param <type> $form_state
 * @return <type>
 */
function panels_flexible_config_item_form(&$form_state) {
  $display = &$form_state['display'];
  $item = &$form_state['item'];
  $siblings = &$form_state['siblings'];
  $settings = &$form_state['settings'];
  $id = &$form_state['id'];

//  $form['#action'] = $form_state['url'];

  if ($item['type'] == 'region') {
    $form['title'] = array(
      '#title' => t('Region title'),
      '#type' => 'textfield',
      '#default_value' => $item['title'],
      '#required' => TRUE,
    );

    $form['class'] = array(
      '#title' => t('Region class'),
      '#type' => 'textfield',
      '#default_value' => isset($item['class']) ? $item['class'] : '',
      '#description' => t('Enter a CSS class that will be used for this region. This can be used to apply automatic styling from your theme, for example.'),
    );
  }

  if ($item['type'] != 'row') {
    // Test to see if there are fluid items to the left or the right. If there
    // are fluid items on both sides, this item cannot be set to fixed.
    $left = $right = FALSE;
    $current = 'left';
    foreach ($siblings as $sibling) {
      if ($sibling == $id) {
        $current = 'right';
      }
      else if ($settings['items'][$sibling]['width_type'] == '%') {
        $$current = TRUE; // Indirection.
      }
    }

    $form['width_type'] = array(
      '#type' => 'select',
      '#title' => t('Width'),
      '#default_value' => $item['width_type'],
      '#options' => array(
        '%' => t('Fluid'),
        'px' => t('Fixed'),
      ),
      '#disabled' => TRUE,
    );
  }
  else {
    $form['contains'] = array(
      '#type' => 'select',
      '#title' => t('Contains'),
      '#default_value' => $item['contains'],
      '#options' => array(
        'region' => t('Regions'),
        'column' => t('Columns'),
      ),
    );

    if (!empty($item['children'])) {
      $form['contains']['#disabled'] = TRUE;
      $form['contains']['#value'] = $item['contains'];
      $form['contains']['#description'] = t('You must remove contained items to change the row container type.');
    }
  }

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Submit handler for editing a flexible item.
 */
function panels_flexible_config_item_form_submit(&$form, &$form_state) {
  $item = &$form_state['item'];
  if ($item['type'] == 'region') {
    $item['title'] = $form_state['values']['title'];
    $item['class'] = $form_state['values']['class'];
  }

  if ($item['type'] != 'row') {
    $item['width_type'] = $form_state['values']['width_type'];
  }
  else {
    $item['contains'] = $form_state['values']['contains'];
  }
}

/**
 * AJAX responder to add a new row, column or region to a flexible layout.
 */
function panels_ajax_flexible_edit_add($cache, $id, $location = 'left') {
  ctools_include('modal');
  ctools_include('ajax');
  $settings = &$cache->display->layout_settings;
  panels_flexible_convert_settings($settings);

  if (empty($settings['items'][$id])) {
    ctools_modal_render(t('Error'), t('Invalid item id.'));
  }

  $parent = &$settings['items'][$id];

  switch ($parent['type']) {
    case 'column':
      $title = t('Add row');
      // Create the new item with defaults.
      $item = array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(),
        'parent' => $id,
      );
      break;
    case 'row':
      switch ($parent['contains']) {
        case 'region':
          $title = $location == 'left' ? t('Add region to left') : t('Add region to right');
          $item = array(
            'type' => 'region',
            'title' => '',
            'width' => 100,
            'width_type' => '%',
            'parent' => $id,
          );
          break;
        case 'column':
          $title = $location == 'left' ? t('Add column to left') : t('Add column to right');
          $item = array(
            'type' => 'column',
            'width' => 100,
            'width_type' => '%',
            'parent' => $id,
            'children' => array(),
          );
          break;
      }
      // Create the new item with defaults.
      break;
    case 'region':
      // Cannot add items to regions.
      break;
  }

  $form_state = array(
    'display' => &$cache->display,
    'parent' => &$parent,
    'item' => &$item,
    'id' => $id,
    'settings' => &$settings,
    'ajax' => TRUE,
    'title' => $title,
    'location' => $location,
  );

  $output = ctools_modal_form_wrapper('panels_flexible_add_item_form', $form_state);
  if (empty($output)) {
    // If the width type changed then other nearby items will have
    // to have their widths adjusted.
    panels_load_include('display-edit');
    panels_edit_cache_set($cache);
    $output = array();

    $css_id = isset($cache->display->css_id) ? $cache->display->css_id : '';
    // Create a renderer object so we can render our new stuff.
    $renderer = new stdClass;
    $renderer->settings = $settings;
    $renderer->content = array();
    $renderer->css_id = $css_id;
    $renderer->did = $cache->display->did;
    $renderer->cache_key = $cache->display->cache_key;
    $renderer->id_str = $css_id ? 'id="' . $css_id . '"' : '';
    $renderer->admin = TRUE;

    $content = '';
    if ($item['type'] == 'region') {
      panels_load_include('display-edit');
      $panel_buttons = panels_edit_panel_get_links($cache->display, $form_state['key']);

      $content = panels_render_region_dnd('', $form_state['key'], $item['title'], $panel_buttons);
      // Manually add the hidden field that our region uses to store pane info.
      $content .= '<input type="hidden" name="panel[pane][' .
        $form_state['key'] . ']" id="edit-panel-pane-' . $form_state['key'] . '" value="" />';

    }
    else {
      // We need to make sure the left/middle/right divs exist inside this
      // so that more stuff can be added inside it as needed.
      foreach (array('left', 'middle', 'right') as $position) {
        if (!empty($content) || $renderer->admin) {
          $content .= '<div class="panels-flexible-' . $item['type'] . '-' . $cache->display->did . '-' . $form_state['key'] . '-' . $position . '"></div>';
        }
      }

    }

    // render the item
    $parent_class = 'panels-flexible-' . $parent['type'] . '-' . $cache->display->did . '-' . $id;
    $item_output = panels_flexible_render_item($renderer, $item, 'panels-flexible-' . $item['type'], $content, $form_state['key'], 0, 0, $item['type'] == 'row');

    // Get all the CSS necessary for the entire row (as width adjustments may
    // have cascaded).
    $css = array();
    panels_flexible_get_css_group($css, $renderer, $parent['children'], '.' . $parent_class, $item['type']);

    $position = isset($renderer->positions[$form_state['key']]) ? $renderer->positions[$form_state['key']] : 'middle';
    // If there's a nearby item, add the splitter and rewrite the width
    // of the nearby item as it probably got adjusted.
    // The blocks of code in this else look very similar but are not actually
    // duplicated because the order changes based on left or right.
    switch ($position) {
      case 'left':
        if ($location == 'left') {
          $item_output .= panels_flexible_render_splitter($renderer, $form_state['key'], $form_state['sibling']);
          $output[] = ctools_ajax_command_prepend('.' . $parent_class . '-left', $item_output);
        }
        else if ($location == 'right') {
          // If we are adding to the right side of the left box, there is
          // a splitter that we have to remove; then we add our box normally,
          // and then add a new splitter for just our guy.
          $output[] = ctools_ajax_command_remove('panels-flexible-splitter-for-panels-flexible-' . $item['type'] . '-' . $cache->display->did . '-' . $form_state['key']);
          $item_output = panels_flexible_render_splitter($renderer, $form_state['sibling'], $form_state['key']) .  $item_output;
          $item_output .= panels_flexible_render_splitter($renderer, $form_state['key'], NULL);
          $output[] = ctools_ajax_command_append('.' . $parent_class . '-left', $item_output);
        }
        break;
      case 'right':
        if (!empty($form_state['sibling'])) {
          $item_output = panels_flexible_render_splitter($renderer, $form_state['sibling'], $form_state['key']) .  $item_output;
        }
        $output[] = ctools_ajax_command_append('.' . $parent_class . '-right', $item_output);
        break;
      case 'middle':
        if ($location == 'left') {
          if (!empty($form_state['sibling'])) {
            $item_output .= panels_flexible_render_splitter($renderer, $form_state['key'], $form_state['sibling']);
          }
          $output[] = ctools_ajax_command_prepend('.' . $parent_class . '-middle', $item_output);
        }
        else {
          if (!empty($form_state['sibling'])) {
            $item_output = panels_flexible_render_splitter($renderer, $form_state['sibling'], $form_state['key']) .  $item_output;
          }
          $output[] = ctools_ajax_command_append('.' . $parent_class . '-middle', $item_output);
        }
        break;

    }

    // Send our fix height command.
    $output[] = array('command' => 'flexible_fix_height');

    if (!empty($form_state['sibling'])) {
      $sibling_width = '.panels-flexible-' . $item['type'] . '-' . $cache->display->did . '-' . $form_state['sibling'] . '-width';
      $output[] = ctools_ajax_command_html($sibling_width, $settings['items'][$form_state['sibling']]['width']);
    }
    foreach ($css as $selector => $data) {
      $output[] = ctools_ajax_command_css($selector, $data);
    }

    // Rerender our parent item links:
    $output[] = ctools_ajax_command_replace('.flexible-links-' . $id,
      panels_flexible_render_item_links($renderer, $id, $parent));

    $output[] = array(
      'command' => 'flexible_fix_firstlast',
      'selector' => '.' . $parent_class . '-inside',
      'base' => 'panels-flexible-' . $item['type'],
    );

    $output[] = ctools_modal_command_dismiss();
  }

  ctools_ajax_render($output);
}
/**
 * Form to add a row, column or region to a flexible layout.
 * @param <type> $form_state
 * @return <type>
 */
function panels_flexible_add_item_form(&$form_state) {
  $display = &$form_state['display'];
  $item = &$form_state['item'];
  $parent = &$form_state['parent'];
  $settings = &$form_state['settings'];
  $location = &$form_state['location'];
  $id = &$form_state['id'];

//  $form['#action'] = $form_state['url'];

  if ($item['type'] == 'region') {
    $form['title'] = array(
      '#title' => t('Region title'),
      '#type' => 'textfield',
      '#default_value' => $item['title'],
      '#required' => TRUE,
    );
  }

  if ($item['type'] != 'row') {
    // If there is a 'fixed' type on the side we're adding to, then this
    // must also be fixed. Otherwise it can be either and should default to
    // fluid.
    $restrict = FALSE;

    if (!empty($parent['children'])) {
      if ($location == 'left') {
        $sibling = reset($parent['children']);
      }
      else {
        $sibling = end($parent['children']);
      }
      if ($settings['items'][$sibling]['width_type'] == 'px') {
        $restrict = TRUE;
        $item['width_type'] = 'px';
      }
    }

    $form['width_type'] = array(
      '#type' => 'select',
      '#title' => t('Width'),
      '#default_value' => $item['width_type'],
      '#options' => array(
        '%' => t('Fluid'),
        'px' => t('Fixed'),
      ),
      '#disabled' => $restrict,
    );
    if ($restrict) {
      // This forces the value because disabled items don't always send
      // their data back.
      $form['width_type']['#value'] = $item['width_type'];
      $form['width_type']['#description'] = t('Items cannot be set to fluid if there are fixed items already on that side.');
    }
  }
  else {
    $form['contains'] = array(
      '#type' => 'select',
      '#title' => t('Contains'),
      '#default_value' => $item['contains'],
      '#options' => array(
        'region' => t('Regions'),
        'column' => t('Columns'),
      ),
    );
  }

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Submit handler for editing a flexible item.
 */
function panels_flexible_add_item_form_submit(&$form, &$form_state) {
  $item = &$form_state['item'];
  $parent = &$form_state['parent'];
  $location = &$form_state['location'];
  $settings = &$form_state['settings'];

  if ($item['type'] == 'region') {
    $item['title'] = $form_state['values']['title'];
  }

  if ($item['type'] != 'row') {
    $item['width_type'] = $form_state['values']['width_type'];
  }
  else {
    $item['contains'] = $form_state['values']['contains'];
  }

  if ($item['type'] == 'region') {
    // derive the region key from the title
    $key = preg_replace("/[^a-z0-9]/", '_', drupal_strtolower($item['title']));
    while (isset($settings['items'][$key])) {
      $key .= '_';
    }
    $form_state['key'] = $key;
  }
  else {
    $form_state['key'] = $key = max(array_keys($settings['items'])) + 1;
  }

  $form_state['sibling'] = NULL;
  if ($item['type'] != 'row' && !empty($parent['children'])) {
    // Figure out what the width should be and adjust our sibling if
    // necessary.
    if ($location == 'left') {
      $form_state['sibling'] = reset($parent['children']);
    }
    else {
      $form_state['sibling'] = end($parent['children']);

    }

    // If there is no sibling, or the sibling is of a different type,
    // the default 100 will work for either fixed or fluid.
    if ($form_state['sibling'] && $settings['items'][$form_state['sibling']]['width_type'] == $item['width_type']) {
      // steal half of the sibling's space.
      $width = $settings['items'][$form_state['sibling']]['width'] / 2;
      $settings['items'][$form_state['sibling']]['width'] = $width;
      $item['width'] = $width;
    }
  }

  // Place the item.
  $settings['items'][$key] = $item;
  if ($location == 'left') {
    array_unshift($parent['children'], $key);
  }
  else {
    $parent['children'][] = $key;
  }
}

/**
 * AJAX responder to remove an existing row, column or region from a flexible
 * layout.
 */
function panels_ajax_flexible_edit_remove($cache, $id) {
  $settings = &$cache->display->layout_settings;
  panels_flexible_convert_settings($settings);

  if (empty($settings['items'][$id])) {
    ctools_ajax_render_error(print_r($settings['items'], 1));
    ctools_ajax_render_error(t('Invalid item id.'));
  }

  $item = &$settings['items'][$id];

  $siblings = &$settings['items'][$item['parent']]['children'];
  $parent_class = '.panels-flexible-' . $settings['items'][$item['parent']]['type'] .
    '-' . $cache->display->did . '-' . $item['parent'];

  // Find the offset of our array. This will also be the key because
  // this is a simple array.
  $offset = array_search($id, $siblings);

  // Only bother with this stuff if our item is fluid, since fixed is
  // as fixed does.
  if ($item['type'] != 'row') {
    if (isset($siblings[$offset + 1])) {
      $next = $siblings[$offset + 1];
    }
    if (isset($siblings[$offset - 1])) {
      $prev = $siblings[$offset - 1];
    }

    if ($item['width_type'] == '%') {
      // First, try next.
      if (isset($next) && $settings['items'][$next]['width_type'] == '%') {
        $settings['items'][$next]['width'] += $item['width'];
      }
      // If that failed, try the previous one.
      else if (isset($prev) && $settings['items'][$prev]['width_type'] == '%') {
        $settings['items'][$prev]['width'] += $item['width'];
      }
    }
    // Not sure what happens if they both failed. Maybe nothing.
  }

  // Remove the item.
  array_splice($siblings, $offset, 1);

  unset($settings['items'][$id]);

  // Save our new state.
  panels_load_include('display-edit');
  panels_edit_cache_set($cache);
  $class = 'panels-flexible-' . $item['type'] . '-' . $cache->display->did . '-' . $id;
  $output = array();

  $output[] = ctools_ajax_command_remove('.' . $class);

  $css_id = isset($cache->display->css_id) ? $cache->display->css_id : '';
  // Create a renderer object so we can render our new stuff.
  $renderer = new stdClass;
  $renderer->settings = $settings;
  $renderer->content = array();
  $renderer->css_id = $css_id;
  $renderer->did = $cache->display->did;
  $renderer->cache_key = $cache->display->cache_key;
  $renderer->id_str = $css_id ? 'id="' . $css_id . '"' : '';
  $renderer->admin = TRUE;

  // Regenerate the CSS for siblings.
  if (!empty($siblings)) {
    // Get all the CSS necessary for the entire row (as width adjustments may
    // have cascaded).
    $css = array();
    panels_flexible_get_css_group($css, $renderer, $siblings, $parent_class, $item['type']);
    foreach ($css as $selector => $data) {
      $output[] = ctools_ajax_command_css($selector, $data);
    }
  }

  // There are potentially two splitters linked to this item to be removed.
  if (!empty($prev)) {
    $output[] = ctools_ajax_command_remove('.flexible-splitter-for-panels-flexible-' . $item['type'] . '-' . $cache->display->did . '-' . $prev);
  }

  // Try to remove the 'next' one even if there isn't a $next.
  $output[] = ctools_ajax_command_remove('.flexible-splitter-for-panels-flexible-' . $item['type'] . '-' . $cache->display->did . '-' . $id);

  if (!empty($prev) && !empty($next)) {
    // Add a new splitter that links $prev and $next:
    $splitter = panels_flexible_render_splitter($renderer, $prev, $next);
    $prev_class = '.panels-flexible-' . $item['type'] . '-' . $cache->display->did . '-' . $prev;
    $output[] = ctools_ajax_command_after($prev_class, $splitter);
    // Send our fix height command.
    $output[] = array('command' => 'flexible_fix_height');
  }
  // Rerender our parent item links:
  $output[] = ctools_ajax_command_replace('.flexible-links-' . $item['parent'],
    panels_flexible_render_item_links($renderer, $item['parent'], $settings['items'][$item['parent']]));

  $output[] = array(
    'command' => 'flexible_fix_firstlast',
    'selector' => $parent_class . '-inside',
    'base' => 'panels-flexible-' . $item['type'],
  );

  ctools_ajax_render($output);
}

/**
 * AJAX responder to store resize information when the user adjusts the
 * splitter.
 */
function panels_ajax_flexible_edit_resize($cache) {
  ctools_include('ajax');
  $settings = &$cache->display->layout_settings;
  panels_flexible_convert_settings($settings);

  $settings['items'][$_POST['left']]['width'] = $_POST['left_width'];
  if (!empty($_POST['right']) && $_POST['right'] != $_POST['left']) {
    $settings['items'][$_POST['right']]['width'] = $_POST['right_width'];
  }

  // Save our new state.
  panels_load_include('display-edit');
  panels_edit_cache_set($cache);

  ctools_ajax_render(array('ok'));
}

