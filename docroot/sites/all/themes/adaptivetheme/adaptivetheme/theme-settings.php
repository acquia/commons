<?php // $Id: theme-settings.php,v 1.1.2.44 2010/03/26 22:35:31 jmburnz Exp $
// adaptivethemes.com

/**
 * @file theme-settings.php
 */

// Initialize theme settings.
include_once(drupal_get_path('theme', 'adaptivetheme') .'/inc/template.theme-settings.inc');

/**
* Implementation of themehook_settings() function.
* The inspiration for these theme settings comes mainly from three themes - Zen,
* Acquia Marina and Mothership. I have added many other settings and refactored most
* of the original code to suit our purpose. Kudos to those who did it first.
*
* @param $saved_settings
*   An array of saved settings for this theme.
* @return
*   A form array.
*/
function adaptivetheme_settings($saved_settings, $subtheme_defaults = array()) {

  global $theme_info;

  // Get the node types
  $node_types = node_get_types('names');

  // Get the default values from the .info file.
  $defaults = adaptivetheme_theme_get_default_settings('adaptivetheme');

  // Allow a subtheme to override the default values.
  $defaults = array_merge($defaults, $subtheme_defaults);

  // Set the default values for content type specific settings
  foreach ($node_types as $type => $name) {
    $defaults["taxonomy_display_{$type}"] = $defaults['taxonomy_display_default'];
    $defaults["taxonomy_format_{$type}"]  = $defaults['taxonomy_format_default'];
    $defaults["taxonomy_delimiter_{$type}"] = $defaults['taxonomy_delimiter_default'];
    $defaults["submitted_by_author_{$type}"] = $defaults['submitted_by_author_default'];
    $defaults["submitted_by_date_{$type}"] = $defaults['submitted_by_date_default'];
    $defaults["display_links_{$type}"] = $defaults['display_links_default'];
  }

  // Merge the saved variables and their default values
  $settings = array_merge($defaults, $saved_settings);

  // Export theme settings
  $exportable_settings = array (
    'skip_navigation_display'           => $settings['skip_navigation_display'],
    'breadcrumb_display'                => $settings['breadcrumb_display'],
    'breadcrumb_separator'              => $settings['breadcrumb_separator'],
    'breadcrumb_home'                   => $settings['breadcrumb_home'],
    'breadcrumb_trailing'               => $settings['breadcrumb_trailing'],
    'breadcrumb_title'                  => $settings['breadcrumb_title'],
    'display_search_form_label'         => $settings['display_search_form_label'],
    'search_snippet'                    => $settings['search_snippet'],
    'search_info_type'                  => $settings['search_info_type'],
    'search_info_user'                  => $settings['search_info_user'],
    'search_info_date'                  => $settings['search_info_date'],
    'search_info_comment'               => $settings['search_info_comment'],
    'search_info_upload'                => $settings['search_info_upload'],
    'search_info_separator'             => $settings['search_info_separator'],
    'primary_links_tree'                => $settings['primary_links_tree'],
    'secondary_links_tree'              => $settings['secondary_links_tree'],
    'mission_statement_pages'           => $settings['mission_statement_pages'],
    'taxonomy_settings_enabled'         => $settings['taxonomy_settings_enabled'],
    'taxonomy_display_default'          => $settings['taxonomy_display_default'],
    'taxonomy_format_default'           => $settings['taxonomy_format_default'],
    'taxonomy_delimiter_default'        => $settings['taxonomy_delimiter_default'],
    'taxonomy_enable_content_type'      => $settings['taxonomy_enable_content_type'],
    'submitted_by_settings_enabled'     => $settings['submitted_by_settings_enabled'],
    'submitted_by_author_default'       => $settings['submitted_by_author_default'],
    'submitted_by_date_default'         => $settings['submitted_by_date_default'],
    'submitted_by_enable_content_type'  => $settings['submitted_by_enable_content_type'],
    'display_links_settings_enabled'    => $settings['display_links_settings_enabled'],
    'display_links_default'             => $settings['display_links_default'],
    'display_links_enable_content_type' => $settings['display_links_enable_content_type'],
    'rebuild_registry'                  => $settings['rebuild_registry'],
    'show_theme_info'                   => $settings['show_theme_info'],
    'cleanup_classes_section'           => $settings['cleanup_classes_section'],
    'cleanup_classes_front'             => $settings['cleanup_classes_front'],
    'cleanup_classes_user_status'       => $settings['cleanup_classes_user_status'],
    'cleanup_classes_normal_path'       => $settings['cleanup_classes_normal_path'],
    'cleanup_classes_node_type'         => $settings['cleanup_classes_node_type'],
    'cleanup_classes_add_edit_delete'   => $settings['cleanup_classes_add_edit_delete'],
    'cleanup_classes_language'          => $settings['cleanup_classes_language'],
    'cleanup_article_id'                => $settings['cleanup_article_id'],
    'cleanup_article_classes_promote'   => $settings['cleanup_article_classes_promote'],
    'cleanup_article_classes_sticky'    => $settings['cleanup_article_classes_sticky'],
    'cleanup_article_classes_teaser'    => $settings['cleanup_article_classes_teaser'],
    'cleanup_article_classes_preview'   => $settings['cleanup_article_classes_preview'],
    'cleanup_article_classes_type'      => $settings['cleanup_article_classes_type'],
    'cleanup_article_classes_language'  => $settings['cleanup_article_classes_language'],
    'cleanup_comment_anonymous'         => $settings['cleanup_comment_anonymous'],
    'cleanup_comment_article_author'    => $settings['cleanup_comment_article_author'],
    'cleanup_comment_by_viewer'         => $settings['cleanup_comment_by_viewer'],
    'cleanup_comment_new'               => $settings['cleanup_comment_new'],
    'cleanup_comment_zebra'             => $settings['cleanup_comment_zebra'],
    'cleanup_comment_wrapper_type'      => $settings['cleanup_comment_wrapper_type'],
    'cleanup_block_block_module_delta'  => $settings['cleanup_block_block_module_delta'],
    'cleanup_block_classes_module'      => $settings['cleanup_block_classes_module'],
    'cleanup_block_classes_zebra'       => $settings['cleanup_block_classes_zebra'],
    'cleanup_block_classes_region'      => $settings['cleanup_block_classes_region'],
    'cleanup_block_classes_count'       => $settings['cleanup_block_classes_count'],
    'cleanup_menu_menu_class'           => $settings['cleanup_menu_menu_class'],
    'cleanup_menu_leaf_class'           => $settings['cleanup_menu_leaf_class'],
    'cleanup_menu_first_last_classes'   => $settings['cleanup_menu_first_last_classes'],
    'cleanup_menu_active_classes'       => $settings['cleanup_menu_active_classes'],
    'cleanup_menu_title_class'          => $settings['cleanup_menu_title_class'],
    'cleanup_links_type_class'          => $settings['cleanup_links_type_class'],
    'cleanup_links_active_classes'      => $settings['cleanup_links_active_classes'],
    'cleanup_links_first_last_classes'  => $settings['cleanup_links_first_last_classes'],
    'cleanup_item_list_zebra'           => $settings['cleanup_item_list_zebra'],
    'cleanup_item_list_first_last'      => $settings['cleanup_item_list_first_last'],
    'cleanup_views_css_name'            => $settings['cleanup_views_css_name'],
    'cleanup_views_view_name'           => $settings['cleanup_views_view_name'],
    'cleanup_views_display_id'          => $settings['cleanup_views_display_id'],
    'cleanup_views_dom_id'              => $settings['cleanup_views_dom_id'],
    'cleanup_views_unformatted'         => $settings['cleanup_views_unformatted'],
    'cleanup_views_item_list'           => $settings['cleanup_views_item_list'],
    'cleanup_fields_type'               => $settings['cleanup_fields_type'],
    'cleanup_fields_name'               => $settings['cleanup_fields_name'],
    'cleanup_fields_zebra'              => $settings['cleanup_fields_zebra'],
    'cleanup_headings_title_class'      => $settings['cleanup_headings_title_class'],
    'cleanup_headings_namespaced_class' => $settings['cleanup_headings_namespaced_class'],
    'links_add_span_elements'           => $settings['links_add_span_elements'],
    'at_user_menu'                      => $settings['at_user_menu'],
    'block_edit_links'                  => $settings['block_edit_links'],
    'at_admin_hide_help'                => $settings['at_admin_hide_help'],
    'layout_method'                     => $settings['layout_method'],
    'layout_width'                      => $settings['layout_width'],
    'layout_sidebar_first_width'        => $settings['layout_sidebar_first_width'],
    'layout_sidebar_last_width'         => $settings['layout_sidebar_last_width'],
    'layout_enable_settings'            => $settings['layout_enable_settings'],
    'layout_enable_width'               => $settings['layout_enable_width'],
    'layout_enable_sidebars'            => $settings['layout_enable_sidebars'],
    'layout_enable_method'              => $settings['layout_enable_method'],
    'layout_enable_frontpage'           => $settings['layout_enable_frontpage'],
    'equal_heights_sidebars'            => $settings['equal_heights_sidebars'],
    'equal_heights_blocks'              => $settings['equal_heights_blocks'],
    'equal_heights_gpanels'             => $settings['equal_heights_gpanels'],
    'horizontal_login_block'            => $settings['horizontal_login_block'],
    'horizontal_login_block_overlabel'  => $settings['horizontal_login_block_overlabel'],
    'horizontal_login_block_enable'     => $settings['horizontal_login_block_enable'],
    'color_schemes'                     => $settings['color_schemes'],
    'color_enable_schemes'              => $settings['color_enable_schemes'],
  );
  // Output key value pairs formatted as settings
  foreach($exportable_settings as $key => $value) {
  	$value = filter_xss($value);
  	$output .= "settings[$key]=\"$value\"\n";
  }
  $exports = $output;

  // Create the form using Forms API: http://api.drupal.org/api/6
  // General Settings
  $form['general_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Skip Navigation
  $form['general_settings']['skip_navigation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Skip Navigation'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['general_settings']['skip_navigation']['skip_navigation_display'] = array(
    '#type' => 'radios',
    '#title'  => t('Modify the display of the skip navigation'),
    '#default_value' => $settings['skip_navigation_display'],
    '#options' => array(
      'show' => t('Show skip navigation'),
      'focus' => t('Show skip navigation when in focus, otherwise is hidden'),
      'hide' => t('Hide skip navigation'),
    ),
  );
  // Mission Statement
  $form['general_settings']['mission_statement'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mission statement'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['general_settings']['mission_statement']['mission_statement_pages'] = array(
    '#type' => 'radios',
    '#title' => t('Where should the mission statement be displayed'),
    '#default_value' => $settings['mission_statement_pages'],
    '#options' => array(
      'home' => t('Display the mission statement only on the home page'),
      'all' => t('Display the mission statement on all pages'),
    ),
  );
  // Breadcrumbs
  $form['general_settings']['breadcrumb'] = array(
    '#type' => 'fieldset',
    '#title' => t('Breadcrumb'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['general_settings']['breadcrumb']['breadcrumb_display'] = array(
    '#type' => 'select',
    '#title' => t('Display breadcrumb'),
    '#default_value' => $settings['breadcrumb_display'],
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
      'admin' => t('Only in the admin section'),
    ),
  );
  $form['general_settings']['breadcrumb']['breadcrumb_separator'] = array(
    '#type'  => 'textfield',
    '#title' => t('Breadcrumb separator'),
    '#description' => t('Text only. Dont forget to include spaces.'),
    '#default_value' => $settings['breadcrumb_separator'],
    '#size' => 8,
    '#maxlength' => 10,
    '#prefix' => '<div id="div-breadcrumb-collapse">',
  );
  $form['general_settings']['breadcrumb']['breadcrumb_home'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the home page link in breadcrumbs'),
    '#default_value' => $settings['breadcrumb_home'],
  );
  $form['general_settings']['breadcrumb']['breadcrumb_trailing'] = array(
    '#type' => 'checkbox',
    '#title' => t('Append a separator to the end of the breadcrumb'),
    '#default_value' => $settings['breadcrumb_trailing'],
    '#description' => t('Useful when the breadcrumb is placed just before the title.'),
  );
  $form['general_settings']['breadcrumb']['breadcrumb_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Append the content title to the end of the breadcrumb'),
    '#default_value' => $settings['breadcrumb_title'],
    '#description' => t('Useful when the breadcrumb is not placed just before the title.'),
    '#suffix' => '</div>',
  );
  // Search Settings
  $form['general_settings']['search'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Search forms
  $form['general_settings']['search']['search_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search forms'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['general_settings']['search']['search_form']['display_search_form_label'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the search form label <em>"Search this site"</em>'),
    '#default_value' => $settings['display_search_form_label'],
  );
  // Search results
  $form['general_settings']['search']['search_results'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search results'),
    '#description' => t('What additional information should be displayed in your search results?'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['general_settings']['search']['search_results']['search_snippet'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display text snippet'),
    '#default_value' => $settings['search_snippet'],
  );
  $form['general_settings']['search']['search_results']['search_info_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display content type'),
    '#default_value' => $settings['search_info_type'],
  );
  $form['general_settings']['search']['search_results']['search_info_user'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display author name'),
    '#default_value' => $settings['search_info_user'],
  );
  $form['general_settings']['search']['search_results']['search_info_date'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display posted date'),
    '#default_value' => $settings['search_info_date'],
  );
  $form['general_settings']['search']['search_results']['search_info_comment'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display comment count'),
    '#default_value' => $settings['search_info_comment'],
  );
  $form['general_settings']['search']['search_results']['search_info_upload'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display attachment count'),
    '#default_value' => $settings['search_info_upload'],
  );
  // Search_info_separator
  $form['general_settings']['search']['search_results']['search_info_separator'] = array(
    '#type' => 'textfield',
    '#title' => t('Search info separator'),
    '#description' => t('Modify the separator. The default is a hypen with a space before and after.'),
    '#default_value' => $settings['search_info_separator'],
    '#size' => 8,
    '#maxlength' => 10,
  );
  // Primary and Secondary Links Settings
  $form['general_settings']['menu_trees'] = array(
    '#type' => 'fieldset',
    '#title' => t('Primary and Secondary Links'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Output Primary and Secondary links as standard Drupal menus (shows levels expanded and with the standard menu classes).'),
  );
  $form['general_settings']['menu_trees']['primary_links_tree'] = array(
    '#type' => 'checkbox',
    '#title' => 'Modify Primary Links',
    '#default_value' => $settings['primary_links_tree'],
  );
  $form['general_settings']['menu_trees']['secondary_links_tree'] = array(
    '#type' => 'checkbox',
    '#title' => 'Modify Secondary Links',
    '#default_value' => $settings['secondary_links_tree'],
  );
  // Node Settings
  $form['node_type_specific'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content type settings'),
    '#description' => t('Use these settings to change the meta information shown with your content.  You can apply these settings to all content types, or check <em>"Use content type specific settings"</em> to customize them for each content type.  For example, you may want to show the date on Stories, but not on other content types.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Author & Date Settings
  $form['node_type_specific']['submitted_by_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Author &amp; Date'),
    '#description' => t('Modify the output of the Author and Date for content types'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['node_type_specific']['submitted_by_container']['submitted_by_settings_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Author &amp; Date Settings'),
    '#description' => t('These settings are disabled by default to avoid conflicts with modules, such as the <a href="!link">Submitted By</a> module. If you encounter issues with a module try disabling this setting.', array('!link' => 'http://drupal.org/project/submitted_by')),
    '#default_value' => $settings['submitted_by_settings_enabled'],
  );
  if ($settings['submitted_by_settings_enabled'] == 1) {
    if (module_exists('submitted_by') == FALSE) {
      // Default & content type specific settings
      foreach ((array('default' => 'Default') + node_get_types('names')) as $type => $name) {
        $form['node_type_specific']['submitted_by_container']['submitted_by'][$type] = array(
          '#type' => 'fieldset',
          '#title' => t('@name', array('@name' => $name)),
          '#description' => t('These settings allow you to modify the output of the Author and Date information shown on articles. For more options you can install the <a href="!link">Submitted By</a> module.', array('!link' => 'http://drupal.org/project/submitted_by')),
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
        );
        $form['node_type_specific']['submitted_by_container']['submitted_by'][$type]["submitted_by_author_{$type}"] = array(
          '#type' => 'checkbox',
          '#title' => t('Display author\'s username'),
          '#default_value' => $settings["submitted_by_author_{$type}"],
        );
        $form['node_type_specific']['submitted_by_container']['submitted_by'][$type]["submitted_by_date_{$type}"] = array(
          '#type' => 'checkbox',
          '#title' => t('Display date posted (you can customize this format on the Date and Time settings page.)'),
          '#default_value' => $settings["submitted_by_date_{$type}"],
        );
        // Options for default settings
        if ($type == 'default') {
          $form['node_type_specific']['submitted_by_container']['submitted_by']['default']['#title'] = t('Default');
          $form['node_type_specific']['submitted_by_container']['submitted_by']['default']['#collapsed'] = $settings['submitted_by_enable_content_type'] ? TRUE : FALSE;
          $form['node_type_specific']['submitted_by_container']['submitted_by']['submitted_by_enable_content_type'] = array(
            '#type' => 'checkbox',
            '#title' => t('Use content type specific settings.'),
            '#default_value' => $settings['submitted_by_enable_content_type'],
          );
        }
        // Collapse content type specific settings if default settings are being used
        else if ($settings['submitted_by_enable_content_type'] == 0) {
        $form['submitted_by'][$type]['#collapsed'] = TRUE;
        }
      }
    }
    else {
      $form['node_type_specific']['submitted_by_container']['#description'] = t('NOTICE: You currently have the <a href="!link">Submitted By</a> module installed and enabled - the author and date theme settings have been disabled to prevent conflicts.', array('!link' => 'http://drupal.org/project/submitted_by'));
      $form['node_type_specific']['submitted_by_container']['submitted_by'][$type]['#disabled'] = 'disabled';
    }
  }
  // Taxonomy term display
  if (module_exists('taxonomy')) {
    $form['node_type_specific']['display_taxonomy_container'] = array(
      '#type' => 'fieldset',
      '#title' => t('Taxonomy Terms'),
      '#description' => t('Modify the output of the Taxonomy Terms for content types'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['node_type_specific']['display_taxonomy_container']['taxonomy_settings_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable Taxonomy Term Settings'),
      '#description' => t('These settings are disabled by default to avoid conflicts with modules. If you encounter issues with a module that modifies the display or output of Taxonomy Terms try disabling this setting.'),
      '#default_value' => $settings['taxonomy_settings_enabled'],
    );
    if ($settings['taxonomy_settings_enabled'] == 1) {
      // Default & content type specific settings
      foreach ((array('default' => 'Default') + node_get_types('names')) as $type => $name) {
        // taxonomy display per node
        $form['node_type_specific']['display_taxonomy_container']['display_taxonomy'][$type] = array(
          '#type' => 'fieldset',
          '#title' => t('@name', array('@name' => $name)),
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
        );
        // Display
        $form['node_type_specific']['display_taxonomy_container']['display_taxonomy'][$type]["taxonomy_display_{$type}"] = array(
          '#type' => 'select',
          '#title' => t('When should taxonomy terms be displayed?'),
          '#default_value' => $settings["taxonomy_display_{$type}"],
          '#options' => array(
            'all' => t('Always display terms'),
            'only' => t('Hide terms on teasers'),
            'never' => t('Never display terms'),
          ),
        );
        // Formatting
        $form['node_type_specific']['display_taxonomy_container']['display_taxonomy'][$type]["taxonomy_format_{$type}"] = array(
          '#type' => 'radios',
          '#title' => t('Taxonomy display format'),
          '#default_value' => $settings["taxonomy_format_{$type}"],
          '#options' => array(
            'vocab' => t('Display each vocabulary on a new line'),
            'list' => t('Display all taxonomy terms together in single list'),
          ),
        );
        // Delimiter
        $form['node_type_specific']['display_taxonomy_container']['display_taxonomy'][$type]["taxonomy_delimiter_{$type}"] = array(
          '#type' => 'textfield',
          '#title' => t('Delimiter'),
          '#description' => t('Modify the delimiter. The default is a comma followed by a space.'),
          '#default_value' => $settings['taxonomy_delimiter_default'],
          '#size' => 8,
          '#maxlength' => 10,
        );
        // Get taxonomy vocabularies by node type
        $vocabs = array();
        $vocabs_by_type = ($type == 'default') ? taxonomy_get_vocabularies() : taxonomy_get_vocabularies($type);
        foreach ($vocabs_by_type as $key => $value) {
          $vocabs[$value->vid] = $value->name;
        }
        // Display taxonomy checkboxes
        foreach ($vocabs as $key => $vocab_name) {
          $form['node_type_specific']['display_taxonomy_container']['display_taxonomy'][$type]["taxonomy_vocab_display_{$type}_{$key}"] = array(
            '#type' => 'checkbox',
            '#title' => t('Display vocabulary: @vocab_name', array('@vocab_name' => $vocab_name)),
            '#default_value' => $settings["taxonomy_vocab_display_{$type}_{$key}"],
          );
        }
        // Options for default settings
        if ($type == 'default') {
          $form['node_type_specific']['display_taxonomy_container']['display_taxonomy']['default']['#title'] = t('Default');
          $form['node_type_specific']['display_taxonomy_container']['display_taxonomy']['default']['#collapsed'] = $settings['taxonomy_enable_content_type'] ? TRUE : FALSE;
          $form['node_type_specific']['display_taxonomy_container']['display_taxonomy']['taxonomy_enable_content_type'] = array(
            '#type' => 'checkbox',
            '#title' => t('Use content type specific settings.'),
            '#default_value' => $settings['taxonomy_enable_content_type'],
          );
        }
        // Collapse content type specific settings if default settings are being used
        else if ($settings['taxonomy_enable_content_type'] == 0) {
          $form['display_taxonomy'][$type]['#collapsed'] = TRUE;
        }
      }
    }
  }
  // Links display
  $form['node_type_specific']['links_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Links'),
    '#description' => t('Links are the "links" displayed at the bottom of articles.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['node_type_specific']['links_container']['display_links_settings_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Links Settings'),
    '#description' => t('These settings are disabled by default to avoid conflicts with modules. If you encounter issues with a module that modifies the display or output of Links try disabling this setting.'),
    '#default_value' => $settings['display_links_settings_enabled'],
  );
  if ($settings['display_links_settings_enabled'] == 1) {
    // Default & content type specific settings
    foreach ((array('default' => 'Default') + node_get_types('names')) as $type => $name) {
      $form['node_type_specific']['links_container']['links'][$type] = array(
        '#type' => 'fieldset',
        '#title' => t('@name', array('@name' => @$name)),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form['node_type_specific']['links_container']['links'][$type]["display_links_{$type}"] = array(
        '#type' => 'select',
        '#title' => t('Display Links'),
        '#default_value' => $settings["display_links_{$type}"],
        '#options' => array(       
          'all' => t('Always display links'),
          'only' => t('Hide links on teasers'),
          'never' => t('Never display links'),
        ),
      );
      // Options for default settings
      if ($type == 'default') {
        $form['node_type_specific']['links_container']['links']['default']['#title'] = t('Default');
        $form['node_type_specific']['links_container']['links']['default']['#collapsed'] = $settings['display_links_enable_content_type'] ? TRUE : FALSE;
        $form['node_type_specific']['links_container']['links']['display_links_enable_content_type'] = array(
          '#type' => 'checkbox',
          '#title' => t('Use content type specific settings.'),
          '#default_value' => $settings['display_links_enable_content_type'],
        );
      }
      // Collapse content type specific settings if default settings are being used
      else if ($settings['display_links_enable_content_type'] == 0) {
        $form['links'][$type]['#collapsed'] = TRUE;
      }
    }
  }
  // Layout settings
  $form['layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layout settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  if ($settings['layout_enable_settings'] == 'on') {
    $image_path = drupal_get_path('theme', 'adaptivetheme') .'/css/core-images';
    $form['layout']['page_layout'] = array(
      '#type' => 'fieldset',
      '#title' => t('Page Layout'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => t('Use these settings to customize the layout of your theme.'),
    );
    if ($settings['layout_enable_width'] == 'on') {
      $form['layout']['page_layout']['layout_width_help'] = array(
        '#prefix' => '<div class="layout-help">',
        '#suffix' => '</div>',
        '#value' => t('<dl><dt>Page width</dt><dd>Set the overall width of the the page.</dd></dl>'),
      );
      $form['layout']['page_layout']['layout_width'] = array(
        '#type' => 'select',
        '#prefix' => '<div class="page-width">',
        '#suffix' => '</div>',
        '#default_value' => $settings['layout_width'],
        '#options' => array(
          '720px' => t('720px'),
          '780px' => t('780px'),
          '840px' => t('840px'),
          '900px' => t('900px'),
          '960px' => t('960px'),
          '1020px' => t('1020px'),
          '1080px' => t('1080px'),
          '1140px' => t('1140px'),
          '1200px' => t('1200px'),
          '1260px' => t('1260px'),
          '100%' => t('100% Fluid'),
        ),
        '#attributes' => array('class' => 'field-layout-width'),
      );
    } // endif width
    if ($settings['layout_enable_sidebars'] == 'on') {
      $form['layout']['page_layout']['layout_sidebar_help'] = array(
        '#prefix' => '<div class="layout-help">',
        '#suffix' => '</div>',
        '#value' => t('<dl><dt>Sidebar widths</dt><dd>Set the width of each sidebar. The content columm will stretch to fill the rest of the page width.</dd></dl>'),
      );
      $form['layout']['page_layout']['layout_sidebar_first_width'] = array(
        '#type' => 'select',
        '#title' => t('Sidebar first'),
        '#prefix' => '<div class="sidebar-width"><div class="sidebar-width-left">',
        '#suffix' => '</div>',
        '#default_value' => $settings['layout_sidebar_first_width'],
        '#options' => array(
          '60' => t('60px'),
          '120' => t('120px'),
          '160' => t('160px'),
          '180' => t('180px'),
          '240' => t('240px'),
          '300' => t('300px'),
          '320' => t('320px'),
          '360' => t('360px'),
          '420' => t('420px'),
          '480' => t('480px'),
          '540' => t('540px'),
          '600' => t('600px'),
          '660' => t('660px'),
          '720' => t('720px'),
          '780' => t('780px'),
          '840' => t('840px'),
          '900' => t('900px'),
          '960' => t('960px'),
        ),
        '#attributes' => array('class' => 'sidebar-width-select'),
      );
      $form['layout']['page_layout']['layout_sidebar_last_width'] = array(
        '#type' => 'select',
        '#title' => t('Sidebar last'),
        '#prefix' => '<div class="sidebar-width-right">',
        '#suffix' => '</div></div>',
        '#default_value' => $settings['layout_sidebar_last_width'],
        '#options' => array(
          '60' => t('60px'),
          '120' => t('120px'),
          '160' => t('160px'),
          '180' => t('180px'),
          '240' => t('240px'),
          '300' => t('300px'),
          '320' => t('320px'),
          '360' => t('360px'),
          '420' => t('420px'),
          '480' => t('480px'),
          '540' => t('540px'),
          '600' => t('600px'),
          '660' => t('660px'),
          '720' => t('720px'),
          '780' => t('780px'),
          '840' => t('840px'),
          '900' => t('900px'),
          '960' => t('960px'),
        ),
        '#attributes' => array('class' => 'sidebar-width-select'),
      );
    } //endif layout sidebars
    if ($settings['layout_enable_method'] == 'on') {
      $form['layout']['page_layout']['layout_method_help'] = array(
        '#prefix' => '<div class="layout-help">',
        '#suffix' => '</div>',
        '#value' => t('<dl><dt>Sidebar layout</dt><dd>Set the default sidebar configuration. You can choose a standard three column layout or place both sidebars to the right or left of the main content column.</dd></dl>'),
      );
      $form['layout']['page_layout']['layout_method'] = array(
        '#type' => 'radios',
        '#prefix' => '<div class="layout-method">',
        '#suffix' => '</div>',
        '#default_value' => $settings['layout_method'],
        '#options' => array(
          '0' => t('<strong>Layout #1</strong>') . theme('image', $image_path .'/layout-default.png') . t('<span class="layout-type">Standard three column layout—left, content, right.</span>'),
          '1' => t('<strong>Layout #2</strong>') . theme('image', $image_path .'/layout-sidebars-right.png') . t('<span class="layout-type">Two columns on the right—content, left, right.</span>'),
          '2' => t('<strong>Layout #3</strong>') . theme('image', $image_path .'/layout-sidebars-left.png') . t('<span class="layout-type">Two columns on the left—left, right, content.</span>'),
        ),
       '#attributes' => array('class' => 'layouts'),
      );
      $form['layout']['page_layout']['layout_enable_settings'] = array(
        '#type' => 'hidden',
        '#value' => $settings['layout_enable_settings'],
      );
    } // endif layout method
  } // endif layout settings
  // Equal heights settings
  $form['layout']['equal_heights'] = array(
    '#type' => 'fieldset',
    '#title' => t('Equal Heights'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description'   => t('These settings allow you to set the sidebars and/or region blocks to be equal height.'),
  );
  // Equal height sidebars
  $form['layout']['equal_heights']['equal_heights_sidebars'] = array(
    '#type' => 'checkbox',
    '#title' => t('Equal Height Sidebars'),
    '#default_value' => $settings['equal_heights_sidebars'],
    '#description'   => t('This setting will make the sidebars and the main content column equal to the height of the tallest column.'),
  );
  // Equal height gpanels
  $form['layout']['equal_heights']['equal_heights_gpanels'] = array(
    '#type' => 'checkbox',
    '#title' => t('Equal Height Gpanels'),
    '#default_value' => $settings['equal_heights_gpanels'],
    '#description'   => t('This will make all Gpanel blocks equal to the height of the tallest block in any Gpanel, regardless of which Gpanel the blocks are in. Good for creating a grid type block layout, however it could be too generic if you have more than one Gpanel active in the page.'),
  );
  // Equal height blocks per region
  $equalized_blocks = array(
    'leaderboard' => t('Leaderboard region'),
    'header' => t('Header region'),
    'secondary-content' => t('Secondary Content region'),
    'content-top' => t('Content Top region'),
    'content-bottom' => t('Content Bottom region'),
    'tertiary-content' => t('Tertiary Content region'),
    'footer' => t('Footer region'),
  );
  $form['layout']['equal_heights']['equal_heights_blocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Equal Height Blocks'),
  );
  $form['layout']['equal_heights']['equal_heights_blocks'] += array(
    '#prefix' => '<div id="div-equalize-collapse">',
    '#suffix' => '</div>',
    '#description' => t('<p>Equal height blocks only makes sense for blocks aligned horizontally so do not apply to sidebars. The equal height settings work well in conjunction with the Skinr block layout classes.</p>'),
  );
  foreach ($equalized_blocks as $name => $title) {
    $form['layout']['equal_heights']['equal_heights_blocks']['equalize_'. $name] = array(
      '#type' => 'checkbox',
      '#title' => $title,
      '#default_value' => $settings['equalize_'. $name],
    );
  }
  // Horizonatal login block
  if ($settings['horizontal_login_block_enable'] == 'on') {
    $form['layout']['login_block'] = array(
      '#type' => 'fieldset',
      '#title' => t('Login Block'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['layout']['login_block']['horizontal_login_block'] = array(
      '#type' => 'checkbox',
      '#title' => t('Horizontal Login Block'),
      '#default_value' => $settings['horizontal_login_block'],
      '#description' => t('Checking this setting will enable a horizontal style login block (all elements on one line). Note that if you are using OpenID this does not work well and you will need a more sophistocated approach than can be provided here.'),
    );
    $form['layout']['login_block']['horizontal_login_block_overlabel'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use Overlabel JavaScript'),
      '#default_value' => $settings['horizontal_login_block_overlabel'],
      '#description' => t('Checking this setting will place the "User name:*" and "Password:*" labels inside the user name and password text fields.'),
    );
  } // endif horizontal block settings
  // Admin settings
  $form['admin_settings']['administration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Admin settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Show user menu
  $form['admin_settings']['administration']['at_user_menu'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show the built in User Menu.'),
    '#default_value' => $settings['at_user_menu'],
    '#description' => t('This will show or hide useful links in the header. NOTE that if the <a href="!link">Admin Menu</a> module is installed most links will not show up because they are included in the Admin Menu.', array('!link' => 'http://drupal.org/project/admin_menu')),
  );
  // Show block edit links
  $form['admin_settings']['administration']['block_edit_links'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show block editing and configuration links.'),
    '#default_value' => $settings['block_edit_links'],
    '#description' => t('When hovering over a block or viewing blocks in the blocks list page privileged users will see block editing and configuration links.'),
  );
  // Hide help messages
  $form['admin_settings']['administration']['at_admin_hide_help'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide help messages.'),
    '#default_value' => $settings['at_admin_hide_help'],
    '#description' => t('When this setting is checked all help messages will be hidden.'),
  );
  // Development settings
  $form['themedev']['dev'] = array(
    '#type' => 'fieldset',
    '#title' => t('Theme development settings'),
    '#description' => t('WARNING: These settings are for the theme developer! Changing these settings may break your site. Make sure you really know what you are doing before changing these.'),
    '#collapsible' => TRUE,
    '#collapsed' => $settings['rebuild_registry'] ? FALSE : TRUE,
  );
  // Global settings
  $form['themedev']['dev']['global'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global Settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  // Rebuild registry
  $form['themedev']['dev']['global']['rebuild_registry'] = array(
    '#type' => 'checkbox',
    '#title' => t('Rebuild the theme registry on every page load.'),
    '#default_value' => $settings['rebuild_registry'],
    '#description' => t('During theme development, it can be very useful to continuously <a href="!link">rebuild the theme registry</a>. WARNING! This is a performance penalty and must be turned off on production websites.', array('!link' => 'http://drupal.org/node/173880#theme-registry')),
  );
  // Show $theme_info
  $form['themedev']['dev']['global']['show_theme_info'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show theme info.'),
    '#default_value' => $settings['show_theme_info'],
    '#description' => t('This will show the output of the global $theme_info variable using Krumo.'),
  );
  if (!module_exists('devel')) {
    $form['themedev']['dev']['global']['show_theme_info']['#description'] = t('NOTICE: The setting requires the <a href="!link">Devel module</a> to be installed. This will show the output of the global $theme_info variable using Krumo.', array('!link' => 'http://drupal.org/project/devel'));
    $form['themedev']['dev']['global']['show_theme_info']['#disabled'] = 'disabled';
  }
  // Add or remove markup
  $form['themedev']['dev']['markup'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add or Remove Markup'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  // Add spans to theme_links
  $form['themedev']['dev']['markup']['links_add_span_elements'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add SPAN tags to Primary and Secondary links anchor text.'),
    '#description' => t('Wrapping SPAN tags around the anchor text can help out when building sliding door type tabs with hover states.'),
    '#default_value' => $settings['links_add_span_elements'],
  );
  // Add or remove extra classes
  $form['themedev']['dev']['classses'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add or Remove CSS Classes'),
    '#description' => t('<p>This is a fast and easy way to add or remove CSS classes during theme development, so you only print what you require. Once you have decided which classes you need you can set new defaults in your subthemes .info file - this is useful if your theme needs to be portable, such as a commercial theme or when moving from development server to the live site. Use the <b>Export Advanced Theme Settings</b> to copy/paste your theme settings to the .info file (save them first if you have made changes).</p><p>Note that whenever you change the defaults in the .info file you need to click <em>"Reset to defaults"</em> to save them to the variables table and have them applied.</p>'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  // Body classes
  $form['themedev']['dev']['classses']['body_classes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Page Classes'),
    '#description' => t('Page classes are added to the BODY element and apply to the whole page.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['themedev']['dev']['classses']['body_classes']['cleanup_classes_section'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print section classes (.section-$section, uses the path-alias)'),
    '#default_value' => $settings['cleanup_classes_section'],
  );
  $form['themedev']['dev']['classses']['body_classes']['cleanup_classes_front'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .front and .not-front classes.'),
    '#default_value' => $settings['cleanup_classes_front'],
  );
  $form['themedev']['dev']['classses']['body_classes']['cleanup_classes_user_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .logged-in and .not-logged-in classes.'),
    '#default_value' => $settings['cleanup_classes_user_status'],
  );
  $form['themedev']['dev']['classses']['body_classes']['cleanup_classes_normal_path'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .page-[$normal_path] classes.'),
    '#default_value' => $settings['cleanup_classes_normal_path'],
  );
  $form['themedev']['dev']['classses']['body_classes']['cleanup_classes_node_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .article-type-[type] classes.'),
    '#default_value' => $settings['cleanup_classes_node_type'],
  );
  $form['themedev']['dev']['classses']['body_classes']['cleanup_classes_add_edit_delete'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print classes for article add, edit and delete pages (.article-[arg]).'),
    '#default_value' => $settings['cleanup_classes_add_edit_delete'],
  );
  if (function_exists('locale')) {
   $form['themedev']['dev']['classses']['body_classes']['cleanup_classes_language'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print classes for Locale page language such as .lang-en, .lang-sv'),
      '#default_value' => $settings['cleanup_classes_language'],
    );
  }
  // Node classes
  $form['themedev']['dev']['classses']['article_classes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Article Classes'),
    '#description' => t('Article classes apply to nodes. They print in the main wrapper DIV for all articles (nodes) in node.tpl.php.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['themedev']['dev']['classses']['article_classes']['cleanup_article_id'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print a unique ID for each article e.g. #article-1.'),
    '#default_value' => $settings['cleanup_article_id'],
  );
  $form['themedev']['dev']['classses']['article_classes']['cleanup_article_classes_sticky'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .article-sticky class for articles set to sticky.'),
    '#default_value' => $settings['cleanup_article_classes_sticky'],
  );
  $form['themedev']['dev']['classses']['article_classes']['cleanup_article_classes_promote'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .article-promoted class for articles promoted to front.'),
    '#default_value' => $settings['cleanup_article_classes_promote'],
  );
  $form['themedev']['dev']['classses']['article_classes']['cleanup_article_classes_teaser'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .article-teaser class on article teasers.'),
    '#default_value' => $settings['cleanup_article_classes_teaser'],
  );
  $form['themedev']['dev']['classses']['article_classes']['cleanup_article_classes_preview'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .article-preview class for article previews.'),
    '#default_value' => $settings['cleanup_article_classes_preview'],
  );
  $form['themedev']['dev']['classses']['article_classes']['cleanup_article_classes_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .[content-type]-article classes.'),
    '#default_value' => $settings['cleanup_article_classes_type'],
  );
  if (function_exists('i18n_init')) {
    $form['themedev']['dev']['classses']['article_classes']['cleanup_article_classes_language'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print .article-lang-[language] classes (requires i18n module)'),
      '#default_value' => $settings['cleanup_article_classes_language'],
    );
  }
  // Comment classes
  $form['themedev']['dev']['classses']['comment_classes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Comment Classes'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['themedev']['dev']['classses']['comment_classes']['comments'] = array(
    '#type' => 'fieldset',
    '#title' => t('Comments'),
    '#description' => t('Comment classes apply to all comments. They print in comment.tpl.php on the wrapper DIV for each comment.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['themedev']['dev']['classses']['comment_classes']['comments']['cleanup_comment_anonymous'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .comment-by-anonymous for anonymous comments.'),
    '#default_value' => $settings['cleanup_comment_anonymous'],
  );
  $form['themedev']['dev']['classses']['comment_classes']['comments']['cleanup_comment_article_author'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .comment-by-article-author for author comments.'),
    '#default_value' => $settings['cleanup_comment_article_author'],
  );
  $form['themedev']['dev']['classses']['comment_classes']['comments']['cleanup_comment_by_viewer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .comment-by-viewer for viewer comments.'),
    '#default_value' => $settings['cleanup_comment_by_viewer'],
  );
  $form['themedev']['dev']['classses']['comment_classes']['comments']['cleanup_comment_new'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .comment-new for new comments.'),
    '#default_value' => $settings['cleanup_comment_new'],
  );
  $form['themedev']['dev']['classses']['comment_classes']['comments']['cleanup_comment_zebra'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .odd and .even classes for comments.'),
    '#default_value' => $settings['cleanup_comment_zebra'],
  );
  $form['themedev']['dev']['classses']['comment_classes']['comment-wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Comment Wrapper'),
   '#description' => t('This class prints in comment-wrapper.tpl.php. The DIV wrapper encloses both the comments and the comment form (if on the same page).'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['themedev']['dev']['classses']['comment_classes']['comment-wrapper']['cleanup_comment_wrapper_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print a content type class on the comments wrapper i.e. .[content-type]-comments.'),
    '#default_value' => $settings['cleanup_comment_wrapper_type'],
  );
  // Block classes
  $form['themedev']['dev']['classses']['block_classes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Block Classes'),
    '#description' => t('Comment classes apply to blocks. They print in the main wrapper DIV for all blocks in block.tpl.php.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['themedev']['dev']['classses']['block_classes']['cleanup_block_block_module_delta'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print a unique ID for each block (#block-module-delta).'),
    '#default_value' => $settings['cleanup_block_block_module_delta'],
  );
  $form['themedev']['dev']['classses']['block_classes']['cleanup_block_classes_module'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print a .block-[module] class.'),
    '#default_value' => $settings['cleanup_block_classes_module'],
  );
  $form['themedev']['dev']['classses']['block_classes']['cleanup_block_classes_zebra'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .odd and .even classes for blocks.'),
    '#default_value' => $settings['cleanup_block_classes_zebra'],
  );
  $form['themedev']['dev']['classses']['block_classes']['cleanup_block_classes_region'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .block-[region] classes.'),
    '#default_value' => $settings['cleanup_block_classes_region'],
  );
  $form['themedev']['dev']['classses']['block_classes']['cleanup_block_classes_count'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .block-[count] classes.'),
    '#default_value' => $settings['cleanup_block_classes_count'],
  );
  // Menu classes
  $form['themedev']['dev']['classses']['menu_classes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Menu, Primary &amp; Secondary Links Classes'),
    '#description' => t('Standard menus get their classes via the <code>theme_menu_tree</code> function override while the Primary and Secondary links use the <code>theme_links</code> function override (both are found in template.theme-overrides.inc). Note that the standard menu class options will not appear and will not be applied if the <a href="!link">DHTML Menu</a> module is installed.', array('!link' => 'http://drupal.org/project/dhtml_menu')),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  if (!function_exists('dhtml_menu_init')) {
    $form['themedev']['dev']['classses']['menu_classes']['menu_menu_classes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Menu Classes'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
    $form['themedev']['dev']['classses']['menu_classes']['menu_menu_classes']['cleanup_menu_menu_class'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print the ul.menu class.'),
      '#default_value' => $settings['cleanup_menu_menu_class'],
    );
    $form['themedev']['dev']['classses']['menu_classes']['menu_menu_classes']['cleanup_menu_leaf_class'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print the .leaf class on menu list items.'),
      '#default_value' => $settings['cleanup_menu_leaf_class'],
    );
    $form['themedev']['dev']['classses']['menu_classes']['menu_menu_classes']['cleanup_menu_first_last_classes'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print the .first and .last classes on menu list items. If there is only one item in the menu the class .single-item will replace the .last class (requires the .leaf class).'),
      '#default_value' => $settings['cleanup_menu_first_last_classes'],
    );
    $form['themedev']['dev']['classses']['menu_classes']['menu_menu_classes']['cleanup_menu_active_classes'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print the .active classes on menu list items (active classes always print on the anchor).'),
      '#default_value' => $settings['cleanup_menu_active_classes'],
    );
    $form['themedev']['dev']['classses']['menu_classes']['menu_menu_classes']['cleanup_menu_title_class'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print classes based on the menu title, i.e. .menu-[title].'),
      '#default_value' => $settings['cleanup_menu_title_class'],
    );
  }
  else {
    $form['themedev']['dev']['classses']['menu_classes']['#description'] = t('NOTICE: You currently have the DHTML Menu module installed. The custom menu class options have been disabled because this module will not work correctly with them enabled - you can still set classes for the Primary and Secondary links (below).');
    $form['themedev']['dev']['classses']['menu_classes']['menu_menu_classes']['#disabled'] = 'disabled';
  }
  $form['themedev']['dev']['classses']['menu_classes']['menu_links_classes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Primary and Secondary Links Classes'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    );
  $form['themedev']['dev']['classses']['menu_classes']['menu_links_classes']['cleanup_links_type_class'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print the type class on Primary and Secondary links.'),
    '#default_value' => $settings['cleanup_links_type_class'],
  );
  $form['themedev']['dev']['classses']['menu_classes']['menu_links_classes']['cleanup_links_active_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print the active classes on Primary and Secondary links.'),
    '#default_value' => $settings['cleanup_links_active_classes'],
  );
  $form['themedev']['dev']['classses']['menu_classes']['menu_links_classes']['cleanup_links_first_last_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .first and .last classes.'),
     '#default_value' => $settings['cleanup_links_first_last_classes'],
  );
  // Item list classes
  $form['themedev']['dev']['classses']['itemlist_classes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Item list Classes'),
    '#description' => t('Item list classes are applied using the <code>theme_item_list</code> function override in template.theme-overrides.inc'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['themedev']['dev']['classses']['itemlist_classes']['cleanup_item_list_zebra'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .odd and .even classes for list items.'),
    '#default_value' => $settings['cleanup_item_list_zebra'],
  );
  $form['themedev']['dev']['classses']['itemlist_classes']['cleanup_item_list_first_last'] = array(
    '#type' => 'checkbox',
    '#title' => t('Print .first and .last classes for the first and last items in the list.'),
    '#default_value' => $settings['cleanup_item_list_first_last'],
  );
  // Views classes
  if (module_exists('views')) {
    $form['themedev']['dev']['classses']['views_classes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Views Classes'),
      '#description' => t('NOTE: If you are using custom Views templates you must use the template overrides that come with Adaptivetheme to preserve this functality.'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['themedev']['dev']['classses']['views_classes']['display'] = array(
      '#type' => 'fieldset',
      '#title' => t('Display Classes'),
      '#description' => t('Control the classes for Views displays (views-view.tpl.php).'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['themedev']['dev']['classses']['views_classes']['display']['cleanup_views_css_name'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print the CSS Name class.'),
      '#default_value' => $settings['cleanup_views_css_name'],
    );
    $form['themedev']['dev']['classses']['views_classes']['display']['cleanup_views_view_name'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print the View Name class.'),
      '#default_value' => $settings['cleanup_views_view_name'],
    );
    $form['themedev']['dev']['classses']['views_classes']['display']['cleanup_views_display_id'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print the Display ID class.'),
      '#default_value' => $settings['cleanup_views_display_id'],
    );
    $form['themedev']['dev']['classses']['views_classes']['display']['cleanup_views_dom_id'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print the DOM ID class.'),
      '#default_value' => $settings['cleanup_views_dom_id'],
    );
    $form['themedev']['dev']['classses']['views_classes']['style'] = array(
      '#type' => 'fieldset',
      '#title' => t('Views Style Classes'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['themedev']['dev']['classses']['views_classes']['style']['cleanup_views_unformatted'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print extra classes for unformatted views (views-view-unformatted.tpl.php).'),
      '#default_value' => $settings['cleanup_views_unformatted'],
    );
    $form['themedev']['dev']['classses']['views_classes']['style']['cleanup_views_item_list'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print extra classes for item list views (views-view-list.tpl.php).'),
      '#default_value' => $settings['cleanup_views_item_list'],
    );
  }
  // Field classes (CCK).
  if (module_exists('content')) {
    $form['themedev']['dev']['classses']['field_classes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Field Classes'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
   $form['themedev']['dev']['classses']['field_classes']['cleanup_fields_type'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print field type classes.'),
      '#default_value' => $settings['cleanup_fields_type'],
    );
   $form['themedev']['dev']['classses']['field_classes']['cleanup_fields_name'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print field name classes.'),
      '#default_value' => $settings['cleanup_fields_name'],
    );
    $form['themedev']['dev']['classses']['field_classes']['cleanup_fields_zebra'] = array(
      '#type' => 'checkbox',
      '#title' => t('Print odd/even zebra classes on CCK fields.'),
      '#default_value' => $settings['cleanup_fields_zebra'],
    );
  }
  // Title classes for headings
  $form['themedev']['dev']['classses']['heading_classes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Heading Classes'),
    '#description' => t('Heading classes apply to article, block and comment titles (h2, h3 etc).'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['themedev']['dev']['classses']['heading_classes']['cleanup_headings_title_class'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add the .title class to all headings.'),
    '#default_value' => $settings['cleanup_headings_title_class'],
  );
  $form['themedev']['dev']['classses']['heading_classes']['cleanup_headings_namespaced_class'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add a pseudo name spaced title class to headings, i.e. .article-title, .block-title, .comment-title.'),
    '#default_value' => $settings['cleanup_headings_namespaced_class'],
  );
  // Theme Settings Export
  $form['theme_settings_export']['export'] = array(
    '#type' => 'fieldset',
    '#title' => t('Export Advanced Theme Settings'),
    '#description' => t('<p>Copy/paste these settings to a text file for backup or paste to your themes .info file (over-write the defaults) - useful if you are moving your theme to a new site and want to retain custom settings.</p><p>NOTE: Content type specific settings are NOT included here, these cannot be set via the info file.</p><p>WARNING! If you are using a WYSIWYG editor it must be disabled for this text area, otherwise all special characters are likely to be converted to HTML entities. If your editor has a \'view source\' feature try that first.</p>'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['theme_settings_export']['export']['exported_settings'] = array(
    '#type' => 'textarea',
    '#default_value' => $exports,
    '#resizable' => FALSE,
    '#cols' => 60,
    '#rows' => 25,
  );
  return $form;
}