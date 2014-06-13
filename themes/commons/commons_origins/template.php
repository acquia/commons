<?php

/**
 * @file
 * Process theme data.
 */

/**
 * Implements hook_theme().
 */
function commons_origins_theme($existing, $type, $theme, $path) {
  return array(
    // Register the newly added theme_form_content() hook so we can utilize
    // theme hook suggestions.
    // @see commons_origins_form_alter().
    'form_content' => array(
      'render element' => 'form',
      'path' => drupal_get_path('theme', 'commons_origins') . '/templates/form',
      'template' => 'form-content',
      'pattern' => 'form_content__',
    ),
  );
}

/**
 * Implements hook_commons_utility_links_alter().
 */
function commons_origins_commons_utility_links_alter(&$element) {
  // Add wrappers to title elements in notification links so that they can be
  // replaced with an icon.
  $iconify = array(
    'unread-invitations',
    'unread-messages',
  );
  foreach ($iconify as $name) {
    if (isset($element[$name])) {
      $words = explode(' ', $element[$name]['title']);
      foreach($words as &$word) {
        if(is_numeric($word)) {
          $word = '<span class="notification-count">' . $word . '</span>';
        }
        else {
          $word = '<span class="notification-label element-invisible">' . $word . '</span>';
        }
      }
      $element[$name]['title'] = implode(' ', $words);
      $element[$name]['html'] = TRUE;
    }
  }
}

/**
 * Implements hook_preprocess_media_oembed().
 */
function commons_origins_preprocess_media_oembed(&$variables) {
  $content = $variables['content'];
  $type = $variables['type'];

  // Video and rich type must have HTML content.
  // Wrap the HTML content in a <div> to allow it to be made responsive.
  if (in_array($type, array('video', 'rich'))) {
    $variables['content'] = '<div class="oembed">' . $content . '</div>';
  }
}

/**
 * Implements hook_preprocess_search_result().
 */
function commons_origins_preprocess_search_result(&$variables, $hook) {
  $variables['title_attributes_array']['class'][] = 'title';
  $variables['title_attributes_array']['class'][] = 'search-result-title';
  $variables['content_attributes_array']['class'][] = 'search-result-content';
}

/**
 * Implements hook_preprocess_search_results().
 *
 * Assemble attributes for styling that core does not do so we can keep the
 * tpl files simpler and make maintaining it a bit less worrisome since there
 * are 2 forms of search supported.
 */
function commons_origins_preprocess_search_results(&$variables, $hook) {
  $variables['classes_array'][] = 'search-results-wrapper';
  $variables['title_attributes_array']['class'][] = 'search-results-title';
  $variables['content_attributes_array']['class'][] = 'search-results-content';
  $variables['content_attributes_array']['class'][] = 'commons-pod';
}

/**
 * Implements hook_process_search_results().
 */
function commons_origins_process_search_results(&$variables, $hook) {
  // Set the title in preprocess so that it can be overridden by modules
  // further upstream.
  if (empty($variables['title'])) {
    $variables['title'] = t('Search results');
  }
}

/**
 * Shows a groups of blocks for starting a search from a filter.
 */
function commons_origins_apachesolr_search_browse_blocks($vars) {
  $result = '';
  if ($vars['content']['#children']) {
    $result .= '<div class="apachesolr-browse-blocks">' . "\n";
    $result .= '  <h2 class="search-results-title">' . t('Browse available categories') . '</h2>' . "\n";
    $result .= '  <div class="commons-pod">' . "\n";
    $result .= '    <p>' . t('Pick a category to launch a search.') . '</p>' . "\n";
    $result .= $vars['content']['#children'] . "\n";
    $result .= '  </div>' . "\n";
    $result .= '</div>';
  }

  return $result;
}

/**
 * Preprocess variables for the html template.
 */
function commons_origins_preprocess_html(&$variables, $hook) {
  global $theme_key;

  $site_name = variable_get('site_name', 'Commons');

  // Add a class to the body so we can adjust styles for the new menu item.
  if (module_exists('commons_search_solr_user')) {
    $variables['classes_array'][] = 'people-search-active';
  }

  $palette = variable_get('commons_origins_palette', 'default');
  if ($palette != 'default') {
    $variables['classes_array'][] = 'palette-active';
    $variables['classes_array'][] = drupal_html_class($palette);
  }

  // Browser/platform sniff - adds body classes such as ipad, webkit, chrome
  // etc.
  $variables['classes_array'][] = css_browser_selector();
}

/**
 * Implements hook_privatemsg_view_alter().
 */
function commons_origins_privatemsg_view_alter(&$elements) {
  // Wrap the message view and reply form in a commons pod.
  $elements['#theme_wrappers'][] = 'container';
  $elements['#attributes']['class'][] = 'privatemsg-conversation';
  $elements['#attributes']['class'][] = 'commons-pod';

  // Knock the reply form title down an h-level.
  if (isset($elements['reply']['reply']['#markup'])) {
    $elements['reply']['reply']['#markup'] = str_replace('h2', 'h3', $elements['reply']['reply']['#markup']);
  }

  // Apply classes to the form actions and make sure the submit comes first.
  if (isset($elements['reply']['actions']['submit'])) {
    $elements['reply']['actions']['submit']['#attributes']['class'][] = 'action-item-primary';
    $elements['reply']['actions']['submit']['#weight'] = 0;
  }
  if (isset($elements['reply']['actions']['cancel'])) {
    $elements['reply']['actions']['cancel']['#attributes']['class'][] = 'action-item';
    $elements['reply']['actions']['cancel']['#weight'] = 1;
  }
}

/**
 * Implements hook_privatemsg_message_view_alter().
 */
