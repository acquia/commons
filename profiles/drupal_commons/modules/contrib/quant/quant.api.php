<?php

/***************************************
(BEFORE YOUR START) ADMIN SETTINGS
--------------------------------------

Inside the admin settings, located at /admin/settings/quant, admins will be presented
with a list of every available quant (loaded from hook_quants). Admins can limit
which charts show on the analytics page. If the admin, at any time, restricts which
quants show up, newly added charts will not show up on the page until they are enabled
here. Quant objects are also cached, so the cache must be cleared before new quants
appear in this list.

API - PROVIDE YOUR OWN QUANT CHARTS
--------------------------------------

The real power of Quant lies in it's ability to generate these charts with very 
little provided information. Quant offers a simple, yet flexible API to allow 
developers to include quant charts with their modules.
*****************************************/

/**
 * Implementation of hook_quants()
 *
 * Provide a quant chart of comment creation over time
 */
function hook_quants() {
  $quants = array();

  $quant = new stdClass;
  $quant->id = 'comment_creation';	 // Unique ID
  $quant->label = t('Comment creation');	 // The title of the chart
  $quant->labelsum = TRUE;	 // Add the sum of items over time to the title
  $quant->table = 'comments';	 // The database table
  $quant->field = 'timestamp';	 // The column that stores the timestamp
  $quant->dataType = 'single';	 // Only one datapoint used
  $quant->chartType = 'line';	 // The type of chart
  $quants[$uant->id] = $quant;

  return $quants;
}

/**
 * Implementation of hook_quants_alter()
 * 
 * Alter the array of quants before they are cached
 */
function hook_quants_alter(&$quants) {
  $quants['comment_creation']->label = t('Comments added');
}

/***************************************
MORE COMPLEX EXAMPLES
--------------------------------------

See what else you can do with quant in the file includes/quants.inc.


PRINT A QUANT ANYWHERE
--------------------------------------

Until better support comes for placing quants anywhere, you have the flexibility
to create quant charts in places like blocks, views, and anywhere where PHP is
available. Simply create your quant object then print it via:

print quant_process($quant, '-1 week');

OR

print quant_process($quant, array('02/29/2010', '05/19/2010'));
**************************************/
