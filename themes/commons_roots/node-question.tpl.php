<?php
// $Id: node-question.tpl.php $
?>

<div id="node-<?php print $node->nid; ?>" class="node <?php print $node_classes; ?>">
  <div class="inner">
    <?php print $picture ?>

    <?php if ($page == 0): ?>
    <h2 class="title"><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
    <?php endif; ?>

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
      <?php print $node->content['body']['#value']; ?>
      <?php if ($submitted_name): ?>
        <span>Submitted by <?php print $submitted_name ?> on <?php print $date; ?></span>
      <?php endif; ?>
      <p class="num-of-answers"><?php print format_plural($node->content['field_answer_count']['field']['#children'], '1 answer', '@count answers'); ?>
      <?php if(!$logged_in): ?>
        <span style="padding-left:30px"><?php print $answers_login; ?><span/>
      <?php endif; ?>
      </p>
      <?php print $node->content['question_answers_node_content_1']['#value']; ?>
    </div>
    
  </div><!-- /inner -->

  <?php if ($node_bottom && !$teaser): ?>
  <div id="node-bottom" class="node-bottom row nested">
    <div id="node-bottom-inner" class="node-bottom-inner inner">
      <?php print $node_bottom; ?>
    </div><!-- /node-bottom-inner -->
  </div><!-- /node-bottom -->
  <?php endif; ?>
  
</div><!-- /node-<?php print $node->nid; ?> -->
