#ifndef CU_ttH_EDA_Misc_cc
#define CU_ttH_EDA_Misc_cc

/// Includes
#include "CU_ttH_EDA.h"
#include "analyzers/ttH_bb/interface/ntuple_helpers.h"

void CU_ttH_EDA::Update_common_vars(const edm::Event &iEvent,
                                    CU_ttH_EDA_event_vars &local)
{
    local.run_nr = (unsigned int)iEvent.id().run();
    local.event_nr = (unsigned int)iEvent.id().event();
    local.lumisection_nr = (unsigned int)iEvent.id().luminosityBlock();

    local.isdata = isdata;
    local.data_era = data_era;
    local.is_OLS = is_OLS;
    local.is_madg = is_madg;
    local.save_gen_info = save_gen_info;
}

/*
int CU_ttH_EDA::Check_beam_spot(edm::Handle<reco::BeamSpot> BS)
{
    if (!BS.isValid())
        return 1;

    if (verbose_)
        printf("\t BeamSpot: x = %.2f,\t y = %.2f,\t z = %.2f \n", BS->x0(),
               BS->y0(), BS->z0());

    return 0;
}
*/

int CU_ttH_EDA::Check_triggers(edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects,
                               edm::Handle<edm::TriggerResults> triggerResults,
                               const edm::Event &iEvent,
                               CU_ttH_EDA_event_vars &local)
{
    if (!triggerResults.isValid()) {
        std::cerr << "Trigger results not valid for tag " << hltTag
                  << std::endl;
        return 1;
    }

    local.pass_HLT_Ele27_WPTight_Gsf_ = -1;
    local.pass_HLT_Ele35_WPTight_Gsf_ = -1;
    local.pass_HLT_Ele38_WPTight_Gsf_ = -1;
    local.pass_HLT_Ele40_WPTight_Gsf_ = -1;
    local.pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned_ = -1;
    local.pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150_ = -1;
    local.pass_HLT_IsoMu27_ = -1;
    local.pass_HLT_IsoMu24_eta2p1_ = -1;
    local.pass_HLT_IsoMu24_ = -1;
    local.pass_HLT_IsoTkMu24_ = -1;
	local.pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_ = -1;
    local.pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ = -1;
    local.pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_ = -1;
    local.pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_ = -1;
    local.pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ = -1;
	local.pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_ = -1;
    local.pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_ = -1;
    local.pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_ = -1;
    local.pass_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_ = -1;
    local.pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_ = -1;
    local.pass_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_ = -1;
	local.pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_ = -1;
	local.pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_ = -1;
    local.pass_HLT_PFMET110_PFMHT110_IDTight_ = -1;
    local.pass_HLT_PFMET120_PFMHT120_IDTight_ = -1;
    local.pass_HLT_PFMET130_PFMHT130_IDTight_ = -1;
    local.pass_HLT_PFMET140_PFMHT140_IDTight_ = -1;
	local.pass_HLT_PFMETTypeOne120_PFMHT120_IDTight_ = -1;
	local.pass_HLT_PFHT500_PFMET100_PFMHT100_IDTight_ = -1;
	local.pass_HLT_PFHT700_PFMET85_PFMHT85_IDTight_ = -1;
	local.pass_HLT_PFHT800_PFMET75_PFMHT75_IDTight_ = -1;
	local.pass_HLT_CaloMET250_HBHECleaned_ = -1;
	local.pass_HLT_PFMET250_HBHECleaned_ = -1;
	local.pass_HLT_PFMET200_HBHE_BeamHaloCleaned_ = -1;
    local.pass_HLT_PFHT180_ = -1;
    local.pass_HLT_PFHT250_ = -1;
    local.pass_HLT_PFHT350_ = -1;
    local.pass_HLT_PFHT370_ = -1;
    local.pass_HLT_PFHT430_ = -1;
    local.pass_HLT_PFHT510_ = -1;
    local.pass_HLT_PFHT590_ = -1;
    local.pass_HLT_PFHT680_ = -1;
    local.pass_HLT_PFHT780_ = -1;
    local.pass_HLT_PFHT890_ = -1;
    local.pass_HLT_PFHT1050_ = -1;
    local.pass_HLT_PFJet40_ = -1;
    local.pass_HLT_PFJet60_ = -1;
    local.pass_HLT_PFJet80_ = -1;
    local.pass_HLT_PFJet140_ = -1;
    local.pass_HLT_PFJet200_ = -1;
    local.pass_HLT_PFJet260_ = -1;
    local.pass_HLT_PFJet320_ = -1;
    local.pass_HLT_PFJet400_ = -1;
    local.pass_HLT_PFJet450_ = -1;
    local.pass_HLT_PFJet500_ = -1;
    local.pass_HLT_PFJet550_ = -1;

    if( triggerResults.isValid() ){

        std::vector<std::string> triggerNames = hlt_config.triggerNames();

        for( unsigned int iPath=0; iPath<triggerNames.size(); iPath++ ){

            std::string pathName = triggerNames[iPath];
            unsigned int hltIndex = hlt_config.triggerIndex(pathName);

            if( hltIndex >= triggerResults->size() ) continue;

            int accept = triggerResults->accept(hltIndex);

            std::string pathNameNoVer = hlt_config.removeVersion(pathName);

            if( pathName.find("HLT_Ele27_WPTight_Gsf_v")!=std::string::npos )
                local.pass_HLT_Ele27_WPTight_Gsf_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_Ele35_WPTight_Gsf_v")!=std::string::npos )
                local.pass_HLT_Ele35_WPTight_Gsf_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_Ele38_WPTight_Gsf_v")!=std::string::npos )
                local.pass_HLT_Ele38_WPTight_Gsf_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_Ele40_WPTight_Gsf_v")!=std::string::npos )
                local.pass_HLT_Ele40_WPTight_Gsf_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned_v")!=std::string::npos )
                local.pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_Ele28_eta2p1_WPTight_Gsf_HT150_v")!=std::string::npos )
                local.pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_IsoMu27_v")!=std::string::npos )
                local.pass_HLT_IsoMu27_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_IsoMu24_eta2p1_v")!=std::string::npos )
                local.pass_HLT_IsoMu24_eta2p1_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_IsoMu24_v")!=std::string::npos )
                local.pass_HLT_IsoMu24_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_IsoTkMu24_v")!=std::string::npos )
                local.pass_HLT_IsoTkMu24_ = (accept) ? 1 : 0;

			if( pathName.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v")!=std::string::npos )
				local.pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v")!=std::string::npos )
                local.pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v")!=std::string::npos )
                local.pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v")!=std::string::npos )
                local.pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v")!=std::string::npos )
                local.pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ = (accept) ? 1 : 0;

			if( pathName.find("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v")!=std::string::npos )
				local.pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v")!=std::string::npos )
                local.pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v")!=std::string::npos )
                local.pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v")!=std::string::npos )
                local.pass_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v")!=std::string::npos )
                local.pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v")!=std::string::npos )
                local.pass_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_ = (accept) ? 1 : 0;

			if( pathName.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v")!=std::string::npos )
				local.pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_ = (accept) ? 1 : 0;

			if( pathName.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v")!=std::string::npos )
				local.pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFMET110_PFMHT110_IDTight_v")!=std::string::npos )
                local.pass_HLT_PFMET110_PFMHT110_IDTight_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFMET120_PFMHT120_IDTight_v")!=std::string::npos )
                local.pass_HLT_PFMET120_PFMHT120_IDTight_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFMET130_PFMHT130_IDTight_v")!=std::string::npos )
                local.pass_HLT_PFMET130_PFMHT130_IDTight_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFMET140_PFMHT140_IDTight_v")!=std::string::npos )
                local.pass_HLT_PFMET140_PFMHT140_IDTight_ = (accept) ? 1 : 0;

			if( pathName.find("HLT_PFMETTypeOne120_PFMHT120_IDTight_v")!=std::string::npos )
				local.pass_HLT_PFMETTypeOne120_PFMHT120_IDTight_ = (accept) ? 1 : 0;

			if( pathName.find("HLT_PFHT500_PFMET100_PFMHT100_IDTight_v")!=std::string::npos )
				local.pass_HLT_PFHT500_PFMET100_PFMHT100_IDTight_ = (accept) ? 1 : 0;

			if( pathName.find("HLT_PFHT700_PFMET85_PFMHT85_IDTight_v")!=std::string::npos )
				local.pass_HLT_PFHT700_PFMET85_PFMHT85_IDTight_ = (accept) ? 1 : 0;

			if( pathName.find("HLT_PFHT800_PFMET75_PFMHT75_IDTight_v")!=std::string::npos )
				local.pass_HLT_PFHT800_PFMET75_PFMHT75_IDTight_ = (accept) ? 1 : 0;

			if( pathName.find("HLT_CaloMET250_HBHECleaned_v")!=std::string::npos )
				local.pass_HLT_CaloMET250_HBHECleaned_ = (accept) ? 1 : 0;

			if( pathName.find("HLT_PFMET250_HBHECleaned_v")!=std::string::npos )
				local.pass_HLT_PFMET250_HBHECleaned_ = (accept) ? 1 : 0;

			if( pathName.find("HLT_PFMET200_HBHE_BeamHaloCleaned_v")!=std::string::npos )
				local.pass_HLT_PFMET200_HBHE_BeamHaloCleaned_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFHT180_v")!=std::string::npos )
                local.pass_HLT_PFHT180_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFHT250_v")!=std::string::npos )
                local.pass_HLT_PFHT250_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFHT350_v")!=std::string::npos )
                local.pass_HLT_PFHT350_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFHT370_v")!=std::string::npos )
                local.pass_HLT_PFHT370_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFHT430_v")!=std::string::npos )
                local.pass_HLT_PFHT430_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFHT510_v")!=std::string::npos )
                local.pass_HLT_PFHT510_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFHT590_v")!=std::string::npos )
                local.pass_HLT_PFHT590_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFHT680_v")!=std::string::npos )
                local.pass_HLT_PFHT680_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFHT780_v")!=std::string::npos )
                local.pass_HLT_PFHT780_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFHT890_v")!=std::string::npos )
                local.pass_HLT_PFHT890_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFHT1050_v")!=std::string::npos )
                local.pass_HLT_PFHT1050_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFJet40_v")!=std::string::npos )
                local.pass_HLT_PFJet40_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFJet60_v")!=std::string::npos )
                local.pass_HLT_PFJet60_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFJet80_v")!=std::string::npos )
                local.pass_HLT_PFJet80_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFJet140_v")!=std::string::npos )
                local.pass_HLT_PFJet140_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFJet200_v")!=std::string::npos )
                local.pass_HLT_PFJet200_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFJet260_v")!=std::string::npos )
                local.pass_HLT_PFJet260_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFJet320_v")!=std::string::npos )
                local.pass_HLT_PFJet320_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFJet400_v")!=std::string::npos )
                local.pass_HLT_PFJet400_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFJet450_v")!=std::string::npos )
                local.pass_HLT_PFJet450_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFJet500_v")!=std::string::npos )
                local.pass_HLT_PFJet500_ = (accept) ? 1 : 0;

            if( pathName.find("HLT_PFJet550_v")!=std::string::npos )
                local.pass_HLT_PFJet550_ = (accept) ? 1 : 0;

        }
    }

    local.pt_trigger_object_.clear();
    local.eta_trigger_object_.clear();
    local.phi_trigger_object_.clear();
    local.filter_trigger_object_.clear();

    std::vector<string> filter_list;
    filter_list.clear();
    filter_list.push_back("hltEle30erJetC34WPTightGsfTrackIsoFilter");
    filter_list.push_back("hltEle30PFJet35EleCleaned");
    filter_list.push_back("hltEle28erHTT100WPTightGsfTrackIsoFilter");
    filter_list.push_back("hltPFHTJet30");
    filter_list.push_back("hltPFHT150Jet30");
    filter_list.push_back("hltEle27WPTightGsfTrackIsoFilter");
    filter_list.push_back("hltEle35noerWPTightGsfTrackIsoFilter");
    filter_list.push_back("hltEle38noerWPTightGsfTrackIsoFilter");
    filter_list.push_back("hltEle40noerWPTightGsfTrackIsoFilter");
    filter_list.push_back("hltSinglePFJet40");
    filter_list.push_back("hltSinglePFJet60");
    filter_list.push_back("hltSinglePFJet80");
    filter_list.push_back("hltSinglePFJet140");
    filter_list.push_back("hltSinglePFJet200");
    filter_list.push_back("hltSinglePFJet260");
    filter_list.push_back("hltSinglePFJet320");
    filter_list.push_back("hltSinglePFJet400");
    filter_list.push_back("hltSinglePFJet450");
    filter_list.push_back("hltSinglePFJet500");
    filter_list.push_back("hltSinglePFJet550");

    if( triggerObjects.isValid() && triggerResults.isValid() ){

        const edm::TriggerNames &names = iEvent.triggerNames(*triggerResults);

        for (pat::TriggerObjectStandAlone obj : *triggerObjects) {

            obj.unpackPathNames(names);
            obj.unpackFilterLabels(iEvent, *triggerResults);

            std::vector<std::string> labels;
            labels.clear();

            for (unsigned h = 0; h < obj.filterLabels().size(); h++) {
                string filter_label = obj.filterLabels()[h];

                for(unsigned int u=0 ; u < filter_list.size(); u++){
                    if( filter_label.compare(filter_list[u]) == 0 ){
                        labels.push_back(filter_label);
                        break;
                    }
                }
            }

            if(labels.size() > 0){
                local.pt_trigger_object_.push_back(obj.pt());
                local.eta_trigger_object_.push_back(obj.eta());
                local.phi_trigger_object_.push_back(obj.phi());
                local.filter_trigger_object_.push_back(labels);
            }
        }
    }
    return 0;
}

int CU_ttH_EDA::Check_filters(edm::Handle<edm::TriggerResults> filterResults,
                              CU_ttH_EDA_event_vars &local)
{
    if (!filterResults.isValid()) {
        std::cerr << "Trigger results not valid for tag " << filterTag
                  << std::endl;
        return 1;
    }

    bool pass = 1;
    for (std::vector<std::string>::const_iterator filter =
             MET_filter_names.begin();
         filter != MET_filter_names.end(); ++filter) {

        unsigned int filterIndex;
        std::string pathName = *filter;
        filterIndex = filter_config.triggerIndex(pathName);
        if (filterIndex >= filterResults->size()) {
            pass = pass * 0;
            break;
        }
        if (filterResults->accept(filterIndex))
            pass = pass * 1;
        else {
            pass = pass * 0;
            break;
        }
    }

    local.MET_filters = pass;

    return 0;
}

int CU_ttH_EDA::Check_vertices_set_MAODhelper(
    edm::Handle<reco::VertexCollection> vertices)
{
    /// Primary vertex handling
    if (!vertices.isValid())
        return 1;

    reco::Vertex vertex;
    int n_PVs = 0;

    for (reco::VertexCollection::const_iterator vtx = vertices->begin();
         vtx != vertices->end(); ++vtx) {

        if (vtx->isFake() || vtx->ndof() < 4.0 || abs(vtx->z()) > 24.0 ||
            abs(vtx->position().Rho()) > 2.0)
            continue;

        if (n_PVs == 0)
            vertex = *vtx;

        ++n_PVs;
    }

    if (verbose_)
        printf("\t Event PV: x = %.3f,\t y = %.3f,\t z = %.3f \n", vertex.x(),
               vertex.y(), vertex.z());

    if (n_PVs > 0)
        miniAODhelper.SetVertex(
            vertex); // FIXME?: overload miniAODhelper::SetVertex(reco::Vertex&)
    else
        miniAODhelper.SetVertex(*(vertices->begin()));

    return 0;
}

int CU_ttH_EDA::Check_PV(const edm::Handle<reco::VertexCollection> &vertices)
{
    reco::VertexCollection::const_iterator vtx = vertices->begin();
    if (vtx->isFake() || vtx->ndof() < 4.0 || abs(vtx->z()) > 24.0 ||
        abs(vtx->position().Rho()) > 2.0)
        return 0;
    else
        return 1;
}

void CU_ttH_EDA::Select_Leptons(CU_ttH_EDA_event_vars &local,
                                const edm_Handles &handle, const double &rho)
{
    // Mu
    local.mu_selected = GetSelectedMuons(
        local.corr_mu, local.mu_seeds, *(handle.muons), min_mu_pT,
        coneSize::R04, corrType::deltaBeta, max_mu_eta, 0.25);

    local.n_mu_tight_sl = 0;
    local.n_mu_tight_di = 0;
    local.lepton_sign = 1;
    for(int i=0; i<(int)local.mu_selected.size(); i++){
        local.lepton_sign *= local.mu_selected[i].charge();
        if(local.corr_mu[i].Pt() > min_mu_tight_di_pT)
            local.n_mu_tight_di++;
        if(local.corr_mu[i].Pt() > min_mu_tight_sl_pT && fabs(local.mu_selected[i].eta()) < max_mu_tight_sl_eta)
            local.n_mu_tight_sl++;
    }

    // Ele

    // Using MVA
    /*
    local.e_with_id = miniAODhelper.GetElectronsWithMVAid(
        handle.electrons_for_mva, handle.mvaValues, handle.mvaCategories);
    */

    // Using Cut-Based ID
    /*
    local.e_selected = miniAODhelper.GetSelectedElectrons(
        *(handle.electrons), min_ele_pT, electronID::electron80XCutBasedM,
        max_ele_eta);
    */

    // Using VID
    local.e_selected =
        GetSelectedElectrons(*(handle.electrons_for_mva), local, min_ele_pT,
                             handle.tight_id_decisions, rho, max_ele_eta);

    local.n_e_tight_sl = 0;
    local.n_e_tight_di = 0;
    for(int i=0; i<(int)local.e_selected.size(); i++){
        local.lepton_sign *= local.e_selected[i].charge();
        if(local.e_selected[i].pt() > min_ele_tight_di_pT)
            local.n_e_tight_di++;
        if(local.e_selected[i].pt() > min_ele_tight_sl_pT && fabs(local.e_selected[i].eta()) < max_ele_tight_sl_eta)
            local.n_e_tight_sl++;
    }

    GetElectronSeeds(local.ele_seeds, local.e_selected);

    local.n_electrons = static_cast<int>(local.e_selected.size());
    local.n_muons = static_cast<int>(local.mu_selected.size());
}

inline bool CU_ttH_EDA::is_ele_tightid(const pat::Electron& iElectron, const double &rho) {

    double SCeta = (iElectron.superCluster().isAvailable()) ? iElectron.superCluster()->position().eta() : -99;
    double absSCeta = fabs(SCeta);
    double sc_energy = iElectron.superCluster()->energy();
    double relIso = miniAODhelper.GetElectronRelIso(iElectron, coneSize::R03, corrType::rhoEA,effAreaType::fall17);

    bool isEB = ( absSCeta <= 1.479 );

    double full5x5_sigmaIetaIeta = iElectron.full5x5_sigmaIetaIeta();
    double dEtaInSeed = iElectron.superCluster().isNonnull() && iElectron.superCluster()->seed().isNonnull() ? iElectron.deltaEtaSuperClusterTrackAtVtx() - iElectron.superCluster()->eta() + iElectron.superCluster()->seed()->eta() : std::numeric_limits<float>::max();
    double fabsdEtaInSeed=fabs(dEtaInSeed);
    double dPhiIn = fabs( iElectron.deltaPhiSuperClusterTrackAtVtx() );
    double hOverE = iElectron.hcalOverEcal();

    double ooEmooP = -999;
    if( iElectron.ecalEnergy() == 0 ) ooEmooP = 1e30;
    else if( !std::isfinite(iElectron.ecalEnergy()) ) ooEmooP = 1e30;
    else ooEmooP = fabs(1.0/iElectron.ecalEnergy() - iElectron.eSuperClusterOverP()/iElectron.ecalEnergy() );

    //double d0 = -999;
    //double dZ = -999;
    double expectedMissingInnerHits = 999;
    if( iElectron.gsfTrack().isAvailable() ){
        //d0 = fabs(iElectron.gsfTrack()->dxy(prim_vertex.position()));
        //dZ = fabs(iElectron.gsfTrack()->dz(prim_vertex.position()));
        expectedMissingInnerHits = iElectron.gsfTrack()->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS);
    }

    bool passConversionVeto = ( iElectron.passConversionVeto() );

    bool pass = false;
    if( isEB ){
        pass = ( full5x5_sigmaIetaIeta < 0.0104 &&
                fabsdEtaInSeed < 0.00353 &&
                dPhiIn < 0.0499 &&
                hOverE < ( 0.026 + (0.5/sc_energy)+ (0.201*rho/sc_energy) ) &&
                ooEmooP < 0.0278 &&
                //d0 < 0.05 &&
                //dZ < 0.1 &&
                expectedMissingInnerHits <= 1 &&
                passConversionVeto &&
                relIso < 0.0361
                );
    }
    else{
        pass = ( full5x5_sigmaIetaIeta < 0.0305 &&
                fabsdEtaInSeed < 0.00567 &&
                dPhiIn < 0.0165 &&
                hOverE < ( 0.026 + (0.5/sc_energy)+ (0.201*rho/sc_energy) ) &&
                ooEmooP < 0.0158 &&
                //d0 < 0.1 &&
                //dZ < 0.2 &&
                expectedMissingInnerHits <= 1 &&
                passConversionVeto &&
                relIso < 0.094
                );
    }

    if (pass == true)
        return 1;
    else
        return 0;
}

inline std::vector<pat::Electron> CU_ttH_EDA::GetSelectedElectrons(
    const edm::View<pat::Electron> &inputElectrons,
    CU_ttH_EDA_event_vars &local, const float iMinPt,
    const edm::Handle<edm::ValueMap<bool>> &tight_id_decisions, const double &rho,
    const float iMaxEta)
{

    std::vector<pat::Electron> selectedElectrons;

    for (size_t i = 0; i < inputElectrons.size(); ++i) {
        const auto el = inputElectrons.ptrAt(i);
		const pat::Electron iElectron = *el;

        bool passesID = false;
        //passesID = (*tight_id_decisions)[el];
		//passesID = (bool)iElectron.userInt("cutBasedElectronID-Fall17-94X-V1-tight");
        passesID = is_ele_tightid(iElectron, rho);

        double absSCeta = fabs((iElectron.superCluster().isAvailable())
                                   ? iElectron.superCluster()->position().eta()
                                   : -99);

        bool inCrack = false;
        if (iElectron.superCluster().isAvailable())
            inCrack = (absSCeta > 1.4442 && absSCeta < 1.5660);

        bool passesKinematics = false;
        passesKinematics = ((iElectron.pt() >= iMinPt) &&
                            (fabs(iElectron.eta()) <= iMaxEta) && !inCrack);

        bool passesIPcuts = false;
        double d0 = -999;
        double dZ = -999;
        if (iElectron.gsfTrack().isAvailable() && local.n_prim_V == 1) {
            d0 = fabs(iElectron.gsfTrack()->dxy(prim_vertex.position()));
            dZ = fabs(iElectron.gsfTrack()->dz(prim_vertex.position()));
        }

        if (absSCeta < 1.479) {
            if (d0 < 0.05 && dZ < 0.1)
                passesIPcuts = true;
        } else {
            if (d0 < 0.1 && dZ < 0.2)
                passesIPcuts = true;
        }

        if (passesKinematics == true && passesID == true &&
			passesIPcuts == true){
            selectedElectrons.push_back(*el);
			double corr_factor1 = iElectron.energy() / iElectron.userFloat("ecalTrkEnergyPreCorr");
			//double corr_factor2 = iElectron.userFloat("energyScaleValue") * iElectron.userFloat("energySigmaValue");
			double uncorr_pt = iElectron.pt() / corr_factor1;
			local.uncorr_ele_pt.push_back(uncorr_pt);
		}
    }
    return selectedElectrons;
}

inline void
CU_ttH_EDA::GetElectronSeeds(std::vector<unsigned int> &ele_seeds,
                             const std::vector<pat::Electron> &inputElectrons)
{

    for (std::vector<pat::Electron>::const_iterator el = inputElectrons.begin(),
                                                    ed = inputElectrons.end();
         el != ed; ++el) {

        const pat::Electron iElectron = *el;

        // get the seed
        //int seed = iElectron.userInt("deterministicSeed");
		int seed = 0;
        ele_seeds.push_back((unsigned int)seed);
    }
}

inline std::vector<pat::Muon> CU_ttH_EDA::GetSelectedMuons(
    std::vector<TLorentzVector> &corr_mu, std::vector<unsigned int> &mu_seeds,
    const std::vector<pat::Muon> &inputMuons, const float iMinPt,
    const coneSize::coneSize iconeSize, const corrType::corrType icorrType,
    const float iMaxEta, const float iMaxIso)
{

    std::vector<pat::Muon> muons = inputMuons;
    std::vector<pat::Muon> selectedMuons;

    for (std::vector<pat::Muon>::const_iterator mu = muons.begin(),
                                                ed = muons.end();
         mu != ed; ++mu) {

        const pat::Muon iMuon = *mu;

        bool passesKinematics = false;
        bool passesIso = false;
        bool passesID = false;

        // get the seed and update the random number generator
        int seed = iMuon.userInt("deterministicSeed");
        rnd.SetSeed((unsigned int)seed);

        int genId = -99;
        double gen_pt = 0.0;
        bool gen_mu_match = false;
        double muon_SF = 1;
        double mu_pT;
        double rel_iso;
        TLorentzVector TL_mu;
        int nl = 0;

        // Rochester Correction

		if (isdata)
			muon_SF = rc.kScaleDT(iMuon.charge(), iMuon.pt(), iMuon.eta(),iMuon.phi(), 0, 0);

        else {
            double u1 = rnd.Rndm();
            double u2 = rnd.Rndm();

            if ((iMuon.genLepton())) {
                genId = iMuon.genLepton()->pdgId();
                if (genId == iMuon.pdgId()) {
                    gen_pt = iMuon.genLepton()->pt();
                    gen_mu_match = true;
                }
            }

            if (iMuon.track().isAvailable())
                nl = iMuon.track()->hitPattern().trackerLayersWithMeasurement();

			if (gen_mu_match == true)
				muon_SF = rc.kScaleFromGenMC(iMuon.charge(), iMuon.pt(), iMuon.eta(), iMuon.phi(), nl, gen_pt, u1, 0, 0);

			else
				muon_SF = rc.kScaleAndSmearMC(iMuon.charge(), iMuon.pt(), iMuon.eta(), iMuon.phi(), nl, u1, u2, 0, 0);
			
        }

        mu_pT = iMuon.pt() * muon_SF;
        //rel_iso = (miniAODhelper.GetMuonRelIso(iMuon, iconeSize, icorrType)) * (iMuon.pt() / mu_pT);
        rel_iso = miniAODhelper.GetMuonRelIso(iMuon, iconeSize, icorrType);

        passesKinematics =
            ((mu_pT >= iMinPt) && (fabs(iMuon.eta()) <= iMaxEta));
        passesIso = (rel_iso < iMaxIso);
        passesID = miniAODhelper.passesMuonPOGIdTight(iMuon);

        if (passesKinematics == true && passesID == true && passesIso == true) {
            selectedMuons.push_back(iMuon);
            TL_mu.SetPtEtaPhiE(mu_pT, iMuon.eta(), iMuon.phi(),
                               (iMuon.energy() * muon_SF));
            corr_mu.push_back(TL_mu);
            mu_seeds.push_back((unsigned int)seed);
        }
    }

    return selectedMuons;
}

/*
void CU_ttH_EDA::Select_Jets(CU_ttH_EDA_event_vars &local,
                             const edm::Event &iEvent,
                             const edm::EventSetup &iSetup,
                             const edm_Handles &handle, const double &rho,
                             const JME::JetResolution &resolution)
*/

void CU_ttH_EDA::Select_Jets(CU_ttH_EDA_event_vars &local,
                             const edm::Event &iEvent,
                             const edm::EventSetup &iSetup,
                             const edm_Handles &handle, const double &rho)

{

    // ID Check
	local.jets_raw = GetSelectedJets(*(handle.jets), 0, 999, "tight");

    local.jets_raw_puid = GetSelectedJets_PUID(local.jets_raw, 4);

    // Uncorrected jets
    local.jets_uncorrected = miniAODhelper.GetUncorrectedJets(local.jets_raw_puid);

    // Jet Energy Correction

    bool doJER;
    if (isdata)
        doJER = 0;
    else
        doJER = 1;

    // using my jet correction function
    local.jets_nominal_corrected =
        // GetCorrectedJets(local.jets_uncorrected, handle.genjets, rho, local,
        // resolution,
        //                 sysType::NA, 1, doJER);
        GetCorrectedJets(local.jets_uncorrected, handle.genjets, rho, local,
                         sysType::NA, 1, doJER);

    // using MiniAODHelper's jet correction function
    // local.jets_corrected =
    // miniAODhelper.GetCorrectedJets(local.jets_uncorrected, iEvent, iSetup,
    // handle.genjets,r,
    // sysType::NA, 1, doJER);

    // Jet Selection (based on nominal correction)
    local.njets_tight = 0;
    local.nbtags_sl = 0;
    local.nbtags_di = 0;
    for (unsigned int j = 0; j < local.jets_nominal_corrected.size(); ++j) {
        if ((local.jets_nominal_corrected[j].pt() > min_jet_pT) &&
            (fabs(local.jets_nominal_corrected[j].eta()) < max_jet_eta)) {
            local.jets_selected_uncorrected.push_back(local.jets_uncorrected[j]);
			double csv_value = miniAODhelper.GetJetCSV(local.jets_nominal_corrected[j], "pfDeepCSVJetTags:probb") + miniAODhelper.GetJetCSV(local.jets_nominal_corrected[j], "pfDeepCSVJetTags:probbb");
            if (local.jets_nominal_corrected[j].pt() > min_jet_tight_pT){
                local.njets_tight++;
                if (csv_value > btag_csv_cut_M)
                    local.nbtags_sl++;
            }
            if (csv_value > btag_csv_cut_M)
                local.nbtags_di++;
        }
    }

    local.n_jets = static_cast<int>(local.jets_selected_uncorrected.size());

    GetJetSeeds(local.jet_seeds, local.jet_puid, local.jet_pudisc,
                local.jets_selected_uncorrected);

}

void CU_ttH_EDA::Init_Mets(CU_ttH_EDA_event_vars &local,
                           const edm_Handles &handle)
{

    local.pfMET = handle.METs->front();
    local.met_pt_uncorr = local.pfMET.pt();
    local.met_phi_uncorr = local.pfMET.phi();

    //local.met_pt_phi_corr = local.pfMET.corPt(pat::MET::Type1XY);
    //local.met_phi_phi_corr = local.pfMET.corPhi(pat::MET::Type1XY);
    local.met_pt_phi_corr = local.pfMET.shiftedPt(pat::MET::NoShift, pat::MET::Type1XY);
    local.met_phi_phi_corr = local.pfMET.shiftedPhi(pat::MET::NoShift, pat::MET::Type1XY);

    if(!isdata){
        local.met_pt_jer_up = local.pfMET.shiftedPt(pat::MET::METUncertainty::JetResUp, pat::MET::Type1XY);
        local.met_pt_jer_down = local.pfMET.shiftedPt(pat::MET::METUncertainty::JetResDown, pat::MET::Type1XY);
        local.met_phi_jer_up = local.pfMET.shiftedPhi(pat::MET::METUncertainty::JetResUp, pat::MET::Type1XY);
        local.met_phi_jer_down = local.pfMET.shiftedPhi(pat::MET::METUncertainty::JetResDown, pat::MET::Type1XY);
    }
    else{
        local.met_pt_jer_up = local.met_pt_phi_corr;
        local.met_pt_jer_down = local.met_pt_phi_corr;
        local.met_phi_jer_up = local.met_phi_phi_corr;
        local.met_phi_jer_down = local.met_phi_phi_corr;
    }
}

inline double CU_ttH_EDA::GetHT(const std::vector<pat::Jet> &inputJets)
{

    double ht = 0;
    for (std::vector<pat::Jet>::const_iterator jet = inputJets.begin(),
                                               ed = inputJets.end();
         jet != ed; ++jet) {
        const pat::Jet iJet = *jet;
        ht = ht + iJet.pt();
    }
    return ht;
}

inline std::vector<pat::Jet>
CU_ttH_EDA::GetSelectedJets(const std::vector<pat::Jet>&inputJets, const float &min_pt, const float &max_eta, const std::string &id)
{
	std::vector<pat::Jet> outputJets;
	for (std::vector<pat::Jet>::const_iterator jet = inputJets.begin(),
		 ed = inputJets.end();
		 jet != ed; ++jet) {

		const pat::Jet iJet = *jet;

		if (iJet.pt() < min_pt)
			continue;

		if (fabs(iJet.eta()) > max_eta)
			continue;

		bool id_pass = false;
		if (id =="tight"){
			if( fabs(iJet.eta())<=2.7 ){
				id_pass = (
						iJet.neutralHadronEnergyFraction() < 0.90 &&
						//iJet.chargedEmEnergyFraction() < 0.90 &&
						iJet.neutralEmEnergyFraction() < 0.90 &&
						iJet.numberOfDaughters() > 1
						);
				if( fabs(iJet.eta())<=2.4 ){
					id_pass = ( id_pass &&
							iJet.chargedHadronEnergyFraction() > 0.0 &&
							iJet.chargedMultiplicity() > 0
							);
				}
			}
			else if( fabs(iJet.eta())>2.7 && fabs(iJet.eta())<=3.0 ){
				id_pass = (
						iJet.neutralEmEnergyFraction() < 0.99 &&
						iJet.neutralEmEnergyFraction() > 0.02 &&
						iJet.neutralMultiplicity() > 2
						);

			}
			else if( fabs(iJet.eta())>3.0 ){
				id_pass = (
						iJet.neutralHadronEnergyFraction() > 0.02 &&
						iJet.neutralEmEnergyFraction() < 0.90 &&
						iJet.neutralMultiplicity() > 10
						);
			}
		}

		if (!id_pass)
			continue;

		outputJets.push_back(iJet);
	}

	return outputJets;
}

inline std::vector<pat::Jet>
CU_ttH_EDA::GetSelectedJets_PUID(const std::vector<pat::Jet> &inputJets,
                                 const int &id)
{

    std::vector<pat::Jet> outputJets;

    for (std::vector<pat::Jet>::const_iterator jet = inputJets.begin(),
                                               ed = inputJets.end();
         jet != ed; ++jet) {

        const pat::Jet iJet = *jet;
        bool passesID = false;

        //int seed = iJet.userInt("pileupJetIdUpdated:fullId");
        int seed = iJet.userInt("pileupJetId:fullId");

        if (seed >= id)
            passesID = true;

        if (passesID == true)
            outputJets.push_back(iJet);
    }

    return outputJets;
}

inline void CU_ttH_EDA::GetJetSeeds(std::vector<unsigned int> &jet_seeds,
                                    std::vector<int> &jet_puid,
                                    std::vector<double> &jet_pudisc,
                                    const std::vector<pat::Jet> &inputJets)
{

    for (std::vector<pat::Jet>::const_iterator jet = inputJets.begin(),
                                               ed = inputJets.end();
         jet != ed; ++jet) {

        const pat::Jet iJet = *jet;

        // get the seed
        int seed = iJet.userInt("deterministicSeed");
        jet_seeds.push_back((unsigned int)seed);

        //int id = iJet.userInt("pileupJetIdUpdated:fullId");
		int id = iJet.userInt("pileupJetId:fullId");
        jet_puid.push_back(id);
        //double disc = iJet.userFloat("pileupJetIdUpdated:fullDiscriminant");
		double disc = iJet.userFloat("pileupJetId:fullDiscriminant");
        jet_pudisc.push_back(disc);
    }
}

void CU_ttH_EDA::SetFactorizedJetCorrector(const sysType::sysType iSysType)
{

    std::vector<JetCorrectorParameters> corrParams_MC;
    std::vector<JetCorrectorParameters> corrParams_B;
    std::vector<JetCorrectorParameters> corrParams_C;
    std::vector<JetCorrectorParameters> corrParams_D;
    std::vector<JetCorrectorParameters> corrParams_E;
	std::vector<JetCorrectorParameters> corrParams_F;

    if (isdata) {

        JetCorrectorParameters *L3JetPar_B = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017B_V6_DATA_L3Absolute_AK4PFchs.txt");
        JetCorrectorParameters *L2JetPar_B = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017B_V6_DATA_L2Relative_AK4PFchs.txt");
        JetCorrectorParameters *L1JetPar_B = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017B_V6_DATA_L1FastJet_AK4PFchs.txt");
        JetCorrectorParameters *L2L3JetPar_B = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017B_V6_DATA_L2L3Residual_AK4PFchs.txt");

		JetCorrectorParameters *L3JetPar_C = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017C_V6_DATA_L3Absolute_AK4PFchs.txt");
		JetCorrectorParameters *L2JetPar_C = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017C_V6_DATA_L2Relative_AK4PFchs.txt");
		JetCorrectorParameters *L1JetPar_C = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017C_V6_DATA_L1FastJet_AK4PFchs.txt");
		JetCorrectorParameters *L2L3JetPar_C = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017C_V6_DATA_L2L3Residual_AK4PFchs.txt");

		JetCorrectorParameters *L3JetPar_D = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017D_V6_DATA_L3Absolute_AK4PFchs.txt");
		JetCorrectorParameters *L2JetPar_D = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017D_V6_DATA_L2Relative_AK4PFchs.txt");
		JetCorrectorParameters *L1JetPar_D = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017D_V6_DATA_L1FastJet_AK4PFchs.txt");
		JetCorrectorParameters *L2L3JetPar_D = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017D_V6_DATA_L2L3Residual_AK4PFchs.txt");

		JetCorrectorParameters *L3JetPar_E = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017E_V6_DATA_L3Absolute_AK4PFchs.txt");
		JetCorrectorParameters *L2JetPar_E = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017E_V6_DATA_L2Relative_AK4PFchs.txt");
		JetCorrectorParameters *L1JetPar_E = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017E_V6_DATA_L1FastJet_AK4PFchs.txt");
		JetCorrectorParameters *L2L3JetPar_E = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017E_V6_DATA_L2L3Residual_AK4PFchs.txt");

		JetCorrectorParameters *L3JetPar_F = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017F_V6_DATA_L3Absolute_AK4PFchs.txt");
		JetCorrectorParameters *L2JetPar_F = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017F_V6_DATA_L2Relative_AK4PFchs.txt");
		JetCorrectorParameters *L1JetPar_F = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017F_V6_DATA_L1FastJet_AK4PFchs.txt");
		JetCorrectorParameters *L2L3JetPar_F = new JetCorrectorParameters("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017F_V6_DATA_L2L3Residual_AK4PFchs.txt");

        corrParams_B.push_back(*L1JetPar_B);
        corrParams_B.push_back(*L2JetPar_B);
        corrParams_B.push_back(*L3JetPar_B);
        corrParams_B.push_back(*L2L3JetPar_B);
        _jetCorrector_B = new FactorizedJetCorrector(corrParams_B);
        corrParams_C.push_back(*L1JetPar_C);
        corrParams_C.push_back(*L2JetPar_C);
        corrParams_C.push_back(*L3JetPar_C);
        corrParams_C.push_back(*L2L3JetPar_C);
        _jetCorrector_C = new FactorizedJetCorrector(corrParams_C);
        corrParams_D.push_back(*L1JetPar_D);
        corrParams_D.push_back(*L2JetPar_D);
        corrParams_D.push_back(*L3JetPar_D);
        corrParams_D.push_back(*L2L3JetPar_D);
        _jetCorrector_D = new FactorizedJetCorrector(corrParams_D);
        corrParams_E.push_back(*L1JetPar_E);
        corrParams_E.push_back(*L2JetPar_E);
        corrParams_E.push_back(*L3JetPar_E);
        corrParams_E.push_back(*L2L3JetPar_E);
        _jetCorrector_E = new FactorizedJetCorrector(corrParams_E);
		corrParams_F.push_back(*L1JetPar_F);
		corrParams_F.push_back(*L2JetPar_F);
		corrParams_F.push_back(*L3JetPar_F);
		corrParams_F.push_back(*L2L3JetPar_F);
		_jetCorrector_F = new FactorizedJetCorrector(corrParams_F);

        std::string _JESUncFile =
            "data/JEC/2016/Spring16_25nsV6_DATA_Uncertainty_AK4PFchs.txt";
        _jetCorrectorUnc = new JetCorrectionUncertainty(_JESUncFile);

        delete L3JetPar_B;
        delete L2JetPar_B;
        delete L1JetPar_B;
        delete L2L3JetPar_B;
        delete L3JetPar_C;
        delete L2JetPar_C;
        delete L1JetPar_C;
        delete L2L3JetPar_C;
        delete L3JetPar_D;
        delete L2JetPar_D;
        delete L1JetPar_D;
        delete L2L3JetPar_D;
        delete L3JetPar_E;
        delete L2JetPar_E;
        delete L1JetPar_E;
        delete L2L3JetPar_E;
		delete L3JetPar_F;
		delete L2JetPar_F;
		delete L1JetPar_F;
		delete L2L3JetPar_F;
    }

    else {
        JetCorrectorParameters *L3JetPar = new JetCorrectorParameters(
            "data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017_V6_MC_L3Absolute_AK4PFchs.txt");
        JetCorrectorParameters *L2JetPar = new JetCorrectorParameters(
            "data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017_V6_MC_L2Relative_AK4PFchs.txt");
        JetCorrectorParameters *L1JetPar = new JetCorrectorParameters(
            "data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017_V6_MC_L1FastJet_AK4PFchs.txt");

        corrParams_MC.push_back(*L1JetPar);
        corrParams_MC.push_back(*L2JetPar);
        corrParams_MC.push_back(*L3JetPar);
        _jetCorrector_MC = new FactorizedJetCorrector(corrParams_MC);

        std::string _JESUncFile =
            "data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017_V6_MC_Uncertainty_AK4PFchs.txt";
        _jetCorrectorUnc = new JetCorrectionUncertainty(_JESUncFile);

        std::vector<std::string> _JESUncFile_sources;
        _JESUncFile_sources.clear();

        jet_jesSF_names.clear();
        jet_jesSF_names.push_back("AbsoluteStat"); // 0
        jet_jesSF_names.push_back("AbsoluteScale"); // 1
        jet_jesSF_names.push_back("AbsoluteMPFBias"); // 2
        jet_jesSF_names.push_back("Fragmentation"); // 3
        jet_jesSF_names.push_back("SinglePionECAL"); // 4
        jet_jesSF_names.push_back("SinglePionHCAL"); // 5
        jet_jesSF_names.push_back("FlavorQCD"); // 6
        jet_jesSF_names.push_back("TimePtEta"); // 7
        jet_jesSF_names.push_back("RelativeJEREC1"); // 8
        jet_jesSF_names.push_back("RelativeJEREC2"); // 9
        jet_jesSF_names.push_back("RelativeJERHF"); // 10
        jet_jesSF_names.push_back("RelativePtBB"); // 11
        jet_jesSF_names.push_back("RelativePtEC1"); // 12
        jet_jesSF_names.push_back("RelativePtEC2"); // 13
        jet_jesSF_names.push_back("RelativePtHF"); // 14
        jet_jesSF_names.push_back("RelativeBal"); // 15
        jet_jesSF_names.push_back("RelativeFSR"); // 16
        jet_jesSF_names.push_back("RelativeStatFSR"); // 17
        jet_jesSF_names.push_back("RelativeStatEC"); // 18
        jet_jesSF_names.push_back("RelativeStatHF"); // 19
        jet_jesSF_names.push_back("PileUpDataMC"); // 20
        jet_jesSF_names.push_back("PileUpPtRef"); // 21
        jet_jesSF_names.push_back("PileUpPtBB"); // 22
        jet_jesSF_names.push_back("PileUpPtEC1"); // 23
        jet_jesSF_names.push_back("PileUpPtEC2"); // 24
        jet_jesSF_names.push_back("PileUpPtHF"); // 25

        _jetCorrectorUnc_sources.clear();
        for(int i=0; i<26; i++){
            _JESUncFile_sources.push_back(("data/JEC/2017/Fall17_17Nov2017_V6/Fall17_17Nov2017_V6_MC_UncertaintySources_" + jet_jesSF_names[i] + "_AK4PFchs.txt").c_str());
            _jetCorrectorUnc_sources.push_back(new JetCorrectionUncertainty(_JESUncFile_sources[i]));
        }

        delete L3JetPar;
        delete L2JetPar;
        delete L1JetPar;
    }
}

void CU_ttH_EDA::SetpT_ResFile()
{

    resolution = JME::JetResolution(string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/JER/2017/Summer16_25nsV1_MC_PtResolution_AK4PFchs.txt");
    resolution_sf = JME::JetResolutionScaleFactor(string(getenv("CMSSW_BASE")) + "/src/analyzers/ttH_bb/data/JER/2017/Summer16_25nsV1_MC_SF_AK4PFchs.txt");

    /*
    std::string JER_file =  string(getenv("CMSSW_BASE")) +
    "/src/analyzers/ttH_bb/data/JER/Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt"
    ;
    std::ifstream infile( JER_file);
    if( ! infile ){
        std::cerr << "Error: cannot open file(" << JER_file << ")" << endl;
        exit(1);
        }

        double eta_min;
        double eta_max;
        double rho_min;
        double rho_max;
        double dummy;
        double pt_min;
        double pt_max;
        double par0;
        double par1;
        double par2;
        double par3;

        JER_etaMin.clear();
        JER_etaMax.clear();
        JER_rhoMin.clear();
        JER_rhoMax.clear();
        JER_PtMin.clear();
        JER_PtMax.clear();
        JER_Par0.clear();
        JER_Par1.clear();
        JER_Par2.clear();
        JER_Par3.clear();

        while
    (infile>>eta_min>>eta_max>>rho_min>>rho_max>>dummy>>pt_min>>pt_max>>par0>>par1>>par2>>par3)
    {
            JER_etaMin.push_back(eta_min);
            JER_etaMax.push_back(eta_max);
            JER_rhoMin.push_back(rho_min);
            JER_rhoMax.push_back(rho_max);
            JER_PtMin .push_back(pt_min);
            JER_PtMax .push_back(pt_max);
            JER_Par0  .push_back(par0);
            JER_Par1  .push_back(par1);
            JER_Par2  .push_back(par2);
            JER_Par3  .push_back(par3);
        }
        infile.close();
     */
}

inline double CU_ttH_EDA::GetJECSF(pat::Jet jet,
                                   const std::string unc_type,
                                   const double &rho,
                                   const CU_ttH_EDA_event_vars &local)
{
    double scale = 1;

    if (!isdata) { // MC
        _jetCorrector_MC->setJetPt(jet.pt());
        _jetCorrector_MC->setJetEta(jet.eta());
        _jetCorrector_MC->setJetA(jet.jetArea());
        _jetCorrector_MC->setRho(rho); //=fixedGridRhoFastjetAll
        scale = _jetCorrector_MC->getCorrection();
    } else { // DATA
        if (local.run_nr >= 297046 && local.run_nr <= 299329) {
            _jetCorrector_B->setJetPt(jet.pt());
            _jetCorrector_B->setJetEta(jet.eta());
            _jetCorrector_B->setJetA(jet.jetArea());
            _jetCorrector_B->setRho(rho); //=fixedGridRhoFastjetAll
            scale = _jetCorrector_B->getCorrection();
        } else if (local.run_nr >= 299368 && local.run_nr <= 302029) {
            _jetCorrector_C->setJetPt(jet.pt());
            _jetCorrector_C->setJetEta(jet.eta());
            _jetCorrector_C->setJetA(jet.jetArea());
            _jetCorrector_C->setRho(rho); //=fixedGridRhoFastjetAll
            scale = _jetCorrector_C->getCorrection();
        } else if (local.run_nr >= 302030 && local.run_nr <= 303434) {
            _jetCorrector_D->setJetPt(jet.pt());
            _jetCorrector_D->setJetEta(jet.eta());
            _jetCorrector_D->setJetA(jet.jetArea());
            _jetCorrector_D->setRho(rho); //=fixedGridRhoFastjetAll
            scale = _jetCorrector_D->getCorrection();
        } else if (local.run_nr >= 303824 && local.run_nr <= 304797) {
            _jetCorrector_E->setJetPt(jet.pt());
            _jetCorrector_E->setJetEta(jet.eta());
            _jetCorrector_E->setJetA(jet.jetArea());
            _jetCorrector_E->setRho(rho); //=fixedGridRhoFastjetAll
            scale = _jetCorrector_E->getCorrection();
        }
		else if (local.run_nr >= 305040 && local.run_nr <= 306462) {
			_jetCorrector_F->setJetPt(jet.pt());
			_jetCorrector_F->setJetEta(jet.eta());
			_jetCorrector_F->setJetA(jet.jetArea());
			_jetCorrector_F->setRho(rho); //=fixedGridRhoFastjetAll
			scale = _jetCorrector_F->getCorrection();
		}
    }

    jet.scaleEnergy(scale);

    if (!unc_type.compare("Nominal"))
        return scale;
    else if (!unc_type.compare("Nominal_up") || !unc_type.compare("Nominal_down")) {
        _jetCorrectorUnc->setJetPt(jet.pt());
        _jetCorrectorUnc->setJetEta(jet.eta());
        double unc = 1;
        double jes = 1;
        if (!unc_type.compare("Nominal_up")) {
            unc = _jetCorrectorUnc->getUncertainty(true);
            jes = 1 + unc;
        } else if (!unc_type.compare("Nominal_down")) {
            unc = _jetCorrectorUnc->getUncertainty(false);
            jes = 1 - unc;
        }
        jet.scaleEnergy(jes);
        return jes;
    }else{
        double unc = 1;
        double jes = 1;
        for(int i=0; i<26; i++){
            std::string jes_var_up = (jet_jesSF_names[i]+"_up").c_str();
            std::string jes_var_down = (jet_jesSF_names[i]+"_down").c_str();
            if(!unc_type.compare(jes_var_up) || !unc_type.compare(jes_var_down)){
                _jetCorrectorUnc_sources[i]->setJetPt(jet.pt());
                _jetCorrectorUnc_sources[i]->setJetEta(jet.eta());
                if (!unc_type.compare(jes_var_up)) {
                    unc = _jetCorrectorUnc_sources[i]->getUncertainty(true);
                    jes = 1 + unc;
                } else if (!unc_type.compare(jes_var_down)) {
                    unc = _jetCorrectorUnc_sources[i]->getUncertainty(false);
                    jes = 1 - unc;
                }
                break;
            }
        }
        jet.scaleEnergy(jes);
        return jes;
    }
}

inline double
CU_ttH_EDA::GetJERSF(pat::Jet jet, const std::string unc_type,
                     const double &rho,
                     const edm::Handle<reco::GenJetCollection> &genjets,
                     const CU_ttH_EDA_event_vars &local,
                     const float &corrFactor, const float &uncFactor)
{

    double min_energy = 1e-2;
    double jerSF = 1.;
    bool genjet_match = 0;
    double dpt_min = 99999;
    double dpt;
    double dR;
    double res = 0;
    double s = 0;
    double scale = 0;

    // from GT and text file (new)

    JME::JetParameters parameters_1;
    parameters_1.set(JME::Binning::JetPt, jet.pt());
    parameters_1.set({JME::Binning::JetEta, jet.eta()});
    parameters_1.set({JME::Binning::Rho, rho});
    res = resolution.getResolution(parameters_1);
    s = resolution_sf.getScaleFactor(parameters_1);

    // from text file (old)
    /*
    for( int unsigned i = 0 ; i < JER_etaMax.size() ; i ++){
        if(jet.eta() < JER_etaMax[i] && jet.eta() >= JER_etaMin[i] && rho <
    JER_rhoMax[i] && rho >= JER_rhoMin[i] ) {
            double jet_pt=jet.pt();
            if(jet_pt < JER_PtMin[i])
                jet_pt=JER_PtMin[i];
            if(jet_pt > JER_PtMax[i])
                jet_pt=JER_PtMax[i];
            res=sqrt( JER_Par0[i]*fabs(JER_Par0[i]) /
    (jet_pt*jet_pt)+JER_Par1[i]*JER_Par1[i]*pow(jet_pt,JER_Par3[i])+JER_Par2[i]*JER_Par2[i]);
        }
    }
    */

    reco::GenJet matched_genjet;

    for (reco::GenJetCollection::const_iterator iter = genjets->begin();
         iter != genjets->end(); ++iter) {
        dpt = fabs(jet.pt() - iter->pt());
        dR = miniAODhelper.DeltaR(&jet, iter);
        if (dR < (0.4 / 2)) {
            if (dpt < (3 * fabs(res) * jet.pt())) {
                genjet_match = 1;
                if (dpt <= dpt_min) {
                    matched_genjet = *(iter);
                    dpt_min = dpt;
                }
            }
        }
    }

    if (genjet_match == 1) {
        if (!unc_type.compare("Nominal_up")) {
            jerSF = GetJERfactor(uncFactor, fabs(jet.eta()),
                                 matched_genjet.pt(), jet.pt());
        } else if (!unc_type.compare("Nominal_down")) {
            jerSF = GetJERfactor(-uncFactor, fabs(jet.eta()),
                                 matched_genjet.pt(), jet.pt());
        } else {
            jerSF =
                GetJERfactor(0, fabs(jet.eta()), matched_genjet.pt(), jet.pt());
        }
    } else if (genjet_match == 0) {
        int seed = jet.userInt("deterministicSeed");
        rnd.SetSeed((unsigned int)seed);
        // double s = GetJERfactor(0, fabs(jet.eta()),0, jet.pt());
        double sig_gaus = res * sqrt(fmax(0.0, (s * s) - 1));
        jerSF = 1 + rnd.Gaus(0, sig_gaus);
    }

    // truncation
    jerSF = max(jerSF, min_energy / jet.energy());

    scale = jerSF * corrFactor;
    jet.scaleEnergy(scale);

    return scale;
}

/*
inline std::vector<pat::Jet> CU_ttH_EDA::GetCorrectedJets(
    const std::vector<pat::Jet> &inputJets,
    const edm::Handle<reco::GenJetCollection> &genjets, const double &rho, const
CU_ttH_EDA_event_vars &local,
    const JME::JetResolution &resolution, const sysType::sysType iSysType,
    const bool &doJES, const bool &doJER, const float &corrFactor,
    const float &uncFactor)
*/
inline std::vector<pat::Jet> CU_ttH_EDA::GetCorrectedJets(
    const std::vector<pat::Jet> &inputJets,
    const edm::Handle<reco::GenJetCollection> &genjets, const double &rho,
    const CU_ttH_EDA_event_vars &local, const sysType::sysType iSysType,
    const bool &doJES, const bool &doJER, const float &corrFactor,
    const float &uncFactor)
{

    std::vector<pat::Jet> outputJets;

    for (std::vector<pat::Jet>::const_iterator it = inputJets.begin(),
                                               ed = inputJets.end();
         it != ed; ++it) {

        pat::Jet jet = (*it);
        double scale = 1.;

        // JEC
        if (doJES == 1) {

            if (!isdata) { // MC
                _jetCorrector_MC->setJetPt(jet.pt());
                _jetCorrector_MC->setJetEta(jet.eta());
                _jetCorrector_MC->setJetA(jet.jetArea());
                _jetCorrector_MC->setRho(rho); //=fixedGridRhoFastjetAll
                scale = _jetCorrector_MC->getCorrection();
            } else { // DATA
				if (local.run_nr >= 297046 && local.run_nr <= 299329) {
					_jetCorrector_B->setJetPt(jet.pt());
					_jetCorrector_B->setJetEta(jet.eta());
					_jetCorrector_B->setJetA(jet.jetArea());
					_jetCorrector_B->setRho(rho); //=fixedGridRhoFastjetAll
					scale = _jetCorrector_B->getCorrection();
				} else if (local.run_nr >= 299368 && local.run_nr <= 302029) {
					_jetCorrector_C->setJetPt(jet.pt());
					_jetCorrector_C->setJetEta(jet.eta());
					_jetCorrector_C->setJetA(jet.jetArea());
					_jetCorrector_C->setRho(rho); //=fixedGridRhoFastjetAll
					scale = _jetCorrector_C->getCorrection();
				} else if (local.run_nr >= 302030 && local.run_nr <= 303434) {
					_jetCorrector_D->setJetPt(jet.pt());
					_jetCorrector_D->setJetEta(jet.eta());
					_jetCorrector_D->setJetA(jet.jetArea());
					_jetCorrector_D->setRho(rho); //=fixedGridRhoFastjetAll
					scale = _jetCorrector_D->getCorrection();
				} else if (local.run_nr >= 303824 && local.run_nr <= 304797) {
					_jetCorrector_E->setJetPt(jet.pt());
					_jetCorrector_E->setJetEta(jet.eta());
					_jetCorrector_E->setJetA(jet.jetArea());
					_jetCorrector_E->setRho(rho); //=fixedGridRhoFastjetAll
					scale = _jetCorrector_E->getCorrection();
				}
				else if (local.run_nr >= 305040 && local.run_nr <= 306462) {
					_jetCorrector_F->setJetPt(jet.pt());
					_jetCorrector_F->setJetEta(jet.eta());
					_jetCorrector_F->setJetA(jet.jetArea());
					_jetCorrector_F->setRho(rho); //=fixedGridRhoFastjetAll
					scale = _jetCorrector_F->getCorrection();
				}
            }

            jet.scaleEnergy(scale);

            if (iSysType == sysType::JESup || iSysType == sysType::JESdown) {
                _jetCorrectorUnc->setJetPt(jet.pt());
                _jetCorrectorUnc->setJetEta(
                    jet.eta()); // here you must use the CORRECTED jet pt
                double unc = 1;
                double jes = 1;
                if (iSysType == sysType::JESup) {
                    unc = _jetCorrectorUnc->getUncertainty(true);
                    jes = 1 + unc;
                } else if (iSysType == sysType::JESdown) {
                    unc = _jetCorrectorUnc->getUncertainty(false);
                    jes = 1 - unc;
                }

                jet.scaleEnergy(jes);
            }
        }
        // JER
        if (doJER == 1) {

            double min_energy = 1e-2;
            double jerSF = 1.;
            bool genjet_match = 0;
            double dpt_min = 99999;
            double dpt;
            double dR;
            double res = 0;
            double s = 0;

            // from text file (new) or from GT

            JME::JetParameters parameters_1;
            parameters_1.set(JME::Binning::JetPt, jet.pt());
            parameters_1.set({JME::Binning::JetEta, jet.eta()});
            parameters_1.set({JME::Binning::Rho, rho});
            res = resolution.getResolution(parameters_1);
            s = resolution_sf.getScaleFactor(parameters_1);

            // from text file (old)

            /*
            for( int unsigned i = 0 ; i < JER_etaMax.size() ; i ++){
                if(jet.eta() < JER_etaMax[i] && jet.eta() >= JER_etaMin[i] &&
            rho < JER_rhoMax[i] && rho >= JER_rhoMin[i] ) {
                    double jet_pt=jet.pt();
                    if(jet_pt < JER_PtMin[i])
                        jet_pt=JER_PtMin[i];
                    if(jet_pt > JER_PtMax[i])
                        jet_pt=JER_PtMax[i];
                    res=sqrt( JER_Par0[i]*fabs(JER_Par0[i]) /
            (jet_pt*jet_pt)+JER_Par1[i]*JER_Par1[i]*pow(jet_pt,JER_Par3[i])+JER_Par2[i]*JER_Par2[i]);
                }
            }
            */

            reco::GenJet matched_genjet;

            for (reco::GenJetCollection::const_iterator iter = genjets->begin();
                 iter != genjets->end(); ++iter) {
                dpt = fabs(jet.pt() - iter->pt());
                dR = miniAODhelper.DeltaR(&jet, iter);
                if (dR < (0.4 / 2)) {
                    if (dpt < (3 * fabs(res) * jet.pt())) {
                        genjet_match = 1;
                        if (dpt <= dpt_min) {
                            matched_genjet = *(iter);
                            dpt_min = dpt;
                        }
                    }
                }
            }

            if (genjet_match == 1) {
                if (iSysType == sysType::JERup) {
                    jerSF = GetJERfactor(uncFactor, fabs(jet.eta()),
                                         matched_genjet.pt(), jet.pt());
                } else if (iSysType == sysType::JERdown) {
                    jerSF = GetJERfactor(-uncFactor, fabs(jet.eta()),
                                         matched_genjet.pt(), jet.pt());
                } else {
                    jerSF = GetJERfactor(0, fabs(jet.eta()),
                                         matched_genjet.pt(), jet.pt());
                }
            } else if (genjet_match == 0) {
                int seed = jet.userInt("deterministicSeed");
                rnd.SetSeed((unsigned int)seed);
                // double s = GetJERfactor(0, fabs(jet.eta()),0, jet.pt());
                double sig_gaus = res * sqrt(fmax(0.0, (s * s) - 1));
                jerSF = 1 + rnd.Gaus(0, sig_gaus);

                /*
                std::cout<<jet.pt()<<"  ";
                std::cout<<jerSF<<"  ";
                std::cout<<1 + rnd.Gaus(0,sig_gaus)<<"     ";
                rnd.SetSeed((unsigned int)seed);
                std::cout<< 1 + rnd.Gaus(0,0.2)*0.2<<"  ";
                std::cout<< 1 + rnd.Gaus(0,0.2)*0.2<<"     ";
                rnd.SetSeed((unsigned int)seed);
                std::cout<<1 + (rnd.Gaus(0,res))*sqrt(fmax(0.0,(s*s)-1))<<"  ";
                std::cout<<1 + (rnd.Gaus(0,res))*sqrt(fmax(0.0,(s*s)-1))<<" ";
                */
            }

            // truncation
            jerSF = max(jerSF, min_energy / jet.energy());

            jet.scaleEnergy(jerSF * corrFactor);
            // std::cout<<jet.pt()<<"\n";
        }
        outputJets.push_back(jet);
    }

    return outputJets;
}

inline double CU_ttH_EDA::GetJERfactor(const int returnType,
                                       const double jetAbsETA,
                                       const double genjetPT,
                                       const double recojetPT)
{

    double factor = 1.;

    double scale_JER = 1., scale_JERup = 1., scale_JERdown = 1.;
    double extrauncertainty = 1.5;

    if (jetAbsETA < 0.522) {
        scale_JER = 1.1595;
        scale_JERup = 1.1595 + 0.0645 * extrauncertainty;
        scale_JERdown = 1.1595 - 0.0645 * extrauncertainty;
    } else if (jetAbsETA < 0.783) {
        scale_JER = 1.1948;
        scale_JERup = 1.1948 + 0.0652 * extrauncertainty;
        scale_JERdown = 1.1948 - 0.0652 * extrauncertainty;
    } else if (jetAbsETA < 1.131) {
        scale_JER = 1.1464;
        scale_JERup = 1.1464 + 0.0632 * extrauncertainty;
        scale_JERdown = 1.1464 - 0.0632 * extrauncertainty;
    } else if (jetAbsETA < 1.305) {
        scale_JER = 1.1609;
        scale_JERup = 1.1609 + 0.1025 * extrauncertainty;
        scale_JERdown = 1.1609 - 0.1025 * extrauncertainty;
    } else if (jetAbsETA < 1.740) {
        scale_JER = 1.1278;
        scale_JERup = 1.1278 + 0.0986 * extrauncertainty;
        scale_JERdown = 1.1278 - 0.0986 * extrauncertainty;
    } else if (jetAbsETA < 1.930) {
        scale_JER = 1.1000;
        scale_JERup = 1.1000 + 0.1079 * extrauncertainty;
        scale_JERdown = 1.1000 - 0.1079 * extrauncertainty;
    } else if (jetAbsETA < 2.043) {
        scale_JER = 1.1426;
        scale_JERup = 1.1426 + 0.1214 * extrauncertainty;
        scale_JERdown = 1.1426 - 0.1214 * extrauncertainty;
    } else if (jetAbsETA < 2.322) {
        scale_JER = 1.1512;
        scale_JERup = 1.1512 + 0.1140 * extrauncertainty;
        scale_JERdown = 1.1512 - 0.1140 * extrauncertainty;
    } else if (jetAbsETA < 2.5) {
        scale_JER = 1.2963;
        scale_JERup = 1.2963 + 0.2371 * extrauncertainty;
        scale_JERdown = 1.2963 - 0.2371 * extrauncertainty;
    } else if (jetAbsETA < 2.853) {
        scale_JER = 1.3418;
        scale_JERup = 1.3418 + 0.2091 * extrauncertainty;
        scale_JERdown = 1.3418 - 0.2091 * extrauncertainty;
    } else if (jetAbsETA < 2.964) {
        scale_JER = 1.7788;
        scale_JERup = 1.7788 + 0.2008 * extrauncertainty;
        scale_JERdown = 1.7788 - 0.2008 * extrauncertainty;
    } else if (jetAbsETA < 3.139) {
        scale_JER = 1.1869;
        scale_JERup = 1.1869 + 0.1243 * extrauncertainty;
        scale_JERdown = 1.1869 - 0.1243 * extrauncertainty;
    } else if (jetAbsETA < 5.191) {
        scale_JER = 1.1922;
		scale_JERup = 1.1922 + 0.1488 * extrauncertainty;
		scale_JERdown = 1.1922 - 0.1488 * extrauncertainty;
    }

    double jetPt_JER = recojetPT;
    double jetPt_JERup = recojetPT;
    double jetPt_JERdown = recojetPT;

    double diff_recojet_genjet = recojetPT - genjetPT;

    jetPt_JER = std::max(0., genjetPT + scale_JER * (diff_recojet_genjet));
    jetPt_JERup = std::max(0., genjetPT + scale_JERup * (diff_recojet_genjet));
    jetPt_JERdown =
        std::max(0., genjetPT + scale_JERdown * (diff_recojet_genjet));

    if (returnType == 1)
        factor = jetPt_JERup / recojetPT;
    else if (returnType == -1)
        factor = jetPt_JERdown / recojetPT;
    else
        factor = jetPt_JER / recojetPT;

    return factor;
}

void CU_ttH_EDA::Check_Event_Selection(CU_ttH_EDA_event_vars &local)
{
    if (!local.MET_filters)
        return;
    if (local.n_prim_V <= 0)
        return;

    int n_lep = local.n_electrons + local.n_muons;
    int n_lep_tight_sl = local.n_e_tight_sl + local.n_mu_tight_sl;
    int n_lep_tight_di = local.n_e_tight_di + local.n_mu_tight_di;
    bool is_sl = false;
    bool is_di = false;

    if (n_lep==0)   // at least one loose lepton
        return;
    if (n_lep_tight_sl==0 && n_lep_tight_di==0)       // at least one tight lepton
        return;

    // Skimming for only trigger studies
    if (is_trigger_study){
        local.event_selection = true;
        return;
    }

    // Tight Skimming
    if (is_tight_skim){
        if(n_lep == 1){                 // Candidate for a SL event
            if(n_lep_tight_sl < 1)
                return;
            if(local.njets_tight < 4 || local.nbtags_sl < 2)
                return;
            is_sl = true;
        }
        else if(n_lep == 2){            // Candidate for a DL event
            if(local.lepton_sign > 0)
                return;
            if(n_lep_tight_di < 1)
                return;
            if(local.njets_tight < 2)
                return;
            is_di = true;
        }
    }
    // Loose Skimming
    else{
        if(local.njets_tight < 2)
            return;
        is_sl = true;
        is_di = true;
    }

    if (!is_sl && !is_di)
        return;
    local.event_selection = true;
}

void CU_ttH_EDA::Fill_addn_quant(CU_ttH_EDA_event_vars &local,
                                 const edm::Event &iEvent,
                                 const edm::EventSetup &iSetup,
                                 const double &rho, const edm_Handles &handle)
{
	// to get JEC scale factors
    GetjetSF(local, rho, handle);

    // Lepton ancestor info
    Fill_lepton_ancestor_info(local);

    // to get Lepton ID, Iso and Trigger SFs
    GetLeptonSF(local);

    // to get b-weight
    //Getbweight(local);
	Getbweight_csv(local);

    if (local.isdata)
        return;

    // Generator Information
    Fill_Gen_info(*(handle.genparticles), *(handle.genjets), local);

    // PDF Weight
    GetPDFweight(local, handle.event_gen_info);

    // Q2 Weight
    if (!local.is_OLS) {
        local.q2_weight_up =
            GetQ2weight(handle.event_gen_info, handle.EvtHandle, "1005");
        local.q2_weight_down =
            GetQ2weight(handle.event_gen_info, handle.EvtHandle, "1009");
    }

	/*
    // b-jetness variables
    if (local.n_prim_V == 1) {
        Set_bjetness_input(local, handle.vertices);
        Get_bjetness_vars(
            local.jets_inp_bjetness, local.PV, *handle.ttrkbuilder,
            handle.electrons_for_mva, handle.muon_h, local.bjetnessFV_num_leps,
            local.bjetnessFV_npvTrkOVcollTrk, local.bjetnessFV_avip3d_val,
            local.bjetnessFV_avip3d_sig, local.bjetnessFV_avsip3d_sig,
            local.bjetnessFV_avip1d_sig);
    }
	*/
}

/*
void CU_ttH_EDA::Fill_common_histos(CU_ttH_EDA_event_vars &local)
{
    n_total->Fill(1.0);
    gen_weight_dist->Fill(local.gen_weight);
    if(local.gen_weight >= 0)
        gen_weight_pos->Fill(1.0,local.gen_weight);
    else
        gen_weight_neg->Fill(1.0,fabs(local.gen_weight));
    ttHf_category->Fill((local.ttHf_cat)%100);

    if (!isdata && !is_madg) {
        if (local.ttHFGenFilter == true)
            ttHF_GenFilter->Fill(1.0);
        else
            ttHF_GenFilter->Fill(0);
    } else
        ttHF_GenFilter->Fill(-1.0);

    SLtag->Fill(local.SL_tag);
    DLtag->Fill(local.DL_tag);
    FHtag->Fill(local.FH_tag);
}
*/

void CU_ttH_EDA::Fill_ntuple_common(CU_ttH_EDA_event_vars &local)
{

    ntuple::Initialize_reco(reco_hbbNtuple);
    ntuple::Initialize_gen(gen_hbbNtuple);
    ntuple::Initialize_comm(comm_hbbNtuple);

    // Event variables
    reco_hbbNtuple.nEvent = local.event_nr;
    reco_hbbNtuple.ls = local.lumisection_nr;
    reco_hbbNtuple.run = local.run_nr;
	reco_hbbNtuple.is_data = isdata;
    reco_hbbNtuple.data_era = data_era;

    comm_hbbNtuple.nEvent = local.event_nr;

    if(save_gen_info)
        reco_hbbNtuple.save_gen_info = 1;
    else
        reco_hbbNtuple.save_gen_info = 0;
    if(is_trigger_study)
        reco_hbbNtuple.is_trigger_study = 1;
    else
        reco_hbbNtuple.is_trigger_study = 0;
    if(is_tight_skim)
        reco_hbbNtuple.is_tight_skim = 1;
    else
        reco_hbbNtuple.is_tight_skim = 0;

    /*
    /// MET Filters
    if(local.MET_filters)
        reco_hbbNtuple.MET_filters = 1;
    else
        reco_hbbNtuple.MET_filters = 0;

    // Event Selection flag
    
    if (local.event_selection)
        reco_hbbNtuple.pass_event_selection = 1;
    else
        reco_hbbNtuple.pass_event_selection = 0;
    */

    // generator weight
    reco_hbbNtuple.gen_weight = local.gen_weight;
    comm_hbbNtuple.gen_weight = local.gen_weight;

	// PS weights
	reco_hbbNtuple.ps_weights = local.ps_weights;

    // PU weight
    reco_hbbNtuple.npv = local.truenpv;
    reco_hbbNtuple.PU_weight = local.PU_weight;
    reco_hbbNtuple.PU_weight_up = local.PU_weight_up;
    reco_hbbNtuple.PU_weight_down = local.PU_weight_down;

    comm_hbbNtuple.npv = local.truenpv;
    comm_hbbNtuple.PU_weight = local.PU_weight;
    comm_hbbNtuple.PU_weight_up = local.PU_weight_up;
    comm_hbbNtuple.PU_weight_down = local.PU_weight_down;

    // ttHF categorization
    reco_hbbNtuple.ttHf_cat = local.ttHf_cat;
    comm_hbbNtuple.ttHf_cat = local.ttHf_cat;

    // ttHFGenFilter
    if (!isdata && !is_madg) {
        if (local.ttHFGenFilter == true){
            reco_hbbNtuple.ttHFGenFilter = 1;
            comm_hbbNtuple.ttHFGenFilter = 1;
        }
        else{
            reco_hbbNtuple.ttHFGenFilter = 0;
            comm_hbbNtuple.ttHFGenFilter = 0;
        }
    } else{
        reco_hbbNtuple.ttHFGenFilter = -1;
        comm_hbbNtuple.ttHFGenFilter = -1;
    }

    // Generator Level b-quark and neutrino info
    if (!isdata) {
        ntuple::fill_ntuple_gen_b(local, gen_hbbNtuple);
        if (save_gen_info)
            ntuple::fill_ntuple_gen_nu(local, gen_hbbNtuple);
    }

    // SL, DL and FH tagger
    reco_hbbNtuple.SL_tag = local.SL_tag;
    reco_hbbNtuple.DL_tag = local.DL_tag;
    reco_hbbNtuple.FH_tag = local.FH_tag;
    comm_hbbNtuple.SL_tag = local.SL_tag;
    comm_hbbNtuple.DL_tag = local.DL_tag;
    comm_hbbNtuple.FH_tag = local.FH_tag;
}

inline void CU_ttH_EDA::Fill_lepton_ancestor_info(CU_ttH_EDA_event_vars &local)
{

    local.sel_ele_parentid.clear();
    local.sel_ele_grandparentid.clear();
    local.sel_mu_parentid.clear();
    local.sel_mu_grandparentid.clear();

    for(unsigned int i=0; i<local.e_selected.size(); i++){
        int parentid = -99;
        int grandparentid = -99;
        if (!isdata) {
            if ((local.e_selected[i].genLepton())) {
                int genId = local.e_selected[i].genLepton()->pdgId();
                if (genId == local.e_selected[i].pdgId()) {
                    Find_link(*(local.e_selected[i].genLepton()));
                    parentid = Find_id(1);
                    grandparentid = Find_id(2);
                }
            }
        }
        local.sel_ele_parentid.push_back(parentid);
        local.sel_ele_grandparentid.push_back(grandparentid);
    }

    for(unsigned int i=0; i<local.mu_selected.size(); i++){
        int parentid = -99;
        int grandparentid = -99;
        if (!isdata) {
            if ((local.mu_selected[i].genLepton())) {
                int genId = local.mu_selected[i].genLepton()->pdgId();
                if (genId == local.mu_selected[i].pdgId()) {
                    Find_link(*(local.mu_selected[i].genLepton()));
                    parentid = Find_id(1);
                    grandparentid = Find_id(2);
                }
            }
        }
        local.sel_mu_parentid.push_back(parentid);
        local.sel_mu_grandparentid.push_back(grandparentid);
    }
}

void CU_ttH_EDA::Fill_Gen_b_info(const std::vector<reco::GenParticle> &genparticles,
                            CU_ttH_EDA_event_vars &local)
{
    local.genbquarks.clear();
    local.genbquarks_imm_parentid.clear();
    local.genbquarks_imm_daughterid.clear();
    local.genbquarks_parentid.clear();
    local.genbquarks_grandparentid.clear();

    local.genbhadrons.clear();
    local.genbhadrons_parentid.clear();
    local.genbhadrons_grandparentid.clear();

    for (std::vector<reco::GenParticle>::const_iterator
             gen = genparticles.begin(),
             ed = genparticles.end();
         gen != ed; ++gen) {
        if (gen->pdgId() == 5 || gen->pdgId() == -5) {
            local.genbquarks.push_back(*gen);
            Find_link(*gen);
            if (gen->numberOfMothers() >= 1)
                local.genbquarks_imm_parentid.push_back(
                    gen->mother(0)->pdgId());
            else
                local.genbquarks_imm_parentid.push_back(-99);
            if (gen->numberOfDaughters() >= 1)
                local.genbquarks_imm_daughterid.push_back(
                    gen->daughter(0)->pdgId());
            else
                local.genbquarks_imm_daughterid.push_back(-99);
            local.genbquarks_parentid.push_back(Find_id(1));
            local.genbquarks_grandparentid.push_back(Find_id(2));
        }

        int b_mesonid = (abs(gen->pdgId()) / 100) % 10;
        int b_baryonid = abs(gen->pdgId()) / 1000;
        int is_b_ancestor = 0;

        if (b_mesonid == 5 || b_baryonid == 5) {
            local.genbhadrons.push_back(*gen);
            if (gen->numberOfMothers() >= 1) {
                for (unsigned int j = 0; j < gen->numberOfMothers(); j++) {
                    if (abs(gen->mother(j)->pdgId()) == 5) {
                        is_b_ancestor = 1;
                        break;
                    }
                }
            }
            local.genbhadrons_is_b_ancestor.push_back(is_b_ancestor);
            Find_link(*gen);
            local.genbhadrons_parentid.push_back(Find_id(1));
            local.genbhadrons_grandparentid.push_back(Find_id(2));
        }
    }
}

void CU_ttH_EDA::Fill_Gen_nu_info(const std::vector<reco::GenParticle> &genparticles,
                             CU_ttH_EDA_event_vars &local)
{
    local.gen_nu.clear();
    local.gen_nu_imm_parentid.clear();
    local.gen_nu_parentid.clear();
    local.gen_nu_grandparentid.clear();

    for (std::vector<reco::GenParticle>::const_iterator
             gen = genparticles.begin(),
             ed = genparticles.end();
         gen != ed; ++gen) {
        if (gen->pdgId() == 12 || gen->pdgId() == 14 || gen->pdgId() == 16) {
            local.gen_nu.push_back(*gen);
            Find_link(*gen);

            if (gen->numberOfMothers() >= 1)
                local.gen_nu_imm_parentid.push_back(gen->mother(0)->pdgId());
            else
                local.gen_nu_imm_parentid.push_back(-99);

            local.gen_nu_parentid.push_back(Find_id(1));
            local.gen_nu_grandparentid.push_back(Find_id(2));
        }
    }
}

inline void
CU_ttH_EDA::Fill_Gen_info(const std::vector<reco::GenParticle> &genparticles,
                          const std::vector<reco::GenJet> &genjets,
                          CU_ttH_EDA_event_vars &local)
{
    local.genelectrons_selected.clear();
    local.genelectrons_selected_parentid.clear();
    local.genelectrons_selected_grandparentid.clear();
    local.genmuons_selected.clear();
    local.genmuons_selected_parentid.clear();
    local.genmuons_selected_grandparentid.clear();
    local.genjets_selected.clear();

    for (std::vector<reco::GenParticle>::const_iterator
             gen = genparticles.begin(),
             ed = genparticles.end();
         gen != ed; ++gen) {
        if (gen->pdgId() == 11 || gen->pdgId() == -11) {
            if( gen->pt() > min_ele_pT && fabs(gen->eta()) < max_ele_eta ){
                local.genelectrons_selected.push_back(*gen);
                Find_link(*gen);
                local.genelectrons_selected_parentid.push_back(Find_id(1));
                local.genelectrons_selected_grandparentid.push_back(Find_id(2));
            }
        } else if (gen->pdgId() == 13 || gen->pdgId() == -13) {
            if( gen->pt() > min_mu_pT && fabs(gen->eta()) < max_mu_eta ){
                local.genmuons_selected.push_back(*gen);
                Find_link(*gen);
                local.genmuons_selected_parentid.push_back(Find_id(1));
                local.genmuons_selected_grandparentid.push_back(Find_id(2));
            }
        }
    }

    for (reco::GenJetCollection::const_iterator iter = genjets.begin();
         iter != genjets.end(); ++iter) {
        if( iter->pt() > min_jet_pT && fabs(iter->eta()) < max_jet_eta )
            local.genjets_selected.push_back(*iter);
    }
}

inline void CU_ttH_EDA::Find_link(const reco::GenParticle &gen)
{

    for (int j = 0; j < 20; j++)
        gen_id_list[j] = -99;

    int i = 0;

    gen_id_list[i++] = gen.pdgId();

    if (gen.numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)->pdgId();
    } else
        return;

    if (gen.mother(0)->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)->mother(0)->pdgId();
    } else
        return;

    if (gen.mother(0)->mother(0)->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)->mother(0)->mother(0)->pdgId();
    } else
        return;

    if (gen.mother(0)->mother(0)->mother(0)->numberOfMothers() >= 1) {
        gen_id_list[i++] =
            gen.mother(0)->mother(0)->mother(0)->mother(0)->pdgId();
    } else
        return;

    if (gen.mother(0)->mother(0)->mother(0)->mother(0)->numberOfMothers() >=
        1) {
        gen_id_list[i++] =
            gen.mother(0)->mother(0)->mother(0)->mother(0)->mother(0)->pdgId();
    } else
        return;

    if (gen.mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->pdgId();
    } else
        return;

    if (gen.mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->pdgId();
    } else
        return;

    if (gen.mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->pdgId();
    } else
        return;

    if (gen.mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->pdgId();
    } else
        return;

    if (gen.mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->pdgId();
    } else
        return;

    if (gen.mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->pdgId();
    } else
        return;

    if (gen.mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->pdgId();
    } else
        return;

    if (gen.mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->pdgId();
    } else
        return;

    if (gen.mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->pdgId();
    } else
        return;

    if (gen.mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->pdgId();
    } else
        return;

    if (gen.mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->pdgId();
    } else
        return;

    if (gen.mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->pdgId();
    } else
        return;

    if (gen.mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->pdgId();
    } else
        return;

    if (gen.mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->mother(0)
            ->numberOfMothers() >= 1) {
        gen_id_list[i++] = gen.mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->mother(0)
                               ->pdgId();
    } else
        return;

    return;
}

