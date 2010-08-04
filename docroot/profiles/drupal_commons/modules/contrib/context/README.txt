$Id: README.txt,v 1.1.4.4 2010/04/30 05:52:06 darthsteven Exp $

Context for Drupal 6.x

Installation
------------
Context can be installed like any other Drupal module -- place it in
the modules directory for your site and enable it (and its requirement,
context) on the admin/build/modules page.

You will probably want to install context_contrib and context_ui as well.
context_contrib provides basic context integration for several contrib
modules including Views and context_ui provides a way for you to edit
contexts through the Drupal admin interface.

Basic usage
-----------
Context allows you to manage contextual conditions and reactions for
different portions of your site. You can think of each context as
representing a 'section' of your site. For each context, you can choose
the conditions that trigger this context to be active and choose different
aspects of Drupal that should respond to this active context.

Think of conditions as a set of rules that are checked during page load
to see what context is active. Any reactions that are associated with
active contexts are then fired.

Example
-------
You want to create a 'pressroom' section of your site. You have a press
room view that displays press release nodes, but you also want to tie
a book with media resources tightly to this section. You would also
like a contact block you've made to appear whenever a user is in the
pressroom section.

1. Add a new context on admin/build/context
2. Set the value to 'pressroom'
3. Under the 'set context' dialogue, associate the pressroom nodetype,
   the pressroom view, and the media kit book with the context.
4. Choose the pressroom menu item to be set active under the 'respond
   to context' items.
5. Add the contact block to a region under the block visibility
   settings.
6. Save the context.

Hooks
-----
hook_context_conditions()
  Provides an array of FormAPI definitions. Allows you to provide
  additional conditions for setting a context.

  Example: context_context_conditions()

hook_context_reactions()
  Provides an array of FormAPI definitions. Allows you to provide
  additional reactions that respond to a set context.

  Example: context_context_reactions()

hook_context_default_contexts()
  Provides an array of exported context definitions. Allows you
  to provide default contexts in your modules.

hook_context_default_contexts_alter()
  A drupal_alter() that acts on the collected array of default
  contexts before they are cached.

hook_context_active_contexts_alter()
  A drupal_alter() that acts on the collected array of active
  contexts on a given page load.

hook_context_links_alter()
  A drupal_alter() that acts on the contextual links provided
  to page.tpl.php.

Maintainers
-----------
yhahn (Young Hahn)
jmiccolis (Jeff Miccolis)
Steven Jones

Contributors
------------
dmitrig01 (Dmitri Gaskin)
Pasqualle (Csuthy Bálint)
