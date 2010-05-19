<?php
// $Id: ajax.inc,v 1.14.2.2 2009/12/07 18:57:44 merlinofchaos Exp $

/**
 * @file
 * Utilize the CTools AJAX responder.
 *
 * The AJAX responder is a javascript tool to make it very easy to do complicated
 * operations as a response to AJAX requests. When links are attached to the ajax
 * responder, the server sends back a packet of JSON data; this packet is an
 * array of commands to carry out.
 *
 * The command names correlate to functions in the responder space, making it
 * relatively easy for applications to provide their own commands to do whatever
 * spiffy functionality is necessary.
 *
 * Each command is an object. $object->command is the type of command and
 * will be used to find the function (it will correllate directly to
 * a function in the Drupal.CTools.AJAX.Command space). The object can
 * contain any other data that the command needs to process.
 *
 * Built in commands include:
 * - replace
 *   - selector: The CSS selector. This can be any selector jquery uses in $().
 *   - data: The data to use with the jquery replace() function.
 *
 * - prepend
 *   - selector: The CSS selector. This can be any selector jquery uses in $().
 *   - data: The data to use with the jquery prepend() function.
 *
 * - append
 *   - selector: The CSS selector. This can be any selector jquery uses in $().
 *   - data: The data to use with the jquery append() function.
 *
 * - after
 *   - selector: The CSS selector. This can be any selector jquery uses in $().
 *   - data: The data to use with the jquery after() function.
 *
 * - before
 *   - selector: The CSS selector. This can be any selector jquery uses in $().
 *   - data: The data to use with the jquery before() function.
 *
 * - remove
 *   - selector: The CSS selector. This can be any selector jquery uses in $().
 *
 * - changed
 *   - selector: The CSS selector. This selector will have 'changed' added as a clas.
 *   - star: If set, will add a star to this selector. It must be within the 'selector' above.
 *
 * - alert
 *   - title: The title of the alert.
 *   - data: The data in the alert.
 *
 * - css
 *   - selector: The CSS selector to add CSS to.
 *   - argument: An array of 'key': 'value' CSS selectors to set.
 *
 * - attr
 *   - selector: The CSS selector. This can be any selector jquery uses in $().
 *   - name: The name or key of the data attached to this selector.
 *   - value: The value of the data.
 *
 * - settings
 *   - argument: An array of settings to add to Drupal.settings via $.extend
 *
 * - data
 *   - selector: The CSS selector. This can be any selector jquery uses in $().
 *   - name: The name or key of the data attached to this selector.
 *   - value: The value of the data. Not just limited to strings can be any format.
 *
 * - redirect
 *   - url: The url to be redirected to. This can be an absolute URL or a Drupal path.
 *
 * - reload
 *
 * - submit
 *   - selector: The CSS selector to identify the form for submission. This can
 *     be any selector jquery uses in $().
 *
 * Commands are usually created with a couple of helper functions, so they
 * look like this:
 *
 * @code
 *   $commands = array();
 *   $commands[] = ctools_ajax_command_replace('#ctools-object-1', 'some html here');
 *   $commands[] = ctools_ajax_command_changed('#ctools-object-1');
 *   ctools_ajax_render($commands); // this function exits.
 * @endcode
 */

/**
 * Render an image as a button link. This will automatically apply an AJAX class
 * to the link and add the appropriate javascript to make this happen.
 *
 * @param $image
 *   The path to an image to use that will be sent to theme('image') for rendering.
 * @param $dest
 *   The destination of the link.
 * @param $alt
 *   The alt text of the link.
 * @param $class
 *   Any class to apply to the link. @todo this should be a options array.
 */
function ctools_ajax_image_button($image, $dest, $alt, $class = '') {
  return ctools_ajax_text_button(theme('image', $image), $dest, $alt, $class);
}

/**
 * Render text as a link. This will automatically apply an AJAX class
 * to the link and add the appropriate javascript to make this happen.
 *
 * Note: 'html' => true so be sure any text is vetted! Chances are these kinds of buttons will
 * not use user input so this is a very minor concern.
 *
 * @param $image
 *   The path to an image to use that will be sent to theme('image') for rendering.
 * @param $dest
 *   The destination of the link.
 * @param $alt
 *   The alt text of the link.
 * @param $class
 *   Any class to apply to the link. @todo this should be a options array.
 * @param $type
 *   A type to use, in case a different behavior should be attached. Defaults
 *   to ctools-use-ajax.
 */
function ctools_ajax_text_button($text, $dest, $alt, $class = '', $type = 'ctools-use-ajax') {
  return l($text, $dest, array('html' => TRUE, 'attributes' => array('class' => "$type $class", 'title' => $alt)));
}

