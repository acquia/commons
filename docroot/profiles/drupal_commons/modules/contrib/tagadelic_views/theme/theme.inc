<?php
// $Id: theme.inc,v 1.1.2.6 2010/06/26 13:19:36 indytechcook Exp $
/**
 * @file
 * Main views plugin, creates Tagadelic as an option under the Style options when a view is created.
 * Created for Drupal 6 by Mark Fairbairn
 * Reviewed by Nathan Burles
 */
function template_preprocess_views_view_tagadelic(&$vars) {
  $view = $vars['view'];
  
  $options  = $view->style_plugin->options;

  /* Handle Term and Node views */
  switch($view->base_table)
  {
	  case "term_data":
		  $base_field_name = 'td.tid';
		  foreach ($view->result as $term) {
			  $ids[] = $term->tid;
		  }
		  break;
	  case "node":
	  default:
		  $base_field_name = 'n.nid';
		  foreach ($view->result as $node) {
			  $ids[] = $node->nid;
		  }
		  break;
  }
  $base_restrictor = '('. implode(',', $ids) .')';

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
      $vid_restrictor = ' AND td.vid IN ('. implode(',', $vids) .')';
    }
  }
  else {
    $vid_restrictor = '';
  }

  if (!isset($vid_restrictor)) {
    $vars['output'] = 'Could not find '. implode(', ', $vocabs_selected) .'!';
  }
  else {
    $result = db_query_range(db_rewrite_sql(
      'SELECT COUNT(*) AS count, td.tid, td.vid, td.name, td.description ' . 
      'FROM {term_data} td INNER JOIN {term_node} tn ON td.tid = tn.tid ' .
      'INNER JOIN {node} n ON tn.vid = n.vid ' .
      'WHERE ' . $base_field_name . ' IN '. $base_restrictor . $vid_restrictor .
      'GROUP BY td.tid, td.vid, td.name, td.description ' .
      'HAVING COUNT(*) > 0 ' .
      'ORDER BY count DESC'), 0, $options['size']);
    $tags = tagadelic_build_weighted_tags($result, $options['steps']);
    $tags = tagadelic_sort_tags($tags);
    $vars['output'] = theme('tagadelic_weighted', $tags);
    if (empty($vars['output'])) {
      $view->result = NULL;
    }
  }
}