------------------------------------------------------------------------------
  User Badges Module for Drupal
------------------------------------------------------------------------------

Description
===========
The User Badges module allows each user to be assigned 'badges', displayed as
a series of iconic images. A common use will probably be to display the badges
along with the user's information within forums, comments, or node postings.
These badges can be assigned individually by the administrator or attached to
a role so that, for example, all users in the 'admin' role will show the
'Administrator' badge which could display as any graphic.

Any badge can optionally be associated to a URL that links the image to a
description page. This URL has token support. If a user has more than one badge,
there is also a mechanism that allows administrators to only show the highest
level badges.

You can also set a special badge for blocked users and even override their 
role badges with this one.

User Badges can be used as a way to establish trust (in the same way as eBay's
star graphics) or as an incentive for users. They can also be a quick way to
identify moderators, administrators, or anyone with a given role.


Limitation
==========

The badge image library is not compatible with the "private" file download method,
but the module can still be used; just ignore the Images tab on the badge admin
screen.


Dependencies
============
In order to upload images via the user interface, user badges depends on:

* Upload

For dynamic badge sizing (optional):

* ImageCache

User Product Badges requires:

* ecommerce


Configuration
=============
Once the module is activated, go to Administer >> User management >> Badges
(admin/user/user_badges). Here you'll find three tabbed sections for User Badges.

* List - Lists all current badges and allows you to edit them.
* Add - Add a new badge.
* Images - The badge image library. If you already have images available, you
    can ignore this, but if you need a way to upload images for badges, this
    is the place.
* Roles - Here you can associate a badge with a given role so that all users
    with that role will display the selected badge.
* Settings - where you can set the global settings for the module
    (including whether or not to use ImageCache).
* Products - This tab is provided by the module User Product Badges. It allows 
    you to associate badges with products for the ecommerce module.


Permissions
===========
The module provides two permissions:

Users with the 'manage badges' access permission will have access to the 
administration pages for the module.

Users with the 'change badge assignments' access permission will be shown a 
'Badges' tab when visiting user profiles. This is the place to manually assign 
badges to users.


Display badges
==============
To display user badges in your theme use:

<?php
  if (module_exists('user_badges')) {
    print user_badges_for_uid($uid);
  }
?>

Note: $uid means 'a user id' here, not the literal use of $uid. Most people will use
the uid of the node ($node->uid) or comment ($comment->uid) author.

In Drupal (and theming), $node is a PHP object that represents the node, and $comment
represents the comment. They are not always both available in every template file, so
check the comments at the top of the file to see what is available. You may have
access to other uids (user ids), and in these cases you can replace $uid with that
value.


Current maintainer
===================
Richard Skinner (http://drupal.org/user/310635)


Former maintainers
==================
* Jeff Robbins (http://drupal.org/user/17190)
* Chad Phillips (http://drupal.org/user/22079)
* Heine Deelstra (http://drupal.org/user/17943)
* Nuno Veloso (http://drupal.org/user/80656)
