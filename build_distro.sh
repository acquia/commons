#!/bin/bash
repos=(commons_activity_streams commons_featured commons_notices commons_profile_social commons_user_profile_pages commons_body commons_follow commons_notify commons_q_a commons_utility_links commons_bw commons_groups commons_pages commons_radioactivity commons_wikis commons_content_moderation commons_like commons_polls commons_search commons_wysiwyg commons_documents commons_location commons_posts commons_site_homepage commons_events commons_misc commons_profile_base commons_topics commons_social_sharing)

pull_git() {
    cd $BUILD_PATH/commons_profile
    if [[ -n $RESET ]]; then
      git reset --hard HEAD
    fi
    git pull origin 7.x-3.x

    cd $BUILD_PATH/repos/modules
    for i in "${repos[@]}"; do
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
  OUTPUT="$OUTPUT <h3>Commons Profile:</h3> `drush rn --date $FROM_DATE $TO_DATE`"

  cd $BUILD_PATH/repos/modules
  for i in "${repos[@]}"; do
    echo $i
    cd $i
    RN=`drush rn --date $FROM_DATE $TO_DATE`
    if [[ -n $RN ]]; then
      OUTPUT="$OUTPUT <h3>$i:</h3> $RN"
    fi
    cd ..
  done
  cd $BUILD_PATH/repos/themes/commons_origins
  RN=`drush rn --date $FROM_DATE $TO_DATE`
  if [[ -n $RN ]]; then
    OUTPUT="$OUTPUT <h3>commons_origins:</h3> $RN"
  fi

  echo $OUTPUT >> $BUILD_PATH/rn.txt
}

build_distro() {
    if [[ -d $BUILD_PATH ]]; then
        cd $BUILD_PATH
        rm -rf ./publish
        # do we have the profile?
        if [[ -d $BUILD_PATH/commons_profile ]]; then
          if [[ -d $BUILD_PATH/repos ]]; then
            drush make commons_profile/build-commons.make --no-cache --working-copy --prepare-install ./publish
            rm -rf publish/profiles/commons/modules/contrib/commons*
            rm -rf publish/profiles/commons/themes/contrib/commons*
          else
            drush make commons_profile/build-commons-dev.make --no-cache --working-copy --prepare-install ./publish
            mkdir $BUILD_PATH/repos
            mkdir $BUILD_PATH/repos/modules
            mkdir $BUILD_PATH/repos/themes
            mv publish/profiles/commons/modules/contrib/commons* repos/modules/
            mv publish/profiles/commons/themes/contrib/commons* repos/themes/
          fi
          ln -sf $BUILD_PATH/repos/modules/commons* publish/profiles/commons/modules/contrib/
          ln -sf $BUILD_PATH/repos/themes/commons* publish/profiles/commons/themes/contrib/
          chmod -R 777 publish/sites/default
          # symlink the profile to our dev copy
          rm -f publish/profiles/commons/*.*
          rm -rf publish/profiles/commons/images
          ln -s $BUILD_PATH/commons_profile/* publish/profiles/commons/
          pull_git
        else
          git clone http://git.drupal.org/project/commons.git commons_profile
          build_distro $BUILD_PATH
        fi
    else
      mkdir $BUILD_PATH
      build_distro $BUILD_PATH
    fi
}

# This allows users to build the most recent release from git and apply it to their directory. No-dev removes the symlinks and puts in real versions of the module.
update() {
    if [[ -d $BUILD_PATH ]]; then
        cd $BUILD_PATH
        # do we have the profile?
        if [[ -d $BUILD_PATH/commons_profile ]]; then
          if [[ $DEV == dev ]]; then
            tar -czvf sites-tmp.tar.gz publish/sites/default
            build_distro $BUILD_PATH
            tar -zxvf sites-tmp.tar.gz
          fi

          if [[ $DEV == nodev ]]; then
            drush make commons_profile/build-commons.make --no-cache --tar publish
            tar -zxvf publish.tar.gz
          fi
        fi
    else
      echo "invalid build path"
      exit 1
    fi
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
    build_distro;;
  update)
    if [[ -n $2 ]]; then
      BUILD_PATH=$2
      if [[ $3 == 'dev' ]] || [[ $3 == 'nodev' ]]; then
        DEV=$3
      else
        DEV='dev'
      fi
    else
      echo "Usage: build_distro.sh update [build_path] [dev|nodev]"
      exit 1
    fi
    update $BUILD_PATH $DEV;;
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
esac