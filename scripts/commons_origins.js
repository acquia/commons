syze.sizes(320, 480, 935);

jQuery(document).ready(function($){

  'use strict';

  var attach_selectBox = function(){
    $('#views-exposed-form-commons-homepage-content-panel-pane-1 select, #edit-custom-search-types, #quicktabs-commons_bw select, .views-exposed-widgets select').selectBox();
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

(function ($) {
  /**
   * Make an item follow the page when an item is in view.
   */
  function showWithElement(tracker, leader) {
    if ($(leader).length > 0) {
      var top = $(leader).offset().top,
          bottom = $(leader).innerHeight() + top,
          trackerHeight = $(tracker).innerHeight();
          position = $(document).scrollTop();

      // Make sure the tracker parent stays aligned with the leader.
      $(tracker).parent().css('top', top);

      // Keep the trigger visible when the leader is in view.
      if (top < position && (bottom - trackerHeight) > position && !$(tracker).hasClass('following')) {
        $(tracker).addClass('following').css('top', $('.region-page-top').offset().top);
      }
      else if ((top >= position || (bottom - trackerHeight) <= position) && $(tracker).hasClass('following')) {
        $(tracker).removeClass('following').css('top', '');
      }
    }
  }

  /**
   * Collapse the filter options for search.
   */
  Drupal.behaviors.filterDrawer = {
    attach: function (context, settings) {
      $('.page-search .region-two-33-66-first, .page-events .region-three-25-50-25-first', context).once('filterDrawer', function () {
        var filters = $(this),
            filterTrigger = $('<a/>', {'href': '#filter-drawer', 'class': 'filter-trigger', 'id': 'filter-drawer'}).text(Drupal.t('Filter results')),
            filterOverlay = $('<div/>', {'class': 'filter-overlay'}),
            results = $('.search-results-content');
            size = $(window).width(),
            triggerWidth = '';

        // Determine if the page is for search or events and set the target
        // width.
        if ($('.page-search', context).length > 0) {
          triggerWidth = 480;
        }
        else if ($('.page-events', context).length > 0) {
          triggerWidth = 768;
        }

        // Add process flags and styling elements.
        $(this).prepend(filterTrigger).addClass('filters-processed');
        $('body').append(filterOverlay);

        // Make sure the trigger is in place on the initial page load.
        if (size <= triggerWidth) {
          showWithElement(filterTrigger, results);
        }

        // Define the clickable areas to control the visibility of the filters.
        $(filterTrigger).click(function () {
          if ($(filterTrigger).hasClass('following')) {
            $(filterTrigger).removeClass('following');
          }
          $(filters).toggleClass('expanded');
          $(filterOverlay).toggleClass('expanded');

          if ($(filters).hasClass('expanded')) {
            $('html, body').animate({
              scrollTop: $(filterTrigger).offset().top - $('.region-page-top').offset().top
            }, 0);
          }

          return false;
        });
        $(filterOverlay).click(function () {
          $(filters).toggleClass('expanded');
          $(filterOverlay).toggleClass('expanded');
          showWithElement(filterTrigger, results);
        });

        // Make the filterToggle follow the search results when scrolling and
        // resizing.
        $(window).resize(function () {
          size = $(window).width();
          if (size <= triggerWidth) {
            showWithElement(filterTrigger, results);
          }
          else {
            $(filters).css('top', '');
          }
        });
        $(document).scroll(function () {
          if (!$(filters).hasClass('expanded')) {
            showWithElement(filterTrigger, results);
          }
        });
      });
    }
  }
})(jQuery);
