<?php
// $Id: docs.inc,v 1.2 2008/07/16 00:09:03 merlinofchaos Exp $

/**
@file
This file contains no working PHP code; it exists to provide additional
documentation for doxygen as well as to document hooks and API functions in
the standard Drupal manner.
 */

/**
@mainpage Panels 2 Documentation

The Panels 2 API Documentation is intended as a guide to the innerworkings of Panels, and will primarily be of interest to Drupal themers and developers. \n\n Panels is a complex and abstract system, which necessitates the use of a lot of specialized terms. If you are new to Panels, we strongly recommend you consult the @ref panels_glossary "Panels Glossary" to familiarize yourself with the jargon.\n\n 

@section panels_api_top Developer API Reference
\li @subpage panels_api_plugins "Plugins API"

Please note that this documentation is generated directly from the Panels project source code. Consequently, if you find errors or have improvements, you can file a patch in the Panels issue queue at http://drupal.org/project/issues/panels like any other patch. Documentation that is not specific to a file, function, or class is contained in the .inc files in /panels/docs.
 */

/**
@page panels_glossary Panels Glossary

\par 
<em>"Hey - you know that box thing in Panels? It's that...ugh, y'know, it's that rectangular, light-colored box. And it's in the Panels editor. It's right there on the editing form, with its name at the top. No, no! Not the name I gave it on the other form, I CAN read - I mean the name of the boxy THING! What in tarnation do I call the thing itself!?!"<sup>*</sup></em>\n

If you've ever tried to talk or write about - or, let's be honest, even <em>use</em> - Panels, then you probably know right where that sentence is coming from. Panels has all kinds of 'things' in it - things you click on, things you look at, things that contain other things, things that pop up, things that slide away, things that...well, the list goes on. It's enough of a challenge knowing what they are when we see them, but trying to communicate about Panels with real people, and not Panels itself? Fuhgettaboutit. So we're working on a little glossary that we're hoping might make that just a little better.

<hr>

@SECglossary{layout,Layout Terms}
Panels' basic purpose is structure content for viewing, and it makes use of its own set of terms to describe this structure. There are three essential terms - @LGt{pane,Pane}, @LGt{panel,Panel}, and @LGt{display,Display}.
@AG{pane,Pane} Panes are individual content items, and are the smallest/highest-level unit of content that the Panels API itself configures and renders. If you've used the Panels 2 content editor at all, then you're probably most familiar with panes via the 'Add Content' @LGt{modal} where you pick out the content you'd like to add. Each one of the items on that form is a @LGt{content_types,content type} (or subtype); once you select one and fill out the form, you'll see a graphical representation of the new pane appear.

@AG{panel,Panel} Panels are the containers that hold @LGt{pane,Panes}. When you select a @LGt{layouts,layout}, what you're choosing is the number and arrangement of panels. The content editor represents panels quite well: panels are the blue (by default) boxes with their name at the top and the plus-shaped button that opens the 'Add content' @LGt{modal}. And yes the namespace ambiguity is awful - we're resolving it soon.

@AG{display,Display} The Display unit is the most abstract of the three layout terms. Again, the Panels 2 content editor is a good way to think about it: there's no visual representation of a display in the editor because the display IS what you're editing: it's the object that contains the @LGt{panel,panels}, and it's settings in the display object that govern, for example, which content types are available on the 'Add Content' form. \n Displays are abstract and often the most difficult for newcomers to Panels to understand. They're also probably the most important thing that developers implementing the Panels API in a @LGt{clientmodule,client module} need to understand, as client modules work primarily with display objects. Displays are essentially the 'root' object of the API - this is functionally true in Panels 2, but it will be literally the case after Panels is rewritten in OO for Panels 3. \n In addition to @LGt{panel,panels}, displays hold almost all of Panels' plugins and are required in most of the @ref mainapi "main API functions"; this is why client modules interact with the Panels API primarily through display objects.
 

@SECglossary{plugins,Panels Plugins}
At its core, Panels is really just a structure for negotiating and handling its plugins. For a thorough introduction to plugins, see the introduction to the @LA{plugins,plugins API}.

@SSECglossary{plugins,general,General Terms}
The following terms are relevant to all plugin types:
@AG{p-d-func,Plugin Declaration Function} All plugins begin with a declaration function. These declaration functions are what Panels searches for in compiling the list of available plugins, and as such are subject to strict naming conventions. The sole purpose of a plugin declaration function is to return a \pdarray populated with plugin \plugprops.

@AG{p-d-array,Plugin Definition Array} Plugin definition arrays are returned from \pdfuncs. They are made up of two types of \plugprops: @LGt{p-p-setting,setting properties} and @LGt{p-p-callback,callback properties}. During each page request, Panels stores the information provided by these plugin definition arrays using the logic defined in panels_get_plugins(), allowing other parts of the Panels API to check settings and/or fire callbacks that have been defined in the definition array.

@AG{plugprop,Plugin Properties} Every plugin definition array is an associative array, and we refer to each of the key/value pairs in that array as a 'property.' These properties govern all aspects of the plugin's behavior.

@AG{p-p-setting,Setting Properties} Setting properties are values that Panels will use directly in various internal processes when deciding how to handle the plugin. Many setting properties are booleans that govern how Panels moves that plugin through various control statements; others are simple strings for administrative interface titles, or drupal 'weight' integers used to sort the plugin within lists.

@AG{p-p-callback,Callback Properties} Callback properties are strings containing function names; Panels fires these callbacks at certain points in its internal processes.


@SSECglossary{plugins,types,Plugin Types}
Panels currently manages eight different types of plugins:
@AG{arguments,Arguments}

@AG{content_types,Content Types}

@AG{context,Context}

@AG{layouts,Layouts}

@AG{styles,Styles}

@AG{relationships,Relationships}

@AG{cache,Cache}

@AG{switchers,Switchers}

@SECglossary{misc,Miscellaneous Terms}
If we could find categories to put these in, we would. Just because we can't find a group to put them in, though, doesn't mean they're not important!
@AG{modal,Javascript Modal Form}

@AG{clientmodule,Client Module}

\n\n
<small><sup>*</sup> Yep, that's right - we were talking about a @LGt{panel,Panel}! Oh, the ambiguity...</small>

 */

/**
@page panels_api_plugins Plugins API Reference

The Panels API uses a system of plugins to manage pretty much everything it
does. Without the plugins, the API is an empty shell; plugins define the
'what, where, and how' of Panels' behavior. Panels uses eight different
types of plugins. Specific reference information for each plugin type is
available on the corresponding page:
    - @Psubplug{content_types,Content Types}

These correspond to the similarly-named subdirectories filled with .inc
files - each of those .inc files declares at least one plugin.

@section panels_api_plugins_top_structure Structure of a Plugin

All panels plugins have the same basic structure. Each plugin begins with a
\pdfunc, which Panels identifies either by function name alone or through a
combination of function name and .inc file location depending on the method
being used. Regardless of the method or plugin type, Panels expects the same
thing to be returned from the plugin declaration function: a \pdarray. The
available \plugprops depend entirely on the type of plugin, so to learn more,
you'll have to consult the documentation for each individual plugin type.


There are eight types of panels plugins at present: context, relationships,
arguments, content_types, styles, layouts, cache, and switchers; Panels
provides an API that allows any module to implement these, but there's a
starter set that comes with Panels itself. They're found in the various
subdirectories that live under the Panels directory.

 */
