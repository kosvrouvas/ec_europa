<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_hook().
 */
function ec_europa_preprocess_form_element_label(array &$variables, $hook) {
  $variables['atomium']['attributes']['wrapper']->append('class', 'ecl-form-label');

  if (isset($variables['attributes']['for'])) {
    $variables['atomium']['attributes']['wrapper']->setAttribute(
      'aria-label',
      $variables['attributes']['for']
    );
  }

  if (isset($variables['attributes']['element']['#id'])) {
    $variables['atomium']['attributes']['wrapper']->setAttribute(
      'id',
      $variables['element']['element']['#id'] . '_label'
    );
  }
}

/**
 * Implements hook_preprocess_hook().
 */
function ec_europa_preprocess_form_element_label__form_element__checkbox(array &$variables, $hook) {
  $variables['atomium']['attributes']['wrapper']->append('class', 'ecl-checkbox__label');

  if (isset($variables['element']['element']) && $variables['element']['element']['#title_display'] === 'invisible') {
    $variables['atomium']['attributes']['wrapper']->remove('class', 'element-invisible');
    $variables['form_element_label'] = array(
      'title' => NULL,
      'required' => NULL,
    );
  }
  $variables['atomium']['attributes']['wrapper']->delete('for');
}

/**
 * Implements hook_preprocess_hook().
 */
function ec_europa_preprocess_form_element_label__form_element__radio(array &$variables, $hook) {
  $variables['atomium']['attributes']['wrapper']->append('class', 'ecl-radio__label');

  if (isset($variables['element']['element']) && $variables['element']['element']['#title_display'] === 'invisible') {
    $variables['atomium']['attributes']['wrapper']->remove('class', 'element-invisible');
    $variables['form_element_label'] = array(
      'title' => NULL,
      'required' => NULL,
    );
  }
  $variables['atomium']['attributes']['wrapper']->delete('for');
}
