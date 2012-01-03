(function ($) {
  Drupal.noticeme = {};
  Drupal.noticeme.initFacebook = function(language) {
    (function(d, s, id) {
      var js, fjs = d.getElementsByTagName(s)[0];
      if (d.getElementById(id)) return;
      js = d.createElement(s); js.id = id;
      js.src = "//connect.facebook.net/" + language + "/all.js#xfbml=1";
      fjs.parentNode.insertBefore(js, fjs);
    }(document, 'script', 'facebook-jssdk'));
  };
  Drupal.noticeme.initGoogle = function(language) {
    window.___gcfg = {lang: language};
    var po = document.createElement('script');
    po.type = 'text/javascript'; po.async = true;
    po.src = 'https://apis.google.com/js/plusone.js';
    var s = document.getElementsByTagName('script')[0];
    s.parentNode.insertBefore(po, s);
  };

  Drupal.noticeme.initTwitter = function(language) {
    !function(d,s,id) {var js,fjs=d.getElementsByTagName(s)[0];if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src="//platform.twitter.com/widgets.js";fjs.parentNode.insertBefore(js,fjs);}}(document,"script","twitter-wjs");
  };

 
  Drupal.behaviors.noticeme = {
    attach: function(context, settings) {
      if ($('.fb-like', context).length) {
        if ($('#fb-root').length === 0) {
          $('<div id="fb-root"></div>').appendTo('body');
        }
        Drupal.noticeme.initFacebook(settings.noticeme.languages.facebook);
      }
      if ($('.g-plusone', context).length) {
        Drupal.noticeme.initGoogle(settings.noticeme.languages.google);
      }
      if ($('.twitter-share-button', context).length) {
        Drupal.noticeme.initTwitter(settings.noticeme.languages.twitter);
      }
    }
  };
})(jQuery);
