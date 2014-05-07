<?php

/**
 * @file
 * Menu callbacks for the Commons Follow UI pages.
 */

/**
 * Form callback for configuring notification settings.
 */
function commons_follow_ui_notification_settings_form($form, &$form_state, $account) {
  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $account->uid,
  );

  $form['explanation'] = array(
    '#markup' => '<p>' . t("Control how you are notified of new content and activity. When you follow a group, topic, user, or other content, you'll see updates in your content and activity streams, and you will automatically get email updates unlesss you disable emails or unfollow.") . '</p>',
  );

  $form['message_subscribe_email'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send email notifications by default.'),
    '#description' => t("If checked, you'll automatically sign up for email notifications when you follow something. Leave unchecked to default to signing up only for activity stream notifications"),
    '#ajax' => array(
      'callback' => 'commons_follow_message_subscribe_email_setting_submit',
    ),
    '#default_value' => isset($account->message_subscribe_email[LANGUAGE_NONE][0]['value']) ? $account->message_subscribe_email[LANGUAGE_NONE][0]['value'] : FALSE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save email notification settings'),
    '#attributes' => array(
      'class' => array('js-hide'),
    ),
  );

  $tabs = commons_follow_ui_generate_tabs($account);

  $form['tabs'] = array(
    '#markup' => drupal_render($tabs),
  );

  $form['#submit'][] = 'commons_follow_message_subscribe_email_setting_submit';

  return $form;
}

/**
 * Submit handler for commons_follow_ui_notification_settings_form().
 */
function commons_follow_message_subscribe_email_setting_submit($form, &$form_state) {
  // Save any changes to the email notifications setting.
  if ($form_state['values']['message_subscribe_email'] != $form['message_subscribe_email']['#default_value']) {
    $account = user_load($form_state['values']['uid']);
    $account->message_subscribe_email[LANGUAGE_NONE][0]['value'] = $form_state['values']['message_subscribe_email'];
    user_save($account);
  }
}
