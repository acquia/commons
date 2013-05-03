api = 2
core = 7.x

; Download Drupal core and apply core patches if needed.
projects[drupal][type] = "core"
projects[drupal][version] = "7.22"

; Hide the profiles under /profiles, so Commons is the only one. This allows
; the installation to start at the Language selection screen, bypassing a
; baffling and silly choice, especially for non-native speakers.
; http://drupal.org/node/1780598#comment-6480088
projects[drupal][patch][] = http://drupal.org/files/spark-install-1780598-5.patch
; This requires a core bug fix to not show the profile selection page when only
; one profile is visible.
; http://drupal.org/node/1074108#comment-6463662
projects[drupal][patch][] = http://drupal.org/files/1074108-skip-profile-16-7.x-do-not-test.patch

; This patch allows install profiles to set a minimum memory limit.
; http://drupal.org/node/1772316#comment-6457618
projects[drupal][patch][] = http://drupal.org/files/allow_change_system-requirements-1772316-4.patch

; This patch allows install profile to list requirements on the install page
; http://drupal.org/node/1971072
projects[drupal][patch][] = http://drupal.org/files/install_profile_requirements_on_install.patch
; Allow to specify SCRIPT HTML element attributes through drupal_add_js()
; http://drupal.org/node/1664602#comment-6221066
projects[drupal][patch][] = http://drupal.org/files/1664602-1.patch