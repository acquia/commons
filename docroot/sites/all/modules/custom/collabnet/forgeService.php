<?php
// $Id: forgeService.php

class GetProjectListMessage {
  public $sessionId; // string
}

class GetProjectDataMessage {
  public $sessionId; // string
  public $projectId; // string
}

class SOAPFilter {
  public $name;  // string
  public $value; // string
}

class GetDocumentFolderListMessage {
  public $sessionId; // string
  public $parentId;  // string
  public $recursive; // boolean
}

class GetDocumentFolderDataMessage {
  public $sessionId; // string
  public $folderId;  // string
}

class GetDocumentListMessage {
  public $sessionId; // string
  public $parentId;  // string
  public $filters;   // array of SOAPFilter
}

class GetDocumentDataMessage {
  public $sessionId;       // string
  public $documentId;      // string
  public $documentVersion; // integer
}

class LoginMessage {
  public $userName; // string
  public $password; // string
}

class LogoffMessage {
  public $userName;  // string
  public $sessionId; // string
}

class ReportingResponse {
  public $clickRate; // string
  public $clicks; // string
  public $clicksPCT; // string
}


/**
 * forgeService class
 *
 *
 *
 * @author    {author}
 * @copyright {copyright}
 * @package   {package}
 */
class forgeService extends SoapClient {
  public $server_uri;

  private static $classmap = array(
                                    'ForgeMessage' => 'ForgeMessage',
                                    'ReportingResponse' => 'ReportingResponse',
                                   );

  public function forgeService($wsdl, $options = array()) {
    foreach(self::$classmap as $key => $value) {
      if(!isset($options['classmap'][$key])) {
        $options['classmap'][$key] = $value;
      }
    }
    parent::__construct($wsdl, $options);
  }

  /**
   *
   *
   * @param ForgeMessage $in0
   * @return ArrayOf_soapenc_string
   */
  public function sendMessage(ForgeMessage $in0) {
    try {
      $time_before = (timer_read('page') / 1000);
      watchdog("collabnet", "About to call __soapCall - page timer: !timer", array('!timer' => $time_before ), WATCHDOG_NOTICE);
      $result = $this->__soapCall('sendMessage', array($in0),       array(
              'uri' => $this->server_uri,
            'soapaction' => ''
           )
           ); 
      $result_str = var_export($result, TRUE);
      $time_after = (timer_read('page') / 1000);           
      watchdog("collabnet", "Return from call to __soapCall - result: !result, page timer: !timer, elapsed time: !elapsed", array('!result' => $result_str, '!timer' => $time_after, '!elapsed' => $time_after - $time_before ), WATCHDOG_NOTICE);
      return $result;
     } catch (Exception $e) {
        watchdog("collabnet", "Exception when calling Collabnet SOAP Service: " . $e->getMessage());
        $result_str = var_export($result, TRUE);
        watchdog("collabnet", "Exception in __soapCall - result: !result, page timer: !timer, elapsed time: !elapsed", array('!result' => $result_str, '!timer' => $time_after, '!elapsed' => $time_after - $time_before ), WATCHDOG_NOTICE);
        $ret = array();
        $ret[0] = 1;
        return $ret;
     }
  }

}

?>
