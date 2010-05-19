
  /js
  
  The js directory contains the core themes jQuery scripts and plugins.
  
  You can enable and disable each script via the genesis.info file.
  
  If you need to control these per subtheme, you can copy and paste the script
  to your subtheme, disable it in genesis.info and then call it directly from 
  your subthemes info file.
  
  The included scripts are:
  
  aria-roles.js
    This adds WAI ARIA landmark roles to specific regions, blocks and other elements.
    Its uses the jQuery attr function to insert the attribute of "role" and an associated
    role, such as "nav", "header" or complimentary.
    
    WAI ARIA roles are an accessibility feature for screen readers.
    http://www.w3.org/TR/wai-aria/
    
  jquery.equalizeheights.js
    A simple jQuery plugin that gives equal height columns. The script only works
    for sidebar left and right, and the content column. You only need to enable this
    and it will work. The caveat is that its quite simple and cannot dynamcially
    resize the sidebars. For example if the browser window is resized, or the draggable
    grippie on text areas is adjusted the columns will not adjust to compensate the changes.
    
    To enable this script see genesis.info.
    
  jquery.equalizeheights.minified.js
    A minified version of jquery.equalizeheights.js (not human readable) and is
    the file Genesis is configured to use by default.
    
  
  preloadCssImages.jQuery_v5.js
    A jQuery plugin that automatically preloads all images referenced in CSS files.
    http://www.filamentgroup.com/lab/update_automatically_preload_images_from_css_with_jquery/
  
  preloadCssImages.jQuery_v5_minfied.js
    A minified version of preloadCssImages.jQuery_v5.js (not human readable) and is
    the file Genesis is configured to use by default.
  
  theme-settings.js
    Show and hide theme settings based on selection.
    
    
  