<?php
// $Id: features-admin-components.tpl.php,v 1.1.2.2 2009/10/01 20:25:40 yhahn Exp $
?>
<div class='clear-block features-components'>
  <div class='column'>
    <div class='info'>
      <h3><?php print $name ?></h3>
      <div class='description'><?php print $description ?></div>
      <?php print $dependencies ?>
    </div>
  </div>
  <div class='column'>
    <div class='components'>
      <?php print $components ?>
      <div class='buttons clear-block'><?php print $buttons ?></div>
    </div>
  </div>
  <?php print $form ?>
</div>