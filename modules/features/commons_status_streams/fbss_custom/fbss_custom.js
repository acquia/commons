Drupal.behaviors.fbss_custom = function (context) {
  $('.facebook-status-text-main', context).each(function() {
    $(this).one('focus', function() {
      $(this).parents('.facebook-status-form').addClass('show-controls');
    });
  });
  
  $('.fbsmp-inner-expanded', context).each(function(){
    $(this).parents('.facebook-status-form').removeClass('controls-collapsed').addClass('controls-expanded');
  });
  
  $('.fbsmp-inner-collapsed', context).each(function(){
    $(this).parents('.facebook-status-form').removeClass('controls-expanded').addClass('controls-collapsed');
  });
}
