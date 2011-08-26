<?php
//$Id: calendar.inc,v 1.1.2.4 2011/01/02 00:00:56 karens Exp $
/**
 * Build calendar
 *
 * @param unknown_type $view
 * @param unknown_type $items
 * @return themed table
 */
function calendar_build_calendar($view, $items) {
  // Remove nodes outside the selected date range.
  $values = array();
  foreach ($items as $delta => $item) {
    if (empty($item->calendar_start_date) || empty($item->calendar_end_date)) {
      continue;
    }
    $item_start = date_format($item->calendar_start_date, DATE_FORMAT_DATE);
    $item_end = date_format($item->calendar_end_date, DATE_FORMAT_DATE);
    if (($item_start >= $view->date_info->min_date_date && $item_start <= $view->date_info->max_date_date)
     || ($item_end >= $view->date_info->min_date_date && $item_end <= $view->date_info->max_date_date)) {
       $values[$item_start][date_format($item->date_start, 'H:i:s')][] = $item;
    }
  }
  $items = $values;
  ksort($items);
 
  $rows = array();
  $curday = drupal_clone($view->date_info->min_date);
 
  switch ($view->date_info->granularity) {
    case 'year':
      $rows = array();
      $view->date_info->mini = TRUE;
      for ($i = 1; $i <= 12; $i++) {
        $rows[$i] = calendar_build_mini_month($curday, $view, $items);
      }
      $view->date_info->mini = FALSE;
      break;
    case 'month':
      $rows = ($view->date_info->mini) ? calendar_build_mini_month($curday, $view, $items) : calendar_build_month($curday, $view, $items);
      break;
    case 'day':
      $rows = calendar_build_day($curday, $view, $items);
      break;
    case 'week':
      $rows = calendar_build_week($curday, $view, $items);
      // Merge the day names in as the first row.
      $rows = array_merge(array(calendar_week_header($view)), $rows);
      break;
  }
  return $rows;
 
}
/**
 * Build one month.
 */
function calendar_build_mini_month(&$curday, $view, $items) {
  $month = date_format($curday, 'n');
  date_modify($curday, '-' . strval(date_format($curday, 'j')-1) . ' days');
  $rows = array();
  do {
    $rows = array_merge($rows, calendar_build_mini_week($curday, $view, $items, TRUE));
    $curday_date = date_format($curday, DATE_FORMAT_DATE);
    $curday_month = date_format($curday, 'n');
  } while ($curday_month == $month && $curday_date <= $view->date_info->max_date_date);
  // Merge the day names in as the first row.
  $rows = array_merge(array(calendar_week_header($view)), $rows);
  return $rows;
}
/**
 * Build one month.
 */
