<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_hook().
 *
 * @SuppressWarnings(PHPMD.CyclomaticComplexity)
 * @SuppressWarnings(PHPMD.NPathComplexity)
 */
function ec_europa_preprocess_page(array &$variables, $hook) {
  $node = NULL;
  if (isset($variables['node'])) {
    $node = $variables['node'];
  }

  // Small fix to maxe the link to the start page use the alias with language.
  $variables['front_page'] = url('<front>');

  // Add information about the number of sidebars.
  if (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = 'ecl-col-6';
  }
  elseif (!empty($variables['page']['sidebar_first']) || !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = 'ecl-col-9';
  }
  else {
    $variables['content_column_class'] = 'ecl-col-12';
  }

  $variables['page_logo_title'] = t('Home - @sitename', array('@sitename' => variable_get('site_name', 'European Commission')));

  // Check if Display Suite is handling node.
  if ($node !== NULL && module_exists('ds')) {
    $layout = ds_get_layout('node', $node->type, 'full');
    if ($layout && isset($layout['is_nexteuropa']) && $layout['is_nexteuropa'] === TRUE) {
      // If our display suite layout has a header region.
      if (isset($layout['regions']['left_header'])) {
        // Move the header_bottom to the node.
        $variables['node']->header_bottom = $variables['page']['header_bottom'];
        unset($variables['page']['header_bottom']);
      }
      if (isset($variables['page']['utility'])) {
        // Move the utility to the node.
        $variables['node']->utility = $variables['page']['utility'];
        unset($variables['page']['utility']);
      }
      ctools_class_add($layout['layout']);

      if (isset($node->ds_switch) && $node->ds_switch !== 'college') {
        $variables['node']->header_bottom_modifier = 'page-bottom-header--full-grey';
      }

      // This disables message-printing on ALL page displays.
      $variables['show_messages'] = FALSE;

      // Add tabs to node object so we can put it in the DS template instead.
      if (isset($variables['tabs'])) {
        $node->local_tabs = drupal_render($variables['tabs']);
      }

      // Use page__ds_node.tpl unless it is an exception.
      $custom_page_templates = array('page__gallery');
      if (empty(\array_intersect($variables['theme_hook_suggestions'], $custom_page_templates))) {
        $variables['theme_hook_suggestions'][] = 'page__ds_node';
      }
    }
  }

  $variables['site_header'] = array(
    '#theme' => _atomium_extend_theme_hook('site_header', $variables['theme_hook_original']),
  );

  $variables['page_header'] = array(
    '#theme' => _atomium_extend_theme_hook('page_header', $variables['theme_hook_original']),
    '#identity' => $variables['site_name'],
    '#title_prefix' => $variables['title_prefix'],
    '#title_suffix' => $variables['title_suffix'],
    '#title' => drupal_get_title(),
  );

  if (isset($node)) {
    // Adding generic introduction field to be later rendered in page template.
    $introduction = variable_get('ec_europa_introduction_field', FALSE);
    $variables['page_header']['#introduction'] = isset($node->{$introduction})
      ? field_view_field('node', $node, $introduction, array('label' => 'hidden')) : NULL;
  }

  $variables['footer'] = array(
    '#theme' => _atomium_extend_theme_hook('footer', $variables['theme_hook_original']),
    '#footer_right' => $variables['page']['footer_right'],
    '#footer_middle' => $variables['page']['footer_middle'],
  );

  if (\in_array('page__splash', $variables['theme_hook_suggestions'], TRUE)) {
    $variables['logo'] = array(
      '#theme' => _atomium_extend_theme_hook('logo', $variables['theme_hook_original']),
      '#title' => t('Home - European Commission'),
      '#attributes' => array(
        'class' => array('ecl-logo--big', 'ecl-u-mh-auto'),
      ),
    );

    $variables['splash'] = array(
      '#theme' => _atomium_extend_theme_hook('splash', $variables['theme_hook_original']),
    );
  }

  // Remove member "action_links" if there is no items to render.
  if (empty($variables['action_links']['#items'])) {
    unset($variables['action_links']);
  }
}