inline int CU_ttH_EDA::Find_id(const int &n)
{

    int j = 0;
    if (j == n)
        return gen_id_list[j];
    j++;
    for (unsigned int i = 1; i < 20; i++) {

        if (gen_id_list[i] != gen_id_list[i - 1]) {

            if (j == n) {
                return gen_id_list[i];
            } else
                j++;
        }
    }

    return gen_id_list[19];
}

void CU_ttH_EDA::Lepton_Tag(const std::vector<reco::GenParticle> &genparticles,
                            CU_ttH_EDA_event_vars &local)
{
    local.SL_tag = 0;
    local.DL_tag = 0;
    local.FH_tag = 0;

    int genid_eminus = 11;
    int genid_eplus = -11;
    int genid_muminus = 13;
    int genid_muplus = -13;
    int genid_tauminus = 15;
    int genid_tauplus = -15;
    int genid_t = 6;
    int genid_tbar = -6;
    int genid_Wplus = 24;
    int genid_Wminus = -24;

    int n_lep_minus = 0;
    int n_lep_plus = 0;
    int n_lep = 0;

    for (std::vector<reco::GenParticle>::const_iterator
             gen = genparticles.begin(),
             ed = genparticles.end();
         gen != ed; ++gen) {

        if (!local.is_OLS) {
            if (!gen->isHardProcess())
                continue;
        }

        int genId, genParentId, genGrandParentId, genGreatGrandParentId,
            genGreatGreatGrandParentId;
        genId = genParentId = genGrandParentId = genGreatGrandParentId =
            genGreatGreatGrandParentId = -99;
        genId = gen->pdgId();

        // Find_id() must have a Find_link() just before it
        Find_link(*gen);
        genParentId = Find_id(1);
        genGrandParentId = Find_id(2);

        /*
        if( gen->numberOfMothers()>=1 ){
            genParentId = gen->mother(0)->pdgId();
            if( gen->mother(0)->numberOfMothers()>=1 ){
                genGrandParentId = gen->mother(0)->mother(0)->pdgId();
                if( gen->mother(0)->mother(0)->numberOfMothers()>=1 ) {
                    genGreatGrandParentId =
        gen->mother(0)->mother(0)->mother(0)->pdgId();
                    if(
        gen->mother(0)->mother(0)->mother(0)->numberOfMothers()>=1 ) {
                        genGreatGreatGrandParentId =
        gen->mother(0)->mother(0)->mother(0)->mother(0)->pdgId();
                    }
                }
            }
        }
        */
        // std::cout<<"GenId :  "<<genId<<"  GenParentId :  "<<genParentId<<"
        // GenGrandParentId :  "<<genGrandParentId<<" GreatGrandParentId :
        // "<<genGreatGrandParentId<<"  GreatGreatGrandParentId :
        // "<<genGreatGreatGrandParentId<<"\n\n";

        // std::cout<<"GenId :  "<<genId<<"  GenParentId :  "<<genParentId<<"
        // GenGrandParentId :  "<<genGrandParentId<<"\n\n";

        if ((genId == genid_muminus) || (genId == genid_eminus) ||
            (genId == genid_tauminus)) {
            if (genParentId == genid_Wminus) {
                if (genGrandParentId == genid_tbar)
                    n_lep_minus++;
            }
        }
        if ((genId == genid_muplus) || (genId == genid_eplus) ||
            (genId == genid_tauplus)) {
            if (genParentId == genid_Wplus) {
                if (genGrandParentId == genid_t)
                    n_lep_plus++;
            }
        }

        /*
        if( (genId == genid_muminus) || (genId == genid_eminus) || (genId ==
        genid_tauminus) ){
            if( genParentId == genId){
                if(genGrandParentId == genid_Wminus) {
                    if(genGreatGrandParentId == genid_tbar)
                        n_lep_minus++;
                    else if(genGreatGrandParentId == genid_Wminus){
                        if(genGreatGreatGrandParentId == genid_tbar)
                            n_lep_minus++;
                    }
                }
            }
        }
        else if( (genId == genid_muplus) || (genId == genid_eplus) || (genId ==
        genid_tauplus) ){
            if( (genParentId == genid_muplus) || (genParentId == genid_eplus) ||
        (genParentId == genid_tauplus) ){
                if(genGrandParentId == genid_Wplus){
                    if(genGreatGrandParentId == genid_t)
                        n_lep_plus++;
                    else if(genGreatGrandParentId == genid_Wplus){
                        if(genGreatGreatGrandParentId == genid_t)
                            n_lep_plus++;
                    }
                }
            }
        }
        */
    }

    n_lep = n_lep_minus + n_lep_plus;

    if (n_lep == 0)
        local.FH_tag = 1;
    else if (n_lep == 1)
        local.SL_tag = 1;
    else if (n_lep == 2) {
        if (n_lep_minus == 1 && n_lep_plus == 1)
            local.DL_tag = 1;
    }

    // std::cout<<"nleptons:  "<<n_lep<<"  SL : "<<local.SL_tag<<"  DL :
    // "<<local.DL_tag<<"  FH : "<<local.FH_tag<<"\n\n";
}

