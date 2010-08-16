<?php
class notifications_views_handler_relationship extends views_handler_relationship {
  function query() {
    $oldfield = $this->field;
    $this->field = $this->real_field;
    parent::query();
    $this->field = $oldfield;
  }
}
