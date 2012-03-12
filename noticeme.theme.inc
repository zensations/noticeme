<?php


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
