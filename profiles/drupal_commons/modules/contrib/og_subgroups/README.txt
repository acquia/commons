--------------------------
DESCRIPTION
--------------------------
This module enables a user with the proper permissions to build group 
hierarchies (or tree) by nesting groups under other groups. Simple or complex
group hierarchies can be easily created.

When a hierarchy has been established, user memberships and/or content posted
to a group can be propagated up, down or sideways along the tree. So when a
user joins a group, their membership can also get created in other parent,
child or sibling groups. Separate propagation settings can be applied for
content and membership propagation.  

Admin rights, both promotion and demotion, can also propagate to other groups
so a group admin of one group can automatically become an admin at other 
groups depending on the propagation settings.

--------------------------
INSTALLATION
--------------------------
Install as usual, see http://drupal.org/node/70151 for further information.

--------------------------
DEPENDENCIES
--------------------------
Subgroups for Organic Groups requires the following modules to also be
installed:
 - Organic Groups (http://drupal.org/project/og)

--------------------------
SETUP
--------------------------
  1. After installation, configure permissions:
     Administer > User management > Permissions > og_subgroup module
     Refer to the PERMISSIONS section below.

  2. Go to the admin settings page (admin/og/subgroups).

  3. Configure the settings as appropriate:
     - Content Propagation:
       Propagate content up (parents), down (children) or sideways
       (siblings). Leaving all checkboxes unchecked means that content will
       not be propagated.

     - Subscribing Members
       Propagate user memberships up (parents), down (children) or sideways
       (siblings). Leaving all checkboxes unchecked means that memberships
       will not be propagated.

     - Unsubscribing Members
       Propagate user memberships removal up (parents), down (children) or
       sideways (siblings). Leaving all checkboxes unchecked means that
       propagation will not happen when unsubscribing memberships.

     - User demotion
       ...

  4. (optional) Go to admin/build/block and enable the Subgroups block.
     This block only shows up when in the context of a group and displays the
     hierarchy for navigation purposes.

  5. Create a group content type, referr to the OG module's README.txt file.

  6. Create a new group node by going to the node/add form. There will be a
     Subgroups fieldset where you can designate a parent group.

--------------------------
PERMISSIONS
--------------------------
  - 'administer groups hierarchy'
    Grant users the privilege to access the module's administrative
    settings page (admin/og/subgroups)

  - 'edit groups hierarchy'
    Grant users the privilege to create and edit hierarchies

--------------------------
Documentation
--------------------------
http://drupal.org/node/267277 - legacy docs. updated docs to come...

--------------------------
MODULES
--------------------------
Subgroups ships with the following sub modules. View the README.txt file of
each sub module for futher details.
  - Hierarchical Select for Subgroups
  - OG Subgroups Context

--------------------------
BLOCKS
--------------------------
OG subgroups module provides a block called 'Subgroups' that shows the 
subgroups tree. The block takes into consideration cases where a user can't 
access a private group but still has access to the node/xxx/subgroups. In such
cases the group will appear as <private group>.

--------------------------
VIEWS
--------------------------
Subgroups has Views integration and provides some fields, arguments, sorts
and filters which are outlined below. The Views Tree module,
(http://drupal.org/project/views_tree), works great for displaying all or a
portion of the subgroup hierarchy in a tree format for blocks or pages display.

Fields:
  - Child Groups
    A list of direct children of a group

  - Parent Group ID
    The nid of the parent group

  - Parent Group Title
    The node title of the parent group

Arguments:
  - Group ID
    Using a group's nid as a starting point, get all group nodes along the
    subgroup path (up, down or sideways).

  - Group ID (for posts)
    Using a group's nid as a starting point, get content that has been posted
    to group nodes along the subgroup path (up, down, sideways).

  - Parent Group ID
    The group ID of a parent node. Filters for groups that has the specified
    parent. Similar to the 'child groups' field but returns each child as a
    separate row.

Sort:
  - Hierarchy Order
    Sort the groups or content by hierarchy order.

Filter:
  - Subgroups overrides the standard OG filter for posts and changes the
    group selector widget to display the groups in a tree format.
