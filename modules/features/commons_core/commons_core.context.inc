<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function commons_core_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'bookmarks';
  $context->description = 'The bookmarks page';
  $context->tag = 'Bookmarks';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'bookmarks' => 'bookmarks',
        'user/*/bookmarks' => 'user/*/bookmarks',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-most_bookmarked-block_1' => array(
          'module' => 'views',
          'delta' => 'most_bookmarked-block_1',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Bookmarks');
  t('The bookmarks page');
  $export['bookmarks'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'global';
  $context->description = 'Show on every page';
  $context->tag = 'Sitewide';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-user_meta-block_1' => array(
          'module' => 'views',
          'delta' => 'user_meta-block_1',
          'region' => 'header',
          'weight' => 0,
        ),
        'commons_core-header_login' => array(
          'module' => 'commons_core',
          'delta' => 'header_login',
          'region' => 'header',
          'weight' => 1,
        ),
        'commons_core-commons_info' => array(
          'module' => 'commons_core',
          'delta' => 'commons_info',
          'region' => 'footer',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Show on every page');
  t('Sitewide');
  $export['global'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-context';
  $context->description = 'The context of a group';
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
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_core-group_create_content' => array(
          'module' => 'commons_core',
          'delta' => 'group_create_content',
          'region' => 'sidebar_last',
          'weight' => -5,
        ),
        'commons_core-group_menu' => array(
          'module' => 'commons_core',
          'delta' => 'group_menu',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-24dcb59a56254e5a470ee2f23590eed2' => array(
          'module' => 'views',
          'delta' => '24dcb59a56254e5a470ee2f23590eed2',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
        'views-bookmarks_your_group-block_1' => array(
          'module' => 'views',
          'delta' => 'bookmarks_your_group-block_1',
          'region' => 'sidebar_last',
          'weight' => 3,
        ),
        'commons_core-group_members' => array(
          'module' => 'commons_core',
          'delta' => 'group_members',
          'region' => 'sidebar_last',
          'weight' => 4,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Group');
  t('The context of a group');
  $export['group-context'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-home';
  $context->description = 'The group home page';
  $context->tag = 'Group';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'group' => 'group',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-group_links-block_1' => array(
          'module' => 'views',
          'delta' => 'group_links-block_1',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-group_tab_content-block_1' => array(
          'module' => 'views',
          'delta' => 'group_tab_content-block_1',
          'region' => 'content',
          'weight' => 0,
        ),
      ),
    ),
    'breadcrumb' => 'groups',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Group');
  t('The group home page');
  $export['group-home'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-listing';
  $context->description = 'The list of available groups on the site';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'groups' => 'groups',
        'groups/*' => 'groups/*',
        '~groups/mine' => '~groups/mine',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_core-create_group' => array(
          'module' => 'commons_core',
          'delta' => 'create_group',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-groups_my_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_my_groups-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-groups_most_active-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_most_active-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
        'views-groups_newest_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_newest_groups-block_1',
          'region' => 'sidebar_last',
          'weight' => 3,
        ),
        'views-groups_featured_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_featured_groups-block_1',
          'region' => 'content_top',
          'weight' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('The list of available groups on the site');
  $export['group-listing'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'group-listing-mine';
  $context->description = 'A listing of your groups';
  $context->tag = '';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'groups_my_groups_listing:page_1' => 'groups_my_groups_listing:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_core-create_group' => array(
          'module' => 'commons_core',
          'delta' => 'create_group',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-groups_newest_groups-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_newest_groups-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
        'views-groups_most_active-block_1' => array(
          'module' => 'views',
          'delta' => 'groups_most_active-block_1',
          'region' => 'sidebar_last',
          'weight' => 2,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('A listing of your groups');
  $export['group-listing-mine'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'notices';
  $context->description = 'Notice listing and nodes';
  $context->tag = 'Notices';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'notice' => 'notice',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
    'views' => array(
      'values' => array(
        'recent_notices:page_1' => 'recent_notices:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'commons_core-create_notice' => array(
          'module' => 'commons_core',
          'delta' => 'create_notice',
          'region' => 'sidebar_last',
          'weight' => 0,
        ),
        'views-notice_latest_comments-block_1' => array(
          'module' => 'views',
          'delta' => 'notice_latest_comments-block_1',
          'region' => 'sidebar_last',
          'weight' => 1,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Notice listing and nodes');
  t('Notices');
  $export['notices'] = $context;

  return $export;
}
