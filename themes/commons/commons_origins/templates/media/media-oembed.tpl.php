<?php

/**
 * @file
 * Template file for theme('media_oembed').
 *
 * General
 *
 * $uri - The media uri for the oEmbed resource (e.g., oembed://http://resource.com/id).
 * $options - An array containing the Media: oEmbed formatter options.
 * $filename - The Media: oEmbed file's file name.
 * $content - The content of the oEmbed resource transformed into HTML appropriate for display.
 *
 * Response parameters
 *
 * Responses can specify a resource type, such as photo or video. Each type has
 * specific parameters associated with it. The following response parameters are
 * valid for all response types:
 *
 * $type (required) - The resource type. Valid values, along with value-specific parameters, are described below.
 * $version (required) - The oEmbed version number. This must be 1.0.
 * $title (optional) - A text title, describing the resource.
 * $author_name (optional) - The name of the author/owner of the resource.
 * $author_url (optional) - A URL for the author/owner of the resource.
 * $provider_name (optional) - The name of the resource provider.
 * $provider_url (optional) - The url of the resource provider.
 * $cache_age (optional) - The suggested cache lifetime for this resource, in seconds. Consumers may choose to use this value or not.
 * $thumbnail_url (optional) - A URL to a thumbnail image representing the resource. If this parameter is present, thumbnail_width and thumbnail_height must also be present.
 * $thumbnail_width (optional) - The width of the optional thumbnail. If this parameter is present, thumbnail_url and thumbnail_height must also be present.
 * $thumbnail_height (optional) - The height of the optional thumbnail. If this parameter is present, thumbnail_url and thumbnail_width must also be present.
 *
 * The photo type
 *
 * $url (required) - The source URL of the image. Consumers should be able to insert this URL into an <img> element. Only HTTP and HTTPS URLs are valid.
 * $width (required) - The width in pixels of the image specified in the url parameter.
 * $height (required) - The height in pixels of the image specified in the url parameter.
 *
 * The video type
 *
 * $html (required) - The HTML required to embed a video player. The HTML should have no padding or margins. Consumers may wish to load the HTML in an off-domain iframe to avoid XSS vulnerabilities.
 * $width (required) - The width in pixels required to display the HTML.
 * $height (required) - The height in pixels required to display the HTML.
 *
 * The link type
 *
 * Responses of this type allow a provider to return any generic embed data
 * (such as title and author_name), without providing either the url or html
 * parameters. The consumer may then link to the resource, using the URL
 * specified in the original request.
 *
 * The rich type
 *
 * $html (required) - The HTML required to display the resource. The HTML should have no padding or margins. Consumers may wish to load the HTML in an off-domain iframe to avoid XSS vulnerabilities. The markup should be valid XHTML 1.0 Basic.
 * $width (required) - The width in pixels required to display the HTML.
 * $height (required) - The height in pixels required to display the HTML.
 */

?>

<div class="oembed oembed-<?php print $type; ?>">
  <?php print $content; ?>
</div>