function commons_origins_privatemsg_message_view_alter(&$elements) {
  if (isset($elements['message_actions'])) {
    // Move the message links into a different variable and make it a renderable
    // array. Privatemsg has the links hardcoded, so this is the only way to
    // gain control and prevent extra processing.
    $elements['message_links'] = array(
      '#theme' => 'links__privatemsg_message',
      '#links' => $elements['message_actions'],
      '#attributes' => array(
        'class' => array('privatemsg-message-links', 'links'),
      ),
    );
    unset($elements['message_actions']);
  }
}

/**
 * Implements hook_preprocess_privatemsg_view().
 */
function commons_origins_preprocess_privatemsg_view(&$variables, $hook) {
  // Make the template conform with Drupal standard attributes.
  if (isset($variables['message_classes'])) {
    $variables['classes_array'] = array_merge($variables['classes_array'], $variables['message_classes']);
  }
  $variables['classes_array'][] = 'clearfix';
  $variables['attributes_array']['id'] = 'privatemsg-mid-' . $variables['mid'];
  $variables['content_attributes_array']['class'][] = 'privatemsg-message-content';

  // Add a distinct class to the "Delete" action.
  if (isset($variables['message_links']['#links'])) {
    foreach ($variables['message_links']['#links'] as &$link) {
      // Due to the lack of a proper key-baed identifier, a string search is the
      // only flexible way to sniff out the link.
      if (strpos($link['href'], 'delete')) {
        $link['attributes']['class'][] = 'message-delete';
      }
    }
  }
}

/**
 * Implements theme_menu_link().
 */
function commons_origins_menu_link($variables) {
  $output = '';
  $path_to_at_core = drupal_get_path('theme', 'adaptivetheme');

  include_once($path_to_at_core . '/inc/get.inc');

  global $theme_key;
  $theme_name = $theme_key;

  $element = $variables['element'];
  commons_origins_menu_link_class($element);
  $sub_menu = '';

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }

  if (at_get_setting('extra_menu_classes', $theme_name) == 1 && !empty($element['#original_link'])) {
    if (!empty($element['#original_link']['depth'])) {
      $element['#attributes']['class'][] = 'menu-depth-' . $element['#original_link']['depth'];
    }
    if (!empty($element['#original_link']['mlid'])) {
      $element['#attributes']['class'][] = 'menu-item-' . $element['#original_link']['mlid'];
    }
  }

  if (at_get_setting('menu_item_span_elements', $theme_name) == 1 && !empty($element['#title'])) {
    $element['#title'] = '<span>' . $element['#title'] . '</span>';
    $element['#localized_options']['html'] = TRUE;
  }

  if (at_get_setting('unset_menu_titles', $theme_name) == 1 && !empty($element['#localized_options']['attributes']['title'])) {
    unset($element['#localized_options']['attributes']['title']);
  }

  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>";
}

/**
 * Helper function to examine menu links and return the appropriate class.
 */
function commons_origins_menu_link_class(&$element)  {
  if ($element['#original_link']['menu_name'] == 'main-menu') {
    $element['#attributes']['class'][] = drupal_html_class($element['#original_link']['menu_name'] . '-' . $element['#original_link']['router_path']);
  }
}

/**
 * Override or insert variables for the page templates.
 */
function commons_origins_preprocess_page(&$variables, $hook) {
  if (module_exists('page_manager')) {
    $p = page_manager_get_current_page();
    if (isset($p['name']) && $p['name'] == 'node_view') {
      $node = $p['contexts']['argument_entity_id:node_1']->data;
      if (module_exists('og') && !og_is_group('node', $node)) {
        $variables['hide_panelized_title'] = 1;
      }
    }
  }

  $variables['header_attributes_array']['class'][] = 'container';

  $cf_pos = in_array('clearfix', $variables['branding_attributes_array']['class']);
  unset($variables['branding_attributes_array']['class'][$cf_pos]);

  // Only load the media styles if Commons Media is enabled.
  if (module_exists('commons_media')) {
    drupal_add_css(drupal_get_path('theme', 'commons_origins') . '/css/commons-media.css', array('media' => 'screen', 'group' => CSS_THEME));
  }
}

/**
 * Override or insert variables into the node templates.
 */
