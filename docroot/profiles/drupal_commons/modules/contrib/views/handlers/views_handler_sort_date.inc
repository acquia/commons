<?php
// $Id: views_handler_sort_date.inc,v 1.1 2008/09/03 19:21:28 merlinofchaos Exp $

/**
 * Basic sort handler for dates.
 *
 * This handler enables granularity, which is the ability to make dates
 * equivalent based upon nearness.
 *
 * @ingroup views_sort_handlers
 */
class views_handler_sort_date extends views_handler_sort {
  function option_definition() {
    $options = parent::option_definition();

    $options['granularity'] = array('default' => 'second');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['granularity'] = array(
      '#type' => 'radios',
      '#title' => t('Granularity'),
      '#options' => array(
        'second' => t('Second'),
        'minute' => t('Minute'),
        'hour'   => t('Hour'),
        'day'    => t('Day'),
        'month'  => t('Month'),
        'year'   => t('Year'),
      ),
      '#description' => t('The granularity is the smallest unit to use when determining whether two dates are the same; for example, if the granularity is "Year" then all dates in 1999, regardless of when they fall in 1999, will be considered the same date.'),
      '#default_value' => $this->options['granularity'],
    );
  }

  /**
   * Called to add the sort to a query.
   */
  function query() {
    // When a exposed sort is by default ASC or DESC, we have to check if 
    // this value was modified. If not, we use the default value for this sort.
    if (!empty($this->options['exposed']) && !empty($this->view->exposed_input[$this->options['expose']['identifier']])) {
      $sort = drupal_strtolower($this->view->exposed_input[$this->options['expose']['identifier']]);
    }
    else {
      $sort = drupal_strtolower($this->options['order']);
    }
    
    $this->ensure_my_table();
    switch ($this->options['granularity']) {
      case 'second':
      default:
        $formula = NULL;
        break;
      case 'minute':
        $formula = views_date_sql_format('YmdHi', "$this->table_alias.$this->real_field");
        break;
      case 'hour':
        $formula = views_date_sql_format('YmdH', "$this->table_alias.$this->real_field");
        break;
      case 'day':
        $formula = views_date_sql_format('Ymd', "$this->table_alias.$this->real_field");
        break;
      case 'month':
        $formula = views_date_sql_format('Ym', "$this->table_alias.$this->real_field");
        break;
      case 'year':
        $formula = views_date_sql_format('Y', "$this->table_alias.$this->real_field");
        break;
    }

    // Ensure sort is valid and add the field.
    if (!empty($sort) && ($sort == 'asc' || $sort == 'desc')) {
      if ($formula) {
        $this->query->add_orderby(NULL, $formula, $sort, $this->table_alias . '_' . $this->field . '_' . $this->options['granularity']);
      }
      else {
        $this->query->add_orderby($this->table_alias, $this->real_field, $sort);
      }
    }
  }
}
