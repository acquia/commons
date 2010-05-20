<?php
// $Id: drupal_commons.profile

// Define the name of the free-tagging vocabulary
define('DRUPAL_COMMONS_TAG_NAME', 'Tags');

// Define the forced ID of the free-tagging vocabulary
define('DRUPAL_COMMONS_TAG_ID', 2);

// Define the name of the user menu dropdown item
define('DRUPAL_COMMONS_USER_MENU_DROPDOWN', 'My Stuff');

// Define the default WYSIWYG editor
define('DRUPAL_COMMONS_EDITOR', 'ckeditor');

// Define the "community manager" role name
define('DRUPAL_COMMONS_MANAGER_ROLE', 'community manager');

// Define the default theme
define('DRUPAL_COMMONS_THEME', 'linden');

// Define the default frontpage
define('DRUPAL_COMMONS_FRONTPAGE', 'home');

// Define the default point amount for posting a node
define('DRUPAL_COMMONS_POINTS_NODE', 5);

// Define the default point amount for posting a comment
define('DRUPAL_COMMONS_POINTS_COMMENT', 2);

// Define the singular name of the user relationship
define('DRUPAL_COMMONS_RELATIONSHIP_SINGULAR', 'Friend');

// Define the plural name of the user relationship
define('DRUPAL_COMMONS_RELATIONSHIP_PLURAL', 'Friends');

/**
 * Return an array of the modules to be enabled when this profile is installed.
 *
 * @return
 *   An array of modules to enable.
 */
function drupal_commons_profile_modules() {
  $modules = array(
    // Default Drupal modules.
    'color', 'comment', 'help', 'menu', 'taxonomy', 'dblog', 'profile',
    'blog', 'aggregator', 'poll',  'search', 'tracker', 'php', 'path',
    
    // Chaos Tools
    'ctools', 'page_manager', 'panels', 'context', 'context_contrib', 'context_ui',
    
    // Views
    'views', 'views_ui', 'views_content',
    
    // getID
    'getid3',
    
    // CCK
    'content', 'content_permissions', 'fieldgroup', 'text', 'filefield', 'imagefield',
    'optionwidgets', 'link', 'filefield_meta',
    
    // Date
    'date_api', 'date_timezone', 'date',  'date_popup', 'date_tools',
     
    // ImageAPI
    'imageapi', 'imagecache', 'imageapi_gd',  'imagecache_profiles', 'imagecache_ui',
    
    // Organic Groups
    'og', 'og_access', 'og_aggregator', 'og_statistics', 'og_views', 'context_og',
    
    // User Relationships
    'user_relationships_api', 'user_relationships_ui', 'user_relationship_views', 'user_relationships_rules',
    'user_relationship_blocks', 'user_relationship_elaborations', 'user_relationship_mailer',
    
    // Taxonomy
    'tagadelic', 'tagadelic_views', 'tagging', 'user_terms',
    
    // Rules
    'token', 'rules', 'rules_admin',
    
    // Editor
    'wysiwyg', 'imce', 'imce_wysiwyg',
    
    // Shoutbox
    'shoutbox', 'shoutbox_group',
    
    // Misc
    'userpoints', 'userpoints_nc', 'wikitools', 'admin_menu', 'ajax_load', 'editablefields', 
    'calendar', 'jcalendar', 'diff', 'freelinking', 'flag', 'pathauto', 'jquery_ui',
    
    // Heartbeat
    'heartbeat', 'heartbeat_views', 'hrules', 'friendlist_activity', 'flag_heartbeat', 'og_activity',
    
    // Commons
    'commons',
    
    // Strongarm
    'strongarm', 
    
    // Features (modules)
    'features', 'features_hb', 
    
    // Features (features)
    'commons_core',
  );

  return $modules;
}

/**
 * Return a description of the profile for the initial installation screen.
 *
 * @return
 *   An array with keys 'name' and 'description' describing this profile,
 *   and optional 'language' to override the language selection for
 *   language-specific profiles.
 */
function drupal_commons_profile_details() {
  $image = '<img src="./profiles/drupal_commons/images/logo.png" alt="Drupal Commons" title="Drupal Commons"/>';
  
  return array(
    'name' => 'Drupal Commons',
    'description' => $image . '<br/>Social collaboration software.'
  );
}

/**
 * Return a list of tasks that this profile supports.
 *
 * @return
 *   A keyed array of tasks the profile will perform during
 *   the final stage. The keys of the array will be used internally,
 *   while the values will be displayed to the user in the installer
 *   task list.
 */
function drupal_commons_profile_task_list() {

}

