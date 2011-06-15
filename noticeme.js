(function ($) {
  Drupal.behaviors.noticeme = {
    attach: function(context, settings) {
      // replace video links with embeds 
      // facebook like button
      $('a.facebook-like-button').each(function() {
        $(this).replaceWith('<iframe class="facebook-like-button" src="' + $(this).attr('href') + '" scrolling="no" frameborder="0" style="border:none;overflow:hidden;width:' + settings.noticeme_facebook_width + 'px;height:' + settings.noticeme_facebook_height + 'px;" allowTransparency="true"></iframe>');
      });
      // twitter button
      $('a.twitter-share-button').attr('data-count', settings.noticeme_twitter_count);
      $('a.google-plus-one').each(function() {
        var count = 'true';
        if (settings.noticeme_plusone_count == 0) {
          count = 'false';
        }
        $(this).replaceWith('<g:plusone count="' + count + '" size="' + settings.noticeme_plusone_size + '" href="' + $(this).attr('href') + '"></g:plusone>');
        gapi.plusone.go();
      });
    }
  }
})(jQuery);
