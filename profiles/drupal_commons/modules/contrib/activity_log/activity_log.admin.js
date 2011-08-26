Drupal.behaviors.activityLogAdmin = function (context) {
  // Make sure we can run context.find().
  var ctxt = $(context);

  // Control toggling visibility of the acting UID field.
  var acting_uid = new Array();
  acting_uid['group_method'] = false;
  acting_uid['stream_owner'] = false;
  acting_uid['viewer']       = false;
  var toggle_acting_uid = function() {
    for (var key in acting_uid) {
      if (acting_uid[key]) {
        ctxt.find('#edit-settings-acting-uid-wrapper').show();
        return;
      }
    }
    ctxt.find('#edit-settings-acting-uid-wrapper').hide();
  }

  // Show/hide grouping settings.
  var handle_gm = function() {
    var val = ctxt.find('input:radio[name="settings[grouping][group_method]"]:checked').val();
    if (val == 'target_action') {
      ctxt.find('#edit-settings-grouping-group-interval-wrapper').hide();
      ctxt.find('#edit-settings-grouping-group-max-wrapper').hide();
      ctxt.find('#edit-settings-grouping-group-summary-wrapper').hide();
      ctxt.find('#edit-settings-grouping-collapse-method-wrapper').hide();
      ctxt.find('#edit-settings-grouping-templates-fieldset').show();
      ctxt.find('.activity-log-admin-description').hide();
    }
    else if (val == 'action' || val == 'user_action') {
      ctxt.find('#edit-settings-grouping-group-interval-wrapper').show();
      ctxt.find('#edit-settings-grouping-group-max-wrapper').show();
      ctxt.find('#edit-settings-grouping-group-summary-wrapper').show();
      ctxt.find('#edit-settings-grouping-collapse-method-wrapper').show();
      ctxt.find('#edit-settings-grouping-templates-fieldset').show();
      ctxt.find('.activity-log-admin-description').show();
    }
    else if (val == 'none') {
      ctxt.find('#edit-settings-grouping-group-interval-wrapper').hide();
      ctxt.find('#edit-settings-grouping-group-max-wrapper').hide();
      ctxt.find('#edit-settings-grouping-group-summary-wrapper').hide();
      ctxt.find('#edit-settings-grouping-collapse-method-wrapper').hide();
      ctxt.find('#edit-settings-grouping-templates-fieldset').hide();
    }
    acting_uid['group_method'] = (val == 'user_action');
    toggle_acting_uid();
  };
  handle_gm();
  ctxt.find('input:radio[name="settings[grouping][group_method]"]').change(handle_gm);

  // Show/hide stream owner exposed fields.
  var so_fields = Drupal.settings.activity_log.stream_owner_expose_fields;
  var handle_so = function() {
    var shown = new Array();
    $.each(so_fields, function(k, v) {
      for (var val in v) {
        if (ctxt.find('input:checkbox[name="settings[visibility][stream_owner_entity_group]['+ k +']"]').attr('checked')) {
          if ($.inArray(v[val], shown) == -1) {
            var type = 'acting-uid';
            if (v[val] == 'id') {
              type = 'visibility-stream-owner-id';
            }
            else if (v[val] == 'type') {
              type = 'visibility-stream-owner-type';
            }
            ctxt.find('#edit-settings-'+ type +'-wrapper').show();
            shown[v[val]] = v[val];
            if (type == 'acting-uid') {
              acting_uid['stream_owner'] = true;
              toggle_acting_uid();
            }
          }
        }
      }
    });
    var f = ['id', 'type', 'acting_uid'];
    for (var val in f) {
      if (shown[f[val]] == undefined || shown[f[val]] == null) {
        var type = 'acting-uid';
        if (f[val] == 'id') {
          type = 'visibility-stream-owner-id';
        }
        else if (f[val] == 'type') {
          type = 'visibility-stream-owner-type';
        }
        if (f[val] != 'acting_uid') {
          ctxt.find('#edit-settings-'+ type +'-wrapper').hide();
        }
        else {
          acting_uid['stream_owner'] = false;
          toggle_acting_uid();
        }
      }
    }
  };
  handle_so();
  $.each(so_fields, function(key, value) {
    ctxt.find('input:checkbox[name="settings[visibility][stream_owner_entity_group]['+ key +']"]').change(handle_so);
  });

  // Show/hide viewer exposed fields.
  var vi_fields = Drupal.settings.activity_log.viewer_expose_fields;
  var handle_vi = function() {
    var shown = new Array();
    $.each(vi_fields, function(k, v) {
      for (var val in v) {
        if (ctxt.find('input:checkbox[name="settings[visibility][viewer_entity_group]['+ k +']"]').attr('checked')) {
          if ($.inArray(v[val], shown) == -1) {
            var type = 'acting-uid';
            if (v[val] == 'id') {
              type = 'visibility-viewer-id';
            }
            ctxt.find('#edit-settings-'+ type +'-wrapper').show();
            shown[v[val]] = v[val];
            if (type == 'acting-uid') {
              acting_uid['viewer'] = true;
              toggle_acting_uid();
            }
          }
        }
      }
    });
    var f = ['id', 'acting_uid'];
    for (var val in f) {
      if (shown[f[val]] == undefined || shown[f[val]] == null) {
        var type = 'acting-uid';
        if (f[val] == 'id') {
          type = 'visibility-viewer-id';
        }
        if (f[val] != 'acting_uid') {
          ctxt.find('#edit-settings-'+ type +'-wrapper').hide();
        }
        else {
          acting_uid['viewer'] = false;
          toggle_acting_uid();
        }
      }
    }
  };
  handle_vi();
  $.each(vi_fields, function(key, value) {
    ctxt.find('input:checkbox[name="settings[visibility][viewer_entity_group]['+ key +']"]').change(handle_vi);
  });
}
