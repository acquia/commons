<?php

require_once("AlchemyAPIParams.php");

class AlchemyAPI
{
	const XML_OUTPUT_MODE = "xml";
	const JSON_OUTPUT_MODE = "json";

	private $_apiKey = '';
	private $_hostPrefix = 'access';

	public function setAPIHost($apiHost)
	{
		$this->_hostPrefix = $apiHost;

		if (strlen($this->_hostPrefix) < 2)
		{
			throw new Exception("Error setting API host.");
		}
	}

	public function setAPIKey($apiKey)
	{
		$this->_apiKey = $apiKey;

		if (strlen($this->_apiKey) < 5)
		{
			throw new Exception("Error setting API key.");
		}
	}

	public function loadAPIKey($filename)
	{
		$handle = fopen($filename, 'r');
		$theData = fgets($handle, 512);
		fclose($handle);
		$this->_apiKey = rtrim($theData);

		if (strlen($this->_apiKey) < 5)
		{
			throw new Exception("Error loading API key.");
		}
	}

	public function URLGetRankedNamedEntities($url, $outputMode = self::XML_OUTPUT_MODE, $namedEntityParams = null)
	{
		$this->CheckURL($url, $outputMode);
		$this->CheckParamType("AlchemyAPI_NamedEntityParams", $namedEntityParams);
		
		if(is_null($namedEntityParams))
			$namedEntityParams = new AlchemyAPI_NamedEntityParams();
		
		$namedEntityParams->setUrl($url);
		$namedEntityParams->setOutputMode($outputMode);

		return $this->GET("URLGetRankedNamedEntities", "url", $namedEntityParams);
	}

	public function HTMLGetRankedNamedEntities($html, $url, $outputMode = self::XML_OUTPUT_MODE, $namedEntityParams = null)
	{
		$this->CheckHTML($html, $url, $outputMode);
		$this->CheckParamType("AlchemyAPI_NamedEntityParams", $namedEntityParams);
				
		if(is_null($namedEntityParams))
			$namedEntityParams = new AlchemyAPI_NamedEntityParams();
		
		$namedEntityParams->setHtml($html);
		$namedEntityParams->setUrl($url);
		$namedEntityParams->setOutputMode($outputMode);

		return $this->POST("HTMLGetRankedNamedEntities", "html", $namedEntityParams);
	}

	public function TextGetRankedNamedEntities($text, $outputMode = self::XML_OUTPUT_MODE, $namedEntityParams = null)
	{
		$this->CheckText($text, $outputMode);
		$this->CheckParamType("AlchemyAPI_NamedEntityParams", $namedEntityParams);
		
		if(is_null($namedEntityParams))
			$namedEntityParams = new AlchemyAPI_NamedEntityParams();
		
		$namedEntityParams->setText($text);
		$namedEntityParams->setOutputMode($outputMode);

		return $this->POST("TextGetRankedNamedEntities", "text", $namedEntityParams);
	}

	public function URLGetRankedKeywords($url, $outputMode = self::XML_OUTPUT_MODE, $keywordParams = null)
	{
		$this->CheckURL($url, $outputMode);
		$this->CheckParamType("AlchemyAPI_KeywordParams", $keywordParams);
		
		if(is_null($keywordParams))
			$keywordParams = new AlchemyAPI_KeywordParams();
		
		$keywordParams->setUrl($url);
		$keywordParams->setOutputMode($outputMode);

		return $this->GET("URLGetRankedKeywords", "url", $keywordParams);
	}

	public function HTMLGetRankedKeywords($html, $url, $outputMode = self::XML_OUTPUT_MODE, $keywordParams = null)
	{
		$this->CheckHTML($html, $url, $outputMode);
		$this->CheckParamType("AlchemyAPI_KeywordParams", $keywordParams);
		
		if(is_null($keywordParams))
			$keywordParams = new AlchemyAPI_KeywordParams();
		
		$keywordParams->setHtml($html);
		$keywordParams->setUrl($url);
		$keywordParams->setOutputMode($outputMode);

		return $this->POST("HTMLGetRankedKeywords", "html", $keywordParams);
	}

	public function TextGetRankedKeywords($text, $outputMode = self::XML_OUTPUT_MODE, $keywordParams = null)
	{
		$this->CheckText($text, $outputMode);
		$this->CheckParamType("AlchemyAPI_KeywordParams", $keywordParams);
		
			if(is_null($keywordParams))
			$keywordParams = new AlchemyAPI_KeywordParams();
		
		$keywordParams->setText($text);
		$keywordParams->setOutputMode($outputMode);

		return $this->POST("TextGetRankedKeywords", "text", $keywordParams);
	}

