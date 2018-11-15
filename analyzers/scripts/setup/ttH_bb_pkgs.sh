#! /bin/bash

parent_path=$(cd "$(dirname "${BASH_SOURCE[0]}")"; pwd -P)
cd $CMSSW_BASE/src

### Deterministic Seeds
git cms-merge-topic yrath:deterministicSeeds

### Electrons

### CutBased ID
git cms-merge-topic lsoffi:CMSSW_9_4_0_pre3_TnP
### MVA ID
git cms-merge-topic guitargeek:ElectronID_MVA2017_940pre3
### ECAL scale and resolution corrections
#git cms-merge-topic cms-egamma:EGIDV1AndScaleSmear_940
git cms-merge-topic cms-egamma:EgammaPostRecoTools_940

### cms-data package(s) for Electron IDs
cd "${CMSSW_BASE}"/external/"${SCRAM_ARCH}"
git clone -b CMSSW_9_4_0_pre3_TnP https://github.com/lsoffi/RecoEgamma-PhotonIdentification.git data/RecoEgamma/PhotonIdentification/data
cd data/RecoEgamma/PhotonIdentification/data
git checkout CMSSW_9_4_0_pre3_TnP
cd "${CMSSW_BASE}"/external/"${SCRAM_ARCH}"
git clone -b CMSSW_9_4_0_pre3_TnP https://github.com/lsoffi/RecoEgamma-ElectronIdentification.git data/RecoEgamma/ElectronIdentification/data
cd data/RecoEgamma/ElectronIdentification/data
git checkout CMSSW_9_4_0_pre3_TnP
cd "${CMSSW_BASE}"/src

### cms-data package(s) for ECAL scale and resolution corrections
#cd "${CMSSW_BASE}"/external/"${SCRAM_ARCH}"
#git clone -b ReReco17NovScaleAndSmearing https://github.com/Sam-Harper/EgammaAnalysis-ElectronTools.git data/EgammaAnalysis/ElectronTools/data
#cd "${CMSSW_BASE}"/src

### MET
#git cms-merge-topic cms-met:METRecipe94x
git cms-merge-topic cms-met:METRecipe94xEEnoisePatch
#git clone https://github.com/cms-met/MetTools.git

### ttHFGenFilter
#git cms-merge-topic riga:ttHFGenFilter_tagging

### Common Classifier
#git clone https://gitlab.cern.ch/ttH/CommonClassifier.git TTH/CommonClassifier
#source TTH/CommonClassifier/setup/install_mem.sh
#source TTH/CommonClassifier/setup/install_recoLikelihood.sh
#cd $CMSSW_BASE/src
#git cms-addpkg PhysicsTools/JetMCAlgos

# FIXME use a symlink in newer CMSSW
#ln -s ${parent_path}/../../../analyzers
cp -rf ${parent_path}/../../../analyzers .
#cp analyzers/Extras/PhysicsTools_JetMCAlgos_python/GenTtbarCategorizer_cfi.py \
#    PhysicsTools/JetMCAlgos/python/
#cp analyzers/Extras/PhysicsTools_JetMCAlgos_plugins/GenTtbarCategorizer.cc \
#    PhysicsTools/JetMCAlgos/plugins/

# FIXME already in the repo
# FIXME use a symlink in newer CMSSW
# ln -s ${parent_path}/../../../external/MiniAOD
cp -rf ${parent_path}/../../../external/MiniAOD .
