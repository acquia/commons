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

<?php print drupal_render_children($form); ?>
