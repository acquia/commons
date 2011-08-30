<?php
// $Id: box.tpl.php,v 1.1 2009/08/19 04:28:07 sociotech Exp $
?>

<div class="box">

<?php if ($title): ?>
  <h2 class="title"><?php print $title ?></h2>
<?php endif; ?>

  <div class="content"><?php print $content ?></div>
</div><!-- /box -->