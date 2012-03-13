<?php
/**
 * @file
 * Theme functions for our social media buttons.
 */

/**
 * Theme the global share buttons block.
 */
function theme_global_share_buttons_block($variables) {
  $element = array();
  if ($variables['facebook_like']) {
    $element['facebook_like'] = array(
      '#markup' => theme('facebook_like', $variables['facebook_like']),
    );
  }
  if ($variables['google_plus_one']) {
    $element['google_plus_one'] = array(
      '#markup' => theme('google_plus', $variables['google_plus_one']),
    );
  }
  if ($variables['twitter_tweet']) {
    $element['twitter_tweet'] = array(
      '#markup' => theme('twitter_tweet', $variables['twitter_tweet']),
    );
  }
  return render($element);
}

/**
 * Theme a facebook like button.
 */
function theme_facebook_like($variables) {
  $element = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array('class' => array('fb-like')),
    '#value' => ' ',
  );
  foreach ($variables as $key => $value) {
    $element['#attributes']['data-' . $key] = $value;
  }
  return render($element);
}

/**
 * Theme a google +1 button.
 */
function theme_google_plus($variables) {
  $element = array(
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array('class' => array('g-plusone')),
    '#value' => ' ',
  );
  foreach ($variables as $key => $value) {
    $element['#attributes']['data-' . $key] = $value;
  }
  return render($element);
}

/**
 * Theme a tweet button.
 */
function theme_twitter_tweet($variables) {
  global $language;
  $element = array(
    '#type' => 'link',
    '#title' => t('Tweet'),
    '#href' => 'https://twitter.com/share',
    '#attributes' => array(
      'class' => array('twitter-share-button'),
      'data-lang' => variable_get('noticeme_' . $language->language . '_twitter', 'en'),
    ),
  );

  foreach ($variables as $key => $value) {
    $element['#attributes']['data-' . $key] = $value;
  }
  return render($element);
}
