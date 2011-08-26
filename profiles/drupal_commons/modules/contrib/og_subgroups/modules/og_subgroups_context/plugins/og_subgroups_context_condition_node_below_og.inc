<?php

/**
 * Enable OG Subgroups to trigger a condition based on node's position
 * below the OG defined in the condition.
 */
class og_subgroups_context_condition_node_below_og extends context_condition {

  /**
   * Condition values
   */
  function condition_values() {
    og_subgroups_include('form');
    // Load the options with hierarchy indents
    $values = og_subgroups_group_select_options();
    // Remove the default first option (no group)
    if (isset($values[0])) {
      unset($values[0]);
    }
    return $values;
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
          
          // Get groups selected in our conditions when context was defined.
          $selected = $context->conditions['og_subgroups_context_condition_node_below_og']['values'];

          // Iterate each of the selected groups
          foreach ($selected as $pid) {
            // Build a parent object to pass
            $parent = new stdClass;
            $parent->nid = $pid;
            // See if the current group is a child of the parent
            if (og_subgroups_group_is_child($parent, $group)) {
              // Activate the context
              $this->condition_met($context, $parent->nid);
              // Stop here
              break;
            }
          }
        }
      }
    }
  }
}