	public function URLGetLanguage($url, $outputMode = self::XML_OUTPUT_MODE, $languageParams = null)
	{
		$this->CheckURL($url, $outputMode);
		$this->CheckParamType("AlchemyAPI_LanguageParams", $languageParams);
		
		if(is_null($languageParams))
			$languageParams = new AlchemyAPI_LanguageParams();
		
		$languageParams->setUrl($url);
		$languageParams->setOutputMode($outputMode);

		return $this->GET("URLGetLanguage", "url", $languageParams);
	}

	public function HTMLGetLanguage($html, $url, $outputMode = self::XML_OUTPUT_MODE, $languageParams = null)
	{
		$this->CheckHTML($html, $url, $outputMode);
		$this->CheckParamType("AlchemyAPI_LanguageParams", $languageParams);
		
		if(is_null($languageParams))
			$languageParams = new AlchemyAPI_LanguageParams();
		
		$languageParams->setHtml($html);
		$languageParams->setUrl($url);
		$languageParams->setOutputMode($outputMode);

		return $this->POST("HTMLGetLanguage", "html", $languageParams);
	}

	public function TextGetLanguage($text, $outputMode = self::XML_OUTPUT_MODE, $languageParams = null)
	{
		$this->CheckText($text, $outputMode);
		$this->CheckParamType("AlchemyAPI_LanguageParams", $languageParams);
		
		if(is_null($languageParams))
			$languageParams = new AlchemyAPI_LanguageParams();
		
		$languageParams->setText($text);
		$languageParams->setOutputMode($outputMode);

		return $this->POST("TextGetLanguage", "text", $languageParams);
	}
	

	public function URLGetCategory($url, $outputMode = self::XML_OUTPUT_MODE, $categorizeParams = null)
	{
		$this->CheckURL($url, $outputMode);
		$this->CheckParamType("AlchemyAPI_CategoryParams", $categorizeParams);
		
		if(is_null($categorizeParams))
			$categorizeParams = new AlchemyAPI_CategoryParams();
		
		$categorizeParams->setUrl($url);
		$categorizeParams->setOutputMode($outputMode);

		return $this->GET("URLGetCategory", "url", $categorizeParams);
	}

	public function HTMLGetCategory($html, $url, $outputMode = self::XML_OUTPUT_MODE, $categorizeParams = null)
	{
		$this->CheckHTML($html, $url, $outputMode);
		$this->CheckParamType("AlchemyAPI_CategoryParams", $categorizeParams);
		
		if(is_null($categorizeParams))
			$categorizeParams = new AlchemyAPI_CategoryParams();
		
		$categorizeParams->setHtml($html);
		$categorizeParams->setUrl($url);
		$categorizeParams->setOutputMode($outputMode);

		return $this->POST("HTMLGetCategory", "html", $categorizeParams);
	}

	public function TextGetCategory($text, $outputMode = self::XML_OUTPUT_MODE, $categorizeParams = null)
	{
		$this->CheckText($text, $outputMode);
		$this->CheckParamType("AlchemyAPI_CategoryParams", $categorizeParams);
		
		if(is_null($categorizeParams))
			$categorizeParams = new AlchemyAPI_CategoryParams();
		
		$categorizeParams->setText($text);
		$categorizeParams->setOutputMode($outputMode);

		return $this->POST("TextGetCategory", "text", $categorizeParams);
	}

	public function URLGetText($url, $outputMode = self::XML_OUTPUT_MODE, $textParams = null)
	{
		$this->CheckURL($url, $outputMode);
		$this->CheckParamType("AlchemyAPI_TextParams", $textParams);
		
		if(is_null($textParams))
			$textParams = new AlchemyAPI_TextParams();
		
		$textParams->setUrl($url);
		$textParams->setOutputMode($outputMode);

		return $this->GET("URLGetText", "url", $textParams);
	}

	public function HTMLGetText($html, $url, $outputMode = self::XML_OUTPUT_MODE, $textParams = null)
	{
		$this->CheckHTML($html, $url, $outputMode);
		$this->CheckParamType("AlchemyAPI_TextParams", $textParams);
		
		if(is_null($textParams))
			$textParams = new AlchemyAPI_TextParams();
		
		$textParams->setHtml($html);
		$textParams->setUrl($url);
		$textParams->setOutputMode($outputMode);

		return $this->POST("HTMLGetText", "html", $textParams);
	}

	public function URLGetRawText($url, $outputMode = self::XML_OUTPUT_MODE, $textParams = null)
	{
		$this->CheckURL($url, $outputMode);
		$this->CheckParamType("AlchemyAPI_TextParams", $textParams);
		
		if(is_null($textParams))
			$textParams = new AlchemyAPI_TextParams();
		
		$textParams->setUrl($url);
		$textParams->setOutputMode($outputMode);
		
		return $this->GET("URLGetRawText", "url", $textParams);
	}

