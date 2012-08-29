(function ($) {
  Drupal.behaviors.commons_events_update_registration_settings_legend = {
    attach: function (context, settings) {
      if ($('#legend-registration-type').length == 0) {
        $('#edit-event-registration-settings .summary').append("<span id='legend-registration-type'></span>");
      }
      if ($('#legend-registration-status').length == 0) {
        $('#edit-event-registration-settings .summary').append("<span id='legend-registration-status'></span>");
      }
      if ($('#legend-event-topics').length == 0) {
        $('#edit-event-topics .summary').append("<span id='legend-event-topics'></span>");
      }
      $('#legend-event-topics').text($(':input[name^="field_topics"]').val());
      $('#legend-registration-type').text($(':input[name^="field_registration_type"] :selected').text());
      $('#legend-registration-status').text($(':input[name="field_status"] :selected').text());
    }
  };
})(jQuery);