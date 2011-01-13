<?php
// $Id: chart_views_plugin_style_chart.inc,v 1.1 2010/06/27 18:36:15 ezrag Exp $
/**
 * @file
 * Drupal Chart API Views Integration. 
 * @Based on the Charts module's Views integration
 */

/**
 * Style plugin to render view as a chart.
 *
 * @ingroup views_style_plugins
 */
class chart_views_plugin_style_chart extends views_plugin_style {
  /**
   * Set default options.
   */
  function options(&$options) {
    // Get the default chart values
    $options['aggregation_field'] = '';
    $options['calc_fields']       = array();
    $options['calc']              = 'COUNT';
    $options['precision']         = 2;
  }

  /**
   * Generate a form for setting options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['type'] = array(
      '#default_value'  => 'bhs',
      '#options'        => chart_types(),
      '#required'       => TRUE,
      '#type'           => 'radios',
    );
    $form['width'] = array(
      '#default_value'  => 600,
      '#description'    => t('The chart width, in pixels'),
      '#required'       => TRUE,
      '#size'           => 8,
      '#type'           => 'textfield',
      '#title'          => t('Width'),
    );
    $form['height'] = array(
      '#default_value'  => 400,
      '#description'    => t('The chart height, in pixels'),
      '#required'       => TRUE,
      '#size'           => 8,
      '#type'           => 'textfield',
      '#title'          => t('Height'),
    );
    // Views Calc related fields
    $form['aggregation_field'] = array(
      '#type'           => 'select',
      '#title'          => t('Legend field'),
      '#options'        => $this->aggregated_field_options(),
      '#default_value'  => $this->options['aggregation_field'],
      '#description'    => t('Select a field to aggreagate the results on.')
      );
    $form['values_legend'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show values in legend'),
      '#default_value' => $this->options['values_legend'],
      '#description' => t('If checked, calculated values will be appended in the chart legend.'),
    );
    $form['calc_fields'] = array(
      '#type'           => 'select',
      '#title'          => t('Operation field'),
      '#options'        => $this->aggregated_field_options(),
      '#default_value'  => $this->calc_fields(),
      '#multiple'       => TRUE,
      '#description'    => t('Select field to perform computations on.')
    );
    $form['calc'] = array(
      '#type'           => 'select',
      '#title'          => t('Operation'),
      '#options'        => $this->calc_options(),
      '#default_value'  => $this->options['calc'],
    );
  }

  /**
   * Generate a form for setting options.
   */
  function options_submit(&$form, &$form_state) {
    $chart = &$form_state['values']['style_options']['chart'];
    foreach (element_children($chart) as $index) {
      $chart['#'. $index] = $chart[$index];
      unset($chart[$index]);
    }
  }

  /**
   * Views Calc operation.
   */
  function calc_options() {
    return array(
      ''      => t('None'),
      'SUM'   => t('Sum'),
      'COUNT' => t('Count'),
      'AVG'   => t('Average'),
      'MIN'   => t('Minimum'),
      'MAX'   => t('Maximum'),
    );
  }

  /**
   * Create an options array of available fields from this view.
   */
  function aggregated_field_options() {
    $field_names = array();
    $handlers = $this->display->handler->get_handlers('field');
    foreach ($handlers as $field => $handler) {
      if ($label = $handler->label()) {
        $field_names[$field] = $label;
      }
      else {
        $field_names[$field] = $handler->ui_name();
      }
    }
    return $field_names;
  }

  /**
   * Make sure calc_fields is always an array, even when not multiple.
   */
  function calc_fields() {
    $calc_fields = (array) $this->options['calc_fields'];
    return array_values($calc_fields);
  }

  /**
   * Define and display a chart from the grouped values.
   */
  function render() {
    // Get chart settings from options form.
    // Get values from rows.
    //drupal_set_message(dprint_r($this->view->field, TRUE));
    foreach ($this->calc_fields() as $calc) {
      foreach ($this->view->result as $row) {
        foreach ($this->view->field as $key => $field) {
          if ($key == $this->options['aggregation_field']) {
            $legend_field = array_key_exists($calc, $this->view->field) ? $this->view->field[$calc] : NULL;
            $legend = !empty($legend_field->options['label']) ? $legend_field->options['label'] : NULL;
            if ($this->options['show_legend']) {
              $data[$calc]['#legend'] = $legend;
            }
            $data[] = $row->$calc;
            $label = strip_tags(theme_views_view_field($this->view, $this->view->field[$key], $row));
            if ($this->options['values_legend']) {
              $label .=  ' '.$row->$calc;
            }
            if ($label != $last_label) {
              $labels[] = $label;
              $last_label = $label;
            }
            else {
              $labels[] = '';
            }
            $data_colors[] = chart_unique_color($label);
          }
        }
      }
    }
    $chart['#data'] = $data;
    $chart['#labels'] = $labels;
    $chart['#type'] = $this->options['type'];
    $chart['#chart_id'] = $this->view->name;
    $chart['#size']['#width'] = $this->options['width'];
    $chart['#size']['#height'] = $this->options['height'];
    $chart['#data_colors'] = $data_colors;

    //Return the rendered chart.
    return chart_render($chart);
  }

  /**
   * Custom SQL query change.
   */
  function query() {
    parent::query();

    // Clear the fields out, we'll replace them with calculated values.
    $this->view->query->clear_fields();
    // Clear out any sorting, it can create unexpected results
    // when Views adds aggregation values for the sorts.
    $this->view->query->orderby = array();

    // Add the grouping information to the query.
    // Field setting of array('aggregate' => TRUE) tells Views not to force
    // another aggregation in for this field.

    foreach ($this->view->field as $field) {
      $query_field = substr($field->field, 0, 3) == 'cid' ? $field->definition['calc'] : $field->table .'.'. $field->field;
      $query_alias = $field->field_alias;

      // Add the aggregation.
      if ($field->field == $this->options['aggregation_field']) {
        $this->view->query->add_orderby(NULL, NULL, 'asc', $query_alias);
        $this->view->query->add_groupby($query_field);
        if (substr($field->field, 0, 3) == 'cid') {
          $this->view->query->add_field(NULL, $query_field, $field->field, array('aggregate' => TRUE));
        }
        else {
          $this->view->query->add_field($field->table, $field->field, NULL, array('aggregate' => TRUE));
        }
      }
      // Add computed values.
      if (in_array($field->field, $this->calc_fields())) {
        $sql = "ROUND(". $this->options['calc'] ."($query_field), ". $this->options['precision'] .")";
        $this->view->query->add_field(NULL, $sql, $field->field, array('aggregate' => TRUE));

        // TODO This part is not relationship-safe, needs additional work
        // to join in the right table if the computation is done
        // on a field that comes from a relationship.

        // Make sure the table with the right alias name is available
        // (it might have been dropped during Views optimizations.)
        $this->view->query->add_table($field->table);
      }
    }
  }
}
