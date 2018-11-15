#ifndef CU_ttH_EDA_Setups_cc
#define CU_ttH_EDA_Setups_cc

/// Includes
#include "CU_ttH_EDA.h"
#include "analyzers/ttH_bb/interface/ntuple_helpers.h"

void CU_ttH_EDA::Set_up_weights()
{
    Init_PU_weight();
    Init_PDF_weight();
    Set_up_b_weights();
    Set_up_qcd_sf();
}

void CU_ttH_EDA::Init_weights(CU_ttH_EDA_event_vars &local)
{
    local.truenpv = -1;
    local.gen_weight = 1;
    local.PU_weight = 1;
    local.PU_weight_up = 1;
    local.PU_weight_down = 1;
    local.pdf_weight_up = 1;
    local.pdf_weight_down = 1;
    local.q2_weight_up = 1;
    local.q2_weight_down = 1;
	local.ps_weights.clear();

    local.b_weight_jesnominal_nominal.clear();
    local.b_weight_jesnominal_hfup.clear();
    local.b_weight_jesnominal_hfdown.clear();
    local.b_weight_jesnominal_hfstats1up.clear();
    local.b_weight_jesnominal_hfstats1down.clear();
    local.b_weight_jesnominal_hfstats2up.clear();
    local.b_weight_jesnominal_hfstats2down.clear();
    local.b_weight_jesnominal_lfup.clear();
    local.b_weight_jesnominal_lfdown.clear();
    local.b_weight_jesnominal_lfstats1up.clear();
    local.b_weight_jesnominal_lfstats1down.clear();
    local.b_weight_jesnominal_lfstats2up.clear();
    local.b_weight_jesnominal_lfstats2down.clear();
    local.b_weight_jesnominal_cferr1up.clear();
    local.b_weight_jesnominal_cferr1down.clear();
    local.b_weight_jesnominal_cferr2up.clear();
    local.b_weight_jesnominal_cferr2down.clear();
    local.b_weight_jesup_nominal.clear();
    local.b_weight_jesdown_nominal.clear();
	local.b_weight_jerup_nominal.clear();
	local.b_weight_jerdown_nominal.clear();
}

void CU_ttH_EDA::Init_SFs(CU_ttH_EDA_event_vars &local)
{
    local.jet_jecSF_nominal.clear();
    local.jet_jecSF_nominal_up.clear();
    local.jet_jecSF_nominal_down.clear();
    local.jet_jesSF_sourcename.clear();
    local.jet_jesSF_up.clear();
    local.jet_jesSF_down.clear();
    local.jet_jerSF_jesnominal_nominal.clear();
    local.jet_jerSF_jesnominal_up.clear();
    local.jet_jerSF_jesnominal_down.clear();
	local.jet_jerSF_jesup_nominal.clear();
	local.jet_jerSF_jesdown_nominal.clear();

    local.ele_sf_id_combined.clear();
    local.ele_sf_id_up_combined.clear();
    local.ele_sf_id_down_combined.clear();
    local.ele_sf_iso_combined.clear();
    local.ele_sf_iso_up_combined.clear();
    local.ele_sf_iso_down_combined.clear();
	local.ele_sf_id_rundep.clear();
	local.ele_sf_id_up_rundep.clear();
	local.ele_sf_id_down_rundep.clear();
	local.ele_sf_iso_rundep.clear();
	local.ele_sf_iso_up_rundep.clear();
	local.ele_sf_iso_down_rundep.clear();

    local.mu_sf_id_combined.clear();
    local.mu_sf_id_up_combined.clear();
    local.mu_sf_id_down_combined.clear();
    local.mu_sf_iso_combined.clear();
    local.mu_sf_iso_up_combined.clear();
    local.mu_sf_iso_down_combined.clear();
    local.mu_sf_tracking_combined.clear();
    local.mu_sf_tracking_up_combined.clear();
    local.mu_sf_tracking_down_combined.clear();
	local.mu_sf_id_rundep.clear();
	local.mu_sf_id_up_rundep.clear();
	local.mu_sf_id_down_rundep.clear();
	local.mu_sf_iso_rundep.clear();
	local.mu_sf_iso_up_rundep.clear();
	local.mu_sf_iso_down_rundep.clear();
	local.mu_sf_tracking_rundep.clear();
	local.mu_sf_tracking_up_rundep.clear();
	local.mu_sf_tracking_down_rundep.clear();
}

