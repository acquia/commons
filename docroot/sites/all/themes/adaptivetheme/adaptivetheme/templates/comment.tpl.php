<?php // $Id: comment.tpl.php,v 1.1.2.3 2010/03/23 04:53:54 jmburnz Exp $
// adaptivethemes.com

/**
 * @file comment.tpl.php
 * Default theme implementation for comments.
 *
 * Available variables:
 * - $author: Comment author. Can be link or plain text.
 * - $content: Body of the post.
 * - $date: Date and time of posting.
 * - $links: Various operational links.
 * - $new: New comment marker.
 * - $picture: Authors picture.
 * - $signature: Authors signature.
 * - $status: Comment status. Possible values are:
 *     comment-unpublished, comment-published or comment-preview.
 * - $submitted: By line with date and time.
 * - $title: Linked title.
 *
 * Helper variables:
 * - $classes: Outputs dynamic classes for advanced themeing.
 * - $title_classes: classes for the title element.
 * - $unpublished: prints a message if the comment is unpublished.
 *
 * These two variables are provided for context.
 * - $comment: Full comment object.
 * - $node: Node object the comments are attached to.
 *
 * Optionally add a count id:
 * <span class="comment-id"><?php print '#'. $id; ?></span>
 *
 * @see template_preprocess_comment()
 * @see genesis_preprocess_comment()
 * @see theme_comment()
 */
?>
<div class="<?php print $classes; ?>">

  <?php if ($title): ?>
    <h3<?php print $title_classes ? ' class="'. $title_classes .'"' : ''; ?>>
      <?php print $title; ?>
      <?php if ($comment->new): ?>
        <span class="new"><?php print $new; ?></span>
      <?php endif; ?>
      <?php print $unpublished; ?>
    </h3>
  <?php endif; ?>

  <?php print $picture; ?>

  <?php if ($submitted): ?>
    <p class="submitted"><?php print $submitted; ?></p>
  <?php endif; ?>

  <?php print $content; ?>

  <?php if ($signature): ?>
    <div class="user-signature"><?php print $signature; ?></div>
  <?php endif; ?>

  <?php if ($links): print $links; endif; ?>

</div> <!-- /comment -->
