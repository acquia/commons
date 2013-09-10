<?php

use Behat\Behat\Context\ClosuredContextInterface,
Behat\Behat\Context\TranslatedContextInterface,
Behat\Behat\Context\BehatContext,
Behat\Behat\Exception\PendingException;
use Behat\Gherkin\Node\PyStringNode,
Behat\Gherkin\Node\TableNode;

//
// Require 3rd-party libraries here:
//
//   require_once 'PHPUnit/Autoload.php';
//   require_once 'PHPUnit/Framework/Assert/Functions.php';
//

/**
* Features context.
*/
class FeatureContext extends Drupal\DrupalExtension\Context\DrupalContext
{
  /**
  * Initializes context.
  * Every scenario gets its own context object.
  *
  * @param array $parameters context parameters (set them up through behat.yml)
  */
  public function __construct(array $parameters)
  {
    // Initialize your context here
  }
    
  /**
  * Take screenshot when step fails.
  * Works only with Selenium2Driver.
  *
  * @AfterStep @javascript
  */
  public function takeScreenshotAfterFailedStep(Behat\Behat\Event\StepEvent $event) {
    if (Behat\Behat\Event\StepEvent::FAILED === $event->getResult()) {
      $step = $event->getStep();
      $id = $step->getParent()->getTitle() . '.' . $step->getType() . ' ' . $step->getText();
      $fileName = getenv("TRAVIS_BUILD_DIR") . '/fail_'.preg_replace('/[^a-zA-Z0-9-_\.]/','_', $id) . '.png';
      $image = $this->getSession()->getScreenshot();
      file_put_contents($fileName, $image);
    }
  }
}
