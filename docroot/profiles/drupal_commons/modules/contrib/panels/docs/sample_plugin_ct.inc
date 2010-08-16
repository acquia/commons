<?php
// $Id: sample_plugin_ct.inc,v 1.2.4.2 2009/01/15 23:42:35 merlinofchaos Exp $

/**
@file
Plugin Reference: Content Types

API documentation for Content Type (Soon to be: Pane Type) plugins.
/

/**
@Pplug{content_types,Content Types}
Content type plugins define the content you can put into panes for display; If you want to see a particular piece of content rendered by Panels, you need to write a content type. \n

<p>Remember - although grouping the callbacks defined in these properties into the same .inc file can be handy, you're not bound to doing so. If you have a visibility checker that you want to share across a lot of content types, for example, consider defining the visibility checker in the main .module file while keeping the rest of the plugin in its own .inc file.</p>
<p>Some unnecessary duplication and inelegancies persist in the logic behind content type plugin properties; this is particularly noteworthy in the case of the add/edit property distinctions. These issues are allowed to persist largely for legacy compatibility reasons.</p>
<p>Plugin declaration functions must adhere to a particular naming convention; see panels_get_directories() for details. \n Note that the \pdarray provided by this sample does NOT define a coherent, working content type; displaying the full range of the plugin's flexibility makes it impossible to do so. For working examples, see the various plugins defined in the panels/content_types directory.</p>

@SECplug{content_types,pdfunc,Content Type Plugin Declaration}
<p>This sample \pdfunc returns a definition array containing ALL of the \plugprops that Panels currently allows. The string used for the array key is significant: it determines the 'type' that panes which are created by this plugin will be assigned.</p>
<p>Keep in mind when choosing a type name that namespace collisions are both silent and destructive (the Panels engine will not emit any errors, it will simply overwrite data). Such collisions will always be decided in favor of the last plugin processed; processing order order is generally determined by the weight of the module (in the system table) defining the plugin.</p>
<p>All the plugins that come packaged with Panels necessarily obey a strict naming convention: the array key used for $items is the same as the name of the file itself, as well as being the same as the string prefixed by the module name (in this case, 'panels_'), and affixed by a string that indicates the type of plugin (in this case, 'panels_content_types'). Your modules need not follow the same conventions, although it is recommended that you do if possible; again, refer to panels_get_directories().</p>
@code
function panels_SAMPLE_CT_panels_content_types() {
  $items['SAMPLE_CT'] = array(
    'title' => t('Sample Content Type'),
    'weight' => -10,
    'single' => TRUE,
    'content_types' => 'panels_admin_content_types_SAMPLE_CT',
    'render callback' => 'panels_content_SAMPLE_CT',
    'add callback' => 'panels_admin_add_SAMPLE_CT',
    'edit callback' => 'panels_admin_edit_SAMPLE_CT',
    'add validate callback' => 'panels_admin_validate_SAMPLE_CT',
    'edit validate callback' => 'panels_admin_validate_SAMPLE_CT',
    'add submit callback' => 'panels_admin_submit_SAMPLE_CT',
    'edit submit callback' => 'panels_admin_submit_SAMPLE_CT',
    'title callback' => 'panels_admin_title_SAMPLE_CT',
    'editor render callback' => 'panels_admin_pane_render_SAMPLE_CT',
    'render last' => TRUE,
    'visibility control' => 'panels_admin_visibility_control_SAMPLE_CT',
    'visibility submit' => 'panels_admin_visibility_submit_SAMPLE_CT',
    'visibility check' => 'panels_content_visibility_check_SAMPLE_CT',
    'visibility serialize' => TRUE,
    'role-based access' => FALSE,
    'roles and visibility' => TRUE,
    'form control' => 'panels_admin_form_control_SAMPLE_CT',
  );
  return $items;
}
@endcode \n\n

@SSECplug{content_types,pdfunc,setprops,Overview of Setting Properties}
<p>Only a few of the twenty properties defined for content type plugins are required, and some of them have default values that Panels will set if you don't assign anything. This first table covers setting properties. Keep in mind that although these tables indicate that there are requirements and interdependencies among the properties, there are no systematic checks to ensure that a plugin meets the requirements. Panels simply assumes that you did it right.</p>
\n
<table>
  <tr>
    <td>Property Name</td>
    <td>Data Type</td>
    <td>Required?</td>
    <td>Default Value</td>
    <td>Dependencies</td>
    <td>Notes</td>
  </tr>
  <tr>
    <td>@AAP{content_types,title,title}</td>
    <td>string</td>
    <td>Yes</td>
    <td></td>
    <td>None</td>
    <td>The title that will be used for this pane on the 'Add Content' modal form, and in the display content editor in general. This is a purely internal setting; normal users will never see it.</td>
  </tr>
  <tr>
    <td>@AAP{content_types,weight,weight}</td>
    <td>Integer</td>
    <td>No</td>
    <td>\c 0</td>
    <td>None</td>
    <td>Standard drupal weighting concept at work here; all it determines is the position of this content type's icon relative to the other content type icons on the general Panels configuration forms. See panels_common_settings().</td>
  </tr>
  <tr>
    <td>@AAP{content_types,single,single}</td>
    <td>Boolean</td>
    <td>No</td>
    <td>\c FALSE</td>
    <td>None</td>
    <td>Indicates that this content type plugin provides only a single content type. Currently, this setting is ONLY used in figuring out how to group the content type on the general Panels configuration forms; see panels_common_settings(). Check out panels_admin_content_types_block() for an example of how one plugin can used define multiple content types (technically, multiple subtypes)</td>
  </tr>
  <tr>
    <td>@AAP{content_types,render-last,render last}</td>
    <td>Boolean</td>
    <td>No</td>
    <td><var>FALSE</var><sup>1</sup></td>
    <td>none</td>
    <td>If set to \c TRUE, this pane will be pushed to the back of the line during the render routine. See panels_render_panes().</td>
  </tr>
  <tr>
    <td>@AAP{content_types,visibility-serialize,visibility serialize}</td>
    <td>Boolean</td>
    <td>Yes<sup>2,3</sup></td>
    <td>FALSE</td>
    <td>@LAP{content_types,t-visibility-control,visibility control}</td>
    <td>If \c TRUE, then contents of $pane->visibility will be serialized before being saved to the database. This should be set as \c TRUE if, for example, your visibility form widget uses checkboxes (and therefore generates an array), as opposed to if your widget uses radios (and therefore generates an integer that can be stored directly). See panels_content_config_form_submit() and panels_save_display() to better understand how this works.</td>
  </tr>
  <tr>
    <td>@AAP{content_types,role-based-access,role-based access}</td>
    <td>Boolean</td>
    <td>No</td>
    <td><var>TRUE</var><sup>4</sup></td>
    <td>none</td>
    <td>Boolean setting to indicate whether you want the your content type to utilize the Panels API's built-in access system, which is based on drupal user roles. Set this to FALSE to disable role-based access.</td>
  </tr>
  <tr>
    <td>@AAP{content_types,roles-and-visibility,roles and visibility}</td>
    <td>Boolean</td>
    <td>No</td>
    <td><var>FALSE</var><sup>1</sup></td>
    <td>@LAP{content_types,t-visibility-control,visibility control}</td>
    <td>If you want your content type to use both your custom visibility logic and Panels' built-in roles-based access system, then set this to <var>TRUE</var>. Setting 'role-based access' to <var>TRUE</var> is not sufficient; see panels_ajax_ct_preconfigure() to understand how this works. If you use both systems, panels_pane_access() will \c AND the results together when determining pane visibility.</td>
  </tr>
</table>
\par
<small>
  <sup>1</sup>  Technically, this property doesn't have a default value. However, because the setting is checked using a call to empty(), it effectively has a default value of <var>FALSE</var>.\n
  <sup>2</sup>  Only required if properties it depends upon have been set.\n
  <sup>3</sup>  Note that this will automatically be set to <var>FALSE</var> if the @LAP{content_types,t-visibility-control,visibility control} property is set defined.\n
  <sup>4</sup>  'Required' is a little misleading in this case. it means that Panels needs this property to be set, not that it must be set by the plugin. So, if the default value works for your plugin, you don't have to define this property.\n
</small>\n\n

@SSECplug{content_types,pdfunc,callprops,Overview of Callback Properties}

<p>This table provides a basic summary for all thirteen @LGt{p-p-callback,callback properties}. Most of the properties also have detailed documentation, which can be reached by clicking the property name.</p>
<p>Parameters that are passed by reference from the function side (through call_user_func_array()) are marked with the by-reference operator.</p>
\attention
apis may break. here's how they're likely to. be warned.
\attention
form control is the most subject to change.
\note
'required' and 'dependencies' have specific meanings.

<table>
  <tr>
    <td>Property Name</td>
    <td>Return Value Type</td>
    <td>Required?</td>
    <td>Dependencies</td>
    <td>Parameters</td>
    <td>Notes</td>
  </tr>
  <tr>
    <td>@LAP{content_types,callbacks_content_types,content_types}@AAP{content_types,t-content_types, }</td>
    <td>Array</td>
    <td>Yes</td>
    <td>None</td>
    <td></td>
    <td>Panels calls this function to find out how many content types this plugin provides, as well as some basic 'gatekeeper' information about each of those content types. Most importantly, optional and required context(s) are defined in this function.</td>
  </tr>
  <tr>
    <td>@LAP{content_types,callbacks_render-callback,render callback}@AAP{content_types,t-render-callback, }</td>
    <td>Object</td>
    <td>Yes</td>
    <td>None</td>
    <td><var>$pane->configuration</var><sup>1</sup>, <var>$panel_args</var>, <var>$context</var></td>
    <td>Panels calls this function while preparing a @LGt{display,display object} for viewing. The callback needs to construct and return an object, which is passed along to the @LAP{styles,Style} and @LAP{layouts,Layout} plugins for handling.</td>
  </tr>
  <tr>
    <td>@LAP{content_types,callbacks_add-callback,add callback}@AAP{content_types,t-add-callback, }</td>
    <td>FAPI Array</td>
    <td>No</td>
    <td>None</td>
    <td><var>$subtype</var>, <var>$parents</var>, <var>$pane->configuration</var><sup>1,2</sup></td>
    <td>This function gets called when the user clicks an icon to add a new pane (from the 'Add Content' @LGt{modal,modal form}). note that it is often possible to use the same, or nearly the same, callback for this as for the @LAP{content_types,callbacks_edit-callback,edit callback}.</td>
  </tr>
  <tr>
    <td>@LAP{content_types,callbacks_edit-callback,edit callback}@AAP{content_types,t-edit-callback, }</td>
    <td>FAPI Array</td>
    <td>No</td>
    <td>None</td>
    <td><var>$subtype</var>, <var>$parents</var>, <var>$pane->configuration</var></td>
    <td>This function gets called when the user clicks the 'Configure' button on an already-existing pane; it partially governs what appears on the resulting configuration modal.</td>
  </tr>
  <tr>
    <td>@LAP{content_types,callbacks_addedit-validate-callback,add/edit validate callback}@AAP{content_types,t-addedit-validate-callback, }</td>
    <td></td>
    <td>No</td>
    <td>None<sup>3</sup></td>
    <td><var>$form</var>, <var>$form_values</var></td>
    <td>Defines a callback to be used as a FAPI validator, but only for the $form_values set by form items defined in the @LAP{content_types,callbacks_edit-callback,add/edit callback}.</td>
  </tr>
  <tr>
    <td>@LAP{content_types,callbacks_addedit-submit-callback,add/edit submit callback}@AAP{content_types,t-addedit-submit-callback, }</td>
    <td>part of the <var>$pane->configuration</var> Array</td>
    <td>No</td>
    <td>None<sup>3</sup></td>
    <td><var>$form_values</var></td>
    <td>Defines a callback to be used as a FAPI submit handler, but only for the $form_values set by form items defined in the @LAP{content_types,callbacks_edit-callback,add/edit callback}.</td>
  </tr>
  <tr>
    <td>@LAP{content_types,callbacks_title-callback,title callback}@AAP{content_types,t-title-callback, }</td>
    <td>String</td>
    <td>Yes</td>
    <td>None</td>
    <td><var>$pane->configuration</var>, <var>$context</var></td>
    <td>This function determines the title that the pane will use in the display content editor, and ONLY that title.</td>
  </tr>
  <tr>
    <td>@LAP{content_types,callbacks_editor-render-callback,editor render callback}@AAP{content_types,t-editor-render-callback, }</td>
    <td>String</td>
    <td>No</td>
    <td>None</td>
    <td><var>$display</var>, <var>$pane</var></td>
    <td>This function determines the title that the pane will use in the display content editor, and ONLY that title.</td>
  </tr>
  <tr>
    <td>@LAP{content_types,callbacks_visibility-control,visibility control}@AAP{content_types,t-visibility-control, }</td>
    <td>FAPI Array</td>
    <td>No</td>
    <td>None</td>
    <td><var>$contexts</var>, <var>$subtype</var>, <var>$pane->configuration</var>, <var>$add</var></td>
    <td>This callback is fired shortly after the add/edit callbacks. Use it to create a form widget form widget from which the user can select values that will make sense when passed to your @LAP{content_types,callbacks_visibility-check,visibility check callback}.</td>
  </tr>
  <tr>
    <td>@LAP{content_types,callbacks_visibility-submit,visibility submit}@AAP{content_types,t-visibility-submit, }</td>
    <td>Mixed</td>
    <td>No</td>
    <td>@LAP{content_types,callbacks_visibility-control,visibility control}</td>
    <td><var>$contexts</var>, <var>$subtype</var>, <var>$pane->configuration</var>, <var>$add</var></td>
    <td>The custom submit handler for your content type's visibility settings. This function is passed the portion of the $form_values array that was generated from the widgets created by the @LAP{content_types,callbacks_visibility-control,visibility control} callback. Most plugins won't need to define this property, even if they define custom visibility control.</td>
  </tr>
  <tr>
    <td>@LAP{content_types,callbacks_visibility-check,visibility check}@AAP{content_types,t-visibility-check, }</td>
    <td>Boolean</td>
    <td>Yes<sup>4</sup></td>
    <td>@LAP{content_types,callbacks_visibility-control,visibility control}</td>
    <td><var>$contexts</var>, <var>$subtype</var>, <var>$pane->configuration</var>, <var>$add</var></td>
    <td>Panels calls this function during the pane accessibility checking routine, which is handled by primarily by panels_pane_access(). Define the logic governing your content type's visibility here.</td>
  </tr>
  <tr>
    <td>@LAP{content_types,callbacks_form-control,form control}@AAP{content_types,t-form-control, }</td>
    <td>FAPI <var>$form</var> Array</td>
    <td>No</td>
    <td>None</td>
    <td><var>&$form</var>, <var>&$pane</var>, <var>&$display</var></td>
    <td>If the other callbacks governing the add/edit form (i.e., the @LAP{content_types,callbacks_edit-callback,add/edit callback} properties or the @LAP{content_types,callbacks_visibility-control,visibility control} property) aren't enough for your needs, then implement this callback. This function is passed virtually all of the Panels editing data by reference. Use with caution.</td>
  </tr>
</table>
\par
<small>
  <sup>1</sup>  In the sample functions, the variable <var>$conf</var> is used. <var>$pane->configuration</var> is used here instead because that's the value being passed in, and it has meaning out of context, unlike <var>$conf</var>.\n
  <sup>2</sup>  Because this is a new pane, its configuration is always going to be empty.\n
  <sup>3</sup>  Even if you haven't defined the add/edit callback property, you can still define the validate/submit properties - Panels doesn't check. Of course, if you do so, your callback will be passed a great big <var>NULL</var>...\n
  <sup>4</sup>  Only required if properties it depends upon have been set.\n
</small>\n

<hr>
\n


@SECplug{content_types,callbacks,Discussion and Samples of Callbacks}

@SSECplug{content_types,callbacks,content_types,Callback Property: 'content_types'}
Callback function set by the @LAP{content_types,t-content_types,content_types} property. Returns an array of data that Panels uses to determine:
    - Whether or not the content type can be added to this display, based on
      what context(s) are available.
    - If context requirements are met, the remainder of the array's data
      defines the icon, title, and description that the content type will
      be rendered with on the the Add Content @LGt{modal,modal}.\n\n

@code
function panels_admin_content_types_SAMPLE_CT() {
  return array(
    // As with the plugin declaration, the value of this array key is significant:
    // it will become the pane's subtype, stored in $pane->subtype.
    'content' => array(
      // The name used for this subtype on the Add Content modal - this is what
      // appears right below the icon.
      'title' => t('SAMPLE CONTENT TYPE'),
      // The name of the icon file to be used for this subtype.
      'icon' => 'icon_node.png',
      // The server path to the directory where the above icon is located.
      'path' => panels_get_path('plugins/content_types/node'),
      // The 'description' appears as a tooltip when the user hovers their
      // mouse pointer over the icon.
      'description' => t('Descriptive text for the SAMPLE CONTENT TYPE, to be used in the tooltip.'),
      // This property indicates which contexts are prerequisites for the content
      // type to be used. If a display lacks a context required by this content
      // type, then it simply will not be displayed. Multiple required contexts
      // can be declared by placing each context into an indexed array.
      'required context' => new ctools_context_required(t('Sample Required Context'), 'sample_context_required'),
      // This property has the same syntax as 'required context', but if optional
      // context requirements are not met, the content type will still be usable,
      // simply in a reduced form. It's up to the plugin author to define just how
      // different that functionality by writing varying the behavior of this plugin's
      // other callbacks according to the presence/absence of the context.
      'optional context' => new ctools_context_optional(t('Sample Optional Context'), 'sample_context_optional'),
      // Category is the group this subtype's icon will be placed in. The first
      // item in the array is the category name, and the second is the subtype's
      // weight in that category (used for ordering the subtypes in the category
      // relative to one another). Omitting a value for weight will cause it to
      // default to 0; if you do omit the weight, you can simply return the
      // t()-wrapped string title of the content type - no need to put it in an array.
      'category' => array(t('Node context'), -9),
    ),
  );
}
@endcode


<hr>


@SSECplug{content_types,callbacks,render-callback,Callback Property: 'render callback'}
Callback function set by the @LAP{content_types,t-render-callback,render callback} property. This callback constructs and returns an object for display.

The sample function below is a direct copy of the node_content plugin's render
callback; abstract example cases are of little use from here on out. Note that
this case only implements three parameters, but there is also a fourth. Your
content type can use as few/many of these parameters as you want, although
you won't be able to much if you don't implement the first parameter, $conf.

@param array $conf
 The contents of $pane->configuration. This will be an array with the following
 keys, by default:
   - override_title (int/bool): 0 or 1, reflecting whether the user checked the
     'override title' checkbox on the pane configuration form.
   - override_title_text (string): a string containing the title override, as
     written by the user on the pane configuration form.
   - css_id (string): the special css id entered by the user on the pane config
     form, if any.
   - css_class (string): same idea as the css id.
   - module (string): a string containing the name of the module implementing
     this content type (or, in some cases, owning/generating the content).\n
The above keys reflect the standard set of form items that the Panels API
provides to every pane type by default. Any additional configuration items that
you add (via the add/edit callbacks) will also appear in $conf by default.
@param array $panel_args
 An indexed array of all arguments, if any, that have been passed to the display.
@param mixed $context
 The contents of $context can vary widely. If only one context is being passed
 to the pane, $context will simply be that context object. If multiple contexts
 are passed, however, then $context will be an indexed array of those contexts.
 The sort of data contained in the context is completely dependent on the how
 that context has been defined.
@param $incoming_content

@return object $block
 An object, ready to be passed through the styling & theming layers. At minimum,
 the object should contain a 'content' element, as well as 'title' and/or
 'subject' elements. If a 'title' element is not included, then the 'subject'
 is copied into $block->title later on in the render process. You are free to
 define as many elements as you want, but those elements will only be used
 if you write a panels style plugin specifically designed to take advantage of
 of them. Note that the '$block' variable name used here is arbitrary.

@code
function panels_content_SAMPLE_CT($conf, $panel_args, $context) {
  // The node_content content_type plugin has a required context of 'node.'
  // This simply double-checks to make sure that the necessary context is present;
  // in particular, it excludes 'empty' contexts, which are used primarily during
  // the edit process.
  if (!empty($context) && empty($context->data)) {
    return;
  }

  // The node context plugin stores an entire, fully-loaded $node object into
  // its $context->data element; this pulls that node data out (via cloning, to
  // ensure the original context data itself remains unchanged) and stores it in
  // a correspondingly-named variable, $node.
  $node = isset($context->data) ? drupal_clone($context->data) : NULL;
  $block->module = 'node';
  // Stores the nid from the context, to ensure it is acecssible later.
  $block->delta = $node->nid;

  // Just in case the context didn't load, but managed to get past the initial
  // checks, this adds filler content to the $block.
  if (empty($node)) {
    $block->delta = 'placeholder';
    $block->subject = t('Node title.');
    $block->content = t('Node content goes here.');
  }
  else {
    if (!empty($conf['identifier'])) {
      $node->panel_identifier = $conf['identifier'];
    }

    $block->subject = $node->title;

    unset($node->title);
    // The pane's content is a complex enough operation that we delegate creating
    // it to a helper function.
    $block->content = panels_admin_SAMPLE_CT($node, $conf);
  }

  // If the user has the necessary permissions, an 'admin link' is generated.
  // Admin links are the special links that appear above the pane's title when
  // you mouse over the pane.
  if (node_access('update', $node)) {
    $block->admin_links['update'] = array(
      'title' => t('Edit node'),
      'alt' => t("Edit this node"),
      'href' => "node/$node->nid/edit",
      'query' => drupal_get_destination(),
    );
  }

  if (!empty($conf['link']) && $node) {
    $block->title_link = "node/$node->nid";
  }

  return $block;
}
@endcode

Probably the most important thing to be noted about this helper function is
just how similar it is to node.module's routine for node rendering.
In fact, it's little more than a minor rewrite of
<a href="http://api.drupal.org/api/function/node_view/5">node_view()</a>; the first lines are lifted directly from <a href="http://api.drupal.org/api/function/node_build_content/5">node_build_content()</a>,
and the latter half from node_view().

@code
function panels_admin_SAMPLE_CT($node, $conf) {
  // Remove the delimiter (if any) that separates the teaser from the body.
  $node->body = str_replace('<!--break-->', '', $node->body);

  // The 'view' hook can be implemented to overwrite the default function
  // to display nodes.
  if (node_hook($node, 'view')) {
    $node = node_invoke($node, 'view', $conf['teaser'], $conf['page']);
  }
  else {
    $node = node_prepare($node, $conf['teaser']);
  }

  if (empty($conf['no_extras'])) {
  // Allow modules to make their own additions to the node.
    node_invoke_nodeapi($node, 'view', $conf['teaser'], $conf['page']);
  }

  if ($conf['links']) {
    $node->links = module_invoke_all('link', 'node', $node, $conf['teaser']);

    foreach (module_implements('link_alter') AS $module) {
      $function = $module .'_link_alter';
      $function($node, $node->links);
    }
  }

  // Set the proper node part, then unset unused $node part so that a bad
  // theme can not open a security hole.
  $content = drupal_render($node->content);
  if ($conf['teaser']) {
    $node->teaser = $content;
    unset($node->body);
  }
  else {
    $node->body = $content;
    unset($node->teaser);
  }

  // Allow modules to modify the fully-built node.
  node_invoke_nodeapi($node, 'alter', $conf['teaser'], $conf['page']);

  return theme('node', $node, $conf['teaser'], $conf['page']);
}
@endcode


<hr>


@SSECplug{content_types,callbacks,add-callback,Callback Property: 'add callback'}
Callback function set by the @LAP{content_types,t-add-callback,add callback} property. This callback constructs
the pane configuration form for newly-added panes. This sample is lifted from
the block content type plugin (block.inc); it is the only built-in Panels content
type that implements an add callback that is different from the edit callback.

Clearly there's relatively little need to differentiate between the add and edit
callbacks; the only thing this one does is make sure that $conf has some of the
right values before heading into the edit form. You still need to define both the
'add callback' and 'edit callback' properties in the plugin declaration array, but you
can just make them point to the same function.

See the edit callback for more detailed discussion. \n

@code
function panels_admin_add_SAMPLE_CT($id, $parents, $conf = array()) {
  list($conf['module'], $conf['delta']) = explode('-', $id, 2);
  return panels_admin_edit_SAMPLE_CT($id, $parents, $conf);
}
@endcode


<hr>


@SSECplug{content_types,callbacks,edit-callback,Callback Property: 'edit callback'}
Callback function set by the @LAP{content_types,t-edit-callback,edit callback} property in the plugin declaration array.
This callback constructs the configuration form for panes that have already been added;
the callback is fired when the 'Configure' button is clicked.

This function essentially operates like a limited and targeted implementation of
<a href="http://api.drupal.org/api/function/hook_form_alter/5">hook_form_alter()</a>; the Panels API wrangles FAPI as needed, so all you need to do
is add the widgets you want for your content type/subtype.

\note
In future versions, the 'Block visibility' properties are likely to be moved into
the appropriate visibility callbacks. They're here now because the block content type
plugin was written long before the visibility system was introduced.

Some of the techniques used in this edit callback are pretty advanced. For a more basic
but quite thorough implementation of this callback, see panels_admin_edit_node_content().

@param string $id
 The subtype of the pane being edited. The block panels content type plugin calls this
 variable '$id' for legacy reasons; we recommend you call this variable $subtype if you
 want your variable names to be optimally descriptive of their values.
@param array $parents
 This parameter is largely deprecated, and is included for legacy API compatibility. Its
 intention was to provide information to form widgets about where they live on the $form.
 It is likely to disappear in Panels3. For all add/edit callbacks:
 @code $parents = array('configuration'); @endcode
 This corresponds to the fact that the $form returned from this callback will not be added
 to the root of the overall $form array, but to the $form['configuration'] sub-array.
 See panels_content_config_form().
@param array $conf
 The contents of $pane->configuration, if any.
@return array $form
 A standard FAPI form array.


@code
function panels_admin_edit_SAMPLE_CT($id, $parents, $conf) {
  $form['module'] = array(
    '#type' => 'value',
    '#value' => $conf['module'],
  );
  $form['delta'] = array(
    '#type' => 'value',
    '#value' => $conf['delta'],
  );

  if (user_access('administer advanced pane settings')) {
    $form['block_visibility'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use block visibility settings (see block config)'),
      '#default_value' => $conf['block_visibility'],
      '#description' => t('If checked, the block visibility settings for this block will apply to this block.'),
    );
    // Module-specific block configurations.
    if ($settings = module_invoke($conf['module'], 'block', 'configure', $conf['delta'])) {
      // Specifically modify a couple of core block forms.
      if ($conf['module'] == 'block') {
        unset($settings['submit']);
        $settings['info']['#type'] = 'value';
        $settings['info']['#value'] = $settings['info']['#default_value'];
      }
      panels_admin_fix_block_tree($settings);
      $form['block_settings'] = array(
        '#type' => 'fieldset',
        '#title' => t('Block settings'),
        '#description' => t('Settings in this section are global and are for all blocks of this type, anywhere in the system.'),
        '#tree' => FALSE,
      );


      $form['block_settings'] += $settings;
    }
  }

  return $form;
}
@endcode


<hr>


@SSECplug{content_types,callbacks,addedit-submit-callback,Callback Property: 'add/edit submit callback'}
Callback function set by the @LAP{content_types,t-addedit-submit-callback,edit callback}'[add|edit] submit callback' property in the plugin
declaration array. In simpler plugins, you won't need to implement this callback;
any values set by the widgets you added to the config form will automatically
have their data added to the $pane->configuration array, which is serialized
and stored in the panels_pane table.

However, in cases where the settings being changed on this form need to be
reflected in some other data structure, this callback can be used to ensure
that the necessary changes are made. In this example (again from the block
content type plugin), hook_block() is invoked with $op = 'save' for the module
that owns the block, thereby allowing the normal block saving routine to
do its thing.


@code
function panels_admin_submit_SAMPLE_CT(&$form_values) {
  if (!empty($form_values['block_settings'])) {
    module_invoke($form_values['module'], 'block', 'save', $form_values['delta'], $form_values['block_settings']);
  }
}
@endcode


<hr>


@SSECplug{content_types,callbacks,title-callback,Callback Property: 'title callback'}
Callback function set by the @LAP{content_types,t-title-callback,title callback} property in the plugin definition array.

Returns the title to be used in the display editor ONLY. When the pane is
rendered for viewing, the value of $obj->title or $obj->subject, as returned
from the callback defined in the 'render callback' property, will become the
pane's title. The only way the value returned from here will show up as the
pane's title upon viewing is if this callback is explicitly called from the
render callback itself (i.e., @code $obj->title = panels_admin_title_SAMPLE_CT($conf, $context); @endcode)

@param array $conf
 The contents of $pane->configuration, if any.
@param mixed $context
 The contents of $context can vary; see other sample callback parameters for details.
@return string $title
 The title to use for the pane in the display editor. Make sure to run it through t(), first.


@code
function panels_admin_title_SAMPLE_CT($conf, $context) {
  return t('"@s" content', array('@s' => $context->identifier));
}
@endcode

@SSECplug{content_types,callbacks,editor-render-callback,Callback Property: 'editor render callback'}
Callback function set by the @LAP{content_types,t-editor-render-callback,editor render callback} property in the plugin definition array.

Returns object used to populate the content area of the pane in the display
editor ONLY.

@param object $display
 The full display object being edited.
@param object $pane
 The pane object being rendered for display editing.

@return object
 The object containing the data to use when rendering the pane. The two fields in the object that are used for rendering are @code $obj->title @endcode, which is used as the title on the collapsible fieldset, and @code $obj->content @endcode, which is the contents of fieldset (if any).

@code
function panels_admin_pane_render_SAMPLE_CT($display, $pane) {
  // Pretend your content type stores a node id in the $configuration array
  // and that you want the title of that node as the fieldset title, and the
  // teaser for that node as the content.
  $node = node_load($pane->configuration['nid']);
  $block = new stdClass();
  $block->title = check_plain($node->title);
  $block->content = node_view($node, TRUE);
  return $block;
}
@endcode

<hr>


@SSECplug{content_types,callbacks,visibility-control,Callback Property: 'visibility control'}
Callback function set by the @LAP{content_types,t-visibility-control,visibility control} property in the plugin declaration array.

If your plugin defines this property, you'll need to be cognizant of your definitions for several other properties: @LAP{content_types,callbacks_visibility-submit,visibility submit}, @LAP{content_types,callbacks_visibility-check,visibility check} and @LAP{content_types,visibility-serialize,visibility serialize}. @LAP{content_types,roles-and-visibility,roles and visibility} is also relevant, but won't be useful to the vast majority of content type plugins.

Operates quite similarly to the add and edit callbacks, with a few exceptions:
   - The FAPI parent is $form['visibility'] instead of $form['configuration']
   - Instead of creating separate callbacks for add and edit, the $add parameter
     indicates which operation is taking place.
   - Whereas a submit handler is often unnecessary for the add/edit callbacks,
     implementing this callback property means you need to be cognizant of several
     other properties in the definition array.
The visibility widget defined in this function is a reworked version of one originally
created for og_panels (but was not/has not yet been committed); the goal is to control
pane visibility according to the status of the current user relative to the group.

Remember, this is NOT where you define the logic behind your visibility handling -
all you're doing here is providing a form widget that to get some data. It's up to
your visibility checker, defined in the @LAP{content_types,callbacks_visibility-check,visibility check} callback, to create the
logic that can take the data from here and make the right decision about pane
visibility.

If you define a more complex system that uses multiple widgets, make sure to return
them all stacked inside a single array, and that you set the FAPI <var>tree</var> property to <var>TRUE</var> as needed.

@param mixed $contexts
 As in the render callback, this is either a context object, or an array of context
 objects. It's unnecessary and probably unwise to include this context
 data directly in the values that get saved in your form visibility function; that
 very same data will be available via the $display variable that's passed to the
 checker. Rather, $context is provided in the event that your visibility widget
 needs to vary depending on some information in $context.
@param string $subtype
 The contents of $pane->subtype for the pane currently being edited.
@param array $conf
 The contents of $pane->configuration, if any.
@param bool $add
 If TRUE, then a new pane is being added. If FALSE, then an existing pane is being edited.
@return array $visibility_widget
 A standard FAPI widget, to be added to the form.


@code
function panels_admin_visibility_control_SAMPLE_CT($contexts, $subtype, $conf, $add) {
  return $visibility_widget = array(
    '#type' => 'radios',
    '#title' => t('Pane Visibility'),
    '#description' => t('Who should this pane be visible to?'),
    '#options' => array(
      'all' => t('Everyone'),
      'member' => t('Only group members'),
      'nonmember' => t('Only group non-members'),
      'admin' => t('Group administrators'),
      ),
    '#default_value' => isset($conf['visibility']) ? $conf['visibility'] : 0,
  );
}
@endcode


<hr>


@SSECplug{content_types,callbacks,visibility-check,Callback Property: 'visibility check'}
Callback function set by the @LAP{content_types,t-visibility-check,visibility check} property in the plugin definition array.

This function takes advantage of cached static variables to increase performance. On any
given page request, we know that only ONE group is going to be accessed, and only ONE user
is going to be doing the accessing. Since the static keyword only lasts through a single page
request, and nid and uid are the two variables that visibility depends upon in this case,
we only have to query the database and build the $visibility array once, no matter how many
panes fire this callback to determine visibility during this page request.

@param object $pane
 The fully-loaded $pane object that we're running the visibility check against. The
 value set by the widget defined in the @LAP{content_types,callbacks_visibility-control,visibility control} callback is contained
 in $pane->visibility.
@param object $display
 The fully-loaded display object that's currently being rendered. If you need $context
 to figure out what action to take, you'll find it/them in $display->context.
@param object $user
 The current $user - the same as what you'd get from <var>global $user</var>.
 Passed for convenience, since visibility is often dependent on the $user.
@return bool
 A boolean indicating if the pane should (TRUE) or should not (FALSE) be visible.


@code
function panels_content_visibility_check_SAMPLE_CT($pane, $display, $user) {
  // use static variable to somewhat reduce queries for complex og_panels pages
  static $visible;
  if (!is_array($visible)) {
    $visible = array();
    $visible['all'] = TRUE;
  }
  if (!isset($visible[$pane->visibility])) {
    $members = array();
    $sql = "SELECT u.uid AS uid, ogu.is_admin AS admin FROM {og_uid} ogu
            INNER JOIN {users} u ON ogu.uid = u.uid WHERE ogu.nid = %d
            AND ogu.is_active = 1 AND u.status = 1 ORDER BY ogu.created DESC";
    // $display holds the context; the $data element of $context holds a node object,
    // and we want the nid of that node.
    $result = db_query($sql, $display->context->data->nid);
    while ($account = db_fetch_array($result)) {
      $members[$account['uid']] = $account['admin'];
    }
    $visible['member'] = in_array($user->uid, array_keys($members));
    $visible['nonmember'] = !$visible['member'];
    $visible['admin'] = $visible['member'] ? $members[$user->uid] : FALSE;
  }
  return $visible[$pane->visibility];
}
@endcode


<hr>


@SSECplug{content_types,callbacks,visibility-submit,Callback Property: 'visibility submit'}
Callback function set by the @LAP{content_types,t-visibility-submit,visibility submit} property in the plugin definition array.
This sample submit handler below is valid for the sample @LAP{content_types,callbacks_visibility-control,visibility control} callback. However, the submit handler itself is
also completely superfluous - the Panels API's built-in handler is entirely
adequate in this case. It is included purely as an excuse to discuss the
parameters of this function, and the different ways in can work.

Implement this if you need to wrangle that data before the Panels API's data storage routines kick in, or if the API's built-in routines are inadequate and you need to build a custom storage mechanism. See panels_content_config_form() and panels_content_config_form_submit() to grok the logic behind if/when/how this callback is triggered.

Most use cases for the Panels visibility system will not need to implement a
submit handler, as the built-in handler in panels_content_config_form_submit()
is adequate for taking care of the data. However, if you need to manipulate
the data generated by your form widget before it gets saved, or if you need
to inform a custom external storage mechanism, hook, whatever, about the
visibility setting, then you should do so here.

Whatever you return from this callback will be saved as the value of
<var>$pane->visibility</var>. If it is a data type that must be serialized before being
put in the database (arrays and objects), then make sure to set the 'visibility
serialize' property to TRUE for this content type.

Note that in this particular sample implementation, the 'visibility serialize'
property should be set to FALSE, as the value produced by the widget in the
sample @LAP{content_types,callbacks_visibility-control,visibility control} function returns a simple string. Because 'visibility
serialize' is FALSE by default, you can also simply not set the property.

Note also that the visibility field in the panels_pane table is the standard
'text' field. The save routines in panels_save_display() will always
convert the value to a string, so bear in mind: even if you send an integer
in, you'll get a string of that number back out on the other end.

@param string $form_value_visibility
  $form_values['visibility'], is the sole argument passed to this callback.
@param bool $add
  As in the @LAP{content_types,callbacks_visibility-control,visibility control} callback parameters: if TRUE, then we're
  in the submit phase for adding a new pane. If <var>FALSE</var>, then we're in the submit phase of an existing pane.
@param object $pane
  The fully-loaded $pane object that we're submitting. Provided primarily for
  content types with complex data storage needs that may be dependent on data
  contained $pane object.
@param object $display
  The fully-loaded $display object that's currently being edited. As with $pane,
  provided primarily for complex implementations that may need some of the data.
@return mixed $form_value_visibility
  This value will be assigned to $pane->visibility, and eventually saved to the
  panel_pane table into the corresponding 'visibility' field.


@code
function panels_admin_visibility_submit_SAMPLE_CT($form_value_visibility, $add, $pane, $display) {
  return $form_value_visibility;
}
@endcode


<hr>


@SSECplug{content_types,callbacks,form-control,Callback Property: 'form control'}
Callback function set by the @LAP{content_types,t-form-control,form control} property in the plugin declaration array.

This callback allows you full control over not only the $form array, but also the
current $pane and $display objects; all three are passed by reference. Note that
they will be passed by reference whether or not you prefix the parameters with
the reference operator; it is included in the below parameters purely for
explanatory purposes. See panels_content_config_form() for the context.

The callback is fired after all other form operations have been performed
immediately, before the fully-built $form is sent back to FAPI for handling.
Changes you make to the $pane and $display objects will also be preserved, as
a call to panels_cache_set() is made. The TRULY intrepid can extract the $cache
object from the value property in <var>$form['vars']</var> and play with that.

This property is provided primarily as a means of allowing significant control
over the innerworkings of the Panels content editing API, without necessitating
direct hacks of the API itself. Probably the most common use case is hiding
some/all of the form widgets that the Panels API adds to all content forms -
the sample function contains a technique for doing just that.

CAUTION: This is an advanced, dangerous feature. Improper use of it can severely
break your content type, and even has the potential to wreak havoc with your
permanent Panels data. Be sure to test implementations of it thoroughly before
putting them in a production environment.

@param array $form
  The all-but-complete FAPI $form array that generates the add/edit content
  form.
@param object $pane
  The fully-loaded $pane object that's currently being edited.
@param object $display
  The fully-loaded $display object that's currently being edited.
@param bool $add
  As in the @LAP{content_types,callbacks_visibility-control,visibility control} callback parameters: if TRUE, then we're
  in the submit phase for adding a new pane. If <var>FALSE</var>, then we're in the submit phase of an existing pane.


@code
function panels_admin_form_control_SAMPLE_CT(&$form, &$pane, &$display) {
  // A technique for stripping all the Panels-provided form widgets from the add/edit form.
  // We'll just replace them all with 'value'-type elements and store the default values.
  foreach ($form['configuration'] as $element => $settings) {
    // Get rid of the formatting elements, if they exist.
    if (in_array($element, array('aligner_start', 'aligner_stop', 'override_title_markup'))) {
      unset($form['configuration'][$element]);
      continue;
    }
    // Skip form elements that aren't generated by the Panels API.
    if (!in_array($element, array('override_title', 'override_title_text', 'css_id', 'css_class'))) {
      continue;
    }
    // We're down to the four we want to get rid of. Now, let's pull out the default values
    $defaults[$element] = $settings['#default_value'];
    unset($form['configuration'][$element]);
  }
  reset($defaults);
  while (list($element, $value) = each($defaults)) {
    $form['configuration'][$element] = array(
      '#type' => 'value',
      '#value' => $value,
    );
  }
  // Now, the (default) values will still be present, and the submit function will work normally
}
@endcode


 */