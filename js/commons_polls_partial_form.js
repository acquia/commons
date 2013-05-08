(function ($) {

  // Handle the "Add more choices" link on the partial poll node form.
  Drupal.behaviors.commons_polls_partial_form = {
    attach: function(context) {
      $('#add-choice').click(function(event) {
        event.preventDefault();
        var $hiddenRows = $('#poll-choice-table tr.hidden', context);
        // Remove the add choices link when revealing the last available row.
        if ($hiddenRows.length == 1) {
          this.remove();
        }
        // Reveal the first hidden choice.
        $hiddenRows.first().show('fast').removeClass('hidden');
      });
    }
  }

})(jQuery);
