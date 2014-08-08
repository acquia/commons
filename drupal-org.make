api = 2
core = 7.x

; Contributed modules.

projects[acquia_connector][type] = "module"
projects[acquia_connector][subdir] = "contrib"
projects[acquia_connector][version] = "2.14"

; Fix signup messages displayed during install.
; https://drupal.org/node/2289903#comment-8899833
projects[acquia_connector][patch][] = "http://drupal.org/files/issues/move-message-generation-2289903-1.patch"

projects[addressfield][type] = "module"
projects[addressfield][subdir] = "contrib"
projects[addressfield][version] = "1.0-beta5"

projects[addressfield_tokens][type] = "module"
projects[addressfield_tokens][subdir] = "contrib"
projects[addressfield_tokens][version] = "1.4"

projects[admin_icons][type] = "module"
projects[admin_icons][subdir] = "contrib"
projects[admin_icons][download][type] = "git"
projects[admin_icons][download][url] = "http://git.drupal.org/project/admin_icons.git"
projects[admin_icons][download][branch] = "7.x-1.x"
projects[admin_icons][download][revision] = "60d9f28801533fecc92216a60d444d89d80e7611"

projects[apachesolr][type] = "module"
projects[apachesolr][subdir] = "contrib"
projects[apachesolr][version] = "1.6"

projects[apachesolr_og][type] = "module"
projects[apachesolr_og][subdir] = "contrib"
projects[apachesolr_og][download][type] = "git"
projects[apachesolr_og][download][url] = "http://git.drupal.org/project/apachesolr_og.git"
projects[apachesolr_og][download][branch] = "7.x-1.x"
projects[apachesolr_og][download][revision] = "49820b4a4fcff7c1c4efe449da033fb6d8711ac5"

; Check the user object before trying to display a result.
; https://drupal.org/node/2077281#comment-7807937
projects[apachesolr_og][patch][] = "http://drupal.org/files/issues/apachesolr_og-check-for-anonymous.patch"

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
projects[breakpoints][version] = "1.2"

projects[connector][type] = "module"
projects[connector][subdir] = "contrib"
projects[connector][version] = "1.0-beta2"

projects[ckeditor][type] = "module"
projects[ckeditor][subdir] = "contrib"
projects[ckeditor][version] = "1.15"

; Accomodate latest Media changes.
; https://drupal.org/node/2159403
projects[ckeditor][patch][] = "http://drupal.org/files/issues/ckeditor-accomodate-latest-media-changes-53.patch"

projects[ctools][type] = "module"
projects[ctools][subdir] = "contrib"
projects[ctools][download][type] = "git"
projects[ctools][download][url] = "http://git.drupal.org/project/ctools.git"
projects[ctools][download][branch] = "7.x-1.x"
projects[ctools][download][revision] = "6e034cb9"
projects[ctools][patch][] = "http://drupal.org/files/issues/missing-ctools-version-2269747-1.patch"

projects[custom_search][type] = "module"
projects[custom_search][subdir] = "contrib"
projects[custom_search][version] = "1.16"

; Avoid akward sanitization of user-entered search strings.
; https://drupal.org/node/2012210
projects[custom_search][patch][] = "http://drupal.org/files/commons_search_js_encode.patch"

projects[date][type] = "module"
projects[date][subdir] = "contrib"
projects[date][version] = "2.8"

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

projects[elements][type] = "module"
projects[elements][subdir] = "contrib"
projects[elements][version] = "1.4"

projects[email_registration][type] = "module"
projects[email_registration][subdir] = "contrib"
projects[email_registration][download][type] = "git"
projects[email_registration][download][url] = "http://git.drupal.org/project/email_registration.git"
projects[email_registration][download][branch] = "7.x-1.x"
projects[email_registration][download][revision] = "1656416"

projects[entity][type] = "module"
projects[entity][subdir] = "contrib"
projects[entity][version] = "1.5"

projects[entitycache][type] = "module"
projects[entitycache][subdir] = "contrib"
projects[entitycache][version] = "1.2"

