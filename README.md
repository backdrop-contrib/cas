# Introduction

As described in the official CAS protocol documentation:

"The Central Authentication Service (CAS) is a single-sign-on / 
single-sign-on protocol for the web. It permits a user to access 
multiple applications while providing their credentials (such as userid 
and password) only once to a central CAS Server application."
 
Using a single-sign on service like CAS is a benefitial because it provides:

* Convenience. Your users don't need to remember credentials for multiple
  different web services.
* Security. Your Drupal website never sees a user's password.

This module implements version 1 and version 2 of the CAS protocol:
http://jasig.github.io/cas/4.1.x/protocol/CAS-Protocol-Specification.html

Not all parts of the specification are implemented, but the core functionality
that the protocol describes works well.

# Requirements

This module requires the following modules: 

* External Authentication (https://drupal.org/porject/externalauth)

# Recommended Modules

* CAS Attributes (http://drupal.org/project/cas_attributes) allows user 
  attributes and roles to be set based on attributes provided by the cas 
  server.  
    
* Markdown Filter (https://drupal.org/project/markdown) when enabled will 
  display the project's help page (README.md) as rendered markdown.

# Installation

Download and install the module as you would with any other Drupal module:

* Download this module and move the folder it the DRUPAL_ROOT/modules 
  directory.
* Enable the module in your Drupal admin interface.
* The configuration page for this module is in /admin/config/people/cas,
  and can be accessed in the admin menu under Configuration -> People -> CAS

# Configuration

## Getting Started and Basic Usage

All of the settings for this module are on the single configuration page
described above. To get started, you simply need to configure the settings
for your CAS server.

The only CAS server setting that may not be easily understood is the
"SSL Verification" setting. In most cases, the default setting (using
server defaults) will work fine. If not, read the "SSL Verification Setting"
section below to learn more.

This module exposes a specific URL path on your website that will trigger
the CAS authentication process for your users:

http://yoursite.com/caslogin (/cas will also work)

Users will be redirected to your CAS server to authenticate. If they already
have an active session with the CAS server, they will immediately be redirected
back to your site and authenticated seemlessly. If not, they will be prompted
to enter their credentials and then redirected back to your Drupal site and
authenticated.

You can create a login button on your website that links directly to this
path to provide a way for your users to easily login.

## Account Handling & Auto Registration

Local Drupal accounts must exist for users that authenticate with CAS.
This module simply provides a way to authenticate these users.

If a user attempts to login with an account that is not already registered on
your Drupal site, they will see an error message.

However, you can configure the module to automatically register users.
This way, when a user authenticates with CAS, a local Drupal account will
automatically be created for that user. The password for the account will
be randomly generated and is not revealed to the user.

This module does NOT prevent local Drupal authentication (using the standard
login form). If a user knew their randomly generated password, or used
the password reset form, they could bypass CAS authenticaton and login to
the Drupal site directly unless Forced Login is properly configured.

## Forced Login

You can enable the Forced Login feature to force anonymous users to
authenticate via CAS when they hit all or some of the pages on your site.

If the user does not have an active session with the CAS server, they will
be forced to enter their credentials before returning to your site. If the
user does have an active session, they will be seemlessly authenticated
locally on your Drupal site and shown the page they requested.

## Gateway Login

With this feature enabled, anonymous users that view some or all pages on
your site will automatically be logged in IF they already have an active
CAS session with the CAS server.

If the user does not have an active session with the CAS server, they will
see the Drupal page requested as normal.

This feature works by quickly redirecting the user to the CAS server to
check for an active session, and then redirecting back to the page they
originally requested on your website.

This feature differs from Forced Login in that it will not force the user
to login if they do not already have an active CAS server session.

*This feature is not currently compatible with any form of page caching.*

## SSL Verification Setting
This module makes an HTTP request to your CAS server during the authentication
process, and since CAS servers must be accessed over HTTPS, this module needs
to know how to verify the SSL/TLS certificate of your CAS server to be
sure it is authentic.

Assuming the SSL cert of your CAS server was signed by a well known
certificate authority, CAS will use the default certificate chain that
should be present on your web server and it will "just work". But if you are
getting errors when authenticating, you may need obtain the PEM certificate
of the certificate authorirty that signed your CAS server's SSL cert and
provide the path to that cert.

Further discussion of this topic is beyond the scope of this documentation,
but web hosts and system administrators should have a deep understanding
of this topic to help further.

## Proxy
Initializing a CAS client as a proxy allows the client to make web service calls 
to other sites or web pages that are protected by cas authentication.  It 
is often used in portal applications allowing the portal product to get 
personalized or secure content from other products participating in single 
sign on. 

Configuring this module to "Initialize this client as a proxy" allows 
other modules on this site to make authenticated requests to other CAS 
enabled products. 

Configuring this module to "Allow this client to be proxied" lets the 
specified sites use this site as a resource for portal channels or other 
web services. 

# Troubleshooting
The fastest way to determine why the module is not behaving as expected it to
enable the debug logging in this module's settings page. Messages related to
the authentication process, including errors, will be logged. To view these
logs, enable the Database Logging module or the Syslog module.