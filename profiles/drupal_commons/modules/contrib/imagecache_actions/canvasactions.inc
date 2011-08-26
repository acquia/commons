<?php
// $Id: canvasactions.inc,v 1.1.4.21 2009/12/28 03:26:53 dman Exp $
/**
 * @file Helper functions for the text2canvas action for imagecache
 * 
 * @author Dan Morrison http://coders.co.nz
 * 
 * Individually configurable rounded corners logic contributed by canaryMason
 * 2009 03 http://drupal.org/node/402112
 *
 * Better algorithm for trimming rounded corners from donquixote 
 * 2009 09 http://drupal.org/node/564036
 *
 */

/**
 * Implementation of imagecache_hook_form()
 *
 * Settings for preparing a canvas.
 *
 * @param $action array of settings for this action
 * @return a form definition
 */
function canvasactions_definecanvas_form($action) {
  if (imageapi_default_toolkit() != 'imageapi_gd') {
    drupal_set_message('Define Canvas not currently supported by using imagemagick. This effect requires GD image toolkit only.', 'warning');
  }
  $defaults = array(
    'RGB' => array(
      'HEX' => '#333333',
    ),
    'under' => TRUE,
    'exact' => array( 
      'width' => '',
      'height' => '',
      'xpos' => 'center',
      'ypos' => 'center',
    ),
    'relative' => array(
      'leftdiff' => '',
      'rightdiff' => '',
      'topdiff' => '',
      'bottomdiff' => '',
    ),
  );
  $action = array_merge($defaults, (array)$action);

  $form = array(
    'RGB' => imagecache_rgb_form($action['RGB']),
    'help' => array(
      '#type' => 'markup',
      '#value' => t('Enter no color value for transparent. This will have the effect of adding clear margins around the image.'),
      '#prefix' => '<p>', '#suffix' => '</p>',
    ),
    'under' => array(
      '#type' => 'checkbox',
      '#title' => t('Resize canvas <em>under</em> image (possibly cropping)'),
      '#default_value' => $action['under'],
      '#description' => t('If <em>not</em> set, this will create a solid flat layer, probably totally obscuring the source image'),
    ),
  );
  $form['info'] = array('#value' => t('Enter values in ONLY ONE of the below options. Either exact or relative. Most values are optional - you can adjust only one dimension as needed. If no useful values are set, the current base image size will be used.'));
  $form['exact'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#title' => 'Exact size',
      'help' => array(
        '#type' => 'markup',
        '#value' => t('Set the canvas to a precise size, possibly cropping the image. Use to start with a known size.'),
        '#prefix' => '<p>', '#suffix' => '</p>',
      ),
      
      'width' => array(
        '#type' => 'textfield',
        '#title' => t('Width'),
        '#default_value' => $action['exact']['width'],
        '#description' => t('Enter a value in pixels or percent'),
        '#size' => 5,
      ),
      'height' => array(
        '#type' => 'textfield',
        '#title' => t('Height'),
        '#default_value' => $action['exact']['height'],
        '#description' => t('Enter a value in pixels or percent'),
        '#size' => 5,
      ),
    );
  $form['exact'] = array_merge($form['exact'], imagecacheactions_pos_form($action['exact']));
  if (! $action['exact']['width'] && !$action['exact']['height']) {
    $form['exact']['#collapsed'] = TRUE;
  }

  $form['relative'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#title' => t('Relative size'),
      'help' => array(
        '#type' => 'markup',
        '#value' => '<p>'. t('Set the canvas to a relative size, based on the current image dimensions. Use to add simple borders or expand by a fixed amount. Negative values may crop the image.') .'</p>',
      ),
      'leftdiff' => array(
        '#type' => 'textfield',
        '#title' => t('left difference'),
        '#default_value' => $action['relative']['leftdiff'],
        '#size' => 6,
        '#description' => t('Enter an offset in pixels.'),
      ),
      'rightdiff' => array(
        '#type' => 'textfield',
        '#title' => t('right difference'),
        '#default_value' => $action['relative']['rightdiff'],
        '#size' => 6,
        '#description' => t('Enter an offset in pixels.'),
      ),
      'topdiff' => array(
        '#type' => 'textfield',
        '#title' => t('top difference'),
        '#default_value' => $action['relative']['topdiff'] ,
        '#size' => 6,
        '#description' => t('Enter an offset in pixels.'),
      ),
      'bottomdiff' => array(
        '#type' => 'textfield',
        '#title' => t('bottom difference'),
        '#default_value' => $action['relative']['bottomdiff'],
        '#size' => 6,
        '#description' => t('Enter an offset in pixels.'),
      ),
    );
  if (! $action['relative']['leftdiff'] && !$action['relative']['rightdiff'] && !$action['relative']['topdiff'] && !$action['relative']['bottomdiff']) {
    $form['relative']['#collapsed'] = TRUE;
  }

  $form['#submit'][] = 'canvasactions_definecanvas_form_submit';
  return $form;
}

