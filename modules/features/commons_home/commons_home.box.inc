<?php

/**
 * Implementation of hook_default_box().
 */
function commons_home_default_box() {
  $export = array();

  $box = new stdClass;
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'homepage_info_box';
  $box->plugin_key = 'simple';
  $box->title = 'Community Powered Innovation';
  $box->description = 'Homepage Commons information';
  $box->options = array(
    'body' => '<p>Welcome to your Commons installation, your ready-to-use solution for communities of all types - from intranets to customer community sites and more. Next, you may want to:</p>

<div class="intro-textblock">
<h3>Customize your site</h3>
Add your own look &amp; feel, configure how it works, or extend it by installing more Drupal modules.
</div>

<div class="intro-textblock">
<h3>Link in the Network</h3>
Enable your free Acquia Network trial to add content recommendations, advanced site search &amp; other features to your site.</div>

<div class="intro-textblock">
<h3>Get help</h3>
Find a consultant to add new features, get support for what\'s there, or learn how to grow your community.
</div>

<p><a class="intro-morebutton" href="http://commons.acquia.com/get-started" target="_blank">Learn more</a></p>',
    'format' => '2',
  );
  $export['homepage_info_box'] = $box;

  return $export;
}