/**
 * Perform any final installation tasks for this profile.
 *
 * @param $task
 *   The current $task of the install system. When hook_profile_tasks()
 *   is first called, this is 'profile'.
 * @param $url
 *   Complete URL to be used for a link or form action on a custom page,
 *   if providing any, to allow the user to proceed with the installation.
 *
 * @return
 *   An optional HTML string to display to the user. Only used if you
 *   modify the $task, otherwise discarded.
 */
function drupal_commons_profile_tasks(&$task, $url) {
  drupal_commons_build_directories();
  drupal_commons_config_vocabulary();
  drupal_commons_config_profile();
  drupal_commons_config_flag();
  drupal_commons_config_menu();
  drupal_commons_config_filter();
  drupal_commons_config_wysiwyg();
  drupal_commons_config_ur();
  drupal_commons_config_heartbeat();
  drupal_commons_config_pathauto();
  drupal_commons_config_ctools();
  drupal_commons_config_roles();
  drupal_commons_config_perms();
  drupal_commons_config_views();
  drupal_commons_config_theme();
  drupal_commons_config_images();
  drupal_commons_config_vars();
  drupal_commons_cleanup();
}

// Create necessary directories
function drupal_commons_build_directories() {
  $dirs = array('ctools', 'ctools/css', 'pictures', 'imagecache');
  
  foreach ($dirs as $dir) {
    $dir = file_directory_path() . '/' . $dir;
    file_check_directory(&$dir, TRUE);
  }
}

// Add and configure vocabularies
function drupal_commons_config_vocabulary() {
  // Add vocabulary for Userpoints.module
  $vocab = array(
    'name' => t(USERPOINTS_CATEGORY_NAME),
    'description' => t('Automatically created by the userpoints module'),
    'multiple' => '0',
    'required' => '0',
    'hierarchy' => '1',
    'relations' => '0',
    'module' => 'userpoints',
  );
  taxonomy_save_vocabulary($vocab);
  
  // Add free-tagging vocabulary for content
  $vocab = array(
    'name' => t(DRUPAL_COMMONS_TAG_NAME),
    'description' => t('Free-tagging vocabulary for all content items'),
    'multiple' => '0',
    'required' => '0',
    'hierarchy' => '0',
    'relations' => '1',
    'tags' => '1',
    'module' => 'taxonomy',
  );
  taxonomy_save_vocabulary($vocab); 
  
  // Force free-tagging vocabulary to a certain ID
  // This is needed for bundled views to work
  db_query("UPDATE {vocabulary} SET vid = %d WHERE name = '%s'",
    DRUPAL_COMMONS_TAG_ID,
    DRUPAL_COMMONS_TAG_NAME
  );
  
  // Link free-tagging vocabulary to node types
  $sql = "INSERT INTO {vocabulary_node_types} (vid, type) VALUES (%d, '%s')";
  db_query($sql, DRUPAL_COMMONS_TAG_ID, 'blog');
  db_query($sql, DRUPAL_COMMONS_TAG_ID, 'discussion');
  db_query($sql, DRUPAL_COMMONS_TAG_ID, 'document');
  db_query($sql, DRUPAL_COMMONS_TAG_ID, 'event');
  db_query($sql, DRUPAL_COMMONS_TAG_ID, 'group');
  db_query($sql, DRUPAL_COMMONS_TAG_ID, 'poll');
  db_query($sql, DRUPAL_COMMONS_TAG_ID, 'wiki'); 
}

// Add custom profile fields
function drupal_commons_config_profile() {
  // Add custom profile fields
  $sql = "INSERT INTO {profile_fields} (title, name, explanation, category, type, weight, required, register, visibility, autocomplete) VALUES ('%s', '%s', '%s', '%s', '%s', %d, %d, %d, %d, %d)";
  db_query($sql, t('Name'), 'profile_name', t('Enter your full name.'), t('Personal Information'), 'textfield', -10, 0, 1, 2, 0);
  db_query($sql, t('Job Title'), 'profile_job', t('What is your job title?'), t('Work Information'), 'textfield', 0, 0, 1, 2, 0);
  db_query($sql, t('My Interests'), 'profile_interests', t('What are your interests, hobbies, etc?'), t('Personal Information'), 'textarea', -8, 0, 0, 2, 0);
  db_query($sql, t('Organization'), 'profile_organization', t('Which organization or department are you a part of?'), t('Work Information'), 'textfield', 0, 0, 0, 2, 0);
  db_query($sql, t('Location'), 'profile_location', t('Where are you located?'), t('Personal Information'), 'textfield', -9, 0, 0, 2, 0);
  db_query($sql, t('About Me'), 'profile_aboutme', t('Explain a little about yourself.'), t('Personal Information'), 'textarea', 0, 0, 0, 2, 0);  
}

