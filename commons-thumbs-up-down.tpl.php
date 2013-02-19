<?php
/**
 * @file
 * Rate widget theme
 */
?>

<ul>
  <li class="thumb-up">
    <?php print $up_button; ?>
  </li>
  <li class="thumb-down">
    <?php print $down_button; ?>
  </li>
</ul>
<?php

if ($info) {
  print '<div class="rate-info"><span class="rate-info-value">' . $score . '</span> <span class="rate-info-label">' . format_plural($score, t('point'), t('points')) . '</span></div>';
}

if ($display_options['description']) {
  print '<div class="rate-description">' . $display_options['description'] . '</div>';
}
