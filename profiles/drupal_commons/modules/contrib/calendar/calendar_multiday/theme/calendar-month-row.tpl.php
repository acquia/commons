<?php
// $Id: calendar-month-row.tpl.php,v 1.1.2.1 2010/11/28 23:31:28 karens Exp $
/**
 * @file
 * Template to display a row
 * 
 * - $inner: The rendered string of the row's contents.
 */
$attrs = ($class) ? 'class="' . $class . '"': '';
$attrs .= ($iehint > 0) ? ' iehint="' . $iehint . '"' : '';
?>
<?php if ($attrs != ''):?>
<tr <?php print $attrs?>>
<?php else:?>
<tr>
<?php endif;?>
  <?php print $inner ?>
</tr>