// Configure flag
function drupal_commons_config_flag() {
  // Fetch bookmark flag ID
  $flag_id = db_result(db_query("SELECT fid FROM {flags} WHERE name = '%s'", 'bookmarks'));
  
  // Enable default bookmark flag to work on content types
  $sql = "INSERT INTO {flag_types} (fid, type) VALUES (%d, '%s')";
  db_query("DELETE FROM {flag_types}");
  db_query($sql, $flag_id, 'blog');
  db_query($sql, $flag_id, 'discussion');
  db_query($sql, $flag_id, 'document');
  db_query($sql, $flag_id, 'event');
  db_query($sql, $flag_id, 'poll');
  db_query($sql, $flag_id, 'wiki');
}

// Configure menu
function drupal_commons_config_menu() {
  /*
   * Create additional primary menu items
   */
  // Create "My Stuff" drop down first, so we can fetch the mlid
  $parent = array('menu_name' => 'primary-links', 'weight' => 15, 'link_path' => 'user', 'link_title' => t(DRUPAL_COMMONS_USER_MENU_DROPDOWN));
  menu_link_save($parent);
  
  // Childs of "My Stuff" menu
  $links = array();
  $links[] = array('menu_name' => 'primary-links', 'weight' => 0, 'link_path' => 'user', 'link_title' => t('My Profile'), 'plid' => $parent['mlid']);
  $links[] = array('menu_name' => 'primary-links', 'weight' => 1, 'link_path' => 'og/my', 'link_title' => t('My Groups'), 'plid' => $parent['mlid']);
  $links[] = array('menu_name' => 'primary-links', 'weight' => 2, 'link_path' => 'group', 'link_title' => t('My Unread'), 'plid' => $parent['mlid']);
  $links[] = array('menu_name' => 'primary-links', 'weight' => 3, 'link_path' => 'bookmarks', 'link_title' => t('My Bookmarks'), 'plid' => $parent['mlid']);
  $links[] = array('menu_name' => 'primary-links', 'weight' => 4, 'link_path' => 'relationships', 'link_title' => t('My Friends'), 'plid' => $parent['mlid']);
  $links[] = array('menu_name' => 'primary-links', 'weight' => 5, 'link_path' => 'myuserpoints', 'link_title' => t('My Points'), 'plid' => $parent['mlid']);
  
  foreach ($links as $link) {
    menu_link_save($link);
  } 
}

// Configure input filters
function drupal_commons_config_filter() {
  // Set allowed HTML tags for Filter HTML format
  variable_set('allowed_html_1', '<a> <img> <em> <p> <strong> <cite> <code> <ul> <ol> <li> <dl> <dt> <dd>');
  
  // Fetch format IDs
  $filtered_html = db_result(db_query("SELECT format FROM {filter_formats} WHERE name = '%s'", 'Filtered HTML'));
  $full_html = db_result(db_query("SELECT format FROM {filter_formats} WHERE name = '%s'", 'Full HTML'));

  // Add wiki-style freelinking to both default formats
  $sql = "INSERT INTO {filters} (format, module, delta, weight) VALUES (%d, '%s', %d, %d)";
  db_query($sql, $filtered_html, 'freelinking', 0, 10);  // Filtered HTML
  db_query($sql, $full_html, 'freelinking', 0, 10);  // Full HTML
}

// Configure wysiwyg
function drupal_commons_config_wysiwyg() {
  // Load external file containing editor settings
  include_once('drupal_commons_editor.inc'); 
  
  // Fetch format IDs
  $filtered_html = db_result(db_query("SELECT format FROM {filter_formats} WHERE name = '%s'", 'Filtered HTML'));
  $full_html = db_result(db_query("SELECT format FROM {filter_formats} WHERE name = '%s'", 'Full HTML'));
  
  // Build SQL statement
  $sql = "INSERT INTO {wysiwyg} (format, editor, settings) VALUES (%d, '%s', '%s')";
  
  // Insert the settings
  db_query($sql, $filtered_html, DRUPAL_COMMONS_EDITOR, serialize(drupal_commons_editor_settings('Filtered HTML')));
  
  // Build settings for filtered html array
  $settings = array();
  
  // Insert the settings
  db_query($sql, $full_html, DRUPAL_COMMONS_EDITOR, serialize(drupal_commons_editor_settings('Full HTML')));
}

