; $Id: README.txt,v 1.1.2.4 2008/04/21 00:38:18 sprsquish Exp $

User Relationship Defaults Module
---------------------------------
This is a plugin module for the User Relationships module.

It allows admins to set default relationships that are created between users when a new user joins.
Think of it like Tom from MySpace.

Send comments to Jeff Smick: http://drupal.org/user/107579/contact, or post an issue at
http://drupal.org/project/user_relationships.


Requirements
------------
Drupal 6
User Relationships Module


Installation
------------
Enable User Relationship Defaults in the "Site building -> modules" administration screen.


Database Schema
---------------
MySQL
=====

-- 
-- Table structure for table `user_relationship_defaults`
-- 
CREATE TABLE IF NOT EXISTS `user_relationship_defaults` (
  `rdid` int(10) unsigned NOT NULL default '0',
  `uid` int(10) unsigned NOT NULL default '0',
  `rtid` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`rdid`),
  KEY `uid` (`uid`),
  KEY `rtid` (`rtid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;


Credits
-------
Written by Jeff Smick.
Written originally for and financially supported by OurChart Inc. (http://www.ourchart.com)
Thanks to the BuddyList module team for their inspiration
