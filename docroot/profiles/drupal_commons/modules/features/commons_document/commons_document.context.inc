<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_document_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-group-document-node';
  $context->description = 'A document node inside a group';
  $context->tag = 'Group';
  $context->conditions = array(
    'context_og_condition_group_type' => array(
      'values' => array(
        'group' => 'group',
      ),
      'options' => array(
        'node_form' => 0,
      ),
    ),
    'node' => array(
      'values' => array(
        'document' => 'document',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-363c36ed99d1c774fcc13d74a03dad8b' => array(
          'module' => 'views',
          'delta' => '363c36ed99d1c774fcc13d74a03dad8b',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-4fa75b28a31d39d57d4357bf10199287' => array(
          'module' => 'views',
          'delta' => '4fa75b28a31d39d57d4357bf10199287',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('A document node inside a group');
  t('Group');

  $export['context_ui-group-group-document-node'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-group-home-documents';
  $context->description = 'Documents block for the group home page';
  $context->tag = 'Group';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'group' => 'group',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-group_block_document_latest-block_1' => array(
          'module' => 'views',
          'delta' => 'group_block_document_latest-block_1',
          'region' => 'sidebar_last',
          'weight' => 6,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Documents block for the group home page');
  t('Group');

  $export['context_ui-group-group-home-documents'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-group-tab-documents';
  $context->description = 'The document tab on a group';
  $context->tag = 'Group';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'group_tab_documents:page_1' => 'group_tab_documents:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-group_block_doc_latest_comments-block_1' => array(
          'module' => 'views',
          'delta' => 'group_block_doc_latest_comments-block_1',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Group');
  t('The document tab on a group');

  $export['context_ui-group-group-tab-documents'] = $context;
  return $export;
}
