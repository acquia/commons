<?php
// $Id: watermark.inc,v 1.1.4.6 2009/10/30 14:03:54 dman Exp $
/**
 * @file routine for image layering
 * 
 */


/****************************************************************************************************************************************/
/**
 * Note that the below code is laboriously slow - it takes and compares every pixel of the two inputs
 * and calculates a new valus for each of them. this is only a fallback because reliable image toolkit 
 * transparencies was buggy on certain platforms :(
 * 
 * DOES NOT WORK WELL on indexed color yet (GIFs)
 */

//Niko (http://www.codeguru.com.ua)
class watermark {
  function create_watermark($main_img_obj, $watermark_img_obj, $x_ins, $y_ins, $alpha_level = 100) {
    $alpha_level /= 100;
    $base_img_obj_w = imagesx($main_img_obj);
    $base_img_obj_h = imagesy($main_img_obj);
    # Should this change to match both images?
    $main_img_obj_w = max($base_img_obj_w, imagesx($watermark_img_obj));
    $main_img_obj_h = max($base_img_obj_h, imagesy($watermark_img_obj));
    // dman: start with the MAX dimensions, 
    // then let the caller crop it later according to its own logic.
    $watermark_img_obj_w = imagesx($watermark_img_obj);
    $watermark_img_obj_h = imagesy($watermark_img_obj);

    $main_img_obj_min_x = $x_ins;
    $main_img_obj_min_y = $y_ins;

    $return_img = imagecreatetruecolor($main_img_obj_w, $main_img_obj_h);
    imagesavealpha($return_img, TRUE);
    imagealphablending($return_img, FALSE);

    // Support indexed color (gif) if I have to
    $transparent_ix = imagecolortransparent($main_img_obj);
    if ($transparent_ix >= 0) {
      $transparent = imagecolorsforindex($main_img_obj, $transparent_ix);
      // Allocate the values to the new image and get new color.
      $transparent = imagecolorallocatealpha($return_img, $transparent['red'], $transparent['green'], $transparent['blue'], $transparent['alpha']);
      imagecolortransparent($return_img, $transparent);
    }
    $watermark_transparent_ix = imagecolortransparent($watermark_img_obj);
    if ($watermark_transparent_ix >= 0) {
      $watermark_transparent = imagecolorsforindex($watermark_img_obj, $watermark_transparent_ix);
    }
    

    for ($y = 0; $y < $main_img_obj_h; $y++) {
      for ($x = 0; $x < $main_img_obj_w; $x++) {

        $return_color = NULL;

        $watermark_x = $x - $main_img_obj_min_x;
        $watermark_y = $y - $main_img_obj_min_y;

        if (($x < $base_img_obj_w) && ($y < $base_img_obj_h)) {
          // try not to go out of bounds when looking for color.
          $main_rgb = imagecolorsforindex($main_img_obj, imagecolorat($main_img_obj, $x, $y));
        }
        else {
          $main_rgb = array('red' => 255, 'green' => 255, 'blue' => 255, 'alpha' => 127);
        }
        
        if ($watermark_x >= 0 && $watermark_x < $watermark_img_obj_w && $watermark_y >= 0 && $watermark_y < $watermark_img_obj_h) {
          $color_ix = imagecolorat($watermark_img_obj, $watermark_x, $watermark_y);
          $watermark_rbg = imagecolorsforindex($watermark_img_obj, $color_ix);

          // Gif indexed color ?
          if ($color_ix == $watermark_transparent_ix) {
            $watermark_rbg['alpha'] = 127;
          }
          
          $watermark_alpha = round(((127 - $watermark_rbg['alpha']) / 127), 2);
          $watermark_alpha = $watermark_alpha * $alpha_level;

          $avg_red = $this->_get_ave_color($main_rgb['red'], $watermark_rbg['red'], $watermark_alpha);
          $avg_green = $this->_get_ave_color($main_rgb['green'], $watermark_rbg['green'], $watermark_alpha);
          $avg_blue = $this->_get_ave_color($main_rgb['blue'], $watermark_rbg['blue'], $watermark_alpha);
          
          // TODO figure out the maths for merging two transparent images
          $new_alpha = min($watermark_rbg['alpha'], $main_rgb['alpha']);
          #$new_alpha = $main_rgb['alpha'];
          #$new_alpha = 0;

          $return_color = $this->_get_image_color($return_img, $avg_red, $avg_green, $avg_blue, $new_alpha);
        }
        else {
          // Point is out of bounds from the watermark. Return the normal image color

          // allow watermark to overflow from the image. Rare, but could be useful
          if ($x > imagesx($main_img_obj) || $y > imagesy($main_img_obj)) {
            // Point is out of bounds from the main image too. Return transparent
            $watermark_rbg = imagecolorsforindex($watermark_img_obj, imagecolorat($watermark_img_obj, $watermark_x, $watermark_y));
            $watermark_alpha = 0;#round(((127 - $watermark_rbg['alpha']) / 127), 2);
            $return_color = $this->_get_image_color($return_img, $watermark_rbg['red'], $watermark_rbg['green'], $watermark_rbg['blue'], $watermark_alpha);
          }
          else {
            $return_color = imagecolorat($main_img_obj, $x, $y);
          }

        }
        if ($return_color == $transparent_ix) {
          $return_color = $transparent;
        }
        imagesetpixel($return_img, $x, $y, $return_color);
      }
    }
    return $return_img;
  }

  function _get_ave_color($color_a, $color_b, $alpha_level) {
    return round((($color_a * (1 - $alpha_level)) + ($color_b * $alpha_level)));
  }

  function _get_image_color($im, $r, $g, $b, $alpha) {
    $c = imagecolorexactalpha($im, $r, $g, $b, $alpha);
    if ($c != -1)
      return $c;
    $c = imagecolorallocate($im, $r, $g, $b, $alpha);
    if ($c != -1)
      return $c;
    return imagecolorclosest($im, $r, $g, $b, $alpha);
  }
}
/****************************************************************************************************************************************/
