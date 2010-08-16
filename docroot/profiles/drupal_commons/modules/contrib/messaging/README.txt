// $Id: README.txt,v 1.1.4.2.2.1 2009/11/11 18:07:24 jareyero Exp $

README.txt - Drupal Module - Messaging
======================================

Drupal Messaging Framework

This is a messaging framework to allow message sending in a channel independent way
It will provide a common API for sending while allowing plugins for multiple channels

This Messaging Framework has been primarily developed to be used by the Notifications Framework.
See Drupal notifications module for an usage usage example implementing the full messaging capabilities.

Online documentation, includes end user and development handbooks: http://drupal.org/node/252582

SimpleTest:
-----------
Tests for this module will run on SimpleTest 6.x-2.8 (old version).
About this see http://drupal.org/node/584596

Features:
---------
- Provides a method agnostic API for composing and sending messages
- Handles message composition and formatting depending on sending method
- Supports multiple plug-ins for different message methods
- Supports 'push' and 'pull' message delivery

Plug-ins provided in this package:
---------------------------------
- messaging_mail: Integration with Drupal core mail API
- messaging_private: Integration with Privatemsg
- messaging_simple: Provides a simple UI for viewing pending messages for a user
- messaging_mime_mail: Mime mail integration
- messaging_phpmailer: HTML mails through PHPMailer
- messaging_debug: Debugging tools for developers
...

Note: some of the plug-ins depend on other packages and may not be available yet for Drupal 6

Developers:
-----------
- Tim Cullen
- Jeff Miccolis
- Jose A. Reyero

Development Seed, http://www.developmentseed.org