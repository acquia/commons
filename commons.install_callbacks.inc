<?php

/**
 * @file
 * Contains Batch API callbacks used during installation.
 */

/**
 * BatchAPI callback.
 *
 * @see commons_install_additional_modules()
 */
function _commons_enable_module($module, $module_name, &$context) {
  module_enable(array($module), FALSE);
  $context['message'] = st('Installed %module module.', array('%module' => $module_name));
}

/**
 * BatchAPI callback.
 *
 * @see commons_demo_content()
 */
function _commons_create_demo_users($operation, &$context) {
  $context['message'] = t('@operation', array('@operation' => $operation));

  // Reset the Flag cache.
  flag_get_flags(NULL, NULL, NULL, TRUE);

  // Create an array of usernames.
  $demo_usernames = array('Jeff Noyes', 'Drew Robertson', 'Lisa Rex', 'Katelyn Fogarty', 'Dharmesh Mistry', 'Erica Ligeski');

  // Create a user for each username.
  foreach ($demo_usernames as $username) {
    list($first_name, $last_name)  = explode(" ", $username);
    $normalized_username = commons_normalize_name($username);
    $password = user_password(8);

    $fields = array(
      'name' => $username,
      'mail' => "{$normalized_username}@example.com",
      'pass' => $password,
      'status' => 1,
      'init' => "{$normalized_username}@example.com",
      'roles' => array(
        DRUPAL_AUTHENTICATED_RID => 'authenticated user',
      ),
    );

    $fields['field_name_first'][LANGUAGE_NONE][0]['value'] = $first_name;
    $fields['field_name_last'][LANGUAGE_NONE][0]['value'] = $last_name;

    $user = user_save(NULL, $fields);

    // Add an avatar to the user account.
    commons_add_user_avatar($user);

    $context['results']['users'][$username] = $user;
  }
}

/**
 * BatchAPI callback.
 *
 * @see commons_demo_content()
 */
function _commons_create_demo_taxonomy_terms($operation, &$context) {
  $context['message'] = t('@operation', array('@operation' => $operation));

  // Create an array of topic names.
  $demo_topic_names = array('brunch', 'Cambridge', 'dining out', 'vegetarian', 'casual', 'meal', 'recipe', 'bbq', 'music', 'festival');

  // Create a taxonomy term for each topic.
  foreach ($demo_topic_names as $topic) {
    $term = new stdClass();
    $term->name = $topic;
    $term->vid = 1;

    taxonomy_term_save($term);

    $context['results']['taxonomy_terms'][$topic] = $term;
  }
}

/**
 * BatchAPI callback.
 *
 * @see commons_demo_content()
 */
function _commons_create_demo_groups($operation, &$context) {
  $context['message'] = t('@operation', array('@operation' => $operation));

  $demo_users = $context['results']['users'];

  // Group: Boston
  $boston_group = new stdClass();
  $boston_group->type = 'group';
  node_object_prepare($boston_group);

  $boston_group->title = 'Boston';
  $boston_group->body[LANGUAGE_NONE][0]['value'] = commons_veggie_ipsum();
  $boston_group->uid = $demo_users['Jeff Noyes']->uid;
  $boston_group->language = LANGUAGE_NONE;
  $boston_group->created = time() - 604800;
  $boston_group->status = 1;
  node_save($boston_group);

  $context['results']['groups']['boston'] = $boston_group;

  // Group: New York City
  $nyc_group = new stdClass();
  $nyc_group->type = 'group';
  node_object_prepare($nyc_group);

  $nyc_group->title = 'New York City';
  $nyc_group->body[LANGUAGE_NONE][0]['value'] = commons_veggie_ipsum();
  $nyc_group->uid = $demo_users['Drew Robertson']->uid;
  $nyc_group->language = LANGUAGE_NONE;
  $nyc_group->status = 1;
  // Make the group 1 week old:
  $nyc_group->created = time() - 604800;
  node_save($nyc_group);

  $context['results']['groups']['new_york_city'] = $nyc_group;
}

/**
 * BatchAPI callback.
 *
 * @see commons_demo_content()
 */
