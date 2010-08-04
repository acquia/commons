<?php
// $Id: pathauto_user.inc,v 1.28.2.2 2008/08/05 17:28:13 freso Exp $

/**
 * @file
 * Hook implementations for user module integration.
 *
 * @ingroup pathauto
 */

/**
 * Implementation of hook_pathauto() for user aliases.
 */
function user_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings = array();
      $settings['module'] = 'user';
      $settings['token_type'] = 'user';
      $settings['groupheader'] = t('User path settings');
      $settings['patterndescr'] = t('Pattern for user account page paths');
      $settings['patterndefault'] = t('users/[user-raw]');
      $patterns = token_get_list('user');
      foreach ($patterns as $type => $pattern_set) {
        if ($type != 'global') {
          foreach ($pattern_set as $pattern => $description) {
            $settings['placeholders']['['. $pattern .']'] = $description;
          }
        }
      }

      $settings['bulkname'] = t('Bulk generate aliases for users that are not aliased');
      $settings['bulkdescr'] = t('Generate aliases for all existing user account pages which do not already have aliases.');
      return (object) $settings;
    default:
      break;
  }
}

/**
 * Implementation of hook_pathauto() for blog aliases.
 */
function blog_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings = array();
      $settings['module'] = 'blog';
      $settings['token_type'] = 'user';
      $settings['groupheader'] = t('Blog path settings');
      $settings['patterndescr'] = t('Pattern for blog page paths');
      $settings['patterndefault'] = t('blogs/[user-raw]');
      $patterns = token_get_list('user');
      foreach ($patterns['user'] as $pattern => $description) {
        $settings['placeholders']['['. $pattern .']'] = $description;
      }
      $settings['supportsfeeds'] = 'feed';
      $settings['bulkname'] = t('Bulk generate aliases for blogs that are not aliased');
      $settings['bulkdescr'] = t('Generate aliases for all existing blog pages which do not already have aliases.');
      return (object) $settings;
    default:
      break;
  }
}

/**
 * Implementation of hook_pathauto() for user-tracker aliases.
 */
function tracker_pathauto($op) {
  switch ($op) {
    case 'settings':
      $settings = array();
      $settings['module'] = 'tracker';
      $settings['token_type'] = 'user';
      $settings['groupheader'] = t('User-tracker path settings');
      $settings['patterndescr'] = t('Pattern for user-tracker page paths');
      $settings['patterndefault'] = t('users/[user-raw]/track');
      $patterns = token_get_list('user');
      foreach ($patterns['user'] as $pattern => $description) {
        $settings['placeholders']['['. $pattern .']'] = $description;
      }
      $settings['supportsfeeds'] = 'feed';
      $settings['bulkname'] = t('Bulk generate aliases for user-tracker paths that are not aliased');
      $settings['bulkdescr'] = t('Generate aliases for all existing user-tracker pages which do not already have aliases.');
      return (object) $settings;
    default:
      break;
  }
}

/**
 * Bulk generate aliases for all users without aliases.
 */
function user_pathauto_bulkupdate() {
  $query = "SELECT uid, name, src, dst FROM {users} LEFT JOIN {url_alias} ON CONCAT('user/', CAST(uid AS CHAR)) = src WHERE uid > 0 AND src IS NULL";
  $result = db_query_range($query, 0, variable_get('pathauto_max_bulk_update', 50));

  $count = 0;
  $placeholders = array();
  while ($user = db_fetch_object($result)) {
    $placeholders = pathauto_get_placeholders('user', $user);
    $src = 'user/'. $user->uid;
    if (pathauto_create_alias('user', 'bulkupdate', $placeholders, $src, $user->uid)) {
      $count++;
    }
  }

  drupal_set_message(format_plural($count,
    'Bulk generation of users completed, one alias generated.',
    'Bulk generation of users completed, @count aliases generated.'));
}

/**
 * Bulk generate aliases for all blogs without aliases.
 */
function blog_pathauto_bulkupdate() {
  $query = "SELECT uid, name, src, dst FROM {users} LEFT JOIN {url_alias} ON CONCAT('blog/', CAST(uid AS CHAR)) = src WHERE uid > 0 AND src IS NULL";
  $result = db_query_range($query, 0, variable_get('pathauto_max_bulk_update', 50));

  $count = 0;
  $placeholders = array();
  while ($user = db_fetch_object($result)) {
    $placeholders = pathauto_get_placeholders('user', $user);
    $src = 'blog/'. $user->uid;
    if (pathauto_create_alias('blog', 'bulkupdate', $placeholders, $src, $user->uid)) {
      $count++;
    }
  }

  drupal_set_message(format_plural($count,
    'Bulk generation of user blogs completed, one alias generated.',
    'Bulk generation of user blogs completed, @count aliases generated.'));
}

/**
 * Bulk generate aliases for user trackers without aliases.
 */
function tracker_pathauto_bulkupdate() {
  // We do the double CONCAT because Pgsql8.1 doesn't support more than three arguments to CONCAT
  // Hopefully some day we can remove that.
  $query = "SELECT uid, name, src, dst FROM {users} LEFT JOIN {url_alias} ON CONCAT(CONCAT('user/', CAST(uid AS CHAR)), '/track') = src WHERE uid > 0 AND src IS NULL";
  $result = db_query_range($query, 0, variable_get('pathauto_max_bulk_update', 50));

  $count = 0;
  $placeholders = array();
  while ($user = db_fetch_object($result)) {
    $placeholders = pathauto_get_placeholders('user', $user);
    $src = 'user/'. $user->uid .'/track';
    if (pathauto_create_alias('tracker', 'bulkupdate', $placeholders, $src, $user->uid)) {
      $count++;
    }
  }

  drupal_set_message(format_plural($count,
    'Bulk generation of user tracker pages completed, one alias generated.',
    'Bulk generation of user tracker pages completed, @count aliases generated.'));
}