function commons_origins_preprocess_node(&$variables, $hook) {
  $node = $variables['node'];

  // Some content does not get a user image on the full node.
  $no_avatar = array(
    'event',
    'group',
    'page',
    'wiki',
  );
  if (!$variables['teaser'] && in_array($node->type, $no_avatar)) {
    $variables['user_picture'] = '';
  }

  // If there does happen to be a user image, add a class for styling purposes.
  if (!empty($variables['user_picture'])) {
    $variables['classes_array'][] = 'user-picture-available';
  }

  // Style node links like buttons.
  if (isset($variables['content']['links'])) {
    foreach ($variables['content']['links'] as $type => &$linkgroup) {
      // Button styling for the "rate" and "flag" types will be handled
      // separately.
      if ($type != 'rate' && $type != 'flag' && substr($type, 0, 1) != '#') {
        foreach ($linkgroup['#links'] as $name => &$link) {
          // Prevent errors when no classes have been defined.
          if (!isset($link['attributes']['class'])) {
            $link['attributes']['class'] = array();
          }

          // Apply button classes to everything but comment_forbidden.
          if ($name != 'comment_forbidden' && $name != 'answer-add' && !is_string($link['attributes']['class'])) {
            $link['attributes']['class'][] = 'action-item-small';
            $link['attributes']['class'][] = 'action-item-inline';
          }
          elseif ($name != 'comment_forbidden' && $name != 'answer-add') {
            $link['attributes']['class'] .= ' action-item-small action-item-inline';
          }
        }
        // Clean the reference so it does not confuse things further down.
        unset($link);
      }
    }
  }

  // Add classes to render the comment-comments link as a button with a number
  // attached.
  if (!empty($variables['content']['links']['comment']['#links']['comment-comments'])) {
    $comments_link = &$variables['content']['links']['comment']['#links']['comment-comments'];
    $comments_link['attributes']['class'][] = 'link-with-counter';
    $chunks = explode(' ', $comments_link['title']);

    // Add appropriate classes to words in the title.
    foreach ($chunks as &$chunk) {
      if ($chunk == $variables['comment_count']) {
        $chunk = '<span class="action-item-small-append">' . $variables['comment_count'] . '</span>';
      }
      else {
        $chunk = '<span class="element-invisible">' . $chunk . '</span>';
      }
    }
    $comments_link['title'] = implode(' ', $chunks);
  }

  // Push the reporting link to the end.
  if (!empty($variables['content']['links']['flag']['#links']['flag-inappropriate_node'])) {
    $variables['content']['report_link'] = array('#markup' => $variables['content']['links']['flag']['#links']['flag-inappropriate_node']['title']);
  }

  if (!empty($variables['content']['links'])) {
    // Hide some of the node links.
    $hidden_links = array(
      'node' => array(
        'node-readmore',
      ),
      'comment' => array(
        'comment-add',
        'comment-new-comments'
      ),
      'flag' => array(
        'flag-inappropriate_node',
      ),
    );
    foreach ($hidden_links as $element => $links) {
      foreach ($links as $link) {
        if (!empty($variables['content']['links'][$element]['#links'][$link])) {
          $variables['content']['links'][$element]['#links'][$link]['#access'] = FALSE;
        }
      }
    }
  }

  // Add a class to the node when there is a logo image.
  if (!empty($variables['field_logo'])) {
    $variables['classes_array'][] = 'logo-available';
  }

  // Move the answer link on question nodes to the top of the content.
  if ($variables['node']->type == 'question' && !empty($variables['content']['links']['answer'])) {
    $variables['content']['answer'] = $variables['content']['links']['answer'];
    $variables['content']['answer']['#attributes']['class'][] = 'node-actions';
    $variables['content']['answer']['#links']['answer-add']['attributes']['class'][] = 'action-item-primary';
    $variables['content']['answer']['#weight'] = -100;
    $variables['content']['links']['answer']['#access'] = FALSE;
  }

  // Groups the related fields into their own container.
  $related_information = array(
    'og_group_ref',
    'field_related_question',
    'field_topics',
  );
  foreach($related_information as $field) {
    if (!empty($variables['content'][$field])) {
      $variables['content']['related_information'][$field] = $variables['content'][$field];
      hide($variables['content'][$field]);
    }
  }
  if (!empty($variables['content']['related_information'])) {
    $variables['content']['related_information'] += array(
      '#theme_wrappers' => array('container'),
      '#attributes' => array(
        'class' => array('related-information', 'clearfix'),
      ),
      '#weight' => 1000,
    );
  }

  // Add classes when there is a voting widget present.
  if (!empty($variables['content']['rate_commons_answer'])) {
    $variables['content_attributes_array']['class'][] = 'has-rate-widget';
    $variables['content']['rate_commons_answer']['#weight'] = 999;
  }

  // Add a general class to the node links.
  if (!empty($variables['content']['links'])) {
    $variables['content']['links']['#attributes']['class'][] = 'node-action-links';

    // For some reason, the node links processing is not always added and
    // multiple ul elements are output instead of a single.
    if (!isset($variables['content']['links']['#pre_render']) || !in_array('drupal_pre_render_links', $variables['content']['links']['#pre_render'])) {
      $variables['content']['links']['#pre_render'][] = 'drupal_pre_render_links';
    }
  }
}

/**
 * Implements hook_preprocess_comment_wrapper().
 */
function commons_origins_preprocess_comment_wrapper(&$variables, $hook) {
  // Change things around to use the attribute arrays for the titles.
  $variables['title_attributes_array']['class'][] = 'comments-title';
  $variables['form_title_attributes_array'] = array(
    'class' => array('comment-title', 'title', 'comment-form', 'comment-form-title')
  );
}

/**
 * Implements hook_process_comment_wrapper().
 */
function commons_origins_process_comment_wrapper(&$variables, $hook) {
  // Make sure the form_title_attributes_array is rendered into a single string.
  $variables['form_title_attributes'] = drupal_attributes($variables['form_title_attributes_array']);
}

/**
 * Implements hook_preprocess_comment().
 */
function commons_origins_preprocess_comment(&$variables, $hook) {
  $variables['content']['links']['#attributes']['class'][] = 'comment-links';

  // Push the reporting link to the end.
  if (!empty($variables['content']['links']['flag']['#links']['flag-inappropriate_comment'])) {
    $variables['content']['report_link'] = array('#markup' => $variables['content']['links']['flag']['#links']['flag-inappropriate_comment']['title']);
    $variables['content']['links']['flag']['#links']['flag-inappropriate_comment']['#access'] = FALSE;
  }
}

/**
 * Implements hook_preprocess_flag().
 */
function commons_origins_preprocess_flag(&$variables, $hook) {
  if (strpos($variables['flag_name_css'], 'inappropriate-') !== 0) {
    // Style the flag links like buttons.
    if ($variables['last_action'] == 'flagged') {
      $variables['flag_classes_array'][] = 'action-item-small-active';
    }
    else {
      $variables['flag_classes_array'][] = 'action-item-small';
    }
    $variables['flag_classes'] = implode(' ', $variables['flag_classes_array']);
  }
}

/**
 * Implements hook_preprocess_two_33_66().
 */
function commons_origins_preprocess_two_33_66(&$variables, $hook) {
  $menu = menu_get_item();

  // Suggest a variant for the search page so the facets will be wrapped in pod
  // styling.
  if (strpos($menu['path'], 'search') === 0) {
    $variables['theme_hook_suggestions'][] = 'two_33_66__search';
  }
}

