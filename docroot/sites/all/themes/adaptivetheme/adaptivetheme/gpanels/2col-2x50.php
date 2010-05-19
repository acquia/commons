<?php // $Id: 2col-2x50.php,v 1.1.2.2 2010/01/02 05:43:09 jmburnz Exp $
// adaptivethemes.com

/**
 * @file 2col-2x50.php
 * Gpanel code snippet to display two 50% width regions as columns.
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
 *
 * Region Variables:
 * 
 * Standard Two column Gpanel 
 * $two_col_2x50_first:  outputs the "2col 2x50 Gpanel col 1" region.
 * $two_col_2x50_second: outputs the "2col 2x50 Gpanel col 2" region.
 */
?>

<!--//   Two column Gpanel 2x50   //-->
<?php if ($two_col_2x50_first or $two_col_2x50_second): ?>
  <div class="two-col-2x50 gpanel clearfix">
    <div class="section region col-1 first"><div class="inner">
      <?php if ($two_col_2x50_first): print $two_col_2x50_first; endif; ?>
    </div></div>
    <div class="section region col-2 last"><div class="inner">
      <?php if ($two_col_2x50_second): print $two_col_2x50_second; endif; ?>
    </div></div>
  </div>
<?php endif; ?>
<!--/end Gpanel-->



