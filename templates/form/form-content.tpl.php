<?php
/**
 * @file form-content.tpl.php
 * Default template implementation to display the content of a form.
 *
 * Available variables:
 * - $form: An array of form elements. Use render() to output individual
 *   elements, but drupal_render_children() to render the whole item.
 */
?>

<?php
  // Some nodes are multicolumn, so check for the second column. 
  if (!empty($form['supplementary'])):
?>
  <?php 
    hide($form['supplementary']); 
    hide($form['actions']);
  ?>
  <div class="columns clearfix">
    <div class="primary-fields">
      <?php print drupal_render_children($form); ?>
    </div>
    <div class="supplementary-fields">
      <?php print render($form['supplementary']); ?>
    </div>
  </div>
  <?php print render($form['actions']); ?>
<?php 
  // If there is no second column, print everything as normal.
  else:
?>
  <?php print drupal_render_children($form); ?>
<?php endif; ?>

