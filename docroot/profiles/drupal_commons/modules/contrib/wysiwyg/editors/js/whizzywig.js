// $Id: whizzywig.js,v 1.4.2.1 2010/02/13 23:58:41 sun Exp $

var wysiwygWhizzywig = { currentField: null, fields: {} };
var buttonPath = null;

/**
 * Override Whizzywig's document.write() function.
 *
 * Whizzywig uses document.write() by default, which leads to a blank page when
 * invoked in jQuery.ready().  Luckily, Whizzywig developers implemented a
 * shorthand w() substitute function that we can override to redirect the output
 * into the global wysiwygWhizzywig variable.
 *
 * @see o()
 */
var w = function (string) {
  if (string) {
    wysiwygWhizzywig.fields[wysiwygWhizzywig.currentField] += string;
  }
  return wysiwygWhizzywig.fields[wysiwygWhizzywig.currentField];
};

/**
 * Override Whizzywig's document.getElementById() function.
 *
 * Since we redirect the output of w() into a temporary string upon attaching
 * an editor, we also have to override the o() shorthand substitute function
 * for document.getElementById() to search in the document or our container.
 * This override function also inserts the editor instance when Whizzywig
 * tries to access its IFRAME, so it has access to the full/regular window
 * object.
 *
 * @see w()
 */
var o = function (id) {
  // Upon first access to "whizzy" + id, Whizzywig tries to access its IFRAME,
  // so we need to insert the editor into the DOM.
  if (id == 'whizzy' + wysiwygWhizzywig.currentField && wysiwygWhizzywig.fields[wysiwygWhizzywig.currentField]) {
    jQuery('#' + wysiwygWhizzywig.currentField).after('<div id="' + wysiwygWhizzywig.currentField + '-whizzywig">' + w() + '</div>');
    // Prevent subsequent invocations from inserting the editor multiple times.
    wysiwygWhizzywig.fields[wysiwygWhizzywig.currentField] = '';
  }
  // If id exists in the regular window.document, return it.
  if (jQuery('#' + id).size()) {
    return jQuery('#' + id).get(0);
  }
  // Otherwise return id from our container.
  return jQuery('#' + id, w()).get(0);
};

(function($) {

/**
 * Attach this editor to a target element.
 */
Drupal.wysiwyg.editor.attach.whizzywig = function(context, params, settings) {
  // Assign button images path, if available.
  if (settings.buttonPath) {
    window.buttonPath = settings.buttonPath;
  }
  // Create Whizzywig container.
  wysiwygWhizzywig.currentField = params.field;
  wysiwygWhizzywig.fields[wysiwygWhizzywig.currentField] = '';
  // Attach editor.
  makeWhizzyWig(params.field, (settings.buttons ? settings.buttons : 'all'));
  // Whizzywig fails to detect and set initial textarea contents.
  var instance = $('#whizzy' + params.field).get(0);
  if (instance) {
    instance.contentWindow.document.body.innerHTML = $('#' + params.field).val();
  }
};

/**
 * Detach a single or all editors.
 */
Drupal.wysiwyg.editor.detach.whizzywig = function(context, params) {
  var detach = function (id) {
    var instance = $('#whizzy' + whizzies[id]).get(0);
    if (!instance) {
      return;
    }
    var body = instance.contentWindow.document.body;
    var $field = $('#' + whizzies[id]);
    body.innerHTML = tidyH(body.innerHTML);

    // Save contents of editor back into textarea.
    $field.val(window.get_xhtml ? get_xhtml(body) : body.innerHTML);
    $field.val($field.val().replace(location.href + '#', '#'));
    // Remove editor instance.
    $('#' + whizzies[id] + '-whizzywig').remove();
    whizzies.splice(id, 1);
  };

  if (typeof params != 'undefined') {
    for (var id in whizzies) {
      if (whizzies[id] == params.field) {
        detach(id);
      }
    }
  }
  else {
    for (var id in whizzies) {
      detach(id);
    }
  }
};

})(jQuery);
