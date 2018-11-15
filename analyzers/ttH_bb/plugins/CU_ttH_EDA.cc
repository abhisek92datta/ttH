#ifndef CU_ttH_EDA_cc
#define CU_ttH_EDA_cc

// -*- C++ -*-
//
// Package:    ttH-LeptonPlusJets/CU_ttH_EDA
// Class:      CU_ttH_EDA
//
/**\class CU_ttH_EDA CU_ttH_EDA.cc
 ttH-LeptonPlusJets/AnalysisCode/plugins/CU_ttH_EDA.cc

 Description: [one line class summary]

 Implementation:
         [Notes on implementation]
*/

/// Includes
#include "CU_ttH_EDA.h"
#include "analyzers/ttH_bb/interface/ntuple_helpers.h"

//
// constants, enums and typedefs
//

//
// static data member definitions
//

/*
 * Function/method section
 */

/// Constructor
CU_ttH_EDA::CU_ttH_EDA(const edm::ParameterSet &iConfig)
    : // Generic
      verbose_(iConfig.getParameter<bool>("verbosity")),
      dumpHLT_(iConfig.getParameter<bool>("print_HLT_event_path")),
      hltTag(iConfig.getParameter<string>("HLT_config_tag")),
      filterTag(iConfig.getParameter<string>("filter_config_tag")),
      // Filters
      MET_filter_names(
          iConfig.getParameter<std::vector<string>>("MET_filter_names")),
      // Cuts
      min_ele_pT(iConfig.getParameter<double>("min_ele_pT")),
      min_mu_pT(iConfig.getParameter<double>("min_mu_pT")),
      min_jet_pT(iConfig.getParameter<double>("min_jet_pT")),
      max_ele_eta(iConfig.getParameter<double>("max_ele_eta")),
      max_mu_eta(iConfig.getParameter<double>("max_mu_eta")),
      max_jet_eta(iConfig.getParameter<double>("max_jet_eta")),
      min_ele_tight_sl_pT(iConfig.getParameter<double>("min_ele_tight_sl_pT")),
      min_ele_tight_di_pT(iConfig.getParameter<double>("min_ele_tight_di_pT")),
      min_mu_tight_sl_pT(iConfig.getParameter<double>("min_mu_tight_sl_pT")),
      min_mu_tight_di_pT(iConfig.getParameter<double>("min_mu_tight_di_pT")),
      min_jet_tight_pT(iConfig.getParameter<double>("min_jet_tight_pT")),
      max_ele_tight_sl_eta(iConfig.getParameter<double>("max_ele_tight_sl_eta")),
      max_mu_tight_sl_eta(iConfig.getParameter<double>("max_mu_tight_sl_eta")),
      btag_csv_cut_M(iConfig.getParameter<double>("btag_csv_cut_M")),
      // Additional
      isdata(iConfig.getParameter<bool>("using_real_data")),
      data_era(iConfig.getParameter<int>("data_era")),
      is_OLS(iConfig.getParameter<bool>("is_OLS")),
      is_madg(iConfig.getParameter<bool>("is_madg")),
      save_gen_info(iConfig.getParameter<bool>("save_gen_info")),
      is_trigger_study(iConfig.getParameter<bool>("is_trigger_study")),
      is_tight_skim(iConfig.getParameter<bool>("is_tight_skim"))
{
    /*
     * now do whatever initialization is needed
     */

    /// just to setup MiniAODHelper (not used anywhere)
    MAODHelper_era = "2015_74x";
    MAODHelper_sample_nr = 2500;
	miniAODhelper.SetUp(MAODHelper_era, MAODHelper_sample_nr, analysisType::LJ, isdata);

    Set_up_tokens(iConfig.getParameter<edm::ParameterSet>("input_tags"));

    // For Jet Correction
    SetFactorizedJetCorrector();

    SetpT_ResFile();

    Set_up_Tree();
    Set_up_weights();

    // Rochester Correction
    rc.init(edm::FileInPath("analyzers/ttH_bb/data/Muon_rochester/2017/RoccoR2017v0.txt").fullPath());
}

