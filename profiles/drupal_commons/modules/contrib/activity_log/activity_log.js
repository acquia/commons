Drupal.behaviors.activityLogAdmin = function (context) {
  // Make sure we can run context.find().
  var ctxt = $(context);
  ctxt.find('.activity-log-collection-more').click(function(e) {
    e.preventDefault();
    var parent = $(this).parents('.activity-log-collection');
    var more = parent.find('.activity-log-collection-more-expand');
    parent.html(more.html());
  });
}
