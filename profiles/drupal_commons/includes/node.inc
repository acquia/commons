<?php

/**
 * @file
 *   Contains node definitions
 */

/**
 * Provide a default group during installation
 */
function _drupal_commons_default_group_node() {
  module_load_include('inc', 'node', 'node.pages');
  
  $group = new stdClass;
  $group->type = 'group';
  node_object_prepare($group);
  $group->uid = 1;
  $group->status = 1;
  $group->format = 1;
  $group->revision = 0;
  $group->title = st('Our Community');
  $group->body = st('Commons provides the software; but we the people need to work out the human aspects of helping this community to succeed. Let&#39;s collaborate on that using this group.');
  $group->teaser = node_teaser($group->body);
  $group->created = time();
  $group->field_featured_group = array(
    0 => array(
      'value' => 'Featured',
    ),
  );
  $group->og_description = st('A group for collaborating to make this community site successful');
  $group->taxonomy['tags'][2] = st('community');
  $group->og_private = 0;
  $group->og_directory = 1;
  $group->og_register = 0;
  $group->og_selective = 0;
  
  return $group;
}

/**
 * Provide a default discussion during installation
 */
function _drupal_commons_default_discussion_node() {
  module_load_include('inc', 'node', 'node.pages');
  
  $node = new stdClass;
  $node->type = 'discussion';
  node_object_prepare($node);
  $node->uid = 1;
  $node->status = 1;
  $node->format = 1;
  $node->revision = 0;
  $node->title = st('Jumpstarting our community');
  $node->body = st('<p>In Commons, all content is all created within the context of a &quot;Group&quot;. Start exploring how to use your site by:</p><ul><li>' . l(t('Viewing a list of all the groups'), 'groups') . ' on this site. (Note: Only this demonstration group exists by default.)</li><li>' . l(t('Creating a new group'), 'node/add/group') . ' of your own. Before you do, you might find an image / graphic for identification use on the group home page. Perhaps a logo, or ..?</li></ul><p>Once you&#39;ve created your group, start building your community by creating various kinds of content. &nbsp;Commons lets members of a group create:</p><ul><li>Blog posts. These are just what you think: personal notes from individuals. &nbsp;Note that other users can comment on these posts.</li><li>Documents. If you want to store attached documents that are useful for a group, create a Document page, describe the attachment in the body of the page, and then attach the files you want.</li><li>Discussions. &nbsp;A discussion is just that: Somebody starts by creating a page with a thought, idea, or question. Others can then comment on the initial post. Comments are &quot;threaded&quot; so you can comment on a comment.</li><li>Wikis. All the three posts above work the same: The initial author of a blog/document/discussion is the only person who can edit the &quot;body&quot; of the page. In contrast, any member of a group can edit the body of a Wiki page. &nbsp;That&#39;s what makes Wiki pages special - anybody can edit the content.</li><li>Events. If you have a special thing happening on a given day/time, create an &quot;Event&quot; describing it. These events will show up on the Calendar tab of a group home page.</li><li>Group RSS feed. If there is interesting content coming from outside this site that you want your group to track, pull that content in as an RSS feed to the site.</li></ul><p>There&#39;s more to building a community than the technology; it&#39;s the people &amp; participation that makes a community work. This set of content types should give you all the choices you need to jump-start this community.</p>');
  $node->teaser = node_teaser($node->body);
  $node->created = time();
  $node->field_featured_content[0]['value'] = 'Featured';
  $node->taxonomy['tags'][2] = st('content types, getting started, groups, jumpstart');
  $node->og_public = 1;

  return $node;
}
