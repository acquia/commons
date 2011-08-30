<?php
// $Id: views_handler_sort.inc,v 1.2 2009/06/26 00:23:42 merlinofchaos Exp $
/**
 * @defgroup views_sort_handlers Views' sort handlers
 * @{
 * Handlers to tell Views how to sort queries
 */

/**
 * Base sort handler that has no options and performs a simple sort
 */
class views_handler_sort extends views_handler {

  /**
   * Determine if a sort can be exposed.
   */
  function can_expose() { return TRUE; }

  /**
   * Provide the basic form which calls through to subforms.
   * If overridden, it is best to call through to the parent,
   * or to at least make sure all of the functions in this form
   * are called.
   */
  function options_form(&$form, &$form_state) {
    if ($this->can_expose()) {
      $this->show_expose_button($form, $form_state);
    }
    $form['start'] = array('#value' => '<div class="clear-block">');
    $this->sort_form($form, $form_state);
    $form['end'] = array('#value' => '</div>');
    if ($this->can_expose()) {
      $this->show_expose_form($form, $form_state);
    }
  }

  /**
   * Simple validate handler
   */
  function options_validate(&$form, &$form_state) {
    $this->sort_validate($form, $form_state);
    if (!empty($this->options['exposed'])) {
      $this->expose_validate($form, $form_state);
    }
  }

  /**
   * Validate the sort form.
   */
  function sort_validate($form, &$form_state) { }

  /**
   * Perform any necessary changes to the form values prior to storage.
   * There is no need for this function to actually store the data.
   */
  function sort_submit($form, &$form_state) { }

  /**
   * Simple submit handler
   */
  function options_submit(&$form, &$form_state) {
    unset($form_state['values']['expose_button']); // don't store this.
    $this->sort_submit($form, $form_state);
    if (!empty($this->options['exposed'])) {
      $this->expose_submit($form, $form_state);
    }
  }

  /**
   * Provide a form for setting the sort.
   *
   * This may be overridden by child classes, and it must
   * define $form['order'];
   */
  function sort_form(&$form, &$form_state) {
    $options = $this->sort_options();
    if (!empty($options)) {
      $form['order'] = array(
        '#type' => 'radios',
        '#options' => $options,
        '#default_value' => $this->options['order'],
      );
    }
  }

  /**
   * Provide a list of options for the default sort form.
   * Should be overridden by classes that don't override sort_form
   */
  function sort_options() { return array(
    'unsorted' => t('Unsorted'),
    'ASC' => t('Sort ascending'), 
    'DESC' => t('Sort descending'),
    ); 
  }

  function expose_form_left(&$form, &$form_state) {
    $form['expose']['label'] = array(
      '#type' => 'textfield',
      '#default_value' => $this->options['expose']['label'],
      '#title' => t('Label'),
      '#size' => 40,
    );
    $form['expose']['identifier'] = array(
      '#type' => 'textfield',
      '#default_value' => $this->options['expose']['identifier'],
      '#title' => t('Sort identifier'),
      '#size' => 40,
      '#description' => t('This will appear in the URL after the ? to identify this sort. Cannot be blank.'),
    );
  }
  
  /**
   * Handle the 'left' side fo the exposed options form.
   */
  function expose_form_right(&$form, &$form_state) {

    $form['expose']['order'] = array(
      '#type' => 'value',
      '#value' => 'unsorted',
     );

    $form['expose']['label'] = array(
      '#type' => 'textfield',
      '#default_value' => $this->options['expose']['label'],
      '#title' => t('Label'),
      '#size' => 40,
    );
  }

  /**
   * Provide default options for exposed sorts.
   */
  function expose_options() {
    $this->options['expose'] = array(
      'order' => $this->options['order'],
      'label' => t('Sort by: ') . $this->ui_name(),
      'identifier' => $this->options['id'] .'_sort',
    );
  }

  /**
   * Validate the options form.
   */
  function expose_validate($form, &$form_state) {
    if (empty($this->options['expose']['identifier'])) {
      if (empty($form_state['values']['options']['expose']['identifier'])) {
        form_error($form['expose']['identifier'], t('The identifier is required if the sort is exposed.'));
      }
    }

    if (!empty($form_state['values']['options']['expose']['identifier']) && $form_state['values']['options']['expose']['identifier'] == 'value') {
      form_error($form['expose']['identifier'], t('This identifier is not allowed.'));
    }
  }
  
  /**
   * Render our chunk of the exposed sort form when selecting
   *
   * You can override this if it doesn't do what you expect.
   */
  function exposed_form(&$form, &$form_state) {
    if (empty($this->options['exposed'])) {
      return;
    }
    
    if (!empty($this->options['expose']['identifier'])) {
      $value = $this->options['expose']['identifier'];
      
      $this->sort_form($form, $form_state);
      $form[$value] = $form['order'];

      $this->exposed_translate($form[$value], 'order');

      unset($form['order']);
    }

  }

  /**
   * Make some translations to a form item to make it more suitable to
   * exposing.
   */
  function exposed_translate(&$form, $type) {
    if (!isset($form['#type'])) {
      return;
    }

    if ($form['#type'] == 'radios') {
      $form['#type'] = 'select';
    }
  }

  /**
   * Tell the renderer about our exposed form. This only needs to be
   * overridden for particularly complex forms. And maybe not even then.
   * 
   * @return
   *   An array with the following keys:
   *   - operator: The $form key of the operator. Set to NULL if no operator.
   *   - value: The $form key of the value. Set to NULL if no value.
   *   - label: The label to use for this piece.
   */
  function exposed_info() {
    if (empty($this->options['exposed'])) {
      return;
    }

    return array(
      'order' => $this->options['expose']['order'],
      'label' => $this->options['expose']['label'],
      'value' => $this->options['expose']['identifier'],
    );
  }

  /**
   * Check to see if input from the exposed sorts should change
   * the behavior of this sort.
   */
  function accept_exposed_input($input) {
    return TRUE;
  }

  function store_exposed_input($input, $status) {
    return TRUE;
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
    
    // Ensure sort is valid and add the field.
    if (!empty($sort) && ($sort == 'asc' || $sort == 'desc')) {
      $this->ensure_my_table();
      $this->query->add_orderby($this->table_alias, $this->real_field, $sort);
    }
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['exposed'] = array('default' => FALSE);
    $options['order'] = array('default' => 'unsorted');
    $options['identifier'] = array('default' => 'unsorted');

    return $options;
  }

  /**
   * Display whether or not the sort sort is ascending or descending
   */
  function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }
    switch ($this->options['order']) {
      case 'ASC':
      case 'asc':
        return t('asc');
        break;
      case 'DESC';
      case 'desc';
        return t('desc');
        break;
      default:
        return t('unsorted');
        break;
    }
  }

}

/**
 * A special handler to take the place of missing or broken handlers.
 */
class views_handler_sort_broken extends views_handler_sort {
  function ui_name($short = FALSE) {
    return t('Broken/missing handler');
  }

  function ensure_my_table() { /* No table to ensure! */ }
  function query() { /* No query to run */ }
  function options_form(&$form, &$form_state) {
    $form['markup'] = array(
      '#prefix' => '<div class="form-item description">',
      '#value' => t('The handler for this item is broken or missing and cannot be used. If a module provided the handler and was disabled, re-enabling the module may restore it. Otherwise, you should probably delete this item.'),
    );
  }

  /**
   * Determine if the handler is considered 'broken'
   */
  function broken() { return TRUE; }
}


/**
 * @}
 */
