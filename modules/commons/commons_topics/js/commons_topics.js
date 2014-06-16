(function ($) {

Drupal.behaviors.topicsFieldsetSummaries = {
  attach: function (context) {
    $('fieldset.topics-form-topics', context).drupalSetSummary(function (context) {
      var topics = $('.form-item-field-topics-und input.form-text', context).val();

      if (topics) {
        return Drupal.t('Topics: @topics', { '@topics': topics });
      }
      else {
        return Drupal.t('No topics');
      }
    });
  }
};

})(jQuery);
