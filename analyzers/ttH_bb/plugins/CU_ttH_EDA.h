#ifndef CU_ttH_EDA_h
#define CU_ttH_EDA_h

/// Core libraries
#include <cmath>  // arctan
#include <cstdio> // printf, fprintf
#include <fstream>
#include <map>
#include <memory>
#include <stdexcept> // standard exceptions
#include <vector>

/// CMSSW user include files
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/VertexCompositePtrCandidate.h"
#include "DataFormats/Candidate/interface/VertexCompositePtrCandidateFwd.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerEventWithRefs.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/L1Trigger/interface/L1EmParticle.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticle.h"
#include "DataFormats/L1Trigger/interface/L1HFRings.h"
#include "DataFormats/L1Trigger/interface/L1HFRingsFwd.h"
#include "DataFormats/L1Trigger/interface/L1JetParticle.h"
#include "DataFormats/L1Trigger/interface/L1MuonParticle.h"
#include "DataFormats/L1Trigger/interface/L1ParticleMap.h"
#include "DataFormats/L1Trigger/interface/L1ParticleMapFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/GenericParticle.h"
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackExtra.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/TrackReco/interface/HitPattern.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"

#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/strbitset.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "JetMETCorrections/Modules/interface/JetResolution.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"

#include "RecoBTag/BTagTools/interface/SignedTransverseImpactParameter.h"
#include "TrackingTools/IPTools/interface/IPTools.h"

#include "MiniAOD/MiniAODHelper/interface/LeptonSFHelper.h"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"

#include "LHAPDF/LHAPDF.h"

/// ROOT includes
#include "TH1.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TTree.h"

/// Higgs and top tagger
#include "MiniAOD/MiniAODHelper/interface/HiggsTagger.h"
#include "MiniAOD/MiniAODHelper/interface/TopTagger.h"

/// structs for holding multiple edm::Handle and EDGetTokenT
#include "CU_ttH_EDA_Handles.h"

#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "analyzers/ttH_bb/interface/CU_ttH_EDA_Ntuple.h"
#include "analyzers/ttH_bb/interface/CU_ttH_EDA_event_vars.h"

#include "analyzers/ttH_bb/interface/RoccoR.h"

#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondTools/BTau/interface/BTagCalibrationReader.h"

/// Configuration reader
#include "yaml-cpp/yaml.h"

/// TMVA
#include "TMVA/Reader.h"

/*
 *
 * Analyzer class
 *
 */

class CU_ttH_EDA : public edm::EDAnalyzer
{
  public:
    explicit CU_ttH_EDA(const edm::ParameterSet &);
    ~CU_ttH_EDA();

    static void fillDescriptions(edm::ConfigurationDescriptions &);

  private:
    /*
     * Function/method section
     */

    /// Standard EDAnalyzer functions
    void analyze(const edm::Event &, const edm::EventSetup &) override;

    void beginJob() override;
    void endJob() override;

    void beginRun(const edm::Run &, const edm::EventSetup &) override;
    void endRun(const edm::Run &, const edm::EventSetup &) override;

    /// One-time-run functions
    void Set_up_tokens(const edm::ParameterSet &);
    void Set_up_b_weights(); // at CU_ttH_EDA()
	void Set_up_qcd_sf();
    void Set_up_Tree();

    // Set_up_name_vectors()

    /// Per-event functions
    void Update_common_vars(const edm::Event &, CU_ttH_EDA_event_vars &);

    /// Object checks. Returns 1 in case of an error
    // int Check_beam_spot(edm::Handle<reco::BeamSpot>);
    int Check_triggers(edm::Handle<pat::TriggerObjectStandAloneCollection>,
                       edm::Handle<edm::TriggerResults>,
                       const edm::Event &,
                       CU_ttH_EDA_event_vars &); // adjusts event variables
    int Check_filters(edm::Handle<edm::TriggerResults>,
                      CU_ttH_EDA_event_vars &);
    int Check_vertices_set_MAODhelper(edm::Handle<reco::VertexCollection>);
    int Check_PV(
        const edm::Handle<reco::VertexCollection> &); // check primary vertex

