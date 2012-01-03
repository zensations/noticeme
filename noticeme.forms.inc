<?php

function _noticeme_settings_form($values) {
  $form = array();
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => @$values['title'],
  );
  $form['og_type'] = array(
    '#type' => 'textfield',
    '#title' => t('Open Graph Type'),
    '#default_value' => @$values['og_type'],
  );
  $form['schema_type'] = array(
    '#type' => 'textfield',
    '#title' => t('Schema Type'),
    '#default_value' => @$values['schema_type'],
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => @$values['description'],
  );
  $form['image'] = array(
    '#type' => 'managed_file',
    '#title' => t('Image'),
    '#default_value' => @$values['image'],
    '#upload_location' => 'public://noticeme/',
  );
  return $form;
}

function _noticeme_configuration_form($values) {
  $form['facebook'] = array(
    '#title' => 'Facebook Like',
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    'display' => array(
      '#title' => t('Display'),
      '#type' => 'select',
      '#options' => array(
        'hidden' => 'hidden',
        'standard' => 'standard',
        'button_count' => 'button_count',
        'box_count' => 'box_count',
      ),
      '#default_value' => $values['facebook_display'],
    ),
    'send' => array(
      '#type' => 'checkbox',
      '#title' => t('Show send button'),
      '#default_value' => $values['facebook_send'],
    ),
    'faces' => array(
      '#type' => 'checkbox',
      '#title' => t('Show faces'),
      '#default_value' => $values['facebook_faces'],
    ),
    'verb' => array(
      '#type' => 'select',
      '#title' => t('Verb'),
      '#options' => array(
        'like' => 'like',
        'recommend' => 'recommend',
      ),
      '#default_value' => $values['facebook_verb'],
    ),
    'color' => array(
      '#type' => 'select',
      '#title' => t('Color'),
      '#options' => array(
        'light' => 'light',
        'dark' => 'dark',
      ),
      '#default_value' => $values['facebook_color'],
    ),
    'font' => array(
      '#type' => 'select',
      '#title' => t('font'),
      '#options' => array(
        'arial' => 'arial',
        'lucida grande' => 'lucida grande',
        'segoe ui' => 'segoe ui',
        'tahoma' => 'tahoma',
        'trebuchet ms' => 'trebuchet ms',
        'verdana' => 'verdana',
      ),
      '#default_value' => $values['facebook_font'],
    ),
  );
  $form['google'] = array(
    '#type' => 'fieldset',
    '#title' => t('Google +1'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    'display' => array(
      '#title' => t('Display'),
      '#type' => 'select',
      '#options' => array(
        'hidden' => 'hidden',
        'small' => 'small',
        'medium' => 'medium',
        'standard' => 'standard',
        'large' => 'large',
      ),
      '#default_value' => $values['google_display'],
    ),
    'annotation' => array(
      '#title' => t('Annotation'),
      '#type' => 'select',
      '#options' => array(
        'info' => 'info',
        'inline' => 'inline',
        'none' => 'none',
      ),
      '#default_value' => $values['google_annotation'],
    ),
  );

  $form['twitter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tweet this'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    'display' => array(
      '#type' => 'select',
      '#title' => t('Display'),
      '#options' => array(
        'hidden' => 'hidden',
        'small' => 'small',
        'large' => 'large',
      ),
      '#default_value' => $values['twitter_display'],
    ),
    'display_count' => array(
      '#type' => 'checkbox',
      '#title' => t('Display count'),
      '#default_value' => $values['twitter_display_count'],
    ),
  );
  return $form;
}