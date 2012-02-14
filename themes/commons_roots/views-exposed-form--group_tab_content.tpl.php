<?php
// $Id: views-exposed-form.tpl.php,v 1.4.4.1 2009/11/18 20:37:58 merlinofchaos Exp $
/**
 * @file views-exposed-form.tpl.php
 *
 * This template handles the layout of the views exposed filter form.
 *
 * Variables available:
 * - $widgets: An array of exposed form widgets. Each widget contains:
 * - $widget->label: The visible label to print. May be optional.
 * - $widget->operator: The operator for the widget. May be optional.
 * - $widget->widget: The widget itself.
 * - $button: The submit button for the form.
 *
 * @ingroup views_templates
 */
?>
<?php 
// Add collapsible fieldset js if it is not already included
drupal_add_js('misc/drupal.js');
drupal_add_js('misc/collapse.js');
?>

<?php if (!empty($q)): ?>
  <?php
    // This ensures that, if clean URLs are off, the 'q' is added first so that
    // it shows up first in the URL.
    print $q;
  ?>
<?php endif; ?>
<fieldset id="views-exposed-form-group-search" class="views-exposed-form">
  <div class="views-exposed-wrapper clear-block">
  <div class="views-exposed-widgets-group-search clear-block">
    <?php foreach($widgets as $id => $widget): ?>
      <div class="views-exposed-widget-group-search views-widget-group-search-<?php print $id; ?>">
        <?php if (!empty($widget->label)): ?>
          <label for="<?php print $widget->id; ?>">
            <?php print $widget->label;?>
          </label>
        <?php endif; ?>
        <?php if (!empty($widget->operator)): ?>
          <div class="views-operator">
            <?php print $widget->operator; ?>
          </div>
        <?php endif; ?>
        <div class="views-widget">
          <?php print $widget->widget; ?>
        </div>
      </div>
    <?php endforeach; ?>
    </div>
    <div class="views-exposed-widget views-exposed-submit">
      <?php print $button ?>
    </div>
  </div>
</fieldset>