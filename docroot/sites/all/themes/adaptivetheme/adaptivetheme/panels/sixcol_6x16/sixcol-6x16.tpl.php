<?php
// $Id: sixcol-6x16.tpl.php,v 1.1.2.2 2010/01/02 05:43:09 jmburnz Exp $
/**
 * @file
 * Template for a 6 column panel layout.
 *
 * This template provides a six column 6 x 16% panel display layout.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['col1']: Content column one.
 *   - $content['col2']: Content column two.
 *   - $content['col3']: Content column three.
 *   - $content['col4']: Content column four.
 *   - $content['col5']: Content column five.
 *   - $content['col6']: Content column six.
 */
?>
<div class="panel-display sixcol-6x16 at-panel clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <div class="panel-panel panel-col-one">
    <div class="inside"><?php print $content['col1']; ?></div>
  </div>
  <div class="panel-panel panel-col-two">
    <div class="inside"><?php print $content['col2']; ?></div>
  </div>
  <div class="panel-panel panel-col-three">
    <div class="inside"><?php print $content['col3']; ?></div>
  </div>
  <div class="panel-panel panel-col-four">
    <div class="inside"><?php print $content['col4']; ?></div>
  </div>
  <div class="panel-panel panel-col-five">
    <div class="inside"><?php print $content['col5']; ?></div>
  </div>
  <div class="panel-panel panel-col-six">
    <div class="inside"><?php print $content['col6']; ?></div>
  </div>
</div>