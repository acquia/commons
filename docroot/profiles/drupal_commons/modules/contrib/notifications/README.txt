// $Id: README.txt,v 1.1.2.1.2.1.2.1 2009/11/12 18:04:00 jareyero Exp $

Notifications: README.txt
=========================

This is a complete notifications/subscriptions framework. The Notifications module is the main engine,
but it doesn't provide by itself any subscriptions or UI besides the administration pages. 
You'll need to enable some subscription types (content, taxonomy...) and some UI module (notifications_ui)
for it to work. 

It includes:
- Several types of subscriptions: content, taxonomy
- Event and message queueing
- Pluggable event types
- Pluggable subscription types

Read online handbook at http://drupal.org/node/252592

Dependencies:
- Tokens module, http://drupal.org/project/tokens
- Messaging module, http://drupal.org/project/messaging

SimpleTest:
-----------
Tests for this module will run on SimpleTest 6.x-2.8 (old version).
About this see http://drupal.org/node/584596

This module was originally based on the subscriptions module, http://drupal.org/project/subscriptions
The code has been used as an starting point but the framework has been completely rewritten.

Developers:
-----------
- Tim Cullen
- Jeff Miccolis
- Jose A. Reyero

Development Seed, http://www.developmentseed.org
