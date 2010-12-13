// $Id: homebox.js,v 1.1.4.36 2010/07/30 02:54:53 mikestefff Exp $
Drupal.homebox = {};
Drupal.behaviors.homebox = function(context) {
  $homebox = $('#homebox:not(.homebox-processed)', context).addClass('homebox-processed');
  
  // Prevent double-clicks from causing a selection
  $(".portlet-header").disableSelection();
  
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
      placeholder: 'homebox-placeholder',
      forcePlaceholderSize: true,
      over: function() {
        Drupal.homebox.equalizeColumnsHeights($columns);
      },
      stop: function() {
        Drupal.homebox.equalizeColumnsHeights($columns);
        $('#homebox-changes-made').show();
      }
    });
    
    // Add tools links
    $boxes = $homebox.find('.homebox-portlet');
    $boxes.find('.portlet-config').each(function() {
      if (jQuery.trim($(this).html()) != '') {
        $(this).prev('.portlet-header').prepend('<div class="portlet-icon portlet-settings"></div>').end();
      };
    });
    $boxes.find('.portlet-header').prepend('<div class="portlet-icon portlet-minus"></div>')
        .prepend('<div class="portlet-icon portlet-close"></div>')
        .end();
        
    // Remove close tool for unclosable blocks
    $homebox.find('.homebox-unclosable div.portlet-close').remove();
    
    // Add maximize link to every portlet
    $boxes.find('.portlet-header .portlet-minus').before('<div class="portlet-icon portlet-maximize"></div>');
    
    // Add region to place maximized portlets
    $homebox.find('.homebox-column-wrapper:first').before('<div class="homebox-maximized"></div>');
    
    // Attach click event to maximize icon
    $boxes.find('.portlet-header .portlet-maximize').click(function() {
      $(this).toggleClass("portlet-maximize");
      $(this).toggleClass("portlet-minimize");
      Drupal.homebox.maximizeBox(this);
      Drupal.homebox.equalizeColumnsHeights($columns);
    });  
    
    // Attach click event on minus
    $boxes.find('.portlet-header .portlet-minus').click(function() {
      $(this).toggleClass("portlet-minus");
      $(this).toggleClass("portlet-plus");
      $(this).parents(".homebox-portlet:first").find(".portlet-content").toggle();
      Drupal.homebox.equalizeColumnsHeights($columns);
      $('#homebox-changes-made').show();
    });
    
    // Attach click event on minus
    $boxes.find('.portlet-header .portlet-minus').each(function() {
      if (!$(this).parents(".homebox-portlet:first").find(".portlet-content").is(':visible')) {
        $(this).toggleClass("portlet-minus");
        $(this).toggleClass("portlet-plus");
        Drupal.homebox.equalizeColumnsHeights($columns);
      };
    });
    
    // Attach double click event on portlet header
    $boxes.find('.portlet-title').dblclick(function() {
      if ($(this).parents(".homebox-portlet:first").find(".portlet-content").is(':visible')) {
        $(this).parent('.portlet-header').find('.portlet-minus').toggleClass("portlet-plus");  
        $(this).parent('.portlet-header').find('.portlet-minus').toggleClass("portlet-minus");
      }
      else {
        $(this).parent('.portlet-header').find('.portlet-plus').toggleClass("portlet-minus");
        $(this).parent('.portlet-header').find('.portlet-plus').toggleClass("portlet-plus"); 
      }
      
      $(this).parents(".homebox-portlet:first").find(".portlet-content").toggle();
      
      Drupal.homebox.equalizeColumnsHeights($columns);
      $('#homebox-changes-made').show();
    });
    
    // Attach click event on settings icon
    $boxes.find('.portlet-header .portlet-settings').click(function() {
      $(this).parents(".homebox-portlet:first").find(".portlet-config").toggle();
      Drupal.homebox.equalizeColumnsHeights($columns);
    });
    
    // Attach click event on close
    $boxes.find('.portlet-header .portlet-close').click(function() {
      $(this).parents(".homebox-portlet:first").hide();
      // Uncheck input settings
      dom_id = $(this).parents(".homebox-portlet:first").attr('id');
      $('#homebox_toggle_' + dom_id).attr('checked', false);
      Drupal.homebox.equalizeColumnsHeights($columns);
      $('#homebox-changes-made').show();
    });
    
    // Add click behaviour to checkboxes that enable/disable blocks
    $togglers = $homebox.find('#homebox-settings input.homebox_toggle_box');
    $togglers.click(function() {
      if ($(this).attr('checked')) {
        el_id = $(this).attr('id').replace('homebox_toggle_', '');
        $('#' + el_id).show();
      }
      else{
        el_id = $(this).attr('id').replace('homebox_toggle_', '');
        $('#' + el_id).hide();
      };
      Drupal.homebox.equalizeColumnsHeights($columns);
      $('#homebox-changes-made').show();
    });
    
    // Apply custom colors to blocks
    $boxes.each(function() {
      var attributes = $(this).attr('class').split(' ');
      for (a in attributes) {
        if (attributes[a].substr(0, 14) == 'homebox-color-') {
          $(this).find('.portlet-header').attr("style", "background: #" + attributes[a].substr(14));
          $(this).find('.homebox-portlet-inner').attr("style", "border: 1px solid #" + attributes[a].substr(14));
        }
      }
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
      
      // Add color classes to blocks
      // This is used when we save so we know what color it is
      $(this).parents(".homebox-portlet:first").attr('class', classes);
      $(this).parents(".homebox-portlet:first").addClass("homebox-color-" + Drupal.homebox.convertRgbToHex(color).replace("#", ''));
      
      // Apply the colors via style attributes
      // This avoid dynamic CSS
      $(this).parents(".homebox-portlet:first").find('.portlet-header').attr("style", "background: " + Drupal.homebox.convertRgbToHex(color));
      $(this).parents(".homebox-portlet:first").find('.homebox-portlet-inner').attr("style", "border: 1px solid " + Drupal.homebox.convertRgbToHex(color));
      $('#homebox-changes-made').show();
    });
    
    // Initialize popup dialogs
    Drupal.homebox.initDialogs();
    
    // Intialize popup links
    Drupal.homebox.initDialogLinks();
    
    // Clear out add item form components
    $('#homebox-add-form-title').val('');
    $('#homebox-add-form-content').val('');
    
    // Equalize column heights after AJAX calls
    $homebox.ajaxStop(function(){
      Drupal.homebox.equalizeColumnsHeights($columns);
    });
    
    // Add tooltips to icons
    $('.portlet-icon').tipsy({
      gravity: 's',
      title: function() {
        switch ($(this).attr('class').replace('portlet-icon portlet-', '')) {
          case 'close':
            return Drupal.t('Close');
          case 'maximize':
            return Drupal.t('Maximize');
          case 'minimize':
            return Drupal.t('Minimize');
          case 'minus':
            return Drupal.t('Collapse');
          case 'plus':
            return Drupal.t('Expand');
          case 'settings':
            return Drupal.t('Settings');
        }
      }
    });
    
    // Remove tooltips on header clicks
    $boxes.find('.portlet-header').click(function() {
      $('.tipsy').remove();
    });
  }
};

