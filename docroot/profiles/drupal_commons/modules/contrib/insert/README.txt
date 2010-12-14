// $Id: README.txt,v 1.1.2.1 2010/07/27 04:01:13 quicksketch Exp $

Insert is a utility that makes inserting images and links to files into text
areas or WYSIWYGs much easier. It adds a simple JavaScript-based button to
FileField and ImageField widgets. When used with ImageField and ImageCache,
images may be inserted into text areas with a specific ImageCache preset.

Insert was written by Nate Haug.

This Module Made by Robots: http://www.lullabot.com

Dependencies
------------

Insert module does not have any dependencies, but it won't do anything unless
you have at least one of the following installed:

* FileField
* ImageField

Recommended
-----------

* ImageCache
* WYSIWYG module

Install
-------

1) Copy the insert folder to the modules folder in your installation. Usually
   this is sites/all/modules.

2) In your Drupal site, enable the module under Administer -> Site building ->
   Modules (/admin/build/modules).

3) Add or configure a FileField or ImageField under Administer -> Content
   management -> Content types -> [type] -> Manage Fields
   (admin/content/node-type/[type]/fields). Once configuring a field, there is a
   new section in the Field options for "Insert". You can then configure the
   field to include an Insert button and what templates you would like to have.

4) Create a piece of content with the configured field. After uploading a file,
   an "Insert" button will appear. Click this button to send the file or image
   into the Body field.

Insert should work on multiple fields (the last field that was active will
received the file), and with most popular WYSIWYG editors. Note that FCKeditor
only supports the Body field due to an API limitation.

Theming
-------

Insert can be configured to work with non-HTML filters like BBCode or Markdown.
To do this, copy the template file you would like to change from the "templates"
directory to your active theme's directory. Then empty your Drupal caches at
admin/settings/performance.

The ImageCache templates may also be used per ImageCache preset. You can copy
the imagecache-insert-image.tpl.php file to your theme directory and then
rename it to imagecache-insert-image--[preset-name].tpl.php, where [preset-name]
is the name of the ImageCache preset. Change underscores to hyphens in the
preset name.
