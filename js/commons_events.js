(function ($) {
  Drupal.behaviors.commons_events_update_registration_settings_legend = {
    attach: function (context, settings) {
      $(':input[name^="field_registration_type"]').change(function() {
        $("[id^='edit-event-registration-settings'] .summary").text($(':input[name^="field_registration_type"] :selected').text());
        if ($(':input[name^="field_registration_type"]').val() == 'external') {
          $(':input[name^="field_status"]').val('0').change();
        }
      });
      $(':input[name^="field_status"]').change(function() {
        var cur = $(':input[name^="field_registration_type"] :selected').text();
        $("[id^='edit-event-registration-settings'] .summary").text(cur + ', ' + $(':input[name="field_status"] :selected').text());
      });
      $(':input[name^="field_registration_type"]').change();
      $(':input[name^="field_status"]').change();
    }
  };
})(jQuery);
