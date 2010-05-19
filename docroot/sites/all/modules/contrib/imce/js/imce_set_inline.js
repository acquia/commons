// $Id: imce_set_inline.js,v 1.3.2.5 2009/09/21 14:26:39 ufku Exp $

var imceInline = {};

imceInline.initiate = function() {
  $('div.imce-inline-wrapper').show().find('a').click(function() {
    var i = this.name.indexOf('-IMCE-');
    imceInline.activeTextarea = $('#'+ this.name.substr(0, i)).get(0);
    imceInline.activeType = this.name.substr(i+6);
 
    if (typeof imceInline.pop == 'undefined' || imceInline.pop.closed) {
      imceInline.pop = window.open(this.href + (this.href.indexOf('?') < 0 ? '?' : '&') +'app=nomatter|imceload@imceInlineImceLoad', '', 'width='+ 760 +',height='+ 560 +',resizable=1');
    }

    imceInline.pop.focus();
    return false;
  });
};

//function to be executed when imce loads.
function imceInlineImceLoad(win) {
  win.imce.setSendTo(Drupal.t('Send to @app', {'@app': Drupal.t('textarea')}), imceInline.insert);
  $(window).unload(function() {
    if (imceInline.pop && !imceInline.pop.closed) imceInline.pop.close();
  });
};

//insert html at cursor position
imceInline.insertAtCursor = function (field, txt, type) {
  field.focus();
  if ('undefined' != typeof(field.selectionStart)) {
    if (type == 'link' && (field.selectionEnd-field.selectionStart)) {
      txt = txt.split('">')[0] +'">'+ field.value.substring(field.selectionStart, field.selectionEnd) +'</a>';
    }
    field.value = field.value.substring(0, field.selectionStart) + txt + field.value.substring(field.selectionEnd, field.value.length);
  }
  else if (document.selection) {
    if (type == 'link' && document.selection.createRange().text.length) {
      txt = txt.split('">')[0] +'">'+ document.selection.createRange().text +'</a>';
    }
    document.selection.createRange().text = txt;
  }
  else {
    field.value += txt;
  }
};

//sendTo function
imceInline.insert = function (file, win) {
  var type = imceInline.activeType == 'link' ? 'link' : (file.width ? 'image' : 'link');
  var html = type == 'image' ? ('<img src="'+ file.url +'" width="'+ file.width +'" height="'+ file.height +'" alt="'+ file.name +'" />') : ('<a href="'+ file.url +'">'+ file.name +' ('+ file.size +')</a>');
  imceInline.activeType = null;
  win.blur();
  imceInline.insertAtCursor(imceInline.activeTextarea, html, type);
};

$(document).ready(imceInline.initiate);