/**
 * Implementation of theme_hook() for imagecache_ui.module
 */
function theme_canvasactions_definecanvas($element) {
  $action = $element['#value'];
  if ($action['exact']['width'] || $action['exact']['width']) {
    $output = $action['exact']['width'] .'x'. $action['exact']['height'];
    $output .= " (". $action['exact']['xpos'] .', '. $action['exact']['ypos'] .") ";
  }
  else {
    $output = ' left:'. $action['relative']['leftdiff'];
    $output .= ' right:'. $action['relative']['rightdiff'];
    $output .= ' top:'. $action['relative']['topdiff'];
    $output .= ' bottom:'. $action['relative']['bottomdiff'];
  }
  $output .= theme_imagecacheactions_rgb($action['RGB']);
  $output .= ($action['under']) ? t(" <b>under</b> image ") : t(" <b>over</b> image ");
  return $output ;
}

/**
 * Implementation of hook_image()
 *
 * Creates a solid background canvas
 *
 * Process the imagecache action on the passed image
 *
 * @param $image
 * array defining an image file, including  :
 *
 *   $image- >source as the filename,
 *
 *   $image->info array
 *
 *   $image->resource handle on the image object
 */
function canvasactions_definecanvas_image(&$image, $action = array()) {
 
  // May be given either exact or relative dimensions.
  if ($action['exact']['width'] || $action['exact']['width']) {
  // Allows only one dimension to be used if the other is unset.
    if (! $action['exact']['width']) $action['exact']['width'] = $image->info['width'];
    if (! $action['exact']['height']) $action['exact']['height'] = $image->info['height'];

    $targetsize['width'] = _imagecache_percent_filter($action['exact']['width'], $image->info['width']);
    $targetsize['height'] = _imagecache_percent_filter($action['exact']['height'], $image->info['height']);

    $targetsize['left'] = _imagecache_keyword_filter($action['exact']['xpos'], $targetsize['width'], $image->info['width']);
    $targetsize['top'] = _imagecache_keyword_filter($action['exact']['ypos'], $targetsize['height'], $image->info['height']);

  }
  else {
    // calculate relative size
    $targetsize['width'] = $image->info['width'] + $action['relative']['leftdiff'] +  $action['relative']['rightdiff'];
    $targetsize['height'] = $image->info['height'] + $action['relative']['topdiff'] +  $action['relative']['bottomdiff'];
    $targetsize['left'] = $action['relative']['leftdiff'];
    $targetsize['top'] = $action['relative']['topdiff'];
  }

  // convert from hex (as it is stored in the UI)
  if ($action['RGB']['HEX'] && $deduced = hex_to_rgb($action['RGB']['HEX'])) {
    $action['RGB'] = array_merge($action['RGB'], $deduced);
  }
  
  // All the maths is done, now defer to the api toolkits;
  $action['targetsize'] = $targetsize;

  $success = imageapi_toolkit_invoke('definecanvas', $image, array($action));
  if ($success) {
    $image->info['width'] = $targetsize['width'];
    $image->info['height'] = $targetsize['height'];
  }
  return $success;

/*

  $newcanvas = imagecreatetruecolor($targetsize['width'], $targetsize['height']);

  if ($RGB['HEX'] && $deduced = hex_to_rgb($RGB['HEX'])) {
    $background = imagecolorallocate($newcanvas, $RGB['red'], $RGB['green'], $RGB['blue']);
  }
  else {
    // No color, attempt transparency, assume white
    $background = imagecolorallocatealpha($newcanvas, 255, 255, 255, 127);
    imagesavealpha($newcanvas, TRUE);
    imagealphablending($newcanvas, FALSE);
    imagesavealpha($image->resource, TRUE);
  }
  imagefilledrectangle($newcanvas, 0, 0, $targetsize['width'], $targetsize['height'], $background);
#  imagealphablending($newcanvas, TRUE);

  if ($action['under']) {
    $canvas_object = (object) array(
      'resource' => $newcanvas,
      'info' => array(
        'width' => $targetsize['width'], 
        'height' => $targetsize['height'],
        'mime_type' => 'image/png',
      ),
      'toolkit' => $image->toolkit,
    );
    imageapi_image_overlay($canvas_object, $image, $targetsize['left'], $targetsize['top'], 100, TRUE);
  } 
  else {
    $image->resource = $newcanvas ;
  }
*/  
  $image->info['width'] = $targetsize['width'];
  $image->info['height'] = $targetsize['height'];
  return TRUE;
}

