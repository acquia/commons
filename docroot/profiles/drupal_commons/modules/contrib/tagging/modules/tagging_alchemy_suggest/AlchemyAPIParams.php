<?php

/* Parameter class for functions URLGetRankedNamedEntities, HTMLGetRankedNamedEntities, TextGetRankedNamedEntities
//
//  See http://www.alchemyapi.com/api/entity/proc.html for detailed parameter descriptions
//
*/
class AlchemyAPI_Params{
	private $url = null;
	private $html = null;
	private $text = null;
	private $outputMode = "xml";
	private $customParameters = null;
	
	private function outputMode_arr()
	{
		return array
		(
			'xml',
			'json'
		);
	} 
	
	public function getUrl(){
		return $this->url;
	}

	public function setUrl($url){
		$this->url = $url;
	}
	
	public function getHtml(){
		return $this->html;
	}

	public function setHtml($html){
		$this->html = $html;
	}
	
	public function getText(){
		return $this->text;
	}

	public function setText($text){
		$this->text = $text;
	}
	
	public function getOutputMode(){
		return $this->outputMode;
	}

	public function setOutputMode($outputMode){
		$arr = $this->outputMode_arr();
		$isValid = false;
		for($i=0;$i<count($arr);$i++){
			if($arr[$i] == $outputMode){
				$this->outputMode = $outputMode;
				return;
			}
		}
		if (!$isValid)
		{
			throw new Exception("Invalid setting (".$outputMode.") for parameter outputMode");
		}
	}
	
	public function getCustomParameters(){
		return $this->customParameters;
	}

	public function setCustomParameters(){
		$this->customParameters = "";
		
		$numargs = func_num_args();
		for($i = 0; $i < $numargs; $i++)
		{
		    $this->customParameters .= "&".func_get_arg($i);
		    if ((++$i) < $numargs)
			$this->customParameters .= "=".rawurlencode(func_get_arg($i));
		}
	}
	
	public function getParameterString() {
		$retString = "";
		if(isset($this->url))
			$retString=$retString."&url=".rawurlencode($this->url);
		if(isset($this->html))
			$retString=$retString."&html=".rawurlencode($this->html);
		if(isset($this->text))
			$retString=$retString."&text=".rawurlencode($this->text);
		if(isset($this->customParameters))
			$retString=$retString.$this->customParameters;
		return $retString;
	}

}

class AlchemyAPI_NamedEntityParams extends AlchemyAPI_Params{	  

	private $disambiguate = null;
	private $linkedData = null;
	private $coreference = null;
	private $quotations = null;
	private $sourceText = null;
	private $showSourceText = null;
	private $maxRetrieve = null;
	private $baseUrl = null;
	private $cQuery = null;
	private $xPath = null;
	
	private function sourceText_arr()
	{
		return array
		(
			'cleaned_or_raw',
			'cleaned',
			'raw',
			'cquery',
			'xpath'
		);
	} 

	public function getDisambiguate(){
		return $this->disambiguate;
	}

	public function setDisambiguate($disambiguate){
		if ($disambiguate != 0 && $disambiguate != 1)
		{
			throw new Exception("Invalid setting (".$disambiguate.") for parameter disambiguate");
		}
		$this->disambiguate = $disambiguate;
	}

	public function getLinkedData(){
		return $this->linkedData;
	}

	public function setLinkedData($linkedData){
		if ($linkedData != 0 && $linkedData != 1)
		{
			throw new Exception("Invalid setting (".$linkedData.") for parameter linkedData");
		}
		$this->linkedData = $linkedData;
	}

	public function getCoreference(){
		return $this->coreference;
	}

	public function setCoreference($coreference){
		if ($coreference != 0 && $coreference != 1)
		{
			throw new Exception("Invalid setting (".$coreference.") for parameter coreference");
		}
		$this->coreference = $coreference;
	}

	public function getQuotations(){
		return $this->quotations;
	}

	public function setQuotations($quotations){
		if ($quotations != 0 && $quotations != 1)
		{
			throw new Exception("Invalid setting (".$quotations.") for parameter quotations");
		}
		$this->quotations = $quotations;
	}
	
