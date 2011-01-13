// $Id: ajax_load_example.js,v 1.2 2009/09/20 14:01:06 markuspetrux Exp $

(function ($) {

Drupal.AjaxLoadExample = Drupal.AjaxLoadExample || {};

/**
 * Ajax load example behavior. 
 */
Drupal.behaviors.AjaxLoadExample = function (context) {
  $('a.ajax-load-example:not(.ajax-load-example-processed)', context)
    .each(function () {
      // The target should not be e.g. a node that will itself be
      // replaced, as this would mean no node is available for
      // ajax_load to attach behaviors to when all scripts are loaded.
      var target = this.parentNode;
      $(this)
        .addClass('ajax-load-example-processed')
        .click(function () {
          $.ajax({
            // Either GET or POST will work.
            type: 'POST',
            data: 'ajax_load_example=1',
            // Need to specify JSON data.
            dataType: 'json',
            url: $(this).attr('href'),
            success: function(response){
              // Call all callbacks.
              if (response.__callbacks) {
                $.each(response.__callbacks, function(i, callback) {
                  // The first argument is a target element, the second
                  // the returned JSON data.
                  eval(callback)(target, response);
                });
                // If you don't want to return this module's own callback,
                // you could of course just call it directly here.
                // Drupal.AjaxLoadExample.formCallback(target, response);
              }
            }
          });
          return false;
        });
    });
};

/**
 * Ajax load example callback. 
 */
Drupal.AjaxLoadExample.formCallback = function (target, response) {
  target = $(target).hide().html(response.content).fadeIn();
  Drupal.attachBehaviors(target);
};

})(jQuery);
