api = 2
core = 7.x

; Contributed modules.

projects[addressfield][type] = "module"
projects[addressfield][subdir] = "contrib"
projects[addressfield][version] = "1.0-beta3"

projects[acquia_connector][type] = "module"
projects[acquia_connector][subdir] = "contrib"
projects[acquia_connector][version] = "2.8"

projects[advancedqueue][type] = "module"
projects[advancedqueue][subdir] = "contrib"
projects[advancedqueue][version] = "1.0-alpha2"

projects[apachesolr][type] = "module"
projects[apachesolr][subdir] = "contrib"
projects[apachesolr][version] = "1.1"

projects[apachesolr_og][type] = "module"
projects[apachesolr_og][subdir] = "contrib"
projects[apachesolr_og][download][type] = "git"
projects[apachesolr_og][download][url] = "http://git.drupal.org/project/apachesolr_og.git"
projects[apachesolr_og][download][branch] = "7.x-1.x"
projects[apachesolr_og][download]revision] = "49820b4a4fcff7c1c4efe449da033fb6d8711ac5"

projects[apachesolr_proximity][type] = "module"
projects[apachesolr_proximity][subdir] = "contrib"
projects[apachesolr_proximity][version] = "1.0-rc1"

projects[connector][type] = "module"
projects[connector][subdir] = "contrib"
projects[connector][version] = "1.0-beta2"

projects[ckeditor][type] = "module"
projects[ckeditor][subdir] = "contrib"
projects[ckeditor][download][type] = "git"
projects[ckeditor][download][url] = "http://git.drupal.org/project/ckeditor.git"
; Use Libraries API for ckeditor.
; http://drupal.org/node/1063482#comment-6964504
projects[ckeditor][download][branch] = "7.x-1.x"
projects[ckeditor][download][revision] = "f6abbda"

; Fatal error if Libraries module is enabled after CKEditor
; http://drupal.org/node/1898294#comment-6980796
projects[ckeditor][patch][] = "http://drupal.org/files/ckeditor-install-lib-1898294-2.patch"

projects[ctools][type] = "module"
projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.3"

projects[custom_search][type] = "module"
projects[custom_search][subdir] = "contrib"
projects[custom_search][download][type] = "git"
projects[custom_search][download][url] = "http://git.drupal.org/project/custom_search.git"
projects[custom_search][download][branch] = "7.x-1.x"
projects[custom_search][download][revision] = "e6be0ee6f5f7c7e56f09e79d0d3351fd193c0840"

projects[date][type] = "module"
projects[date][subdir] = "contrib"
projects[date][version] = "2.6"

projects[date_facets][type] = "module"
projects[date_facets][subdir] = "contrib"
projects[date_facets][version] = "1.0-beta1"

; Keeping this to the latest version, since it should only be used for development.
projects[devel][version] = "1.x-dev"
projects[devel][type] = "module"
projects[devel][subdir] = "contrib"

projects[diff][type] = "module"
projects[diff][subdir] = "contrib"
projects[diff][version] = "3.2"

projects[email_registration][type] = "module"
projects[email_registration][subdir] = "contrib"
projects[email_registration][version] = "1.1"

projects[entity][type] = "module"
projects[entity][subdir] = "contrib"
projects[entity][version] = "1.0"

; Force LANGUAGE_NONE entities to still display within rendered entities.
; http://drupal.org/node/1782134
projects[entity][patch][] = "http://drupal.org/files/entity-translatable_fields_not_overriding_und_with_empty_values.patch"

projects[entitycache][type] = "module"
projects[entitycache][subdir] = "contrib"
projects[entitycache][version] = "1.1"

projects[entityreference][type] = "module"
projects[entityreference][subdir] = "contrib"
projects[entityreference][download][type] = "git"
projects[entityreference][download][url] = "http://git.drupal.org/project/entityreference.git"
projects[entityreference][download][branch] = "7.x-1.x"
projects[entityreference][download][revision] = "06089a92ee8b269f153064ad3090ce6b464f38aa"

; Profile has no recommended release
projects[edit_profile][type] = "module"
projects[edit_profile][subdir] = "contrib"
projects[edit_profile][version] = "1.0-beta2"

projects[entityreference_prepopulate][type] = "module"
projects[entityreference_prepopulate][subdir] = "contrib"
projects[entityreference_prepopulate][version] = "1.2"

projects[features][type] = "module"
projects[features][subdir] = "contrib"
projects[features][download][type] = "git"
projects[features][download][url] = "http://git.drupal.org/project/features.git"
projects[features][download][branch] = "7.x-2.x"
projects[features][download][revision] = "63db687c75d7880bb5d2652fa9227e3ca6e4e9f0"

