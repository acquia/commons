// $Id: mollom.js,v 1.2.2.11 2010/02/19 05:50:39 dries Exp $

(function ($) {

/**
 * Open Mollom privacy policy link in a new window.
 *
 * Required for valid XHTML Strict markup.
 */
Drupal.behaviors.mollomPrivacy = function (context) {
  $('.mollom-privacy a', context).click(function () {
    this.target = '_blank';
  });
};

/**
 * Attach click event handlers for CAPTCHA links.
 */
Drupal.behaviors.mollomCaptcha = function (context) {
  $('a.mollom-audio-captcha', context).click(getAudioCaptcha);
  $('a.mollom-image-captcha', context).click(getImageCaptcha);
};

function getAudioCaptcha() {
  var context = $(this).parents('form');

  // Extract the Mollom session ID from the form:
  var mollomSessionId = $('input.mollom-session-id', context).val();

  // Retrieve an audio CAPTCHA:
  $.getJSON(Drupal.settings.basePath + 'mollom/captcha/audio/' + mollomSessionId,
    function (data) {
      if (!(data && data.content)) {
        return;
      }
      // Inject new audio CAPTCHA.
      $('.mollom-captcha-content', context).parent().html(data.content);
      // Update session id.
      $('input.mollom-session-id', context).val(data.session_id);
      // Add an onclick-event handler for the new link.
      $('a.mollom-image-captcha', context).click(getImageCaptcha);
    }
  );
  return false;
}

function getImageCaptcha() {
  var context = $(this).parents('form');

  // Extract the Mollom session ID from the form:
  var mollomSessionId = $('input.mollom-session-id', context).val();

  // Retrieve an image CAPTCHA:
  $.getJSON(Drupal.settings.basePath + 'mollom/captcha/image/' + mollomSessionId,
    function (data) {
      if (!(data && data.content)) {
        return;
      }
      // Inject new image CAPTCHA.
      $('.mollom-captcha-content', context).parent().html(data.content);
      // Update session id.
      $('input.mollom-session-id', context).val(data.session_id);
      // Add an onclick-event handler for the new link.
      $('a.mollom-audio-captcha', context).click(getAudioCaptcha);
    }
  );
  return false;
}

})(jQuery);
