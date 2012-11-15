api = 2
core = 7.x

; Contributed modules.

projects[addressfield][type] = "module"
projects[addressfield][subdir] = "contrib"

projects[aloha][version] = "2.x-dev"
projects[aloha][type] = "module"
projects[aloha][subdir] = "contrib"

projects[connector][version] = "1.x-dev"
projects[connector][type] = "module"
projects[connector][subdir] = "contrib"


projects[ctools][type] = "module"
projects[ctools][subdir] = "contrib"
; http://drupal.org/node/1494860#comment-6204438
projects[ctools][patch][] = "http://drupal.org/files/ctools-dependent-js-broken-with-jquery-1.7-1494860-30.patch"

projects[custom_search][type] = "module"
projects[custom_search][subdir] = "contrib"
projects[custom_search][download][type] = "git"
projects[custom_search][download][url] = "http://git.drupal.org/project/custom_search.git"
projects[custom_search][download][branch] = "7.x-1.x"

projects[date][type] = "module"
projects[date][subdir] = "contrib"

projects[devel][version] = "1.x-dev"
projects[devel][type] = "module"
projects[devel][subdir] = "contrib"

projects[diff][version] = "2.0"
projects[diff][type] = "module"
projects[diff][subdir] = "contrib"

projects[email_registration][type] = "module"
projects[email_registration][subdir] = "contrib"

projects[entity][type] = "module"
projects[entity][subdir] = "contrib"

projects[entityreference][version] = "1.x-dev"
projects[entityreference][type] = "module"
projects[entityreference][subdir] = "contrib"

projects[entityreference_prepopulate][type] = "module"
projects[entityreference_prepopulate][subdir] = "contrib"

projects[features][version] = "2.x-dev"
projects[features][type] = "module"
projects[features][subdir] = "contrib"

; Separate fields from field instances.
; http://drupal.org/node/1064472#comment-6438406
projects[features][patch][] = "http://drupal.org/files/1064472_features_field_split_23.patch"

projects[flag][type] = "module"
projects[flag][subdir] = "contrib"

projects[flag_abuse][type] = "module"
projects[flag_abuse][subdir] = "contrib"
projects[flag_abuse][download][type] = "git"
projects[flag_abuse][download][url] = "http://git.drupal.org/project/flag_abuse.git"
projects[flag_abuse][download][branch] = "7.x-2.x"

projects[http_client][version] = "2.x-dev"
projects[http_client][type] = "module"
projects[http_client][subdir] = "contrib"

projects[admin_icons][version] = "1.x-dev"
projects[admin_icons][type] = "module"
projects[admin_icons][subdir] = "contrib"

projects[jquery_update][version] = "2.x-dev"
projects[jquery_update][type] = "module"
projects[jquery_update][subdir] = "contrib"

projects[link][type] = "module"
projects[link][subdir] = "contrib"

projects[menu_attributes][type] = "module"
projects[menu_attributes][subdir] = "contrib"

projects[message][type] = "module"
projects[message][download][type] = "git"
projects[message][download][url] = "http://git.drupal.org/project/message.git"
projects[message][download][branch] = "7.x-1.x"
projects[message][subdir] = "contrib"

projects[message_notify][type] = "module"
projects[message_notify][download][type] = "git"
projects[message_notify][download][url] = "http://git.drupal.org/project/message_notify.git"
projects[message_notify][download][branch] = "7.x-2.x"
projects[message_notify][subdir] = "contrib"

projects[message_subscribe][type] = "module"
projects[message_subscribe][download][type] = "git"
projects[message_subscribe][download][url] = "http://git.drupal.org/project/message_subscribe.git"
projects[message_subscribe][download][branch] = "7.x-1.x"
projects[message_subscribe][subdir] = "contrib"

projects[module_filter][type] = "module"
projects[module_filter][subdir] = "contrib"

projects[oauth][version] = "3.x-dev"
projects[oauth][type] = "module"
projects[oauth][subdir] = "contrib"

projects[oauthconnector][version] = "1.x-dev"
projects[oauthconnector][type] = "module"
projects[oauthconnector][subdir] = "contrib"

projects[og][version] = "2.x-dev"
projects[og][type] = "module"
projects[og][subdir] = "contrib"

projects[panelizer][type] = "module"
projects[panelizer][version] = "3.x-dev"
projects[panelizer][subdir] = "contrib"

projects[panels][type] = "module"
projects[panels][subdir] = "contrib"
; Fatal error: Call to undefined function panels_get_layouts()
; http://drupal.org/node/1828684#comment-6694732
projects[panels][patch][] = "http://drupal.org/files/1828684-layout-fix-6.patch"

projects[queue_mail][type] = "module"
projects[queue_mail][subdir] = "contrib"

projects[quicktabs][type] = "module"
projects[quicktabs][subdir] = "contrib"

projects[radioactivity][type] = "module"
projects[radioactivity][subdir] = "contrib"
; Notice error for accessing an undefined array element
; http://drupal.org/node/1816252#comment-6617208
projects[radioactivity][patch][] = "http://drupal.org/files/undefined_array-1816252-1.patch"

