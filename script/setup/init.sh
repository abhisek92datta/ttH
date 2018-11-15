#! /bin/bash
#
# A helper script to setup ttH repo
#
# Note: it assumes a certain directory structure.
#

parent_path=$(cd "$(dirname "${BASH_SOURCE[0]}")"; pwd -P)

. ${parent_path}/../../githooks/init.sh
git submodule init
git submodule sync    # Ensure the submodule points to the right place
git submodule update  # Update the submodule
git submodule foreach git checkout master  # Ensure subs are on master branch
git submodule foreach git pull origin master # Pull the latest master
