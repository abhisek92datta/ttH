import os
import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

from RecoJets.Configuration.RecoJets_cff import *
from RecoJets.Configuration.RecoPFJets_cff import *
from JetMETCorrections.Configuration.JetCorrectionProducersAllAlgos_cff import *
from JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff import *
from JetMETCorrections.Configuration.JetCorrectionServices_cff import *

#
# options
#
options = VarParsing("python")

# add custom options
options.register("realData",
                 True,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "input dataset contains real data"
                 )
options.register("dataEra",
                 "",
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.string,
                 "the era of the data taking period, e.g. '2017B', empty for MC"
                 )
options.register("vMiniAOD",
		 "v1",
  		 VarParsing.multiplicity.singleton,
		 VarParsing.varType.string,
		 "MiniAOD version - v1, v2re"
		 )
options.register("deterministicSeeds",
                 True,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "create collections with deterministic seeds"
                 )
options.register("electronSmearing",
                 "Run2017_17Nov2017_v1",
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.string,
                 "correction type for electron energy smearing"
                 )
options.register("recomputeMET",
                 True,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "recorrect MET using latest JES and e/g corrections"
                 )
options.register("JESUncFileB",
		 "${CMSSW_VERSION}/src/analyzers/ttH_bb/data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017B_V6_DATA_Uncertainty_AK4PFchs.txt",
		 VarParsing.multiplicity.singleton,
		 VarParsing.varType.string,
		 "JES uncertainty file"
		 )
options.register("JESUncFileC",
		 "${CMSSW_VERSION}/src/analyzers/ttH_bb/data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017C_V6_DATA_Uncertainty_AK4PFchs.txt",
		 VarParsing.multiplicity.singleton,
		 VarParsing.varType.string,
		 "JES uncertainty file"
		 )
options.register("JESUncFileD",
		 "${CMSSW_VERSION}/src/analyzers/ttH_bb/data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017D_V6_DATA_Uncertainty_AK4PFchs.txt",
		 VarParsing.multiplicity.singleton,
		 VarParsing.varType.string,
		 "JES uncertainty file"
		 )
options.register("JESUncFileE",
		 "${CMSSW_VERSION}/src/analyzers/ttH_bb/data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017E_V6_DATA_Uncertainty_AK4PFchs.txt",
		 VarParsing.multiplicity.singleton,
		 VarParsing.varType.string,
		 "JES uncertainty file"
		 )
options.register("JESUncFileF",
		 "${CMSSW_VERSION}/src/analyzers/ttH_bb/data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017F_V6_DATA_Uncertainty_AK4PFchs.txt",
		 VarParsing.multiplicity.singleton,
		 VarParsing.varType.string,
		 "JES uncertainty file"
		 )
options.register("updatePUJetId",
                 False,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "update the PUJetId values"
                 )
options.register("isTtbar",
                 False, # set to True for all ttbar datasets
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "creates the ttbar gen id and performs ttbar heavy flavour tagging"
                 )
options.parseArguments()

#
# collection placeholders
#
electronCollection = cms.InputTag("slimmedElectrons", "", "RECO")
muonCollection     = cms.InputTag("slimmedMuons", "", "RECO")
tauCollection      = cms.InputTag("slimmedTaus", "", "RECO")
photonCollection   = cms.InputTag("slimmedPhotons", "", "RECO")
METCollection      = cms.InputTag("slimmedMETs", "", "RECO")
jetCollection      = cms.InputTag("slimmedJets", "", "RECO")



process = cms.Process("MAOD")

#process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring())

process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
   ## Single Electron
   '/store/data/Run2017B/SingleElectron/MINIAOD/17Nov2017-v1/40000/00701B6B-E9DB-E711-B111-02163E019D6D.root',

   ## Single Muon
   #'',

   ## Double Electron
   #'',

   ## Electron Muon
   #'',

   ## Double Muon
   #'',
   )
)

import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'data/JSON/2017/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt').getVLuminosityBlockRange()

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load('Configuration.Geometry.GeometryRecoDB_cff')
#process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")

process.load( "Configuration.StandardSequences.FrontierConditions_GlobalTag_cff" )
process.GlobalTag.globaltag = '94X_dataRun2_v6'

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))
process.options.allowUnscheduled = cms.untracked.bool(True)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

seq = cms.Sequence()

process.ak4PFCHSL1Fastjet = cms.ESProducer(
    'L1FastjetCorrectionESProducer',
    level       = cms.string('L1FastJet'),
    algorithm   = cms.string('AK4PFchs'),
    srcRho      = cms.InputTag( 'fixedGridRhoFastjetAll' )
)

