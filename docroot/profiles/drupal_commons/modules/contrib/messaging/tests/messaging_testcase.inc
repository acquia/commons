<?php
// $Id: messaging_testcase.inc,v 1.1.2.1.2.3 2008/12/16 15:00:29 jareyero Exp $ 
/*
 * Base class for Messaging testing
 *  * Created on Mar 18, 2008
 */

class MessagingTestCase extends DrupalWebTestCase {
  var $_messaging_status;
  // Store current status for clean up
  function messagingStartTest() {
    $this->_messaging_status['max_mqid'] = db_result(db_query("SELECT max(mqid) FROM {messaging_store}"));
  }
  // Clean up operations
  function messagingCleanUp() {
    db_query("DELETE FROM {messaging_store} WHERE mqid > %d", $this->_messaging_status['max_mqid']);
  }
  // Create random message
  function randomMessage() {
    $message['subject'] = $this->randomName(50, 'Test subject '); 
    $message['body'] = array(
        'header' => $this->randomName(100, 'Test body header '),
        'main' => $this->randomName(100, 'Test body main '),
        'footer' => $this->randomName(100, 'Test body footer ')
    );
    $message['params'] = array(1, 2);
    return (object)$message;
  }
}

/**
 * Foo callback functions for testing
 */
function messaging_test_foo_message_callback($message, $info) {
  return $message;
}
function messaging_test_foo_getargs_callback() {  
  return func_get_args();
}

