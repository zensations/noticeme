<?php
/**
 * @file
 * 
 */

/**
 * Menu callback: 'admin/config/search/noticeme'.
 */
function noticeme_admin_settings($form, &$form_state) {
  // Fetch stored global default metadata values.
  $values = array(
    'title' => variable_get('noticeme_title', ''),
    'og_type' => variable_get('noticeme_og_type', ''),
    'schema_type' => variable_get('noticeme_schema_type', ''),
    'description' => variable_get('noticeme_description', ''),
  );

  $form['metadata'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global metadata'),
    // Displays the form for global default metadata values.
    'form' => _noticeme_settings_form($values),
  );

  unset($form['metadata']['form']['image']);

  $form['configuration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sitewide Facebook configuration'),
    'noticeme_fb_admins' => array(
      '#type' => 'textfield',
      '#title' => t('Facebook administrators'),
      '#default_values' => variable_get('noticeme_fb_admins', ''),
    ),
    'noticeme_fb_appid' => array(
      '#type' => 'textfield',
      '#title' => t('Facebook application ID'),
      '#default_values' => variable_get('noticeme_fb_appid', ''),
    ),
  );
  $form['languages'] = array(
    '#theme' => 'noticeme_languages',
    '#title' => t('API Languages'),
  );

  // Allow the admin to set different languages for fb, twitter and google,
  // depending on the current users language.
  foreach (_noticeme_language_list as $id => $label) {
    $row = array(
      'system' => array('#markup' => $label),
      'noticeme_' . $id . '_facebook' => array(
        '#type' => 'select',
        '#options' => _noticeme_facebook_languages(),
        '#default_value' => variable_get('noticeme_' . $id . '_facebook', 'en_US'),
      ),
      'noticeme_' . $id . '_google' => array(
        '#type' => 'select',
        '#options' => _noticeme_google_languages(),
        '#default_value' => variable_get('noticeme_' . $id . '_google', 'en-US'),
      ),
      'noticeme_' . $id . '_twitter' => array(
        '#type' => 'select',
        '#options' => _noticeme_twitter_languages(),
        '#default_value' => variable_get('noticeme_' . $id . '_twitter', 'en'),
      ),
    );
    $form['languages'][$id] = $row;
  }
  return system_settings_form($form);
}
/**
 * Validate handler for noticeme_admin_settings() form.
 */
function noticeme_admin_settings_validate(&$form, &$form_state) {
  $keys = array('title', 'og_type', 'schema_type', 'description');
  foreach ($keys as $key) {
    $form_state['values']['noticeme_' . $key] = $form_state['values'][$key];
    unset($form_state['values'][$key]);
  }
}

/**
 * Get currently installed languages.
 *
 * @return
 *   An array of currently installed languages in the way
 *   locale_language_list() does. if the locale module is not active it creates an
 *   equivalent array consisting of only the default language (english)
 */
function _noticeme_language_list() {
  global $language;
  if (module_exists('locale')) {
    return locale_language_list();
  }
  else {
    // If the locale module is not active, there can only be the current language.
    return array($language->language => $language->name);
  }
}

/**
 * Themes the languages table used in the noticeme settings page.
 *
 * Used on admin/config/search/noticeme.
 */
function theme_noticeme_languages($element) {
  $languages = array(
    '#theme' => 'table',
    '#header' => array(
      t('System'),
      t('Facebook'),
      t('Google'),
      t('Twitter'),
    ),
    '#rows' => array(),
  );
  foreach (_noticeme_language_list() as $id => $label) {
    $languages['#rows'][$id] = array(
      'system' => drupal_render($element['form'][$id]['system']),
      'facebook' => drupal_render($element['form'][$id]['noticeme_' . $id . '_facebook']),
      'google' => drupal_render($element['form'][$id]['noticeme_' . $id . '_google']),
      'twitter' => drupal_render($element['form'][$id]['noticeme_' . $id . '_twitter']),
    );
  }
  return drupal_render($languages);
}

/**
 * Returns an array of languages available on facebook.
 *
 * Copied from
 * http://www.facebook.com/ajax/intl/language_dialog.php?uri=http%3A%2F%2Fwww.facebook.com%2Ftranslations%2Fprefs.php
 * You need to be logged in to see this.
 */
