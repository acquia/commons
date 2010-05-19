// $Id: imce_extras.js,v 1.2.2.4 2009/06/24 12:18:48 ufku Exp $
//This pack implemets: keyboard shortcuts, file sorting, resize bars, and inline thumbnail preview.

//add onload hook. unshift to make sure it runs first after imce loads.
imce.hooks.load.unshift(function () {
  imce.NW = imce.el('navigation-wrapper'), imce.BW = imce.el('browse-wrapper');
  imce.LPW = imce.el('log-prv-wrapper'), imce.LW = imce.el('log-wrapper');
  //add scale calculator for resizing.
  $('#edit-width, #edit-height').focus(function () {
    var fid, r, w, isW, val;
    if (fid = imce.vars.prvfid) {
      isW = this.id == 'edit-width', val =  imce.el(isW ? 'edit-height' : 'edit-width').value*1;
      if (val && (w = imce.isImage(fid)) && (r = imce.fids[fid].cells[3].innerHTML*1 / w))
        this.value = Math.round(isW ? val/r : val*r);
    }
  });
  //$(imce.tree[imce.conf.dir].a).focus();//focus on the active directory branch
});

/**************** SHORTCUTS ********************/

imce.initiateShortcuts = function () {
  $(imce.NW).attr('tabindex', '0').keydown(function (e) {
    if (F = imce.dirKeys['k'+ e.keyCode]) return F(e);
  });
  $(imce.FLW).attr('tabindex', '0').keydown(function (e) {
    if (F = imce.fileKeys['k'+ e.keyCode]) return F(e);
  }).focus();
};

//shortcut key-function pairs for directories
imce.dirKeys = {
  k35: function (e) {//end-home. select first or last dir
    var L = imce.tree['.'].li;
    if (e.keyCode == 35) while (imce.hasC(L, 'expanded')) L = L.lastChild.lastChild;
    $(L.childNodes[1]).click().focus();
  },
  k37: function (e) {//left-right. collapse-expand directories.(right may also move focus on files)
    var L, B = imce.tree[imce.conf.dir], right = e.keyCode == 39;
    if (B.ul && (right ^ imce.hasC(L = B.li, 'expanded')) ) $(L.firstChild).click();
    else if (right) $(imce.FLW).focus();
  },
  k38: function (e) {//up. select the previous directory
    var B = imce.tree[imce.conf.dir];
    if (L = B.li.previousSibling) {
      while (imce.hasC(L, 'expanded')) L = L.lastChild.lastChild;
      $(L.childNodes[1]).click().focus();
    }
    else if ((L = B.li.parentNode.parentNode) && L.tagName == 'LI') $(L.childNodes[1]).click().focus();
  },
  k40: function (e) {//down. select the next directory
    var B = imce.tree[imce.conf.dir], L = B.li, U = B.ul;
    if (U && imce.hasC(L, 'expanded')) $(U.firstChild.childNodes[1]).click().focus();
    else do {if (L.nextSibling) return $(L.nextSibling.childNodes[1]).click().focus();
    }while ((L = L.parentNode.parentNode).tagName == 'LI');
  }
};
//add equal keys
imce.dirKeys.k36 = imce.dirKeys.k35;
imce.dirKeys.k39 = imce.dirKeys.k37;

