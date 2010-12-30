<?php
// $Id: drupal_commons.profile

// Define the name of the free-tagging vocabulary
define('DRUPAL_COMMONS_TAG_NAME', 'Tags');

// Define the forced ID of the free-tagging vocabulary
define('DRUPAL_COMMONS_TAG_ID', 2);

// Define the default WYSIWYG editor
define('DRUPAL_COMMONS_EDITOR', 'ckeditor');

// Define the allowed filtered html tags
define('DRUPAL_COMMONS_FILTERED_HTML', '<a> <img> <br> <em> <p> <strong> <cite> <sub> <sup> <span> <blockquote> <code> <ul> <ol> <li> <dl> <dt> <dd> <pre> <address> <h2> <h3> <h4> <h5> <h6>');

// Define the "community manager" role name
define('DRUPAL_COMMONS_MANAGER_ROLE', 'community manager');

// Define the "content manager" role name
define('DRUPAL_COMMONS_CONTENT_ROLE', 'content manager');

// Define the default theme
define('DRUPAL_COMMONS_THEME', 'acquia_commons');

// Define the default point amount for posting a node
define('DRUPAL_COMMONS_POINTS_NODE', 5);

// Define the default point amount for posting a comment
define('DRUPAL_COMMONS_POINTS_COMMENT', 2);

// Define the default point amount for uploading a profile picture
define('DRUPAL_COMMONS_POINTS_PICTURE', 5);

// Define the default point amount for posting a shout
define('DRUPAL_COMMONS_POINTS_SHOUT', 1);

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
    'contact',
    
    // CTools
    'ctools', 
    
    // Panels
    'page_manager', 'panels', 
    
    // Context
    'context', 'context_ui',
    
    // Views
    'views', 'views_ui', 'views_content',
    
    // getID
    'getid3',
    
    // CCK
    'content', 'content_permissions', 'fieldgroup', 'text', 'filefield', 'imagefield',
    'optionwidgets', 'link', 'filefield_meta',
    
    // Date
    'date_api', 'date_timezone', 'date',  'date_popup', 'date_tools',
     
    // ImageAPI + ImageCache
    'imageapi', 'imagecache', 'imageapi_gd',  'imagecache_profiles', 'imagecache_ui',
    'imagecache_canvasactions',
    
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
    'wysiwyg',
    
    // Messaging
    'messaging', 'messaging_mail', 'messaging_simple',
    
    // Notifications
    'notifications', 'notifications_autosubscribe', 'notifications_content',
    'notifications_ui', 'notifications_views',
    
    // Misc
    'wikitools', 'admin_menu', 'ajax_load', 'editablefields', 
    'calendar', 'jcalendar', 'diff', 'freelinking', 'flag', 'pathauto', 'jquery_ui', 'insert',
    'vertical_tabs', 'transliteration', 'password_policy',
    
    // Userpoints
    'userpoints', 'userpoints_nc', 'userpoints_user_picture',
    
    // Shoutbox
    'shoutbox', 'shoutbox_group', 'shoutbox_points',
    
    // Heartbeat
    'heartbeat', 'heartbeat_views', 'hrules', 'friendlist_activity', 'flag_heartbeat', 'og_activity',
    
    // Analytics
    'chart', 'quant',
    
    // Theme
    'skinr',
    
    // Strongarm
    'strongarm', 
    
    // Features
    'features',
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
  return array(
    'name' => 'Drupal Commons',
    'description' => 'Select this profile to install the Drupal Commons distribution for powering your community website. Drupal Commons provides provides blogging, discussions, user profiles, and other useful community features for both private communities (e.g. an Intranet), or public communities (e.g. a customer community).'
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
  $tasks = array();
  $tasks['configure-commons'] = t('Configure Drupal Commons');
  return $tasks;
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
  if ($task == 'profile') {
    $task = 'configure-commons';  
  }
  
  if ($task == 'configure-commons-batch') {
    include_once 'includes/batch.inc';
    $output = _batch_page();
  }
  
  if ($task == 'configure-commons') {
    $operations = array();
    $operations[] = array('drupal_commons_config_roles', array());
    $operations[] = array('drupal_commons_config_perms', array());
    $operations[] = array('drupal_commons_enable_features', array());
    $operations[] = array('drupal_commons_build_directories', array());
    $operations[] = array('drupal_commons_config_taxonomy', array());
    $operations[] = array('drupal_commons_config_profile', array());
    $operations[] = array('drupal_commons_config_filter', array());
    $operations[] = array('drupal_commons_config_password', array());
    $operations[] = array('drupal_commons_config_wysiwyg', array());
    $operations[] = array('drupal_commons_config_ur', array());
    $operations[] = array('drupal_commons_config_heartbeat', array());
    $operations[] = array('drupal_commons_config_ctools', array());
    $operations[] = array('drupal_commons_config_views', array());
    $operations[] = array('drupal_commons_config_theme', array());
    $operations[] = array('drupal_commons_config_images', array());
    $operations[] = array('drupal_commons_config_vars', array());
  
    $batch = array(
      'operations' => $operations,
      'title' => t('Configuring Drupal Commons'),
      'error_message' => t('An error occurred. Please try reinstalling again.'),
      'finished' => 'drupal_commons_cleanup',
    );
  
    variable_set('install_task', 'configure-commons-batch');
    batch_set($batch);
    batch_process($url, $url);
  }
  
  return $output;
}

