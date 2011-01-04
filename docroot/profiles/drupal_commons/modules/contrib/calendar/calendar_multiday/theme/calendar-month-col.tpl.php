<?php
// $Id: calendar-month-col.tpl.php,v 1.1.2.1 2010/11/28 23:31:28 karens Exp $ 
/**
 * @file
 * Template to display a column
 * 
 * - $item: The item to render within a td element.
 */
$id = (isset($item['id'])) ? 'id="' . $item['id'] . '" ' : '';
$date = (isset($item['date'])) ? 'date="' . $item['date'] . '" ' : '';
?>
<td <?php print $id?>class="<?php print $item['class'] ?>" colspan="<?php print $item['colspan'] ?>" rowspan="<?php print $item['rowspan'] ?>"<?php print $date ?>>
  <div class="inner">
    <?php print $item['entry'] ?>
  </div>
</td>
