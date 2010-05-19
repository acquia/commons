// $Id: ajax-responder.js,v 1.18.2.6 2010/01/22 06:48:08 merlinofchaos Exp $
/**
 * @file
 *
 * CTools flexible AJAX responder object.
 */

(function ($) {
  Drupal.CTools = Drupal.CTools || {};
  Drupal.CTools.AJAX = Drupal.CTools.AJAX || {};
  Drupal.CTools.AJAX.commands = Drupal.CTools.AJAX.commands || {};

  /**
   * Success callback for an ajax request.
   *
   * This function expects to receive a packet of data from a JSON object
   * which is essentially a list of commands. Each commands must have a
   * 'command' setting and this setting must resolve to a function in the
   * Drupal.CTools.AJAX.commands space.
   */
  Drupal.CTools.AJAX.respond = function(data) {
    for (i in data) {
      if (data[i]['command'] && Drupal.CTools.AJAX.commands[data[i]['command']]) {
        Drupal.CTools.AJAX.commands[data[i]['command']](data[i]);
      }
    }
  };

  /**
   * Generic replacement click handler to open the modal with the destination
   * specified by the href of the link.
   */
  Drupal.CTools.AJAX.clickAJAXLink = function() {
    if ($(this).hasClass('ctools-ajaxing')) {
      return false;
    }

    var url = $(this).attr('href');
    var object = $(this);
    $(this).addClass('ctools-ajaxing');
    try {
      url = url.replace(/nojs/g, 'ajax');
      $.ajax({
        type: "POST",
        url: url,
        data: { 'js': 1, 'ctools_ajax': 1 },
        global: true,
        success: Drupal.CTools.AJAX.respond,
        error: function(xhr) {
          Drupal.CTools.AJAX.handleErrors(xhr, url);
        },
        complete: function() {
          object.removeClass('ctools-ajaxing');
        },
        dataType: 'json'
      });
    }
    catch (err) {
      alert("An error occurred while attempting to process " + url);
      $(this).removeClass('ctools-ajaxing');
      return false;
    }

    return false;
  };

  /**
   * Generic replacement click handler to open the modal with the destination
   * specified by the href of the link.
   */
  Drupal.CTools.AJAX.clickAJAXButton = function() {
    if ($(this).hasClass('ctools-ajaxing')) {
      return false;
    }

    // Put our button in.
    this.form.clk = this;

    var url = Drupal.CTools.AJAX.findURL(this);
    $(this).addClass('ctools-ajaxing');
    var object = $(this);
    try {
      if (url) {
        url = url.replace('/nojs/', '/ajax/');
        $.ajax({
          type: "POST",
          url: url,
          data: { 'js': 1, 'ctools_ajax': 1 },
          global: true,
          success: Drupal.CTools.AJAX.respond,
          error: function(xhr) {
            Drupal.CTools.AJAX.handleErrors(xhr, url);
          },
          complete: function() {
            object.removeClass('ctools-ajaxing');
          },
          dataType: 'json'
        });
      }
      else {
        var form = this.form;
        url = $(form).attr('action');
        url = url.replace('/nojs/', '/ajax/');
        $(form).ajaxSubmit({
          type: "POST",
          url: url,
          data: { 'js': 1, 'ctools_ajax': 1 },
          global: true,
          success: Drupal.CTools.AJAX.respond,
          error: function(xhr) {
            Drupal.CTools.AJAX.handleErrors(xhr, url);
          },
          complete: function() {
            object.removeClass('ctools-ajaxing');
          },
          dataType: 'json'
        });
      }
    }
    catch (err) {
      alert("An error occurred while attempting to process " + url);
      $(this).removeClass('ctools-ajaxing');
      return false;
    }
    return false;
  };

  /**
   * Display error in a more fashion way
   */
  Drupal.CTools.AJAX.handleErrors = function(xhr, path) {
    var error_text = '';

    if ((xhr.status == 500 && xhr.responseText) || xhr.status == 200) {
      error_text = xhr.responseText;

      // Replace all &lt; and &gt; by < and >
      error_text = error_text.replace("/&(lt|gt);/g", function (m, p) {
        return (p == "lt")? "<" : ">";
      });

      // Now, replace all html tags by empty spaces
      error_text = error_text.replace(/<("[^"]*"|'[^']*'|[^'">])*>/gi,"");

      // Fix end lines
      error_text = error_text.replace(/[\n]+\s+/g,"\n");
    }
    else if (xhr.status == 500) {
      error_text = xhr.status + ': ' + Drupal.t("Internal server error. Please see server or PHP logs for error information.");
    }
    else {
      error_text = xhr.status + ': ' + xhr.statusText;
    }

    alert(Drupal.t("An error occurred at @path.\n\nError Description: @error", {'@path': path, '@error': error_text}));
  }

  /**
   * Generic replacement for change handler to execute ajax method.
   */
  Drupal.CTools.AJAX.changeAJAX = function () {
    if ($(this).hasClass('ctools-ajaxing')) {
      return false;
    }

    var url = Drupal.CTools.AJAX.findURL(this);
    $(this).addClass('ctools-ajaxing');
    var object = $(this);
    var form_id = $(object).parents('form').get(0).id;
    try {
      if (url) {
        url = url.replace('/nojs/', '/ajax/');
        $.ajax({
          type: "POST",
          url: url,
          data: {'ctools_changed': $(this).val(), 'js': 1, 'ctools_ajax': 1 },
          global: true,
          success: Drupal.CTools.AJAX.respond,
          error: function(xhr) {
            Drupal.CTools.AJAX.handleErrors(xhr, url);
          },
          complete: function() {
            object.removeClass('ctools-ajaxing');
            if ($(object).hasClass('ctools-ajax-submit-onchange')) {
              $('form#' + form_id).submit();
            }
          },
          dataType: 'json'
        });
      }
      else {
        if ($(object).hasClass('ctools-ajax-submit-onchange')) {
          $('form#' + form_id).submit();
        }
        return false;
      }
    }
    catch (err) {
      alert("An error occurred while attempting to process " + url);
      $(this).removeClass('ctools-ajaxing');
      return false;
    }
    return false;
  };

  /**
   * Find a URL for an AJAX button.
   *
   * The URL for this gadget will be composed of the values of items by
   * taking the ID of this item and adding -url and looking for that
   * class. They need to be in the form in order since we will
   * concat them all together using '/'.
   */
  Drupal.CTools.AJAX.findURL = function(item) {
    var url = '';
    var url_class = '.' + $(item).attr('id') + '-url';
    $(url_class).each(
      function() {
        if (url && $(this).val()) {
          url += '/';
        }
        url += $(this).val();
      });
    return url;
  };

  Drupal.CTools.AJAX.commands.prepend = function(data) {
    $(data.selector).prepend(data.data);
    Drupal.attachBehaviors($(data.selector));
  };

  Drupal.CTools.AJAX.commands.append = function(data) {
    $(data.selector).append(data.data);
    Drupal.attachBehaviors($(data.selector));
  };

  Drupal.CTools.AJAX.commands.replace = function(data) {
    $(data.selector).replaceWith(data.data);
    Drupal.attachBehaviors($(data.selector));
  };

  Drupal.CTools.AJAX.commands.after = function(data) {
    var object = $(data.data);
    $(data.selector).after(object);
    Drupal.attachBehaviors(object);
  };

  Drupal.CTools.AJAX.commands.before = function(data) {
    var object = $(data.data);
    $(data.selector).before(object);
    Drupal.attachBehaviors(object);
  };

  Drupal.CTools.AJAX.commands.html = function(data) {
    $(data.selector).html(data.data);
    Drupal.attachBehaviors($(data.selector));
  };

  Drupal.CTools.AJAX.commands.remove = function(data) {
    $(data.selector).remove();
  };

  Drupal.CTools.AJAX.commands.changed = function(data) {
    if (!$(data.selector).hasClass('changed')) {
      $(data.selector).addClass('changed');
      if (data.star) {
        $(data.selector).find(data.star).append(' <span class="star">*</span> ');
      }
    }
  };

  Drupal.CTools.AJAX.commands.alert = function(data) {
    alert(data.text, data.title);
  };

  Drupal.CTools.AJAX.commands.css = function(data) {
  /*
    if (data.selector && data.selector.contains('* html ')) {
      // This indicates an IE hack and we should only do it if we are IE.
      if (!jQuery.browser.msie) {
        return;
      }
      data.selector = data.selector.replace('* html ', '');
    }
  */
    $(data.selector).css(data.argument);
  };

  Drupal.CTools.AJAX.commands.settings = function(data) {
    $.extend(Drupal.settings, data.argument);
  };

  Drupal.CTools.AJAX.commands.data = function(data) {
    $(data.selector).data(data.name, data.value);
  };

  Drupal.CTools.AJAX.commands.attr = function(data) {
    $(data.selector).attr(data.name, data.value);
  };

  Drupal.CTools.AJAX.commands.restripe = function(data) {
    // :even and :odd are reversed because jquery counts from 0 and
    // we count from 1, so we're out of sync.
    $('tbody tr:not(:hidden)', $(data.selector))
      .removeClass('even')
      .removeClass('odd')
      .filter(':even')
        .addClass('odd')
      .end()
      .filter(':odd')
        .addClass('even');
  };

  Drupal.CTools.AJAX.commands.redirect = function(data) {
    location.href = data.url;
  };

  Drupal.CTools.AJAX.commands.reload = function(data) {
    location.reload();
  };

  Drupal.CTools.AJAX.commands.submit = function(data) {
    $(data.selector).submit();
  }


  /**
   * Bind links that will open modals to the appropriate function.
   */
  Drupal.behaviors.CToolsAJAX = function(context) {
    // Bind links
    $('a.ctools-use-ajax:not(.ctools-use-ajax-processed)', context)
      .addClass('ctools-use-ajax-processed')
      .click(Drupal.CTools.AJAX.clickAJAXLink);

    // Bind buttons
    $('input.ctools-use-ajax:not(.ctools-use-ajax-processed), button.ctools-use-ajax:not(.ctools-use-ajax-processed)', context)
      .addClass('ctools-use-ajax-processed')
      .click(Drupal.CTools.AJAX.clickAJAXButton);

    // Bind select
    $('select, input:text, input:radio, input:checkbox', context)
       .filter('.ctools-use-ajax-onchange:not(.ctools-use-ajax-processed)')
       .addClass('ctools-use-ajax-processed')
       .change(Drupal.CTools.AJAX.changeAJAX);
  };
})(jQuery);
