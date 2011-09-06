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
projects[views_bulk_operations][subdir] = "contrib/views_bulk_operations"
projects[views_bulk_operations][version] = "1.10"

projects[admin][subdir] = "contrib"
projects[admin][version] = "2.0"

projects[ajax_load][subdir] = "contrib"
projects[ajax_load][version] = "1.x-dev"

projects[boxes][subdir] = "contrib"
projects[boxes][version] = "1.0"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.8"

projects[calendar][subdir] = "contrib"
projects[calendar][version] = "2.4"

projects[chart][subdir] = "contrib"
projects[chart][version] = "1.3"


projects[cck][subdir] = "contrib"
projects[cck][version] = "2.9"

projects[context][subdir] = "contrib"
projects[context][version] = "3.0"

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

projects[og_aggregator][subdir] = "contrib"
projects[og_aggregator][version] = "1.4"

projects[og_features][subdir] = "contrib"
projects[og_features][version] = "1.1"

projects[og_invite_link][subdir] = "contrib"
projects[og_invite_link][version] = "1.0"

projects[og_statistics][subdir] = "contrib"
projects[og_statistics][version] = "1.0-rc5"

projects[og_subgroups][subdir] = "contrib"
projects[og_subgroups][version] = "1.0-beta3"

projects[password_policy][subdir] = "contrib"
projects[password_policy][version] = "1.0-beta1"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.5"

projects[quant][subdir] = "contrib"
projects[quant][version] = "1.x-dev"

projects[rules][subdir] = "contrib"
projects[rules][version] = "1.4"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.0"

projects[tagadelic][subdir] = "contrib"
projects[tagadelic][version] = "1.3"

projects[tagadelic_views][subdir] = "contrib"
projects[tagadelic_views][version] = "1.2"

projects[token][subdir] = "contrib"
projects[token][version] = "1.16"

projects[transliteration][subdir] = "contrib"
projects[transliteration][version] = "3.0"

projects[userpoints_contrib][subdir] = "contrib"
projects[userpoints_contrib][version] = "1.x-dev"

projects[user_badges][subdir] = "contrib"
projects[user_badges][version] = "1.6"

projects[user_relationships][subdir] = "contrib"
projects[user_relationships][version] = "1.0"

projects[user_terms][subdir] = "contrib"
projects[user_terms][version] = "1.0"

projects[userpoints][subdir] = "contrib"
projects[userpoints][version] = "1.2"

projects[userpoints_nc][subdir] = "contrib"
projects[userpoints_nc][version] = "1.1"

projects[userpoints_user_picture][subdir] = "contrib"
projects[userpoints_user_picture][version] = "1.2"

projects[vertical_tabs][subdir] = "contrib"
projects[vertical_tabs][version] = "1.0-rc1"

projects[views][subdir] = "contrib"
projects[views][version] = "2.12"

projects[views_slideshow][subdir] = "contrib"
projects[views_slideshow][version] = "2.3"

projects[wikitools][subdir] = "contrib"
projects[wikitools][version] = "1.3"

projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][version] = "2.x-dev"

projects[wysiwyg_filter][subdir] = "contrib"
projects[wysiwyg_filter][version] = "1.5"


projects[activity_log][download][type] = "git"
projects[activity_log][download][url] = "http://git.drupal.org/project/activity_log.git"
projects[activity_log][download][version] = "6.x-2.x"
projects[activity_log][type] = "module"
projects[activity_log][subdir] = "contrib"


projects[commons_features][download][type] = "git"
projects[commons_features][download][revision] = "6.x-2.x"
projects[commons_features][download][url] = "http://git.drupal.org/sandbox/ezrag/1262136.git"
projects[commons_features][type] = "module"


projects[digests][download][type] = "git"
projects[digests][download][url] = "http://git.drupal.org/project/digests.git"
projects[digests][download][revision] = "6.x-1.x"
projects[digests][type] = "module"
projects[digests][subdir] = "contrib"

projects[facebook_status][download][type] = "git"
projects[facebook_status][download][url] = "http://git.drupal.org/project/facebook_status.git"
projects[facebook_status][download][revision] = "6.x-3.x"
projects[facebook_status][subdir] = "contrib"

; Themes

projects[fusion][version] = "1.0"
; @TODO: Create contrib project(s) for Commons-specific themes.

