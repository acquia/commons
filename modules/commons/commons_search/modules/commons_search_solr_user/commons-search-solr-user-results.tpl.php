<?php

/**
 * @file
 * Default theme implementation for displaying solr user search results.
 *
 * Available variables:
 * - $results: All results.
 * - $title: The title for the grouping of content.
 *
 *
 * @see template_preprocess_commons_search_solr_user_results()
 *
 * @ingroup themeable
 */
?>

<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <h3<?php print $title_attributes; ?>><?php print $title; ?></h3>
  <div<?php print $content_attributes; ?>>
    <?php print render($content); ?>
  </div>
</div>
