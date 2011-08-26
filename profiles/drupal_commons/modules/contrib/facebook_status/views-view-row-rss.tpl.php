<?php

/**
 * @file
 *   Default view template to display a item in an RSS feed.
 *
 * Copied from views/theme/views-view-row-rss.tpl.php.
 */
?>
  <item>
    <title><?php print $title; ?></title>
    <link><?php print $link; ?></link>
    <description><?php print $description; ?></description>
    <?php print $item_elements; ?>
  </item>
