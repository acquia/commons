Drupal.behaviors.fbss_comments = function (context) {
  var ctxt = $(context);
  // The "Comment" link when there are no comments. Reveals the textarea and save button.
  ctxt.find('.fbss-comments-show-comment-form').one('click', function() {
    $(this).hide();
    var f = $('#'+ this.id +' + div');
    f.show();
    var sid = this.id.split('-').pop();
    f.find('.fbss-comments-replace-'+ sid +'-inner').show();
    f.find('.fbss-comments-textarea').focus();
    return false;
  });
  // The "Comment" link when there are comments. Reveals the textarea and save button.
  ctxt.find('.fbss-comments-show-comment-form-inner').one('click', function() {
    $(this).hide();
    var sid = this.id.split('-').pop();
    $(this).parents('form').find('.fbss-comments-replace-'+ sid +'-inner').show();
    $(this).parents('form').find('.fbss-comments-textarea').focus();
    return false;
  });
  // The "Show all X comments" link when there are fewer than 10 comments. Reveals the hidden comments.
  ctxt.find('a.fbss-comments-show-comments').one('click', function() {
    $(this).hide();
    $('#'+ this.id +' ~ div.fbss-comments-hide').show();
    return false;
  });
  // Hide things we're not ready to show yet.
  ctxt.find('.fbss-comments-hide').hide();
  // Show things we're not ready to hide yet.
  ctxt.find('.fbss-comments-show-comment-form, .fbss-comments-show-comment-form-inner, .fbss-comments-show-comments').show();
  ctxt.find('.fbss-comments-show-comments').css('display', 'block');
  // Disable the save button at first.
  ctxt.find('.fbss-comments-submit').attr('disabled', true);
  // Disable the save button after saving a comment.
  ctxt.find('.fbss-comments-comment-form').bind('ahah_success', function() {
    $(this).find('.fbss-comments-submit').attr('disabled', true);
  });
  // Enable the save button if there is text in the textarea.
  ctxt.find('.fbss-comments-textarea').keypress(function(key) {
    var th = $(this);
    setTimeout(function() {
      if (th.val().length > 0) {
        th.parents('form').find('input').attr('disabled', false);
      }
      else {
        th.parents('form').find('input').attr('disabled', true);
      }
    }, 10);
  });
  // Modal Frame integration.
  if (Drupal.modalFrame) {
    ctxt.find('.fbss-comments-edit-delete a').click(function(event) {
      event.preventDefault();
      var sid = $(this).parents('form').attr('id').split('-').pop();
      var th = $(this);
      var handle = function() {
        $.get('index.php?q=fbss_comments/js/modalframe/'+ sid, function(data) {
          th.parents('.fbss-comments').replaceWith($(data));
          Drupal.attachBehaviors($(data));
        });
      };
      Drupal.modalFrame.open({url: $(this).attr('href'), onSubmit: handle});
    });
  }
  if ($.fn.autogrow) {
    // jQuery Autogrow plugin integration.
    // $('.fbss-comments-textarea').autogrow({expandTolerance: 2});
  }
}