function calendar_build_month(&$curday, $view, $items) {
  $month = date_format($curday, 'n');
  $curday_date = date_format($curday, DATE_FORMAT_DATE);
  $weekdays = calendar_untranslated_days($items, $view);
  date_modify($curday, '-' . strval(date_format($curday, 'j')-1) . ' days');
  $rows = array();
  do {
    $init_day = clone($curday);
    $today = date_format(date_now(date_default_timezone_name()), DATE_FORMAT_DATE);
    $month = date_format($curday, 'n');
    $week = date_week($curday_date);
    $first_day = variable_get('date_first_day', 0);
    $week_rows = calendar_build_week($curday, $view, $items, TRUE);
    $multiday_buckets = $week_rows['multiday_buckets'];
    $singleday_buckets = $week_rows['singleday_buckets'];
   
    $total_rows = $week_rows['total_rows'];
   
    // Theme each row
    $output = "";
    $final_day = clone($curday);
 
    $iehint = 0;
    $max_multirow_cnt = 0;
    $max_singlerow_cnt = 0;
   
    for ($i = 0; $i < $total_rows + 1; $i++) {
      $inner = "";
     
      // If we're displaying the week number, add it as the
      // first cell in the week.
      if ($i == 0 && !empty($view->date_info->style_with_weekno) && !in_array($view->date_info->granularity, array('day', 'week'))) {
        $url = $view->get_path() .'/'. $view->date_info->year .'-W'. $week;
        if (!empty($view->date_info->display_types['week'])) {
          $weekno = l($week, $url, array('query' => !empty($view->date_info->append) ? $view->date_info->append : ''));
        }
        else {
          // Do not link week numbers, if Week views are disabled.
          $weekno = $week;
        }
        $item = array(
          'entry' => $weekno,
          'colspan' => 1,
          'rowspan' => $total_rows + 1,
          'id' => $view->name . '-weekno-' . $curday_date, 
          'class' => 'week'
        );
        $inner .= theme('calendar_month_col', $item);
      }
     
      $curday = clone($init_day);
 
      // move backwards to the first day of the week
      $day_wday = date_format($curday, 'w');
      date_modify($curday, '-' . strval((7 + $day_wday - $first_day) % 7) . ' days');
     
      for ( $wday = 0; $wday < 7; $wday++) {
 
        $curday_date = date_format($curday, DATE_FORMAT_DATE);
        $class = strtolower($weekdays[$wday]);
        $item = NULL;
        $in_month = !($curday_date < $view->date_info->min_date_date || $curday_date > $view->date_info->max_date_date || date_format($curday, 'n') != $month);
       
        // Add the datebox
        if ($i == 0) {
          $count = $in_month ? intval(count($multiday_buckets[$wday]) + count($singleday_buckets[$wday])) : FALSE;
          $item = array(
            'entry' => theme('calendar_datebox', $curday_date, $view, $items, $count),
            'colspan' => 1,
            'rowspan' => 1,
            'class' => 'date-box',
            'date' => $curday_date,
            'id' => $view->name . '-' . $curday_date . '-date-box'
          );
          $item['class'] .= ($curday_date == $today && $in_month ? ' today' : '') .
            ($curday_date < $today ? ' past' : '') .
            ($curday_date > $today ? ' future' : '');
        }
        else {
          $index = $i - 1;
          $multi_count = count($multiday_buckets[$wday]);
         
          // Process multiday buckets first.  If there is a multiday-bucket item in this row...
          if ($index < $multi_count) {
           
            // If this item is filled with either a blank or an entry...
            if ($multiday_buckets[$wday][$index]['filled']) {
             
              // Add item and add class
              $item = $multiday_buckets[$wday][$index];
              $item['class'] =  'multi-day';
              $item['date'] = $curday_date;
             
              // Is this an entry?
              if (!$multiday_buckets[$wday][$index]['avail']) {
               
                // If the item either starts or ends on today,
                // then add tags so we can style the borders
                if ($curday_date == $today && $in_month) {
                  $item['class'] .=  ' starts-today';
                }
               
                // Calculate on which day of this week this item ends on..
                $end_day = clone($curday);
                $span = $item['colspan'] - 1;
                date_modify($end_day, '+' . $span .' day');
                $endday_date = date_format($end_day, DATE_FORMAT_DATE);
               
                // If it ends today, add class
                if ($endday_date == $today && $in_month) {
                  $item['class'] .=  ' ends-today';
                }
              }
            }
           
            // If this is an acutal entry, add classes regarding the state of the
            // item
            if ($multiday_buckets[$wday][$index]['avail']) {
              $item['class'] .= ' ' . $wday . ' ' . $index . ' no-entry ' . ($curday_date == $today && $in_month ? ' today' : '') .
                ($curday_date < $today ? ' past' : '') .
                ($curday_date > $today ? ' future' : '');
            }
           
          // Else, process the single day bucket - we only do this once per day
          }
          elseif ($index == $multi_count) {
           
            $single_day_cnt = 0;
            // If it's empty, add class
            if (count($singleday_buckets[$wday]) == 0) {
              $single_days = "&nbsp;";
              if ($max_multirow_cnt == 0 ) {
                $class = ($multi_count > 0 ) ? 'single-day no-entry noentry-multi-day' : 'single-day no-entry';
              }
              else {
                $class = 'single-day';
              }
            }
            else {
              $single_days = "";
              foreach ($singleday_buckets[$wday] as $day) {
                foreach ($day as $event) {
                  $single_day_cnt++;
                  $single_days .= (isset($event['more_link'])) ? '<div class="calendar-more">' . $event['entry'] . '</div>' : $event['entry'];
                }
              }
              $class = 'single-day';
            }
           
            $rowspan = $total_rows - $index;
           
            // Add item...
            $item = array(
              'entry' => $single_days,
              'colspan' => 1,
              'rowspan' => $rowspan,
              'class' => $class,
              'date' => $curday_date,
              'id' => $view->name . '-' . $curday_date . '-' . $index
            );
           
            // Hack for ie to help it properly space single day rows
            if ($rowspan > 1 && $in_month && $single_day_cnt > 0) {
              $max_multirow_cnt = max($max_multirow_cnt, $single_day_cnt);
            }
            else {
              $max_singlerow_cnt = max($max_singlerow_cnt, $single_day_cnt);
            }
           
            // If the singlerow is bigger than the multi-row, then null out
            // ieheight - I'm estimating that a single row is twice the size of
            // multi-row.  This is really the best that can be done with ie
            if ($max_singlerow_cnt >= $max_multirow_cnt || $max_multirow_cnt <= $multi_count / 2 ) {
              $iehint = 0;
            }
            elseif ($rowspan > 1 && $in_month && $single_day_cnt > 0) {
              $iehint = max($iehint, $rowspan - 1); // How many rows to adjust for?
            }
           
            // Set the class
            $item['class'] .= ($curday_date == $today && $in_month ? ' today' : '') .
              ($curday_date < $today ? ' past' : '') .
              ($curday_date > $today ? ' future' : '');
          }
        }
 
        // If there isn't an item, then add empty class
        if ($item != NULL) {
          if (!$in_month) {
            $item['class'] .= ' empty';
          }
          // Style this entry - it will be a <td>.
          $inner .= theme('calendar_month_col', $item);
        }
       
        date_modify($curday, '+1 day');
      }
     
      if ($i == 0) {
        $output .= theme('calendar_month_row', $inner, 'date-box', $iehint);
      }
      elseif ($i == $total_rows) {
        $output .= theme('calendar_month_row', $inner, 'single-day', $iehint);
        $iehint = 0;
        $max_singlerow_cnt = 0;
        $max_multirow_cnt = 0;
      }
      else {
        // Style all the columns into a row
        $output .= theme('calendar_month_row', $inner, 'multi-day');
      }
    }
    $curday = $final_day;
   
    // Add the row into the row array....
    $rows[] = array('data' => $output);
   
    $curday_date = date_format($curday, DATE_FORMAT_DATE);
    $curday_month = date_format($curday, 'n');
  } while ($curday_month == $month && $curday_date <= $view->date_info->max_date_date);
 
  // Merge the day names in as the first row.
  $rows = array_merge(array(calendar_week_header($view)), $rows);
  return $rows;
}
/**
 * Build one week row.
 */
