<?php
// $Id: user_terms_handler_field_term_user_tid.inc,v 1.1.2.5 2010/02/05 22:06:04 joachim Exp $

/**
 * Field handler for terms. 
 *
 * Inherits from views_handler_field_term_node_tid, but we have to be careful
 * not to inherit stuff that is specific to {node} and {node_revisions} tables.
 */
class user_terms_handler_field_term_user_tid extends views_handler_field_term_node_tid {
  function init(&$view, $options) {
    // Call the *GRANDPARENT* init, because we don't want the additional fields
    // that our parent class views_handler_field_term_node_tid adds.
    views_handler_field_prerender_list::init($view, $options);
    
    // Add the uid field to we're guaranteed it when this field is on a view 
    // whose base is other than user.
    $this->additional_fields['uid'] = array(
      'table' => 'users', 
      'field' => 'uid'
    );    
  }

  /**
   * Use the parent form, but only show the vocabs that apply to users.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Remove from the form the vocabularies that aren't used on users.
    $user_terms_vocabularies = variable_get('user_terms_vocabs', array());
    foreach ($form['vids']['#options'] as $key => $value) {
      if (!$user_terms_vocabularies[$key]) {
        unset($form['vids']['#options'][$key]);
      }
    }
  }

  /**
   * Fake field: don't query.
   */
  function query() {
    $this->add_additional_fields();
  }

  /**
   * Loads all terms and builds an array of items with the uid as index.
   */
  function pre_render($values) {
    $this->field_alias = $this->aliases['uid'];

    $uids = array();
    foreach ($values as $result) {
      $uids[$result->{$this->aliases['uid']}] = $result->{$this->aliases['uid']};
    }
    
    // Filter out the anonymous users: they can have no terms.
    $uids = array_filter($uids);

    if ($uids) {
      $voc = '';
      if (!empty($this->options['limit']) && !empty($this->options['vids'])) {
        $voc = " AND td.vid IN (" . implode(', ', array_keys(array_filter($this->options['vids']))) . ")";
      }

      $tids_string = implode(',', $uids);
      $result = db_query("SELECT td.*, tu.uid, v.name as vocabulary FROM {term_data} td INNER JOIN {term_user} tu ON td.tid = tu.tid INNER JOIN {vocabulary} v ON v.vid = td.vid WHERE tu.uid IN ($tids_string) $voc ORDER BY td.weight, td.name");
  
      while ($term = db_fetch_object($result)) {
        $this->items[$term->uid][$term->tid]['name'] = check_plain($term->name); 
        $this->items[$term->uid][$term->tid]['tid'] = $term->tid;
        $this->items[$term->uid][$term->tid]['vid'] = $term->vid;
        $this->items[$term->uid][$term->tid]['vocabulary'] = check_plain($term->vocabulary);
          
        if (!empty($this->options['link_to_taxonomy'])) {
          $this->items[$term->uid][$term->tid]['make_link'] = TRUE;
          $this->items[$term->uid][$term->tid]['path'] = taxonomy_term_path($term);
        }
      }
    }
  }
  
  function render_item($count, $item) {
    return $item['name'];
  }  

  function document_self_tokens(&$tokens) {
    $tokens['[' . $this->options['id'] . '-tid' . ']'] = t('The taxonomy term ID for the term.');
    $tokens['[' . $this->options['id'] . '-name' . ']'] = t('The taxonomy term name for the term.');
    $tokens['[' . $this->options['id'] . '-vid' . ']'] = t('The vocabulary ID for the vocabulary the term belongs to.');
    $tokens['[' . $this->options['id'] . '-vocabulary' . ']'] = t('The name for the vocabulary the term belongs to.');
  }

  function add_self_tokens(&$tokens, $item) {
    $tokens['[' . $this->options['id'] . '-tid' . ']'] = $item['tid'];
    $tokens['[' . $this->options['id'] . '-name' . ']'] = $item['name'];
    $tokens['[' . $this->options['id'] . '-vid' . ']'] = $item['vid'];
    $tokens['[' . $this->options['id'] . '-vocabulary' . ']'] = $item['vocabulary'];
  }
}