// Configure user_relationships
function drupal_commons_config_ur() {
  // Add initial relationship type 'Friend'
  db_query("INSERT INTO {user_relationship_types} (name, plural_name, is_oneway, is_reciprocal, requires_approval, expires_val) 
    VALUES ('%s', '%s', %d, %d, %d, %d)", 
    t(DRUPAL_COMMONS_RELATIONSHIP_SINGULAR), 
    t(DRUPAL_COMMONS_RELATIONSHIP_PLURAL), 
    0, 0, 1, 0);
}

// Configure heartbeat
function drupal_commons_config_heartbeat() {
  // Refresh all available heartbeat streams
  // This registers the relational activity stream
  heartbeat_check_access_types();
  
  // Rebuild all available heartbeat message templates
  heartbeat_messages_rebuild();
  
  // Disable stream tabs on user profiles
  $streams = variable_get('heartbeat_stream_data', '');
  
  if ($streams) {
    foreach ($streams as $key => $value) {
      $streams[$key]['profile'] = 0;
    }
  
    variable_set('heartbeat_stream_data', $streams);
  }
}

// Configure pathauto
function drupal_commons_config_pathauto() {
  // For reasons unknown, we can't Strongarm this
  variable_set('pathauto_taxonomy_2_pattern', 'tag/[catpath-raw]');
}

// Configure ctools
function drupal_commons_config_ctools() {
  ctools_include('context');
  ctools_include('plugins');
  
  // Enable node view override (variants imported via Features)
  $page = page_manager_get_page_cache('node_view');
  if ($function = ctools_plugin_get_function($page->subtask, 'enable callback')) {
    $result = $function($page, FALSE);

    // We want to re-cache this if it's changed so that status is properly
    // updated on the changed form.
    if (!empty($page->changed)) {
      page_manager_set_page_cache($page);
    }
  }
  
  // Enable profile view override (variant imported via Features) 
  $page = page_manager_get_page_cache('user_view');
  if ($function = ctools_plugin_get_function($page->subtask, 'enable callback')) {
    $result = $function($page, FALSE);

    // We want to re-cache this if it's changed so that status is properly
    // updated on the changed form.
    if (!empty($page->changed)) {
      page_manager_set_page_cache($page);
    }
  }
}

// Configure roles
function drupal_commons_config_roles() {
  // Add the "Community Manager" role
  db_query("INSERT INTO {role} (name) VALUES ('%s')", t(DRUPAL_COMMONS_MANAGER_ROLE));
}

// Configure permissions
function drupal_commons_config_perms() {
  // Load external permissions file
  include_once('drupal_commons_perms.inc');
  
  $roles_data = array();
  
  // Fetch available roles
  $roles = db_query("SELECT * FROM {role}");
  
  // Set up roles data
  while ($role = db_fetch_object($roles)) {
    $roles_data[$role->name] = array(
      'rid' => $role->rid,
      'permissions' => array(),
    );  
  }
  
  // Fetch set permissions
  $permissions = drupal_commons_import_permissions();
  
  // Add permissions to roles
  foreach ($permissions as $permission) {
    // Find which roles have the given permission
    foreach ($permission['roles'] as $role) {
      $roles_data[$role]['permissions'][] = $permission['name'];
    }
  }
  
  // Purge permissions, just in case there are any stored
  db_query("DELETE FROM {permission}");
  
  // Store all of the permissions
  foreach ($roles_data as $role_data) {
    db_query("INSERT INTO {permission} (rid, perm) VALUES (%d, '%s')", $role_data['rid'], implode($role_data['permissions'], ', '));
  }
}

// Configure views
function drupal_commons_config_views() {
  /*
   * Disable unneeded views to avoid confusion
   * This is helpful because we've overridden many OG views
   */
  
  // First fetch any disabled views, just in case
  $disabled = variable_get('views_defaults', array());
  
  // Now add the views we want to disable
  $disabled['og'] = TRUE;
  $disabled['og_members_block'] = TRUE;
  $disabled['og_my'] = TRUE;
  
  // Disable views and update the cache
  variable_set('views_defaults', $disabled);
  views_invalidate_cache();
}
  
// Configure theme
function drupal_commons_config_theme() {
  // Disable garland
  db_query("UPDATE {system} SET status = 0 WHERE type = 'theme' and name = '%s'", 'garland');
  
  // Enable Commons theme
  db_query("UPDATE {system} SET status = 1 WHERE type = 'theme' and name = '%s'", DRUPAL_COMMONS_THEME);
  
  // Set Commons theme as the default
  variable_set('theme_default', DRUPAL_COMMONS_THEME);
  
  // Refresh registry
  list_themes(TRUE);
  drupal_rebuild_theme_registry();
}

