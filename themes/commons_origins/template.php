<?php

/**
 * Row & block theme functions
 * Adds divs to elements in page.tpl.php
 */
function commons_origins_grid_row($element, $name, $class='', $width='', $extra='') {
  $output = '';
  $extra = ($extra) ? ' ' . $extra : '';
  if ($element) {
    if ($class == 'full-width') {
      $output .= '<div id="' . $name . '-wrapper" class="' . $name . '-wrapper full-width">' . "\n";
      $output .= '<div id="' . $name . '" class="' . $name . ' row ' . $width . $extra . '">' . "\n";
    }
    else {
      $output .= '<div id="' . $name . '" class="' . $name . ' row ' . $class . ' ' . $width . $extra . '">' . "\n";
    }
    $output .= '<div id="' . $name . '-inner" class="' . $name . '-inner inner clearfix">' . "\n";
    if ($name == 'sidebar-last') {
      $output .= '<span class="sidebar-last-cap"></span>'. "\n";
    }
    $output .= $element;
    $output .= '</div><!-- /' . $name . '-inner -->' . "\n";
    $output .= '</div><!-- /' . $name . ' -->' . "\n";
    $output .= ($class == 'full-width') ? '</div><!-- /' . $name . '-wrapper -->' . "\n" : '';
  }
  return $output;
}

function commons_origins_preprocess_page(&$variables) {
  $variables['pre_header_top'] = theme('grid_row', $variables['header_top'], 'header-top', 'full-width', $variables['grid_width']);
  $variables['pre_secondary_links'] = theme('grid_block', theme('links', $variables['secondary_links']), 'secondary-menu');
  $variables['pre_search_box'] = theme('grid_block', $variables['search_box'], 'search-box');
  $variables['pre_primary_links_tree'] = theme('grid_block', $variables['primary_links_tree'], 'primary-menu');
  $variables['pre_breadcrumb'] = theme('grid_block', $variables['breadcrumb'], 'breadcrumbs');
  $variables['pre_preface_top'] = theme('grid_row', $variables['preface_top'], 'preface-top', 'full-width', $variables['grid_width']);
  $variables['pre_sidebar_first'] = theme('grid_row', $variables['sidebar_first'], 'sidebar-first', 'nested', $variables['sidebar_first_width']);
  $variables['pre_preface_bottom'] = theme('grid_row', $variables['preface_bottom'], 'preface-bottom', 'nested');
  $variables['pre_help'] = theme('grid_block', $variables['help'], 'content-help');
  $variables['pre_messages'] = theme('grid_block', $variables['messages'], 'content-messages');
  $variables['pre_tabs'] = theme('grid_block', $variables['tabs'], 'content-tabs');
  $variables['pre_content_bottom'] = theme('grid_row', $variables['content_bottom'], 'content-bottom', 'nested');
  $variables['pre_sidebar_last'] = theme('grid_row', $variables['sidebar_last'], 'sidebar-last', 'nested', $variables['sidebar_last_width']);
  $variables['pre_postscript_top'] = theme('grid_row', $variables['postscript_top'], 'postscript-top', 'nested');
  $variables['pre_postscript_bottom'] = theme('grid_row', $variables['postscript_bottom'], 'postscript-bottom', 'full-width', $variables['grid_width']);
  $variables['pre_footer'] = theme('grid_row', $variables['footer'] . $variables['footer_message'], 'footer', 'full-width', $variables['grid_width']);
  
  //show group description if group node present
  if (isset($variables['node'])) {
    $node = $variables['node'];
    if (og_is_group_type($node->type)) {
      $variables['group_header_image'] = content_format('field_group_image', $node->field_group_image[0], 'user_picture_meta_default');
      
      if (!empty($node->body)) {
        $variables['group_header_text'] = check_markup($node->body, $node->format);  
      }
      else {
        $variables['group_header_text'] = check_plain($node->og_description);
      }
    }
  }  
}

function commons_origins_preprocess_node(&$variables) {
  $query = 'destination=' . $_GET['q'];
  $variables['answers_login'] =  t('<a href="@login">Login</a> or <a href="@register">register</a> to vote', array('@login' => url('user/login', array('query' => $query)), '@register' => url('user/register', array('query' => $query))));
}
