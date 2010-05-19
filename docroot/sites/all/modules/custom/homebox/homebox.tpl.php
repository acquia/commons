<?php
// $Id: homebox.tpl.php,v 1.1.2.1 2009/05/19 13:58:39 jchatard Exp $

/**
 * @file
 * homebox.tpl.php
 * Default layout for homebox.
 */
?>
<?php global $user; ?>
<div id="homebox" class="column-count-<?php print $column_count ?>">
  <ul class="homebox-config-links">
    <li class="homebox-config-link">
      <a href="#" id="homebox-add"><?php print t('Edit content') ?></a>
    </li>
    <?php if ($user->uid): ?>
      <li class="homebox-config-link">
        <span id="homebox-restore">
          <a href="#"><?php print t('Restore to defaults') ?></a>
        </span>  
      </li>
      <li class="homebox-config-link">
        <span id="homebox-save">
          <a href="#"><?php print t('Save settings') ?></a>
          <span><?php print t('Saving settings...'); ?></span>
        </span>
      </li>
    <?php endif; ?>
  </ul>
  
  <ul id="homebox-settings" class="homebox-settings-hidden">
    <?php foreach ($available_blocks as $key => $block): ?>
      <?php if ($block['closable']): ?>
        <li>
          <input type="checkbox" class="homebox_toggle_box" <?php print $block['checked'] ?> id="homebox_toggle_<?php print $block['dom_id'] ?>" /> <?php print $block['subject'] ?>
        </li>
      <?php endif; ?>
    <?php endforeach ?>
  </ul>

  <?php for ($i = 1; $i <= count($regions); $i++): ?>
   <div class="homebox-column-wrapper">
    <div class="homebox-column" id="homebox-column-<?php print $i ?>">
      <?php foreach ($regions[$i] as $key => $weight): ?>
        <?php foreach ($weight as $block): ?>
          <?php if ($block->content): ?>
            <?php print theme('homebox_block', $block, $page) ?>
          <?php endif ?>
        <?php endforeach ?>
      <?php endforeach ?>
    </div>
   </div>
  <?php endfor ?>

  <div class="clear-block"></div>
</div>

<?php
// Print CSS classes based on colors
print $color_css_classes;
?>
<!-- End Homebox -->
