<?php
// $Id: node_form_buttons.inc,v 1.1.2.1 2010/01/29 20:18:25 merlinofchaos Exp $

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'icon' => 'icon_node_form.png',
  'title' => t('Node form submit buttons'),
  'description' => t('Submit buttons for the node form.'),
  'required context' => new ctools_context_required(t('Form'), 'node_form'),
  'category' => t('Form'),
);

function ctools_node_form_buttons_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('node_form');

  $block->title = '';
  $block->delta = 'buttons';

  if (isset($context->form)) {
    $block->content = drupal_render($context->form['buttons']);
  }
  else {
    $block->content = t('Node form buttons.');
  }
  return $block;
}

function ctools_node_form_buttons_content_type_admin_title($subtype, $conf, $context) {
  return t('"@s" node form submit buttons', array('@s' => $context->identifier));
}

function ctools_node_form_buttons_content_type_edit_form(&$form, &$form_state) {
  // provide a blank form so we have a place to have context setting.
}
