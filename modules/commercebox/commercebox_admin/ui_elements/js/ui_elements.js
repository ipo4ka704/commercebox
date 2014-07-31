(function($) {
  /*
   * Open colorpicker on click
   */
  Drupal.behaviors.otherColorButton = {
    attach: function (context, settings) {
      var $colorpicker = $('.form-button-settings .form-item-bg-color, .form-button-settings #color-picker');
      $colorpicker.hide();
      $('.form-button-settings .form-type-radios input[type="radio"]').click(function() {
        $colorpicker.hide();
        if ($(this).val() == 'other') {
          $colorpicker.toggle();
        }
      });
      var $picker_pager = $('.form-item-pager-other-style, #color-picker-pager');
      $picker_pager.hide();
      $('.form-item-pager-style input[type="radio"]').click(function() {
        $picker_pager.hide();
        if($(this).val() == 'other') {
//        console.log(1);
          $picker_pager.toggle();
        }
      });
    }
  }

  Drupal.behaviors.colorElements = {
    attach: function (context, settings) {
      var $bg_color = $('.form-item-page-style-color input');
      var $colorpicker = $('.form-item-page-style-color, #color-picker-page-style');
      $('#edit-preview-image img').css('background',$bg_color.val());
      $colorpicker.hide();

      $('.page-admin-ui-elements-page-style #edit-bg-default input[type="radio"]').click(function() {
        $colorpicker.hide();
        if ($(this).val() == 'other') {
          $bg_color = $('.form-item-page-style-color input');
          $colorpicker.toggle();
          $('#edit-preview-image img').css('background',$bg_color.val());
          $('#color-picker-page-style').hover(function() {
            $(this).mousemove(function(){
//              console.log(1);
              $('#edit-preview-image img').css('background',$bg_color.val());
            });
          });
        }
        else {
          $bg_color = $(this).val();
          if ($(this).val() == 'default') {
            $bg_color = '9ee7ff';
          }
          $('#edit-preview-image img').css('background','#' + $bg_color);
        }
      });
    }
  }
  // for buttons page
//  var $elem =
  Drupal.behaviors.buttonsElements = {
    attach: function (context, settings) {
//      var $bg_color = $('.form-item-bg-color input');
      //Add 6 div to image
      for(var i=0; i<6; i++) {
        $('.page-admin-ui-elements-button #edit-preview-image').append('<div class="image-button" id="id-button'+i+'">Add to cart</div>');
      }
      //Default bacground
      var $defbacg =  $('input.form-submit').css('background');
      var $radius = $('input.form-submit').css('border-radius');
      if ($radius == '') {
        $radius = 'none';
      }
      var $imgbacg = $('#ui-elements-button-form input[name="default_pager_style"]').val();
      $('#edit-preview-image img').css('background',$imgbacg);
      $('.image-button').css({'background': $defbacg, 'border-radius': $radius});
      //onclick set bacground color
      $('#edit-bg-default input[type="radio"]').click(function() {
        var $background = $(this).next().css('background');
        if($(this).val() == 'other') {
          $background = $('.form-item-bg-color input').val();
        }
        $('.image-button').css({'background': $background, 'border-radius': '0' });
        $('#color-picker').hover(function() {
          $(this).mousemove(function(){
            $bg_color = $('.form-item-bg-color input').val();
            $('.image-button, #edit-submit').css({'background': $bg_color});
          });
        });
      });
      // Clic to Rounded Buttons
      $('#edit-bg-rounded input[type="radio"]').click(function() {
        var $background = $(this).next().css('background');
        if($(this).val() == 'other') {
          $background = $('.form-item-bg-color input').val();
        }
        $('.image-button, #edit-submit').css({'background': $background, 'border-radius': '30px'});
        $('#color-picker').hover(function() {
          $(this).mousemove(function(){
            $bg_color = $('.form-item-bg-color input').val();
            $('.image-button, #edit-submit').css({'background': $bg_color, 'border-radius': '30px'});
          });
        });
      });
      // Clic to Rounded Buttons
      $('#edit-pager-style input[type="radio"]').click(function() {
        var $background = $(this).next().css('background');
        if($(this).val() == 'other') {
          $background = $('.form-item-pager-other-style input').val();
        }
        $('#edit-preview-image img').css('background',$background);

        $('#color-picker-pager').hover(function() {
          $(this).mousemove(function(){
            var $bg_color = $('.form-item-pager-other-style input').val();
            $('#edit-preview-image img').css('background',$bg_color);
          });
        });
      });
    }
  }

  Drupal.behaviors.selectRadioButton = {
    attach: function (context, settings) {
      $('#ui-elements-button-form .form-item-bg-default .form-type-radio > label').click(function() {
        if ($('.form-type-radios .form-item-bg-default input[type="radio"]').val() != 'none') {
          $('.form-type-radios .form-item-bg-rounded input[value="none"]').attr('checked',true);
        }
      });
      $('#ui-elements-button-form .form-item-bg-rounded .form-type-radio > label').click(function() {
        if ($('.form-type-radios .form-item-bg-rounded input[type="radio"]').val() != 'none') {
          $('.form-type-radios.form-item-bg-default input[value="none"]').attr('checked',true);
        }
      });
    }
  };

})(jQuery);
