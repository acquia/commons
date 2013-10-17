#!/bin/bash
set -e

#modules=(commons_activity_streams commons_featured commons_notices commons_profile_social commons_user_profile_pages commons_body commons_follow commons_notify commons_q_a commons_utility_links commons_bw commons_groups commons_pages commons_radioactivity commons_wikis commons_content_moderation commons_like commons_polls commons_search commons_wysiwyg commons_documents commons_location commons_posts commons_site_homepage commons_events commons_misc commons_profile_base commons_topics commons_social_sharing commons_trusted_contacts)
themes=(commons_origins)

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
    for i in "${modules[@]}"; do
      echo $i
      cd $i
      if [[ -n $RESET ]]; then
        git reset --hard HEAD
      fi
      git pull origin 7.x-3.x
      cd ..
    done
    cd $BUILD_PATH/repos/themes/commons_origins
    git pull origin 7.x-3.x
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
        rm -rf ./publish
        # do we have the profile?
        if [[ -d $BUILD_PATH/commons_profile ]]; then
          if [[ -d $BUILD_PATH/repos ]]; then
            rm -f /tmp/commons.tar.gz
            drush make --no-cache --no-core --contrib-destination --tar $BUILD_PATH/commons_profile/drupal-org.make /tmp/commons
            drush make --no-cache --prepare-install --drupal-org=core $BUILD_PATH/commons_profile/drupal-org-core.make ./publish
          else
            mkdir $BUILD_PATH/repos
            mkdir $BUILD_PATH/repos/modules
            mkdir $BUILD_PATH/repos/themes
            build_distro $BUILD_PATH
          fi
          # symlink the profile to our dev copy
          chmod -R 777 $BUILD_PATH/publish/sites/default
          rm -rf publish/profiles/commons
          ln -s $BUILD_PATH/commons_profile publish/profiles/commons
          cd publish/profiles
          tar -zxvf /tmp/commons.tar.gz
          chmod -R 775 $BUILD_PATH/publish/profiles/commons
        else
          git clone --branch 7.x-3.x-merged ${USERNAME}@git.drupal.org:project/commons.git commons_profile
          build_distro $BUILD_PATH
        fi
    else
      mkdir $BUILD_PATH
      build_distro $BUILD_PATH $USERNAME
    fi
}

# This allows you to test the make file without needing to upload it to drupal.org and run the main make file.
update() {
  if [[ -d $DOCROOT ]]; then
    cd $DOCROOT
    # do we have the profile?
    if [[ -d $DOCROOT/profiles/commons ]]; then
      # do we have an installed commons profile?
        rm -f /tmp/publish.tar.gz
        rm -f /tmp/commons.tar.gz
        drush make --tar --drupal-org=core profiles/commons/drupal-org-core.make /tmp/publish
        drush make --tar --drupal-org profiles/commons/drupal-org.make /tmp/commons
        cd ..
        tar -zxvf /tmp/publish.tar.gz
        cd publish/profiles
        # remove the symlinks in the repos before we execute
        find . -mindepth 2 -type l | awk -F/ '{print $5}' | sed '/^$/d' > /tmp/repos.txt
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
      echo "Usage: build_distro.sh test_makefile [build_path]"
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
