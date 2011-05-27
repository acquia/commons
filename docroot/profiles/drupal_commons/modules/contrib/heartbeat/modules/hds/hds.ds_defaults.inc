<?php

/**
 * @file
 * Display suite export data for hds
 */
function hds_ds_default() {

  $data = array(
    'hds' =>
    array(
      'heartbeatactivity' =>
      array(
        'full' =>
        array(
          'fields' =>
          array(
            'ds_message' =>
            array(
              'weight' => '-19',
              'format' => '',
              'region' => 'middle',
              'labelformat' => 'hidden',
            ),
            'ds_created' =>
            array(
              'weight' => '-19',
              'format' => '',
              'region' => 'right',
              'labelformat' => 'hidden',
            ),
            'ds_attachments' =>
            array(
              'weight' => '-20',
              'format' => '',
              'region' => 'disabled',
              'labelformat' => 'hidden',
            ),
          ),
        ),
      ),
    ),
  );

  return $data;

}