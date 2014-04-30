#!/bin/bash
#set -e

#modules=(commons_activity_streams commons_featured commons_notices commons_profile_social commons_user_profile_pages commons_body commons_follow commons_notify commons_q_a commons_utility_links commons_bw commons_groups commons_pages commons_radioactivity commons_wikis commons_content_moderation commons_like commons_polls commons_search commons_wysiwyg commons_documents commons_location commons_posts commons_site_homepage commons_events commons_misc commons_profile_base commons_topics commons_social_sharing commons_trusted_contacts)
#themes=(commons_origins)

merge_repos() {
  cd $BUILD_PATH/commons_profile
  for i in "${modules[@]}"; do
    if [[ -n $USERNAME ]]; then
      git remote add ${i} ${USERNAME}@git.drupal.org:project/${i}.git
    else
      git remote add ${i} http://git.drupal.org/project/${i}.git
    fi
    git fetch ${i}
    git merge -s ours --no-commit ${i}/7.x-3.x
    git read-tree --prefix=modules/commons/${i} -u ${i}/7.x-3.x
    git commit -m "Merged ${i} into Commons repo"
    git remote rm ${i}
    echo "Successfully added $i to commons profile"
  done
  #do the theme now
  i=commons_origins
  if [[ -n $USERNAME ]]; then
    git remote add ${i} ${USERNAME}@git.drupal.org:project/${i}.git
  else
    git remote add ${i} http://git.drupal.org/project/${i}.git
  fi
  git fetch ${i}
  git merge -s ours --no-commit ${i}/7.x-3.x
  git read-tree --prefix=themes/commons/${i} -u ${i}/7.x-3.x
  git commit -m "Merged ${i} into Commons repo"
  echo "Successfully added $i to commons profile"
}

# this function is no longer needed because we're in one repo now.
pull_git() {
    cd $BUILD_PATH/commons_profile
    if [[ -n $RESET ]]; then
      git reset --hard HEAD
    fi
    git pull origin 7.x-3.x

    cd $BUILD_PATH/repos/modules
    for i in `ls | awk -F/ '{print $1}'`; do
      echo $i
      cd $i
      if [[ -n $RESET ]]; then
        git reset --hard HEAD
      fi
      git pull origin
      cd ..
    done
}

release_notes() {
  rm -rf rn.txt
  pull_git $BUILD_PATH
  OUTPUT="<h2>Release Notes for $RELEASE</h2>"
  cd $BUILD_PATH/commons_profile
  OUTPUT="$OUTPUT <h3>Drupal Commons:</h3> `drush rn --date $FROM_DATE $TO_DATE`"

  ## old repos. don't use this anymore
  # cd $BUILD_PATH/repos/modules
  # for i in "${modules[@]}"; do
  #  echo $i
  #  cd $i
  #  RN=`drush rn --date $FROM_DATE $TO_DATE`
  #  if [[ -n $RN ]]; then
  #    OUTPUT="$OUTPUT <h3>$i:</h3> $RN"
  #  fi
  #  cd ..
  #done
  #cd $BUILD_PATH/repos/themes/commons_origins
  #RN=`drush rn --date $FROM_DATE $TO_DATE`
  #if [[ -n $RN ]]; then
  #  OUTPUT="$OUTPUT <h3>commons_origins:</h3> $RN"
  #fi

  echo $OUTPUT >> $BUILD_PATH/rn.txt
  echo "Release notes for $RELEASE created at $BUILD_PATH/rn.txt"
}

