<?php
// $Id: date-vcalendar.tpl.php,v 1.1.2.5 2010/11/20 13:25:54 karens Exp $
/**
 * $calname
 *   The name of the calendar.
 * $events
 *   @see date-vevent.tpl.php.
 *   @see date-valarm.tpl.php.
 */
?>
BEGIN:VCALENDAR
VERSION:2.0
METHOD:PUBLISH
X-WR-CALNAME: <?php print $calname ?>
PRODID:-//Drupal iCal API//EN
<?php foreach($events as $event): ?>
<?php print theme('date_vevent', $event); ?>
<?php endforeach; ?>
END:VCALENDAR
