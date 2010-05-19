// $Id: imce_set_app.js,v 1.3.2.9 2009/09/21 14:26:39 ufku Exp $
//When imce url contains &app=appName|fileProperty1@correspondingFieldId1|fileProperty2@correspondingFieldId2|...
//the specified fields are filled with the specified properties of the selected file.

var appFields = {}, appWindow = (top.appiFrm||window).opener || parent;

//execute when imce loads.
imce.hooks.load.push(function(win) {
  var data = decodeURIComponent(location.href.substr(location.href.lastIndexOf('app=')+4)).split('|');
  var appName = data.shift();
  //extract fields
  for (var i in data) {
    var arr = data[i].split('@');
    appFields[arr[0]] = arr[1];
  }
  //run custom onload function if available.
  if (appFields['onload'] && $.isFunction(appWindow[appFields['onload']])) {
    appWindow[appFields['onload']](win);
    delete appFields['onload'];
  }
  //alternative sytax for some servers that ban URLs containing onload keyword.
  else if (appFields['imceload'] && $.isFunction(appWindow[appFields['imceload']])) {
    appWindow[appFields['imceload']](win);
    delete appFields['imceload'];
  }
  //set custom sendto function. appFinish is the default.
  var sendtoFunc = appFields['url'] ? appFinish : false;
  //check sendto@funcName syntax in URL
  if (appFields['sendto'] && $.isFunction(appWindow[appFields['sendto']])) {
    sendtoFunc = appWindow[appFields['sendto']];
    delete appFields['sendto'];
  }
  //check windowname+ImceFinish. old method
  else if (win.name && $.isFunction(appWindow[win.name +'ImceFinish'])) {
    sendtoFunc = appWindow[win.name +'ImceFinish'];
  }
  //highlight file
  if (appFields['url']) {
    if (appFields['url'].indexOf(',') > -1) {//support multiple url fields url@field1,field2..
      var arr = appFields['url'].split(',');
      for (var i in arr) {
        if ($('#'+ arr[i], appWindow.document).size()) {
          appFields['url'] = arr[i];
          break;
        }
      }
    }
    var filename = $('#'+ appFields['url'], appWindow.document).val();
    imce.highlight(filename.substr(filename.lastIndexOf('/')+1));
  }
  //set send to
  if (sendtoFunc) {
    imce.setSendTo(Drupal.t('Send to @app', {'@app': appName}), sendtoFunc);
  }
});

//sendTo function
var appFinish = function(file, win) {
  var doc = $(appWindow.document);
  for (var i in appFields) {
    doc.find('#'+ appFields[i]).val(file[i]);
  }
  if (appFields['url']) {
    try{
      doc.find('#'+ appFields['url']).blur().change().focus();
    }catch(e){
      try{
        doc.find('#'+ appFields['url']).trigger('onblur').trigger('onchange').trigger('onfocus');//inline events for IE
      }catch(e){}
    }
  }
  appWindow.focus();
  win.close();
};
