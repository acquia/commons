Feature: Comments
  In order to interact with others in content
  As an authenticated user
  I should be able to post comments

  Scenario: Anonymous users cannot post comments for event content type
    Given I am on "/groups/boston/best-brunch-places-cambridge"
    Then I should see "Log in or register to post comments"
      And I should not see "Add new comment"

  @api
  Scenario: Log in as authenticated user and post comments
    Given I am logged in as a user with the "authenticated user" role
    When I go to "/groups/boston/best-brunch-places-cambridge"
    Then I should see "Add new comment"
      And I should not see "Log in or register to post comments"
