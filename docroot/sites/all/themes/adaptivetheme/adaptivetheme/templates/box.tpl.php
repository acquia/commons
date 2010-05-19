<?php // $Id: box.tpl.php,v 1.1.2.2 2009/12/16 22:52:29 jmburnz Exp $
// adaptivethemes.com

/**
 * @file box.tpl.php
 * Theme implementation to display a box.
 *
 * Available variables:
 * - $title: Box title.
 * - $content: Box content.
 *
 * @see template_preprocess()
 */
?>
<div class="box"><div class="box-inner">
  <?php if ($title): ?>
    <h2 class="box-title title"><?php print $title ?></h2>
  <?php endif; ?>
  <?php print $content ?>
</div></div> <!-- /box -->
