<?php
// $Id: block.tpl.php,v 1.1.2.1 2010/01/11 00:08:12 sociotech Exp $
?>

<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="block block-<?php print $block->module ?> <?php print $block_zebra; ?> <?php print $position; ?> <?php print $skinr; ?>">
  <div class="inner clearfix">
    <?php if (isset($edit_links)): ?>
    <?php print $edit_links; ?>
    <?php endif; ?>
    <?php if ($block->subject): ?>
    <h2 class="title block-title"><?php print $block->subject ?></h2>
    <?php endif;?>
    <div class="content">
      <?php print $block->content ?>
    </div>
  </div><!-- /block-inner -->
</div><!-- /block -->
