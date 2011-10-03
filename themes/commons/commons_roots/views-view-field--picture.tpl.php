<?php
 /**
  * This template is used to print a single field in a view. It is not
  * actually used in default Views, as this is registered as a theme
  * function which has better performance. For single overrides, the
  * template is perfectly okay.
  *
  * Variables available:
  * - $view: The view object
  * - $field: The field handler object that can process the input
  * - $row: The raw SQL result that can be used
  * - $output: The processed output that will normally be used.
  *
  * When fetching output from the $row, this construct should be used:
  * $data = $row->{$field->field_alias}
  *
  * The above will guarantee that you'll always get the correct data,
  * regardless of any changes in the aliasing that might happen if
  * the view is modified.
  */
?>
<?php 
  $picture = $row->{$field->field_alias};

  if (!isset($picture) || $picture == '') {
    $picture = variable_get('user_picture_default', '');
  }
  
  if ($picture != '') {
    $field_name = $field->aliases['name'];
    $field_uid = $field->aliases['uid'];
    
    $name = $row->{$field_name};
    $uid = $row->{$field_uid};
    
    $preset = $field->options['imagecache_preset'];  
    print commons_roots_thumb_user_picture($picture, $preset, $name, $uid);
  }
?>

