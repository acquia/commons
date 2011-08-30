<?php
// $Id: textactions.inc,v 1.1.2.16 2009/09/04 23:28:04 dman Exp $
/**
 * @file Helper functions for imagecache_textactions
 * 
 * Static text2canvas and dynamic caption functions
 * 
 * Ported by dman
 * from http://drupal.org/node/264862#comment-865490 by patrickharris
 * 
 * The bottom-20 positioning that dynamic text uses is good, and should be
 * worked back into other dimension calculations.
 * 
 * Contains a stub for imageapi functions : imageapi_image_overlaytext_alpha
 * that may be ported over to there if that makes sense.
 */

/**
 * Place text on top of the current canvas
 *
 * Implementation of imagecache_hook_form()
 *
 * @param $action array of settings for this action
 * @return a form definition
 */
function textactions_text2canvas_form($action) {
  $defaults = array(
    'size' => 12,
    'angle' => 0,
    'xpos' => 'left+10',
    'ypos' => 'bottom-10',
    'RGB' => array(
      'red' => 51,
      'green' => 51,
      'blue' => 51,
      'HEX' => '#333333',
    ),
    'alpha' => 100,
    'fontfile' => 'liberation-fonts-1.04/LiberationSans-Regular.ttf',
    'text' => 'Hello World!',
    'evaluate_text' => FALSE,
  );
  $action = array_merge($defaults, (array)$action);
  $form = array(
    'size' => array(
      '#type' => 'textfield',
      '#title' => t('Size'),
      '#default_value' => $action['size'],
      '#description' => t('Size: The font size. Depending on your version of GD, this should be specified as the pixel size (GD1) or point size (GD2).'),
      '#size' => 3,
    ),
    'angle' => array(
      '#type' => 'textfield',
      '#title' => t('Angle'),
      '#default_value' => $action['angle'],
      '#description' => t('Angle: The angle in degrees, with 0 degrees being left-to-right reading text. Higher values represent a counter-clockwise rotation. For example, a value of 90 would result in bottom-to-top reading text.'),
      '#size' => 3,
    ),
    'alpha' => array(
      '#type' => 'textfield',
      '#title' => t('Opacity'),
      '#default_value' => $action['alpha'],
      '#size' => 3,
      '#description' => t('Opacity: 1-100.'),
      '#element_validate' => array('imagecache_actions_validate_alpha'),
    ),
    'xpos' => array(
      '#type' => 'textfield',
      '#title' => t('X offset'),
      '#default_value' => $action['xpos'],
      '#description' => t('Enter an offset in pixels or use a keyword: <em>left</em>, <em>center</em>, or <em>right</em>. Syntax like <em>right-20</em> is also valid.'),
      '#size' => 10,
    ),
    'ypos' => array(
      '#type' => 'textfield',
      '#title' => t('Y offset'),
      '#default_value' => $action['ypos'],
      '#description' => t('Enter an offset in pixels or use a keyword: <em>top</em>, <em>center</em>, or <em>bottom</em>. Syntax like <em>bottom-20</em> is also valid.'),
      '#size' => 10,
    ),
    'RGB' => imagecache_rgb_form($action['RGB']),
    'fontfile' => array(
      '#type' => 'textfield',
      '#title' => t('Font file name'),
      '#default_value' => $action['fontfile'],
      '#description' => t('Font file is either the full system path (eg <code>/usr/share/fonts/truetype/ttf-bitstream-vera/VeraMono.ttf</code>), a font file inside the in the module dir "%moduledir" or the files "%filedir" folder). Example: "arial.ttf". You <em>might</em> find a list of fonts available at !helplink if your system supports it.', array('%moduledir' => drupal_get_path('module', 'imagecache_textactions'), '%filedir' => file_directory_path(), '!helplink' => l('fonts help', 'admin/help/imagecache_textactions') )),
      '#element_validate' => array('textactions_text2canvas_validate_fontfile'),
    ),
    'text' => array(
      '#type' => 'textarea',
      '#rows' => 7,
      '#title' => t('Text'),
      '#default_value' => $action['text'],
      '#description' => t('The text string. If you are using a WYSIWYG editor, you should disable it for this field!'),
      '#wysiwyg' => FALSE,
    ),
    'evaluate_text' => array(
      '#type' => 'checkbox',
      '#title' => t('Evaluate text as PHP code'),
      '#default_value' => $action['evaluate_text'],
      '#description' => t('If selected, the text will be treated as PHP code.
      <p>
        Enter PHP code that will <b>return</b> your dynamic text. Do not use %php tags. 
        <br />EG <code>return format_date(time());</code>  
        <br /><code>return $file_data->description ? $file_data->description : $node->title;</code>
      </p>
      <p>Note that executing incorrect PHP-code can break your Drupal site.</p>
      <p>
        <b>If it\'s an image.module image</b> then a <b>$node</b> object with its values 
        <em>may</em> be available.
        <br/><code>return $node->title;</code>
        <br/><code>return format_date($node->created);</code>
      </p>

      <p>
        If it\'s an image that has been attached to a node using <b>CCK-filefield-imagefield</b>
        (or just filefield)
        then as well as the parent <b>$node</b> object,
        a <b>$file_data</b> object that may contain a file description from that file field.
        <br/><code>return $file_data->description;</code>
        <small>So far that seems to be the only available \'data\' provided by filefield, 
        but you can investigate the node structure using devel.module or print_r() 
        to see what else this array actually contains</small>.
      </p>
      <p>
        If it\'s a file that\'s just been <b>attached using upload.module</b>,
        a <b>$file_data</b> object may also have a description.
        <br/><code>return $file_data->description;</code>
      </p>
      <p>
        If the image path is detected as belonging to more than one node, just the
        data for the first one found is returned. 
      </p>

      <p>
        An "<b>$image</b>" object is also available, but that usually contains only technical data, including 
        <br/><code>return $image->source;</code>
        <br/><code>return basename($image->source);</code>
        <br/><code>return $image->info["filesize"];</code>
      </p>
      ', 
      array('%php' => '<?php ?>'))
    ),
  );
  if (! user_access('administer site configuration')) {
    $form['evaluate_text']['#disabled'] = TRUE;
    $form['text']['#disabled'] = $action['evaluate_text']; // lock this if an admin has enabled evaluation.
    $form['evaluate_text']['#description'] = 'requires <b>administer site configuration</b> permissions.';
  }
  return $form;
}

