<?php

/**
 * Provide the core profile fields
 */
function commons_profile_profile_fields() {
  $fields = array();

  // Personal Information
  
  // First name
  $field = new stdClass;
  $field->title = t('First name');
  $field->name = 'profile_name';
  $field->explanation = t('Enter your first name.');
  $field->category = t('Personal information');
  $field->type = 'textfield';
  $field->weight = -10;
  $field->required = 1;
  $field->register = 1;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[$field->name] = $field;
  
  // Last name
  $field = new stdClass;
  $field->title = t('Last name');
  $field->name = 'profile_last_name';
  $field->explanation = t('Enter your last name.');
  $field->category = t('Personal information');
  $field->type = 'textfield';
  $field->weight = -9;
  $field->required = 1;
  $field->register = 1;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[$field->name] = $field;
  
  // Location
  $field = new stdClass;
  $field->title = t('Location');
  $field->name = 'profile_location';
  $field->explanation = t('Where are you located?');
  $field->category = t('Personal information');
  $field->type = 'textfield';
  $field->weight = -8;
  $field->required = 0;
  $field->register = 0;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[$field->name] = $field;
  
  // My interests
  $field = new stdClass;
  $field->title = t('My interests');
  $field->name = 'profile_interests';
  $field->explanation = t('What are your interests, hobbies, etc?');
  $field->category = t('Personal information');
  $field->type = 'textarea';
  $field->weight = -7;
  $field->required = 0;
  $field->register = 0;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[$field->name] = $field;
  
  // About me
  $field = new stdClass;
  $field->title = t('About me');
  $field->name = 'profile_aboutme';
  $field->explanation = t('Explain a little about yourself.');
  $field->category = t('Personal information');
  $field->type = 'textarea';
  $field->weight = -6;
  $field->required = 0;
  $field->register = 0;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[$field->name] = $field;
  
  // Twitter
  $field = new stdClass;
  $field->title = t('Twitter');
  $field->name = 'profile_twitter_link';
  $field->explanation = t('Link to your Twitter account, e.g. http://twitter.com/your-username.');
  $field->category = t('Personal information');
  $field->type = 'url';
  $field->weight = -5;
  $field->required = 0;
  $field->register = 0;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[$field->name] = $field;
  
  // Facebook
  $field = new stdClass;
  $field->title = t('Facebook');
  $field->name = 'profile_facebook_link';
  $field->explanation = t('Link to your Facebook account, e.g. http://facebook.com/your-username.');
  $field->category = t('Personal information');
  $field->type = 'url';
  $field->weight = -4;
  $field->required = 0;
  $field->register = 0;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[$field->name] = $field;
  
  // LinkedIn
  $field = new stdClass;
  $field->title = t('LinkedIn');
  $field->name = 'profile_linkedin_link';
  $field->explanation = t('Link to your LinkedIn account, e.g. http://linkedin.com/in/your-username.');
  $field->category = t('Personal information');
  $field->type = 'url';
  $field->weight = -3;
  $field->required = 0;
  $field->register = 0;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[$field->name] = $field;
  
  // Work Information
  
  // Job title
  $field = new stdClass;
  $field->title = t('Job title');
  $field->name = 'profile_job';
  $field->explanation = t('What is your job title?');
  $field->category = t('Work information');
  $field->type = 'textfield';
  $field->weight = -10;
  $field->required = 0;
  $field->register = 1;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[$field->name] = $field;
  
  // Organization
  $field = new stdClass;
  $field->title = t('Organization');
  $field->name = 'profile_organization';
  $field->explanation = t('Which organization or department are you a part of?');
  $field->category = t('Work information');
  $field->type = 'textfield';
  $field->weight = -9;
  $field->required = 0;
  $field->register = 1;
  $field->visibility = 2;
  $field->autocomplete = 0;
  $fields[$field->name] = $field;
  
  return $fields;
}
