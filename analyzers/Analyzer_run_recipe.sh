#! /bin/bash
voms-proxy-init -voms cms

parent_path=$(cd "$(dirname "${BASH_SOURCE[0]}")"; pwd -P)

CMSSW_init()
{
    cd ${CMSSW_BASE}/src
    if [ ! -d ".git" ]; then
        git cms-init
    fi
}

CMSSW_build()
{
    scram b &> build.log
}

#
# Do block
#
CMSSW_init
CMSSW_build
. ${parent_path}/scripts/setup/ttH_bb_pkgs.sh
CMSSW_build
