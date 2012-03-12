/**
 * @file
 * Sets the veritcal tab description for "Social Media", in which noticeme stuff is.
 */

(function ($) {
  Drupal.behaviors.noticeme_form = {
    attach: function(context) {
      $('fieldset.noticeme-configuration', context).drupalSetSummary(function(context) {
        return Drupal.t('Using default');
      });
    }
  }
}(jQuery));
