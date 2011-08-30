<?php
// $Id: extractor_simple.inc,v 1.5 2010/09/10 19:21:08 alexb Exp $

/**
 * @file:
 * Simple term extraction.
 */

/**
 * Finds tags in text.
 */
function drupalwiki_extractor_extract($text, $lang = 'de', $minCount = 2) {
  $text = strip_tags($text);
  $text = str_replace('&nbsp;',' ',$text);
  // replace punctation
  $text = preg_replace(array('/[?]/','/[.]/','/[,]/','/:/'),' ',$text); 
  $text = drupalwiki_extractor_strip_symbols( $text );
  $text = drupalwiki_extractor_strip_numbers( $text );
  
  $text = drupal_strtolower( $text );
  mb_regex_encoding( "utf-8" );
  //$words = preg_split("/[\s,.:\-\(\)\[\]{}*\/]+/", $text);
  $words = preg_split("/[\s\t]/", $text);
  $result = array();
  // remove stopwords
  $stopWords  = drupalwiki_extractor_stop_words();
  $words = array_diff( $words, $stopWords );

 // $stemmer = _drupalwiki_extractor_pecl_stem_loaded($lang);
 // dsm($stemmer);
  foreach($words as $key => &$word) {
    $word = trim($word);
    // remove all words starting with a special character, a number or shorter then 3
    if( strlen($word) < 3 || !preg_match("/^[\w]+/", $word) || preg_match("/^[\d]+/", $word) ) {
      unset($words[$key]);
    } 
    /*if($stemmer != FALSE) {
 	$word = $stemmer($word);
    }*/
  }
  
  $keywordCounts = array_count_values( $words );
  arsort( $keywordCounts, SORT_NUMERIC );
  $result = array();
  foreach($keywordCounts as $key => $count ){
    if($minCount != NULL && $minCount > $count) {
	// skip
    }
    else {
      $result[] = array(
	'#name' => ucfirst($key),
	'#weight' => -$count
      );
   }
  }
  return $result;
}

function _drupalwiki_extractor_pecl_stem_loaded($lang) {
  // TODO: add more
  switch($lang) {
    case 'de':
      $stemmer = 'stem_german';
    break;
    default:
      $stemmer = 'stem_english';
    break;
  }

  return (extension_loaded('stem') && function_exists($stemmer)) ? $stemmer : FALSE;
}

function drupalwiki_extractor_strip_symbols( $text )
{
    $plus   = '\+\x{FE62}\x{FF0B}\x{208A}\x{207A}';
    $minus  = '\x{2012}\x{208B}\x{207B}';
 
    $units  = '\\x{00B0}\x{2103}\x{2109}\\x{23CD}';
    $units .= '\\x{32CC}-\\x{32CE}';
    $units .= '\\x{3300}-\\x{3357}';
    $units .= '\\x{3371}-\\x{33DF}';
    $units .= '\\x{33FF}';
 
    $ideo   = '\\x{2E80}-\\x{2EF3}';
    $ideo  .= '\\x{2F00}-\\x{2FD5}';
    $ideo  .= '\\x{2FF0}-\\x{2FFB}';
    $ideo  .= '\\x{3037}-\\x{303F}';
    $ideo  .= '\\x{3190}-\\x{319F}';
    $ideo  .= '\\x{31C0}-\\x{31CF}';
    $ideo  .= '\\x{32C0}-\\x{32CB}';
    $ideo  .= '\\x{3358}-\\x{3370}';
    $ideo  .= '\\x{33E0}-\\x{33FE}';
    $ideo  .= '\\x{A490}-\\x{A4C6}';
 
    return preg_replace(
        array(
        // Remove modifier and private use symbols.
            '/[\p{Sk}\p{Co}]/u',
        // Remove mathematics symbols except + - = ~ and fraction slash
            '/\p{Sm}(?<![' . $plus . $minus . '=~\x{2044}])/u',
        // Remove + - if space before, no number or currency after
            '/((?<= )|^)[' . $plus . $minus . ']+((?![\p{N}\p{Sc}])|$)/u',
        // Remove = if space before
            '/((?<= )|^)=+/u',
        // Remove + - = ~ if space after
            '/[' . $plus . $minus . '=~]+((?= )|$)/u',
        // Remove other symbols except units and ideograph parts
            '/\p{So}(?<![' . $units . $ideo . '])/u',
        // Remove consecutive white space
            '/ +/',
        ),
        ' ',
        $text );
}

