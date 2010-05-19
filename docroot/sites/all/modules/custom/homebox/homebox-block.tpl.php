<?php
// $Id: homebox-block.tpl.php,v 1.1.2.2 2009/05/26 14:18:32 jchatard Exp $

/**
 * @file
 * homebox-block.tpl.php
 * Default theme implementation each homebox block.
 */
?>
<div id="homebox-block-<?php print $block->module .'-'. $block->delta; ?>" class="<?php print $block->homebox_classes ?> clear-block block block-<?php print $block->module ?>">
  <div class="homebox-portlet-inner">
    <h3 class="portlet-header"><?php print $block->subject ?></h3>
    <div class="portlet-config">
      <?php if ($page->settings['color']): ?>
        <div class="homebox-colors">
          <?php for ($i=0; $i < HOMEBOX_NUMBER_OF_COLOURS; $i++): ?>
            <span href="#" class="homebox-color-selector" style="background-color: <?php print $page->settings['colors'][$i] ?>;">&nbsp;</span>
          <?php endfor ?>
        </div>
      <?php endif ?>
      <?php if ($page->settings['color'] || $block->module == 'views' && !is_null($filters)): ?>
        <div class="clear-block"></div>
      <?php endif ?>
    </div>
    <div class="portlet-content"><?php print $block->content ?></div>
  </div>
</div>
