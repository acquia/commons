# Commons
[![Travis build status](https://img.shields.io/travis/acquia/commons/7.x-3.x.svg)](https://travis-ci.org/acquia/commons) [![Scrutinizer code quality](https://img.shields.io/scrutinizer/g/acquia/commons/7.x-3.x.svg)](https://scrutinizer-ci.com/g/acquia/commons)

Drupal Commons is a "community collaboration website in a box" built on Drupal.

### Installation

In addition to standard installation via the UI, Commons can be built using Drush make.

  ``drush make build-commons.make ~/Destination/docroot``

Use the ``site-install`` command to install Drupal with the Commons installation profile.

  ``drush si commons``

You may now login to your site.

  ``drush uli -l http://mysite.dd``

### Behat tests

Install the drupal-extension for mink/behat from the Commons profile.

  ``cd profiles/commons/tests && composer install``

Set up a behat.yml file replacing ``@BASE_URL@`` with the URL to your site and ``@DRUPAL_ROOT@`` with the path to your site on disk.

  ``cp behat.template.yml behat.yml``

Check that behat is installed and running.

  ``bin/behat --help``

Run tests.

  ``bin/behat``

### Documentation

Official documentation for Commons is available at https://docs.acquia.com/commons.

### Resources

The Commons project is available at: http://drupal.org/project/commons.
