Drupal.behaviors.facebookStatusAdmin = function (context) {
  // Make sure we can run context.find().
  var ctxt = $(context);
  var handle = function() {
    if (ctxt.find('input:radio[name=visibility]:checked').val() == '3') {
      ctxt.find('#edit-pages-wrapper').hide();
      ctxt.find('#edit-context-wrapper').show();
    }
    else {
      ctxt.find('#edit-pages-wrapper').show();
      ctxt.find('#edit-context-wrapper').hide();
    }
  };
  handle();
  ctxt.find('input:radio[name=visibility]').change(handle);
}
