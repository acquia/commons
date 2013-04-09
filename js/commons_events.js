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
      $(':input[name^="field_topics"]').change(function() {
        if ($(':input[name^="field_topics"]').val() == "") {
          $("[id^='edit-event-topics'] .summary").text("No topics");
        }
        else {
          $("[id^='edit-event-topics'] .summary").text($(':input[name^="field_topics"]').val());
        }
      });
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
      $(':input[name^="field_topics"]').change();
      $(':input[name^="field_registration_type"]').change();
      $(':input[name^="field_status"]').change();
    }
  };
})(jQuery);
