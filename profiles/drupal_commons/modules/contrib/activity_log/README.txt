The Activity Log module is designed to provide the easiest-to-use, most
flexible, most extensible, and most standards-oriented activity stream solution
for Drupal.

Activity streams provide a fantastic way of seeing an overview of what's
happening on a website by surfacing relevant, time-sensitive events. With
status updates provided by the Facebook-style Statuses module, the stream
provides a space for non-essential ("ambient") communication that is not so
urgent that it needs to crowd colleagues' email inboxes and but not so
transient that it can live in instant messaging. It fills the gap of where
casual conversations should live.

From a somewhat more technical level, the module essentially allows creating
Views that describe multiple kinds of activities -- i.e. a list of both node,
user, and relationship activity (among other things).

To log actions as activities on the site, you must create a Rule at
/admin/rules/trigger and add the "Log activity" action to it. This action's
configuration form lets you specify the templates you want to use to display
the activity, where you want the activity to be displayed, and how you want the
activity grouped with similar activity (if at all). When the rule is triggered,
the activity will be recorded.

Activities are displayed using Views. Unlike other activity stream solutions
for Drupal, the activity stream displayed by Activity Log is dynamic. This
means that the entities displayed in the stream reflect their current state --
not just the way they existed when the activity was stored. For example, if a
node creation action is triggered on Monday, and the node's title is changed on
Tuesday, then if the activity stream is viewed on Wednesday it will show the
new title of the node.

Because activity message templates are specified in Rules and displayed
dynamically in Views, this creates the ability to interact directly with
entities in the stream. For example, with the Flag module installed, you can
add flag link tokens to the message that will enable you to "Like" or "Report"
a node directly from the stream (and not just "Like" or "Report" the activity
itself). Additionally this module is recommended for use with the Facebook-
style Statuses module ( http://drupal.org/project/facebook_status ) which
allows easily writing "status updates" that can appear in the stream instantly
without refreshing the page. You can comment directly on status updates from
within the stream.

Additionally, integration with the Radioactivity module is provided, which
allows sorting activity streams by the relevancy of the activity messages. This
lets more interesting and important activity float to the top of the stream
while older and less relevant activities fall off the end.

If you would like to delete old activity messages, navigate to
/admin/settings/activity_log and set how old activity messages must be before
they will be deleted. Deleting activity messages does not delete the associated
content (for example deleting a message about creating a node does not delete
the node itself). Old activity messages will get deleted when cron runs, so
if you want to take advantage of this option make sure that you have a cron job
running regularly.