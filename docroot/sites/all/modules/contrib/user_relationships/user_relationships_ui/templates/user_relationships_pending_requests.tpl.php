<?php
// $Id: user_relationships_pending_requests.tpl.php,v 1.1.2.8 2009/10/15 15:23:26 aufumy Exp $
/**
 * @file
 * Page to manage sent and received relationship requests
 */

  $output = '';
  $pager_id = 0;
  $section_headings = array(
    'sent_requests'     => t('Sent Requests'),
    'received_requests' => t('Received Requests')
  );

  foreach ($sections as $column => $section) {
    if (!$$section) { continue; }
    $rows = array();

    $rows[] = array(
      array('data' => $section_headings[$section], 'header' => TRUE, 'colspan' => 2)
    );

    foreach ($$section as $relationship) {
      $links = array();
      if ($section == 'sent_requests') {
        $links[] = theme('user_relationships_pending_request_cancel_link', $account->uid, $relationship->rid);
      }
      else {
        $links[] = theme('user_relationships_pending_request_approve_link',    $account->uid, $relationship->rid);
        $links[] = theme('user_relationships_pending_request_disapprove_link', $account->uid, $relationship->rid);
      }
      $links = implode(' | ', $links);

      if ($relationship->requester_id == $account->uid) {
        $rows[]   = array(t('@rel_name to !requestee', array('@rel_name' => ur_tt("user_relationships:rtid:$relationship->rtid:name", $relationship->name), '!requestee' => theme('username', $relationship->requestee))), $links);
      }
      else {
        $rows[]   = array(t('@rel_name from !requester', array('@rel_name' => ur_tt("user_relationships:rtid:$relationship->rtid:name", $relationship->name), '!requester' => theme('username', $relationship->requester))), $links);
      }
    }

    $output .=
      theme('table', array(), $rows, array('class' => 'user-relationships-pending-listing-table')).
      theme('pager', NULL, $relationships_per_page, $pager_id++);
  }

  if ($output == '') {
    $output = t('No pending relationships found');
  }

  print $output;
?>
