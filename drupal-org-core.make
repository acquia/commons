api = 2
core = 7.x

; Download Drupal core and apply core patches if needed.
projects[drupal][type] = "core"
projects[drupal][version] = 7.41

; This patch allows install profile to list requirements on the install page
; http://drupal.org/node/1971072
projects[drupal][patch][] = http://drupal.org/files/install_profile_requirements_on_install.patch

; This patch allows install profiles to set a minimum memory limit.
; http://drupal.org/node/1772316#comment-6457618
projects[drupal][patch][] = http://drupal.org/files/drupal-7.x-allow_profile_change_sys_req-1772316-21.patch

; Allow to specify SCRIPT HTML element attributes through drupal_add_js()
; http://drupal.org/node/1664602#comment-6221066
projects[drupal][patch][] = http://drupal.org/files/1664602-1.patch

; Optimize node access queries.
; https://drupal.org/comment/8516319#comment-8516319
projects[drupal][patch][] = https://drupal.org/files/issues/drupal-106721-optimize_node_access_queries-81.patch

; Statically cache node access grants
; https://drupal.org/comment/8495029#comment-8495029
projects[drupal][patch][] = http://drupal.org/files/issues/node_access_grants-static-cache-11.patch

; File_get_file_references is slow and buggy
; https://drupal.org/node/1805690#comment-8734045
projects[drupal][patch][] = http://drupal.org/files/issues/1805690_11.patch

; hook_comment_unpublish is never invoked
; https://www.drupal.org/node/2289369#comment-8897089
projects[drupal][patch][] = http://drupal.org/files/issues/comment-unpublish-d7-2289369-1-do-not-test.patch

; HTML IDs are reset each time a form is processed
; https://www.drupal.org/node/1831560#comment-10258827
projects[drupal][patch][] = http://drupal.org/files/issues/d7-form-html-id-1831560-14.patch

; Pass $page_callback_result through hook_page_delivery_callback_alter().
; http://drupal.org/node/897504
projects[drupal][patch][] = "http://drupal.org/files/issues/pass-page-callback-result-897504-2.patch"

; Xss filter() ignores malicious content in data-attributes and mangles image captions.
; http://drupal.org/node/2105841
projects[drupal][patch][] = "http://drupal.org/files/issues/do-2105841_no_protocol_filter-90.patch"
