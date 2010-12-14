<?php
// $Id: quant.quants.inc,v 1.1.2.6 2010/09/28 13:25:20 mikestefff Exp $

/**
 * Implementation of hook_quants()
 * 
 * Provide quant objects to be rendered as charts
 * 
 * Quant object items:
 *  id          A unique ID (Ex: 'comment_creation')
 *  label       The title of the chart
 *  labelsum    Whether or not to display the sum of items in the title (Boolean)
 *  table       Which database to query from
 *  field       The database field that stores the timestamp
 *  query       Specify a complete DB query to use to fetch the items 
 *                 (Optional; Use %d to indicate timestamp. This overrides field and table)
 *  queryCustom If query is set, you must provide the same query here altered to take a 'from'
 *                and 'to' date. (User %d to specify both, with 'from' coming before 'to')
 *  dataType    Specify the type of data we're dealing with (Options: single, multiple, count)
 *  group       The database field to group items on. (Optional; Only needed if dataType= multiple)
 *  count       Which database field to count (Optional; Only needed if dataType= count)
 *  chartType   Which type of chart to use (Options: line, bar, pie)
 * 
 * -- * See Organic group quants below for complex examples * --
 * 
 * @return
 *   An array of quant objects
 */
function _quant_quants() {
  $quants = array();
  
  // User Creation
  $quant = new stdClass;
  $quant->id = 'user_creation';
  $quant->label = t('User creation');
  $quant->labelsum = TRUE;
  $quant->table = 'users';
  $quant->field = 'created';
  $quant->dataType = 'single';
  $quant->chartType = 'line';
  $quants[] = $quant;
  
  // Content Creation
  $quant = new stdClass;
  $quant->id = 'content_creation';
  $quant->label = t('Content creation');
  $quant->labelsum = TRUE;
  $quant->table = 'node';
  $quant->field = 'created';
  $quant->query = quant_node_query();
  $quant->queryCustom = quant_node_query(array(), TRUE);
  $quant->dataType = 'single';
  $quant->chartType = 'line';
  $quants[] = $quant;
  
  // Comment Creation
  if (module_exists('comment')) {
    $quant = new stdClass;
    $quant->id = 'comment_creation';
    $quant->label = t('Comment creation');
    $quant->labelsum = TRUE;
    $quant->table = 'comments';
    $quant->field = 'timestamp';
    $quant->dataType = 'single';
    $quant->chartType = 'line';
    $quants[] = $quant;
  }
  
  // Content Creation by Type
  $quant = new stdClass;
  $quant->id = 'node_creation_by_type';
  $quant->label = t('Content creation by type');
  $quant->labelsum = TRUE;
  $quant->table = 'node';
  $quant->field = 'created';
  $quant->group = 'type'; // Which db field to group items by
  $quant->query = quant_node_query(array($quant->group));
  $quant->queryCustom = quant_node_query(array($quant->group), TRUE);
  $quant->dataType = 'multiple'; // See $quant->group
  $quant->chartType = 'line';
  $quants[] = $quant;
  
  // Aggregate Content Creation by Type
  $quant = new stdClass;
  $quant->id = 'node_creation_aggregate_by_type';
  $quant->label = t('Aggregate content creation');
  $quant->labelsum = TRUE;
  $quant->table = 'node';
  $quant->field = 'created';
  $quant->count = 'type'; // Which db field to we want to count
  $quant->dataType = 'count';
  $quant->chartType = 'pie';
  $quants[] = $quant;
  
  // User Points - Uses transactions only, not point amount
  if (module_exists('userpoints')) {
    $quant = new stdClass;
    $quant->id = 'user_points';
    $quant->label = t('User point transactions');
    $quant->labelsum = TRUE;
    $quant->table = 'userpoints_txn';
    $quant->field = 'time_stamp';
    $quant->dataType = 'single';
    $quant->chartType = 'line';
    $quants[] = $quant;
  }
  
  // Organic Groups
  if (module_exists('og')) {
    // Group Joins
    $quant = new stdClass;
    $quant->id = 'group_joins';
    $quant->label = t('Group joins');
    $quant->labelsum = TRUE;
    $quant->table = 'og_uid'; // The table to grab items from
    $quant->field = 'created'; // Which table field holds the timestamp
    $quant->dataType = 'single'; // We're just dealing with one item
    $quant->chartType = 'line';
    $quants[] = $quant;  
    
    // Group Creation
    $quant = new stdClass;
    $quant->id = 'group_creation';
    $quant->label = t('Group creation');
    $quant->labelsum = TRUE; // Show the total amount of items in the chart title
    $quant->query = "SELECT n.created FROM {og} g INNER JOIN {node} n 
      ON g.nid = n.nid WHERE n.created >= %d 
      ORDER BY n.created DESC"; // We can provide a custom query instead
    $quant->queryCustom = "SELECT n.created FROM {og} g INNER JOIN {node} n 
      ON g.nid = n.nid WHERE n.created >= %d AND n.created <= %d
      ORDER BY n.created DESC"; // We need to provide the query altered for a custom interval
    $quant->table = 'og';
    $quant->field = 'created';
    $quant->dataType = 'single';
    $quant->chartType = 'line';
    $quants[] = $quant;
  }
  
  // User Shouts
  if (module_exists('shoutbox')) {
    $quant = new stdClass;
    $quant->id = 'user_shouts';
    $quant->label = t('User shouts');
    $quant->labelsum = TRUE;
    $quant->table = 'shoutbox';
    $quant->field = 'created';
    $quant->dataType = 'single';
    $quant->chartType = 'line';
    $quants[] = $quant;
  }
  
  // Invites
  if (module_exists('invite')) {
    // Invites sent
    $quant = new stdClass;
    $quant->id = 'user_invites_sent';
    $quant->label = t('Invites sent');
    $quant->labelsum = TRUE;
    $quant->table = 'invite';
    $quant->field = 'created';
    $quant->dataType = 'single';
    $quant->chartType = 'line';
    $quants[] = $quant;
    
    // Invites accepted
    $quant = new stdClass;
    $quant->id = 'user_invites_accepted';
    $quant->label = t('Invites accepted');
    $quant->labelsum = TRUE;
    $quant->query = "SELECT created FROM {invite} WHERE joined = 1 AND created >= %d 
      ORDER BY created DESC";
    $quant->queryCustom = "SELECT created FROM {invite} WHERE joined = 1 AND created >= %d 
      AND created <= %d ORDER BY created DESC";
    $quant->table = 'invite';
    $quant->field = 'created';
    $quant->dataType = 'single';
    $quant->chartType = 'line';
    $quants[] = $quant;
  }
  
  return $quants;
}

