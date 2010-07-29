<?php
// $Id: views_plugin_style_tagadelic.inc,v 1.1.2.1 2009/01/30 00:12:49 indytechcook Exp $
class views_plugin_style_tagadelic extends views_plugin_style {
  function option_definition() {
    $options = parent::option_definition();
    $options['steps'] = array('default' => '6');
    $options['size'] = array('default' => '500');
    $options['vocab'] = array('default' => '');
    return $options;
  }
  
  function options(&$options) {
    parent::options($options);
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['steps'] = array(
      '#type' => 'textfield',
      '#title' => t('Variation in weight, higher is more.'),
      '#default_value' => $this->options['steps'],
    );
    $form['size'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of results to give.'),
      '#default_value' => $this->options['size'],
    );
    $form['vocab'] = array(
      '#type' => 'textfield',
      '#title' => t('Vocabs to use.'),
      '#default_value' => $this->options['vocab'],
    );
  }
}