inline void CU_ttH_EDA::GetjetSF(CU_ttH_EDA_event_vars &local,
                                 const double &rho, const edm_Handles &handle)
{
    local.jet_jesSF_sourcename = jet_jesSF_names;

    std::vector<double> jes_sf_temp_up[26];
    std::vector<double> jes_sf_temp_down[26];
	std::vector<double> jer_sf_temp_up[26];
	std::vector<double> jer_sf_temp_down[26];
    for(int j=0; j<26; j++){
        jes_sf_temp_up[j].clear();
        jes_sf_temp_down[j].clear();
		jer_sf_temp_up[j].clear();
		jer_sf_temp_down[j].clear();
    }

    for(unsigned int i=0; i<local.jets_selected_uncorrected.size(); i++){
        pat::Jet jet = local.jets_selected_uncorrected[i];
        local.jet_jecSF_nominal.push_back(GetJECSF(jet, "Nominal", rho, local));

        if (!isdata) {
            local.jet_jecSF_nominal_up.push_back(GetJECSF(jet, "Nominal_up", rho, local));
            local.jet_jecSF_nominal_down.push_back(GetJECSF(jet, "Nominal_down", rho, local));
            for(int j=0; j<26; j++){
                std::string jes_var_up = (jet_jesSF_names[j]+"_up").c_str();
                std::string jes_var_down = (jet_jesSF_names[j]+"_down").c_str();
                jes_sf_temp_up[j].push_back(GetJECSF(jet, jes_var_up, rho, local));
                jes_sf_temp_down[j].push_back(GetJECSF(jet, jes_var_down, rho, local));
            }
            jet.scaleEnergy(local.jet_jecSF_nominal[i]);
            local.jet_jerSF_jesnominal_nominal.push_back(GetJERSF(jet, "Nominal", rho, handle.genjets, local));
            local.jet_jerSF_jesnominal_up.push_back(GetJERSF(jet, "Nominal_up", rho, handle.genjets, local));
            local.jet_jerSF_jesnominal_down.push_back(GetJERSF(jet, "Nominal_down", rho, handle.genjets, local));
			for(int j=0; j<26; j++){
				pat::Jet jet2 = local.jets_selected_uncorrected[i];
				jet2.scaleEnergy(jes_sf_temp_up[j][i]);
				jer_sf_temp_up[j].push_back(GetJERSF(jet2, "Nominal", rho, handle.genjets, local));
				pat::Jet jet3 = local.jets_selected_uncorrected[i];
				jet3.scaleEnergy(jes_sf_temp_down[j][i]);
				jer_sf_temp_down[j].push_back(GetJERSF(jet3, "Nominal", rho, handle.genjets, local));
			}
        }
        else{
            local.jet_jecSF_nominal_up.push_back(1.0);
            local.jet_jecSF_nominal_down.push_back(1.0);
            for(int j=0; j<26; j++){
                jes_sf_temp_up[j].push_back(1.0);
                jes_sf_temp_down[j].push_back(1.0);
				jer_sf_temp_up[j].push_back(1.0);
				jer_sf_temp_down[j].push_back(1.0);
            }
            local.jet_jerSF_jesnominal_nominal.push_back(1.0);
            local.jet_jerSF_jesnominal_up.push_back(1.0);
            local.jet_jerSF_jesnominal_down.push_back(1.0);
        }
    }

    for(int j=0; j<26; j++){
        local.jet_jesSF_up.push_back(jes_sf_temp_up[j]);
        local.jet_jesSF_down.push_back(jes_sf_temp_down[j]);
		local.jet_jerSF_jesup_nominal.push_back(jer_sf_temp_up[j]);
		local.jet_jerSF_jesdown_nominal.push_back(jer_sf_temp_down[j]);
    }
}

