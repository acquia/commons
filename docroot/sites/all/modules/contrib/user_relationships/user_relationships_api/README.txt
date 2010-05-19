$Id: README.txt,v 1.1.2.7 2009/07/10 07:27:49 alexk Exp $

User Relationships API
------------------
This the API only portion of User Relationships. This is required by all UR plugins and addon
modules. It provides no frontend interface.

Installation Notes
------------------
PostgreSQL users, please read http://drupal.org/node/331692 and check out the patch in it, as 
the current install schema does not apparently work with PostgreSQL.

Developers
------------
There are a number of API functions and two hooks. The API functions are all defined in
user_relationships_api.api.inc. I've provded a list below for quick lookup, but you'll
need to see the documentation in that file for a deeper explanaition.

  Functions
  =========
  user_relationships_type_load($param = array())
  user_relationships_types_load($reset = NULL)
  user_relationships_type_save(&$rtype)
  user_relationships_type_delete($rtid)

  user_relationships_load($param = array(), $options = array(), $reset = FALSE)
  user_relationships_api_translate_user_info(&$relationship)
  user_relationships_request_relationship($requester, $requestee, $type, $approved = FALSE)
  user_relationships_save_relationship(&$relationship, $op = 'request')
  user_relationships_delete_relationship(&$relationship, &$deleted_by, $op = 'remove')


  Hooks
  =====
  hook_user_relationships_type($op, &$relationship_type)
    presave | When either saving a new relationship type or updating an existing relationship type
    insert  | After saving a new relationship type
    update  | After saving an existing relationship type
    delete  | After deleting a relationship type
    load    | When a relationship type is loaded

  hook_user_relationships($op, &$relationship)
    load        | When a relationship is loaded
    presave     | When either saving a new relationship or updating an existing relationship
    request     | After a new relationship has been requested
    cancel      | When a relationship has been removed (specifically cancelled)
    update      | After saving an existing relationship
    approve     | After approving a relationship
    disapprove  | When a relationship has been removed (specifically disapproved)
    remove      | When a relationship has been removed
