<?php

/**
 * @file
 * PushAssist module admin page with PushAssist account stats.
 */

/**
 * Checks to see if PushAssist is logged in.
 */
function pushassist_validate_user()
{
    $key = variable_get('pushassist_apiKey', '');

    $secret = variable_get('pushassist_secretKey', '');

    if ($key && $secret) {

        return drupal_get_form('pushassist_dashboard');
    } else {

        return drupal_get_form('pushassist_account_verify');
    }
}

/*  account register  start */


function pushassist_account_verify()
{
    $form['#attached']['css'] = array(
        drupal_get_path('module', 'pushassist') . '/css/pushassist.css',
    );

    $form['pushassist-registration-form'] = array(
        '#prefix' => '<div class="content clearfix" id="pushassist"> <div class="col-md-6"><h4>Create an Account</h4><div id="pushassist_account_create">',
        '#suffix' => '</div></div>',
    );

    $form['pushassist-registration-form']['pushassist_user_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Full Name'),
        '#maxlength' => 150,
        '#attributes' => array('placeholder' => t('Full Name')),
    );

    $form['pushassist-registration-form']['pushassist_campany_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Company Name'),
        '#maxlength' => 150,
        '#attributes' => array('placeholder' => t('Company Name')),
    );

    $form['pushassist-registration-form']['pushassist_contact'] = array(
        '#type' => 'textfield',
        '#title' => t('Contact no with Country Code'),
        '#maxlength' => 20,
        '#attributes' => array('placeholder' => t('Contact no with Country Code')),
    );

    $form['pushassist-registration-form']['pushassist_email'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#maxlength' => 150,
        '#attributes' => array('placeholder' => t('Email')),
    );

    $form['pushassist-registration-form']['pushassist_password'] = array(
        '#type' => 'password',
        '#title' => t('Password'),
        '#maxlength' => 100,
        '#attributes' => array('placeholder' => t('Password')),
    );

    $protocol_array = array('http://' => 'http://', 'https://' => 'https://');

    $form['pushassist-registration-form']['pushassist_protocol'] = array(
        '#prefix' => '<div class="col-sm-2" id="protocol">',
        '#title' => t('Protocol'),
        '#type' => 'select',
        '#options' => $protocol_array,
        '#multiple' => False,
        '#suffix' => '</div>',
    );

    $form['pushassist-registration-form']['pushassist_site_url'] = array(
        '#prefix' => '<div class="col-sm-5" id="pushassist_site_url">',
        '#type' => 'textfield',
        '#title' => t('Site URL'),
        '#attributes' => array('placeholder' => t('Site URL')),
        '#suffix' => '</div>',
    );

    $form['pushassist-registration-form']['pushassist_account_name'] = array(
        '#prefix' => '<div class="clearfix"></div><div class="col-sm-5" id="pushassist_account_name">',
        '#type' => 'textfield',
        '#title' => t('accountname'),
        '#attributes' => array('placeholder' => t('accountname')),
        '#suffix' => '</div><div class="col-sm-4" id="subdomain">.pushassist.com</div>',
    );

    $form['pushassist-registration-form']['submit'] = array(
        '#prefix' => '<div class="clearfix"></div>',
        '#type' => 'submit',
        '#value' => t('Create Account'),
        '#validate' => array('pushassist_create_account_validate'),
        '#submit' => array('pushassist_create_account_submit'),
    );

    $form['pushassist-api-form'] = array(
        '#prefix' => '<div class="col-md-6"><h4>Provide API Key And Secret Key</h4><div id="pushassist_account_verify">',
    );

    $form['pushassist-api-form']['pushassist_auth_api_key'] = array(
        '#type' => 'textfield',
        '#title' => t('API Key'),
        '#maxlength' => 150,
        '#attributes' => array('placeholder' => t('API Key')),
    );

    $form['pushassist-api-form']['pushassist_auth_secret_key'] = array(
        '#type' => 'textfield',
        '#title' => t('Secret Key'),
        '#maxlength' => 150,
        '#attributes' => array('placeholder' => t('Secret Key')),
    );


    $form['pushassist-api-form']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
        '#validate' => array('pushassist_account_verify_validate'),
        '#submit' => array('pushassist_account_verify_submit'),
    );

    $form['pushassist-api-instruction'] = array(
        '#prefix' => '<h4>How to get API Keys</h4><div class="panel panel-default"><div class="panel-body">
                    <p>
                        If you are an existing user of PushAssist you can find your api keys under your PushAssist
                        control panel. To get your API and Secret Keys login to your <strong>PushAssist Admin Control
                            Panel</strong> and click <strong>Sites</strong>. Copy the API Key and Secret Keys from your
                        control Panel and paste above. Your account login details were sent to you at the time of
                        signup. In case you have missed your account credentials please send us an email at <a href="mailto:support@pushassist.com">support@pushassist.com</a> containing your site url and
                        we will send you your account credentials.
                    </p>
                    <p> Please do not share your API and Secret keys with anyone. </p>                ',
        '#suffix' => '</div></div></div>',
    );

    return $form;
}

function pushassist_create_account_validate($form, &$form_state)
{

    $regex = "((https?|ftp)\:\/\/)?"; // SCHEME
    $regex .= "([a-z0-9+!*(),;?&=\$_.-]+(\:[a-z0-9+!*(),;?&=\$_.-]+)?@)?"; // User and Pass
    $regex .= "([a-z0-9-.]*)\.([a-z]{2,4})"; // Host or IP
    $regex .= "(\:[0-9]{2,5})?"; // Port
    $regex .= "(\/([a-z0-9+\$_-]\.?)+)*\/?"; // Path
    $regex .= "(\?[a-z+&\$_.-][a-z0-9;:@&%=+\/\$_.-]*)?"; // GET Query
    $regex .= "(#[a-z_.-][a-z0-9+\$_.-]*)?"; // Anchor
    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_user_name = trim($form_state['values']['pushassist_user_name']);

    $pushassist_contact = $form_state['values']['pushassist_contact'];

    $pushassist_email = trim($form_state['values']['pushassist_email']);

    $pushassist_password = trim($form_state['values']['pushassist_password']);

    $pushassist_protocol = trim($form_state['values']['pushassist_protocol']);

    $pushassist_site_url = trim($form_state['values']['pushassist_site_url']);

    $pushassist_account_name = trim($form_state['values']['pushassist_account_name']);

    $pushassist_url = $pushassist_protocol . $pushassist_site_url;

    if (empty($pushassist_user_name)) {

        form_set_error('pushassist_user_name', t('Please provide full name.'));
        return false;

    } else if (!preg_match("/^[a-zA-Z ]*$/", $pushassist_user_name)) {

        form_set_error('pushassist_user_name', t('Please provide valid full name.'));
        return false;
    }

    if (strlen($pushassist_contact) > 0) {

        if (!preg_match('/^\s*(?:\+?(\d{1,3}))?([-. (]*(\d{3})[-. )]*)?((\d{3})[-. ]*(\d{2,4})(?:[-.x ]*(\d+))?)\s*$/', $pushassist_contact)) {

            form_set_error('pushassist_contact', t('Please provide valid contact no with country code.'));
            return false;
        }
    }

    if (empty($pushassist_email)) {

        form_set_error('pushassist_email', t('Please provide email.'));
        return false;

    } else if (filter_var($pushassist_email, FILTER_VALIDATE_EMAIL) === false) {

        form_set_error('pushassist_email', t('Please provide valid email.'));
        return false;
    }

    if (empty($pushassist_password)) {

        form_set_error('pushassist_password', t('Please provide password.'));
        return false;
    }

    if (empty($pushassist_site_url)) {

        form_set_error('pushassist_site_url', t('Please provide site URL.'));
        return false;

    } else if (!preg_match("/^$regex$/", $pushassist_url)) {

        form_set_error('pushassist_site_url', t('Please provide valid site URL.'));
        return false;
    }

    if (empty($pushassist_account_name)) {

        form_set_error('pushassist_account_name', t('Please provide accountname.'));
        return false;

    } else if (!preg_match("#^[a-zA-Z0-9]+$#", $pushassist_account_name)) {

        form_set_error('pushassist_account_name', t('Please provide valid accountname.'));
        return false;
    }

    $reserved_words = array(

        'pushassist', 'admin', 'backend', 'account', 'api', 'backoffice', 'http', 'https', 'www', 'google', 'facebook', 'yahoo', 'gmail', 'superadmin', 'ftp', 'com', 'config', 'bootstrap', 'php', 'register', 'ajax', 'twitter', 'app', 'application', 'dashboard', 'ip', 'IP', 'login'
    );

    if (in_array($pushassist_account_name, $reserved_words)) {

        form_set_error('pushassist_account_name', t("Sorry, This account name is not valid. please try with new accountname."));
        return false;
    }
}

function pushassist_create_account_submit($form, &$form_state)
{

    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_user_name = trim($form_state['values']['pushassist_user_name']);

    $pushassist_campany_name = trim($form_state['values']['pushassist_campany_name']);

    $pushassist_contact = trim($form_state['values']['pushassist_contact']);

    $pushassist_email = trim($form_state['values']['pushassist_email']);

    $pushassist_password = trim($form_state['values']['pushassist_password']);

    $pushassist_protocol = trim($form_state['values']['pushassist_protocol']);

    $pushassist_site_url = trim($form_state['values']['pushassist_site_url']);

    $pushassist_account_name = trim($form_state['values']['pushassist_account_name']);

    $account_create = pushassist_create_account($pushassist_user_name, $pushassist_campany_name, $pushassist_contact, $pushassist_email, $pushassist_password, $pushassist_protocol, $pushassist_site_url, $pushassist_account_name);

    $account_create_info = json_decode($account_create->data, true);

    if ($account_create_info['status'] == 'Success') {

        $account_info = pushassist_login($account_create_info['api_key'], $account_create_info['auth_secret']);

        $account_details = json_decode($account_info->data, true);

        if (isset($account_details['apiKey']) && isset($account_details['apiSecret'])) {

            variable_set('pushassist_apiKey', $account_details['apiKey']);
            variable_set('pushassist_secretKey', $account_details['apiSecret']);
            variable_set('pushassist_jsPath', $account_details['jsPath']);
            variable_set('pushassist_remainSubscribers', $account_details['subscribers_remain']);
            variable_set('pushassist_accountName', $account_details['account_name']);
            variable_set('pushassist_imagePath', $account_details['site_image']);

            variable_set('pushassist_setting_utm_source', 'pushassist');
            variable_set('pushassist_setting_utm_medium', 'pushassist_notification');
            variable_set('pushassist_setting_utm_campaign', 'pushassist');
            variable_set('pushassist_auto_push_message', 'We have just published an article, check it out!');

            drupal_set_message(t("Login Successful."));

            drupal_goto('admin/config/administration/pushassist/pushassist_menu');

        } else if (isset($account_details['error'])) {

            form_set_error(t($account_details['error']));
            $form_state['rebuild'] = TRUE;

        } else {

            form_set_error(t($account_details['errors']));
            $form_state['rebuild'] = TRUE;
        }

    } else {

        if ($account_create_info['status'] == 'Error') {

            form_set_error('pushassist_account_name', t($account_create_info['error_message']));

        } else {

            form_set_error('pushassist_account_name', t($account_create_info['errors']));
        }
    }
}


function pushassist_account_verify_validate($form, &$form_state)
{

    $pushassist_auth_api_key = $form_state['values']['pushassist_auth_api_key'];

    $pushassist_auth_secret_key = $form_state['values']['pushassist_auth_secret_key'];

    if (empty($pushassist_auth_api_key)) {

        form_set_error('pushassist_auth_api_key', t('API Key Can not be Empty.'));
        return false;
    }

    if (empty($pushassist_auth_secret_key)) {

        form_set_error('pushassist_auth_secret_key', t('Secret Key Can not be Empty.'));
        return false;
    }

}

function pushassist_account_verify_submit($form, &$form_state)
{
    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_auth_api_key = $form_state['values']['pushassist_auth_api_key'];

    $pushassist_auth_secret_key = $form_state['values']['pushassist_auth_secret_key'];

    $account_info = pushassist_login($pushassist_auth_api_key, $pushassist_auth_secret_key);

    $account_details = json_decode($account_info->data, true);

    if (isset($account_details['apiKey']) && isset($account_details['apiSecret'])) {

        variable_set('pushassist_apiKey', $account_details['apiKey']);
        variable_set('pushassist_secretKey', $account_details['apiSecret']);
        variable_set('pushassist_jsPath', $account_details['jsPath']);
        variable_set('pushassist_remainSubscribers', $account_details['subscribers_remain']);
        variable_set('pushassist_accountName', $account_details['account_name']);
        variable_set('pushassist_imagePath', $account_details['site_image']);

        variable_set('pushassist_setting_utm_source', 'pushassist');
        variable_set('pushassist_setting_utm_medium', 'pushassist_notification');
        variable_set('pushassist_setting_utm_campaign', 'pushassist');
        variable_set('pushassist_auto_push_message', 'We have just published an article, check it out!');

        drupal_set_message(t("Login Successful."));

    } else if (isset($account_details['error'])) {

        drupal_set_message(t($account_details['error']));
        $form_state['rebuild'] = TRUE;

    } else {

        drupal_set_message(t($account_details['errors']));
        $form_state['rebuild'] = TRUE;
    }
}


