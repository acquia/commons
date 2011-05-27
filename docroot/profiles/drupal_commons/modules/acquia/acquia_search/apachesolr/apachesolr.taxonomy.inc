<?php

/**
 * @file
 *   Administrative pages for the Apache Solr framework regarding taxonomy.
 */

/**
 * Overrides taxonomy/term/X links
 */
function apachesolr_search_taxonomy_term_page($str_tids = '', $depth = 0, $op = 'page') {
  $terms = taxonomy_terms_parse_string($str_tids);
  if ($terms['operator'] != 'and' && $terms['operator'] != 'or') {
    drupal_not_found();
  }

  if ($terms['tids']) {
    $result = db_query(db_rewrite_sql('SELECT t.tid, t.name FROM {term_data} t WHERE t.tid IN (' . db_placeholders($terms['tids']) . ')', 't', 'tid'), $terms['tids']);
    $tids = array(); // we rebuild the $tids-array so it only contains terms the user has access to.
    $names = array();
    while ($term = db_fetch_object($result)) {
      $tids[] = $term->tid;
      $names[] = $term->name;
    }

    if ($names) {
      $term = taxonomy_get_term($tids[0]);

      // Only support one term, only page callbacks, and only depth = 0 (because of way Solr indexing works)
      // Check if term belongs to vocabulary selected by admin as an available filter
      if (user_access('search content') && count($terms['tids']) == 1 && $op == 'page' && $depth == 0 && in_array('im_vid_' . $term->vid, apachesolr_get_enabled_facets('apachesolr_search'))) {
        $title = implode(', ', $names);
        drupal_set_title(check_plain($title));

        // Build breadcrumb based on first hierarchy of first term:
        $current = new stdClass();
        $current->tid = $tids[0];
        $breadcrumb = array();
        while ($parents = taxonomy_get_parents($current->tid)) {
          $current = array_shift($parents);
          $breadcrumb[] = l($current->name, 'taxonomy/term/' . $current->tid);
        }
        $breadcrumb[] = l(t('Home'), NULL);
        $breadcrumb = array_reverse($breadcrumb);
        drupal_set_breadcrumb($breadcrumb);

        $_GET['retain-filters'] = 1; //??
        module_load_include('inc', 'search', 'search.pages');

        try {
          $data = apachesolr_search_execute('', 'tid:' . $tids[0], variable_get('apachesolr_search_taxonomy_sort', 'created desc'), 'search/apachesolr_search', isset($_GET['page']) ? $_GET['page'] : 0);
        }
        catch (Exception $e) {
          watchdog('Apache Solr', nl2br(check_plain($e->getMessage())) . ' in apachesolr_search_taxonomy_term_page', NULL, WATCHDOG_ERROR);
          // Fallback to normal taxonomy/term page
          require_once(drupal_get_path('module', 'taxonomy') .'/taxonomy.pages.inc');
          return taxonomy_term_page($str_tids, $depth, $op);
        }

        $results = theme('search_results', $data, 'apachesolr_search');
        if ($results) {
          $results = theme('box', t('Results for %term', array('%term' => $term->name)), $results);
        }
        else {
          $results = theme('box', t('Your search yielded no results'), variable_get('apachesolr_search_noresults', apachesolr_search_noresults()));
        }

        drupal_add_feed(url('taxonomy/term/' . $str_tids . '/' . $depth . '/feed'), 'RSS - '. $title);
        return drupal_get_form('search_form', NULL, '', 'apachesolr_search') . $results;
      }

      // Fallback to normal taxonomy/term page
      require_once(drupal_get_path('module', 'taxonomy') .'/taxonomy.pages.inc');
      return taxonomy_term_page($str_tids, $depth, $op);
    }
    else {
      drupal_not_found();
    }
  }
}
