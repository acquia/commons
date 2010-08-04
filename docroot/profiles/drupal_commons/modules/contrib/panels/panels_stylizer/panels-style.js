// $Id: panels-style.js,v 1.1.2.1 2010/02/17 01:09:46 merlinofchaos Exp $

/**
 * Provide some extra responses for the page list so we can have automatic
 * on change.
 */

Drupal.behaviors.PanelsStyleList = function() {
  var timeoutID = 0;
  $('form#panels-stylizer-list-styles-form select:not(.panels-processed)')
    .addClass('panels-processed')
    .change(function() {
      $('#edit-style-apply').click();
    });
  $('form#panels-stylizer-list-styles-form input[type=text]:not(.panels-processed)')
    .addClass('panels-processed')
    .keyup(function(e) {
      switch (e.keyCode) {
        case 16: // shift
        case 17: // ctrl
        case 18: // alt
        case 20: // caps lock
        case 33: // page up
        case 34: // page down
        case 35: // end
        case 36: // home
        case 37: // left arrow
        case 38: // up arrow
        case 39: // right arrow
        case 40: // down arrow
        case 9:  // tab
        case 13: // enter
        case 27: // esc
          return false;
        default:
          if (!$('#edit-style-apply').hasClass('ctools-ajaxing')) {
            if ((timeoutID)) {
              clearTimeout(timeoutID);
            }

            timeoutID = setTimeout(function() { $('#edit-style-apply').click(); }, 300);
        }
      }
    });
}