//shortcut key-function pairs for files
imce.fileKeys = {
  k38: function (e) {//up-down. select previous-next row
    var fid = imce.lastFid(), i = fid ? imce.fids[fid].rowIndex+e.keyCode-39 : 0;
    imce.fileClick(imce.findex[i], e.ctrlKey, e.shiftKey);
  },
  k35: function (e) {//end-home. select first or last row
    imce.fileClick(imce.findex[e.keyCode == 35 ? imce.findex.length-1 : 0], e.ctrlKey, e.shiftKey);
  },
  k13: function (e) {//enter-insert. send file to external app.
    imce.send(imce.vars.prvfid);
    return false;
  },
  k37: function (e) {//left. focus on directories
    $(imce.tree[imce.conf.dir].a).focus();
  },
  k65: function (e) {//ctrl+A to select all
    if (e.ctrlKey && imce.findex.length) {
      var fid = imce.findex[0].id;
      imce.selected[fid] ? (imce.vars.lastfid = fid) : imce.fileSelect(fid);//select first row
      imce.fileClick(imce.findex[imce.findex.length-1], false, true);//shift+click last row
      return false;
    }
  }
};
//add equal keys
imce.fileKeys.k40 = imce.fileKeys.k38;
imce.fileKeys.k36 = imce.fileKeys.k35;
imce.fileKeys.k45 = imce.fileKeys.k13;
//add default operation keys. delete, R(esize), T(humbnails), U(pload)
$.each({k46: 'delete', k82: 'resize', k84: 'thumb', k85: 'upload'}, function (k, op) {
  imce.fileKeys[k] = function (e) {
    if (imce.ops[op] && !imce.ops[op].disabled) imce.opClick(op);
  };
});

/**************** SORTING ********************/

//prepare column sorting
imce.initiateSorting = function() {
  //add cache hook. cache the old directory's sort settings before the new one replaces it.
  imce.hooks.cache.push(function (cache, newdir) {
    cache.cid = imce.vars.cid, cache.dsc = imce.vars.dsc;
  });
  //add navigation hook. refresh sorting after the new directory content is loaded.
  imce.hooks.navigate.push(function (data, olddir, cached) {
    cached ? imce.updateSortState(data.cid, data.dsc) : imce.firstSort();
  });
  imce.vars.cid = imce.cookie('icid')*1;
  imce.vars.dsc = imce.cookie('idsc')*1;
  imce.cols = imce.el('file-header').rows[0].cells;
  $(imce.cols).click(function () {imce.columnSort(this.cellIndex, imce.hasC(this, 'asc'));});
  $(window).unload(function() {imce.cookie('icid', imce.vars.cid); imce.cookie('idsc', imce.vars.dsc ? 1 : 0);});
  imce.firstSort();
};

//sort the list for the first time
imce.firstSort = function() {
  imce.columnSort(imce.vars.cid, imce.vars.dsc);
};

//sort file list according to column index.
imce.columnSort = function(cid, dsc) {
  if (imce.findex.length < 2) return;
  if (cid == imce.vars.cid && dsc != imce.vars.dsc) {
    imce.findex.reverse();
  }
  else {
    var func = 'sort'+ (cid == 0 ? 'Str' : 'Num') + (dsc ? 'Dsc' : 'Asc');
    var prop = cid == 2 || cid == 3 ? 'innerHTML' : 'id';
    //sort rows
    imce.findex.sort(cid ? function(r1, r2) {return imce[func](r1.cells[cid][prop], r2.cells[cid][prop])} : function(r1, r2) {return imce[func](r1.id, r2.id)});
  }
  //insert sorted rows
  for (var row, i=0; row = imce.findex[i]; i++) {
    imce.tbody.appendChild(row);
  }
  imce.updateSortState(cid, dsc);
};

//update column states
imce.updateSortState = function(cid, dsc) {
  $(imce.cols[imce.vars.cid]).removeClass(imce.vars.dsc ? 'desc' : 'asc');
  $(imce.cols[cid]).addClass(dsc ? 'desc' : 'asc');
  imce.vars.cid = cid;
  imce.vars.dsc = dsc;
};

//sorters
imce.sortStrAsc = function(a, b) {return a.toLowerCase() < b.toLowerCase() ? -1 : 1;};
imce.sortStrDsc = function(a, b) {return imce.sortStrAsc(b, a);};
imce.sortNumAsc = function(a, b) {return a-b;};
imce.sortNumDsc = function(a, b) {return b-a};

/**************** RESIZE-BARS  ********************/