/**
 * Draw a color (or transparency) behind an image
 * 
 * $targetsize is an array expected to contain a width,height and a left,top
 * offset.
 */
function imageapi_gd_image_definecanvas(&$image, $action = array()) {
  $targetsize = $action['targetsize'];
  $RGB = $action['RGB'];

  $newcanvas = imagecreatetruecolor($targetsize['width'], $targetsize['height']);

  if ($RGB['HEX']) {
    $background = imagecolorallocate($newcanvas, $RGB['red'], $RGB['green'], $RGB['blue']);
  }
  else {
    // No color, attempt transparency, assume white
    $background = imagecolorallocatealpha($newcanvas, 255, 255, 255, 127);
    imagesavealpha($newcanvas, TRUE);
    imagealphablending($newcanvas, FALSE);
    imagesavealpha($image->resource, TRUE);
  }
  imagefilledrectangle($newcanvas, 0, 0, $targetsize['width'], $targetsize['height'], $background);
#  imagealphablending($newcanvas, TRUE);

  if ($action['under']) {
    $canvas_object = (object) array(
      'resource' => $newcanvas,
      'info' => array(
        'width' => $targetsize['width'], 
        'height' => $targetsize['height'],
        'mime_type' => 'image/png',
        'extension' => 'png',
      ),
      'toolkit' => $image->toolkit,
    );
    imageapi_image_overlay($canvas_object, $image, $targetsize['left'], $targetsize['top'], 100, TRUE);
  } 
  else {
    $image->resource = $newcanvas ;
  }
  return TRUE;
}

/**
 * Draw a color (or transparency) behind an image
 * 
 * $targetsize is an array expected to contain a width,height and a left,top
 * offset.
 */
function imageapi_imagemagick_image_definecanvas(&$image, $action = array()) {
  $targetsize = $action['targetsize'];
  $RGB = $action['RGB'];
  
  # TODO needs work.
  #
  $crop = " -background '#{$RGB['HEX']}' -crop   '{$targetsize['width']}x{$targetsize['height']}-{$targetsize['left']}-{$targetsize['top']}!' ";
  $draw = '';

  $draw = " -draw '";
  $draw .= " fill '#{$RGB['HEX']}' polygon 0,0 {$targetsize['width']},0 {$targetsize['width']},{$targetsize['height']} 0,{$targetsize['height']} ";
  $draw .= " ' ";
  #$draw .= " -composite ";
  $draw .= " +repage ";

  $compose = " $crop $draw ";
  $image->ops[] = $compose; 
  return TRUE; 
  
}


////////////////////////////////////////////////

/**
 * Place a given image under the current canvas
 *
 * Implementation of imagecache_hook_form()
 *
 * @param $action array of settings for this action
 * @return a form definition
 */
function canvasactions_canvas2file_form($action) {
  if (imageapi_default_toolkit() != 'imageapi_gd') {
    drupal_set_message('Overlays are not currently supported by using imagemagick. This effect requires GD image toolkit only.', 'warning');
  }

  $defaults = array(
    'xpos' => '0',
    'ypos' => '0',
    'alpha' => '100',
    'path' => '',
    'dimensions' => 'original',
  );
  $action = array_merge($defaults, (array)$action);

  $form = imagecacheactions_pos_form($action);
  $form['alpha'] = array(
    '#type' => 'textfield',
    '#title' => t('opacity'),
    '#default_value' => $action['alpha'],
    '#size' => 6,
    '#description' => t('Opacity: 0-100. Be aware that values other than 100% may be slow to process.'),
  );
  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('file name'),
    '#default_value' => $action['path'],
    '#description' => t('File may be in the "files/" folder, or relative to the Drupal siteroot.'),
    '#element_validate' => array('canvasactions_file2canvas_validate_file'),
  );
  $form['dimensions'] = array(
    '#type' => 'radios',
    '#title' => t('final dimensions'),
    '#default_value' => $action['dimensions'],
    '#options' => array('original' => 'original (dimensions are retained)', 'background' => 'background (image will be forced to match the size of the background)', 'minimum' => 'minimum (image may be cropped)', 'maximum' => 'maximum (image may end up with gaps)'),
    '#description' => t('What to do when the background image is a different size from the source image. Backgrounds are not tiled, but may be arbitrarily large.'),
  );
  return $form;
}

/**
 * Implementation of theme_hook() for imagecache_ui.module
 */
