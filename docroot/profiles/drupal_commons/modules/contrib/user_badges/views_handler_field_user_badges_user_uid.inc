<?php
// $Id: views_handler_field_user_badges_user_uid.inc,v 1.1 2008/11/20 17:12:09 heine Exp $
/**
 * @file
 * A handler to provide proper displays for user badges.
 *
 * @author Heine Deelstra (Heine), http://drupal.org/user/17943
 * @author Richard Skinner (Likeless), http://drupal.org/user/310635
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_user_badges_user_uid extends views_handler_field {
  
  function render($values) {
    
    //We'll be needing the uid
    $uid = $values->{$this->field_alias};
    
    switch ($this->options['appearance']) {
      
      //For the text options, get the badge objects and format their names
      case 'linked_text':
      case 'unlinked_text':
        $user_badges = user_badges_get_badges($uid);
        
        //If we have no badges for the user, just return nothing.
        if (count($user_badges) == 0) {
          return '';
        }
        
        foreach ((array)$user_badges as $badge) {
          if ($this->options['appearance'] == 'linked_text' && $badge->href) {
            $badges[] = l($badge->name, $badge->href);
          }
          else {
            $badges[] = check_plain($badge->name);
          }
        }
        
        return implode($this->options['seperator'], $badges);
      
      //Send the array of badge objects to the custom theme function
      case 'custom_theme':
        $user_badges = user_badges_get_badges($uid);
        return theme($this->options['theme'], $user_badges);
        
      //This case is for everything else. It returns the normal themed badges.
      default:
        return user_badges_for_uid($uid);
    }
  }
  
  //Our options initialisation
  function option_definition() {
    $options = parent::option_definition();
    $options['appearance'] = 'badges';
    $options['seperator'] = ' ';
    $options['theme'] = '';
    return $options;
  }
  
  //Our options form
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    
    $form['appearance'] = array(
      '#title' => t('Appearance'),
      '#description' => t('How the badges will appear.'),
      '#type' => 'radios',
      '#options' => array(
        'badges' => t('Badges'),
        'linked_text' => t('Linked Text'),
        'unlinked_text' => t('Unlinked Text'),
        'custom_theme' => t('Custom Theme'),
      ),
      '#default_value' => $this->options['appearance'],
      '#weight' => -3,
    );
    
    $form['seperator'] = array(
      '#title' => t('Text Seperator'),
      '#description' => t('If you select text formats above, this is the string that will go between each badge name.'),
      '#type' => 'textfield',
      '#default_value' => $this->options['seperator'],
      '#size' => 6, 
      '#maxlength' => 128,
      '#weight' => -2,
    );
    
    $form['theme'] = array(
      '#title' => t('Custom Theme'),
      '#description' => t('If you select "Custom Theme" above, enter the name of your theme here. It will be passed an array of badge objects.'),
      '#type' => 'textfield',
      '#default_value' => $this->options['theme'],
      '#maxlength' => 128,
      '#weight' => -1,
    );
    
  }
}
