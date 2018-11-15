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
                 False,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "input dataset contains real data"
                 )
options.register("dataEra",
                 "",
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.string,
                 "the era of the data taking period, e.g. '2016B', empty for MC"
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
options.register("JESUncFile", 
		 "${CMSSW_VERSION}/src/analyzers/ttH_bb/data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017_V6_MC_Uncertainty_AK4PFchs.txt",
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
                 True, # set to True for all ttbar datasets
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.bool,
                 "creates the ttbar gen id and performs ttbar heavy flavour tagging"
                 )
options.parseArguments()

#
# collection placeholders
#
electronCollection = cms.InputTag("slimmedElectrons", "", "PAT")
muonCollection     = cms.InputTag("slimmedMuons", "", "PAT")
tauCollection      = cms.InputTag("slimmedTaus", "", "PAT")
photonCollection   = cms.InputTag("slimmedPhotons", "", "PAT")
METCollection      = cms.InputTag("slimmedMETs", "", "PAT")
jetCollection      = cms.InputTag("slimmedJets", "", "PAT")


process = cms.Process("MAOD")

#process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring())

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    #htobb
    '/store/mc/RunIIFall17MiniAOD/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/94X_mc2017_realistic_v10-v1/00000/CC0FCC49-B50A-E811-9694-02163E0144C8.root'
    #tt+jets
    #'/store/mc/RunIISummer17MiniAOD/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/MINIAODSIM/92X_upgrade2017_realistic_v10_ext1-v2/70000/FA9F26BB-3C9A-E711-8687-02163E0148A7.root'
    #tt+jets SL
    #'/store/mc/RunIIFall17MiniAOD/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/94X_mc2017_realistic_v10-v1/00000/0044D634-7FED-E711-B0EF-0242AC130002.root'
    #tt+jets DL
    #'/store/mc/RunIIFall17MiniAOD/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/94X_mc2017_realistic_v10-v2/60000/0284120D-22EF-E711-95D1-FA163EA2D2AB.root'
    #tt+jets FH
    #'/store/mc/RunIIFall17MiniAODv2/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/90000/FEC12209-9C42-E811-AA07-008CFAFC6284.root'
    )
)


# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load('Configuration.Geometry.GeometryRecoDB_cff')
#process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.MagneticField_38T_cff")

# Supplies PDG ID to real name resolution of MC particles
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.load( "Configuration.StandardSequences.FrontierConditions_GlobalTag_cff" )
process.GlobalTag.globaltag = '94X_mc2017_realistic_v14'

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.options.allowUnscheduled = cms.untracked.bool(True)

process.maxEvents = cms.untracked.PSet(
	input = cms.untracked.int32(-1)
)

seq = cms.Sequence()

process.ak4PFCHSL1Fastjet = cms.ESProducer(
    'L1FastjetCorrectionESProducer',
    level       = cms.string('L1FastJet'),
    algorithm   = cms.string('AK4PFchs'),
    srcRho      = cms.InputTag( 'fixedGridRhoFastjetAll' )
    )

process.ak4PFchsL2Relative = ak4CaloL2Relative.clone( algorithm = 'AK4PFchs' )
process.ak4PFchsL3Absolute = ak4CaloL3Absolute.clone( algorithm = 'AK4PFchs' )

