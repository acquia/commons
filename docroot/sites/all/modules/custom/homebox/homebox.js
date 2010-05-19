// $Id: homebox.js,v 1.1.2.2 2010/04/30 09:13:31 jchatard Exp $
Drupal.homebox = {};
Drupal.behaviors.homebox = function(context) {
  $homebox = $('#homebox:not(.homebox-processed)', context).addClass('homebox-processed');
  
  if ($homebox.length > 0) {
    // Find all columns
    $columns = $homebox.find('div.homebox-column');
    
    // Equilize columns height
    $columns = Drupal.homebox.equalizeColumnsHeights($columns);
    
    // Make columns sortable
    $columns.sortable({
      items: '.homebox-portlet.homebox-draggable',
      handle: '.portlet-header',
      connectWith: $columns,
      revert: true,
      placeholder: 'homebox-placeholder',
      forcePlaceholderSize: true,
      stop: function() {
        Drupal.homebox.equalizeColumnsHeights($columns);
      }
    });
    // Add tools links
    $boxes = $homebox.find('.homebox-portlet');
    $boxes.find('.portlet-config').each(function() {
      if (jQuery.trim($(this).html()) != '') {
        $(this).prev('.portlet-header').prepend('<span class="portlet-icon portlet-settings"></span>').end();
      };
    });
    $boxes.find('.portlet-header').prepend('<span class="portlet-icon portlet-minus"></span>')
        .prepend('<span class="portlet-icon portlet-close"></span>')
        .end();
    // Remove close tool for unclosable blocks
    $homebox.find('.homebox-unclosable span.portlet-close').remove();
    // Attach click event on minus
    $boxes.find('.portlet-header .portlet-minus').click(function() {
      $(this).toggleClass("portlet-minus");
      $(this).toggleClass("portlet-plus");
      $(this).parents(".homebox-portlet:first").find(".portlet-content").toggle();
      Drupal.homebox.equalizeColumnsHeights($columns);
    });
    // Attach click event on minus
    $boxes.find('.portlet-header .portlet-minus').each(function() {
      if (!$(this).parents(".homebox-portlet:first").find(".portlet-content").is(':visible')) {
        $(this).toggleClass("portlet-minus");
        $(this).toggleClass("portlet-plus");
        Drupal.homebox.equalizeColumnsHeights($columns);
      };
    });
    // Attach click event on settings icon
    $boxes.find('.portlet-header .portlet-settings').click(function() {
      $(this).parents(".homebox-portlet:first").find(".portlet-config").toggle();
    });
    // Attach click event on close
    $boxes.find('.portlet-header .portlet-close').click(function() {
      $(this).parents(".homebox-portlet:first").hide();
      // Uncheck input settings
      dom_id = $(this).parents(".homebox-portlet:first").attr('id');
      $('#homebox_toggle_' + dom_id).attr('checked', false);
      Drupal.homebox.equalizeColumnsHeights($columns);
    });
    // Add click behaviour to checkboxes that enable/disable blocks
    $togglers = $homebox.find('#homebox-settings input.homebox_toggle_box');
    $togglers.click(function() {
      if ($(this).attr('checked')) {
        el_id = $(this).attr('id').replace('homebox_toggle_', '');
        $('#' + el_id).show();
      }else{
        el_id = $(this).attr('id').replace('homebox_toggle_', '');
        $('#' + el_id).hide();
      };
      Drupal.homebox.equalizeColumnsHeights($columns);
    });
    // Add click behaviour to color buttons
    $boxes.find('.homebox-color-selector').click(function() {
      color = $(this).css('background-color');
      classes = $(this).parents(".homebox-portlet:first").attr('class').split(" ");
      jQuery.each(classes, function(key, value) {
        if (value.indexOf('homebox-color-') == 0) {
          classes[key] = "";
        };
      });
      classes = classes.join(" ");
      $(this).parents(".homebox-portlet:first").attr('class', classes);
      $(this).parents(".homebox-portlet:first").addClass("homebox-color-" + Drupal.homebox.convertRgbToHex(color).replace("#", ''));
    });
    // Edit content link
    $('#homebox-add').click(function() {
      $('#homebox-settings').slideToggle();
    });
    // Save settings link
    $('#homebox-save a').click(function() {
      Drupal.homebox.saveBoxes();
    });
    // Restore to defaults link
    $('#homebox-restore a').click(function() {
      Drupal.homebox.restoreBoxes();
    });
    
    $homebox.ajaxStop(function(){
      Drupal.homebox.equalizeColumnsHeights($columns);
    });
  }
};

