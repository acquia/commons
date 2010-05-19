; $Id: README.txt,v 1.1.2.4 2009/08/22 19:33:31 alexk Exp $

User Relationship Node Access
-----------------------------
Lets users set node permissions according to their relationships

The module allows node authors to share their posts with users with whom they have an establish relationship. It's also possible to grant edit and delete rights to related users. If you use Organic Groups, the module allows author's related users who aren't in any selected OG audience to still access the post. This module on its own does not deny access to any content.

Configuration
-----------------
1. Enable the module under Admin -> Site Building -> Modules
2. Under Administer -> Users -> Permissions, enable the "grant view permission to related users" permission to desired user roles that will be sharing their posts with their related users. For example, authenticated users
3. Under Administer -> Content Management -> Posting to social network enable the content types you with to be shareable. For our example, we'll enable Blog entry. Content types that are not checked will not have the "Post to social network" fieldset on the node creation/edit form
4. Now, when a user in the role you set in step 2 goes to create one of the enabled content types, they will see a fieldset called "Post to social network". In it they can check which types of relationships (out of those defined on your site) can see this post.

Advanced usage
-----------------
If you grant additional permissions "grant edit permission to related users" and "grant delete permission to related users", the form component on node creation form will change to a more complicated matrix of checkboxes, where node author can allow certain relationships to also edit and/or delete the node. This can be used for peer review, document approval, and other use cases.

Theming
-----------------
The standard "Post to social network" form component can be themed using standard Drupal form theming approaches. See http://api.drupal.org/api/file/developer/topics/forms_api.html/6.
Advanced form component "User Relationships Node Access" is themed by function theme_user_relationship_node_access_form($form), which you can override in your theme.
