// $Id: vertical_tabs.js,v 1.3.2.19 2010/02/03 18:24:42 davereid Exp $

Drupal.verticalTabs = Drupal.verticalTabs || {};
Drupal.settings.verticalTabs = Drupal.settings.verticalTabs || {};

Drupal.behaviors.verticalTabs = function() {
  if (!$('.vertical-tabs-list').size() && Drupal.settings.verticalTabs) {
    var ul = $('<ul class="vertical-tabs-list"></ul>');
    var panes = $('<div class="vertical-tabs-panes"></div>');
    $.each(Drupal.settings.verticalTabs, function(k, v) {
      var summary = '', cssClass = 'vertical-tabs-list-' + k;
      if (v.callback && Drupal.verticalTabs[v.callback]) {
        summary = '<span class="summary">'+ Drupal.verticalTabs[v.callback].apply(this, v.args) +'</span>';
      }
      else {
        cssClass += ' vertical-tabs-nosummary';
      }

      // Add a list item to the vertical tabs list.
      $('<li class="vertical-tab-button"><a href="#' + k + '" class="' + cssClass + '"><strong>'+ v.name + '</strong>' + summary +'</a></li>').appendTo(ul)
        .find('a')
        .bind('click', function() {
          $(this).parent().addClass('selected').siblings().removeClass('selected');
          $('.vertical-tabs-' + k).show().siblings('.vertical-tabs-pane').hide();
          return false;
      });

      // Find the contents of the fieldset (depending on #collapsible property).
      var fieldset = $('<fieldset></fieldset>');
      var fieldsetContents = $('.vertical-tabs-' + k + ' > .fieldset-wrapper > *');
      if (fieldsetContents.size()) {
        fieldsetContents.appendTo(fieldset);
      }
      else {
        $('.vertical-tabs-' + k).children().appendTo(fieldset);
      }

      // Remove the legend from the fieldset.
      fieldset.children('legend').remove();

      // Add the fieldset contents to the toggled fieldsets.
      fieldset.appendTo(panes)
      .addClass('vertical-tabs-' + k)
      .addClass('vertical-tabs-pane')
      .find('input, select, textarea').bind('change', function() {
        if (v.callback && Drupal.verticalTabs[v.callback]) {
          $('a.vertical-tabs-list-' + k + ' span.summary').html(Drupal.verticalTabs[v.callback].apply(this, v.args));
        }
      });
      $('.vertical-tabs-' + k).remove();
    });

    $('div.vertical-tabs').html(ul).append(panes);

    // Add an error class to any fieldsets with errors in them.
    $('fieldset.vertical-tabs-pane').each(function(i){
      if ($(this).find('div.form-item .error').size()) {
        $('li.vertical-tab-button').eq(i).addClass('error');
      }
    })

    // Activate the first tab.
    $('fieldset.vertical-tabs-pane').hide();
    $('fieldset.vertical-tabs-pane:first').show();
    $('div.vertical-tabs ul li:first').addClass('first selected');
    $('div.vertical-tabs ul li:last').addClass('last');
    $('div.vertical-tabs').show();
  }
}

Drupal.behaviors.verticalTabsReload = function() {
  $.each(Drupal.settings.verticalTabs, function(k, v) {
    if (v.callback && Drupal.verticalTabs[v.callback]) {
      $('a.vertical-tabs-list-' + k + ' span.summary').html(Drupal.verticalTabs[v.callback].apply(this, v.args));
    }
  });
}
