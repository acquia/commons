<?php
// $Id: token_comment.inc,v 1.3.4.5 2009/05/31 15:56:09 greggles Exp $

/**
 * @file
 * Implementations of token module hooks for the core comment module.
 *
 * The token module requires specific hooks to be added to modules
 * so that those modules can return data about their objects to the
 * token API.  Until and unless token becomes a part of core, the
 * implementations of the token hooks for core modules are provided
 * in the token module itself.
 * @ingroup token
 */

/**
 * Implementation of hook_token_values().
 */
function comment_token_values($type, $object = NULL, $options = array()) {
  $values = array();
  switch ($type) {
    case 'comment':

      // Cast to an object just in case fussy Drupal gave us an array
      $comment = (object)$object;

      $values['comment-cid']             = $comment->cid;
      $values['comment-nid']             = $comment->nid;
      $values['comment-title']           = check_plain($comment->subject);
      $values['comment-body']            = check_markup($comment->comment, $comment->format);
      $values['comment-author-name']     = check_plain($comment->name);
      $values['comment-author-uid']      = $comment->uid;
      $values['comment-author-homepage'] = check_url($comment->homepage);

      // Raw counterparts of user supplied data.
      $values['comment-title-raw']       = $comment->subject;
      $values['comment-body-raw']        = $comment->comment;
      $values['comment-author-name-raw'] = $comment->name;

      if (!empty($comment->mail)) {
        $account_mail = $comment->mail;
      }
      elseif (!empty($comment->uid)) {
        $account_mail = db_result(db_query("SELECT mail FROM {users} WHERE uid = %d", $comment->uid));
      }
      else {
        $account_mail = '';
      }
      $values['comment-author-mail']     = check_plain($account_mail);
      $values['comment-author-mail-raw'] = $account_mail;

      // Included in case a consuming module wants to format the body
      $values['comment-body-format']     = $comment->format;

      $values['comment-yyyy']            = date('Y', $comment->timestamp);
      $values['comment-yy']              = date('y', $comment->timestamp);
      $values['comment-month']           = date('F', $comment->timestamp);
      $values['comment-mon']             = date('M', $comment->timestamp);
      $values['comment-mm']              = date('m', $comment->timestamp);
      $values['comment-m']               = date('n', $comment->timestamp);
      $values['comment-ww']              = date('W', $comment->timestamp);
      $values['comment-date']            = date('N', $comment->timestamp);
      $values['comment-day']             = date('l', $comment->timestamp);
      $values['comment-ddd']             = date('D', $comment->timestamp);
      $values['comment-dd']              = date('d', $comment->timestamp);
      $values['comment-d']               = date('j', $comment->timestamp);
      break;
  }

  return $values;
}

/**
 * Implementation of hook_token_list().
 */
function comment_token_list($type = 'all') {
  if ($type == 'comment' || $type == 'all') {
    $tokens['comment']['comment-cid']             = t('Comment ID');
    $tokens['comment']['comment-nid']             = t("Comment's node ID");
    $tokens['comment']['comment-title']           = t('Comment title');
    $tokens['comment']['comment-title-raw']       = t('Comment title. WARNING - raw user input');
    $tokens['comment']['comment-body']            = t('Comment body');
    $tokens['comment']['comment-body-raw']        = t('Comment body. WARNING - raw user input');

    $tokens['comment']['comment-author-uid']      = t("Comment author's user id");
    $tokens['comment']['comment-author-name']     = t("Comment author's user name");
    $tokens['comment']['comment-author-name-raw'] = t("Comment author's user name. WARNING - raw user input");
    $tokens['comment']['comment-author-homepage'] = t("Comment author's home page.");

    $tokens['comment']['comment-author-mail']     = t("Comment author's e-mail.");
    $tokens['comment']['comment-author-mail-raw'] = t("Comment author's e-mail. WARNING - raw user input.");

    $tokens['comment']['comment-yyyy']            = t("Comment creation year (four digit)");
    $tokens['comment']['comment-yy']              = t("Comment creation year (two digit)");
    $tokens['comment']['comment-month']           = t("Comment creation month (full word)");
    $tokens['comment']['comment-mon']             = t("Comment creation month (abbreviated)");
    $tokens['comment']['comment-mm']              = t("Comment creation month (two digit, zero padded)");
    $tokens['comment']['comment-m']               = t("Comment creation month (one or two digit)");
    $tokens['comment']['comment-ww']              = t("Comment creation week (two digit)");
    $tokens['comment']['comment-date']            = t("Comment creation date (day of month)");
    $tokens['comment']['comment-day']             = t("Comment creation day (full word)");
    $tokens['comment']['comment-ddd']             = t("Comment creation day (abbreviation)");
    $tokens['comment']['comment-dd']              = t("Comment creation day (two digit, zero-padded)");
    $tokens['comment']['comment-d']               = t("Comment creation day (one or two digit)");

    return $tokens;
  }
}