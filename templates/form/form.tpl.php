<?php
/**
 * @file
 * Output a form.
 *
 * This is an override of Drupal's default theme_form() to make theme
 * hook suggestions and theming easier.
 *
 * @see theme_form()
 * @see pure_suggestions_form()
 * @see pure_preprocess_form()
 * @see pure_process_form()
 */
?>
<form<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>
    <?php
      // Due to the way the Drupal renders forms, we cannot control individual
      // form elements in this template. If you would like to have more granular
      // control of the form elements, use form-content.tpl.php or variant.
    ?>
    <?php print $element['#children']; ?>
  </div>
</form>

