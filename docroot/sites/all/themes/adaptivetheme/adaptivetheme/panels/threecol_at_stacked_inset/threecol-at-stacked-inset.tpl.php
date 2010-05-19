<?php
// $Id: threecol-at-stacked-inset.tpl.php,v 1.1.2.2 2010/01/02 05:43:09 jmburnz Exp $
//adaptivethemes

/**
 * @file
 * Template for a 3 column stacked panel layout with extra panels top and bottom.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top']: Content in the top row.
 *   - $content['left']: Content in the left column.
 *   - $content['middle']: Content in the middle column.
 *   - $content['right']: Content in the right column.
 *   - $content['bottom']: Content in the bottom row.
 */
?>
<div class="panel-display threecol-at-stacked-inset clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <div class="panel-panel panel-col-first">
    <div class="inside"><?php print $content['left']; ?></div>
  </div>
  <div class="center-wrapper">
    <div class="panel-panel panel-col-top">
      <div class="inside"><?php print $content['top']; ?></div>
    </div>
    <div class="panel-panel panel-col">
      <div class="inside"><?php print $content['middle']; ?></div>
    </div>
    <div class="panel-panel panel-col-last">
      <div class="inside"><?php print $content['right']; ?></div>
    </div>
    <div class="panel-panel panel-col-bottom">
      <div class="inside"><?php print $content['bottom']; ?></div>
    </div>
  </div>
</div>