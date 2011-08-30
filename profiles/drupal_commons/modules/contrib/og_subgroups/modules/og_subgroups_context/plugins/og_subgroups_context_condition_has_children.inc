<?php

define('OG_SUBGROUPS_CONTEXT_NO_CHILDREN', 0);
define('OG_SUBGROUPS_CONTEXT_HAS_CHILDREN', 1);

/**
 * Enable OG Subgroups to trigger a condition based on whether or not 
 * the current group has children
 */
class og_subgroups_context_condition_has_children extends context_condition {

  /**
   * Condition form
   */
  function condition_form($context) {
    $default = $this->fetch_from_context($context, 'values');
    if ($default) {
      $default = array_shift($default); 
    }
    return array(
      'og_subgroups_context_has_children' => array(
        '#title' => $this->title,
        '#type' => 'radios',
        '#options' => array(
          OG_SUBGROUPS_CONTEXT_NO_CHILDREN => t('Does not have children'),
          OG_SUBGROUPS_CONTEXT_HAS_CHILDREN => t('Has children'),
        ),
        '#description' => $this->description,
        '#default_value' => $default ? $default : OG_SUBGROUPS_CONTEXT_NO_CHILDREN,
      ),
    );
  }
  
  /**
   * Condition form submit handler.
   */
  function condition_form_submit($values) {
    return drupal_map_assoc($values);
  }

  /**
   * Execute the plugin
   */
  function execute() {
    if ($this->condition_used()) {
      // Determine the group we're in
      if ($group = og_subgroups_context_current_group()) {
        foreach ($this->get_contexts($value) as $context) {
          og_subgroups_include('tree');
          
          // Extract the chosen setting
          $setting = array_shift($context->conditions['og_subgroups_context_condition_has_children']['values']);
          
          // Evaluate the setting
          switch ($setting) {
            case OG_SUBGROUPS_CONTEXT_NO_CHILDREN:
              if (!og_subgroups_get_group_children($group)) {
                $this->condition_met($context, $value);
              }
              break;
              
            case OG_SUBGROUPS_CONTEXT_HAS_CHILDREN:
              if (og_subgroups_get_group_children($group)) {
                $this->condition_met($context, $value);
              }
              break;
          }
        }
      }
    }
  }
}