process.ak4PFchsL2Relative = ak4CaloL2Relative.clone( algorithm = 'AK4PFchs' )
process.ak4PFchsL3Absolute = ak4CaloL3Absolute.clone( algorithm = 'AK4PFchs' )
process.ak4PFchsResidual = ak4CaloResidual.clone( algorithm = 'AK4PFchs' )

process.ak4PFchsL1L2L3 = cms.ESProducer("JetCorrectionESChain",
    correctors = cms.vstring(
    'ak4PFCHSL1Fastjet', 
    'ak4PFchsL2Relative', 
    'ak4PFchsL3Absolute',
    'ak4PFchsResidual')
)


#
# deterministic seed producer
#

if options.deterministicSeeds:
    process.load("PhysicsTools.PatUtils.deterministicSeeds_cfi")
    process.deterministicSeeds.produceCollections = cms.bool(True)
    process.deterministicSeeds.produceValueMaps   = cms.bool(False)
    process.deterministicSeeds.electronCollection = electronCollection
    process.deterministicSeeds.muonCollection     = muonCollection
    process.deterministicSeeds.tauCollection      = tauCollection
    process.deterministicSeeds.photonCollection   = photonCollection
    process.deterministicSeeds.jetCollection      = jetCollection
    process.deterministicSeeds.METCollection      = METCollection
    seq += process.deterministicSeeds

    # overwrite output collections
    #electronCollection = cms.InputTag("deterministicSeeds", "electronsWithSeed", process.name_())
    muonCollection     = cms.InputTag("deterministicSeeds", "muonsWithSeed", process.name_())
    tauCollection      = cms.InputTag("deterministicSeeds", "tausWithSeed", process.name_())
    photonCollection   = cms.InputTag("deterministicSeeds", "photonsWithSeed", process.name_())
    jetCollection      = cms.InputTag("deterministicSeeds", "jetsWithSeed", process.name_())
    METCollection      = cms.InputTag("deterministicSeeds", "METsWithSeed", process.name_())


#
# EGamma routine to apply IDs + Scale & Smearing Corrections
#

if options.electronSmearing:
	process.load("Configuration.StandardSequences.Services_cff")
	process.load("Geometry.CaloEventSetup.CaloTowerConstituents_cfi")

	from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq

	setupEgammaPostRecoSeq(process, isMiniAOD=True,
		applyEnergyCorrections    = False,
		applyVIDOnCorrectedEgamma = False,
		era='2017-Nov17ReReco'
	)
	seq += process.egammaScaleSmearSeq
	seq += process.egammaPostRecoSeq
	electronCollection = cms.InputTag("slimmedElectrons", "", process.name_())

	from RecoEgamma.EgammaTools.calibratedEgammas_cff import calibratedPatElectrons as calibratedElectrons
	process.correctedElectrons = calibratedElectrons.clone(src = electronCollection)
	process.correctedElectrons.produceCalibratedObjs = cms.bool(True)
	process.correctedElectrons.semiDeterministic = cms.bool(True)
	seq += process.correctedElectrons
	electronCollection = cms.InputTag("correctedElectrons", "", process.name_())


#
# electron VIDs
#

#from PhysicsTools.SelectorUtils.tools.vid_id_tools import DataFormat, \
#    switchOnVIDElectronIdProducer, setupAllVIDIdsInModule, setupVIDElectronSelection

#eleVIDModules = ["RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V1_cff"]

#switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)

#for mod in eleVIDModules:
#    setupAllVIDIdsInModule(process, mod, setupVIDElectronSelection)

# update some VID modules to work with potentially changed electron collections
#process.egmGsfElectronIDs.physicsObjectSrc = electronCollection
#process.electronRegressionValueMapProducer.srcMiniAOD = electronCollection
#process.electronMVAValueMapProducer.srcMiniAOD = electronCollection


#
# MET corrections and uncertainties
#

#if options.dataEra in ("2016B"):
#	JESUncFile = JESUncFileB
#elif options.dataEra in ("2016C"):
#	JESUncFile = JESUncFileC
#elif options.dataEra in ("2016D"):
#	JESUncFile = JESUncFileD
#elif options.dataEra in ("2016E"):
#	JESUncFile = JESUncFileE
#elif options.dataEra in ("2016F"):
#	JESUncFile = JESUncFileF

