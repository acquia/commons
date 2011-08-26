

INTRODUCTION
---------------------------------------------

Quant provides an engine for producing quantitative, time-based analytics 
for virtually any Drupal component. Quant takes raw data about normal Drupal 
actions, such as node creation, and plots the activity over time, with the 
selected time being configurable. 


REQUIREMENTS
---------------------------------------------

Chart API (http://drupal.org/project/chart)


RECOMMENDED
---------------------------------------------

jQuery UI (http://drupal.org/project/jquery_ui)
  - Used to display the datepicker dialog

INSTALLATION
---------------------------------------------

1. Add both quant and chart to your site's modules directory
2. If you're using chart-6.x-1.2, it is highly recommended that you apply 
this patch to chart: http://drupal.org/files/issues/chart-fix-division-by-zero.patch
Or, if you'd like to download a pre-patched version of Chart, try here:
http://drupal.org/node/904478#comment-3419284
--
If you're using chart-6.x-1.3, it is highly recommended that you apply
this patch to chart: http://drupal.org/files/issues/chart-division-by-zero-594202.patch
3. Enable both modules
4. If you plan to use jquery_ui, add it to your site's module directory
and enable it
5. Visit quant's settings page: site.com/admin/settings/quant
6. Visit the analytics report: site.com/analytics


CHARTS PROVIDED
---------------------------------------------

Content creation
Comment creation
Content creation by type
Aggregate content creation
User creation
User shouts (requires shoutbox)
User point transactions (requires userpoints)
Group creation (requires organic groups)
Group joins (requires organic groups)
Invites sent (requires invite)
Invites accepted (requires invite)

~~~

Want to add your own charts? See API.txt.
