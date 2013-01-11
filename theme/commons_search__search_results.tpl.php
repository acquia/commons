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
 * - $type: The type of search, e.g., "node" or "user".
 *
 *
 * @see template_preprocess_custom_search_results()
 */
?>
<?php if ($search_results) : ?>
  <h2><?php print $search_title;?></h2>
  <?php if (isset($filter) && $filter != '' && $filter_position == 'above') { ?>
    <div class="custom-search-filter">
      <?php print $filter; ?>
    </div>
  <?php } ?>
  <ol class="search-results <?php print $module; ?>-results">
    <?php print $search_results; ?>
  </ol>
  <?php if (isset($filter) && $filter != '' && $filter_position == 'below') { ?>
    <div class="custom-search-filter">
      <?php print $filter; ?>
    </div>
  <?php } ?>
  <?php print $pager; ?>
<?php else : ?>
  <h2><?php print t('Your search yielded no results');?></h2>
  <?php print search_help('search#noresults', drupal_help_arg()); ?>
<?php endif; ?>
