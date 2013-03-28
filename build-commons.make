api = 2
core = 7.x

; Include the definition of how to build Drupal core directly, including patches.
includes[] = "drupal-org-core.make"

; Download the Commons install profile and recursively build all its dependencies.
projects[commons][type] = "profile"