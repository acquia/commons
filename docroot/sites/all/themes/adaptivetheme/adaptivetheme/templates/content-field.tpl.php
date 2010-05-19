<?php // $Id: content-field.tpl.php,v 1.1.2.3 2010/03/23 04:53:54 jmburnz Exp $
// adaptivethemes.com

/**
 * @file content-field.tpl.php
 * Default theme implementation to display the value of a field.
 *
 * Available variables:
 * - $node: The node object.
 * - $field: The field array.
 * - $items: An array of values for each item in the field array.
 * - $teaser: Whether this is displayed as a teaser.
 * - $page: Whether this is displayed as a page.
 * - $field_name: The field name.
 * - $field_type: The field type.
 * - $field_name_css: The css-compatible field name.
 * - $field_type_css: The css-compatible field type.
 * - $label: The item label.
 * - $label_display: Position of label display, inline, above, or hidden.
 * - $field_empty: Whether the field has any valid value.
 *
 * Each $item in $items contains:
 * - 'view' - the themed view for that item
 *
 * @see template_preprocess_content_field()
 */
?>
<?php if (!$field_empty): ?>
<?php
  $field_classes = array();
  if (theme_get_setting(cleanup_fields_type)) {
    $field_classes[] = $field_type_css;
  }
  if (theme_get_setting(cleanup_fields_name)) {
    $field_classes[] = $field_name_css;
  }
  $classes = implode(' ', $field_classes);
?>
<div class="field<?php print $classes ? ' '. $classes : ''; ?>">
  <?php if ($label_display == 'above'): ?>
    <h3 class="label"><?php print t($label); ?></h3>
  <?php endif; ?>
    <?php $count = 1;
    foreach ($items as $delta => $item):
      if (!$item['empty']): ?>
        <?php theme_get_setting(cleanup_fields_zebra) ? $zebra = $count % 2 ? 'odd' : 'even' : $zebra = '' ;?>
        <?php if ($label_display == 'inline'): ?>
          <h3 class="label inline"><?php print t($label); ?>:&nbsp;</h3>
          <div class="item inline<?php print $zebra ? ' '. $zebra : ''; ?>"><?php print $item['view']; ?></div>
        <?php else: ?>
          <div class="item<?php print $zebra ? ' '. $zebra : ''; ?>"><?php print $item['view']; ?></div>
        <?php endif; ?>
      <?php $count++;
      endif;
    endforeach; ?>
</div>
<?php endif; ?> <!-- /content-field -->