function theme_canvasactions_canvas2file($element) {
  $data = $element['#value'];

  $filepath = $data['path'];
  if (!file_exists($filepath) ) {
    $filepath = file_create_path($data['path']);
  }
  $file_url = url($filepath);
  return "xpos:{$data['xpos']} , ypos:{$data['ypos']} alpha:{$data['alpha']}%. file path:<a href='$file_url'>{$data['path']}</a>, dimensions:{$data['dimensions']}" ;
}

/**
 * Place the source image on the current background
 *
 * Implementation of hook_image()
 *
 * Note - this is currently incompatable with imagemagick, due to the way it
 * addresses $image->resource directly - a gd only thing.
 *
 * @param $image
 * @param $action
 */
function canvasactions_canvas2file_image(&$image, $action = array()) {
  // Search for full (siteroot) paths, then file dir paths, then relative to the current theme
  $filepath = $action['path'];
  if (!file_exists($filepath) ) {
    $filepath = file_create_path($action['path']);
  }
  if (! file_exists($filepath) ) {
    trigger_error("Failed to load underlay image $filepath.", E_USER_ERROR);
    return FALSE;
  }
  
  $underlay = imageapi_image_open($filepath);

  // To handle odd sizes, we will resize/crop the background image to the desired dimensions before 
  // starting the merge. The built-in imagecopymerge, and the watermark library both do not
  // allow overlays to be bigger than the target.
  // Adjust size
  $crop_rules = array('xoffset' => 0, 'yoffset' => 0, );
  if (empty($action['dimensions'])) $action['dimensions'] = 'original';
  switch ($action['dimensions']) {
    case 'original' :
      // If the underlay is smaller than the target size, 
      // then when preparing the underlay by cropping it, 
      // the offsets may need to be negative
      // which will produce a 'cropped' image larger than the original
      // In this case, we need to calculate the position of the bg image
      // in relation to the space it will occupy under the top layer
      #$crop_rules['xoffset'] = $underlay->info['width'] - $image->info['width'] ;

      $crop_rules['width'] = $image->info['width'];
      $crop_rules['height']  = $image->info['height'];
      break;
    case 'background' :
      $crop_rules['width'] = $underlay->info['width'];
      $crop_rules['height'] = $underlay->info['height'];
      break;
    case 'minimum' :
      $crop_rules['width'] = min($underlay->info['width'], $image->info['width']);
      $crop_rules['height'] = min($underlay->info['height'], $image->info['height']);
      break;
    case 'maximum' :
      $crop_rules['width'] = max($underlay->info['width'], $image->info['width']);
      $crop_rules['height'] = max($underlay->info['height'], $image->info['height']);
      break;
  }
  // imageapi crop assumes upsize is legal.
  imagecache_include_standard_actions(); // ensure the library is loaded.

  // Crop both before processing to avoid unwanted processing.
  imagecache_crop_image($underlay, $crop_rules);
  # BUG - this doesn't position either
  // Actually this fails because imagecache_crop fills it with solid color when 'cropping' to a larger size.
  #imagecache_crop_image($image, $crop_rules);
  #dpm(get_defined_vars());
  // This func modifies the underlay image by ref, placing the current canvas on it
  if (imageapi_image_overlay($underlay, $image, $action['xpos'], $action['ypos'], $action['alpha'], TRUE)) {
    $image->resource = $underlay->resource;
    return TRUE;
  }
}

////////////////////////////////////////////////


/**
 * Place a given image on top of the current canvas
 *
 * Implementation of imagecache_hook_form()
 *
 * @param $action array of settings for this action
 * @return a form definition
 */
function canvasactions_file2canvas_form($action) {
  if (imageapi_default_toolkit() != 'imageapi_gd') {
    drupal_set_message('Overlays are not currently supported by using imagemagick. This effect requires GD image toolkit only.', 'warning');
  }

  $defaults = array(
    'xpos' => '',
    'ypos' => '',
    'alpha' => '100',
    'path' => '',
  );
  $action = array_merge($defaults, (array)$action);
  
  $form = array(
    'help' => array(
      '#type' => 'markup',
      '#value' => t('Note that using a transparent overlay that is larger than the source image may result in unwanted results - a solid background.'),
    )
  );
  $form += imagecacheactions_pos_form($action);
  $form['alpha'] = array(
    '#type' => 'textfield',
    '#title' => t('opacity'),
    '#default_value' => $action['alpha'],
    '#size' => 6,
    '#description' => t('Opacity: 0-100. <b>Warning:</b> Due to a limitation in the GD toolkit, using an opacity other than 100% requires the system to use an algorithm that\'s much slower than the built-in functions. If you want partial transparency, you are better to use an already-transparent png as the overlay source image.'),
  );
  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('file name'),
    '#default_value' => $action['path'],
    '#description' => t('File may be in the "files/" folder, or relative to the Drupal siteroot.'),
    '#element_validate' => array('canvasactions_file2canvas_validate_file'),
  );
  return $form;
}


