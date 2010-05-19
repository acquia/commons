// $Id: modal.js,v 1.17.2.5 2010/01/22 06:48:08 merlinofchaos Exp $
/**
 * @file
 *
 * Implement a modal form.
 *
 * @see modal.inc for documentation.
 *
 * This javascript relies on the CTools ajax responder.
 */

(function ($) {
  // Make sure our objects are defined.
  Drupal.CTools = Drupal.CTools || {};
  Drupal.CTools.Modal = Drupal.CTools.Modal || {};

  /**
   * Display the modal
   */
  Drupal.CTools.Modal.show = function() {
    var resize = function(e) {
      // For reasons I do not understand, when creating the modal the context must be
      // Drupal.CTools.Modal.modal but otherwise the context must be more than that.
      var context = e ? document : Drupal.CTools.Modal.modal;
      $('div.ctools-modal-content', context).css({
        'width': $(window).width() * .8 + 'px',
        'height': $(window).height() * .8 + 'px'
      });
      $('div.ctools-modal-content .modal-content', context).css({
        'width': ($(window).width() * .8 - 25) + 'px',
        'height': ($(window).height() * .8 - 35) + 'px'
      });
    }

    if (!Drupal.CTools.Modal.modal) {
      Drupal.CTools.Modal.modal = $(Drupal.theme('CToolsModalDialog'));
      $(window).bind('resize', resize);
    }

    resize();
    $('span.modal-title', Drupal.CTools.Modal.modal).html(Drupal.t('Loading...'));
    var opts = {
      // @todo this should be elsewhere.
      opacity: '.55',
      background: '#fff'
    };

    Drupal.CTools.Modal.modalContent(Drupal.CTools.Modal.modal, opts);
    $('#modalContent .modal-content').html(Drupal.theme('CToolsModalThrobber'));
  };

  /**
   * Hide the modal
   */
  Drupal.CTools.Modal.dismiss = function() {
    if (Drupal.CTools.Modal.modal) {
      Drupal.CTools.Modal.unmodalContent(Drupal.CTools.Modal.modal);
    }
  };

  /**
   * Provide the HTML to create the modal dialog.
   */
  Drupal.theme.prototype.CToolsModalDialog = function () {
    var html = ''
    html += '  <div id="ctools-modal">'
    html += '    <div class="ctools-modal-content">' // panels-modal-content
    html += '      <div class="modal-header">';
    html += '        <a class="close" href="#">';
    html +=            Drupal.settings.CToolsModal.closeText + Drupal.settings.CToolsModal.closeImage;
    html += '        </a>';
    html += '        <span id="modal-title" class="modal-title">&nbsp;</span>';
    html += '      </div>';
    html += '      <div id="modal-content" class="modal-content">';
    html += '      </div>';
    html += '    </div>';
    html += '  </div>';

    return html;
  }

  /**
   * Provide the HTML to create the throbber.
   */
  Drupal.theme.prototype.CToolsModalThrobber = function () {
    var html = '';
    html += '  <div id="modal-throbber">';
    html += '    <div class="modal-throbber-wrapper">';
    html +=        Drupal.settings.CToolsModal.throbber;
    html += '    </div>';
    html += '  </div>';

    return html;
  };

  /**
   * Generic replacement click handler to open the modal with the destination
   * specified by the href of the link.
   */
  Drupal.CTools.Modal.clickAjaxLink = function() {
    // show the empty dialog right away.
    Drupal.CTools.Modal.show();
    Drupal.CTools.AJAX.clickAJAXLink.apply(this);
    if (!$(this).hasClass('ctools-ajaxing')) {
      Drupal.CTools.Modal.dismiss();
    }

    return false;
  };

  /**
   * Generic replacement click handler to open the modal with the destination
   * specified by the href of the link.
   */
  Drupal.CTools.Modal.clickAjaxButton = function() {
    if ($(this).hasClass('ctools-ajaxing')) {
      return false;
    }

    Drupal.CTools.Modal.show();
    Drupal.CTools.AJAX.clickAJAXButton.apply(this);
    if (!$(this).hasClass('ctools-ajaxing')) {
      Drupal.CTools.Modal.dismiss();
    }

    return false;
  };

  /**
   * Submit responder to do an AJAX submit on all modal forms.
   */
  Drupal.CTools.Modal.submitAjaxForm = function() {
    if ($(this).hasClass('ctools-ajaxing')) {
      return false;
    }

    url = $(this).attr('action');
    $(this).addClass('ctools-ajaxing');
    var object = $(this);
    try {
      url.replace('/nojs/', '/ajax/');

      var ajaxOptions = {
        type: 'POST',
        url: url,
        data: { 'js': 1, 'ctools_ajax': 1 },
        global: true,
        success: Drupal.CTools.AJAX.respond,
        error: function(xhr) {
          Drupal.CTools.AJAX.handleErrors(xhr, url);
        },
        complete: function() {
          object.removeClass('ctools-ajaxing');
          $('.ctools-ajaxing', object).removeClass('ctools-ajaxing');
        },
        dataType: 'json'
      };

      // If the form requires uploads, use an iframe instead and add data to
      // the submit to support this and use the proper response.
      if ($(this).attr('enctype') == 'multipart/form-data') {
        $(this).append('<input type="hidden" name="ctools_multipart" value="1">');
        ajaxIframeOptions = {
          success: Drupal.CTools.AJAX.iFrameJsonRespond,
          iframe: true
        };
        ajaxOptions = $.extend(ajaxOptions, ajaxIframeOptions);
      }

      $(this).ajaxSubmit(ajaxOptions);
    }
    catch (err) {
      alert("An error occurred while attempting to process " + url);
      $(this).removeClass('ctools-ajaxing');
      $('div.ctools-ajaxing', this).remove();
      return false;
    }
    return false;
  }

  /**
   * Wrapper for handling JSON responses from an iframe submission
   */
  Drupal.CTools.AJAX.iFrameJsonRespond = function(data) {
    var myJson = eval(data);
    Drupal.CTools.AJAX.respond(myJson);
  }

  /**
   * Bind links that will open modals to the appropriate function.
   */
  Drupal.behaviors.CToolsModal = function(context) {
    // Bind links
    $('a.ctools-use-modal:not(.ctools-use-modal-processed)', context)
      .addClass('ctools-use-modal-processed')
      .click(Drupal.CTools.Modal.clickAjaxLink);

    // Bind buttons
    $('input.ctools-use-modal:not(.ctools-use-modal-processed), button.ctools-use-modal:not(.ctools-use-modal-processed)', context)
      .addClass('ctools-use-modal-processed')
      .click(Drupal.CTools.Modal.clickAjaxButton);

    if ($(context).attr('id') == 'modal-content') {
      // Bind submit links in the modal form.
      $('form:not(.ctools-use-modal-processed)', context)
        .addClass('ctools-use-modal-processed')
        .submit(Drupal.CTools.Modal.submitAjaxForm);
      // add click handlers so that we can tell which button was clicked,
      // because the AJAX submit does not set the values properly.

      $('input[type="submit"]:not(.ctools-use-modal-processed), button:not(.ctools-use-modal-processed)', context)
        .addClass('ctools-use-modal-processed')
        .click(function() {
          if (Drupal.autocompleteSubmit && !Drupal.autocompleteSubmit()) {
            return false;
          }

          // Make sure it knows our button.
          if (!$(this.form).hasClass('ctools-ajaxing')) {
            this.form.clk = this;
            $(this).after('<div class="ctools-ajaxing"> &nbsp; </div>');
          }
        });

    }
  };

  // The following are implementations of AJAX responder commands.

  /**
   * AJAX responder command to place HTML within the modal.
   */
  Drupal.CTools.AJAX.commands.modal_display = function(command) {
    $('#modal-title').html(command.title);
    $('#modal-content').html(command.output);
    Drupal.attachBehaviors($('#modal-content'));
  }

  /**
   * AJAX responder command to dismiss the modal.
   */
  Drupal.CTools.AJAX.commands.modal_dismiss = function(command) {
    Drupal.CTools.Modal.dismiss();
  }

  /**
   * Display loading
   */
  Drupal.CTools.AJAX.commands.modal_loading = function(command) {
    Drupal.CTools.AJAX.commands.modal_display({
      output: Drupal.theme('CToolsModalThrobber'),
      title: Drupal.t('Loading...')
    });
  }
})(jQuery);