projects[realname][type] = "module"
projects[realname][subdir] = "contrib"

projects[registration][version] = "1.x-dev"
projects[registration][type] = "module"
projects[registration][subdir] = "contrib"

projects[rules][type] = "module"
projects[rules][subdir] = "contrib"

projects[strongarm][version] = "2.x-dev"
projects[strongarm][type] = "module"
projects[strongarm][subdir] = "contrib"

projects[timeago][type] = "module"
projects[timeago][subdir] = "contrib"
projects[timeago][download][type] = "git"
projects[timeago][download][url] = "http://git.drupal.org/project/timeago.git"
projects[timeago][download][branch] = "7.x-2.x"

; Provide a dedicated date type:
; http://drupal.org/node/1427226#comment-6638836
projects[timeago][patch][] = "http://drupal.org/files/1427226-timeago-date-type.patch"

projects[token][type] = "module"
projects[token][subdir] = "contrib"

projects[views][type] = "module"
projects[views][subdir] = "contrib"
projects[views][version] = "3.x-dev"

projects[views_field_view][type] = "module"
projects[views_field_view][subdir] = "contrib"

projects[views_load_more][type] = "module"
projects[views_load_more][subdir] = "contrib"

projects[views_bulk_operations][type] = "module"
projects[views_bulk_operations][subdir] = "contrib"

projects[votingapi][type] = "module"
projects[votingapi][subdir] = "contrib"

; Commons contrib modules:

projects[commons_activity_streams][type] = "module"
projects[commons_activity_streams][subdir] = "contrib"
projects[commons_activity_streams][download][type] = "git"
projects[commons_activity_streams][download][url] = "http://git.drupal.org/project/commons_activity_streams.git"
projects[commons_activity_streams][download][branch] = "7.x-3.x"

projects[commons_body][type] = "module"
projects[commons_body][subdir] = "contrib"
projects[commons_body][download][type] = "git"
projects[commons_body][download][url] = "http://git.drupal.org/project/commons_body.git"
projects[commons_body][download][branch] = "7.x-3.x"

projects[commons_bw][type] = "module"
projects[commons_bw][subdir] = "contrib"
projects[commons_bw][download][type] = "git"
projects[commons_bw][download][url] = "http://git.drupal.org/project/commons_bw.git"
projects[commons_bw][download][branch] = "7.x-3.x"

projects[commons_content_moderation][type] = "module"
projects[commons_content_moderation][subdir] = "contrib"
projects[commons_content_moderation][download][type] = "git"
projects[commons_content_moderation][download][url] = "http://git.drupal.org/project/commons_content_moderation.git"
projects[commons_content_moderation][download][branch] = "7.x-3.x"

projects[commons_documents][type] = "module"
projects[commons_documents][subdir] = "contrib"
projects[commons_documents][download][type] = "git"
projects[commons_documents][download][url] = "http://git.drupal.org/project/commons_documents.git"
projects[commons_documents][download][branch] = "7.x-3.x"

projects[commons_groups][type] = "module"
projects[commons_groups][subdir] = "contrib"
projects[commons_groups][download][type] = "git"
projects[commons_groups][download][url] = "http://git.drupal.org/project/commons_groups.git"
projects[commons_groups][download][branch] = "7.x-3.x"

projects[commons_events][type] = "module"
projects[commons_events][subdir] = "contrib"
projects[commons_events][download][type] = "git"
projects[commons_events][download][url] = "http://git.drupal.org/project/commons_events.git"
projects[commons_events][download][branch] = "7.x-3.x"

projects[commons_featured][type] = "module"
projects[commons_featured][subdir] = "contrib"
projects[commons_featured][download][type] = "git"
projects[commons_featured][download][url] = "http://git.drupal.org/project/commons_featured.git"
projects[commons_featured][download][branch] = "7.x-3.x"

projects[commons_follow][type] = "module"
projects[commons_follow][subdir] = "contrib"
projects[commons_follow][download][type] = "git"
projects[commons_follow][download][url] = "http://git.drupal.org/project/commons_follow.git"
projects[commons_follow][download][branch] = "7.x-3.x"

projects[commons_location][type] = "module"
projects[commons_location][subdir] = "contrib"
projects[commons_location][download][type] = "git"
projects[commons_location][download][url] = "http://git.drupal.org/project/commons_location.git"
projects[commons_location][download][branch] = "7.x-3.x"

projects[commons_misc][type] = "module"
projects[commons_misc][subdir] = "contrib"
projects[commons_misc][download][type] = "git"
projects[commons_misc][download][url] = "http://git.drupal.org/project/commons_misc.git"
projects[commons_misc][download][branch] = "7.x-3.x"

projects[commons_notices][type] = "module"
projects[commons_notices][subdir] = "contrib"
projects[commons_notices][download][type] = "git"
projects[commons_notices][download][url] = "http://git.drupal.org/project/commons_notices.git"
projects[commons_notices][download][branch] = "7.x-3.x"

