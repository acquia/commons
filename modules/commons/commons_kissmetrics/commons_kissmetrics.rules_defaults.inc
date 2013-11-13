<?php
/**
 * @file
 * commons_kissmetrics.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commons_kissmetrics_default_rules_configuration() {
  $items = array();
  $items['rules_commons_kissmetrics_collect_referenced_groups'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_collect_referenced_groups" : {
      "LABEL" : "Commons KISSmetrics: Collect Referenced Groups",
      "PLUGIN" : "rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "commons_kissmetrics_referenced_groups" : { "label" : "Referenced Groups", "type" : "node" },
        "commons_kissmetrics_collected_groups" : { "label" : "Collected Groups", "type" : "text", "parameter" : false }
      },
      "IF" : [
        { "entity_has_field" : {
            "entity" : [ "commons-kissmetrics-referenced-groups" ],
            "field" : "og_group_ref"
          }
        }
      ],
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "commons-kissmetrics-referenced-groups:og-group-ref" ] },
            "ITEM" : { "referenced_group" : "Referenced Group" },
            "DO" : [
              { "data_set" : {
                  "data" : [ "commons-kissmetrics-collected-groups" ],
                  "value" : "Group|[referenced-group:title]\\r\\n[commons-kissmetrics-collected-groups:value]"
                }
              }
            ]
          }
        }
      ],
      "PROVIDES VARIABLES" : [ "commons_kissmetrics_collected_groups" ]
    }
  }');
  $items['rules_commons_kissmetrics_user_adds_a_trusted_contact'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_adds_a_trusted_contact" : {
      "LABEL" : "Commons KISSmetrics: User Adds A Trusted Contact",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics", "og" ],
      "ON" : { "og_user_insert" : [] },
      "IF" : [ { "data_is" : { "data" : [ "og-membership:state" ], "value" : "2" } } ],
      "DO" : [
        { "kissmetrics_record_event" : {
            "name" : "User Added A Trusted Contact",
            "properties" : "User|[account:name]"
          }
        }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_approves_a_trusted_contact'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_approves_a_trusted_contact" : {
      "LABEL" : "Commons KISSmetrics: User Approves A Trusted Contact",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics", "og" ],
      "ON" : { "og_user_approved" : [] },
      "IF" : [ { "data_is" : { "data" : [ "og-membership:state" ], "value" : "1" } } ],
      "DO" : [
        { "kissmetrics_record_event" : {
            "name" : "User Approved A Trusted Contact",
            "properties" : "User|[account:name]"
          }
        }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_creates_content'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_creates_content" : {
      "LABEL" : "Commons KISSmetrics: User Creates Content",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics" ],
      "ON" : { "node_insert" : [] },
      "DO" : [
        { "component_rules_commons_kissmetrics_collect_referenced_groups" : {
            "USING" : { "commons_kissmetrics_referenced_groups" : [ "node" ] },
            "PROVIDE" : { "commons_kissmetrics_collected_groups" : { "commons_kissmetrics_collected_groups" : "Collected Groups" } }
          }
        },
        { "kissmetrics_record_event" : {
            "name" : "User Created Content",
            "properties" : "Title|[node:title]\\r\\nType|[node:content-type:name]\\r\\n[commons-kissmetrics-collected-groups:value]"
          }
        }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_edits_profile'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_edits_profile" : {
      "LABEL" : "Commons KISSmetrics: User Edits Profile",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics" ],
      "ON" : { "user_update" : [] },
      "DO" : [
        { "kissmetrics_record_event" : { "name" : "User Edited Profile", "properties" : "User|[account:name]" } }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_edits_wiki'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_edits_wiki" : {
      "LABEL" : "Commons KISSmetrics: User Edits Wiki",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics" ],
      "ON" : { "node_update" : [] },
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "wiki" : "wiki" } } } }
      ],
      "DO" : [
        { "component_rules_commons_kissmetrics_collect_referenced_groups" : {
            "USING" : { "commons_kissmetrics_referenced_groups" : [ "node" ] },
            "PROVIDE" : { "commons_kissmetrics_collected_groups" : { "commons_kissmetrics_collected_groups" : "Collected Groups" } }
          }
        },
        { "kissmetrics_record_event" : {
            "name" : "User Edited Wiki",
            "properties" : "Title|[node:title]\\r\\n[commons-kissmetrics-collected-groups:value]"
          }
        }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_flags_content_as_inappropriate'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_flags_content_as_inappropriate" : {
      "LABEL" : "Commons KISSmetrics: User Flags Content As Inappropriate",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics", "flag" ],
      "ON" : { "flag_flagged_inappropriate_node" : [] },
      "DO" : [
        { "kissmetrics_record_event" : {
            "name" : "User Flagged Content As Inappropriate",
            "properties" : "Title|[flagged-node:title]"
          }
        }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_follows_content'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_follows_content" : {
      "LABEL" : "Commons KISSmetrics: User Follows Content",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics", "flag" ],
      "ON" : { "flag_flagged_commons_follow_node" : [] },
      "DO" : [
        { "component_rules_commons_kissmetrics_collect_referenced_groups" : {
            "USING" : { "commons_kissmetrics_referenced_groups" : [ "flagged-node" ] },
            "PROVIDE" : { "commons_kissmetrics_collected_groups" : { "commons_kissmetrics_collected_groups" : "Collected Groups" } }
          }
        },
        { "kissmetrics_record_event" : {
            "name" : "User Followed Content",
            "properties" : "Title|[flagged-node:title]\\r\\n[commons-kissmetrics-collected-groups:value]"
          }
        }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_follows_group'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_follows_group" : {
      "LABEL" : "Commons KISSmetrics: User Follows Group",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics", "flag" ],
      "ON" : { "flag_flagged_commons_follow_group" : [] },
      "DO" : [
        { "kissmetrics_record_event" : {
            "name" : "User Followed Group",
            "properties" : "Title|[flagged-node:title]"
          }
        }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_follows_topic'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_follows_topic" : {
      "LABEL" : "Commons KISSmetrics: User Follows Topic",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics", "flag" ],
      "ON" : { "flag_flagged_commons_follow_term" : [] },
      "DO" : [
        { "kissmetrics_record_event" : {
            "name" : "User Followed Topic",
            "properties" : "Name|[flagged-taxonomy-term:name]"
          }
        }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_follows_user'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_follows_user" : {
      "LABEL" : "Commons KISSmetrics: User Follows User",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics", "flag" ],
      "ON" : { "flag_flagged_commons_follow_user" : [] },
      "DO" : [
        { "kissmetrics_record_event" : {
            "name" : "User Followed User",
            "properties" : "User|[flagged-user:name]"
          }
        }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_likes_content'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_likes_content" : {
      "LABEL" : "Commons KISSmetrics: User Likes Content",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics", "voting_rules" ],
      "ON" : { "voting_rules_insert_node" : [] },
      "DO" : [
        { "kissmetrics_record_event" : { "name" : "User Liked Content", "properties" : "Title|[node:title]" } }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_logs_in'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_logs_in" : {
      "LABEL" : "Commons KISSmetrics: User Logs In",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics" ],
      "ON" : { "user_login" : [] },
      "DO" : [
        { "kissmetrics_record_event" : { "name" : "User Logged In", "properties" : "User|[account:name]" } }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_logs_out'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_logs_out" : {
      "LABEL" : "Commons KISSmetrics: User Logs Out",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics" ],
      "ON" : { "user_logout" : [] },
      "DO" : [
        { "kissmetrics_record_event" : { "name" : "User Logged Out", "properties" : "User|[[account:name]]" } }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_posts_comment'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_posts_comment" : {
      "LABEL" : "Commons KISSmetrics: User Posts Comment",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics", "comment" ],
      "ON" : { "comment_insert" : [] },
      "DO" : [
        { "component_rules_commons_kissmetrics_collect_referenced_groups" : {
            "USING" : { "commons_kissmetrics_referenced_groups" : [ "comment:node" ] },
            "PROVIDE" : { "commons_kissmetrics_collected_groups" : { "commons_kissmetrics_collected_groups" : "Collected Groups" } }
          }
        },
        { "kissmetrics_record_event" : {
            "name" : "User Posted Comment",
            "properties" : "Title|[comment:title]\\r\\nAssociated Content|[comment:node:title]\\r\\n[commons-kissmetrics-collected-groups:value]"
          }
        }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_registers'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_registers" : {
      "LABEL" : "Commons KISSmetrics: User Registers",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics" ],
      "ON" : { "user_insert" : [] },
      "DO" : [
        { "kissmetrics_record_event" : { "name" : "User Registered", "properties" : "User|[[account:name]]" } }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_replies_to_private_message_thread'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_replies_to_private_message_thread" : {
      "LABEL" : "Commons KISSmetrics: User Replies To Private Message Thread",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics", "privatemsg_rules" ],
      "ON" : { "privatemsg_insert" : [] },
      "IF" : [
        { "NOT data_is_empty" : { "data" : [ "privatemsg-message:thread-id" ] } }
      ],
      "DO" : [
        { "kissmetrics_record_event" : {
            "name" : "User Replied To Private Message Thread",
            "properties" : "Author|[privatemsg-message:author]\\r\\nRecipient|[recipient:name]"
          }
        }
      ]
    }
  }');
  $items['rules_commons_kissmetrics_user_starts_new_private_message_thread'] = entity_import('rules_config', '{ "rules_commons_kissmetrics_user_starts_new_private_message_thread" : {
      "LABEL" : "Commons KISSmetrics: User Starts New Private Message Thread",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Commons KISSmetrics" ],
      "REQUIRES" : [ "rules", "kissmetrics", "privatemsg_rules" ],
      "ON" : { "privatemsg_insert" : [] },
      "IF" : [ { "data_is_empty" : { "data" : [ "privatemsg-message:thread-id" ] } } ],
      "DO" : [
        { "kissmetrics_record_event" : {
            "name" : "User Started New Private Message Thread",
            "properties" : "Author|[privatemsg-message:author]\\r\\nRecipient|[recipient:name]"
          }
        }
      ]
    }
  }');
  return $items;
}