	public function HTMLGetRawText($html, $url, $outputMode = self::XML_OUTPUT_MODE, $textParams = null)
	{
		$this->CheckHTML($html, $url, $outputMode);
		$this->CheckParamType("AlchemyAPI_TextParams", $textParams);
		
		if(is_null($textParams))
			$textParams = new AlchemyAPI_TextParams();
		
		$textParams->setHtml($html);
		$textParams->setUrl($url);
		$textParams->setOutputMode($outputMode);

		return $this->POST("HTMLGetRawText", "html", $textParams);
	}

	public function URLGetTitle($url, $outputMode = self::XML_OUTPUT_MODE, $textParams = null)
	{
		$this->CheckURL($url, $outputMode);
		$this->CheckParamType("AlchemyAPI_TextParams", $textParams);
		
		if(is_null($textParams))
			$textParams = new AlchemyAPI_TextParams();
		
		$textParams->setUrl($url);
		$textParams->setOutputMode($outputMode);

		return $this->GET("URLGetTitle", "url", $textParams);
	}

	public function HTMLGetTitle($html, $url, $outputMode = self::XML_OUTPUT_MODE, $textParams = null)
	{
		$this->CheckHTML($html, $url, $outputMode);
		$this->CheckParamType("AlchemyAPI_TextParams", $textParams);
		
		if(is_null($textParams))
			$textParams = new AlchemyAPI_TextParams();
		
		$textParams->setHtml($html);
		$textParams->setUrl($url);
		$textParams->setOutputMode($outputMode);

		return $this->POST("HTMLGetTitle", "html", $textParams);
	}

	public function URLGetFeedLinks($url, $outputMode = self::XML_OUTPUT_MODE, $params = null)
	{
		$this->CheckURL($url, $outputMode);
		$this->CheckParamType("AlchemyAPI_Params", $params);
		
		if(is_null($params))
			$params = new AlchemyAPI_Params();
		
		$params->setUrl($url);
		$params->setOutputMode($outputMode);

		return $this->GET("URLGetFeedLinks", "url", $params);
	}

	public function HTMLGetFeedLinks($html, $url, $outputMode = self::XML_OUTPUT_MODE, $params = null)
	{
		$this->CheckHTML($html, $url, $outputMode);
		$this->CheckParamType("AlchemyAPI_Params", $params);
	
		if(is_null($params))
			$params = new AlchemyAPI_Params();
		
		
		$params->setHtml($html);
		$params->setUrl($url);
		$params->setOutputMode($outputMode);

		return $this->POST("HTMLGetFeedLinks", "html", $params);
	}

	public function URLGetMicroformats($url, $outputMode = self::XML_OUTPUT_MODE, $params = null)
	{
		$this->CheckURL($url, $outputMode);
		$this->CheckParamType("AlchemyAPI_Params", $params);
		
		if(is_null($params))
			$params = new AlchemyAPI_Params();
		
		$params->setUrl($url);
		$params->setOutputMode($outputMode);

		return $this->GET("URLGetMicroformatData", "url", $params);
	}

	public function HTMLGetMicroformats($html, $url, $outputMode = self::XML_OUTPUT_MODE, $params = null)
	{
		$this->CheckHTML($html, $url, $outputMode);
		$this->CheckParamType("AlchemyAPI_Params", $params);
		
		if(is_null($params))
			$params = new AlchemyAPI_Params();
		
		$params->setHtml($html);
		$params->setUrl($url);
		$params->setOutputMode($outputMode);

		return $this->POST("HTMLGetMicroformatData", "html", $params);
	}

	public function URLGetConstraintQuery($url, $query, $outputMode = self::XML_OUTPUT_MODE, $constraintParams = null)
    {
        $this->CheckURL($url, $outputMode);
		$this->CheckParamType("AlchemyAPI_ConstraingQueryParams", $constraintParams);
		
        if (strlen($query) < 2)
        {
            throw new Exception("Invalid constraint query specified.");
        }
		
		if(is_null($constraintParams))
			$constraintParams = new AlchemyAPI_ConstraintQueryParams();
		
		$constraintParams->setUrl($url);
		$constraintParams->setOutputMode($outputMode);
		$constraintParams->setCQuery($query);

        return $this->GET("URLGetConstraintQuery", "url", $constraintParams);
    }

