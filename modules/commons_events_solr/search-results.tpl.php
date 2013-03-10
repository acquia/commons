<?php

/**
 * @file
 * Overrides modules/search/search-results.tpl.php.
 *
 * Variables provided by the Rich Snippets module:
 * - $sponsored_links: Sponsored results displayed at the top of the page.
 *
 * Available variables:
 * - $search_results: All results as rendered through search-result.tpl.php.
 * - $module: The machine-readable name of the module (tab) being searched, such
 *   as "node" or "user".
 *
 * @see template_preprocess_search_results()
 */
?>
<?php if (!empty($sponsored_links)): ?>
  <?php print $sponsored_links; ?>
<?php endif; ?>
<?php if ($search_results): ?>
  <div class="search-results-wrapper">
    <h2><?php print (isset($search_title) ? $search_title : t('Search results')); ?></h2>
    <ol class="search-results <?php print $module; ?>-results">
      <?php print $search_results; ?>
    </ol>
  </div>
  <?php print $pager; ?>
<?php else : ?>
  <h2><?php print t('Your search yielded no results');?></h2>
  <?php print search_help('search#noresults', drupal_help_arg()); ?>
<?php endif; ?>
