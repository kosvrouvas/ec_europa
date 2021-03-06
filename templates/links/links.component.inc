<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function ec_europa_preprocess_links(array &$variables, $hook) {
  // Links can be empty.
  if (empty($variables['links'])) {
    return;
  }

  foreach ($variables['links']['links']['#items'] as &$link) {
    $link['link']['#options']['attributes']['class'][] = 'ecl-link';
    $link['link']['#options']['attributes']['class'][] = 'ecl-link--standalone';
  }
}
