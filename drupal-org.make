api = 2
core = 7.x

; Contributed modules.

projects[addressfield][type] = "module"
projects[addressfield][subdir] = "contrib"

projects[acquia_connector][type] = "module"
projects[acquia_connector][subdir] = "contrib"

projects[advancedqueue][type] = "module"
projects[advancedqueue][subdir] = "contrib"

projects[apachesolr][type] = "module"
projects[apachesolr][subdir] = "contrib"

projects[apachesolr_og][version] = "1.x-dev"
projects[apachesolr_og][type] = "module"
projects[apachesolr_og][subdir] = "contrib"

projects[apachesolr_proximity][type] = "module"
projects[apachesolr_proximity][subdir] = "contrib"

projects[connector][version] = "1.x-dev"
projects[connector][type] = "module"
projects[connector][subdir] = "contrib"

projects[ckeditor][type] = "module"
projects[ckeditor][subdir] = "contrib"
projects[ckeditor][download][type] = "git"
projects[ckeditor][download][url] = "http://git.drupal.org/project/ckeditor.git"
; Use Libraries API for ckeditor
; http://drupal.org/node/1063482#comment-6964504
projects[ckeditor][download][branch] = "7.x-1.x"
projects[ckeditor][revision] = "f6abbda"

projects[ctools][type] = "module"
projects[ctools][subdir] = "contrib"
; http://drupal.org/node/1494860#comment-6204438
projects[ctools][patch][] = "http://drupal.org/files/ctools-dependent-js-broken-with-jquery-1.7-1494860-30.patch"

projects[custom_search][type] = "module"
projects[custom_search][subdir] = "contrib"
projects[custom_search][version] = "1.x-dev"

projects[date][type] = "module"
projects[date][subdir] = "contrib"

projects[date_facets][type] = "module"
projects[date_facets][subdir] = "contrib"

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

projects[entitycache][type] = "module"
projects[entitycache][subdir] = "contrib"

projects[entityreference][version] = "1.x-dev"
projects[entityreference][type] = "module"
projects[entityreference][subdir] = "contrib"

projects[edit_profile][type] = "module"
projects[edit_profile][subdir] = "contrib"

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
projects[flag_abuse][version] = "2.x-dev"

projects[redirect][type] = "module"
projects[redirect][subdir] = "contrib"

projects[http_client][version] = "2.x-dev"
projects[http_client][type] = "module"
projects[http_client][subdir] = "contrib"

projects[admin_icons][version] = "1.x-dev"
projects[admin_icons][type] = "module"
projects[admin_icons][subdir] = "contrib"

projects[libraries][type] = "module"
projects[libraries][subdir] = "contrib"

projects[link][type] = "module"
projects[link][subdir] = "contrib"

projects[menu_attributes][type] = "module"
projects[menu_attributes][subdir] = "contrib"

projects[message][type] = "module"
projects[message][subdir] = "contrib"
projects[message][version] = "1.x-dev"


projects[message_notify][type] = "module"
projects[message_notify][subdir] = "contrib"
projects[message_notify][version] = "2.x-dev"

projects[message_subscribe][type] = "module"
projects[message_subscribe][subdir] = "contrib"
projects[message_subscribe][version] = "1.x-dev"

projects[memcache][type] = "module"
projects[memcache][subdir] = "contrib"

projects[metatag][type] = "module"
projects[metatag][subdir] = "contrib"
; Support for rel=author link in head
; http://drupal.org/node/1865228#comment-6839604
projects[metatag][patch][] = "http://drupal.org/files/metatag-n1865228-3.patch"

projects[module_filter][type] = "module"
projects[module_filter][subdir] = "contrib"

projects[mollom][type] = "module"
projects[mollom][subdir] = "contrib"

projects[oauth][version] = "3.x-dev"
projects[oauth][type] = "module"
projects[oauth][subdir] = "contrib"

projects[oauthconnector][version] = "1.x-dev"
projects[oauthconnector][type] = "module"
projects[oauthconnector][subdir] = "contrib"

projects[og][version] = "2.x-dev"
projects[og][type] = "module"
projects[og][subdir] = "contrib"
; Language tweak for 'user has been added to [group]'
; http://drupal.org/node/1842830
projects[og][patch][] = "http://drupal.org/files/og-add-group-message.patch"

