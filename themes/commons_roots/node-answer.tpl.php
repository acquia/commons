<?php
// $Id: node-answer.tpl.php $
?>

<div id="node-<?php print $node->nid; ?>" class="node <?php print $node_classes; ?>">
  <div class="inner">
    <?php print $picture ?>

    <?php if ($node_top && !$teaser): ?>
    <div id="node-top" class="node-top row nested">
      <div id="node-top-inner" class="node-top-inner inner">
        <?php print $node_top; ?>
      </div><!-- /node-top-inner -->
    </div><!-- /node-top -->
    <?php endif; ?>

    <?php if ($terms): ?>
    <div class="terms">
      <?php print $terms; ?>
    </div>
    <?php endif;?>
    
    <div class="content clearfix">
      <?php print $content ?>
      <?php if ($submitted_name): ?>
        <span class="answer-by"><?php print $submitted_name; ?> on <a href="<?php print request_uri() . '#node-' . $node->nid; ?>" class="answer-time-date"><?php print $date; ?></a></span>
      <?php endif; ?>
    </div>
    
    <?php if ($node->links['comment_add']): ?>
    <div class="links">
      <div class="comment_clear_style answer-add-comment">
        <a href="<?php print base_path() . $node->links['comment_add']['href'] . '#' . $node->links['comment_add']['fragment']; ?>" title="Share your thoughts and opinions related to this posting.">Comment</a>
      </div>
      <?php if ($node->comment_count > 0): ?>
      <div class="comment_clear_style answer-comment-count">
        <a href="<?php print base_path() . $node->path; ?>"><?php print format_plural($node->comment_count, '1 comment', '@count comments'); ?></a>
      </div>
      <?php endif; ?>
    </div>
    <?php endif; ?>

  </div><!-- /inner -->

  <?php if ($node_bottom && !$teaser): ?>
  <div id="node-bottom" class="node-bottom row nested">
    <div id="node-bottom-inner" class="node-bottom-inner inner">
      <?php print $node_bottom; ?>
    </div><!-- /node-bottom-inner -->
  </div><!-- /node-bottom -->
  <?php endif; ?>
</div><!-- /node-<?php print $node->nid; ?> -->
