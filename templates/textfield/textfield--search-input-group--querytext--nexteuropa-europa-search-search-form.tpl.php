<?php

/**
 * @file
 * Contains template file.
 */
?>
<input<?php print $atomium['attributes']['element']
  ->append('class', array('ecl-text-input ecl-search-form__textfield'))
  ->set('size', '30'); ?>/><?php print render($suffix); ?>