function pushassist_dashboard()
{
    global $base_url;

    $favicon = $base_url . base_path() . drupal_get_path('module', 'pushassist') . '/images/pushassist_default.png';

    $form['#attached']['css'] = array(
        drupal_get_path('module', 'pushassist') . '/css/pushassist.css',
    );

    $type = theme_get_setting('favicon_mimetype');

    drupal_add_html_head_link(

        array(
            'rel' => 'shortcut icon',
            'href' => $favicon,
            'type' => $type,
        )
    );

    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    $pushassist_accountName = variable_get('pushassist_accountName', '');

    $account_info = pushassist_login($pushassist_apikey, $pushassist_secretkey);

    $account_details = json_decode($account_info->data, true);

    if ($account_details) {

        variable_set('pushassist_apiKey', $account_details['apiKey']);
        variable_set('pushassist_secretKey', $account_details['apiSecret']);
        variable_set('pushassist_jsPath', $account_details['jsPath']);
        variable_set('pushassist_remainSubscribers', $account_details['subscribers_remain']);
        variable_set('pushassist_accountName', $account_details['account_name']);
        variable_set('pushassist_imagePath', $account_details['site_image']);
    }

    $dashboard_details = pushassist_dashboard_stats($pushassist_apikey, $pushassist_secretkey);

    if (isset($dashboard_details)) {

        $dashboard_info = json_decode($dashboard_details->data, true);

        $form['dashboard'] = array(
            '#prefix' => '<div id="pushassist" class="content dashboard clearfix"><div class="page-header">
            <h1 class="title">Dashboard</h1>',
            '#markup' => '<div class="sub_count"><span>' . $account_details['subscribers_remain'] . ' subscribers left</span>
				<a href="https://' . check_plain($pushassist_accountName) . '.pushassist.com/dashboard/" target="_blank">Upgrade to Premium</a></div>',
            '#suffix' => '</div>',
        );

        $form['dashboard-stats'] = array(
            '#prefix' => '<div class="container-widget clearfix"><div class="col-md-12"><ul class="topstats clearfix">',
        );

        if ($dashboard_info['delivered_change'] == 'negative') {

            $delivered_change = '<b class="color-down"><i class="fa fa-caret-down"></i>';

        } else {

            $delivered_change = '<b class="color-up"><i class="fa fa-caret-up"></i>';
        }

        $form['dashboard-stats']['total-delivered'] = array(

            '#markup' => '<li class="col-xs-6 col-lg-2">
                        <span class="title"><i class="fa fa-send"></i> Total Delivered </span>
                        <h3>' . number_format($dashboard_info['total_delivered']) . '</h3> <span class="diff">' .
                $delivered_change . ' ' .
                $dashboard_info['delivered_percentage'] . '%
						</b> from last week</span>
                    </li>',
        );

        if ($dashboard_info['clicks_change'] == 'negative') {

            $clicks_change = '<b class="color-down"><i class="fa fa-caret-down"></i>';

        } else {

            $clicks_change = '<b class="color-up"><i class="fa fa-caret-up"></i>';
        }

        $form['dashboard-stats']['total-clicks'] = array(

            '#markup' => '<li class="col-xs-6 col-lg-2">
                        <span class="title"><i class="fa fa-check-square-o"></i> Total Clicks </span>
                        <h3 class="color-up">' . number_format($dashboard_info['total_clicks']) . '</h3> <span class="diff">' .
                $clicks_change . ' ' .
                $dashboard_info['clicks_percentage'] . '%
						</b> from last week</span>
                    </li>',
        );

        if ($dashboard_info['active_subscribers_change'] == 'negative') {

            $subscribers_change = '<b class="color-down"><i class="fa fa-caret-down"></i>';

        } else {

            $subscribers_change = '<b class="color-up"><i class="fa fa-caret-up"></i>';
        }

        $form['dashboard-stats']['active_subscribers'] = array(

            '#markup' => '<li class="col-xs-6 col-lg-2">
                        <span class="title"><i class="fa fa-users"></i> Active Subscribers </span>
                        <h3>' . number_format($dashboard_info['active_subscribers']) . '</h3> <span class="diff">' .
                $subscribers_change . ' ' .
                $dashboard_info['active_subscribers_percentage'] . '%
						</b> from last week</span>
                    </li>',
        );

        if ($dashboard_info['unsubscribed_change'] == 'negative') {

            $subscribers_change = '<b class="color-up"><i class="fa fa-caret-up"></i>';

        } else {

            $subscribers_change = '<b class="color-down"><i class="fa fa-caret-down"></i>';
        }

        $form['dashboard-stats']['unsubscribed'] = array(

            '#markup' => '<li class="col-xs-6 col-lg-2">
                        <span class="title"><i class="fa fa-users"></i> Unsubscribed </span>
                        <h3>' . number_format($dashboard_info['unsubscribed']) . '</h3> <span class="diff">' .
                $subscribers_change . ' ' .
                $dashboard_info['unsubscribed_percentage'] . '%
						</b> from last week</span>
                    </li>',
        );

        $form['dashboard-stats']['total-campaign'] = array(

            '#markup' => '<li class="col-xs-6 col-lg-2"> <span class="title"><i class="fa  fa-cogs"></i> Campaigns </span> <h3 class="color-up">' . number_format($dashboard_info['campaign_count']) . '</h3>
						<span class="diff"><b class="color-down"></b> active this week </span> </li>',
        );

        $form['dashboard-stats']['total-segments'] = array(

            '#markup' => '<li class="col-xs-6 col-lg-2"> <span class="title"><i class="fa  fa-send"></i> Segments </span> <h3 class="color-up">' . number_format($dashboard_info['segment_count']) . '</h3>
						<span class="diff"><b class="color-down"></b> created </span> </li>',
        );

        $form['sidebar'] = array(

            '#prefix' => '<div class="col-md-2 col-lg-2">
                                <div class="sidebar clearfix">
                                    <ul class="sidebar-panel nav">
                                        <li><span class="icon color5"><i class="fa fa-home"></i></span>' . l(t('Dashboard'), 'admin/config/administration/pushassist/pushassist_menu') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-bell"></i></span>' . l(t('Notifications'), 'admin/config/administration/pushassist/notification_details') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-send"></i></span>' . l(t('Send Notification'), 'admin/config/administration/pushassist/new_notification') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-object-ungroup"></i></span>' . l(t('Segments'), 'admin/config/administration/pushassist/segment_details') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gear"></i></span>' . l(t('Create Segment'), 'admin/config/administration/pushassist/create_segment') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-users"></i></span>' . l(t('Subscribers'), 'admin/config/administration/pushassist/subscribers') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gears"></i></span>' . l(t('Settings'), 'admin/config/administration/pushassist/pushassist_settings') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-hourglass-start"></i></span>' . l(t('Campaigns'), 'admin/config/administration/pushassist/pushassist_campaigns') . '</li>',
            '#suffix' => '</ul></div></div>',
        );

        $form['dashboard-notifications'] = array(

            '#prefix' => '<div class="col-md-10 col-lg-10">
                <div class="panel panel-widget">',
        );

        $form['dashboard-notifications']['table'] = array(

            '#markup' => '<div class="panel-body table-responsive">
                        <table class="table table-hover">
                            <thead>
                            <tr>
                                <td>#</td>
                                <td>Site</td>
                                <td>Message</td>
                                <td style="width: 100px;">Total Sent</td>
                                <td style="width: 100px;">Delivered</td>
                                <td style="width: 100px;">Unsubscribed</td>
                                <td style="width: 110px;">Clicked</td>
                                <td>Created Date</td>
                                <td style="width: 105px;">Is Campaign</td>
                            </tr>
                            </thead>
                            <tbody>',
        );

        if ($dashboard_info['last_notifications']) {

            $no = 1;

            foreach ($dashboard_info['last_notifications'] as $row) {

                $total_sent = $row['total_sent'] + $row['failed'];

                if($row['total_sent'] != 0) {

                    $percentChange = ($row['total_clicked'] / $row['total_sent']) * 100;

                } else {

                    $percentChange = 0;
                }

                $percentChange = round(abs($percentChange), 2);

                if ($row['campaign_flag'] > 0) {

                    $is_campaign = 'Yes';

                } else {

                    $is_campaign = 'No';
                }

                $form['dashboard-notifications']['table-row' . $no] = array(

                    '#markup' => '<tr>
                                        <td>' . $no . '</td>
                                        <td>' . $row['siteURL'] . '</td>
                                        <td>
                                            <h5 class="margin-t-0">' . $row['title'] . '</h5>
                                            <p class="margin-b-5">' . $row['message'] . '</p>
                                            <a href="' . $row['url'] . '"
                                               target="_blank">' . $row['url'] . '</a>
                                        </td>
                                        <td>' . number_format($total_sent) . '</td>
                                        <td>' . number_format($row['total_sent']) . '</td>
                                        <td>' . number_format($row['failed']) . '</td>
                                        <td>' . number_format($row['total_clicked']) . '
											<b class="color-up margin-l-15"> ' . (int)$percentChange . '% </b>
										</td>
                                        <td>' . date('M d, Y ,  h:m:s', strtotime($row['created_at'])) . '</td>
                                        <td>' . $is_campaign . '</td>
                                    </tr>',
                );

                $no++;
            }

        } else {

            $form['dashboard-notifications']['table-row'] = array(

                '#markup' => '<tr><td colspan="9" class="center"> No Record Found.</td>',
                '#suffix' => '</tbody></table></div></div></div>',
            );
        }

        return $form;
    }
}

function pushassist_notification_details_view()
{
    $form['#attached']['css'] = array(
        drupal_get_path('module', 'pushassist') . '/css/pushassist.css',
    );

    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    $notification_history = pushassist_notification_details($pushassist_apikey, $pushassist_secretkey);

    $form['dashboard-notifications'] = array(

        '#prefix' => '<div id="pushassist" class="content dashboard clearfix"><div class="page-header">
                    <h1 class="title">Sent Notifications</h1>',
        '#markup' => '<div class="sub_count"> <a href="' . 'admin/config/administration/pushassist/new_notification' . '">Send New Notification</a></div>',
        '#suffix' => '</div><div class="container-widget clearfix">',
    );

    $form['sidebar'] = array(

        '#prefix' => '<div class="col-md-2 col-lg-2">
                                <div class="sidebar clearfix">
                                    <ul class="sidebar-panel nav">
                                        <li><span class="icon color5"><i class="fa fa-home"></i></span>' . l(t('Dashboard'), 'admin/config/administration/pushassist/pushassist_menu') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-bell"></i></span>' . l(t('Notifications'), 'admin/config/administration/pushassist/notification_details') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-send"></i></span>' . l(t('Send Notification'), 'admin/config/administration/pushassist/new_notification') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-object-ungroup"></i></span>' . l(t('Segments'), 'admin/config/administration/pushassist/segment_details') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gear"></i></span>' . l(t('Create Segment'), 'admin/config/administration/pushassist/create_segment') . '</li>
                                        <li><span class="icon color8"><i class="fa  fa-users"></i></span>' . l(t('Subscribers'), 'admin/config/administration/pushassist/subscribers') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gears"></i></span>' . l(t('Settings'), 'admin/config/administration/pushassist/pushassist_settings') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-hourglass-start"></i></span>' . l(t('Campaigns'), 'admin/config/administration/pushassist/pushassist_campaigns') . '</li>',
        '#suffix' => '</ul></div></div>',
    );

    $form['notifications-details-table']['table'] = array(

        '#markup' => '<div class="col-md-10 col-lg-10">
                <div class="panel panel-widget">
                    <div class="panel-body table-responsive">
                        <table class="table table-hover">
                            <thead>
                            <tr>
                                <td>#</td>
                                <td>Site</td>
                                <td>Message</td>
                                <td>Total Sent</td>
                                <td>Delivered</td>
                                <td>Unsubscribed</td>
                                <td>Clicked</td>
                                <td>Created Date</td>
                            </tr>
                            </thead>
                            <tbody>'
    );

    if (isset($notification_history)) {

        $notification_info = json_decode($notification_history->data, true);

        $no = 1;

        if ($notification_info) {

            foreach ($notification_info as $row) {

                $total_sent = ($row['total_sent'] + $row['failed']);

                $percentChange = ($row['total_clicked'] / $row['total_sent']) * 100;

                $percentChange = round(abs($percentChange), 2);

                /*
                if ($row['campaign_flag'] > 0) {

                    $is_campaign = 'Yes';

                } else {

                    $is_campaign = 'No';
                }
                */

                $form['notifications-details-table']['table-row' . $no] = array(

                    '#markup' => '<tr>
                                        <td>' . $no . '</td>
                                        <td>' . $row['siteurl'] . '</td>
                                        <td>
                                            <div class="col-sm-3 table_image">
                                                <img alt="Notification Logo"
                                                     src="' . $row['logo'] . '">
                                            </div>

                                            <h5 class="margin-t-0">' . $row['title'] . '</h5>
                                            <p class="margin-b-5">' . $row['message'] . '</p>
                                            <a href="' . $row['redirecturl'] . '"
                                               target="_blank">' . $row['redirecturl'] . '</a>
                                        </td>
                                        <td>' . number_format($total_sent) . '</td>
                                        <td>' . number_format($row['total_sent']) . '</td>
                                        <td>' . number_format($row['failed']) . '</td>
                                        <td>' . number_format($row['total_clicked']) . '
											<b class="color-up margin-l-15"> ' . (int)$percentChange . '% </b>
										</td>
                                        <td>' . date('M d, Y ,  h:m:s', strtotime($row['created_at'])) . '</td>
                                    </tr>',
                );

                $no++;
            }
        }
    } else {

        $form['notifications-details-table']['table-row'] = array(

            '#markup' => '<tr><td colspan="9" class="center"> No Record Found.</td>',
            '#suffix' => '</tbody></table></div></div></div>',
        );
    }

    return $form;
}