inline void CU_ttH_EDA::GetLeptonSF(CU_ttH_EDA_event_vars &local)
{
    for(unsigned int i=0; i<local.e_selected.size(); i++){

        if (isdata) {
            local.ele_sf_id_combined.push_back(1.0);
            local.ele_sf_id_up_combined.push_back(1.0);
            local.ele_sf_id_down_combined.push_back(1.0);
            local.ele_sf_iso_combined.push_back(1.0);
            local.ele_sf_iso_up_combined.push_back(1.0);
            local.ele_sf_iso_down_combined.push_back(1.0);
			local.ele_sf_id_rundep.push_back(1.0);
			local.ele_sf_id_up_rundep.push_back(1.0);
			local.ele_sf_id_down_rundep.push_back(1.0);
			local.ele_sf_iso_rundep.push_back(1.0);
			local.ele_sf_iso_up_rundep.push_back(1.0);
			local.ele_sf_iso_down_rundep.push_back(1.0);
            continue;
        }

		double e_id_BCDEF = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 0, "ID_BCDEF");
        double e_id_B = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 0, "ID_B");
		double e_id_C = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 0, "ID_C");
		double e_id_D = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 0, "ID_D");
		double e_id_E = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 0, "ID_E");
		double e_id_F = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 0, "ID_F");
		local.ele_sf_id_combined.push_back(e_id_BCDEF);
        local.ele_sf_id_rundep.push_back((e_id_B*4.767 + e_id_C*9.583 + e_id_D*4.224 + e_id_E*9.261 + e_id_F*13.463) / 41.298);

		double e_id_BCDEF_up = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 1, "ID_BCDEF");
		double e_id_B_up = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 1, "ID_B");
		double e_id_C_up = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 1, "ID_C");
		double e_id_D_up = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 1, "ID_D");
		double e_id_E_up = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 1, "ID_E");
		double e_id_F_up = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 1, "ID_F");
		local.ele_sf_id_up_combined.push_back(e_id_BCDEF_up);
		local.ele_sf_id_up_rundep.push_back((e_id_B_up*4.767 + e_id_C_up*9.583 + e_id_D_up*4.224 + e_id_E_up*9.261 + e_id_F_up*13.463) / 41.298);

		double e_id_BCDEF_down = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), -1, "ID_BCDEF");
		double e_id_B_down = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), -1, "ID_B");
		double e_id_C_down = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), -1, "ID_C");
		double e_id_D_down = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), -1, "ID_D");
		double e_id_E_down = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), -1, "ID_E");
		double e_id_F_down = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), -1, "ID_F");
		local.ele_sf_id_down_combined.push_back(e_id_BCDEF_down);
		local.ele_sf_id_down_rundep.push_back((e_id_B_down*4.767 + e_id_C_down*9.583 + e_id_D_down*4.224 + e_id_E_down*9.261 + e_id_F_down*13.463) / 41.298);


		double e_iso_BCDEF = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 0, "Iso_BCDEF");
		double e_iso_B = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 0, "Iso_B");
		double e_iso_C = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 0, "Iso_C");
		double e_iso_D = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 0, "Iso_D");
		double e_iso_E = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 0, "Iso_E");
		double e_iso_F = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 0, "Iso_F");
		local.ele_sf_iso_combined.push_back(e_iso_BCDEF);
		local.ele_sf_iso_rundep.push_back((e_iso_B*4.767 + e_iso_C*9.583 + e_iso_D*4.224 + e_iso_E*9.261 + e_iso_F*13.463) / 41.298);

		double e_iso_BCDEF_up = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 1, "Iso_BCDEF");
		double e_iso_B_up = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 1, "Iso_B");
		double e_iso_C_up = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 1, "Iso_C");
		double e_iso_D_up = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 1, "Iso_D");
		double e_iso_E_up = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 1, "Iso_E");
		double e_iso_F_up = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), 1, "Iso_F");
		local.ele_sf_iso_up_combined.push_back(e_iso_BCDEF_up);
		local.ele_sf_iso_up_rundep.push_back((e_iso_B_up*4.767 + e_iso_C_up*9.583 + e_iso_D_up*4.224 + e_iso_E_up*9.261 + e_iso_F_up*13.463) / 41.298);

		double e_iso_BCDEF_down = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), -1, "Iso_BCDEF");
		double e_iso_B_down = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), -1, "Iso_B");
		double e_iso_C_down = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), -1, "Iso_C");
		double e_iso_D_down = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), -1, "Iso_D");
		double e_iso_E_down = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), -1, "Iso_E");
		double e_iso_F_down = leptonSFhelper.GetElectronSF(local.uncorr_ele_pt[i],local.e_selected[i].superCluster()->position().eta(), -1, "Iso_F");
		local.ele_sf_iso_down_combined.push_back(e_iso_BCDEF_down);
		local.ele_sf_iso_down_rundep.push_back((e_iso_B_down*4.767 + e_iso_C_down*9.583 + e_iso_D_down*4.224 + e_iso_E_down*9.261 + e_iso_F_down*13.463) / 41.298);
    }

    for(unsigned int i=0; i<local.mu_selected.size(); i++){

        if(isdata){
            local.mu_sf_id_combined.push_back(1.0);
            local.mu_sf_id_up_combined.push_back(1.0);
            local.mu_sf_id_down_combined.push_back(1.0);
            local.mu_sf_iso_combined.push_back(1.0);
            local.mu_sf_iso_up_combined.push_back(1.0);
            local.mu_sf_iso_down_combined.push_back(1.0);
            local.mu_sf_tracking_combined.push_back(1.0);
            local.mu_sf_tracking_up_combined.push_back(1.0);
            local.mu_sf_tracking_down_combined.push_back(1.0);
			local.mu_sf_id_rundep.push_back(1.0);
			local.mu_sf_id_up_rundep.push_back(1.0);
			local.mu_sf_id_down_rundep.push_back(1.0);
			local.mu_sf_iso_rundep.push_back(1.0);
			local.mu_sf_iso_up_rundep.push_back(1.0);
			local.mu_sf_iso_down_rundep.push_back(1.0);
			local.mu_sf_tracking_rundep.push_back(1.0);
			local.mu_sf_tracking_up_rundep.push_back(1.0);
			local.mu_sf_tracking_down_rundep.push_back(1.0);
            continue;
        }

        double mu_id_BCDEF = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 0, "ID_BCDEF");
		double mu_id_BC = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 0, "ID_BC");
		double mu_id_DE = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 0, "ID_DE");
		double mu_id_F = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 0, "ID_F");
		local.mu_sf_id_combined.push_back(mu_id_BCDEF);
        local.mu_sf_id_rundep.push_back((mu_id_BC*14.350 + mu_id_DE*13.485 + mu_id_F*13.463) / 41.298);

		double mu_id_BCDEF_up = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 1, "ID_BCDEF");
		double mu_id_BC_up = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 1, "ID_BC");
		double mu_id_DE_up = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 1, "ID_DE");
		double mu_id_F_up = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 1, "ID_F");
		local.mu_sf_id_up_combined.push_back(mu_id_BCDEF_up);
		local.mu_sf_id_up_rundep.push_back((mu_id_BC_up*14.350 + mu_id_DE_up*13.485 + mu_id_F_up*13.463) / 41.298);

		double mu_id_BCDEF_down = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), -1, "ID_BCDEF");
		double mu_id_BC_down = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), -1, "ID_BC");
		double mu_id_DE_down = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), -1, "ID_DE");
		double mu_id_F_down = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), -1, "ID_F");
		local.mu_sf_id_down_combined.push_back(mu_id_BCDEF_down);
		local.mu_sf_id_down_rundep.push_back((mu_id_BC_down*14.350 + mu_id_DE_down*13.485 + mu_id_F_down*13.463) / 41.298);


		double mu_iso_BCDEF = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 0, "Iso_BCDEF");
		double mu_iso_BC = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 0, "Iso_BC");
		double mu_iso_DE = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 0, "Iso_DE");
		double mu_iso_F = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 0, "Iso_F");
		local.mu_sf_iso_combined.push_back(mu_iso_BCDEF);
		local.mu_sf_iso_rundep.push_back((mu_iso_BC*14.350 + mu_iso_DE*13.485 + mu_iso_F*13.463) / 41.298);

		double mu_iso_BCDEF_up = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 1, "Iso_BCDEF");
		double mu_iso_BC_up = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 1, "Iso_BC");
		double mu_iso_DE_up = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 1, "Iso_DE");
		double mu_iso_F_up = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 1, "Iso_F");
		local.mu_sf_iso_up_combined.push_back(mu_iso_BCDEF_up);
		local.mu_sf_iso_up_rundep.push_back((mu_iso_BC_up*14.350 + mu_iso_DE_up*13.485 + mu_iso_F_up*13.463) / 41.298);

		double mu_iso_BCDEF_down = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), -1, "Iso_BCDEF");
		double mu_iso_BC_down = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), -1, "Iso_BC");
		double mu_iso_DE_down = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), -1, "Iso_DE");
		double mu_iso_F_down = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), -1, "Iso_F");
		local.mu_sf_iso_down_combined.push_back(mu_iso_BCDEF_down);
		local.mu_sf_iso_down_rundep.push_back((mu_iso_BC_down*14.350 + mu_iso_DE_down*13.485 + mu_iso_F_down*13.463) / 41.298);

		/*
		double mu_tracking_BCDEF = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 0, "Tracking_BCDEF");
		double mu_tracking_BC = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 0, "Tracking_BC");
		double mu_tracking_DE = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 0, "Tracking_DE");
		double mu_tracking_F = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 0, "Tracking_F");
		local.mu_sf_tracking_combined.push_back(mu_tracking_BCDEF);
		local.mu_sf_tracking_rundep.push_back((mu_tracking_BC*14.350 + mu_tracking_DE*13.485 + mu_tracking_F*13.463) / 41.298);

		double mu_tracking_BCDEF_up = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 1, "Tracking_BCDEF");
		double mu_tracking_BC_up = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 1, "Tracking_BC");
		double mu_tracking_DE_up = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 1, "Tracking_DE");
		double mu_tracking_F_up = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), 1, "Tracking_F");
		local.mu_sf_tracking_up_combined.push_back(mu_tracking_BCDEF_up);
		local.mu_sf_tracking_up_rundep.push_back((mu_tracking_BC_up*14.350 + mu_tracking_DE_up*13.485 + mu_tracking_F_up*13.463) / 41.298);

		double mu_tracking_BCDEF_down = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), -1, "Tracking_BCDEF");
		double mu_tracking_BC_down = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), -1, "Tracking_BC");
		double mu_tracking_DE_down = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), -1, "Tracking_DE");
		double mu_tracking_F_down = leptonSFhelper.GetMuonSF(local.mu_selected[i].pt(), local.mu_selected[i].eta(), -1, "Tracking_F");
		local.mu_sf_tracking_down_combined.push_back(mu_tracking_BCDEF_down);
		local.mu_sf_tracking_down_rundep.push_back((mu_tracking_BC_down*14.350 + mu_tracking_DE_down*13.485 + mu_tracking_F_down*13.463) / 41.298);
	    */
		local.mu_sf_tracking_combined.push_back(1.0);
		local.mu_sf_tracking_rundep.push_back(1.0);
		local.mu_sf_tracking_up_combined.push_back(1.0);
		local.mu_sf_tracking_up_rundep.push_back(1.0);
		local.mu_sf_tracking_down_combined.push_back(1.0);
		local.mu_sf_tracking_down_rundep.push_back(1.0);
    }
}


