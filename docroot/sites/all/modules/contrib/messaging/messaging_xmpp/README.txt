/* $Id: */

IMPORTANT:
----------
This is an extended xmpp messaging module. It needs the patched xmppframework included with the module.

It is currently under heavy development, unsupported and not advised for production sites.

Included modules:
- messaging_xmpp 		Basic handling of in/out XMPP messages
- messaging_xmppchat	Post and read to/from xmpp chat

These modules may depend on other modules included in these packages:
- http://svn3.cvsdude.com/devseed/sandbox/drupal-6/messaging_incoming/
- http://svn3.cvsdude.com/devseed/sandbox/drupal-6/messaging_processor/

The xmpp messaging module provides a hook into the messaging framework so you can send xmpp headline messages
for providing information and notifications.

For any other use, please use the original XMPPFramework by Darren Ferguson, http://drupal.org/project/xmppframework
