// $Id: content_types.js,v 1.1.2.1 2009/12/09 01:08:39 davereid Exp $

Drupal.verticalTabs = Drupal.verticalTabs || {};

Drupal.verticalTabs.submission = function() {
  var vals = [];
  vals.push(Drupal.checkPlain($('.vertical-tabs-submission #edit-title-label').val()) || Drupal.t('Requires a title'));
  vals.push(Drupal.checkPlain($('.vertical-tabs-submission #edit-body-label').val()) || Drupal.t('No body'));
  return vals.join(', ');
}

Drupal.verticalTabs.workflow = function() {
  var vals = [];
  $(".vertical-tabs-workflow input[name^='node_options']:checked").parent().each(function() {
    vals.push(Drupal.checkPlain($(this).text()));
  });
  if (!$('.vertical-tabs-workflow #edit-node-options-status').is(':checked')) {
    vals.unshift(Drupal.t('Not published'));
  }
  return vals.join(', ');
}