projects[commons_notify][type] = "module"
projects[commons_notify][subdir] = "contrib"
projects[commons_notify][download][type] = "git"
projects[commons_notify][download][url] = "http://git.drupal.org/project/commons_notify.git"
projects[commons_notify][download][branch] = "7.x-3.x"

projects[commons_pages][type] = "module"
projects[commons_pages][subdir] = "contrib"
projects[commons_pages][download][type] = "git"
projects[commons_pages][download][url] = "http://git.drupal.org/project/commons_pages.git"
projects[commons_pages][download][branch] = "7.x-3.x"

projects[commons_posts][type] = "module"
projects[commons_posts][subdir] = "contrib"
projects[commons_posts][download][type] = "git"
projects[commons_posts][download][url] = "http://git.drupal.org/project/commons_posts.git"
projects[commons_posts][download][branch] = "7.x-3.x"

projects[commons_profile_base][type] = "module"
projects[commons_profile_base][subdir] = "contrib"
projects[commons_profile_base][version] = "2.x-dev"

projects[commons_profile_social][type] = "module"
projects[commons_profile_social][subdir] = "contrib"
projects[commons_profile_social][download][type] = "git"
projects[commons_profile_social][download][url] = "http://git.drupal.org/project/commons_profile_social.git"
projects[commons_profile_social][download][branch] = "7.x-3.x"

projects[commons_radioactivity][type] = "module"
projects[commons_radioactivity][subdir] = "contrib"
projects[commons_radioactivity][download][type] = "git"
projects[commons_radioactivity][download][url] = "http://git.drupal.org/project/commons_radioactivity.git"
projects[commons_radioactivity][download][branch] = "7.x-3.x"


projects[commons_search][type] = "module"
projects[commons_search][subdir] = "contrib"
projects[commons_search][download][type] = "git"
projects[commons_search][download][url] = "http://git.drupal.org/project/commons_search.git"
projects[commons_search][download][branch] = "7.x-3.x"

projects[commons_site_homepage][type] = "module"
projects[commons_site_homepage][subdir] = "contrib"
projects[commons_site_homepage][download][type] = "git"
projects[commons_site_homepage][download][url] = "http://git.drupal.org/project/commons_site_homepage.git"
projects[commons_site_homepage][download][branch] = "7.x-3.x"

projects[commons_user_profile_pages][type] = "module"
projects[commons_user_profile_pages][subdir] = "contrib"
projects[commons_user_profile_pages][download][type] = "git"
projects[commons_user_profile_pages][download][url] = "http://git.drupal.org/project/commons_user_profile_pages.git"
projects[commons_user_profile_pages][download][branch] = "7.x-3.x"

projects[commons_wikis][type] = "module"
projects[commons_wikis][subdir] = "contrib"
projects[commons_wikis][download][type] = "git"
projects[commons_wikis][download][url] = "http://git.drupal.org/project/commons_wikis.git"
projects[commons_wikis][download][branch] = "7.x-3.x"

projects[commons_wysiwyg][type] = "module"
projects[commons_wysiwyg][subdir] = "contrib"
projects[commons_wysiwyg][download][type] = "git"
projects[commons_wysiwyg][download][url] = "http://git.drupal.org/project/commons_wysiwyg.git"
projects[commons_wysiwyg][download][branch] = "7.x-3.x"

projects[commons_topics][type] = "module"
projects[commons_topics][subdir] = "contrib"
projects[commons_topics][download][type] = "git"
projects[commons_topics][download][url] = "http://git.drupal.org/project/commons_topics.git"
projects[commons_topics][download][branch] = "7.x-3.x"

; Contributed themes.

projects[adaptivetheme][type] = "theme"
projects[adaptivetheme][subdir] = "contrib"
projects[adaptivetheme][download][type] = "git"
projects[adaptivetheme][download][url] = "http://git.drupal.org/project/adaptivetheme.git"
projects[adaptivetheme][download][branch] = "7.x-3.x"
; Refactor require_once() instances into discrete functions:
; http://drupal.org/node/1776730#comment-6705274
projects[adaptivetheme][patch][] = "http://drupal.org/files/1776730-adaptivetheme-refactor-require-into-discrete-functions-21.patch"

projects[sky][type] = "theme"
projects[sky][subdir] = "contrib"

projects[commons_origins][type] = "theme"
projects[commons_origins][download][type] = "git"
projects[commons_origins][download][url] = "http://git.drupal.org/project/commons_origins.git"
projects[commons_origins][download][branch] = "7.x-3.x"
projects[commons_origins][subdir] = "contrib"

; Libraries.
; NOTE: These need to be listed in http://drupal.org/packaging-whitelist.

libraries[timeago][download][type] = "get"
libraries[timeago][destination] = "modules/contrib"
; We'd like to switch to a specific commit hash,
; pending http://drupal.org/node/1821996#comment-6678062.
libraries[timeago][download][url] = "https://raw.github.com/rmm5t/jquery-timeago/master/jquery.timeago.js"
