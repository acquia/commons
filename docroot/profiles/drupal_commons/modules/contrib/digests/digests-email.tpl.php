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
<table id="digests">
  <?php if (!empty($logo)) : ?>
    <tr>
      <td>
        <?php print $logo; ?>
      </td>
    </tr>
  <?php endif; ?>
  <?php if ($header): ?>
    <tr>
      <td>
        <div id="digests-header">
          <?php print $header; ?>
        </div>
      </td>
    </tr>
  <?php endif; ?>
  <?php if(!empty($stream)) : ?>
    <tr>
      <td>
        <table id="digests-stream">
          <tbody>
            <tr>
              <td>
                <?php print $stream; ?>
              </td>
            </tr>
          </tbody>
        </table>
      </td>
    </tr>
  <?php endif; ?>
  <?php if ($footer): ?>
    <tr>
      <td>
        <div id="digests-footer">
          <?php print $footer; ?>
        </div>
      </td>
    </tr>
  <?php endif; ?>
  <?php if ($unsubscribe): ?>
    <tr>
      <td>
        <div id="digests-unsubscribe">
          <?php print $unsubscribe; ?>
        </div>
      </td>
    </tr>
  <?php endif; ?>
</table>
