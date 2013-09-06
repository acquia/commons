#!/bin/bash
set -e

#
# Build the distribution using the same process used on Drupal.org
#
# When building, we expect that you're building within a directory structure like
# the following:
#   commons/
#     /commons_profile
#     /docroot
#     /docroot2, etc, etc
#     /repos
#     /patches
#     /screenshots
#
#
# Usage: scripts/build.sh [-y] <destination> from the profile main directory.
#
# BUILD_ROOT = development path for commons
# DESTINATION = docroot for commons builds

confirm () {
  read -r -p "${1:-Are you sure? [Y/n]} " response
  case $response in
    [yY][eE][sS]|[yY])
      true
      ;;
    *)
      false
      ;;
  esac
}

# Figure out directory real path.
realpath () {
  TARGET_FILE=$1

  cd `dirname $TARGET_FILE`
  TARGET_FILE=`basename $TARGET_FILE`

  while [ -L "$TARGET_FILE" ]
  do
    TARGET_FILE=`readlink $TARGET_FILE`
    cd `dirname $TARGET_FILE`
    TARGET_FILE=`basename $TARGET_FILE`
  done

  PHYS_DIR=`pwd -P`
  RESULT=$PHYS_DIR/$TARGET_FILE
  echo $RESULT
}

usage() {
  echo "Usage: build.sh [-y] <DESTINATION_PATH>" >&2
  echo "Use -y to skip deletion confirmation" >&2
  echo "Use --gitusername to use authenticated git instead of http" >&2
  echo "Use --build_root to build the whole dir structure, not just the docroot" > &2
  exit 1
}

BUILD_ROOT=`pwd -P`
DESTINATION=$1
ASK=true

while getopts ":yhg:" opt; do
  case $opt in
    y)
      DESTINATION=$2
      ASK=false
      ;;
    h)
      usage
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      usage
      ;;
  esac
done

if [ "x$DESTINATION" == "x" ]; then
  usage
fi

if [ ! -f drupal-org.make ]; then
  echo "[error] Run this script from the distribution base path, eg scripts/build.sh"
  exit 1
fi

DESTINATION=$(realpath $DESTINATION)

case $OSTYPE in
  darwin*)
    TEMP_BUILD=`mktemp -d -t tmpdir`
    ;;
  *)
    TEMP_BUILD=`mktemp -d`
    ;;
esac
# Drush make expects destination to be empty.
rmdir $TEMP_BUILD

if [ -d $DESTINATION ]; then
  echo "Removing existing destination: $DESTINATION"
  if $ASK; then
    confirm && chmod -R 777 $DESTINATION && rm -rf $DESTINATION
    if [ -d $DESTINATION ]; then
      echo "Aborted."
      exit 1
    fi
  else
    chmod -R 777 $DESTINATION && rm -rf $DESTINATION
  fi
  echo "done"
fi

# Build the profile.
echo "Building the profile..."
echo `pwd`

if [[ -d $BUILD_PATH ]]; then
    cd $BUILD_PATH
    rm -rf ./publish
    # do we have the profile?
    if [[ -d $BUILD_PATH/commons_profile ]]; then
      if [[ -d $BUILD_PATH/repos ]]; then
        drush make commons_profile/build-commons.make --no-cache --working-copy --prepare-install ./publish
      else
        mkdir $BUILD_PATH/repos
        mkdir $BUILD_PATH/repos/modules
        mkdir $BUILD_PATH/repos/themes
        build_distro $BUILD_PATH
      fi
      chmod -R 777 publish/sites/default
      # symlink the profile to our dev copy
      echo "untaring"
      tar -czvf modules.tar.gz publish/profiles/commons/modules/contrib
      tar -czvf themes.tar.gz publish/profiles/commons/themes/contrib
      rm -rf publish/profiles/commons
      ln -s $BUILD_PATH/commons_profile publish/profiles/commons
      tar -zxvf modules.tar.gz
      tar -zxvf themes.tar.gz
    else
      git clone --branch 7.x-3.x-merged ${USERNAME}@git.drupal.org:project/commons.git commons_profile
      build_distro $BUILD_PATH
    fi
else
  mkdir $BUILD_PATH
  build_distro $BUILD_PATH $USERNAME
fi



drush make --no-cache --no-core --contrib-destination drupal-org.make tmp

# Build a drupal-org-core.make file if it doesn't exist.
if [ ! -f drupal-org-core.make ]; then
  cat >> drupal-org-core.make <<EOF
api = 2
core = 7.x
projects[drupal] = 7
EOF
fi

# Build the distribution and copy the profile in place.
echo "Building the distribution..."
drush make drupal-org-core.make $TEMP_BUILD
echo -n "Moving to destination... "
cp -r tmp $TEMP_BUILD/profiles/commerce_kickstart
rm -rf tmp
cp -r . $TEMP_BUILD/profiles/commerce_kickstart
mv $TEMP_BUILD $DESTINATION
echo "done"
