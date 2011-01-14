<?php
// $Id$

// Define the forced ID of the free-tagging vocabulary
define('DRUPAL_COMMONS_TAG_ID', 2);

// Define the default WYSIWYG editor
define('DRUPAL_COMMONS_EDITOR', 'ckeditor');

// Define the default theme
define('DRUPAL_COMMONS_THEME', 'acquia_commons');

/**
 * Return an array of the modules to be enabled when this profile is installed.
 * 
 * To save time during installation, only enable module here that are either
 * required by Features or not included in any Commons features
 * 
 * @see
 *   drupal_commons_enable_features()
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
    
    // Panels
    'page_manager', 'panels', 
    
    // Context
    'context',
    
    // Date
    'date_api', 'date_timezone',

    // Taxonomy
    'tagging',
    
    // Misc
    'vertical_tabs', 'transliteration', 'password_policy',
    
    // Theme
    'skinr',
    
    // Strongarm
    'strongarm', 
    
    // Features
    'features',
    
    // Drupal Commons update tracker
    'commons_release',
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
  $logo = '<a href="http://drupal.org/project/commons" target="_blank"><img alt="Drupal Commons" title="Drupal Commons" src="' . base_path() . 'profiles/drupal_commons/images/logo.png' . '"></img></a>';
  $description = st('Select this profile to install the Drupal Commons distribution for powering your community website. Drupal Commons provides provides blogging, discussions, user profiles, and other useful community features for both private communities (e.g. an Intranet), or public communities (e.g. a customer community).');
  $description .= '<br/>' . $logo;
  
  return array(
    'name' => 'Drupal Commons',
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
  $tasks['configure-commons'] = st('Configure Drupal Commons');
  $tasks['install-commons'] = st('Install Drupal Commons');
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
    $task = 'configure-commons';  
  }
  
  // Provide a form to choose features
  if ($task == 'configure-commons') {
    $output = drupal_get_form('drupal_commons_features_form', $url);
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
    foreach ($features as $feature) {
      $operations[] = array('features_install_modules', array(array($feature)));
    }

    // Post-installation operations
    $operations[] = array('drupal_commons_config_roles', array());
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
  
    // Build the batch process
    $batch = array(
      'operations' => $operations,
      'title' => st('Configuring Drupal Commons'),
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
 * Provide a form to choose which features to enable
 */