build_distro() {
  if [[ -d $BUILD_PATH ]]; then
      cd $BUILD_PATH
      #backup the sites directory
      if [[ -d docroot ]]; then
        rm -rf ./docroot
      fi
      # do we have the profile?
      if [[ -d $BUILD_PATH/commons_profile ]]; then
        if [[ -d $BUILD_PATH/repos ]]; then
          rm -f /tmp/commons.tar.gz
          drush make --no-cache --prepare-install --drupal-org=core $BUILD_PATH/commons_profile/drupal-org-core.make $BUILD_PATH/docroot
          drush make --no-cache --no-core --contrib-destination --tar $BUILD_PATH/commons_profile/drupal-org.make /tmp/commons
        else
          mkdir -p $BUILD_PATH/repos/modules/contrib
          cd $BUILD_PATH/repos/modules/contrib
          for i in "${modules[@]}"; do
            echo "bringing in ${i} for $USERNAME";
            if [[ -n $USERNAME ]]; then
              git clone ${USERNAME}@git.drupal.org:project/${i}.git
            else
              git clone http://git.drupal.org/project/${i}.git
            fi
          done
          cd $BUILD_PATH/repos
          mkdir -p $BUILD_PATH/repos/themes/contrib
          cd $BUILD_PATH/repos/themes
          for i in "${themes[@]}"; do
            if [[ -n $USERNAME ]]; then
              git clone ${USERNAME}@git.drupal.org:project/${i}.git
            else
              git clone http://git.drupal.org/project/${i}.git
            fi
          done
          build_distro $BUILD_PATH
        fi
        # symlink the profile sites folder to our dev copy
        cd docroot
        if [[ -d $BUILD_PATH/sites ]]; then
          rm -rf $BUILD_PATH/docroot/sites
          ln -s ../sites $BUILD_PATH/docroot/sites
        else
          mv $BUILD_PATH/docroot/sites $BUILD_PATH/sites
          ln -s ../sites $BUILD_PATH/docroot/sites
        fi
        chmod -R 777 $BUILD_PATH/docroot/sites/default

        ## put commons profile and modules into the profile folder
        rm -rf docroot/profiles/commons
        if [ -e $BUILD_PATH/repos.txt ]; then
          UNTAR="tar -zxvf /tmp/commons.tar.gz -X $BUILD_PATH/repos.txt"
        else
          cd $BUILD_PATH/repos
          find * -mindepth 1 -maxdepth 2 -type d -not -path ".*" -not -path "modules/.*" -not -path "themes/.*" -not -path "modules/contrib" -not -path "themes/contrib" > $BUILD_PATH/repos.txt
          # exclude repos since we're updating already by linking it to the repos directory.
          UNTAR="tar -zxvf /tmp/commons.tar.gz -X $BUILD_PATH/repos.txt"
        fi
        cd $BUILD_PATH/docroot/profiles
        eval $UNTAR
        cd commons
        ln -s ../../../commons_profile/* .
        ln -s ../../../../commons_profile/modules/commons ${BUILD_PATH}/docroot/profiles/commons/modules/
        ln -s ../../../../commons_profile/themes/commons ${BUILD_PATH}/docroot/profiles/commons/themes/
        for line in $(cat $BUILD_PATH/repos.txt); do
          ln -s ../../../../../repos/${line} ${BUILD_PATH}/docroot/profiles/commons/$(echo ${line} | awk -F/ '{print $1}')/contrib/
        done
        chmod -R 775 $BUILD_PATH/docroot/profiles/commons
      else
        git clone --branch 7.x-3.x ${USERNAME}@git.drupal.org:project/commons.git commons_profile
        build_distro $BUILD_PATH
      fi
  else
    mkdir $BUILD_PATH
    build_distro $BUILD_PATH $USERNAME
  fi
}

site_install() {
  read -p "You're about to DESTROY all data for site ${SITE} Are you sure? " -n 1 -r
  if [[ $REPLY =~ ^[Yy]$ ]]; then
    cd ${BUILD_PATH}/docroot/sites/${SITE}
    drush -y sql-drop
    drush site-install --site-name=${SITE} --account-name=admin --account-pass=${ADMIN_PASS} --account-mail=${ADMIN_EMAIL} --site-mail=commons_site@example.com -v -y commons commons_anonymous_welcome_text_form.commons_install_example_content=${DEMO_CONTENT} commons_anonymous_welcome_text_form.commons_anonymous_welcome_title="Commons Example Site" commons_anonymous_welcome_text_form.commons_anonymous_welcome_body="Using the site-install version of commons." commons_create_first_group.commons_first_group_title="Sales Group" commons_create_first_group.commons_first_group_body="This is the sales group from site-install."
  fi
}

# This allows you to test the make file without needing to upload it to drupal.org and run the main make file.
update() {
  if [[ -d $DOCROOT ]]; then
    cd $DOCROOT
    # do we have the profile?
    if [[ -d $DOCROOT/profiles/commons ]]; then
      # do we have an installed commons profile?
        rm -f /tmp/docroot.tar.gz
        rm -f /tmp/commons.tar.gz
        drush make --no-cache --tar --drupal-org=core profiles/commons/drupal-org-core.make /tmp/docroot
        drush make --no-core --no-cache --tar --drupal-org profiles/commons/drupal-org.make /tmp/commons
        cd ..
        tar -zxvf /tmp/docroot.tar.gz
        cd docroot/profiles/commons/modules/contrib
        # remove the symlinks in the repos before we execute
        find . -type l | awk -F/ '{print $2}' > /tmp/repos.txt
        cd $DOCROOT/profiles
        # exclude repos since we're updating already by linking it to the repos directory.
        UNTAR="tar -zxvf /tmp/commons.tar.gz -X /tmp/repos.txt"
        eval $UNTAR
        echo "Successfully Updated drupal from make files"
        exit 0
    fi
  fi
  echo "Unable to find Build path or drupal root. Please run build first"
  exit 1
}

case $1 in
  site-install)
    if [[ -n $2 ]] && [[ -n $3 ]]; then
      BUILD_PATH=$2
    else
      echo "Usage build_distro.sh site-install [build_path] [site] [demo-content] [admin-email] [admin-pass]"
    fi
    if [[ -n $3 ]]; then
      SITE=$3
    else
      SITE='default'
    fi
    if [[ -n $4 ]]; then
      DEMO_CONTENT='TRUE'
    else
      DEMO_CONTENT='FALSE'
    fi
    if [[ -n $5 ]]; then
      ADMIN_EMAIL=$5
    else
      ADMIN_EMAIL='admin@example.com'
    fi
    if [[ -n $6 ]]; then
      ADMIN_PASS=$6
    else
      ADMIN_PASS='admin'
    fi

    site_install $BUILD_PATH $SITE $DEMO_CONTENT $ADMIN_EMAIL $ADMIN_PASS;;
  pull)
    if [[ -n $2 ]]; then
      BUILD_PATH=$2
      if [[ -n $3 ]]; then
       RESET=1
      fi
    else
      echo "Usage: build_distro.sh pull [build_path]"
      exit 1
    fi
    pull_git $BUILD_PATH $RESET;;
  build)
    if [[ -n $2 ]]; then
      BUILD_PATH=$2
    else
      echo "Usage: build_distro.sh build [build_path]"
      exit 1
    fi
    if [[ -n $3 ]]; then
      USERNAME=$3
    fi
    build_distro $BUILD_PATH $USERNAME;;
  rn)
    if [[ -n $2 ]] && [[ -n $3 ]] && [[ -n $4 ]] && [[ -n $5 ]]; then
      BUILD_PATH=$2
      RELEASE=$3
      FROM_DATE=$4
      TO_DATE=$5
    else
      echo "Usage: build_distro.sh rn [build_path] [release] [from_date] [to_date]"
      exit 1
    fi
    release_notes $BUILD_PATH $RELEASE $FROM_DATE $TO_DATE;;
  update)
    if [[ -n $2 ]]; then
      DOCROOT=$2
    else
      echo "Usage: build_distro.sh update [DOCROOT]"
      exit 1
    fi
    if [[ -n $3 ]]; then
      USERNAME=$3
    fi
    update $DOCROOT;;
  merge_repos)
    if [[ -n $2 ]]; then
      BUILD_PATH=$2
    else
      echo "Usage: build_distro.sh build [build_path]"
      exit 1
    fi
    if [[ -n $3 ]]; then
      USERNAME=$3
    fi
    merge_repos $BUILD_PATH $USERNAME;;
esac