process.ak4PFchsL1L2L3 = cms.ESProducer("JetCorrectionESChain",
    correctors = cms.vstring(
    'ak4PFCHSL1Fastjet', 
    'ak4PFchsL2Relative', 
    'ak4PFchsL3Absolute')
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
    #         from MetTools.MetPhiCorrections.tools.multPhiCorr_ReMiniAOD_Data_BCDEF_80X_sumPt_cfi \
    #            import multPhiCorr_Data_BCDEF_80X as metPhiCorrParams
    #    else: # "2016G", "2016Hv2", "2016Hv3"
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


#ttHf categorization

# Setting input particle collections to be used by the tools
genJetCollection = 'ak4GenJetsCustom'
#genJetCollection = 'slimmedGenJets'
genParticleCollection = 'prunedGenParticles'
genJetInputParticleCollection = 'packedGenParticles'
    
## producing a subset of particles to be used for jet clustering
from RecoJets.Configuration.GenJetParticles_cff import genParticlesForJetsNoNu
process.genParticlesForJetsNoNu = genParticlesForJetsNoNu.clone(
	src = cms.InputTag(genJetInputParticleCollection)
)
seq += process.genParticlesForJetsNoNu

    
# Producing own jets for testing purposes
from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets
process.ak4GenJetsCustom = ak4GenJets.clone(
        src = cms.InputTag("genParticlesForJetsNoNu"),
        #    src = genJetInputParticleCollection,
	jetAlgorithm = cms.string("AntiKt"),
        rParam = cms.double(0.4)
)
seq += process.ak4GenJetsCustom

    
# Ghost particle collection used for Hadron-Jet association 
# MUST use proper input particle collection
from PhysicsTools.JetMCAlgos.HadronAndPartonSelector_cfi import selectedHadronsAndPartons
process.selectedHadronsAndPartons = selectedHadronsAndPartons.clone(
        particles = cms.InputTag(genParticleCollection)
)
seq += process.selectedHadronsAndPartons

from PhysicsTools.JetMCAlgos.AK4PFJetsMCFlavourInfos_cfi import ak4JetFlavourInfos
process.genJetFlavourInfos = ak4JetFlavourInfos.clone(
	jets = cms.InputTag(genJetCollection)
)
seq += process.genJetFlavourInfos
    
# Input particle collection for matching to gen jets (partons + leptons) 
# MUST use use proper input jet collection: the jets to which hadrons should be associated
# rParam and jetAlgorithm MUST match those used for jets to be associated with hadrons
# More details on the tool: https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideBTagMCTools#New_jet_flavour_definition


    
from PhysicsTools.JetMCAlgos.GenHFHadronMatcher_cff import matchGenBHadron
# Plugin for analysing B hadrons
# MUST use the same particle collection as in selectedHadronsAndPartons
process.matchGenBHadron = matchGenBHadron.clone(
        genParticles = cms.InputTag(genParticleCollection),
        jetFlavourInfos = cms.InputTag("genJetFlavourInfos"),
	onlyJetClusteredHadrons = cms.bool(False)
)
seq += process.matchGenBHadron
    
# Plugin for analysing C hadrons
# MUST use the same particle collection as in selectedHadronsAndPartons
from PhysicsTools.JetMCAlgos.GenHFHadronMatcher_cff import matchGenCHadron
process.matchGenCHadron = matchGenCHadron.clone(
        genParticles = cms.InputTag(genParticleCollection),
        jetFlavourInfos = cms.InputTag("genJetFlavourInfos"),
	onlyJetClusteredHadrons = cms.bool(False)
)
seq += process.matchGenCHadron
    
## Producer for ttbar categorisation ID
# MUST use same genJetCollection as used for tools above
#from PhysicsTools.JetMCAlgos.GenTtbarCategorizer_cfi import categorizeGenTtbar
from TopQuarkAnalysis.TopTools.GenTtbarCategorizer_cfi import categorizeGenTtbar
process.categorizeGenTtbar = categorizeGenTtbar.clone(
		genJets = cms.InputTag(genJetCollection),
		genJetPtMin     = cms.double(20.),
		genJetAbsEtaMax = cms.double(2.4)
)

seq += process.categorizeGenTtbar


# the ttHFGen filter, used as a tagger
if options.isTtbar:
	from PhysicsTools.JetMCAlgos.ttHFGenFilter_cfi import ttHFGenFilter
	process.ttHFGenFilter = ttHFGenFilter.clone(
		genParticles = cms.InputTag(genParticleCollection),
		taggingMode  = cms.bool(True)
	)
	seq += process.ttHFGenFilter

# load the analysis:
process.load("analyzers.ttH_bb.ttHbb_MC_cfi")

# pat object collections
process.ttHbb.input_tags.electrons = electronCollection
process.ttHbb.input_tags.muons     = muonCollection
process.ttHbb.input_tags.mets      = METCollection
process.ttHbb.input_tags.jets     = jetCollection

#process.ttHbb.input_tags.ttHFGenFilter = cms.InputTag("ttHFGenFilter")


process.TFileService = cms.Service("TFileService",
	fileName = cms.string('ttHbbNtuple.root')
)

process.p = cms.Path(
    #process.electronMVAValueMapProducer
    #process.egmGsfElectronIDSequence
    #* process.genParticlesForJetsNoNu
    #* process.ak4GenJetsCustom
    #* process.selectedHadronsAndPartons
    #* process.genJetFlavourInfos
    #* process.matchGenBHadron
    #* process.matchGenCHadron
    #* process.categorizeGenTtbar
    #process.fullPatMetSequence
    seq + process.ttHbb
)
