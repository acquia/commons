<?php

/**
 * Minified node creation form.
 */
class commons_bw_handler_node_partial_form extends views_handler_area {

  function option_definition() {
    $options = parent::option_definition();
    $options['bundle'] = array('default' => NULL);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $bundles = og_get_all_group_content_bundle();

    $form['bundle'] = array(
      '#type' => 'select',
      '#title' => t('Node type'),
      '#options' => !empty($bundles['node']) ? $bundles['node'] : array(),
      '#default_value' => $this->options['bundle'],
      '#required' => TRUE,
    );
  }

  function render($empty = FALSE) {
    $cache = &drupal_static(__METHOD__, array());

    $bundle = $this->options['bundle'];
    $group_id = !empty($this->view->args[0]) ? $this->view->args[0] : NULL;

    // Verify content creation access.
    $permission = "create $bundle content";
    if ($group_id && !og_user_access('node', $group_id, $permission)) {
      return;
    }
    elseif (!user_access($permission)) {
      return;
    }

    // Avoid rendering a form for the same bundle twice; Instead, mark that it
    // should be moved to this position from previously rendered form.
    // See partial_node_form.js.
    if (!empty($cache[$bundle])) {
      return '<div class="partial-node-form-placeholder" data-bundle="' . $bundle . '"></div>';
    }
    $cache[$bundle] = TRUE;

    $form = drupal_get_form("commons_bw_partial_node_form__$bundle", $bundle, $group_id);
    return render($form);
  }
}