Drupal.homebox.equalizeColumnsHeights = function(columns) {
  maxHeight = 0;
  $columns.each(function() {
    $(this).height('auto');
    currentHeight = $(this).height();
    if (maxHeight < currentHeight) {
      maxHeight = currentHeight;
    };
  }).each(function() {
    $(this).height(maxHeight);
  });
  return $columns;
};

Drupal.homebox.restoreBoxes = function() {
  // Determine page name
  name = $('#homebox').find('input:hidden.name').val();
  
  // Replace link with message
  $('#homebox-restore').html('Restoring default settings...');
  
  $.ajax({
    url: Drupal.settings.basePath + '?q=homebox/js/restore',
    type: "POST",
    cache: "false",
    dataType: "json",
    data: {name: name},
    success: function() {
      location.reload(); // Reload page to show defaults
    },
    error: function() {
      $('#homebox-restore').html('<span style="color:red;">Restore failed. Please refresh page.</span>');
      console.log(Drupal.t("An error occured while trying to restore to defaults."))
    }
  });
};  

Drupal.homebox.saveBoxes = function() {
  var color = new String();
  var open = new Boolean();
  var block = new String();
  var blocks = {};

  $columns = Drupal.homebox.equalizeColumnsHeights($columns);
  $columns.each(function(colIndex) {
    // Determine region
    var colIndex = colIndex + 1;
    $(this).find('>.homebox-portlet').each(function(boxIndex) {
      // Determine page name
      name = $(this).find('input:hidden.name').val();
      
      // Determine block name
      block = $(this).find('input:hidden.homebox').val();
      
      // Determine visibility
      visible = 0;
      if ($(this).is(':visible')) {
        visible = 1;
      };
      
      // Determine custom color, if any
      attributes = $(this).attr('class').split(' ');
      for (a in attributes) {
        if (attributes[a].substr(0, 14) == 'homebox-color-') {
          color = attributes[a].substr(14);
        }
        else {
          color = 'default'; 
        }
      }
      
      // Determine state (open/closed)
      open = $(this).find(".portlet-content").is(':visible');

      // Build blocks object
      blocks[block] = {
          region: colIndex,
          status: visible,
          color: color,
          open: open
      }
    });
  });
 
  // Encode JSON
  blocks = JSON.stringify(blocks);
  
  // Replace save link with message
  $('#homebox-save a').hide();
  $('#homebox-save span').show();
  
  $.ajax({
    url: Drupal.settings.basePath + '?q=homebox/js/save',
    type: "POST",
    cache: "false",
    dataType: "json",
    data: {name: name, blocks: blocks},
    success: function() {
      // Replace message with save link
      $('#homebox-save a').show();
      $('#homebox-save span').hide();
    },
    error: function() {
      $('#homebox-save').html('<span style="color:red;">Save failed. Please refresh page.</span>');
      console.log(Drupal.t("An error occured while trying to save you settings."))
    }
  });
}

Drupal.homebox.convertRgbToHex = function(rgb) {
  if (!jQuery.browser.msie) {
    // Script taken from
    // http://stackoverflow.com/questions/638948/background-color-hex-to-js-variable-jquery
    var parts = rgb.match(/^rgb\((\d+),\s*(\d+),\s*(\d+)\)$/);
    // parts now should be ["rgb(0, 70, 255", "0", "70", "255"]
    delete (parts[0]);
    for (var i = 1; i <= 3; ++i) {
      parts[i] = parseInt(parts[i]).toString(16);
      if (parts[i].length == 1) parts[i] = '0' + parts[i];
    }
    return "#" + parts.join(''); // "0070ff"
  } else {
    return rgb;
  };
};
