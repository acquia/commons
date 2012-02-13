Drupal.behaviors.check_js = function (context) {
  
  if ($('html').hasClass('no-js')) {
    $('html').removeClass('no-js');
  }

};

Drupal.behaviors.user_dropdown = function (context) {
  
  if (!$('body').hasClass('user-dropdown-processed')) {
    
    $('body').addClass('user-dropdown-processed');
    $('.view-user-meta .views-field-name a').attr('href','javascript:;');
    $('.views-field-nothing, .views-field-nothing-1').wrapAll('<div class="user-field-options" />');
    $('.user-field-options').width($('.view-user-meta .views-field-name .welcome-text').width());
    
    $('.view-user-meta .views-field-name a').click(function(){
      if ($('body').hasClass('user-dropdown-open')) {
        $('.user-field-options').hide();
        $('body').removeClass('user-dropdown-open');
      } else {
        $('.user-field-options').show();
        $('body').addClass('user-dropdown-open');
      }
    });
    
  }

};

Drupal.behaviors.equal_height = function (context) {
  
  var height = 0;
  
  var elements = $('#sidebar-first, #sidebar-last, #content-group');
  
  elements.each(function(){
    if ($(this).height() > height) {
      height = $(this).height();
    }
  });
  
  elements.css('min-height',height + 'px');

};