projects[panelizer][type] = "module"
projects[panelizer][version] = "3.x-dev"
projects[panelizer][subdir] = "contrib"

projects[panels][type] = "module"
projects[panels][subdir] = "contrib"
; Fatal error: Call to undefined function panels_get_layouts()
; http://drupal.org/node/1828684#comment-6694732
projects[panels][patch][] = "http://drupal.org/files/1828684-layout-fix-6.patch"

; PHP 5.3.9 Strict Warning on Panels Empty Value
; http://drupal.org/node/1632898#comment-6412840
projects[panels][patch][] = "http://drupal.org/files/panels-n1632898-15.patch"

projects[pathauto][type] = "module"
projects[pathauto][subdir] = "contrib"

projects[pm_existing_pages][type] = "module"
projects[pm_existing_pages][subdir] = "contrib"

projects[quicktabs][type] = "module"
projects[quicktabs][subdir] = "contrib"
projects[quicktabs][version] = "3.x-dev"

projects[radioactivity][type] = "module"
projects[radioactivity][subdir] = "contrib"
projects[radioactivity][version] = "2.x-dev"

; Notice error for accessing an undefined array element
; http://drupal.org/node/1816252#comment-6617208
projects[radioactivity][patch][] = "http://drupal.org/files/undefined_array-1816252-1.patch"

; Radioactivity not compatible with Memcache module
; http://drupal.org/node/1860216
projects[radioactivity][patch][] = "http://drupal.org/files/radioactivity-memcache.patch"

projects[r4032login][type] = "module"
projects[r4032login][subdir] = "contrib"

projects[rate][type] = "module"
projects[rate][subdir] = "contrib"

projects[realname][type] = "module"
projects[realname][subdir] = "contrib"

projects[registration][version] = "1.x-dev"
projects[registration][type] = "module"
projects[registration][subdir] = "contrib"

projects[rules][type] = "module"
projects[rules][subdir] = "contrib"

projects[search_facetapi][type] = "module"
projects[search_facetapi][subdir] = "contrib"

projects[sharethis][type] = "module"
projects[sharethis][subdir] = "contrib"

projects[facetapi][type] = "module"
projects[facetapi][subdir] = "contrib"

projects[rich_snippets][type] = "module"
projects[rich_snippets][subdir] = "contrib"

projects[schemaorg][type] = "module"
projects[schemaorg][subdir] = "contrib"

projects[strongarm][version] = "2.x-dev"
projects[strongarm][type] = "module"
projects[strongarm][subdir] = "contrib"

projects[timeago][type] = "module"
projects[timeago][subdir] = "contrib"
projects[timeago][version] = "2.x-dev"

; Provide a dedicated date type:
; http://drupal.org/node/1427226#comment-6638836
projects[timeago][patch][] = "http://drupal.org/files/1427226-timeago-date-type.patch"

projects[title][type] = "module"
projects[title][subdir] = "contrib"

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

projects[views_litepager][type] = "module"
projects[views_litepager][subdir] = "contrib"

projects[votingapi][type] = "module"
projects[votingapi][subdir] = "contrib"

; Commons contrib modules:

projects[commons_activity_streams][type] = "module"
projects[commons_activity_streams][subdir] = "contrib"
projects[commons_activity_streams][version] = "3.x-dev"

projects[commons_body][type] = "module"
projects[commons_body][subdir] = "contrib"
projects[commons_body][version] = "3.x-dev"

projects[commons_bw][type] = "module"
projects[commons_bw][subdir] = "contrib"
projects[commons_bw][version] = "3.x-dev"

projects[commons_content_moderation][type] = "module"
projects[commons_content_moderation][subdir] = "contrib"
projects[commons_content_moderation][version] = "3.x-dev"

projects[commons_documents][type] = "module"
projects[commons_documents][subdir] = "contrib"
projects[commons_documents][version] = "3.x-dev"

projects[commons_groups][type] = "module"
projects[commons_groups][subdir] = "contrib"
projects[commons_groups][version] = "3.x-dev"

projects[commons_events][type] = "module"
projects[commons_events][subdir] = "contrib"
projects[commons_events][version] = "3.x-dev"

projects[commons_featured][type] = "module"
projects[commons_featured][subdir] = "contrib"
projects[commons_featured][version] = "3.x-dev"

