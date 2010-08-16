<?php
// $Id: template.php 7713 2010-07-16 15:26:08Z sheena $

/**
 *  theme_breadcrumb()
 */

function acquia_commons_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    return '<div class="breadcrumb">'. implode(' > ', $breadcrumb) .'</div>';
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
  $submitted_by = '<span class="comment-name">'.  theme('username', $vars['comment']) .'</span>';
  $submitted_by .= '<span class="comment-date">'.  time_ago($vars['comment']->timestamp).' '.t('ago').'</span>';     // Format date as small, medium, or large
  $vars['submitted'] = $submitted_by;
}

/**
*  Profile preprocessing
**/

function acquia_commons_preprocess_user_profile_item(&$vars) {
 
 //separate userpoints value from the edit links
 if($vars['title'] == 'Points') { 
 $userpoints = explode(' - ', $vars['value']);
  $vars['value'] = '<span class="points">'.$userpoints[0].'</span><span    class="edit-links">'.$userpoints[1].'</span>';
  unset($vars['title']);
  }
  
}

/**
 *  implementation of theme_shoutbox_post()
 */
function acquia_commons_shoutbox_post($shout, $links = array(), $alter_row_color=TRUE) {
  global $user;
  
  //Gather moderation links
  if ($links) {
    foreach ($links as $link) {
      $linkattributes = $link['linkattributes'];
      $link_html = '<img src="'. $link['img'] .'"  width="'. $link['img_width'] .'" height="'. $link['img_height'] .'" alt="'. $link['title'] .'" class="shoutbox-imglink">';
      $link_url = 'shoutbox/'. $shout->shout_id .'/'. $link['action'];
      $img_links = l($link_html, $link_url, array('html' => TRUE, 'query' => array('destination' => drupal_get_path_alias($_GET['q'])))) . $img_links;
    }
  }
  
  //Generate user name with link
  if ($shout->uid > 0) {
    $user_name = l($shout->nick, 'user/' . $shout->uid);
  }
  else {
    //Anonymous
    $user_name = $shout->nick;  
  }

  //Generate title attribute
  $title = t('Posted ' . format_date($shout->created, 'custom', 'm/d/y') . ' at ' . format_date($shout->created, 'custom', 'h:ia') . ' by ' . $shout->nick);
  
  $shout_classes = "shoutbox-msg ";
  if ($alter_row_color) {
    $shout_classes .= (($shout->color) ? ("odd ") : ("even "));
  }

  //Check for moderation
  if ($shout->moderate == 1) {
    $shout_classes .= "shoutbox-unpublished ";
    $shout->shout .= t("(This shout is waiting for approval by a moderator.)");
  }
  
  //Check for specific user class
  if ($shout->uid == $user->uid) {
    $user_class = ' shoutbox-current-user-name';
  }
  elseif ($shout->uid == 0) {
    $user_class = ' shoutbox-anonymous-user';  
  }
  
  //convert timestamp to time ago
  $post_time_ago = time_ago($shout->created);
  
  //load user image and format
   
   $author_picture ='';
   $shout_author =  user_load($array = array(uid => $shout->uid,));

      if(($shout_author->picture == '' ) && (variable_get('user_picture_default', '') != '')){
      $shout_author->picture =  variable_get('user_picture_default', '');
      }
      $author_picture ='';
      if($shout_author->picture != ''){
     $author_picture = theme_imagecache('user_picture_meta', $shout_author->picture, $shout_author->name, $shout_author->name);
     }
   
  return "<div class=\" $shout_classes \" title=\"$title\"><div class=\"shoutbox-admin-links\">$img_links</div><div class=\"shoutbox-post-info\">".$author_picture."<span class=\"shoutbox-user-name $user_class\">$user_name</span><span class=\"shoutbox-msg-time\">" . $post_time_ago . " ".t('ago')."</span></div><div class=\"shout-message\"> $shout->shout</div></div>\n";
}


//script to convert timestamp to "time ago"
function time_ago($tm,$rcs = 0) {

$cur_tm = time(); 

$dif = $cur_tm-$tm;

$pds = array('second','minute','hour','day','week','month','year','decade');

$lngh = array(1,60,3600,86400,604800,2630880,31570560,315705600);

for($v = sizeof($lngh)-1; ($v >= 0)&&(($no = $dif/$lngh[$v])<=1); $v--); if($v < 0) $v = 0; $_tm = $cur_tm-($dif%$lngh[$v]);

$no = floor($no); if($no <> 1) $pds[$v] .='s'; $x=sprintf("%d %s ",$no,$pds[$v]);
if(($rcs == 1)&&($v >= 1)&&(($cur_tm-$_tm) > 0)) $x .= time_ago($_tm);
return $x;

}


function acquia_commons_item_list($items = array(), $title = NULL, $type = 'ul', $attributes = NULL) {
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
      if(!is_numeric($i)){
      if (count($children) > 0) {
        $data .= theme_item_list($children, NULL, $type, $attributes); // Render nested list
      }
      if ($c == $num_items - 1) {
        $attributes['class'] = empty($attributes['class']) ? 'first' : ($attributes['class'] .' first');
      }
      if ($c == 0) {
        $attributes['class'] = empty($attributes['class']) ? 'last' : ($attributes['class'] .' last');
      }
      $attributes['class'] = $attributes['class'].' ' . ($c % 2 ? 'even' : 'odd');
      $output .= '<li'. drupal_attributes($attributes) .'>'. $data ."</li>\n";
      } else {
      if (count($children) > 0) {
        $data .= theme_item_list($children, NULL, $type, $attributes); // Render nested list
      }
      if ($i == 0) {
        $attributes['class'] = empty($attributes['class']) ? 'first' : ($attributes['class'] .' first');
      }
      if ($i == $num_items - 1) {
        $attributes['class'] = empty($attributes['class']) ? 'last' : ($attributes['class'] .' last');
      }
      $attributes['class'] = $attributes['class'].' ' . ($i % 2 ? 'even' : 'odd');
      $output .= '<li'. drupal_attributes($attributes) .'>'. $data ."</li>\n";
    }
    }
    $output .= "</$type>";
  }
  $output .= '</div>';
  return $output;
}

function acquia_commons_preprocess_block ($variables) {
  $variables['template_files'][] = 'block-'.$variables['block']->region.'-'.$variables['block']->module;
    $variables['template_files'][] = 'block-'.$variables['block']->region.'-'.$variables['block']->module.'-'.$variables['block']->delta;
  
}