core = 6.x

api = 2
projects[drupal][version] = "6.22"

; Profiles
; Please fill the following out. Type may be one of get, cvs, git, bzr or svn,
; and url is the url of the download.
projects[drupal_commons][download][type] = "git"
projects[drupal_commons][download][url] = "http://git.drupal.org/sandbox/ezrag/1262660.git"
projects[drupal_commons][download][revision] = "6.x-2.x"
projects[drupal_commons][type] = "profile"

; Modules
projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations][version] = "1.11"

projects[admin][subdir] = "contrib"
projects[admin][version] = "2.0"


projects[ajax_load][download][type] = "git"
projects[ajax_load][download][url] = "http://git.drupal.org/project/ajax_load.git" 
projects[ajax_load][download][revision] = "8b0921252fcf599e7b15276bd815bcf81521eb27"
projects[ajax_load][subdir] = "contrib"

projects[boxes][subdir] = "contrib"
projects[boxes][version] = "1.0"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.8"

projects[calendar][subdir] = "contrib"
projects[calendar][version] = "2.4"

projects[chart][subdir] = "contrib"
projects[chart][version] = "1.3"

; Chart patches in PATCHES.txt from Acquia Commons GitHub repo:

; http://drupal.org/node/594202#comment-3943160
projects[chart][patch][] = "http://drupal.org/files/issues/chart-division-by-zero-594202.patch"
  

projects[cck][subdir] = "contrib"
projects[cck][version] = "2.9"

projects[context][subdir] = "contrib"
projects[context][version] = "3.0"

; Context patches in PATCHES.txt from Acquia Commons GitHub repo:

; http://drupal.org/node/916194#comment-3719526
projects[context][patch][] = "http://drupal.org/files/issues/916194-10-context-block-content.patch"

projects[context_og][subdir] = "contrib"
projects[context_og][version] = "3.0"

projects[date][subdir] = "contrib"
projects[date][version] = "2.7"

projects[diff][subdir] = "contrib"
projects[diff][version] = "2.2"

projects[tagging][subdir] = "contrib"
projects[tagging][version] = "2.5"

projects[editablefields][subdir] = "contrib"
projects[editablefields][version] = "2.0"

; Editable fields patches in PATCHES.txt from Acquia Commons GitHub repo:
Issue: http://drupal.org/node/777870
projects[editablefields][patch][] = "http://drupal.org/files/issues/editablefields-removeFocus.patch"

projects[features][subdir] = "contrib"
projects[features][version] = "1.0"

projects[filefield][subdir] = "contrib"
projects[filefield][version] = "3.10"

projects[flag][subdir] = "contrib"
projects[flag][version] = "1.3"

projects[freelinking][subdir] = "contrib"
projects[freelinking][version] = "1.10"

projects[getid3][subdir] = "contrib"
projects[getid3][version] = "1.4"

projects[imageapi][subdir] = "contrib"
projects[imageapi][version] = "1.10"

projects[imagecache][subdir] = "contrib"
projects[imagecache][version] = "2.0-beta12"

projects[imagecache_actions][subdir] = "contrib"
projects[imagecache_actions][version] = "1.8"

projects[imagecache_profiles][subdir] = "contrib"
projects[imagecache_profiles][version] = "1.3"

projects[imagefield][subdir] = "contrib"
projects[imagefield][version] = "3.10"

projects[insert][subdir] = "contrib"
projects[insert][version] = "1.1"

projects[invite][subdir] = "contrib"
projects[invite][version] = "2.0-beta3"

projects[jquery_ui][subdir] = "contrib"
projects[jquery_ui][version] = "1.4"

projects[link][subdir] = "contrib"
projects[link][version] = "2.9"

projects[messaging][subdir] = "contrib"
projects[messaging][version] = "2.4"

projects[mimemail][subdir] = "contrib"
projects[mimemail][version] = "1.0-beta2"

projects[notifications][subdir] = "contrib"
projects[notifications][version] = "2.3"

projects[og][subdir] = "contrib"
projects[og][version] = "2.1"
; http://drupal.org/node/881380
projects[og][patch][] = "http://drupal.org/files/issues/og-DRUPAL-6--2.views-constants.0.patch"

; OG patches in PATCHES.txt from Acquia Commons GitHub repo:

; http://drupal.org/node/333072#comment-3264980
; This patch is incorrectly rolled against an OG subdirectory, so it doesn't apply.
;projects[og][patch][] = "http://drupal.org/files/issues/og_views-fix-search-view.patch"

