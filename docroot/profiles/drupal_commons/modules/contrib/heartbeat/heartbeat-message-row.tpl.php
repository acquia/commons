<?php
// $Id: heartbeat-message-row.tpl.php,v 1.1.2.12 2011/01/21 00:53:09 stalski Exp $

/**
 * @file
 *   Template file for one row, rendered by heartbeat
 *
 * @var
 * - $message : after it was parsed by heartbeat (grouped)
 * - $time_info : information about the time of activity
 * - $class : extra classes to use on the row
 * - $attachments : attachment on the message id (of the grouped message)
 *
 * @remarks
 *   beat-item-<uaid> is necessairy. The beat item id is used to toggle
 *   visibility of the "number more" messages when grouping exceeded the
 *   maximum allowed grouped property.
 */

?>
<div class="heartbeat-message-block <?php print $message->message_id . ' ' . $zebra; ?>">

  <div class="beat-item <?php print $message->classes ?>" id="beat-item-<?php print $message->uaid ?>">

    <?php print $message->content['message']; ?>
    <?php if (!empty($message->content['time_info'])): ?>
    <span class="heartbeat_times"><?php print $message->content['time_info']; ?></span>
    <?php endif; ?>

    <div class="clear"></div>

    <?php if (!empty($message->content['widgets'])) : ?>
    <div class="heartbeat-attachments">
      <?php print $message->content['widgets']; ?>
    </div>
    <?php endif; ?>

    <?php if (!empty($message->content['buttons'])) :?>
    <div class="heartbeat-buttons">
      <?php print $message->content['buttons']; ?>
    </div>
    <?php endif; ?>

    <br class="clearfix" />

  </div>

  <?php if (count($message->uaids) > 0) :?>
  <div class="beat-item <?php print $message->classes ?>" id="beat-item-<?php print $message->uaid ?>-ungrouped" style="display: none;">
  <?php foreach ($message->additions->source as $ungrouped_message) { ?>
    <?php print $ungrouped_message; ?><br />
  <?php } ?>
    <div class="heartbeat-buttons">
    <?php print l(t('Back'), drupal_get_destination(), array('attributes' => array('onclick' => 'javascript:Drupal.heartbeat.splitGroupedMessage(' . $message->uaid .', null); return false;')))?>
    </div>
    <br class="clearfix" />
  </div>
  <?php endif; ?>

</div>