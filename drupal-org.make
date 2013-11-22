api = 2
core = 7.x

; Contributed modules.

projects[acquia_connector][type] = "module"
projects[acquia_connector][subdir] = "contrib"
projects[acquia_connector][version] = "2.12"

projects[addressfield][type] = "module"
projects[addressfield][subdir] = "contrib"
projects[addressfield][version] = "1.0-beta4"

projects[addressfield_tokens][type] = "module"
projects[addressfield_tokens][subdir] = "contrib"
projects[addressfield_tokens][version] = "1.3"

projects[admin_icons][type] = "module"
projects[admin_icons][subdir] = "contrib"
projects[admin_icons][download][type] = "git"
projects[admin_icons][download][url] = "http://git.drupal.org/project/admin_icons.git"
projects[admin_icons][download][branch] = "7.x-1.x"
projects[admin_icons][download][revision] = "60d9f28801533fecc92216a60d444d89d80e7611"

projects[advancedqueue][type] = "module"
projects[advancedqueue][subdir] = "contrib"
projects[advancedqueue][version] = "1.0-alpha2"

projects[apachesolr][type] = "module"
projects[apachesolr][subdir] = "contrib"
projects[apachesolr][version] = "1.6"

projects[apachesolr_og][type] = "module"
projects[apachesolr_og][subdir] = "contrib"
projects[apachesolr_og][download][type] = "git"
projects[apachesolr_og][download][url] = "http://git.drupal.org/project/apachesolr_og.git"
projects[apachesolr_og][download][branch] = "7.x-1.x"
projects[apachesolr_og][download]revision] = "49820b4a4fcff7c1c4efe449da033fb6d8711ac5"

projects[apachesolr_proximity][type] = "module"
projects[apachesolr_proximity][subdir] = "contrib"
projects[apachesolr_proximity][version] = "1.0-rc1"

projects[apachesolr_user][type] = "module"
projects[apachesolr_user][subdir] = "contrib"
projects[apachesolr_user][download][type] = "git"
projects[apachesolr_user][download][url] = "http://git.drupal.org/project/apachesolr_user.git"
projects[apachesolr_user][download][branch] = "7.x-1.x"
projects[apachesolr_user][download]revision] = "a86c5aebfceaf4a3fc53544762a36ca1b70809d5"

; Check the user object before trying to display a result.
; https://drupal.org/node/2077281#comment-7807937
projects[apachesolr_user][patch][] = "http://drupal.org/files/2077281-apache-solr-user-check-3.patch"

projects[breakpoints][type] = "module"
projects[breakpoints][subdir] = "contrib"
projects[breakpoints][version] = "1.1"

projects[connector][type] = "module"
projects[connector][subdir] = "contrib"
projects[connector][version] = "1.0-beta2"

projects[ckeditor][type] = "module"
projects[ckeditor][subdir] = "contrib"
projects[ckeditor][version] = "1.13"

projects[ctools][type] = "module"
projects[ctools][subdir] = "contrib"
projects[ctools][download][type] = "git"
projects[ctools][download][url] = "http://git.drupal.org/project/ctools.git"
projects[ctools][download][branch] = "7.x-1.x"
projects[ctools][download][revision] = "e81da7a57f63ca95d2c713afcec65a5659aada9e"

; Introduce UUIDs onto panes & displays.
; http://drupal.org/node/1277908#comment-7216356
projects[ctools][patch][] = "http://drupal.org/files/ctools-uuids_for_exported_objects-1277908-118.patch"

projects[custom_search][type] = "module"
projects[custom_search][subdir] = "contrib"
projects[custom_search][download][type] = "git"
projects[custom_search][download][url] = "http://git.drupal.org/project/custom_search.git"
projects[custom_search][download][branch] = "7.x-1.x"
projects[custom_search][download][revision] = "20144e64494c83a448067d587e59df5d7e4780bb"

; Avoid akward sanitization of user-entered search strings.
; https://drupal.org/node/2012210
projects[custom_search][patch][] = "http://drupal.org/files/commons_search_js_encode.patch"

projects[date][type] = "module"
projects[date][subdir] = "contrib"
projects[date][version] = "2.6"

projects[date_facets][type] = "module"
projects[date_facets][subdir] = "contrib"
projects[date_facets][version] = "1.0-beta2"

; Keeping this to the latest version, since it should only be used for development.
projects[devel][version] = "1.x-dev"
projects[devel][type] = "module"
projects[devel][subdir] = "contrib"

projects[diff][type] = "module"
projects[diff][subdir] = "contrib"
projects[diff][version] = "3.2"

; Profile has no recommended release.
projects[edit_profile][type] = "module"
projects[edit_profile][subdir] = "contrib"
projects[edit_profile][version] = "1.0-beta2"

