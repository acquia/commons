<?php // $Id: page.tpl.php,v 1.1.2.4 2010/01/01 21:13:37 jmburnz Exp $
// adaptivethemes.com

/**
 * @file page.tpl.php
 * Theme implementation to display a single Drupal page for Genesis Subtheme.
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
 * - $head: Markup for the HEAD (including meta tags, keyword tags, and
 *     so on).
 * - $head_title: A modified version of the page title, for use in the TITLE tag.
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *     for the page.
 * - $section_class: A CSS class that uses .+ the 1st URL argument, allows for
 *     themeing site sections based on path.
 * - $classes: A set of CSS classes (preprocess $body_classes + Genesis custom classes). 
 *     This contains flags indicating the current layout (multiple columns, single column), 
 *     the current path, whether the user is logged in, and so on.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *     when linking to the front page. This includes the language domain or prefix.
 * - $site_logo: The preprocessed $logo varaible. Includes the path to the logo image, 
 *     as defined in theme configuration and wrapped in an anchor linking to the homepage.
 * - $site_name: The name of the site (preprocessed) wrapped in an anchor linking to the homepage. 
 *     Empty when display has been disabled in theme settings.
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
 * Page content (in order of occurrance in the default page.tpl.php):
 * - $leaderboard: Custom region for displaying content at the top of the page, useful
 *     for displaying a banner.
 * - $header: The header blocks region for display content in the header.
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
 * - $left: region for the left sidebar.
 * - $right: region for the right sidebar.
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
<body id="at-admin" class="<?php print $section_class . $classes; ?>">
  <div id="wrapper">
    <div id="skip-nav" class="element-invisible">
      <!-- NEVER use display:none to hide skip links - see http://drupal.org/node/472572 -->
      <a href="#main-content"><?php print t('Skip to main content'); ?></a>
    </div>
    <div id="header"><div class="header-inner clearfix">
      <?php if ($primary_menu): ?>
        <div id="primary"><div class="primary-inner">
          <h2 class="element-invisible"><?php print t('Main menu'); ?></h2>
          <?php print $primary_menu; ?> <!-- /primary links menu -->
        </div></div>
      <?php endif; ?>
      <?php if ($linked_site_logo or $linked_site_name or $site_slogan): ?>
        <div id="branding">
          <?php if ($linked_site_logo or $linked_site_name): ?>
            <?php if ($title): ?>
              <div class="logo-site-name"><strong>
                <?php if ($linked_site_logo): ?><span id="logo"><?php print $linked_site_logo; ?></span><?php endif; ?>
                <?php if ($linked_site_name): ?><span id="site-name"><?php print $linked_site_name; ?></span><?php endif; ?>
              </strong></div>           
            <?php else: /* Use h1 when the content title is empty */ ?>     
              <h1 class="logo-site-name">
                <?php if ($linked_site_logo): ?><span id="logo"><?php print $linked_site_logo; ?></span><?php endif; ?>
                <?php if ($linked_site_name): ?><span id="site-name"><?php print $linked_site_name; ?></span><?php endif; ?>
             </h1>
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
        <div id="header-region"><?php print $header; ?></div><!-- /header-region -->
      <?php endif; ?>
      <?php if ($admin_welcome): ?>
        <div id="user-date"><?php print $admin_welcome; ?></div> <!-- /admin welcome -->
      <?php endif; ?>
      <?php if ($admin_user_links): ?>
        <div id="user-menu">
          <h2 class="element-invisible"><?php print t('User menu'); ?></h2>
          <?php print $admin_user_links; ?>
        </div> <!-- /admin user link -->
      <?php endif; ?>
    </div></div> <!-- /header -->
    <div id="shadow"></div>
    <div id="container">
      <?php if ($breadcrumb): ?>
        <div id="breadcrumb">
          <h2 class="element-invisible"><?php print t('You are here:'); ?></h2>
          <?php print $breadcrumb; ?>
        </div> <!-- /breadcrumb -->
      <?php endif; ?>
      <?php if ($messages or $help): ?>
        <div id="messages-and-help">
          <h2 class="element-invisible"><?php print t('System messages:'); ?></h2>
          <?php if ($messages): print $messages; endif; ?>
          <?php if ($help): print $help; endif; ?>
        </div> <!-- /messages and help -->
      <?php endif; ?>
      <?php if ($secondary_content): ?>
        <div id="secondary-content"><?php print $secondary_content; ?></div> <!-- /secondary-content -->
      <?php endif; ?>
      <div id="columns"><div class="columns-inner clearfix">
        <div id="content-column"><div class="content-inner">
          <?php if ($content_top): ?>
            <div id="content-top"><?php print $content_top; ?></div> <!-- /content-top -->
          <?php endif; ?>
          <div id="main-content">
            <?php if ($title or $tabs): ?>
              <div id="main-content-header">
                <?php if ($title): ?><h1 id="page-title"><?php print $title; ?></h1><?php endif; ?> <!-- /page title -->
                <?php if ($tabs): ?>
                  <div class="local-tasks"><?php print $tabs; ?></div> <!-- /tabs -->
                <?php endif; ?>
              </div>
            <?php endif; ?>
            <div id="content"><?php print $content; ?></div> <!-- /content -->
          </div> <!-- /main-content -->
          <?php if ($content_bottom): ?>
            <div id="content-bottom"><?php print $content_bottom; ?></div> <!-- /content-bottom -->
          <?php endif; ?>
        </div></div> <!-- /content-column -->
        <?php if ($left): ?>
          <div id="sidebar-first" class="sidebar"><?php print $left; ?></div> <!-- /sidebar-left -->
        <?php endif; ?>
        <?php if ($right): ?>
          <div id="sidebar-last" class="sidebar"><?php print $right; ?></div> <!-- /sidebar-right -->
        <?php endif; ?>
      </div></div> <!-- /columns -->
      <?php if ($tertiary_content): ?>
        <div id="tertiary-content"><?php print $tertiary_content; ?></div> <!-- /tertiary-content -->
      <?php endif; ?>
      <?php if ($footer or $footer_message or $feed_icons): ?>
        <div id="footer" class="clearfix">
          <?php if ($footer): ?>
            <div id="footer-region"><?php print $footer; ?></div> <!-- /footer-region -->
          <?php endif; ?>
          <?php if ($footer_message): ?>
            <div id="footer-message"><?php print $footer_message; ?></div> <!-- /footer-message -->
          <?php endif; ?>
          <?php if ($feed_icons): ?>
            <div id="feed-icons"><?php print $feed_icons; ?></div>
          <?php endif; ?>
          <?php print $attribution; ?>
        </div> <!-- /footer -->
      <?php endif; ?>
    </div> <!-- /container -->
    <?php print $closure ?>
  </div> <!-- /wrapper -->
</body>
</html>