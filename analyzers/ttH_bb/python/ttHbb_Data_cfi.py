# Configurations for ttH bb analysis
#
# Abhisek Datta
#

import FWCore.ParameterSet.Config as cms

import analyzers.ttH_bb.CU_ttH_read_yaml_Data as read_yaml

ttHbb =  cms.EDAnalyzer('CU_ttH_EDA',
        # Generic
        verbosity = cms.bool(read_yaml.verbosity),
        print_HLT_event_path = cms.bool(read_yaml.print_HLT_event_path),
        HLT_config_tag = cms.string(read_yaml.HLT_config_tag),
        filter_config_tag = cms.string(read_yaml.filter_config_tag),
        # Filters
        MET_filter_names = cms.vstring(read_yaml.filter_names),
        # Cuts
        min_ele_pT = cms.double(read_yaml.min_ele_pT),
        min_mu_pT = cms.double(read_yaml.min_mu_pT),
        min_jet_pT = cms.double(read_yaml.min_jet_pT),
        max_ele_eta = cms.double(read_yaml.max_ele_eta),
        max_mu_eta = cms.double(read_yaml.max_mu_eta),
        max_jet_eta = cms.double(read_yaml.max_jet_eta),
        min_ele_tight_sl_pT = cms.double(read_yaml.min_ele_tight_sl_pT),
        min_ele_tight_di_pT = cms.double(read_yaml.min_ele_tight_di_pT),
        min_mu_tight_sl_pT = cms.double(read_yaml.min_mu_tight_sl_pT),
        min_mu_tight_di_pT = cms.double(read_yaml.min_mu_tight_di_pT),
        min_jet_tight_pT = cms.double(read_yaml.min_jet_tight_pT),
        max_ele_tight_sl_eta = cms.double(read_yaml.max_ele_tight_sl_eta),
        max_mu_tight_sl_eta = cms.double(read_yaml.max_mu_tight_sl_eta),
        btag_csv_cut_M = cms.double(read_yaml.btag_csv_cut_M),
        # Additional
        using_real_data = cms.bool(read_yaml.using_real_data),
        data_era = cms.int32(read_yaml.data_era),
        is_OLS = cms.bool(read_yaml.is_OLS),
		is_madg = cms.bool(read_yaml.is_madg),
        save_gen_info = cms.bool(read_yaml.save_gen_info),
        is_trigger_study = cms.bool(read_yaml.is_trigger_study),
        is_tight_skim = cms.bool(read_yaml.is_tight_skim),
                          
        # InputTags
        input_tags = cms.PSet(
            pv = cms.InputTag("offlineSlimmedPrimaryVertices"),
            sv = cms.InputTag("slimmedSecondaryVertices"),
            pileup = cms.InputTag("addPileupInfo"),
            rho = cms.InputTag("fixedGridRhoFastjetAll"),
            electrons = cms.InputTag("slimmedElectrons"),
            muons = cms.InputTag("slimmedMuons"),
            jets = cms.InputTag("slimmedJets"),
            mets = cms.InputTag("slimmedMETs"),
            genjets = cms.InputTag("slimmedGenJets"),
            genparticles = cms.InputTag("prunedGenParticles"),
            pfcand = cms.InputTag("packedPFCandidates"),
            beamspot = cms.InputTag("offlineBeamSpot"),
			#mvaValues = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16GeneralPurposeV1Values"),
			#mvaCategories = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16GeneralPurposeV1Categories"),
            eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-tight"),
            genTtbarId = cms.InputTag("categorizeGenTtbar", "genTtbarId"),
            #ttHFGenFilter = cms.InputTag("ttHFGenFilter"),
            pileupinfo = cms.InputTag("slimmedAddPileupInfo"),
            lhepprod = cms.InputTag("externalLHEProducer")
        )
)