function pushassist_segment_details_view()
{
    $form['#attached']['css'] = array(
        drupal_get_path('module', 'pushassist') . '/css/pushassist.css',
    );

    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    $segment_history = pushassist_segment_details($pushassist_apikey, $pushassist_secretkey);

    $form['dashboard-segment'] = array(

        '#prefix' => '<div id="pushassist" class="content dashboard clearfix"><div class="page-header">
                    <h1 class="title">Segment Details</h1>',
        '#markup' => '<div class="sub_count"> <a href="admin/config/administration/pushassist/create_segment">Add New</a></div>',
        '#suffix' => '</div><div class="container-widget clearfix">',
    );

    $form['sidebar'] = array(

        '#prefix' => '<div class="col-md-2 col-lg-2">
                                <div class="sidebar clearfix">
                                    <ul class="sidebar-panel nav">
                                        <li><span class="icon color5"><i class="fa fa-home"></i></span>' . l(t('Dashboard'), 'admin/config/administration/pushassist/pushassist_menu') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-bell"></i></span>' . l(t('Notifications'), 'admin/config/administration/pushassist/notification_details') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-send"></i></span>' . l(t('Send Notification'), 'admin/config/administration/pushassist/new_notification') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-object-ungroup"></i></span>' . l(t('Segments'), 'admin/config/administration/pushassist/segment_details') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gear"></i></span>' . l(t('Create Segments'), 'admin/config/administration/pushassist/create_segment') . '</li>
                                        <li><span class="icon color8"><i class="fa  fa-users"></i></span>' . l(t('Subscribers'), 'admin/config/administration/pushassist/subscribers') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gears"></i></span>' . l(t('Settings'), 'admin/config/administration/pushassist/pushassist_settings') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-hourglass-start"></i></span>' . l(t('Campaigns'), 'admin/config/administration/pushassist/pushassist_campaigns') . '</li>',
        '#suffix' => '</ul></div></div>',
    );

    $form['segment-details-table']['table'] = array(

        '#markup' => '<div class="col-md-10 col-lg-10">
                <div class="panel panel-widget">
                    <div class="panel-body table-responsive">
                        <table class="table table-hover">
                            <thead>
                            <tr>
                                <td>#</td>
                                <td>Segment Name</td>
                                <td>Subscribers Count</td>
                                <td>Created Date</td>
                            </tr>
                            </thead>
                            <tbody>'
    );

    if (isset($segment_history)) {

        $segment_info = json_decode($segment_history->data, true);

        $no = 1;

        if ($segment_info) {

            foreach ($segment_info as $row) {

                $form['segment-details-table']['table-row' . $no] = array(

                    '#markup' => '<tr>
                                        <td>' . $no . '</td>
                                        <td>' . $row['name'] . '</td>
                                        <td>' . number_format($row['subscriber_count']) . '</td>
                                        <td>' . date('M d, Y ,  h:m:s', strtotime($row['created_at'])) . '</td>
                                    </tr>',
                );

                $no++;
            }
        }
    } else {

        $form['segment-details-table']['table-row'] = array(

            '#markup' => '<tr><td class="center" colspan="4"> <p>No Record Found. </p></td>',
            '#suffix' => '</tbody></table></div></div></div>',
        );
    }

    return $form;
}

function pushassist_subscirbers_view()
{
    $form['#attached']['css'] = array(
        drupal_get_path('module', 'pushassist') . '/css/pushassist.css',
    );

    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    $subscribers_history = pushassist_subscribers_details($pushassist_apikey, $pushassist_secretkey);

    $form['dashboard-subscribers'] = array(

        '#prefix' => '<div id="pushassist" class="content dashboard clearfix"><div class="page-header">
                    <h1 class="title">Subscribers Details</h1>',
        '#suffix' => '</div><div class="container-widget clearfix">',
    );

    $form['sidebar'] = array(

        '#prefix' => '<div class="col-md-2 col-lg-2">
                                <div class="sidebar clearfix">
                                    <ul class="sidebar-panel nav">
                                        <li><span class="icon color5"><i class="fa fa-home"></i></span>' . l(t('Dashboard'), 'admin/config/administration/pushassist/pushassist_menu') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-bell"></i></span>' . l(t('Notifications'), 'admin/config/administration/pushassist/notification_details') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-send"></i></span>' . l(t('Send Notification'), 'admin/config/administration/pushassist/new_notification') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-object-ungroup"></i></span>' . l(t('Segments'), 'admin/config/administration/pushassist/segment_details') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gear"></i></span>' . l(t('Create Segments'), 'admin/config/administration/pushassist/create_segment') . '</li>
                                        <li><span class="icon color8"><i class="fa  fa-users"></i></span>' . l(t('Subscribers'), 'admin/config/administration/pushassist/subscribers') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gears"></i></span>' . l(t('Settings'), 'admin/config/administration/pushassist/pushassist_settings') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-hourglass-start"></i></span>' . l(t('Campaigns'), 'admin/config/administration/pushassist/pushassist_campaigns') . '</li>',
        '#suffix' => '</ul></div></div>',
    );

    $form['subscribers-details-table']['table'] = array(

        '#markup' => '<div class="col-md-10 col-lg-10">
                <div class="panel panel-widget">
                    <div class="panel-body table-responsive">
                        <table class="table table-hover">
                            <thead>
                            <tr>
                                <td>#</td>
                                <td>Site URL</td>
                                <td>Chrome</td>
                                <td>Firefox</td>
                                <td>Safari</td>
                                <td>Total</td>
                                <td>Active</td>
                                <td>Unsubscribed</td>
                            </tr>
                            </thead>
                            <tbody>'
    );

    if (isset($subscribers_history)) {

        $subscribers_info = json_decode($subscribers_history->data, true);

        $no = 1;

        if ($subscribers_info) {

            foreach ($subscribers_info as $row) {

                $form['subscribers-details-table']['table-row' . $no] = array(

                    '#markup' => '<tr>
                                        <td>' . $no . '</td>
                                        <td>' . $row['siteurl'] . '</td>
                                        <td>' . number_format($row['Chrome']) . '</td>
                                        <td>' . number_format($row['Firefox']) . '</td>
                                        <td>' . number_format($row['Safari']) . '</td>
                                        <td>' . number_format($row['total']) . '</td>
                                        <td>' . number_format($row['active']) . '</td>
                                        <td>' . number_format($row['unsubscribed']) . '</td>
                                    </tr>',
                );

                $no++;
            }
        }
    } else {

        $form['subscribers-details-table']['table-row'] = array(

            '#markup' => '<tr><td colspan="5" class="center"> <p>No Record Found. </p></td>',
            '#suffix' => '</tbody></table></div></div></div>',
        );
    }

    return $form;
}

function pushassist_show_create_segment_form()
{

    return drupal_get_form('pushassist_create_segment');
}

