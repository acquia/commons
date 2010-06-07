<?php

/**
* @file drupal_soap_client.inc
* Wrapper class for SOAP client
*/

/**
* @class DrupalSoapClient 
* Wrapper class for SOAP client
*/

class DrupalSoapClient
{
  // private
  private $client  = NULL;
  private $options = array();
  private $library = '';
  
  function __construct($library, $client, $options)
  {
    $this->library = $library;
    $this->client  = $client;
    $this->options = $options;
  }
    
  /**
  * request a SOAP service function call. Fault, if occur, will be
  * handle and translate to an ordinary error.
  * 
  * @param $function
  *   A string represent the function name.
  * 
  * @param $params
  *   An array of the function's parameters.
  * 
  * @return
  *   An array of the result with following keys:
  *   - #error  : false, if no error. Otherwise, it is the error message
  *   - #return : the return value from the service.
  */
  function call($function, $params = array())
  {
    $result = array();
    $result['#error']  = FALSE;
    $result['#return'] = NULL;
    
    // validate parameters
    if ( empty($function) )
    {
      $result['#error'] = t('Function name is required');
      return $result;
    }
    
    //watchdog('soapclient', 'making soap call', NULL, WATCHDOG_DEBUG);

    $params = (array) $params;

    if ( $this->client == NULL )
    {
      $result['#error'] = t('SOAP client object is not initialised');
      return $result;
    }

    if ( $this->library == 'nuSOAP' )
    {
      $result['#return'] = $this->client->call($function, $params,
                                               $this->options['namespace'],
                                               $this->options['action'],
                                               $this->options['headers'],
                                               NULL,
                                               $this->options['style'],
                                               $this->options['use']);
      //dpm($params);
      //dpm($result);

      if ( $this->client->fault )
      {
        $result['#error'] = t('Fault !code: !msg', array( '!code' => $result['return']['faultcode'], '!msg' => $result['return']['faultstring'] ));
        return $result;
      }

      $err_msg = $this->client->getError();

      if ( ! empty($err_msg) )
      {
        $result['#error'] = t('Service return error - !msg', array('!msg' => $err_msg));
        return $result;
      }
    }
    else if ( $this->library == 'PHP5SOAP' )
    {
      try
      {
        $result['#return'] = $this->client->__soapCall($function, $params);
      }
      catch(Exception $e)
      {
        $result['#error'] = t($e->getMessage());
        return $result;
      }

      if ( is_soap_fault($result['#return']) )
      {
        $result['#error'] = t('Fault !code: !msg', array( '!code' => $result['#return']->faultcode, '!msg' => $result['#return']->faultstring ));
        return $result;
      }
      
      $result['#return'] = soapclient_object_to_array($result['#return']);
    }
    else // not supported library
    {
      $result['#error'] = t("Un-supported SOAP library - {$this->library}");
      return $result;
    }

    return $result;
  }
}
