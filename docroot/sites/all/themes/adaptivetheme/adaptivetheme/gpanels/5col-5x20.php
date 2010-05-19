<?php // $Id: 5col-5x20.php,v 1.1.2.2 2010/01/02 05:43:09 jmburnz Exp $
// adaptivethemes.com

/**
 * @file 5col-5x20.php
 * Gpanel code snippet to display 5x20% width regions as columns.
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
 * regions[five_col_first]   = 5col Gpanel col 1
 * regions[five_col_second]  = 5col Gpanel col 2
 * regions[five_col_third]   = 5col Gpanel col 3
 * regions[five_col_fourth]  = 5col Gpanel col 4
 * regions[five_col_fifth]   = 5col Gpanel col 5
 */
?>

<!--//   Five column Gpanel   //-->
<?php if ($five_col_first or $five_col_second or $five_col_third or $five_col_fourth or $five_col_fifth): ?>
  <div class="five-col-5x20 gpanel clearfix">
    <div class="section region col-1 first"><div class="inner">
      <?php if ($five_col_first): print $five_col_first; endif; ?>
    </div></div>
    <div class="section region col-2"><div class="inner">
      <?php if ($five_col_second): print $five_col_second; endif; ?>
    </div></div>
    <div class="section region col-3"><div class="inner">
      <?php if ($five_col_third): print $five_col_third; endif; ?>
    </div></div>
    <div class="section region col-4"><div class="inner">
      <?php if ($five_col_fourth): print $five_col_fourth; endif; ?>
    </div></div>
    <div class="section region col-5 last"><div class="inner">
      <?php if ($five_col_fifth): print $five_col_fifth; endif; ?>
    </div></div> 
  </div>
<?php endif; ?>
<!--/end Gpanel-->



