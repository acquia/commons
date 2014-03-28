(function ($) {

Drupal.behaviors.autoUpload = {
  attach: function (context, settings) {
    // Loop through all of the managed file form elements on the page.
    $('.form-managed-file').each(function(index, element) {
      // Hide/show the file upload/remove button if a file is not present.
      if ($(this).children('span.file').length == 0 ) {
        $(this).children('input.form-submit').hide();
      };

      // Automatically upload the file if a file is selected.
      $(this).delegate('input.form-file', 'change', function() {
        $(this).siblings('input.form-submit').mousedown();
      });
    });
  }
};

})(jQuery);
