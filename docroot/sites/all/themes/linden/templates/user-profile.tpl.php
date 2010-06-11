<div class="disa-user-profile">
    <div class="picture">
    <?
        if ($account->picture) {
            $user_pic = theme('imagecache', 'profile_pictures', $account->picture, $alt, $title, $attributes);
        } else {
            $user_pic = theme('imagecache', 'profile_pictures', 'default-user.png', $alt, $title, $attributes);
        }
        print $user_pic;
    ?>
        <div class="profile-info-box profile-created">
            <label>Member Since:</label>
            <span><?php print date("Y", $account->created); ?></span>
        </div>
    </div>
    <div class="info">
        <?php
            $pts = userpoints_get_current_points($account->uid);
            $pts_class = 'pts-none';
            if($pts > 5000){
                $pts_class = 'pts-gold';
            } else if($pts > 2500){
                $pts_class = 'pts-silver';
            } else if($pts > 100){
                $pts_class = 'pts-bronze';
            }
        ?>
        <div class="profile-info-box profile-points">
            <label>Points:</label>
            <span class="star <?php print $pts_class; ?>"></span>
            <span><?php print ($pts ? $pts : '<em>0</em>'); ?> Points</span>
            <div class="clear"></div>
        </div>
        <div class="profile-info-box profile-name">
            <label>Name:</label>
            <span><?php print ($account->profile_name ? $account->profile_name . ' ' . $account->profile_last_name : '<em>Real name not provided</em>'); ?></span>
        </div>
        <div class="profile-info-box profile-job">
            <label>Job Title:</label>
            <span><?php print ($account->profile_job ? $account->profile_job : '<em>Title not provided</em>'); ?></span>
        </div>
        <div class="profile-info-box profile-organization">
            <label>Organization:</label>
            <span><?php print ($account->profile_organization ? $account->profile_organization : '<em>Organization not provided</em>'); ?></span>
        </div>
        <div class="profile-info-box profile-location">
            <label>Location:</label>
            <span><?php print ($account->profile_location ? $account->profile_location : '<em>Location not provided</em>'); ?></span>
        </div>
        <div class="profile-info-box profile-interests">
            <label>Interests:</label>
            <span><?php print ($account->profile_interests ? $account->profile_interests : '<em>None provided</em>'); ?></span>
        </div>
        <div class="profile-info-box profile-aboutme">
            <label>About Me:</label>
            <span><?php print ($account->profile_aboutme ? $account->profile_aboutme : '<em>This user has not yet completed their bio.</em>'); ?></span>
        </div>
    </div>
    <div class="clear"></div>
</div>
