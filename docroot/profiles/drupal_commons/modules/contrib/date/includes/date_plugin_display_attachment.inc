<?php
// $Id: date_plugin_display_attachment.inc,v 1.1.2.3 2010/03/05 11:55:53 karens Exp $
/**
 * The plugin that handles date navigation attachments.
 * 
 * Creates a special attachment for this purpose only. 
 */
class date_plugin_display_attachment extends views_plugin_display_attachment {
  
  // Require the date_nav style. That style has a date_nav type
  // so it won't show up as a style option on any other display.
  function get_style_type() { return 'date_nav'; }
  
  // No options to set style, force it to the right value.
  function defaultable_sections($section = NULL) {
    if (in_array($section, array('row_options', 'row_plugin', 'items_per_page'))) {
      return FALSE;
    }
    return parent::defaultable_sections($section);
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['style_plugin']['default'] = 'date_nav';
    $options['items_per_page']['default'] = 0;
    $options['row_plugin']['default'] = '';
    //$options['defaults']['default']['style_plugin'] = FALSE;
    $options['defaults']['default']['style_options'] = FALSE;
    $options['defaults']['default']['items_per_page'] = FALSE;
    $options['defaults']['default']['row_plugin'] = FALSE;
    $options['defaults']['default']['row_options'] = FALSE;

    return $options;
  } 
}

