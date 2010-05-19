
 /gpanels

  GPanels are drop in multi-column snippets for displaying blocks in 
  vertical columns, such as 2 columns, 3 columns or 4 columns.
 
  How to use a Gpanel:
 
  1. Copy and paste a Gpanel into your page.tpl.php file.
  2. Uncomment the matching regions in your subthemes info file.
  3. Clear the cache (in Performance settings) to refresh the theme registry. 
  
  Now you can add blocks to the Gpanel regions. The layout CSS for 
  these regions is already set up so there is nothing more to do.
  
  Gpanels are built with percentages and expand to fill their containging
  element, normally a div. They will stretch and compress so it does not 
  matter how wide the page is, or what unit you use to set the page width.
  
  
  Gpanels in Page Templates:
  
  You can paste a Gpanel almost anywhere in page.tpl.php and they will 
  display correctly. If you embed a Gpanel into an existing region you
  may have to alter the conditional logic for the Gpanel to show up.
  
  
  Gpanel in Node Templates:
  
  Technically you can paste a Gpanel into node.tpl.php also. To get them 
  to work you will need to make the regions available to the node template. 
  You do this in your subthemes theme_preprocess_node() function.
  
  For example, to enable the regions for the 2col-50-50 Gpanel for 
  the node template, add this to your subthemes theme_node_preprocess()
  function (in your subthemes template.php file).

    function themeName_preprocess_node(&$vars, $hook) {
      $vars['two_col_first'] = theme('blocks', 'two_col_first');
      $vars['two_col_second'] = theme('blocks', 'two_col_second');
    }
  
  - See page-gpanel_examples.tpl.php in the gpanels folder.
    
    
    
    