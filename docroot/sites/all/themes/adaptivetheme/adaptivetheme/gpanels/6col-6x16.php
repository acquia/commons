<?php // $Id: 6col-6x16.php,v 1.1.2.2 2010/01/02 05:43:09 jmburnz Exp $
// adaptivethemes.com

/**
 * @file 6col-6x16.php
 * Gpanel code snippet to display 6x16% width regions as columns.
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
 * regions[six_col_first]    = 6col Gpanel col 1
 * regions[six_col_second]   = 6col Gpanel col 2
 * regions[six_col_third]    = 6col Gpanel col 3
 * regions[six_col_fourth]   = 6col Gpanel col 4
 * regions[six_col_fifth]    = 6col Gpanel col 5
 * regions[six_col_sixth]    = 6col Gpanel col 6
 */
?>

<!--//   Six column Gpanel   //-->
<?php if ($six_col_first or $six_col_second or $six_col_third or $six_col_fourth or $six_col_fifth or $six_col_sixth): ?>
  <div class="six-col-6x16 gpanel clearfix">
    <div class="section region col-1 first"><div class="inner">
      <?php if ($six_col_first): print $six_col_first; endif; ?>
    </div></div>
    <div class="section region col-2"><div class="inner">
      <?php if ($six_col_second): print $six_col_second; endif; ?>
    </div></div>
    <div class="section region col-3"><div class="inner">
      <?php if ($six_col_third): print $six_col_third; endif; ?>
    </div></div>
    <div class="section region col-4"><div class="inner">
      <?php if ($six_col_fourth): print $six_col_fourth; endif; ?>
    </div></div>
    <div class="section region col-5 last"><div class="inner">
      <?php if ($six_col_fifth): print $six_col_fifth; endif; ?>
    </div></div>
    <div class="section region col-6 last"><div class="inner">
      <?php if ($six_col_sixth): print $six_col_sixth; endif; ?>
    </div></div>
  </div>
<?php endif; ?>
<!--/end Gpanel-->