projects[commons_follow][type] = "module"
projects[commons_follow][subdir] = "contrib"
projects[commons_follow][version] = "3.x-dev"

projects[commons_location][type] = "module"
projects[commons_location][subdir] = "contrib"
projects[commons_location][version] = "3.x-dev"

projects[commons_misc][type] = "module"
projects[commons_misc][subdir] = "contrib"
projects[commons_misc][version] = "3.x-dev"


projects[commons_notices][type] = "module"
projects[commons_notices][subdir] = "contrib"
projects[commons_notices][version] = "3.x-dev"

projects[commons_notify][type] = "module"
projects[commons_notify][subdir] = "contrib"
projects[commons_notify][version] = "3.x-dev"

projects[commons_pages][type] = "module"
projects[commons_pages][subdir] = "contrib"
projects[commons_pages][version] = "3.x-dev"

projects[commons_posts][subdir] = "contrib"
projects[commons_posts][type] = "module"
projects[commons_posts][download][type] = "git"
projects[commons_posts][download][url] = "http://git.drupal.org/project/commons_posts.git"
projects[commons_posts][download][branch] = "7.x-3.x"


projects[commons_polls][type] = "module"
projects[commons_polls][subdir] = "contrib"
projects[commons_polls][version] = "3.x-dev"

projects[commons_profile_base][type] = "module"
projects[commons_profile_base][subdir] = "contrib"
projects[commons_profile_base][version] = "3.x-dev"

projects[commons_profile_social][type] = "module"
projects[commons_profile_social][subdir] = "contrib"
projects[commons_profile_social][version] = "3.x-dev"

projects[commons_q_a][type] = "module"
projects[commons_q_a][subdir] = "contrib"
projects[commons_q_a][version] = "3.x-dev"

projects[commons_radioactivity][type] = "module"
projects[commons_radioactivity][subdir] = "contrib"
projects[commons_radioactivity][version] = "3.x-dev"

projects[commons_like][type] = "module"
projects[commons_like][subdir] = "contrib"
projects[commons_like][version] = "3.x-dev"

projects[commons_search][type] = "module"
projects[commons_search][subdir] = "contrib"
projects[commons_search][version] = "3.x-dev"

projects[commons_site_homepage][type] = "module"
projects[commons_site_homepage][subdir] = "contrib"
projects[commons_site_homepage][version] = "3.x-dev"

projects[commons_utility_links][type] = "module"
projects[commons_utility_links][subdir] = "contrib"
projects[commons_utility_links][version] = "3.x-dev"

projects[commons_user_profile_pages][type] = "module"
projects[commons_user_profile_pages][subdir] = "contrib"
projects[commons_user_profile_pages][version] = "3.x-dev"

projects[commons_wikis][type] = "module"
projects[commons_wikis][subdir] = "contrib"
projects[commons_wikis][version] = "3.x-dev"

projects[commons_wysiwyg][type] = "module"
projects[commons_wysiwyg][subdir] = "contrib"

projects[commons_topics][type] = "module"
projects[commons_topics][subdir] = "contrib"
projects[commons_topics][version] = "3.x-dev"

; Contributed themes.

projects[adaptivetheme][type] = "theme"
projects[adaptivetheme][subdir] = "contrib"
projects[adaptivetheme][download][type] = "git"
projects[adaptivetheme][download][url] = "http://git.drupal.org/project/adaptivetheme.git"
projects[adaptivetheme][download][branch] = "7.x-3.x"
projects[adaptivetheme][download][revision] = "8e46acc"

projects[sky][type] = "theme"
projects[sky][subdir] = "contrib"

projects[commons_origins][type] = "theme"
projects[commons_origins][version] = "3.x-dev"
projects[commons_origins][subdir] = "contrib"

; Libraries.
; NOTE: These need to be listed in http://drupal.org/packaging-whitelist.

libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.0/ckeditor_4.0_standard.tar.gz"
libraries[ckeditor][type] = "libraries"

libraries[timeago][download][type] = "get"
libraries[timeago][type] = "libraries"
; We'd like to switch to a specific commit hash,
; pending http://drupal.org/node/1821996#comment-6678062.
libraries[timeago][download][url] = "https://raw.github.com/rmm5t/jquery-timeago/master/jquery.timeago.js"
