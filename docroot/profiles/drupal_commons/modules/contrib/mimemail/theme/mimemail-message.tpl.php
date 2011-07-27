<?php

/**
 * @file
 * Default theme implementation to format an HTML mail.
 *
 * Copy this file in your default theme folder to create a custom themed mail.
 * Rename it to mimemail-message--[mailkey].tpl.php to override it for a
 * specific mail.
 *
 * Available variables:
 * - $recipient: The recipient of the message
 * - $subject: The message subject
 * - $body: The message body
 * - $css: Internal style sheets
 * - $mailkey: The message identifier
 *
 * @see template_preprocess_mimemail_message()
 */
?>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <title>Your Message Subject or Title</title>
  <style type="text/css">

    /* Client-specific Styles */
    #outlook a { padding: 0; } /* Force Outlook to provide a "view in browser" button. */
    body { width: 100% !important; } .ReadMsgBody { width: 100%; } .ExternalClass { width: 100%; } /* Force Hotmail to display emails at full width */
    body { -webkit-text-size-adjust: none; -ms-text-size-adjust: none; } /* Prevent Webkit and Windows Mobile platforms from changing default font sizes. */

    /* Reset Styles */
    body { margin: 0; padding: 0; }
    img { height: auto; line-height: 100%; outline: none; text-decoration: none; }
    #backgroundTable { height: 100% !important; margin: 0; padding: 0; width: 100% !important; }

    p {
       margin: 1em 0;
    }

    h1, h2, h3, h4, h5, h6 {
       color: black !important;
       line-height: 100% !important;
    }

    h1 a, h2 a, h3 a, h4 a, h5 a, h6 a {
       color: blue !important;
    }

    h1 a:active, h2 a:active,  h3 a:active, h4 a:active, h5 a:active, h6 a:active {
       color: red !important; /* Preferably not the same color as the normal header link color.  There is limited support for psuedo classes in email clients, this was added just for good measure. */
    }

    h1 a:visited, h2 a:visited,  h3 a:visited, h4 a:visited, h5 a:visited, h6 a:visited {
       color: purple !important; /* Preferably not the same color as the normal header link color. There is limited support for psuedo classes in email clients, this was added just for good measure. */
    }

    table td {
       border-collapse: collapse;
    }

    .yshortcuts, .yshortcuts a, .yshortcuts a:link,.yshortcuts a:visited, .yshortcuts a:hover, .yshortcuts a span { color: black; text-decoration: none !important; border-bottom: none !important; background: none !important; } /* Body text color for the New Yahoo.  This example sets the font of Yahoo's Shortcuts to black. */
    
    /* admin CSS */
    <?php if ($css): ?>
      <?php print $css ?>
    <?php endif; ?>
  </style>
</head>
<body id="mimemail-body" <?php if ($mailkey): print 'class="'. $mailkey .'"'; endif; ?>>
  <table cellpadding="12" cellspacing="" border="0" id="backgroundTable" style="width:100%;border-collapse:collapse;font-size:16px;font-family:'Lucida Grande',Verdana,Arial,Helvetica,sans-serif">
    <tr>
      <td>
        <?php print $body ?>
      </td>
    </tr>
  </table>  
  <!-- End of wrapper table -->
</body>
</html>