/**
 * Create a command array for the error case.
 */
function ctools_ajax_command_error($error = '') {
  return array(
    'command' => 'alert',
    'title' => t('Error'),
    'text' => $error ? $error : t('Server reports invalid input error.'),
  );
}

/**
 * Create a replace command for the AJAX responder.
 *
 * The replace command will replace a portion of the current document
 * with the specified HTML.
 *
 * @param $selector
 *   The CSS selector. This can be any selector jquery uses in $().
 * @param $html
 *   The data to use with the jquery replace() function.
 */
function ctools_ajax_command_replace($selector, $html) {
  return array(
    'command' => 'replace',
    'selector' => $selector,
    'data' => $html,
  );
}

/**
 * Set the HTML of a given selector to the given data.
 *
 * @param $selector
 *   The CSS selector. This can be any selector jquery uses in $().
 * @param $html
 *   The data to use with the jquery replace() function.
 */
function ctools_ajax_command_html($selector, $html) {
  return array(
    'command' => 'html',
    'selector' => $selector,
    'data' => $html,
  );
}

/**
 * Create a prepend command for the AJAX responder.
 *
 * This will prepend the HTML to the specified selector.
 *
 * @param $selector
 *   The CSS selector. This can be any selector jquery uses in $().
 * @param $html
 *   The data to use with the jquery prepend() function.
 */
function ctools_ajax_command_prepend($selector, $html) {
  return array(
    'command' => 'prepend',
    'selector' => $selector,
    'data' => $html,
  );
}

/**
 * Create an append command for the AJAX responder.
 *
 * This will append the HTML to the specified selector.
 *
 * @param $selector
 *   The CSS selector. This can be any selector jquery uses in $().
 * @param $html
 *   The data to use with the jquery append() function.
 */
function ctools_ajax_command_append($selector, $html) {
  return array(
    'command' => 'append',
    'selector' => $selector,
    'data' => $html,
  );
}

/**
 * Create an after command for the AJAX responder.
 *
 * This will add the HTML after the specified selector.
 *
 * @param $selector
 *   The CSS selector. This can be any selector jquery uses in $().
 * @param $html
 *   The data to use with the jquery after() function.
 */
function ctools_ajax_command_after($selector, $html) {
  return array(
    'command' => 'after',
    'selector' => $selector,
    'data' => $html,
  );
}

/**
 * Create a before command for the AJAX responder.
 *
 * This will add the HTML before the specified selector.
 *
 * @param $selector
 *   The CSS selector. This can be any selector jquery uses in $().
 * @param $html
 *   The data to use with the jquery before() function.
 */
function ctools_ajax_command_before($selector, $html) {
  return array(
    'command' => 'before',
    'selector' => $selector,
    'data' => $html,
  );
}

/**
 * Create a remove command for the AJAX responder.
 *
 * This will remove the specified selector and everything within it.
 *
 * @param $selector
 *   The CSS selector. This can be any selector jquery uses in $().
 */
function ctools_ajax_command_remove($selector) {
  return array(
    'command' => 'remove',
    'selector' => $selector,
  );
}

/**
 * Create a changed command for the AJAX responder.
 *
 * This will mark an item as 'changed'.
 *
 * @param $selector
 *   The CSS selector. This can be any selector jquery uses in $().
 * @param $star
 *   An optional CSS selector which must be inside $selector. If specified,
 *   a star will be appended.
 */
function ctools_ajax_command_changed($selector, $star = '') {
  return array(
    'command' => 'changed',
    'selector' => $selector,
    'star' => $star,
  );
}

/**
 * Create a changed command for the AJAX responder.
 *
 * This will mark an item as 'changed'.
 *
 * @param $selector
 *   The CSS selector. This can be any selector jquery uses in $().
 * @param $argument
 *   An array of key: value pairs to set in the CSS for the selector.
 */
function ctools_ajax_command_css($selector, $argument) {
  return array(
    'command' => 'css',
    'selector' => $selector,
    'argument' => $argument,
  );
}

/**
 * Create a settings command for the AJAX responder.
 *
 * This will extend Drupal.settings with the given array.
 *
 * @param $argument
 *   An array of key: value pairs to add to the settings.
 */
function ctools_ajax_command_settings($argument) {
  return array(
    'command' => 'settings',
    'argument' => $argument,
  );
}

/**
 * Create a data command for the AJAX responder.
 *
 * This will attach the name=value pair of data to the selector via
 * jquery's data cache.
 *
 * @param $selector
 *   The CSS selector. This can be any selector jquery uses in $().
 * @param $name
 *   The name or key: of the data attached to this selector.
 * @param $value
 *  The value of the data. Not just limited to strings can be any format.
 */