/**
 * Strip numbers from text.
 */
function drupalwiki_extractor_strip_numbers( $text )
{
    $urlchars      = '\.,:;\'=+\-_\*%@&\/\\\\?!#~\[\]\(\)';
    $notdelim      = '\p{L}\p{M}\p{N}\p{Pc}\p{Pd}' . $urlchars;
    $predelim      = '((?<=[^' . $notdelim . '])|^)';
    $postdelim     = '((?=[^'  . $notdelim . '])|$)';
 
    $fullstop      = '\x{002E}\x{FE52}\x{FF0E}';
    $comma         = '\x{002C}\x{FE50}\x{FF0C}';
    $arabsep       = '\x{066B}\x{066C}';
    $numseparators = $fullstop . $comma . $arabsep;
    $plus          = '\+\x{FE62}\x{FF0B}\x{208A}\x{207A}';
    $minus         = '\x{2212}\x{208B}\x{207B}\p{Pd}';
    $slash         = '[\/\x{2044}]';
    $colon         = ':\x{FE55}\x{FF1A}\x{2236}';
    $units         = '%\x{FF05}\x{FE64}\x{2030}\x{2031}';
    $units        .= '\x{00B0}\x{2103}\x{2109}\x{23CD}';
    $units        .= '\x{32CC}-\x{32CE}';
    $units        .= '\x{3300}-\x{3357}';
    $units        .= '\x{3371}-\x{33DF}';
    $units        .= '\x{33FF}';
    $percents      = '%\x{FE64}\x{FF05}\x{2030}\x{2031}';
    $ampm          = '([aApP][mM])';
 
    $digits        = '[\p{N}' . $numseparators . ']+';
    $sign          = '[' . $plus . $minus . ']?';
    $exponent      = '([eE]' . $sign . $digits . ')?';
    $prenum        = $sign . '[\p{Sc}#]?' . $sign;
    $postnum       = '([\p{Sc}' . $units . $percents . ']|' . $ampm . ')?';
    $number        = $prenum . $digits . $exponent . $postnum;
    $fraction      = $number . '(' . $slash . $number . ')?';
    $numpair       = $fraction . '([' . $minus . $colon . $fullstop . ']' .
        $fraction . ')*';
 
    return preg_replace(
        array(
        // Match delimited numbers
            '/' . $predelim . $numpair . $postdelim . '/u',
        // Match consecutive white space
            '/ +/u',
        ),
        ' ',
        $text );
}

/**
 * Stop words.
 */
