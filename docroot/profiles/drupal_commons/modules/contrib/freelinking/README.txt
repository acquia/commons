# freelinking.module -- a freelinking filter for Drupal
---

by [ea. Farris] [1], with portions adapted from work done by [Christopher
Whipple] [2] on his wiki.module.

## What it does

freelinking.module allows content authors to link to other pieces of
content (ie., nodes) in the Drupal site easily, using CamelCase words
and freelinking delimiters, currently defined as double-square brackets
( [[ and ]] ).

When enabled, the freelinking filter searches the body of nodes looking
for "CamelCase" style words (words that begin with a capital letter and
have one or more capitalized words run together) and words or phrases
enclosed in double-square brackets [[like this]]. These words become
clickable to a node with the words as the title. If no node so titled
exists, the link will attempt to create the node and present the user
with the node creation form, with the title already filled in.

In addition to these simple linking styles, freelinking.module also
supports an expanded syntax using the double-square bracket method.
Freelinks containing a bar (or pipe, '|') will link different text to
the target. For example, [[this is what's shown|this is the target]]
will link the text "this is what's shown" to content titled "this is the
target," or, if that doesn't exist, the create content page will be
shown with "this is the target" as the title.

Freelinks within double-square brackets can also contain URLs that begin
with http://. So links like this [[Drupal Web Site|http://www.drupal.org]]
are acceptable, as is [[http://www.drupal.org]], which will show the URL
in the body and link it.

## Installation and activation

For installation instrutions, and for information on how to activate
this module, see INSTALL.txt

## Configuration

Currently, freelinking.module supports the following configuration
options:

- What kind of node will the filter attempt to create if a target node
  was not found? This can be any node type. A simple flexinode with
  title and body, that is editable by anyone, could turn Drupal into a
  wiki. Defaults to 'blog.'

- What kind of node will be searched for, when looking up a title? This
  should be the same as the creation node type, above, or new
  freelinking-created content won't ever be found. Defaults to 'no
  restrictions,' meaning all content types are eligible to be the target
  of a freelink.

- If you don't want to turn CamelCase words into links, you can turn
  that off. It defaults to on.

Other options planned, but not yet implemented, include:

- Flexible delimiters for phrases. Double-square brackets are used by
  the interwiki.module [3], so this filter should give some choice as to
  what will be used as the freelinking delimiters.
- Restrict freelinking to nodes created by the same user. For example,
  Author1 writing a blog entry with freelinks should expect his links to
  resolve to other content by him, and not just any content on the site.
  This would give multi-authored sites into several private wikis, each
  linking only to his or her own content.

## "freelinks" menu option

When the freelinking.module is activated, a "freelinks" menu choice
appears on the navigation menu. Clicking this brings up a page showing
all the freelinks currently indexed in the Drupal site, along with a
link to either "view this content" or "create this content." With this
page, users can find content that is the target of a link, but doesn't
yet exist, "filling in the gaps," so to speak. This feature came about
because of a feature request at http://drupal.org/node/20405 .

---
References

[1] : mailto:eafarris@gmail.com
[2] : http://crw.typepad.com
[3] : http://drupal.org/project/interwiki

---
freelinking.module by ea.Farris <eafarris@gmail.com>
$Id: README.txt,v 1.3.8.1 2008/03/18 13:28:11 eafarris Exp $
