<?php // $Id: 2col-33-66.php,v 1.1.2.2 2010/01/02 05:43:09 jmburnz Exp $
// adaptivethemes.com

/**
 * @file 2col-33-66.php
 * Gpanel code snippet to display two regions (33%/66%) as columns.
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
 * Region Variables:
 * 
 * $two_col_33_66_first:  outputs the "2col 33-66 Gpanel col 1" region.
 * $two_col_33_66_second: outputs the "2col 33-66 Gpanel col 2" region.
 */
?>

<!--//   Two column 33-66 Gpanel   //-->
<?php if ($two_col_33_66_first or $two_col_33_66_second): ?>
  <div class="two-col-33-66 gpanel clearfix">
    <div class="section region col-1 first"><div class="inner">
      <?php if ($two_col_33_66_first): print $two_col_33_66_first; endif; ?>
    </div></div>
    <div class="section region col-2 last"><div class="inner">
      <?php if ($two_col_33_66_second): print $two_col_33_66_second; endif; ?>
    </div></div>
  </div>
<?php endif; ?>
<!--/end Gpanel-->