; Fix core translation support.
; http://drupal.org/node/1349566#comment-7781063
projects[entitycache][patch][] = "http://drupal.org/files/add-translation-information-on-each-request-1349566-12.patch"

projects[entityreference][type] = "module"
projects[entityreference][subdir] = "contrib"
projects[entityreference][version] = "1.1"

; Autocomplete widgets cannot reference a single entity result.
; http://drupal.org/node/1959624#comment-8451891
projects[entityreference][patch][] = "http://drupal.org/files/issues/entityreference-autocomplete-widget-single-entity-1959624-6.patch"

projects[entityreference_prepopulate][type] = "module"
projects[entityreference_prepopulate][subdir] = "contrib"
projects[entityreference_prepopulate][version] = "1.5"

; Entityreference prepopulate overwrites field instance custom default value functions.
; http://drupal.org/node/2304301#comment-8973459
projects[entityreference_prepopulate][patch][] = "http://drupal.org/files/issues/check-for-default-value-function-2304301-1.patch"

projects[entity_translation][type] = "module"
projects[entity_translation][subdir] = "contrib"
projects[entity_translation][version] = "1.0-beta3"

projects[facetapi][type] = "module"
projects[facetapi][subdir] = "contrib"
projects[facetapi][version] = "1.5"

projects[features][type] = "module"
projects[features][subdir] = "contrib"
projects[features][version] = "2.2"

projects[file_entity][type] = "module"
projects[file_entity][subdir] = "contrib"
projects[file_entity][version] = "2.0-alpha3"

; Issue #2081713: Fix undefined index errors with empty (remote) files.
; https://drupal.org/node/2081713
projects[file_entity][patch][] = "http://drupal.org/files/issues/add-filesize-checks-2081713-13.patch"

projects[flag][type] = "module"
projects[flag][subdir] = "contrib"
projects[flag][version] = "2.2"

; Issue #1965760: Manually set taxonomy term flag types because its different.
; http://drupal.org/node/1965760
projects[flag][patch][] = "http://drupal.org/files/issues/1965760.29.flag_.entity-tokens.patch"

; Provide a hook to allow default flag definitions to be altered.
; https://drupal.org/node/2027091#comment-8012263
projects[flag][patch][] = "http://drupal.org/files/flag-default-flags-alter-hook-2027091-03.patch"

projects[flag_abuse][type] = "module"
projects[flag_abuse][subdir] = "contrib"
projects[flag_abuse][version] = "2.0"

projects[gravatar][type] = "module"
projects[gravatar][subdir] = "contrib"
projects[gravatar][download][type] = "git"
projects[gravatar][download][url] = "http://git.drupal.org/project/gravatar.git"
projects[gravatar][download][branch] = "7.x-1.x"
projects[gravatar][download][revision] = "bb2f81e6"

projects[http_client][type] = "module"
projects[http_client][subdir] = "contrib"
projects[http_client][version] = "2.4"

projects[i18n][type] = "module"
projects[i18n][subdir] = "contrib"
projects[i18n][download][type] = "git"
projects[i18n][download][url] = "http://git.drupal.org/project/i18n.git"
projects[i18n][download][branch] = "7.x-1.x"
projects[i18n][download][revision] = "3777b86"

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
projects[l10n_update][version] = "1.0"

projects[libraries][type] = "module"
projects[libraries][subdir] = "contrib"
projects[libraries][version] = "2.2"

projects[lingotek][type] = "module"
projects[lingotek][subdir] = "contrib"
projects[lingotek][version] = "5.10"

projects[link][type] = "module"
projects[link][subdir] = "contrib"
projects[link][version] = "1.2"

projects[media][type] = "module"
projects[media][subdir] = "contrib"
projects[media][download][type] = "git"
projects[media][download][url] = "http://git.drupal.org/project/media.git"
projects[media][download][branch] = "7.x-2.x"
projects[media][download][revision] = "b2c2d78"

; New filelfield browser widget is massively confusing the user
; https://drupal.org/comment/8570379#comment-8570379
projects[media][patch][] = "http://drupal.org/files/issues/automatically-attach-files-2216329-2.patch"

