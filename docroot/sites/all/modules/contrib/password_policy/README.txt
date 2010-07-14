// $Id: README.txt,v 1.7 2010/04/15 04:00:10 deekayen Exp $

Password policy
==========================================
This module provides a way to specify a certain level of password
complexity (aka. "password hardening") for user passwords on a
system by defining a password policy.

A password policy can be defined with a set of constraints which
must be met before a user password change will be accepted. Each
constraint has a parameter allowing for the minimum number of valid
conditions which must be met before the constraint is satisfied.

Example: an uppercase constraint (with a parameter of 2) and a
digit constraint (with a parameter of 4) means that a user password
must have at least 2 uppercase letters and at least 4 digits for it
to be accepted.

Current constraints include:

  * Digit constraint
  * Letter constraint
  * Letter/Digit constraint (Alphanumeric)
  * Length constraint
  * Uppercase constraint
  * Lowercase constraint
  * Punctuation constraint
  * Character types constraint (allows the adminstrator to set the minimum
    number of character types required, but without actually dictating which
    ones must be used.  Example - Windows requires any 3 (user's choice) of
    uppercase, lowercase, numbers, or punctuation.
  * History constraint (checks hashed password against a
    collection of users previous hashed passwords looking for
    recent duplicates)
  * Username constraint

The module also implements configurable password expiration features:

  * When a password is not changed for a certain amount of time the user is blocked.
  * Expiration of the passwords can begin after expiration time after enabling of the
    policy or immediately all users with a passwords older then expiration time will
    be blocked (retroactive behavior).
  * The notifications (warnings) are mailed to the users several times (configurable)
    before the password expires. Drupal message is shown on login before the expiration
    and the user is forwarded to a password change page.
  * Warning e-mail message's subject and body are configurable.
  * When the password expires the user can be immediately blocked, or he can be let to
    login to the site once to change his password. If he does not change the password
    on that login, he won't be able to login again (will be bocked).

Security note
==========================================
Enforcing tough policy is only good from a technical standpoint. You are 
likely to end up with a situation where the users write down their super
secure and super impossible to remember passwords. Help texts on how can
you memorize such things (like shifting a word one row up the keyboard
and so on). You should have separate company policy that deters users from
writing passwords on a Post-it on the backside of their keyboard.

Consider a company policy to use strong password generator tools like
http://supergenpass.com/ or 1Password on MacOS.

Requirements
==========================================
Drupal 6.x
MySQL 5.0.3 or something else which supports varchar > 255

Credits
==========================================
Drupal 4.7 version was written by David Ayre <drupal at ayre dot ca>
Refactored and maintained by Miglius Alaburda <miglius at gmail dot com>
Sponsored by Bryght, SPAWAR, McDean