; http://drupal.org/node/835030
projects[og][patch][] = "http://drupal.org/files/issues/og_notifications-subscriptions-not-saving-835030.patch"

; http://drupal.org/node/1051258
; Does not apply:
;projects[og][patch][] = "http://drupal.org/files/issues/og_notifications-add-form-labels.patch"

; http://drupal.org/node/1128492
projects[og][patch][] = "http://drupal.org/files/issues/og_views-add-leave-group-field.patch"

; http://drupal.org/node/793588
projects[og][patch][] = "http://drupal.org/files/issues/793588-og_uid-add-index-3.patch"

projects[og_aggregator][subdir] = "contrib"
projects[og_aggregator][version] = "1.4"

; OG_Aggregator patches in PATCHES.txt from Acquia Commons GitHub repo:

; http://drupal.org/node/768958
; Does not apply:
; projects[og_aggregator][patch][] = "http://drupal.org/files/issues/og_aggregator-fix-context-check-768958.patch"

; http://drupal.org/node/854246
; Does not apply but committed upstream.
; projects[og_aggregator][patch][] = "http://drupal.org/files/issues/og_aggregator-fix-titlecase.patch"

; http://drupal.org/node/854248
; Does not apply to og_aggregator 1.4 but has been committed upstream.
; projects[og_aggregator][patch][] = "http://drupal.org/files/issues/og_aggregator-fix-wsod.patch

; http://drupal.org/node/768958
; Does not apply.
projects[og_aggregator][patch][] = "http://drupal.org/files/issues/og_aggregator-fix-context-check-768958.patch"

; Issue: http://drupal.org/node/854246
projects[og_aggregator][patch][] = "http://drupal.org/files/issues/og_aggregator-fix-titlecase.patch"

; Issue: http://drupal.org/node/854248
projects[og_aggregator][patch][] = "http://drupal.org/files/issues/og_aggregator-fix-wsod.patch"

projects[og_features][subdir] = "contrib"
projects[og_features][version] = "1.1"

projects[og_invite_link][subdir] = "contrib"
projects[og_invite_link][version] = "1.0"

projects[og_statistics][subdir] = "contrib"
projects[og_statistics][version] = "1.0-rc5"

; OG_Statistics patches in PATCHES.txt from Acquia Commons GitHub repo:

; http://drupal.org/node/1162902#comment-4491368
projects[og_statistics][patch][] = "http://drupal.org/files/issues/og_statistics-fix-race-condition-on-group-creation-1162902_0.patch"

; http://drupal.org/node/1162928#comment-4491270
projects[og_statistics][patch][] = "http://drupal.org/files/issues/og_statistics-proper-determination-of-unapproved-1162928_0.patch"

projects[og_subgroups][subdir] = "contrib"
projects[og_subgroups][version] = "1.0-beta3"

projects[password_policy][subdir] = "contrib"
projects[password_policy][version] = "1.0-beta1"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.5"

projects[quant][download][type] = "git"
projects[quant][download][url] = "http://git.drupal.org/project/quant.git"
projects[quant][download][revision] = "2d204b2"
projects[quant][subdir] = "contrib"

projects[rules][subdir] = "contrib"
projects[rules][version] = "1.4"
; http://drupal.org/node/978620#comment-3763720
projects[rules][patch][] = "http://drupal.org/files/issues/rules.rules_defaults_alter_0.patch"

projects[strongarm][subdir] = "contrib"
projects[strongarm][download][version] = "6.x-2.0"

projects[tagadelic][subdir] = "contrib"
projects[tagadelic][version] = "1.3"

projects[tagadelic_views][subdir] = "contrib"
projects[tagadelic_views][version] = "1.2"

projects[token][subdir] = "contrib"
projects[token][version] = "1.16"

projects[transliteration][subdir] = "contrib"
projects[transliteration][version] = "3.0"

projects[userpoints_contrib][subdir] = "contrib"
projects[userpoints_contrib][download][type] = "git"
projects[userpoints_contrib][download][url] = "http://git.drupal.org/project/userpoints.git"
projects[userpoints_contrib][download][revision] = "0359e9497882d98080b5854b19ebc1bd34a7c24a"

; Based on the date of 5ae09b723a8197f29d9ee7f562777ef221cb16de from the GitHub Acquia Commons repo.
projects[userpoints_contrib][download][type] = git
projects[userpoints_contrib][download][url] = "http://git.drupal.org/project/userpoints_contrib.git"
projects[userpoints_contrib][version] = "0359e9497882d98080b5854b19ebc1bd34a7c24a"