function commons_origins_preprocess_three_25_50_25(&$variables, $hook) {
  $menu = menu_get_item();

  // Suggest a variant for the search page so the facets will be wrapped in pod
  // styling.
  if (isset($menu['page_arguments']) && $menu['page_arguments'][0] == 'solr_events') {
    $variables['theme_hook_suggestions'][] = 'three_25_50_25__events';
  }
}

/**
 * Implements hook_preprocess_panelizer_view_mode().
 */
function commons_origins_preprocess_panelizer_view_mode(&$variables, $hook) {
  // Add classed to identity the entity type being overridden.
  $variables['classes_array'][] = drupal_html_class('panelizer-' . $variables['element']['#entity_type']);
  $variables['title_attributes_array']['class'][] = drupal_html_class($variables['element']['#entity_type'] . '-title');
  $variables['title_attributes_array']['class'][] = drupal_html_class('panelizer-' . $variables['element']['#entity_type'] . '-title');

  // Add some extra theme hooks for the subthemers.
  $variables['hook_theme_suggestions'][] = $hook . '__' . $variables['element']['#entity_type'];
  $variables['hook_theme_suggestions'][] = $hook . '__' . $variables['element']['#entity_type'] . '__' . $variables['element']['#bundle'];
}

/**
 * Implements hook_preprocess_panels_pane().
 */
function commons_origins_preprocess_panels_pane(&$variables, $hook) {
  $pane = $variables['pane'];

  // Add pod styling to some of the panels panes.
  $not_pods = array(
    'commons_events-commons_events_create_event_link',
  );
  $content_pods = array(
    'commons_question_answers-panel_pane_1',
  );
  if (($pane->panel == 'two_66_33_second' && !in_array($pane->subtype, $not_pods)) || in_array($pane->subtype, $content_pods)) {
    $variables['attributes_array']['class'][] = 'commons-pod';
  }

  // Mimic the class for the facetapi blocks on the panel variant.
  if (strpos($pane->subtype, 'facetapi-') === 0) {
    $variables['attributes_array']['class'][] = 'block-facetapi';
  }

  // Hide the pane title for the group contributor count.
  if ($pane->subtype == 'node:commons-groups-group-contributors-count-topics') {
    $variables['title_attributes_array']['class'][] = 'element-invisible';
  }

  // Apply common classes to the recent items related to a group.
  static $recent_count = 0;
  if ($pane->subtype == 'commons_groups_recent_content' || $pane->subtype == 'commons_contributors_group-panel_pane_1') {
    $variables['attributes_array']['class'][] = 'group-recent-data';
    $variables['attributes_array']['class'][] = $recent_count % 2 == 0 ? 'group-recent-data-even' : 'group-recent-data-odd';
    $recent_count++;
  }

  // Hide the groups view title since it is redundant.
  if ($pane->subtype == 'commons_groups_directory-panel_pane_1') {
    $variables['title_attributes_array']['class'][] = 'element-invisible';
  }
}

/**
 * Overrides theme_panels_default_style_render_region();
 */
function commons_origins_panels_default_style_render_region($variables) {
  $output = '';
  // Remove the empty panels-separator div.
  $output .= implode("\n", $variables['panes']);
  return $output;
}

/**
 * Implements hook_preprocess_views_view().
 */
function commons_origins_preprocess_views_view(&$variables, $hook) {
  $view = $variables['view'];

  // Wrap page views in pod styling.
  if ($view->display_handler->plugin_name == 'page') {
    $variables['classes_array'][] = 'commons-pod';
    $variables['classes_array'][] = 'clearfix';
  }

  // Style some views without bottom borders and padding.
  $plain = array(
    'commons_groups_directory' => array('panel_pane_1'),
    'commons_groups_recent_content' => array('block'),
    'commons_groups_user_groups' => array('panel_pane_1'),
    'commons_radioactivity_groups_active_in_group' => array('panel_pane_1'),
  );
  if (isset($plain[$variables['name']]) && in_array($variables['display_id'], $plain[$variables['name']])) {
    $variables['classes_array'][] = 'view-plain';
  }
}

/**
 * Implements hook_preprocess_views_view_unformatted().
 */
function commons_origins_preprocess_views_view_unformatted(&$variables, $hook) {
  $view = $variables['view'];

  // Prevent the avatars in the activity stream blocks from bleeding into the
  // rows below them.
  if ($view->name == 'commons_activity_streams_activity') {
    foreach ($variables['classes_array'] as &$classes) {
      $classes .= ' clearfix';
    }
  }

  // Add a class to rows designating the node type for the rows that give us the
  // node type information.
  foreach ($view->result as $id => $result) {
    if (isset($result->node_type)) {
      $variables['classes_array'][$id] .= ' ' . drupal_html_class('row-type-' . $result->node_type);
    }
    else if (($view->name == 'commons_events_upcoming' && $view->override_path != 'events') || $view->name == 'commons_events_user_upcoming_events') {
      $variables['classes_array'][$id] .= ' ' . drupal_html_class('row-type-event');
    }
  }
}

/**
 * Implements hook_preprocess_pager().
 */
function commons_origins_preprocess_pager_link (&$variables, $hook) {
  // Style pager links like buttons.
  $variables['attributes']['class'][] = 'action-item';
  $variables['attributes']['class'][] = 'action-item-inline';
}

/**
 * Implements hook_preprocess_form().
 *
 * Since Commons Origins overrides the default theme_form() function, we will
 * need to perform some processing on attributes to make it work in a template.
 */