function _commons_create_demo_content($operation, &$context) {
  $context['message'] = t('@operation', array('@operation' => $operation));

  $demo_users = $context['results']['users'];
  $demo_taxonomy_terms = $context['results']['taxonomy_terms'];
  $demo_groups = $context['results']['groups'];

  // Post: Best brunch places in Cambridge
  $post = new stdClass();
  $post->type = 'post';
  node_object_prepare($post);

  $post->title = 'Best brunch places in Cambridge';
  $post->uid = $demo_users['Lisa Rex']->uid;
  $post->language = LANGUAGE_NONE;
  // 1:30 ago.
  $post->created = time() - 5400;
  $post->body[LANGUAGE_NONE][0]['value'] = "My aunt and I have been trying a lot of brunch places in Cambridge. Here's our favorites: <ul><li>North Street Grille for their breads
<li>Mixtura for the souffles
<li>The Neighborhood Restaurant for the vast quantities of food
<li>City Girl Cafe for the ambiance <li>Bom Cafe for granola";
  $post->body[LANGUAGE_NONE][0]['format'] = filter_default_format();

  $post->og_group_ref[LANGUAGE_NONE][0]['target_id'] = $demo_groups['boston']->nid;
  $post->field_radioactivity[LANGUAGE_NONE][0]['radioactivity_energy'] = 8;

  $post->field_topics[LANGUAGE_NONE][]['tid'] = $demo_taxonomy_terms['brunch']->tid;
  $post->field_topics[LANGUAGE_NONE][]['tid'] = $demo_taxonomy_terms['Cambridge']->tid;
  $post->field_topics[LANGUAGE_NONE][]['tid'] = $demo_taxonomy_terms['dining out']->tid;

  node_save($post);

  // Wiki: How to create a veggie burger
  $wiki = new stdClass();
  $wiki->type = 'wiki';
  node_object_prepare($wiki);
  $wiki->created = time() - 604800;
  $wiki->title = 'How to create a veggie burger';
  $wiki->uid = $demo_users['Dharmesh Mistry']->uid;
  $wiki->language = LANGUAGE_NONE;
  $wiki->body[LANGUAGE_NONE][0]['value'] = "Celtuce quandong gumbo coriander avocado yarrow broccoli rabe parsnip nori mung bean watercress taro pea sprouts cress. Bush tomato water spinach radish green bean okra spinach garlic cress. Cucumber squash tigernut swiss chard celery cabbage beet greens nori groundnut grape melon seakale. Earthnut pea kakadu plum chicory potato plantain fennel gumbo chickweed gourd cauliflower wakame green bean epazote taro quandong. Celery turnip kombu lotus root lettuce sierra leone bologi kale cauliflower gumbo parsnip taro welsh onion melon asparagus green bean beet greens black-eyed pea jícama. Kohlrabi lentil turnip greens plantain bush tomato leek arugula courgette amaranth yarrow.";
  $wiki->body[LANGUAGE_NONE][0]['format'] = filter_default_format();

  $wiki->og_group_ref[LANGUAGE_NONE][0]['target_id'] = $demo_groups['boston']->nid;
  $wiki->field_radioactivity[LANGUAGE_NONE][0]['radioactivity_energy'] = 8;

  $wiki->field_topics[LANGUAGE_NONE][]['tid'] = $demo_taxonomy_terms['vegetarian']->tid;
  $wiki->field_topics[LANGUAGE_NONE][]['tid'] = $demo_taxonomy_terms['casual']->tid;
  $wiki->field_topics[LANGUAGE_NONE][]['tid'] = $demo_taxonomy_terms['meal']->tid;
  $wiki->field_topics[LANGUAGE_NONE][]['tid'] = $demo_taxonomy_terms['recipe']->tid;

  node_save($wiki);

  // Event: Ribfest Boston 2012
  $event = new stdClass();
  $event->type = 'event';
  node_object_prepare($event);

  $event->title = 'Ribfest Boston 2012';
  $event->uid = $demo_users['Katelyn Fogarty']->uid;
  $event->language = LANGUAGE_NONE;
  $event->body[LANGUAGE_NONE][0]['value'] = "<strong>What ignited in 1999 as a community block party has exploded into one of Boston's most anticipated street festivals.</strong> Averaging 50,000 pounds of ribs and BBQ from more than 30 restaurants, Ribfest Boston 2013 is expected to draw more than 50,000 people. As a nationally recognized music festival, we host a hot blend of Indie, pop, Indie Roots, rock and alt country for one of the most unique band lineups in the city. Families can spend the whole weekend in Kids Square to enjoy live entertainment, inflatables, games and more.";
  $event->body[LANGUAGE_NONE][0]['format'] = filter_default_format();
  $event->og_group_ref[LANGUAGE_NONE][0]['target_id'] = $demo_groups['boston']->nid;

  $event->field_topics[LANGUAGE_NONE][]['tid'] = $demo_taxonomy_terms['bbq']->tid;
  $event->field_topics[LANGUAGE_NONE][]['tid'] = $demo_taxonomy_terms['music']->tid;
  $event->field_topics[LANGUAGE_NONE][]['tid'] = $demo_taxonomy_terms['festival']->tid;

  // The event starts 6 months from now.
  $event->field_date[LANGUAGE_NONE][0]['value'] = format_date(REQUEST_TIME + 15552000, 'custom', 'Y-m-d 10:00:00');
  // The event ends 6 months and one day from now.
  $event->field_date[LANGUAGE_NONE][0]['value2'] = format_date(REQUEST_TIME + 15638400, 'custom', 'Y-m-d 10:00:00');

  $event->field_address[LANGUAGE_NONE][0]['thoroughfare'] = '25 Corporate Drive';
  $event->field_address[LANGUAGE_NONE][0]['premise'] = '4th floor';
  $event->field_address[LANGUAGE_NONE][0]['postal_code'] = '01803';
  $event->field_address[LANGUAGE_NONE][0]['country'] = 'US';
  $event->field_address[LANGUAGE_NONE][0]['location'] = 'Waterfront';
  $event->field_address[LANGUAGE_NONE][0]['administrative_area']  = 'MA';
  $event->field_address[LANGUAGE_NONE][0]['locality'] = 'Boston';
  $event->og_group_ref[LANGUAGE_NONE][0]['target_id'] = $demo_groups['boston']->nid;
  node_save($event);
}

/**
 * BatchAPI callback.
 *
 * @see commons_demo_content()
 */
function _commons_convert_administrator_to_group($operation, &$context) {
  $context['message'] = t('@operation', array('@operation' => $operation));

  $wrapper = entity_metadata_wrapper('user', 1);
  $wrapper->{OG_GROUP_FIELD}->set(TRUE);
  $wrapper->save();

  // Don't display the 'registration settings have been saved' message.
  drupal_get_messages('status', TRUE);
  drupal_get_messages('completed', TRUE);

  // Delete the demo content variable
  variable_del('commons_selected_extras');
}