	public function getSourceText(){
		return $this->sourceText;
	}

	public function setSourceText($sourceText){
		$arr = $this->sourceText_arr();
		$isValid = false;
		for($i=0;$i<count($arr);$i++){
			if($arr[$i] == $sourceText){
				$this->sourceText = $sourceText;
				return;
			}
		}
		if (!$isValid)
		{
			throw new Exception("Invalid setting (".$sourceText.") for parameter sourceText");
		}
	}

	public function getShowSourceText(){
		return $this->showSourceText;
	}

	public function setShowSourceText($showSourceText){
		if ($showSourceText != 0 && $showSourceText != 1)
		{
			throw new Exception("Invalid setting (".$showSourceText.") for parameter showSourceText");
		}
		$this->showSourceText = $showSourceText;
	}

	public function getMaxRetrieve(){
		return $this->maxRetrieve;
	}

	public function setMaxRetrieve($maxRetrieve){
		$this->maxRetrieve = $maxRetrieve;
	}

	public function getBaseUrl(){
		return $this->baseUrl;
	}

	public function setBaseUrl($baseUrl){
		$this->baseUrl = $baseUrl;
	}
	
	public function getCQuery(){
		return $this->cQuery;
	}

	public function setCQuery($cQuery){
		$this->cQuery = $cQuery;
	}
	
	public function getXPath(){
		return $this->xPath;
	}

	public function setXPath($xPath){
		$this->xPath = $xPath;
	}
	

	
	public function getParameterString() {
		$retString = parent::getParameterString();
		if(isset($this->disambiguate))
			$retString=$retString."&disambiguate=".rawurlencode($this->disambiguate);
		if(isset($this->linkedData))
			$retString=$retString."&linkedData=".rawurlencode($this->linkedData);
		if(isset($this->coreference))
			$retString=$retString."&coreference=".rawurlencode($this->coreference);
		if(isset($this->quotations))
			$retString=$retString."&quotations=".rawurlencode($this->quotations);
		if(isset($this->showSourceText))
			$retString=$retString."&showSourceText=".rawurlencode($this->showSourceText);
		if(isset($this->sourceText))
			$retString=$retString."&sourceText=".rawurlencode($this->sourceText);
		if(isset($this->maxRetrieve))
			$retString=$retString."&maxRetrieve=".rawurlencode($this->maxRetrieve);
		if(isset($this->baseUrl))
			$retString=$retString."&baseUrl=".rawurlencode($this->baseUrl);
		if(isset($this->cQuery))
			$retString=$retString."&cquery=".rawurlencode($this->cQuery);
		if(isset($this->xPath))
			$retString=$retString."&xpath=".rawurlencode($this->xPath);
		return $retString;
	}

}

/* Parameter class for functions URLGetCategory, HTMLGetCategory, TextGetCategory
//
//  See http://www.alchemyapi.com/api/categ/proc.html for detailed parameter descriptions
//
*/
class AlchemyAPI_CategoryParams extends AlchemyAPI_Params{	  

	private $sourceText = null;
	private $cQuery = null;
	private $xPath = null;
	private $baseUrl = null;
	
	private function sourceText_arr()
	{
		return array
		(
			'cleaned_or_raw',
			'cquery',
			'xpath'
		);
	}  
	
	public function getSourceText(){
		return $this->sourceText;
	}

	public function setSourceText($sourceText){
		$arr = $this->sourceText_arr();
		$isValid = false;
		for($i=0;$i<count($arr);$i++){
			if($arr[$i] == $sourceText){
				$this->sourceText = $sourceText;
				return;
			}
		}
		if (!$isValid)
		{
			throw new Exception("Invalid setting (".$sourceText.") for parameter sourceText");
		}
	}

	public function getCQuery(){
		return $this->cQuery;
	}

	public function setCQuery($cQuery){
		$this->cQuery = $cQuery;
	}

	public function getXPath(){
		return $this->xPath;
	}

	public function setXPath($xPath){
		$this->xPath = $xPath;
	}

	public function getBaseUrl(){
		return $this->baseUrl;
	}

	public function setBaseUrl($baseUrl){
		$this->baseUrl = $baseUrl;
	}
	
