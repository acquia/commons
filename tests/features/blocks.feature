Feature: Block functionality
  Scenario: Search form
    Given I am on "/"
    Then I should see "Site" in the "Header" region
      And I should see "Users" in the "Header" region
  Scenario: Commons utility links
    Given I am on "/"
    Then I should see "Sign up" in the "Header" region
      And I should see "Log in" in the "Header" region
  Scenario: Main menu
    Given I am on "/"
    Then I should see "Home" in the "Menu bar" region
      And I should see "Groups" in the "Menu bar" region
      And I should see "Events" in the "Menu bar" region
  Scenario: Main page content
    Given I am on "/"
    Then I should see "Welcome to our community" in the "Content" region
  Scenario: Default footer
    Given I am on "/"
    Then I should see "A Commons Community, powered by Acquia" in the "Footer" region

  @api
  Scenario: Main page content
    Given I am on "/"
      And I am logged in as a user with the "authenticated user" role
    Then I should not see "What's going on?" in the "Content" region

  @api
  Scenario: Commons utility links
    Given I am on "/"
      And I am logged in as a user with the "authenticated user" role
    Then I should see "Log out" in the "Header" region
      And I should see "Settings" in the "Header" region
