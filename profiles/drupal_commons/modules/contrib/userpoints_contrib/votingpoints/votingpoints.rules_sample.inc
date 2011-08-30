<?php
//$Id: votingpoints.rules_sample.inc,v 1.1 2009/01/29 17:36:04 kbahey Exp $

/**
 * Implementation of hook_rules_actions_default
 */
function votingpoints_rules_defaults() {
  return array (
    'rules' => 
    array (
      'rules_1' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_comment_insert',
        '#label' => 'Points given when commenting an application or idea',
        '#active' => 1,
        '#weight' => '0',
        '#status' => 'custom',
        '#conditions' => 
        array (
          0 => 
          array (
            '#info' => 
            array (
              'label' => 'commented content is Application Shop or Forum topic',
              'arguments' => 
              array (
                'node' => 
                array (
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
              'help' => 'Evaluates to TRUE, if the given content has one of the selected content types.',
            ),
            '#name' => 'rules_condition_content_is_type',
            '#settings' => 
            array (
              'type' => 
              array (
                'application' => 'application',
                'forum' => 'forum',
              ),
              '#argument map' => 
              array (
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
            '#weight' => 0,
          ),
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Grants points to a acting user',
              'label callback' => false,
              'arguments' => 
              array (
                'user' => 
                array (
                  'type' => 'user',
                  'label' => 'User',
                ),
              ),
              'module' => 'Userpoints',
              'eval input' => 
              array (
                0 => 'points',
              ),
            ),
            '#name' => 'userpoints_action_grant_points',
            '#settings' => 
            array (
              'points' => '1',
              '#argument map' => 
              array (
                'user' => 'user',
              ),
            ),
            '#type' => 'action',
          ),
          1 => 
          array (
            '#type' => 'action',
            '#settings' => 
            array (
              'points' => '1',
              '#argument map' => 
              array (
                'node_author' => 'user',
              ),
            ),
            '#name' => 'userpoints_action_grant_points',
            '#info' => 
            array (
              'label' => 'Grants points to a commented comment author',
              'label callback' => false,
              'arguments' => 
              array (
                'user' => 
                array (
                  'type' => 'user',
                  'label' => 'User',
                ),
              ),
              'module' => 'Userpoints',
              'eval input' => 
              array (
                0 => 'points',
              ),
            ),
            '#weight' => 0,
          ),
        ),
      ),
      'rules_2' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Points given when creating application for a user',
        '#active' => 1,
        '#weight' => '0',
        '#status' => 'custom',
        '#conditions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Content has type application',
              'label callback' => false,
              'arguments' => 
              array (
                'node' => 
                array (
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
              'help' => 'Evaluates to TRUE, if the given content has one of the selected content types.',
            ),
            '#name' => 'rules_condition_content_is_type',
            '#settings' => 
            array (
              'type' => 
              array (
                'application' => 'application',
              ),
              '#argument map' => 
              array (
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
          1 => 
          array (
            '#type' => 'condition',
            '#settings' => 
            array (
              '#argument map' => 
              array (
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_published',
            '#info' => 
            array (
              'label' => 'created content is published',
              'arguments' => 
              array (
                'node' => 
                array (
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Grants points to user creating an application',
              'label callback' => false,
              'arguments' => 
              array (
                'user' => 
                array (
                  'type' => 'user',
                  'label' => 'User',
                ),
              ),
              'module' => 'Userpoints',
              'eval input' => 
              array (
                0 => 'points',
              ),
            ),
            '#name' => 'userpoints_action_grant_points',
            '#settings' => 
            array (
              'points' => '5',
              '#argument map' => 
              array (
                'author' => 'user',
              ),
            ),
            '#type' => 'action',
          ),
        ),
      ),
      'rules_3' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Points given when creating an idea',
        '#active' => 1,
        '#weight' => '0',
        '#status' => 'custom',
        '#conditions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Content has type idea (forum topic)',
              'label callback' => false,
              'arguments' => 
              array (
                'node' => 
                array (
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
              'help' => 'Evaluates to TRUE, if the given content has one of the selected content types.',
            ),
            '#name' => 'rules_condition_content_is_type',
            '#settings' => 
            array (
              'type' => 
              array (
                'forum' => 'forum',
              ),
              '#argument map' => 
              array (
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
          1 => 
          array (
            '#type' => 'condition',
            '#settings' => 
            array (
              '#argument map' => 
              array (
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_published',
            '#info' => 
            array (
              'label' => 'created content is published',
              'arguments' => 
              array (
                'node' => 
                array (
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Grants points to a user creating an idea',
              'label callback' => false,
              'arguments' => 
              array (
                'user' => 
                array (
                  'type' => 'user',
                  'label' => 'User',
                ),
              ),
              'module' => 'Userpoints',
              'eval input' => 
              array (
                0 => 'points',
              ),
            ),
            '#name' => 'userpoints_action_grant_points',
            '#settings' => 
            array (
              'points' => '2',
              '#argument map' => 
              array (
                'author' => 'user',
              ),
            ),
            '#type' => 'action',
          ),
        ),
      ),
      'rules_6' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_votingpoints_event',
        '#label' => 'Points given when voting on an application',
        '#active' => 1,
        '#weight' => '0',
        '#status' => 'custom',
        '#conditions' => 
        array (
          0 => 
          array (
            '#type' => 'condition',
            '#settings' => 
            array (
              'type' => 
              array (
                'application' => 'application',
              ),
              '#argument map' => 
              array (
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => 
            array (
              'label' => 'Content has type application',
              'label callback' => false,
              'arguments' => 
              array (
                'node' => 
                array (
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
              'help' => 'Evaluates to TRUE, if the given content has one of the selected content types.',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Grant points to a user',
              'arguments' => 
              array (
                'user' => 
                array (
                  'type' => 'user',
                  'label' => 'User',
                ),
              ),
              'module' => 'Userpoints',
              'eval input' => 
              array (
                0 => 'points',
              ),
            ),
            '#name' => 'userpoints_action_grant_points',
            '#settings' => 
            array (
              'points' => '1',
              '#argument map' => 
              array (
                'user' => 'user',
              ),
            ),
            '#type' => 'action',
          ),
        ),
      ),
      
      
      'rules_7' => 
      array (
        '#type' => 'rule',
        '#set' => 'event_node_delete',
        '#label' => 'Points substracted when deleting an application',
        '#active' => 1,
        '#weight' => '0',
        '#status' => 'custom',
        '#conditions' => 
        array (
          0 => 
          array (
            '#type' => 'condition',
            '#settings' => 
            array (
              'type' => 
              array (
                'application' => 'application',
              ),
              '#argument map' => 
              array (
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => 
            array (
              'label' => 'Content has type application',
              'label callback' => false,
              'arguments' => 
              array (
                'node' => 
                array (
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
              'help' => 'Evaluates to TRUE, if the given content has one of the selected content types.',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Substracts points from a user',
              'label callback' => false,
              'arguments' => 
              array (
                'user' => 
                array (
                  'type' => 'user',
                  'label' => 'User',
                ),
              ),
              'module' => 'Userpoints',
              'eval input' => 
              array (
                0 => 'points',
              ),
            ),
            '#name' => 'userpoints_action_grant_points',
            '#settings' => 
            array (
              'points' => '-5',
              '#argument map' => 
              array (
                'author' => 'user',
              ),
            ),
            '#type' => 'action',
          ),
        ),
      ),  
    ),
  );
  
}