/**
 * Check if the named file is available
 */
function canvasactions_file2canvas_validate_file(&$element, &$form_status) {
  if (! file_exists($element['#value']) && ! file_exists(file_create_path($element['#value'])) ) {
    form_error($element, t("Unable to find the named file '%filepath' in either the site or the files directory. Please check the path. Use relative paths only.", array('%filepath' => $element['#value'])) );
  }
}

/**
 * Implementation of theme_hook() for imagecache_ui.module
 */
function theme_canvasactions_file2canvas($element) {
  $action = $element['#value'];
  return '<strong>'. basename($action['path']) . '</strong> x:'. $action['xpos'] .', y:'. $action['ypos'] .' alpha:'. $action['alpha'] .'%' ;
}

/**
 * Place the source image on the current background
 *
 * Implementation of hook_image()
 *
 *
 * @param $image
 * @param $action
 */
function canvasactions_file2canvas_image(&$image, $action = array()) {
  // search for full (siteroot) paths, then file dir paths, then relative to the current theme
  if (file_exists($action['path'])) {
    $overlay = imageapi_image_open($action['path'], $image->toolkit);
  }
  else if (file_exists(file_create_path($action['path']))) {
    $overlay = imageapi_image_open(file_create_path($action['path']), $image->toolkit);
  }
  if (! isset($overlay) || ! $overlay) {
    trigger_error(t("Failed to find overlay image %path for imagecache_actions file-to-canvas action. File was not found in the sites 'files' path or the current theme folder.", array('%path' => $action['path'])), E_USER_WARNING);
    return FALSE;
  }
  return imageapi_image_overlay($image, $overlay, $action['xpos'], $action['ypos'], $action['alpha']);
}


///////////////////////////////////////////////////////////////////

/**    
 * Place the source image on top of the current canvas    
 * 
 * Implementation of imagecache_hook_form()
 *    
 *    
 *    
 * @param $action array of settings for this action   
 * @return a form definition    
 */   
function canvasactions_source2canvas_form($action) {    
  $defaults = array(    
    'xpos' => '',   
    'ypos' => '',   
    'alpha' => '100',   
    'path' => '',   
  );    
  $action = array_merge($defaults, (array)$action);   
    
  $form = imagecacheactions_pos_form($action);    
  $form['alpha'] = array(   
      '#type' => 'textfield',   
      '#title' => t('opacity'),   
      '#default_value' => $action['alpha'],   
      '#size' => 6,   
      '#description' => t('Opacity: 0-100.'),   
  );    
  return $form;   
}   


     
/**   
 * Implementation of theme_hook() for imagecache_ui.module    
 */   
function theme_canvasactions_source2canvas($element) {    
  $data = $element['#value'];   
  return 'xpos:'. $data['xpos'] .', ypos:'. $data['ypos'] .' alpha:'. $data['alpha'] .'%' ;   
}

/**    
  * Place the source image on the current background   
  *    
  * Implementation of hook_image()   
  *    
  *    
  * @param $image    
  * @param $action   
  */   
function canvasactions_source2canvas_image(&$image, $action = array()) {    
  $overlay = imageapi_image_open($image->source); // this probably means opening the image twice. c'est la vie    
  return imageapi_image_overlay($image, $overlay, $action['xpos'], $action['ypos'], $action['alpha']);      
}

///////////////////////////////////////////////////////////////////

/**
 * Set radius for corner rounding
 * 
 * Implementation of imagecache_hook_form()
 *
 * @param $action array of settings for this action
 * @return a form definition
 */
