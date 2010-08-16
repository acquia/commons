// $Id: jwysiwyg.js,v 1.3.4.1 2010/02/13 23:58:41 sun Exp $
(function($) {

/**
 * Attach this editor to a target element.
 */
Drupal.wysiwyg.editor.attach.jwysiwyg = function(context, params, settings) {
  // Attach editor.
  $('#' + params.field).wysiwyg();
};

/**
 * Detach a single or all editors.
 */
Drupal.wysiwyg.editor.detach.jwysiwyg = function(context, params) {
  var $field = $('#' + params.field);
  var editor = $field.data('wysiwyg');
  if (typeof editor != 'undefined') {
    editor.saveContent();
    editor.element.remove();
  }
  $field.removeData('wysiwyg');
  $field.show();
};

})(jQuery);