/**
 * Enable the Commons features
 */
function drupal_commons_enable_features() {
  $features = array(
    'commons_core',
    'commons_notifications',
    'commons_admin',
    'commons_seo',
    'commons_home',
    'commons_dashboard',
    'commons_wiki',
    'commons_blog',
    'commons_document',
    'commons_discussion',
    'commons_event',
    'commons_poll',
    'commons_group_aggregator',
  );
  features_install_modules($features);
}

/**
 * Create necessary directories
 */
function drupal_commons_build_directories() {
  $dirs = array('ctools', 'ctools/css', 'pictures', 'imagecache', 'css', 'js');
  
  foreach ($dirs as $dir) {
    $dir = file_directory_path() . '/' . $dir;
    file_check_directory($dir, TRUE);
  }
}

/**
 * Configure taxonomy
 * 
 * Add and configure vocabularies
 */
function drupal_commons_config_taxonomy() {
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
    'help' => t('Press enter or click !plus between tags.', array('!plus' => '\'+\'')),
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
  db_query($sql, DRUPAL_COMMONS_TAG_ID, 'group');
  db_query($sql, DRUPAL_COMMONS_TAG_ID, 'notice');
  db_query($sql, DRUPAL_COMMONS_TAG_ID, 'page');
}

/**
 * Configure profile
 * 
 * Add custom profile fields
 */
function drupal_commons_config_profile() {
  // Add custom profile fields
  $sql = "INSERT INTO {profile_fields} (title, name, explanation, category, type, weight, required, register, visibility, autocomplete) VALUES ('%s', '%s', '%s', '%s', '%s', %d, %d, %d, %d, %d)";
  
  // Personal Information
  db_query($sql, t('First name'), 'profile_name', t('Enter your first name.'), t('Personal information'), 'textfield', -10, 1, 1, 2, 0);
  db_query($sql, t('Last name'), 'profile_last_name', t('Enter your last name.'), t('Personal information'), 'textfield', -9, 1, 1, 2, 0);
  db_query($sql, t('Location'), 'profile_location', t('Where are you located?'), t('Personal information'), 'textfield', -8, 0, 0, 2, 0);
  db_query($sql, t('My interests'), 'profile_interests', t('What are your interests, hobbies, etc?'), t('Personal information'), 'textarea', -7, 0, 0, 2, 0);
  db_query($sql, t('About me'), 'profile_aboutme', t('Explain a little about yourself.'), t('Personal information'), 'textarea', -6, 0, 0, 2, 0); 
  
  // Work Information
  db_query($sql, t('Job title'), 'profile_job', t('What is your job title?'), t('Work information'), 'textfield', -10, 0, 1, 2, 0);
  db_query($sql, t('Organization'), 'profile_organization', t('Which organization or department are you a part of?'), t('Work information'), 'textfield', -9, 0, 1, 2, 0);
}

