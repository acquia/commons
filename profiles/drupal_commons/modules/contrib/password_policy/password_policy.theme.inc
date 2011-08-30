<?php
// $Id: password_policy.theme.inc,v 1.4 2010/03/15 17:24:08 deekayen Exp $
/**
 * @file
 * Theme callback file for the password_policy module.
 */

//////////////////////////////////////////////////////////////////////////////
// Password policy admin themes

/**
 * Custom theme for rendering a radio list of defined policies.
 * This layout is based on a similar layout found in the "filter" module.
 *
 * @ingroup themeable
 */
function theme_password_policy_admin_list($form) {
  $rows = array();
  foreach ($form as $pid => $element) {
    if (isset($element['edit']) && is_array($element['edit'])) {
      $rows[] = array(
        check_plain($form[$pid]['name']['#value']),
        $form[$pid]['roles']['#value'],
        drupal_render($form['enabled'][$pid]),
        drupal_render($form['weight'][$pid]),
        drupal_render($form[$pid]['view']),
        drupal_render($form[$pid]['edit']),
        drupal_render($form[$pid]['delete'])
      );
      unset($form[$pid]);
    }
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => t('No policies defined.'), 'colspan' => 5));
    unset($form['submit']);
    unset($form['clear']);
  }
  $header = array(t('Policy'), t('Roles'), t('Enabled'), t('Weight'), array('data' => t('Operations'), 'colspan' => 3));
  $output = theme('table', $header, $rows);
  $output .= drupal_render($form);

  return $output;
}

