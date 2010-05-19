<?php // $Id: views-view-unformatted.tpl.php,v 1.1.2.5 2010/03/14 01:59:18 jmburnz Exp $
// adaptivethemes.com

/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php
// Conditionally add extra classes.
if (theme_get_setting(cleanup_views_unformatted)) {
  $extra_classes = TRUE;
}
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>
  <div class="views-row-unformatted<?php print $extra_classes ? ' ' . $classes[$id] : ''; ?>">
    <?php print $row; ?>
  </div>
<?php endforeach; ?> <!-- /views-view-unformatted -->
