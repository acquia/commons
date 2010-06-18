// $Id: path.js,v 1.1.2.1 2009/12/09 01:08:39 davereid Exp $

Drupal.verticalTabs = Drupal.verticalTabs || {};

Drupal.verticalTabs.path = function() {
  var path = $('#edit-path').val();
  if (path) {
    return Drupal.t('Alias: @alias', { '@alias': path });
  }
  else {
    return Drupal.t('No alias');
  }
}
