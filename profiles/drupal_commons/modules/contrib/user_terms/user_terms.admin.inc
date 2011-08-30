<?php
// $Id: user_terms.admin.inc,v 1.1.2.1 2010/01/16 15:01:06 joachim Exp $

/**
 * @file
 *   Provides admin pages for the module.
 */

/**
 * The admin form for choosing the vocabulary to associate users with.
 *
 * @return array
 *   The form elements.
 */
function user_terms_settings() {
  $form = array();
  $vocabs = taxonomy_get_vocabularies();

  foreach ($vocabs as $vid => $voc) {
    $options[$vid] = $voc->name;
  }

  $form['user_terms_vocabs'] = array(
    '#type'          => 'select',
    '#title'         => t('User vocabularies'),
    '#options'       => $options,
    '#description'   => t('Choose the vocabularies that will be used to tag users. To select multiple values, hold down the Control key while clicking. If you are using an Apple, hold down the Apple or Command key.'),
    '#default_value' => variable_get('user_terms_vocabs', ''),
    '#multiple'      => TRUE,
  );

  // Only add this option if the profile module is enabled.
  if (module_exists('profile')) {
    $data    = profile_categories();
    $options = array(
      'account' => t('Account (main page)'),
    );

    foreach ($data as $datum) {
      $options[$datum['name']] = $datum['name'];
    }

    $form['user_terms_profile_path'] = array(
      '#type'           => 'select',
      '#title'          => t('Profile page'),
      '#options'        => $options,
      '#description'    => t('The profile category on which vocabularies should appear when the user is editing their profile.'),
      '#default_value'  => variable_get('user_terms_profile_path', 'account'),
    );
  }

  $form['user_terms_group'] = array(
    '#type'         => 'fieldset',
    '#title'        => t('Group terms'),
    '#collapsible'  => FALSE,
  );

    $form['user_terms_group']['user_terms_group_terms'] = array(
      '#type'           => 'checkbox',
      '#title'          => t('Group terms'),
      '#default_value'  => variable_get('user_terms_group_terms', FALSE),
      '#description'    => t('Show all terms from all vocabularies under a single heading, rather than one heading per vocabulary.'),
    );

    $form['user_terms_group']['user_terms_group_title'] = array(
      '#type'           => 'textfield',
      '#title'          => t('Grouped terms heading'),
      '#default_value'  => variable_get('user_terms_group_title', USER_TERMS_GROUP_TITLE),
      '#description'    => t('The text to use as a heading when all terms are grouped.'),
      '#size'           => 32,
    );

  return system_settings_form($form);
}