/**
 * Check if the named font is available
 */
function textactions_text2canvas_validate_fontfile(&$element, &$form_status) {
  if (! $fontfile = textactions_find_font($element['#value'], TRUE)) {
    // Just warn, don't prevent
    drupal_set_message(t("
      Unable to confirm that the font '%fontfile' is available on your system. 
      This may fail, or your system may provide an appropriate fallback, 
      depending on your toolkit behaviour. 
      Ensure the path to the ttf file is correct, 
      and permissions allow the webserver to read the file and directory.", 
      array('%fontfile' => $element['#value'])), 'warning' );
  }
  else {
    drupal_set_message(t("Font was found OK at %fontfile", array('%fontfile' => $fontfile)), 'notice');
  }
}


/**
 * Implementation of theme_hook() for imagecache_ui.module
 */
function theme_textactions_text2canvas($element) {
  $data = $element['#value'];
  return "<em><strong>". $data['text'] ."</strong></em>" 
  . t("<br/>%sizepx #%color %alpha% %angle&deg; (%xpos, %ypos)", 
    array(
      '%size' => $data['size'],
      '%color' => strtoupper($data['RGB']['HEX']),
      '%alpha' => $data['alpha'],
      '%angle' => $data['angle'],
      '%xpos' => $data['xpos'],
      '%ypos' => $data['ypos'],
    )
  ) ;
}

/**
 * Place the source image on the current background
 *
 * Implementation of hook_image()
 *
 * @param $image
 * @param $action
 */