function commons_origins_preprocess_form(&$variables, $hook) {
  // Bootstrap the with some of Drupal's default variables.
  template_preprocess($variables, $hook);

  $element = &$variables['element'];
  if (isset($element['#action'])) {
    $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
  }
  element_set_attributes($element, array('method', 'id'));
  if (empty($element['#attributes']['accept-charset'])) {
    $element['#attributes']['accept-charset'] = "UTF-8";
  }
  $variables['attributes_array'] = $element['#attributes'];

  // Roll the classes into the attributes.
  if (empty($variables['attributes_array']['class'])) {
    $variables['attributes_array']['class'] = $variables['classes_array'];
  }
  else {
    $variables['attributes_array']['class'] = array_merge($variables['attributes_array']['class'], $variables['classes_array']);
  }

  // Give the search form on the search page pod styling.
  if (isset($element['#search_page']) || (isset($element['module']) && ($element['module']['#value'] == 'search_facetapi' || $element['module']['#value'] == 'user'))) {
    $variables['attributes_array']['class'][] = 'search-form-page';
    $variables['attributes_array']['class'][] = 'commons-pod';
    $variables['attributes_array']['class'][] = 'clearfix';
  }

  // Wrap some forms in the commons pod styling.
  $pods = array(
    'user-login',
    'user-pass',
    'user-register-form',
  );
  if (in_array($element['#id'], $pods)) {
    $variables['attributes_array']['class'][] = 'commons-pod';
  }

  // Give the dynamic filters a special class to target.
  if (strpos($element['#id'], 'views-exposed-form-commons-homepage-content') === 0 || strpos($element['#id'], 'views-exposed-form-commons-events-upcoming') === 0 || strpos($element['#id'], 'views-exposed-form-commons-bw') === 0) {
    $variables['attributes_array']['class'][] = 'dynamic-filter-lists';
  }

  // Give the keyword filter a pod wrapper.
  if (strpos($element['#id'], 'views-exposed-form-commons-groups') === 0) {
    $variables['attributes_array']['class'][] = 'keyword-filter';
    $variables['attributes_array']['class'][] = 'commons-pod';
  }

  // Set an identifying class to the event attendance form.
  if(strpos($element['#id'], 'commons-events-attend-event-form') === 0) {
    $variables['attributes_array']['class'][] = 'node-actions';
  }

  // Make sure the bottom of the partial node form clears all content.
  if (strpos($element['#form_id'], 'commons_bw_partial_node_form_') === 0) {
    $variables['attributes_array']['class'][] = 'user-picture-available';
    $variables['attributes_array']['class'][] = 'clearfix';
  }

  // Place the user avatar to the left of the private message form content.
  if ($variables['element']['#form_id'] == 'commons_trusted_contacts_messages_popup') {
    $variables['content_attributes_array']['class'][] = 'user-picture-available';
  }
}

/**
 * Implements hook_process_form().
 *
 * Since Commons Origins overrides the default theme_form() function, we will
 * need to perform some processing on attributes to make it work in a template.
 */
function commons_origins_process_form(&$variables, $hook) {
  // Crunch down attribute arrays.
  template_process($variables, $hook);
}

/**
 * Implements hook_preprocess_form_content().
 */
function commons_origins_preprocess_form_content(&$variables, $hook) {
  // Bootstrap the with some of Drupal's default variables.
  template_preprocess($variables, $hook);

  if (isset($variables['form']['supplementary'])) {
    foreach ($variables['form']['supplementary'] as &$field) {
      if (is_array($field) && isset($field['#theme_wrappers'])) {
        $field['#theme_wrappers'][] = 'container';
        $field['#attributes']['class'][] = 'commons-pod';
      }
    }
  }

  // The buttons for toggling event attendance should be large and noticeable.
  // These forms have a varying form id, so check for if the id contains a
  // string instead of the whole thing.
  if (strpos($variables['form']['#form_id'], 'commons_events_attend_event_form') === 0) {
    $variables['form']['submit']['#attributes']['class'][] = 'action-item-primary';
  }
  if (strpos($variables['form']['#form_id'], 'commons_events_cancel_event_form') === 0) {
    $variables['form']['submit']['#attributes']['class'][] = 'action-item-active';
  }

  // Make the "Save" button more noticeable.
  if (isset($variables['form']['#node_edit_form']) && $variables['form']['#node_edit_form']) {
    $variables['form']['actions']['submit']['#attributes']['class'][] = 'action-item-primary';
  }

  // Make the comment form "Save" button more noticeable.
  if ($variables['form']['#id'] == 'comment-form') {
    $variables['form']['actions']['submit']['#attributes']['class'][] = 'action-item-primary';
  }

  // Hide the label and make the search button primary.
  if (isset($variables['form']['#search_page']) || (isset($variables['form']['module']) && ($variables['form']['module']['#value'] == 'search_facetapi' || $variables['form']['module']['#value'] == 'user'))) {
    $variables['form']['basic']['keys']['#title_display'] = 'invisible';
    $variables['form']['basic']['submit']['#attributes']['class'][] = 'action-item-search';
  }

  // Make the partial post form submit button a primary action and give some
  // theme hook suggestions for easy overriding.
  if (strpos($variables['form']['#form_id'], 'commons_bw_partial_node_form_') === 0) {
    $variables['form']['actions']['submit']['#attributes']['class'][] = 'action-item-primary';

    if (isset($variables['form']['title'])) {
      $variables['form']['title']['#markup'] = '<h3 class="partial-node-form-title">' . $variables['form']['title']['#markup'] . '</h3>';
    }
  }

  // Make the links and buttons on the private message forms have the
  // appropriate styles.
  if ($variables['form']['#form_id'] == 'commons_trusted_contacts_messages_popup' || $variables['form']['#form_id'] == 'privatemsg_new') {
    if (isset($variables['form']['actions']['submit'])) {
      $variables['form']['actions']['submit']['#attributes']['class'][] = 'action-item-primary';
    }
    if (isset($variables['form']['actions']['full_form'])) {
      $variables['form']['actions']['full_form']['#attributes']['class'][] = 'action-item';
    }
    if (isset($variables['form']['actions']['cancel'])) {
      $variables['form']['actions']['cancel']['#attributes']['class'][] = 'action-item';
      $variables['form']['actions']['cancel']['#weight'] = $variables['form']['actions']['submit']['#weight'] + 1;
    }
  }
}

