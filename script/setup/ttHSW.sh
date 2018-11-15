#! /bin/bash
#
# A helper script to setup and install ttHSW
#
# Note: it assumes a certain directory structure.
#

parent_path=$(cd "$(dirname "${BASH_SOURCE[0]}")"; pwd -P)
ttHSW_path=${parent_path}/../../external/ttHSW
ttHSW_local=${parent_path}/../../local

#
# Prerequisites
#
## Returns from a script if needed stuff is missing
if [ ! -d ${ttHSW_path} ]; then
    echo "ttHSW is missing!"
    return 1
fi

if [ -z ${ROOTSYS} ] || [ ! -d ${ROOTSYS} ]; then
    echo "ROOTSYS is missing!" "Set up the ROOT."
    return 1
fi

#
#   Functions
#
Prepare_ttHSW()
{
    local current_pwd=${PWD}
    mkdir ${ttHSW_path}/build
    cd ${ttHSW_path}/build
    
    cmake .. -DCMAKE_INSTALL_PREFIX=${ttHSW_local}
    cd ${current_pwd}
}

Build_install_ttHSW()
{
    local current_pwd=${PWD}
    cd ${ttHSW_path}/build
    
    make -j $(nproc)
    make install
    cd ${current_pwd}
}

#
#   Execution part
#
Prepare_ttHSW
Build_install_ttHSW
. ${ttHSW_local}/setup.sh