/// Destructor
CU_ttH_EDA::~CU_ttH_EDA()
{
    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

    rnd.SetSeed(0);

	/*
    f_CSVwgt_HF->Close();
    f_CSVwgt_LF->Close();
    delete f_CSVwgt_HF;
    delete f_CSVwgt_LF;
	*/
	delete btag_reader;

    delete pdfSet;
}

/*
 *
 * Analyze block
 *
 */

/*
 * method called for each event
 */

void CU_ttH_EDA::analyze(const edm::Event &iEvent,
                         const edm::EventSetup &iSetup)
{
    using namespace edm;
    ++event_count;

    /// Declaring local struct for data readout and manipulations
    CU_ttH_EDA_event_vars local;
    Update_common_vars(iEvent, local);

    /// Create and set up edm:Handles in stack mem.
    edm_Handles handle;
    Set_up_handles(iEvent, iSetup, local, handle, token);

    /// Run checks on event containers via their handles
    Check_triggers(handle.triggerObjects, handle.triggerResults, iEvent, local);
    Check_filters(handle.filterResults, local);
    
    Check_vertices_set_MAODhelper(handle.vertices);

    local.n_prim_V = Check_PV(handle.vertices);
    prim_vertex = *(handle.vertices->begin());

    // Setting rho
    const auto rho = *handle.srcRho;
    miniAODhelper.SetRho(rho);

    // Lepton selection
    Select_Leptons(local, handle, rho);

    // Jet selection
    Select_Jets(local, iEvent, iSetup, handle, rho);

    // MET
    Init_Mets(local, handle);

    Init_flags(local);
    Init_weights(local);
    Init_SFs(local);
    Init_bjetness_var(local);

    // General event selection criteria
    Check_Event_Selection(local);

    if (local.event_selection) {
        ++selection_count;
    }

    // SL, DL and FH tagger
    if (!local.isdata)
        Lepton_Tag(*(handle.genparticles), local);
    else {
        local.SL_tag = -1;
        local.DL_tag = -1;
        local.FH_tag = -1;
    }

    // generator weight
    if (!isdata)
        local.gen_weight = handle.event_gen_info->weight();

    // PS weights
    if (!isdata)
	GetPSweights(local, handle);

    // ttHF categorization
    local.ttHf_cat = -1;
    if (!isdata && handle.genTtbarId.isValid())
        local.ttHf_cat = *handle.genTtbarId;

    // ttHFGenFilter
    local.ttHFGenFilter = false;
    if (!isdata && !is_madg)
        //local.ttHFGenFilter = *(handle.ttHFGenFilter);
	 	local.ttHFGenFilter = -1;

    // Generator Level b-quark and neutrino info
    if (!isdata) {
        Fill_Gen_b_info(*(handle.genparticles), local);
        Fill_Gen_nu_info(*(handle.genparticles), local);
    }

    // PU Weight
    if (!isdata)
        GetPUweight(handle.PupInfo, local);

    // Filling Common Info
    //Fill_common_histos(local);
    Fill_ntuple_common(local);

	gen_SL_count += local.SL_tag;
	gen_DL_count += local.DL_tag;
	gen_FH_count += local.FH_tag;
	if (local.ttHFGenFilter) {
		gen_SL_hf_count += local.SL_tag;
		gen_DL_hf_count += local.DL_tag;
		gen_FH_hf_count += local.FH_tag;
	} else {
		gen_SL_nonhf_count += local.SL_tag;
		gen_DL_nonhf_count += local.DL_tag;
		gen_FH_nonhf_count += local.FH_tag;
	}
	gen_tot_hf_count = gen_SL_hf_count + gen_DL_hf_count + gen_FH_hf_count;
	gen_tot_nonhf_count = gen_SL_nonhf_count + gen_DL_nonhf_count + gen_FH_nonhf_count;
	gen_tot_count = gen_SL_count + gen_DL_count + gen_FH_count;

    // Additional quantities, Fill ntuple
    if (local.event_selection) {
        Fill_addn_quant(local, iEvent, iSetup, rho, handle);
        ntuple::write_ntuple(local, miniAODhelper, reco_hbbNtuple, gen_hbbNtuple, comm_hbbNtuple, save_gen_info);

        // Fill Ntuple
        recoTree->Fill();
        if (!isdata)
            genTree->Fill();
    }
    if (!isdata)
        commTree->Fill();
}

