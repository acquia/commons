// $Id: openwysiwyg.js,v 1.1.4.1 2010/02/13 23:58:41 sun Exp $

// Reset $() to jQuery.  Yuck!
$ = jQuery;

(function($) {

/**
 * Attach this editor to a target element.
 */
Drupal.wysiwyg.editor.attach.openwysiwyg = function(context, params, settings) {
  jQuery.noConflict();
  $ = Drupal.wysiwyg._openwysiwyg;

  // Initialize settings.
  settings.ImagesDir = settings.path + 'images/';
  settings.PopupsDir = settings.path + 'popups/';
  settings.CSSFile = settings.path + 'styles/wysiwyg.css';
  //settings.DropDowns = [];
  var config = new WYSIWYG.Settings();
  for (var setting in settings) {
    config[setting] = settings[setting];
  }
  // Attach editor.
  WYSIWYG.setSettings(params.field, config);
  WYSIWYG_Core.includeCSS(WYSIWYG.config[params.field].CSSFile);
  WYSIWYG._generate(params.field, config);

  $ = jQuery;
};

/**
 * Detach a single or all editors.
 */
Drupal.wysiwyg.editor.detach.openwysiwyg = function(context, params) {
  jQuery.noConflict();
  $ = Drupal.wysiwyg._openwysiwyg;

  if (typeof params != 'undefined') {
    var instance = WYSIWYG.config[params.field];
    if (typeof instance != 'undefined') {
      WYSIWYG.updateTextArea(params.field);
      jQuery('#wysiwyg_div_' + params.field).remove();
      delete instance;
    }
    jQuery('#' + params.field).show();
  }
  else {
    jQuery.each(WYSIWYG.config, function(field) {
      WYSIWYG.updateTextArea(field);
      jQuery('#wysiwyg_div_' + field).remove();
      delete this;
      jQuery('#' + field).show();
    });
  }

  $ = jQuery;
};

/**
 * Custom implementation of $() for openwysiwyg.
 */
Drupal.wysiwyg._openwysiwyg = function (id) {
	return document.getElementById(id);
};

// Override editor functions.
WYSIWYG.getEditor = function (n) {
  return Drupal.wysiwyg._openwysiwyg("wysiwyg" + n);
};
WYSIWYG._closeDropDowns = WYSIWYG.closeDropDowns;
WYSIWYG.closeDropDowns = function (n, id) {
  jQuery.noConflict();
  $ = Drupal.wysiwyg._openwysiwyg;
  WYSIWYG._closeDropDowns(n, id);
  $ = jQuery;
};
WYSIWYG._openDropDown = WYSIWYG.openDropDown;
WYSIWYG.openDropDown = function (n, id) {
  jQuery.noConflict();
  $ = Drupal.wysiwyg._openwysiwyg;
  WYSIWYG._openDropDown(n, id);
  $ = jQuery;
};
WYSIWYG._viewSource = WYSIWYG.viewSource;
WYSIWYG.viewSource = function (n, id) {
  jQuery.noConflict();
  $ = Drupal.wysiwyg._openwysiwyg;
  WYSIWYG._viewSource(n, id);
  $ = jQuery;
};
WYSIWYG._viewText = WYSIWYG.viewText;
WYSIWYG.viewText = function (n, id) {
  jQuery.noConflict();
  $ = Drupal.wysiwyg._openwysiwyg;
  WYSIWYG._viewText(n, id);
  $ = jQuery;
};

})(jQuery);
