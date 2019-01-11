<?php

/**
 * @file
 * PushAssist API calls.
 */

/*  Common request to PushAssist API.  */

function pushassist_remote_request($remote_data)
{

    $remote_url = 'https://api.pushassist.com/' . $remote_data['remoteAction'];

    $headers = array(
        'X-Auth-Token' => $remote_data['pushassist_appKey'],
        'X-Auth-Secret' => $remote_data['pushassist_appSecret'],
        'Accept' => 'application/json',
        "Content-Type" => 'application/json'
    );

    $remote_payload = array(
        'method' => $remote_data['method'],
        'headers' => $headers,
        'data' => $remote_data['remoteContent'],
    );

    $response = drupal_http_request($remote_url, $remote_payload);

    return $response;
}

/*   PushAssist API & Secret Key Verify  */

function pushassist_create_account($pushassist_user_name, $pushassist_campany_name, $pushassist_contact, $pushassist_email, $pushassist_password, $pushassist_protocol, $pushassist_site_url, $pushassist_account_name)
{
    $remoteContent = array("account" => array("name" => $pushassist_user_name,
        "company_name" => $pushassist_campany_name,
        "contact" => $pushassist_contact,
        "email" => $pushassist_email,
        "password" => $pushassist_password,
        "protocol" => $pushassist_protocol,
        "siteurl" => $pushassist_site_url,
        "subdomain" => $pushassist_account_name));

    $remote_data = array(
        'method' => 'POST',
        'remoteAction' => 'accounts/',
        'pushassist_appKey' => '',
        'pushassist_appSecret' => '',
        'remoteContent' => json_encode($remoteContent),
    );

    return pushassist_remote_request($remote_data);
}

function pushassist_login($pushassist_auth_api_key, $pushassist_auth_secret_key)
{

    $remote_data = array(
        'method' => 'GET',
        'remoteAction' => 'accounts_info/',
        'pushassist_appKey' => $pushassist_auth_api_key,
        'pushassist_appSecret' => $pushassist_auth_secret_key,
        'remoteContent' => json_encode(array()),
    );

    return pushassist_remote_request($remote_data);
}

function pushassist_dashboard_stats($pushassist_auth_api_key, $pushassist_auth_secret_key)
{

    $remote_data = array(
        'method' => 'GET',
        'remoteAction' => 'dashboard/',
        'pushassist_appKey' => $pushassist_auth_api_key,
        'pushassist_appSecret' => $pushassist_auth_secret_key,
        'remoteContent' => json_encode(array()),
    );

    return pushassist_remote_request($remote_data);
}

function pushassist_notification_details($pushassist_auth_api_key, $pushassist_auth_secret_key)
{

    $remote_data = array(
        'method' => 'GET',
        'remoteAction' => 'notifications?per_page=20',
        'pushassist_appKey' => $pushassist_auth_api_key,
        'pushassist_appSecret' => $pushassist_auth_secret_key,
        'remoteContent' => json_encode(array()),
    );

    return pushassist_remote_request($remote_data);
}

function pushassist_segment_details($pushassist_auth_api_key, $pushassist_auth_secret_key)
{

    $remote_data = array(
        'method' => 'GET',
        'remoteAction' => 'segments?per_page=20',
        'pushassist_appKey' => $pushassist_auth_api_key,
        'pushassist_appSecret' => $pushassist_auth_secret_key,
        'remoteContent' => json_encode(array()),
    );

    return pushassist_remote_request($remote_data);
}

function pushassist_subscribers_details($pushassist_auth_api_key, $pushassist_auth_secret_key)
{

    $remote_data = array(
        'method' => 'GET',
        'remoteAction' => 'subscribers?per_page=20',
        'pushassist_appKey' => $pushassist_auth_api_key,
        'pushassist_appSecret' => $pushassist_auth_secret_key,
        'remoteContent' => json_encode(array()),
    );

    return pushassist_remote_request($remote_data);
}

function pushassist_create_segment_api($pushassist_auth_api_key, $pushassist_auth_secret_key, $pushassist_segment_name)
{

    $segment_name = array("segment" => array(
        "segment_name" => $pushassist_segment_name)
    );

    $remote_data = array(
        'method' => 'POST',
        'remoteAction' => 'segments/',
        'pushassist_appKey' => $pushassist_auth_api_key,
        'pushassist_appSecret' => $pushassist_auth_secret_key,
        'remoteContent' => json_encode($segment_name),
    );

    return pushassist_remote_request($remote_data);
}

function pushassist_send_notification_api($pushassist_auth_api_key, $pushassist_auth_secret_key, $pushassist_notification_title, $pushassist_notification_message, $pushassist_notification_url, $notification_logo_path, $pushassist_notification_utm_source, $pushassist_notification_medium, $pushassist_notification_utm_campaign, $segment_array)
{

    $notification = array("notification" => array(
        "title" => $pushassist_notification_title,
        "message" => $pushassist_notification_message,
        "redirect_url" => $pushassist_notification_url,
        "image" => $notification_logo_path),
        "utm_params" => array("utm_source" => $pushassist_notification_utm_source,
            "utm_medium" => $pushassist_notification_medium,
            "utm_campaign" => $pushassist_notification_utm_campaign),
        "segments" => $segment_array
    );

    $remote_data = array(
        'method' => 'POST',
        'remoteAction' => 'notifications/',
        'pushassist_appKey' => $pushassist_auth_api_key,
        'pushassist_appSecret' => $pushassist_auth_secret_key,
        'remoteContent' => json_encode($notification),
    );

    return pushassist_remote_request($remote_data);
}

