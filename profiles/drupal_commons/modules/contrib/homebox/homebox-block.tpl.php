<?php
// $Id: homebox-block.tpl.php,v 1.1.4.9 2010/07/02 19:38:19 mikestefff Exp $

/**
 * @file
 * homebox-block.tpl.php
 * Default theme implementation each homebox block.
 */
?>
<div id="homebox-block-<?php print $block->module .'-'. $block->delta; ?>" class="<?php print $block->homebox_classes ?> clear-block block block-<?php print $block->module ?>">
  <div class="homebox-portlet-inner">
    <h3 class="portlet-header"><span class="portlet-title"><?php print $block->subject ?></span></h3>
    <div class="portlet-config">
      <?php if ($page->settings['color']): ?>
        <div class="homebox-colors">
          <span class="homebox-color-message"><?php print t('Select a color') . ':'; ?></span>
          <?php for ($i=0; $i < HOMEBOX_NUMBER_OF_COLOURS; $i++): ?>
            <span class="homebox-color-selector" style="background-color: <?php print $page->settings['colors'][$i] ?>;">&nbsp;</span>
          <?php endfor ?>
        </div>
      <?php endif; ?>
      <?php if ($block->module == 'homebox'): ?>
        <button id="delete-<?php print $block->module . '_' . $block->delta; ?>" class="homebox-delete-custom-link"><?php print t('Delete'); ?></button>
        <button id="edit-<?php print $block->module . '_' . $block->delta; ?>" class="homebox-edit-custom-link"><?php print t('Edit'); ?></button>
      <?php endif; ?>
      <?php if ($page->settings['color'] || $block->module == 'views' && !is_null($filters)): ?>
        <div class="clear-block"></div>
      <?php endif ?>
    </div>
    <div class="portlet-content content"><?php print $block->content; ?></div>
    <?php print $block->hidden; ?>
  </div>
</div>
