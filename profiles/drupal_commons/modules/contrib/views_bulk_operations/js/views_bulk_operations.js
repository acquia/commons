(function ($) {
// START jQuery

Drupal.vbo = Drupal.vbo || {};

Drupal.behaviors.vbo = function(context) {
  // Force Firefox to reload the page if Back is hit.
  // https://developer.mozilla.org/en/Using_Firefox_1.5_caching
  window.onunload = function(){}

  // Prepare VBO forms for processing.
  $('form.views-bulk-operations-form', context)
    .not('.views-bulk-operations-form-step-2, .views-bulk-operations-form-step-3')
    .each(Drupal.vbo.prepareAction)
    .each(Drupal.vbo.prepareSelectors);
}

Drupal.vbo.selectionModes = {
  all: 1,
  allPages: 2,
  none: 3
}

Drupal.vbo.prepareSelectors = function() {
  var $form = $(this);
  var form_id = $form.attr('id');

  $('select.views-bulk-operations-selector', $form).change(function() {
    if (this.options[this.selectedIndex].value == Drupal.vbo.selectionModes.all || this.options[this.selectedIndex].value == Drupal.vbo.selectionModes.allPages) {
      var selection = {};
      $('input:checkbox.vbo-select', $form).each(function() {
        this.checked = true;
        $(this).parents('tr:first').addClass('selected');
        selection[this.value] = 1;
      });
      selection['selectall'] = this.options[this.selectedIndex].value == Drupal.vbo.selectionModes.allPages ? 1 : 0;
      $('input#edit-objects-selectall', $form).val(selection['selectall']);

      if (Drupal.settings.vbo[form_id].options.preserve_selection) {
        $.post(Drupal.settings.vbo[form_id].ajax_select, {view_name: Drupal.settings.vbo[form_id].view_name, view_id: Drupal.settings.vbo[form_id].view_id, selection: JSON.stringify(selection)});
      }
    }
    else if (this.options[this.selectedIndex].value == Drupal.vbo.selectionModes.none) {
      $('input:checkbox.vbo-select', $form).each(function() {
        this.checked = false;
        $(this).parents('tr:first').removeClass('selected');
      });
      $('input#edit-objects-selectall', $form).val(0);

      if (Drupal.settings.vbo[form_id].options.preserve_selection) {
        $.post(Drupal.settings.vbo[form_id].ajax_select, {view_name: Drupal.settings.vbo[form_id].view_name, view_id: Drupal.settings.vbo[form_id].view_id, selection: JSON.stringify({'selectall': -1})});
      }
    }
  });

  $('#views-bulk-operations-dropdown select', $form).change(function() {
    if (Drupal.settings.vbo[form_id].options.preserve_selection) {
      $.post(Drupal.settings.vbo[form_id].ajax_select, {view_name: Drupal.settings.vbo[form_id].view_name, view_id: Drupal.settings.vbo[form_id].view_id, selection: JSON.stringify({'operation': this.options[this.selectedIndex].value})});
    }
  });

  $(':checkbox.vbo-select', $form).click(function() {
    var selection = {};
    selection[this.value] = this.checked ? 1 : 0;
    $(this).parents('tr:first')[ this.checked ? 'addClass' : 'removeClass' ]('selected');

    if (Drupal.settings.vbo[form_id].options.preserve_selection) {
      $.post(Drupal.settings.vbo[form_id].ajax_select, {view_name: Drupal.settings.vbo[form_id].view_name, view_id: Drupal.settings.vbo[form_id].view_id, selection: JSON.stringify(selection)});
    }
  }).each(function() {
    $(this).parents('tr:first')[ this.checked ? 'addClass' : 'removeClass' ]('selected');
  });

  // Set up the ability to click anywhere on the row to select it.
  $('tr.rowclick', $form).click(function(event) {
    if (event.target.nodeName.toLowerCase() != 'input' && event.target.nodeName.toLowerCase() != 'a') {
      $(':checkbox.vbo-select', this).each(function() {
        var checked = this.checked;
        // trigger() toggles the checkmark *after* the event is set,
        // whereas manually clicking the checkbox toggles it *beforehand*.
        // that's why we manually set the checkmark first, then trigger the
        // event (so that listeners get notified), then re-set the checkmark
        // which the trigger will have toggled. yuck!
        this.checked = !checked;
        $(this).trigger('click');
        this.checked = !checked;
      });
    }
  });
}

Drupal.vbo.prepareAction = function() {
  // Skip if no view is Ajax-enabled.
  if (typeof(Drupal.settings.views) == "undefined" || typeof(Drupal.settings.views.ajaxViews) == "undefined") return;

  var $form = $(this);
  $.each(Drupal.settings.views.ajaxViews, function(i, view) {
    if (view.view_name == Drupal.settings.vbo[$form.attr('id')].view_name) {
      var action = $form.attr('action');
      var params = {};
      var query = action.replace(/.*?\?/, '').split('&');
      var cleanUrl = true, replaceAction = false;
      $.each(query, function(i, str) {
        var element = str.split('=');
        if (element[0] == 'view_path') {
          action = decodeURIComponent(element[1]);
          replaceAction = true;
        }
        else if (element[0] == 'q') {
          cleanUrl = false;
        }
        else if (typeof(view[element[0]]) == 'undefined' && typeof(element[1]) != 'undefined') {
          params[element[0]] = element[1];
        }
      });
      if (replaceAction) {
        params = $.param(params);
        if (cleanUrl) {
          action = Drupal.settings.basePath + action;
        }
        else {
          params = 'q=' + action + (params.length > 0 ? '&' + params : '');
          action = Drupal.settings.basePath;
        }
        $form.attr('action', action + (params.length > 0 ? '?' + params : ''));
      }
    }
  });
}

Drupal.vbo.ajaxViewResponse = function(target, response) {
  $.each(Drupal.settings.vbo, function(form_dom_id, settings) {
    if (settings.form_id == response.vbo.form_id) {
      Drupal.settings.vbo[form_dom_id].view_id = response.vbo.view_id;
    }
  });
}

// END jQuery
})(jQuery);
