#!/bin/bash

: ${DRUSH:=drush}
: ${DRUSH_ARGS:=}

COMMONS_FEATURES="commons_activity_page commons_activity_streams commons_bw commons_content_moderation commons_events commons_events_pages commons_featured commons_follow commons_follow_group commons_follow_node commons_follow_term commons_follow_user commons_groups commons_groups_directory commons_groups_pages commons_like commons_location commons_media commons_misc commons_notify commons_pages commons_polls commons_posts commons_profile_base commons_profile_social commons_q_a commons_q_a_pages commons_radioactivity commons_radioactivity_groups commons_search commons_search_core commons_site_homepage commons_social_sharing commons_trusted_contacts commons_user_profile_pages commons_wikis commons_wikis_pages commons_wysiwyg commons_documents commons_notices"

# TODO: We should make sure that 'diff' is downloaded first!
$DRUSH $DRUSH_ARGS en -y diff

OVERRIDDEN=0
for commons_feature in $COMMONS_FEATURES; do
  echo "Checking $commons_feature..."
  if $DRUSH $DRUSH_ARGS features-diff $commons_feature 2>&1 | grep -v 'Feature is in its default state'; then
    OVERRIDDEN=1
  fi
done

exit $OVERRIDDEN
