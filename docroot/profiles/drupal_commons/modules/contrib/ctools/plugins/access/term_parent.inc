<?php
// $Id: term_parent.inc,v 1.1.2.1 2010/04/14 20:35:39 merlinofchaos Exp $

/**
 * @file
 * Plugin to provide access control based upon a parent term.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Taxonomy: parent term"),
  'description' => t('Control access by existence of a parent term.'),
  'callback' => 'ctools_term_parent_ctools_access_check',
  'default' => array('vid' => array(), 'negate' => 0),
  'settings form' => 'ctools_term_parent_ctools_access_settings',
  'settings form validation' => 'ctools_term_parent_ctools_access_settings_validate',
  'settings form submit' => 'ctools_term_parent_ctools_access_settings_submit',
  'summary' => 'ctools_term_parent_ctools_access_summary',
  'required context' => new ctools_context_required(t('Term'), array('term', 'terms')),
);

/**
 * Settings form for the 'by parent term' access plugin
 */
function ctools_term_parent_ctools_access_settings(&$form, &$form_state, $conf) {
  // If no configuration was saved before, set some defaults.
  if (empty($conf)) {
    $conf = array(
      'vid' => 0,
      'negate' => 0,
    );
  }
  if (!isset($conf['vid'])) {
    $conf['vid'] = 0;
    $conf['negate'] = 0;
  }

  $form['settings']['vid'] = array(
    '#title' => t('Vocabulary'),
    '#type' => 'select',
    '#options' => array(),
    '#description' => t('Select the vocabulary for this form. If there exists a parent term in that vocabulary, this access check will succeed.'),
    '#id' => 'ctools-select-vid',
    '#default_value' => $conf['vid'],
    '#required' => TRUE,
  );

  $options = array();

  // Loop over each of the configured vocabularies.
  foreach (taxonomy_get_vocabularies() as $vid => $vocabulary) {
    $options[$vid] = $vocabulary->name;
  }
  $form['settings']['vid']['#options'] = $options;


  $form['settings']['negate'] = array(
    '#title' => t('Negate'),
    '#type' => 'radios',
    '#options' => array(0 => t('Has parent term'), 1 => t('Does not have parent term')),
    '#description' => t('Negate this selection. If you chose "does not have parent term" and there does not exist a parent term in that vocabulary, this access check will succeed.'),
    '#default_value' => $conf['negate'],
  );
}

/**
 * Check for access.
 */
function ctools_term_parent_ctools_access_check($conf, $context) {
  // As far as I know there should always be a context at this point, but this
  // is safe.
  if (empty($context) || empty($context->data) || empty($context->data->vid) || empty($context->data->tid)) {
    return FALSE;
  }

  // Get the $vid.
  if (!isset($conf['vid'])) {
    return FALSE;
  }
  $vid = $conf['vid'];

  $count = db_query('SELECT COUNT(*) FROM {term_hierarchy} th INNER JOIN {term_data} td ON th.parent = td.tid WHERE th.parent = %d AND td.vid = %d',  $context->data->tid, $vid);

  if ($conf['negate']) {
    return $count ? FALSE : TRUE;
  }
  else {
    return $count ? TRUE : FALSE;
  }
}

/**
 * Provide a summary description based upon the checked terms.
 */
function ctools_term_parent_ctools_access_summary($conf, $context) {
  $vocab = taxonomy_vocabulary_load($conf['vid']);

  if ($conf['negate']) {
    return t('"@term" has no parent in vocabulary "@vocab"', array('@term' => $context->identifier, '@vocab' => $vocab->name));
  }
  else {
    return t('"@term" has parent in vocabulary "@vocab"', array('@term' => $context->identifier, '@vocab' => $vocab->name));
  }
}
