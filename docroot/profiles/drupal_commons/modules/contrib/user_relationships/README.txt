$Id: README.txt,v 1.6.2.9 2008/04/21 00:38:17 sprsquish Exp $

User Relationships
------------------
User Relationships is a pretty self-descriptive module. It allows users the
opportunity to create relationships between each other.

The module has been broken up into component pieces in an effort to keep the size
down and the speed up. The list of modules and a quick intro about each is below

Send comments to Jeff Smick: http://drupal.org/user/107579/contact, or post an issue at
http://drupal.org/project/user_relationships.

Requirements
------------
Drupal 6


Installation
------------
1.  Copy the user_relationships folder to the appropriate Drupal (sites/all/modules or sites/all/default) directory.

2.  Enable User Relationships in the "Site building -> Modules" administration screen.

    If this is only a requirement of another module and the UI is not needed you'll
    only need to enable the API module.

3.  If you've enabled the UI module you can create relationship types and modify settings under
    Administer -> User management -> Relationships


Included Modules
----------------
NOTE: Please read the individual README.txt files in each module's directory for a more in-depth
      explanation of the module and its functionality.

User Relationships API:
  This is the purely functional portion. It will only provide an API that other modules can
  use to control relationships

User Relationships UI:
  A basic user interface. UR-UI provides admins the ability to create realtionship types and
  users to request/cancel/approve/disapprove/remove relationships with each other.

User Relationship Blocks:
  Provides some basic blocks to show relationships and perform actions.

User Relationship Defaults:
  Gives admins the ability to create default relationships that are added to a user when they sign up

User Relationship Implications:
  Enables the creation of implied relationships, relationships that are created automatically when
  a specified relationship is created.

User Relationships Mailer:
  A helper module that will send email notifications about relationship actions



Credits
-------
Written by Jeff Smick (sprsquish).
Originally written for and financially supported by OurChart Inc. (http://www.ourchart.com)
Thanks to the BuddyList module team for their inspiration
