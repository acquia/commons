<?php

/**
 * Filter by what the user is following.
 */
class commons_follow_handler_filter_follow extends views_handler_filter {
  function can_expose() { return TRUE; }
  function query() {
    $table = $this->ensure_my_table();
      // Select for source translations (tnid = nid). Conditionally, also accept either untranslated nodes (tnid = 0).
    //@Todo: Allow other modules to return a list of mids to include for "The user is following."
    // Provide an API that lets other modules define these OR detect them automagically.
    // Query for NIDs, UIDs, and TIDs that the user is following based on what they have flagged.
    $this->query->add_where_expression($this->options['group'], "$table.mid IN (:mids)", array(':mids' => commons_follow_get_followed_message_ids()));
  }
}