	public function getParameterString() {
		$retString = parent::getParameterString();
		if(isset($this->sourceText))
			$retString=$retString."&sourceText=".rawurlencode($this->sourceText);
		if(isset($this->cQuery))
			$retString=$retString."&cquery=".rawurlencode($this->cQuery);
		if(isset($this->xPath))
			$retString=$retString."&xpath=".rawurlencode($this->xPath);
		if(isset($this->baseUrl))
			$retString=$retString."&baseUrl=".rawurlencode($this->baseUrl);	
		return $retString;
	}

}

/* Parameter class for functions URLGetLanguage, HTMLGetLanguage, TextGetLanguage
//
//  See http://www.alchemyapi.com/api/lang/proc.html for detailed parameter descriptions
//
*/
class AlchemyAPI_LanguageParams extends AlchemyAPI_Params{	  

	private $sourceText = null;
	private $cQuery = null;
	private $xPath = null;
	
	private function sourceText_arr()
	{
		return array
		(
			'cleaned_or_raw',
			'cleaned',
			'raw',
			'cquery',
			'xpath'
		);
	}  
	
	public function getSourceText(){
		return $this->sourceText;
	}

	public function setSourceText($sourceText){
		$arr = $this->sourceText_arr();
		$isValid = false;
		for($i=0;$i<count($arr);$i++){
			if($arr[$i] == $sourceText){
				$this->sourceText = $sourceText;
				return;
			}
		}
		if (!$isValid)
		{
			throw new Exception("Invalid setting (".$sourceText.") for parameter sourceText");
		}
	}

	public function getCQuery(){
		return $this->cQuery;
	}

	public function setCQuery($cQuery){
		$this->cQuery = $cQuery;
	}

	public function getXPath(){
		return $this->xPath;
	}

	public function setXPath($xPath){
		$this->xPath = $xPath;
	}
	
	public function getParameterString() {
		$retString = parent::getParameterString();
		if(isset($this->sourceText))
			$retString=$retString."&sourceText=".rawurlencode($this->sourceText);
		if(isset($this->cQuery))
			$retString=$retString."&cquery=".rawurlencode($this->cQuery);
		if(isset($this->xPath))
			$retString=$retString."&xpath=".rawurlencode($this->xPath);
		return $retString;
	}

}

/* Parameter class for functions URLGetRankedKeywords, HTMLGetRankedKeywords, TextGetRankedKeywords
//
//  See http://www.alchemyapi.com/api/keyword/proc.html for detailed parameter descriptions
//
*/
class AlchemyAPI_KeywordParams extends AlchemyAPI_Params{	  

	private $maxRetrieve = null;
	private $sourceText = null;
	private $showSourceText = null;
	private $cQuery = null;
	private $xPath = null;
	private $baseUrl = null;
	private $keywordExtractMode = null;
	
	private function sourceText_arr()
	{
		return array
		(
			'cleaned_or_raw',
			'cleaned',
			'raw',
			'cquery',
			'xpath'
		);
	}    
	
	public function getMaxRetrieve(){
		return $this->maxRetrieve;
	}

	public function setMaxRetrieve($souceText){
		$this->maxRetrieve = $maxRetrieve;
	}
	
	public function getSourceText(){
		return $this->sourceText;
	}

	public function setSourceText($sourceText){
		$arr = $this->sourceText_arr();
		$isValid = false;
		for($i=0;$i<count($arr);$i++){
			if($arr[$i] == $sourceText){
				$this->sourceText = $sourceText;
				return;
			}
		}
		if (!$isValid)
		{
			throw new Exception("Invalid setting (".$sourceText.") for parameter sourceText");
		}
	}

	public function getShowSourceText(){
		return $this->showSourceText;
	}

	public function setShowSourceText($showSourceText){
		if ($showSourceText != 0 && $showSourceText != 1)
		{
			throw new Exception("Invalid setting (".$showSourceText.") for parameter showSourceText");
		}
		$this->showSourceText = $showSourceText;
	}

	public function getCQuery(){
		return $this->cQuery;
	}

	public function setCQuery($cQuery){
		$this->cQuery = $cQuery;
	}