function calendar_build_mini_week(&$curday, $view, $items, $check_month = FALSE) {
  $curday_date = date_format($curday, DATE_FORMAT_DATE);
  $weekdays = calendar_untranslated_days($items, $view);
  $today = date_format(date_now(date_default_timezone_name()), DATE_FORMAT_DATE);
  $month = date_format($curday, 'n');
  $week = date_week($curday_date);
  $first_day = variable_get('date_first_day', 0);
  // move backwards to the first day of the week
  $day_wday = date_format($curday, 'w');
  date_modify($curday, '-' . strval((7 + $day_wday - $first_day) % 7) . ' days');
  $curday_date = date_format($curday, DATE_FORMAT_DATE);
   
  // If we're displaying the week number, add it as the
  // first cell in the week.
  if (!empty($view->date_info->style_with_weekno) && !in_array($view->date_info->granularity, array('day', 'week'))) {
    $url = date_real_url($view, NULL, $view->date_info->year .'-W'. $week);
    if (!empty($view->date_info->display_types['week'])) {
      $weekno = l($week, $url, array('query' => !empty($view->date_info->append) ? $view->date_info->append : ''));
    }
    else {
      // Do not link week numbers, if Week views are disabled.
      $weekno = $week;
    }
    $rows[$week][] = array(
      'data' => $weekno,
      'id' => $view->name . '-weekno-' . $curday_date, 
      'class' => 'week');
  }
  for ($i = 0; $i < 7; $i++) {
    $curday_date = date_format($curday, DATE_FORMAT_DATE);
    $class = strtolower($weekdays[$i] . ' mini');
    if ($check_month && ($curday_date < $view->date_info->min_date_date || $curday_date > $view->date_info->max_date_date || date_format($curday, 'n') != $month)) {
      $class .= ' empty';
      $content = array(
        'date' => '',
        'datebox' => '',
        'empty' => theme('calendar_empty_day', $curday_date, $view),
        'link' => '',
        'all_day' => array(),
        'items' => array(),
        );
    }
    else {
      $content = calendar_build_day($curday, $view, $items);
      $class .= ($curday_date == $today ? ' today' : '') .
        ($curday_date < $today ? ' past' : '') .
        ($curday_date > $today ? ' future' : '') .
        (empty($items[$curday_date]) ? ' has-no-events' : ' has-events');
    }
   
    $rows[$week][] = array(
      'data' => $content,
      'class' => $class, 'id' => $view->name . '-' . $curday_date);
    date_modify($curday, '+1 day');
  }
  return $rows;
}
/**
 * Build one week row.
 */
