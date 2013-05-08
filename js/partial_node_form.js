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

})(jQuery);
