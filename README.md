CAS
======================

Central Authentication Services (CAS) is a commonly used Single Sign-On
protocol used by many universities and large organizations. For a brief
introduction, please see the CAS website: https://www.apereo.org/projects/cas

Requirements
------------

Minimum of PHP 5.6 with the following extensions: curl, openssl, dom, zlib, and xml


Installation
------------
Install this module using the official Backdrop CMS instructions at
https://docs.backdropcms.org/documentation/extend-with-modules.

  - Navigate to Configuration > User accounts > CAS settings to configure the CAS module.


Differences from Drupal 7
-------------------------

  - cas_server is no longer included with base module. See Issues below for more information.


Issues
------

  - cas_server has been removed from the base module because of both its complexity and the inability to accurately and sufficiently test it.

Bugs and feature requests should be reported in [the Issue Queue](https://github.com/rbargerhuff/cas/issues).


Current Maintainers
-------------------

[Rick Bargerhuff](https://github.com/rbargerhuff).

Seeking additional maintainers.


Credits
-------

Ported to Backdrop CMS by [Rick Bargerhuff](https://github.com/rbargerhuff).

Originally maintained for Drupal by:

  - [bkosborne](https://www.drupal.org/u/bkosborne).

  - [claudiucristea](https://www.drupal.org/u/claudiucristea).

  - [metzlerd](https://www.drupal.org/u/metzlerd).


License
-------

This project is GPL v2 software.
See the LICENSE.txt file in this directory for complete text.
