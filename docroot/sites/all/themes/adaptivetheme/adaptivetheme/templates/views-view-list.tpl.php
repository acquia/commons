<?php // $Id: views-view-list.tpl.php,v 1.1.2.3 2010/03/14 01:59:18 jmburnz Exp $
// adaptivethemes.com

/**
 * @file views-view-list.tpl.php
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */
?>
<?php
// Conditionally add extra classes.
if (theme_get_setting(cleanup_views_item_list)) {
  $extra_classes = TRUE;
}
?>
<div class="item-list">
  <?php if (!empty($title)) : ?>
    <h3><?php print $title; ?></h3>
  <?php endif; ?>
  <<?php print $options['type']; ?>>
    <?php foreach ($rows as $id => $row): ?>
      <li class="views-list-item<?php print $extra_classes ? ' ' . $classes[$id] : ''; ?>"><?php print $row; ?></li>
    <?php endforeach; ?>
  </<?php print $options['type']; ?>>
</div> <!-- /views-view-list -->
