<?php
// $Id: comment.tpl.php 7510 2010-06-15 19:09:36Z sheena $
?>

<div class="comment <?php print $comment_classes;?> clear-block">
<div class="comment-info">  
 <?php if ($comment->new): ?>
  <a id="new"></a>
  <span class="new"><?php print $new ?></span>
  <?php endif; ?>
  <?php if ($comment->picture):
 print(theme_imagecache('user_picture_meta', $comment->picture, $name, $name)); endif;?>
    <div class="submitted">
    <?php print $submitted ?>
  </div>
  
    <?php if ($links): ?>
  <div class="links">
    <?php print $links ?>
  </div>
  <?php endif; ?>
  </div>
 <div class="comment-content">
  
  <h3 class="title"><?php print $title ?></h3>

  
  <div class="content">
    <?php print $content ?>
    
    <?php if ($signature): ?>
    <div class="signature">
      <?php print $signature ?>
    </div>
    <?php endif; ?>
  </div>
  </div>

  
</div><!-- /comment -->