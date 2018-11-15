#!/bin/sh
#
# A script that links custom githooks to your .git/hooks/
#

#
# function space
#
Link_hooks()
{
    GIT_PWD=`git rev-parse --show-toplevel`
    echo "GIT top directory: ${GIT_PWD}"

    hookname="pre-commit"
    if [ -f ${GIT_PWD}/.git/hooks/${hookname} ]; then
        echo "Hook ${hookname} exists => do nothing."
    else
        echo "Linking hook ${hookname}"
        ln -s ../../githooks/${hookname} ${GIT_PWD}/.git/hooks/${hookname}
    fi
    
    unset GIT_PWD
}

#
# execute
#
Link_hooks
