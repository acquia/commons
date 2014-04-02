(function ($) {

Drupal.behaviors.autoEmbed = {
  attach: function (context, settings) {
    // Automatically click the submit button to embed the file.
    $('.button.fake-ok').click();
  }
};

})(jQuery);
