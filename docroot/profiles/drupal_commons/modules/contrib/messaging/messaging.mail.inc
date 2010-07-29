<?php
// $Id: messaging.mail.inc,v 1.1.2.1.2.1 2009/06/13 14:49:13 jareyero Exp $
/**
 * @file
 *   Common library for mail methods
 * 
 * This is the only non method agnostic functionality in this module. As there are several plug-ins
 * for mail sending, we add this helper function here so its available for all them.
 */

/**
 * Rebuild message in Drupal mail format
 * 
 * @param $destination
 *   Email destination
 * @param $message
 *   Message object
 * @param $params
 *   Aditional parameters
 * @param $alter
 *   Whether to run the mail_alter hook
 */
function messaging_mail_prepare($destination, $message, $params, $alter = TRUE) {

  // The message 'from' will depend on message sender if present, otherwise default to site mail
  $default_from = variable_get('site_mail', ini_get('sendmail_from'));
  
  if (empty($params['from'])) {
    if (!empty($message->sender_account) && !empty($message->sender_account->mail)) {
      $from = check_plain($message->sender_account->name) . ' <'.$message->sender_account->mail.'>';
    } elseif(!empty($message->sender_name) && $default_from) {
      $from = check_plain($message->sender_name) . ' <'.$default_from.'>';
    } else {
      $from = $default_from;
    }
    $params['from'] = $from;
  } else {
    $from = $params['from'];
  }

  // Build the mail object, mimic drupal_mail() format
  $mail = array(
    'id'       => 'messaging_'. (!empty($message->type) ? 'message-'.$message->type : 'message'),
    'to'       => $destination,
    'from'     => $from,
    'language' => !empty($message->language) ? $message->language : language_default(),
    'params'   => $params,
    'subject'  => $message->subject,
    'body'     => $message->body,
    'headers'  => messaging_mail_headers($message, $params),
    'attachments' => !empty($message->files) ? $message->files : array(),
  );  

  // Invoke hook_mail_alter() to allow all modules to alter the resulting e-mail.
  if ($alter) {
    drupal_alter('mail', $mail);
  }
  return $mail;
}

/**
 * Get mail headers. Helper function for mail methods
 * 
 */
function messaging_mail_headers($message, $params) {
  
  $headers = !empty($params['headers']) ? $params['headers'] : array();
  
  // Add some default headers
  $headers += array(
    'MIME-Version'              => '1.0',
    'Content-Type'              => 'text/plain; charset=UTF-8; format=flowed; delsp=yes',
    'Content-Transfer-Encoding' => '8Bit',
    'X-Mailer'                  => 'Drupal'
  );
  
  $default_from = variable_get('site_mail', ini_get('sendmail_from'));
  $from = !empty($params['from']) ? $params['from'] : $default_from;

  // Set default headers depending on data
  $headers += array(
    'From' => $from,
    'Reply-To' => $from,
  );
  
  if ($default_from) {
    // To prevent e-mail from looking like spam, the addresses in the Sender and
    // Return-Path headers should have a domain authorized to use the originating
    // SMTP server. Errors-To is redundant, but shouldn't hurt.
    $more_headers['Sender'] = $more_headers['Return-Path'] = $more_headers['Errors-To'] = $default_from;
    $headers += $more_headers;
  }  

  return $headers;
}
