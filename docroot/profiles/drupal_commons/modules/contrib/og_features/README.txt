OVERVIEW
-------------------------------------------
OG Features aims to allow group owners and site administrators to disable 
certain Features within a given group without the use of the Spaces module.

What is a feature? A feature can either be a normal feature created by
the Features module, or it can be a module that bundles existing components
of your site; so, OG Features, does not require the Features module. A 
Feature or Module can provide one or many OG Features. 

If a user has adequate permissions, and there are toggleable features 
available, a tab will appear on the group labeled "Featured" which 
provides a checkbox to enable/disable each feature for that group.


HOW IT WORKS
-------------------------------------------
og_features uses a number of hooks and alters to effectively disable the
components specified in each toggleable feature. hook_menu_alter() hijacks 
the access callback for every single menu item, and passes all relevant 
menu information into the custom access callback used to analyze each item. 
The custom access callback then attempts to detect the current group context, 
determines which features have been disabled for that group, and will deny 
access if the page originates from a component in any of the disabled features. 
If there is no group, or if the the request is not from a denied feature, 
the original access callback will be invoked to determine access. Other 
hooks used to prevent access to certain components:

* hook_og_links_alter() 
 - To remove disabled node types from the og details block
 - To remove specified link keys
* hook_context_load_alter() [
 - To remove contexts from disabled features
* hook_views_exposed_form_alter() [
 - To remove disabled node types from any node type filters
* hook_form_alter() 
 - To remove groups from the group selection on group posts if the node 
   has been disabled for that group
* hook_panels_pre_render() 
 - To remove views and panel panes from panels
* hook_views_query_alter()
 - To remove disabled node types from node views


WHAT IS SUPPORTED
-------------------------------------------
* Node types
 - Will remove the group from group post node forms where you select 
   which groups to add the node to
 - Will remove the node type from exposed view filters for node type
 - Will remove the node type from the og links block
 - Will remove nodes from Views inside a group if the node type is disabled
* Views
* Context
* Panel panes
* Page paths
 - For example, some modules add a tab to group home page. You can specify 
   the path for OG Features to disable within the group
 - OG Features will also automatically disable any custom page callbacks 
   implemented inside the feature itself
* OG menu links
 - Provide the key of the link inside the group details block
 

ADMIN SETTINGS
-------------------------------------------
Navigate to the OG features admin page inside the OG admin menu. From there,
you can set global settings for each OG feature, for each group type. The
available options for each OG feature, for each node type, are "toggle"
(group admins can toggle the feature), "always enabled", or "always 
disabled". If the feature is not set to "toggle", it won't show on the
group "Features" tab.


WHAT IS MISSING
-------------------------------------------
Ability to make feature customizations, not just disable/enable (possible?)


HOOKS/API (INTEGRATION)
-------------------------------------------
See og_features.api.php


OTHER USEFUL FUNCTIONS
-------------------------------------------
og_features has some other useful functions that other modules and features 
might find useful.

* og_features_feature_is_disabled($feature, $group = NULL)
 - Determine if a feature is disabled for a given group, or the current 
   group if group is omitted.
 - This could be useful for features/module that add links to the og_links 
   block
* og_features_component_is_disabled($type, $name, $group = NULL)
 - Determine if a certain feature component is disabled
 - Example: og_features_component_is_disabled('node', 'discussion');
* og_features_in_feature($feature, $type, $name)
 - Determine if a feature component is part of a certain feature 
   (applies only to what is supplied in hook_og_features())
 - Example: og_features_in_feature('document_feature', 'views', 'og_tab_document');