void CU_ttH_EDA::GetPUweight(edm::Handle<std::vector<PileupSummaryInfo>> PupInfo,
                        CU_ttH_EDA_event_vars &local)
{
    double pu_weight = 1;
    double pu_weight_up = 1;
    double pu_weight_down = 1;
    double numTruePV = -1;
    if ((PupInfo.isValid())) {
        for (std::vector<PileupSummaryInfo>::const_iterator PVI =
                 PupInfo->begin();
             PVI != PupInfo->end(); ++PVI) {
            int BX = PVI->getBunchCrossing();
            if (BX == 0) {
                numTruePV = PVI->getTrueNumInteractions();
            }
        }
    }
    local.truenpv = numTruePV;

	/*
    for (int i = 0; i < 98; ++i) {
        if (numTruePV < (PU_x[i] + 1)) {
            pu_weight = PU_y[i];
            pu_weight_up = PU_y_up[i];
            pu_weight_down = PU_y_down[i];
            break;
        }
    }
	*/
	
    local.PU_weight = pu_weight;
    local.PU_weight_up = pu_weight_up;
    local.PU_weight_down = pu_weight_down;
}

void CU_ttH_EDA::GetPSweights(CU_ttH_EDA_event_vars &local, const edm_Handles &handle)
{
	std::vector<double> v_psWeight = handle.event_gen_info->weights();
	// Normalize all Parton-Shower weights to the nominal one
	if(v_psWeight.size() > 0)
	{
		const double nominal_psWeight = v_psWeight.at(0);
		if(nominal_psWeight == 0.)
			{
			throw cms::Exception("Input") << "nominal PS-Weight equal to zero (failed to normalize other PS-Weights)";
			}
		for(uint i=0; i<v_psWeight.size(); ++i){
			v_psWeight.at(i) /= nominal_psWeight;
		}
	}
	local.ps_weights = v_psWeight;
}

