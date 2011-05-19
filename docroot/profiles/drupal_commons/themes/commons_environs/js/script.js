$(document).ready(function(){
  /* show and hide search text */
  $('.search-box-inner input#edit-search-theme-form-header').attr('value', 'SEARCH');
  $('.search-box-inner input#edit-search-theme-form-header').focus(function(){
    $(this).attr('value', '');
  });
  $('.search-box-inner input#edit-search-theme-form-header').blur(function(){
    if ($(this).attr('value') === '') {
      $(this).attr('value', 'SEARCH');
    };
      });
  
  $('.header-site-info').prepend('<img src="/profiles/drupal_commons/themes/commons_environs/images/border-orange-left.png" class="border-orange-left"/><img src="/profiles/drupal_commons/themes/commons_environs/images/border-orange-right.png" class="border-orange-right"/>');
  
  $('.content-content').each(function(){
    if ($(this).prev().hasClass('content-tabs')) {
      $(this).addClass('top-left-straight');
    }
  });
  
  $('.not-front.og-context ul.sf-menu a').each(function(){
    if ($(this).attr('href') === '/community') {
      $(this).parent().addClass('active-trail');
      /*$(this).wrapInner('<span/>');*/
    }
  });
});
