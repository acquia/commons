<?php
// $Id: block.tpl.php 5639 2009-12-24 01:14:40Z chris $
?>

<?php $skinr.=' fusion-horiz-login';
drupal_add_js(drupal_get_path('theme', 'fusion_core').'/js/jquery.overlabel.js', 'theme'); ?>

<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="block block-<?php print $block->module ?> <?php print $block_zebra; ?> <?php print $position; ?> <?php print $skinr; ?>">
  <div class="inner clearfix">
    <?php if (isset($edit_links)): ?>
    <?php print $edit_links; ?>
    <?php endif; ?>
    <?php if ($block->subject): ?>
   <!-- <h2 class="title block-title"><?php print $block->subject ?></h2>-->
    <?php endif;?>
    <div class="content">
      <?php print $block->content ?>
    </div>
  </div><!-- /block-inner -->
</div><!-- /block -->