projects[user_badges][subdir] = "contrib"
projects[user_badges][version] = "1.6"

; User_badges patches in PATCHES.txt from Acquia Commons GitHub repo:
; http://drupal.org/node/964546#comment-4001354
projects[user_badges][patch][] = "http://drupal.org/files/issues/user_badges-foreach-error-964546_1.patch"

; http://drupal.org/node/986822#comment-4001216
projects[user_badges][patch][] = "http://drupal.org/files/issues/user_badges-undefined-constant-986822.patch"

projects[user_relationships][subdir] = "contrib"
projects[user_relationships][version] = "1.0"

; User_relationships patches in PATCHES.txt from Acquia Commons GitHub repo:
; http://drupal.org/node/1121038#comment-4322488
projects[user_relationships][patch][] = "http://drupal.org/files/issues/user_relationships_disable_notifications_0_0.patch"

projects[user_terms][subdir] = "contrib"
projects[user_terms][version] = "1.0"
; User_terms patches in PATCHES.txt from Acquia Commons GitHub repo:
; http://drupal.org/node/617088#comment-2901188
projects[user_terms][patch][] = "http://drupal.org/files/issues/user_terms-freeTagging.patch"

projects[userpoints][subdir] = "contrib"
projects[userpoints][version] = "1.2"

projects[userpoints_nc][subdir] = "contrib"
projects[userpoints_nc][version] = "1.1"

; Userpoints_nc patches in PATCHES.txt from Acquia Commons GitHub repo:
; http://drupal.org/node/875140#comment-3859230
projects[userpoints_nc][patch][] = "http://drupal.org/files/issues/userpoints_nc-fixed-delete-operation-label.patch"

projects[userpoints_user_picture][subdir] = "contrib"
projects[userpoints_user_picture][version] = "1.2"

projects[vertical_tabs][subdir] = "contrib"
projects[vertical_tabs][version] = "1.0-rc1"

projects[views][subdir] = "contrib"
projects[views][version] = "2.12"

; Views patches in PATCHES.txt from Acquia Commons GitHub repo
; http://drupal.org/node/571234#comment-3122678
projects[views][patch][] = "http://drupal.org/files/issues/views-executed.patch"

; http://drupal.org/node/228510#comment-3426202
; Does not apply via Drush but Committed upstream. Can be mostly applied manually patch -p0 (3 hunks fail). 
; projects[views][patch][]  = "http://drupal.org/files/issues/228510.patch"


projects[views_slideshow][subdir] = "contrib"
projects[views_slideshow][version] = "2.3"

projects[wikitools][subdir] = "contrib"
projects[wikitools][version] = "1.3"


projects[wysiwyg][download][type] = "git"
projects[wysiwyg][download][url] = "http://git.drupal.org/project/wysiwyg.git"
projects[wysiwyg][download][revision] = "ddfaf684a45eb2ba3e4f866e5e5e6e1c10c8c020"
projects[wysiwyg][subdir] = "contrib"

projects[wysiwyg_filter][subdir] = "contrib"
projects[wysiwyg_filter][version] = "1.5"


projects[activity_log][download][type] = "git"
projects[activity_log][download][url] = "http://git.drupal.org/project/activity_log.git"
; Based on on https://github.com/acquia/commons/commit/fbf4b41f12aacc4762627d6c2c418fe5c4e74955.
projects[activity_log][download][revision] = "7891fa4af86f0cf323e534410fa66e2ddc8cf1f3"
projects[activity_log][type] = "module"
projects[activity_log][subdir] = "contrib"

projects[digests][download][type] = "git"
projects[digests][download][url] = "http://git.drupal.org/project/digests.git"
; Based on 93a98a3d7b45a5934f5604c9452046e8e8e0c474 from Commons GitHub Repo
projects[digests][download][revision] = "91412517706a08e41c27961b4f003e5df3e5b47e"
projects[digests][type] = "module"
projects[digests][subdir] = "contrib"

projects[facebook_status][download][type] = "git"
projects[facebook_status][download][url] = "http://git.drupal.org/project/facebook_status.git"
; Based on Commons GitHub ec26466cb3c4b51a5bc52a77a74f4c90e153fb9e
projects[facebook_status][download][revision] = "383c837fc0a42fc181c54f666e20def93480d154"
projects[facebook_status][subdir] = "contrib"

; Themes

projects[fusion][version] = "1.0"
projects[fusion][project][type] = theme

