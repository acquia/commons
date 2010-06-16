<?php
// $Id: maintenance-page.tpl.php,v 1.1.2.3 2010/02/14 06:44:15 sociotech Exp $
?>

<body id="<?php print $body_id; ?>" class="<?php print $body_classes; ?>">
  <div id="page" class="page">
    <div id="page-inner" class="page-inner">
      <div id="skip">
        <a href="#main-content-area"><?php print t('Skip to Main Content Area'); ?></a>
      </div>

      <!-- header-group row: width = grid_width -->
      <div id="header-group-wrapper" class="header-group-wrapper full-width">
        <div id="header-group" class="header-group row <?php print $grid_width; ?>">
          <div id="header-group-inner" class="header-group-inner inner">
            <?php if ($logo || $site_name || $site_slogan): ?>
            <div id="header-site-info" class="header-site-info block">
              <div id="header-site-info-inner" class="header-site-info-inner inner">
                <?php if ($logo): ?>
                <div id="logo">
                  <a href="<?php print check_url($front_page); ?>" title="<?php print t('Home'); ?>"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
                </div>
                <?php endif; ?>
                <?php if ($site_name): ?>
                <span id="site-name"><a href="<?php print check_url($front_page); ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a></span>
                <?php endif; ?>
                <?php if ($site_slogan): ?>
                <span id="slogan"><?php print $site_slogan; ?></span>
                <?php endif; ?>
              </div><!-- /header-site-info-inner -->
            </div><!-- /header-site-info -->
            <?php endif; ?>
          </div><!-- /header-group-inner -->
        </div><!-- /header-group -->
      </div><!-- /header-group-wrapper -->

      <!-- main row: width = grid_width -->
      <div id="main-wrapper" class="main-wrapper full-width">
        <div id="main" class="main row <?php print $grid_width; ?>">
          <div id="main-inner" class="main-inner inner">
            <div id="content-region" class="content-region row nested">
              <div id="content-region-inner" class="content-region-inner inner">
                <a name="main-content" id="main-content"></a>
                <?php print theme('grid_block', $tabs, 'content-tabs'); ?>
                <div id="content-inner" class="content-inner block">
                  <div id="content-inner-inner" class="content-inner-inner inner">
                    <?php if ($title): ?>
                    <h1 class="title"><?php print $title; ?></h1>
                    <?php endif; ?>
                    <?php if ($content): ?>
                    <div id="content-content" class="content-content">
                      <?php print $content; ?>
                    </div><!-- /content-content -->
                    <?php endif; ?>
                  </div><!-- /content-inner-inner -->
                </div><!-- /content-inner -->
              </div><!-- /content-region-inner -->
            </div><!-- /content-region -->
          </div><!-- /main-inner -->
        </div><!-- /main -->
      </div><!-- /main-wrapper -->

    </div><!-- /page-inner -->
  </div><!-- /page -->
  <?php print $closure; ?>
</body>
</html>