function pushassist_create_segment()
{
    $form['#attached']['css'] = array(
        drupal_get_path('module', 'pushassist') . '/css/pushassist.css',
    );

    $form['sidebar'] = array(

        '#prefix' => '<div id="pushassist" class="content dashboard clearfix"><div class="page-header">
                    <h1 class="title">Create Segment</h1> </div><div class="container-widget clearfix"> <div class="col-md-2 col-lg-2">
                                <div class="sidebar clearfix">
                                    <ul class="sidebar-panel nav">
                                        <li><span class="icon color5"><i class="fa fa-home"></i></span>' . l(t('Dashboard'), 'admin/config/administration/pushassist/pushassist_menu') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-bell"></i></span>' . l(t('Notifications'), 'admin/config/administration/pushassist/notification_details') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-send"></i></span>' . l(t('Send Notification'), 'admin/config/administration/pushassist/new_notification') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-object-ungroup"></i></span>' . l(t('Segments'), 'admin/config/administration/pushassist/segment_details') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gear"></i></span>' . l(t('Create Segments'), 'admin/config/administration/pushassist/create_segment') . '</li>
                                        <li><span class="icon color8"><i class="fa  fa-users"></i></span>' . l(t('Subscribers'), 'admin/config/administration/pushassist/subscribers') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gears"></i></span>' . l(t('Settings'), 'admin/config/administration/pushassist/pushassist_settings') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-hourglass-start"></i></span>' . l(t('Campaigns'), 'admin/config/administration/pushassist/pushassist_campaigns') . '</li>',
        '#suffix' => '</ul></div></div>',
    );


    $form['pushassist-segment-form'] = array(

        '#prefix' => '<div id="pushassist_create_segment" class="col-md-5">',
        '#suffix' => '</div>',
    );

    $form['pushassist-segment-form']['pushassist_segment_name'] = array(
        '#prefix' => '<div class="form-setting">',
        '#type' => 'textfield',
        '#title' => t('Segment Name'),
        '#maxlength' => 40,
        '#required' => TRUE,
        '#attributes' => array('placeholder' => t('Segment Name')),
        '#description' => t('Limit 40 Characters. E.g. Google'),
    );

    $form['pushassist-segment-form']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Create Segment'),
        '#submit' => array('pushassist_create_segment_submit'),
        '#suffix' => '</div>',
    );

    $form['pushassist-segment-instruction'] = array(
        '#prefix' => '<div class="pull-right col-md-5 dummy-notification shadow panel panel-default">
                        <p class="h5 pb15"><strong>How to Implement Segments for your Push Notification Subscribers.</strong></p>
                        <div class="widget shadow dummy-notification-inner-wrapper pb15">
                        <p> <strong> Step 1 : </strong> Create a new segment. Go to Create Segments </p>
                        <p> <strong> Step 2 : </strong> Copy the following JavaScript code and paste it on your site page(s). </p>
                        <p> <strong> Subscribe for Single Segment </strong> </p>
                        <p>
                            &lt;script&gt;
                            <br>
                            &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; var _pa = [];<br>
                            &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; _pa.push(\'segmentname\');
                            <br>
                            &lt;/script&gt;
                        </p><p> <strong> Subscribe for Multiple Segment </strong> </p>
                        <p>
                            &lt;script&gt;
                            <br>
                            &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; var _pa = [];<br>
                            &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; _pa.push(\'segmentname1\', \'segmentname2\');
                            <br>
                            &lt;/script&gt;
                        </p>',
        '#suffix' => '</div></div>',
    );

    return $form;
}

function pushassist_create_segment_submit($form, &$form_state)
{
    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_segment_name = $form_state['values']['pushassist_segment_name'];

    $pushassist_segment_name = str_replace(' ', '+', $pushassist_segment_name);

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    if (empty($pushassist_segment_name)) {

        form_set_error('pushassist_segment_name', t('Segment Name Can not be Empty.'));
        return false;
    }

    $segment_response = pushassist_create_segment_api($pushassist_apikey, $pushassist_secretkey, $pushassist_segment_name);

    $segment_result = json_decode($segment_response->data, true);

    if ($segment_result['status'] == 'Success') {

        drupal_set_message(t($segment_result['response_message']));

        drupal_goto('admin/config/administration/pushassist/segment_details');

    } else if ($segment_result['status'] == 'Error') {

        drupal_set_message(t($segment_result['error']));

    } else if (isset($segment_result['error'])) {

        drupal_set_message(t($segment_result['error']));
        $form_state['rebuild'] = TRUE;

    } else {

        drupal_set_message(t($segment_result['errors']));
        $form_state['rebuild'] = TRUE;
    }
}

function pushassist_show_send_notification_form()
{

    return drupal_get_form('pushassist_send_notification');
}

function pushassist_send_notification()
{
    $segment_array = array();

    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    $pushassist_accountName = variable_get('pushassist_accountName', '');

    $pushassist_imagePath = variable_get('pushassist_imagePath', '');

    $segment_response = pushassist_segment_details($pushassist_apikey, $pushassist_secretkey);

    $segment_result = json_decode($segment_response->data, true);

    if ($segment_result) {

        foreach ($segment_result as $value) {

            $user_list = (array)$value;

            $segment_array[$user_list['id']] = $user_list['name'];
        }

    } else {

        $segment_array = array();
    }

    $form['#attached']['css'] = array(
        drupal_get_path('module', 'pushassist') . '/css/pushassist.css',
    );

    $form['#attached']['js'] = array(
        drupal_get_path('module', 'pushassist') . '/js/pushassist.js',
    );

    $form['sidebar'] = array(

        '#prefix' => '<div id="pushassist" class="content dashboard clearfix"><div class="page-header">
                    <h1 class="title">New Notification</h1> </div><div class="container-widget clearfix"> <div class="col-md-2 col-lg-2">
                                <div class="sidebar clearfix">
                                    <ul class="sidebar-panel nav">
                                        <li><span class="icon color5"><i class="fa fa-home"></i></span>' . l(t('Dashboard'), 'admin/config/administration/pushassist/pushassist_menu') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-bell"></i></span>' . l(t('Notifications'), 'admin/config/administration/pushassist/notification_details') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-send"></i></span>' . l(t('Send Notification'), 'admin/config/administration/pushassist/new_notification') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-object-ungroup"></i></span>' . l(t('Segments'), 'admin/config/administration/pushassist/segment_details') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gear"></i></span>' . l(t('Create Segments'), 'admin/config/administration/pushassist/create_segment') . '</li>
                                        <li><span class="icon color8"><i class="fa  fa-users"></i></span>' . l(t('Subscribers'), 'admin/config/administration/pushassist/subscribers') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gears"></i></span>' . l(t('Settings'), 'admin/config/administration/pushassist/pushassist_settings') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-hourglass-start"></i></span>' . l(t('Campaigns'), 'admin/config/administration/pushassist/pushassist_campaigns') . '</li>',
        '#suffix' => '</ul></div></div>',
    );

    $form['pushassist-send-notification-form'] = array(
        '#prefix' => '<div class="col-md-5"><div id="pushassist_send_notification" class="form-setting">',
        '#suffix' => '</div></div>',
    );

    $form['pushassist-send-notification-form']['pushassist_notification_title'] = array(
        '#type' => 'textfield',
        '#title' => t('Notification Title'),
        '#maxlength' => 77,
        '#required' => TRUE,
        '#attributes' => array('placeholder' => t('Notification Title')),
        '#description' => t('Limit 77 Characters'),
        '#id' => 'pushassist_notification_title',
    );

    $form['pushassist-send-notification-form']['pushassist_notification_message'] = array(
        '#type' => 'textfield',
        '#title' => t('Notification Message'),
        '#maxlength' => 138,
        '#required' => TRUE,
        '#attributes' => array('placeholder' => t('Notification Message')),
        '#description' => t('Limit 138 Characters'),
        '#id' => 'pushassist_notification_message',
    );

    $form['pushassist-send-notification-form']['pushassist_notification_url'] = array(
        '#type' => 'textfield',
        '#title' => t('Notification URL'),
        '#attributes' => array('placeholder' => t('Enter a URL to push your subscribers to (yoursite.com)')),
        '#id' => 'pushassist_notification_url',
    );

    $form['pushassist-send-notification-form']['pushassist_notification_logo'] = array(
        '#prefix' => '<span class="upload btn-success fileinput-button" id="logo_upload">',
        '#type' => 'file',
        '#title' => t('Notification Logo'),
        '#suffix' => '</span><p class="clearfix">Image size must be exactly 250x250px.</p>',
    );

    $form['pushassist-send-notification-form']['pushassist_is_utm_show'] = array(
        '#type' => 'checkbox',
        '#value' => 0,
        '#title' => t('Add UTM Parameters'),
        '#id' => 'pushassist_is_utm_show',
    );

    $form['pushassist-send-notification-form']['pushassist_is_utm_show_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => 0,
        '#attributes' => array(
            'id' => 'pushassist_is_utm_show_hidden',
        )
    );

    $form['pushassist-send-notification-form']['pushassist_notification_utm_source'] = array(
        '#prefix' => '<div id="pushassist_notification_utm_source_div" style="display: none;">',
        '#type' => 'textfield',
        '#title' => t('UTM Source'),
        '#maxlength' => 45,
        '#default_value' => 'pushassist',
        '#attributes' => array('placeholder' => t('UTM Source')),
        '#description' => t('Limit 45 Characters'),
        '#id' => 'pushassist_notification_utm_source',
        '#suffix' => '</div>',
    );

    $form['pushassist-send-notification-form']['pushassist_notification_utm_medium'] = array(
        '#prefix' => '<div id="pushassist_notification_utm_medium_div" style="display: none;">',
        '#type' => 'textfield',
        '#title' => t('UTM Medium'),
        '#maxlength' => 73,
        '#default_value' => 'pushassist_notification',
        '#attributes' => array('placeholder' => t('UTM Medium')),
        '#description' => t('Limit 73 Characters'),
        '#id' => 'pushassist_notification_utm_medium',
        '#suffix' => '</div>',
    );

    $form['pushassist-send-notification-form']['pushassist_notification_utm_campaign'] = array(
        '#prefix' => '<div id="pushassist_notification_utm_campaign_div" style="display: none;">',
        '#type' => 'textfield',
        '#title' => t('UTM Campaign'),
        '#maxlength' => 500,
        '#default_value' => 'pushassist',
        '#attributes' => array('placeholder' => t('UTM Campaign')),
        '#description' => t('Limit 500 Characters'),
        '#id' => 'pushassist_notification_utm_campaign',
        '#suffix' => '</div>',
    );

    $form['pushassist-send-notification-form']['pushassist_notification_segment'] = array(
        '#type' => 'select',
        '#options' => $segment_array,
        '#title' => t('Segment'),
        '#multiple' => TRUE,
    );

    $form['pushassist-send-notification-form']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Send'),
    );

    $form['pushassist-segment-instruction'] = array(
        '#prefix' => '<div class="col-md-5 dummy-notification shadow panel panel-default notification-preview">
                <p class="h4 pb15">Preview</p>
                <div class="widget shadow dummy-notification-inner-wrapper">
                    <div class="wrapper">
                        <div class="img_wrapper pull-left">
                            <img id="logo" src="' . $pushassist_imagePath . '" class="img-responsive">
                        </div>
                        <div class="text_wrapper pull-left">
                            <div class="title">
                                <div class="title_txt pull-left" id="preview_notification_title">
                                    Notification Title
                                </div>
                                <div class="closer pull-right">
                                    x
                                </div>
                            </div>
                            <div class="message" id="preview_notification_message">
                                Notification Message
                            </div>

                            <div class="domain">
                                <div class="domain">
                                    ' . $pushassist_accountName . '.' . 'pushassist.com </div>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="widget">
                    <p class="h5" id="preview_redirect_url" name="redirect_url" style="padding-left: 50px;">URL to open when user clicks the notification:</p>
                </div>',
        '#suffix' => '</div>',
    );

    return $form;
}

function pushassist_send_notification_submit($form, &$form_state)
{
    $segment_array = array();

    $regex = "((https?|ftp)\:\/\/)?"; // SCHEME
    $regex .= "([a-z0-9+!*(),;?&=\$_.-]+(\:[a-z0-9+!*(),;?&=\$_.-]+)?@)?"; // User and Pass
    $regex .= "([a-z0-9-.]*)\.([a-z]{2,4})"; // Host or IP
    $regex .= "(\:[0-9]{2,5})?"; // Port
    $regex .= "(\/([a-z0-9+\$_-]\.?)+)*\/?"; // Path
    $regex .= "(\?[a-z+&\$_.-][a-z0-9;:@&%=+\/\$_.-]*)?"; // GET Query
    $regex .= "(#[a-z_.-][a-z0-9+\$_.-]*)?"; // Anchor
    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_notification_title = $form_state['values']['pushassist_notification_title'];

    $pushassist_notification_message = $form_state['values']['pushassist_notification_message'];

    $pushassist_notification_url = $form_state['values']['pushassist_notification_url'];

    $pushassist_is_utm_show_hidden = $form_state['values']['pushassist_is_utm_show_hidden'];

    $pushassist_notification_utm_source = $form_state['values']['pushassist_notification_utm_source'];

    $pushassist_notification_medium = $form_state['values']['pushassist_notification_utm_medium'];

    $pushassist_notification_utm_campagin = $form_state['values']['pushassist_notification_utm_campaign'];

    if ($pushassist_is_utm_show_hidden != 1) {

        $pushassist_notification_utm_source = '';
        $pushassist_notification_medium = '';
        $pushassist_notification_utm_campagin = '';
    }

    $pushassist_notification_segment = array_filter($form_state['values']['pushassist_notification_segment']);

    $pushassist_notification_logo_obj = file_save_upload('pushassist_notification_logo', '', 'public://');

    if (isset($pushassist_notification_logo_obj->filename)) {

        $notification_logo_path = file_create_url($pushassist_notification_logo_obj->uri);

    } else {

        $notification_logo_path = '';
    }

    if (count($pushassist_notification_segment) > 0) {

        foreach ($pushassist_notification_segment as $value) {

            $segment_array[] = (int)$value;
        }

    } else {

        $segment_array = array();
    }

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    if (empty($pushassist_notification_title)) {

        form_set_error('pushassist_notification_title', t('Notification Title can not be empty.'));
        return false;
    }

    if (empty($pushassist_notification_message)) {

        form_set_error('pushassist_notification_message', t('Notification Message can not be empty.'));
        return false;
    }

    if (!empty($pushassist_notification_url)) {

        if (!preg_match("/^$regex$/", $pushassist_notification_url)) {

            form_set_error('pushassist_notification_url', t('Please provide valid URL.'));
            return false;
        }
    }

    $notification_response = pushassist_send_notification_api($pushassist_apikey, $pushassist_secretkey, $pushassist_notification_title, $pushassist_notification_message, $pushassist_notification_url, $notification_logo_path, $pushassist_notification_utm_source, $pushassist_notification_medium, $pushassist_notification_utm_campagin, $segment_array);

    $notification_result = json_decode($notification_response->data, true);

    if ($notification_result['status'] == 'Success') {

        drupal_set_message(t($notification_result['response_message']));

        drupal_goto('admin/config/administration/pushassist/pushassist_menu');

    } else if ($notification_result['status'] == 'Error') {

        drupal_set_message(t($notification_result['error_message']));

    } else if (isset($notification_result['error'])) {

        drupal_set_message(t($notification_result['error']));
        $form_state['rebuild'] = TRUE;

    } else {

        drupal_set_message(t($notification_result['errors']));
        $form_state['rebuild'] = TRUE;
    }
}

function pushassist_settings_view()
{
    $output = array();

    $output['pushassist-setting-form'] = drupal_get_form('pushassist_settings');
    $output['pushassist-auto-send-notification-settings-form'] = drupal_get_form('pushassist_autopush_from');
    $output['pushassist-gcm-setting-form'] = drupal_get_form('gcm_setting_form');;

    return $output;
}