void CU_ttH_EDA::Init_bjetness_var(CU_ttH_EDA_event_vars &local)
{
    local.bjetnessFV_num_leps = -1;
    local.bjetnessFV_npvTrkOVcollTrk = -1;
    local.bjetnessFV_avip3d_val = -1;
    local.bjetnessFV_avip3d_sig = -1;
    local.bjetnessFV_avsip3d_sig = -1;
    local.bjetnessFV_avip1d_sig = -1;
}

void CU_ttH_EDA::Init_flags(CU_ttH_EDA_event_vars &local)
{
    local.event_selection = false;
}

void CU_ttH_EDA::Init_PU_weight()
{
    //ifstream fin;
    //fin.open("data/PU_weight/2017/PU_weights.txt");
    for (int i = 0; i < 98; ++i) {
        //fin >> PU_x[i] >> PU_y[i] >> PU_y_up[i] >> PU_y_down[i];
		PU_x[i] = PU_y[i] = PU_y_up[i] = PU_y_down[i] = 0;
    }
    //fin.close();
}

void CU_ttH_EDA::Init_PDF_weight()
{
    pdfSet = new LHAPDF::PDFSet("PDF4LHC15_nlo_30");
    _systPDFs = pdfSet->mkPDFs();
}

void CU_ttH_EDA::Set_up_tokens(const edm::ParameterSet &config)
{
    token.triggerResults = consumes<edm::TriggerResults>(
        edm::InputTag(std::string("TriggerResults"), std::string(""), hltTag));
    token.filterResults = consumes<edm::TriggerResults>(
        edm::InputTag(std::string("TriggerResults"), std::string(""), filterTag));
    token.triggerObjects = consumes<pat::TriggerObjectStandAloneCollection>(
        edm::InputTag(std::string("slimmedPatTrigger"), std::string(""), filterTag));
    //token.triggerObjects = consumes<pat::TriggerObjectStandAloneCollection>(
    //    edm::InputTag(std::string("selectedPatTrigger"), std::string(""), filterTag));
    token.vertices = consumes<reco::VertexCollection>(
        config.getParameter<edm::InputTag>("pv"));
    token.sec_vertices = consumes<reco::VertexCompositePtrCandidateCollection>(
        config.getParameter<edm::InputTag>("sv"));
    token.PU_info = consumes<std::vector<PileupSummaryInfo>>(
        config.getParameter<edm::InputTag>("pileup"));
    token.srcRho = consumes<double>(config.getParameter<edm::InputTag>("rho"));
    token.electrons = consumes<pat::ElectronCollection>(
        config.getParameter<edm::InputTag>("electrons"));
    token.muons = consumes<pat::MuonCollection>(
        config.getParameter<edm::InputTag>("muons"));
    token.jets = consumes<pat::JetCollection>(
        config.getParameter<edm::InputTag>("jets"));
    token.METs = consumes<pat::METCollection>(
        config.getParameter<edm::InputTag>("mets"));
    token.genjets = consumes<reco::GenJetCollection>(
        config.getParameter<edm::InputTag>("genjets"));
    token.genparticles = consumes<reco::GenParticleCollection>(
        config.getParameter<edm::InputTag>("genparticles"));
    token.PF_candidates = consumes<pat::PackedCandidateCollection>(
        config.getParameter<edm::InputTag>("pfcand"));
    token.BS = consumes<reco::BeamSpot>(
        config.getParameter<edm::InputTag>("beamspot"));
    token.eleTightIdMapToken_ = consumes<edm::ValueMap<bool>>(
        config.getParameter<edm::InputTag>("eleTightIdMap"));

    // token.mvaValuesMapToken_ = consumes<edm::ValueMap<float>>(
    //    config.getParameter<edm::InputTag>("mvaValues"));
    // token.mvaCategoriesMapToken_ = consumes<edm::ValueMap<int>>(
    //    config.getParameter<edm::InputTag>("mvaCategories"));
    // token.electrons_for_mva_token = mayConsume<edm::View<reco::GsfElectron>>(
    //    config.getParameter<edm::InputTag>("electrons"));

    token.electrons_for_mva_token = consumes<edm::View<pat::Electron>>(
        config.getParameter<edm::InputTag>("electrons"));
    token.muon_h_token = consumes<edm::View<pat::Muon>>(
        config.getParameter<edm::InputTag>("muons"));
    if (!isdata) {
        token.event_gen_info = consumes<GenEventInfoProduct>(
            edm::InputTag(std::string("generator")));
        token.genTtbarIdToken_ =
            consumes<int>(config.getParameter<edm::InputTag>("genTtbarId"));
        //if (!is_madg) {
        //    token.ttHFGenFilterToken_ = consumes<bool>(
        //        config.getParameter<edm::InputTag>("ttHFGenFilter"));
        //}
    }
    token.puInfoToken = consumes<std::vector<PileupSummaryInfo>>(
        config.getParameter<edm::InputTag>("pileupinfo"));
    if (!isdata && !is_OLS) {
        token.lheptoken = consumes<LHEEventProduct>(
            config.getParameter<edm::InputTag>("lhepprod"));
    }
}