function drupal_commons_features_form($form_state, $url) {
  drupal_set_title(st('Choose from available features'));
  
  $form = array();
  
  // Help message
  $form['message'] = array(
    '#type' => 'item',
    '#value' => st('The selected features will be enabled after the installation has completed. At any time, you can turn the available features on or off.'),
  );
  
  // Required features
  $form['required'] = array(
    '#type' => 'fieldset',
    '#title' => st('Required'),
    '#description' => t('These features are required for Drupal Commons to operate.'),
  );
  $form['required']['feature-commons_core'] = array(
    '#type' => 'checkbox',
    '#title' => st('Core'),
    '#default_value' => 1,
    '#disabled' => 1,
    '#required' => TRUE,
    '#value' => 1,
    '#description' => st('Provides the essential components for Drupal Commons'),
  );
  $form['required']['feature-commons_home'] = array(
    '#type' => 'checkbox',
    '#title' => st('Home page'),
    '#default_value' => 1,
    '#disabled' => 1,
    '#required' => TRUE,
    '#value' => 1,
    '#description' => st('Provides a community-driven home page.'),
  );
  
  // Content-related features
  $form['content'] = array(
    '#type' => 'fieldset',
    '#title' => st('Content'),
    '#description' => t('Select which content types you wish Drupal Commons to make available to members of Drupal Commons groups. Note: If you de-select any of these, you can always enable them again after installation.'),
  );
  $form['content']['feature-commons_blog'] = array(
    '#type' => 'checkbox',
    '#title' => st('Blogs'),
    '#default_value' => 1,
    '#description' => t('Used by individuals to create personal blog posts within a group.'),
  );
  $form['content']['feature-commons_discussion'] = array(
    '#type' => 'checkbox',
    '#title' => st('Discussions'),
    '#default_value' => 1,
    '#description' => st('Used to create threaded topical discussions within a group.'),
  );
  $form['content']['feature-commons_document'] = array(
    '#type' => 'checkbox',
    '#title' => st('Documents'),
    '#default_value' => 1,
    '#description' => st('Used as a container for attaching documents, images, and other digital files useful to a group.'),
  );
  $form['content']['feature-commons_wiki'] = array(
    '#type' => 'checkbox',
    '#title' => st('Wikis'),
    '#default_value' => 1,
    '#description' => st('A type of page that is editable by all members in a group (vs. editable only its original author).'),
  );
  $form['content']['feature-commons_poll'] = array(
    '#type' => 'checkbox',
    '#title' => st('Polls'),
    '#default_value' => 1,
    '#description' => st('Used to create polls within a group.'),
  );
  $form['content']['feature-commons_event'] = array(
    '#type' => 'checkbox',
    '#title' => st('Events & calendars'),
    '#default_value' => 1,
    '#description' => st('Used to create an event calendar for a group.'),
  );
  
  // Misc features
  $form['misc'] = array(
    '#type' => 'fieldset',
    '#title' => st('Other functions'),
    '#description' => st('Select which functions you wish to provide in Drupal Commons. Again, if you de-select any of these, you can enable them again after installation.'),
  );
  $form['misc']['feature-commons_dashboard'] = array(
    '#type' => 'checkbox',
    '#title' => st('Dashboard'),
    '#default_value' => 1,
    '#description' => st('A feature that provides a unique-per-user, user-customizable dashboard of recent relevant site activity.'),
  );
  $form['misc']['feature-commons_notifications'] = array(
    '#type' => 'checkbox',
    '#title' => st('Notifications'),
    '#default_value' => 1,
    '#description' => st('Provides a way for group administrators to pull RSS content into a group from other sources.'),
  );
  $form['misc']['feature-commons_reputation'] = array(
    '#type' => 'checkbox',
    '#title' => st('User awards'),
    '#default_value' => 1,
    '#description' => st('Award users points and badges for performing community-related actions.'),
  );
  $form['misc']['feature-commons_group_aggregator'] = array(
    '#type' => 'checkbox',
    '#title' => st('Content aggregator'),
    '#default_value' => 1,
    '#description' => st('Provides a way for group administrators to pull RSS content into a group from other sources.'),
  );
  $form['misc']['feature-commons_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Admin assist'),
    '#default_value' => 1,
    '#description' => st('Bundles a variety of administrative interface tools in one place. (Bundled as a single feature so administrators who wish to use alternate admin interface tools can turn off the defaults easily.).'),
  );
  $form['misc']['feature-commons_seo'] = array(
    '#type' => 'checkbox',
    '#title' => st('SEO'),
    '#default_value' => 1,
    '#description' => st('Bundles all SEO-oriented capabilities in a module separate from Drupal Commons Core (for ease of administration).'),
  );
  
  // Acquia features
  $form['acquia'] = array(
    '#type' => 'fieldset',
    '#title' => st('Acquia'),
    '#description' => st('The !an can supplement the functionality of Drupal Commons by providing enhanced site search (faceted search, content recommendations, content biasing, multi-site search, and others using the Apache Solr service), spam protection (using the Mollom service), and more.  A free 30-day trial is available.', array('!an' => l(t('Acquia Network'), 'http://acquia.com/products-services/acquia-network', array('attributes' => array('target' => '_blank'))))),
  );
  $form['acquia']['feature-acquia_network_subscription'] = array(
    '#type' => 'checkbox',
    '#title' => st('Acquia Network'),
    '#default_value' => 0,
    '#description' => st('Select this either if you wish to try a free trial of the Acquia Network or want to enter the keys for your existing Acquia Network subscription.'),
  );
  
  // Redirect URL to remain inside the installation after submission
  $form['url'] = array(
    '#type' => 'value',
    '#value' => $url,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => st('Continue'),
  );
  
  return $form;
}

/**
 * Submit handler for the feature choice form
 */