; Separate fields from field instances.
; http://drupal.org/node/1064472#comment-7042482
projects[features][patch][] = "http://drupal.org/files/features-instances-1064472-59.patch"

projects[flag][type] = "module"
projects[flag][subdir] = "contrib"
projects[flag][version] = "2.0"

projects[flag_abuse][type] = "module"
projects[flag_abuse][subdir] = "contrib"
projects[flag_abuse][version] = "2.0-alpha1"


projects[redirect][type] = "module"
projects[redirect][subdir] = "contrib"
projects[redirect][version] = "1.0-rc1"

projects[http_client][type] = "module"
projects[http_client][subdir] = "contrib"
projects[http_client][version] = "2.4"

projects[admin_icons][type] = "module"
projects[admin_icons][subdir] = "contrib"
projects[admin_icons][download][type] = "git"
projects[admin_icons][download][url] = "http://git.drupal.org/project/admin_icons.git"
projects[admin_icons][download][branch] = "7.x-1.x"
projects[admin_icons][download][revision] = "60d9f28801533fecc92216a60d444d89d80e7611"

projects[libraries][type] = "module"
projects[libraries][subdir] = "contrib"
projects[libraries][version] = "2.1"

projects[link][type] = "module"
projects[link][subdir] = "contrib"
projects[link][version] = "1.1"

projects[menu_attributes][type] = "module"
projects[menu_attributes][subdir] = "contrib"
projects[menu_attributes][version] = "1.0-rc2"

projects[message][type] = "module"
projects[message][subdir] = "contrib"
projects[message][download][type] = "git"
projects[message][download][url] = "http://git.drupal.org/project/message.git"
projects[message][download][branch] = "7.x-1.x"
projects[message][download][revision] = "5ae12e8c0b7482f8525106825009409f3b9b7140"

; Make message access alterable.
; http://drupal.org/node/1920560#comment-7080942
projects[message][patch][] = "http://drupal.org/files/1920560-message-access-alterable.patch"

projects[message_notify][type] = "module"
projects[message_notify][subdir] = "contrib"
projects[message_notify][download][type] = "git"
projects[message_notify][download][url] = "http://git.drupal.org/project/message_notify.git"
projects[message_notify][download][branch] = "7.x-2.x"
projects[message_notify][download][revision] = "f8731d574f427dda3bc99e75f541549305655309"

projects[message_subscribe][type] = "module"
projects[message_subscribe][subdir] = "contrib"
projects[message_subscribe][download][type] = "git"
projects[message_subscribe][download][url] = "http://git.drupal.org/project/message_subscribe.git"
projects[message_subscribe][download][branch] = "7.x-1.x"
projects[message_subscribe][download][revision] = "0063ab0fd922a5dbd2a052114a75a60e10e6ab07"

; Remove "email" as default notifier.
; http://drupal.org/node/1828184#comment-7081868
projects[message_subscribe][patch][] = "http://drupal.org/files/email-notifiers-1828184-15.patch"

projects[memcache][type] = "module"
projects[memcache][subdir] = "contrib"
projects[memcache][version] = "1.0"

projects[metatag][type] = "module"
projects[metatag][subdir] = "contrib"
projects[metatag][version] = "1.0-beta5"

; Support for rel=author link in head
; http://drupal.org/node/1865228#comment-6839604
projects[metatag][patch][] = "http://drupal.org/files/metatag-n1865228-3.patch"

projects[module_filter][type] = "module"
projects[module_filter][subdir] = "contrib"
projects[module_filter][version] = "1.7"

projects[mollom][type] = "module"
projects[mollom][subdir] = "contrib"
projects[mollom][version] = "2.4"

projects[oauth][type] = "module"
projects[oauth][subdir] = "contrib"
projects[oauth][version] = "3.1"

projects[oauthconnector][type] = "module"
projects[oauthconnector][subdir] = "contrib"
projects[oauthconnector][download][type] = "git"
projects[oauthconnector][download][url] = "http://git.drupal.org/project/oauthconnector.git"
projects[oauthconnector][download][branch] = "7.x-1.x"
projects[oauthconnector][download][revision] = "0ce7ac9614710c0f68d0a58cb4ae4667f8bd6fa7"

projects[og][type] = "module"
projects[og][subdir] = "contrib"
projects[og][version] = "2.1"

; og_group_ref field should respect og_user_access()
; http://drupal.org/node/1902086#comment-7026516
projects[og][patch][] = "http://drupal.org/files/1902086-og-ref-respect-og-user-access-3.patch"

projects[panelizer][type] = "module"
projects[panelizer][subdir] = "contrib"
projects[panelizer][version] = "3.1"