function pushassist_autopush_from(){

    $form['pushassist-auto-send-notification-settings-form'] = array(
        '#prefix' => '<div id="pushassist-autopush-settings" class="form-setting"> <strong> Auto Send Push Notifications </strong>',
    );

    $form['pushassist-auto-send-notification-settings-form']['pushassist_auto_push_publish'] = array(
        '#type' => 'checkbox',
        '#title' => t('When a Post is Published'),
        '#default_value' => variable_get('pushassist_auto_push_publish', FALSE),
    );

    $form['pushassist-auto-send-notification-settings-form']['pushassist_auto_push_update'] = array(
        '#type' => 'checkbox',
        '#title' => t('When a Post is Updated'),
        '#default_value' => variable_get('pushassist_auto_push_update', FALSE),
    );
	
	$form['pushassist-auto-send-notification-settings-form']['pushassist_auto_push_logo_img_post'] = array(
        '#type' => 'checkbox',
        '#title' => t('Use logo image as post image'),
        '#default_value' => variable_get('pushassist_auto_push_logo_img_post', FALSE),
    );

    $form['pushassist-auto-send-notification-settings-form']['pushassist_auto_push_UTMparameters'] = array(
        '#type' => 'checkbox',
        '#title' => t('Auto Push UTM Parameters'),
        '#default_value' => variable_get('pushassist_auto_push_UTMparameters', FALSE),
        '#id' => 'pushassist_auto_push_UTMparameters',
    );

    $hide_show = variable_get('pushassist_auto_push_UTMparameters', FALSE);

    if ($hide_show) {

        $class = 'block';

    } else {

        $class = 'none';
    }

    $form['pushassist-auto-send-notification-settings-form']['pushassist_setting_utm_source'] = array(
        '#prefix' => '<div id="pushassist_setting_utm_source_div" style="display:' . $class . ';">',
        '#type' => 'textfield',
        '#title' => t('UTM Source'),
        '#maxlength' => 45,
        '#default_value' => variable_get('pushassist_setting_utm_source', ''),
        '#attributes' => array('placeholder' => t('UTM Source')),
        '#required' => TRUE,
        '#description' => t('Limit 45 Characters'),
        '#id' => 'pushassist_notification_utm_source',
        '#suffix' => '</div>',
    );

    $form['pushassist-auto-send-notification-settings-form']['pushassist_setting_utm_medium'] = array(
        '#prefix' => '<div id="pushassist_setting_utm_medium_div" style="display: ' . $class . ';">',
        '#type' => 'textfield',
        '#title' => t('UTM Medium'),
        '#maxlength' => 73,
        '#default_value' => variable_get('pushassist_setting_utm_medium', ''),
        '#attributes' => array('placeholder' => t('UTM Medium')),
        '#required' => TRUE,
        '#description' => t('Limit 73 Characters'),
        '#id' => 'pushassist_notification_utm_medium',
        '#suffix' => '</div>',
    );

    $form['pushassist-auto-send-notification-settings-form']['pushassist_setting_utm_campaign'] = array(
        '#prefix' => '<div id="pushassist_setting_utm_campaign_div" style="display: ' . $class . ';">',
        '#type' => 'textfield',
        '#title' => t('UTM Campaign'),
        '#maxlength' => 500,
        '#default_value' => variable_get('pushassist_setting_utm_campaign', ''),
        '#attributes' => array('placeholder' => t('UTM Campaign')),
        '#required' => TRUE,
        '#description' => t('Limit 500 Characters'),
        '#id' => 'pushassist_notification_utm_campaign',
        '#suffix' => '</div>',
    );

    $form['pushassist-auto-send-notification-settings-form']['pushassist_auto_push_message'] = array(
        '#type' => 'textfield',
        '#title' => t('Notification message when a post is published'),
        '#maxlength' => 138,
        '#default_value' => variable_get('pushassist_auto_push_message', ''),
        '#attributes' => array('placeholder' => t('Notification message when a post is published')),
        '#required' => TRUE,
        //'#description' => t('Limit 138 Characters'),
        '#id' => 'pushassist_auto_push_message',
    );

    $form['pushassist-auto-send-notification-settings-form']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save Settings'),
        '#validate' => array('pushassist_auto_notification_validate'),
        '#submit' => array('pushassist_auto_notification_submit'),
        '#suffix' => '</div> </div>',
    );

    return $form;
}

function gcm_setting_form(){

    module_load_include('inc', 'pushassist', 'pushassist.api');

    $image_path = base_path() . drupal_get_path('module', 'pushassist') . '/images/pushassist_opt_in_box_setting.png';

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    $account_info = pushassist_login($pushassist_apikey, $pushassist_secretkey);

    $account_details = json_decode($account_info->data, true);

    $form['pushassist-gcm-setting-form'] = array(
        '#prefix' => '<div class="col-md-5" id="pushassist-gcm-setting"><div class="form-setting"> <div class="margin-b-40"> <p><strong>What is a GCM Key? How do I get export my subscribers, What if I want to switch to other
                            vendor.</strong></p>
                    <p class="margin-b-15 margin-t-15">At the time of installation, you have to provide your GCM (Google
                        Cloud Messaging) API Key for Chrome and Certificate Details for Safari that is used.</p>
                    <p>We need this information to export your subscriber’s ID’s. Please note that only premium accounts
                        can export the subscribers.</p>
                    <p class="margin-b-15 margin-t-15"> Please read <a target="_blank" style="color: #0000ff !important;" href="https://pushassist.com/adding-your-own-gcm-key-project-id-in-pushassist/"> GCM registration</a> guidelines here. </p> </div> ',
    );

    $form['pushassist-gcm-setting-form']['pushassist_gcm_project_number'] = array(
        '#type' => 'textfield',
        '#title' => t('GCM Project No.'),
        '#default_value' => $account_details['gcm_project_number'],
        '#required' => TRUE,
        '#attributes' => array('placeholder' => t('GCM Project No.')),
        '#id' => 'pushassist_gcm_project_number',
    );

    $form['pushassist-gcm-setting-form']['pushassist_gcm_project_api'] = array(
        '#type' => 'textfield',
        '#title' => t('GCM API Key'),
        '#required' => TRUE,
        '#default_value' => $account_details['gcm_api_key'],
        '#attributes' => array('placeholder' => t('GCM API Key')),
        '#id' => 'pushassist_gcm_project_api',
    );

    $form['pushassist-gcm-setting-form']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save Settings'),
        '#validate' => array('pushassist_gcm_setting_form_validate'),
        '#submit' => array('pushassist_gcm_setting_form_submit'),
        '#suffix' => '<hr class="margin-b-20 margin-t-20"> <p class="margin-b-15">Screenshot of advance configurations that are possible with your PushAssist account. &nbsp;&nbsp;&nbsp;
                        <a target="_blank" class="btn btn-default margin-t-0" href="https://' . $account_details['account_name'] . '.pushassist.com/allsites/">Customize Now</a>
                    </p> <img class="margin-b-15 margin-t-15" src="' . $image_path . '" alt="Advance Configuration"></div></div>',
    );

    return $form;
}

function pushassist_settings()
{
    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    $account_info = pushassist_login($pushassist_apikey, $pushassist_secretkey);

    $account_details = json_decode($account_info->data, true);

    $template = array('1' => 'Default', '2' => 'Template 1', '3' => 'Template 2', '4' => 'Template 3', '5' => 'Template 4', '6' => 'Template 5', '7' => 'Template 6', '8' => 'Template 7');

    $location = array('1' => 'Top Left', '2' => 'Top Right', '3' => 'Top Center', '4' => 'Bottom Left', '5' => 'Bottom Right', '6' => 'Bottom Center');
    $location_1 = array('1' => 'Top Left', '2' => 'Top Right', '4' => 'Bottom Left', '5' => 'Bottom Right');
    $location_2 = array('7' => 'Top', '8' => 'Bottom');

    $form['#attached']['css'] = array(
        drupal_get_path('module', 'pushassist') . '/css/pushassist.css',
    );

    $form['#attached']['js'] = array(
        drupal_get_path('module', 'pushassist') . '/js/pushassist.js',
    );

    $form['sidebar'] = array(

        '#prefix' => '<div id="pushassist" class="content dashboard clearfix"><div class="page-header">
                    <h1 class="title">Settings / Account Information</h1> </div><div class="container-widget clearfix"> <div class="col-md-2 col-lg-2">
                                <div class="sidebar clearfix">
                                    <ul class="sidebar-panel nav">
                                        <li><span class="icon color5"><i class="fa fa-home"></i></span>' . l(t('Dashboard'), 'admin/config/administration/pushassist/pushassist_menu') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-bell"></i></span>' . l(t('Notifications'), 'admin/config/administration/pushassist/notification_details') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-send"></i></span>' . l(t('Send Notification'), 'admin/config/administration/pushassist/new_notification') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-object-ungroup"></i></span>' . l(t('Segments'), 'admin/config/administration/pushassist/segment_details') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gear"></i></span>' . l(t('Create Segments'), 'admin/config/administration/pushassist/create_segment') . '</li>
                                        <li><span class="icon color8"><i class="fa  fa-users"></i></span>' . l(t('Subscribers'), 'admin/config/administration/pushassist/subscribers') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gears"></i></span>' . l(t('Settings'), 'admin/config/administration/pushassist/pushassist_settings') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-hourglass-start"></i></span>' . l(t('Campaigns'), 'admin/config/administration/pushassist/pushassist_campaigns') . '</li>',
        '#suffix' => '</ul></div></div>',
    );

    $form['pushassist-setting-form'] = array(
        '#prefix' => '<div class="col-md-5"><div id="pushassist_setting" class="form-setting">',
    );

    $form['pushassist-setting-form']['pushassist_interval'] = array(
        '#prefix' => '<div id="time_interval"> <p> Ask for permission after </p>',
        '#type' => 'textfield',
        '#attributes' => array(
            'data-type' => 'number',
            'placeholder' => t('Interval'),
            '#max' => 30,
        ),
        '#title' => t(''),
        '#default_value' => $account_details['notification_interval'],
        '#maxlength' => 2,
        '#id' => 'pushassist_interval',
        '#suffix' => '<p> seconds on your website. </p></div>',
    );

    $form['pushassist-setting-form']['pushassist_opt_in_title'] = array(
        '#type' => 'textfield',
        '#title' => t('Opt In Box Title'),
        '#default_value' => $account_details['opt_in_title'],
        '#maxlength' => 80,
        '#required' => TRUE,
        '#attributes' => array('placeholder' => t('Opt In Box Title')),
        '#description' => t('Limit 80 Characters'),
        '#id' => 'pushassist_opt_in_title',
    );

    $form['pushassist-setting-form']['pushassist_opt_in_subtitle'] = array(
        '#type' => 'textfield',
        '#title' => t('Opt In Box Subtitle'),
        '#default_value' => $account_details['opt_in_subtitle'],
        '#maxlength' => 105,
        '#required' => TRUE,
        '#attributes' => array('placeholder' => t('Opt In Box Subtitle')),
        '#description' => t('Limit 105 Characters'),
        '#id' => 'pushassist_opt_in_subtitle',
    );

    $form['pushassist-setting-form']['pushassist_allow_button_text'] = array(
        '#type' => 'textfield',
        '#title' => t('Allow Button Text'),
        '#default_value' => $account_details['allow_button'],
        '#maxlength' => 25,
        '#required' => TRUE,
        '#attributes' => array('placeholder' => t('Allow Button Text')),
        '#id' => 'pushassist_allow_button_text',
    );

    $form['pushassist-setting-form']['pushassist_disallow_button_text'] = array(
        '#type' => 'textfield',
        '#title' => t('Don\'t Allow Button Text'),
        '#default_value' => $account_details['disallow_button'],
        '#maxlength' => 25,
        '#required' => TRUE,
        '#attributes' => array('placeholder' => t('Don\'t Allow Button Text')),
        '#id' => 'pushassist_disallow_button_text',
    );

    $form['pushassist-setting-form']['pushassist_template'] = array(
        '#type' => 'select',
        '#options' => $template,
        '#title' => t('Notification Template'),
        '#default_value' => $account_details['template'],
        '#id' => 'pushassist_template',
    );

    if (isset($account_details['opt_in_location'])) {

        $hidden_location = $account_details['opt_in_location'];

    } else {

        $hidden_location = 1;
    }

    $form['pushassist-setting-form']['pushassist_hidden_template_location'] = array(
        '#type' => 'hidden',
        '#default_value' => $hidden_location,
        '#attributes' => array(
            'id' => 'pushassist_hidden_template_location',
        )
    );

    if ($account_details['template'] < 7 || $account_details['template'] == '1') {

        $class = 'block';

    } else {

        $class = 'none';
    }

    $form['pushassist-setting-form']['pushassist_location'] = array(
        '#prefix' => '<div id="pushassist_template_location" style="display:' . $class . '">',
        '#type' => 'select',
        '#options' => $location,
        '#title' => t('Template Location'),
        '#default_value' => $account_details['opt_in_location'],
        '#id' => 'pushassist_location',
        '#suffix' => '</div>',
    );

    if ($account_details['template'] == 7) {

        $class_1 = 'block';

    } else {

        $class_1 = 'none';
    }

    $form['pushassist-setting-form']['pushassist_location_l'] = array(
        '#prefix' => '<div id="pushassist_template_location_1" style="display:' . $class_1 . '">',
        '#type' => 'select',
        '#options' => $location_1,
        '#title' => t('Template Location'),
        '#default_value' => $account_details['opt_in_location'],
        '#id' => 'pushassist_location_1',
        '#suffix' => '</div>',
    );

    if ($account_details['template'] == 8) {

        $class_2 = 'block';

    } else {

        $class_2 = 'none';
    }

    $form['pushassist-setting-form']['pushassist_location_2'] = array(
        '#prefix' => '<div id="pushassist_template_location_2" style="display:' . $class_2 . '">',
        '#type' => 'select',
        '#options' => $location_2,
        '#title' => t('Template Location'),
        '#default_value' => $account_details['opt_in_location'],
        '#id' => 'pushassist_location_2',
        '#suffix' => '</div>',
    );

    $form['pushassist-setting-form']['pushassist_setting_logo'] = array(
        '#prefix' => '<span class="upload btn-success fileinput-button" id="logo_upload">',
        '#type' => 'file',
        '#title' => t('Site Logo'),
        '#suffix' => '</span><p class="clearfix">Image size must be exactly 250x250px.</p>',
    );

    if(empty($account_details['child_text'])){

        $child_window_text = 'Would Like to Send You Push Notifications. Click Allow to receive notifications.';

    } else {

        $child_window_text = $account_details['child_text'];
    }

    $form['pushassist-setting-form']['pushassist_child_text'] = array(
        '#prefix' => '<hr> <h5>Notification Subscription Setting</h5>',
        '#type' => 'textfield',
        '#title' => t('Opt-in Text'),
        '#default_value' => $child_window_text,
        '#maxlength' => 100,
        '#attributes' => array('placeholder' => t('Opt-in Text')),
        '#description' => t('Limit 100 Characters'),
        '#id' => 'pushassist_optin_text',
    );

    $form['pushassist-setting-form']['pushassist_child_title'] = array(
        '#type' => 'textfield',
        '#title' => t('Opt-in Title'),
        '#default_value' => $account_details['child_title'],
        '#maxlength' => 45,
        '#required' => TRUE,
        '#attributes' => array('placeholder' => t('Opt-in Title')),
        '#description' => t('Limit 45 Characters'),
        '#id' => 'pushassist_optin_title',
    );

    $form['pushassist-setting-form']['pushassist_child_message'] = array(
        '#type' => 'textfield',
        '#title' => t('Opt-in Message'),
        '#default_value' => $account_details['child_message'],
        '#maxlength' => 73,
        '#required' => TRUE,
        '#attributes' => array('placeholder' => t('Opt-in Message')),
        '#description' => t('Limit 73 Characters'),
        '#id' => 'pushassist_optin_subtitle',
    );

    $form['pushassist-setting-form']['pushassist_notification_title'] = array(
        '#prefix' => '<hr> <h5>Welcome Message for first time subscribers</h5>',
        '#type' => 'textfield',
        '#title' => t('Notification Title'),
        '#default_value' => $account_details['title'],
        '#maxlength' => 45,
        '#attributes' => array('placeholder' => t('Notification Title')),
        '#description' => t('Limit 45 Characters'),
        '#id' => 'pushassist_notification_title',
    );

    $form['pushassist-setting-form']['pushassist_notification_message'] = array(
        '#type' => 'textfield',
        '#title' => t('Notification Message'),
        '#default_value' => $account_details['message'],
        '#maxlength' => 73,
        '#attributes' => array('placeholder' => t('Notification Message')),
        '#description' => t('Limit 73 Characters'),
        '#id' => 'pushassist_notification_message',
    );

    $form['pushassist-setting-form']['pushassist_redirect_url'] = array(
        '#type' => 'textfield',
        '#title' => t('Redirect URL'),
        '#default_value' => $account_details['redirect_url'],
        '#attributes' => array('placeholder' => t('Redirect URL')),
        '#id' => 'pushassist_redirect_url',
    );

    $form['pushassist-setting-form']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save Settings'),
        '#submit' => array('pushassist_setting_form_submit'),
    );

    return $form;
}