function textactions_text2canvas_image(&$image, $action = array()) {
  $fontpath = textactions_find_font($action['fontfile']);
  if (! $fontpath) {
    drupal_set_message(t("Failed to locate the requested font %fontfile. Cannot overlay text onto image.", array('%fontfile' => $action['fontfile'])));
    return FALSE;
  }

  if ($action['evaluate_text']) {
    $text = textactions_evaluate_text($image, $action);
  }
  else {
    $text = $action['text'];
  }
  $text = strip_tags($text);

  // Calculate position by first creating a temp image containing the text and accessing its dimensions
  $temp = textactions_create_font_image($action['size'], $action['angle'], $fontpath, $text );

  if (! $temp) {
    drupal_set_message(t('Failed to generate text image. Cannot calculate text dimensions. Not overlaying text.'), 'error');
    return;
  }

  // parse keywords
  $x_ins = textactions_keyword_filter($action['xpos'], $image->info['width'], $temp['width'], $temp['bx'], 'x');
  $y_ins = textactions_keyword_filter($action['ypos'], $image->info['height'], $temp['height'], $temp['by'], 'y');

  // convert color from hex (as it is stored in the UI)
  if ($action['RGB']['HEX'] && $deduced = hex_to_rgb($action['RGB']['HEX'])) {
    $action['RGB'] = array_merge($action['RGB'], $deduced);
  }

  $action['alpha'] = ($action['alpha'] / 100); //Convert to decimal between 0 and 1
  $action['RGB']['alpha'] = ((1 - $action['alpha']) * 127); //convert opacity to proper alpha value (0 = opaque, 127 = transparent)

  return imageapi_image_overlaytext_alpha($image, $text, $action['size'], $x_ins, $y_ins, $action['RGB'], $fontpath, $action['angle']);
}

/**
 * Generate the dynamic text for this image.
 * Was textactions caption - now merged as an option of text2canvas
 * 
 * TODO further code review for safety etc
 * 
 * @param $image object, as provided by imageapi
 * @param $action definition
 * 
 * @return $text Plain or code string to be placed on the imagecache process.
 */
function MOVED_textactions_evaluate_text($image, $action) {

  // HOOK_metadata from file attempts to glean info from any direction possible - EXIF, XMP, DB, description.txt
  // @see the meta_* project
  $meta = module_invoke_all('metadata_from_file', $image->source);
  $file_data = (object) $meta;

  // Try to load the attached node - if any
  static $panic; #This can trigger recursion! build-load-build-etc
  if ($panic) return;
  $panic = TRUE;
  $node = imagecache_actions_node_from_filepath($image->source, $file_data) ;
  $panic = FALSE;

  // Process the php using drupal_eval (rather than eval), 
  // but with GLOBAL variables, so they can be passed successfully
  $GLOBALS['image'] = $image;
  $GLOBALS['node'] = $node;
  $GLOBALS['file_data'] = $file_data;
  
  $text = @drupal_eval('<'.'?php global $node; global $image; global $file_data; '. $action['text'] .' ?'.'>');

  // Warn about errors in the php code if I can
  if (empty($text) && function_exists('error_get_last') && $last_error = error_get_last()) {
    drupal_set_message("Problem evaluating dynamic text. <br/><code>{$action['text']}</code><br/> ". $last_error['message'], 'error');
  }

  return $text;
}


/**
 * Creates an image containing only the text - used to calculate the true
 * bounding box.
 */
function textactions_create_font_image( $size, $angle, $font, $char ) {
    $rect = imagettfbbox( $size, 0, $font, $char );
    if (!$rect) {
      return NULL;
    }
    if ( 0 == $angle ) {
        $imh = $rect[1] - $rect[7];
        $imw = $rect[2] - $rect[0];
        $bx = -1 - $rect[0];
        $by = -1 - $rect[7];
    } 
    else {
        $rad = deg2rad( $angle );
        $sin = sin( $rad );
        $cos = cos( $rad );
        if ( $angle > 0 ) {
            $tmp = $rect[6] * $cos + $rect[7] * $sin;
            $bx = -1 - round( $tmp );
            $imw = round( $rect[2] * $cos + $rect[3] * $sin - $tmp );
            $tmp = $rect[5] * $cos - $rect[4] * $sin;
            $by = -1 - round( $tmp );
            $imh = round( $rect[1] * $cos - $rect[0] * $sin - $tmp );
        } 
        else {
            $tmp = $rect[0] * $cos + $rect[1] * $sin;
            $bx = -1 - round( $tmp );
            $imw = round( $rect[4] * $cos + $rect[5] * $sin - $tmp );
            $tmp = $rect[7] * $cos - $rect[6] * $sin;
            $by = -1 - round( $tmp );
            $imh = round( $rect[3] * $cos - $rect[2] * $sin - $tmp );
        }
    }
  
  return array('width' => $imw, 'height' => $imh, 'bx' => $bx, 'by' => $by);
}

