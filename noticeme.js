(function ($) {
  Drupal.noticeme = {};
  Drupal.noticeme.initFacebook = function() {
    (function(d, s, id) {
      var js, fjs = d.getElementsByTagName(s)[0];
      if (d.getElementById(id)) return;
      js = d.createElement(s); js.id = id;
      js.src = "//connect.facebook.net/" + Drupal.settings.noticeme.fblang + "/all.js#xfbml=1";
      fjs.parentNode.insertBefore(js, fjs);
    }(document, 'script', 'facebook-jssdk'));
  };
  Drupal.noticeme.initGoogle = function() {
    var po = document.createElement('script');
    po.type = 'text/javascript'; po.async = true;
    po.src = 'https://apis.google.com/js/plusone.js';
    var s = document.getElementsByTagName('script')[0];
    s.parentNode.insertBefore(po, s);
  };
  Drupal.noticeme.initTwitter = function() {
    !function(d,s,id) {var js,fjs=d.getElementsByTagName(s)[0];if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src="//platform.twitter.com/widgets.js";fjs.parentNode.insertBefore(js,fjs);}}(document,"script","twitter-wjs");
  };
 
  Drupal.behaviors.noticeme = {
    attach: function(context, settings) {
      if ($('#fb-root').length === 0) {
        $('<div id="fb-root"></div>').appendTo('body');
      }
      if ($('.fb-like', context).length) {
        Drupal.noticeme.initFacebook();
      }
      if ($('.g-plusone', context).length) {
        Drupal.noticeme.initGoogle();
      }
      if ($('.twitter-share-button', context).length) {
        Drupal.noticeme.initTwitter();
      }
    }
  };
})(jQuery);