projects[email_registration][type] = "module"
projects[email_registration][subdir] = "contrib"
projects[email_registration][version] = "1.1"

projects[entity][type] = "module"
projects[entity][subdir] = "contrib"
projects[entity][version] = "1.2"

projects[entitycache][type] = "module"
projects[entitycache][subdir] = "contrib"
projects[entitycache][version] = "1.2"

; Fix core translation support.
; http://drupal.org/node/1349566#comment-7781063
projects[entitycache][patch][] = "http://drupal.org/files/add-translation-information-on-each-request-1349566-12.patch"

projects[entityreference][type] = "module"
projects[entityreference][subdir] = "contrib"
projects[entityreference][version] = "1.1"

projects[entityreference_prepopulate][type] = "module"
projects[entityreference_prepopulate][subdir] = "contrib"
projects[entityreference_prepopulate][version] = "1.3"

projects[entity_translation][type] = "module"
projects[entity_translation][subdir] = "contrib"
projects[entity_translation][version] = "1.0-beta3"

projects[facetapi][type] = "module"
projects[facetapi][subdir] = "contrib"
projects[facetapi][version] = "1.3"

projects[features][type] = "module"
projects[features][subdir] = "contrib"
projects[features][version] = "2.0"

projects[flag][type] = "module"
projects[flag][subdir] = "contrib"
projects[flag][version] = "2.1"

; Issue #1965760: Manually set taxonomy term flag types because its different.
; http://drupal.org/node/1965760
projects[flag][patch][] = "http://drupal.org/files/1965760-flag-taxonomy-types.patch"

; Issue #1971980: Features export does not take flag_definition_alter into account.
; http://drupal.org/node/1971980
projects[flag][patch][] = "http://drupal.org/files/flag-features_export-1971980-3.patch"

projects[flag_abuse][type] = "module"
projects[flag_abuse][subdir] = "contrib"
projects[flag_abuse][version] = "2.0-alpha1"

projects[http_client][type] = "module"
projects[http_client][subdir] = "contrib"
projects[http_client][version] = "2.4"

projects[i18n][type] = "module"
projects[i18n][subdir] = "contrib"
projects[i18n][version] = "1.10"

projects[i18nviews][type] = "module"
projects[i18nviews][subdir] = "contrib"
projects[i18nviews][download][type] = "git"
projects[i18nviews][download][url] = "http://git.drupal.org/project/i18nviews.git"
projects[i18nviews][download][branch] = "7.x-3.x"
projects[i18nviews][download][revision] = "26bd52c"

projects[kissmetrics][type] = "module"
projects[kissmetrics][subdir] = "contrib"
projects[kissmetrics][version] = "1.0-rc3"

projects[l10n_update][type] = "module"
projects[l10n_update][subdir] = "contrib"
projects[l10n_update][version] = "1.0-beta3"

projects[libraries][type] = "module"
projects[libraries][subdir] = "contrib"
projects[libraries][version] = "2.1"

projects[lingotek][type] = "module"
projects[lingotek][subdir] = "contrib"
projects[lingotek][version] = "4.09"

projects[link][type] = "module"
projects[link][subdir] = "contrib"
projects[link][version] = "1.1"

projects[memcache][type] = "module"
projects[memcache][subdir] = "contrib"
projects[memcache][version] = "1.0"

projects[menu_attributes][type] = "module"
projects[menu_attributes][subdir] = "contrib"
projects[menu_attributes][version] = "1.0-rc2"

projects[message][type] = "module"
projects[message][subdir] = "contrib"
projects[message][version] = "1.9"

; Make message access alterable.
; http://drupal.org/node/1920560#comment-7080942
projects[message][patch][] = "http://drupal.org/files/1920560-message-access-alterable.patch"

; Add support for the undefined language.
; http://drupal.org/node/2006702#comment-7842259
projects[message][patch][] = "http://drupal.org/files/message_field_undefined-lang.2006702-14.patch"

projects[message_notify][type] = "module"
projects[message_notify][subdir] = "contrib"
projects[message_notify][version] = "2.5"

projects[message_subscribe][type] = "module"
projects[message_subscribe][subdir] = "contrib"
projects[message_subscribe][version] = "1.0-rc1"

projects[metatag][type] = "module"
projects[metatag][subdir] = "contrib"
projects[metatag][version] = "1.0-beta7"

; Support for rel=author link in head.
; http://drupal.org/node/1865228#comment-6839604
projects[metatag][patch][] = "http://drupal.org/files/metatag-n1865228-3.patch"

projects[module_filter][type] = "module"
projects[module_filter][subdir] = "contrib"
projects[module_filter][version] = "1.8"

projects[mollom][type] = "module"
projects[mollom][subdir] = "contrib"
projects[mollom][version] = "2.8"

