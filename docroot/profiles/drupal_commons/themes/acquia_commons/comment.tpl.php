<?php
// $Id: comment.tpl.php 7713 2010-07-16 15:26:08Z sheena $
?>

<div class="comment <?php print $comment_classes;?> clear-block">

  <div class="comment-info">  
    <?php if ($comment->new): ?>
      <a id="new"></a>
      <span class="new"><?php print $new ?></span>
    <?php endif; ?>
    <?php 
      if (!$comment->picture && (variable_get('user_picture_default', '') != '')) {
        $comment->picture =  variable_get('user_picture_default', '');
      }
      if ($comment->picture) { 
        $picture = theme_imagecache('user_picture_meta', $comment->picture, $name, $name);
        if (user_access('access user profiles')) {
          print l($picture, "user/{$comment->uid}", array('html' => TRUE));
        }
        else {
          print $picture; 
        }
      }
    ?>
    <div class="submitted">
      <?php print $submitted ?>
    </div>
  
    <?php if ($links): ?>
      <div class="links">
        <?php print $links ?>
      </div>
    <?php endif; ?>
  </div>
 
  <div class="comment-content-wrapper">
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
  </div>
  
</div><!-- /comment -->
