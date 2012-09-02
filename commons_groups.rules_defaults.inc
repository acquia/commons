<?php


function commons_groups_default_rules_configuration_alter(&$configs) {
  // Disable default OG new content notifications.
  // The language doesn't correspond to Commons' open groups model and we use
  // commons_follow and commons_follow_notify for new content notifications.
  $configs['rules_og_member_active']->active = FALSE;
}