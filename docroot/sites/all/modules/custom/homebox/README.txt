// $Id: README.txt,v 1.1.2.3 2010/04/30 09:13:31 jchatard Exp $

Welcome to Home box.

CONTENTS OF THIS FILE
---------------------

 * Requirements
 * Optional requirements
 * Installation
 * Things to know

REQUIREMENTS
------------

 * jQuery UI 6.x-1.2 - http://drupal.org/project/jquery_ui
 * jQuery UI 1.6
   - Grab jQuery UI package from Google Code - http://jquery-ui.googlecode.com/files/jquery.ui-1.6.zip

OPTIONAL REQUIREMENTS
---------------------

The following modules are not required but recommended for integration or ease of use:

 * Path 6.x (provided with Drupal core)
 * Color picker 6.x-1.0-beta1 - http://drupal.org/project/colorpicker
 * Views 6.x-2.10 -  http://drupal.org/project/views
 * Advanced Help 6.x-1.2 - http://drupal.org/project/advanced_help

INSTALLATION
------------

 * Enable jQuery UI modules
 * Be sure to follow instructions from README.txt in jQuery UI module

   --- IMPORTANT ---- Begin
   Be sure to grab jQuery UI package from Google Code - http://jquery-ui.googlecode.com/files/jquery.ui-1.6.zip

   If not sure read this http://drupal.org/node/463270
   --- IMPORTANT ---- End

 * Enable optional modules if you want (see list above)
 * Enable Home box module
 * Go to Administer > Site building > Home box
 * Create an new page
 * Edit your newly created page to fill in the desired path alias
 * Visit your page settings, set the number of columns, etc.
 * Visit your page layout and assign some blocks
 * A menu item is automatically created in the navigation menu
 * Don't forget to visit Drupal permissions' page to allow access to your page by some roles
 
THINGS TO KNOW
--------------
 * Empty home box page (404)
   If you do not assign any block for a page, Drupal will return a 404 error, this is by design

 * Permissions
   Homebox tries to respect Drupal permissions system, so if you don't see some blocks,
   maybe they are only visible by some roles
 
 * Views 2
   You can add blocks created with Views, but you must be aware of the followings:
   - Your View must have a "block display"
   - Give a "Title" to your Block
   - In "Block settings" give an "Admin" value to your block
   - If you use "Exposed filters":
     - You should check the option "Remember (Remember the last setting the user gave this filter.)"
       for exposed filter you set.
     - "Use AJAX" must be set to "Yes" (otherwise, user will be sent to the page display of the View when clicking the Apply button)
     - "Empty text" should be set, if no value is given, then exposed filters won't work if initial view result is empty
