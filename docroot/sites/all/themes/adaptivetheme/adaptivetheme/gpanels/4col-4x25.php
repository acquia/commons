<?php // $Id: 4col-4x25.php,v 1.1.2.2 2010/01/02 05:43:09 jmburnz Exp $
// adaptivethemes.com

/**
 * @file 4col-4x25.php
 * Gpanel code snippet to display 4x25% width regions as columns.
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
 * $four_col_first:  outputs the "4col Gpanel col 1" region.
 * $four_col_second: outputs the "4col Gpanel col 2" region.
 * $four_col_third:  outputs the "4col Gpanel col 3" region.
 * $four_col_third:  outputs the "4col Gpanel col 4" region.
 */
?>

<!--//   Four column Gpanel   //-->
<?php if ($four_col_first or $four_col_second or $four_col_third or $four_col_fourth): ?>
  <div class="four-col-4x25 gpanel clearfix">
    <div class="section region col-1 first"><div class="inner">
      <?php if ($four_col_first): print $four_col_first; endif; ?>
    </div></div>
    <div class="section region col-2"><div class="inner">
      <?php if ($four_col_second): print $four_col_second; endif; ?>
    </div></div>
    <div class="section region col-3"><div class="inner">
      <?php if ($four_col_third): print $four_col_third; endif; ?>
    </div></div>
    <div class="section region col-4 last"><div class="inner">
      <?php if ($four_col_fourth): print $four_col_fourth; endif; ?>
    </div></div>
  </div>
<?php endif; ?>
<!--/end Gpanel-->







