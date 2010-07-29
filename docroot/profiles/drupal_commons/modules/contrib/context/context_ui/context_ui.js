// $Id: context_ui.js,v 1.3.2.5.2.3 2010/03/20 10:28:07 darthsteven Exp $

if (typeof(Drupal) == "undefined" || !Drupal.context_ui) {
  Drupal.context_ui = {};

  // Helper function for retrieving a link hash
  Drupal.context_ui.getHash = function(href) {
    var start = href.lastIndexOf('#') + 1;
    var hash = href.substr(start);
    return hash;
  }

  // Sets populates the hidden region element
  Drupal.context_ui.regionblocks = function (region) {
    var serialized = '';
    $('table#context-ui-region-' + region + ' tr').each(function() {
      if (serialized == '') {
        serialized = $(this).attr('id');
      }
      else {
        serialized = serialized +","+ $(this).attr('id');
      }
    });
    $("input#edit-block-regions-"+ region).val(serialized);
  }
}

Drupal.behaviors.context_ui = function(context) {
  // Tabledrag
  for (var base in Drupal.settings.tableDrag) {
    if (!$('#' + base + '.contextui-processed', context).size()) {
      // Add additional tabledrag event handlers to populate our
      // hidden fields
      $('#' + base).bind('mouseup', function(event) {
        var region = $(this).attr('id').substr(18); // 18 == strlen('context-ui-region-');
        Drupal.context_ui.regionblocks(region);
        return;
      });
      $('#' + base).addClass('contextui-processed');
    }
  }

  // Block removers
  $('table#context-ui-blocks a.remove:not(.contextui-processed)').each(function() {
    // Add click handler
    $(this).click(function() {
      // Retrieve region & block id from row
      var region = $(this).parents('table').attr('id').substr(18);
      var bid = $(this).parents('tr').eq(0).remove().attr('id');

      // Return this block to the selector
      $('div.context-ui-block-selector input[value='+bid+']').attr('checked', 0).parents('div.form-item').eq(0).show();

      // Set region value
      Drupal.context_ui.regionblocks(region);
      return false;
    });

    // Hide blocks in the selector that are enabled
    var bid = $(this).parents('tr').eq(0).attr('id');
    $('div.context-ui-block-selector input[value='+bid+']').parents('div.form-item').eq(0).hide();
    $(this).addClass('contextui-processed');
  });

  // Display the item widget
  $('table#context-ui-items td.display a:not(.contextui-processed)').each(function() {
    $(this).click(function() {
      var hash = Drupal.context_ui.getHash($(this).attr('href'));

      $('table#context-ui-items td.display a').removeClass('selected');
      $(this).addClass('selected');

      $("table#context-ui-items td.widget div.buttons").show();
      $("table#context-ui-items td.widget div.widget").removeClass('active');
      $("table#context-ui-items td.widget div#widget-"+ hash).addClass('active');

      return false;
    });
    $(this).addClass('contextui-processed');
  });

  // Add blocks to a region
  $('table#context-ui-blocks td.display a:not(.contextui-processed)').each(function() {
    $(this).click(function() {
      var hash = Drupal.context_ui.getHash($(this).attr('href'));
      var region = hash.replace(/_/g, '-');

      var selected = $("div.context-ui-block-selector input:checked");
      if (selected.size() > 0) {
        selected.each(function() {
          if (!$(this).attr('disabled')) {
            // create new block markup
            var block = document.createElement('tr');

            // get the label and remove the checkbox
            var clonedlabel = $(this).parents('div.form-item').eq(0).hide().children('label').clone();
            var checkboxitem = clonedlabel.find('input');
            checkboxitem.replaceWith(' ');
            var text = clonedlabel.html();

            $(block).attr('id', $(this).attr('value')).addClass('draggable');
            $(block).html("<td>"+ text + "<input class='block-weight' /></td><td><a href='' class='remove'>X</a></td>");

            // add block item to region
            var base = "context-ui-region-"+ region
            Drupal.tableDrag[base].makeDraggable(block);
            $('table#'+base).append(block);
            Drupal.attachBehaviors($('table#'+base));

            Drupal.context_ui.regionblocks(region);
            $(this).removeAttr('checked');
          }
        });
      }

      return false;
    });
    $(this).addClass('contextui-processed');
  });

  // Update item display
  $("table#context-ui-items td.widget input:checkbox, table#context-ui-items td.widget input:radio").each(function() {
    if (!$(this).is('.contextui-processed')) {
      $(this).change(function() {
        var parent = $(this).parents('div.widget');
        var hash = parent.attr('id').substr(7); // 7 == strlen('widget-');
        var list = '';
        $('input[checked]', parent).each(function() {
          var label = $(this).parents('label').text();
          list = list + "<li>"+ label +"</li>";
        });
        $("table#context-ui-items td.display #display-"+ hash).html(list);
      });
      $(this).addClass('contextui-processed');
    }
  });

  // Select widgets get their own logic
  $("table#context-ui-items td.widget select").each(function() {
    if (!$(this).is('.contextui-processed')) {
      $(this).change(function() {
        var parent = $(this).parents('div.widget');
        var hash = parent.attr('id').substr(7); // 7 == strlen('widget-');
        var list = '';
        $('option:selected', this).each(function() {
          var label = $(this).val();
          list = list + "<li>"+ label +"</li>";
        });
        $("table#context-ui-items td.display #display-"+ hash).html(list);
      });
      $(this).addClass('contextui-processed');
    }
  });
}
