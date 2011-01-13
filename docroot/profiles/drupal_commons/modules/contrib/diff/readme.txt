DESCRIPTION
----------------
This module adds 'diff' functionality to the 'Revisions' tab, allowing
users to nicely view all the changes between any two revisions of a node.

Users may also preview their changes before saving a new node.

TECHNICAL
-------------------
- Diff compares the raw data, not the filtered output, making
it easier to see changes to HTML entities, etc.
- The diff engine itself is a GPL'ed php diff engine from phpwiki.

API
-----------------
- This module offers hook_diff() which modules may use to inject their changes into the presentation of the diff. For example, this is used by cck.inc, upload.inc, and taxonomy.inc in this package.

TODO
-----------------
- Consider using in core.

MAINTAINERS
---------------
Moshe Weitzman  - http://drupal.org/moshe
Derek Wright  - http://drupal.org/user/46549
rötzi - http://drupal.org/user/73064