function ctools_ajax_command_data($selector, $name, $value) {
  return array(
    'command' => 'data',
    'selector' => $selector,
    'name' => $name,
    'value' => $value,
  );
}

 /**
  * Set a single property to a value, on all matched elements.
  *
  * @param $selector
  *   The CSS selector. This can be any selector jquery uses in $().
  * @param $name
  *   The name or key: of the data attached to this selector.
  * @param $value
  *  The value of the data.
  */
 function ctools_ajax_command_attr($selector, $name, $value) {
   return array(
     'command' => 'attr',
     'selector' => $selector,
     'name' => $name,
     'value' => $value,
   );
 }

/**
 * Force a table to be restriped.
 *
 * This is usually used after a table has been modifed by a replace or append
 * command.
 *
 * @param $selector
 *   The CSS selector. This can be any selector jquery uses in $().
 */
function ctools_ajax_command_restripe($selector) {
  return array(
    'command' => 'restripe',
    'selector' => $selector,
  );
}

/**
 * Force a client-side redirect.
 *
 * @param $url
 *   The url to be redirected to. This can be an absolute URL or a
 *   Drupal path.
 */
function ctools_ajax_command_redirect($url) {
  return array(
    'command' => 'redirect',
    'url' => url($url),
  );
}

/**
 * Force a reload of the current page.
 */
function ctools_ajax_command_reload() {
  return array(
    'command' => 'reload',
  );
}

/**
 * Submit a form.
 *
 * This is useful for submitting a parent form after a child form has finished
 * processing in a modal overlay.
 *
 * @param $selector
 *   The CSS selector to identify the form for submission. This can be any
 *   selector jquery uses in $().
 */
function ctools_ajax_command_submit($selector) {
  return array(
    'command' => 'submit',
    'selector' => $selector,
  );
}

/**
 * Render a commands array into JSON and immediately hand this back
 * to the AJAX requester.
 */
function ctools_ajax_render($commands = array()) {
  if (!empty($_REQUEST['ctools_multipart'])) {
    // We don't use drupal_json here because the header is not true. We're not really
    // returning JSON, strictly-speaking, but rather JSON content wrapped in a <textarea>
    // as per the "file uploads" example here: http://malsup.com/jquery/form/#code-samples
    echo '<textarea>' . drupal_to_js($commands) . '</textarea>';
  }
  else {
    drupal_json($commands);
  }
  exit;
}

/**
 * Send an error response back via AJAX and immediately exit.
 */
function ctools_ajax_render_error($error = '') {
  $commands = array();
  $commands[] = ctools_ajax_command_error($error);
  ctools_ajax_render($commands);
}

/**
 * Associate a URL to a form element with a hidden form.
 *
 * This is a helper function to easily associate a URL with a form element
 * which can be used for different ajax functionality.
 *
 * You would call this function on a form element in the form function like this:
 *
 * @code
 *   $form['example'] = array(
 *     '#title' => t('Example'),
 *     '#type' => 'select',
 *     '#options' => array(1 => 'One', 2 => 'Two', 3 => 'Three'),
 *     '#default_value' => 1,
 *   );
 *   ctools_ajax_associate_url_to_element($form, $form['example'], 'example/ajax/urlpath');
 * @endcode
 *
 * The AJAX request will POST the value of the form element in the "ctools_changed" parameter.
 *
 * @param &$form
 *   Reference to the form element. This is required to have the #id and #attribute
 *   elements populated and to create the hidden form element for each select.
 * @param &$form_element
 *   The form element we are going to take action on.
 * @param $dest
 *   The URL to associate the form element to.
 * @param $type
 *   A type to use, in case a different behavior should be attached. Defaults
 *   to ctools-use-ajax.
 */
function ctools_ajax_associate_url_to_element(&$form, &$form_element, $dest, $type = 'ctools-use-ajax') {
  drupal_add_js('misc/jquery.form.js', 'core');
  if (!isset($form_element['#id'])) {
    //Create a unique ID to associate $form_element and hidden elements since we dont have an ID
    $form_element['#id'] = uniqid('ctools-ajax-url-');

    if (empty($form_element['#attributes']['class'])) {
      $form_element['#attributes']['class'] = $type;
    }
    else {
      $form_element['#attributes']['class'] .= " $type";
    }
  }

  //Add hidden form element to hold base URL
  $form[$form_element['#id'] . '-url'] = array(
    '#type' => 'hidden',
    '#value' => $dest,
    '#attributes' => array('class' =>  $form_element['#id'] . '-url'),
  );
}
