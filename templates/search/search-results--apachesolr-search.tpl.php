<?php

/**
 * @file
 * Default theme implementation for displaying search results.
 *
 * This template collects each invocation of theme_search_result(). This and
 * the child template are dependent to one another sharing the markup for
 * definition lists.
 *
 * Note that modules may implement their own search type and theme function
 * completely bypassing this template.
 *
 * Available variables:
 * - $search_results: All results as it is rendered through
 *   search-result.tpl.php
 * - $module: The machine-readable name of the module (tab) being searched, such
 *   as "node" or "user".
 *
 *
 * @see template_preprocess_search_results()
 *
 * @ingroup themeable
 */
?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if ($search_results): ?>
    <?php if (!empty($title)): ?>
      <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
    <?php endif; ?>
    <div<?php print $content_attributes; ?>>
      <ol class="search-results <?php print $module; ?>-results">
        <?php print $search_results; ?>
      </ol>
    </div>
    <?php print $pager; ?>
  <?php else : ?>
    <h2<?php print $title_attributes; ?>><?php print t('Your search yielded no results');?></h2>
    <div<?php print $content_attributes; ?>>
      <?php print search_help('search#noresults', drupal_help_arg()); ?>
    </div>
  <?php endif; ?>
</div>