projects[navbar][type] = "module"
projects[navbar][subdir] = "contrib"
projects[navbar][download][type] = "git"
projects[navbar][download][url] = "http://git.drupal.org/project/navbar.git"
projects[navbar][download][branch] = "7.x-1.x"
projects[navbar][download][revision] = "dd542e1a74d9c9b3a9b5bd699aad9a4b65e5c5b7"

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
projects[og][version] = "2.4"

; Auto-assign role to group manager broken on groups with overridden roles.
; https://drupal.org/node/2005800#comment-7684873
projects[og][patch][] = "http://drupal.org/files/issues/og-default-role-member-2005800-23.patch"

; og_ui should give users the theme, not admin ui when creating groups.
; http://drupal.org/node/1800208
projects[og][patch][] = "http://drupal.org/files/og_ui-group_node_add_theme-1800208-5.patch"

projects[panelizer][type] = "module"
projects[panelizer][subdir] = "contrib"
projects[panelizer][version] = "3.1"

projects[panels][type] = "module"
projects[panels][subdir] = "contrib"
projects[panels][version] = "3.3"

; Fatal error: Call to undefined function panels_get_layouts().
; http://drupal.org/node/1828684#comment-6694732
projects[panels][patch][] = "http://drupal.org/files/1828684-layout-fix-6.patch"

; PHP 5.3.9 Strict Warning on Panels Empty Value.
; http://drupal.org/node/1632898#comment-6412840
projects[panels][patch][] = "http://drupal.org/files/panels-n1632898-15.patch"

; Add internationalization support.
; http://drupal.org/node/1179034#comment-7216342
projects[panels][patch][] = "http://drupal.org/files/panels-1179034-41_____panels-uuids-127790-100__-80.patch"

projects[paranoia][type] = "module"
projects[paranoia][subdir] = "contrib"
projects[paranoia][version] = "1.3"

projects[pathauto][type] = "module"
projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.2"

projects[placeholder][type] = "module"
projects[placeholder][subdir] = "contrib"
projects[placeholder][version] = "1.0"

projects[pm_existing_pages][type] = "module"
projects[pm_existing_pages][subdir] = "contrib"
projects[pm_existing_pages][version] = "1.4"

projects[potx][type] = "module"
projects[potx][subdir] = "contrib"
projects[potx][version] = "1.0"

projects[privatemsg][type] = "module"
projects[privatemsg][subdir] = "contrib"
projects[privatemsg][version] = "1.4"

; Add preliminary Views integration.
; http://drupal.org/node/1573000
projects[privatemsg][patch][] = "http://drupal.org/files/privatemsg-1573000-64.patch"

; Enable privatemsg_realname when realname is enabled.
; https://drupal.org/node/2070719
projects[privatemsg][patch][] = "http://drupal.org/files/2077223-privatemsg-realname-enabled-1.patch"

projects[quicktabs][type] = "module"
projects[quicktabs][subdir] = "contrib"
projects[quicktabs][version] = "3.6"
projects[quicktabs][patch][] = "http://drupal.org/files/2104643-revert-qt-487518-5.patch"

projects[r4032login][type] = "module"
projects[r4032login][subdir] = "contrib"
projects[r4032login][version] = "1.7"

projects[radioactivity][type] = "module"
projects[radioactivity][subdir] = "contrib"
projects[radioactivity][download][type] = "git"
projects[radioactivity][download][url] = "http://git.drupal.org/project/radioactivity.git"
projects[radioactivity][download][branch] = "7.x-2.x"
projects[radioactivity][download][revision] = "aee21dbed4f54d0e626e3c19ecc550bf1ec656f6"

; Radioactivity not compatible with Memcache module.
; http://drupal.org/node/1860216
projects[radioactivity][patch][] = "http://drupal.org/files/radioactivity-memcache.patch"

projects[rate][type] = "module"
projects[rate][subdir] = "contrib"
projects[rate][version] = "1.6"

; Add widget to node/comment $links.
; http://drupal.org/node/947516#comment-6979780
projects[rate][patch][] = "http://drupal.org/files/947516-rate-node-links-15.patch"

projects[realname][type] = "module"
projects[realname][subdir] = "contrib"
projects[realname][version] = "1.1"

projects[redirect][type] = "module"
projects[redirect][subdir] = "contrib"
projects[redirect][version] = "1.0-rc1"

projects[registration][subdir] = "contrib"
projects[registration][type] = "module"
projects[registration][version] = "1.2"

projects[rich_snippets][type] = "module"
projects[rich_snippets][subdir] = "contrib"
projects[rich_snippets][version] = "1.0-beta3"