function calendar_build_week(&$curday, $view, $items, $check_month = FALSE) {
  $curday_date = date_format($curday, DATE_FORMAT_DATE);
  $weekdays = calendar_untranslated_days($items, $view);
  $month = date_format($curday, 'n');
  $first_day = variable_get('date_first_day', 0);
 
  // Set up buckets
  $total_rows = 0;
  $multiday_buckets = array( array(), array(), array(), array(), array(), array(), array());
  $singleday_buckets = array( array(), array(), array(), array(), array(), array(), array());
 
  // move backwards to the first day of the week
  $day_wday = date_format($curday, 'w');
  date_modify($curday, '-' . strval((7 + $day_wday - $first_day) % 7) . ' days');
  $curday_date = date_format($curday, DATE_FORMAT_DATE);
   
  for ($i = 0; $i < 7; $i++) {
    if ($check_month && ($curday_date < $view->date_info->min_date_date || $curday_date > $view->date_info->max_date_date || date_format($curday, 'n') != $month)) {
      $class = strtolower($weekdays[$i]) .' empty';
      $singleday_buckets[$i][][] = array(
        'entry' => theme('calendar_empty_day', $curday_date, $view),
        'item' => NULL
      );
    }
    else {
      calendar_build_week_day($curday, $view, $items, $i, $multiday_buckets, $singleday_buckets);
    }
    $total_rows = max(count($multiday_buckets[$i]) + 1, $total_rows);
    date_modify($curday, '+1 day');
    $curday_date = date_format($curday, DATE_FORMAT_DATE);
  }
 
  $rows = array(
    'multiday_buckets' => $multiday_buckets,
    'singleday_buckets' => $singleday_buckets,
    'total_rows' => $total_rows);
  return $rows;
}
/**
 * Build the contents of a single day for the $rows results.
 */
