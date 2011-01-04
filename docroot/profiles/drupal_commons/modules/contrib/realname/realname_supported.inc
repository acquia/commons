<?php
// $Id: realname_supported.inc,v 1.1.2.2 2008/11/03 20:10:34 nancyw Exp $
/**
 * @file
 * Realname module support list.
 */

function realname_supported_modules() {
  $list = array(
    'content_profile' => array(
      'name' => 'Content Profile',
      'types' => TRUE,
      ),
    'profile' => array(
      'name' => 'Core Profile',
      'types' => FALSE,
      ),
    );
  return $list;
}
