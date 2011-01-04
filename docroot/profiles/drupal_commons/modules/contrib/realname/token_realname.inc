<?php
// $Id: token_realname.inc,v 1.1.2.11 2010/10/27 07:29:16 davereid Exp $ */
/**
* @file
*   Token module support for the realname module.
*/

function realname_token_list($type = 'all') {
  $tokens = array();
  switch ($type) {
    case 'user':
    case 'node':
      $tokens[$type]['realname-node-author'] = t('The realname of node author.');

    case 'all':
    case 'global':
    case 'comment':
      $tokens[$type]['realname'] = t('The RealName for the user.');
      $tokens[$type]['realname-link'] = t('Themed username link.');
      $tokens[$type]['homepage'] = t('The home page for the user.');
      $tokens[$type]['realname-comment-author'] = t('The realname of comment author.');
      return $tokens;
  }
}

function realname_token_values($type, $object = NULL, $options = array()) {
  global $user;
  $tokens = array();
  if (!$object) {
    $object = $user;
  }
  switch ($type) {
    case 'user':
    case 'node':
      // If there's a nid, then create a token with the realname of
      // author of the node.
      if (!empty($object->nid) && $object->uid) {
        $tokens['realname-node-author'] = db_result(db_query("SELECT realname FROM {realname} WHERE uid = %d", $object->uid));
      }
    
//    case 'all':
    case 'global':
    case 'comment':
      // If there's a cid, then create a token with the realname of
      // author of the comment
      if (!empty($object->cid) && $object->uid) {
        $tokens['realname-comment-author'] = db_result(db_query("SELECT realname FROM {realname} WHERE uid = %d", $object->uid));
      }

      if (!isset($object->uid)) {
        return;
      }

      $tokens['realname'] = realname_make_name($object);
      $tokens['realname-link'] = theme('username', $object);
      $tokens['homepage'] = isset($object->homepage) ? $object->homepage : NULL;
      return $tokens;

  }
}
