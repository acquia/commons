// $Id: node.js,v 1.1.2.1 2009/12/09 01:08:39 davereid Exp $

Drupal.verticalTabs = Drupal.verticalTabs || {};

Drupal.verticalTabs.revision_information = function() {
  if ($('#edit-revision').length) {
    if ($('#edit-revision').attr('checked')) {
      return Drupal.t('New revision');
    }
    else {
      return Drupal.t('No revision');
    }
  }
  else {
    return '';
  }
}

Drupal.verticalTabs.author = function() {
  var author = $('#edit-name').val() || Drupal.t('Anonymous');
  var date = $('#edit-date').val();
  if (date) {
    return Drupal.t('By @name on @date', { '@name': author, '@date': date });
  }
  else {
    return Drupal.t('By @name', { '@name': author });
  }
}

Drupal.verticalTabs.options = function() {
  var vals = [];
  if ($('#edit-status').attr('checked')) {
    vals.push(Drupal.t('Published'));
  }
  else {
    vals.push(Drupal.t('Not published'));
  }
  if ($('#edit-promote').attr('checked')) {
    vals.push(Drupal.t('Promoted to front page'));
  }
  if ($('#edit-sticky').attr('checked')) {
    vals.push(Drupal.t('Sticky on top of lists'));
  }
  if (vals.join(', ') == '') {
    return Drupal.t('None');
  }
  return vals.join(', ');
}
