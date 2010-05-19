<?php // $Id: template.preprocess-node.inc,v 1.1.2.22 2010/03/19 05:02:24 jmburnz Exp $
// adaptivethemes.com

/**
 * @file template.preprocess-node.inc
 */

/**
 * Override or insert variables into the node templates.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 * @param $hook
 *   The name of the theme function being called.
 */

global $theme, $user;

if (theme_get_setting('cleanup_article_id')) {
  // Set article id.
  $vars['article_id'] = 'article-'. $vars['node']->nid;
}

// Special classes for nodes. Emulates Drupal 7 node classes for forward compatibility.
$classes = array();

$classes[] = 'article';

if (theme_get_setting('cleanup_article_classes_promote')) {
  if ($vars['promote']) {
    $classes[] = 'article-promoted';
  }
}

if (theme_get_setting('cleanup_article_classes_sticky')) {
  if ($vars['sticky']) {
    $classes[] = 'article-sticky';
  }
}

if (theme_get_setting('cleanup_article_classes_teaser')) {
  if ($vars['teaser']) {
    $classes[] = 'article-teaser';
  }
}

if (theme_get_setting('cleanup_article_classes_preview')) {
  if (isset($vars['preview'])) {
    $classes[] = 'article-preview';
  }
}

if (!$vars['status']) {
  $classes[] = 'article-unpublished';
}

// Add support for Skinr module classes http://drupal.org/project/skinr
if (function_exists('node_skinr_data') && !empty($vars['skinr'])) {
  $classes[] = $vars['skinr'];
}

// Class for content types e.g. "article-page", "article-my-content-type", etc.
if (theme_get_setting('cleanup_article_classes_type')) {
  $classes[] = $vars['node']->type .'-article';
}

// Language specific article class.
if (theme_get_setting('cleanup_article_classes_language')) {
  if (function_exists('i18n_init')) {
    if ($vars['node']->language) {
      global $language;
      $classes[] = 'article-lang-'. $vars['node']->language;
    }
  }
}

if (theme_get_setting('cleanup_article_classes_zebra')) {
  $classes[] = $vars['zebra'];
}

// $classes is the variable that holds the node classes and is printed in node tpl files.
$vars['classes'] = implode(' ', $classes); // Concatenate with spaces.

// Set title classes
$title_classes = array();

if (theme_get_setting('cleanup_headings_title_class')) {
  $title_classes[] = 'title';
}

if (theme_get_setting('cleanup_headings_namespaced_class')) {
  $title_classes[] = 'article-title';
}

$vars['title_classes'] = implode(' ', $title_classes);

// Add article_aside region content.
$vars['article_aside'] = theme('blocks', 'article_aside');

// Support node tpl suggestions per node nid.
$vars['template_files'][] = 'node-'.$vars['node']->nid; 

// Set message if node is unpublished.
if (!$vars['node']->status) {
  if ($vars['page']) {
    drupal_set_message(t('%title is currently unpublished', array('%title' => $vars['node']->title)), 'warning');
  }
  else {
    $vars['unpublished'] = '<span class="unpublished">'. t('Unpublished') .'</span>';
  }
}

// Node Theme Settings.
// Date & author theme settings.
if (theme_get_setting('submitted_by_settings_enabled') == 1 && !function_exists('submitted_by_node_submitted')) {
  $date = t('Posted ') .'<em class="time">'. format_date($vars['node']->created, 'medium') .'</em>';
  $author = '<em class="author">'. theme('username', $vars['node']) .'</em>';
  $author_only_separator = t('Posted by ');
  $author_date_separator = t(' by ');
  $submitted_by_content_type = (theme_get_setting('submitted_by_enable_content_type') == 1) ? $vars['node']->type : 'default';
  $date_setting = (theme_get_setting('submitted_by_date_'. $submitted_by_content_type) == 1);
  $author_setting = (theme_get_setting('submitted_by_author_'. $submitted_by_content_type) == 1);
  $author_separator = ($date_setting) ? $author_date_separator : $author_only_separator;
  $date_author = ($date_setting) ? $date : '';
  $date_author .= ($author_setting) ? $author_separator . $author : '';
  $vars['submitted'] = $date_author;
}

