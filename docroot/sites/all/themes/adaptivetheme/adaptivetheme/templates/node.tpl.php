<?php // $Id: node.tpl.php,v 1.1.2.3 2010/03/23 04:53:54 jmburnz Exp $
// adaptivethemes.com

/**
 * @file node.tpl.php
 * Theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: Node body or teaser depending on $teaser flag.
 * - $picture: The authors picture of the node output from
 *     theme_user_picture().
 * - $date: Formatted creation date (use $created to reformat with
 *     format_date()).
 * - $links: Themed links like "Read more", "Add new comment", etc. output
 *     from theme_links().
 * - $name: Themed username of node author output from theme_user().
 * - $node_url: Direct url of the current node.
 * - $terms: the themed list of taxonomy term links output from theme_links().
 * - $submitted: themed submission information output from
 *     theme_node_submitted().
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *     teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Helper variables:
 * - $article_id: Outputs a unique id for each article (node).
 * - $classes: Outputs dynamic classes for advanced themeing.
 * - $title_classes: classes for title element.
 *
 * Regions
 * - $article_aside: region embedded in the node template.
 *
 * Node status variables:
 * - $teaser: Flag for the teaser state.
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *     main body content.
 * - $unpublished: prints a message if the node is unpublished.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see genesis_preprocess_node()
 */
?>
<div<?php print $article_id ? ' id="'. $article_id .'"' : ''; ?> class="<?php print $classes; ?>">

  <?php if (!$page): ?>
    <h2<?php print $title_classes ? ' class="'. $title_classes .'"' : ''; ?>>
      <a href="<?php print $node_url; ?>" rel="bookmark"><?php print $title; ?></a>
      <?php print $unpublished; ?>
    </h2>
  <?php endif; ?>

  <?php if ($submitted): ?>
    <p class="submitted"><?php print $submitted; ?></p>
  <?php endif; ?>

  <?php if ($picture): print $picture; endif; ?>

  <?php print $content; ?>

  <?php if ($terms): print $terms; endif; ?>

  <?php if ($links): print $links; endif; ?>

  <?php if ($article_aside && !$teaser): ?>
    <div id="article-aside" class="aside"><?php print $article_aside; ?></div>
  <?php endif; ?>

</div> <!-- /article -->
