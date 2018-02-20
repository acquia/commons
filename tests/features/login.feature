Feature: Anonymous user login
  In order to access content for authenticated users
  As an anonymous user
  I want to be able to login

  Background:
    Given users:
      | name     | pass      | mail             | roles               |
      | TestUser | ChangeMe! | foo@test.com  | content moderator   |

  @standard_login @api
  Scenario: Content Moderator is able to login
    Given I am on "/user"
    When I fill in "TestUser" for "edit-name"
    And I fill in "ChangeMe!" for "edit-pass"
    And I press "Log in"
    Then I should see "Log out"

  @standard_login @api
  Scenario: User can request a new password if it has been lost
    Given I am on "/user/password"
    Then I should see "Request new password"
    When I fill in "TestUser" for "name"
    And press "E-mail new password"
    Then I should see "Further instructions have been sent to your e-mail address."
    And I should see "Log in"