projects[media_oembed][type] = "module"
projects[media_oembed][subdir] = "contrib"
projects[media_oembed][version] = "2.1"

projects[memcache][type] = "module"
projects[memcache][subdir] = "contrib"
projects[memcache][version] = "1.2"

projects[menu_attributes][type] = "module"
projects[menu_attributes][subdir] = "contrib"
projects[menu_attributes][version] = "1.0-rc2"

projects[message][type] = "module"
projects[message][subdir] = "contrib"
projects[message][download][type] = "git"
projects[message][download][url] = "http://git.drupal.org/project/message.git"
projects[message][download][branch] = "7.x-1.x"
projects[message][download][revision] = "3bbdd5e6"

; Make message access alterable.
; http://drupal.org/node/1920560#comment-7080942
projects[message][patch][] = "http://drupal.org/files/1920560-message-access-alterable.patch"

; Add support for the undefined language.
; http://drupal.org/node/2006702#comment-7842259
projects[message][patch][] = "http://drupal.org/files/message_field_undefined-lang.2006702-14.patch"

; Fix Undefined index: message_type in _field_ui on field listings
; https://drupal.org/node/1391442
projects[message][patch][] = "http://drupal.org/files/issues/message-entity_info_hook_notice_undefined_index-1391442-34.patch"

projects[message_notify][type] = "module"
projects[message_notify][subdir] = "contrib"
projects[message_notify][version] = "2.5"

projects[message_subscribe][type] = "module"
projects[message_subscribe][subdir] = "contrib"
projects[message_subscribe][version] = "1.0-rc2"

; Message Subscribe sends emails regardless of context
; https://www.drupal.org/node/1828184
projects[message_subscribe][patch][] = "http://drupal.org/files/issues/group-context-1828184-53.patch"

; By default, don't notify blocked users
; https://www.drupal.org/node/2184567
projects[message_subscribe][patch][] = "http://drupal.org/files/issues/2184567-message-subscribe-blocked-users-23.patch"

projects[metatag][type] = "module"
projects[metatag][subdir] = "contrib"
projects[metatag][version] = "1.0-rc2"

projects[module_filter][type] = "module"
projects[module_filter][subdir] = "contrib"
projects[module_filter][version] = "1.8"

projects[mollom][type] = "module"
projects[mollom][subdir] = "contrib"
projects[mollom][version] = "2.10"

projects[navbar][type] = "module"
projects[navbar][subdir] = "contrib"
projects[navbar][version] = "1.4"

; Change I-beam cursors in the navbar to be a pointer instead.
; https://drupal.org/node/2173041
projects[navbar][patch][] = "http://drupal.org/files/issues/2173041-3-i-beam-menu-hover.patch"

projects[oauth][type] = "module"
projects[oauth][subdir] = "contrib"
projects[oauth][version] = "3.2"

projects[oauthconnector][type] = "module"
projects[oauthconnector][subdir] = "contrib"
projects[oauthconnector][download][type] = "git"
projects[oauthconnector][download][url] = "http://git.drupal.org/project/oauthconnector.git"
projects[oauthconnector][download][branch] = "7.x-1.x"
projects[oauthconnector][download][revision] = "42c6f66"

projects[oembed][type] = "module"
projects[oembed][subdir] = "contrib"
projects[oembed][download][type] = "git"
projects[oembed][download][url] = "http://git.drupal.org/project/oembed.git"
projects[oembed][download][branch] = "7.x-1.x"
projects[oembed][download][revision] = "9aa5303"

; Remove the media submodule as it conflicts with the Media: oEmbed module.
; https://drupal.org/node/2269745#comment-8796261
projects[oembed][patch][] = "http://drupal.org/files/issues/remove-media-submodule-2269745-2.patch"

projects[og][type] = "module"
projects[og][subdir] = "contrib"
projects[og][version] = "2.7"

