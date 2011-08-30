###   ABOUT   #############################################################################

messaging_phpmailer, Version 1.0

Author:
  Brian Neisler, aka, bneisler
  brian@theamoebaproject.com
  http://www.theamoebaproject.com
  http://www.mothersclick.com

Contributors:
  Ted Serbinski, aka, m3avrck
  hello@tedserbinski.com
  http://tedserbinski.com

Requirements: Drupal 5.0


###   FEATURES   #############################################################################

- uses PHPMailer <http://phpmailer.codeworxtech.com/> as the mailer
- works as an extension of the messaging module <http://drupal.org/project/messaging/>
- provides an alternate method to sending html email in Drupal
- cuts out drupal_mail so that drupal can send both html emails and plain text emails.



###   INSTALLATION   #############################################################################

1. Download and unzip the messaging_phpmailer module into your modules directory.

2. Download the PHPMailer class: http://phpmailer.codeworxtech.com/
   Unzip the PHPMailer folder into you messaging_phpmailer folder.
   Rename folder to PHPMailer

3. Goto Administer > Site Building > Modules and enable Messaging PHPMailer

4. Goto Administer > Site Configuration > Messaging
   Select the settings tab.
   Select Full HTML as the filer for Messaging PHPMailer. Save settings.


###   NOTES   #############################################################################

- This module does NOT use drupal_mail. This is done on purpose so that mail can be sent as both plain text and HTML. 
  If you wish to override drupal_mail you will have to implement drupal_mail_wrapper() yourself to call the 
  messaging_phpmailer_send() function. Also you will need to set the stmp variable.
