(function ($) {

Drupal.behaviors.radioactivityFieldsetSummaries = {
  attach: function (context) {
    $('fieldset.radioactivity-form-energy', context).drupalSetSummary(function (context) {
      var energy = $('.form-item-field-radioactivity-und-0-radioactivity-energy input', context).val();

      if (energy) {
        return Drupal.t('Energy: @energy', { '@energy': energy });
      }
      else {
        return Drupal.t('Not radioactive');
      }
    });
  }
};

})(jQuery);