/*
 * Declare all dialog windows
 */
Drupal.homebox.initDialogs = function() {
  // Put widget selection in a dialog window
  $('#homebox-settings').dialog({
    modal: true,
    autoOpen: false,
    width: 400
  });
    
  // Save settings progress dialog
  $('#homebox-save-message').dialog({
    modal: true,
    height: 100,
    autoOpen: false
  });
  
  // Deletion confirmation dialog
  $('#homebox-delete-custom-message').dialog({
    autoOpen: false,
	  modal: true,
    height: 145,
    width: 500,
    buttons: {
		  'Delete': function() {
				Drupal.homebox.deleteItem($(this).find('input').val());
			},
		  Cancel: function() {
			  $(this).dialog('close');
		  }
    }  
  }); 
  
  // Add item dialog
  $('#homebox-add-form').dialog({
    autoOpen: false,
	  modal: true,
    zIndex: 500,
    width: 500,
    height: 350,
    buttons: {
		  'Submit': function() {
        Drupal.homebox.addItem();
      },
      Cancel: function() {
        $('#homebox-add-form-status').hide();
        $('#homebox-add-form-title').val('');
        $('#homebox-add-form-content').val('');
				$(this).dialog('close');
			}
    }
  });
  
  // Edit item dialog
  $('#homebox-edit-form').dialog({
    autoOpen: false,
	  modal: true,
    zIndex: 500,
    width: 500,
    height: 350,
    buttons: {
		  'Submit': function() {
        Drupal.homebox.editItem($(this).find('input:hidden').val());
        $('#homebox-changes-made').show();
      },
      Cancel: function() {
        $('#homebox-edit-form-status').hide();
        $('#homebox-edit-form-title').val('');
        $('#homebox-edit-form-content').val('');
				$(this).dialog('close');
			}
    }
  });
  
  // Restore to default in-progress dialog
  $('#homebox-restore-inprogress').dialog({
    autoOpen: false,
	  modal: true,
    height: 100
  });
  
  // Restore to default confirmation dialog
  $('#homebox-restore-confirmation').dialog({
    height: 160,
    width: 450,
    autoOpen: false,
	  modal: true,
		buttons: {
		  'Restore': function() {
			  $(this).dialog('close');
        Drupal.homebox.restoreBoxes();
      },
			Cancel: function() {
			  $(this).dialog('close');
      }
    }
  });
};