inline double
CU_ttH_EDA::GetQ2weight(const edm::Handle<GenEventInfoProduct> &event_gen_info,
                        const edm::Handle<LHEEventProduct> &EvtHandle,
                        const string &ud)
{
    double theWeight;
    theWeight = event_gen_info->weight();
    unsigned int i;
    for (i = 0; i < EvtHandle->weights().size(); ++i) {
        if (!(ud.compare(EvtHandle->weights()[i].id)))
            theWeight *=
                EvtHandle->weights()[i].wgt / EvtHandle->originalXWGTUP();
    }
    return theWeight;
}

void CU_ttH_EDA::FillCSVHistos(TFile *fileHF, TFile *fileLF)
{
    for (int iSys = 0; iSys < 31; ++iSys) {
        for (int iPt = 0; iPt < 5; ++iPt)
            h_csv_wgt_hf[iSys][iPt] = NULL;
        for (int iPt = 0; iPt < 3; ++iPt) {
            for (int iEta = 0; iEta < 3; ++iEta)
                h_csv_wgt_lf[iSys][iPt][iEta] = NULL;
        }
    }
    for (int iSys = 0; iSys < 5; ++iSys) {
        for (int iPt = 0; iPt < 5; ++iPt)
            c_csv_wgt_hf[iSys][iPt] = NULL;
    }

    // CSV reweighting
    for (int iSys = 0; iSys < 31; ++iSys) {
        TString syst_csv_suffix_hf = "final";
        TString syst_csv_suffix_c = "final";
        TString syst_csv_suffix_lf = "final";

        switch (iSys) {
        case 0:
            // this is the nominal case
            break;
        case 1:
            // JESUp
            syst_csv_suffix_hf = "final_JESUp";
            syst_csv_suffix_lf = "final_JESUp";
            syst_csv_suffix_c = "final_cErr1Up";
            break;
        case 2:
            // JESDown
            syst_csv_suffix_hf = "final_JESDown";
            syst_csv_suffix_lf = "final_JESDown";
            syst_csv_suffix_c = "final_cErr1Down";
            break;
        case 3:
            // purity up
            syst_csv_suffix_hf = "final_LFUp";
            syst_csv_suffix_lf = "final_HFUp";
            syst_csv_suffix_c = "final_cErr2Up";
            break;
        case 4:
            // purity down
            syst_csv_suffix_hf = "final_LFDown";
            syst_csv_suffix_lf = "final_HFDown";
            syst_csv_suffix_c = "final_cErr2Down";
            break;
        case 5:
            // stats1 up
            syst_csv_suffix_hf = "final_Stats1Up";
            syst_csv_suffix_lf = "final_Stats1Up";
            break;
        case 6:
            // stats1 down
            syst_csv_suffix_hf = "final_Stats1Down";
            syst_csv_suffix_lf = "final_Stats1Down";
            break;
        case 7:
            // stats2 up
            syst_csv_suffix_hf = "final_Stats2Up";
            syst_csv_suffix_lf = "final_Stats2Up";
            break;
        case 8:
            // stats2 down
            syst_csv_suffix_hf = "final_Stats2Down";
            syst_csv_suffix_lf = "final_Stats2Down";
            break;
		case 9:
			// JESAbsoluteScaleUp
			syst_csv_suffix_hf = "final_JESAbsoluteScaleUp";
			syst_csv_suffix_lf = "final_JESAbsoluteScaleUp";
			break;
		case 10:
			// JESAbsoluteScaleDown
			syst_csv_suffix_hf = "final_JESAbsoluteScaleDown";
			syst_csv_suffix_lf = "final_JESAbsoluteScaleDown";
			break;
		case 11:
			// JESAbsoluteMPFBiasUp
			syst_csv_suffix_hf = "final_JESAbsoluteMPFBiasUp";
			syst_csv_suffix_lf = "final_JESAbsoluteMPFBiasUp";
			break;
		case 12:
			// JESAbsoluteMPFBiasDown
			syst_csv_suffix_hf = "final_JESAbsoluteMPFBiasDown";
			syst_csv_suffix_lf = "final_JESAbsoluteMPFBiasDown";
			break;
		case 13:
			// JESSinglePionECALUp
			syst_csv_suffix_hf = "final_JESSinglePionECALUp";
			syst_csv_suffix_lf = "final_JESSinglePionECALUp";
			break;
		case 14:
			// JESSinglePionECALDown
			syst_csv_suffix_hf = "final_JESSinglePionECALDown";
			syst_csv_suffix_lf = "final_JESSinglePionECALDown";
			break;
		case 15:
			// JESSinglePionHCALUp
			syst_csv_suffix_hf = "final_JESSinglePionHCALUp";
			syst_csv_suffix_lf = "final_JESSinglePionHCALUp";
			break;
		case 16:
			// JESSinglePionHCALDown
			syst_csv_suffix_hf = "final_JESSinglePionHCALDown";
			syst_csv_suffix_lf = "final_JESSinglePionHCALDown";
			break;
		case 17:
			// JESFlavorQCDUp
			syst_csv_suffix_hf = "final_JESFlavorQCDUp";
			syst_csv_suffix_lf = "final_JESFlavorQCDUp";
			break;
		case 18:
			// JESFlavorQCDDown
			syst_csv_suffix_hf = "final_JESFlavorQCDDown";
			syst_csv_suffix_lf = "final_JESFlavorQCDDown";
			break;
		case 19:
			// JESTimePtEtaUp
			syst_csv_suffix_hf = "final_JESTimePtEtaUp";
			syst_csv_suffix_lf = "final_JESTimePtEtaUp";
			break;
		case 20:
			// JESTimePtEtaDown
			syst_csv_suffix_hf = "final_JESTimePtEtaDown";
			syst_csv_suffix_lf = "final_JESTimePtEtaDown";
			break;
		case 21:
			// JESRelativeFSRUp
			syst_csv_suffix_hf = "final_JESRelativeFSRUp";
			syst_csv_suffix_lf = "final_JESRelativeFSRUp";
			break;
		case 22:
			// JESRelativeFSRDown
			syst_csv_suffix_hf = "final_JESRelativeFSRDown";
			syst_csv_suffix_lf = "final_JESRelativeFSRDown";
			break;
		case 23:
			// JESPileUpDataMCUp
			syst_csv_suffix_hf = "final_JESPileUpDataMCUp";
			syst_csv_suffix_lf = "final_JESPileUpDataMCUp";
			break;
		case 24:
			// JESPileUpDataMCDown
			syst_csv_suffix_hf = "final_JESPileUpDataMCDown";
			syst_csv_suffix_lf = "final_JESPileUpDataMCDown";
			break;
		case 25:
			// JESPileUpPtRefUp
			syst_csv_suffix_hf = "final_JESPileUpPtRefUp";
			syst_csv_suffix_lf = "final_JESPileUpPtRefUp";
			break;
		case 26:
			// JESPileUpPtRefDown
			syst_csv_suffix_hf = "final_JESPileUpPtRefDown";
			syst_csv_suffix_lf = "final_JESPileUpPtRefDown";
			break;
		case 27:
			// JESPileUpPtBBUp
			syst_csv_suffix_hf = "final_JESPileUpPtBBUp";
			syst_csv_suffix_lf = "final_JESPileUpPtBBUp";
			break;
		case 28:
			// JESPileUpPtBBDown
			syst_csv_suffix_hf = "final_JESPileUpPtBBDown";
			syst_csv_suffix_lf = "final_JESPileUpPtBBDown";
			break;
		case 29:
			// JESPileUpPtEC1Up
			syst_csv_suffix_hf = "final_JESPileUpPtEC1Up";
			syst_csv_suffix_lf = "final_JESPileUpPtEC1Up";
			break;
		case 30:
			// JESPileUpPtEC1Down
			syst_csv_suffix_hf = "final_JESPileUpPtEC1Down";
			syst_csv_suffix_lf = "final_JESPileUpPtEC1Down";
			break;
        }

        for (int iPt = 0; iPt < 5; ++iPt)
            h_csv_wgt_hf[iSys][iPt] = (TH1D *)fileHF->Get(Form("csv_ratio_Pt%i_Eta0_%s", iPt, syst_csv_suffix_hf.Data()));

        if (iSys < 5) {
            for (int iPt = 0; iPt < 5; ++iPt)
                c_csv_wgt_hf[iSys][iPt] = (TH1D *)fileHF->Get(Form("c_csv_ratio_Pt%i_Eta0_%s", iPt, syst_csv_suffix_c.Data()));
        }

        for (int iPt = 0; iPt < 4; ++iPt) {
            for (int iEta = 0; iEta < 3; ++iEta)
                h_csv_wgt_lf[iSys][iPt][iEta] =
                    (TH1D *)fileLF->Get(Form("csv_ratio_Pt%i_Eta%i_%s", iPt, iEta, syst_csv_suffix_lf.Data()));
        }
    }

    return;
}