// Configure default images
function drupal_commons_config_images() {
  // Copy default user image to files directory
  $user_image = 'profiles/drupal_commons/images/default-user.png';
  file_copy(&$user_image, 0, FILE_EXISTS_REPLACE); // Defaults to files directory
  
  // Copy default group image to files directory
  $group_image = 'profiles/drupal_commons/images/default-group.png';
  file_copy(&$group_image, 0, FILE_EXISTS_REPLACE); // Defaults to files directory
  
  // Process default user image through ImageCache
  $preset = imagecache_preset_by_name('profile_pictures');
  imagecache_build_derivative(
    $preset['actions'], 
    $user_image, 
    file_directory_path() . '/imagecache/profile_pictures/default-user.png'
  );
  
  // Process default user image thumbnail through ImageCache
  $preset = imagecache_preset_by_name('user_picture_meta');
  imagecache_build_derivative(
    $preset['actions'], 
    $user_image, 
    file_directory_path() . '/imagecache/user_picture_meta/default-user.png'
  );
  
  // Set user image as the default
  variable_set('user_picture_default', 'default-user.png');
  
  // Process default group image through ImageCache
  $preset = imagecache_preset_by_name('group_images');
  imagecache_build_derivative(
    $preset['actions'], 
    $group_image, 
    file_directory_path() . '/imagecache/group_images/imagefield_default_images/default-group.png'
  );
  
  // Process default group image thumbnail through ImageCache
  $preset = imagecache_preset_by_name('group_images_thumb');
  imagecache_build_derivative(
    $preset['actions'], 
    $group_image, 
    file_directory_path() . '/imagecache/group_images_thumb/imagefield_default_images/default-group.png'
  );
  
  // Simulate that we've uploaded the group image
  db_query("INSERT INTO {files} (uid, filename, filepath, filemime, filesize, status, timestamp)
    VALUES (%d, '%s', '%s', '%s', %d, %d, %d)",
    1,
    'default-group.png',
    file_directory_path() . '/imagecache/group_images/imagefield_default_images/default-group.png',
    'image/png',
    filesize($group_image),
    1,
    time()
  );
  
  // Now fetch the file
  $file = db_fetch_object(db_query("SELECT * from {files} WHERE filename = '%s'", 'default-group.png'));
  
  // Fetch group image CCK field settings to alter
  $settings = db_result(db_query("SELECT widget_settings FROM {content_node_field_instance} WHERE field_name = 'field_group_image'"));
  $settings = unserialize($settings);
  $settings['default_image'] = array(
    'filename' => $file->filename,
    'filepath' => $file->filepath,
    'filemime' => $file->filemime,
    'source' => 'default_image_upload',
    'destination' => $file->filepath,
    'filesize' => $file->filesize,
    'uid' => $file->uid,
    'status' => $file->status,
    'timestamp' => $file->timestamp,
    'fid' => $file->fid
  );
  $settings['use_default_image'] = 1;
  
  // Put the altered settings back
  db_query("UPDATE {content_node_field_instance} SET widget_settings = '%s' WHERE field_name = 'field_group_image'", serialize($settings));
}

// Configure variables. These should be set but not forced by Strongarm/Features
function drupal_commons_config_vars() {
  // Set default homepage
  variable_set('site_frontpage', DRUPAL_COMMONS_FRONTPAGE);
  
  // Set a default point amount so userpoints works out-of-the-box
  variable_set('userpoints_post_blog', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_post_poll', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_post_discussion', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_post_document', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_post_event', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_post_group', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_post_wiki', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_post_comment', DRUPAL_COMMONS_POINTS_COMMENT);
  
  // Force anonymous users to login
  variable_set('commons_force_login', 1);
  
  // Show large amount of tags on tag cloud page
  variable_set('tagadelic_page_amount', 500);
}

// Various actions needed to clean up after the installation
function drupal_commons_cleanup() {
  // Rebuild node access database - required after OG installation
  node_access_rebuild();
  
  // Rebuild node types
  node_types_rebuild();
  
  // Rebuild the menu
  menu_rebuild();
  
  // Clear drupal message queue for non-warning/errors
  drupal_get_messages('status', TRUE);

  // Clear out caches
  $core = array('cache', 'cache_block', 'cache_filter', 'cache_page');
  $cache_tables = array_merge(module_invoke_all('flush_caches'), $core);
  foreach ($cache_tables as $table) {
    cache_clear_all('*', $table, TRUE);
  }
  
  // Say hello to the dog!
  watchdog('commons', t('Welcome to Drupal Commons from Acquia!'));
}