/**
 * Implements hook_process_form_content().
 */
function commons_origins_process_form_content(&$variables, $hook) {
  // Crunch down attribute arrays.
  template_process($variables, $hook);
}

/**
 * Implements hook_preprocess_rate_template_commons_like().
 */
function commons_origins_preprocess_rate_template_commons_like(&$variables, $hook) {
  // Roll the content into a renderable array to make the template simpler.
  $variables['content'] = array(
    'link' => array(
      '#theme' => 'rate_button__commons_like',
      '#text' => $variables['links'][0]['text'],
      '#href' => $variables['links'][0]['href'],
      '#class' => 'rate-commons-like-btn action-item-small action-item-merge',
    ),
    'count' => array(
      '#theme' => 'html_tag',
      '#tag' => 'span',
      '#value' => $variables['results']['count'],
      '#attributes' => array(
        'class' => array(
          'rate-commons-like-count',
          'action-item-small-append',
          'action-item-merge',
        ),
      ),
    ),
  );
}

/**
 * Overrides hook_rate_button() for commons_like.
 */
function commons_origins_rate_button__commons_like($variables) {
  $text = $variables['text'];
  $href = $variables['href'];
  $class = $variables['class'];
  static $id = 0;
  $id++;

  $classes = 'rate-button';
  if ($class) {
    $classes .= ' ' . $class;
  }
  if (empty($href)) {
    // Widget is disabled or closed.
    return '<span class="' . $classes . '" id="rate-button-' . $id . '">' .
      '<span class="element-invisible">' . check_plain($text) . '</span>' .
      '</span>';
  }
  else {
    return '<a class="' . $classes . '" id="rate-button-' . $id . '" rel="nofollow" href="' . htmlentities($href) . '" title="' . check_plain($text) . '">' .
      '<span class="element-invisible">' . check_plain($text) . '</span>' .
      '</a>';
  }
}

/**
 * Implements hook_form_alter().
 */
function commons_origins_form_alter(&$form, &$form_state, $form_id) {
  // Give forms a common theme function so we do not have to declare every
  // single form we want to override in hook_theme().
  if (is_array($form['#theme'])) {
    $hooks = array('form_content');
    $form['#theme'] = array_merge($form['#theme'], $hooks);
  }
  else {
    $form['#theme'] = array(
      $form['#theme'],
      'form_content',
    );
  }

  // Description text on these fields is redundant.
  if ($form_id == 'user_login') {
    $form['name']['#description'] = '';
    $form['pass']['#description'] = '';
  }

  if ($form_id == 'user_register_form') {
    $form['account']['mail']['#description'] = t('Password reset and notification emails will be sent to this address.');
  }

  if (isset($form['#node_edit_form']) && $form['#node_edit_form']) {
    // Vertical tabs muck things up, so things need to be shuffled to get rid
    // of them.
    $general_settings = array();
    foreach ($form as $id => $field) {
      if (is_array($field) && isset($field['#group']) && $field['#group'] == 'additional_settings' && (!isset($field['#access']) || $field['#access'] !== FALSE)) {
        $general_settings[$id] = $field;
        $general_settings[$id]['#collapsible'] = TRUE;
        $general_settings[$id]['#collapsed'] = TRUE;
        unset($general_settings[$id]['#group']);
      }
    }
    if (!empty($general_settings)) {
      $form['general_settings'] = array(
        '#theme_wrappers' => array('container'),
        '#attributes' => array(
          'class' => array('general-settings'),
        ),
        '#weight' => 100,
        'general_settings' => $general_settings,
      );
      $form['additional_settings']['#access'] = FALSE;
    }

    // Declare the fields to go into each column.
    $supplementary = array(
      'event_topics',
      'field_topics',
      'general_settings',
    );

    foreach ($supplementary as $field) {
      if (isset($form[$field])) {
        // Translate the field to the appropriate container.
        $form['supplementary'][$field] = $form[$field];

        // Remove access to the old placement instead of unset() to maintain
        // the legacy information.
        $form[$field]['#access'] = FALSE;
      }
    }
  }
}

/**
 * Implements hook_views_bulk_operations_form_Alter().
 */
function commons_origins_views_bulk_operations_form_alter(&$form, $form_state, $vbo) {
  // change the buttons' fieldset wrapper to a div and push it to the bottom of
  // the form.
  $form['select']['#type'] = 'container';
  $form['select']['#weight'] = 9999;
}

/**
 * Implements hook_css_alter().
 */
function commons_origins_css_alter(&$css) {
  // Remove preset styles that interfere with theming.
  $unset = array(
    drupal_get_path('module', 'search') . '/search.css',
    drupal_get_path('module', 'rich_snippets') . '/rich_snippets.css',
    drupal_get_path('module', 'commons_like') . '/commons-like.css',
    drupal_get_path('module', 'panels') . '/css/panels.css',
  );
  foreach ($unset as $path) {
    if (isset($css[$path])) {
      unset($css[$path]);
    }
  }
}

/**
 * Overrides theme_links() for nodes.
 *
 * This allows for the theme to set a link's #access argument to FALSE so it
 * will not render.
 */