; Auto-assign role to group manager broken on groups with overridden roles.
; https://drupal.org/node/2005800#comment-7684873
projects[og][patch][] = "http://drupal.org/files/issues/og-default-role-member-2005800-25.patch"

; og_ui should give users the theme, not admin ui when creating groups.
; http://drupal.org/node/1800208
projects[og][patch][] = "http://drupal.org/files/og_ui-group_node_add_theme-1800208-5.patch"

; Missing permissions when installing a new site.
; http://drupal.org/node/2301831
projects[og][patch][] = "http://drupal.org/files/issues/og-missing-permission-roles-2301831-1.patch"

; Missing permissions when reverting features.
; http://drupal.org/node/2021673
projects[og][patch][] = "http://drupal.org/files/og-Do_not_export_nonexisting_roles-2021673-1.patch"

projects[panelizer][type] = "module"
projects[panelizer][subdir] = "contrib"
projects[panelizer][version] = "3.1"

projects[panels][type] = "module"
projects[panels][subdir] = "contrib"
projects[panels][download][type] = "git"
projects[panels][download][url] = "http://git.drupal.org/project/panels.git"
projects[panels][download][branch] = "7.x-3.x"
projects[panels][download][revision] = "8059bda2b"

projects[paranoia][type] = "module"
projects[paranoia][subdir] = "contrib"
projects[paranoia][version] = "1.3"

projects[pathauto][type] = "module"
projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.2"

projects[picture][type] = "module"
projects[picture][subdir] = "contrib"
projects[picture][download][type] = "git"
projects[picture][download][url] = "http://git.drupal.org/project/picture.git"
projects[picture][download][branch] = "7.x-1.x"
projects[picture][download][revision] = "18b94b9"

; Add ctools as a dependency
; https://drupal.org/node/2173043
projects[picture][patch][] = "http://drupal.org/files/issues/add-ctools-dependency-2173043-1.patch"

; Allow filter tips to be translated
; https://drupal.org/node/2139459
projects[picture][patch][] = "http://drupal.org/files/issues/translate-filter-tips-2139459-1.patch"

; Move hook_uninstall() to picture.install to fix issues on uninstall.
; https://drupal.org/node/2173015
projects[picture][patch][] = "http://drupal.org/files/issues/move-uninstall-hook-implementation-2173015-1.patch"

; Remove implementation of hook_file_formatter_info() to remove duplicate file formatter.
; https://drupal.org/node/2172841
projects[picture][patch][] = "http://drupal.org/files/issues/remove-file-formatter-hook-implementation-2172831-1.patch"

; Remove implementation of hook_ctools_plugin_api() to fix issues with features.
; https://drupal.org/node/2172831
projects[picture][patch][] = "http://drupal.org/files/issues/remove-ctools-hook-implementation-2172831-1.patch"

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
projects[radioactivity][version] = "2.9"

projects[rate][type] = "module"
projects[rate][subdir] = "contrib"
projects[rate][version] = "1.7"

; Add widget to node/comment $links.
; http://drupal.org/node/947516#comment-6979780
projects[rate][patch][] = "http://drupal.org/files/947516-rate-node-links-15.patch"

; Only load CSS when necessary.
; https://drupal.org/node/2180853
projects[rate][patch][] = "http://drupal.org/files/issues/attach-rate-css-2180853-3.patch"

projects[realname][type] = "module"
projects[realname][subdir] = "contrib"
projects[realname][version] = "1.2"

; Realname entityreference autocomplete API update
; https://drupal.org/node/2225889
projects[realname][patch][] = "http://drupal.org/files/issues/2225889-realname-correct-menu-3.patch"

projects[redirect][type] = "module"
projects[redirect][subdir] = "contrib"
projects[redirect][version] = "1.0-rc1"

projects[registration][subdir] = "contrib"
projects[registration][type] = "module"
projects[registration][version] = "1.3"

projects[rich_snippets][type] = "module"
projects[rich_snippets][subdir] = "contrib"
projects[rich_snippets][version] = "1.0-beta4"

projects[rules][type] = "module"
projects[rules][subdir] = "contrib"
projects[rules][version] = "2.7"