function canvasactions_roundedcorners_form($action) {
  if (imageapi_default_toolkit() != 'imageapi_gd') {
    drupal_set_message('Rounded corners are not currently supported by using imagemagick. This effect requires GD image toolkit only.', 'warning');
  }

  drupal_add_js(drupal_get_path('module', 'imagecache_canvasactions') .'/imagecache_actions.jquery.js');
  $defaults = array(
    'radius' => '16',
    #'antialias' => TRUE,
    'independent_corners_set' => array(
      'independent_corners' => FALSE,
      'radii' => array(
        'tl' => 0,
        'tr' => 0,
        'bl' => 0,
        'br' => 0,
      ),
    ),
  );
  $action = array_merge($defaults, (array)$action);

  $form['radius'] = array(
      '#type' => 'textfield',
      '#title' => t('radius'),
      '#default_value' => $action['radius'],
      '#size' => 2,
  );

  $form['independent_corners_set'] = array(
      '#type' => 'fieldset',
      '#title' => t('Individual Corner Values'),
      '#collapsible' => TRUE,
      '#collapsed' => (! $action['independent_corners_set']['independent_corners']),
  );
  $form['independent_corners_set']['independent_corners'] = array(
      '#type' => 'checkbox',
      '#title' => t('Set Corners Independently'),
      '#default_value' => $action['independent_corners_set']['independent_corners'],
  );
  $corners = array(
    'tl' => t("Top Left Radius"),
    'tr' => t("Top Right Radius"),
    'bl' => t("Bottom Left Radius"),
    'br' => t("Bottom Right Radius"),
  );
  // Loop over the four corners and create field elements for them.
  $form['independent_corners_set']['radii'] = array('#type' => 'item', '#id' => 'independent-corners-set', );
  foreach ($corners as $attribute => $label) {
    $form['independent_corners_set']['radii'][$attribute] = array(
        '#type' => 'textfield',
        '#title' => $label,
        '#default_value' => 0+$action['independent_corners_set']['radii'][$attribute],
        '#size' => 2,
    );
  }
/*
  $form['antialias'] = array(
      '#type' => 'checkbox',
      '#title' => t('antialias'),
      '#return_value' => TRUE,
      '#default_value' => $action['antialias'],
      '#description' => t('Attempt antialias smoothing when drawing the corners'),
  );
*/
  $form['notes'] = array(
      '#type' => 'markup',
      '#value' => t('
        Note: the rounded corners effect uses true alpha transparency masking. 
        This means that this effect <b>will fail to be saved</b> on jpegs 
        <em>unless</em> you either <ul>
        <li>convert the image to PNG (using the coloractions filter for that),</li>
        <li>define a canvas underneath it (using canvasactions-define-canvas) or</li> 
        <li>underlay a solid color (using coloractions-alpha-flatten) or</li> 
        <li>underlay a background image (canvasactions-underlay)</li> 
        </ul>
        as a later part of this imagecache pipeline.
        <br/>
      '),
  );

  return $form;
}

function canvasactions_roundedcorners_image(&$image, $action = array()) {
  $independent_corners = !empty($action['independent_corners_set']['independent_corners']);
  if (!$independent_corners) {
    // set the independant corners to all be the same.
    $corners = array('tl', 'tr', 'bl', 'br');
    foreach ($corners as $key) {
      // Use the all-the-same radius setting.
      $action['independent_corners_set']['radii'][$key] = $action['radius'];
    }
  }
  
  return imageapi_toolkit_invoke('roundedcorners', $image, array($action));
}

/**
 * Trim rounded corners off an image, using an anti-aliasing algorithm.
 * 
 * Implementation of hook_image()
 * 
 * Note, this is not image toolkit-agnostic yet! It just assumes GD.
 * We can abstract it out once we have something else to abstract to.
 * In the meantime just don't.
 * 
 * 'handcoded' rounded corners logic contributed by donquixote 2009-08-31
 *
 * @param $image
 * @param $action
 */
function imageapi_gd_image_roundedcorners(&$image, $action = array()) {
  // Read settings.
  $width = $image->info['width'];
  $height = $image->info['height'];
  $radius = $action['radius'];
  $independent_corners = !empty($action['independent_corners_set']['independent_corners']);
  $corners = array('tl', 'tr', 'bl', 'br');

  $im = &$image->resource;
  // Prepare drawing on the alpha channel.
  imagesavealpha($im, TRUE);
  imagealphablending($im, FALSE);

  foreach ($corners as $key) {
    if ($independent_corners) {
      $r = $action['independent_corners_set']['radii'][$key];
    } 
    else {
      // Use the all-the-same radius setting.
      $r = $radius;
    }

    // key can be 'tl', 'tr', 'bl', 'br'.
    $is_bottom = ($key{0}=='b');
    $is_right = ($key{1}=='r');
    
    // dx and dy are in "continuous coordinates",
    // and mark the distance of the pixel middle to the image border.
    for ($dx = .5; $dx < $r; ++$dx) {
      for ($dy = .5; $dy < $r; ++$dy) {
        
        // ix and iy are in discrete pixel indices,
        // counting from the top left
        $ix = floor($is_right ? $width-$dx : $dx);
        $iy = floor($is_bottom ? $height-$dy : $dy);
        
        $opacity = _canvasactions_roundedcorners_pixel_opacity($dx, $dy, $r);
        if ($opacity >= 1) {
          // we can finish this row,
          // all following pixels will be fully opaque.
          break;
        }
        
        // Color lookup at ($ix, $iy).
        $color_ix = imagecolorat($im, $ix, $iy);
        $color = imagecolorsforindex($im, $color_ix);
        
        if (isset($rgba['alpha'])) {
          $color['alpha'] = 127 - round($opacity * (127 - $color['alpha']));
        } 
        else {
          $color['alpha'] = 127 - round($opacity * 127);
        }
        // Value should not be more than 127, and not less than 0.
        $color['alpha'] = ($color['alpha'] > 127) ? 127 : (($color['alpha'] < 0) ? 0 : $color['alpha']);
        $color_ix = imagecolorallocatealpha($im, $color['red'], $color['green'], $color['blue'], $color['alpha']);
        imagesetpixel($im, $ix, $iy, $color_ix);
      }
    }
  }
  return TRUE;
}

/**
 * Calculate the transparency value for a rounded corner pixel
 * 
 * @param $x
 *   distance from pixel center to image border (left or right)
 *   should be an integer + 0.5
 *   
 * @param $y
 *   distance from pixel center to image border (top or bottom)
 *   should be an integer + 0.5
 *   
 * @param $r
 *   radius of the rounded corner
 *   should be an integer
 *   
 * @return float
 *   opacity value between 0 (fully transparent) and 1 (fully opaque).
 */
function _canvasactions_roundedcorners_pixel_opacity($x, $y, $r) {
  if ($x < 0 || $y < 0) {
    return 0;
  } 
  else if ($x > $r || $y > $r) {
    return 1;
  }
  $dist_2 = ($r-$x)*($r-$x) + ($r-$y)*($r-$y);
  $r_2 = $r*$r;
  if ($dist_2 > ($r+0.8)*($r+0.8)) {
    return 0;
  } 
  else if ($dist_2 < ($r-0.8)*($r-0.8)) {
    return 1; 
  } 
  else {
    // this pixel needs special analysis.
    // thanks to a quite efficient algorithm, we can afford 10x antialiasing :)
    $opacity = 0.5;
    if ($x > $y) {
      // cut the pixel into 10 vertical "stripes"
      for ($dx=-0.45; $dx<0.5; $dx+=0.1) {
        // find out where the rounded corner edge intersects with the stripe
        // this is plain triangle geometry.
        $dy = $r - $y - sqrt($r_2 - ($r-$x-$dx)*($r-$x-$dx));
        $dy = ($dy > 0.5) ? 0.5 : (($dy < -0.5) ? -0.5 : $dy);
        // count the opaque part of the stripe.
        $opacity -= 0.1 * $dy;
      }
    } 
    else {
      // cut the pixel into 10 horizontal "stripes"
      for ($dy=-0.45; $dy<0.5; $dy+=0.1) {
        // this is the math:
        //   ($r-$x-$dx)^2 + ($r-$y-$dy)^2 = $r^2
        //   $dx = $r - $x - sqrt($r^2 - ($r-$y-$dy)^2) 
        $dx = $r - $x - sqrt($r_2 - ($r-$y-$dy)*($r-$y-$dy));
        $dx = ($dx > 0.5) ? 0.5 : (($dx < -0.5) ? -0.5 : $dx);
        $opacity -= 0.1 * $dx;
      }
    }
    return ($opacity < 0) ? 0 : (($opacity > 1) ? 1 : $opacity);
  }
}



/**
 * imageapi_roundedcorners
 */
function imageapi_imagemagick_image_roundedcorners(&$image, $action = array()) {
  // Based on the imagemagick documentation.
  // http://www.imagemagick.org/Usage/thumbnails/#rounded
  // Create arc cut-outs, then mask them.
  // Draw black triangles and white circles.
  // draw circle is center: x,y, and a point on the perimeter
  $corners = array('tl', 'tr', 'bl', 'br');
  $radii = $action['independent_corners_set']['radii'];
  $width = $image->info['width'];
  $height = $image->info['height'];
  $tl = $radii['tl'];
  $tr = $radii['tr'];
  $bl = $radii['bl'];
  $br = $radii['br'];

  $drawmask = " -draw '";
  if ($tl) {
    $drawmask .= " fill black polygon 0,0 0,{$tl} {$tl},0 ";
    $drawmask .= " fill white circle {$tl},{$tl} {$tl},0 ";
  }
  if ($tr) {
    $right = $width-$tr;
    $drawmask .= " fill black polygon {$right},0 {$width},0 {$width},{$tr} ";
    $drawmask .= " fill white circle {$right},{$tr} {$right},0 ";
  }
  if ($bl) {
    $bottom = $height-$bl;
    $drawmask .= " fill black polygon 0,{$bottom} 0,{$height} {$bl},{$height} ";
    $drawmask .= " fill white circle {$bl},{$bottom} 0,{$bottom} ";
  }
  if ($br) {
    $bottom = $height-$br;
    $right = $width-$br;
    $drawmask .= " fill black polygon {$right},{$height} {$width},{$bottom} {$width},{$height} ";
    $drawmask .= " fill white circle {$right},{$bottom} {$width},{$bottom} ";
  }
  $drawmask .= " ' ";

  $compose = " \\( +clone  -threshold -1 {$drawmask} \\) +matte -compose CopyOpacity -composite ";
  $image->ops[] = $compose; 
  return TRUE; 
} 

/**
 * Implementation of theme_hook() for imagecache_ui.module
 */
function theme_canvasactions_roundedcorners($element) {
  $data = $element['#value'];
  if (!empty($data['independent_corners_set']['independent_corners'])) {
    $dimens = join('px | ', $data['independent_corners_set']['radii']) .'px';
  } 
  else { 
    $dimens = "Radius: {$data['radius']}px"; 
  }
  return $dimens;
}

///////////////////////////////////////////////////////////////////

/**
 * Switch between presets depending on logic
 * 
 * Implementation of imagecache_hook_form()
 *
 * @param $action array of settings for this action
 * @return a form definition
 */
function canvasactions_aspect_form($action) {
  $defaults = array( 'ratio_adjustment' => 1 );
  $action = array_merge($defaults, (array)$action);
  
  $form = array(
    'help' => array(
      '#type' => 'markup',
      '#value' => t('You must create the two presets to use <em>before</em> enabling this process.'),
    )
  );

  $presets = array();
  foreach (imagecache_presets(TRUE) as $preset) {
    $presets[$preset['presetid']] = $preset['presetname'];
  }

  $form['portrait'] = array(
    '#type' => 'select',
    '#title' => t('Preset to use if the image is portrait (vertical)'),
    '#default_value' => $action['portrait'],
    '#options' => $presets,
  );
  $form['landscape'] = array(
    '#type' => 'select',
    '#title' => t('Preset to use if the image is landscape (horizontal)'),
    '#default_value' => $action['landscape'],
    '#options' => $presets,
  );

  $form['ratio_adjustment'] = array(
    '#type' => 'textfield',
    '#title' => t('Ratio Adjustment (advanced)'),
    '#size' => 3,
    '#default_value' => $action['ratio_adjustment'],
    '#description' => t("
This allows you to bend the rules for how different the proportions need to be to trigger the switch.  
<br/>If the (width/height)*n is greater than 1, use 'landscape', otherwise use 'portrait'.
<br/>When n = 1 (the default) it will switch between portrait and landscape modes.
<br/>If n > 1, images that are slightly wide will still be treated as portraits.
If n < 1 then blunt portraits will be treated as landscape.
    "),
  );
  
  
  return $form;
}


/**
 * Implementation of theme_hook() for imagecache_ui.module
 */
function theme_canvasactions_aspect($element) {
  $action = $element['#value'];
  $presets = imagecache_presets(TRUE); 
  $ratio_adjustment = '';
  if ($action['ratio_adjustment'] != 1) {
    $ratio_adjustment = " (switch at 1:{$action['ratio_adjustment']})";
  }
  return 'Portrait size: <strong>'. $presets[$action['portrait']]['presetname'] . '</strong>. Landscape size: <strong>'. $presets[$action['landscape']]['presetname'] .'</strong>'. $ratio_adjustment ;
}

/**
 * Choose the action and trigger that.
 * 
 * Implementation of hook_image()
 *
 *
 * @param $image
 * @param $action
 */
function canvasactions_aspect_image(&$image, $action = array()) {
  $ratio_adjustment = 0 + $action['ratio_adjustment'];
  if (!$ratio_adjustment) {
    $ratio_adjustment = 1;
  }
  $aspect = $image->info['width'] / $image->info['height'];
  // width / height * adjustment. If > 1, it's wide. 
  $preset_id = (($aspect * $ratio_adjustment) > 1) ? $action['landscape'] : $action['portrait'];
  $preset = imagecache_preset($preset_id);

  // Run the preset actions ourself. Cannot invoke a preset from the top as it handles filenames, not image objects.
  // ripped from imagecache_build_derivative()
  foreach ($preset['actions'] as $sub_action) {
    _imagecache_apply_action($sub_action, $image);
  }
  return TRUE;
}


///////////////////////////////////////////////////////////////////
