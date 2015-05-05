<?php

/**
 * Implements hook_drush_command().
 */
function entity_translation_upgrade_drush_command() {
  $items = array();

  $items['entity-translation-upgrade'] = array(
    'description' => "Upgrades all nodes of the specified content type from Content translation to Entity translation.",
    'arguments' => array(
      'content_type' => 'Content type of nodes to be upgraded.',
    ),
    'examples' => array(
      'drush entity-translation-upgrade article' => 'Upgrades all nodes of content type "article" from Content translation to Entity translation.',
    ),
    'aliases' => array('etu'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 *
 * @param
 *   A string with the help section
 *
 * @return
 *   A string with the help text for the entity-translation-upgrade command
 */
function entity_translation_upgrade_drush_help($section) {
  switch ($section) {
    case 'drush:entity-translation-upgrade':
      return dt("Brief help for Drush command entity-translation-upgrade.");
    case 'meta:entity_translation_upgrade:title':
      return dt("Entity Translation Upgrade commands");
    case 'meta:entity_translation_upgrade:summary':
      return dt("Upgrading nodes to Entity translation.");
  }
}

/**
 * Implementation of drush_hook_COMMAND().
 *
 * @param
 *   The content type of which the nodes shall be upgraded
 *
 * Run the batch upgrading nodes of the specified content_type to Entity translation.
 * Let user chose content type from a list, if argument has not been provided.
 */
function drush_entity_translation_upgrade($content_type = "") {
	_entity_translation_upgrade_drush($content_type);
}

/**
 * Finshed batch callback, drush version.
 */
function entity_translation_upgrade_drush_end($success, $results, $operations, $elapsed) {
  // print result messages
  if (!empty($results)) {
    $message = format_plural($results['total'], '1 node translation successfully upgraded.', '@count node translations successfully upgraded.');
    $severity = 'ok';
    watchdog('entity translation upgrade', '@count node translations successfully upgraded.', array('@count' => $results['total']), WATCHDOG_INFO);
  }
  else {
    $message = t('No node translation available for the upgrade.');
    $severity = 'warning';
  }

  drush_log($message, $severity);
}

