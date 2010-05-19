<?php // $Id: template.block-editing.inc,v 1.1.2.9 2010/01/03 02:27:07 jmburnz Exp $
// adaptivethemes.com

/**
 * @file template.block-editing.inc
 */

/**
 * Add block editing variables into the block templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
function adaptivetheme_preprocess_block_editing(&$vars, $hook) {
  $block = $vars['block'];
  $block_path = 'admin/build/block/configure/' . $block->module . '/' . $block->delta;
  $destination = drupal_get_destination();
  // Display 'Edit this block' link for block module blocks.
  if ($block->module == 'block') {
    $edit_links[] = l('<span>'. t('Edit Block') .'</span>', $block_path,
      array(
        'attributes' => array(
          'class' => 'block-edit-link edit-block-block',
          'title' => t('Edit block'),
        ),
        'query' => $destination,
        'html' => TRUE,
      )
    );
  }
  // Display 'Configure' for other blocks.
  else {
    $edit_links[] = l('<span>'. t('Configure') .'</span>', $block_path,
      array(
        'attributes' => array(
          'class' => 'block-edit-link edit-block-block',
          'title' => t('Configure block'),
        ),
        'query' => $destination,
        'html' => TRUE,
      )
    );
  }
  // Display 'Edit Menu' for menu blocks.
  if (($block->module == 'menu' || ($block->module == 'user' && $block->delta == 1)) && user_access('administer menu')) {
    $menu_name = ($block->module == 'user') ? 'navigation' : $block->delta;
    $edit_links[] = l('<span>'. t('Edit Menu') .'</span>', 'admin/build/menu-customize/'. $menu_name,
      array(
       'attributes' => array(
          'class' => 'block-edit-link edit-block-menu',
          'title' => t('Edit menu'),
        ),
        'query' => $destination,
        'html' => TRUE,
      )
    );
  }
  $vars['edit_links_array'] = $edit_links;
  $vars['edit_links'] = '<div class="edit-links">'. implode(' ', $edit_links) .'</div>';
}