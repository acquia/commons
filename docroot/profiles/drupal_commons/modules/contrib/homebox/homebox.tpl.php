<?php
// $Id: homebox.tpl.php,v 1.1.4.18 2010/07/02 19:49:39 mikestefff Exp $

/**
 * @file
 * homebox.tpl.php
 * Default layout for homebox.
 */
?>
<?php global $user; ?>
<div id="homebox" class="column-count-<?php print $column_count; ?> homebox-<?php print $page->name; ?>">
  <div id="homebox-buttons">
    <button id="homebox-edit-link"><?php print t('Toggle items'); ?></button>
    <?php if ($user->uid): ?>
      <?php if ($page->settings['custom']): ?>
        <button id="homebox-add-link"><?php print t('Add item'); ?></button>
      <?php endif; ?>
      <button id="homebox-restore-link"><?php print t('Restore to defaults'); ?></button>
      <button id="homebox-save-link"><?php print t('Save settings'); ?></button>
      <span id="homebox-minimize-to-save"><?php print t('Minimize to save'); ?></span>
      <span id="homebox-changes-made">* <?php print t('Unsaved'); ?></span>
    <?php endif; ?>
  </div>
  
  <div id="homebox-settings" title="Toggle available widgets">
    <ul>
      <?php foreach ($available_blocks as $key => $block): ?>
        <?php if ($block['closable']): ?>
          <li>
            <input type="checkbox" class="homebox_toggle_box" <?php print $block['checked']; ?> id="homebox_toggle_<?php print $block['dom_id']; ?>" /> <?php print $block['subject']; ?>
          </li>
        <?php endif; ?>
      <?php endforeach ?>
    </ul>
  </div>

  <?php for ($i = 1; $i <= count($regions); $i++): ?>
   <div class="homebox-column-wrapper homebox-column-wrapper-<?php print $i; ?>"<?php print count($page->settings['widths']) ? ' style="width: ' . $page->settings['widths'][$i] . '%;"' : ''; ?>>
    <div class="homebox-column" id="homebox-column-<?php print $i; ?>">
      <?php foreach ($regions[$i] as $key => $weight): ?>
        <?php foreach ($weight as $block): ?>
          <?php if ($block->content): ?>
            <?php print theme('homebox_block', $block, $page); ?>
          <?php endif ?>
        <?php endforeach ?>
      <?php endforeach ?>
    </div>
   </div>
  <?php endfor ?>

  <!-- Used by jQuery UI to provide popups -->
  <div id="homebox-save-message"><?php print t('Saving settings') . '...'; ?></div>
  <div id="homebox-restore-confirmation" title="<?php print t('Are you sure you want to restore to defaults?'); ?>">
    <div style="width:400px;"><?php print t('Completing this action will purge your custom settings and items and restore the page to the default configuration.
    This action cannot be undone.'); ?></div>
  </div>
  <div id="homebox-restore-inprogress"><?php print t('Restoring default settings') . '...'; ?></div>
  <div id="homebox-add-form" title="<?php print t('Add a new item'); ?>">
    <form class="form-item" action="">
      <div id="homebox-add-form-status"></div>
      <div>
        <label><?php print t('Title'); ?></label>
        <input type="text" name="title" id="homebox-add-form-title" class="" />
        <label><?php print t('Content') ?></label>
        <textarea name="content" id="homebox-add-form-content" class="" rows="5" cols="5"></textarea>
      </div>
    </form>
  </div>
  <div id="homebox-edit-form" title="<?php print t('Edit item'); ?>">
    <form class="form-item" action="">
      <div id="homebox-edit-form-status"></div>
      <div>
        <label><?php print t('Title'); ?></label>
        <input type="text" name="title" id="homebox-edit-form-title" class="" />
        <label><?php print t('Content'); ?></label>
        <textarea name="content" id="homebox-edit-form-content" class="" rows="5" cols="5"></textarea>
        <input type="hidden" value="" />
      </div>
    </form>
  </div>
  <div id="homebox-delete-custom-message" title="<?php print t('Deletion confirmation'); ?>">
    <?php print t('Are you sure you want to delete this item? This action cannot be undone.'); ?>
    <input type="hidden" value="" />
  </div>
  <div class="clear-block"></div>
  <!-- Used by jQuery to determine page ID -->
  <input type="hidden" class="name" value="<?php print $page->name; ?>" />
</div>

<!-- End Homebox -->
