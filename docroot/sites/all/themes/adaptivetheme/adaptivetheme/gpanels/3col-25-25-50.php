<?php // $Id: 3col-25-25-50.php,v 1.1.2.2 2010/01/02 05:43:09 jmburnz Exp $
// adaptivethemes.com

/**
 * @file 3col-25-25-50.php
 * Gpanel code snippet to display three regions (25%, 25%, 50%) as columns.
 *
 * GPanels are drop in multi-column snippets for displaying blocks in 
 * vertical columns, such as 2 columns, 3 columns or 4 columns.
 *
 * How to use a Gpanel:
 * 1. Copy and paste a Gpanel into your page.tpl.php file.
 * 2. Uncomment the matching regions in your subthemes info file.
 * 3. Clear the cache (in Performance settings) to refresh the theme registry. 
 *
 * Now you can add blocks to the regions as per normal. The layout CSS for 
 * these regions is already set up so there is nothing more to do.
 * 
 * Gpanels are fluid, meaning they stretch and compress with the page width.
 *
 * Region variables:
 * $three_col_25_25_50_first:  outputs the "3col 25-25-50 Gpanel col 1" region.
 * $three_col_25_25_50_second: outputs the "3col 25-25-50 Gpanel col 2" region.
 * $three_col_25_25_50_third:  outputs the "3col 25-25-50 Gpanel col 3" region.
 */
?>

<!--//   Three column 25-25-50 Gpanel   //-->
<?php if ($three_col_25_25_50_first or $three_col_25_25_50_second or $three_col_25_25_50_third): ?>
  <div class="three-col-25-25-50 gpanel clearfix">
    <div class="section region col-1 first"><div class="inner">
      <?php if ($three_col_25_25_50_first): print $three_col_25_25_50_first; endif; ?>
    </div></div>
    <div class="section region col-2"><div class="inner">
      <?php if ($three_col_25_25_50_second): print $three_col_25_25_50_second; endif; ?>
    </div></div>
    <div class="section region col-3 last"><div class="inner">
      <?php if ($three_col_25_25_50_third): print $three_col_25_25_50_third; endif; ?>
    </div></div>
  </div>
<?php endif; ?>
<!--/end Gpanel-->





