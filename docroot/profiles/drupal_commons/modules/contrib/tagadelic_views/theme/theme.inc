<?php
// $Id: theme.inc,v 1.1.2.3 2009/10/05 13:07:19 indytechcook Exp $
/**
 * @file
 * Main views plugin, creates Tagadelic as an option under the Style options when a view is created.
 * Created for Drupal 6 by Mark Fairbairn
 * Reviewed by Nathan Burles
 */
function template_preprocess_views_view_tagadelic(&$vars) {
  $view = $vars['view'];
  
  $options  = $view->style_plugin->options;

  foreach ($view->result as $node) {
    $nids[] = $node->nid;
  }
  $nid_restrictor = '('. implode(',', $nids) .')';

  if ($options['vocab'] != '') {
    $vocabs_selected = split(',', $options['vocab']);
    $taxonomy_vocabs = array();
    foreach (taxonomy_get_vocabularies() as $vocab) {
      $taxonomy_vocabs[$vocab->vid] = $vocab->name;
    }
    foreach ($vocabs_selected as $key => &$vocab) {
      $vocab = trim($vocab);
      if ($vocab == '') {
        array_splice($vocabs_selected, $key, 1);
      };
    }
    $vocabs_to_use = array_intersect($taxonomy_vocabs, $vocabs_selected);
    foreach (array_keys($vocabs_to_use) as $vocabid) {
      $vids[] = $vocabid;
    }

    if (isset($vids)) {
      $vid_restrictor = ' AND d.vid IN ('. implode(',', $vids) .')';
    }
  }
  else {
    $vid_restrictor = '';
  }

  if (!isset($vid_restrictor)) {
    $vars['output'] = 'Could not find '. implode(', ', $vocabs_selected) .'!';
  }
  else {
    $result = db_query_range('SELECT COUNT(*) AS count, d.tid, d.name, d.vid FROM {term_data} d INNER JOIN {term_node} n ON d.tid = n.tid WHERE n.nid IN '. $nid_restrictor . $vid_restrictor .' GROUP BY d.tid, d.name, d.vid ORDER BY count DESC', 0, $options['size']);
    $tags = tagadelic_build_weighted_tags($result, $options['steps']);
    $tags = tagadelic_sort_tags($tags);
    if (!empty($vars['output'])) {
      $view->result= NULL;
    }
    $vars['output'] = theme('tagadelic_weighted', $tags);
  }
}