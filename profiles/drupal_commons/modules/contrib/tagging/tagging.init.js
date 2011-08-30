// $Id: tagging.init.js,v 1.12.2.6 2010/10/17 10:23:24 eugenmayer Exp $

// Author: Eugen Mayer (http://kontextwork.de)
// Copyright 2010
Drupal.behaviors.tagging = function() {
  $('input.tagging-widget-input:not(.tagging-processed)').tagging();
}
