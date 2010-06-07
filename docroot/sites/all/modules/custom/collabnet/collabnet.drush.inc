<?php
// $Id: collabnet.drush.inc

/**
 * Implementation of hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and 
 * description.
 *
 * Notice how this structure closely resembles how 
 * you define menu hooks.
 * 
 * @See drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function collabnet_drush_command() {
  $items = array();

  // the key in the $items array is the name of the command.
  $items['collabnet-send'] = array(
    // the name of the function implementing your command.
    'callback' => 'collabnet_drush_send_queued_messages',
    // a short description of your command
    'description' => "Send the messages in the collabnet queue",
    'arguments' => array(
      'messages' => 'The number of messages to send in this run.  If the argument is not provided all messages will be sent.',
    ),
  );

  // the key in the $items array is the name of the command.
  $items['collabnet-test'] = array(
    // the name of the function implementing your command.
    'callback' => 'collabnet_drush_send_test_message',
    // a short description of your command
    'description' => "Send a test message using the collabnet service test functionality.",
    'arguments' => array(
      'addresses' => 'Email to send a test message to.',
    ),
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function collabnet_drush_help($section) {
  switch ($section) {
    case 'drush:collabnet send':
      return dt("Sends messages from the collabnet queue.");
    case 'drush:collabnet test':
      return dt("Sends a test message using collabnet (this will be queued and sent on the next queue process)");
  }
}

/**
 * Send messages from the collabnet queue. 
 *
 * @param
 *   The number of messages to send from the queue.
 */
function collabnet_drush_send_queued_messages($messages = NULL) {
  $messages_sent = collabnet_process_queue($messages, TRUE);
  if ( ( $messages_sent ) || ( $messages_sent === 0 ) ) { 
    drush_log("Message queue has been processed, " . $messages_sent . " messages sent.", 'completed');
  } else {
    drush_log("Message queue could not be processed.  Check watchdog for errors.", 'failed', TRUE);
  }
}

function collabnet_drush_send_test_message($address) {
  if ( !isset($address) ) {
    drush_log("Cannot send a test message without an address to send to", 'failed', TRUE);
    return FALSE;
  }
  
  $success = collabnet_send_test_message($address);
  if ( $success ) {
    drush_log("Test message has been queued.  It will be sent the next time the queue is processed.", 'completed');
  } else {
    drush_log("Sending a test message failed", 'failed', TRUE);    
  }
  return $success ;
}