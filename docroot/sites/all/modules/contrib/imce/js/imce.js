// $Id: imce.js,v 1.15.2.10 2009/07/09 19:29:09 ufku Exp $

//Global container.
var imce = {tree: {}, findex: [], fids: {}, selected: {}, selcount: 0, ops: {}, cache: {}, urlId: {},
vars: {previewImages: 1, cache: 1},
hooks: {load: [], list: [], navigate: [], cache: []},

//initiate imce.
initiate: function() {
  imce.conf = Drupal.settings.imce || {};
  if (imce.conf.error != false) return;
  imce.FLW = imce.el('file-list-wrapper');
  imce.prepareMsgs();//process initial status messages
  imce.initiateTree();//build directory tree
  imce.hooks.list.unshift(imce.processRow);//set the default list-hook.
  imce.initiateList();//process file list
  imce.initiateOps();//prepare operation tabs
  imce.refreshOps();
  if (window['imceOnLoad']) imceOnLoad(window);
  imce.invoke('load', window);//run functions set by external applications.
},

/**************** DIRECTORIES ********************/

//process navigation tree
initiateTree: function() {
  $('#navigation-tree li').each(function(i) {
    var a = this.firstChild;
    a.firstChild.data = imce.decode(a.firstChild.data);
    var branch = imce.tree[a.title] = {'a': a, li: this, ul: this.lastChild.tagName == 'UL' ? this.lastChild : null};
    if (a.href) imce.dirClickable(branch);
    imce.dirCollapsible(branch);
  });
},

//Add a dir to the tree under parent
dirAdd: function(dir, parent, clickable) {
  if (imce.tree[dir]) return clickable ? imce.dirClickable(imce.tree[dir]) : imce.tree[dir];
  var parent = parent || imce.tree['.'];
  parent.ul = parent.ul ? parent.ul : parent.li.appendChild(document.createElement('ul'));
  var branch = imce.dirCreate(dir, imce.decode(dir.substr(dir.lastIndexOf('/')+1)), clickable);
  parent.ul.appendChild(branch.li);
  return branch;
},

//create list item for navigation tree
dirCreate: function(dir, text, clickable) {
  if (imce.tree[dir]) return imce.tree[dir];
  var branch = imce.tree[dir] = {li: document.createElement('li'), a: document.createElement('a')};
  $(branch.a).addClass('folder').text(text).attr('title', dir).appendTo(branch.li);
  imce.dirCollapsible(branch);
  return clickable ? imce.dirClickable(branch) : branch;
},

//change currently active directory
dirActivate: function(dir) {
  if (dir != imce.conf.dir) {
    if (imce.tree[imce.conf.dir]){
      $(imce.tree[imce.conf.dir].a).removeClass('active');
    }
    $(imce.tree[dir].a).addClass('active');
    imce.conf.dir = dir;
  }
  return imce.tree[imce.conf.dir];
},

//make a dir accessible
dirClickable: function(branch) {
  if (branch.clkbl) return branch;
  $(branch.a).attr('href', '#').removeClass('disabled').click(function() {imce.navigate(this.title); return false;});
  branch.clkbl = true;
  return branch;
},

//sub-directories expand-collapse ability
dirCollapsible: function (branch) {
  if (branch.clpsbl) return branch;
  $(document.createElement('span')).addClass('expander').html('&nbsp; &nbsp;').click(function() {
    if (branch.ul) {
      $(branch.ul).toggle();
      $(branch.li).toggleClass('expanded');
    }
    else if (branch.clkbl){
      $(branch.a).click();
    }
  }).prependTo(branch.li);
  branch.clpsbl = true;
  return branch;
},

//update navigation tree after getting subdirectories.
dirSubdirs: function(dir, subdirs) {
  var branch = imce.tree[dir];
  if (subdirs && subdirs.length) {
    var prefix = dir == '.' ? '' : dir +'/';
    for (var i in subdirs) {//add subdirectories
      imce.dirAdd(prefix + subdirs[i], branch, true);
    }
    $(branch.li).removeClass('leaf').addClass('expanded');
    $(branch.ul).show();
  }
  else if (!branch.ul){//no subdirs->leaf
    $(branch.li).removeClass('expanded').addClass('leaf');
  }
},

/**************** FILES ********************/

//process file list
initiateList: function(cached) {
  var L = imce.hooks.list, dir = imce.conf.dir, token = {'%dir':  dir == '.' ? $(imce.tree['.'].a).text() : imce.decode(dir)}
  imce.findex = [], imce.fids = {}, imce.selected = {}, imce.selcount = 0, imce.vars.lastfid = null;
  imce.tbody = imce.el('file-list').tBodies[0];
  if (imce.tbody.rows.length) {
    for (var row, i = 0; row = imce.tbody.rows[i]; i++) {
      var fid = row.id;
      imce.findex[i] = imce.fids[fid] = row;
      if (cached) {
        if (imce.hasC(row, 'selected')) {
          imce.selected[imce.vars.lastfid = fid] = row;
          imce.selcount++;
        }
      }
      else {
        for (var func, j = 0; func = L[j]; j++) func(row);//invoke list-hook
      }
    }
    imce.setMessage(Drupal.t('Directory %dir is loaded.', token));
  }
  else if (imce.conf.perm.browse) imce.setMessage(Drupal.t('Directory %dir is empty.', token), 'warning');
  else imce.setMessage(Drupal.t('File browsing is disabled in directory %dir.', token), 'error');
},

//add a file to the list. (having properties name,size,formatted size,width,height,date,formatted date)
fileAdd: function(file) {
  var row, fid = file.name, i = imce.findex.length, attr = ['name', 'size', 'width', 'height', 'date'];
  if (!(row = imce.fids[fid])) {
    row = imce.findex[i] = imce.fids[fid] = imce.tbody.insertRow(i);
    for (var i in attr) row.insertCell(i).className = attr[i];
  }
  row.cells[0].innerHTML = row.id = fid;
  row.cells[1].innerHTML = file.fsize; row.cells[1].id = file.size;
  row.cells[2].innerHTML = file.width;
  row.cells[3].innerHTML = file.height;
  row.cells[4].innerHTML = file.fdate; row.cells[4].id = file.date;
  imce.invoke('list', row);
  if (imce.vars.prvfid == fid) imce.setPreview(fid);
  if (file.id) imce.urlId[imce.getURL(fid)] = file.id;
},

//remove a file from the list
fileRemove: function(fid) {
  if (!(row = imce.fids[fid])) return;
  imce.fileDeSelect(fid);
  imce.findex.splice(row.rowIndex, 1);
  $(row).remove();
  delete imce.fids[fid];
  if (imce.vars.prvfid == fid) imce.setPreview();
},

//return a file object containing all properties.
fileGet: function (fid) {
  var row = imce.fids[fid];
  var url = imce.getURL(fid);
  return row ? {
    name: imce.decode(fid),
    url: url,
    size: row.cells[1].innerHTML,
    bytes: row.cells[1].id * 1,
    width: row.cells[2].innerHTML * 1,
    height: row.cells[3].innerHTML * 1,
    date: row.cells[4].innerHTML,
    time: row.cells[4].id * 1,
    id: imce.urlId[url] || 0, //file id for newly uploaded files
    relpath: (imce.conf.dir == '.' ? '' : imce.conf.dir +'/') + fid //rawurlencoded path relative to file directory path.
  } : null;
},

//simulate row click. selection-highlighting
fileClick: function(row, ctrl, shft) {
  if (!row) return;
  var fid = typeof(row) == 'string' ? row : row.id;
  if (ctrl || fid == imce.vars.prvfid) {
    imce.fileToggleSelect(fid);
  }
  else if (shft) {
    var last = imce.lastFid();
    var start = last ? imce.fids[last].rowIndex : -1;
    var end = imce.fids[fid].rowIndex;
    var step = start > end ? -1 : 1;
    while (start != end) {
      start += step;
      imce.fileSelect(imce.findex[start].id);
    }
  }
  else {
    for (var fname in imce.selected) {
      imce.fileDeSelect(fname);
    }
    imce.fileSelect(fid);
  }
  //set preview
  imce.setPreview(imce.selcount == 1 ? imce.lastFid() : null);
},

//file select/deselect functions
fileSelect: function (fid) {
  if (imce.selected[fid] || !imce.fids[fid]) return;
  imce.selected[fid] = imce.fids[imce.vars.lastfid=fid];
  $(imce.selected[fid]).addClass('selected');
  imce.selcount++;
},
fileDeSelect: function (fid) {
  if (!imce.selected[fid] || !imce.fids[fid]) return;
  if (imce.vars.lastfid == fid) imce.vars.lastfid = null;
  $(imce.selected[fid]).removeClass('selected');
  delete imce.selected[fid];
  imce.selcount--;
},
fileToggleSelect: function (fid) {
  imce['file'+ (imce.selected[fid] ? 'De' : '') +'Select'](fid);
},

/**************** OPERATIONS ********************/

//process file operation form and create operation tabs.
initiateOps: function() {
  imce.setHtmlOps();
  imce.setUploadOp();//upload
  imce.setFileOps();//thumb, delete, resize
},

//process existing html ops.
setHtmlOps: function () {
  $('#ops-list>li').each(function() {
    var name = this.id.substr(8);
    var Op = imce.ops[name] = {div: imce.el('op-content-'+ name), li: imce.el('op-item-'+ name)};
    Op.a = Op.li.firstChild;
    Op.title = Op.a.innerHTML;
    $(Op.a).click(function() {imce.opClick(name); return false;});
  });
},

//convert upload form to an op.
setUploadOp: function () {
  if (!imce.el('imce-upload-form')) return;
  var form = $(imce.el('imce-upload-form'));
  form.find('fieldset').each(function() {//clean up fieldsets
    this.removeChild(this.firstChild);
    $(this).after(this.childNodes);
  }).remove();
  form.ajaxForm(imce.uploadSettings());//set ajax
  imce.opAdd({name: 'upload', title: Drupal.t('Upload'), content: form});//add op
},

//convert fileop form submit buttons to ops.
setFileOps: function () {
  $(imce.el('edit-filenames-wrapper')).remove();
  $('#imce-fileop-form fieldset').each(function() {//remove fieldsets
    var sbmt = $('input:submit', this);
    if (!sbmt.size()) return;
    var Op = {name: sbmt.attr('id').substr(5)};
    var func = function() {imce.fopSubmit(Op.name); return false;};
    sbmt.click(func);
    Op.title = this.firstChild.innerHTML;
    this.removeChild(this.firstChild);
    Op.name == 'delete' ? (Op.func = func) : (Op.content = this.childNodes);
    imce.opAdd(Op);
  }).remove();
  imce.vars.opform = $(imce.el('imce-fileop-form')).serialize();//serialize remaining parts.
},

//refresh ops states. enable/disable
refreshOps: function() {
  for (var p in imce.conf.perm) {
    if (imce.conf.perm[p]) imce.opEnable(p);
    else imce.opDisable(p);
  }
},

//add a new file operation
opAdd: function (op) {
  var name = op.name || ('op-'+ $('#ops-list>li').size());
  var Op = imce.ops[name] = {title: op.title||'Untitled'};
  if (op.content) {
    Op.div = document.createElement('div');
    $(Op.div).attr('id', 'op-content-'+ name).addClass('op-content').append(op.content).appendTo(imce.el('op-contents'));
  }
  Op.a = document.createElement('a');
  Op.li = document.createElement('li');
  $(Op.a).attr({href: '#', 'name': name}).html(op.title).click(function() {imce.opClick(this.name); return false;});
  $(Op.li).attr('id', 'op-item-'+ op.name).append(Op.a).appendTo(imce.el('ops-list'));
  Op.func = op.func || function(){};
  return Op;
},

//perform op click
opClick: function(name) {
  if (!(Op = imce.ops[name]) || Op.disabled) return imce.setMessage(Drupal.t('You can\'t perform this operation.'), 'error');
  if (Op.div) {
    if (imce.vars.op) {
      var oldOp = imce.ops[imce.vars.op];
      $(oldOp.div).slideUp();
      $(oldOp.li).removeClass('active');
      oldOp.func(false);
      if (imce.vars.op == name) {
        imce.vars.op = null;
        return false;
      }
    }
    $(Op.div).slideDown('normal', function(){setTimeout("$('input:first', imce.ops[imce.vars.op].div).focus()", 10)});
    $(Op.li).addClass('active');
    imce.vars.op = name;
  }
  Op.func(true);
  return true;
},

//enable a file operation
opEnable: function(name) {
  if ((Op = imce.ops[name]) && Op.disabled) {
    Op.disabled = false;
    $(Op.li).show();
  }
},

//disable a file operation
opDisable: function(name) {
  if ((Op = imce.ops[name]) && !Op.disabled) {
    Op.disabled = true;
    $(Op.li).hide();
    if (imce.vars.op == name) {
      imce.vars.op = null;
      $(Op.div).hide();
      $(Op.li).removeClass('active');
    }
  }
},

/**************** AJAX OPERATIONS  ********************/

//navigate to dir
navigate: function(dir) {
  if (imce.vars.navbusy || (dir == imce.conf.dir && !confirm(Drupal.t('Do you want to refresh the current directory?')))) return;
  var cache = imce.vars.cache && dir != imce.conf.dir;
  var set = imce.navSet(dir, cache);
  if (cache && imce.cache[dir]) {//load from the cache
    set.success({data: imce.cache[dir]});
    set.complete();
  }
  else $.ajax(set);//live load
},
//ajax navigation settings
navSet: function (dir, cache) {
  $(imce.tree[dir].li).addClass('loading');
  imce.vars.navbusy = dir;
  return {url: imce.ajaxURL('navigate', dir),
  type: 'GET',
  dataType: 'json',
  success: function(response) {
    if (response.data && !response.data.error) {
      if (cache) imce.navCache(imce.conf.dir, dir);//cache the current dir
      imce.navUpdate(response.data, dir);
    }
    imce.processResponse(response);
  },
  complete: function () {
    $(imce.tree[dir].li).removeClass('loading');
    imce.vars.navbusy = null;
  }
  };
},

//update directory using the given data
navUpdate: function(data, dir) {
  var cached = data == imce.cache[dir], olddir = imce.conf.dir;
  if (cached) data.files.id = 'file-list';
  $(imce.FLW).html(data.files);
  imce.dirActivate(dir);
  imce.dirSubdirs(dir, data.subdirectories);
  $.extend(imce.conf.perm, data.perm);
  imce.refreshOps();
  imce.initiateList(cached);
  imce.setPreview(imce.selcount == 1 ? imce.lastFid() : null);
  imce.invoke('navigate', data, olddir, cached);
},

//set cache
navCache: function (dir, newdir) {
  var C = imce.cache[dir] = {'dir': dir, files: imce.el('file-list'), dirsize: imce.el('dir-size').innerHTML, perm: $.extend({}, imce.conf.perm)};
  C.files.id = 'cached-list-'+ dir;
  imce.el('forms-wrapper').appendChild(C.files);
  imce.invoke('cache', C, newdir);
},

/**************** UPLOAD  ********************/
//validate upload form
uploadValidate: function (data, form, options) {
  var path = data[0].value;
  if (!path) return false;
  if (imce.conf.extensions != '*') {
    var ext = path.substr(path.lastIndexOf('.') + 1);
    if ((' '+ imce.conf.extensions +' ').indexOf(' '+ ext.toLowerCase() +' ') == -1) {
      return imce.setMessage(Drupal.t('Only files with the following extensions are allowed: %files-allowed.', {'%files-allowed': imce.conf.extensions}), 'error');
    }
  }
  var sep = path.indexOf('/') == -1 ? '\\' : '/';
  imce.setMessage(Drupal.t('Uploading %filename...', {'%filename': path.substr(path.lastIndexOf(sep) + 1)}));
  options.url = imce.ajaxURL('upload');//make url contain current dir.
  imce.fopLoading('upload', true);
  return true;
},

//settings for upload
uploadSettings: function () {
  return {beforeSubmit: imce.uploadValidate, success: function (response) {imce.processResponse(Drupal.parseJson(response));}, complete: function () {imce.fopLoading('upload', false);}, resetForm: true};
},

/**************** FILE OPS  ********************/
//validate default ops(delete, thumb, resize)
fopValidate: function(fop) {
  if (!imce.validateSelCount(1, imce.conf.filenum)) return false;
  switch (fop) {
    case 'delete':
      return confirm(Drupal.t('Delete selected files?'));
    case 'thumb':
      if (!$('input:checked', imce.ops['thumb'].div).size()) {
        return imce.setMessage(Drupal.t('Please select a thumbnail.'), 'error');
      }
      return imce.validateImage();
    case 'resize':
      var w = imce.el('edit-width').value, h = imce.el('edit-height').value;
      var maxDim = imce.conf.dimensions.split('x');
      var maxW = maxDim[0]*1, maxH = maxW ? maxDim[1]*1 : 0;
      if (w.search(/^[1-9][0-9]*$/) == -1 || h.search(/^[1-9][0-9]*$/) == -1 || (maxW && (maxW < w*1 || maxH < h*1))) {
        return imce.setMessage(Drupal.t('Please specify dimensions within the allowed range that is from 1x1 to @dimensions.', {'@dimensions': maxW ? imce.conf.dimensions : Drupal.t('unlimited')}), 'error');
      }
      return imce.validateImage();
  }

  var func = fop +'OpValidate';
  if (imce[func]) return imce[func](fop);
  return true;
},

//submit wrapper for default ops
fopSubmit: function(fop) {
  switch (fop) {
    case 'thumb': case 'delete': case 'resize':  return imce.commonSubmit(fop);
  }
  var func = fop +'OpSubmit';
  if (imce[func]) return imce[func](fop);
},

//common submit function shared by default ops
commonSubmit: function(fop) {
  if (!imce.fopValidate(fop)) return false;
  imce.fopLoading(fop, true);
  $.ajax(imce.fopSettings(fop));
},

//settings for default file operations
fopSettings: function (fop) {
  return {url: imce.ajaxURL(fop), type: 'POST', dataType: 'json', success: imce.processResponse, complete: function (response) {imce.fopLoading(fop, false);}, data: imce.vars.opform +'&filenames='+ imce.serialNames() +'&jsop='+ fop + (imce.ops[fop].div ? '&'+ $('input', imce.ops[fop].div).serialize() : '')};
},

//toggle loading state
fopLoading: function(fop, state) {
  var el = imce.el('edit-'+ fop), func = state ? 'addClass' : 'removeClass'
  if (el) {
    $(el)[func]('loading').attr('disabled', state);
  }
  else {
    $(imce.ops[fop].li)[func]('loading');
    imce.ops[fop].disabled = state;
  }
},

/**************** PREVIEW & SEND TO  ********************/

//preview a file.
setPreview: function (fid) {
  var row, html = '';
  imce.vars.prvfid = fid;
  if (fid && (row = imce.fids[fid])) {
    var width = row.cells[2].innerHTML * 1;
    html = imce.vars.previewImages && width ? imce.imgHtml(fid, width, row.cells[3].innerHTML) : imce.decode(fid);
    html = '<a href="#" onclick="imce.send(\''+ fid +'\'); return false;" title="'+ (imce.vars.prvtitle||'') +'">'+ html +'</a>';
  }
  imce.el('file-preview').innerHTML = html;
},

//default file send function. sends the file to the new window.
send: function (fid) {
  if (fid) window.open(imce.getURL(fid));
},

//add an operation for an external application to which the files are send.
setSendTo: function (title, func) {
  imce.send = function (fid) { if(fid) func(imce.fileGet(fid), window);};
  var opFunc = function () {
    if (imce.selcount != 1) return alert(Drupal.t('Please select a single file.'));
    imce.send(imce.vars.prvfid);
  };
  imce.vars.prvtitle = title;
  return imce.opAdd({'title': title, func: opFunc});
},

/**************** LOG MESSAGES  ********************/

//move initial page messages into log
prepareMsgs: function () {
  var msgs;
  if (msgs = imce.el('imce-messages')) {
    $('>div', msgs).each(function (){
      var type = this.className.split(' ')[1];
      var li = $('>ul li', this);
      if (li.size()) li.each(function () {imce.setMessage(this.innerHTML, type);});
      else imce.setMessage(this.innerHTML, type);
    });
    $(msgs).remove();
  }
  //log clearer
  $(imce.el('log-clearer')).css('display', 'inline').click(function() {$(imce.el('log-wrapper')).empty();return false;});
},

//insert log message
setMessage: function (msg, type) {
  var logs = imce.el('log-wrapper'), div = document.createElement('div');
  div.className = type || 'status';
  div.innerHTML = '<span class="time">'+ imce.logTime() +'</span> ' + msg;
  logs.appendChild(div);
  $(logs).animate({scrollTop: logs.scrollHeight}, 'slow');
  return false;
},

//return time in HH:MM:SS format for log
logTime: function () {
  var t = new Date(), h = t.getHours(), m = t.getMinutes(), s = t.getSeconds();
  return (h < 10 ? '0' : '') + h +':'+ (m < 10 ? '0' : '') + m +':'+ (s < 10 ? '0' : '') + s;
},

/**************** OTHER HELPER FUNCTIONS  ********************/
//invoke hooks
invoke: function (hook) {
  var i, args, func, funcs;
  if ((funcs = imce.hooks[hook]) && funcs.length) {
    (args = $.makeArray(arguments)).shift();
    for (i = 0; func = funcs[i]; i++) func.apply(this, args);
  }
},

//process response
processResponse: function (response) {
  if (response.data) imce.resData(response.data);
  if (response.messages) imce.resMsgs(response.messages);
},
//process response data
resData: function (data) {
  var i, added, removed;
  if (added = data.added) {
    var cnt = imce.findex.length;
    for (i in added) {//add new files or update existing
      imce.fileAdd(added[i]);
    }
    if (added.length == 1) {//if it is a single file operation
      imce.highlight(added[0].name);//highlight
    }
    if (imce.findex.length != cnt) {//if new files added
      $(imce.FLW).animate({scrollTop: imce.FLW.scrollHeight}).focus();//scroll to bottom.
    }
  }
  if (removed = data.removed) for (i in removed) {
    imce.fileRemove(removed[i]);
  }
  imce.conf.dirsize = data.dirsize;
  imce.updateStat();
},
//set response messages
resMsgs: function (msgs) {
  for (var type in msgs) for (var i in msgs[type]) {
    imce.setMessage(msgs[type][i], type);
  }
},

//return img markup
imgHtml: function (fid, width, height) {
  return '<img src="'+ imce.getURL(fid) +'" width="'+ width +'" height="'+ height +'" alt="'+ imce.decode(fid) +'">';
},
//check if the file is an image
isImage: function (fid) {
  return imce.fids[fid].cells[2].innerHTML * 1;
},
//find the first non-image in the selection
getNonImage: function (selected) {
  for (var fid in selected) {
    if (!imce.isImage(fid)) return fid;
  }
  return false;
},
//validate current selection for images
validateImage: function () {
  var nonImg = imce.getNonImage(imce.selected);
  return nonImg ? imce.setMessage(Drupal.t('%filename is not an image.', {'%filename': imce.decode(nonImg)}), 'error') : true;
},
//validate number of selected files
validateSelCount: function (Min, Max) {
  if (Min && imce.selcount < Min) {
    return imce.setMessage(Min == 1 ? Drupal.t('Please select a file.') : Drupal.t('You must select at least %num files.', {'%num': Min}), 'error');
  }
  if (Max && Max < imce.selcount) {
    return imce.setMessage(Drupal.t('You are not allowed to operate on more than %num files.', {'%num': Max}), 'error');
  }
  return true;
},

//update file count and dir size
updateStat: function () {
  imce.el('file-count').innerHTML = imce.findex.length;
  imce.el('dir-size').innerHTML = imce.conf.dirsize;
},
//serialize selected files. return fids with a colon between them
serialNames: function () {
  var str = '';
  for (var fid in imce.selected) {
    str += ':'+ fid;
  }
  return str.substr(1);
},
//get file url. re-encode & and # for mod rewrite
getURL: function (fid) {
  var path = (imce.conf.dir == '.' ? '' : imce.conf.dir +'/') + fid;
  return imce.conf.furl +'/'+ (imce.conf.clean && imce.conf.prvt ? path.replace(/%(23|26)/g, '%25$1') : path);
},
//el. by id
el: function (id) {
  return document.getElementById(id);
},
//find the latest selected fid
lastFid: function () {
  if (imce.vars.lastfid) return imce.vars.lastfid;
  for (var fid in imce.selected);
  return fid;
},
//create ajax url
ajaxURL: function (op, dir) {
  return imce.conf.url + (imce.conf.clean ? '?' :'&') +'jsop='+ op +'&dir='+ (dir||imce.conf.dir);
},
//fast class check
hasC: function (el, name) {
  return el.className && (' '+ el.className +' ').indexOf(' '+ name +' ') != -1;
},
//highlight a single file
highlight: function (fid) {
  if (imce.vars.prvfid) imce.fileClick(imce.vars.prvfid);
  imce.fileClick(fid);
},
//process a row
processRow: function (row) {
  row.cells[0].innerHTML = imce.decode(row.id);
  row.onmousedown = function(e) {var e = e||window.event; imce.fileClick(this, e.ctrlKey, e.shiftKey);};
},
//decode urls. uses unescape. can be overridden to use decodeURIComponent
decode: function (str) {
  return unescape(str);
},
//global ajax error function
ajaxError: function (e, response, settings, thrown) {
  imce.setMessage(Drupal.ahahError(response, settings.url).replace('\n', '<br />'), 'error');
}
};

//initiate
$(document).ready(imce.initiate).ajaxError(imce.ajaxError);