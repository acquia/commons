Feature: Content types
  Background:
    Given I am logged in as a user with the "authenticated user" role

  @api
  Scenario: Authenticated users can create groups
    Given I am on "/node/add/group"
    When I fill in "Group title" for "title_field[und][0][value]"
      And I fill in "Group body" for "body[und][0][value]"
      And I press "Save"
    Then I should see "Thanks for your group submission! This group has entered the moderation queue and will be reviewed shortly."
      And I should see "Group title"
      And I should see "Group body"

  @api
  Scenario: Authenticated users cannot create pages
    Given I am on "/node/add/page"
    Then I should see "Access denied"

  @api
  Scenario: Authenticated users can create polls
    Given I am on "/node/add/poll"
    When I fill in "Poll title" for "title_field[und][0][value]"
      And I fill in "Choice 1" for "choice[new:0][chtext]"
      And I fill in "Choice 2" for "choice[new:1][chtext]"
      And I press "Save"
    Then I should see "Poll title"
      And I should see "Choice 1"
      And I should see "Choice 2"

  @api
  Scenario: Authenticated users can create posts
    Given I am on "/node/add/post"
    When I fill in "Post title" for "title_field[und][0][value]"
    And I fill in "Post body" for "body[und][0][value]"
    And I press "Save"
    Then I should see "Post title"
      And I should see "Post body"

  @api
  Scenario: Authenticated users can create questions and answers
    Given I am on "/node/add/question"
    When I fill in "Question title" for "title_field[und][0][value]"
      And I fill in "Question body" for "body[und][0][value]"
      And I press "Save"
    Then I should see "Question title"
      And I should see "Question body"
    Given I am on "/node/add/answer"
    When I fill in "Question title" for "field_related_question[und][0][target_id]"
      And I fill in "Answer title" for "title_field[und][0][value]"
      And I fill in "Answer body" for "body[und][0][value]"
      And I press "Save"
    Then I should see "Answer title"
      And I should see "Answer body"

  @api
  Scenario: Authenticated users can create wikis
    Given I am on "/node/add/wiki"
    When I fill in "Wiki title" for "title_field[und][0][value]"
    And I fill in "Wiki body" for "body[und][0][value]"
    And I press "Save"
    Then I should see "Wiki title"
    And I should see "Wiki body"
