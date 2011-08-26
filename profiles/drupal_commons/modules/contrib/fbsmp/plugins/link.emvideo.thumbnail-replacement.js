
/**
 *  @file
 *  This will use jQuery AJAX to replace a thumbnail with its video version.
 *  Mostly from the emvideo module.
 */
Drupal.behaviors.fbsmpLinkEmvideoThumbnailReplacement = function(context) {
  
  //Process the tags to 
  //1) place the span tag for the play icon.
  //2) replace it with video on click.
  $('a.fbsmp-link-emvideo-thumbnail-replacement:not(.fbsmp-link-emvideo-thumbnail-replacement-processed)', context).addClass('fbsmp-link-emvideo-thumbnail-replacement-processed').each(function() {
    
    $(this).children('.fbsmp-link-thumbnail').after('<span></span>');
    
    // When clicking the image, load the video with AJAX.
    $(this).click(function() {
      // 'this' won't point to the element when it's inside the ajax closures,
      // so we reference it using a variable.
      var element = this;
      $.ajax({
        url: element.href,
        dataType: 'html',
        success: function (data) {
          if (data) {
            // Success.
            $(element).parent().html(data);
          }
          else {
            // Failure.
            alert('An unknown error occurred.\n'+ element.href);
          }
        },
        error: function (xmlhttp) {
          alert('An HTTP error '+ xmlhttp.status +' occurred.\n'+ element.href);
        }
      });
      return false;
    });
  });
};
