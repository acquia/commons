<h2> Features yet implemented </h2>
<ul>
 <li><b>You get tag suggestions based on your current content!*</b></li>
 <li> Adding a suggestion using one-click</li>
 <li> Tagging using a 'nicer' and easier visual interface.</li>
 <li> <b>No comma-seperated lists anymore!</b></li>
 <li> Using mouse to one-click-remove assigned tags.</li> 
 <li> Supports several tagging-vocabularies on one node-edit form</li> 
 <li> Use the simple suggestion-API or the alter methods to add new suggestions</li> 
 <li> Theme the whole output</li> 
 <li> Reuse the form-element 'tagging_widget'</li>
</ul>

<b>You can see how the plugin works - just look into this <a href="http://wiki.impressive-media.de/doc/tagging-unleashed-drupal-module-implements-easy-tagging-with-suggestions?fullsize=1">video-podcast</a></b>

<h2> Compatibility / Dependencies </h2>
<h3>Server Dependencies</h3>
none (optional extractor)
<h3>Client Browser Dependencies</h3>
 - Javascript
 - <b>This plugin works in: IE6, IE7, IE8, FF(3.0.x - 3.5.x), Safari, Opera(9.63)</b>

<h2>Installation</h2>
You need JQuery and taxonomy, which are both in the Drupal-Core.
<ol>
 <li>Just activate the module and then create or edit a tag-Vocabulary.</li>
 <li>Now check the checkbox "Tagggin Widget" in the vocabulary settings</li>
 <li>Got to the configuration page if you like. Disable or enable to the suggestions example and set the maximum amount of suggestions to show</li>
 <li>Edit a node - use the new widget</li>
 <li>*(optional) If you want a expamle suggestion-implementation based on your content, you have to install extractor. http://drupal.org/project/extractor
<ol>
<li>Just enable the module - your done.</li>
</ol>
</ol>

<h2> Goals </h2>

<h3>Usability</h3>
This plugin should provide the ability and usability to tag content. Tagging should be fast as hell, it should be inviting. This is one goal.

<h3>On the fly tagging</h3>
Tag content without switiching into the edito mode. Provide easy and fast interfaces for those purposes

<h3>Extensibility</h3>
This plugin should become very stable and use the current Drupal-API by best practice - as much as possible. Its not the primary goal to have the newest features in here as fast as possible, its more about getting them done right.
This should provide the ability to be highly extensible, providing a API for other plugins to reuse the UX-Parts and write better Tagging-tools. One of the primary Tools are semantic suggestions for tags

<h3>Tag-Suggestions</h3>
This plugin should provide the needed API to let other modules provide suggestions for the most important tags for the current content. The user can be supported to learn, how tagging should work. Also, the user can save a lot of time, because he can simply click on a set of suggested terms, using his mouse. Or remove them - by using his mouse again.
Suggestions can have weights and therefor are sorted

<h3>Autotagging</h3>
As a long term goal, based on the suggestions, user should be able to have a "autotag this content" button


<h3>Note</h3>
You have to activate the Tagging-Widget for every vocabulary


<h2>API</h2>
<h3>hook_tagging_suggestions($vid, $node)</h3>
Every time a module gets edited, all registered modules using hook_suggestions are called. They get the current vocabulary ID and the current node as arguments. The hooks are expected to return an array, with a hash for each item inside:
[]['#name'] = "termname"
[]['#weight]= decimal between 1 and 10
Heigher weights, means faster sinking, means the suggestion is not to "important" :)

You can use the $vid to only trigger on specific vocabulars only.
This way you can include suggestions using opencalais or extractor.
<h4>tagging_suggestions_alter($suggestions,$vid)</h4>
You can alter the suggestions <b>after</b> the hook_tagging_suggestion have been called. Make exclusions, your own stopword or context-sensitive additions.


<h3>Theming</h3>

<h4>theme_tagging_tags_list($suggestions,$vid)</h4>
Render the list of tags as HTML. . Every term must be in a <b>div</b> with at least the class "tagging-text".

<h4>theme_tagging_suggestions_list($suggestions,$vid)</h4>
Render the list of suggestions as HTML. Every suggestion-term must be in a <b>div</b> with at least the class "tagging-suggest-tag".

<h4>theme_tagging_widget</h4>
Render the whole tagging_widget. Give it a new layout or a new UX.Render the button which should be shown next to the input field. The input field must have the class "tagging-widget-input-$vid" assigned to it at least.

<h4>theme_tagging_widget_button</h4>
Render the button which should be shown next to the input field. It must have the class "tagging-button-$vid" assigned to it at least.

<h4>theme_tagging_widget_wrapper</h4>
Render the wrapper of the widget and embed it wherever you like. It must at have the id "tagging-widget-container".

<h3>JQuery Plugin: Tagging</h3>
$('selectorname-ID').tagging()
Thats pretty anything you need to initialize any input element on the page. You have to provide some wrappers:
<ul>
<li> .tagging-button-ID : Optional Button for "add this term"</li>
<li>.tagging_widget-ID: Input field, which will be your autocompletition-field</li>
<li>.tagging-wrapper-ID: Where should all added tags get visually shown</li>
<li>.suggestion-tagging-wrapper-ID: where should the suggested tags get shown</li>
<li>.tagging-widget-target-ID: Where should the tags be saved in. Most probably some vocab-edit-field (hidden)</li>
</ul>
<b>The JQuery-Plugin will get more generic so it can be used more widely. Most of the options which are static right now, should be changeable by options. The current one should be the default</b>

<h2>Contributions / Issues</h2>
Contributions are highly respected, also feedback on issues or patches. 

<h2>Feature requests</h2>
Please don't hassle with feature request, but please think about them properly, before you file in a issue-ticket. Please provide a basic outline of what the goal or the benefit of this feature would be. Outline the group of user you think is interested in.

Implement them! :)

<b>This plugin was sponsored by <a href="http://impressive-media.de">Impressive.media GbR</a></b>
