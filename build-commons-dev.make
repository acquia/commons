api = 2
core = 7.x

; Include the definition of how to build Drupal core directly, including patches.
includes[] = "drupal-org-core.make"

; Download the Commons install profile and recursively build all its dependencies.
projects[commons][type] = "profile"
projects[commons][download][type] = "git"
projects[commons][download][url] = "http://git.drupal.org/project/commons.git"
; http://drupal.org/node/1908812#comment-7045196
projects[commons][patch][] = "http://drupal.org/files/1908812-drupal-org-dev-make-17.patch"
projects[commons][download][branch] = "7.x-3.x"