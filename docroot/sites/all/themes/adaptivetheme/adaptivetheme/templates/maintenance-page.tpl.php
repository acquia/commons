<?php // $Id: maintenance-page.tpl.php,v 1.1.2.3 2010/01/03 01:37:53 jmburnz Exp $
// adaptivethemes.com
/**
* @file maintenance-page.tpl.php
*
* Theme implementation to display a single Drupal page while off-line.
*
* Adaptivetheme maintenance page does not include sidebars by default, nor
* does it print messages, tabs or anything else that typically you would
* not see on a maintenance page. If you require any of these additional variables
* you will need to add them. Also the columns layout has been totally removed.
*
* themename_preprocess is disabled when the database is not active (see
* template.php). This is because it calls many functions that rely on the database
* being active and will cause errors when the maintenance page is viewed.
*
* @see template_preprocess()
* @see template_preprocess_maintenance_page()
*/
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>
<body class="<?php print $body_classes; ?>">
  <div id="container">
    <div id="header" class="clearfix">
      <?php if ($logo or $site_name or $site_slogan): ?>
        <div id="branding">
          <?php if ($logo or $site_name): ?>
            <div class="logo-site-name"><strong>
              <?php if (!empty($logo)): ?>
                <span id="logo">
                  <a href="<?php print $base_path; ?>" title="<?php print t('Home page'); ?>" rel="home">
                    <img src="<?php print $logo; ?>" alt="<?php print t('Home page'); ?>" />
                  </a>
                </span>
              <?php endif; ?>
              <?php if (!empty($site_name)): ?>
                <span id="site-name">
                  <a href="<?php print $base_path ?>" title="<?php print t('Home page'); ?>" rel="home">
                    <?php print $site_name; ?>
                  </a>
                </span>
              <?php endif; ?>
            </strong></div> <!-- /logo and site name -->
            <?php if ($site_slogan): ?>
              <div id="site-slogan"><?php print $site_slogan; ?></div>
            <?php endif; ?> <!-- /slogan -->
          <?php endif; ?>
        </div> <!-- /branding -->
      <?php endif; ?>
    </div> <!-- /header -->
    <div id="main-content">
      <?php if ($title): ?><h1 id="page-title"><?php print $title; ?></h1><?php endif; ?>
      <div id="content"><?php print $content; ?></div>
    </div> <!-- /main-content -->
  </div> <!-- /container -->
  <?php print $closure ?>
</body>
</html>