; $Id: README.txt,v 1.2.4.1 2008/10/20 18:29:36 nancyw Exp $

The RealName module allows the admin to choose fields from the user profile
that will be used to add a "realname" element (method) to a user object.
Hook_user is used to automatically add this to any user object that is loaded.

Installation
------------
Standard module installation applies.

Menus
-----
The only menu item is for the settings page.

Settings
--------
The most up-to-date information is at http://drupal.org/node/266616.

Permissions
-----------
There is one new permission, "use realname." This allows you to control which roles see the realname and which don't.

The settings page is controlled by the "administer users" permission.