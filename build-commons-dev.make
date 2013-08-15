api = 2
core = 7.x

; Include the definition of how to build Drupal core directly, including patches.
includes[] = "drupal-org-core.make"

; Download the Commons install profile and recursively build all its dependencies.
projects[commons][type] = "profile"
projects[commons][download][type] = "git"
projects[commons][download][url] = "http://git.drupal.org/project/commons.git"
projects[commons][download][branch] = "7.x-3.x"
; Provide a -dev version of the Commons make file, stopgap for nightly development snapshot
; https://drupal.org/node/1908812
projects[commons][patch][] = "http://drupal.org/files/1908812-commons-make-dev-59.patch"