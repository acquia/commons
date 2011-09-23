QUICK START GUIDE
-----------------
Click Site building > Views > Add
View name = "test", View type = "Node"
Click "Add display" to create a new page
Click Style: Unformatted and select "Bulk Operations", then click "Update"
In Page: Style options > Selected operations, select a few operations then click "Update default display"
In Fields, press +, then select "Node: Title", then click "Add" then "Update default display"
if you're using Views 6.x-3.x, you also need to add the "Node: Nid" field. You can set it as "Exclude from display", as VBO only needs it internally.
In Page settings, click Path: None and type "test", then click "Update"
Click "Save", then "View Page" (top-right corner)
Enjoy your first VBO!

TECHNICAL DETAILS
-----------------
The module works by exposing a new Views 2 Style plugin called "Bulk Operations".
The settings for this plugin allow to choose the operations that should appear on the view.
Operations are gathered from two sources: 1) Action API 2) hook_node_operations and hook_user_operations.
The module also allows to use Batch API or the Job queue module to process the selected nodes, in order to avoid timeouts.

VBO can support all object types supported by Views. Natively, VBO comes with support for nodes, users and comments.
Through the new VBO-defined hook_views_bulk_operations_object_info(), other modules can help VBO handle arbitrary object types.
Refer to function views_bulk_operations_views_bulk_operations_object_info() for information.

EXAMPLE VBO
-----------
As an example, the module comes with a re-implementation of the Content admin page.
To access it, just go to the URL admin/content/node2.
You can modify the path to admin/content/node to override the default Content admin page.

INCLUDED ACTIONS
--------------
- Modify node taxonomy terms
The module comes with a new action to manipulate nodes' taxonomy terms.
Unlike Taxonomy Node Operations, which creates a new action for each single term,
this module exposes a single configurable action that allows the user to choose which term(s) should be added to the selected nodes.
The user can also choose to keep existing terms or to erase them.

- Delete node, user, comment
Actions to delete these objects.

- Rulesets -> actions
Detect rulesets created with the Rules module and expose them as actions that VBO can invoke.

- Arbitrary PHP script
Write PHP code that is applied to each node in VBO.
This action requires the 'administer site configuration' permission - even if actions_permissions.module says otherwise.

- Modify node fields
Bulk-modify CCK and other node fields.

- Modify profile fields
Bulk-modify user profile fields.

- Modify user roles
Assign and unassign roles to users.

- Managing blocks
The Views Block module (part of Views Hacks) exposes block data to Views, allowing VBO to manage blocks just as nodes or users. Try it out!

FAQ
---
- Even though the action gets called on my selected nodes, these nodes still retain their old values! What's going on?
Actions in D6 use a flag called 'changes_node_property' to give a hint to Drupal whether this action modifies node contents
or performs a read-only operation on the node. VBO uses that flag to determine whether node_save() should be called or not after executing the action.
Actions that modify node contents but don't expose this flag in hook_action_info() will not be properly handled by VBO!
Checkout node.module's node_action_info() implementation for an example.

- How can I write an action that performs a function on all selected nodes AT ONCE?
You need to write a node operation instead of an action. Whereas actions get called *once for every selected node*, node operations are called once only,
and they are passed an array of selected nodes. Check out sirkitree's article for the same concept applied to user operations.
Note: If you use Batch API to execute your actions, VBO will revert to calling the action once per node instead.
This is because it doesn't make sense to batch one single action.

- I need VBO to modify thousands of nodes at once! Help!
VBO is designed to handle large numbers of nodes, without causing memory errors or timeouts.
When you select thousands of nodes, you can choose to execute the operations using Batch API, which provides visual feedback on VBO's progress.
To select Batch API, edit your view, open the "Bulk Operation" style settings and in the section "To execute operations:", select "Use Batch API".
You can also choose to execute the operations during cron runs via the Job queue module if you have it enabled.

- How can I use VBO to copy values from one field to another?
You will need to write simple PHP code.

Install Devel, and open the "Dev load" tab on a node of the type you want to manipulate.
Write down the name of the source field, as well as the array key that contains the field value. E.g.
'field_contact' => array(
  0 => array('value' => 'Some value'),
);
Use the stock VBO at /admin/content/node2 and filter the nodes by the desired type. Then choose the action "Modify node fields" and press "Execute".
On the "Set parameters for 'Modify node fields'" page, locate the destination field and check it ON.
In the "Code" area of that field, write the script needed to copy the value from the source field.
The help text below the code area shows you the expected format, and you can access the node being manipulated using the variable $node. E.g.
return array(
  0 => array('value' => $node->field_contact[0]['value']),
);
Press "Next" then "Confirm"

- How can I make sure that unauthorized users are prevented from destroying nodes or any other parts of my Drupal installation?
VBO gives a lot of power to admins, so it's important that security measures be enforced. There are currently 3 different ways to restrict access to VBO:

1) Using the bundled actions_permissions module, the admin can set permissions on each individual action.
   VBO honors those permissions by hiding the unauthorized actions *and* checking permissions again when it is about to execute an action.
2) VBO also calls node_access on each node that is about to be acted upon. Nodes for which the user does not have appropriate permissions
   are discarded from the execution list. The action flag changes_node_property is mapped to node_access('update').
   There are other mappings as well described in the VBO development guide.
3) The author of actions can specify additional permissions in hook_action_info under the attribute 'permissions' => array(perm1, perm2, ...).

- What is the difference between these pairs of actions:
  -- Make post sticky (node_make_sticky_action) vs Make sticky (node_mass_update:c4d...794)
  -- Promote post to front page (node_promote_action) vs Promote to front page (node_mass_update:14de7d028b4bffdf2b4a266562ca18ac)
  -- Publish (node_mass_update:9c5...047) vs Publish post (node_publish_action)
  -- Unpublish (node_mass_update:0cc...080) vs Unpublish post (node_unpublish_action)
These pairs are functionally equivalent. Technically, they differ in that the node_mass_update function is a core node operation used in
the original content administration screen, whereas the node_xxx_action functions are core actions.
As a site administrator, feel free to choose either for your VBO content administration screen.

- How can I edit fields created for the Content Profile module?
Create a Node view and filter by the content types that are attached to Content Profile. Then use the "Modify node fields" action to edit those fields.

KNOWN ISSUES
------------
- "Access denied" when selecting all (or many) rows
This occurs because too much data is sent to the database server. For MySQL, increase max_allowed_packet (e.g. to 32M). See also: https://drupal.org/node/845618.
