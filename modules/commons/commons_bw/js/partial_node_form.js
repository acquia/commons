(function ($) {

/**
 * Handles presentation of multiple partial forms of the same node bundle; When
 * showing a tab, check if it has a form's placeholder and if so, move the form
 * to the current tab and move the placeholder to the former form's tab.
 */
Drupal.behaviors.commonsBwPartialNodeForm = {
  attach: function (context, settings) {
    $('.quicktabs-tabs a', context).click(function(){
      var $activeTab = $('#quicktabs-container-commons_bw .quicktabs-tabpage:not(.quicktabs-hide)', context);
      // Check for a form placeholder.
      var $placeholder = $activeTab.find('.partial-node-form-placeholder');
      if (!$placeholder.length) {
        return;
      }

      var $form = $('.commons-bw-partial-node-form-' + $placeholder.data('bundle'), context);
      var $originalParent = $form.parent();
      // Replace the placeholder and the form.
      $form.appendTo($placeholder.parent());
      $placeholder.appendTo($originalParent);
    });
  }
}

/**
 * Expand a form when it is focused.
 */
Drupal.behaviors.commonsBwExpandableForm = {
  attach: function (context, settings) {
    $('.commons-bw-partial-node-form', context).once('commonsBwExpandableForm', function () {
      // Assemble the variables.
      var form = $(this),
          toggleText = Drupal.t('Collapse the form'),
          toggle = $('<a/>').attr({
            'class': 'expandable-form-toggle element-hidden',
            'href': '#',
            'title': toggleText
          }).append(toggleText),
          triggerField = form.find('.trigger-field'),
          fullFormLink = form.find('a.full-form'),
          hideables = form.find('.hideable-field'),
          errors = form.find('.error');

      // Determine if the form has any errors.
      if (!errors.length) {
        // Forms with errors are shown expanded, so only add the toggle link to
        // the top of forms which are error free.
        form.prepend(toggle).addClass('expandable-form compact-form');

        // Hide the hidden fields on load.
        hideables.addClass('element-invisible');
      }
      else {
        // The full form link is only shown on collapsed forms so it is hidden
        // for consistency.
        fullFormLink.addClass('element-hidden');
      }

      // Make all hidden fields visible when the trigger field comes into
      // focus.
      triggerField.find('textarea, input').focus(function () {
        form.addClass('expanded-form').removeClass('compact-form');
        toggle.removeClass('element-hidden');
        hideables.removeClass('element-invisible');
        fullFormLink.addClass('element-hidden');
      });

      // Hide all the hidden fields when the trigger link is clicked.
      toggle.click(function () {
        form.addClass('compact-form').removeClass('expanded-form');
        toggle.addClass('element-hidden');
        hideables.addClass('element-invisible');
        fullFormLink.removeClass('element-hidden');
        return false;
      });
    });
  }
}

})(jQuery);