if options.recomputeMET:
    # use the standard tool
    from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD
    # do not use a postfix here!
    runMetCorAndUncFromMiniAOD(process,
       isData           = options.realData,
       #jecUncFile       = os.path.basename(options.JESUncFile),
       electronColl     = electronCollection.value(),
       muonColl         = muonCollection.value(),
       tauColl          = tauCollection.value(),
       photonColl       = photonCollection.value(),
       jetCollUnskimmed = jetCollection.value(),
       recoMetFromPFCs  = True
    )
    # overwrite output collections
    METCollection = cms.InputTag("slimmedMETs", "", process.name_())

    # also add MET corrections due to e/g corrections, such as the slew rate fix in reMiniAOD
    if options.realData and options.vMiniAOD == "v2re":
        from PhysicsTools.PatUtils.tools.corMETFromMuonAndEG import corMETFromMuonAndEG
        corMETFromMuonAndEG(process,
           pfCandCollection      = "",
           electronCollection    = "slimmedElectronsBeforeGSFix",
           photonCollection      = "slimmedPhotonsBeforeGSFix",
           corElectronCollection = electronCollection.value(),
           corPhotonCollection   = photonCollection.value(),
           allMETEGCorrected     = True,
           muCorrection          = False,
           eGCorrection          = True,
           runOnMiniAOD          = True,
           postfix               = "MuEGClean"
        )
        process.slimmedMETsMuEGClean = getattr(process, METCollection.getModuleLabel()).clone(
           src             = cms.InputTag("patPFMetT1MuEGClean"),
           rawVariation    = cms.InputTag("patPFMetRawMuEGClean"),
           t1Uncertainties = cms.InputTag("patPFMetT1%sMuEGClean")
        )
        del process.slimmedMETsMuEGClean.caloMET

        # overwrite output collections
        METCollection = cms.InputTag("slimmedMETsMuEGClean", "", process.name_())


    # patch the phi correction parameter sets that are used in runMetCorAndUncFromMiniAOD,
    # we only need to overwrite patMultPhiCorrParams_T1Txy_25ns with the new one
    #if options.realData:
    #    if options.dataEra in ("2016B", "2016C", "2016D", "2016E", "2016F"):
    #        from MetTools.MetPhiCorrections.tools.multPhiCorr_ReMiniAOD_Data_BCDEF_80X_sumPt_cfi \
    #            import multPhiCorr_Data_BCDEF_80X as metPhiCorrParams
	#   else: # "2016G", "2016Hv2", "2016Hv3"
    #        from MetTools.MetPhiCorrections.tools.multPhiCorr_ReMiniAOD_Data_GH_80X_sumPt_cfi \
    #            import multPhiCorr_Data_GH_80X as metPhiCorrParams
    #else:
    #    from MetTools.MetPhiCorrections.tools.multPhiCorr_Summer16_MC_DY_80X_sumPt_cfi \
    #        import multPhiCorr_MC_DY_sumPT_80X as metPhiCorrParams
    # actual patch
    #getattr(process, "patPFMetTxyCorr").parameters = cms.VPSet(pset for pset in metPhiCorrParams)

    seq += process.fullPatMetSequence

#
# update PUJetId values
#
if options.updatePUJetId:
    process.load("RecoJets.JetProducers.PileupJetID_cfi")
    process.pileupJetIdUpdated = process.pileupJetId.clone(
      jets             = jetCollection,
      vertexes         = cms.InputTag("offlineSlimmedPrimaryVertices"),
      inputIsCorrected = cms.bool(True),
      applyJec         = cms.bool(True)
    )
    seq += process.pileupJetIdUpdated

    process.load("PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff")
    process.updatedPatJets.jetSource         = jetCollection
    process.updatedPatJets.addJetCorrFactors = cms.bool(False)
    process.updatedPatJets.userData.userFloats.src.append("pileupJetIdUpdated:fullDiscriminant")
    process.updatedPatJets.userData.userInts.src.append("pileupJetIdUpdated:fullId")
    seq += process.updatedJets

    # overwrite output collections
    jetCollection = cms.InputTag("updatedPatJets", "", process.name_())



# load the analysis:
process.load("analyzers.ttH_bb.ttHbb_Data_cfi")

# pat object collections
process.ttHbb.input_tags.electrons = electronCollection
process.ttHbb.input_tags.muons     = muonCollection
process.ttHbb.input_tags.mets      = METCollection
process.ttHbb.input_tags.jets     = jetCollection

process.TFileService = cms.Service("TFileService",
	fileName = cms.string('ttHbbNtuple.root')
)

process.p = cms.Path(
    #process.electronMVAValueMapProducer
    #process.egmGsfElectronIDSequence
    #process.fullPatMetSequence
    seq + process.ttHbb
)