; Remove snippets from non-node type searches.
; http://drupal.org/node/1923904#comment-7094488
projects[rich_snippets][patch][] = "http://drupal.org/files/1923904-search-nodes-only.patch"

projects[rules][type] = "module"
projects[rules][subdir] = "contrib"
projects[rules][version] = "2.6"

projects[schemaorg][type] = "module"
projects[schemaorg][subdir] = "contrib"
projects[schemaorg][version] = "1.0-beta4"

projects[search_facetapi][type] = "module"
projects[search_facetapi][subdir] = "contrib"
projects[search_facetapi][version] = "1.0-beta2"

projects[sharethis][type] = "module"
projects[sharethis][subdir] = "contrib"
projects[sharethis][version] = "2.5"

projects[strongarm][type] = "module"
projects[strongarm][subdir] = "contrib"
projects[strongarm][download][type] = "git"
projects[strongarm][download][url] = "http://git.drupal.org/project/strongarm.git"
projects[strongarm][download][branch] = "7.x-2.x"
projects[strongarm][download][revision] = "5a2326ba67e59923ecce63d9bb5e0ed6548abdf8"

projects[timeago][type] = "module"
projects[timeago][subdir] = "contrib"
projects[timeago][version] = "2.2"

; Provide a dedicated date type.
; http://drupal.org/node/1427226#comment-6638836
projects[timeago][patch][] = "http://drupal.org/files/1427226-timeago-date-type.patch"

projects[title][type] = "module"
projects[title][subdir] = "contrib"
projects[title][version] = "1.0-alpha7"

projects[token][type] = "module"
projects[token][subdir] = "contrib"
projects[token][version] = "1.5"

projects[translation_helpers][type] = "module"
projects[translation_helpers][subdir] = "contrib"
projects[translation_helpers][version] = "1.0"

projects[variable][type] = "module"
projects[variable][subdir] = "contrib"
projects[variable][version] = "2.3"

projects[views][type] = "module"
projects[views][subdir] = "contrib"
projects[views][version] = "3.7"

projects[views_bulk_operations][type] = "module"
projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.1"

projects[views_field_view][type] = "module"
projects[views_field_view][subdir] = "contrib"
projects[views_field_view][version] = "1.1"

projects[views_litepager][type] = "module"
projects[views_litepager][subdir] = "contrib"
projects[views_litepager][version] = "3.0"

projects[views_load_more][type] = "module"
projects[views_load_more][subdir] = "contrib"
projects[views_load_more][version] = "1.1"

projects[votingapi][type] = "module"
projects[votingapi][subdir] = "contrib"
projects[votingapi][version] = "2.11"

projects[voting_rules][type] = "module"
projects[voting_rules][subdir] = "contrib"
projects[voting_rules][version] = "1.0-alpha1"

; Contributed themes.

projects[adaptivetheme][type] = "theme"
projects[adaptivetheme][subdir] = "contrib"
projects[adaptivetheme][download][type] = "git"
projects[adaptivetheme][download][url] = "http://git.drupal.org/project/adaptivetheme.git"
projects[adaptivetheme][download][branch] = "7.x-3.x"
projects[adaptivetheme][download][revision] = "b4b38c3c01d066e733c2942020c51962cd64231c"

; Remove link around comment creation date.
; http://drupal.org/node/1427226#comment-6638836
projects[adaptivetheme][patch][] = "http://drupal.org/files/remove-comment-creation-link-2018081-1.patch"

projects[sky][type] = "theme"
projects[sky][subdir] = "contrib"
projects[sky][version] = "3.0-rc1"

; Libraries.
; NOTE: These need to be listed in http://drupal.org/packaging-whitelist.

libraries[backbone][download][type] = "get"
libraries[backbone][type] = "libraries"
libraries[backbone][download][url] = "https://github.com/jashkenas/backbone/archive/1.1.0.tar.gz"

libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.0/ckeditor_4.0_full.tar.gz"
libraries[ckeditor][type] = "libraries"

libraries[modernizr][download][type] = "get"
libraries[modernizr][type] = "libraries"
libraries[modernizr][download][url] = "https://github.com/Modernizr/Modernizr/archive/v2.7.0.tar.gz"

libraries[placeholder][download][type] = "get"
libraries[placeholder][type] = "libraries"
libraries[placeholder][download][url] = "https://github.com/mathiasbynens/jquery-placeholder/archive/v2.0.7.tar.gz"

libraries[timeago][download][type] = "get"
libraries[timeago][type] = "libraries"
libraries[timeago][download][url] = "https://raw.github.com/rmm5t/jquery-timeago/v1.3.0/jquery.timeago.js"

libraries[underscore][download][type] = "get"
libraries[underscore][type] = "libraries"
libraries[underscore][download][url] = "https://github.com/jashkenas/underscore/archive/1.4.4.zip"