function pushassist_setting_form_submit($form, $form_state)
{
    $values = $form_state['values'];

    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_interval = $values['pushassist_interval'];

    $pushassist_opt_in_title = $values['pushassist_opt_in_title'];

    $pushassist_opt_in_subtitle = $values['pushassist_opt_in_subtitle'];

    $pushassist_allow_button_text = $values['pushassist_allow_button_text'];

    $pushassist_disallow_button_text = $values['pushassist_disallow_button_text'];

    $pushassist_template = $values['pushassist_template'];

    $pushassist_hidden_template_location = $values['pushassist_hidden_template_location'];

    $pushassist_child_text = $values['pushassist_child_text'];

    $pushassist_child_title = $values['pushassist_child_title'];

    $pushassist_child_message = $values['pushassist_child_message'];

    $pushassist_notification_title = $values['pushassist_notification_title'];

    $pushassist_notification_message = $values['pushassist_notification_message'];

    $pushassist_redirect_url = $values['pushassist_redirect_url'];

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    if (!is_numeric($pushassist_interval)) {

        form_set_error('pushassist_interval', t('Opt-in Time interval should be digit.'));
        return false;
    }

    if ($pushassist_interval > 30) {

        form_set_error('pushassist_interval', t('Opt-in Time interval should not greater than 30.'));
        return false;
    }

    if (empty($pushassist_opt_in_title)) {

        form_set_error('pushassist_opt_in_title', t('Opt-in Box Title can not be empty.'));
        return false;
    }

    if (empty($pushassist_opt_in_subtitle)) {

        form_set_error('pushassist_opt_in_subtitle', t('Opt-in Box Subtitle can not be empty.'));
        return false;
    }

    if (empty($pushassist_allow_button_text)) {

        form_set_error('pushassist_allow_button_text', t('Allow Button Text can not be empty.'));
        return false;
    }

    if (empty($pushassist_disallow_button_text)) {

        form_set_error('pushassist_disallow_button_text', t('Dis Allow Button Text can not be empty.'));
        return false;
    }

    if (empty($pushassist_child_title)) {

        form_set_error('pushassist_child_title', t('Opt-in Title can not be empty.'));
        return false;
    }

    if (empty($pushassist_child_message)) {

        form_set_error('pushassist_child_message', t('Opt-in Message can not be empty.'));
        return false;
    }

    $pushassist_setting_logo_obj = file_save_upload('pushassist_setting_logo', '', 'public://');

    if ($pushassist_setting_logo_obj->filesize > 5000) {

        form_set_error('pushassist_setting_logo', t('Image Size should be 250x250px.'));
        return false;
    }

    if (isset($pushassist_setting_logo_obj->filename)) {

        $tm = time();

        $logo_path = file_create_url($pushassist_setting_logo_obj->uri);

        $image_name = $tm.'-'.$pushassist_setting_logo_obj->filename;

        $image_data = base64_encode(file_get_contents($logo_path));;

    } else {

        $image_data = '';

        $image_name = '';
    }

    $gcm_setting_response = pushassist_advance_setting_api($pushassist_apikey, $pushassist_secretkey, $pushassist_interval, $pushassist_opt_in_title, $pushassist_opt_in_subtitle, $pushassist_allow_button_text, $pushassist_disallow_button_text, $pushassist_template, $pushassist_hidden_template_location, $image_name, $image_data, $pushassist_child_text, $pushassist_child_title, $pushassist_child_message, $pushassist_notification_title, $pushassist_notification_message, $pushassist_redirect_url);

    $gcm_result = json_decode($gcm_setting_response->data, true);

    if ($gcm_result['status'] == 'Success') {

        drupal_set_message(t($gcm_result['response_message']));

        drupal_goto('admin/config/administration/pushassist/pushassist_settings');

    } else if ($gcm_result['status'] == 'Error') {

        drupal_set_message(t($gcm_result['error_message']));

    } else if (isset($gcm_result['error'])) {

        drupal_set_message(t($gcm_result['error']));
        $form_state['rebuild'] = TRUE;

    } else {

        drupal_set_message(t($gcm_result['errors']));
        $form_state['rebuild'] = TRUE;
    }
}

function pushassist_auto_notification_validate($form, $form_state)
{

    if (empty($form_state['values']['pushassist_setting_utm_source'])) {

        form_set_error('pushassist_setting_utm_source', t('UTM Source can not be empty.'));
        return false;

    } else if (empty($form_state['values']['pushassist_setting_utm_medium'])){

        form_set_error('pushassist_setting_utm_medium', t('UTM Medium can not be empty.'));
        return false;

    } else if (empty($form_state['values']['pushassist_setting_utm_campaign'])) {

        form_set_error('pushassist_setting_utm_campaign', t('UTM Campaign can not be empty.'));
        return false;
    }
}

function pushassist_auto_notification_submit($form, $form_state)
{

    variable_set('pushassist_auto_push_publish', $form_state['values']['pushassist_auto_push_publish']);
    variable_set('pushassist_auto_push_update', $form_state['values']['pushassist_auto_push_update']);
	variable_set('pushassist_auto_push_logo_img_post', $form_state['values']['pushassist_auto_push_logo_img_post']);

    variable_set('pushassist_auto_push_UTMparameters', $form_state['values']['pushassist_auto_push_UTMparameters']);

    if (isset($form_state['values']['pushassist_auto_push_UTMparameters'])) {

        variable_set('pushassist_setting_utm_source', $form_state['values']['pushassist_setting_utm_source']);
        variable_set('pushassist_setting_utm_medium', $form_state['values']['pushassist_setting_utm_medium']);
        variable_set('pushassist_setting_utm_campaign', $form_state['values']['pushassist_setting_utm_campaign']);

    } else {

        variable_set('pushassist_setting_utm_source', 'pushassist');
        variable_set('pushassist_setting_utm_medium', 'pushassist_notification');
        variable_set('pushassist_setting_utm_campaign', 'pushassist');
    }

    if (isset($form_state['values']['pushassist_auto_push_message'])) {

        variable_set('pushassist_auto_push_message', $form_state['values']['pushassist_auto_push_message']);

    } else {

        variable_set('pushassist_auto_push_message', 'We have just published an article, check it out!');
    }

    drupal_set_message(t("Setting Successfully Save."));

    drupal_goto('admin/config/administration/pushassist/pushassist_settings');
}

function pushassist_gcm_setting_form_validate($form, $form_state)
{
    $pushassist_gcm_project_number = $form_state['values']['pushassist_gcm_project_number'];

    $pushassist_gcm_project_api = $form_state['values']['pushassist_gcm_project_api'];

    if (empty($pushassist_gcm_project_number)) {

        form_set_error('pushassist_gcm_project_number', t('GCM Project Number can not be empty.'));
        return false;
    }

    if (empty($pushassist_gcm_project_api)) {

        form_set_error('pushassist_gcm_project_api', t('GCM Project API Key can not be empty.'));
        return false;
    }
}

function pushassist_gcm_setting_form_submit($form, $form_state)
{
    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_gcm_project_number = $form_state['values']['pushassist_gcm_project_number'];

    $pushassist_gcm_project_api = $form_state['values']['pushassist_gcm_project_api'];

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    $gcm_setting_response = pushassist_gcm_setting_api($pushassist_apikey, $pushassist_secretkey, $pushassist_gcm_project_number, $pushassist_gcm_project_api);

    $gcm_result = json_decode($gcm_setting_response->data, true);

    if ($gcm_result['status'] == 'Success') {

        drupal_set_message(t($gcm_result['response_message']));

        drupal_goto('admin/config/administration/pushassist/pushassist_settings');

    } else if ($gcm_result['status'] == 'Error') {

        drupal_set_message(t($gcm_result['error_message']));

    } else if (isset($gcm_result['error'])) {

        drupal_set_message(t($gcm_result['error']));
        $form_state['rebuild'] = TRUE;

    } else {

        drupal_set_message(t($gcm_result['errors']));
        $form_state['rebuild'] = TRUE;
    }
}

function pushassist_campaigns_view()
{
    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    $account_info = pushassist_login($pushassist_apikey, $pushassist_secretkey);

    $account_details = json_decode($account_info->data, true);

    if($account_details['planType']  == 'Free') {

        return drupal_get_form('pushassist_campaigns');

    } else {

        return drupal_get_form('pushassist_schedule_campaigns');
    }
}