	public function getXPath(){
		return $this->xPath;
	}

	public function setXpath($xPath){
		$this->xPath = $xPath;
	}

	public function getBaseUrl(){
		return $this->baseUrl;
	}

	public function setBaseUrl($baseUrl){
		$this->baseUrl = $baseUrl;
	}
	
	public function getKeywordExtractMode(){
		return $this->keywordExtractMode;
	}

	public function setKeywordExtractMode($keywordExtractMode){
		if ($keywordExtractMode != "strict")
		{
			throw new Exception("Invalid setting (".$keywordExtractMode.") for parameter keywordExtractMode");
		}
		$this->keywordExtractMode = $keywordExtractMode;
	}
	
	
	public function getParameterString() {
		$retString = parent::getParameterString();
		if(isset($this->maxRetrieve))
			$retString=$retString."&maxRetrieve=".rawurlencode($this->maxRetrieve);
		if(isset($this->sourceText))
			$retString=$retString."&sourceText=".rawurlencode($this->sourceText);
		if(isset($this->showSourceText))
			$retString=$retString."&showSourceText=".rawurlencode($this->showSourceText);
		if(isset($this->cQuery))
			$retString=$retString."&cquery=".rawurlencode($this->cQuery);
		if(isset($this->xPath))
			$retString=$retString."&xpath=".rawurlencode($this->xPath);
		if(isset($this->baseUrl))
			$retString=$retString."&baseUrl=".rawurlencode($this->baseUrl);
		if(isset($this->keywordExtractMode))
			$retString=$retString."&keywordExtractMode=".rawurlencode($this->keywordExtractMode);
		return $retString;
	}

}

/* Parameter class for functions URLGetText, HTMLGetText, URLGetRawText, HTMLGetRawText, URLGetTitle, HTMLGetTitle
//
//  See http://www.alchemyapi.com/api/text/proc.html for detailed parameter descriptions
//
*/
class AlchemyAPI_TextParams extends AlchemyAPI_Params{	  

	private $useMetaData = null;
	private $extractLinks = null;

	public function getUseMetaData(){
		return $this->useMetaData;
	}

	public function setUseMetaData($useMetaData){
		if ($useMetaData != 0 && $useMetaData != 1)
		{
			throw new Exception("Invalid setting (".$useMetaData.") for parameter useMetaData");
		}
		$this->useMetaData = $useMetaData;
	}

	public function getExtractLinks(){
		return $this->extractLinks;
	}

	public function setExtractLinks($extractLinks){
		if ($extractLinks != 0 && $extractLinks != 1)
		{
			throw new Exception("Invalid setting (".$extractLinks.") for parameter extractLinks");
		}
		$this->extractLinks = $extractLinks;
	}
	
	public function getParameterString() {
		$retString = parent::getParameterString();
		if(isset($this->useMetaData))
			$retString=$retString."&useMetaData=".rawurlencode($this->useMetaData);
		if(isset($this->extractLinks))
			$retString=$retString."&extractLinks=".rawurlencode($this->extractLinks);
		return $retString;
	}

}

/* Parameter class for functions URLGetConstraintQuery, HTMLGetConstraintQuery, TextGetConstraintQuery
//
//  See http://www.alchemyapi.com/api/scrape/proc.html for detailed parameter descriptions
//
*/
class AlchemyAPI_ConstraintQueryParams extends AlchemyAPI_Params{

	private $cQuery = null;

	public function getCQuery(){
		return $this->cQuery;
	}

	public function setCQuery($cQuery){
		$this->cQuery = $cQuery;
	}

	public function getParameterString() {
		$retString = parent::getParameterString();
		if(isset($this->cQuery))
			$retString=$retString."&cquery=".rawurlencode($this->cQuery);
		return $retString;
	}

}


/* Parameter class for functions URLGetMicroformats, HTMLGetMicroformats, TextGetMicroformats
//
//  See http://www.alchemyapi.com/api/mformat/proc.html for detailed parameter descriptions
//
*/
class AlchemyAPI_MicroformatParams extends AlchemyAPI_Params{

	public function getParameterString() {
		$retString = parent::getParameterString();
		return $retString;
	}

}
	
	





?>