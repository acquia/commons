// $Id: screenshot.js,v 1.1.2.2 2010/02/14 06:44:15 sociotech Exp $
/*
 * Screenshot preview script 
 * (based on "Easiest Tooltip" script by Alen Grakalic: http://cssglobe.com)
 *
 */

this.screenshotPreview = function(){
  // configure distance of preview from the cursor
  var xOffset = 20;
  var yOffset = 0;

  $('span.preview-icon').hover(function(e){
    var img_class = this.id;
    var caption = $(this).parent().text();
    // add preview markup
    $('body').append('<div id="screenshot">' +
                     '<div class="screenshot-preview ' + img_class + '" alt="preview"></div>' + 
                     '<div class="screenshot-caption">' + caption + '</div>' +
                     '</div>');
    $("#screenshot").hide();  // hide preview until dimensions are set
    $("#screenshot").css("left", (e.pageX + xOffset) + "px").css("top", (e.pageY + yOffset) + "px");  // set initial preview position
    // load image in order to set preview dimensions
    var img = new Image();
    img.onload = function() {
      var caption_height = parseFloat($("#screenshot .screenshot-caption").css("height"));
      $("#screenshot").css("height", img.height + caption_height);
      $("#screenshot").css("width", img.width);
      $("#screenshot ." + img_class).css("height", img.height);
      $("#screenshot ." + img_class).css("width", img.width);
      $("#screenshot .screenshot-caption").css("width", img.width - 10);
      $("#screenshot").fadeIn("fast");  // now show preview
    }
    img.src = $("." + img_class).css("background-image").replace(/^url|[\(\)\"]/g, '');
  },
  function(){
    $("#screenshot").remove();
  });
  // adjust preview position with cursor movement
  $("span.preview-icon").mousemove(function(e){
    $("#screenshot").css("left", (e.pageX + xOffset) + "px").css("top", (e.pageY + yOffset) + "px");
  });
};

// start the script on page load
$(document).ready(function(){
  if ($('span.preview-icon').size() > 0) {
    screenshotPreview();
  }
});