    // Lepton operations
    inline bool is_ele_tightid(const pat::Electron&, const double &);
    inline std::vector<pat::Electron>
    GetSelectedElectrons(const edm::View<pat::Electron> &,
                         CU_ttH_EDA_event_vars &, const float,
                         const edm::Handle<edm::ValueMap<bool>> &,
                         const double &, const float = 2.4);
    inline void GetElectronSeeds(std::vector<unsigned int> &,
                                 const std::vector<pat::Electron> &);
    inline std::vector<pat::Muon>
    GetSelectedMuons(std::vector<TLorentzVector> &, std::vector<unsigned int> &,
                     const std::vector<pat::Muon> &, const float,
                     const coneSize::coneSize = coneSize::R04,
                     const corrType::corrType = corrType::deltaBeta,
                     const float = 2.5, const float = 0.25);
    void Lepton_Tag(const std::vector<reco::GenParticle> &,
                    CU_ttH_EDA_event_vars &);
    inline void Find_link(const reco::GenParticle &);
    inline int Find_id(const int &);
    inline void Fill_lepton_ancestor_info(CU_ttH_EDA_event_vars &);

    // Jet operations
	inline std::vector<pat::Jet>
	GetSelectedJets(const std::vector<pat::Jet>&, const float &, const float &, const std::string &);
    inline std::vector<pat::Jet>
    GetSelectedJets_PUID(const std::vector<pat::Jet> &, const int &);
    inline void GetJetSeeds(std::vector<unsigned int> &, std::vector<int> &,
                            std::vector<double> &,
                            const std::vector<pat::Jet> &);
    void
    SetFactorizedJetCorrector(const sysType::sysType iSysType = sysType::NA);
    void SetpT_ResFile();
    /*
    inline std::vector<pat::Jet>
    GetCorrectedJets(const std::vector<pat::Jet> &,
                     const edm::Handle<reco::GenJetCollection> &,
                     const double &, const CU_ttH_EDA_event_vars &,
                     const JME::JetResolution &,
                     const sysType::sysType iSysType = sysType::NA,
                     const bool &doJES = 1, const bool &doJER = 1,
                     const float &corrFactor = 1, const float &uncFactor = 1);
    */
    inline std::vector<pat::Jet>
    GetCorrectedJets(const std::vector<pat::Jet> &,
                     const edm::Handle<reco::GenJetCollection> &,
                     const double &, const CU_ttH_EDA_event_vars &,
                     const sysType::sysType iSysType = sysType::NA,
                     const bool &doJES = 1, const bool &doJER = 1,
                     const float &corrFactor = 1, const float &uncFactor = 1);
    inline double GetJERfactor(const int, const double, const double,
                               const double);
    inline double GetJECSF(pat::Jet, const std::string, const double &,
                           const CU_ttH_EDA_event_vars &);
    inline double GetJERSF(pat::Jet, const std::string, const double &,
                           const edm::Handle<reco::GenJetCollection> &,
                           const CU_ttH_EDA_event_vars &,
                           const float &corrFactor = 1,
                           const float &uncFactor = 1);
    inline double GetHT(const std::vector<pat::Jet> &);

    // Object Selection functions
    void Select_Leptons(CU_ttH_EDA_event_vars &, const edm_Handles &, const double &);
    /*
    void Select_Jets(CU_ttH_EDA_event_vars &, const edm::Event &,
                     const edm::EventSetup &, const edm_Handles &,
                     const double &, const JME::JetResolution &);
    */
    void Select_Jets(CU_ttH_EDA_event_vars &, const edm::Event &,
                     const edm::EventSetup &, const edm_Handles &,
                     const double &);
    void Init_Mets(CU_ttH_EDA_event_vars &, const edm_Handles &);

    // Initialization functions
    void Init_flags(CU_ttH_EDA_event_vars &);
    void Init_PU_weight();
    void Init_PDF_weight();
    void Init_weights(CU_ttH_EDA_event_vars &);
    void Init_SFs(CU_ttH_EDA_event_vars &);
    void Init_bjetness_var(CU_ttH_EDA_event_vars &);

    // General event Selection functions
    void Check_Event_Selection(CU_ttH_EDA_event_vars &);

    // Weights and SFs
    void Set_up_weights();

