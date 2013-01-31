var get_size = function(){
  'use strict';

  var curr_width = jQuery(window).width();
  var html_elem = jQuery('html');

  if (curr_width <= 480 && !html_elem.hasClass('lt-480')) {
    html_elem.addClass('lt-480');
  } else if (curr_width > 480 && html_elem.hasClass('lt-480')) {
    html_elem.removeClass('lt-480');
  }
};

jQuery(document).ready(function($){

  'use strict';

//    $.fn.textWidth = function(){
//      var html_org = $(this).html();
//      var html_calc = '<span>' + html_org + '</span>';
//      $(this).html(html_calc);
//      var width = $(this).find('span:first').width();
//      $(this).html(html_org);
//      return width;
//    };

//    var selectwidth = $('#edit-following option:selected').textWidth();
//    console.log(selectwidth);

  get_size();

  $(window).resize(function(){
    get_size();
  });

  var attach_selectBox = function(){
    $('#views-exposed-form-commons-homepage-content-panel-pane-1 select, #edit-custom-search-types, #quicktabs-commons_bw select').selectBox();
  };

  $('.views-exposed-widgets .form-select, .custom-search-selector').wrap('<div class="form-select-wrapper" />');

  $(document).delegate('.views-exposed-widgets .form-select', 'change', function() {
    $('.views-exposed-widgets .views-submit-button').fadeIn(300);
  });

  $(document).delegate('.views-exposed-widgets .form-select', 'click', function() {
    $('.views-exposed-widgets').addClass('widgets-active');
  });

  //placeholder functionality
  // $('.view-id-commons_homepage_content .views-row-1 article h1').append("<div class='tag new'></div><div class='tag featured'></div>");
  $('#block-system-main-menu .menu-depth-1 a').append("<div class='arrow'></div>");

  $('.commons-bw-create-choose').click(function(){
    $('body').addClass('create-choose-open');
  });

  $('.commons-bw-create-choose-bg').click(function(){
    $('body').removeClass('create-choose-open');
  });

  attach_selectBox();

  $(document).ajaxComplete(function(){
    attach_selectBox();
  });
});