function calendar_build_week_day($curday, $view, $items, $wday, &$multiday_buckets, &$singleday_buckets) {
  $curday_date = date_format($curday, DATE_FORMAT_DATE);
  $max_events = !empty($view->date_info->style_max_items) ? $view->date_info->style_max_items : 0;
  $hide = !empty($view->date_info->style_max_items_behavior) ? ($view->date_info->style_max_items_behavior == 'hide') : FALSE;
  $multiday_theme = ($view->date_info->style_multiday_theme == '1');
  $cur_cnt = 0;
  $total_cnt = 0;
  $types = array();
 
  // If we are hiding, count before processing further
  if ($max_events != CALENDAR_SHOW_ALL) {
    foreach ($items as $date => $day) {
      if ($date == $curday_date) {
        foreach ($day as $time => $hour) {
          foreach ($hour as $key => $item) {
            $total_cnt++;
            $types[$item->type] = $item;
          }
        }
      }
    }
  }
 
  // If we haven't already exceeded the max or we'll showing all, then process the items
  if ($max_events == CALENDAR_SHOW_ALL || !$hide || $total_cnt <= $max_events) {
    // Count currently filled items
    foreach ($multiday_buckets[$wday] as $bucket) {
      if (!$bucket['avail']) {
        $cur_cnt++;
      }
    }
   
    foreach ($items as $date => $day) {
      if ($date == $curday_date) {
        $count = 0;
        ksort($day);
        foreach ($day as $time => $hour) {
          foreach ($hour as $key => $item) {
            $count++;
           
            // Can we add an item?
            if ($max_events == CALENDAR_SHOW_ALL || $cur_cnt <= $max_events) {
              $all_day = $item->calendar_start_date == $item->calendar_end_date;
              $theme = isset($item->calendar_node_theme) ? $item->calendar_node_theme : 'calendar_'. $view->date_info->granularity .'_node';
   
              // Parse out date part
              $start_ydate = date_format($item->date_start, DATE_FORMAT_DATE);
              $end_ydate = date_format($item->date_end, DATE_FORMAT_DATE);
              $cur_ydate = date_format($curday, DATE_FORMAT_DATE);
             
              $is_multi_day = ($start_ydate < $cur_ydate || $end_ydate > $cur_ydate);
             
              // Does this event span multi-days?
              if ($multiday_theme && ($is_multi_day || $all_day)) {
               
                // If this the first day of the week, or is the start date of the multi-day event,
                // then record this item, otherwise skip over
                $day_no = date_format($curday, 'd');
                if ($wday == 0 || $start_ydate == $cur_ydate || ($view->date_info->granularity == 'month' && $day_no == 1) || ($all_day && !$is_multi_day)) {
                  $cur_cnt++;
                 
                  // Calculate the colspan for this event
 
                  // If the last day of this event exceeds the end of the current month or week,
                  // truncate the remaining days
                  $diff = date_difference($view->date_info->max_date, $curday, 'days');
                  $remaining_days = ($view->date_info->granularity == 'month') ? min(6 - $wday, $diff) : $diff - 1;                 
                  // The bucket_cnt defines the colspan.  colspan = bucket_cnt + 1
                  $days = date_difference($curday, $item->date_end, 'days');
                  $bucket_cnt = max(0, min($days, $remaining_days));
                 
                  // See if there is an avaiable slot to add an event.  This will allow
                  // an event to precede a row filled up by a previous day event
                  $avail = FALSE;
                  $bucket_index = count($multiday_buckets[$wday]);
                  for ($i = 0; $i < $bucket_index; $i++) {
                    if ($multiday_buckets[$wday][$i]['avail']) {
                      $bucket_index = $i;
                      break;
                    }
                  }
                 
                  // Add continuation attributes
                  $item->continuation =  ($item->date_start < $curday);
                  $item->continues = ( $days > $bucket_cnt );
                                 
                  // Assign the item to the available bucket
                  $multiday_buckets[$wday][$bucket_index] = array(
                    'colspan' => $bucket_cnt + 1,
                    'rowspan' => 1,
                    'filled' => TRUE,
                    'avail' => FALSE,
                    'all_day' => $all_day,
                    'item' => $item,
                    'wday' => $wday,
                    'entry' => theme($theme, $item, $view)
                  );
                 
                  // Block out empty buckets for the next days in this event for this week
                  for ($i = 0; $i < $bucket_cnt; $i++) {
                    $bucket = &$multiday_buckets[$i + $wday + 1];
                    $bucket_row_count = count($bucket);
                    $row_diff = $bucket_index - $bucket_row_count;
                   
                    // Fill up the preceding buckets - these are available for future
                    // events
                    for ( $j = 0; $j < $row_diff; $j++) {
                      $bucket[($bucket_row_count + $j) ] = array(
                        'entry' => '&nbsp;',
                        'colspan' => 1,
                        'rowspan' => 1,
                        'filled' => TRUE,
                        'avail' => TRUE,
                        'wday' => $wday,
                        'item' => NULL
                      );
                    }
                    $bucket[$bucket_index] = array(
                      'filled' => FALSE,
                      'avail' => FALSE
                    );
                  }
                }
              }
              else {
                $cur_cnt++;
                // Assign to single day bucket
                $singleday_buckets[$wday][$time][] = array(
                  'entry' => theme($theme, $item, $view),
                  'item' => $item,
                  'colspan' => 1,
                  'rowspan' => 1,
                  'filled' => TRUE,
                  'avail' => FALSE,
                  'wday' => $wday,
                );
              }
            }
            else {
              break;  // exceeded count
            }
          }
        }
      }
    }
  }
   
  // Add a more link if necessary
  if ($max_events != CALENDAR_SHOW_ALL && $total_cnt > 0 && $cur_cnt < $total_cnt) {
    $singleday_buckets[$wday][][] = array(
      'entry' => theme('calendar_'. $view->date_info->calendar_type .'_multiple_node', $curday_date, $total_cnt, $view, $types),
      'more_link' => TRUE,
      'item' => NULL
    );
  }
}
/**
 * Build the contents of a single day for the $rows results.
 */