/*
 * Attach click events to all links which handle
 * dialog windows
 */
Drupal.homebox.initDialogLinks = function() {
  // Edit content link
  $('#homebox-edit-link').click(function() {
    $('#homebox-settings').dialog('open');
  });
    
  // Save settings link
  $('#homebox-save-link').click(function() {
    Drupal.homebox.saveBoxes();
  });
    
  // Restore to defaults link
  $('#homebox-restore-link').click(function() {
    $('#homebox-restore-confirmation').dialog('open');
  });
    
  // Add items link
  $('#homebox-add-link').click(function() {
    $('#homebox-add-form').dialog('open');
  });
    
  // Delete custom item link
  $('.homebox-delete-custom-link').click(function() {
    // Place the block ID into the dialog
    $('#homebox-delete-custom-message input').val(
      $(this).attr('id').replace('delete-', '')
    );
    $('#homebox-delete-custom-message').dialog('open'); 
  });
  
  // Edit custom item link
  $('.homebox-edit-custom-link').click(function() {
    // Place the block ID into the dialog
    $('#homebox-edit-form input:hidden').val(
      $(this).attr('id').replace('edit-', '')
    );
    // Populate the title field
    $('#homebox-edit-form-title').val($(this).parents('.homebox-portlet').find('.portlet-title').html());
    // Populate the content field
    $('#homebox-edit-form-content').val($(this).parents('.homebox-portlet').find('.portlet-content').html().HTMLtoNewline());
    // Open the dialog
    $('#homebox-edit-form').dialog('open'); 
  });
};

/*
 * Set all column heights equal
 */
Drupal.homebox.equalizeColumnsHeights = function(columns) {
  maxHeight = 0;
  $columns.each(function() {
    if ($(this).parent('.homebox-column-wrapper').attr('style') != 'width: 100%;') {
      $(this).height('auto');
      currentHeight = $(this).height();
      if (maxHeight < currentHeight) {
        maxHeight = currentHeight;
      };
    };
  }).each(function() {
    if ($(this).parent('.homebox-column-wrapper').attr('style') != 'width: 100%;') {
      $(this).height(maxHeight);
    }
  });
  
  return $columns;
};

/*
 * Deletes user's settings via AJAX call, then
 * reloads the page to restore the defaults
 */
Drupal.homebox.restoreBoxes = function() {
  // Show in-progress dialog
  $('#homebox-restore-inprogress').dialog('open');
  
  // Determine page name
  name = $('#homebox').find('input:hidden.name').val();
  
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
      $('#homebox-restore-inprogress').html('<span style="color:red;">' + Drupal.t('Restore failed. Please refresh page.') + '</span>');
    }
  });
};  