/**
 * Configure input filters
 */
function drupal_commons_config_filter() {
  // Force filter format and filter IDs
  // Necessary because Drupal doesn't use machine names for everything
  
  // Filtered HTML
  db_query("UPDATE {filters} f INNER JOIN {filter_formats} ff ON f.format = ff.format SET f.format = 1 WHERE ff.name = 'Filtered HTML'");
  db_query("UPDATE {filter_formats} SET format = 1 WHERE name = 'Filtered HTML'");
  
  // Full HTML
  db_query("UPDATE {filters} f INNER JOIN {filter_formats} ff ON f.format = ff.format SET f.format = 2 WHERE ff.name = 'Full HTML'");
  db_query("UPDATE {filter_formats} SET format = 2 WHERE name = 'Full HTML'");
  
  // PHP code
  db_query("UPDATE {filters} f INNER JOIN {filter_formats} ff ON f.format = ff.format SET f.format = 3 WHERE ff.name = 'PHP code'");
  db_query("UPDATE {filter_formats} SET format = 3 WHERE name = 'PHP code'");
  
  // Messaging
  db_query("UPDATE {filters} f INNER JOIN {filter_formats} ff ON f.format = ff.format SET f.format = 4 WHERE ff.name = 'Messaging plain text'");
  db_query("UPDATE {filter_formats} SET format = 4 WHERE name = 'Messaging plain text'");
  
  // Let community and content manager role use Full HTML
  db_query("UPDATE {filter_formats} SET roles = ',3,4,' WHERE name = 'Full HTML'");
    
  // Create a "links-only" filter format that Shoutbox will use
  db_query("INSERT INTO {filter_formats} (format, name, cache) VALUES (5, 'Links Only', 1)");
  
  // Add filters to the format
  db_query("INSERT INTO {filters} (format, module, delta, weight) VALUES (5, 'filter', 0, -10)");
  db_query("INSERT INTO {filters} (format, module, delta, weight) VALUES (5, 'filter', 2, -9)");
  
  // Adjust settings for the filter
  variable_set('filter_url_length_5', 60);
  variable_set('filter_html_5', 1);
  variable_set('filter_html_help_5', 0);
  variable_set('allowed_html_5', '');
  
  // Set allowed HTML tags for Filter HTML format
  variable_set('allowed_html_1', DRUPAL_COMMONS_FILTERED_HTML);
}

/**
 * Configure password policy
 */
function drupal_commons_config_password() {  
  // Add the password policy
  $policy = new stdClass;
  $policy->pid = 1;
  $policy->name = t('Constraints');
  $policy->description = t('Default list of password constraints');
  $policy->enabled = 1;
  $policy->policy = array(
    'alphanumeric' => 7,  // Contain at least 7 alphanumeric chars
    'username' => 1,      // Must not equal the username
    'length' => 7,        // Must be longer than 7 chars
    'punctuation' => 0,   // Punctuation is required
  );
  $policy->policy = serialize($policy->policy);
  $policy->created = time();
  drupal_write_record('password_policy', $policy);
  
  // Attach the policy to the authenticated user role
  $policy_role = new stdClass;
  $policy_role->rid = 2;
  $policy_role->pid = $policy->pid;
  drupal_write_record('password_policy_role', $policy_role);
  
  // Make the restrictions visible when changing your password
  variable_set('password_policy_show_restrictions', 1);
}

/**
 * Configure wysiwyg
 */
function drupal_commons_config_wysiwyg() {
  // Load external file containing editor settings
  include_once('drupal_commons_editor.inc'); 
  
  // Add settings for 'Filtered HTML'
  $item = new stdClass;
  $item->format = 1;
  $item->editor = DRUPAL_COMMONS_EDITOR;
  $item->settings = serialize(drupal_commons_editor_settings('Filtered HTML'));
  drupal_write_record('wysiwyg', $item);
  
  // Add settings for 'Full HTML'
  $item = new stdClass;
  $item->format = 2;
  $item->editor = DRUPAL_COMMONS_EDITOR;
  $item->settings = serialize(drupal_commons_editor_settings('Full HTML'));
  drupal_write_record('wysiwyg', $item);
}

