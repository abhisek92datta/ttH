# util/ntuple_st2

## Compilation

Prerequisite: prepare ttHSW.

Steps to build:
* (optional) . scripts/dict_CU_ttH_EDA_Ntuple.sh # produces dict for root files
* mkdir build
* cd build
* (optional) ln -s ../src/dict/*.pcm # ROOT will look for this at runtime
* cmake ..
* make

Notes:
- uncomment ntuple_dict.cc in CMakeLists if intend to use
