<?php
/**
 * @file
 * Field definition hooks four the noticeme field.
 */

/**
 * Implements hook_field_info().
 */
function noticeme_field_info() {
  $fields = array();
  $fields['noticeme'] = array(
    'label' => t('Noticeme'),
    'description' => t('Adds social media buttons to the entity.'),
    'default_widget' => 'noticeme_widget',
    'default_formatter' => 'noticeme_buttons',
  );
  return $fields;
}

/**
 * Implements hook_field_formatter_info().
 */
function noticeme_field_formatter_info() {
  return array(
    'noticeme_buttons' => array(
      'label' => t('Noticeme'),
      'field types' => array('noticeme'),
      'settings' => array(
        'facebook_display' => 'button_count',
        'facebook_send' => 0,
        'facebook_faces' => 0,
        'facebook_verb' => 'like',
        'facebook_color' => 'light',
        'facebook_font' => 'lucida grande',
        'google_display' => 'medium',
        'google_annotation' => 'box',
        'twitter_display' => 'small',
        'twitter_display_count' => 1,
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function noticeme_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $element = _noticeme_configuration_form($instance['display'][$view_mode]['settings']);
  $element['#element_validate'] = array('_noticeme_field_formatter_settings_validate');
  return $element;
}

/**
 * Validate handler for noticeme_field_formatter_settings_form().
 */
function _noticeme_field_formatter_settings_validate($element, &$form_state, $form) {
  $field = $form_state['formatter_settings_edit'];
  $values = &$form_state['values']['fields'][$field]['settings_edit_form']['settings'];
  // We rewrite those settings here so the settings array can be used more easily
  // in noticeme_field_formatter_view().
  foreach ($values as $network => $settings) {
    foreach ($settings as $key => $value) {
      $values[$key] = $value;
    }
  }
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function noticeme_field_formatter_settings_summary($field, $instance, $view_mode) {
  $summary = array();
  $settings = $instance['display'][$view_mode]['settings'];
  if (@$settings['facebook_display'] != 'hidden') {
    $summary[] = 'Facebook Like';
  }
  if (@$settings['google_display'] != 'hidden') {
    $summary[] = 'Google +1';
  }
  if (@$settings['twitter_display'] != 'hidden') {
    $summary[] = 'Tweet this!';
  }
  return implode('<br/>', $summary);
}

/**
 * Implements hook_field_formatter_view().
 */
function noticeme_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $url = entity_uri($entity_type, $entity);
  if (!$url) {
    return;
  }
  $url = url($url['path'], array('absolute' => TRUE));
  $element = array();
  foreach (array_keys($items) as $delta) {
    // The values in $display['settings'] are written in
    // _noticeme_field_formatter_settings_validate() to be used here.
    if ($display['settings']['facebook_display'] != 'hidden') {
      $element[$delta] = array(
        '#prefix' => '<div class="noticeme-buttons">',
        '#suffix' => '</div>',
      );
      $element[$delta]['facebook'] = array(
        '#theme' => 'facebook_like',
        '#href' => $url,
        '#layout' => $display['settings']['facebook_display'],
        '#send' => $display['settings']['facebook_send']?'true':'false',
        '#show-faces' => $display['settings']['facebook_faces']?'true':'false',
        '#action' => $display['settings']['facebook_verb'],
        '#colorscheme' => $display['settings']['facebook_color'],
        '#font' => $display['settings']['facebook_font'],
      );
    }
    if ($display['settings']['google_display'] != 'hidden') {
      $element[$delta]['google'] = array(
        '#theme' => 'google_plus',
        '#href' => $url,
        '#size' => $display['settings']['google_display'],
        '#annotation' => $display['settings']['google_annotation'],
      );
    }
    if ($display['settings']['twitter_display'] != 'hidden') {
      $element[$delta]['twitter'] = array(
        '#theme' => 'twitter_tweet',
        '#url' => $url,
        '#size' => $display['settings']['twitter_display'],
        '#count' => $display['settings']['twitter_display_count'],
      );
    }
  }
  return $element;
}

/**
 * Implements hook_field_widget_info().
 */
function noticeme_field_widget_info() {
  return array(
    'noticeme_widget' => array(
      'label' => t('Noticeme'),
      'field types' => array('noticeme'),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function noticeme_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  $item = (count($items) > 0)?$items[0]:array();
  return _noticeme_settings_form($item);
}


/**
 * Implements hook_field_is_empty().
 */
function noticeme_field_is_empty($item, $field) {
  // the field is never empty and should even be displayed without data
  return FALSE;
}

/**
 * Implements hook_field_presave().
 */
function noticeme_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  list($id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);
  foreach ($items as $item) {
    $file = file_load($item['image']);
    // If the user set an image, make it permanent.
    if (!empty($file) && !$file->status) {
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
    }
  }
}

/**
 * Implements hook_field_update().
 *
 * Checks for files that have been removed from the object.
 */
function noticeme_field_update($entity_type, $entity, $field, $instance, $langcode, &$items) {
  list($id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);

  // On new revisions, all files are considered to be a new usage and no
  // deletion of previous file usages are necessary.
  if (!empty($entity->revision)) {
    foreach ($items as $item) {
      $file = file_load($item['image']);
      if ($file) {
        file_usage_add($file, 'file', $entity_type, $id);
      }
    }
    return;
  }

  // Build a display of the current FIDs.
  $current_fids = array();
  foreach ($items as $item) {
    $current_fids[] = $item['image'];
  }

  // Create a bare-bones entity so that we can load its previous values.
  $original = entity_create_stub_entity($entity_type, array($id, $vid, $bundle));
  field_attach_load($entity_type, array($id => $original), FIELD_LOAD_CURRENT, array('field_id' => $field['id']));

  // Compare the original field values with the ones that are being saved.
  $original_fids = array();
  if (!empty($original->{$field['field_name']}[$langcode])) {
    foreach ($original->{$field['field_name']}[$langcode] as $original_item) {
      $original_fids[] = $original_item['image'];
      if (isset($original_item['image']) && !in_array($original_item['image'], $current_fids)) {
        // Decrement the file usage count by 1 and delete the file if possible.
        if ($file = file_load($original_item['image'])) {
          file_field_delete_file((array) $file, $field, $entity_type, $id);
        }
      }
    }
  }

  // Add new usage entries for newly added files.
  foreach ($items as $item) {
    if (!in_array($item['image'], $original_fids)) {
      $file = file_load($item['image']);
      if ($file) {
        file_usage_add($file, 'file', $entity_type, $id);
      }
    }
  }
}