// Taxonomy theme settings.
if (theme_get_setting('taxonomy_settings_enabled') == 1 && function_exists('taxonomy_perm')) {
  $taxonomy_content_type = (theme_get_setting('taxonomy_enable_content_type') == 1) ? $vars['node']->type : 'default';
  $taxonomy_display = theme_get_setting('taxonomy_display_'. $taxonomy_content_type);
  $taxonomy_format = theme_get_setting('taxonomy_format_'. $taxonomy_content_type);
  $delimiter = filter_xss(theme_get_setting('taxonomy_delimiter_'. $taxonomy_content_type));
  if ($taxonomy_display == 'all' || ($taxonomy_display == 'only' && $vars['page'])) {
    $output = '';
    switch ($taxonomy_format) {
      case "list":
        $terms = taxonomy_node_get_terms($vars['node']);
        $links = array();
        $term_index = 0;
        foreach ($terms as $term) {
          $term_count = count($terms);
          $term_index++;
          if (theme_get_setting('taxonomy_vocab_display_'. $taxonomy_content_type .'_'. $term->vid) == 1) {
            $links[] = '<li>'. l($term->name, taxonomy_term_path($term), array('attributes' => array('rel' => 'tag', 'title' => strip_tags($term->description)))) . ( $term_index == $term_count ? '' : $delimiter ) .'</li>';
          }
        }
        $output .= implode("", $links);
        if ($output != '') {
          $output = '<ul class="taxonomy">'. $output .'</ul>';
        }
        break;
      case "vocab":
        $heading_level = $vars['page'] ? 'h2' : 'h3';
        $vocabularies = taxonomy_get_vocabularies($vars['node']->type);
        $vocab_index = 0;
        foreach ($vocabularies as $vocabulary) {
          $vocab_index++;
          $terms = '';
          if (theme_get_setting('taxonomy_vocab_display_'. $taxonomy_content_type .'_'. $vocabulary->vid) == 1) {
            $terms = taxonomy_node_get_terms_by_vocabulary($vars['node'], $vocabulary->vid);
          }
          if ($terms) {
            if (module_exists('i18n')){
              $terms = i18ntaxonomy_localize_terms ($terms);
            }
            $links = array();
            $output .= '<li class="vocab vocab-'. safe_string($vocabulary->name) .'"><'. $heading_level .' class="vocab-name">'. $vocabulary->name .'</'. $heading_level .'><ul class="vocab-list">' ;
            $term_count = count($terms);
            $term_index = 0;
            foreach ($terms as $term) {
              $term_index++;
              $links[] = '<li>'. l($term->name, taxonomy_term_path($term), array('attributes' => array('rel' => 'tag', 'title' => strip_tags($term->description)))) .  ( $term_index == $term_count ? '' : $delimiter )  .'</li>';
            }
          $output .= implode("", $links);
          $output .= '</ul></li>';
          
          }
        }
        if ($output != '') {
          $output = '<ul class="taxonomy">'. $output .'</ul>';
        }
        break;
    }
    $vars['terms'] = $output;
  }
  else {
    $vars['terms'] = '';
  }
}

// Display links.
if (theme_get_setting('display_links_settings_enabled') == 1) {
  $links_content_type = (theme_get_setting('display_links_enable_content_type') == 1) ? $vars['node']->type : 'default';
  $links_display = theme_get_setting('display_links_'. $links_content_type);
  if ($links_display == 'all' || ($links_display == 'only' && $vars['page'])) {
    $vars['links'] = $vars['links'];
  }
  else {
    $vars['links'] = '';
  }
}

/* Variables for node-product.tpl.php, save this for another day...
if (uc_product_is_product($vars['node']->type)) {
  $vars['uc_image']         = $vars['node']->content['image']['#value'];
  $vars['uc_body']          = $vars['node']->content['body']['#value'];
  $vars['uc_display_price'] = $vars['node']->content['display_price']['#value'];
  $vars['uc_add_to_cart']   = $vars['node']->content['add_to_cart']['#value'];
  $vars['uc_weight']        = $vars['node']->content['weight']['#value'];
  $vars['uc_dimensions']    = $vars['node']->content['dimensions']['#value'];
  $vars['uc_model']         = $vars['node']->content['model']['#value'];
  $vars['uc_list_price']    = $vars['node']->content['list_price']['#value'];
  $vars['uc_cost']          = $vars['node']->content['cost']['#value'];
  $vars['uc_sell_price']    = $vars['node']->content['sell_price']['#value'];
}
*/