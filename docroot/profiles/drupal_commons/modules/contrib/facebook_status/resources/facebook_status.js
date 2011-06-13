var fbss_allowClickRefresh = true;
var fbss_refreshIDs;
Drupal.behaviors.facebookStatus = function (context) {
  var initialLoad = false;
  // Drupal passes document as context on page load.
  if (context == document) {
    initialLoad = true;
  }
  // Make sure we can run context.find().
  var ctxt = $(context);
  facebook_status_submit_disabled = false;
  var $facebook_status_field = ctxt.find('.facebook-status-text:first');
  var facebook_status_original_value = $facebook_status_field.val();
  var fbss_maxlen = Drupal.settings.facebook_status.maxlength;
  var fbss_hidelen = parseInt(Drupal.settings.facebook_status.hideLength);
  if (fbss_refreshIDs == undefined) {
    fbss_refreshIDs = Drupal.settings.facebook_status.refreshIDs;
  }
  if ($.fn.autogrow && $facebook_status_field) {
    // jQuery Autogrow plugin integration.
    $facebook_status_field.autogrow({expandTolerance: 2});
  }
  if (Drupal.settings.facebook_status.autofocus) {
    $facebook_status_field.focus();
  }
  if (Drupal.settings.facebook_status.noautoclear || Drupal.settings.facebook_status.autofocus) {
    if ($facebook_status_field.val() && $facebook_status_field.val().length != 0 && fbss_maxlen != 0) {
      fbss_print_remaining(fbss_maxlen - facebook_status_original_value.length, $facebook_status_field.parents('.facebook-status-update').find('.facebook-status-chars'));
    }
  }
  else {
    $.each(ctxt.find('.facebook-status-text-main'), function(i, val) {
      $(this).addClass('facebook-status-faded');
    });
    // Clear the status field the first time it's in focus if it hasn't been changed.
    ctxt.find('.facebook-status-text-main').one('focus', function() {
      var th = $(this);
      if (th.val() == facebook_status_original_value) {
        th.val('');
        if (fbss_maxlen != 0) {
          fbss_print_remaining(fbss_maxlen, th.parents('.facebook-status-update').find('.facebook-status-chars'));
        }
      }
      th.removeClass('facebook-status-faded');
    });
  }
  // Truncate long status messages.
  function fbss_truncate(i, val) {
    var th = $(val);
    var oldMsgText = th.html();
    var oldMsgLen = oldMsgText.length;
    if (oldMsgLen > fbss_hidelen) {
      var newMsgText =
        oldMsgText.substring(0, fbss_hidelen - 1) +
        '<span class="facebook-status-hellip">&hellip;&nbsp;</span><a class="facebook-status-readmore-toggle active">' +
        Drupal.t('Read more') +
        '</a><span class="facebook-status-readmore">' +
        oldMsgText.substring(fbss_hidelen - 1) +
        '</span>';
      th.html(newMsgText);
      th.find('.facebook-status-readmore').hide();
      th.find('.facebook-status-readmore-toggle').click(function(e) {
        var thi = $(this);
        e.preventDefault();
        var pa = thi.parents('.facebook-status-content');
        thi.hide();
        pa.find('.facebook-status-hellip').hide();
        pa.find('.facebook-status-readmore').show();
      });
    }
  }
  if (fbss_hidelen > 0) {
    ctxt.find('.facebook-status-content').each(fbss_truncate);
  }
  // Modal Frame integration.
  if (Drupal.modalFrame) {
    ctxt.find('.facebook-status-edit a, .facebook-status-delete a').click(function(event) {
      event.preventDefault();
      Drupal.modalFrame.open({url: $(this).attr('href'), onSubmit: fbss_refresh});
    });
  }
  // Don't show multiple loading symbols if a status is submitted via AHAH after an attached view changes pages via AJAX.
  ctxt.find('#facebook-status-replace').unbind('ahah_success');
  // React when a status is submitted.
  ctxt.find('#facebook-status-replace').bind('ahah_success', function(context) {
    if ($(context.target).html() != $(this).html()) {
      return;
    }
    fbss_refresh();
  });
  // On document load, add a refresh link where applicable.
  if (initialLoad && fbss_refreshIDs && Drupal.settings.facebook_status.refreshLink) {
    var loaded = {};
    $.each(fbss_refreshIDs, function(i, val) {
      if (val && val != undefined) {
        if ($.trim(val) && loaded[val] !== true) {
          loaded[val] = true;
          var element = $(val);
          element.wrap('<div></div>');
          var rlink = '<a href="'+ window.location.href +'">'+ Drupal.t('Refresh') +'</a>';
          element.parent().after('<div class="facebook-status-refresh-link">'+ rlink +'</div>');
        }
      }
    });
  }
  // Refresh views appropriately.
  ctxt.find('.facebook-status-refresh-link a').click(function() {
    if (fbss_allowClickRefresh) {
      fbss_allowClickRefresh = false;
      setTimeout('fbss_allowRefresh()', 2000);
      $(this).after('<div class="fbss-remove-me ahah-progress ahah-progress-throbber"><div class="throbber">&nbsp;</div></div>');
      fbss_refresh();
    }
    return false;
  });
  // Restore original status text if the field is blank and the slider is clicked.
  ctxt.find('.facebook-status-intro').click(function() {
    var th = $(this);
    var te = th.parents('.facebook-status-update').find('.facebook-status-text');
    if (te.val() == '') {
      te.val(facebook_status_original_value);
      if (fbss_maxlen != 0) {
        fbss_print_remaining(fbss_maxlen - facebook_status_original_value.length, th.parents('.facebook-status-update').find('.facebook-status-chars'));
      }
    }
  });
  if (fbss_maxlen != 0) {
    // Count remaining characters.
    ctxt.find('.facebook-status-text').bind('keydown keyup', function(fbss_key) {
      var th = $(this);
      var thCC = th.parents('.facebook-status-update').find('.facebook-status-chars');
      var fbss_remaining = fbss_maxlen - th.val().length;
      fbss_print_remaining(fbss_remaining, thCC);
    });
  }
}
// Change remaining character count.
function fbss_print_remaining(fbss_remaining, where) {
  if (fbss_remaining >= 0) {
    where.html(Drupal.formatPlural(fbss_remaining, '1 character left', '@count characters left', {}));
    if (facebook_status_submit_disabled) {
      $('.facebook-status-submit').attr('disabled', false);
      facebook_status_submit_disabled = false;
    }
  }
  else if (Drupal.settings.facebook_status.maxlength != 0) {
    where.html('<span class="facebook-status-negative">'+ Drupal.formatPlural(Math.abs(fbss_remaining), '-1 character left', '-@count characters left', {}) +'</span>');
    if (!facebook_status_submit_disabled) {
      $('.facebook-status-submit').attr('disabled', true);
      facebook_status_submit_disabled = true;
    }
  }
}
// Disallow refreshing too often or double-clicking the Refresh link.
function fbss_allowRefresh() {
  fbss_allowClickRefresh = !fbss_allowClickRefresh;
}
// Refresh parts of the page.
function fbss_refresh() {
  if (Drupal.heartbeat) {
    Drupal.heartbeat.pollMessages();
  }
  // Refresh elements by re-loading the current page and replacing the old version with the updated version.
  var loaded = {};
  if (fbss_refreshIDs && fbss_refreshIDs != undefined) {
    var loaded2 = {};
    $.each(fbss_refreshIDs, function(i, val) {
      if (val && val != undefined) {
        if ($.trim(val) && loaded2[val] !== true) {
          loaded2[val] = true;
          var element = $(val);
          element.before('<div class="fbss-remove-me ahah-progress ahah-progress-throbber" style="display: block; clear: both; float: none;"><div class="throbber">&nbsp;</div></div>');
        }
      }
    });
    var location = window.location.pathname +'?';
    // Build the relative URL with query parameters.
    var query = window.location.search.substring(1);
    if ($.trim(query) != "") {
      location += query +'&';
    }
    // IE will cache the result unless we add an identifier (in this case, the time).
    $.get(location +"ts="+ (new Date()).getTime(), function(data, textStatus) {
      // From load() in jQuery source. We already have the scripts we need.
      var new_data = data.replace(/<script(.|\s)*?\/script>/g, "");
      if (Drupal.settings.fbss_comments && Drupal.settings.fbss_comments.ahah_enabled) {
        // EVIL BLACK MAGIC - updates Drupal.settings.ahah to reflect AHAH forms that are about to be loaded
        var settings_script = data.match(/(<script[\s\S]*?Drupal\.settings\,\s)((.|\s)*?)\/script>/)[2];
        eval('Drupal.settings2 = '+ settings_script.substring(0, settings_script.length-15));
        $.extend(Drupal.settings.ahah, Drupal.settings2.ahah);
      }
      // From ahah.js. Apparently Safari crashes with just $().
      var new_content = $('<div></div>').html(new_data);
      if (textStatus != 'error' && new_content) {
        // Replace relevant content in the viewport with the updated version.
        $.each(fbss_refreshIDs, function(i, val) {
          if (val && val != undefined) {
            if ($.trim(val) != '' && loaded[val] !== true) {
              var element = $(val);
              var insert = new_content.find(val);
              // If a refreshID is found multiple times on the same page, replace each one sequentially.
              if (insert.length && insert.length > 0 && element.length && element.length >= insert.length) {
                $.each(insert, function(j, v) {
                  v = $(v);
                  var el = $(element[j]);
                  // Don't bother replacing anything if the replacement region hasn't changed.
                  if (v.get() != el.get()) {
                    el.replaceWith(v);
                    Drupal.attachBehaviors(v);
                  }
                });
              }
              loaded[val] = true;
            }
          }
        });
      }
      $('.fbss-remove-me').remove();
    });
  }
  else {
    $('.fbss-remove-me').remove();
  }
}
