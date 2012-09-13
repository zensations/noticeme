/**
 * @file
 * This file handles loading and (re)rendering of share/like/tweet buttons.
 */

(function ($) {
  Drupal.noticeme = {};

  /**
   * Load FB js library or rerender like buttons if it's been loaded already.
   */
  Drupal.noticeme.initFacebook = function(language) {
    if(jQuery('#facebook-jssdk').length) {
      // FB js sdk has already been loaded. So only parse the page, no need to load it again.
      try {
        FB.XFBML.parse();
      }
      catch(ex){}
    }
    // Load the FB js sdk.
    else {
      (function(d, s, id) {
        var js, fjs = d.getElementsByTagName(s)[0];
        if (d.getElementById(id)) return;
        js = d.createElement(s); js.id = id;
        js.src = "//connect.facebook.net/" + language + "/all.js#xfbml=1";
        fjs.parentNode.insertBefore(js, fjs);
      }(document, 'script', 'facebook-jssdk'));
    }
  };


  /**
   * Load google+ js library or rerender +1 buttons if it's been loaded already.
   */
  Drupal.noticeme.initGoogle = function(language) {
    // The Library has been laoded. Only rerender +1 buttons.
    if(jQuery('#gapi').length) {
      jQuery('.noticeme-buttons').each(function(index) {
        gapi.plusone.go(this);
      });
    }
    // Load the G+ library which automatically renders +1 buttons.
    else {
      var po = document.createElement('script');
      po.type = 'text/javascript';
      po.async = true;
      po.src = 'https://apis.google.com/js/plusone.js';
      po.id = 'gapi';
      var s = document.getElementsByTagName('script')[0];
      s.parentNode.insertBefore(po, s);
    }
  };

  /**
   * Load twitter js library or rerender tweet buttons if it's been loaded already.
   */
  Drupal.noticeme.initTwitter = function(language) {
    // The twitter library has been laoded. Rerender the tweet buttons.
    if(jQuery('#twitter-wjs').length ) {
      //twttr.widgets.load();
    }
    // Load twitter library and render tweet buttons.
    else {
      !function(d,s,id) {var js,fjs=d.getElementsByTagName(s)[0];if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src="//platform.twitter.com/widgets.js";fjs.parentNode.insertBefore(js,fjs);}}(document,"script","twitter-wjs");
    }
  };

 
  Drupal.behaviors.noticeme = {
    attach: function(context, settings) {
      // Ensure that the fb-root div exists and load the FB js library when
      // there are like buttons to render.
      if ($('.fb-like', context).length) {
        if ($('#fb-root').length === 0) {
          $('<div id="fb-root"></div>').appendTo('body');
        }
        Drupal.noticeme.initFacebook(settings.noticeme.languages.facebook);
      }

      // Load G+ libary if there are +1 buttons to render.
      if ($('.g-plusone', context).length) {
        Drupal.noticeme.initGoogle(settings.noticeme.languages.google);
      }

      // Load twitter libary if there are tweet buttons to render.
      if ($('.twitter-share-button', context).length) {
        Drupal.noticeme.initTwitter(settings.noticeme.languages.twitter);
      }
    }
  };
})(jQuery);
