<?php
// $Id: context_ui-list-contexts.tpl.php,v 1.1.2.1 2010/04/21 01:23:38 darthsteven Exp $
/**
 * @file
 *
 * Displays the list of contexts on the administration screen.
 */
?>

<p><?php print $help ?></p>

<?php foreach ($contexts_tree as $namespace => $attributes): ?>
  <?php foreach ($attributes as $attribute => $contexts): ?>
    <div class='context-namespace-attribute context-<?php print $namespace ?>-<?php print $attribute ?> clear'>
      <div class='context-namespace-attribute-title'>
        <?php print $namespace ?> &gt; <?php print $attribute ?>
      </div>
      <?php foreach ($contexts as $name => $context): ?>
        <table class="contexts-entry <?php print $context->classes ?>">
          <tbody>
            <tr>
              <td class="context-name">
                <?php print $help_type_icon ?>
                <?php print t('<em>@type</em> context: <strong>@context</strong>', array('@type' => $context->type, '@context' => $context->name)) ?>
                <?php if (!empty($context->tag)): ?>
                  &nbsp;(<?php print $context->tag ?>)
                <?php endif ?>
              </td>
              <td class="context-ops"><?php print $context->ops ?></td>
            </tr>
            <tr>
              <td>
                <?php if ($context->conditions): ?>
                  <?php print t('Conditions: @conditions', array('@conditions' => $context->conditions)) ?> <br />
                <?php endif ?>
                <?php if ($context->reactions): ?>
                  <?php print t('Reactions: @reactions', array('@reactions' => $context->reactions)) ?>
                <?php endif ?>
              </td>
              <td colspan="2" class="description">
                <?php print $context->description ?>
              </td>
            </tr>
          </tbody>
        </table>
      <?php endforeach ?>
    </div>
  <?php endforeach ?>
<?php endforeach ?>