function commons_origins_links($variables) {
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];
  global $language_url;
  $output = '';

  if (count($links) > 0) {
    $output = '';

    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading.
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      if (!isset($link['#access']) || $link['#access'] !== FALSE) {
        $class = array($key);

        // Add first, last and active classes to the list of links to help out themers.
        if ($i == 1) {
          $class[] = 'first';
        }
        if ($i == $num_links) {
          $class[] = 'last';
        }
        if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page())) && (empty($link['language']) || $link['language']->language == $language_url->language)) {
          $class[] = 'active';
        }
        $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';

        if (isset($link['href'])) {
          // Pass in $link as $options, they share the same keys.
          $output .= l($link['title'], $link['href'], $link);
        }
        elseif (!empty($link['title'])) {
          // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
          if (empty($link['html'])) {
            $link['title'] = check_plain($link['title']);
          }
          $span_attributes = '';
          if (isset($link['attributes'])) {
            $span_attributes = drupal_attributes($link['attributes']);
          }
          $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
        }

        $i++;
        $output .= "</li>\n";
      }
    }

    $output .= '</ul>';
  }

  return $output;
}

/**
 * Overrides theme_fieldset().
 *
 * Add another div wrapper around fieldsets for styling purposes.
 */
function commons_origins_fieldset($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id'));
  _form_set_class($element, array('form-wrapper'));

  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';
  if (!empty($element['#title'])) {
    // Always wrap fieldset legends in a SPAN for CSS positioning.
    $output .= '<legend><span class="fieldset-legend">' . $element['#title'] . '</span></legend>';
  }
  $output .= '<div class="fieldset-wrapper">';
  if (!empty($element['#description'])) {
    $output .= '<div class="fieldset-description">' . $element['#description'] . '</div>';
  }
  $output .= $element['#children'];
  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }
  $output .= '</div>';
  $output .= "</fieldset>\n";
  return '<div class="fieldset-outer-wrapper">' . $output . '</div>';
}

/**
 * Process an address to add microformat structure and remove &nbsp;
 * characters.
 */
function _commons_origins_format_address(&$address) {
  $address['#theme_wrappers'][] = 'container';
  $address['#attributes']['class'][] = 'adr';
  if (!empty($address['street_block']['thoroughfare'])) {
    $address['street_block']['thoroughfare']['#attributes']['class'][] = 'street-address';
  }
  if (!empty($address['street_block']['premise'])) {
    $address['street_block']['premise']['#attributes']['class'][] = 'extended-address';
  }
  if (!empty($address['locality_block']['locality'])) {
    $address['locality_block']['locality']['#suffix'] = ',';
  }
  if (!empty($address['locality_block']['administrative_area'])) {
    $address['locality_block']['administrative_area']['#attributes']['class'][] = 'region';
    // Remove the hardcoded "&nbsp;&nbsp;" as it causes issues with
    // formatting.
    $address['locality_block']['administrative_area']['#prefix'] = ' ';
  }
  if (!empty($address['locality_block']['postal_code'])) {
    // Remove the hardcoded "&nbsp;&nbsp;" as it causes issues with
    // formatting.
    $address['locality_block']['postal_code']['#prefix'] = ' ';
  }
  if (!empty($address['country'])) {
    $address['country']['#attributes']['class'][] = 'country-name';
  }
}

/**
 * Implements hook_preprocess_field().
 */
function commons_origins_preprocess_field(&$variables, $hook) {
  // Style the trusted contact link like a button.
  if (isset($variables['element']['#formatter']) && $variables['element']['#formatter'] == 'trusted_contact') {
    foreach ($variables['items'] as &$container) {
      foreach (element_children($container) as $index) {
        $item = &$container[$index];
        if (isset($item['#options'])) {
          $item['#options']['attributes']['class'][] = 'action-item-small';
        }
        if (isset($item['#href']) && strpos($item['#href'], 'messages')) {
          $item['#options']['attributes']['class'][] = 'message-contact';
        }
        elseif (isset($item['#href'])) {
          $item['#options']['attributes']['class'][] = 'trusted-status-request';
        }
      }
    }
  }
}

/**
 * Override theme_html_tag__request_pending().
 */
function commons_origins_html_tag__request_pending($variables) {
  $element = $variables['element'];
  $element['#attributes']['class'][] = 'action-item-small-active';
  $element['#attributes']['class'][] = 'trusted-status-pending';
  $attributes = drupal_attributes($element['#attributes']);

  if (!isset($element['#value'])) {
    return '<' . $element['#tag'] . $attributes . " />\n";
  }
  else {
    $output = '<' . $element['#tag'] . $attributes . '>';
    if (isset($element['#value_prefix'])) {
      $output .= $element['#value_prefix'];
    }
    $output .= $element['#value'];
    if (isset($element['#value_suffix'])) {
      $output .= $element['#value_suffix'];
    }
    $output .= '</' . $element['#tag'] . ">\n";
    return $output;
  }
}

/**
 * Overrides theme_field() for group fields.
 *
 * This will apply button styling to the links for leaving and joining a group.
 */
function commons_origins_field__group_group__group($variables) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<div class="field-label"' . $variables['title_attributes'] . '>' . $variables['label'] . ':&nbsp;</div>';
  }

  // Render the items.
  $output .= '<div class="field-items"' . $variables['content_attributes'] . '>';
  foreach ($variables['items'] as $delta => $item) {
    if (isset($item['#type']) && $item['#type'] == 'link') {
      if (strpos($item['#href'], '/subscribe')) {
        $item['#options']['attributes']['class'][] = 'action-item-primary';
      }
      else {
        $item['#options']['attributes']['class'][] = 'action-item';
      }
    }

    $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
    $output .= '<div class="' . $classes . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</div>';
  }
  $output .= '</div>';

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>';

  return $output;
}

/**
 * Overrides theme_field__addressfield().
 */