function drupal_commons_features_form_submit(&$form, &$form_state) {
  // Build an array of chosen features
  $features = array();
  
  // Extract the selected features from the form
  foreach ($form_state['values'] as $key => $value) {
    if (substr($key, 0, 8) == 'feature-') {
      if ($value == 1) {
        $features[] = substr($key, 8);
      }
    }
  }
  
  // Store a temporary variable to access later
  variable_set('commons_selected_features', $features);
  
  // Initiate the next installation step
  variable_set('install_task', 'install-commons');
  
  // Redirect back to the installation page
  drupal_goto($form_state['values']['url']);
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
    'help' => st('Press enter or click !plus between tags.', array('!plus' => '\'+\'')),
  );
  taxonomy_save_vocabulary($vocab); 
  
  // Force free-tagging vocabulary to a certain ID
  // This is needed for bundled views to work
  db_query("UPDATE {vocabulary} SET vid = %d WHERE name = '%s'",
    DRUPAL_COMMONS_TAG_ID,
    st('Tags')
  );
}

/**
 * Configure profile
 * 
 * Add custom profile fields
 */
function drupal_commons_config_profile() {
  $fields = array();

  // Personal Information
  
  // First name
  $field = new stdClass;
  $field->title = st('First name');
  $field->name = 'profile_name';
  $field->explanation = st('Enter your first name.');
  $field->category = st('Personal information');
  $field->type = 'textfield';
  $field->weight = -10;
  $field->required = 1;
  $field->register = 1;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[] = $field;
  
  // Last name
  $field = new stdClass;
  $field->title = st('Last name');
  $field->name = 'profile_last_name';
  $field->explanation = st('Enter your last name.');
  $field->category = st('Personal information');
  $field->type = 'textfield';
  $field->weight = -9;
  $field->required = 1;
  $field->register = 1;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[] = $field;
  
  // Location
  $field = new stdClass;
  $field->title = st('Location');
  $field->name = 'profile_location';
  $field->explanation = st('Where are you location?');
  $field->category = st('Personal information');
  $field->type = 'textfield';
  $field->weight = -8;
  $field->required = 0;
  $field->register = 0;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[] = $field;
  
  // My interests
  $field = new stdClass;
  $field->title = st('My interests');
  $field->name = 'profile_interests';
  $field->explanation = st('What are your interests, hobbies, etc?');
  $field->category = st('Personal information');
  $field->type = 'textarea';
  $field->weight = -7;
  $field->required = 0;
  $field->register = 0;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[] = $field;
  
  // About me
  $field = new stdClass;
  $field->title = st('About me');
  $field->name = 'profile_aboutme';
  $field->explanation = st('Explain a little about yourself.');
  $field->category = st('Personal information');
  $field->type = 'textarea';
  $field->weight = -6;
  $field->required = 0;
  $field->register = 0;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[] = $field;
  
  // Work Information
  
  // Job title
  $field = new stdClass;
  $field->title = st('Job title');
  $field->name = 'profile_job';
  $field->explanation = st('What is your job title?');
  $field->category = st('Work information');
  $field->type = 'textfield';
  $field->weight = -10;
  $field->required = 0;
  $field->register = 1;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[] = $field;
  
  // Organization
  $field = new stdClass;
  $field->title = st('Organization');
  $field->name = 'profile_organization';
  $field->explanation = st('Which organization or department are you a part of?');
  $field->category = st('Work information');
  $field->type = 'textfield';
  $field->weight = -9;
  $field->required = 0;
  $field->register = 1;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[] = $field;
  
  // Save the fields
  foreach ($fields as $field) {
    drupal_write_record('profile_fields', $field);
  }
}

/**
 * Configure input filters
 */
