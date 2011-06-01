(function ($) {
  Drupal.behaviors.noticeme = {
    attach: function(context, settings) {
      // replace video links with embeds 
      // facebook like button
      $('a.facebook-like-button').each(function() {
        $(this).replaceWith('<iframe class="facebook-like-button" src="' + $(this).attr('href') + '" scrolling="no" frameborder="0" style="border:none;overflow:hidden;width:' + settings.noticeme_width + 'px;height:' + settings.noticeme_facebook_height + 'px;" allowTransparency="true"></iframe>');
      });
      // twitter button
      $('a.data-count-vertical').attr('data-count', 'vertical');
      $('a.data-count-horizontal').attr('data-count', 'horizontal');
      $('a.data-count-none').attr('data-count', 'none');
    }
  }
})(jQuery);
