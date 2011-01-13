$Id: README.txt,v 1.1.2.1 2009/06/22 12:36:04 alexk Exp $

User Relationship Migrate Module
---------------------------------

This is a plugin module for the User Relationships module. It allows admins to migrate
Buddy List 2 (not Buddylist) relationships to User Relationships.

If you have trouble, post an issue including URLs you are accessing and screenshots as necessary at
http://drupal.org/project/user_relationships.


Requirements
------------
Drupal 6
User Relationships Module
Buddy List 2 tables (its not necessary to have the Buddylist2 module actually installed)


Installation
------------
Enable User Relationship Migrate in the "Site building -> Modules" administration screen.


Usage
-----
After enabling the module, go to the "User management -> Relationships" page
(admin/user/relationships) and click on "Migrate buddylist2" in the menu across the top.

Enter a relationship type for the migrated relationships, and click Migrate. 
Your Buddylist data will be treated correctly depending on the type of relationship you are 
importing into (one-way vs. two-way)

Tested on a MacBook Pro 2.4GHz Core2Duo with 4GB of RAM a 706,000 row buddylist table
took ~40 seconds to migrate.

Running this module more than once without clearing the previous migration will cause
UNIQUE KEY errors in the table. This is to help eliminate duplicate entries. 

You will also see UNIQUE KEY errors if some relationships being imported already exist 
in User Relationships (that is, users have already created some of them).

After running this you can disable the module as you will no longer need it.


Credits
-------
Written by JB Christy.
Refactored by Jeff Smick.
Written originally for and financially supported by OurChart Inc. (http://www.ourchart.com)
Thanks to Jeff Smick for the User Relationships module, and to the Buddy List folks.

Modified to work in Drupal 6 by Dave Myburgh (incrn8). 
Additional tweaks by Alex Karshakevich (alex.k)