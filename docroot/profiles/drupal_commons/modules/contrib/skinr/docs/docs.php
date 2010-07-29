<?php
// $Id: docs.php,v 1.1 2009/06/11 05:34:34 jgirlygirl Exp $
/**
 * @file
 * This file contains no working PHP code; it exists to provide additional documentation
 * for doxygen as well as to document hooks in the standard Drupal manner.
 */

/**
 * @mainpage Skinr API Manual
 *
 * Topics:
 * - @ref skinr_hooks
 */

/**
 * @defgroup skinr_hooks Skinrs hooks
 * @{
 * Hooks that can be implemented by other modules in order to implement the
 * Skinr API.
 */

/**
 * Configure Skinr for this module.
 *
 * This hook should be placed in MODULENAME.skinr.inc and it will be auto-loaded.
 * This must either be in the same directory as the .module file or in a subdirectory
 * named 'includes'.
 *
 * The configuration info is keyed by the MODULENAME. In the case of $data['block']
 * 'block' is the name of the module.
 *
 * There are two section to the configuration array:
 * - When you specify a "form", Skinr will insert its skins selector into the form
 *   with the specified form_id. Example: $data[MODULENAME]['form'][FORM_ID] = ...
 *   You can specify multiple forms that Skinr should add its skins selector to. A
 *   good example where this would be needed is blocks where you have a different
 *   form_id for adding a new block than when editing an existing block.
 * - When you specify "preprocess", Skinr will create a $vars['skinr'] variable
 *   containing the appropriate skin classes for the specified preprocess hook.
 *   Example: $data[MODULENAME]['preprocess'][PREPROCESS_HOOK] = ...
 *
 * Form options:
 * - "index_handler" is required. It specifies a function that returns an index where
 *   Skinr can find the values in its data structure.
 * - "access_handler" specifies a function that returns TRUE if you wish to grant access
 *   to skinr, or FALSE if not.
 * - "data_handler" specifies a function that returns the data used to populate the form.
 *   This is useful in cases where a module caches data (like panels and views) and has
 *   an option to cancel changes.
 * - "submit_handler" specifies a function that process the form data and saves it.
 * - "preprocess_hook" is required. Each skin states which preprocess hooks it will
 *   work for. This parameter will limit the available skins by the specified
 *   preprocess hook.
 * - "title" overrides the default title on the Skinr fieldset.
 * - "description" overrides the default description that provides additional
 *   information to the user about this Skinr selector.
 * - "weight" overrides the order where Skinrs selector appears on the form.
 * - "collapsed" sets whether the fieldset appears collapsed or not. Defaults to TRUE.
 * - "selector_weight" overrides the weight of the selector field inside the fieldset.
 *   This is useful, for instance, if you have multiple modules add selectors to the
 *   same form.
 * - "selector_title" overrides the title of the selector field inside the fieldset.
 *
 * Preprocess options:
 * - "indexhandler" is required. It specifies a function that returns an index where
 *   Skinr can find the values in its data structure.
 */
function hook_skinr_data() {
  $data['example']['form']['block_admin_configure'] = array(
    'index_handler' => 'example_skinr_index_handler',
    'preprocess_hook' => 'block',
    'title' => t('Skinr settings'),
    'description' => t('Here you can manage which Skinr styles, if any, you want to apply.'),
    'weight' => 1,
    'collapsed' => TRUE,
    'selector_weight' => 0,
    'selector_title' => t('Choose Skinr Style(s)'),
  );
  $data['example']['form']['block_add_block_form'] = array(
    'index_handler' => 'example_skinr_index_handler',
    'title' => t('Skinr settings'),
    'description' => t('Here you can manage which Skinr styles, if any, you want to apply to this block.'),
    'weight' => -10,
    'collapsed' => FALSE,
  );

  $data['example']['preprocess']['block'] = array(
    'index_handler' => 'block_skinr_preprocess_handler_block',
  );

  return $data;
}

/**
 * Register Skinr API information. This is required for your module to have
 * its include files loaded.
 *
 * The full documentation for this hook is in the advanced help.
 */
function hook_skinr_api() {
  return array(
    'api' => 1,
    'path' => drupal_get_path('module', 'modulename'),
  );
}

/**
 * @}
 */
