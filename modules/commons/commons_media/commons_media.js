(function ($) {

Drupal.behaviors.autoUpload = {
  attach: function (context, settings) {
    $('form', context).delegate('input.form-file', 'change', function() {
      $(this).next('input[type="submit"]').mousedown();
    });
  }
};

})(jQuery);
