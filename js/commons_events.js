(function ($) {
  $.fn.changeElementType = function(newType) {
    var attrs = {};
    if ($(this).length) {
      $.each(this[0].attributes, function(idx, attr) {
        attrs[attr.nodeName] = attr.nodeValue;
      });
    }
    this.replaceWith(function() {
      return $("<" + newType + "/>", attrs).append($(this).contents());
    });
  }
  Drupal.behaviors.commons_events_update_registration_settings_legend = {
    attach: function (context, settings) {
      $("#edit-event-registration-settings .summary").changeElementType("div");
      $("#edit-event-topics .summary").changeElementType("div");
      if ($('#legend-registration-type').length == 0) {
        $('#edit-event-registration-settings .summary').append("<span id='legend-registration-type'></span>");
      }
      if ($('#legend-registration-status').length == 0) {
        $('#edit-event-registration-settings .summary').append("<span id='legend-registration-status'></span>");
      }
      if ($('#legend-event-topics').length == 0) {
        $('#edit-event-topics .summary').append("<span id='legend-event-topics'></span>");
      }
      $(':input[name^="field_topics"]').change(function() {
        if ($(':input[name^="field_topics"]').val() == "") {
          $('#legend-event-topics').text("No topics");
        }
        else {
          $('#legend-event-topics').text($(':input[name^="field_topics"]').val());
        }
      });
      $(':input[name^="field_registration_type"]').change(function() {
        $('#legend-registration-type').text($(':input[name^="field_registration_type"] :selected').text());
        if ($(':input[name^="field_registration_type"]').val() == 'external') {
          $(':input[name^="field_status"]').val('0').change();
        }
      });
      $(':input[name^="field_status"]').change(function() {
        $('#legend-registration-status').text($(':input[name="field_status"] :selected').text());
      });
      $(':input[name^="field_topics"]').change();
      $(':input[name^="field_registration_type"]').change();
      $(':input[name^="field_status"]').change();
    }
  };
})(jQuery);