Drupal.homebox.maximizeBox = function(icon) {
  // References to active portlet and its homebox
  var portlet = $(icon).parents('.homebox-portlet');
  var homebox = $(icon).parents('#homebox');

  // Only fire this action if this widget isnt being dragged
  if (!$(portlet).hasClass('ui-sortable-helper')) {
    // Check if we're maximizing or minimizing the portlet
    if ($(portlet).hasClass('portlet-maximized')) {
      // Minimizing portlet
         
      // Move this portlet to its original place (remembered with placeholder)
      $(portlet).insertBefore($(homebox).find('.homebox-maximized-placeholder'))
        .toggleClass('portlet-maximized');
          
      // Remove placeholder
      $(homebox).find('.homebox-maximized-placeholder').remove();
        
      // Show columns again
      $(homebox).find('.homebox-column').show();
         
      // Show close icon again
      $(portlet).find('.portlet-close').show();
       
      // Show the save button
      $('#homebox-save-link').show();
      $('#homebox-minimize-to-save').hide();
      
      // Restore the checkbox under "Edit Content"
      $('input#homebox_toggle_' + $(portlet).attr('id')).removeAttr('disabled');
    }
    else {
      // Maximizing portlet
         
      // Add the portlet to maximized content place and create a placeholder 
      // (for minimizing back to its place)
      $(portlet)
        .before('<div class="homebox-maximized-placeholder"></div>')
        .appendTo($(icon).parents('#homebox').find('.homebox-maximized'))
        .toggleClass('portlet-maximized');
           
      // Hide columns - only show maximized content place (including maximized widget)
      $(homebox).find('.homebox-column').hide();

      // Hide close icon (you wont be able to return if you close the widget)
      $(portlet).find('.portlet-close').hide();  
      
      // Hide the save button
      $('#homebox-save-link').hide();
      $('#homebox-minimize-to-save').show();
    
      // Disable the checkbox under "Edit content"
      $('input#homebox_toggle_' + $(portlet).attr('id')).attr('disabled', 'disabled');
    }    
  }
};

/*
 * Add a custom block
 */
Drupal.homebox.addItem = function() {
  var block = {};
  var title = $('#homebox-add-form-title').val().stripTags();
  var content = $('#homebox-add-form-content').val();
  
  // Make sure both fields are supplied
  if (!title || !content) {
    $('#homebox-add-form-status').show();
    $('#homebox-add-form-status').html(Drupal.t('All fields are required.'));
    return;
  }
  
  // Convert content newlines to HTML
  content = content.newlineToHTML();
  
  // Place data into the custom block object
  block = {
		title: title,
		body: content
	}
	
	// Encode the block
	block = JSON.stringify(block);

  // Show progress message
  $('#homebox-add-form').html(Drupal.t('Adding item') + '...');

  // Save current configuration
  // We pass the custom block in, because it will be added
  // after the full save is executed, only if successful 
  Drupal.homebox.saveBoxes(block);
};

/*
 * The AJAX call for adding an item
 * 
 * This needs to be separate so that .saveBoxes()
 * can call it after a successful AJAX save
 */
Drupal.homebox.addItemAjax = function(name, block) {
  $.ajax({
    url: Drupal.settings.basePath + '?q=homebox/js/add',
    type: "POST",
    cache: "false",
    dataType: "json",
    data: {name: name, block: block},
    success: function() {
      $('#homebox-add-form').html(Drupal.t('Refreshing page') + '...');
      location.reload(); // Reload page
    },
    error: function() {
      $('#homebox-add-form').html('<span style="color:red;">' + Drupal.t('Save failed. Please refresh page.') + '</span>');
    }
  });
};

/*
 * Delete a custom block from the page
 */
Drupal.homebox.deleteItem = function(block) {
  var name = $('#homebox').find('input:hidden.name').val();
  
  $('#homebox-delete-custom-message').html(Drupal.t('Deleting item') + '...');
  
  $.ajax({
    url: Drupal.settings.basePath + '?q=homebox/js/delete',
    type: "POST",
    cache: "false",
    dataType: "json",
    data: {name: name, block: block},
    success: function() {
      $('#homebox-delete-custom-message').html(Drupal.t('Refreshing page') + '...');
      location.reload(); // Reload page
    },
    error: function() {
      $('#homebox-delete-custom-message').html('<span style="color:red;">' + Drupal.t('Deletion failed. Please refresh page.') + '</span>');
    }
  });
};

