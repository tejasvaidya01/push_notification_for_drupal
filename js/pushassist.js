(function ($) {
  'use strict';

  Drupal.behaviors.customModule = {

    attach: function (context, settings) {

      $('#pushassist_notification_title').keyup(function () {

        var title = $('#pushassist_notification_title').val();

        if (title !== '') {

          $('#preview_notification_title').text(title);

        }
        else {

          $('#preview_notification_title').text('Notification Title');
        }
      });

      $('#pushassist_notification_message').keyup(function () {

        var message = $('#pushassist_notification_message').val();

        if (message !== '') {

          $('#preview_notification_message').text(message);

        }
        else {

          $('#preview_notification_message').text('Notification Message');
        }
      });

      $('#pushassist_notification_url').keyup(function () {

        var utm_source = $('#pushassist_notification_utm_source').val();
        var utm_medium = $('#pushassist_notification_utm_medium').val();
        var utm_campaign = $('#pushassist_notification_utm_campaign').val();
        var url = $('#pushassist_notification_url').val();
        var is_utm_show = $('#pushassist_is_utm_show_hidden').val();

        if (url !== '' && is_utm_show === 0) {

          $('#preview_redirect_url').text(url);

        }
        else if (url !== '' && is_utm_show === 1) {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);

        }
        else {
          $('#preview_redirect_url').text('URL to open when user clicks the notification:');
        }
      });

      $('#pushassist_notification_title').blur(function () {

        var title = $('#pushassist_notification_title').val();

        if (title !== '') {

          $('#preview_notification_title').text(title);
        }
        else {

          $('#preview_notification_title').text('Notification Title');
        }
      });

      $('#pushassist_notification_message').blur(function () {

        var message = $('#pushassist_notification_message').val();

        if (message !== '') {

          $('#preview_notification_message').text(message);

        }
        else {

          $('#preview_notification_message').text('Notification Message');
        }
      });

      $('#pushassist_notification_url').blur(function () {

        var url = $('#pushassist_notification_url').val();
        var utm_source = $('#pushassist_notification_utm_source').val();
        var utm_medium = $('#pushassist_notification_utm_medium').val();
        var utm_campaign = $('#pushassist_notification_utm_campaign').val();
        var is_utm_show = $('#pushassist_is_utm_show_hidden').val();

        if (url !== '' && is_utm_show === 0) {

          $('#preview_redirect_url').text(url);

        }
        else if (url !== '' && is_utm_show === 1) {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);

        }
        else {
          $('#preview_redirect_url').text('URL to open when user clicks the notification:');
        }
      });

      $('#pushassist_notification_utm_source').keyup(function () {

        var url = $('#pushassist_notification_url').val();
        var utm_source = $('#pushassist_notification_utm_source').val();
        var utm_medium = $('#pushassist_notification_utm_medium').val();
        var utm_campaign = $('#pushassist_notification_utm_campaign').val();

        if (url !== '') {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);
        }
      });

      $('#pushassist_notification_utm_source').blur(function () {

        var url = $('#pushassist_notification_url').val();
        var utm_source = $('#pushassist_notification_utm_source').val();
        var utm_medium = $('#pushassist_notification_utm_medium').val();
        var utm_campaign = $('#pushassist_notification_utm_campaign').val();

        if (url !== '') {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);
        }
      });

      $('#pushassist_notification_utm_medium').keyup(function () {

        var url = $('#pushassist_notification_url').val();
        var utm_source = $('#pushassist_notification_utm_source').val();
        var utm_medium = $('#pushassist_notification_utm_medium').val();
        var utm_campaign = $('#pushassist_notification_utm_campaign').val();

        if (url !== '') {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);
        }
      });

      $('#pushassist_notification_utm_medium').blur(function () {

        var url = $('#pushassist_notification_url').val();
        var utm_source = $('#pushassist_notification_utm_source').val();
        var utm_medium = $('#pushassist_notification_utm_medium').val();
        var utm_campaign = $('#pushassist_notification_utm_campaign').val();

        if (url !== '') {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);
        }
      });

      $('#pushassist_notification_utm_campaign').keyup(function () {

        var url = $('#pushassist_notification_url').val();
        var utm_source = $('#pushassist_notification_utm_source').val();
        var utm_medium = $('#pushassist_notification_utm_medium').val();
        var utm_campaign = $('#pushassist_notification_utm_campaign').val();

        if (url !== '') {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);
        }
      });

      $('#pushassist_notification_utm_campaign').blur(function () {

        var url = $('#pushassist_notification_url').val();
        var utm_source = $('#pushassist_notification_utm_source').val();
        var utm_medium = $('#pushassist_notification_utm_medium').val();
        var utm_campaign = $('#pushassist_notification_utm_campaign').val();

        if (url !== '') {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);
        }
      });

      $('#pushassist_is_utm_show').click(function () {

        var url = $('#pushassist_notification_url').val();

        if ($('#pushassist_is_utm_show').is(':checked')) {

          var utm_source = $('#pushassist_notification_utm_source').val();
          var utm_medium = $('#pushassist_notification_utm_medium').val();
          var utm_campaign = $('#pushassist_notification_utm_campaign').val();

          $('#pushassist_is_utm_show_hidden').val(1);
          $('#pushassist_notification_utm_source_div').show('slow');
          $('#pushassist_notification_utm_medium_div').show('slow');
          $('#pushassist_notification_utm_campaign_div').show('slow');

          if (url === '') {

            $('#preview_redirect_url').text('URL to open when user clicks the notification:');
          }
          else {

            $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);
          }

        }
        else {

          $('#pushassist_is_utm_show_hidden').val(0);

          $('#pushassist_notification_utm_source_div').hide('slow');
          $('#pushassist_notification_utm_medium_div').hide('slow');
          $('#pushassist_notification_utm_campaign_div').hide('slow');

          if (url === '') {

            $('#preview_redirect_url').text('URL to open when user clicks the notification:');
          }
          else {

            $('#preview_redirect_url').text(url);
          }
        }
      });

        /*   Campaign    */

      $('#pushassist_campaign_title').keyup(function () {

        var title = $('#pushassist_campaign_title').val();

        if (title !== '') {

          $('#preview_campaign_title').text(title);
        }
        else {

          $('#preview_campaign_title').text('Campaign Title');
        }
      });

      $('#pushassist_campaign_message').keyup(function () {

        var message = $('#pushassist_campaign_message').val();

        if (message !== '') {

          $('#preview_campaign_message').text(message);

        }
        else {

          $('#preview_campaign_message').text('Campaign Message');
        }
      });

      $('#pushassist_campaign_url').keyup(function () {

        var utm_source = $('#pushassist_campaign_utm_source').val();
        var utm_medium = $('#pushassist_campaign_utm_medium').val();
        var utm_campaign = $('#pushassist_campaign_utm_campaign').val();
        var url = $('#pushassist_campaign_url').val();
        var is_utm_show = $('#pushassist_campaign_is_utm_show_hidden').val();

        if (url !== '' && is_utm_show === 0) {

          $('#preview_redirect_url').text(url);

        }
        else if (url !== '' && is_utm_show === 1) {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);

        }
        else {
          $('#preview_redirect_url').text('URL to open when user clicks the notification:');
        }
      });

      $('#pushassist_campaign_title').blur(function () {

        var title = $('#pushassist_campaign_title').val();

        if (title !== '') {

          $('#preview_campaign_title').text(title);
        }
        else {

          $('#preview_campaign_title').text('Campaign Title');
        }
      });

      $('#pushassist_campaign_message').blur(function () {

        var message = $('#pushassist_campaign_message').val();

        if (message !== '') {

          $('#preview_campaign_message').text(message);
        }
        else {

          $('#preview_campaign_message').text('Campaign Message');
        }
      });

      $('#pushassist_campaign_url').blur(function () {

        var utm_source = $('#pushassist_campaign_utm_source').val();
        var utm_medium = $('#pushassist_campaign_utm_medium').val();
        var utm_campaign = $('#pushassist_campaign_utm_campaign').val();
        var url = $('#pushassist_campaign_url').val();
        var is_utm_show = $('#pushassist_campaign_is_utm_show_hidden').val();

        if (url !== '' && is_utm_show === 0) {

          $('#preview_redirect_url').text(url);

        }
        else if (url !== '' && is_utm_show === 1) {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);

        }
        else {
          $('#preview_redirect_url').text('URL to open when user clicks the notification:');
        }
      });

      $('#pushassist_campaign_utm_source').keyup(function () {

        var url = $('#pushassist_campaign_url').val();
        var utm_source = $('#pushassist_campaign_utm_source').val();
        var utm_medium = $('#pushassist_campaign_utm_medium').val();
        var utm_campaign = $('#pushassist_campaign_utm_campaign').val();

        if (url !== '') {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);
        }
      });

      $('#pushassist_campaign_utm_source').blur(function () {

        var url = $('#pushassist_campaign_url').val();
        var utm_source = $('#pushassist_campaign_utm_source').val();
        var utm_medium = $('#pushassist_campaign_utm_medium').val();
        var utm_campaign = $('#pushassist_campaign_utm_campaign').val();

        if (url !== '') {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);
        }
      });

      $('#pushassist_campaign_utm_medium').keyup(function () {

        var url = $('#pushassist_campaign_url').val();
        var utm_source = $('#pushassist_campaign_utm_source').val();
        var utm_medium = $('#pushassist_campaign_utm_medium').val();
        var utm_campaign = $('#pushassist_campaign_utm_campaign').val();

        if (url !== '') {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);
        }
      });

      $('#pushassist_campaign_utm_medium').blur(function () {

        var url = $('#pushassist_campaign_url').val();
        var utm_source = $('#pushassist_campaign_utm_source').val();
        var utm_medium = $('#pushassist_campaign_utm_medium').val();
        var utm_campaign = $('#pushassist_campaign_utm_campaign').val();

        if (url !== '') {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);
        }
      });

      $('#pushassist_campaign_utm_campaign').keyup(function () {

        var url = $('#pushassist_campaign_url').val();
        var utm_source = $('#pushassist_campaign_utm_source').val();
        var utm_medium = $('#pushassist_campaign_utm_medium').val();
        var utm_campaign = $('#pushassist_campaign_utm_campaign').val();

        if (url !== '') {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);
        }
      });

      $('#pushassist_campaign_utm_campaign').blur(function () {

        var url = $('#pushassist_campaign_url').val();
        var utm_source = $('#pushassist_campaign_utm_source').val();
        var utm_medium = $('#pushassist_campaign_utm_medium').val();
        var utm_campaign = $('#pushassist_campaign_utm_campaign').val();

        if (url !== '') {

          $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);
        }
      });

      $('#pushassist_campaign_is_utm_show').click(function () {

        var url = $('#pushassist_campaign_url').val();

        if ($('#pushassist_campaign_is_utm_show').is(':checked')) {

          var utm_source = $('#pushassist_campaign_utm_source').val();
          var utm_medium = $('#pushassist_campaign_utm_medium').val();
          var utm_campaign = $('#pushassist_campaign_utm_campaign').val();

          $('#pushassist_campaign_is_utm_show_hidden').val(1);

          $('#pushassist_campaign_utm_source_div').show('slow');
          $('#pushassist_campaign_utm_medium_div').show('slow');
          $('#pushassist_campaign_utm_campaign_div').show('slow');

          if (url === '') {

            $('#preview_redirect_url').text('URL to open when user clicks the notification:');
          }
          else {

            $('#preview_redirect_url').text(url + '?utm_source=' + utm_source + '&utm_medium=' + utm_medium + '&utm_campaign=' + utm_campaign);
          }

        }
        else {

          $('#pushassist_campaign_is_utm_show_hidden').val(0);

          $('#pushassist_campaign_utm_source_div').hide('slow');
          $('#pushassist_campaign_utm_medium_div').hide('slow');
          $('#pushassist_campaign_utm_campaign_div').hide('slow');

          if (url === '') {

            $('#preview_redirect_url').text('URL to open when user clicks the notification:');
          }
          else {

            $('#preview_redirect_url').text(url);
          }
        }
      });

      $('#pushassist_auto_push_UTMparameters').click(function () {

        if ($('#pushassist_auto_push_UTMparameters').is(':checked')) {

          $('#pushassist_setting_utm_source_div').show('slow');
          $('#pushassist_setting_utm_medium_div').show('slow');
          $('#pushassist_setting_utm_campaign_div').show('slow');

        }
        else {

          $('#pushassist_setting_utm_source_div').hide('slow');
          $('#pushassist_setting_utm_medium_div').hide('slow');
          $('#pushassist_setting_utm_campaign_div').hide('slow');
        }
      });

      $('#pushassist_template').change(function () {

        var template = $('#pushassist_template').val();

        if (template === '8') {

          $('#pushassist_template_location_2').show();
          $('#pushassist_template_location_1').hide();
          $('#pushassist_template_location').hide();

          $('#pushassist_hidden_template_location').val($('#pushassist_location_2').val());

        }

        if (template === '7') {

          $('#pushassist_template_location_2').hide();
          $('#pushassist_template_location_1').show();
          $('#pushassist_template_location').hide();

          $('#pushassist_hidden_template_location').val($('#pushassist_location_1').val());

        }

        if (template < 7) {

          $('#pushassist_template_location_2').hide();
          $('#pushassist_template_location_1').hide();
          $('#pushassist_template_location').show();

          $('#pushassist_hidden_template_location').val($('#pushassist_location').val());
        }
      });

      $('#pushassist_location').change(function () {

        var template_location = $('#pushassist_location').val();

        $('#pushassist_hidden_template_location').val(template_location);
      });

      $('#pushassist_location_1').change(function () {

        var template_location = $('#pushassist_location_1').val();

        $('#pushassist_hidden_template_location').val(template_location);
      });

      $('#pushassist_location_2').change(function () {

        var template_location = $('#pushassist_location_2').val();

        $('#pushassist_hidden_template_location').val(template_location);
      });
    }
  };

})(jQuery);