/**
 * Configure user_relationships
 */
function drupal_commons_config_ur() {
  // Add initial relationship type 'Friend'
  $relationship = new stdClass;
  $relationship->name = t(DRUPAL_COMMONS_RELATIONSHIP_SINGULAR);
  $relationship->plural_name = t(DRUPAL_COMMONS_RELATIONSHIP_PLURAL);
  $relationship->requires_approval = 1;
  $relationship->expires_val = 0;
  $relationship->is_oneway = 0;
  $relationship->is_reciprocal = 0; 
  $is_type = TRUE;
  $type = 'insert';
  
  // Save relationship
  drupal_write_record('user_relationship_types', $relationship);

  // Alert other modules about the new relationship
  $hook = 'user_relationships'. ($is_type ? '_type' : '');
  foreach (module_implements($hook) as $module) {
    $function = $module .'_'. $hook;
    $function($type, $relationship);
  }
}

/**
 * Configure heartbeat
 */
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

/**
 * Configure ctools
 */
function drupal_commons_config_ctools() {
  ctools_include('context');
  ctools_include('plugins');
  
  // Enable node view override (variants imported via Features)
  $page = page_manager_get_page_cache('node_view');
  if ($function = ctools_plugin_get_function($page->subtask, 'enable callback')) {
    $result = $function($page, FALSE);

    if (!empty($page->changed)) {
      page_manager_set_page_cache($page);
    }
  }
  
  // Enable profile view override (variant imported via Features) 
  $page = page_manager_get_page_cache('user_view');
  if ($function = ctools_plugin_get_function($page->subtask, 'enable callback')) {
    $result = $function($page, FALSE);

    if (!empty($page->changed)) {
      page_manager_set_page_cache($page);
    }
  }
}

/**
 * Configure roles
 */
function drupal_commons_config_roles() {
  // Add the "Community Manager" role
  db_query("INSERT INTO {role} (rid, name) VALUES (3, '%s')", t(DRUPAL_COMMONS_MANAGER_ROLE));
  
  // Add the "Content Manager" role
  db_query("INSERT INTO {role} (rid, name) VALUES (4, '%s')", t(DRUPAL_COMMONS_CONTENT_ROLE));
  
  // Make sure first user is a "Community Manager"
  db_query("INSERT INTO {users_roles} (uid, rid) VALUES (1, 3)");
}

/**
 * Configure permissions
 * 
 * Avoid using Features because we expect these to be changed
 */
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
    $perm = new stdClass;
    $perm->rid = $role_data['rid'];
    $perm->perm = implode($role_data['permissions'], ', ');
    drupal_write_record('permission', $perm);
  }
}

/**
 * Configure views
 * 
 * Disable unneeded views to avoid confusion
 * This is helpful because we've overridden many OG views
 */
