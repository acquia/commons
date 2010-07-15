/* $Id: README.txt,v 1.4.4.2 2009/06/09 18:44:16 smk Exp $ */

-- SUMMARY --

The purpose of this module is to provide a central transliteration service for
other Drupal modules, as well as sanitizing file names while uploading files
to Drupal.

For a full description visit the project page:
  http://drupal.org/project/transliteration
Bug reports, feature suggestions and latest developments:
  http://drupal.org/project/issues/transliteration


-- INSTALLATION --

1. Copy the transliteration module to your modules directory

2. If you are installing to an existing Drupal site, you might want to enable
   retroactive transliteration during installation of this module. This will
   update all file names containing non-ASCII characters. However, if you have
   hard-coded links in your contents these will be broken and require manual
   fixing. Therefore you have to manually enable this feature by editing
   transliteration.install and change the following line at the top of the file:

     define('TRANSLITERATION_RETROACTIVE', FALSE);

   to

     define('TRANSLITERATION_RETROACTIVE', TRUE);

   If you already installed the module and would like to execute retroactive
   transliteration afterwards, you can rerun update.php and manually select
   update #1.

3. Enable the module on Site building > Modules.

4. That's it. The names of all new uploaded files will now automatically be
   transliterated and cleaned from non-ASCII characters.


-- 3RD PARTY INTEGRATION --

Third party developers who are seeking an easy way to transliterate strings may
use the transliteration_get() helper function:

if (module_exists('transliteration')) {
  $transliterated = transliteration_get($string);
}

You might want to take a look at the PHPDoc for an explanation of additional
function parameters.


-- LANGUAGE SPECIFIC REPLACEMENTS --

This module uses transliteration data collected from various sources which might
be incomplete or inaccurate for your specific language. Therefore,
transliteration supports language specific alterations to the basic replacements. The following guide explains how to add them:

1. First find the Unicode character code you want to replace. As an example,
   we'll be adding a custom transliteration for the cyrillic character 'г'
   (hexadecimal code 0x0433) using the ASCII character 'q' for Azerbaijani
   input.

2. Transliteration stores its mappings in banks with 256 characters each. The
   first two digits of the character code (04) tell you in which file you'll
   find the corresponding mapping. In our case it is data/x04.php.

3. If you open that file in an editor, you'll find the base replacement matrix
   consisting of 16 lines with 16 characters on each line, and zero or more
   additional language-specific variants. To add our custom replacement, we need
   to do two things: first, we need to create a new transliteration variant
   for Azerbaijani since it doesn't exist yet, and second, we need to map the
   last two digits of the hexadecimal character code (33) to the desired output.
   To do this, add a new key right before the last closing bracket:

     'az' => array(0x33 => 'q'),

   (see http://people.w3.org/rishida/names/languages.html for a list of
   language codes).

   Any Azerbaijani input will now use the appropriate variant.

Also take a look at data/x00.php which already contains a bunch of language
specific replacements. If you think your overrides are useful for others please
create and file a patch at http://drupal.org/project/issues/transliteration.


-- CREDITS --

Authors:
* Stefan M. Kudwien (smk-ka) - dev@unleashedmind.com
* Daniel F. Kudwien (sun) - dev@unleashedmind.com

This project has been sponsored by UNLEASHED MIND
Specialized in consulting and planning of Drupal powered sites, UNLEASHED
MIND offers installation, development, theming, customization, and hosting
to get you started. Visit http://www.unleashedmind.com for more information.

UTF-8 normalization uses MediaWiki's UtfNormal.php (http://www.mediawiki.org)
and transliteration is based on CPAN's Text::Unidecode library
(http://search.cpan.org/~sburke/Text-Unidecode-0.04/lib/Text/Unidecode.pm).

