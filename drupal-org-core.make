api = 2
core = 7.x

; Download Drupal core and apply core patches if needed.
projects[drupal][type] = "core"
projects[drupal][version] = "7.15"

; Allow to specify SCRIPT HTML element attributes through drupal_add_js()
; https://drupal.org/node/1664602#comment-6221066
projects[drupal][patch][] = https://drupal.org/files/1664602-1.patch
