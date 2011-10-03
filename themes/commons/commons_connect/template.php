<?php
// $Id: template.php 8021 2010-10-19 13:01:34Z sheena $

/**
 * Breadcrumb themeing
 */
function commons_connect_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    $html = '<div class="crumbtitle">' . t('You are here:') . '</div>';
	  $html .= '<div class="breadcrumb">'. implode(' &raquo; ', $breadcrumb) .'</div>';
    return $html;
  }
}

/**
 * Page preprocessing
 */
function acquia_commons_preprocess_page(&$vars) {
  // Format the footer message
  // We do this here instead of in page.tpl.php because 
  // we need a formatted message to pass along to the
  // same theme function as the $footer in order to have
  // them nested together
  if (isset($vars['footer_message']) && strlen($vars['footer_message'])) {
    $markup = '';
    $markup .= '<div id="footer-message" class="footer-message">';
    $markup .= '<div id="footer-message-inner" class="footer-message-inner inner">';
    $markup .= $vars['footer_message'];
    $markup .= '</div><!-- /footer-message-inner -->';
    $markup .= '</div><!-- /footer-message -->';
    $vars['footer_message'] = $markup;
  }
}

/**
 * Comment preprocessing
 */
function acquia_commons_preprocess_comment(&$vars) {
  global $user;
  static $comment_odd = TRUE;                                                                             // Comment is odd or even

  // Build array of handy comment classes
  $comment_classes = array();
  $comment_classes[] = $comment_odd ? 'odd' : 'even';
  $comment_odd = !$comment_odd;
  $comment_classes[] = ($vars['comment']->status == COMMENT_NOT_PUBLISHED) ? 'comment-unpublished' : '';  // Comment is unpublished
  $comment_classes[] = ($vars['comment']->new) ? 'comment-new' : '';                                      // Comment is new
  $comment_classes[] = ($vars['comment']->uid == 0) ? 'comment-by-anon' : '';                             // Comment is by anonymous user
  $comment_classes[] = ($user->uid && $vars['comment']->uid == $user->uid) ? 'comment-mine' : '';         // Comment is by current user
  $node = node_load($vars['comment']->nid);                                                               // Comment is by node author
  $vars['author_comment'] = ($vars['comment']->uid == $node->uid) ? TRUE : FALSE;
  $comment_classes[] = ($vars['author_comment']) ? 'comment-by-author' : '';
  $comment_classes = array_filter($comment_classes);                                                      // Remove empty elements
  $vars['comment_classes'] = implode(' ', $comment_classes);                                              // Create class list separated by spaces

  // Date & author
  $ago =  t('!interval ago', array('!interval' => format_interval(time() - $vars['comment']->timestamp)));
  $submitted_by = '<span class="comment-name">' . theme('username', $vars['comment']) . '</span>';
  $submitted_by .= '<span class="comment-date">' . $ago . '</span>';     // Format date as small, medium, or large
  $vars['submitted'] = $submitted_by;
  
  // Picture
  if (theme_get_setting('toggle_comment_user_picture')) {
    if (!$vars['comment']->picture && (variable_get('user_picture_default', '') != '')) {
      $vars['comment']->picture = variable_get('user_picture_default', '');
    }
    if ($vars['comment']->picture) { 
      $picture = theme_imagecache('user_picture_meta', $vars['comment']->picture, $vars['comment']->name, $vars['comment']->name);
      if (user_access('access user profiles')) {
        $vars['comment']->picture = l($picture, "user/{$vars['comment']->uid}", array('html' => TRUE));
      }
      else {
        $vars['comment']->picture = $picture; 
      }
    }
  }
  else {
    unset($vars['comment']); 
  }
}

/**
 * Profile preprocessing
 */
function commons_connect_preprocess_user_profile_item(&$vars) {
  // Separate userpoints value from the edit links
  if ($vars['title'] == 'Points') { 
    $userpoints = explode(' - ', $vars['value']);
    $vars['value'] = '<span class="points">' . $userpoints[0] . '</span><span class="edit-links">' . $userpoints[1] . '</span>';
    unset($vars['title']);
  }
}

/**
 * Implementation of theme_shoutbox_post()
 */
