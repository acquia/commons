<?php

/**
 * @file
 *   Rules integration default configuration for Facebook-style Micropublisher.
 */

/**
 * Implementation of hook_rules_defaults().
 */
function fbsmp_rules_defaults() {
  $config = array (
  'rules' => 
  array (
    'fbsmp_delete_status_rules' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_fbsmp_delete_status',
      '#label' => 'Delete FBSS status having FBSMP Link attachment',
      '#active' => 1,
      '#weight' => '0',
      '#categories' => 
      array (
        0 => 'fbsmp',
      ),
      '#status' => 'default',
      '#conditions' => 
      array (
        0 => 
        array (
          '#type' => 'condition',
          '#settings' => 
          array (
            '#argument map' => 
            array (
              'attachment' => 'attachment',
            ),
          ),
          '#name' => 'fbsmp_attachment_is_link',
          '#info' => 
          array (
            'label' => 'The FBSS status has Link attachment',
            'arguments' => 
            array (
              'plugin' => 
              array (
                'type' => 'value',
                'default value' => 'link',
              ),
              'attachment' => 
              array (
                'type' => 'fbsmp',
                'label' => 'The FBSMP attachment object.',
              ),
            ),
            'base' => 'fbsmp_check_attachment_condition',
            'module' => 'Facebook-style Micropublisher',
          ),
          '#weight' => 0,
        ),
      ),
      '#actions' => 
      array (
        0 => 
        array (
          '#weight' => 0,
          '#info' => 
          array (
            'label' => 'Show a configurable message on the site',
            'module' => 'System',
            'eval input' => 
            array (
              0 => 'message',
            ),
          ),
          '#name' => 'rules_action_drupal_message',
          '#settings' => 
          array (
            'message' => 'Link deleted.',
            'error' => 0,
          ),
          '#type' => 'action',
        ),
      ),
      '#version' => 6003,
    ),
  ),
);
  return $config;
}