function commons_origins_field__addressfield($variables) {
  $output = '';

  // Add Microformat classes to each address.
  foreach($variables['items'] as &$address) {
    // Only display an address if it has been populated. We determine this by
    // validating that the administrative area has been populated.
    if (!empty($address['#address']['administrative_area'])) {
      _commons_origins_format_address($address);
    }
    else {
      // Deny access to incomplete addresses.
      $address['#access'] = FALSE;
    }
  }

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<div class="field-label"' . $variables['title_attributes'] . '>' . $variables['label'] . ':</div> ';
  }

  // Render the items.
  $output .= '<div class="field-items"' . $variables['content_attributes'] . '>';
  foreach ($variables['items'] as $delta => $item) {
    $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
    $output .= '<div class="' . $classes . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</div>';
  }
  $output .= '</div>';

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>';

  return $output;
}

/**
 * Implements hook_preprocess_views_view_field().
 */
function commons_origins_preprocess_views_view_field(&$variables, $hook) {
  // Make sure empty addresses are not displayed.
  // Views does not use theme_field__addressfield(), so we need to process
  // these implementations separately.
  if (isset($variables['theme_hook_suggestion']) && $variables['theme_hook_suggestion'] == 'views_view_field__field_address') {
    foreach ($variables['row']->field_field_address as $key => &$address) {
      if (!$address['raw']['administrative_area']) {
        // If an address is incomplete, remove it and tell the system a
        // rebuild is needed.
        unset($variables['row']->field_field_address[$key]);
      }
      else {
        _commons_origins_format_address($address['rendered']);
      }
    }

    // The output will need rebuilt to get the changes applied.
    $variables['output'] = $variables['field']->advanced_render($variables['row']);
  }
}

/**
 * Implements hook_preprocess_user_profile().
 */
function commons_origins_preprocess_user_profile(&$variables, $hook) {
  if (in_array('user_profile__search_results', $variables['theme_hook_suggestions'])) {
    // Give the profile a distinctive class to target and wrap the display in
    // pod styling.
    $variables['classes_array'][] = 'profile-search-result';
    $variables['classes_array'][] = 'commons-pod';

    // Wrap the group list and related title in a div.
    if (isset($variables['user_profile']['group_membership'])) {
      $variables['user_profile']['group_membership']['#theme_wrappers'][] = 'container';
      $variables['user_profile']['group_membership']['#attributes']['class'][] = 'profile-groups';
    }

    // Group actionable items together in a container.
    $variables['user_profile']['user_actions'] = array();
    $user_actions = array(
      'flags',
      'privatemsg_send_new_message',
      'group_group',
    );
    foreach ($user_actions as $action) {
      if (isset($variables['user_profile'][$action])) {
        $variables['user_profile']['user_actions'][$action] = $variables['user_profile'][$action];
        $variables['user_profile'][$action]['#access'] = FALSE;
      }
    }
    if (!module_exists('commons_trusted_contacts') && isset(  $variables['user_profile']['user_actions']['group_group'])) {
      $variables['user_profile']['user_actions']['group_group']['#access'] = FALSE;
    }
    if (!empty($variables['user_profile']['user_actions'])) {
      $variables['user_profile']['user_actions'] += array(
        '#theme_wrappers' => array('container'),
        '#attributes' => array(
          'class' => array('profile-actions'),
        ),
      );
    }
  }
}

/**
 * Implements hook_preprocess_commons_search_solr_user_results().
 */
function commons_origins_preprocess_commons_search_solr_user_results(&$variables, $hook) {
  // Hide the results title.
  $variables['title_attributes_array']['class'][] = 'element-invisible';
}

/**
 * Implements hook_process_node().
 */
function commons_origins_process_node(&$variables, $hook) {
  $node = $variables['node'];
  $wrapper = entity_metadata_wrapper('node', $node);

  // Use timeago module for formatting node submission date
  // if it is enabled and also configured to be used on nodes.
  if (module_exists('timeago') && variable_get('timeago_node', 1)) {
    $variables['date'] = timeago_format_date($node->created, $variables['date']);
    $use_timeago_date_format = TRUE;
  }
  else {
    $use_timeago_date_format = FALSE;
  }

  // Replace the submitted text on nodes with something a bit more pertinent to
  // the content type.
  if (variable_get('node_submitted_' . $node->type, TRUE)) {
    $node_type_info = node_type_get_type($variables['node']);
    $type_attributes = array('class' => array(
      'node-content-type',
      drupal_html_class('node-content-type-' . $node->type),
    ));
    $placeholders = array(
      '!type' => '<span' . drupal_attributes($type_attributes) . '>' . check_plain($node_type_info->name) . '</span>',
      '!user' => $variables['name'],
      '!date' => $variables['date'],
      '@interval' => format_interval(REQUEST_TIME - $node->created),
    );
    // Show what group the content belongs to if applicable.
    if (!empty($node->{OG_AUDIENCE_FIELD}) && $wrapper->{OG_AUDIENCE_FIELD}->count() == 1) {
      $placeholders['!group'] = l($wrapper->{OG_AUDIENCE_FIELD}->get(0)->label(), 'node/' . $wrapper->{OG_AUDIENCE_FIELD}->get(0)->getIdentifier());
      if ($use_timeago_date_format == TRUE) {
        $variables['submitted'] = t('!type created !date in the !group group by !user', $placeholders);
      }
      else {
        $variables['submitted'] = t('!type created @interval ago in the !group group by !user', $placeholders);
      }
    }
    else {
      if ($use_timeago_date_format == TRUE) {
        $variables['submitted'] = t('!type created !date by !user', $placeholders);
      }
      else {
        $variables['submitted'] = t('!type created @interval ago by !user', $placeholders);
      }
    }
  }

  // Append a feature label to featured node teasers.
  if ($variables['teaser'] && $variables['promote']) {
    $variables['submitted'] .= ' <span class="featured-node-tooltip">' . t('Featured') . ' ' . $variables['type'] . '</span>';
  }
}
