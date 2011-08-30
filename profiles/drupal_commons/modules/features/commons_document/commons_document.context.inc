<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_document_context_default_contexts() {
  $export = array();
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'content-document-page';
  $context->description = 'The documents page';
  $context->tag = 'Document';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'content_document_page:page_1' => 'content_document_page:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_core-group_create_content' => array(
          'module' => 'commons_core',
          'delta' => 'group_create_content',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-caad6a250d3875f477bedd51f96ab857' => array(
          'module' => 'views',
          'delta' => 'caad6a250d3875f477bedd51f96ab857',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Document');
  t('The documents page');

  $export['content-document-page'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-document-node';
  $context->description = 'A document node inside a group';
  $context->tag = 'Document';
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
  t('Document');

  $export['group-document-node'] = $context;
  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-tab-documents';
  $context->description = 'The document tab on a group';
  $context->tag = 'Document';
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
        'views-4fa75b28a31d39d57d4357bf10199287' => array(
          'module' => 'views',
          'delta' => '4fa75b28a31d39d57d4357bf10199287',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Document');
  t('The document tab on a group');

  $export['group-tab-documents'] = $context;
  return $export;
}
