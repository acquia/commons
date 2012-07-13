; This Drush make script assembles a development version of the Drupal Commons distribution.
; To package Commons using this script, install Drush make (http://drupal.org/project/drush_make).
; Packaging with the --working-copy flag is recommended for developers since
; it reduces the effort necessary to roll a patch against Commons components
; that live at http://drupal.org/project/commons .

core = 6.x
api = 2

projects[drupal][version] = "6.26"
; http://drupal.org/node/1564996#comment-5963056
projects[drupal][patch][] = "http://drupal.org/files/1564996_one_time_watchdog_more_info-D6.patch"

projects[drupal_commons][type] = "profile"
projects[drupal_commons][download][type] = "file"
projects[drupal_commons][download][url] = "http://ftp.drupal.org/files/projects/commons-6.x-2.9.tar.gz"

  