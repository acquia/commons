<?php print $anchors; ?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="privatemsg-message-information author-datetime">
    <span class="privatemsg-author-name"><?php print $author_name_link; ?></span> <span class="privatemsg-message-date"><?php print $message_timestamp; ?></span>
    <?php print $author_picture; ?>
    <?php if (isset($new)): ?>
      <span class="new privatemsg-message-new"><?php print $new ?></span>
    <?php endif ?>
  </div>
  <div <?php print $content_attributes; ?>>
    <div class="privatemsg-message-body">
      <?php print $message_body; ?>
    </div>
  </div>
  <?php print render($message_links); ?>
  <?php if (isset($message_actions)): ?>
    <?php print $message_actions ?>
  <?php endif ?>
</div>