projects[panels][type] = "module"
projects[panels][subdir] = "contrib"
projects[panels][version] = "3.3"

; Fatal error: Call to undefined function panels_get_layouts()
; http://drupal.org/node/1828684#comment-6694732
projects[panels][patch][] = "http://drupal.org/files/1828684-layout-fix-6.patch"

; PHP 5.3.9 Strict Warning on Panels Empty Value
; http://drupal.org/node/1632898#comment-6412840
projects[panels][patch][] = "http://drupal.org/files/panels-n1632898-15.patch"

projects[pathauto][type] = "module"
projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.2"

projects[pm_existing_pages][type] = "module"
projects[pm_existing_pages][subdir] = "contrib"
projects[pm_existing_pages][version] = "1.4"

projects[quicktabs][type] = "module"
projects[quicktabs][subdir] = "contrib"
projects[quicktabs][download][type] = "git"
projects[quicktabs][download][url] = "http://git.drupal.org/project/quicktabs.git"
projects[quicktabs][download][branch] = "7.x-3.x"
projects[quicktabs][download][revision] = "0788eba"

projects[radioactivity][type] = "module"
projects[radioactivity][subdir] = "contrib"
projects[radioactivity][download][type] = "git"
projects[radioactivity][download][url] = "http://git.drupal.org/project/radioactivity.git"
projects[radioactivity][download][branch] = "7.x-2.x"
projects[radioactivity][download][revision] = "aee21dbed4f54d0e626e3c19ecc550bf1ec656f6"

; Radioactivity not compatible with Memcache module
; http://drupal.org/node/1860216
projects[radioactivity][patch][] = "http://drupal.org/files/radioactivity-memcache.patch"

projects[r4032login][type] = "module"
projects[r4032login][subdir] = "contrib"
projects[r4032login][version] = "1.5"

projects[rate][type] = "module"
projects[rate][subdir] = "contrib"
projects[rate][version] = "1.6"

; Add widget to node/comment $links
; http://drupal.org/node/947516#comment-6979780
projects[rate][patch][] = "http://drupal.org/files/947516-rate-node-links-15.patch"

projects[realname][type] = "module"
projects[realname][subdir] = "contrib"
projects[realname][version] = "1.1"

projects[registration][subdir] = "contrib"
projects[registration][type] = "module"
projects[registration][download][type] = "git"
projects[registration][download][url] = "http://git.drupal.org/project/registration.git"
projects[registration][download][branch] = "7.x-1.x"
projects[registration][download][revision] = "267f05b"

; Update Entity cache support
; http://drupal.org/node/1867564#comment-7001180
projects[registration][patch][] = "http://drupal.org/files/entity_cache_support-1867564-4.patch"

projects[rules][type] = "module"
projects[rules][subdir] = "contrib"
projects[rules][version] = "2.3"

projects[search_facetapi][type] = "module"
projects[search_facetapi][subdir] = "contrib"
projects[search_facetapi][version] = "1.0-beta2"

projects[sharethis][type] = "module"
projects[sharethis][subdir] = "contrib"
projects[sharethis][version] = "2.5"

projects[facetapi][type] = "module"
projects[facetapi][subdir] = "contrib"
projects[facetapi][version] = "1.3"

projects[rich_snippets][type] = "module"
projects[rich_snippets][subdir] = "contrib"
projects[rich_snippets][version] = "1.0-beta2"

; Remove snippets from non-node type searches:
; http://drupal.org/node/1923904#comment-7094488
projects[rich_snippets][patch][] = "http://drupal.org/files/1923904-search-nodes-only.patch"

projects[schemaorg][type] = "module"
projects[schemaorg][subdir] = "contrib"
projects[schemaorg][version] = "1.0-beta3"

projects[strongarm][type] = "module"
projects[strongarm][subdir] = "contrib"
projects[strongarm][download][type] = "git"
projects[strongarm][download][url] = "http://git.drupal.org/project/strongarm.git"
projects[strongarm][download][branch] = "7.x-2.x"
projects[strongarm][download][revision] = "5a2326ba67e59923ecce63d9bb5e0ed6548abdf8"

projects[timeago][type] = "module"
projects[timeago][subdir] = "contrib"
projects[timeago][version] = "2.x-dev"
projects[timeago][download][type] = "git"
projects[timeago][download][url] = "http://git.drupal.org/project/timeago.git"
projects[timeago][download][branch] = "7.x-2.x"
projects[timeago][download][revision] = "768ea66"

; Provide a dedicated date type:
; http://drupal.org/node/1427226#comment-6638836
projects[timeago][patch][] = "http://drupal.org/files/1427226-timeago-date-type.patch"