function _noticeme_facebook_languages() {
  return array(
    'af_ZA' => 'Afrikaans',
    'az_AZ' => 'Azeri [beta]',
    'id_ID' => 'Indonesian',
    'ms_MY' => 'Malay',
    'bs_BA' => 'Bosnian [beta]',
    'ca_ES' => 'Catalan',
    'cs_CZ' => 'Czech',
    'cy_GB' => 'Welsh',
    'da_DK' => 'Danish',
    'de_DE' => 'German',
    'et_EE' => 'Estonian [beta]',
    'en_PI' => 'English (Pirate) [beta]',
    'en_GB' => 'English (UK)',
    'en_UD' => 'English (Upside Down)',
    'en_US' => 'English (US)',
    'es_LA' => 'Spanish',
    'es_ES' => 'Spanish (Spain)',
    'eo_EO' => 'Esperanto [beta]',
    'eu_ES' => 'Basque',
    'tl_PH' => 'Filipino',
    'fo_FO' => 'Faroese [beta]',
    'fr_CA' => 'French (Canada)',
    'fr_FR' => 'French (France)',
    'fy_NL' => 'Frisian [beta]',
    'ga_IE' => 'Irish [beta]',
    'gl_ES' => 'Galician [beta]',
    'ko_KR' => 'Korean',
    'hr_HR' => 'Croatian',
    'is_IS' => 'Icelandic [beta]',
    'it_IT' => 'Italian',
    'ka_GE' => 'Georgian [beta]',
    'sw_KE' => 'Swahili [beta]',
    'ku_TR' => 'Kurdish [beta]',
    'lv_LV' => 'Latvian [beta]',
    'fb_LT' => 'Leet Speak [beta]',
    'lt_LT' => 'Lithuanian',
    'la_VA' => 'Latin [beta]',
    'hu_HU' => 'Hungarian',
    'nl_NL' => 'Dutch',
    'ja_JP' => 'Japanese',
    'nb_NO' => 'Norwegian (bokmal)',
    'nn_NO' => 'Norwegian (nynorsk) [beta]',
    'pl_PL' => 'Polish',
    'pt_BR' => 'Portuguese (Brazil)',
    'pt_PT' => 'Portuguese (Portugal)',
    'ro_RO' => 'Romanian',
    'ru_RU' => 'Russian',
    'sq_AL' => 'Albanian [beta]',
    'sk_SK' => 'Slovak',
    'sl_SI' => 'Slovenian',
    'fi_FI' => 'Finnish',
    'sv_SE' => 'Swedish',
    'th_TH' => 'Thai',
    'vi_VN' => 'Vietnamese',
    'tr_TR' => 'Turkish',
    'zh_CN' => 'Simplified Chinese (China)',
    'zh_TW' => 'Traditional Chinese (Taiwan)',
    'zh_HK' => 'Traditional Chinese (Hong Kong)',
    'el_GR' => 'Greek',
    'be_BY' => 'Belarusian [beta]',
    'bg_BG' => 'Bulgarian',
    'mk_MK' => 'Macedonian [beta]',
    'sr_RS' => 'Serbian',
    'uk_UA' => 'Ukrainian [beta]',
    'hy_AM' => 'Armenian [beta]',
    'he_IL' => 'Hebrew',
    'ar_AR' => 'Arabic',
    'ps_AF' => 'Pashto [beta]',
    'fa_IR' => 'Persian [beta]',
    'ne_NP' => 'Nepali [beta]',
    'hi_IN' => 'Hindi',
    'bn_IN' => 'Bengali',
    'pa_IN' => 'Punjabi',
    'ta_IN' => 'Tamil',
    'te_IN' => 'Telugu',
    'ml_IN' => 'Malayalam',
    'km_KH' => 'Khmer [beta]',
  );
}

/**
 * Returns an array of languages available on google+
 *
 * Copied from https://www.google.com/settings/language (you need to be logged in).
 */
function _noticeme_google_languages() {
  return array(
    'ar' => 'Arabic',
    'bg' => 'Bulgarian',
    'ca' => 'Catalan',
    'zh-CN' => 'Chinese (Simplified)',
    'zh-TW' => 'Chinese (Traditional)',
    'hr' => 'Croatian',
    'cs' => 'Czech',
    'da' => 'Danish',
    'nl' => 'Dutch',
    'en-UK' => 'English (US)',
    'en-GB' => 'English (UK)',
    'et' => 'Estonian',
    'fil' => 'Filipino',
    'fi' => 'Finnish',
    'fr' => 'French',
    'de' => 'German',
    'el' => 'Greek',
    'iw' => 'Hebrew',
    'hi' => 'Hindi',
    'hu' => 'Hungarian',
    'id' => 'Indonesian',
    'it' => 'Italian',
    'ja' => 'Japanese',
    'ko' => 'Korean',
    'lv' => 'Latvian',
    'lt' => 'Lithuanian',
    'ms' => 'Malay',
    'no' => 'Norwegian',
    'fa' => 'Persian',
    'pl' => 'Polish',
    'pt-BR' => 'Portuguese (Brazil)',
    'pt-PT' => 'Portuguese (Portugal)',
    'ro' => 'Romanian',
    'ru' => 'Russian',
    'sr' => 'Serbian',
    'sv' => 'Swedish',
    'sk' => 'Slovak',
    'sl' => 'Slovenian',
    'es' => 'Spanish',
    'es-419' => 'Spanish (Latin America)',
    'th' => 'Thai',
    'tr' => 'Turkish',
    'uk' => 'Ukrainian',
    'vi' => 'Vietnamese',
  );
}

/**
 * Returns an array of languages available on twitter
 *
 * Copied from https://twitter.com/settings/account.
 * You need to be logged in to see this.
 */
function _noticeme_twitter_languages() {
  return array(
    'hi' => 'Hindi',
    'zh-cn' => 'Simplified Chinese',
    'pt' => 'Portuguese',
    'id' => 'Indonesian',
    'it' => 'Italian',
    'es' => 'Spanish',
    'da' => 'Danish',
    'en' => 'English',
    'fil' => 'Filipino',
    'ko' => 'Korean',
    'fr' => 'French',
    'no' => 'Norwegian',
    'zh-tw' => 'Traditional Chinese',
    'nl' => 'Dutch',
    'ru' => 'Russian',
    'de' => 'German',
    'ja' => 'Japanese',
    'fi' => 'Finnish',
    'msa' => 'Malay',
    'pl' => 'Polish',
  );
}