    void FillCSVHistos(TFile *fileHF, TFile *fileLF);
    double GetCSVWeight(std::vector<double> jetPts, std::vector<double> jetEtas,
                        std::vector<double> jetCSVs,
                        std::vector<int> jetFlavors, int iSys, double &csvWgtHF,
                        double &csvWgtLF, double &csvWgtCF);
    inline void Getbweight(CU_ttH_EDA_event_vars &);
	inline void Getbweight_csv(CU_ttH_EDA_event_vars &);
	inline void GetQCDSF(CU_ttH_EDA_event_vars &);
    void GetPUweight(edm::Handle<std::vector<PileupSummaryInfo>>,
                              CU_ttH_EDA_event_vars &);
	void GetPSweights(CU_ttH_EDA_event_vars &, const edm_Handles &);
    inline void GetPDFweight(CU_ttH_EDA_event_vars &,
                             const edm::Handle<GenEventInfoProduct> &);
    inline double GetQ2weight(const edm::Handle<GenEventInfoProduct> &,
                              const edm::Handle<LHEEventProduct> &,
                              const string &);
    inline void GetjetSF(CU_ttH_EDA_event_vars &, const double &,
                         const edm_Handles &);
    inline void GetLeptonSF(CU_ttH_EDA_event_vars &);

	/*
    inline void Set_bjetness_input(CU_ttH_EDA_event_vars &,
                                   const edm::Handle<reco::VertexCollection> &);
    inline vector<reco::TransientTrack>
    Get_ttrks(vector<reco::Track>, const TransientTrackBuilder &);
    inline bool Is_goodtrk(reco::Track, const reco::Vertex &);
    inline bool Is_loosePOG_jetmuon(const pat::PackedCandidate &,
                                    edm::Handle<edm::View<pat::Muon>>);
    inline bool Is_softLep_jetelectron(const pat::PackedCandidate &,
                                       edm::Handle<edm::View<pat::Electron>>,
                                       const reco::Vertex &);
    inline void Get_bjetness_trkinfos(vector<pat::Jet>, const reco::Vertex &,
                                      vector<reco::Track> &, double &, double &,
                                      edm::Handle<edm::View<pat::Electron>>,
                                      edm::Handle<edm::View<pat::Muon>>,
                                      double &, double &,
                                      vector<tuple<double, double, double>> &);
    inline void Get_avip3d(vector<reco::Track>, const TransientTrackBuilder &,
                           reco::Vertex,
                           vector<tuple<double, double, double>> &, double &,
                           double &, double &);
    inline void Get_avip1d(vector<reco::Track>, const TransientTrackBuilder &,
                           reco::Vertex,
                           vector<tuple<double, double, double>> &, double &);
    inline void Get_bjetness_vars(vector<pat::Jet>, const reco::Vertex &,
                                  const TransientTrackBuilder &,
                                  edm::Handle<edm::View<pat::Electron>>,
                                  edm::Handle<edm::View<pat::Muon>>, double &,
                                  double &, double &, double &, double &,
                                  double &);
	*/
    /// Other functions
    inline void Fill_Gen_info(const std::vector<reco::GenParticle> &,
                              const std::vector<reco::GenJet> &,
                              CU_ttH_EDA_event_vars &);
    void Fill_Gen_b_info(const std::vector<reco::GenParticle> &,
                                CU_ttH_EDA_event_vars &);
    void Fill_Gen_nu_info(const std::vector<reco::GenParticle> &,
                                 CU_ttH_EDA_event_vars &);
    void Fill_ntuple_common(CU_ttH_EDA_event_vars &);
    void Fill_common_histos(CU_ttH_EDA_event_vars &);
    void Fill_addn_quant(CU_ttH_EDA_event_vars &, const edm::Event &,
                         const edm::EventSetup &, const double &,
                         const edm_Handles &);

    template <typename T1, typename T2>
    std::vector<T1> removeOverlapdR(const std::vector<T1> &v1,
                                    const std::vector<T2> &v2,
                                    double dR = 0.02);

    /*
     * Variable section
     */

    /// debug flags
    bool verbose_;
    bool dumpHLT_;

    edm_Tokens token; // common tokens for all events

    /// Triggers, paths: configs filled/updated via run
    HLTConfigProvider hlt_config;
    HLTConfigProvider filter_config;

    /// Triggers, paths.
    // Used for trigger statistics, filled via run (trigger_stats = true)
    std::string hltTag;
    std::string filterTag;

    // filters
    std::vector<std::string> MET_filter_names;

    /// Output file is opened/closed through CMS py config
    edm::Service<TFileService> fs_;

    /// Common sample parameters
    unsigned long event_count;     // running event counter
    unsigned long selection_count; // counting event selections
    int gen_SL_count;
    int gen_DL_count;
    int gen_FH_count;
    int gen_SL_hf_count;
    int gen_SL_nonhf_count;
    int gen_DL_hf_count;
    int gen_DL_nonhf_count;
    int gen_FH_hf_count;
    int gen_FH_nonhf_count;
    int gen_tot_count;
    int gen_tot_hf_count;
    int gen_tot_nonhf_count;

