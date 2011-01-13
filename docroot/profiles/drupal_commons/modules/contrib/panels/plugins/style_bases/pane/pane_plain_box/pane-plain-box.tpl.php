<?php
// $Id: pane-plain-box.tpl.php,v 1.1.2.1 2010/07/13 23:55:58 merlinofchaos Exp $
/**
 * @file
 *
 * Display the box for rounded corners.
 *
 * - $pane: The pane being rendered
 * - $display: The display being rendered
 * - $content: An object containing the content and title
 * - $output: The result of theme('panels_pane')
 * - $classes: The classes that must be applied to the top divs.
 */
?>
<div class="<?php print $classes ?>">
  <?php print $output; ?>
</div>