/*
 * method called once each job just before starting event loop
 */

void CU_ttH_EDA::beginJob()
{
    TH1::SetDefaultSumw2(true);

    event_count = 0;
    selection_count = 0;
    gen_SL_count = 0;
    gen_DL_count = 0;
    gen_FH_count = 0;
    gen_tot_count = 0;
    gen_SL_hf_count = 0;
    gen_SL_nonhf_count = 0;
    gen_DL_hf_count = 0;
    gen_DL_nonhf_count = 0;
    gen_FH_hf_count = 0;
    gen_FH_nonhf_count = 0;
    gen_tot_hf_count = 0;
    gen_tot_nonhf_count = 0;
}

/*
 * method called once each job just after ending the event loop
 */

void CU_ttH_EDA::endJob() { return; }

/*
 * method called when starting to processes a run
 */
void CU_ttH_EDA::beginRun(const edm::Run &iRun, const edm::EventSetup &iSetup)
{
    /// Update HLTConfigProvider(s) for the new run
    bool hlt_config_changed = true; // init() updates this one
    if (!hlt_config.init(iRun, iSetup, hltTag, hlt_config_changed)) {
        std::cerr << "Warning, didn't find trigger process HLT,\t" << hltTag
                  << std::endl;
        return;
    }

    if (hlt_config_changed)
        std::cout << "New " << hltTag << " config has been loaded.\n";

    bool filter_config_changed = true; // init() updates this one
    if (!filter_config.init(iRun, iSetup, filterTag, filter_config_changed)) {
        std::cerr << "Warning, didn't find filter process HLT,\t" << filterTag
                  << std::endl;
        return;
    }

    if (filter_config_changed)
        std::cout << "New " << filterTag << " config has been loaded.\n";
}

/*
 * method called when ending the processing of a run
 */
void CU_ttH_EDA::endRun(const edm::Run &, const edm::EventSetup &)
{
    std::cout
        << "***************************************************************"
        << std::endl;
    std::cout
        << "***************************************************************"
        << std::endl;
    std::cout << "Number of events selected = " << selection_count << std::endl;
    std::cout
        << "***************************************************************"
        << std::endl;
    std::cout
        << "***************************************************************"
        << std::endl;
    std::cout << "Total number of events = " << event_count << std::endl;
    std::cout
        << "***************************************************************"
        << std::endl;
    std::cout
        << "***************************************************************"
        << std::endl;
    std::cout << "Total number of SL tagged events = " << gen_SL_count
              << ", SL hf : " << gen_SL_hf_count
              << ", SL nonhf : " << gen_SL_nonhf_count << std::endl;
    std::cout << "Total number of DL tagged events = " << gen_DL_count
              << ", DL hf : " << gen_DL_hf_count
              << ", DL nonhf : " << gen_DL_nonhf_count << std::endl;
    std::cout << "Total number of FH tagged events = " << gen_FH_count
              << ", FH hf : " << gen_FH_hf_count
              << ", FH nonhf : " << gen_FH_nonhf_count << std::endl;
    std::cout << "Total number of tagged events = " << gen_tot_count
              << ", Total hf : " << gen_tot_hf_count
              << ", Total nonhf : " << gen_tot_nonhf_count << std::endl;
    std::cout
        << "***************************************************************"
        << std::endl;
}

// ------------ method fills 'descriptions' with the allowed parameters for the
// module  ------------
void CU_ttH_EDA::fillDescriptions(edm::ConfigurationDescriptions &descriptions)
{
    // The following says we do not know what parameters are allowed so do no
    // validation
    // Please change this to state exactly what you do use, even if it is no
    // parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
}

// define this as a CMSSW plugin
DEFINE_FWK_MODULE(CU_ttH_EDA);

#endif
