(function ($) {

/**
 * Initially hide the group selection and make it visible when the custom
 * audience radio is selected.
 */
Drupal.behaviors.commonsAudienceToggle = {
  attach: function (context, settings) {
    $('.commons-bw-partial-node-form, .node-form', context).once('commonsAudienceToggle', function(){
      // Load items into simple variables to make things a bit easier to read.
      var form = $(this),
          groupReference = form.find('.field-name-og-group-ref'),
          radioToggle = form.find('input[name=group_audience_type]');

      // Hide the group selection on load only if custom is not selected.
      if ($('input:radio[name=group_audience_type]:checked').val() != 'custom') {
        groupReference.addClass('element-hidden');
      }

      // When the "custom" audience radio is selected, make the group selection
      // visible.
      radioToggle.change(function () {
        var radio = $(this),
            radioValue = radio.val();

        if (radioValue == 'custom' && radio.is(':checked')) {
          groupReference.removeClass('element-hidden');
        }
        else {
          groupReference.addClass('element-hidden');
        }
      });
    });
  }
}

})(jQuery);
