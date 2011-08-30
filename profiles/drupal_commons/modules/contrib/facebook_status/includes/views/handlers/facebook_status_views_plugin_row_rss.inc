<?php

/**
 * @file
 *   Contains the FBSS RSS row style plugin.
 */

/**
 * Formats a status as an RSS item.
 */
class facebook_status_views_plugin_row_rss extends views_plugin_row {
  // Basic properties that let the row style follow relationships.
  var $base_table = 'facebook_status';
  var $base_field = 'sid';

  function render($row) {
    global $base_url;

    $sid = $row->{$this->field_alias};
    if (!is_numeric($sid)) {
      return;
    }

    // Load the specified status:
    $status = facebook_status_load($sid);
    if (empty($status)) {
      return;
    }
    $sender = _facebook_status_user_load($status->sender);
    $context = facebook_status_determine_context($status->type);
    $recipient = $context['handler']->load_recipient($status->recipient);
    $message = _facebook_status_run_filter($status->message);
    if (variable_get('facebook_status_nl2br', 0)) {
      $message = nl2br($message);
    }
    $args = array(
      '@sender' => (module_exists('realname') && !empty($sender->realname)) ? $sender->realname : $sender->name,
      '@recipient' => $context['handler']->recipient_name($recipient),
      '!message' => filter_xss($status->message, array()),
    );

    $item = new stdClass();
    $item->title = ($sender->uid == $status->recipient && $status->type == 'user') ? t('@sender: !message', $args) : t('@sender &raquo; @recipient: !message', $args);
    $item->link = url("statuses/$status->sid", array('absolute' => TRUE));
    $item->sid = $status->sid;
    $item->description = $message;

    $item->elements = array(
      array('key' => 'pubDate', 'value' => gmdate('r', $status->created)),
      array(
        'key' => 'dc:creator',
        'value' => check_plain($sender->name),
        'namespace' => array('xmlns:dc' => 'http://purl.org/dc/elements/1.1/'),
      ),
      array(
        'key' => 'guid',
        'value' => $status->sid . ' at ' . $base_url,
        'attributes' => array('isPermaLink' => 'false')
      ),
    );

    foreach ($item->elements as $element) {
      if (isset($element['namespace'])) {
        $this->view->style_plugin->namespaces = array_merge($this->view->style_plugin->namespaces, $element['namespace']);
      }
    }

    return theme($this->theme_functions(), $this->view, $this->options, $item);
  }
}
