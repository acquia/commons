$Id: README.txt,v 1.1 2008/10/20 19:33:59 kbahey Exp $

By Khalid Baheyeldin

Copyright 2008 http://2bits.com

Description
-----------
This module provides performance statistics logging for a site, such as page generation
times, and memory usage, for each page load.

This module is useful for developers and site administrators alike to identify pages that
are slow to generate or use excessive memory.

Features include:
* Settings to enable detailed logging or summary logging. The module defaults to no
  logging at all.

* Detailed logging causes one database row to be written for each page load of the site.
  The data includes page generation time in milliseconds, and the number of bytes allocated
  to PHP, time stamp, ...etc.

* Summary logging logs the average and maximum page generation time, average and maximum memory
  usage, last access time, and number of accesses for each path.

* Summary is logged to APC, if installed, so as to not cause extra load on the database. This is
  the only mode recommended for live sites.

* A settings option is available when using summary mode with APC, to exclude pages with less
  than a certain number of accesses. Useful for large sites.

* Support for normal page cache.

Note that detailed logging is only suitable for a site that is in development or testing. Do NOT enable
detailed logging on a live site.

The memory measurement feature of this module depends on the memory_get_peak_usage() function, available
only in PHP 5.2.x or later.

Only summary logging with APC is the recommended mode for live sites, with a threshold of 2 or more.

Patches:
--------
For Drupal 5.x, a simple patch is needed if you want to use the module with Drupal's normal page caching
mode.

The patch is included in the patches directory in the module's tarball.

To apply the patch, check http://drupal.org/patch for instructions.

If you are using Drupal 6.x or higher, there is no need for this patch.

Bugs/Features/Patches:
----------------------
If you want to report bugs, feature requests, or submit a patch, please do so at the project page on
the Drupal web site at http://drupal.org/project/performance

Author
------
Khalid Baheyeldin (http://baheyeldin.com/khalid and http://2bits.com)

If you use this module, find it useful, and want to send the author a thank you note, then use the
Feedback/Contact page at the URL above.

The author can also be contacted for paid customizations of this and other modules.
