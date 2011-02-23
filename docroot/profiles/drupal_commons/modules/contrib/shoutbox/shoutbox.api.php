<?php
// $Id: shoutbox.api.php,v 1.1.2.1 2011/02/22 16:42:27 mikestefff Exp $

/**
 * Implementation of hook_shoutbox()
 * 
 * See shoutbox_group for a detailed example
 * 
 * @param $op
 *   The current operation (see code below)
 * @param $shout
 *   The shout object used in the operation
 * @param $a1
 *   An additional parameter that contains data based on the operation
 * @param $form_state
 *   The form state of the shout form. Usually only used on the shoutbox form.
 *   Modules like shoutbox_group attach extra data to the form with a form_alter.
 */
function hook_shoutbox($op, &$shout, &$a1 = NULL, $form_state = NULL) {
  switch ($op) {
    case 'insert':
      // A shout was just added
      break;
      
    case 'presave':
      // A shout is about to be saved
      // ********** IMPORTANT**********
      // If it recommended that in presave, you set $shout->module to the name of your
      // module. This will prevent shoutbox from displaying your module's shouts on
      // general shoutboxes - unless that is what is desired.
      break;
    
    case 'edit':
      // An edited shout is about to be saved
      break;
      
    case 'view':
      // A shout is about to be viewed
      break;
      
    case 'unpublish':
      // A shout is being unpublished
      // Will not be called if a shout is initially saved unpublished
      break;
      
    case 'publish':
      // A shout is being published
      // Will not be called if a shout is initially saved published
      break;
    
    case 'delete':
      // A shout was just removed
      break;
      
    case 'link':
      // Alter the link to the shoutbox page
      $a1 = 'shoutbox/something/custom';
      break;
      
    case 'form':
      // Alter the shoutbox add form
      $a1['new_field'] = array('#type' => 'textbox', etc);
      break;
      
    case 'js path':
      // Alter the AJAX callback path
      $a1 = 'something/js/callback';
      break;
      
    case 'query':
      // Alter the database query used to fetch shouts
      $a1 = "SELECT s.* FROM {shoutbox} s INNER JOIN ....";
      break;
  }
}