function pushassist_schedule_campaign_api($pushassist_auth_api_key, $pushassist_auth_secret_key, $pushassist_campaign_title, $pushassist_campaign_message, $pushassist_campaign_url, $pushassist_campaign_date, $campaign_logo_path, $pushassist_campaign_utm_source, $pushassist_campaign_medium, $pushassist_campaign_utm_campaign, $segment_array, $pushassist_campaign_timezone)
{

    $campaign = array("campaign" => array(
        "title" => $pushassist_campaign_title,
        "message" => $pushassist_campaign_message,
        "redirect_url" => $pushassist_campaign_url,
        "timezone" => $pushassist_campaign_date,
        "image" => $campaign_logo_path),
        "utm_params" => array("utm_source" => $pushassist_campaign_utm_source,
            "utm_medium" => $pushassist_campaign_medium,
            "utm_campaign" => $pushassist_campaign_utm_campaign),
        "segments" => $segment_array,
        "campaign_timezone" => $pushassist_campaign_timezone,
    );

    $remote_data = array(
        'method' => 'POST',
        'remoteAction' => 'campaigns/',
        'pushassist_appKey' => $pushassist_auth_api_key,
        'pushassist_appSecret' => $pushassist_auth_secret_key,
        'remoteContent' => json_encode($campaign),
    );

    return pushassist_remote_request($remote_data);
}

function pushassist_send_notification_new_post($pushassist_auth_api_key, $pushassist_auth_secret_key, $pushassist_notification_title, $pushassist_notification_message, $pushassist_notification_url, $notification_logo_path, $UTM_source, $UT_medium, $UTM_campaign)
{

    $notification = array("notification" => array(
        "title" => $pushassist_notification_title,
        "message" => $pushassist_notification_message,
        "redirect_url" => $pushassist_notification_url,
        "image" => $notification_logo_path),
        "utm_params" => array("utm_source" => $UTM_source,
            "utm_medium" => $UT_medium,
            "utm_campaign" => $UTM_campaign),
        "segments" => array()
    );

    $remote_data = array(
        'method' => 'POST',
        'remoteAction' => 'notifications/',
        'pushassist_appKey' => $pushassist_auth_api_key,
        'pushassist_appSecret' => $pushassist_auth_secret_key,
        'remoteContent' => json_encode($notification),
    );

    return pushassist_remote_request($remote_data);
}

function pushassist_gcm_setting_api($pushassist_apikey, $pushassist_secretkey, $pushassist_gcm_project_number, $pushassist_gcm_project_api)
{

    $gcm_settings = array("accountgcmsetting" => array("project_number" => $pushassist_gcm_project_number,
        "project_api_key" => trim($pushassist_gcm_project_api))
    );

    $remote_data = array(
        'method' => 'POST',
        'remoteAction' => 'gcmsettings/',
        'pushassist_appKey' => $pushassist_apikey,
        'pushassist_appSecret' => $pushassist_secretkey,
        'remoteContent' => json_encode($gcm_settings),
    );

    return pushassist_remote_request($remote_data);
}

function pushassist_advance_setting_api($pushassist_apikey, $pushassist_secretkey, $pushassist_interval, $pushassist_opt_in_title, $pushassist_opt_in_subtitle, $pushassist_allow_button_text, $pushassist_disallow_button_text, $pushassist_template, $pushassist_hidden_template_location, $image_name, $image_data, $pushassist_child_text, $pushassist_child_title, $pushassist_child_message, $pushassist_notification_title, $pushassist_notification_message, $pushassist_redirect_url)
{

    $advance_settings = array("templatesetting" => array("interval_time" => $pushassist_interval,
        "opt_in_title" => trim($pushassist_opt_in_title),
        "opt_in_subtitle" => trim($pushassist_opt_in_subtitle),
        "allow_button_text" => trim($pushassist_allow_button_text),
        "disallow_button_text" => trim($pushassist_disallow_button_text),
        "template" => $pushassist_template,
        "location" => $pushassist_hidden_template_location,
        "image_data" => $image_data,
        "image_name" => trim($image_name),
        "child_window_text" => trim($pushassist_child_text),
        "child_window_title" => trim($pushassist_child_title),
        "child_window_message" => trim($pushassist_child_message),
        "notification_title" => trim($pushassist_notification_title),
        "notification_message" => trim($pushassist_notification_message),
        "redirect_url" => trim($pushassist_redirect_url))
    );

    $remote_data = array(
        'method' => 'POST',
        'remoteAction' => 'settings/',
        'pushassist_appKey' => $pushassist_apikey,
        'pushassist_appSecret' => $pushassist_secretkey,
        'remoteContent' => json_encode($advance_settings),
    );

    return pushassist_remote_request($remote_data);
}