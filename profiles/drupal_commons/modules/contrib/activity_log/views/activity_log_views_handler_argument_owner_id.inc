<?php

/**
 * @file
 *   Allow only statuses with a specific tag.
 */

/**
 * Argument handler to select statuses containing a specific tag.
 */
class activity_log_views_handler_argument_owner_id extends views_handler_argument_numeric {
  function option_definition() {
    $options = parent::option_definition();
    $options['include'] = array(
      'default' => array(),
      'translatable' => FALSE,
    );
    return $options;
  }
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $opt = array();
    if (module_exists('og')) {
      $opt['og'] = t("The argument user's Organic Groups");
    }
    if (module_exists('user_relationships_api')) {
      $opt['ur'] = t("The argument user's relationships");
      foreach (user_relationships_types_load() as $type) {
        $opt['ur-'. $type->rtid] = t("The argument user's %type relationships", array('%type' => $type->name));
      }
    }
    if (!empty($opt)) {
      $form['include'] = array(
        '#title' => t('Include activity for'),
        '#description' => t('Include activity on this view from other streams if the argument user is the current user.'),
        '#type'  => 'checkboxes',
        '#options' => $opt,
        '#default_value' => $this->options['include'],
      );
    }
  }
  function query() {
    $options = array_filter($this->options['include']);
    if (empty($options)) {
      parent::query();
      return;
    }
    global $user;
    $this->ensure_my_table();
    if (!empty($this->options['break_phrase'])) {
      views_break_phrase($this->argument, $this);
    }
    else {
      $this->value = array($this->argument);
    }
    if (count($this->value) > 1) {
      $operator = empty($this->options['not']) ? 'IN' : 'NOT IN';
      $placeholders = '('. db_placeholders($this->value) .')';
      $args = $this->value;
    }
    else {
      $operator = empty($this->options['not']) ? '=' : '!=';
      $placeholders = '%d';
      $args = array($this->argument);
    }
    $query = "$this->table_alias.$this->real_field $operator $placeholders";
    $query_args = $args;
    if (in_array($user->uid, $args)) {
      $subquery = array();
      if (!empty($options['og']) && module_exists('og')) {
        $subquery[] = db_prefix_tables("$this->table_alias.$this->real_field IN (SELECT nid FROM {og_uid} WHERE is_active = 1 AND uid $operator $placeholders)");
        $query_args = array_merge($query_args, $args);
      }
      if (module_exists('user_relationships_api')) {
        if (!empty($options['ur'])) {
          $rels = $this->_activity_log_get_user_relationships($user->uid);
          if (!empty($rels)) {
            $subquery[] = db_prefix_tables("$this->table_alias.$this->real_field IN (". db_placeholders($rels) .")");
            $query_args = array_merge($query_args, $rels);
          }
        }
        else {
          foreach (user_relationships_types_load() as $type) {
            if (in_array('ur-'. $type->rtid, $options)) {
              $rels = $this->_activity_log_get_user_relationships($user->uid, $type->rtid);
              if (!empty($rels)) {
                $subquery[] = db_prefix_tables("$this->table_alias.$this->real_field IN (". db_placeholders($rels) .")");
                $query_args = array_merge($query_args, $rels);
              }
            }
          }
        }
      }
      if (!empty($subquery)) {
        $query .= " OR ($this->table_alias.stream_owner_type = 'user' AND (". implode(" OR ", $subquery) ."))";
      }
    }
    $this->query->add_where(0, $query, $query_args);
  }
  function _activity_log_get_user_relationships($uid, $rtid = 0) {
    if (!$rtid) {
      $result = db_query("
        SELECT ur.requester_id, ur.requestee_id
        FROM user_relationships ur
        INNER JOIN user_relationship_types urt
          ON ur.rtid = urt.rtid
        WHERE (ur.requester_id = %d OR ur.requestee_id = %d) AND (ur.approved = 1 OR urt.is_oneway = 0)
      ", $uid, $uid);
    }
    else {
      $result = db_query("
        SELECT ur.requester_id, ur.requestee_id
        FROM user_relationships ur
        INNER JOIN user_relationship_types urt
          ON ur.rtid = urt.rtid
        WHERE (ur.requester_id = %d OR ur.requestee_id = %d) AND (ur.approved = 1 OR urt.is_oneway = 0) AND ur.rtid = %d
      ", $uid, $uid, $rtid);
    }
    $uids = array();
    while ($rel = db_fetch_object($result)) {
      $uids[] = ($rel->requester_id == $uid) ? $rel->requestee_id : $rel->requester_id;
    }
    return $uids;
  }
}
