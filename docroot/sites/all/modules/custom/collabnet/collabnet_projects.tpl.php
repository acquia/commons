<?php
// $Id: collabnet_projects.tpl.php
?>

<?php
  $length = count($rows) / 2;
  $i = 0;
  
  foreach ($rows as $key => $project_info) {
    $project_link = 'http://socialteamforge.net/sf/go/' . $project_info['id'];
    if ($i == 0 || $i == $length) {
?>
      <div class="grid_5 content">
<?php
    }
?>
    <h3><?php print(l($project_info['title'], $project_link)); ?></h3>
    <p><?php print('Description: ' . $project_info['description']); ?></p>
    <p><?php print('Date Created: ' . $project_info['dateCreated']); ?></p>
    <p><?php print(l('View project in TeamForge.', $project_link))?></p>
<?php
    if ($i == ($length - 1) || $i == (2 * $length) - 1) {
?>
      </div>
<?php
    }
    $i++;
  }
?>
