<?php
// $Id: twocol-at-33-66.tpl.php,v 1.1.2.2 2010/01/02 05:43:09 jmburnz Exp $
/**
 * @file
 * Template for a 2 column panel layout.
 *
 * This template provides a two column 33%-66% panel display layout, to 
 * fit the Adaptivetheme grid system.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['left']: Content in the left column.
 *   - $content['right']: Content in the right column.
 */
?>
<div class="panel-display twocol-at-33-66 at-panel clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <div class="panel-panel panel-col-first">
    <div class="inside"><?php print $content['left']; ?></div>
  </div>
  <div class="panel-panel panel-col-last">
    <div class="inside"><?php print $content['right']; ?></div>
  </div>
</div>