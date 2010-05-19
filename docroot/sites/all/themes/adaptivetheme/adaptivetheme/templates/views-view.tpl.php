<?php // $Id: views-view.tpl.php,v 1.1.2.4 2010/03/14 01:59:18 jmburnz Exp $
// adaptivethemes.com

/**
 * @file views-view.tpl.php
 * Main view template
 *
 * Variables available:
 * - $css_name: A css-safe version of the view name.
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 * - $admin_links: A rendered list of administrative links
 * - $admin_links_raw: A list of administrative links suitable for theme('links')
 * - $skinr: Print skinr module classes if any.
 *
 * @ingroup views_templates
 */
?>
<?php
// Conditionally add CSS classes.
$classes = array();
if (theme_get_setting(cleanup_views_css_name)) {
  $classes[] = 'view-' . $css_name;
}
if (theme_get_setting(cleanup_views_view_name)) {
  $classes[] = 'view-id-' . $name;
}
if (theme_get_setting(cleanup_views_display_id)) {
  $classes[] = 'view-display-id-' . $display_id;
}
if (theme_get_setting(cleanup_views_dom_id)) {
  $classes[] = 'view-dom-id-' . $dom_id;
}
//Skinr module classes.
$classes[] = $skinr;
if ($classes) {
  $views_classes = implode(' ', $classes);
}
?>
<div class="view<?php print $views_classes ? ' ' . $views_classes : '';?>">
  <?php if ($admin_links): ?>
    <div class="views-admin-links views-hide">
      <?php print $admin_links; ?>
    </div>
  <?php endif; ?>
  <?php if ($header): ?>
    <div class="view-header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>

  <?php if ($exposed): ?>
    <div class="view-filters">
      <?php print $exposed; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_before): ?>
    <div class="attachment attachment-before">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>

  <?php if ($rows): ?>
    <div class="view-content">
      <?php print $rows; ?>
    </div>
  <?php elseif ($empty): ?>
    <div class="view-empty">
      <?php print $empty; ?>
    </div>
  <?php endif; ?>

  <?php if ($pager): ?>
    <?php print $pager; ?>
  <?php endif; ?>

  <?php if ($attachment_after): ?>
    <div class="attachment attachment-after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <?php print $more; ?>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <div class="feed-icon">
      <?php print $feed_icon; ?>
    </div>
  <?php endif; ?>
</div> <!-- /views-view -->