    /// Cuts
    double min_ele_pT;
    double min_mu_pT;
    double min_jet_pT;
    double max_ele_eta;
    double max_mu_eta;
    double max_jet_eta;
    double min_ele_tight_sl_pT;
    double min_ele_tight_di_pT;
    double min_mu_tight_sl_pT;
    double min_mu_tight_di_pT;
    double min_jet_tight_pT;
    double max_ele_tight_sl_eta;
    double max_mu_tight_sl_eta;
    double btag_csv_cut_M;

    // for JEC and JEC_SF calc
    FactorizedJetCorrector *_jetCorrector_MC;
    FactorizedJetCorrector *_jetCorrector_B;
	FactorizedJetCorrector *_jetCorrector_C;
	FactorizedJetCorrector *_jetCorrector_D;
	FactorizedJetCorrector *_jetCorrector_E;
	FactorizedJetCorrector *_jetCorrector_F;
    JetCorrectionUncertainty *_jetCorrectorUnc;
    std::vector<JetCorrectionUncertainty *> _jetCorrectorUnc_sources;
    std::vector<std::string> jet_jesSF_names;
    // const JetCorrector* corrector;

    // for JER
    std::vector<double> JER_etaMin;
    std::vector<double> JER_etaMax;
    std::vector<double> JER_rhoMin;
    std::vector<double> JER_rhoMax;
    std::vector<double> JER_PtMin;
    std::vector<double> JER_PtMax;
    std::vector<double> JER_Par0;
    std::vector<double> JER_Par1;
    std::vector<double> JER_Par2;
    std::vector<double> JER_Par3;

    // 4 momentum

    double E;
    double p;
    double pz;
    double py;
    double px;

    // primary vertex
    reco::Vertex prim_vertex;

    // JER
    JME::JetResolution resolution;
    JME::JetResolutionScaleFactor resolution_sf;

    // for b-weights
    std::string inputFileHF;
    std::string inputFileLF;
    TFile *f_CSVwgt_HF;
    TFile *f_CSVwgt_LF;
    TH1D *h_csv_wgt_hf[31][6];
    TH1D *c_csv_wgt_hf[31][6];
    TH1D *h_csv_wgt_lf[31][4][3];

	// for qcd SF
	std::string inputFile_qcd;
	TFile *f_FakeSF;
	TH2D *h_FakeSF_Mu;
	TH2D *h_FakeSF_El;

    // Selection helper
    MiniAODHelper miniAODhelper;
    LeptonSFHelper leptonSFhelper;

    // Object for Rochester Correction for muons
    RoccoR rc;

    // for PDF weight
    LHAPDF::PDFSet *pdfSet;
    std::vector<LHAPDF::PDF *> _systPDFs;

    bool isdata;
    int data_era;
    bool is_OLS;
    bool is_madg;
    bool save_gen_info;
    bool is_trigger_study;
    bool is_tight_skim;
    int MAODHelper_sample_nr; // past insample_, in-development var. for
                              // MAODHelper?
    std::string MAODHelper_era;

    // for PU weight

    int PU_x[100];
    double PU_y[100];
    double PU_y_up[100];
    double PU_y_down[100];

    // Generator Info
    int gen_id_list[100];

    TRandom3 rnd;

    // tree, histos and ntuple
    TTree *recoTree;
    TTree *genTree;
    TTree *commTree;

    /*
    TH1D *n_total;
    TH1D *gen_weight_dist;
    TH1D *gen_weight_pos;
    TH1D *gen_weight_neg;
    TH1D *ttHf_category;
    TH1D *ttHF_GenFilter;
    TH1D *SLtag;
    TH1D *DLtag;
    TH1D *FHtag;
    */
    CU_ttH_EDA_Reco_Ntuple reco_hbbNtuple;
    CU_ttH_EDA_Gen_Ntuple gen_hbbNtuple;
    CU_ttH_EDA_Comm_Ntuple comm_hbbNtuple;

	BTagCalibrationReader *btag_reader;
};

template <typename T1, typename T2>
std::vector<T1> CU_ttH_EDA::removeOverlapdR(const std::vector<T1> &v1,
                                            const std::vector<T2> &v2,
                                            double dR)
{
    std::vector<T1> res;
    for (const auto &o1 : v1) {
        bool keep = true;
        for (const auto &o2 : v2)
            if (miniAODhelper.DeltaR(&o1, &o2) < dR)
                keep = false;
        if (keep)
            res.push_back(o1);
    }
    return res;
}

#endif
