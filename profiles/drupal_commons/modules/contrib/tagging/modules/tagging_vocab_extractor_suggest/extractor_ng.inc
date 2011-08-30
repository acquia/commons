<?php
// $Id$

/**
 * @file:
 * Simple term extraction.
 */

/**
 * Finds tags in text.
 */
function extractor_ng_extract($text) {
  $text = strip_tags($text);
  $words = _extractor_ng_split($text);
  $vid = variable_get('extractor_ng_vid', 1);
  $result = array();
  for ($pos = 0; $pos < count($words); $pos++) {
    $term_names = $term_tids = $terms = array();
    $word = $words[$pos];

    // 1) get all terms any synonyms that start with this word.
    foreach (_extractor_ng_lookup($word) as $term) {
      $term_tids[$term->name] = $term->tid;
      $term_names[$term->name] = $term->name;
    }

    // Skip to immediate loop if no results.
    if (!count($term_tids)) {
      continue;
    }

    // 2) Order result by length desc.
    $sorted = FALSE;
    $sorted_terms = array_values($term_names);

    while (!$sorted) {
      $sorted = TRUE;
      for ($i = 0; $i < count($sorted_terms) - 1; $i++) {
        if (strlen($sorted_terms[$i]) < strlen($sorted_terms[$i+1])) {
          $tmp = $sorted_terms[$i+1];
          $sorted_terms[$i+1] = $sorted_terms[$i];
          $sorted_terms[$i] = $tmp;
          $sorted = FALSE;
        }
      }
    }
    foreach ($sorted_terms as $term) {
      $result[$term_tids[$term]] = $term_names[$term];
    }
  }

  return $result;
}

/**
 * Split text into words.
 */
function _extractor_ng_split($text) {
  $tmp = preg_split("/[\s,.:\-\(\)\[\]{}*\/]+/", $text);
  
  $result = array();
  $max_word_count = variable_get('tagging_vocab_extractor_suggest_max_word_count', 4);

  foreach($tmp as $key => $word) {
	$result[] = $word;
 	for($i = 1;$i <=$max_word_count;$i++) {
		if(array_key_exists(($key+$i),$tmp)) {
			$word = "$word {$tmp[$key+$i]}";
			$result[] = $word;
		}
	}	
  }
  
  return $result;
}

/**
 * Look up terms for a given word. Supports up to 2000 terms.
 */
function _extractor_ng_lookup($word) {
  // Do not bother if word starts with a numeric or if word is in stop word list.
  if (is_numeric($word[0]) || in_array($word, _extractor_ng_stopwords())) {
    return array();
  }
  $terms = array();
  // COLLATE utf8_bin for cs
  $result = db_query('SELECT td.tid, td.name FROM {term_data} as td LEFT JOIN {term_synonym} as ts on ts.tid=td.tid WHERE td.vid = %d AND ( td.name COLLATE utf8_bin ="%s" OR ts.name COLLATE utf8_bin ="%s" )', variable_get('extractor_ng_vid', 1), $word, $word );
  while ($term = db_fetch_object($result)) {
    $terms[$term->tid] = $term;
  }

  return $terms;
}

/**
 * Stop words.
 */
function _extractor_ng_stopwords() {
  return array('a', 'able', 'about', 'across', 'after', 'all', 'almost', 'also', 'am', 'among', 'an', 'and', 'any', 'are', 'as', 'at', 'be', 'because', 'been', 'but', 'by', 'can', 'cannot', 'could', 'dear', 'did', 'do', 'does', 'either', 'else', 'ever', 'every', 'for', 'from', 'get', 'got', 'had', 'has', 'have', 'he', 'her', 'hers', 'him', 'his', 'how', 'however', 'i', 'if', 'in', 'into', 'is', 'it', 'its', 'just', 'least', 'let', 'like', 'likely', 'may', 'me', 'might', 'most', 'must', 'my', 'neither', 'no', 'nor', 'not', 'of', 'off', 'often', 'on', 'only', 'or', 'other', 'our', 'own', 'rather', 'said', 'say', 'says', 'she', 'should', 'since', 'so', 'some', 'than', 'that', 'the', 'their', 'them', 'then', 'there', 'these', 'they', 'this', 'tis', 'to', 'too', 'twas', 'us', 'wants', 'was', 'we', 'were', 'what', 'when', 'where', 'which', 'while', 'who', 'whom', 'why', 'will', 'with', 'would', 'yet', 'you', 'your');
}
