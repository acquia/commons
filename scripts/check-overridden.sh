#!/bin/bash

: ${DRUSH:=drush}
: ${DRUSH_ARGS:=}

PANOPOLY_FEATURES="panopoly_admin panopoly_core panopoly_demo panopoly_images panopoly_magic panopoly_pages panopoly_search panopoly_theme panopoly_users panopoly_widgets panopoly_wysiwyg" 

# TODO: We should make sure that 'diff' is downloaded first!
$DRUSH $DRUSH_ARGS en -y diff

OVERRIDDEN=0
for panopoly_feature in $PANOPOLY_FEATURES; do
  echo "Checking $panopoly_feature..."
  if $DRUSH $DRUSH_ARGS features-diff $panopoly_feature 2>&1 | grep -v 'Feature is in its default state'; then
    OVERRIDDEN=1
  fi
done

exit $OVERRIDDEN
