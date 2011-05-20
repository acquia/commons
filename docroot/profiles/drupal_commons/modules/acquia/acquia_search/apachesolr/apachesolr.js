
Drupal.behaviors.apachesolr = function(context) {
  $('.apachesolr-hidden-facet', context).hide();
  $('<a href="#" class="apachesolr-showhide"></a>').text(Drupal.t('Show more')).click(function() {
    if ($(this).parent().find('.apachesolr-hidden-facet:visible').length == 0) {
      $(this).parent().find('.apachesolr-hidden-facet').show();
      $(this).text(Drupal.t('Show fewer'));
    }
    else {
      $(this).parent().find('.apachesolr-hidden-facet').hide();
      $(this).text(Drupal.t('Show more'));
    }
    return false;
  }).appendTo($('.block-apachesolr_search:has(.apachesolr-hidden-facet), .block-apachesolr:has(.apachesolr-hidden-facet)', context));
}
