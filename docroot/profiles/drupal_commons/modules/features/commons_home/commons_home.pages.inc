<?php

/**
 * @file
 *   Page callbacks for commons_home
 */

/**
 * Page callback for the homepage
 */
function commons_home_homepage() {
  // Active the context
  context_set('context', 'home', context_load('home'));  
  // Return nothing, as context handles the content
  return '';
}