double CU_ttH_EDA::GetCSVWeight(std::vector<double> jetPts,
                                std::vector<double> jetEtas,
                                std::vector<double> jetCSVs,
                                std::vector<int> jetFlavors, int iSys,
                                double &csvWgtHF, double &csvWgtLF,
                                double &csvWgtCF)
{
    csvWgtHF = csvWgtLF = csvWgtCF = 0;
    int iSysHF = 0;
    switch (iSys) {
    case 7:
        iSysHF = 1;
        break; // JESUp
    case 8:
        iSysHF = 2;
        break; // JESDown
    case 9:
        iSysHF = 3;
        break; // LFUp
    case 10:
        iSysHF = 4;
        break; // LFDown
    case 13:
        iSysHF = 5;
        break; // Stats1Up
    case 14:
        iSysHF = 6;
        break; // Stats1Down
    case 15:
        iSysHF = 7;
        break; // Stats2Up
    case 16:
        iSysHF = 8;
        break; // Stats2Down
	case 201:
		iSysHF = 9;
		break; // JESAbsoluteScaleUp
	case 101:
		iSysHF = 10;
		break; // JESAbsoluteScaleDown
	case 202:
		iSysHF = 11;
		break; // JESAbsoluteMPFBiasUp
	case 102:
		iSysHF = 12;
		break; // JESAbsoluteMPFBiasDown
	case 204:
		iSysHF = 13;
		break; // JESSinglePionECALUp
	case 104:
		iSysHF = 14;
		break; // JESSinglePionECALDown
	case 205:
		iSysHF = 15;
		break; // JESSinglePionHCALUp
	case 105:
		iSysHF = 16;
		break; // JESSinglePionHCALDown
	case 206:
		iSysHF = 17;
		break; // JESFlavorQCDUp
	case 106:
		iSysHF = 18;
		break; // JESFlavorQCDDown
	case 207:
		iSysHF = 19;
		break; // JESTimePtEtaUp
	case 107:
		iSysHF = 20;
		break; // JESTimePtEtaDown
	case 216:
		iSysHF = 21;
		break; // JESRelativeFSRUp
	case 116:
		iSysHF = 22;
		break; // JESRelativeFSRDown
	case 220:
		iSysHF = 23;
		break; // JESPileUpDataMCUp
	case 120:
		iSysHF = 24;
		break; // JESPileUpDataMCDown
	case 221:
		iSysHF = 25;
		break; // JESPileUpPtRefUp
	case 121:
		iSysHF = 26;
		break; // JESPileUpPtRefDown
	case 222:
		iSysHF = 27;
		break; // JESPileUpPtBBUp
	case 122:
		iSysHF = 28;
		break; // JESPileUpPtBBDown
	case 223:
		iSysHF = 29;
		break; // JESPileUpPtEC1Up
	case 123:
		iSysHF = 30;
		break; // JESPileUpPtEC1Down
    default:
        iSysHF = 0;
        break; // NoSys
    }

    int iSysC = 0;
    switch (iSys) {
    case 21:
        iSysC = 1;
        break;
    case 22:
        iSysC = 2;
        break;
    case 23:
        iSysC = 3;
        break;
    case 24:
        iSysC = 4;
        break;
    default:
        iSysC = 0;
        break;
    }

    int iSysLF = 0;
    switch (iSys) {
    case 7:
        iSysLF = 1;
        break; // JESUp
    case 8:
        iSysLF = 2;
        break; // JESDown
    case 11:
        iSysLF = 3;
        break; // HFUp
    case 12:
        iSysLF = 4;
        break; // HFDown
    case 17:
        iSysLF = 5;
        break; // Stats1Up
    case 18:
        iSysLF = 6;
        break; // Stats1Down
    case 19:
        iSysLF = 7;
        break; // Stats2Up
    case 20:
        iSysLF = 8;
        break; // Stats2Down
	case 201:
		iSysLF = 9;
		break; // JESAbsoluteScaleUp
	case 101:
		iSysLF = 10;
		break; // JESAbsoluteScaleDown
	case 202:
		iSysLF = 11;
		break; // JESAbsoluteMPFBiasUp
	case 102:
		iSysLF = 12;
		break; // JESAbsoluteMPFBiasDown
	case 204:
		iSysLF = 13;
		break; // JESSinglePionECALUp
	case 104:
		iSysLF = 14;
		break; // JESSinglePionECALDown
	case 205:
		iSysLF = 15;
		break; // JESSinglePionHCALUp
	case 105:
		iSysLF = 16;
		break; // JESSinglePionHCALDown
	case 206:
		iSysLF = 17;
		break; // JESFlavorQCDUp
	case 106:
		iSysLF = 18;
		break; // JESFlavorQCDDown
	case 207:
		iSysLF = 19;
		break; // JESTimePtEtaUp
	case 107:
		iSysLF = 20;
		break; // JESTimePtEtaDown
	case 216:
		iSysLF = 21;
		break; // JESRelativeFSRUp
	case 116:
		iSysLF = 22;
		break; // JESRelativeFSRDown
	case 220:
		iSysLF = 23;
		break; // JESPileUpDataMCUp
	case 120:
		iSysLF = 24;
		break; // JESPileUpDataMCDown
	case 221:
		iSysLF = 25;
		break; // JESPileUpPtRefUp
	case 121:
		iSysLF = 26;
		break; // JESPileUpPtRefDown
	case 222:
		iSysLF = 27;
		break; // JESPileUpPtBBUp
	case 122:
		iSysLF = 28;
		break; // JESPileUpPtBBDown
	case 223:
		iSysLF = 29;
		break; // JESPileUpPtEC1Up
	case 123:
		iSysLF = 30;
		break; // JESPileUpPtEC1Down
    default:
        iSysLF = 0;
        break; // NoSys
    }

    double csvWgthf = 1.;
    double csvWgtC = 1.;
    double csvWgtlf = 1.;

    for (int iJet = 0; iJet < int(jetPts.size()); ++iJet) {

        double csv = jetCSVs[iJet];
        double jetPt = jetPts[iJet];
        double jetAbsEta = fabs(jetEtas[iJet]);
        int flavor = jetFlavors[iJet];

        int iPt = -1;
        int iEta = -1;

        if ((abs(flavor) == 4) || (abs(flavor) == 5)) { // HF
            if (jetPt >= 20 && jetPt < 30)
                iPt = 0;
            else if (jetPt >= 30 && jetPt < 50)
                iPt = 1;
            else if (jetPt >= 50 && jetPt < 70)
                iPt = 2;
            else if (jetPt >= 70 && jetPt < 100)
                iPt = 3;
            else if (jetPt >= 100)
                iPt = 4;
        } else { // LF
            if (jetPt >= 20 && jetPt < 30)
                iPt = 0;
            else if (jetPt >= 30 && jetPt < 40)
                iPt = 1;
            else if (jetPt >= 40 && jetPt < 60)
                iPt = 2;
            else if (jetPt >= 60)
                iPt = 3;
        }

        if (jetAbsEta >= 0 && jetAbsEta < 0.8)
            iEta = 0;
        else if (jetAbsEta >= 0.8 && jetAbsEta < 1.6)
            iEta = 1;
        else if (jetAbsEta >= 1.6 && jetAbsEta < 2.41)
            iEta = 2;

        if (iPt < 0 || iEta < 0)
            std::cout << "Error, couldn't find Pt, Eta bins for this b-flavor "
                         "jet, jetPt = "
                      << jetPt << ", jetAbsEta = " << jetAbsEta << std::endl;

        if (abs(flavor) == 5) {
            int useCSVBin =
                (csv >= 0.) ? h_csv_wgt_hf[iSysHF][iPt]->FindBin(csv) : 1;
            double iCSVWgtHF =
                h_csv_wgt_hf[iSysHF][iPt]->GetBinContent(useCSVBin);
            if (iCSVWgtHF != 0)
                csvWgthf *= iCSVWgtHF;
        } else if (abs(flavor) == 4) {
            int useCSVBin =
                (csv >= 0.) ? c_csv_wgt_hf[iSysC][iPt]->FindBin(csv) : 1;
            double iCSVWgtC =
                c_csv_wgt_hf[iSysC][iPt]->GetBinContent(useCSVBin);
            if (iCSVWgtC != 0)
                csvWgtC *= iCSVWgtC;
        } else {
            if (iPt >= 3)
                iPt =
                    3; /// [30-40], [40-60] and [60-10000] only 3 Pt bins for lf
            int useCSVBin =
                (csv >= 0.) ? h_csv_wgt_lf[iSysLF][iPt][iEta]->FindBin(csv) : 1;
            double iCSVWgtLF =
                h_csv_wgt_lf[iSysLF][iPt][iEta]->GetBinContent(useCSVBin);
            if (iCSVWgtLF != 0)
                csvWgtlf *= iCSVWgtLF;
        }
    }

    double csvWgtTotal = csvWgthf * csvWgtC * csvWgtlf;

    csvWgtHF = csvWgthf;
    csvWgtLF = csvWgtlf;
    csvWgtCF = csvWgtC;

    return csvWgtTotal;
}

inline void CU_ttH_EDA::Getbweight_csv(CU_ttH_EDA_event_vars &local)
{
    int i = -1;
	for (std::vector<pat::Jet>::const_iterator iJet = local.jets_selected_uncorrected.begin();iJet != local.jets_selected_uncorrected.end(); ++iJet){
        i++;
		double csv_sf = 1.0;
		double pt = iJet->pt() * local.jet_jecSF_nominal[i] * local.jet_jerSF_jesnominal_nominal[i];
		double eta = fabs(iJet->eta());
		double csv = miniAODhelper.GetJetCSV(*iJet, "pfDeepCSVJetTags:probb") + miniAODhelper.GetJetCSV(*iJet, "pfDeepCSVJetTags:probbb");
		if (!isdata && pt>=20){
			if (pt > 1000)
				pt = 1000.0;
			if (iJet->hadronFlavour() == 5)
				csv_sf = btag_reader->eval_auto_bounds("central", BTagEntry::FLAV_B, eta, pt, csv);
			else if (iJet->hadronFlavour() == 4)
				csv_sf = btag_reader->eval_auto_bounds("central", BTagEntry::FLAV_C, eta, pt, csv);
			else
				csv_sf = btag_reader->eval_auto_bounds("central", BTagEntry::FLAV_UDSG, eta, pt, csv);
		}
		local.b_weight_jesnominal_nominal.push_back(csv_sf);
	}
}