function calendar_build_day($curday, $view, $items) {
  $curday_date = date_format($curday, DATE_FORMAT_DATE);
  $selected = FALSE;
  $max_events = !empty($view->date_info->style_max_items) ? $view->date_info->style_max_items : 0;
  $types = array();
  $inner = array();
  $all_day = array();
  $empty = '';
  $link = '';
  $count = 0;
  foreach ($items as $date => $day) {
    if ($date == $curday_date) {
      $count = 0;
      $selected = TRUE;
      ksort($day);
      foreach ($day as $time => $hour) {
        foreach ($hour as $key => $item) {
          $count++;
          $types[$item->type] = $item;
          if (!$view->date_info->mini && ($max_events == CALENDAR_SHOW_ALL || $count <= $max_events || ($count > 0 && $max_events == CALENDAR_HIDE_ALL))) {
            // Theme the item here unless this is a 'Day' or 'Week' view.
            // Day and week views need to do more processing before rendering
            // the item, so just past them the unrendered item.
            $theme = isset($item->calendar_node_theme) ? $item->calendar_node_theme : 'calendar_'. $view->date_info->granularity .'_node';
            if ($item->calendar_all_day) {
              $all_day[] = in_array($view->date_info->calendar_type, array('day', 'week')) ? $item : theme($theme, $item, $view);
            }
            else {
              $key = date_format($item->date_start, 'H:i:s');
              $inner[$key][] = in_array($view->date_info->calendar_type, array('day', 'week')) ? $item : theme($theme, $item, $view);
            }
          }
        }
      }
    }
  }
  ksort($inner);
  if (empty($inner) && empty($all_day)) {
    $empty = theme('calendar_empty_day', $curday_date, $view);
  }
  // We have hidden events on this day, use the theme('calendar_multiple_') to show a link.
  if ($max_events != CALENDAR_SHOW_ALL && $count > 0 && $count > $max_events && $view->date_info->calendar_type != 'day' && !$view->date_info->mini) {
    if ($view->date_info->style_max_items_behavior == 'hide' || $max_events == CALENDAR_HIDE_ALL) {
      $all_day = array();
      $inner = array();
    }
    $link = theme('calendar_'. $view->date_info->calendar_type .'_multiple_node', $curday_date, $count, $view, $types);
  }
   
  $content = array(
    'date' => $curday_date,
    'datebox' => theme('calendar_datebox', $curday_date, $view, $items, $selected),
    'empty' => $empty,
    'link' => $link,
    'all_day' => $all_day,
    'items' => $inner,
    );
  return $content;
}
