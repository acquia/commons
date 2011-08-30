// $Id: block.js,v 1.1.2.1 2009/12/09 04:35:33 davereid Exp $

Drupal.verticalTabs = Drupal.verticalTabs || {};

Drupal.verticalTabs.user_vis_settings = function() {
  return $('fieldset.vertical-tabs-user_vis_settings input[name="custom"]:radio:checked').parent().text();
}

Drupal.verticalTabs.role_vis_settings = function() {
  var vals = [];
  $('fieldset.vertical-tabs-role_vis_settings input[type="checkbox"]:checked').each(function () {
    vals.push($.trim($(this).parent().text()));
  });
  if (!vals.length) {
    vals.push(Drupal.t('Not restricted'));
  }
  return vals.join(', ');
}

Drupal.verticalTabs.page_vis_settings = function() {
  return $('fieldset.vertical-tabs-page_vis_settings input[name="visibility"]:radio:checked').parent().text();
}