/**
 * Accept a keyword (center, top, left, etc) and return it as an offset in pixels.
 * Called on either the x or y values.
 * 
 * @param $value 
 *   string or int value. May be something like "20", "center", "left+20"
 * @param $current_size
 *   int size in pixels of the range this item is to be placed in
 * @param $object_size
 *   int size in pixels of the object to be placed
 * 
 * @param $xy
 *   Whether the axis is on the x or the y (unused)
 * 
 */
function textactions_keyword_filter($value, $current_pixels, $new_pixels, $adj, $xy) {
  // check if we have plus or minus values
  $v = explode('+', $value);
  $v2 = explode('-', $value);
  if (!empty($v2[1])) {
    $v[1]=-intval($v2[1]); 
    $v[0]=$v2[0];
  }

  switch ($v[0]) {
    case 'top':
    case 'left':
      $value = 0;
      break;
    case 'bottom':
    case 'right':
      $value = $current_pixels - $new_pixels;
      break;
    case 'center':
      $value = $current_pixels/2 - $new_pixels/2;
      break;
  }
  
  // Perform the adjustment.
  $value=$value+$adj;
  // Add any extra negative or positive.
  if (!empty($v[1])) $value = $value + $v[1];
  return $value;
}



/**
 * Place text on an image.
 *
 * @ingroup imageapi
 */
function imageapi_image_overlaytext_alpha(&$image, $text, $size = 12, $x = 0, $y = 0, $RGB = 0, $fontfile = 'MgOpenModernaBold', $angle = 0) {
  return imageapi_toolkit_invoke('overlaytext_alpha', $image, array($text, $size, $x, $y, $RGB, $fontfile, $angle));
}

/**
 * Place text on an image.
 *
 * @ingroup imageapi
 */
function imageapi_gd_image_overlaytext_alpha(&$image, $text, $size = 12, $x = 0, $y = 0, $RGB, $fontfile = 'MgOpenModernaBold', $angle = 0) {
  $color = imagecolorallocatealpha($image->resource, $RGB['red'], $RGB['green'], $RGB['blue'], $RGB['alpha']);

  // Merging images where one or the other is partially transparent needs to be supported or we get black blocks.
  //  EG text over PNG
  // This flag will be lost again in jpegs, but that's after we've merged, so it's OK.
  imagesavealpha($image->resource, TRUE);
  imagealphablending($image->resource, TRUE);

  $bounds = imagettftext($image->resource, $size, $angle, $x, $y, $color, $fontfile, $text);
  if (empty($bounds)) return FALSE;
  return TRUE;
}


/** 
 * UTILITY
 */

/**
 * Given a font name or path, return the full real path.
 * Because the toolkit doesn't scan too well, we need to look ahead to avoid
 * problems and validate.
 *
 * Look for the named font file relative to Drupal, the module, and the files
 * dir.
 *
 * @param $fontpath a font file name, eg 'arial.ttf'
 * @param $strict bool. if set, the func will return nothing on failure. Normal
 * behaviour is to return the input fontfile name, trusting the system to be
 * able to find it for you. Strict is used to trigger a validation alert.
 *
 * @return the FULL filepath of the font so the image toolkit knows exactly
 * where it is.
 */
function textactions_find_font($fontpath, $strict = FALSE) {
  // Track down the font.
  if (is_file($fontpath)) {
    return realpath($fontpath);
  }

  $fontpath = ltrim($fontpath, '/');
  // Try local
  $tryfontpath = drupal_get_path('module', 'imagecache_textactions') .'/fonts/'. $fontpath;
  if (is_file($tryfontpath)) {
    return realpath($tryfontpath);
  }

  // Try in the files directory
  $tryfontpath =  file_create_path($fontpath);
  if (is_file($tryfontpath)) {
    return realpath($tryfontpath);
  }

  if ($strict) return FALSE;
  // otherwise, just return what we had and hope it's in a system library
  return $fontpath;
}