function drupal_commons_config_views() {
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
  
/**
 * Configure theme
 */
function drupal_commons_config_theme() {
  // Disable garland
  db_query("UPDATE {system} SET status = 0 WHERE type = 'theme' and name = '%s'", 'garland');
  
  // Enable Fusion
  db_query("UPDATE {system} SET status = 1 WHERE type = 'theme' and name = '%s'", 'fusion_core');
  
  // Enable Commons theme
  db_query("UPDATE {system} SET status = 1 WHERE type = 'theme' and name = '%s'", DRUPAL_COMMONS_THEME);
  
  // Set Commons theme as the default
  variable_set('theme_default', DRUPAL_COMMONS_THEME);
  
  // Refresh registry
  list_themes(TRUE);
  drupal_rebuild_theme_registry();
}

/**
 * Configure default images
 * 
 * The group and profile default images need to be processed by ImageCache
 * and stored in the files directory
 */
function drupal_commons_config_images() {
  // Copy default user image to files directory
  $user_image = 'profiles/drupal_commons/images/default-user.png';
  file_copy($user_image, 0, FILE_EXISTS_REPLACE); // Defaults to files directory
  
  // Copy default group image to files directory
  $group_image = 'profiles/drupal_commons/images/default-group.png';
  file_copy($group_image, 0, FILE_EXISTS_REPLACE); // Defaults to files directory
  
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
  $file = new stdClass;
  $file->uid = 1;
  $file->filename = 'default-group.png';
  $file->filepath = file_directory_path() . '/' . $file->filename;
  $file->filemime = 'image/png';
  $file->filesize = filesize($group_image);
  $file->status = 1;
  $file->timestamp = time();
  drupal_write_record('files', $file);
}

/**
 * Configure variables
 * 
 * These should be set but not enforced by Strongarm
 */
function drupal_commons_config_vars() {
  // Set a default point amount so userpoints works out-of-the-box
  variable_set('userpoints_post_page', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_post_blog', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_post_poll', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_post_discussion', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_post_document', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_post_event', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_post_group', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_post_wiki', DRUPAL_COMMONS_POINTS_NODE);
  variable_set('userpoints_user_picture', DRUPAL_COMMONS_POINTS_PICTURE);
  variable_set('userpoints_post_comment', DRUPAL_COMMONS_POINTS_COMMENT);
  variable_set('shoutbox_points_amount', DRUPAL_COMMONS_POINTS_SHOUT);
  
  // Some Shoutbox tweaks
  variable_set('shoutbox_filter_format', 5);
  variable_set('shoutbox_escape_html', 0);
  variable_set('shoutbox_expire', 120);
  variable_set('shoutbox_showamount_block', 8);
  
  // Show large amount of tags on tag cloud page
  variable_set('tagadelic_page_amount', 500);
  
  // Preprocess JS and CSS files
  variable_set('preprocess_css', 1);
  variable_set('preprocess_js', 1);
  
  // Keep errors in the log and off the screen
  variable_set('error_level', 0);
  
  // Don't restrict user profile image upload size
  variable_set('user_picture_file_size', '');
}

/**
 * Various actions needed to clean up after the installation
 */
function drupal_commons_cleanup() {
  // Rebuild node access database - required after OG installation
  node_access_rebuild();
  
  // Rebuild node types
  node_types_rebuild();
  
  // Clear drupal message queue for non-warning/errors
  drupal_get_messages('status', TRUE);

  // Clear out caches
  $core = array('cache', 'cache_block', 'cache_filter', 'cache_page');
  $cache_tables = array_merge(module_invoke_all('flush_caches'), $core);
  foreach ($cache_tables as $table) {
    cache_clear_all('*', $table, TRUE);
  }
  
  // Clear out JS and CSS caches
  drupal_clear_css_cache();
  drupal_clear_js_cache();
  
  
  // Some features will need reverting
  $revert = array(
    'commons_core' => array('menu_links'),
    'commons_notifications' => array('variable'),
    'commons_blog' => array('menu_links'),
    'commons_event' => array('menu_links'),
    'commons_poll' => array('menu_links'),
    'commons_document' => array('menu_links'),
    'commons_discussion' => array('menu_links'),
    'commons_wiki' => array('menu_links', 'variable'),
    'commons_home' => array('page_manager_pages'),
  );
  features_revert($revert);
  
  // Say hello to the dog!
  watchdog('commons', t('Welcome to Drupal Commons from Acquia!'));
  
  // Finish the installation
  variable_set('install_task', 'profile-finished');
}

/**
 * Alter the install profile configuration form and provide timezone location options.
 */
function system_form_install_configure_form_alter(&$form, $form_state) {
  // Taken from Open Atrium
  if (function_exists('date_timezone_names') && function_exists('date_timezone_update_site')) {
    $form['server_settings']['date_default_timezone']['#access'] = FALSE;
    $form['server_settings']['#element_validate'] = array('date_timezone_update_site');
    $form['server_settings']['date_default_timezone_name'] = array(
      '#type' => 'select',
      '#title' => t('Default time zone'),
      '#default_value' => NULL,
      '#options' => date_timezone_names(FALSE, TRUE),
      '#description' => t('Select the default site time zone. If in doubt, choose the timezone that is closest to your location which has the same rules for daylight saving time.'),
      '#required' => TRUE,
    );
  }
}
