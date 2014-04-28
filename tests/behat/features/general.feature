Feature: General functionality
  Scenario: Anonymous users cannot create content
    Given I am on "/node/add"
    Then I should see "Access denied. You must log in to view this page."
      And I should not see "Add content"

  Scenario: Anonymous users cannot create groups
    Given I am on "/groups"
    Then I should not see "Create a group"

  Scenario: Anonymous users cannot create events
    Given I am on "/events"
    Then I should not see "List an event"

  Scenario: Anonymous users can view user profiles
    Given I am on "/user/1"
    Then I should see "admin"
