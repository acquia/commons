<?php

/**
 * @file
 * Variables for the Commons Site Homepage module.
 */

/**
 * Implements hook_variable_group_info().
 */
function commons_site_homepage_variable_group_info() {
  $groups['commons_site_homepage'] = array(
    'title' => t('Commons Site Homepage'),
    'description' => t("Text that will be shown on your community's homepage to help new visitors understand what your community is about and why they should join."),
  );

  return $groups;
}

/**
 * Implements hook_variable_info().
 */
function commons_site_homepage_variable_info($options) {
  $variable['commons_anonymous_welcome_title'] = array(
    'type' => 'string',
    'title' => t('Welcome headline', array(), $options),
    'description' => t('A short description of the community that visitors can understand at a glance.'),
    'default' => 'The open-source alternative for enterprise-scale business software',
    'group' => 'commons_site_homepage',
  );
  $variable['commons_anonymous_welcome_body'] = array(
    'type' => 'string',
    'title' => t('Welcome body text', array(), $options),
    'description' => t('A couple of sentences elaborating about your community.'),
    'default' => 'Enable social networking to create productive interactions. Whether your community is public or private, Commons does it!',
    'group' => 'commons_site_homepage',
  );

  return $variable;
}
