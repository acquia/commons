// $Id: comment.js,v 1.1.2.1 2009/12/09 01:08:39 davereid Exp $

Drupal.verticalTabs = Drupal.verticalTabs || {};

Drupal.verticalTabs.comment_settings = function() {
  return $('.vertical-tabs-comment_settings input:checked').parent().text();
}

Drupal.verticalTabs.comment = function() {
  var vals = [];
  vals.push($(".vertical-tabs-comment input[name='comment']:checked").parent().text());
  vals.push($(".vertical-tabs-comment input[name='comment_default_mode']:checked").parent().text());
  vals.push(Drupal.t('@number comments per page', {'@number': $(".vertical-tabs-comment select[name='comment_default_per_page'] option:selected").val()}));
  return vals.join(', ');
}