function drupal_commons_config_filter() {
  // Force filter format and filter IDs
  
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
  require_once('drupal_commons.editor.inc'); 
  
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
  $relationship->name = st('Friend');
  $relationship->plural_name = st('Friends');
  $relationship->requires_approval = 1;
  $relationship->expires_val = 0;
  $relationship->is_oneway = 0;
  $relationship->is_reciprocal = 0; 
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
  // Make sure first user is a "Community Manager"
  $record = new stdClass;
  $record->uid = 1;
  $record->rid = 3;
  drupal_write_record('user_roles', $record);
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
 * Create an initial group with a discussion
 */
function drupal_commons_create_group() {
  module_load_include('inc', 'node', 'node.pages');
  
  // Create the group
  $group = new stdClass;
  $group->type = 'group';
  node_object_prepare($group);
  $group->uid = 1;
  $group->status = 1;
  $group->format = 1;
  $group->revision = 0;
  $group->title = st('Our Community');
  $group->body = st('Drupal Commons provides the software; but we the people need to work out the human aspects of helping this community to succeed. Let&#39;s collaborate on that using this group.');
  $group->teaser = node_teaser($group->body);
  $group->created = time();
  $group->field_featured_group = array(
    0 => array(
      'value' => 'Featured',
    ),
  );
  $group->og_description = st('A group for collaborating to make this community site successful');
  $group->taxonomy['tags'][2] = st('community');
  $group->og_private = 0;
  $group->og_directory = 1;
  $group->og_register = 0;
  $group->og_selective = 0;
  node_save($group);
  
  // Check if discussion nodes were enabled
  if (in_array('commons_discussion', variable_get('commons_selected_features', array()))) {
    // Create the discussion
    $node = new stdClass;
    $node->type = 'discussion';
    node_object_prepare($node);
    $node->uid = 1;
    $node->status = 1;
    $node->format = 1;
    $node->revision = 0;
    $node->title = st('Jumpstarting our community');
    $node->body = st('<p>In Drupal Commons, all content is all created within the context of a &quot;Group&quot;. Start exploring how to use your site by:</p><ul><li><a href="/og">Viewing a list of all the groups</a> on this site. (Note: Only this demonstration group exists by default.)</li><li><a href="/node/add/group">Creating a new group</a> of your own. Before you do, you might find an image / graphic for identification use on the group home page. Perhaps a logo, or ..?</li></ul><p>Once you&#39;ve created your group, start building your community by creating various kinds of content. &nbsp;Drupal Commons lets members of a group create:</p><ul><li>Blog posts. These are just what you think: personal notes from individuals. &nbsp;Note that other users can comment on these posts.</li><li>Documents. If you want to store attached documents that are useful for a group, create a Document page, describe the attachment in the body of the page, and then attach the files you want.</li><li>Discussions. &nbsp;A discussion is just that: Somebody starts by creating a page with a thought, idea, or question. Others can then comment on the initial post. Comments are &quot;threaded&quot; so you can comment on a comment.</li><li>Wikis. All the three posts above work the same: The initial author of a blog/document/discussion is the only person who can edit the &quot;body&quot; of the page. In contrast, any member of a group can edit the body of a Wiki page. &nbsp;That&#39;s what makes Wiki pages special - anybody can edit the content.</li><li>Events. If you have a special thing happening on a given day/time, create an &quot;Event&quot; describing it. These events will show up on the Calendar tab of a group home page.</li><li>Group RSS feed. If there is interesting content coming from outside this site that you want your group to track, pull that content in as an RSS feed to the site.</li></ul><p>There&#39;s more to building a community than the technology; it&#39;s the people &amp; participation that makes a community work. This set of content types should give you all the choices you need to jump-start this community.</p>');
    $node->teaser = node_teaser($node->body);
    $node->created = time();
    $node->field_featured_content[0]['value'] = 'Featured';
    $node->taxonomy['tags'][2] = st('content types, getting started, groups, jumpstart');
    $node->og_public = 1;
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
    'acquia_network_subscription' => array('user_permission')
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
  watchdog('commons', st('Welcome to Drupal Commons from Acquia!'));
  
  // Create a test group which contains a node
  drupal_commons_create_group();
  
  // Remove the feature choices
  variable_del('commons_selected_features');
  
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
      '#description' => st('Select the default site time zone. If in doubt, choose the timezone that is closest to your location which has the same rules for daylight saving time.'),
      '#required' => TRUE,
    );
  }
}
