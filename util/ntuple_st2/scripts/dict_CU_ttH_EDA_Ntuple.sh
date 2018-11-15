#! /bin/bash 

parent_path=$(cd "$(dirname "${BASH_SOURCE[0]}")"; pwd -P)

genreflex \
    ${parent_path}/../../../analyzers/ttH_bb/interface/CU_ttH_EDA_Ntuple.h \
    -o ${parent_path}/../src/dict/ntuple_dict.cc

# ln -s ${parent_path}/../../../analyzers/ttH_bb/src/CU_ttH_EDA_Ntuple.cc \
#     ${parent_path}/../src/dict/CU_ttH_EDA_Ntuple.cc
