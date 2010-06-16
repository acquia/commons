// $Id: script.js,v 1.1.2.4 2010/02/14 06:44:15 sociotech Exp $

Drupal.behaviors.fusionEqualheights = function (context) {
  if (jQuery().equalHeights) {
    $("#header-top-wrapper div.equal-heights div.content").equalHeights();
    $("#header-group-wrapper div.equal-heights div.content").equalHeights();
    $("#preface-top-wrapper div.equal-heights div.content").equalHeights();
    $("#preface-bottom div.equal-heights div.content").equalHeights();
    $("#sidebar-first div.equal-heights div.content").equalHeights();
    $("#content-top div.equal-heights div.content").equalHeights();
    $("#content-region div.equal-heights div.content").equalHeights();
    $("#content-bottom div.equal-heights div.content").equalHeights();
    $("#node-top div.equal-heights div.content").equalHeights();
    $("#node-bottom div.equal-heights div.content").equalHeights();
    $("#sidebar-last div.equal-heights div.content").equalHeights();
    $("#postscript-top div.equal-heights div.content").equalHeights();
    $("#postscript-bottom-wrapper div.equal-heights div.content").equalHeights();
    $("#footer-wrapper div.equal-heights div.content").equalHeights();
  }
};

Drupal.behaviors.fusionIE6fixes = function (context) {
  // IE6 & less-specific functions
  // Add hover class to primary menu li elements on hover
  if ($.browser.msie && ($.browser.version < 7)) {
    $('form input.form-submit').hover(function() {
      $(this).addClass('hover');
      }, function() {
        $(this).removeClass('hover');
    });
    $('#primary-menu ul.sf-menu li.expanded').hover(function() {
      $(this).addClass('hover');
      }, function() {
        $(this).removeClass('hover');
    });
    $('#search input#search_header').hover(function() {
      $(this).addClass('hover');
      }, function() {
        $(this).removeClass('hover');
    });
  };
};

Drupal.behaviors.fusionOverlabel = function (context) {
  if (jQuery().overlabel) {
    $("div.fusion-horiz-login label").overlabel();
  }
};

Drupal.behaviors.fusionSuperfish = function (context) {
  $("#primary-menu ul.sf-menu").superfish({
    hoverClass:  'sfHover',
    delay:       250,
    animation:   {opacity:'show',height:'show'},
    speed:       'fast',
    autoArrows:  false,
    dropShadows: false,
    disableHI:   true
  }).supposition();
};

Drupal.behaviors.fusionSuperfishBlocks = function (context) {
  $("div.block ul.sf-menu").superfish({
    hoverClass:  'sfHover',
    delay:       250,
    animation:   {opacity:'show',height:'show'},
    speed:       'fast',
    autoArrows:  false,
    dropShadows: false,
    disableHI:   true
  }).supposition();
};

Drupal.behaviors.fusionGridMask = function (context) {
  if ($('body.grid-mask-enabled').size() > 0) {
    var grid_width_pos = parseInt($('body').attr('class').indexOf('grid-width-')) + 11;
    var grid_width = $('body').attr('class').substring(grid_width_pos, grid_width_pos + 2);
    var grid = '<div id="grid-mask-overlay" class="full-width"><div class="row">';
    for (i = 1; i <= grid_width; i++) {
      grid += '<div class="block grid' + grid_width + '-1"><div class="inner"></div></div>';
    }
    grid += '</div></div>';
    $('body.grid-mask-enabled').prepend(grid);
    $('#grid-mask-overlay .row').addClass('grid' + grid_width + '-' + grid_width);
    $('#grid-mask-overlay .block .inner').height($('body').height());
  }
};

Drupal.behaviors.fusionGridMaskToggle = function (context) {
  if ($('body.grid-mask-enabled').size() > 0) {
    $('body.grid-mask-enabled').prepend('<div id="grid-mask-toggle">grid</div>');
    $('div#grid-mask-toggle')
      .toggle( function () {
        $(this).toggleClass('grid-on');
        $('body').toggleClass('grid-mask');
      },
      function() {
        $(this).toggleClass('grid-on');
        $('body').toggleClass('grid-mask');
      });
  }
};
