syze.sizes(320, 480, 935);

jQuery(document).ready(function($){

  'use strict';

  var set_follow_checkboxes = function(){
    $('#quicktabs-commons_follow_ui .flag-email-group a, #quicktabs-commons_follow_ui .flag-email-node a, #quicktabs-commons_follow_ui .flag-email-user a, #quicktabs-commons_follow_ui .flag-email-term a').each(function(){
      var a_target = $(this).addClass('formatted-as-checkbox').removeClass('action-item-small action-item-small-active');

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

  var set_disabled_checkboxes = function(){
    $('#quicktabs-commons_follow_ui .flag-email-group span, #quicktabs-commons_follow_ui .flag-email-node span, #quicktabs-commons_follow_ui .flag-email-user span, #quicktabs-commons_follow_ui .flag-email-term span').each(function(){
      var a_target = $(this).addClass('formatted-as-checkbox').removeClass('action-item-small action-item-small-active');

      if (a_target.children('span').length === 0) {
        a_target.wrapInner('<span></span>');
      }

      if (a_target.hasClass('flag-action') && a_target.children('input').length === 0) {
        a_target.prepend('<input type="checkbox" disabled="disabled">');
      } else if (a_target.children('input').length === 0) {
        a_target.prepend('<input type="checkbox" disabled="disabled" checked>');
      }
    });
  };

  $(document).delegate('.views-exposed-widgets .form-select', 'change', function() {
    $('.views-exposed-widgets').addClass('widget-changed');
  });

  $(document).delegate('.views-exposed-widgets .form-select', 'click', function() {
    $('.views-exposed-widgets').addClass('widgets-active');
  });

  if($('#quicktabs-commons_follow_ui a.flag').length > 0) {
      set_follow_checkboxes();

      $(document).ajaxComplete(function(){
        set_follow_checkboxes();
      });
  } else {
      set_disabled_checkboxes();
  }
});

(function ($) {

  /**
   * Make select elements simulate an anchor element.
   */
  function hiddenSelect (selectContainer) {
    var select = selectContainer.children('select').addClass('hidden-select').wrap('<span class="hidden-select-wrapper"></span>');
        val = select.children('option[value="' + select.val() + '"]').text();

    $('<a />', {
      'class': 'select-status',
      'href': '#'
    }).text(val).insertBefore(select);

    var selectStatus = select.siblings('a.select-status'),
        wrapper = select.parent().addClass('select-inactive');

    select.mousedown(function () {
      wrapper.addClass('select-active').removeClass('select-inactive');
      select.focus();
    }).change(function () {
      val = select.children('option[value="' + select.val() + '"]').text();
      selectStatus.text(val);
      select.blur();
    }).blur(function () {
      wrapper.addClass('select-inactive').removeClass('select-active').delay(3000).css('width', selectStatus.outerWidth());
    });
  }

  /**
   * Allow select forms to be styled more directly.
   */
  Drupal.behaviors.formSelect = {
    attach: function (context, settings) {
      var selects = $('.search-form .form-type-select, .views-exposed-widgets .form-type-select', context),
          counter = 0;

      if (selects.length > 0) {
        selects.once('formSelect', function () {
          hiddenSelect($(this));
        });
      }
    }
  };

  /**
   * Define a variable height on fieldsets to accommodate multi-line layouts.
   */
  Drupal.behaviors.collapsibleHeight = {
    attach: function (context, settings) {
      $('fieldset.collapsible', context).once('collapsibleHeight', function () {
        var fieldset = $(this),
            minHeight = fieldset.find('legend').height();


        fieldset.css('min-height', minHeight + 'px');

        // Adjust the height on window resize.
        $(window).resize(function () {
          var minHeight = fieldset.find('legend').height();
          fieldset.css('min-height', minHeight + 'px');
        });
      });
    }
  };

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
            results = $('.search-results-content, .pane-search-result'),
            size = $(window).width(),
            triggerWidth = '';

        // Only function if there are filters available.
        if (filters.find('.panel-pane').length > 0) {
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
              $(filters).css('top', '').removeClass('expanded');
              $(filterOverlay).removeClass('expanded');
            }
          });
          $(document).scroll(function () {
            if (!$(filters).hasClass('expanded')) {
              showWithElement(filterTrigger, results);
            }
          });
        }
      });
    }
  };
})(jQuery);