function pushassist_schedule_campaigns(){

    drupal_add_library('system','ui.datepicker');
    drupal_add_js('jQuery(document).ready(function(){jQuery( ".pickadate" ).datepicker({
      dateFormat: "yy-mm-dd",
      autoSize: true
    });});', 'inline');

    $segment_array = array();

    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    $pushassist_accountName = variable_get('pushassist_accountName', '');

    $pushassist_imagePath = variable_get('pushassist_imagePath', '');

    $segment_response = pushassist_segment_details($pushassist_apikey, $pushassist_secretkey);

    $segment_result = json_decode($segment_response->data, true);

    if ($segment_result) {

        foreach ($segment_result as $value) {

            $user_list = (array)$value;

            $segment_array[$user_list['id']] = $user_list['name'];
        }

    } else {

        $segment_array = array();
    }
	
	$minute_array = array('00:00' => '00:00','00:10' => '00:10','00:20' => '00:20','00:30' => '00:30','00:40' => '00:40','00:50' => '00:50','01:00' => '01:00','01:10' => '01:10','01:20' => '01:20','01:30' => '01:30',
        '01:40' => '01:40','01:50' => '01:50','02:00' => '02:00','02:10' => '02:10','02:20' => '02:20','02:30' => '02:30','02:40' => '02:40','02:50' => '02:50','03:00' => '03:00','03:10' => '03:10','03:20' => '03:20', '03:30' => '03:30','03:40' => '03:40','03:50' => '03:50','04:00' => '04:00','04:10' => '04:10','04:20' => '04:20','04:30' => '04:30','04:40' => '04:40','04:50' => '04:50','05:00' => '05:00','05:10' => '05:10', '05:20' => '05:20','05:30' => '05:30','05:40' => '05:40','05:50' => '05:50','06:00' => '06:00','06:10' => '06:10','06:20' => '06:20','06:30' => '06:30','06:40' => '06:40','06:50' => '06:50','07:00' => '07:00', '07:10' => '07:10','07:20' => '07:20','07:30' => '07:30','07:40' => '07:40','07:50' => '07:50','08:00' => '08:00','08:10' => '08:10','08:20' => '08:20','08:30' => '08:30','08:40' => '08:40','08:50' => '08:50', '09:00' => '09:00','09:10' => '09:10','09:20' => '09:20','09:30' => '09:30','09:40' => '09:40','09:50' => '09:50','10:00' => '10:00','10:10' => '10:10','10:20' => '10:20','10:30' => '10:30','10:40' => '10:40', '10:50' => '10:50','11:00' => '11:00','11:10' => '11:10','11:20' => '11:20','11:30' => '11:30','11:40' => '11:40','11:50' => '11:50','12:00' => '12:00','12:10' => '12:10','12:20' => '12:20','12:30' => '12:30', '12:40' => '12:40','12:50' => '12:50','13:00' => '13:00','13:10' => '13:10','13:20' => '13:20','13:30' => '13:30','13:40' => '13:40','13:50' => '13:50','14:00' => '14:00','14:10' => '14:10','14:20' => '14:20', '14:30' => '14:30','14:40' => '14:40','14:50' => '14:50','15:00' => '15:00','15:10' => '15:10','15:20' => '15:20','15:30' => '15:30','15:40' => '15:40','15:50' => '15:50','16:00' => '16:00','16:10' => '16:10', '16:20' => '16:20','16:30' => '16:30','16:40' => '16:40','16:50' => '16:50','17:00' => '17:00','17:10' => '17:10','17:20' => '17:20','17:30' => '17:30','17:40' => '17:40','17:50' => '17:50','18:00' => '18:00', '18:10' => '18:10','18:20' => '18:20','18:30' => '18:30','18:40' => '18:40','18:50' => '18:50','19:00' => '19:00','19:10' => '19:10','19:20' => '19:20','19:30' => '19:30','19:40' => '19:40','19:50' => '19:50',
        '20:00' => '20:00','20:10' => '20:10','20:20' => '20:20','20:30' => '20:30','20:40' => '20:40','20:50' => '20:50','21:00' => '21:00','21:10' => '21:10','21:20' => '21:20','21:30' => '21:30','21:40' => '21:40', '21:50' => '21:50','22:00' => '22:00','22:10' => '22:10','22:20' => '22:20','22:30' => '22:30','22:40' => '22:40','22:50' => '22:50','23:00' => '23:00','23:10' => '23:10','23:20' => '23:20','23:30' => '23:30', '23:40' => '23:40','23:50' => '23:50');

    $timezones = array(
        'Pacific/Honolulu' => 'Hawaii',
        'US/Alaska' => 'Alaska',
        'America/Los_Angeles' => 'Pacific Time (US & Canada)',
        'US/Arizona' => 'Arizona',
        'US/Mountain' => 'Mountain Time (US & Canada)',
        'US/Central' => 'Central Time (US & Canada)',
        'US/Eastern' => 'Eastern Time (US & Canada)',
        'US/East-Indiana' => 'Indiana (East)',
        'Pacific/Midway' => 'Midway Island',
        'US/Samoa' => 'American Samoa',
        'America/Tijuana' => 'Tijuana',
        'America/Chihuahua' => 'Chihuahua',
        'America/Mazatlan' => 'Mazatlan',
        'America/Managua' => 'Central America',
        'America/Mexico_City' => 'Mexico City',
        'America/Monterrey' => 'Monterrey',
        'Canada/Saskatchewan' => 'Saskatchewan',
        'America/Bogota' => 'Bogota',
        'America/Lima' => 'Lima',
        'America/Bogota' => 'Quito',
        'Canada/Atlantic' => 'Atlantic Time (Canada)',
        'America/Caracas' => 'Caracas',
        'America/La_Paz' => 'La Paz',
        'America/Santiago' => 'Santiago',
        'Canada/Newfoundland' => 'Newfoundland',
        'America/Sao_Paulo' => 'Brasilia',
        'America/Argentina/Buenos_Aires' => 'Buenos Aires',
        'America/Godthab' => 'Greenland',
        'America/Noronha' => 'Mid-Atlantic',
        'Atlantic/Azores' => 'Azores',
        'Atlantic/Cape_Verde' => 'Cape Verde Is.',
        'Africa/Casablanca' => 'Casablanca',
        'Europe/Dublin' => 'Dublin',
        'Europe/Lisbon' => 'Lisbon',
        'Europe/London' => 'London',
        'Africa/Monrovia' => 'Monrovia',
        'UTC' => 'UTC',
        'Europe/Amsterdam' => 'Amsterdam',
        'Europe/Belgrade' => 'Belgrade',
        'Europe/Berlin' => 'Bern',
        'Europe/Bratislava' => 'Bratislava',
        'Europe/Brussels' => 'Brussels',
        'Europe/Budapest' => 'Budapest',
        'Europe/Copenhagen' => 'Copenhagen',
        'Europe/Ljubljana' => 'Ljubljana',
        'Europe/Madrid' => 'Madrid',
        'Europe/Paris' => 'Paris',
        'Europe/Prague' => 'Prague',
        'Europe/Rome' => 'Rome',
        'Europe/Sarajevo' => 'Sarajevo',
        'Europe/Skopje' => 'Skopje',
        'Europe/Stockholm' => 'Stockholm',
        'Europe/Vienna' => 'Vienna',
        'Europe/Warsaw' => 'Warsaw',
        'Africa/Lagos' => 'West Central Africa',
        'Europe/Zagreb' => 'Zagreb',
        'Europe/Athens' => 'Athens',
        'Europe/Bucharest' => 'Bucharest',
        'Africa/Cairo' => 'Cairo',
        'Africa/Harare' => 'Harare',
        'Europe/Helsinki' => 'Helsinki',
        'Europe/Istanbul' => 'Istanbul',
        'Asia/Jerusalem' => 'Jerusalem',
        'Europe/Helsinki' => 'Kyiv',
        'Africa/Johannesburg' => 'Pretoria',
        'Europe/Riga' => 'Riga',
        'Europe/Sofia' => 'Sofia',
        'Europe/Tallinn' => 'Tallinn',
        'Europe/Vilnius' => 'Vilnius',
        'Asia/Baghdad' => 'Baghdad',
        'Asia/Kuwait' => 'Kuwait',
        'Europe/Minsk' => 'Minsk',
        'Africa/Nairobi' => 'Nairobi',
        'Asia/Riyadh' => 'Riyadh',
        'Europe/Volgograd' => 'Volgograd',
        'Asia/Tehran' => 'Tehran',
        'Asia/Muscat' => 'Abu Dhabi',
        'Asia/Baku' => 'Baku',
        'Europe/Moscow' => 'Moscow',
        'Asia/Muscat' => 'Muscat',
        'Asia/Tbilisi' => 'Tbilisi',
        'Asia/Yerevan' => 'Yerevan',
        'Asia/Kabul' => 'Kabul',
        'Asia/Karachi' => 'Karachi',
        'Asia/Tashkent' => 'Tashkent',
        'Asia/Calcutta' => 'Chennai',
        'Asia/Kolkata' => 'Kolkata',
        'Asia/Katmandu' => 'Kathmandu',
        'Asia/Almaty' => 'Almaty',
        'Asia/Dhaka' => 'Dhaka',
        'Asia/Yekaterinburg' => 'Ekaterinburg',
        'Asia/Rangoon' => 'Rangoon',
        'Asia/Bangkok' => 'Bangkok',
        'Asia/Jakarta' => 'Jakarta',
        'Asia/Novosibirsk' => 'Novosibirsk',
        'Asia/Hong_Kong' => 'Beijing',
        'Asia/Chongqing' => 'Chongqing',
        'Asia/Krasnoyarsk' => 'Krasnoyarsk',
        'Asia/Kuala_Lumpur' => 'Kuala Lumpur',
        'Australia/Perth' => 'Perth',
        'Asia/Singapore' => 'Singapore',
        'Asia/Taipei' => 'Taipei',
        'Asia/Ulan_Bator' => 'Ulaan Bataar',
        'Asia/Urumqi' => 'Urumqi',
        'Asia/Irkutsk' => 'Irkutsk',
        'Asia/Seoul' => 'Seoul',
        'Asia/Tokyo' => 'Tokyo',
        'Australia/Adelaide' => 'Adelaide',
        'Australia/Darwin' => 'Darwin',
        'Australia/Brisbane' => 'Brisbane',
        'Australia/Canberra' => 'Canberra',
        'Pacific/Guam' => 'Guam',
        'Australia/Hobart' => 'Hobart',
        'Australia/Melbourne' => 'Melbourne',
        'Pacific/Port_Moresby' => 'Port Moresby',
        'Australia/Sydney' => 'Sydney',
        'Asia/Yakutsk' => 'Yakutsk',
        'Asia/Vladivostok' => 'Vladivostok',
        'Pacific/Auckland' => 'Auckland',
        'Pacific/Fiji' => 'Fiji',
        'Pacific/Kwajalein' => 'International Date Line West',
        'Asia/Kamchatka' => 'Kamchatka',
        'Asia/Magadan' => 'Magadan',
        'Pacific/Fiji' => 'Marshall Is.',
        'Asia/Magadan' => 'New Caledonia',
        'Pacific/Auckland' => 'Wellington',
        'Pacific/Tongatapu' => 'Nuku alofa'
    );

    $form['#attached']['css'] = array(
        drupal_get_path('module', 'pushassist') . '/css/pushassist.css',
    );

    $form['#attached']['js'] = array(
        drupal_get_path('module', 'pushassist') . '/js/pushassist.js',
    );

    $form['sidebar'] = array(

        '#prefix' => '<div id="pushassist" class="content dashboard clearfix"><div class="page-header">
                    <h1 class="title">Campaigns</h1> </div><div class="container-widget clearfix"> <div class="col-md-2 col-lg-2">
                                <div class="sidebar clearfix">
                                    <ul class="sidebar-panel nav">
                                        <li><span class="icon color5"><i class="fa fa-home"></i></span>' . l(t('Dashboard'), 'admin/config/administration/pushassist/pushassist_menu') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-bell"></i></span>' . l(t('Notifications'), 'admin/config/administration/pushassist/notification_details') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-send"></i></span>' . l(t('Send Notification'), 'admin/config/administration/pushassist/new_notification') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-object-ungroup"></i></span>' . l(t('Segments'), 'admin/config/administration/pushassist/segment_details') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gear"></i></span>' . l(t('Create Segments'), 'admin/config/administration/pushassist/create_segment') . '</li>
                                        <li><span class="icon color8"><i class="fa  fa-users"></i></span>' . l(t('Subscribers'), 'admin/config/administration/pushassist/subscribers') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gears"></i></span>' . l(t('Settings'), 'admin/config/administration/pushassist/pushassist_settings') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-hourglass-start"></i></span>' . l(t('Campaigns'), 'admin/config/administration/pushassist/pushassist_campaigns') . '</li>',
        '#suffix' => '</ul></div></div>',
    );

    $form['pushassist-create-campaign-form'] = array(
        '#prefix' => '<div class="col-md-5"><div id="pushassist_create_campaign" class="form-setting">',
        '#suffix' => '</div></div>',
    );

    $form['pushassist-create-campaign-form']['pushassist_campaign_title'] = array(
        '#type' => 'textfield',
        '#title' => t('Campaign Title'),
        '#maxlength' => 77,
        '#required' => TRUE,
        '#attributes' => array('placeholder' => t('Campaign Title')),
        '#description' => t('Limit 77 Characters'),
        '#id' => 'pushassist_campaign_title',
    );

    $form['pushassist-create-campaign-form']['pushassist_campaign_message'] = array(
        '#type' => 'textfield',
        '#title' => t('Campaign Message'),
        '#maxlength' => 138,
        '#required' => TRUE,
        '#attributes' => array('placeholder' => t('Campaign Message')),
        '#description' => t('Limit 138 Characters'),
        '#id' => 'pushassist_campaign_message',
    );

    $form['pushassist-create-campaign-form']['pushassist_campaign_url'] = array(
        '#type' => 'textfield',
        '#title' => t('Campaign URL'),
        '#attributes' => array('placeholder' => t('Enter a URL to push your subscribers to (yoursite.com)')),
        '#id' => 'pushassist_campaign_url',
    );

    $form['pushassist-create-campaign-form']['pushassist_campaign_date'] = array(
        '#prefix' => '<div class="date_picker">',
        '#type' => 'textfield',
        '#title' => t('Campaign Date'),
        '#required' => TRUE,
        '#size' => 10,
        '#maxlength' => 10,
        '#attributes' => array('placeholder' => t('Campaign Date'), 'class' => array('pickadate')),
        '#description' => t('Date Format (YYYY-MM-DD)'),
        '#id' => 'pushassist_campaign_date',
    );

    $form['pushassist-create-campaign-form']['pushassist_campaign_minutes'] = array(
        '#type' => 'select',
        '#options' => $minute_array,
        '#title' => t('Minute'),
        '#description' => t('(HH:MM)'),
        '#multiple' => FALSE,
        '#id' => 'pushassist_campaign_minutes',
        '#suffix' => '</div>',
    );

    $form['pushassist-create-campaign-form']['pushassist_campaign_logo'] = array(
        '#prefix' => '<span class="upload btn-success fileinput-button" id="logo_upload">',
        '#type' => 'file',
        '#title' => t('Campaign Logo'),
        '#suffix' => '</span><p class="clearfix">Image size must be exactly 250x250px.</p>',
    );

    $form['pushassist-create-campaign-form']['pushassist_campaign_is_utm_show'] = array(
        '#type' => 'checkbox',
        '#value' => 0,
        '#title' => t('Add UTM Parameters'),
        '#id' => 'pushassist_campaign_is_utm_show',
    );

    $form['pushassist-create-campaign-form']['pushassist_campaign_is_utm_show_hidden'] = array(
        '#type' => 'hidden',
        '#default_value' => 0,
        '#attributes' => array(
            'id' => 'pushassist_campaign_is_utm_show_hidden',
        )
    );

    $form['pushassist-create-campaign-form']['pushassist_campaign_utm_source'] = array(
        '#prefix' => '<div id="pushassist_campaign_utm_source_div" style="display: none;">',
        '#type' => 'textfield',
        '#title' => t('UTM Source'),
        '#maxlength' => 45,
        '#default_value' => 'pushassist',
        '#attributes' => array('placeholder' => t('UTM Source')),
        '#description' => t('Limit 45 Characters'),
        '#id' => 'pushassist_campaign_utm_source',
        '#suffix' => '</div>',
    );

    $form['pushassist-create-campaign-form']['pushassist_campaign_utm_medium'] = array(
        '#prefix' => '<div id="pushassist_campaign_utm_medium_div" style="display: none;">',
        '#type' => 'textfield',
        '#title' => t('UTM Medium'),
        '#maxlength' => 73,
        '#default_value' => 'pushassist_notification',
        '#attributes' => array('placeholder' => t('UTM Medium')),
        '#description' => t('Limit 73 Characters'),
        '#id' => 'pushassist_campaign_utm_medium',
        '#suffix' => '</div>',
    );

    $form['pushassist-create-campaign-form']['pushassist_campaign_utm_campaign'] = array(
        '#prefix' => '<div id="pushassist_campaign_utm_campaign_div" style="display: none;">',
        '#type' => 'textfield',
        '#title' => t('UTM Campaign'),
        '#maxlength' => 500,
        '#default_value' => 'pushassist',
        '#attributes' => array('placeholder' => t('UTM Campaign')),
        '#description' => t('Limit 500 Characters'),
        '#id' => 'pushassist_campaign_utm_campaign',
        '#suffix' => '</div>',
    );

    $form['pushassist-create-campaign-form']['pushassist_campaign_segment'] = array(
        '#type' => 'select',
        '#options' => $segment_array,
        '#title' => t('Segment'),
        '#multiple' => TRUE,
    );

    $form['pushassist-create-campaign-form']['pushassist_campaign_timezone'] = array(
        '#type' => 'select',
        '#options' => $timezones,
        '#title' => t('TimeZone'),
        '#multiple' => FALSE,
    );

    $form['pushassist-create-campaign-form']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Create Campaign'),
        '#submit' => array('pushassist_create_campaign_form_submit'),
    );

    $form['pushassist-segment-instruction'] = array(
        '#prefix' => '<div class="col-md-5 dummy-notification shadow panel panel-default notification-preview">
                <p class="h4 pb15">Preview</p>
                <div class="widget shadow dummy-notification-inner-wrapper">
                    <div class="wrapper">
                        <div class="img_wrapper pull-left">
                            <img id="logo" src="' . $pushassist_imagePath . '" class="img-responsive">
                        </div>
                        <div class="text_wrapper pull-left">
                            <div class="title">
                                <div class="title_txt pull-left" id="preview_campaign_title">
                                    Campaign Title
                                </div>
                                <div class="closer pull-right">
                                    x
                                </div>
                            </div>
                            <div class="message" id="preview_campaign_message">
                                Campaign Message
                            </div>

                            <div class="domain">
                                <div class="domain">
                                    ' . $pushassist_accountName . '.' . 'pushassist.com </div>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="widget">
                    <p class="h5" id="preview_redirect_url" name="redirect_url" style="padding-left: 50px;">URL to open when user clicks the notification:</p>
                </div>',
        '#suffix' => '</div>',
    );

    return $form;
}

