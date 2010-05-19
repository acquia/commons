<?php
// $Id: user_relationships-actions_block.tpl.php,v 1.1.2.5 2008/10/30 12:49:33 alexk Exp $
/**
 * @file 
 * Template of relationships add/remove block
 * List of current relationships to the viewed user
 */
$output = array();

if ($current_relationships) {
  $output[] = theme('item_list', $current_relationships, t('Your relationships to this user'), 'ul', array('class' => 'user_relationships'));
}

// List of actions that can be taken between the current and viewed user
if ($actions) {
  $output[] = theme('item_list', $actions, t('Relationship actions'), 'ul', array('class' => 'user_relationships_actions'));
}

print implode('', $output);

?>