//set resizers for resizable areas and recall previous dimensions
imce.initiateResizeBars = function () {
  imce.setResizer('navigation-resizer', 'X', 'navigation-wrapper', null, 1);
  imce.setResizer('log-resizer', 'X', 'log-wrapper', null, 1);
  imce.setResizer('browse-resizer', 'Y', 'browse-wrapper', 'log-prv-wrapper', 50, imce.resizeList);
  imce.setResizer('content-resizer', 'Y', 'resizable-content', null, 150, imce.resizeRows);
  imce.recallDimensions();
  $(window).unload(function() {
    imce.cookie('ih1', $(imce.BW).height());
    imce.cookie('ih2', $(imce.LPW).height());
    imce.cookie('iw1', Math.max($(imce.NW).width(), 1));
    imce.cookie('iw2', Math.max($(imce.LW).width(), 1));
  });
};

//set a resize bar
imce.setResizer = function (resizer, axis, area1, area2, Min, endF) {
  var O = axis == 'X' ? {pos: 'pageX', func: 'width'} : {pos: 'pageY', func: 'height'};
  var Min = Min || 0;
  $(imce.el(resizer)).mousedown(function(e) {
    var pos = e[O.pos];
    var end = start = $(imce.el(area1))[O.func]();
    var Max = area2 ? (start + $(imce.el(area2))[O.func]()) : 1200;
    $(document).mousemove(doDrag).mouseup(endDrag);
    function doDrag(e) {
      end = Math.min(Max - Min, Math.max(start + e[O.pos] - pos, Min));
      $(imce.el(area1))[O.func](end);
      if (area2) $(imce.el(area2))[O.func](Max - end);
      return false;
    }
    function endDrag(e) {
      $(document).unbind("mousemove", doDrag).unbind("mouseup", endDrag);
      if (endF) endF(start, end, Max);
    }
  });
};

//set height file-list area
imce.resizeList = function(start, end, Max) {
  var el = $(imce.FLW), h = el.height() + end - start;
  el.height(h < 1 ? 1 : h);
};

//set heights of browse and log-prv areas.
imce.resizeRows = function(start, end, Max) {
  var el = $(imce.BW), h = el.height();
  var diff = end - start, r = h / start, d = Math.round(diff * r), h1 = Math.max(h + d, 50);
  el.height(h1);
  $(imce.LPW).height(end - h1 - $(imce.el('browse-resizer')).height() - 1);
  imce.resizeList(h, h1);
};

//get area dimensions of the last session from the cookie
imce.recallDimensions = function() {
  if (h1 = imce.cookie('ih1')*1) {
    var h2 = imce.cookie('ih2')*1, w1 = imce.cookie('iw1')*1, w2 = imce.cookie('iw2')*1;
    var el = $(imce.BW), h = el.height(), w = el.width();
    $(imce.NW).width(Math.min(w1, w-5));
    $(imce.LW).width(Math.min(w2, w-5));
    el.height(h1);
    imce.resizeList(h, h1);
    $(imce.LPW).height(h2);
  }
};

//cookie get & set
imce.cookie = function (name, value) {
  if (typeof(value) == 'undefined') {//get
    return unescape((document.cookie.match(new RegExp('(^|;) *'+ name +'=([^;]*)(;|$)')) || ['', '', ''])[2]);
  }
  document.cookie = name +'='+ escape(value) +'; expires='+ (new Date(new Date()*1 + 30*86400000)).toGMTString() +'; path=/';//set
};

//view thumbnails(smaller than tMaxW x tMaxH) inside the rows.
imce.thumbRow = function (row) {
  var h, w = row.cells[2].innerHTML*1;
  if (!w || imce.vars.tMaxW < w || imce.vars.tMaxH < (h = row.cells[3].innerHTML*1)) return;
  var prvH = h, prvW = w;
  if (imce.vars.prvW < w || imce.vars.prvH < h) {
    if (h < w) {
      prvW = imce.vars.prvW;
      prvH = prvW*h/w;
    }
    else {
      prvH = imce.vars.prvH;
      prvW = prvH*w/h;
    }
  }
  var img = new Image(prvW, prvH);
  img.src = imce.getURL(row.id);
  var cell = row.cells[0];
  cell.insertBefore(img, cell.firstChild);
};