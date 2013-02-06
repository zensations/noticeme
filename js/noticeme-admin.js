(function($){
  Drupal.behaviors.noticeme_admin = {
    attach: function (context, settings) {
      $('fieldset.noticeme-configuration').drupalSetSummary(function(context){
        var overridden = [];
        if($('.noticeme-title', context).val() != '') {
          overridden.push(Drupal.t('Title'));
        }
        if($('.noticeme-og', context).val() != '') {
          overridden.push(Drupal.t('Open Graph Type'));
        }
        if($('.noticeme-schema', context).val() != '') {
          overridden.push(Drupal.t('Schema Type'));
        }
        if($('.noticeme-description', context).val() != '') {
          overridden.push(Drupal.t('Description'));
        }
        $('.noticeme-image', context).val();
        if($('.noticeme-image input[type="file"]', context).length === 0) {
          overridden.push(Drupal.t('Image'));
        }
        if (overridden.length > 0) {
          return Drupal.t('Overrides: %fields', {
            '%fields': overridden.join(', ')
          });
        }
        else {
          return Drupal.t('Defaults from content');
        }
      });
    }
  };
}(jQuery));