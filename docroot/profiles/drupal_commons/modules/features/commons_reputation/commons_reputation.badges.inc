<?php

/**
 * An array containing the default user badges
 */
function commons_reputation_default_badges() {
  $path = drupal_get_path('module', 'commons_reputation');
  $badges = array();
  
  // Badge: super_contributor
  $badge = new stdClass;
  $badge->name = t('Super contributor');
  $badge->image = $path . '/images/bars-5.png';
  $badge->weight = -5;
  $badge->fixedweight = 1;
  $badges['super_contributor'] = $badge;
  
  // Badge: frequent_contributor
  $badge = new stdClass;
  $badge->name = t('Frequent contributor');
  $badge->image = $path . '/images/bars-4.png';
  $badge->weight = -4;
  $badge->fixedweight = 1;
  $badges['frequent_contributor'] = $badge;
  
  // Badge: regular_contributor
  $badge = new stdClass;
  $badge->name = t('Regular contributor');
  $badge->image = $path . '/images/bars-3.png';
  $badge->weight = -3;
  $badge->fixedweight = 1;
  $badges['regular_contributor'] = $badge;
  
  // Badge: contributor
  $badge = new stdClass;
  $badge->name = t('Contributor');
  $badge->image = $path . '/images/bars-2.png';
  $badge->weight = -2;
  $badge->fixedweight = 1;
  $badges['contributor'] = $badge;
  
  // Badge: member
  $badge = new stdClass;
  $badge->name = t('Member');
  $badge->image = $path . '/images/bars-1.png';
  $badge->weight = -1;
  $badge->fixedweight = 1;
  $badges['member'] = $badge;
  
  // Badge: user
  $badge = new stdClass;
  $badge->name = t('User');
  $badge->image = $path . '/images/bars-0.png';
  $badge->weight = 0;
  $badge->fixedweight = 1;
  $badges['user'] = $badge;
  
  return $badges;
}
