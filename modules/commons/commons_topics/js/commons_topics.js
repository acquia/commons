(function ($) {
  Drupal.behaviors.commons_topics_update_legend = {
    attach: function (context, settings) {
      $(':input[name^="field_topics"]').change(function() {
        if ($(':input[name^="field_topics"]').val() == "") {
          $("[id^='edit-topics-wrapper'] .summary").text(Drupal.t("No topics"));
        }
        else {
          $("[id^='edit-topics-wrapper'] .summary").text($(':input[name^="field_topics"]').val());
        }
      });
      $(':input[name^="field_topics"]').change();
    }
  };
})(jQuery);
