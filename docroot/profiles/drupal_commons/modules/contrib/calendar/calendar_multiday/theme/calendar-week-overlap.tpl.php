<?php
// $Id: calendar-week-overlap.tpl.php,v 1.1.2.1 2010/11/28 23:31:28 karens Exp $ 
/**
 * @file
 * Template to display a view as a calendar week with overlapping items
 * 
 * @see template_preprocess_calendar_week.
 *
 * $day_names: An array of the day of week names for the table header.
 * $rows: The rendered data for this week.
 * 
 * For each day of the week, you have:
 * $rows['date'] - the date for this day, formatted as YYYY-MM-DD.
 * $rows['datebox'] - the formatted datebox for this day.
 * $rows['empty'] - empty text for this day, if no items were found.
 * $rows['all_day'] - an array of formatted all day items.
 * $rows['items'] - an array of timed items for the day.
 * $rows['items'][$time_period]['hour'] - the formatted hour for a time period.
 * $rows['items'][$time_period]['ampm'] - the formatted ampm value, if any for a time period.
 * $rows['items'][$time_period]['values'] - An array of formatted items for a time period.
 * 
 * $view: The view.
 * $min_date_formatted: The minimum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * $max_date_formatted: The maximum date for this calendar in the format YYYY-MM-DD HH:MM:SS.
 * 
 */
//dsm('Display: '. $display_type .': '. $min_date_formatted .' to '. $max_date_formatted);
//dsm($rows);
//dsm($items);
?>

<div class="calendar-calendar"><div class="week-view">
  <div id="header-container">
  <table class="full">
  <tbody>
    <tr class="holder"><td class="calendar-time-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td></tr>
    <tr>
      <th class="calendar-agenda-hour">&nbsp;</th>
      <?php foreach ($day_names as $cell): ?>
        <th class="<?php print $cell['class']; ?>">
          <?php print $cell['data']; ?>
        </th>
      <?php endforeach; ?>
    </tr>
  </tbody>
  </table>
  </div>
  <div id="multi-day-container">
  <table class="full">
  <tbody>
  <tr class="holder"><td class="calendar-time-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td></tr>
    <?php for ($i = 0; $i < $multiday_rows; $i++): ?>
    <?php 
      $colpos = 0; 
      $rowclass = "all-day";
      if( $i == 0) {
        $rowclass .= " first";
      }
      if( $i == $multiday_rows - 1) {
        $rowclass .= " last";
      }
    ?>
    <tr class="<?php print $rowclass?>">
      <?php if($i == 0 && ($by_hour_count > 0 || !empty($start_times))) :?>
      <td class="<?php print $agenda_hour_class ?>" rowspan="<?php print $multiday_rows?>">
        <span class="calendar-hour"><?php print date_t('All day', 'datetime')?></span>
      </td>
      <?php endif; ?>
      <?php for($j = 0; $j < 6; $j++): ?>
        <?php $cell = (empty($all_day[$j][$i])) ? NULL : $all_day[$j][$i]; ?>
        <?php if($cell != NULL && $cell['filled'] && $cell['wday'] == $j): ?>
          <?php for($k = $colpos; $k < $cell['wday']; $k++) : ?>
          <td class="calendar-agenda-items multi-day no-entry"><div class="inner">&nbsp;</div></td>
          <?php endfor;?>
          <td colspan="<?php print $cell['colspan']?>" class="calendar-agenda-items multi-day">
            <div class="inner">
            <?php print $cell['entry']?>
            </div>
          </td>
          <?php $colpos = $cell['wday'] + $cell['colspan']; ?>
        <?php endif; ?>
      <?php endfor; ?>  
      <?php for($j = $colpos; $j < 7; $j++) : ?>
      <td class="calendar-agenda-items multi-day no-entry"><div class="inner">&nbsp;</div></td>
      <?php endfor;?>
    </tr>
    <?php endfor; ?>
    <?php if ($multiday_rows == 0) :?>
    <tr>
      <td class="<?php print $agenda_hour_class ?>">
        <span class="calendar-hour"><?php print date_t('All day', 'datetime')?></span>
      </td>
      <?php for($j = 0; $j < 6; $j++): ?>
      <td class="calendar-agenda-items multi-day no-entry"><div class="inner">&nbsp;</div></td>
      <?php endfor; ?>
     </tr>
    <?php endif; ?>
    <tr class="expand">
      <td class="<?php print $agenda_hour_class ?>">
        <span class="calendar-hour">&nbsp;</span>
      </td>
      <?php for($j = 0; $j < 6; $j++): ?>
      <td class="calendar-agenda-items multi-day no-entry"><div class="inner">&nbsp;</div></td>
      <?php endfor; ?>
     </tr>
  </thead> 
  </table>
  </div>
  <div class="header-body-divider">&nbsp;</div>
  <div id="single-day-container">
    <script>
      try {
        // Hide container while it renders...  Degrade w/o javascript support
        $('#single-day-container').css('visibility','hidden');
      }catch(e){ 
        // swallow 
      }
    </script>
    <table class="full">
      <tbody>
        <tr class="holder"><td class="calendar-time-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td><td class="calendar-day-holder"></td></tr>
        <tr>
          <?php for ($index = 0; $index < 8; $index++): ?>
          <?php if ($index == 0 ): ?>
          <td class="first">
          <?php elseif ($index == 7 ) : ?>
          <td class="last">
          <?php else : ?>
          <td>
          <?php endif; ?>
            <?php foreach ($start_times as $time_cnt => $start_time): ?>
              <?php 
                if ($time_cnt == 0) {
                  $class = 'first ';
                }
                elseif ($time_cnt == count($start_times) - 1) {
                  $class = 'last ';
                }
                else {
                  $class = '';
                } ?>
              <?php if( $index == 0 ): ?>
              <?php $time = $items[$start_time];?>
              <div class="<?php print $class?>calendar-agenda-hour">
                <span class="calendar-hour"><?php print $time['hour']; ?></span>
                <span class="calendar-ampm"><?php print $time['ampm']; ?></span>
              </div>
              <?php else: ?>
              <div class="<?php print $class?>calendar-agenda-items single-day">
                <div class="half-hour">&nbsp;</div>
                <div class="calendar item-wrapper">
                  <div class="inner">
                    <?php if(!empty($items[$start_time]['values'][$index - 1])) :?>
                      <?php foreach($items[$start_time]['values'][$index - 1] as $item) :?>
                        <?php if (isset($item['is_first']) && $item['is_first']) :?>
                        <div class="item <?php print $item['class']?> first_item">
                        <?php else : ?>
                        <div class="item <?php print $item['class']?>">
                        <?php endif; ?>
                        <?php print $item['entry'] ?>
                        </div>
                      <?php endforeach; ?>
                    <?php endif; ?>
                  </div>
                </div>
              </div>
              <?php endif; ?>
            <?php endforeach;?>
          </td>
          <?php endfor;?>
        </tr>
      </tbody>
    </table>
  </div>
  <div class="single-day-footer">&nbsp;</div>
</div></div>
<script>
try {
  // Size and position the viewport inline so there are no delays
  calendar_resizeViewport();
  calendar_scrollToFirst();

  // Show it now that it is complete and positioned
  $('#single-day-container').css('visibility','visible');
}catch(e){ 
  // swallow 
}
</script>