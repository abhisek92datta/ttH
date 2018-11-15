# Analyzers

This is for "ttH " -  H to bb" analysis - 2017 Data

# Installation :

source /cvmfs/cms.cern.ch/cmsset_default.sh

export SCRAM_ARCH="slc6_amd64_gcc630"

source /cvmfs/cms.cern.ch/crab3/crab.sh

export CMSSW_VERSION="CMSSW_9_4_6_patch1"

cmsrel $CMSSW_VERSION

cd ${CMSSW_VERSION}/src

cmsenv

cd ../..

git clone https://abdatta@gitlab.cern.ch/Cornell/ttH.git

cd ttH/

git checkout ttHbb_v2_Data2017

cd ..

. ttH/analyzers/Analyzer_run_recipe.sh

cd ${CMSSW_BASE}/src/analyzers/ttH_bb/

# Step 1 : Run to Create Ntuples :

# For MC :
   
# To Run Locally:

in test/CU_ttH_mc_EDA_cfg.py :

1. put desired MC filename 

cmsRun test/CU_ttH_mc_EDA_cfg.py > output_log.txt

# To Run on GRID using CRAB :

crab submit -c crabConfig_MC.py

For submitting multiple jobs for different MC samples simultaneously :

1. cd ${CMSSW_BASE}/src/analyzers/ttH_bb/
2. cp macros/MC_crab_jobs/* .
3. ./crab_submit.sh

# For DATA :

# To Run Locally:

in test/CU_ttH_data_EDA_cfg.py :

1. put desired DATA filename
2. put latest Lumi (JSON) filename

cmsRun test/CU_ttH_data_EDA_cfg.py > output_log.txt

# To Run on GRID using CRAB :

crab submit -c crabConfig_Data.py

For submitting multiple jobs for different Datasets simultaneously :

1. cd ${CMSSW_BASE}/src/analyzers/ttH_bb/
2. cp macros/Data_crab_jobs/* .
3. ./crab_submit.sh


# Step 2 : Running macro on ntuples to obtain yields and histograms for Control Plots


# Step 3 : Combining MC and Data histograms and obtaining Data-MC comparison plots


# Step 4 : To Run BDT on ntuples


# Step 5 : Obtaining Limits using Higgs Combine 


# Additional Stuff :

# CRAB commands :
To check status :
crab status -d \<crab_output_directory_name\>

To resubmit :
crab resubmit -d \<crab_output_directory_name\>

To kill : 
crab kill -d \<crab_output_directory_name\>

# Formatting :

clang-format -style=file -i *.h
clang-format -style=file -i *.cc

# Before Commit :

. script/setup/init.sh



