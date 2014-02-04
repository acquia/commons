<?php

/**
 * @file
 * Hooks provided by the Commons Utility Links module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Define utility links.
 *
 * This hook allows modules to register utility links for the functionality that
 * they provide. For example, a social integration module could use it to
 * register a "Find Friends" utility link which points to a page where the
 * current user can search for other site users that they have connected with on
 * social networks such as Twitter or Facebook.
 *
 * @return
 *   An associative array of utility links whose keys are used as its CSS class.
 *   Each link should be itself an array, with the same elements used in
 *   theme_links(), except for the addition of a 'weight' element that is used
 *   for ordering the links.
 *
 * For a detailed usage example, see commons_utility_links.module.
 *
 * @see theme_links()
 * @see hook_commons_utility_links_alter()
 */
function hook_commons_utility_links() {
  $links = array();

  if (user_is_logged_in()) {
    global $user;
    $account = $user;
    $links['find_fiends']= array(
      'href' => 'user/' . $account->uid . '/find_friends',
      'title' => t('Find friends'),
    );
  }

  return $links;
}

/**
 * Perform alterations on utility links.
 *
 * @param $links
 *   An associative array of utility links whose keys are used as its CSS class.
 *   Each link should be itself an array, with the same elements used in
 *   theme_links(), except for the addition of a 'weight' element that is used
 *   for ordering the links.
 *
 * @see theme_links()
 * @see hook_commons_utility_links()
 */
function hook_commons_utility_links_alter(&$links) {
  // Change the title of the user account link from the user's name to
  // 'Account'.
  $links['name']['title'] = t('Account');
}

/**
 * @} End of "addtogroup hooks".
 */