    public function HTMLGetConstraintQuery($html, $url, $query, $outputMode = self::XML_OUTPUT_MODE, $constraintParams = null)
    {
        $this->CheckHTML($html, $url, $outputMode);
		$this->CheckParamType("AlchemyAPI_ConstraingQueryParams", $constraintParams);
		
        if (strlen($query) < 2)
        {
            throw new Exception("Invalid constraint query specified.");
        }
				
		$constraintParams = new AlchemyAPI_ConstraintQueryParams();
		
		$constraintParams->setUrl($url);
		$constraintParams->setHtml($html);
		$constraintParams->setOutputMode($outputMode);
		$constraintParams->setCQuery($query);

        return $this->POST("HTMLGetConstraintQuery", "html", $constraintParams);
    }

	private function CheckOutputMode($outputMode)
	{
		if (strlen($this->_apiKey) < 5)
                {
                        throw new Exception("Load an API key.");
                }

                if (self::XML_OUTPUT_MODE !== $outputMode &&
                    self::JSON_OUTPUT_MODE !== $outputMode)
                {
                        throw new Exception("Illegal Output Mode specified, see *_OUTPUT_MODE constants.");
                }
	}

	private function CheckURL($url, $outputMode)
	{
		$this->CheckOutputMode($outputMode);

		if (strlen($url) < 10)
		{
			throw new Exception("Enter a valid URL to analyze.");
		}
	}

	private function CheckHTML($html, $url, $outputMode)
	{
		$this->CheckURL($url, $outputMode);

		if (strlen($html) < 10)
		{
			throw new Exception("Enter a HTML document to analyze.");
		}
	}

	private function CheckText($text, $outputMode)
	{
		$this->CheckOutputMode($outputMode);

		if (strlen($text) < 5)
		{
			throw new Exception("Enter some text to analyze.");
		}
	}
	
	private function CheckParamType($className, $class)
	{
		if(!is_null($class) && ($className != get_class($class)) )
		{
			throw new Exception("Trying to pass ".get_class($class)." into a function that requires ".$className);
		}
	}

	private function POST()
	{ // callMethod, $callPrefix, $parameterObject
		$callMethod = func_get_arg(0);
		$callPrefix = func_get_arg(1);
		$paramObj = func_get_arg(2);
		
		$outputMode = $paramObj->getOutputMode();
		
		$data = "apikey=".$this->_apiKey."&outputMode=".$outputMode.$paramObj->getParameterString();
		
		$params = array('http' => array('method' => 'POST',
						'Content-type'=> 'application/x-www-form-urlencoded',
						'Content-length' =>strlen( $data ),
						'content' => $data
						));

		$hostPrefix = $this->_hostPrefix;
		$endpoint = "http://$hostPrefix.alchemyapi.com/calls/$callPrefix/$callMethod";

		$context = stream_context_create($params);
		
		return $this->DoRequest($endpoint,$context,$outputMode);
	}
	
	private function GET()
	{ // callMethod, $callPrefix, $parameterObject
		$callMethod = func_get_arg(0);
		$callPrefix = func_get_arg(1);
		$paramObj = func_get_arg(2);
		
		$outputMode = $paramObj->getOutputMode();
		
		$data = "apikey=".$this->_apiKey."&outputMode=".$outputMode.$paramObj->getParameterString();

		$params = array('http' => array('method' => 'GET',
						'Content-type'=> 'application/x-www-form-urlencoded'
						));

		$hostPrefix = $this->_hostPrefix;
		$uri = "http://$hostPrefix.alchemyapi.com/calls/$callPrefix/$callMethod"."?".$data;

		$context = stream_context_create($params);
		
		return $this->DoRequest($uri,$context,$outputMode);
	
	}
	
	private function DoRequest($uri,$context, $outputMode) 
	{
		$fp = @fopen($uri, 'rb', false, $context);
		if (!($fp))
		{
			throw new Exception("Error making API call.");
		}

		$response = @stream_get_contents($fp);
		fclose($fp);
		if ($response === false)
		{
			throw new Exception("Error making API call.");
		}

		if (self::XML_OUTPUT_MODE == $outputMode)
		{
			$doc = simplexml_load_string($response);

                	if (!($doc))
	        	{
    	        		throw new Exception("Error making API call.");
			}

			$status = $doc->xpath("/results/status");
			if ($status[0] != "OK")
			{
				$statusInfo = $doc->xpath("/results/statusInfo");
				throw new Exception("Error making API call: $statusInfo[0]");
			}
		}
		else
		{
			$obj = json_decode($response);

			if (is_null($obj))
			{
				throw new Exception("Error making API call.");
			}
			if ("OK" != $obj->{'status'})
			{
				$statusInfo = $obj->{'statusInfo'};
				throw new Exception("Error making API call: $statusInfo");
			}
		}

		return $response;
	}
}


?>
