;
; drush make --no-core -y  --contrib-destination=. apachesolr.make

core = 6.x
api = 2


libraries[SolrPhpClient][download][type] = "file"
libraries[SolrPhpClient][download][url] = "http://solr-php-client.googlecode.com/files/SolrPhpClient.r22.2009-11-09.tgz"
libraries[SolrPhpClient][download][sha1] = "32fa0e387c92d02fe4da4ca2ebbbeddb2d6ce0a8"
libraries[SolrPhpClient][destination] = "."