function drupalwiki_extractor_stop_words($lang = 'de') {
  $stopwords['en']  = array('a', 'about', 'above', 'above', 'across', 'after', 'afterwards', 'again', 'against', 'all', 'almost', 'alone', 'along', 'already', 'also','although','always','am','among', 'amongst', 'amoungst', 'amount',  'an', 'and', 'another', 'any','anyhow','anyone','anything','anyway', 'anywhere', 'are', 'around', 'as',  'at', 'back','be','became', 'because','become','becomes', 'becoming', 'been', 'before', 'beforehand', 'behind', 'being', 'below', 'beside', 'besides', 'between', 'beyond', 'bill', 'both', 'bottom','but', 'by', 'call', 'can', 'cannot', 'cant', 'co', 'con', 'could', 'couldnt', 'cry', 'de', 'describe', 'detail', 'do', 'done', 'down', 'due', 'during', 'each', 'eg', 'eight', 'either', 'eleven','else', 'elsewhere', 'empty', 'enough', 'etc', 'even', 'ever', 'every', 'everyone', 'everything', 'everywhere', 'except', 'few', 'fifteen', 'fify', 'fill', 'find', 'fire', 'first', 'five', 'for', 'former', 'formerly', 'forty', 'found', 'four', 'from', 'front', 'full', 'further', 'get', 'give', 'go', 'had', 'has', 'hasnt', 'have', 'he', 'hence', 'her', 'here', 'hereafter', 'hereby', 'herein', 'hereupon', 'hers', 'herself', 'him', 'himself', 'his', 'how', 'however', 'hundred', 'ie', 'if', 'in', 'inc', 'indeed', 'interest', 'into', 'is', 'it', 'its', 'itself', 'keep', 'last', 'latter', 'latterly', 'least', 'less', 'ltd', 'made', 'many', 'may', 'me', 'meanwhile', 'might', 'mill', 'mine', 'more', 'moreover', 'most', 'mostly', 'move', 'much', 'must', 'my', 'myself', 'name', 'namely', 'neither', 'never', 'nevertheless', 'next', 'nine', 'no', 'nobody', 'none', 'noone', 'nor', 'not', 'nothing', 'now', 'nowhere', 'of', 'off', 'often', 'on', 'once', 'one', 'only', 'onto', 'or', 'other', 'others', 'otherwise', 'our', 'ours', 'ourselves', 'out', 'over', 'own','part', 'per', 'perhaps', 'please', 'put', 'rather', 're', 'same', 'see', 'seem', 'seemed', 'seeming', 'seems', 'serious', 'several', 'she', 'should', 'show', 'side', 'since', 'sincere', 'six', 'sixty', 'so', 'some', 'somehow', 'someone', 'something', 'sometime', 'sometimes', 'somewhere', 'still', 'such', 'system', 'take', 'ten', 'than', 'that', 'the', 'their', 'them', 'themselves', 'then', 'thence', 'there', 'thereafter', 'thereby', 'therefore', 'therein', 'thereupon', 'these', 'they', 'thickv', 'thin', 'third', 'this', 'those', 'though', 'three', 'through', 'throughout', 'thru', 'thus', 'to', 'together', 'too', 'top', 'toward', 'towards', 'twelve', 'twenty', 'two', 'un', 'under', 'until', 'up', 'upon', 'us', 'very', 'via', 'was', 'we', 'well', 'were', 'what', 'whatever', 'when', 'whence', 'whenever', 'where', 'whereafter', 'whereas', 'whereby', 'wherein', 'whereupon', 'wherever', 'whether', 'which', 'while', 'whither', 'who', 'whoever', 'whole', 'whom', 'whose', 'why', 'will', 'with', 'within', 'without', 'would', 'yet', 'you', 'your', 'yours', 'yourself', 'yourselves', 'the');

  $stopwords['de'] = array('ab','bei','da','deshalb','ein','für','haben','hier','ich','ja','kann','machen','muesste','nach','oder','seid','sonst','und','vom','wann','wenn','wie','zu','bin','eines','hat','manche','solches','an','anderm','bis','das','deinem','demselben','dir','doch','einig','er','eurer','hatte','ihnen','ihre','ins','jenen','keinen','manchem','meinen','nichts','seine','soll','unserm','welche','werden','wollte','während','alle','allem','allen','aller','alles','als','also','am','ander','andere','anderem','anderen','anderer','anderes','andern','anderr','anders','auch','auf','aus','bist','bsp.','daher','damit','dann','dasselbe','dazu','daß','dein','deine','deinen','deiner','deines','dem','den','denn','denselben','der','derer','derselbe','derselben','des','desselben','dessen','dich','die','dies','diese','dieselbe','dieselben','diesem','diesen','dieser','dieses','dort','du','durch','eine','einem','einen','einer','einige','einigem','einigen','einiger','einiges','einmal','es','etwas','euch','euer','eure','eurem','euren','eures','ganz','ganze','ganzen','ganzer','ganzes','gegen','gemacht','gesagt','gesehen','gewesen','gewollt','hab','habe','hatten','hin','hinter','ihm','ihn','ihr','ihrem','ihren','ihrer','ihres','im','in','indem','ist','jede','jedem','jeden','jeder','jedes','jene','jenem','jener','jenes','jetzt','kein','keine','keinem','keiner','keines','konnte','können','könnte','mache','machst','macht','machte','machten','man','manchen','mancher','manches','mein','meine','meinem','meiner','meines','mich','mir','mit','muss','musste','müßt','nicht','noch','nun','nur','ob','ohne','sage','sagen','sagt','sagte','sagten','sagtest','sehe','sehen','sehr','seht','sein','seinem','seinen','seiner','seines','selbst','sich','sicher','sie','sind','so','solche','solchem','solchen','solcher','sollte','sondern','um','uns','unse','unsen','unser','unses','unter','viel','von','vor','war','waren','warst','was','weg','weil','weiter','welchem','welchen','welcher','welches','werde','wieder','will','wir','wird','wirst','wo','wolle','wollen','wollt','wollten','wolltest','wolltet','würde','würden','z.B.','zum','zur','zwar','zwischen','über','aber','abgerufen','abgerufene','abgerufener','abgerufenes','acht','acute','allein','allerdings','allerlei','allg','allgemein','allmählich','allzu','alsbald','amp','and','andererseits','andernfalls','anerkannt','anerkannte','anerkannter','anerkanntes','anfangen','anfing','angefangen','angesetze','angesetzt','angesetzten','angesetzter','ansetzen','anstatt','arbeiten','aufgehört','aufgrund','aufhören','aufhörte','aufzusuchen','ausdrücken','ausdrückt','ausdrückte','ausgenommen','ausser','ausserdem','author','autor','außen','außer','außerdem','außerhalb','background','bald','bearbeite','bearbeiten','bearbeitete','bearbeiteten','bedarf','bedurfte','bedürfen','been','befragen','befragte','befragten','befragter','begann','beginnen','begonnen','behalten','behielt','beide','beiden','beiderlei','beides','beim','beinahe','beitragen','beitrugen','bekannt','bekannte','bekannter','bekennen','benutzt','bereits','berichten','berichtet','berichtete','berichteten','besonders','besser','bestehen','besteht','beträchtlich','bevor','bezüglich','bietet','bisher','bislang','biz','bleiben','blieb','bloss','bloß','border','brachte','brachten','brauchen','braucht','bringen','bräuchte','bzw','böden','ca','ca.','collapsed','com','comment','content','da?','dabei','dadurch','dafür','dagegen','dahin','damals','danach','daneben','dank','danke','danken','dannen','daran','darauf','daraus','darf','darfst','darin','darum','darunter','darüber','darüberhinaus','dass','davon','davor','demnach','denen','dennoch','derart','derartig','derem','deren','derjenige','derjenigen','derzeit','desto','deswegen','diejenige','diesseits','dinge','direkt','direkte','direkten','direkter','doc','doppelt','dorther','dorthin','drauf','drei','dreißig','drin','dritte','drunter','drüber','dunklen','durchaus','durfte','durften','dürfen','dürfte','eben','ebenfalls','ebenso','ehe','eher','eigenen','eigenes','eigentlich','einbaün','einerseits','einfach','einführen','einführte','einführten','eingesetzt','einigermaßen','eins','einseitig','einseitige','einseitigen','einseitiger','einst','einstmals','einzig','elf','ende','entsprechend','entweder','ergänze','ergänzen','ergänzte','ergänzten','erhalten','erhielt','erhielten','erhält','erneut','erst','erste','ersten','erster','eröffne','eröffnen','eröffnet','eröffnete','eröffnetes','etc','etliche','etwa','fall','falls','fand','fast','ferner','finden','findest','findet','folgende','folgenden','folgender','folgendes','folglich','for','fordern','fordert','forderte','forderten','fortsetzen','fortsetzt','fortsetzte','fortsetzten','fragte','frau','frei','freie','freier','freies','fuer','fünf','gab','ganzem','gar','gbr','geb','geben','geblieben','gebracht','gedurft','geehrt','geehrte','geehrten','geehrter','gefallen','gefiel','gefälligst','gefällt','gegeben','gehabt','gehen','geht','gekommen','gekonnt','gemocht','gemäss','genommen','genug','gern','gestern','gestrige','getan','geteilt','geteilte','getragen','gewissermaßen','geworden','ggf','gib','gibt','gleich','gleichwohl','gleichzeitig','glücklicherweise','gmbh','gratulieren','gratuliert','gratulierte','gute','guten','gängig','gängige','gängigen','gängiger','gängiges','gänzlich','haette','halb','hallo','hast','hattest','hattet','heraus','herein','heute','heutige','hiermit','hiesige','hinein','hinten','hinterher','hoch','html','http','hundert','hätt','hätte','hätten','höchstens','igitt','image','immer','immerhin','important','indessen','info','infolge','innen','innerhalb','insofern','inzwischen','irgend','irgendeine','irgendwas','irgendwen','irgendwer','irgendwie','irgendwo','je','jed','jedenfalls','jederlei','jedoch','jemand','jenseits','jährig','jährige','jährigen','jähriges','kam','kannst','kaum','kei nes','keinerlei','keineswegs','klar','klare','klaren','klares','klein','kleinen','kleiner','kleines','koennen','koennt','koennte','koennten','komme','kommen','kommt','konkret','konkrete','konkreten','konkreter','konkretes','konnten','könn','könnt','könnten','künftig','lag','lagen','langsam','lassen','laut','lediglich','leer','legen','legte','legten','leicht','leider','lesen','letze','letzten','letztendlich','letztens','letztes','letztlich','lichten','liegt','liest','links','längst','längstens','mag','magst','mal','mancherorts','manchmal','mann','margin','med','mehr','mehrere','meist','meiste','meisten','meta','mindestens','mithin','mochte','morgen','morgige','muessen','muesst','musst','mussten','muß','mußt','möchte','möchten','möchtest','mögen','möglich','mögliche','möglichen','möglicher','möglicherweise','müssen','müsste','müssten','müßte','nachdem','nacher','nachhinein','nahm','natürlich','ncht','neben','nebenan','nehmen','nein','neu','neue','neuem','neuen','neuer','neues','neun','nie','niemals','niemand','nimm','nimmer','nimmt','nirgends','nirgendwo','nter','nutzen','nutzt','nutzung','nächste','nämlich','nötigenfalls','nützt','oben','oberhalb','obgleich','obschon','obwohl','oft','online','org','padding','per','pfui','plötzlich','pro','reagiere','reagieren','reagiert','reagierte','rechts','regelmäßig','rief','rund','sang','sangen','schlechter','schließlich','schnell','schon','schreibe','schreiben','schreibens','schreiber','schwierig','schätzen','schätzt','schätzte','schätzten','sechs','sect','sehrwohl','sei','seit','seitdem','seite','seiten','seither','selber','senke','senken','senkt','senkte','senkten','setzen','setzt','setzte','setzten','sicherlich','sieben','siebte','siehe','sieht','singen','singt','sobald','sodaß','soeben','sofern','sofort','sog','sogar','solange','solc hen','solch','sollen','sollst','sollt','sollten','solltest','somit','sonstwo','sooft','soviel','soweit','sowie','sowohl','spielen','später','startet','startete','starteten','statt','stattdessen','steht','steige','steigen','steigt','stets','stieg','stiegen','such','suchen','sämtliche','tages','tat','tatsächlich','tatsächlichen','tatsächlicher','tatsächliches','tausend','teile','teilen','teilte','teilten','titel','total','trage','tragen','trotzdem','trug','trägt','tun','tust','tut','txt','tät','ueber','umso','unbedingt','ungefähr','unmöglich','unmögliche','unmöglichen','unmöglicher','unnötig','unsem','unser','unsere','unserem','unseren','unserer','unseres','unten','unterbrach','unterbrechen','unterhalb','unwichtig','usw','var','vergangen','vergangene','vergangener','vergangenes','vermag','vermutlich','vermögen','verrate','verraten','verriet','verrieten','version','versorge','versorgen','versorgt','versorgte','versorgten','versorgtes','veröffentlichen','veröffentlicher','veröffentlicht','veröffentlichte','veröffentlichten','veröffentlichtes','viele','vielen','vieler','vieles','vielleicht','vielmals','vier','vollständig','voran','vorbei','vorgestern','vorher','vorne','vorüber','völlig','während','wachen','waere','warum','weder','wegen','weitere','weiterem','weiteren','weiterer','weiteres','weiterhin','weiß','wem','wen','wenig','wenige','weniger','wenigstens','wenngleich','wer','werdet','weshalb','wessen','wichtig','wieso','wieviel','wiewohl','willst','wirklich','wodurch','wogegen','woher','wohin','wohingegen','wohl','wohlweislich','womit','woraufhin','woraus','worin','wurde','wurden','währenddessen','wär','wäre','wären','zahlreich','zehn','zeitweise','ziehen','zieht','zog','zogen','zudem','zuerst','zufolge','zugleich','zuletzt','zumal','zurück','zusammen','zuviel','zwanzig','zwei','zwölf','ähnlich','übel','überall','überallhin','überdies','übermorgen','übrig','übrigens');

  return $stopwords[$lang];
}
