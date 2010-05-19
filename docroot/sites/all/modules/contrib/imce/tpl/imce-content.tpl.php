<?php
// $Id: imce-content.tpl.php,v 1.8.2.5 2009/09/21 12:10:12 ufku Exp $
$imce =& $imce_ref['imce'];//keep this line.
$directory = drupal_get_path('module', 'imce');

//main css file.
drupal_add_css($directory .'/css/imce-content.css');

//Browsing enhancements. Keyboard shortcuts, file sorting, resizebars, and inline thumbnail preview. (Safe to delete)
drupal_add_js($directory .'/js/imce_extras.js');
drupal_add_js('
  imce.hooks.load.push(imce.initiateShortcuts);//shortcuts for directories and files
  imce.hooks.load.push(imce.initiateSorting);//file sorting
  imce.hooks.load.push(imce.initiateResizeBars);//area resizing bars
  imce.hooks.list.push(imce.thumbRow); $.extend(imce.vars, {tMaxW: 120, tMaxH: 120, prvW: 40, prvH: 40});//inline thumbs
', 'inline');
//You can disable any of the extra features by deleting or commenting the corresponding line.
//For inline thumnails: images that are smaller than (tMaxW x tMaxH) are previewed inside the rows as (prvW x prvH).
//This does not affect the main previewing feature, which can be disabled by uncommenting the line below.
//drupal_add_js('$.extend(imce.vars, {previewImages: 0});', 'inline');
?>
<!--[if IE]><style type="text/css">#file-list-wrapper{padding-right: 2em}#file-list{margin-right: -2em}</style><![endif]-->
<!--[if IE 6]><style type="text/css">.y-resizer{font-size: 0.2em;}#sub-browse-wrapper{float: left; clear: right;}#preview-wrapper{overflow: visible;}#file-preview{width: 99%; height: 99%; overflow: auto;}</style><![endif]-->
<noscript><?php print t('You should use a javascript-enabled browser in order to experince a much more user-friendly interface.'); ?></noscript>

<div id="imce-content">

<a href="#" id="help-box"><!-- Update help content if you disable any of the extra features above. -->
  <div id="help-box-title"><?php print t('Help'); ?>!</div>
  <div id="help-box-content">
    <strong><?php print t('Tips'); ?></strong>:
    <ul class="tips">
      <li><?php print t('Select a file by clicking the corresponding row in the file list.'); ?></li>
      <li><?php print t('Ctrl+click to add files to the selection or to remove files from the selection.'); ?></li>
      <li><?php print t('Shift+click to create a range selection. Click to start the range and shift+click to end it.'); ?></li>
      <li><?php print t('Sort the files by clicking a column header of the file list.'); ?></li>
      <li><?php print t('Resize the work-spaces by dragging the horizontal or vertical resize-bars.'); ?></li>
      <li><?php print t('Keyboard shortcuts for file list: up, down, left, home, end, ctrl+A.'); ?></li>
      <li><?php print t('Keyboard shortcuts for selected files: enter/insert, delete, R(esize), T(humbnails), U(pload).'); ?></li>
      <li><?php print t('Keyboard shortcuts for directory list: up, down, left, right, home, end.'); ?></li>
    </ul>
    <strong><?php print t('Limitations'); ?></strong>:
    <ul class="tips">
      <li><?php print t('Maximum file size per upload') .': '. ($imce['filesize'] ? format_size($imce['filesize']) : t('unlimited')); ?></li>
      <li><?php print t('Permitted file extensions') .': '. ($imce['extensions'] != '*' ? $imce['extensions'] : t('all')); ?></li>
      <li><?php print t('Maximum image resolution') .': '. ($imce['dimensions'] ? $imce['dimensions'] : t('unlimited')); ?></li>
      <li><?php print t('Maximum number of files per operation') .': '. ($imce['filenum'] ? $imce['filenum'] : t('unlimited')); ?></li>
    </ul>
  </div>
</a>

<div id="ops-wrapper">
  <div id="op-items" class="clear-block"><ul class="tabs secondary" id="ops-list"></ul></div>
  <div id="op-contents"></div>
</div>

<div id="resizable-content">

<div id="browse-wrapper">

  <div id="navigation-wrapper">
    <div class="navigation-text"><?php print t('Navigation'); ?></div>
    <ul id="navigation-tree"><li class="expanded root"><?php print $tree; ?></li></ul>
  </div>

  <div id="navigation-resizer" class="x-resizer"></div>

  <div id="sub-browse-wrapper">

    <div id="file-header-wrapper">
      <table id="file-header" class="files"><tbody><tr>
        <td class="name"><?php print t('File name'); ?></td>
        <td class="size"><?php print t('Size'); ?></td>
        <td class="width"><?php print t('Width'); ?></td>
        <td class="height"><?php print t('Height'); ?></td>
        <td class="date"><?php print t('Date'); ?></td>
      </tr></tbody></table>
    </div>

    <div id="file-list-wrapper">
      <?php print theme('imce_file_list', $imce_ref); /* see imce-file-list-tpl.php */?>
    </div>

    <div id="dir-stat"><?php print t('!num files using !dirsize of !quota', array(
        '!num' => '<span id="file-count">'. count($imce['files']) .'</span>',
        '!dirsize' => '<span id="dir-size">'. format_size($imce['dirsize']) .'</span>',
        '!quota' => '<span id="dir-quota">'. ($imce['quota'] ? format_size($imce['quota']) : ($imce['tuquota'] ? format_size($imce['tuquota']) : t('unlimited quota'))) .'</span>'
      )); ?>
    </div>

  </div><!-- sub-browse-wrapper -->
</div><!-- browse-wrapper -->

<div id="browse-resizer" class="y-resizer"></div>

<div id="log-prv-wrapper">
  <div id="log-wrapper"></div>
  <div id="log-resizer" class="x-resizer"></div>
  <div id="preview-wrapper"><div id="file-preview"></div></div>
</div>

</div><!-- resizable-content -->

<div id="content-resizer" class="y-resizer"></div>
<a href="#" id="log-clearer" class="imce-hide"><?php print t('Clear log'); ?></a>

<div id="forms-wrapper"><?php print $forms; ?></div>

</div><!-- imce-content -->