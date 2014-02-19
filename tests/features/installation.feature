Feature: Site installation
  Scenario: Installation succeeded
    Given I am on "/"
    Then I should see "Oh hai"
  
  @javascript
  Scenario: Installation succeeded with js enabled
    Given I am on "/"
    Then I should see "Oh hai"

  Scenario: Login as the administrator
    Given I am on "/user"
    And for "name" I enter "admin"
    And for "pass" I enter "commons"
    When I press "Log in"
    Then I should see "What's going on?"

  @javascript
  Scenario: Login as the administrator with js enabled
    Given I am on "/user"
    And for "name" I enter "admin"
    And for "pass" I enter "commons"
    When I press "Log in"
    Then I should see "What's going on?"