void CU_ttH_EDA::Set_up_Tree()
{
    recoTree = fs_->make<TTree>("recoTree", "Reco tree");
    if (!isdata){
        genTree = fs_->make<TTree>("genTree", "Gen tree");
        commTree = fs_->make<TTree>("commTree", "Common tree");
    }

    /*
    n_total = fs_->make<TH1D>("n_total","n_total; n_total; Nr. of Events",3,-1,2);
    gen_weight_dist = fs_->make<TH1D>("gen_weight_dist","gen_weight_dist; gen_weight_dist; Nr. of Events",20000,-1000,1000);
    gen_weight_pos = fs_->make<TH1D>("gen_weight_pos","gen_weight_pos; gen_weight_pos; Nr. of Events",3,-1,2);
    gen_weight_neg = fs_->make<TH1D>("gen_weight_neg","gen_weight_neg; gen_weight_neg; Nr. of Events",3,-1,2);
    ttHf_category = fs_->make<TH1D>("ttHf_category","ttHf_category; ttHf_category; Nr. of Events",20,40,60);
    ttHF_GenFilter = fs_->make<TH1D>("ttHF_GenFilter","ttHF_GenFilter; ttHF_GenFilter; Nr. of Events",4,-2,2);
    SLtag = fs_->make<TH1D>("SLtag","SLtag; SLtag; Nr. of Events",3,-1,2);
    DLtag = fs_->make<TH1D>("DLtag","DLtag; DLtag; Nr. of Events",3,-1,2);
    FHtag = fs_->make<TH1D>("FHtag","FHtag; FHtag; Nr. of Events",3,-1,2);
    */

    ntuple::set_up_reco_branches(recoTree, data_era, save_gen_info, reco_hbbNtuple);
    if (!isdata){
        ntuple::set_up_gen_branches(genTree, data_era, save_gen_info, gen_hbbNtuple);
        ntuple::set_up_comm_branches(commTree, data_era, save_gen_info, comm_hbbNtuple);
    }
}

void CU_ttH_EDA::Set_up_b_weights()
{
	/*
    inputFileHF = "data/csv_weights/csv_rwt_fit_hf_v2_final_2017_6_7_all.root";
    inputFileLF = "data/csv_weights/csv_rwt_fit_lf_v2_final_2017_6_7_all.root";

    f_CSVwgt_HF = new TFile((inputFileHF).c_str());
    f_CSVwgt_LF = new TFile((inputFileLF).c_str());
    FillCSVHistos(f_CSVwgt_HF, f_CSVwgt_LF);
	*/

	BTagCalibration calib("deepcsv", "data/csv_weights/2017/DeepCSV_94XSF_V2_B_F.csv");
	btag_reader = new BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central");

	btag_reader->load(calib, BTagEntry::FLAV_B, "comb");
	btag_reader->load(calib, BTagEntry::FLAV_C, "comb");
	btag_reader->load(calib, BTagEntry::FLAV_UDSG, "comb");
}

void CU_ttH_EDA::Set_up_qcd_sf()
{
    inputFile_qcd = "data/QCD/2016/FakeScaleFactor_nominal.root";
    f_FakeSF = new TFile((inputFile_qcd).c_str());

    h_FakeSF_Mu = (TH2D*)f_FakeSF->Get("Mu_FakeSF");
    h_FakeSF_El = (TH2D*)f_FakeSF->Get("El_FakeSF");
}

#endif
