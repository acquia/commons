Feature: Trusted Contacts
  In order to communicate between different users on my commons site
  As an authenticated user
  I should be able to contact other users and add them to my friends list.

  Scenario: Anonymous user doesn't have access to add trusted contacts or follow users
    Given I am not logged in
    When I visit "/users/jeff-noyes"
    Then I should not see the link "Add as trusted contact"
      And I should not see the link "Follow"

  @api
  Scenario: Authenticated user can see add trusted contact and follow links
    Given I am logged in as a user with the "authenticated user" role
    When I visit "/users/jeff-noyes"
    Then I should see the link "Add as trusted contact"
      And I should see the link "Follow"

  @api
  Scenario: Authenticated user can add a trusted contact
    Given I am logged in as a user with the "authenticated user" role
    When I visit "/users/jeff-noyes"
      And I should see the link "Add as trusted contact"
      And I click "Add as trusted contact"
    Then I should see "Awaiting Confirmation"
