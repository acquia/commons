<?php
// $Id: og_statistics.faceted_search.inc,v 1.2.2.1 2009/08/12 19:56:41 dereine Exp $

/**
 * @file
 *   Integration of og_statistics into faceted_search.
 *
 * @TODO
 *   Add every statistic field for the sort availible.
 */

/**
 * Implementation of hook_form_alter().
 */
function og_statistics_form_faceted_search_edit_form_alter(&$form, &$form_state) {
  $env_id = $form['env_id']['#value'];
  //    drupal_set_message('Faceted_search alter :'.var_export($form['info'], true));
  $form['info']['name']['#weight'] = -5;
  $form['info']['title']['#weight'] = -4;
  $form['info']['description']['#weight'] = -3;
  $form['info']['types']['#weight'] = -2;
  $form['info']['og_statistics_sort'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sort by number of group nodes'),
    '#default_value' => faceted_search_variable_get($env_id, 'og_statistics_sort', FALSE),
    '#description' => t('If <em>only</em> searching group content types enables sorting by the most recent node added to the group, rather than comment added to the group node itself.'),
    '#weight' => -1,
  );
}
}

/**
 * Implementation of hook_faceted_search_query_alter().
 *
 * This is quite late in the sequence, but were altering a facet
 * (the content-type one) rather than making a new one we could hook
 * in the sort(s) to. 
 * @todo I guess there is a much better way of doing this! Like
 * maybe inheriting content-type facet and extending it and making it
 * sort an option?
 */
function og_statistics_faceted_search_query_alter($search, &$query) {
  if (faceted_search_variable_get($search->_env_id, 'og_statistics_sort', FALSE)) { // change for a variable
    $query->tables['default']['c']['table'] = 'og_statistics';
    $query->fields['default']['score']['field'] = '%d * POW(2, (GREATEST(MAX(n.created), MAX(n.changed), MAX(c.last_node_timestamp)) - %d) * 6.43e-8)';
  }
}