projects[schemaorg][type] = "module"
projects[schemaorg][subdir] = "contrib"
projects[schemaorg][version] = "1.0-beta4"

projects[search_facetapi][type] = "module"
projects[search_facetapi][subdir] = "contrib"
projects[search_facetapi][version] = "1.0-beta2"

projects[sharethis][type] = "module"
projects[sharethis][subdir] = "contrib"
projects[sharethis][version] = "2.9"

projects[smartcrop][type] = "module"
projects[smartcrop][subdir] = "contrib"
projects[smartcrop][version] = "1.0-beta2"

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
projects[variable][version] = "2.5"

projects[views][type] = "module"
projects[views][subdir] = "contrib"
projects[views][version] = "3.8"

; Update Views Content access filter per core performance improvements.
; https://drupal.org/comment/8516039#comment-8516039
projects[views][patch][] = "http://drupal.org/files/issues/views-content_access_filter_per_core_performance-2204257-4_0.patch"

projects[views_bulk_operations][type] = "module"
projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.2"

projects[views_field_view][type] = "module"
projects[views_field_view][subdir] = "contrib"
projects[views_field_view][version] = "1.1"

projects[views_litepager][type] = "module"
projects[views_litepager][subdir] = "contrib"
projects[views_litepager][version] = "3.0"

projects[views_load_more][type] = "module"
projects[views_load_more][subdir] = "contrib"
projects[views_load_more][version] = "1.2"

; Suppress notice error when loading more content from views_load_more.
; https://drupal.org/node/2207467
projects[views_load_more][patch][] = "http://drupal.org/files/issues/fix-notice-undefined-index-2152935-3.patch"

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
projects[adaptivetheme][download][revision] = "18693ff59db7cb3171f282a982d04fe6544b63a1"

projects[ember][type] = "theme"
projects[ember][subdir] = "contrib"
projects[ember][download][type] = "git"
projects[ember][download][url] = "http://git.drupal.org/project/ember.git"
projects[ember][download][branch] = "7.x-2.x"
projects[ember][download][revision] = "caf4df7"

projects[sky][type] = "theme"
projects[sky][subdir] = "contrib"
projects[sky][version] = "3.0"

; Libraries.
; NOTE: These need to be listed in http://drupal.org/packaging-whitelist.

libraries[backbone][download][type] = "get"
libraries[backbone][type] = "libraries"
libraries[backbone][download][url] = "https://github.com/jashkenas/backbone/archive/1.1.0.tar.gz"

libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.3.4/ckeditor_4.3.4_full.zip"
libraries[ckeditor][type] = "libraries"

libraries[ckeditor_lineutils][download][type] = "get"
libraries[ckeditor_lineutils][download][url] = "http://download.ckeditor.com/lineutils/releases/lineutils_4.3.4.zip"
libraries[ckeditor_lineutils][type] = "libraries"
libraries[ckeditor_lineutils][subdir] = "ckeditor/plugins"
libraries[ckeditor_lineutils][directory_name] = "lineutils"

libraries[ckeditor_widget][download][type] = "get"
libraries[ckeditor_widget][download][url] = "http://download.ckeditor.com/widget/releases/widget_4.3.4.zip"
libraries[ckeditor_widget][type] = "libraries"
libraries[ckeditor_widget][subdir] = "ckeditor/plugins"
libraries[ckeditor_widget][directory_name] = "widget"

libraries[modernizr][download][type] = "get"
libraries[modernizr][type] = "libraries"
libraries[modernizr][download][url] = "https://github.com/Modernizr/Modernizr/archive/v2.7.1.tar.gz"

libraries[timeago][download][type] = "get"
libraries[timeago][type] = "libraries"
libraries[timeago][download][url] = "https://raw.githubusercontent.com/rmm5t/jquery-timeago/v1.4.1/jquery.timeago.js"

libraries[underscore][download][type] = "get"
libraries[underscore][type] = "libraries"
libraries[underscore][download][url] = "https://github.com/jashkenas/underscore/archive/1.5.2.zip"
