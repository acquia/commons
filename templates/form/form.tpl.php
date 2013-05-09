<?php
/**
 * @file
 * Output a form.
 *
 * @see theme_form()
 * @see commons_origins_preprocess_form()
 * @see commons_origins_process_form()
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

