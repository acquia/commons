api = 2
core = 7.x

; Download Drupal core and apply core patches if needed.
projects[drupal][type] = "core"
projects[drupal][version] = "7.21"

; Hide the profiles under /profiles, so Commons is the only one. This allows
; the installation to start at the Language selection screen, bypassing a
; baffling and silly choice, especially for non-native speakers.
; http://drupal.org/node/1780598#comment-6480088
projects[drupal][patch][] = http://drupal.org/files/spark-install-1780598-5.patch
; This requires a core bug fix to not show the profile selection page when only
; one profile is visible.
; http://drupal.org/node/1074108#comment-6463662
projects[drupal][patch][] = http://drupal.org/files/1074108-skip-profile-16-7.x-do-not-test.patch


; Allow to specify SCRIPT HTML element attributes through drupal_add_js()
; http://drupal.org/node/1664602#comment-6221066
projects[drupal][patch][] = http://drupal.org/files/1664602-1.patch