/**
 * Build a node database query
 * Avoid grabbing nodes that act as organic groups
 * 
 * @param $additional_fields
 *   An array of additional database fields to fetch other than 'created'
 * @param $custom
 *   Boolean indication whether we should return a format for query
 *   or queryCustom. (See hook_quants() documentation)
 * @return
 *   A database query statement
 */
function quant_node_query($additional_fields = array(), $custom = FALSE) {
  $query = '';
  $omit = array();
  
  // Add required field to array
  $additional_fields[] = 'created';
  
  // Omit group nodes, if any
  if (module_exists('og')) {
    $types = db_query("SELECT type FROM {node_type}");
    while ($node = db_fetch_object($types)) {
      if (og_is_group_type($node->type)) {
        $omit[] = $node->type;
      }
    }
  }
  
  if (count($omit)) {
    $query = "SELECT " . implode(', ', $additional_fields) . " FROM {node} WHERE created >= %d" . ($custom ? " AND created <= %d " : " ") . "AND type NOT LIKE '" . implode('\', \'', $omit) . "' ORDER BY created DESC";
  }
  else {
    $query = "SELECT " . implode(', ', $additional_fields) . " FROM {node} WHERE created >= %d" . ($custom ? " AND created <= %d " : " ") . "ORDER BY created DESC";
  }
  
  return $query;
}
