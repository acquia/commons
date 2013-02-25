syze.sizes(320, 480, 935);

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

  var attach_selectBox = function(){
    $('#views-exposed-form-commons-homepage-content-panel-pane-1 select, #edit-custom-search-types, #quicktabs-commons_bw select').selectBox();
  };

  var set_follow_checkboxes = function(){
    $('#quicktabs-commons_follow_ui .flag-email-group a, #quicktabs-commons_follow_ui .flag-email-node a, #quicktabs-commons_follow_ui .flag-email-user a, #quicktabs-commons_follow_ui .flag-email-term a').each(function(){
      var a_target = $(this);

      if (a_target.children('span').length === 0) {
        a_target.wrapInner('<span></span>');
      }
      
      if (a_target.hasClass('flag-action') && a_target.children('input').length === 0) {
        a_target.prepend('<input type="checkbox">');
      } else if (a_target.children('input').length === 0) {
        a_target.prepend('<input type="checkbox" checked>');
      }
    });
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

  $('.page-node-add #edit-additional-settings').css('top', ($('.page-node-add .field-type-taxonomy-term-reference-form').height() + 15));

  attach_selectBox();
  set_follow_checkboxes();

  $(document).ajaxComplete(function(){
    attach_selectBox();
    set_follow_checkboxes();
  });
});
