/*
 *  
 */
Drupal.behaviors.conxtextual_search_box = function (context) {
  $('#search-theme-form:not(.contextual-search-processed)')
    .addClass('contextual-search-processed')
    .each(Drupal.contextual_search_box.initialize);
};

Drupal.contextual_search_box = Drupal.contextual_search_box || {};

Drupal.contextual_search_box.initialize = function (i, element) {
  var $select = $('select[name=refine]', element);
  var $wrapper = $('<div class="contextual-search-wrapper"><div class="contextual-search-inner"><ul class="contextual-search-list"></ul></div></div>').appendTo(element);
    
  var $list = $('ul', $wrapper);
  var $options = $('option', $select);
  $options.each(function(i, option) {
    var $link = $('<a href="#" class="contextual-search-link" value="' + $(this).val() + '">' + $(this).text() + '</a>')
      .bind('click', element, Drupal.contextual_search_box.select);
    
    if (i == 0) {
      $link.addClass('first');
    } else if (i == ($options.length -1)) {
      $link.addClass('last');
    }
    
    $('<li></li>').append($link).appendTo($list);
  });
  
  // Add the launcher link
  $('<a class="contextual-search-launcher" href="#" title="' + Drupal.t('Click to reveal more options') + '">' + $(':selected', $select).text() + '</a>')
    .prependTo($('.contextual-search-inner', $wrapper));
  
  $('body').bind('click', $wrapper, Drupal.contextual_search_box.toggle);
};

Drupal.contextual_search_box.toggle = function (event) {
  var $list = $('.contextual-search-list', event.data);
  var $launcher = $('.contextual-search-launcher', event.data);
  
  if ($(event.target).hasClass('contextual-search-launcher')) {
    event.preventDefault();
    // Show the list.
    if ($list.width() == $launcher.width()) {
      $launcher.css({color: 'transparent'});
      $list.slideDown();
    } else {
      $launcher.animate({width: $list.width()}, function () {
        $launcher.css({color: 'transparent'});
        $list.slideDown();
      });
    }
  } else if ($list.is(':visible')) {
    // Hide the list.
    $list.slideUp(function() {
      $launcher.removeAttr('style');
      var width = $launcher.width();
      $launcher.width($list.width());
      $launcher.animate({width: width});
    });
  }
};

Drupal.contextual_search_box.select = function (event) {
  event.preventDefault();
  $('select[name=refine]', event.data).val($(event.target).attr('value'));
  var $launcher = $('.contextual-search-launcher', event.data)
  $launcher.text($(event.target).text());
};