inline void CU_ttH_EDA::Getbweight(CU_ttH_EDA_event_vars &local)
{
    int i = -1;
    std::vector<double> bweight_jesup[26];
    std::vector<double> bweight_jesdown[26];
    for(int j=0; j<26; j++){
        bweight_jesup[j].clear();
        bweight_jesdown[j].clear();
    }

    for (std::vector<pat::Jet>::const_iterator iJet = local.jets_selected_uncorrected.begin();
        iJet != local.jets_selected_uncorrected.end(); ++iJet){

        i++;
        if (isdata){
            local.b_weight_jesnominal_nominal.push_back(1.0);
            local.b_weight_jesnominal_hfup.push_back(1.0);
            local.b_weight_jesnominal_hfdown.push_back(1.0);
            local.b_weight_jesnominal_hfstats1up.push_back(1.0);
            local.b_weight_jesnominal_hfstats1down.push_back(1.0);
            local.b_weight_jesnominal_hfstats2up.push_back(1.0);
            local.b_weight_jesnominal_hfstats2down.push_back(1.0);
            local.b_weight_jesnominal_lfup.push_back(1.0);
            local.b_weight_jesnominal_lfdown.push_back(1.0);
            local.b_weight_jesnominal_lfstats1up.push_back(1.0);
            local.b_weight_jesnominal_lfstats1down.push_back(1.0);
            local.b_weight_jesnominal_lfstats2up.push_back(1.0);
            local.b_weight_jesnominal_lfstats2down.push_back(1.0);
            local.b_weight_jesnominal_cferr1up.push_back(1.0);
            local.b_weight_jesnominal_cferr1down.push_back(1.0);
            local.b_weight_jesnominal_cferr2up.push_back(1.0);
            local.b_weight_jesnominal_cferr2down.push_back(1.0);
            for(int j=0; j<26; j++){
                bweight_jesup[j].push_back(1.0);
                bweight_jesdown[j].push_back(1.0);
            }
			local.b_weight_jerup_nominal.push_back(1.0);
			local.b_weight_jerdown_nominal.push_back(1.0);
            continue;
        }

        double csvWgtHF, csvWgtLF, csvWgtCF;
        std::vector<double> jet_pt_corr;
        std::vector<double> jet_eta;
        std::vector<double> jet_csv;
        std::vector<int> jet_flav;
        jet_pt_corr.clear();
        jet_eta.clear();
        jet_csv.clear();
        jet_flav.clear();

        double jet_pt_uncorr = iJet->pt();
        jet_eta.push_back(iJet->eta());
        jet_csv.push_back(miniAODhelper.GetJetCSV(*iJet, "pfDeepCSVJetTags:probb") + miniAODhelper.GetJetCSV(*iJet, "pfDeepCSVJetTags:probbb"));
        jet_flav.push_back(iJet->hadronFlavour());

		jet_pt_corr.push_back(jet_pt_uncorr * local.jet_jecSF_nominal[i] * local.jet_jerSF_jesnominal_nominal[i]);

        if(jet_pt_corr[0]>20){
            local.b_weight_jesnominal_nominal.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 0, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_hfup.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 11, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_hfdown.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 12, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_hfstats1up.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 13, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_hfstats1down.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 14, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_hfstats2up.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 15, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_hfstats2down.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 16, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_lfup.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 9, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_lfdown.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 10, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_lfstats1up.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 17, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_lfstats1down.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 18, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_lfstats2up.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 19, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_lfstats2down.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 20, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_cferr1up.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 21, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_cferr1down.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 22, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_cferr2up.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 23, csvWgtHF, csvWgtLF, csvWgtCF));
            local.b_weight_jesnominal_cferr2down.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 24, csvWgtHF, csvWgtLF, csvWgtCF));
        }
        else{
            local.b_weight_jesnominal_nominal.push_back(1.0);
            local.b_weight_jesnominal_hfup.push_back(1.0);
            local.b_weight_jesnominal_hfdown.push_back(1.0);
            local.b_weight_jesnominal_hfstats1up.push_back(1.0);
            local.b_weight_jesnominal_hfstats1down.push_back(1.0);
            local.b_weight_jesnominal_hfstats2up.push_back(1.0);
            local.b_weight_jesnominal_hfstats2down.push_back(1.0);
            local.b_weight_jesnominal_lfup.push_back(1.0);
            local.b_weight_jesnominal_lfdown.push_back(1.0);
            local.b_weight_jesnominal_lfstats1up.push_back(1.0);
            local.b_weight_jesnominal_lfstats1down.push_back(1.0);
            local.b_weight_jesnominal_lfstats2up.push_back(1.0);
            local.b_weight_jesnominal_lfstats2down.push_back(1.0);
            local.b_weight_jesnominal_cferr1up.push_back(1.0);
            local.b_weight_jesnominal_cferr1down.push_back(1.0);
            local.b_weight_jesnominal_cferr2up.push_back(1.0);
            local.b_weight_jesnominal_cferr2down.push_back(1.0);
        }
        jet_pt_corr.clear();

        for(int j=0; j<26; j++){
			jet_pt_corr.push_back(jet_pt_uncorr * local.jet_jecSF_nominal[i] * local.jet_jesSF_up[j][i] * local.jet_jerSF_jesup_nominal[j][i]);
			if(jet_pt_corr[0]>20){
				if( j!=1 && j!=2 && j!=4 && j!=5 && j!=6 && j!=7 && j!=16 && j!=20 && j!=21 && j!=22 && j!=23 )
					bweight_jesup[j].push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 0, csvWgtHF, csvWgtLF, csvWgtCF));
				else
					bweight_jesup[j].push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, (200+j), csvWgtHF, csvWgtLF, csvWgtCF));
			}
			else
				bweight_jesup[j].push_back(1.0);
			jet_pt_corr.clear();
			jet_pt_corr.push_back(jet_pt_uncorr * local.jet_jecSF_nominal[i] * local.jet_jesSF_down[j][i] * local.jet_jerSF_jesdown_nominal[j][i]);
			if(jet_pt_corr[0]>20){
				if( j!=1 && j!=2 && j!=4 && j!=5 && j!=6 && j!=7 && j!=16 && j!=20 && j!=21 && j!=22 && j!=23 )
					bweight_jesdown[j].push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 0, csvWgtHF, csvWgtLF, csvWgtCF));
				else
					bweight_jesdown[j].push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, (100+j), csvWgtHF, csvWgtLF, csvWgtCF));
			}
			else
				bweight_jesdown[j].push_back(1.0);
			jet_pt_corr.clear();
        }

		jet_pt_corr.push_back(jet_pt_uncorr * local.jet_jecSF_nominal[i] * local.jet_jerSF_jesnominal_up[i]);
		if(jet_pt_corr[0]>20)
			local.b_weight_jerup_nominal.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 0, csvWgtHF, csvWgtLF, csvWgtCF));
		else
			local.b_weight_jerup_nominal.push_back(1.0);
		jet_pt_corr.clear();
		jet_pt_corr.push_back(jet_pt_uncorr * local.jet_jecSF_nominal[i] * local.jet_jerSF_jesnominal_down[i]);
		if(jet_pt_corr[0]>20)
			local.b_weight_jerdown_nominal.push_back(GetCSVWeight(jet_pt_corr, jet_eta, jet_csv, jet_flav, 0, csvWgtHF, csvWgtLF, csvWgtCF));
		else
			local.b_weight_jerdown_nominal.push_back(1.0);
		jet_pt_corr.clear();
    }

    for(int j=0; j<26; j++){
        local.b_weight_jesup_nominal.push_back(bweight_jesup[j]);
        local.b_weight_jesdown_nominal.push_back(bweight_jesdown[j]);
    }
}

inline void
CU_ttH_EDA::GetPDFweight(CU_ttH_EDA_event_vars &local,
                         const edm::Handle<GenEventInfoProduct> &genInfos)
{

    auto pdfInfos = genInfos->pdf();
    double pdfNominal = pdfInfos->xPDF.first * pdfInfos->xPDF.second;

    std::vector<double> pdfs;
    for (size_t j = 0; j < pdfSet->size(); ++j) {
        double xpdf1 = _systPDFs[j]->xfxQ(pdfInfos->id.first, pdfInfos->x.first,
                                          pdfInfos->scalePDF);
        double xpdf2 = _systPDFs[j]->xfxQ(
            pdfInfos->id.second, pdfInfos->x.second, pdfInfos->scalePDF);
        pdfs.push_back(xpdf1 * xpdf2);
    }

    const LHAPDF::PDFUncertainty pdfUnc = pdfSet->uncertainty(pdfs, 68.);

    double weight_up = 1.0;
    double weight_down = 1.0;
    if (std::isfinite(1. / pdfNominal)) {
        weight_up = (pdfUnc.central + pdfUnc.errplus) / pdfNominal;
        weight_down = (pdfUnc.central - pdfUnc.errminus) / pdfNominal;
    }
    local.pdf_weight_up = weight_up;
    local.pdf_weight_down = weight_down;
}
/*
inline void CU_ttH_EDA::Set_bjetness_input(
    CU_ttH_EDA_event_vars &local,
    const edm::Handle<reco::VertexCollection> &vertices)
{
    local.PV = *vertices->begin();
    std::vector<pat::Jet> jets;
    pat::Jet temp_jet;
    double n_jets = 0;
    double n_max;

    jets = local.jets_selected_uncorrected;
    n_jets = (int)local.jets_selected_uncorrected.size();

    for (int i = 0; i < n_jets; i++) {
        for (int j = (n_jets - 1); j > i; j--) {
            if ((miniAODhelper.GetJetCSV(jets[j], "pfDeepCSVJetTags:probb") + miniAODhelper.GetJetCSV(jets[j], "pfDeepCSVJetTags:probbb")) >
                ((miniAODhelper.GetJetCSV(jets[j-1], "pfDeepCSVJetTags:probb") + miniAODhelper.GetJetCSV(jets[j-1], "pfDeepCSVJetTags:probbb")))) {
                temp_jet = jets[j - 1];
                jets[j - 1] = jets[j];
                jets[j] = temp_jet;
            }
        }
    }

    if (n_jets > 6)
        n_max = 6;
    else
        n_max = n_jets;

    for (int k = 1; k < n_max; k++)
        local.jets_inp_bjetness.push_back(jets[k]);
}

inline vector<reco::TransientTrack>
CU_ttH_EDA::Get_ttrks(vector<reco::Track> trks,
                      const TransientTrackBuilder &ttrkbuilder)
{
    vector<reco::TransientTrack> ttrks;
    for (uint tr = 0; tr < trks.size(); tr++) {
        reco::TransientTrack ttrk = ttrkbuilder.build(&trks[tr]);
        ttrks.push_back(ttrk);
    }
    return ttrks;
}

inline bool CU_ttH_EDA::Is_goodtrk(reco::Track trk, const reco::Vertex &vtx)
{
    bool isgoodtrk = false;
    if (trk.pt() > 1 && trk.hitPattern().numberOfValidHits() >= 8 &&
        trk.hitPattern().numberOfValidPixelHits() >= 2 &&
        trk.normalizedChi2() < 5 && std::abs(trk.dxy(vtx.position())) < 0.2 &&
        std::abs(trk.dz(vtx.position())) < 17)
        isgoodtrk = true;

    return isgoodtrk;
}

inline bool
CU_ttH_EDA::Is_loosePOG_jetmuon(const pat::PackedCandidate &jcand,
                                edm::Handle<edm::View<pat::Muon>> muon_h)
{
    bool ismu = false;
    for (const pat::Muon &mu : *muon_h) {
        if (deltaR(jcand.p4(), mu.p4()) < 0.1 &&
            fabs(jcand.pt() - mu.pt()) / mu.pt() < 0.05) {
            if (mu.isLooseMuon())
                ismu = true;
            if (ismu)
                break;
        }
    }
    return ismu;
}

inline bool CU_ttH_EDA::Is_softLep_jetelectron(
    const pat::PackedCandidate &jcand,
    edm::Handle<edm::View<pat::Electron>> electron_pat, const reco::Vertex &vtx)
{
    bool isele = false;
    for (edm::View<pat::Electron>::const_iterator ele = electron_pat->begin();
         ele != electron_pat->end(); ele++) {
        const pat::Electron &lele = *ele;
        if (deltaR(jcand.p4(), lele.p4()) < 0.1 &&
            fabs(jcand.pt() - lele.pt()) / lele.pt() < 0.05) {
            const reco::HitPattern &hitPattern =
                lele.gsfTrack().get()->hitPattern();
            uint32_t hit =
                hitPattern.getHitPattern(reco::HitPattern::TRACK_HITS, 0);
            bool hitCondition =
                !(reco::HitPattern::validHitFilter(hit) &&
                  ((reco::HitPattern::pixelBarrelHitFilter(hit) &&
                    reco::HitPattern::getLayer(hit) < 3) ||
                   reco::HitPattern::pixelEndcapHitFilter(hit)));
            if (!hitCondition && lele.passConversionVeto())
                isele = true;
            if (isele)
                break;
        }
    }
    return isele;
}

inline void CU_ttH_EDA::Get_bjetness_trkinfos(
    vector<pat::Jet> evtjets, const reco::Vertex &vtx,
    vector<reco::Track> &jetchtrks, double &bjetness_num_pvtrks,
    double &bjetness_num_npvtrks,
    edm::Handle<edm::View<pat::Electron>> electron_pat,
    edm::Handle<edm::View<pat::Muon>> muon_h, double &bjetness_num_eles,
    double &bjetness_num_mus, vector<tuple<double, double, double>> &jetsdir)
{
    // Loop over evt jet
    for (uint j = 0; j < evtjets.size(); j++) {
        pat::Jet jet = evtjets[j];
        // Access jet daughters
        vector<reco::CandidatePtr> jdaus(jet.daughterPtrVector());
        sort(jdaus.begin(), jdaus.end(),
             [](const reco::CandidatePtr &p1, const reco::CandidatePtr &p2) {
                 return p1->pt() > p2->pt();
             });
        for (uint jd = 0; jd < jdaus.size(); jd++) {
            const pat::PackedCandidate &jcand =
                dynamic_cast<const pat::PackedCandidate &>(*jdaus[jd]);
            // dR requirement
            if (deltaR(jcand.p4(), jet.p4()) > 0.4)
                continue;
            reco::Track trk = reco::Track(jcand.pseudoTrack());
            bool isgoodtrk = Is_goodtrk(trk, vtx);
            // Minimal conditions for a BJetness jet constituent
            if (isgoodtrk && jcand.charge() != 0 && jcand.fromPV() > 1) {
                jetchtrks.push_back(trk);
                if (jcand.fromPV() == 3)
                    bjetness_num_pvtrks++;
                if (jcand.fromPV() == 2)
                    bjetness_num_npvtrks++;
                jetsdir.push_back(make_tuple(jet.px(), jet.py(), jet.pz()));
                if (fabs(jcand.pdgId()) == 13 &&
                    Is_loosePOG_jetmuon(jcand, muon_h))
                    bjetness_num_mus++;
                if (fabs(jcand.pdgId()) == 11 &&
                    Is_softLep_jetelectron(jcand, electron_pat, vtx))
                    bjetness_num_eles++;
                // if(fabs(jcand.pdgId())==11 &&
                // is_loosePOGNoIPNoIso_jetelectron(jcand,electron_pat,vtx))
                // bjetness_num_eles++;
            } // Ch trks
        }     // Loop on jet daus
    }         // Loop on evt jet
}

inline void CU_ttH_EDA::Get_avip3d(
    vector<reco::Track> trks, const TransientTrackBuilder &ttrkbuilder,
    reco::Vertex vtx, vector<tuple<double, double, double>> &jetsdir,
    double &jetchtrks_avip3d_val, double &jetchtrks_avip3d_sig,
    double &jetchtrks_avsip3d_sig)
{
    double valtemp = 0;
    vector<reco::TransientTrack> ttrks = Get_ttrks(trks, ttrkbuilder);
    for (uint t = 0; t < ttrks.size(); t++) {
        valtemp =
            IPTools::absoluteImpactParameter3D(ttrks[t], vtx).second.value();
        if (valtemp == valtemp)
            jetchtrks_avip3d_val += valtemp;
        valtemp = IPTools::absoluteImpactParameter3D(ttrks[t], vtx)
                      .second.significance();
        if (valtemp == valtemp)
            jetchtrks_avip3d_sig += valtemp;
        GlobalVector jetsdirgv(get<0>(jetsdir[t]), get<1>(jetsdir[t]),
                               get<2>(jetsdir[t]));
        valtemp = IPTools::signedImpactParameter3D(ttrks[t], jetsdirgv, vtx)
                      .second.significance();
        if (valtemp == valtemp)
            jetchtrks_avsip3d_sig += valtemp;
    }
}

inline void CU_ttH_EDA::Get_avip1d(
    vector<reco::Track> trks, const TransientTrackBuilder &ttrkbuilder,
    reco::Vertex vtx, vector<tuple<double, double, double>> &jetsdir,
    double &jetchtrks_avip1d_sig)
{
    double valtemp = 0;
    vector<reco::TransientTrack> ttrks = Get_ttrks(trks, ttrkbuilder);
    SignedTransverseImpactParameter stip;
    for (uint t = 0; t < ttrks.size(); t++) {
        GlobalVector jetsdirgv(get<0>(jetsdir[t]), get<1>(jetsdir[t]),
                               get<2>(jetsdir[t]));
        valtemp = fabs(stip.zImpactParameter(ttrks[t], jetsdirgv, vtx)
                           .second.significance());
        if (valtemp == valtemp)
            jetchtrks_avip1d_sig += valtemp;
    }
}

inline void CU_ttH_EDA::Get_bjetness_vars(
    vector<pat::Jet> evtjets, const reco::Vertex &vtx,
    const TransientTrackBuilder &ttrkbuilder,
    edm::Handle<edm::View<pat::Electron>> electron_pat,
    edm::Handle<edm::View<pat::Muon>> muon_h, double &bjetnessFV_num_leps,
    double &bjetnessFV_npvTrkOVcollTrk, double &bjetnessFV_avip3d_val,
    double &bjetnessFV_avip3d_sig, double &bjetnessFV_avsip3d_sig,
    double &bjetnessFV_avip1d_sig)
{
    // Get BJetness trk info
    vector<reco::Track> jetschtrks;
    jetschtrks.clear();
    double num_pvtrks = 0;
    double num_npvtrks = 0;
    double num_eles = 0;
    double num_mus = 0;
    vector<tuple<double, double, double>> jetsdir;
    jetsdir.clear();

    Get_bjetness_trkinfos(evtjets, vtx, jetschtrks, num_pvtrks, num_npvtrks,
                          electron_pat, muon_h, num_eles, num_mus, jetsdir);

    bjetnessFV_num_leps = num_eles + num_mus;
    if (jetschtrks.size() != 0) {
        bjetnessFV_npvTrkOVcollTrk = num_npvtrks / double(jetschtrks.size());
        // Get BJetness Impact Parameters
        double ip_valtemp = 0;
        // 3D
        double jetchtrks_avip3d_val = 0;
        double jetchtrks_avip3d_sig = 0;
        double jetchtrks_avsip3d_sig = 0;

        Get_avip3d(jetschtrks, ttrkbuilder, vtx, jetsdir, jetchtrks_avip3d_val,
                   jetchtrks_avip3d_sig, jetchtrks_avsip3d_sig);
        ip_valtemp = jetchtrks_avip3d_val / jetschtrks.size();
        if (ip_valtemp == ip_valtemp)
            bjetnessFV_avip3d_val = ip_valtemp;
        else
            bjetnessFV_avip3d_val = -996;
        ip_valtemp = jetchtrks_avip3d_sig / jetschtrks.size();
        if (ip_valtemp == ip_valtemp)
            bjetnessFV_avip3d_sig = ip_valtemp;
        else
            bjetnessFV_avip3d_sig = -996;
        ip_valtemp = jetchtrks_avsip3d_sig / jetschtrks.size();
        if (ip_valtemp == ip_valtemp)
            bjetnessFV_avsip3d_sig = ip_valtemp;
        else
            bjetnessFV_avsip3d_sig = -996;
        // 1D
        double jetchtrks_avip1d_sig = 0;
        Get_avip1d(jetschtrks, ttrkbuilder, vtx, jetsdir, jetchtrks_avip1d_sig);
        ip_valtemp = jetchtrks_avip1d_sig / jetschtrks.size();
        if (ip_valtemp == ip_valtemp)
            bjetnessFV_avip1d_sig = ip_valtemp;
        else
            bjetnessFV_avip1d_sig = -996;
    } else {
        bjetnessFV_npvTrkOVcollTrk = -998;
        bjetnessFV_avip3d_val = -998;
        bjetnessFV_avip3d_sig = -998;
        bjetnessFV_avsip3d_sig = -998;
        bjetnessFV_avip1d_sig = -998;
    }
}
*/
#endif
