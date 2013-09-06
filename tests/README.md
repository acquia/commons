# The Commons Test Suite

Current status:  
[![Build Status](https://travis-ci.org/acquia/commons3.png?branch=7.x-3.x)](https://travis-ci.org/acquia/commons3)

This folder is the home for the Drupal Commons integration tests.  
To run the tests on commits, the [drupal.org project](https://drupal.org/project/commons) is mirrored 
to [Github](https://github.com/acquia/commons3) so we're able to use [Travis CI](https://travis-ci.org/) to run the tests.
The Travis CI project page for Commons can be found [over here](https://travis-ci.org/acquia/commons3/).


## The build process

The Travis CI build process is configured within the [.travis.yml](../.travis.yml) file present in the root directory.  
It currently includes:

- building the makefile using Drush
- installing the resulting distribution using drush site-install
- running the behat based tests ("features")


## The stack

### [Behat](http://behat.org/):  
A php based Behavior Driven Development framework for testing your business expectations.  
It drives the whole test lifecycle and allows us to formulate test cases as regular english sentences.
### [Mink](http://mink.behat.org/):  
Mink is an open source acceptance test framework for web applications.  
It "remote controls" several different types of browsers (from Firefox to headless phantomjs based ones).
### [Drupal Extension](https://drupal.org/project/drupalextension):  
The Drupal Extension is an integration layer between Behat, Mink Extension, and Drupal. It provides step definitions for common testing scenarios specific to Drupal sites.
The predefined drupal specific steps should save us a lot of time writing helper code for using the basic navigational elements.
The currently (July 2013) defined steps are as follows:

    $ bin/behat -dl
    Given /^(?:that I|I) am at "(?P[^"]*)"$/
     When /^I visit "(?P[^"]*)"$/
     When /^I click "(?P<link>[^"]*)"$/
    Given /^for "(?P<field>[^"]*)" I enter "(?P<value>[^"]*)"$/
    Given /^I enter "(?P<value>[^"]*)" for "(?P<field>[^"]*)"$/
     When /^I press the "(?P<button>[^"]*)" button$/
     Then /^I should see the link "(?P<link>[^"]*)"$/
     Then /^I should not see the link "(?P<link>[^"]*)"$/
     Then /^I (?:|should )see the heading "(?P<heading>[^"]*)"$/
     Then /^I (?:|should )not see the heading "(?P<heading>[^"]*)"$/
     Then /^I should see the heading "(?P<heading>[^"]*)" in the "(?P<region>[^"]*)"(?:| region)$/
     Then /^I should see the "(?P<heading>[^"]*)" heading in the "(?P<region>[^"]*)"(?:| region)$/
     When /^I (?:follow|click) "(?P<link>[^"]*)" in the "(?P<region>[^"]*)"(?:| region)$/
     Then /^I should see the link "(?P<link>[^"]*)" in the "(?P<region>[^"]*)"(?:| region)$/
     Then /^I should not see the link "(?P<link>[^"]*)" in the "(?P<region>[^"]*)"(?:| region)$/
     Then /^I should see (?:the text |)"(?P<text>[^"]*)" in the "(?P<region>[^"]*)"(?:| region)$/
     Then /^I should not see (?:the text |)"(?P<text>[^"]*)" in the "(?P<region>[^"]*)"(?:| region)$/
    Given /^I press "(?P<button>[^"]*)" in the "(?P<region>[^"]*)"(?:| region)$/
    Given /^(?:|I )fill in "(?P<value>(?:[^"]|\\")*)" for "(?P<field>(?:[^"]|\\")*)" in the "(?P<region>[^"]*)"(?:| region)$/
    Given /^(?:|I )fill in "(?P<field>(?:[^"]|\\")*)" with "(?P<value>(?:[^"]|\\")*)" in the "(?P<region>[^"]*)"(?:| region)$/
     Then /^(?:I|I should) see the text "(?P<text>[^"]*)"$/
     Then /^I should not see the text "(?P<text>[^"]*)"$/
     Then /^I should get a "(?P<code>[^"]*)" HTTP response$/
     Then /^I should not get a "(?P<code>[^"]*)" HTTP response$/
    Given /^I check the box "(?P<checkbox>[^"]*)"$/
    Given /^I uncheck the box "(?P<checkbox>[^"]*)"$/
     When /^I select the radio button "(?P<label>[^"]*)" with the id "(?P<id>[^"]*)"$/
     When /^I select the radio button "(?P<label>[^"]*)"$/
    Given /^I am an anonymous user$/
    Given /^I am not logged in$/
    Given /^I am logged in as a user with the "(?P<role>[^"]*)" role$/
    Given /^I click "(?P<link>[^"]*)" in the "(?P<row_text>[^"]*)" row$/
    Given /^the cache has been cleared$/
    Given /^I run cron$/
    Given /^I am viewing (?:a|an) "(?P<type>[^"]*)" node with the title "(?P<title>[^"]*)"$/
    Given /^(?:a|an) "(?P<type>[^"]*)" node with the title "(?P<title>[^"]*)"$/
    Given /^I am viewing my "(?P<type>[^"]*)" node with the title "(?P<title>[^"]*)"$/
    Given /^"(?P<type>[^"]*)" nodes:$/
    Given /^I am viewing (?:a|an) "(?P<vocabulary>[^"]*)" term with the name "(?P<name>[^"]*)"$/
    Given /^(?:a|an) "(?P<vocabulary>[^"]*)" term with the name "(?P<name>[^"]*)"$/
    Given /^users:$/
    Given /^"(?P<vocabulary>[^"]*)" terms:$/
     Then /^I should see the error message(?:| containing) "([^"]*)"$/
     Then /^I should see the following <error messages>$/
    Given /^I should not see the error message(?:| containing) "([^"]*)"$/
     Then /^I should not see the following <error messages>$/
     Then /^I should see the success message(?:| containing) "([^"]*)"$/
     Then /^I should see the following <success messages>$/
    Given /^I should not see the success message(?:| containing) "([^"]*)"$/
     Then /^I should not see the following <success messages>$/
     Then /^I should see the message(?:| containing) "([^"]*)"$/
     Then /^I should not see the message(?:| containing) "([^"]*)"$/
     Then /^(?:|I )break$/
    Given /^(?:|I )am on (?:|the )homepage$/
     When /^(?:|I )go to (?:|the )homepage$/
    Given /^(?:|I )am on "(?P<page>[^"]+)"$/
     When /^(?:|I )go to "(?P<page>[^"]+)"$/
     When /^(?:|I )reload the page$/
     When /^(?:|I )move backward one page$/
     When /^(?:|I )move forward one page$/
     When /^(?:|I )press "(?P<button>(?:[^"]|\\")*)"$/
     When /^(?:|I )follow "(?P<link>(?:[^"]|\\")*)"$/
     When /^(?:|I )fill in "(?P<field>(?:[^"]|\\")*)" with "(?P<value>(?:[^"]|\\")*)"$/
     When /^(?:|I )fill in "(?P<field>(?:[^"]|\\")*)" with:$/
     When /^(?:|I )fill in "(?P<value>(?:[^"]|\\")*)" for "(?P<field>(?:[^"]|\\")*)"$/
     When /^(?:|I )fill in the following:$/
     When /^(?:|I )select "(?P<option>(?:[^"]|\\")*)" from "(?P<select>(?:[^"]|\\")*)"$/
     When /^(?:|I )additionally select "(?P<option>(?:[^"]|\\")*)" from "(?P<select>(?:[^"]|\\")*)"$/
     When /^(?:|I )check "(?P<option>(?:[^"]|\\")*)"$/
     When /^(?:|I )uncheck "(?P<option>(?:[^"]|\\")*)"$/
     When /^(?:|I )attach the file "(?P[^"]*)" to "(?P<field>(?:[^"]|\\")*)"$/
     Then /^(?:|I )should be on "(?P<page>[^"]+)"$/
     Then /^(?:|I )should be on (?:|the )homepage$/
     Then /^the (?i)url(?-i) should match (?P<pattern>"([^"]|\\")*")$/
     Then /^the response status code should be (?P<code>\d+)$/
     Then /^the response status code should not be (?P<code>\d+)$/
     Then /^(?:|I )should see "(?P<text>(?:[^"]|\\")*)"$/
     Then /^(?:|I )should not see "(?P<text>(?:[^"]|\\")*)"$/
     Then /^(?:|I )should see text matching (?P<pattern>"(?:[^"]|\\")*")$/
     Then /^(?:|I )should not see text matching (?P<pattern>"(?:[^"]|\\")*")$/
     Then /^the response should contain "(?P<text>(?:[^"]|\\")*)"$/
     Then /^the response should not contain "(?P<text>(?:[^"]|\\")*)"$/
     Then /^(?:|I )should see "(?P<text>(?:[^"]|\\")*)" in the "(?P<element>[^"]*)" element$/
     Then /^(?:|I )should not see "(?P<text>(?:[^"]|\\")*)" in the "(?P<element>[^"]*)" element$/
     Then /^the "(?P<element>[^"]*)" element should contain "(?P<value>(?:[^"]|\\")*)"$/
     Then /^the "(?P<element>[^"]*)" element should not contain "(?P<value>(?:[^"]|\\")*)"$/
     Then /^(?:|I )should see an? "(?P<element>[^"]*)" element$/
     Then /^(?:|I )should not see an? "(?P<element>[^"]*)" element$/
     Then /^the "(?P<field>(?:[^"]|\\")*)" field should contain "(?P<value>(?:[^"]|\\")*)"$/
     Then /^the "(?P<field>(?:[^"]|\\")*)" field should not contain "(?P<value>(?:[^"]|\\")*)"$/
     Then /^the "(?P<checkbox>(?:[^"]|\\")*)" checkbox should be checked$/
     Then /^the checkbox "(?P<checkbox>(?:[^"]|\\")*)" (?:is|should be) checked$/
     Then /^the "(?P<checkbox>(?:[^"]|\\")*)" checkbox should not be checked$/
     Then /^the checkbox "(?P<checkbox>(?:[^"]|\\")*)" should (?:be unchecked|not be checked)$/
     Then /^the checkbox "(?P<checkbox>(?:[^"]|\\")*)" is (?:unchecked|not checked)$/
     Then /^(?:|I )should see (?P<num>\d+) "(?P<element>[^"]*)" elements?$/
     Then /^print current URL$/
     Then /^print last response$/
     Then /^show last response$/

## Writing new tests


For information about how to write tests, I'd suggest looking at the official [behat documentation](http://docs.behat.org/quick_intro.html#define-your-feature).
One small piece of information: When you tag a scenario with @javascript, it will be executed in Firefox/Selenium2 rather than using the default "headless" goute driver.
