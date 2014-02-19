Feature: General functionality
  Scenario: Anonymous users cannot create content
    Given I am on "/node/add"
    Then I should see "Access denied. You must log in to view this page."
    And I should not see "Add content"

  Scenario: Anonymous users cannot create groups
    Given I am on "/groups"
    And I should not see "Create a group"

  Scenario: Anonymous users cannot create events
    Given I am on "/events"
    And I should not see "List an event"

  Scenario: Anonymous users can view user profiles
    Given I am on "/user/1"
    Then I should see "admin"

  Scenario: Anonymous users can see the Commons footer
    Given I am on "/"
    Then I should see "A Commons Community, powered by Acquia"

  Scenario: Anonymous users can create new accounts
    Given I am on "/user/register"
    And for "mail" I enter "newuser@example.com"
    When I press "Sign up"
    Then I should see "A welcome message with further instructions has been sent to your e-mail address."

  Scenario: Anonymous users can view a listing of public groups
    Given I am on "/groups"
    Then I should see "Groups"
    And I should see "Most active groups"
    And I should see "Boston"