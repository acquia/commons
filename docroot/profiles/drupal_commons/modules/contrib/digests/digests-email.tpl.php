<?php
/**
 * @file
 *   Renders a digest email.
 *
 * See http://drupal.org/node/226776 for a list of default variables.
 *
 * Other variables available:
 * - $account: The user account object of the user receiving the message
 * - $messages: An array of activity message objects
 * - $stream: The themed (HTML) list of activity messages
 * - $name: The name of the user being sent the message
 * - $name_link: The name of the user being sent the message, linked to their profile
 * - $date_small: The small formatted date per the site's settings
 * - $date_medium: The medium formatted date per the site's settings
 * - $date_large: The large formatted date per the site's settings
 * - $logo: HTML for the logo image
 * - $header: The email header set by the administrator
 * - $footer: The email footer set by the administrator
 * - $unsubscribe: Instructions on how to unsubscribe from digest emails
 *
 * NOTE:
 * HTML and CSS do not work the same way in emails as they do in web pages.
 * The most consistent way to style emails is to use tables for the structure.
 * Additionally, only inline styles will have any effect in some clients (most
 * notably Gmail).
 */
?>
<div id="digests">
  <?php if ($logo) {
    print $logo;
  } ?>
  <?php if ($header): ?>
    <div id="digests-header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>
  <table id="digests-stream" style="border: 1px solid #CCCCCC; margin: 12px 24px; max-width: 800px; min-width: 480px; padding: 18px 30px">
    <tbody>
      <?php print $stream; ?>
    </tbody>
  </table>
  <?php if ($footer): ?>
    <div id="digests-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>
  <?php if ($unsubscribe): ?>
    <div id="digests-unsubscribe">
      <?php print $unsubscribe; ?>
    </div>
  <?php endif; ?>
</div>