/*
 * Save the current state of the homebox
 * 
 * @param save
 *   Optionally, A JSON-encoded custom block object. This is passed in
 *   because we want to first save the current state, then add the
 *   custom block so changes are preserved, and that we can only
 *   add if and when the first ajax call is successful.
 */
Drupal.homebox.saveBoxes = function(save) {
  var color = new String();
  var open = new Boolean();
  var block = new String();
  var name = $('#homebox').find('input:hidden.name').val();
  var blocks = {};
  
  // Show progress dialog
  $('#homebox-save-message').dialog('open');

  $columns = Drupal.homebox.equalizeColumnsHeights($columns);
  $columns.each(function(colIndex) {
    // Determine region
    var colIndex = colIndex + 1;
    $(this).find('>.homebox-portlet').each(function(boxIndex) {
      // Determine block name
      block = $(this).find('input:hidden.homebox').val();
      
      // Determine visibility
      visible = 0;
      if ($(this).is(':visible')) {
        visible = 1;
      };

      // Determine custom color, if any
      attributes = $(this).attr('class').split(' ');
      color = 'default';
      for (a in attributes) {
        if (attributes[a].substr(0, 14) == 'homebox-color-') {
          color = attributes[a].substr(14);
        }
      }
      
      // Determine state (open/closed)
      open = $(this).find(".portlet-content").is(':visible');

      // Build blocks object
      if (block.search('homebox_') != -1) {
        // If block is custom, we need more data
        blocks[block] = {
          region: colIndex,
          status: visible,
          color: color,
          open: open,
          title: $(this).find('.portlet-title').html().stripTags(),
          content: $(this).find('.portlet-content').html(),
          module: 'homebox',
          delta: block.replace('homebox_', '')
        }
      }
      else {
        blocks[block] = {
          region: colIndex,
          status: visible,
          color: color,
          open: open
        }
      }
    });
  });
 
  // Encode JSON
  blocks = JSON.stringify(blocks);
  
  $.ajax({
    url: Drupal.settings.basePath + '?q=homebox/js/save',
    type: "POST",
    cache: "false",
    dataType: "json",
    data: {name: name, blocks: blocks},
    success: function() {
      $('#homebox-save-message').dialog('close');
      $('#homebox-changes-made').hide();
      
      if (save) {
        // If a block was passed in, save it as a
        // custom block after ajax success.
        Drupal.homebox.addItemAjax(name, save); 
      }
    },
    error: function() {
      $('#homebox-save-message').html('<span style="color:red;">' + Drupal.t('Save failed. Please refresh page.') + '</span>');
    }
  });
};

/*
 * Edit a custom item
 * 
 * @param block
 *   The block ID being edited
 */
Drupal.homebox.editItem = function(block) {
  var title = $('#homebox-edit-form-title').val().stripTags();
  var content = $('#homebox-edit-form-content').val();
  
  // Make sure both fields are supplied
  if (!title || !content) {
    $('#homebox-edit-form-status').show();
    $('#homebox-edit-form-status').html(Drupal.t('All fields are required.'));
    return;
  }
  
  // Alter block ID to match block class
  block = block.replace('_', '-');
  
  // Convert newlines to HTML
  content = content.newlineToHTML();
  
  // Replace block title with input
  $('#homebox-block-' + block).find('.portlet-title').html(title);
  $('#homebox-block-' + block).find('.portlet-content').html(content);
  
  // Clear form and close dialog
  $('#homebox-edit-form-status').hide();
  $('#homebox-edit-form-title').val('');
  $('#homebox-edit-form-content').val('');
	$('#homebox-edit-form').dialog('close');
  
  // Equalize columns
  Drupal.homebox.equalizeColumnsHeights($columns);
};

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

// Strip all tags from a string
String.prototype.stripTags = function() {
   return this.replace(/<([^>]+)>/g,'');
};

// Replace newline characters with HTML breakrules
String.prototype.newlineToHTML = function() {
  return this.replace(/\r?\n|\r/g, "<br />");
};

// Replace HTML breakfules with newline characters
String.prototype.HTMLtoNewline = function() {
  return this.replace(/<br>|<br\/>|<br \/>/gi, "\n");
};
