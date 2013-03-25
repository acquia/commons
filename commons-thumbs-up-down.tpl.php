<?php
/**
 * @file
 * Rate widget theme
 */
?>

<div class="commons-q-a-rate-up-down clearfix">
  <?php
  print '<div class="rate-info"><span class="rate-info-value">' . $results['rating'] . '</span> <span class="rate-info-label">' . format_plural($results['rating'], 'point', 'points') . '</span></div>';

  if ($display_options['description']) {
    print '<div class="rate-description">' . $display_options['description'] . '</div>';
  }
  ?>

  <div class="commons-q-a-rate-buttons">
    <div class="commons-q-a-rate-trigger commons-q-a-rate-up">
      <?php print $up_button; ?>
    </div>
    <div class="commons-q-a-rate-trigger commons-q-a-rate-down">
      <?php print $down_button; ?>
    </div>
  </div>
</div>