function pushassist_create_campaign_form_submit($form, $form_state){

    $segment_array = array();

    $regex = "((https?|ftp)\:\/\/)?"; // SCHEME
    $regex .= "([a-z0-9+!*(),;?&=\$_.-]+(\:[a-z0-9+!*(),;?&=\$_.-]+)?@)?"; // User and Pass
    $regex .= "([a-z0-9-.]*)\.([a-z]{2,4})"; // Host or IP
    $regex .= "(\:[0-9]{2,5})?"; // Port
    $regex .= "(\/([a-z0-9+\$_-]\.?)+)*\/?"; // Path
    $regex .= "(\?[a-z+&\$_.-][a-z0-9;:@&%=+\/\$_.-]*)?"; // GET Query
    $regex .= "(#[a-z_.-][a-z0-9+\$_.-]*)?"; // Anchor
    module_load_include('inc', 'pushassist', 'pushassist.api');

    $pushassist_campaign_title = $form_state['values']['pushassist_campaign_title'];

    $pushassist_campaign_message = $form_state['values']['pushassist_campaign_message'];

    $pushassist_campaign_url = $form_state['values']['pushassist_campaign_url'];

    $pushassist_campaign_date = $form_state['values']['pushassist_campaign_date'];
	
	$pushassist_campaign_minutes = $form_state['values']['pushassist_campaign_minutes'];	

    $pushassist_is_utm_show_hidden = $form_state['values']['pushassist_campaign_is_utm_show_hidden'];

    $pushassist_campaign_utm_source = $form_state['values']['pushassist_campaign_utm_source'];

    $pushassist_campaign_medium = $form_state['values']['pushassist_campaign_utm_medium'];

    $pushassist_campaign_utm_campagin = $form_state['values']['pushassist_campaign_utm_campaign'];
    
    if ($pushassist_is_utm_show_hidden != 1) {

        $pushassist_campaign_utm_source = '';
        $pushassist_campaign_medium = '';
        $pushassist_campaign_utm_campagin = '';
    }

    $pushassist_campaign_segment = array_filter($form_state['values']['pushassist_campaign_segment']);

	$pushassist_campaign_timezone = $form_state['values']['pushassist_campaign_timezone'];
	
    $pushassist_campaign_logo_obj = file_save_upload('pushassist_campaign_logo', '', 'public://');

    if (isset($pushassist_campaign_logo_obj->filename)) {

        $campaign_logo_path = file_create_url($pushassist_campaign_logo_obj->uri);

    } else {

        $campaign_logo_path = '';
    }

    if (count($pushassist_campaign_segment) > 0) {

        foreach ($pushassist_campaign_segment as $value) {

            $segment_array[] = (int)$value;
        }

    } else {

        $segment_array = array();
    }

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    if (empty($pushassist_campaign_title)) {

        form_set_error('pushassist_campaign_title', t('Campaign Title can not be empty.'));
    }

    if (empty($pushassist_campaign_message)) {

        form_set_error('pushassist_campaign_message', t('Campaign Message can not be empty.'));
        return false;
    }

    if (!empty($pushassist_campaign_url)) {

        if (!preg_match("/^$regex$/", $pushassist_campaign_url)) {

            form_set_error('pushassist_campaign_url', t('Please provide valid URL.'));
            return false;
        }
    }

    if (empty($pushassist_campaign_date)) {

        form_set_error('pushassist_campaign_date', t('Campaign Date can not be empty.'));
        return false;
		
    } else {

        $pushassist_campaign_date = $pushassist_campaign_date.' '.$pushassist_campaign_minutes;
    }

    $campaign_response = pushassist_schedule_campaign_api($pushassist_apikey, $pushassist_secretkey, $pushassist_campaign_title, $pushassist_campaign_message, $pushassist_campaign_url, $pushassist_campaign_date, $campaign_logo_path, $pushassist_campaign_utm_source, $pushassist_campaign_medium, $pushassist_campaign_utm_campagin, $segment_array, $pushassist_campaign_timezone);

    $campaign_result = json_decode($campaign_response->data, true);

    if ($campaign_result['status'] == 'Success') {

        drupal_set_message(t($campaign_result['response_message']));

        drupal_goto('admin/config/administration/pushassist/pushassist_menu');

    } else if ($campaign_result['status'] == 'Error') {

        drupal_set_message(t($campaign_result['error_message']));

    } else if (isset($campaign_result['error'])) {

        drupal_set_message(t($campaign_result['error']));
        $form_state['rebuild'] = TRUE;

    } else {

        drupal_set_message(t($campaign_result['errors']));
        $form_state['rebuild'] = TRUE;
    }
}

function pushassist_campaigns()
{
    module_load_include('inc', 'pushassist', 'pushassist.api');

    $image_path = base_path() . drupal_get_path('module', 'pushassist') . '/images/campaign_notification.png';

    $pushassist_apikey = variable_get('pushassist_apiKey', '');

    $pushassist_secretkey = variable_get('pushassist_secretKey', '');

    $account_info = pushassist_login($pushassist_apikey, $pushassist_secretkey);

    $account_details = json_decode($account_info->data, true);

    $form['#attached']['css'] = array(
        drupal_get_path('module', 'pushassist') . '/css/pushassist.css',
    );

    $form['#attached']['js'] = array(
        drupal_get_path('module', 'pushassist') . '/js/pushassist.js',
    );

    $form['sidebar'] = array(

        '#prefix' => '<div id="pushassist" class="content dashboard clearfix"><div class="page-header">
                    <h1 class="title">Campaigns</h1> </div><div class="container-widget clearfix"> <div class="col-md-2 col-lg-2">
                                <div class="sidebar clearfix">
                                    <ul class="sidebar-panel nav">
                                        <li><span class="icon color5"><i class="fa fa-home"></i></span>' . l(t('Dashboard'), 'admin/config/administration/pushassist/pushassist_menu') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-bell"></i></span>' . l(t('Notifications'), 'admin/config/administration/pushassist/notification_details') . '</li>
                                        <li><span class="icon color9"><i class="fa fa-send"></i></span>' . l(t('Send Notification'), 'admin/config/administration/pushassist/new_notification') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-object-ungroup"></i></span>' . l(t('Segments'), 'admin/config/administration/pushassist/segment_details') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gear"></i></span>' . l(t('Create Segments'), 'admin/config/administration/pushassist/create_segment') . '</li>
                                        <li><span class="icon color8"><i class="fa  fa-users"></i></span>' . l(t('Subscribers'), 'admin/config/administration/pushassist/subscribers') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-gears"></i></span>' . l(t('Settings'), 'admin/config/administration/pushassist/pushassist_settings') . '</li>
                                        <li><span class="icon color8"><i class="fa fa-hourglass-start"></i></span>' . l(t('Campaigns'), 'admin/config/administration/pushassist/pushassist_campaigns') . '</li>',
        '#suffix' => '</ul></div></div>',
    );

    $form['pushassist-campaign-form'] = array(
        '#prefix' => '<div class="col-md-6"><div id="pushassist_campaign" class="form-setting"><p class="margin-b-15">Following screenshot shows how you can create and schedule a campaign. <strong> This feature is available in premium plans. </strong> &nbsp; &nbsp; &nbsp; </p> <div class="center padding-t-5 margin-b-10"> <a target="_blank" class="btn btn-default" href="https://' . $account_details['account_name'] . '.pushassist.com/campaign/">Upgrade to Premium</a> </div><img class="margin-b-15 margin-t-15" src="' . $image_path . '" alt="PushAssist Campaign">',
        '#suffix' => '</div></div></div>',
    );

    return $form;

}

/**
 * Removes account specific database values used by PushAssist module on Sign Out.
 */
function pushassist_account_signout()
{
    variable_del('pushassist_apiKey');
    variable_del('pushassist_secretKey');
    variable_del('pushassist_jsPath');
    variable_del('pushassist_remainSubscribers');
    variable_del('pushassist_accountName');
    variable_del('pushassist_imagePath');

    variable_del('pushassist_auto_push_publish');
    variable_del('pushassist_auto_push_update');
	variable_del('pushassist_auto_push_logo_img_post');

    variable_del('pushassist_auto_push_UTMparameters');

    variable_del('pushassist_setting_utm_source');
    variable_del('pushassist_setting_utm_medium');
    variable_del('pushassist_setting_utm_campaign');
    variable_del('pushassist_auto_push_message');

    drupal_goto('admin/config/administration/pushassist/pushassist_menu');
}