function commons_connect_shoutbox_post($shout, $links = array(), $alter_row_color=TRUE) {
  global $user;
  
  // Gather moderation links
  if ($links) {
    foreach ($links as $link) {
      $linkattributes = $link['linkattributes'];
      $link_html = '<img src="'. $link['img'] .'"  width="'. $link['img_width'] .'" height="'. $link['img_height'] .'" alt="'. $link['title'] .'" class="shoutbox-imglink"/>';
      $link_url = 'shout/'. $shout->shout_id .'/'. $link['action'];
      $img_links = l($link_html, $link_url, array('html' => TRUE, 'query' => array('destination' => drupal_get_path_alias($_GET['q'])))) . $img_links;
    }
  }
  
  // Generate user name with link
  $user_name = shoutbox_get_user_link($shout);

  // Generate title attribute
  $title = t('Posted !date at !time by !name', array('!date' => format_date($shout->created, 'custom', 'm/d/y'), '!time' => format_date($shout->created, 'custom', 'h:ia'), '!name' => $shout->nick));

  // Add to the shout classes
  $shout_classes = array();
  $shout_classes[] = 'shoutbox-msg';

  // Check for moderation
  if ($shout->moderate == 1) {
    $shout_classes[] = 'shoutbox-unpublished';
    $approval_message = '&nbsp;(' . t('This shout is waiting for approval by a moderator.') . ')';
  }
  
  // Check for specific user class
  $user_classes = array();
  $user_classes[] = 'shoutbox-user-name';
  if ($shout->uid == $user->uid) {
    $user_classes[] = 'shoutbox-current-user-name';
  }
  else if ($shout->uid == 0) {
    $user_classes[] = 'shoutbox-anonymous-user';  
  }
  
  // Load user image and format
  $author_picture ='';
  $shout_author =  user_load($shout->uid);
  if (!$shout_author->picture && variable_get('user_picture_default', '')) {
    $shout_author->picture = variable_get('user_picture_default', '');
  }
  if ($shout_author->picture) {
    $author_picture = theme_imagecache('user_picture_meta', $shout_author->picture, $shout_author->name, $shout_author->name);
  }
  
  // Time format
  $format = variable_get('shoutbox_time_format', 'ago');
  switch ($format) {
    case 'ago';
      $submitted =  t('!interval ago', array('!interval' => format_interval(time() - $shout->created)));
      break;
    case 'small':
    case 'medium':
    case 'large':
      $submitted = format_date($shout->created, $format);
      break;
  }
   
  // Build the post
  $post = '';
  $post .= '<div class="' . implode(' ', $shout_classes) . '" title="' . $title . '">';
  $post .= '<div class="shoutbox-admin-links">' . $img_links . '</div>';
  $post .= '<div class="shoutbox-post-info">' . $author_picture;
  $post .= '<span class="shoutbox-user-name ' . implode(' ', $user_classes) . '">'. $user_name . '</span>';
  $post .= '<span class="shoutbox-msg-time">' . $submitted . '</span>';
  $post .= '</div>';
  $post .= '<div class="shout-message">' . $shout->shout . $approval_message . '</div>';
  $post .= '</div>' . "\n";

  return $post;
}

function commons_connect_item_list($items = array(), $title = NULL, $type = 'ul', $attributes = NULL) {
  $output = '<div class="item-list">';
  if (isset($title)) {
    $output .= '<h3>'. $title .'</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type". drupal_attributes($attributes) .'>';
    $num_items = count($items);
    $c = $num_items;
    foreach ($items as $i => $item) {
    $c--;
      $attributes = array();
      $children = array();
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
         $data = $item;
      }
      
      if (!is_numeric($i)) {
        if (count($children) > 0) {
          $data .= theme_item_list($children, NULL, $type, $attributes); // Render nested list
        }
        if ($c == $num_items - 1) {
          $attributes['class'] = empty($attributes['class']) ? 'first' : ($attributes['class'] .' first');
        }
        if ($c == 0) {
          $attributes['class'] = empty($attributes['class']) ? 'last' : ($attributes['class'] .' last');
        }
        
        $attributes['class'] .= ' ' . ($c % 2 ? 'even' : 'odd');
        $output .= '<li'. drupal_attributes($attributes) .'>'. $data ."</li>\n";
      } 
      else {
        if (count($children) > 0) {
          $data .= theme_item_list($children, NULL, $type, $attributes); // Render nested list
        }
        if ($i == 0) {
          $attributes['class'] = empty($attributes['class']) ? 'first' : ($attributes['class'] .' first');
        }
        if ($i == $num_items - 1) {
          $attributes['class'] = empty($attributes['class']) ? 'last' : ($attributes['class'] .' last');
        }
        
        $attributes['class'] .= ' ' . ($i % 2 ? 'even' : 'odd');
        $output .= '<li'. drupal_attributes($attributes) .'>'. $data ."</li>\n";
      }
    }
    
    $output .= "<$type>";
  }
  $output .= '</div>';
  return $output;
}

