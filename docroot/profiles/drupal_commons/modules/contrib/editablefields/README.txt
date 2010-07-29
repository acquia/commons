Thanks to Amitaibu for the following text, which may help some
people. This comes complete with some example code to cut'n'past into
the CCK and Views (if you have models installed to let you do that).


1. Create a content type.
Content name = Editable

2. Create a View:
Page URL = EditFields
View Type = Editable list
Fields = Title, Caption.
In the caption set Option=Editable
Filter = Only Editable content type.
3. Create some nodes from the 'Editable' content type
4. Invoke the view - the caption field can be edited.

For the lazy among us you can import the CCK and Views:
CCK (Enable "Content Copy" module):
$content[type]  = array (
  'name' => 'Editable',
  'type' => 'editable',
  'description' => 'Editable Fields demo',
  'title_label' => 'Title',
  'body_label' => '',
  'min_word_count' => '0',
  'help' => '',
  'node_options' =>
  array (
    'status' => true,
    'promote' => true,
    'sticky' => false,
    'revision' => false,
  ),
  'comment' => '2',
  'old_type' => 'editable',
  'orig_type' => '',
  'module' => 'node',
  'custom' => '1',
  'modified' => '1',
  'locked' => '0',
);
$content[fields]  = array (
  0 =>
  array (
    'widget_type' => 'text',
    'label' => 'Caption',
    'weight' => '0',
    'rows' => '1',
    'description' => '',
    'default_value_widget' =>
    array (
      'field_caption' =>
      array (
        0 =>
        array (
          'value' => '',
        ),
      ),
    ),
    'default_value_php' => '',
    'group' => false,
    'required' => '0',
    'multiple' => '0',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'field_name' => 'field_caption',
    'field_type' => 'text',
    'module' => 'text',
    'default_value' =>
    array (
      0 =>
      array (
        'value' => '',
      ),
    ),
  ),
);

Views:
  $view = new stdClass();
  $view->name = 'Editable_Fields';
  $view->description = 'Editable_Fields Views demo';
  $view->access = array (
);
  $view->view_args_php = '';
  $view->page = TRUE;
  $view->page_title = '';
  $view->page_header = '';
  $view->page_header_format = '1';
  $view->page_footer = '';
  $view->page_footer_format = '1';
  $view->page_empty = '';
  $view->page_empty_format = '1';
  $view->page_type = 'editablefields_list';
  $view->url = 'editablefields';
  $view->use_pager = TRUE;
  $view->nodes_per_page = '10';
  $view->sort = array (
  );
  $view->argument = array (
  );
  $view->field = array (
    array (
      'tablename' => 'node',
      'field' => 'title',
      'label' => '',
      'handler' => 'views_handler_field_nodelink',
      'options' => 'link',
    ),
    array (
      'tablename' => 'node_data_field_caption',
      'field' => 'field_caption_value',
      'label' => '',
      'handler' => 'content_views_field_handler_group',
      'options' => 'editable',
    ),
  );
  $view->filter = array (
    array (
      'tablename' => 'node',
      'field' => 'status',
      'operator' => '=',
      'options' => '',
      'value' => '1',
    ),
    array (
      'tablename' => 'node',
      'field' => 'type',
      'operator' => 'OR',
      'options' => '',
      'value' => array (
  0 => 'editable',
),
    ),
  );
  $view->exposed_filter = array (
  );
  $view->requires = array(node, node_data_field_caption);
  $views[$view->name] = $view;