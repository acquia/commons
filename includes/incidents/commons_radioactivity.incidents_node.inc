<?php

/**
* Implements hook_node_update().
*/
function commons_radioactivity_node_update($node) {
  // If there are no groups associated with this node
  // then there's nothing to do here.
  if (!isset($node->og_group_ref)) {
    return;
  }
  if ($node->og_group_ref !== $node->original->og_group_ref) {
    commons_radioactivity_process_node_group_membership_change($node);
  }
}