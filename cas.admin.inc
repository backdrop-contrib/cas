<?php

/**
 * @file
 * CAS module settings UI.
 */

/**
 * Provides settings pages.
 */
function cas_admin_settings() {
  $config = config('cas.settings');

  $form['#config'] = 'cas.settings';
  $form['library'] = array(
    '#type' => 'fieldset',
    '#title' => t('Library (phpCAS)'),
    '#collapsible' => TRUE,
  );

  // Confirmation that phpCAS was loaded.
  $version = @cas_phpcas_load();
  $form['library']['cas_library_info_dir'] = array(
    '#type' => 'item',
    '#markup' => '<div>' . t('phpCAS version %version successfully loaded.', array('%version' => $version)) . '</div>',
  );

  $form['server'] = array(
    '#type' => 'fieldset',
    '#title' => t('CAS Server'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['server']['cas_version'] = array(
    '#type' => 'radios',
    '#title' => t('Version'),
    '#default_value' => $config->get('cas_version'),
    '#options' => array(
      '1.0' => '1.0',
      '2.0' => t('2.0'),
      '3.0' => t('3.0 or higher (requires phpCAS >= 1.3.3)'),
      'S1' => t('SAML Version 1.1'),
    ),
  );

  $form['server']['cas_server'] = array(
    '#type' => 'textfield',
    '#title' => t('Hostname'),
    '#default_value' => $config->get('cas_server'),
    '#size' => 30,
    // Hostnames can be 255 characters long.
    '#maxlength' => 255,
    '#description' => t('Hostname or IP Address of the CAS server. CAS logins will not work until this hostname is entered.'),
  );

  $form['server']['cas_port'] = array(
    '#type' => 'textfield',
    '#title' => t('Port'),
    '#default_value' => $config->get('cas_port'),
    '#size' => 5,
    // The maximum port number is 65536, 5 digits.
    '#maxlength' => 5,
    '#description' => t('443 is the standard SSL port. 8443 is the standard non-root port for Tomcat.'),
  );

  $form['server']['cas_uri'] = array(
    '#type' => 'textfield',
    '#title' => t('URI'),
    '#default_value' => $config->get('cas_uri'),
    '#size' => 30,
    '#description' => t('If CAS is not at the root of the host, include a URI (e.g., /cas).'),
  );

  $form['server']['cas_cert'] = array(
    '#type' => 'textfield',
    '#title' => t('Certificate Authority PEM Certificate'),
    '#default_value' => $config->get('cas_cert'),
    '#maxlength' => 255,
    '#description' => t('The path to the certificate (in PEM format) of the Certificate Authority that issued the SSL certificate of the CAS server. If omitted, the SSL cert of your CAS server will NOT be verified for authenticity. Most operating systems provide a standard CA cert bundle that can be provided here that would work for certificates signed by a well-known authority.'),
  );

  $form['login'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login form'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['login']['cas_login_form'] = array(
    '#type' => 'radios',
    '#title' => t('Add CAS link to login forms'),
    '#default_value' => $config->get('cas_login_form'),
    '#options' => array(
      CAS_NO_LINK => t('Do not add link to login forms'),
      CAS_ADD_LINK => t('Add link to login forms'),
      CAS_MAKE_DEFAULT => t('Make CAS login default on login forms'),
      CAS_REDIRECT => t('Redirect the login form to CAS'),
    ),
  );

  $form['login']['cas_login_invite'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS Login invitation'),
    '#default_value' => $config->get('cas_login_invite'),
    '#description' => t('Message users will see to invite them to log in with CAS credentials.'),
  );

  $form['login']['cas_login_backdrop_invite'] = array(
    '#type' => 'textfield',
    '#title' => t('Backdrop login invitation'),
    '#default_value' => $config->get('cas_login_backdrop_invite'),
    '#description' => t('Message users will see to invite them to log in with Backdrop credentials.'),
  );

  $form['login']['cas_login_redir_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirection notification message'),
    '#default_value' => $config->get('cas_login_redir_message'),
    '#description' => t('Message users see at the top of the CAS login form to warn them that they are being redirected to the CAS server.'),
  );

  // Setting for message displayed to user upon successful login
  $form['login']['cas_login_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Successful login message'),
    '#default_value' => $config->get('cas_login_message'),
    '#description' => t('Message displayed when a user logs in successfully. <em>%cas_username</em> will be replaced with the user\'s name.'),
  );


  $form['account'] = array(
    '#type' => 'fieldset',
    '#title' => t('User accounts'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['account']['cas_user_register'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically create Backdrop accounts'),
    '#default_value' => $config->get('cas_user_register'),
    '#description' => t('Whether a Backdrop account is automatically created the first time a CAS user logs into the site. If disabled, you will need to pre-register Backdrop accounts for authorized users.'),
  );

  $form['account']['cas_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#field_prefix' => t('username@'),
    '#default_value' => $config->get('cas_domain'),
    '#size' => 30,
    // Hostnames can be 255 characters long.
    '#maxlength' => 255,
    '#description' => t("If provided, automatically generate each new user's e-mail address. If omitted, the e-mail field will not be populated. Other modules may be used to populate the e-mail field from CAS attributes or LDAP servers."),
  );

  // Taken from Backdrop's User module.
  $roles = array_map('check_plain', user_roles(TRUE));

  $checkbox_authenticated = array(
    '#type' => 'checkbox',
    '#title' => $roles[BACKDROP_AUTHENTICATED_ROLE],
    '#default_value' => TRUE,
    '#disabled' => TRUE,
  );
  unset($roles[BACKDROP_AUTHENTICATED_ROLE]);
  $form['account']['cas_auto_assigned_role'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles'),
    '#description' => t('The selected roles will be automatically assigned to each CAS user on login. Use this to automatically give CAS users additional privileges or to identify CAS users to other modules.'),
    '#default_value' => $config->get('cas_auto_assigned_role'),
    '#options' => $roles,
    '#access' => user_access('administer permissions'),
    BACKDROP_AUTHENTICATED_ROLE => $checkbox_authenticated,
  );

  $form['account']['cas_hide_email'] = array(
    '#type' => 'checkbox',
    '#title' => t('Users cannot change email address'),
    '#default_value' => $config->get('cas_hide_email'),
    '#description' => t('Hide email address field on the edit user form.'),
  );

  $form['account']['cas_hide_password'] = array(
    '#type' => 'checkbox',
    '#title' => t('Users cannot change password'),
    '#default_value' => $config->get('cas_hide_password'),
    '#description' => t('Hide password field on the edit user form. This also removes the requirement to enter your current password before changing your e-mail address.'),
  );

  if (module_exists('persistent_login')) {
    $form['account']['cas_allow_rememberme'] = array(
      '#type' => 'checkbox',
      '#title' => t('Users can stay logged in between sessions'),
      '#default_value' => $config->get('cas_allow_rememberme'),
      '#description' => t('If Persistent Login is enabled, users can choose to stay logged in between browser sessions'),
      );
  }

  $form['pages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Redirection'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['pages']['cas_check_frequency'] = array(
    '#type' => 'radios',
    '#title' => t('Check with the CAS server to see if the user is already logged in?'),
    '#default_value' => $config->get('cas_check_frequency'),
    '#options' => array(
      CAS_CHECK_NEVER => 'Never',
      CAS_CHECK_ONCE => 'Once per browser session',
      CAS_CHECK_ALWAYS => 'Always (every page load)',
    ),
    '#description' => t('This implements the') . ' <a href="https://wiki.jasig.org/display/CAS/gateway">Gateway feature</a> ' . t('of the CAS Protocol.') . ' <strong>WARNING:</strong> ' . t('Enabling it at all will') . ' <em>' . t('completely disable page caching') . '</em>' . t(', and will prevent users from logging out locally unless also logged out of CAS. Setting it to "Always" will perform redirects on EVERY page load unless the user is already logged in, and is not recommended in most circumstances.'),
  );

  $form['pages']['cas_access'] = array(
    '#type' => 'radios',
    '#title' => t('Require CAS login for'),
    '#default_value' => $config->get('cas_access'),
    '#options' => array(t('specific pages'), t('all pages except specific pages')),
  );

  $form['pages']['cas_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Specific pages'),
    '#default_value' => $config->get('cas_pages'),
    '#cols' => 40,
    '#rows' => 5,
    '#description' => t("Enter one page per line as Backdrop paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
  );

  $form['pages']['cas_exclude'] = array(
    '#type' => 'textarea',
    '#title' => t('Excluded Pages'),
    '#default_value' => $config->get('cas_exclude'),
    '#cols' => 40,
    '#rows' => 5,
    '#description' => t("Indicates which pages will be ignored (no login checks). Enter one page per line as Backdrop paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
  );


  $form['misc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login/Logout Destinations'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Settings for redirection upon first login
  $form['misc']['cas_first_login_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Initial login destination'),
    '#default_value' => $config->get('cas_first_login_destination'),
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t("Backdrop path or URL. Enter a destination if you want the user to be redirected to this page on their first CAS login. An example path is <em>blog</em> for the blog page, <em>&lt;front&gt;</em> for the front page, or <em>user</em> for the user's page."),
  );

  // Setting for page to return to after a CAS logout
  $form['misc']['cas_logout_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Logout destination'),
    '#default_value' => $config->get('cas_logout_destination'),
    '#size' => 40,
    '#maxlength' => 255,
    '#description' => t("Backdrop path or URL. Enter a destination if you want a user to be directed to this page after logging out of CAS, or leave blank to direct users back to the previous page. An example path is <em>blog</em> for the blog page or <em>&lt;front&gt;</em> for the front page."),
  );

  $form['misc']['cas_changePasswordURL'] = array(
    '#type' => 'textfield',
    '#title' => t('Change password URL'),
    '#default_value' => $config->get('cas_changePasswordURL'),
    '#maxlength' => 255,
    '#description' => t('The URL users should use for changing their password.  Leave blank to use the standard Backdrop page.'),
  );

  $form['misc']['cas_registerURL'] = array(
    '#type' => 'textfield',
    '#title' => t('Registration URL'),
    '#default_value' => $config->get('cas_registerURL'),
    '#maxlength' => 255,
    '#description' => t('The URL users should use for changing registering.  Leave blank to use the standard Backdrop page.'),
  );

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Miscellaneous & Experimental Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['advanced']['cas_proxy'] = array(
    '#type' => 'checkbox',
    '#title' => t('Initialize CAS as proxy'),
    '#default_value' => $config->get('cas_proxy'),
    '#description' => t('Initialize phpCAS as a proxy rather than a client. The proxy ticket returned by the CAS server allows access to external services as the CAS user.')
  );

  $form['advanced']['cas_proxy_settings'] = array(
    '#type' => 'container',
    '#states' => array(
      'invisible' => array(
        'input[name="cas_proxy"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['advanced']['cas_proxy_settings']['cas_pgtformat'] = array(
    '#type' => 'radios',
    '#title' => t('CAS PGT storage file format'),
    '#default_value' => $config->get('cas_pgtformat'),
    '#options' => array('plain' => t('Plain Text'), 'xml' => t('XML')),
    '#after_build' => array('cas_pgtformat_version_check'),
  );

  $form['advanced']['cas_proxy_settings']['cas_pgtpath'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS PGT storage path'),
    '#default_value' => $config->get('cas_pgtpath'),
    '#maxlength' => 255,
    '#description' => t("Only needed if 'Use CAS proxy initializer' is configured. Leave empty for default."),
  );

  $form['advanced']['cas_proxy_list'] = array(
    '#type' => 'textarea',
    '#title' => t('CAS proxy list'),
    '#description' => t("If CAS client could be proxied, indicate each proxy server absolute url per line. If not provided, phpCAS will exclude by default all tickets provided by proxy. Each proxy server url could be a plain url or a regular expression. IMPORTANT : regular expression delimiter must be a slash. For example : https://proxy.example.com/ AND/OR regular expression : /^https:\/\/app[0-9]\.example\.com\/rest\//."),
    '#default_value' => $config->get('cas_proxy_list'),
    '#after_build' => array('cas_proxy_list_version_check'),
  );

  $form['advanced']['cas_debugfile'] = array(
    '#type' => 'textfield',
    '#title' => t('CAS debugging output file'),
    '#default_value' => $config->get('cas_debugfile'),
    '#maxlength' => 255,
    '#description' => "<p>" . t("A file system path and filename where the CAS debug log will be written. May be either a full path or a path relative to the Backdrop installation root. The directory and file must be writable by Backdrop.") . "</p> <p>" . t("Leave blank to disable logging.") . "</p> <p><strong>" . t("Debugging should not be enabled on production systems.") . "</strong></p>",
  );

  $form['advanced']['cas_single_logout_session_lifetime'] = array(
    '#type' => 'number',
    '#title' => t('Max lifetime of session mapping data'),
    '#description' => t('This module stores a mapping of Backdrop session IDs ' .
      'to CAS server session IDs to support single logout. Normally this data is ' .
      'cleared automatically when a user is logged out, but not always. ' .
      'To make sure this storage does not grow out of control, session mapping ' .
      'data older than the specified amount of days is cleared during cron. ' .
      'This should be a length of time slightly longer than the session ' .
      'lifetime of your Backdrop site or CAS server.'),
    '#default_value' => $config->get('cas_single_logout_session_lifetime'),
    '#field_suffix' => t('days'),
    '#size' => 4,
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Proxy chain object only exists with phpCAS version >= 1.3. As phpCAS CAS.php
 * is include only after building element 'cas_library_info_dir', we must check it after it.
 */
function cas_proxy_list_version_check($element, &$form_state) {
  if (!defined('PHPCAS_VERSION') || version_compare(PHPCAS_VERSION, '1.3', '<')) {
    $element['#access'] = FALSE;
  }
  return $element;
}

/**
 * Since 1.3, pgt format isn't supported and default to plain.
 */
function cas_pgtformat_version_check($element, &$form_state) {
  if (!defined('PHPCAS_VERSION') || version_compare(PHPCAS_VERSION, '1.3', '>')) {
    $element['#access'] = FALSE;
  }
  return $element;
}