function commons_connect_preprocess_block($variables) {
  $variables['template_files'][] = 'block-'.$variables['block']->region.'-'.$variables['block']->module;
  $variables['template_files'][] = 'block-'.$variables['block']->region.'-'.$variables['block']->module.'-'.$variables['block']->delta;
}

function commons_connect_search_theme_form($form) {
	$form['search_theme_form']['#value']= t('Search...');
	$form['submit']['#type'] = 'image_button';
	$form['submit']['#src'] = drupal_get_path('theme', 'commons_connect') . '/images/search_icon.gif';
	$form['submit']['#attributes']['class'] = 'btn';
	return '<div id="search" class="container-inline">' . drupal_render($form) . '</div>';
}

function commons_connect_commons_core_info_block() {
  $content = '';
  
  $content .= '<div id="acquia-footer-message">';

  $content .= '<a href="http://acquia.com/drupalcommons" title="' . t('Commons social business software') . '">';
  $content .= theme('image', 'profiles/drupal_commons/images/commons_droplet.png', t('Commons social business software'), t('Commons social business software'));
  $content .= '</a>';
  $content .= '<span>';
  $content .= t('A !dc Community, powered by', array('!dc' => l(t('Commons'), 'http://acquia.com/drupalcommons', array('attributes' => array('title' => t('A Commons social business software')))))) . '&nbsp;';
  $content .= l(t('Acquia'), 'http://acquia.com', array('attributes' => array('title' => t('Acquia'))));
  $content .= '</span>';
  $content .= '</div>';
  
  $content .= '<div id="fusion-footer-message">';
  $content .= t('Theme by') . '&nbsp;';
  $content .= '<a href="http://www.brightlemon.com" title="' . t('Drupal Themes by BrightLemon') . '">' . t('BrightLemon') . '</a>';
  $content .= ', ' . t('powered by') . '&nbsp;';
  $content .= '<a href="http://fusiondrupalthemes.com" title="' . t('Premium Drupal themes powered by Fusion') . '">' . t('Fusion') . '</a>.';
  $content .= '</div>';

  return $content;
}

//hide links and change page title
function commons_connect_taxonomy_term_page($tids, $result) {
  $str_tids = arg(2);
  $terms = taxonomy_terms_parse_string($str_tids);
  $title_result = db_query(db_rewrite_sql('SELECT t.tid, t.name FROM {term_data} t WHERE t.tid IN ('. db_placeholders($terms['tids']) .')', 't', 'tid'), $terms['tids']);
  $title_tids = array(); // we rebuild the $tids-array so it only contains terms the user has access to.
  $names = array();
  while ($term = db_fetch_object($title_result)) {
    $title_tids[] = $term->tid;
    $names[] = $term->name;
  }
  $last_name = array_pop($names);
  if (count($names) == 0) {
    $title = t("Pages containing '@tag'", array('@tag' => $last_name));    
  } elseif ($terms['operator'] == "or") {
      $title = t("Pages containing '@tags or @last_tag'", array('@tags' => implode(", ", $names), '@last_tag' => $last_name));
  } else {
      $title = t("Pages containing '@tags and @last_tag'", array('@tags' => implode(", ", $names), '@last_tag' => $last_name));
  }
  drupal_set_title($title);

  drupal_add_css(drupal_get_path('module', 'taxonomy') .'/taxonomy.css');

  $output = '';

  // Only display the description if we have a single term, to avoid clutter and confusion.
  if (count($tids) == 1) {
    $term = taxonomy_get_term($tids[0]);
    $description = $term->description;

    // Check that a description is set.
    if (!empty($description)) {
      $output .= '<div class="taxonomy-term-description">';
      $output .= filter_xss_admin($description);
      $output .= '</div>';
    }
  }

  $output .= commons_connect_taxonomy_render_nodes($result);

  return $output;
}

function commons_connect_taxonomy_render_nodes($result) {
  $output = '';
  $has_rows = FALSE;
  while ($node = db_fetch_object($result)) {
    $output .= node_view(node_load($node->nid), TRUE, FALSE, FALSE);
    $has_rows = TRUE;
  }
  if ($has_rows) {
    $output .= theme('pager', NULL, variable_get('default_nodes_main', 10), 0);
  }
  else {
    $output .= '<p>'. t('There are currently no posts in this category.') .'</p>';
  }
  return $output;
}

// call scripts
drupal_add_js(path_to_theme() . '/scripts/clear_default_searchbox_text.js', 'theme'); // call on every page since search box is displayed everywhere
