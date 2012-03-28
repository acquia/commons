<?php

// Define the default WYSIWYG editor
define('DRUPAL_COMMONS_EDITOR', 'ckeditor');

// Define the default theme
define('DRUPAL_COMMONS_DEFAULT_THEME', 'commons_origins');

/**
 * Return an array of the modules to be enabled when this profile is installed.
 * 
 * To save time during installation, only enable module here that are either
 * required by Features or not included in any Commons features
 *
 * @return
 *   An array of modules to enable.
 */
function drupal_commons_profile_modules() {
  $modules = array(
    // Default Drupal modules.
    'color', 'comment', 'help', 'menu', 'taxonomy', 'dblog', 'profile',
    'search', 'tracker', 'php', 'path', 'contact',
    
    // CTools
    'ctools', 
    
    // Context
    'context',
    
    // Date
    'date_api', 'date_timezone',
    
    // Misc
    'vertical_tabs', 'transliteration', 'password_policy',
    
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
  $logo = '<a href="http://drupal.org/project/commons" target="_blank"><img alt="Commons" title="Commons" src="./profiles/drupal_commons/images/logo.png"></img></a>';
  $description = st('Select this profile to install the Commons distribution for powering your community website. Commons provides provides blogging, discussions, user profiles, and other useful community features for both private communities (e.g. an Intranet), or public communities (e.g. a customer community).');
  $description .= '<br/>' . $logo;
  
  return array(
    'name' => 'Commons',
    'description' => $description,
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
  $tasks['configure-features'] = st('Select features');
  $tasks['configure-theme'] = st('Select theme');
  $tasks['install-commons'] = st('Install Commons');
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
  // Skip to the configure task
  if ($task == 'profile') {
    $task = 'configure-features';  
  }
  
  // If we're using Drush to install, skip the forms
  if (defined('DRUSH_BASE_PATH')) {
    drupal_commons_include('drush');
    _drupal_commons_drush_tasks($task);
  }
  
  // Provide a form to choose features
  if ($task == 'configure-features') {
    drupal_commons_include('form');
    $output = drupal_get_form('drupal_commons_features_form', $url);
  }
  
  // Provide a form to choose the theme
  if ($task == 'configure-theme') {
    drupal_commons_include('form');
    $output = drupal_get_form('drupal_commons_theme_form', $url);
  }
  
  // Installation batch process
  if ($task == 'install-commons') {
    // Determine the installation operations
    $operations = array();
    
    // Pre-installation operations
    $operations[] = array('drupal_commons_build_directories', array());
    $operations[] = array('drupal_commons_config_taxonomy', array());
    
    // Feature installation operations
    $features = variable_get('commons_selected_features', array());
    // The Acquia Network feature module is deprecated
    // per http://drupal.org/node/1408284.
    if (in_array('acquia_network_subscription', $features)) {
      unset($features['feature-acquia_network_subscription']);
      drupal_install_modules(array('acquia_agent', 'acquia_spi'));
    }
    

    foreach ($features as $feature) {
      $operations[] = array('features_install_modules', array(array($feature)));
    }

    // Post-installation operations
    $operations[] = array('drupal_commons_config_filter', array());
    $operations[] = array('drupal_commons_config_password', array());
    $operations[] = array('drupal_commons_config_wysiwyg', array());
    $operations[] = array('drupal_commons_config_ur', array());
    $operations[] = array('drupal_commons_config_views', array());
    $operations[] = array('drupal_commons_config_images', array());
    $operations[] = array('drupal_commons_config_vars', array());
    $operations[] = array('drupal_commons_config_tidy_node_links', array());

    // Build the batch process
    $batch = array(
      'operations' => $operations,
      'title' => st('Configuring Commons'),
      'error_message' => st('An error occurred. Please try reinstalling again.'),
      'finished' => 'drupal_commons_cleanup',
    );
  
    // Start the batch
    variable_set('install_task', 'install-commons-batch');
    batch_set($batch);
    batch_process($url, $url);
  }
  
  // Persist the page while batch executes
  if ($task == 'install-commons-batch') {
    include_once 'includes/batch.inc';
    $output = _batch_page();
  }
  
  return $output;
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
  // Add free-tagging vocabulary for content
  $vocab = array(
    'name' => st('Tags'),
    'description' => st('Free-tagging vocabulary for all content items'),
    'multiple' => '0',
    'required' => '0',
    'hierarchy' => '0',
    'relations' => '1',
    'tags' => '1',
    'module' => 'taxonomy',
  );
  taxonomy_save_vocabulary($vocab); 
  
  // Store the vocabulary id
  variable_set('commons_tags_vid', $vocab['vid']);
}

/**
 * Configure input filters
 */
function drupal_commons_config_filter() {
  // Force filter format and filter IDs
  $filters_sql = "UPDATE {filters} f INNER JOIN {filter_formats} ff ON f.format = ff.format SET f.format = %d WHERE ff.name = '%s'";
  $filter_formats = "UPDATE {filter_formats} SET format = %d WHERE name = '%s'";
  
  // Filtered HTML
  db_query($filters_sql, 1, 'Filtered HTML');
  db_query($filter_formats, 1, 'Filtered HTML');
  
  // Full HTML
  db_query($filters_sql, 2, 'Full HTML');
  db_query($filter_formats, 2, 'Full HTML');
  
  // PHP code
  db_query($filters_sql, 3, 'PHP code');
  db_query($filter_formats, 3, 'PHP code');
  
  // Messaging
  db_query($filters_sql, 4, 'Messaging plain text');
  db_query($filter_formats, 4, 'Messaging plain text');
  
  // Let community and content manager role use Full HTML
  db_query("UPDATE {filter_formats} SET roles = ',3,4,' WHERE name = 'Full HTML'");
    
  // Create a "links-only" filter format
  $format = new stdClass;
  $format->format = 5;
  $format->name = st('Links only');
  $format->cache = 1;
  drupal_write_record('filter_formats', $format);
  
  // Add filters to the format
  $filter = new stdClass;
  $filter->format = 5;
  $filter->module = 'filter';
  $filter->delta = 0;
  $filter->weight = -10;
  drupal_write_record('filters', $filter);
  
  $filter = new stdClass;
  $filter->format = 5;
  $filter->module = 'filter';
  $filter->delta = 2;
  $filter->weight = -9;
  drupal_write_record('filters', $filter);
  
  // Adjust settings for the filter
  variable_set('filter_url_length_5', 60);
  variable_set('filter_html_5', 1);
  variable_set('filter_html_help_5', 0);
  variable_set('allowed_html_5', '');
  
  // Remove the HTML filter from Filtered HTML
  db_query("DELETE FROM {filters} WHERE format = 1 AND module = 'filter' AND delta = 0");
  
  // Add WYSIWYG filter to Filtered HTML
  $filter = new stdClass;
  $filter->format = 1;
  $filter->module = 'wysiwyg_filter';
  $filter->delta = 0;
  $filter->weight = -8;
  drupal_write_record('filters', $filter);
  
  // Adjust the weight of the HTML corrector for Filtered HTML
  db_query("UPDATE {filters} SET weight = -7 WHERE module = 'filter' AND delta = 3");
}

/**
 * Configure password policy
 */
function drupal_commons_config_password() {  
  // Add the password policy
  $policy = new stdClass;
  $policy->pid = 1;
  $policy->name = st('Constraints');
  $policy->description = st('Default list of password constraints');
  $policy->enabled = 1;
  $policy->policy = array(
    'alphanumeric' => 7,  // Contain at least 7 alphanumeric chars
    'username' => 1,      // Must not equal the username
    'length' => 7,        // Must be longer than 7 chars
    'punctuation' => 0,   // Punctuation isn't required
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
  drupal_commons_include('editor'); 
  
  $settings = drupal_commons_editor_settings();
  
  // Add settings for 'Filtered HTML'
  $item = new stdClass;
  $item->format = 1;
  $item->editor = DRUPAL_COMMONS_EDITOR;
  $item->settings = serialize($settings['Filtered HTML']);
  drupal_write_record('wysiwyg', $item);
  
  // Add settings for 'Full HTML'
  $item = new stdClass;
  $item->format = 2;
  $item->editor = DRUPAL_COMMONS_EDITOR;
  $item->settings = serialize($settings['Full HTML']);
  drupal_write_record('wysiwyg', $item);
}

/**
 * Configure user_relationships
 */
function drupal_commons_config_ur() {
  // Add initial relationship type 'Friend'
  $relationship = new stdClass;
  $relationship->name = st('follower');
  $relationship->plural_name = st('users you follow');
  $relationship->requires_approval = 0;
  $relationship->expires_val = 0;
  $relationship->is_oneway = 1;
  $relationship->is_reciprocal = 1; 
  $type = 'insert';
  
  // Save relationship
  drupal_write_record('user_relationship_types', $relationship);

  // Alert other modules about the new relationship
  $hook = 'user_relationships_type';
  foreach (module_implements($hook) as $module) {
    $function = $module .'_'. $hook;
    $function($type, $relationship);
  }
}

/**
 * Configure views
 * 
 * Disable unneeded views to avoid confusion
 * This is helpful because we've cloned many OG views
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
  // Show large amount of tags on tag cloud page
  variable_set('tagadelic_page_amount', 500);
  
  // Preprocess JS and CSS files
  variable_set('preprocess_css', 1);
  variable_set('preprocess_js', 1);
  
  // Keep errors in the log and off the screen
  variable_set('error_level', 0);
  
  // Don't restrict user profile image upload size
  variable_set('user_picture_file_size', '');
  
  // Set user terms to use the "tags" vocabulary we created
  $vid = variable_get('commons_tags_vid', 1);
  variable_set('user_terms_vocabs', array($vid => $vid));
}

/**
 * Configure tidy node links
 */
function drupal_commons_config_tidy_node_links() {
  $theme = variable_get('theme_default','garland');
  if ($theme == 'commons_origins') {
    drupal_install_modules(array('tidy_node_links'));
  }
}

/**
 * Create an initial group with a discussion
 */
function drupal_commons_create_group() {
  drupal_commons_include('node');
  
  // Create the group
  $group = _drupal_commons_default_group_node();
  node_save($group);
  
  // Check if discussion nodes were enabled
  if (in_array('commons_discussion', variable_get('commons_selected_features', array()))) {
    // Create the discussion
    $node = _drupal_commons_default_discussion_node();
    $node->og_groups = array($group->nid => $group->nid);
    node_save($node);
  }
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
    'commons_seo' => array('variable'),
    'commons_blog' => array('menu_links', 'user_permission'),
    'commons_event' => array('menu_links'),
    'commons_poll' => array('menu_links'),
    'commons_document' => array('menu_links'),
    'commons_discussion' => array('menu_links'),
    'commons_wiki' => array('menu_links', 'variable'),
    'commons_home' => array('page_manager_pages'),
    'commons_reputation' => array('menu_links'),
    'commons_admin' => array('user_permission'),
    'commons_answers' => array('user_permission'),
  );
  
  // Make sure we only try to revert features we've enabled
  $enabled = variable_get('commons_selected_features', array('commons_core'));
  
  foreach ($revert as $feature => $value) {
    if (!in_array($feature, $enabled)) {
      unset($revert[$feature]);
    }
  }
  features_revert($revert);
  
  // Say hello to the dog!
  watchdog('commons', st('Welcome to Commons from Acquia!'));
  
  // Create a test group which contains a node
  drupal_commons_create_group();
  // Rebuild Activity Log templates.
  activity_log_rebuild_everything();
  // Remove the feature choices
  variable_del('commons_selected_features');
  
  // Finish the installation
  variable_set('install_task', 'profile-finished');
}

/**
 * Helper function to load include files
 * 
 * @param $name
 *   The file name without the .inc extension
 * @param $dir
 *   The directory containing the include file
 */
function drupal_commons_include($name, $dir = 'includes') {
  require_once("profiles/drupal_commons/{$dir}/{$name}.inc");
}

/**
 * Alter the install profile selection form
 */
function system_form_install_select_profile_form_alter(&$form, $form_state) {
  foreach($form['profile'] as $key => $element) {
    // Set Commons as the default
    $form['profile'][$key]['#value'] = 'drupal_commons';
  }
}

/**
 * Alter the install profile configuration
 */
function system_form_install_configure_form_alter(&$form, $form_state) {
  // Add option to turn on forced login
  $form['site_information']['commons_force_login'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force users to login'),
    '#description' => t('If checked, users will be required to log into the site to access it. Users who are not logged in will be redirected to a login page. Select this setting if your Commons site must be closed to the public, such as a company intranet.'),
  );
  
  // Add timezone options required by date (Taken from Open Atrium)
  if (function_exists('date_timezone_names') && function_exists('date_timezone_update_site')) {
    $form['server_settings']['date_default_timezone']['#access'] = FALSE;
    $form['server_settings']['#element_validate'] = array('date_timezone_update_site');
    $form['server_settings']['date_default_timezone_name'] = array(
      '#type' => 'select',
      '#title' => t('Default time zone'),
      '#default_value' => NULL,
      '#options' => date_timezone_names(FALSE, TRUE),
      '#description' => st('Select the default site time zone. If in doubt, choose the timezone that is closest to your location which has the same rules for daylight saving time.'),
      '#required' => TRUE,
    );
  }
  
  // Add an additional submit handler to process the form
  $form['#submit'][] = 'drupal_commons_install_configure_form_submit';
}

/**
 * Submit handler for the installation configure form
 */
function drupal_commons_install_configure_form_submit(&$form, &$form_state) {
  variable_set('commons_force_login', $form_state['values']['commons_force_login']);
}