; Redundant call to drupal_add_js() when Libraries module is enabled.
; http://drupal.org/node/1945942
projects[timeago][patch][] = "http://drupal.org/files/timeago-libraries-a.patch"

projects[title][type] = "module"
projects[title][subdir] = "contrib"
projects[title][version] = "1.0-alpha7"

projects[token][type] = "module"
projects[token][subdir] = "contrib"
projects[token][version] = "1.5"


projects[views][type] = "module"
projects[views][subdir] = "contrib"
projects[views][version] = "3.6"


projects[views_field_view][type] = "module"
projects[views_field_view][subdir] = "contrib"
projects[views_field_view][version] = "1.0"

projects[views_load_more][type] = "module"
projects[views_load_more][subdir] = "contrib"
projects[views_load_more][version] = "1.1"

projects[views_bulk_operations][type] = "module"
projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.1"

projects[views_litepager][type] = "module"
projects[views_litepager][subdir] = "contrib"
projects[views_litepager][version] = "3.0"

; We have the version of voting api at the top so it doesn't get included in our dev make patch.
projects[votingapi][version] = "2.11"
projects[votingapi][type] = "module"
projects[votingapi][subdir] = "contrib"

; Commons contrib modules:
; We don't tag a release here because want them to auto-increment.. and we are the ones who test it.

; We don't have a release for this?!?!
projects[commons_activity_streams][type] = "module"
projects[commons_activity_streams][subdir] = "contrib"

projects[commons_body][type] = "module"
projects[commons_body][subdir] = "contrib"

projects[commons_bw][type] = "module"
projects[commons_bw][subdir] = "contrib"

projects[commons_content_moderation][type] = "module"
projects[commons_content_moderation][subdir] = "contrib"

projects[commons_documents][type] = "module"
projects[commons_documents][subdir] = "contrib"

projects[commons_groups][type] = "module"
projects[commons_groups][subdir] = "contrib"

projects[commons_events][type] = "module"
projects[commons_events][subdir] = "contrib"

projects[commons_featured][type] = "module"
projects[commons_featured][subdir] = "contrib"

projects[commons_follow][type] = "module"
projects[commons_follow][subdir] = "contrib"

projects[commons_location][type] = "module"
projects[commons_location][subdir] = "contrib"

projects[commons_misc][type] = "module"
projects[commons_misc][subdir] = "contrib"

projects[commons_notices][type] = "module"
projects[commons_notices][subdir] = "contrib"

projects[commons_notify][type] = "module"
projects[commons_notify][subdir] = "contrib"

projects[commons_pages][type] = "module"
projects[commons_pages][subdir] = "contrib"

projects[commons_posts][subdir] = "contrib"
projects[commons_posts][type] = "module"

projects[commons_polls][type] = "module"
projects[commons_polls][subdir] = "contrib"

projects[commons_profile_base][type] = "module"
projects[commons_profile_base][subdir] = "contrib"

projects[commons_profile_social][type] = "module"
projects[commons_profile_social][subdir] = "contrib"

projects[commons_q_a][type] = "module"
projects[commons_q_a][subdir] = "contrib"

projects[commons_radioactivity][type] = "module"
projects[commons_radioactivity][subdir] = "contrib"

projects[commons_like][type] = "module"
projects[commons_like][subdir] = "contrib"

projects[commons_search][type] = "module"
projects[commons_search][subdir] = "contrib"

projects[commons_social_sharing][type] = "module"
projects[commons_social_sharing][subdir] = "contrib"

projects[commons_site_homepage][type] = "module"
projects[commons_site_homepage][subdir] = "contrib"

projects[commons_utility_links][type] = "module"
projects[commons_utility_links][subdir] = "contrib"

projects[commons_user_profile_pages][type] = "module"
projects[commons_user_profile_pages][subdir] = "contrib"

projects[commons_wikis][type] = "module"
projects[commons_wikis][subdir] = "contrib"

projects[commons_wysiwyg][type] = "module"
projects[commons_wysiwyg][subdir] = "contrib"

projects[commons_topics][type] = "module"
projects[commons_topics][subdir] = "contrib"

; Contributed themes.

projects[adaptivetheme][type] = "theme"
projects[adaptivetheme][subdir] = "contrib"
projects[adaptivetheme][download][type] = "git"
projects[adaptivetheme][download][url] = "git://git.drupal.org/project/adaptivetheme.git"
projects[adaptivetheme][download][branch] = "7.x-3.x"
projects[adaptivetheme][download][revision] = "4e29d43"

projects[sky][type] = "theme"
projects[sky][subdir] = "contrib"
projects[sky][version] = "3.0-rc1"

projects[commons_origins][type] = "theme"
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
