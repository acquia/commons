<?php // $Id: page.tpl.php,v 1.1.2.8 2010/03/23 04:53:54 jmburnz Exp $
// adaptivethemes.com

/**
 * @file page.tpl.php
 * Theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *     least, this will always default to /.
 * - $css: An array of CSS files for the current page.
 * - $directory: The directory the theme is located in, e.g. themes/garland or
 *     themes/garland/minelli.
 * - $is_front: TRUE if the current page is the front page. Used to toggle the mission statement.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Page metadata:
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *     so on).
 * - $head_title: A modified version of the page title, for use in the TITLE tag.
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *     for the page.
 * - $classes: A set of CSS classes (preprocess $body_classes + custom classes).
 *     This contains flags indicating the current layout (multiple columns, single column),
 *     the current path, whether the user is logged in, and so on.
 *
 * Layout variable:
 * - $layout_settings: prints the layout CSS if the layout theme settings are enabled.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *     when linking to the front page. This includes the language domain or prefix.
 * - $linked_site_logo: The preprocessed $logo variable. Includes the path to the logo image,
 *     as defined in theme configuration and wrapped in an anchor linking to the home page.
 * - $linked_site_name: The name of the site (preprocessed) wrapped in an anchor linking to
 *     the home page.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *     in theme settings.
 * - $mission: The text of the site mission, empty when display has been disabled
 *     in theme settings.
 *
 * Navigation:
 * - $primary_menu: The preprocessed $primary_links (array), an array containing primary
 *     navigation links for the site, if they have been configured.
 * - $secondary_menu: The preprocessed $secondary_links (array), an array containing secondary
 *     navigation links for the site, if they have been configured.
 * - $search_box: HTML to display the search box, empty if search has been disabled.
 *
 * Page content:
 * - $leaderboard: Custom region for displaying content at the top of the page, useful
 *     for displaying a banner.
 * - $header: The header blocks region for display content in the header.
 * - $menu_bar: a region for placing dynamic menus.
 * - $secondary_content: Full width custom region for displaying content between the header
 *     and the main content columns.
 * - $breadcrumb: The breadcrumb trail for the current page.
 * - $content_top: A custom region for displaying content above the main content.
 * - $title: The page title, for use in the actual HTML content.
 * - $help: Dynamic help text, mostly for admin pages.
 * - $messages: HTML for status and error messages. Should be displayed prominently.
 * - $tabs: Tabs linking to any sub-pages beneath the current page (e.g., the view
 *     and edit tabs when displaying a node).
 * - $content: The main content of the current Drupal page.
 * - $content_bottom: A custom region for displaying content above the main content.
 * - $left: Region for the left sidebar.
 * - $right: Region for the right sidebar.
 * - $tertiary_content: Full width custom region for displaying content between main content
 *   columns and the footer.
 *
 * Footer/closing data:
 * - $footer : The footer region.
 * - $footer_message: The footer message as defined in the admin settings.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $closure: Final closing markup from any modules that have altered the page.
 *     This variable should always be output last, after all other dynamic content.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see genesis_preprocess_page()
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $layout_settings; ?>
  <?php print $scripts; ?>
</head>
<body class="<?php print $classes; ?>">
  <div id="container">

    <div id="skip-nav" class="<?php print $skip_nav_class; ?>">
      <!-- To adjust the display of the skip link see the Advanced theme settings (General settings), and never use display:none! -->
      <a href="#main-content"><?php print t('Skip to main content'); ?></a>
    </div>

    <?php // Add support for Admin module header, http://drupal.org/project/admin. ?>
    <?php if (!empty($admin)) print $admin; ?>

    <?php if (!empty($admin_user_links)): ?>
      <div id="user-menu" class="clearfix">
        <h2 class="element-invisible"><?php print t('User menu'); ?></h2>
        <?php print $admin_user_links; ?>
      </div> <!-- /admin user link -->
    <?php endif; ?>

    <?php if ($leaderboard): ?>
      <div id="leaderboard"><?php print $leaderboard; ?></div> <!-- /leaderboard -->
    <?php endif; ?>

    <div id="header" class="clearfix">

      <?php if ($linked_site_logo or $linked_site_name or $site_slogan): ?>
        <div id="branding">

          <?php if ($linked_site_logo or $linked_site_name): ?>
            <?php if ($title): ?>
              <div class="logo-site-name"><strong>
                <?php if ($linked_site_logo): ?><span id="logo"><?php print $linked_site_logo; ?></span><?php endif; ?>
                <?php if ($linked_site_name): ?><span id="site-name"><?php print $linked_site_name; ?></span><?php endif; ?>
              </strong></div> <!-- /logo/site name -->
            <?php else: /* Use h1 when the content title is empty */ ?>
              <h1 class="logo-site-name">
                <?php if ($linked_site_logo): ?><span id="logo"><?php print $linked_site_logo; ?></span><?php endif; ?>
                <?php if ($linked_site_name): ?><span id="site-name"><?php print $linked_site_name; ?></span><?php endif; ?>
              </h1> <!-- /logo/site name -->
            <?php endif; ?>
          <?php endif; ?>

          <?php if ($site_slogan): ?>
            <div id="site-slogan"><?php print $site_slogan; ?></div> <!-- /slogan -->
          <?php endif; ?>

        </div> <!-- /branding -->
      <?php endif; ?>

      <?php if ($search_box): ?>
        <div id="search-box"<?php print $toggle_label ?>><?php print $search_box; ?></div> <!-- /search box -->
      <?php endif; ?>

      <?php if ($header): ?>
        <div id="header-region"><?php print $header; ?></div> <!-- /header region -->
      <?php endif; ?>

    </div> <!-- /header -->

    <?php if (!empty($menu_bar)): ?>
      <div id="menu-bar">
        <?php print $menu_bar; ?>
      </div> <!-- /menu bar -->
    <?php endif; ?>

    <?php if (!empty($primary_menu)): ?>
      <div id="primary" class="nav">
        <h2 class="element-invisible"><?php print t('Main Menu'); ?></h2>
        <?php print $primary_menu; ?>
      </div> <!-- /primary link menu -->
    <?php endif; ?>

    <?php if (!empty($secondary_menu)): ?>
      <div id="secondary" class="nav">
        <h2 class="element-invisible"><?php print t('Secondary Menu'); ?></h2>
        <?php print $secondary_menu; ?>
      </div> <!-- /secondary link menu -->
    <?php endif; ?>

    <?php if ($breadcrumb): ?>
      <div id="breadcrumb">
        <h2 class="element-invisible"><?php print t('You are here:'); ?></h2>
        <?php print $breadcrumb; ?>
      </div> <!-- /breadcrumb -->
    <?php endif; ?>

    <?php if ($messages or $help): ?>
      <div id="messages-and-help">
        <h2 class="element-invisible"><?php print t('System Messages'); ?></h2>
        <?php if ($messages): print $messages; endif; ?>
        <?php if ($help): print $help; endif; ?>
      </div> <!-- /messages/help -->
    <?php endif; ?>

    <?php if ($secondary_content): ?>
      <div id="secondary-content"><?php print $secondary_content; ?></div> <!-- /secondary-content -->
    <?php endif; ?>

    <div id="columns"><div class="columns-inner clearfix">

      <div id="content-column"><div class="content-inner">

        <?php if ($mission): ?>
          <div id="mission"><?php print $mission; ?></div> <!-- /mission -->
        <?php endif; ?>

        <?php if ($content_top): ?>
          <div id="content-top"><?php print $content_top; ?></div> <!-- /content-top -->
        <?php endif; ?>

        <div id="main-content">

          <?php if ($title or $tabs): ?>
            <div id="main-content-header">
              <?php if ($title): ?><h1 id="page-title"><?php print $title; ?></h1><?php endif; ?>
              <?php if ($tabs): ?>
                <div class="local-tasks"><?php print $tabs; ?></div>
              <?php endif; ?>
            </div>
          <?php endif; ?>

          <?php if ($content_aside): ?>
            <div id="content-aside"><?php print $content_aside; ?></div> <!-- /content-aside -->
          <?php endif; ?>

          <div id="content"><?php print $content; ?></div>

        </div> <!-- /main-content -->

        <?php if ($content_bottom): ?>
          <div id="content-bottom"><?php print $content_bottom; ?></div> <!-- /content-bottom -->
        <?php endif; ?>

      </div></div> <!-- /content-column -->

      <?php if ($left): ?>
        <div id="sidebar-first" class="sidebar"><?php print $left; ?></div> <!-- /sidebar-first -->
      <?php endif; ?>

      <?php if ($right): ?>
        <div id="sidebar-last" class="sidebar"><?php print $right; ?></div> <!-- /sidebar-last -->
      <?php endif; ?>

    </div></div> <!-- /columns -->

    <?php if ($tertiary_content): ?>
      <div id="tertiary-content"><?php print $tertiary_content; ?></div> <!-- /tertiary-content -->
    <?php endif; ?>

    <?php if ($footer or $footer_message or $feed_icons): ?>
      <div id="footer">

        <?php if ($footer): ?>
          <div id="footer-region"><?php print $footer; ?></div> <!-- /footer-region -->
        <?php endif; ?>

        <?php if ($footer_message): ?>
          <div id="footer-message"><?php print $footer_message; ?></div> <!-- /footer-message -->
        <?php endif; ?>

        <?php if ($feed_icons): ?>
          <div id="feed-icons"><?php print $feed_icons; ?></div> <!-- /feed icons -->
        <?php endif; ?>

      </div> <!-- /footer -->
    <?php endif; ?>

  </div> <!-- /container -->

  <?php print $closure ?>

</body>
</html>