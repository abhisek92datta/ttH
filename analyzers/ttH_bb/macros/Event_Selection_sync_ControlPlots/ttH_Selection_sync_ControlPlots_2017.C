#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TH3.h"
#include "TH2F.h"
#include "TF1.h"
#include "TF2.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include "TAxis.h"
#include "TMath.h"
#include "TRandom3.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <exception>
#include <cmath> 
#include <iomanip>
#include <fstream>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "TGraphAsymmErrors.h"
#include "TVector.h"
#include "TVector2.h"
#include "TLorentzVector.h"

#if !defined(__CINT__) && !defined(__MAKECINT__)
#include "CU_ttH_EDA_Ntuple.h"
#endif

typedef std::vector< TLorentzVector >          vecTLorentzVector;
typedef std::vector<int>                       vint;
typedef std::vector<unsigned int>              vuint;
typedef std::vector<double>                    vdouble;
typedef std::vector<std::vector<double> >      vvdouble;
typedef std::vector<std::vector<int> >         vvint;

double dR_calc( double eta1, double phi1, double eta2, double phi2){

    double deta = eta1 - eta2;
    double dphi = TVector2::Phi_mpi_pi(phi1 - phi2);
    double dR = sqrt(deta*deta + dphi*dphi);
    return dR;
}

double dilepton_invariant_mass( double E1, double pt1, double eta1, double phi1, double E2, double pt2, double eta2, double phi2 ){
    TLorentzVector lv1;
    lv1.SetPtEtaPhiE(pt1,eta1,phi1,E1);
    TLorentzVector lv2;
    lv2.SetPtEtaPhiE(pt2,eta2,phi2,E2);
    TLorentzVector lv = lv1 + lv2;
    return lv.M();
}

int reco_hlt_dR_match( double reco_eta, double reco_phi, std::vector<double> hlt_eta, std::vector<double> hlt_phi, double dR_cut ){

    double dR_min = 9999;
    int match_index = -1;

    for(unsigned int i=0; i<hlt_eta.size(); i++){
        double dR = dR_calc(reco_eta, reco_phi, hlt_eta[i], hlt_phi[i]);
        if(dR < dR_cut){
            if(dR < dR_min){
                match_index = i;
                dR_min = dR;
            }
        }
    }
    std::cout<<dR_min<<"  "<<match_index<<"\n";
    return match_index;
}

int check_filter_label( std::vector<string> filter_label_list , string filter ){

    int filter_match = 0;
    for(unsigned int i=0; i<filter_label_list.size(); i++){
        if( filter_label_list[i].compare(filter) == 0 ){
            filter_match = 1;
            break;
        }
    }
    return filter_match;
}

void ttH_Selection_sync_ControlPlots_2017( int maxNentries=-1, int Njobs=1, int jobN=1 ) {

    // Reading from input file

    ifstream fin;
    ofstream fout;
    FILE *file_sync;
    std::string data_mc;
    std::string sample_dataset;
    int n_input_files;
    std::string file;
    std::string process;
    std::string jet_sys;
    double xs;
    std::vector<std::string> treefilenames;
    std::string output_hist_filename;
    std::string output_yields_filename;
    std::string sync_filename;
    int is_data_input = 0;
    int dataset_index = 0;

    fin.open("input.txt");
    fin>>data_mc;
    fin>>sample_dataset;
    fin>>process;
    fin>>jet_sys;
    fin>>n_input_files;
    for(int i=0; i<n_input_files; i++){
        fin>>file;
        treefilenames.push_back(file);
    }
    fin>>xs;
    fin.close();

    // Setting up output files

    output_hist_filename = ("ttH_Selection_ControlPlots_"+ data_mc + "_" + sample_dataset + "_" + process + "_" + jet_sys + ".root").c_str();
    output_yields_filename = ("output_" + data_mc + "_" + sample_dataset + "_" + process + "_" + jet_sys + "_yields.txt").c_str();
    sync_filename = ("Cornell_" + data_mc + "_" + sample_dataset + ".csv").c_str();
    fout.open(output_yields_filename);
    char* sync_filename_char = new char[sync_filename.length() + 1];
    std::strcpy(sync_filename_char, sync_filename.c_str());
    file_sync = std::fopen(sync_filename_char, "w");
 fprintf(file_sync,"run,lumi,event,is_e,is_mu,is_ee,is_emu,is_mumu,n_jets,n_btags,lep1_pt,lep1_eta,lep1_iso,lep1_pdgId,lep1_idSF,lep1_isoSF,lep2_pt,lep2_eta,lep2_iso,lep2_pdgId,lep2_idSF,lep2_isoSF,jet1_pt,jet1_eta,jet1_phi,jet1_jesSF,jet1_jesSF_up,jet1_jesSF_down,jet1_jesSF_PileUpDataMC_down,jet1_jesSF_RelativeFSR_up,jet1_jerSF_nominal,jet1_csv,jet1_PUJetId,jet1_PUJetDiscriminant,jet2_pt,jet2_eta,jet2_phi,jet2_jesSF,jet2_jesSF_up,jet2_jesSF_down,jet2_jesSF_PileUpDataMC_down,jet2_jesSF_RelativeFSR_up,jet2_jerSF_nominal,jet2_csv,jet2_PUJetId,jet2_PUJetDiscriminant,MET_pt,MET_phi,mll,ttHFCategory,ttHFGenFilterTag,n_interactions,puWeight,csvSF,csvSF_lf_up,csvSF_hf_down,csvSF_cErr1_down,pdf_up,pdf_down,me_up,me_down,triggerSF,top_pt_weight,bdt_output,dnn_ttH_output,dnn_ttbb_output,isSLIsoFlip,isSLMETFlip,isSLQCDRegion\n");

    if (data_mc.find("mc")!=std::string::npos)
        is_data_input = 0;
    else if (data_mc.find("data")!=std::string::npos){
        is_data_input = 1;
        if (sample_dataset.find("se")!=std::string::npos)
            dataset_index = 1;
        else if (sample_dataset.find("sm")!=std::string::npos)
            dataset_index = 2;
        else if (sample_dataset.find("de")!=std::string::npos)
            dataset_index = 3;
        else if (sample_dataset.find("em")!=std::string::npos)
            dataset_index = 4;
        else if (sample_dataset.find("dm")!=std::string::npos)
            dataset_index = 5;
    }

    // ttH Selection Cuts

    double min_sl_ele_pt = 30.0;
    double min_sl_mu_pt = 26.0;
    double min_sl_veto_ele_pt = 15.0;
    double min_sl_veto_mu_pt = 15.0;
    double max_sl_ele_eta = 2.1;
    double max_sl_mu_eta = 2.1;
    double max_sl_veto_ele_eta = 2.4;
    double max_sl_veto_mu_eta = 2.4;

    double min_di_ele1_pt = 25.0;
    double min_di_ele2_pt = 15.0;
    double min_di_mu1_pt = 25.0;
    double min_di_mu2_pt = 15.0;
    double max_di_ele1_eta = 2.4;
    double max_di_ele2_eta = 2.4;
    double max_di_mu1_eta = 2.4;
    double max_di_mu2_eta = 2.4;

    double max_mu_loose_iso = 0.25;
    double max_mu_tight_iso = 0.15;

    double min_jet_pt = 30.0;
    double min_jet2_pt = 20.0;
    double max_jet_eta = 2.4;

    double min_sl_njets = 4;
    double min_di_njets = 2;
    double min_sl_nbtags = 2;
    double min_di_nbtags = 1;

    double min_di_mll = 20.0;
    double min_sl_met = 20.0;
    double min_di_met = 40.0;

    int min_pujetid_sl = 4;
    int min_pujetid_di = 7;
    double jet_csv_med_cut = 0.4941;
    double lep_jet_min_dR = 0.4;

    // Initializing counters

    int N_total = 0;
    int N_basic_sel = 0;
    double sum_pos_gen_weights = 0;
    double sum_neg_gen_weights = 0;
    double sum_gen_weights = 0;
    double prod_gen_weights = 1;
    double sum_gen_PU_weights = 0;
    double sum_gen_PU_up_weights = 0;
    double sum_gen_PU_down_weights = 0;

    int N_sel_raw = 0;
    int N_SL_raw = 0;
    int N_DL_raw = 0;
    int N_e_raw = 0;
    int N_mu_raw = 0;
    int N_ee_raw = 0;
    int N_emu_raw = 0;
    int N_mumu_raw = 0;

    int N_SL_4j3b_raw = 0;
    int N_SL_4j4b_raw = 0;
    int N_SL_5j3b_raw = 0;
    int N_SL_5j4b_raw = 0;
    int N_SL_6j2b_raw = 0;
    int N_SL_6j3b_raw = 0;
    int N_SL_6j4b_raw = 0;
    int N_DL_3j2b_raw = 0;
    int N_DL_3j3b_raw = 0;
    int N_DL_4j2b_raw = 0;
    int N_DL_4j3b_raw = 0;
    int N_DL_4j4b_raw = 0;

    // Weighted Yields

    double N_sel = 0;
    double N_SL = 0;
    double N_DL = 0;
    double N_e = 0;
    double N_mu = 0;
    double N_ee = 0;
    double N_emu = 0;
    double N_mumu = 0;

    double N_SL_4j3b = 0;
    double N_SL_4j4b = 0;
    double N_SL_5j3b = 0;
    double N_SL_5j4b = 0;
    double N_SL_6j2b = 0;
    double N_SL_6j3b = 0;
    double N_SL_6j4b = 0;
    double N_DL_3j2b = 0;
    double N_DL_3j3b = 0;
    double N_DL_4j2b = 0;
    double N_DL_4j3b = 0;
    double N_DL_4j4b = 0;

    double N_SL_genweighted = 0;
    double N_DL_genweighted = 0;
    double N_e_genweighted = 0;
    double N_mu_genweighted = 0;
    double N_ee_genweighted = 0;
    double N_emu_genweighted = 0;
    double N_mumu_genweighted = 0;

    double N_SL_4j3b_genweighted = 0;
    double N_SL_4j4b_genweighted = 0;
    double N_SL_5j3b_genweighted = 0;
    double N_SL_5j4b_genweighted = 0;
    double N_SL_6j2b_genweighted = 0;
    double N_SL_6j3b_genweighted = 0;
    double N_SL_6j4b_genweighted = 0;
    double N_DL_3j2b_genweighted = 0;
    double N_DL_3j3b_genweighted = 0;
    double N_DL_4j2b_genweighted = 0;
    double N_DL_4j3b_genweighted = 0;
    double N_DL_4j4b_genweighted = 0;

    // Weighted Yields L

    double L = 35.92; // 1/fb
    double lumi_norm = 0;
    double lumi_norm_genweighted = 0;

    double N_sel_norm = 0;
    double N_SL_norm = 0;
    double N_DL_norm = 0;
    double N_e_norm = 0;
    double N_mu_norm = 0;
    double N_ee_norm = 0;
    double N_emu_norm = 0;
    double N_mumu_norm = 0;

    double N_SL_4j3b_norm = 0;
    double N_SL_4j4b_norm = 0;
    double N_SL_5j3b_norm = 0;
    double N_SL_5j4b_norm = 0;
    double N_SL_6j2b_norm = 0;
    double N_SL_6j3b_norm = 0;
    double N_SL_6j4b_norm = 0;
    double N_DL_3j2b_norm = 0;
    double N_DL_3j3b_norm = 0;
    double N_DL_4j2b_norm = 0;
    double N_DL_4j3b_norm = 0;
    double N_DL_4j4b_norm = 0;

    double N_SL_genweighted_norm = 0;
    double N_DL_genweighted_norm = 0;
    double N_e_genweighted_norm = 0;
    double N_mu_genweighted_norm = 0;
    double N_ee_genweighted_norm = 0;
    double N_emu_genweighted_norm = 0;
    double N_mumu_genweighted_norm = 0;

    double N_SL_4j3b_genweighted_norm = 0;
    double N_SL_4j4b_genweighted_norm = 0;
    double N_SL_5j3b_genweighted_norm = 0;
    double N_SL_5j4b_genweighted_norm = 0;
    double N_SL_6j2b_genweighted_norm = 0;
    double N_SL_6j3b_genweighted_norm = 0;
    double N_SL_6j4b_genweighted_norm = 0;
    double N_DL_3j2b_genweighted_norm = 0;
    double N_DL_3j3b_genweighted_norm = 0;
    double N_DL_4j2b_genweighted_norm = 0;
    double N_DL_4j3b_genweighted_norm = 0;
    double N_DL_4j4b_genweighted_norm = 0;

    // Setting output file and input Trees

    std::string histofilename = output_hist_filename;

    TChain *reco_chain = new TChain("ttHbb/recoTree");
    TChain *gen_chain = new TChain("ttHbb/genTree");
    TChain *comm_chain = new TChain("ttHbb/commTree");

    for(int i=0; i<n_input_files; i++){
        reco_chain->Add(treefilenames[i].c_str());
        if(is_data_input==0){
            gen_chain->Add(treefilenames[i].c_str());
            comm_chain->Add(treefilenames[i].c_str());
        }
    }

    TFile histofile(histofilename.c_str(),"recreate");
    histofile.cd();

    // Setting up Histograms for Control Plots
    
    TH1::SetDefaultSumw2();

    // Single Electron Histograms
    TH1D* pt_e1_sl_e = new TH1D("pt_e1_sl_e","Leading Electron pT Distribution (Single Electron) ;Leading Electron pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_e1_sl_e = new TH1D("eta_e1_sl_e","Leading Electron eta Distribution (Single Electron) ;Leading Electron #eta; Nr. of Events",15,-3,3);
    TH1D* phi_e1_sl_e = new TH1D("phi_e1_sl_e","Leading Electron phi Distribution (Single Electron) ;Leading Electron #phi; Nr. of Events",10,-3,3);
    TH1D* pt_jet1_sl_e = new TH1D("pt_jet1_sl_e","Leading Jet pT Distribution (Single Electron) ;Jet 1 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet2_sl_e = new TH1D("pt_jet2_sl_e","2nd Leading Jet pT Distribution (Single Electron) ;Jet 2 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet3_sl_e = new TH1D("pt_jet3_sl_e","3rd Leading Jet pT Distribution (Single Electron) ;Jet 3 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet4_sl_e = new TH1D("pt_jet4_sl_e","4th Leading Jet pT Distribution (Single Electron) ;Jet 4 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet5_sl_e = new TH1D("pt_jet5_sl_e","5th Leading Jet pT Distribution (Single Electron) ;Jet 5 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet6_sl_e = new TH1D("pt_jet6_sl_e","6th Leading Jet pT Distribution (Single Electron) ;Jet 6 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet_all_sl_e = new TH1D("pt_jet_all_sl_e","Jet (all) pT Distribution (Single Electron) ;Jet pT (GeV);Nr. of Events",50,0,300);
    TH1D* csv_jet_all_sl_e = new TH1D("csv_jet_all_sl_e","Jet (all) CSV Distribution (Single Electron) ;Jet CSV (GeV);Nr. of Events",50,0,1);
    TH1D* ht_sl_e = new TH1D("ht_sl_e","HT Distribution (Single Electron) ;HT (GeV);Nr. of Events",50,0,1000);
    TH1D* njets_sl_e = new TH1D("njets_sl_e","Jet Multiplicity (Single Electron) ;Nr. of jets; Nr. of Events",15,0,15);
    TH1D* nbtags_sl_e = new TH1D("nbtags_sl_e","B-jet Multiplicity (Single Electron) ;Nr. of b-jets; Nr. of Events",8,0,8);
    TH1D* npv_sl_e = new TH1D("npv_sl_e","Nr. of Primary Vertices (Single Electron)  ;NPV; Nr. of Events",20,0,75);

    TH1D* pt_e1_sl_e_genweighted = new TH1D("pt_e1_sl_e_genweighted","Gen_Weighted Leading Electron pT Distribution (Single Electron) ;Leading Electron pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_e1_sl_e_genweighted = new TH1D("eta_e1_sl_e_genweighted","Gen_Weighted Leading Electron eta Distribution (Single Electron) ;Leading Electron #eta; Nr. of Events",15,-3,3);
    TH1D* phi_e1_sl_e_genweighted = new TH1D("phi_e1_sl_e_genweighted","Gen_Weighted Leading Electron phi Distribution (Single Electron) ;Leading Electron #phi; Nr. of Events",10,-3,3);
    TH1D* pt_jet1_sl_e_genweighted = new TH1D("pt_jet1_sl_e_genweighted","Gen_Weighted Leading Jet pT Distribution (Single Electron) ;Jet 1 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet2_sl_e_genweighted = new TH1D("pt_jet2_sl_e_genweighted","Gen_Weighted 2nd Leading Jet pT Distribution (Single Electron) ;Jet 2 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet3_sl_e_genweighted = new TH1D("pt_jet3_sl_e_genweighted","Gen_Weighted 3rd Leading Jet pT Distribution (Single Electron) ;Jet 3 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet4_sl_e_genweighted = new TH1D("pt_jet4_sl_e_genweighted","Gen_Weighted 4th Leading Jet pT Distribution (Single Electron) ;Jet 4 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet5_sl_e_genweighted = new TH1D("pt_jet5_sl_e_genweighted","Gen_Weighted 5th Leading Jet pT Distribution (Single Electron) ;Jet 5 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet6_sl_e_genweighted = new TH1D("pt_jet6_sl_e_genweighted","Gen_Weighted 6th Leading Jet pT Distribution (Single Electron) ;Jet 6 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet_all_sl_e_genweighted = new TH1D("pt_jet_all_sl_e_genweighted","Gen_Weighted Jet (all) pT Distribution (Single Electron) ;Jet pT (GeV);Nr. of Events",50,0,300);
    TH1D* csv_jet_all_sl_e_genweighted = new TH1D("csv_jet_all_sl_e_genweighted","Gen_Weighted Jet (all) CSV Distribution (Single Electron) ;Jet CSV (GeV);Nr. of Events",50,0,1);
    TH1D* ht_sl_e_genweighted = new TH1D("ht_sl_e_genweighted","Gen_Weighted HT Distribution (Single Electron) ;HT (GeV);Nr. of Events",50,0,1000);
    TH1D* njets_sl_e_genweighted = new TH1D("njets_sl_e_genweighted","Gen_Weighted Jet Multiplicity (Single Electron) ;Nr. of jets; Nr. of Events",15,0,15);
    TH1D* nbtags_sl_e_genweighted = new TH1D("nbtags_sl_e_genweighted","Gen_Weighted B-jet Multiplicity (Single Electron) ;Nr. of b-jets; Nr. of Events",8,0,8);
    TH1D* npv_sl_e_genweighted = new TH1D("npv_sl_e_genweighted","Gen_Weighted Nr. of Primary Vertices (Single Electron)  ;NPV; Nr. of Events",20,0,75);

    // Single Muon Histograms
    TH1D* pt_mu1_sl_mu = new TH1D("pt_mu1_sl_mu","Leading Muon pT Distribution (Single Muon) ;Leading Muon pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_mu1_sl_mu = new TH1D("eta_mu1_sl_mu","Leading Muon eta Distribution (Single Muon) ;Leading Muon #eta; Nr. of Events",15,-3,3);
    TH1D* phi_mu1_sl_mu = new TH1D("phi_mu1_sl_mu","Leading Muon phi Distribution (Single Muon) ;Leading Muon #phi; Nr. of Events",10,-3,3);
    TH1D* pt_jet1_sl_mu = new TH1D("pt_jet1_sl_mu","Leading Jet pT Distribution (Single Muon) ;Jet 1 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet2_sl_mu = new TH1D("pt_jet2_sl_mu","2nd Leading Jet pT Distribution (Single Muon) ;Jet 2 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet3_sl_mu = new TH1D("pt_jet3_sl_mu","3rd Leading Jet pT Distribution (Single Muon) ;Jet 3 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet4_sl_mu = new TH1D("pt_jet4_sl_mu","4th Leading Jet pT Distribution (Single Muon) ;Jet 4 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet5_sl_mu = new TH1D("pt_jet5_sl_mu","5th Leading Jet pT Distribution (Single Muon) ;Jet 5 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet6_sl_mu = new TH1D("pt_jet6_sl_mu","6th Leading Jet pT Distribution (Single Muon) ;Jet 6 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet_all_sl_mu = new TH1D("pt_jet_all_sl_mu","Jet (all) pT Distribution (Single Muon) ;Jet pT (GeV);Nr. of Events",50,0,300);
    TH1D* csv_jet_all_sl_mu = new TH1D("csv_jet_all_sl_mu","Jet (all) CSV Distribution (Single Muon) ;Jet CSV (GeV);Nr. of Events",50,0,1);
    TH1D* ht_sl_mu = new TH1D("ht_sl_mu","HT Distribution (Single Muon) ;HT (GeV);Nr. of Events",50,0,1000);
    TH1D* njets_sl_mu = new TH1D("njets_sl_mu","Jet Multiplicity (Single Muon) ;Nr. of jets; Nr. of Events",15,0,15);
    TH1D* nbtags_sl_mu = new TH1D("nbtags_sl_mu","B-jet Multiplicity (Single Muon) ;Nr. of b-jets; Nr. of Events",8,0,8);
    TH1D* npv_sl_mu = new TH1D("npv_sl_mu","Nr. of Primary Vertices (Single Muon)  ;NPV; Nr. of Events",20,0,75);

    TH1D* pt_mu1_sl_mu_genweighted = new TH1D("pt_mu1_sl_mu_genweighted","Gen_Weighted Leading Muon pT Distribution (Single Muon) ;Leading Muon pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_mu1_sl_mu_genweighted = new TH1D("eta_mu1_sl_mu_genweighted","Gen_Weighted Leading Muon eta Distribution (Single Muon) ;Leading Muon #eta; Nr. of Events",15,-3,3);
    TH1D* phi_mu1_sl_mu_genweighted = new TH1D("phi_mu1_sl_mu_genweighted","Gen_Weighted Leading Muon phi Distribution (Single Muon) ;Leading Muon #phi; Nr. of Events",10,-3,3);
    TH1D* pt_jet1_sl_mu_genweighted = new TH1D("pt_jet1_sl_mu_genweighted","Gen_Weighted Leading Jet pT Distribution (Single Muon) ;Jet 1 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet2_sl_mu_genweighted = new TH1D("pt_jet2_sl_mu_genweighted","Gen_Weighted 2nd Leading Jet pT Distribution (Single Muon) ;Jet 2 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet3_sl_mu_genweighted = new TH1D("pt_jet3_sl_mu_genweighted","Gen_Weighted 3rd Leading Jet pT Distribution (Single Muon) ;Jet 3 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet4_sl_mu_genweighted = new TH1D("pt_jet4_sl_mu_genweighted","Gen_Weighted 4th Leading Jet pT Distribution (Single Muon) ;Jet 4 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet5_sl_mu_genweighted = new TH1D("pt_jet5_sl_mu_genweighted","Gen_Weighted 5th Leading Jet pT Distribution (Single Muon) ;Jet 5 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet6_sl_mu_genweighted = new TH1D("pt_jet6_sl_mu_genweighted","Gen_Weighted 6th Leading Jet pT Distribution (Single Muon) ;Jet 6 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet_all_sl_mu_genweighted = new TH1D("pt_jet_all_sl_mu_genweighted","Gen_Weighted Jet (all) pT Distribution (Single Muon) ;Jet pT (GeV);Nr. of Events",50,0,300);
    TH1D* csv_jet_all_sl_mu_genweighted = new TH1D("csv_jet_all_sl_mu_genweighted","Gen_Weighted Jet (all) CSV Distribution (Single Muon) ;Jet CSV (GeV);Nr. of Events",50,0,1);
    TH1D* ht_sl_mu_genweighted = new TH1D("ht_sl_mu_genweighted","Gen_Weighted HT Distribution (Single Muon) ;HT (GeV);Nr. of Events",50,0,1000);
    TH1D* njets_sl_mu_genweighted = new TH1D("njets_sl_mu_genweighted","Gen_Weighted Jet Multiplicity (Single Muon) ;Nr. of jets; Nr. of Events",15,0,15);
    TH1D* nbtags_sl_mu_genweighted = new TH1D("nbtags_sl_mu_genweighted","Gen_Weighted B-jet Multiplicity (Single Muon) ;Nr. of b-jets; Nr. of Events",8,0,8);
    TH1D* npv_sl_mu_genweighted = new TH1D("npv_sl_mu_genweighted","Gen_Weighted Nr. of Primary Vertices (Single Muon)  ;NPV; Nr. of Events",20,0,75);

    // Double Electron Histograms
    TH1D* pt_e1_di_ee = new TH1D("pt_e1_di_ee","Leading Electron pT Distribution (Double Electron) ;Leading Electron pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_e1_di_ee = new TH1D("eta_e1_di_ee","Leading Electron eta Distribution (Double Electron) ;Leading Electron #eta; Nr. of Events",15,-3,3);
    TH1D* phi_e1_di_ee = new TH1D("phi_e1_di_ee","Leading Electron phi Distribution (Double Electron) ;Leading Electron #phi; Nr. of Events",10,-3,3);
    TH1D* pt_e2_di_ee = new TH1D("pt_e2_di_ee","Sub-leading Electron pT Distribution (Double Electron) ;Sub-leading Electron pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_e2_di_ee = new TH1D("eta_e2_di_ee","Sub-leading Electron eta Distribution (Double Electron) ;Sub-leading Electron #eta; Nr. of Events",10,-3,3);
    TH1D* phi_e2_di_ee = new TH1D("phi_e2_di_ee","Sub-leading Electron phi Distribution (Double Electron) ;Sub-leading Electron #phi; Nr. of Events",10,-3,3);
    TH1D* pt_jet1_di_ee = new TH1D("pt_jet1_di_ee","Leading Jet pT Distribution (Double Electron) ;Jet 1 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet2_di_ee = new TH1D("pt_jet2_di_ee","2nd Leading Jet pT Distribution (Double Electron) ;Jet 2 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet3_di_ee = new TH1D("pt_jet3_di_ee","3rd Leading Jet pT Distribution (Double Electron) ;Jet 3 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet4_di_ee = new TH1D("pt_jet4_di_ee","4th Leading Jet pT Distribution (Double Electron) ;Jet 4 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet5_di_ee = new TH1D("pt_jet5_di_ee","5th Leading Jet pT Distribution (Double Electron) ;Jet 5 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet6_di_ee = new TH1D("pt_jet6_di_ee","6th Leading Jet pT Distribution (Double Electron) ;Jet 6 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet_all_di_ee = new TH1D("pt_jet_all_di_ee","Jet (all) pT Distribution (Double Electron) ;Jet pT (GeV);Nr. of Events",50,0,300);
    TH1D* csv_jet_all_di_ee = new TH1D("csv_jet_all_di_ee","Jet (all) CSV Distribution (Double Electron) ;Jet CSV (GeV);Nr. of Events",50,0,1);
    TH1D* ht_di_ee = new TH1D("ht_di_ee","HT Distribution (Double Electron) ;HT (GeV);Nr. of Events",50,0,1000);
    TH1D* njets_di_ee = new TH1D("njets_di_ee","Jet Multiplicity (Double Electron) ;Nr. of jets; Nr. of Events",15,0,15);
    TH1D* nbtags_di_ee = new TH1D("nbtags_di_ee","B-jet Multiplicity (Double Electron) ;Nr. of b-jets; Nr. of Events",8,0,8);
    TH1D* npv_di_ee = new TH1D("npv_di_ee","Nr. of Primary Vertices (Double Electron)  ;NPV; Nr. of Events",20,0,75);

    TH1D* pt_e1_di_ee_genweighted = new TH1D("pt_e1_di_ee_genweighted","Gen_Weighted Leading Electron pT Distribution (Double Electron) ;Leading Electron pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_e1_di_ee_genweighted = new TH1D("eta_e1_di_ee_genweighted","Gen_Weighted Leading Electron eta Distribution (Double Electron) ;Leading Electron #eta; Nr. of Events",15,-3,3);
    TH1D* phi_e1_di_ee_genweighted = new TH1D("phi_e1_di_ee_genweighted","Gen_Weighted Leading Electron phi Distribution (Double Electron) ;Leading Electron #phi; Nr. of Events",10,-3,3);
    TH1D* pt_e2_di_ee_genweighted = new TH1D("pt_e2_di_ee_genweighted","Gen_Weighted Sub-leading Electron pT Distribution (Double Electron) ;Sub-leading Electron pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_e2_di_ee_genweighted = new TH1D("eta_e2_di_ee_genweighted","Gen_Weighted Sub-leading Electron eta Distribution (Double Electron) ;Sub-leading Electron #eta; Nr. of Events",10,-3,3);
    TH1D* phi_e2_di_ee_genweighted = new TH1D("phi_e2_di_ee_genweighted","Gen_Weighted Sub-leading Electron phi Distribution (Double Electron) ;Sub-leading Electron #phi; Nr. of Events",10,-3,3);
    TH1D* pt_jet1_di_ee_genweighted = new TH1D("pt_jet1_di_ee_genweighted","Gen_Weighted Leading Jet pT Distribution (Double Electron) ;Jet 1 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet2_di_ee_genweighted = new TH1D("pt_jet2_di_ee_genweighted","Gen_Weighted 2nd Leading Jet pT Distribution (Double Electron) ;Jet 2 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet3_di_ee_genweighted = new TH1D("pt_jet3_di_ee_genweighted","Gen_Weighted 3rd Leading Jet pT Distribution (Double Electron) ;Jet 3 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet4_di_ee_genweighted = new TH1D("pt_jet4_di_ee_genweighted","Gen_Weighted 4th Leading Jet pT Distribution (Double Electron) ;Jet 4 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet5_di_ee_genweighted = new TH1D("pt_jet5_di_ee_genweighted","Gen_Weighted 5th Leading Jet pT Distribution (Double Electron) ;Jet 5 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet6_di_ee_genweighted = new TH1D("pt_jet6_di_ee_genweighted","Gen_Weighted 6th Leading Jet pT Distribution (Double Electron) ;Jet 6 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet_all_di_ee_genweighted = new TH1D("pt_jet_all_di_ee_genweighted","Gen_Weighted Jet (all) pT Distribution (Double Electron) ;Jet pT (GeV);Nr. of Events",50,0,300);
    TH1D* csv_jet_all_di_ee_genweighted = new TH1D("csv_jet_all_di_ee_genweighted","Gen_Weighted Jet (all) CSV Distribution (Double Electron) ;Jet CSV (GeV);Nr. of Events",50,0,1);
    TH1D* ht_di_ee_genweighted = new TH1D("ht_di_ee_genweighted","Gen_Weighted HT Distribution (Double Electron) ;HT (GeV);Nr. of Events",50,0,1000);
    TH1D* njets_di_ee_genweighted = new TH1D("njets_di_ee_genweighted","Gen_Weighted Jet Multiplicity (Double Electron) ;Nr. of jets; Nr. of Events",15,0,15);
    TH1D* nbtags_di_ee_genweighted = new TH1D("nbtags_di_ee_genweighted","Gen_Weighted B-jet Multiplicity (Double Electron) ;Nr. of b-jets; Nr. of Events",8,0,8);
    TH1D* npv_di_ee_genweighted = new TH1D("npv_di_ee_genweighted","Gen_Weighted Nr. of Primary Vertices (Double Electron)  ;NPV; Nr. of Events",20,0,75);

    // Electron Muon Histograms
    TH1D* pt_e1_di_emu = new TH1D("pt_e1_di_emu","Electron pT Distribution (Electron Muon) ;Electron pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_e1_di_emu = new TH1D("eta_e1_di_emu","Electron eta Distribution (Electron Muon) ;Electron #eta; Nr. of Events",15,-3,3);
    TH1D* phi_e1_di_emu = new TH1D("phi_e1_di_emu","Electron phi Distribution (Electron Muon) ;Electron #phi; Nr. of Events",10,-3,3);
    TH1D* pt_mu1_di_emu = new TH1D("pt_mu1_di_emu","Muon pT Distribution (Electron Muon) ;Muon pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_mu1_di_emu = new TH1D("eta_mu1_di_emu","Muon eta Distribution (Electron Muon) ;Muon #eta; Nr. of Events",10,-3,3);
    TH1D* phi_mu1_di_emu = new TH1D("phi_mu1_di_emu","Muon phi Distribution (Electron Muon) ;Muon #phi; Nr. of Events",10,-3,3);
    TH1D* pt_jet1_di_emu = new TH1D("pt_jet1_di_emu","Leading Jet pT Distribution (Electron Muon) ;Jet 1 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet2_di_emu = new TH1D("pt_jet2_di_emu","2nd Leading Jet pT Distribution (Electron Muon) ;Jet 2 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet3_di_emu = new TH1D("pt_jet3_di_emu","3rd Leading Jet pT Distribution (Electron Muon) ;Jet 3 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet4_di_emu = new TH1D("pt_jet4_di_emu","4th Leading Jet pT Distribution (Electron Muon) ;Jet 4 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet5_di_emu = new TH1D("pt_jet5_di_emu","5th Leading Jet pT Distribution (Electron Muon) ;Jet 5 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet6_di_emu = new TH1D("pt_jet6_di_emu","6th Leading Jet pT Distribution (Electron Muon) ;Jet 6 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet_all_di_emu = new TH1D("pt_jet_all_di_emu","Jet (all) pT Distribution (Electron Muon) ;Jet pT (GeV);Nr. of Events",50,0,300);
    TH1D* csv_jet_all_di_emu = new TH1D("csv_jet_all_di_emu","Jet (all) CSV Distribution (Electron Muon) ;Jet CSV (GeV);Nr. of Events",50,0,1);
    TH1D* ht_di_emu = new TH1D("ht_di_emu","HT Distribution (Electron Muon) ;HT (GeV);Nr. of Events",50,0,1000);
    TH1D* njets_di_emu = new TH1D("njets_di_emu","Jet Multiplicity (Electron Muon) ;Nr. of jets; Nr. of Events",15,0,15);
    TH1D* nbtags_di_emu = new TH1D("nbtags_di_emu","B-jet Multiplicity (Electron Muon) ;Nr. of b-jets; Nr. of Events",8,0,8);
    TH1D* npv_di_emu = new TH1D("npv_di_emu","Nr. of Primary Vertices (Electron Muon)  ;NPV; Nr. of Events",20,0,75);

    TH1D* pt_e1_di_emu_genweighted = new TH1D("pt_e1_di_emu_genweighted","Gen_Weighted Electron pT Distribution (Electron Muon) ;Electron pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_e1_di_emu_genweighted = new TH1D("eta_e1_di_emu_genweighted","Gen_Weighted Electron eta Distribution (Electron Muon) ;Electron #eta; Nr. of Events",15,-3,3);
    TH1D* phi_e1_di_emu_genweighted = new TH1D("phi_e1_di_emu_genweighted","Gen_Weighted Electron phi Distribution (Electron Muon) ;Electron #phi; Nr. of Events",10,-3,3);
    TH1D* pt_mu1_di_emu_genweighted = new TH1D("pt_mu1_di_emu_genweighted","Gen_Weighted Muon pT Distribution (Electron Muon) ;Muon pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_mu1_di_emu_genweighted = new TH1D("eta_mu1_di_emu_genweighted","Gen_Weighted Muon eta Distribution (Electron Muon) ;Muon #eta; Nr. of Events",10,-3,3);
    TH1D* phi_mu1_di_emu_genweighted = new TH1D("phi_mu1_di_emu_genweighted","Gen_Weighted Muon phi Distribution (Electron Muon) ;Muon #phi; Nr. of Events",10,-3,3);
    TH1D* pt_jet1_di_emu_genweighted = new TH1D("pt_jet1_di_emu_genweighted","Gen_Weighted Leading Jet pT Distribution (Electron Muon) ;Jet 1 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet2_di_emu_genweighted = new TH1D("pt_jet2_di_emu_genweighted","Gen_Weighted 2nd Leading Jet pT Distribution (Electron Muon) ;Jet 2 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet3_di_emu_genweighted = new TH1D("pt_jet3_di_emu_genweighted","Gen_Weighted 3rd Leading Jet pT Distribution (Electron Muon) ;Jet 3 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet4_di_emu_genweighted = new TH1D("pt_jet4_di_emu_genweighted","Gen_Weighted 4th Leading Jet pT Distribution (Electron Muon) ;Jet 4 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet5_di_emu_genweighted = new TH1D("pt_jet5_di_emu_genweighted","Gen_Weighted 5th Leading Jet pT Distribution (Electron Muon) ;Jet 5 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet6_di_emu_genweighted = new TH1D("pt_jet6_di_emu_genweighted","Gen_Weighted 6th Leading Jet pT Distribution (Electron Muon) ;Jet 6 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet_all_di_emu_genweighted = new TH1D("pt_jet_all_di_emu_genweighted","Gen_Weighted Jet (all) pT Distribution (Electron Muon) ;Jet pT (GeV);Nr. of Events",50,0,300);
    TH1D* csv_jet_all_di_emu_genweighted = new TH1D("csv_jet_all_di_emu_genweighted","Gen_Weighted Jet (all) CSV Distribution (Electron Muon) ;Jet CSV (GeV);Nr. of Events",50,0,1);
    TH1D* ht_di_emu_genweighted = new TH1D("ht_di_emu_genweighted","Gen_Weighted HT Distribution (Electron Muon) ;HT (GeV);Nr. of Events",50,0,1000);
    TH1D* njets_di_emu_genweighted = new TH1D("njets_di_emu_genweighted","Gen_Weighted Jet Multiplicity (Electron Muon) ;Nr. of jets; Nr. of Events",15,0,15);
    TH1D* nbtags_di_emu_genweighted = new TH1D("nbtags_di_emu_genweighted","Gen_Weighted B-jet Multiplicity (Electron Muon) ;Nr. of b-jets; Nr. of Events",8,0,8);
    TH1D* npv_di_emu_genweighted = new TH1D("npv_di_emu_genweighted","Gen_Weighted Nr. of Primary Vertices (Electron Muon)  ;NPV; Nr. of Events",20,0,75);

    // Double Muon Histograms
    TH1D* pt_mu1_di_mumu = new TH1D("pt_mu1_di_mumu","Leading Muon pT Distribution (Double Muon) ;Leading Muon pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_mu1_di_mumu = new TH1D("eta_mu1_di_mumu","Leading Muon eta Distribution (Double Muon) ;Leading Muon #eta; Nr. of Events",15,-3,3);
    TH1D* phi_mu1_di_mumu = new TH1D("phi_mu1_di_mumu","Leading Muon phi Distribution (Double Muon) ;Leading Muon #phi; Nr. of Events",10,-3,3);
    TH1D* pt_mu2_di_mumu = new TH1D("pt_mu2_di_mumu","Sub-leading Muon pT Distribution (Double Muon) ;Sub-leading Muon pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_mu2_di_mumu = new TH1D("eta_mu2_di_mumu","Sub-leading Muon eta Distribution (Double Muon) ;Sub-leading Muon #eta; Nr. of Events",10,-3,3);
    TH1D* phi_mu2_di_mumu = new TH1D("phi_mu2_di_mumu","Sub-leading Muon phi Distribution (Double Muon) ;Sub-leading Muon #phi; Nr. of Events",10,-3,3);
    TH1D* pt_jet1_di_mumu = new TH1D("pt_jet1_di_mumu","Leading Jet pT Distribution (Double Muon) ;Jet 1 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet2_di_mumu = new TH1D("pt_jet2_di_mumu","2nd Leading Jet pT Distribution (Double Muon) ;Jet 2 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet3_di_mumu = new TH1D("pt_jet3_di_mumu","3rd Leading Jet pT Distribution (Double Muon) ;Jet 3 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet4_di_mumu = new TH1D("pt_jet4_di_mumu","4th Leading Jet pT Distribution (Double Muon) ;Jet 4 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet5_di_mumu = new TH1D("pt_jet5_di_mumu","5th Leading Jet pT Distribution (Double Muon) ;Jet 5 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet6_di_mumu = new TH1D("pt_jet6_di_mumu","6th Leading Jet pT Distribution (Double Muon) ;Jet 6 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet_all_di_mumu = new TH1D("pt_jet_all_di_mumu","Jet (all) pT Distribution (Double Muon) ;Jet pT (GeV);Nr. of Events",50,0,300);
    TH1D* csv_jet_all_di_mumu = new TH1D("csv_jet_all_di_mumu","Jet (all) CSV Distribution (Double Muon) ;Jet CSV (GeV);Nr. of Events",50,0,1);
    TH1D* ht_di_mumu = new TH1D("ht_di_mumu","HT Distribution (Double Muon) ;HT (GeV);Nr. of Events",50,0,1000);
    TH1D* njets_di_mumu = new TH1D("njets_di_mumu","Jet Multiplicity (Double Muon) ;Nr. of jets; Nr. of Events",15,0,15);
    TH1D* nbtags_di_mumu = new TH1D("nbtags_di_mumu","B-jet Multiplicity (Double Muon) ;Nr. of b-jets; Nr. of Events",8,0,8);
    TH1D* npv_di_mumu = new TH1D("npv_di_mumu","Nr. of Primary Vertices (Double Muon)  ;NPV; Nr. of Events",20,0,75);

    TH1D* pt_mu1_di_mumu_genweighted = new TH1D("pt_mu1_di_mumu_genweighted","Gen_Weighted Leading Muon pT Distribution (Double Muon) ;Leading Muon pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_mu1_di_mumu_genweighted = new TH1D("eta_mu1_di_mumu_genweighted","Gen_Weighted Leading Muon eta Distribution (Double Muon) ;Leading Muon #eta; Nr. of Events",15,-3,3);
    TH1D* phi_mu1_di_mumu_genweighted = new TH1D("phi_mu1_di_mumu_genweighted","Gen_Weighted Leading Muon phi Distribution (Double Muon) ;Leading Muon #phi; Nr. of Events",10,-3,3);
    TH1D* pt_mu2_di_mumu_genweighted = new TH1D("pt_mu2_di_mumu_genweighted","Gen_Weighted Sub-leading Muon pT Distribution (Double Muon) ;Sub-leading Muon pT (GeV);Nr. of Events",50,0,300);
    TH1D* eta_mu2_di_mumu_genweighted = new TH1D("eta_mu2_di_mumu_genweighted","Gen_Weighted Sub-leading Muon eta Distribution (Double Muon) ;Sub-leading Muon #eta; Nr. of Events",10,-3,3);
    TH1D* phi_mu2_di_mumu_genweighted = new TH1D("phi_mu2_di_mumu_genweighted","Gen_Weighted Sub-leading Muon phi Distribution (Double Muon) ;Sub-leading Muon #phi; Nr. of Events",10,-3,3);
    TH1D* pt_jet1_di_mumu_genweighted = new TH1D("pt_jet1_di_mumu_genweighted","Gen_Weighted Leading Jet pT Distribution (Double Muon) ;Jet 1 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet2_di_mumu_genweighted = new TH1D("pt_jet2_di_mumu_genweighted","Gen_Weighted 2nd Leading Jet pT Distribution (Double Muon) ;Jet 2 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet3_di_mumu_genweighted = new TH1D("pt_jet3_di_mumu_genweighted","Gen_Weighted 3rd Leading Jet pT Distribution (Double Muon) ;Jet 3 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet4_di_mumu_genweighted = new TH1D("pt_jet4_di_mumu_genweighted","Gen_Weighted 4th Leading Jet pT Distribution (Double Muon) ;Jet 4 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet5_di_mumu_genweighted = new TH1D("pt_jet5_di_mumu_genweighted","Gen_Weighted 5th Leading Jet pT Distribution (Double Muon) ;Jet 5 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet6_di_mumu_genweighted = new TH1D("pt_jet6_di_mumu_genweighted","Gen_Weighted 6th Leading Jet pT Distribution (Double Muon) ;Jet 6 pT (GeV);Nr. of Events",50,0,300);
    TH1D* pt_jet_all_di_mumu_genweighted = new TH1D("pt_jet_all_di_mumu_genweighted","Gen_Weighted Jet (all) pT Distribution (Double Muon) ;Jet pT (GeV);Nr. of Events",50,0,300);
    TH1D* csv_jet_all_di_mumu_genweighted = new TH1D("csv_jet_all_di_mumu_genweighted","Gen_Weighted Jet (all) CSV Distribution (Double Muon) ;Jet CSV (GeV);Nr. of Events",50,0,1);
    TH1D* ht_di_mumu_genweighted = new TH1D("ht_di_mumu_genweighted","Gen_Weighted HT Distribution (Double Muon) ;HT (GeV);Nr. of Events",50,0,1000);
    TH1D* njets_di_mumu_genweighted = new TH1D("njets_di_mumu_genweighted","Gen_Weighted Jet Multiplicity (Double Muon) ;Nr. of jets; Nr. of Events",15,0,15);
    TH1D* nbtags_di_mumu_genweighted = new TH1D("nbtags_di_mumu_genweighted","Gen_Weighted B-jet Multiplicity (Double Muon) ;Nr. of b-jets; Nr. of Events",8,0,8);
    TH1D* npv_di_mumu_genweighted = new TH1D("npv_di_mumu_genweighted","Gen_Weighted Nr. of Primary Vertices (Double Muon)  ;NPV; Nr. of Events",20,0,75);

    /*
    // Trigger SF : Opening Files

    // Single Electron
    std::string TRIGGERinputFile_e = "TriggerSF/TriggerSF_EG_Run2016All_v1.root";
    TFile *f_TRIGGERSF_e = new TFile(std::string(TRIGGERinputFile_e).c_str(),"READ");
    TH2F *h_ele_TRIGGER_abseta_pt_ratio = (TH2F*)f_TRIGGERSF_e->Get("Ele27_WPTight_Gsf");

    // Single Muon
    std::string TRIGGERinputFile_BF_mu =  "TriggerSF/Trigger_EfficienciesAndSF_MU_RunBtoF.root";
    std::string TRIGGERinputFile_GH_mu =  "TriggerSF/Trigger_EfficienciesAndSF_MU_Period4.root";
    TFile *f_TRIGGERSF_BF_mu = new TFile(std::string(TRIGGERinputFile_BF_mu).c_str(),"READ");
    TFile *f_TRIGGERSF_GH_mu = new TFile(std::string(TRIGGERinputFile_GH_mu).c_str(),"READ");
    TH2F *h_mu_TRIGGER_BF_abseta_pt_ratio = (TH2F*)f_TRIGGERSF_BF_mu->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/pt_abseta_ratio");
    TH2F *h_mu_TRIGGER_GH_abseta_pt_ratio = (TH2F*)f_TRIGGERSF_GH_mu->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/pt_abseta_ratio");

    // Di Electron
    std::string TRIGGERinputFile_ee = "TriggerSF/triggerSummary_ee_ReReco2016_ttH.root";
    TFile *f_TRIGGERSF_ee = new TFile(std::string(TRIGGERinputFile_ee).c_str(),"READ");
    TH2F *h_ele_ele_TRIGGER_abseta_abseta = (TH2F*)f_TRIGGERSF_ee->Get("scalefactor_eta2d_with_syst");

    // Di Muon
    std::string TRIGGERinputFile_mumu = "TriggerSF/triggerSummary_mumu_ReReco2016_ttH.root";
    TFile *f_TRIGGERSF_mumu = new TFile(std::string(TRIGGERinputFile_mumu).c_str(),"READ");
    TH2F *h_mu_mu_TRIGGER_abseta_abseta = (TH2F*)f_TRIGGERSF_mumu->Get("scalefactor_eta2d_with_syst");

    // Electron Muon
    std::string TRIGGERinputFile_emu = "TriggerSF/triggerSummary_emu_ReReco2016_ttH.root";
    TFile *f_TRIGGERSF_emu = new TFile(std::string(TRIGGERinputFile_emu).c_str(),"READ");
    TH2F *h_ele_mu_TRIGGER_abseta_abseta = (TH2F*)f_TRIGGERSF_emu->Get("scalefactor_eta2d_with_syst");
    */


    // JEC Uncertainties
    std::vector<std::string> jet_jesSF_names;
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


    int nentries = reco_chain->GetEntries();
    int NeventsPerJob = int( double(nentries)/double(Njobs) + 0.000001 ) + 1;

    int firstEvent = (jobN-1)*NeventsPerJob + 1;
    int lastEvent  = firstEvent + NeventsPerJob;
    if( jobN==Njobs ) lastEvent = -1;
    if( jobN==1 ) firstEvent = 0;

    int nentries_comm = comm_chain->GetEntries();
    int NeventsPerJob_comm = int( double(nentries_comm)/double(Njobs) + 0.000001 ) + 1;

    int firstEvent_comm = (jobN-1)*NeventsPerJob_comm + 1;
    int lastEvent_comm  = firstEvent_comm + NeventsPerJob_comm;
    if( jobN==Njobs ) lastEvent_comm = -1;
    if( jobN==1 ) firstEvent_comm = 0;

    // Assigning variables for each branch from Tree in ntuple

    CU_ttH_EDA_Reco_Ntuple *reco_ntuple = 0;
    CU_ttH_EDA_Gen_Ntuple *gen_ntuple = 0;
    CU_ttH_EDA_Comm_Ntuple *comm_ntuple = 0;

    /*
    int nEvent_comm;
    double gen_weight_comm;
    double PU_weight_comm, PU_weight_up_comm, PU_weight_down_comm;
    int npv_comm;

    int nEvent, ls, run, is_data;
    int data_era;
    int save_gen_info, is_trigger_study, is_tight_skim;
    int npv;
    int ttHf_cat;
    int ttHFGenFilter;

    int pass_HLT_Ele35_WPTight_Gsf;
    int pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned;
    int pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150;
    int pass_HLT_IsoMu27;
    int pass_HLT_IsoMu24_eta2p1;
    int pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
    int pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
    int pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
    int pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
    int pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
    int pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
    int pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
    int pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
    int pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;


    vdouble * mu_pt = 0;
    vdouble * mu_pt_uncorr = 0;
    vdouble * mu_eta = 0;
    vdouble * mu_phi = 0;
    vdouble * mu_E = 0;
    vdouble * mu_iso = 0;
    vint * mu_pdgid = 0;

    vdouble * ele_pt = 0;
    vdouble * ele_pt_uncorr = 0;
    vdouble * ele_eta = 0;
    vdouble * ele_sc_eta = 0;
    vdouble * ele_phi = 0;
    vdouble * ele_E = 0;
    vdouble * ele_iso = 0;
    vint * ele_pdgid = 0;

    vdouble * jet_pt_uncorr = 0;
    vdouble * jet_eta = 0;
    vdouble * jet_phi = 0;
    vdouble * jet_E = 0;
    vdouble * jet_CSV = 0;
    vint * jet_flavor = 0;
    vint * jet_puid = 0;
    vdouble * jet_pudisc = 0;

    double met_pt_phi_corr;
    double met_phi_phi_corr;
    double met_pt_jer_up;
    double met_phi_jer_up;
    double met_pt_jer_down;
    double met_phi_jer_down;

    vdouble * jet_jecSF_nominal = 0;
    vdouble * jet_jecSF_nominal_up = 0;
    vdouble * jet_jecSF_nominal_down = 0;
    vvdouble * jet_jesSF_up = 0;
    vvdouble * jet_jesSF_down = 0;
    vdouble * jet_jerSF_jesnominal_nominal = 0;
    vdouble * jet_jerSF_jesnominal_up = 0;
    vdouble * jet_jerSF_jesnominal_down = 0;
    vvdouble * jet_jerSF_jesup_nominal = 0;
    vvdouble * jet_jerSF_jesdown_nominal = 0;

    vdouble * ele_sf_id_combined = 0;
    vdouble * ele_sf_id_up_combined = 0;
    vdouble * ele_sf_id_down_combined = 0;
    vdouble * ele_sf_iso_combined = 0;
    vdouble * ele_sf_iso_up_combined = 0;
    vdouble * ele_sf_iso_down_combined = 0;
    vdouble * ele_sf_id_rundep = 0;
    vdouble * ele_sf_id_up_rundep = 0;
    vdouble * ele_sf_id_down_rundep = 0;
    vdouble * ele_sf_iso_rundep = 0;
    vdouble * ele_sf_iso_up_rundep = 0;
    vdouble * ele_sf_iso_down_rundep = 0;

    vdouble * mu_sf_id_combined = 0;
    vdouble * mu_sf_id_up_combined = 0;
    vdouble * mu_sf_id_down_combined = 0;
    vdouble * mu_sf_iso_combined = 0;
    vdouble * mu_sf_iso_up_combined = 0;
    vdouble * mu_sf_iso_down_combined = 0;
    vdouble * mu_sf_tracking_combined = 0;
    vdouble * mu_sf_tracking_up_combined = 0;
    vdouble * mu_sf_tracking_down_combined = 0;
    vdouble * mu_sf_id_rundep = 0;
    vdouble * mu_sf_id_up_rundep = 0;
    vdouble * mu_sf_id_down_rundep = 0;
    vdouble * mu_sf_iso_rundep = 0;
    vdouble * mu_sf_iso_up_rundep = 0;
    vdouble * mu_sf_iso_down_rundep = 0;
    vdouble * mu_sf_tracking_rundep = 0;
    vdouble * mu_sf_tracking_up_rundep = 0;
    vdouble * mu_sf_tracking_down_rundep = 0;

    vdouble * b_weight_jesnominal_nominal = 0;
    vdouble * b_weight_jesnominal_hfup = 0;
    vdouble * b_weight_jesnominal_hfdown = 0;
    vdouble * b_weight_jesnominal_hfstats1up = 0;
    vdouble * b_weight_jesnominal_hfstats1down = 0;
    vdouble * b_weight_jesnominal_hfstats2up = 0;
    vdouble * b_weight_jesnominal_hfstats2down = 0;
    vdouble * b_weight_jesnominal_lfup = 0;
    vdouble * b_weight_jesnominal_lfdown = 0;
    vdouble * b_weight_jesnominal_lfstats1up = 0;
    vdouble * b_weight_jesnominal_lfstats1down = 0;
    vdouble * b_weight_jesnominal_lfstats2up = 0;
    vdouble * b_weight_jesnominal_lfstats2down = 0;
    vdouble * b_weight_jesnominal_cferr1up = 0;
    vdouble * b_weight_jesnominal_cferr1down = 0;
    vdouble * b_weight_jesnominal_cferr2up = 0;
    vdouble * b_weight_jesnominal_cferr2down = 0;
    vvdouble * b_weight_jesup_nominal = 0;
    vvdouble * b_weight_jesdown_nominal = 0;

    double gen_weight;
    double PU_weight;
    double PU_weight_up;
    double PU_weight_down;
    double pdf_weight_up;
    double pdf_weight_down;
    double q2_weight_up;
    double q2_weight_down;
    vdouble * ps_weights = 0;
    */

    if(is_data_input==0){
        comm_chain->SetBranchAddress("comm_ntuple", &comm_ntuple );
        /*
        comm_chain->SetBranchAddress("nEvent", &nEvent_comm );
        comm_chain->SetBranchAddress("gen_weight", &gen_weight_comm );
        comm_chain->SetBranchAddress("PU_weight", &PU_weight_comm );
        comm_chain->SetBranchAddress("PU_weight_up", &PU_weight_up_comm );
        comm_chain->SetBranchAddress("PU_weight_down", &PU_weight_down_comm );
        comm_chain->SetBranchAddress("npv", &npv_comm );
        */
    }

    reco_chain->SetBranchAddress("reco_ntuple", &reco_ntuple );
    if(is_data_input==0)
        gen_chain->SetBranchAddress("gen_ntuple", &gen_ntuple );
    /*
    reco_chain->SetBranchAddress("nEvent", &nEvent );
    reco_chain->SetBranchAddress("ls", &ls );
    reco_chain->SetBranchAddress("run", &run );
    reco_chain->SetBranchAddress("is_data", &is_data );
    reco_chain->SetBranchAddress("data_era", &data_era );
    reco_chain->SetBranchAddress("save_gen_info", &save_gen_info );
    reco_chain->SetBranchAddress("is_trigger_study", &is_trigger_study );
    reco_chain->SetBranchAddress("is_tight_skim", &is_tight_skim );
    reco_chain->SetBranchAddress("npv", &npv );
    reco_chain->SetBranchAddress("ttHf_cat", &ttHf_cat );
    reco_chain->SetBranchAddress("ttHFGenFilter", &ttHFGenFilter );
    reco_chain->SetBranchAddress("pass_HLT_Ele35_WPTight_Gsf_", &pass_HLT_Ele35_WPTight_Gsf );
    reco_chain->SetBranchAddress("pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned_", &pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned );
    reco_chain->SetBranchAddress("pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150_", &pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150 );
    reco_chain->SetBranchAddress("pass_HLT_IsoMu27_", &pass_HLT_IsoMu27 );
    reco_chain->SetBranchAddress("pass_HLT_IsoMu24_eta2p1_", &pass_HLT_IsoMu24_eta2p1 );
    reco_chain->SetBranchAddress("pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_", &pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL );
    reco_chain->SetBranchAddress("pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_", &pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ );
    reco_chain->SetBranchAddress("pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_", &pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL );
    reco_chain->SetBranchAddress("pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_", &pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ );
    reco_chain->SetBranchAddress("pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_", &pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ );
    reco_chain->SetBranchAddress("pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_", &pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ );
    reco_chain->SetBranchAddress("pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_", &pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ );
    reco_chain->SetBranchAddress("pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_", &pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 );
    reco_chain->SetBranchAddress("pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_", &pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 );
    reco_chain->SetBranchAddress("ele_pt", &ele_pt );
    reco_chain->SetBranchAddress("ele_pt_uncorr", &ele_pt_uncorr );
    reco_chain->SetBranchAddress("ele_eta", &ele_eta );
    reco_chain->SetBranchAddress("ele_sc_eta", &ele_sc_eta );
    reco_chain->SetBranchAddress("ele_phi", &ele_phi );
    reco_chain->SetBranchAddress("ele_E", &ele_E );
    reco_chain->SetBranchAddress("ele_iso", &ele_iso );
    reco_chain->SetBranchAddress("ele_pdgid", &ele_pdgid );
    reco_chain->SetBranchAddress("mu_pt", &mu_pt );
    reco_chain->SetBranchAddress("mu_pt_uncorr", &mu_pt_uncorr );
    reco_chain->SetBranchAddress("mu_eta", &mu_eta );
    reco_chain->SetBranchAddress("mu_phi", &mu_phi );
    reco_chain->SetBranchAddress("mu_E", &mu_E );
    reco_chain->SetBranchAddress("mu_iso", &mu_iso );
    reco_chain->SetBranchAddress("mu_pdgid", &mu_pdgid );
    reco_chain->SetBranchAddress("jet_pt_uncorr", &jet_pt_uncorr );
    reco_chain->SetBranchAddress("jet_eta", &jet_eta );
    reco_chain->SetBranchAddress("jet_phi", &jet_phi );
    reco_chain->SetBranchAddress("jet_E", &jet_E );
    reco_chain->SetBranchAddress("jet_CSV", &jet_CSV );
    reco_chain->SetBranchAddress("jet_flavor", &jet_flavor );
    reco_chain->SetBranchAddress("jet_puid", &jet_puid );
    reco_chain->SetBranchAddress("jet_pudisc", &jet_pudisc );
    reco_chain->SetBranchAddress("met_pt_phi_corr", &met_pt_phi_corr );
    reco_chain->SetBranchAddress("met_phi_phi_corr", &met_phi_phi_corr );
    reco_chain->SetBranchAddress("met_pt_jer_up", &met_pt_jer_up );
    reco_chain->SetBranchAddress("met_phi_jer_up", &met_phi_jer_up );
    reco_chain->SetBranchAddress("met_pt_jer_down", &met_pt_jer_down );
    reco_chain->SetBranchAddress("met_phi_jer_down", &met_phi_jer_down );
    reco_chain->SetBranchAddress("jet_jecSF_nominal", &jet_jecSF_nominal );
    reco_chain->SetBranchAddress("jet_jecSF_nominal_up", &jet_jecSF_nominal_up );
    reco_chain->SetBranchAddress("jet_jecSF_nominal_down", &jet_jecSF_nominal_down );
    reco_chain->SetBranchAddress("jet_jesSF_up", &jet_jesSF_up );
    reco_chain->SetBranchAddress("jet_jesSF_down", &jet_jesSF_down );
    reco_chain->SetBranchAddress("jet_jerSF_jesnominal_nominal", &jet_jerSF_jesnominal_nominal );
    reco_chain->SetBranchAddress("jet_jerSF_jesnominal_up", &jet_jerSF_jesnominal_up );
    reco_chain->SetBranchAddress("jet_jerSF_jesnominal_down", &jet_jerSF_jesnominal_down );
    reco_chain->SetBranchAddress("jet_jerSF_jesup_nominal", &jet_jerSF_jesup_nominal );
    reco_chain->SetBranchAddress("jet_jerSF_jesdown_nominal", &jet_jerSF_jesdown_nominal );
    reco_chain->SetBranchAddress("ele_sf_id_combined", &ele_sf_id_combined );
    reco_chain->SetBranchAddress("ele_sf_id_up_combined", &ele_sf_id_up_combined );
    reco_chain->SetBranchAddress("ele_sf_id_down_combined", &ele_sf_id_down_combined );
    reco_chain->SetBranchAddress("ele_sf_iso_combined", &ele_sf_iso_combined );
    reco_chain->SetBranchAddress("ele_sf_iso_up_combined", &ele_sf_iso_up_combined );
    reco_chain->SetBranchAddress("ele_sf_iso_down_combined", &ele_sf_iso_down_combined );
    reco_chain->SetBranchAddress("ele_sf_id_rundep", &ele_sf_id_rundep );
    reco_chain->SetBranchAddress("ele_sf_id_up_rundep", &ele_sf_id_up_rundep );
    reco_chain->SetBranchAddress("ele_sf_id_down_rundep", &ele_sf_id_down_rundep );
    reco_chain->SetBranchAddress("ele_sf_iso_rundep", &ele_sf_iso_rundep );
    reco_chain->SetBranchAddress("ele_sf_iso_up_rundep", &ele_sf_iso_up_rundep );
    reco_chain->SetBranchAddress("ele_sf_iso_down_rundep", &ele_sf_iso_down_rundep );
    reco_chain->SetBranchAddress("mu_sf_id_combined", &mu_sf_id_combined );
    reco_chain->SetBranchAddress("mu_sf_id_up_combined", &mu_sf_id_up_combined );
    reco_chain->SetBranchAddress("mu_sf_id_down_combined", &mu_sf_id_down_combined );
    reco_chain->SetBranchAddress("mu_sf_iso_combined", &mu_sf_iso_combined );
    reco_chain->SetBranchAddress("mu_sf_iso_up_combined", &mu_sf_iso_up_combined );
    reco_chain->SetBranchAddress("mu_sf_iso_down_combined", &mu_sf_iso_down_combined );
    reco_chain->SetBranchAddress("mu_sf_tracking_combined", &mu_sf_tracking_combined );
    reco_chain->SetBranchAddress("mu_sf_tracking_up_combined", &mu_sf_tracking_up_combined );
    reco_chain->SetBranchAddress("mu_sf_tracking_down_combined", &mu_sf_tracking_down_combined );
    reco_chain->SetBranchAddress("mu_sf_id_rundep", &mu_sf_id_rundep );
    reco_chain->SetBranchAddress("mu_sf_id_up_rundep", &mu_sf_id_up_rundep );
    reco_chain->SetBranchAddress("mu_sf_id_down_rundep", &mu_sf_id_down_rundep );
    reco_chain->SetBranchAddress("mu_sf_iso_rundep", &mu_sf_iso_rundep );
    reco_chain->SetBranchAddress("mu_sf_iso_up_rundep", &mu_sf_iso_up_rundep );
    reco_chain->SetBranchAddress("mu_sf_iso_down_rundep", &mu_sf_iso_down_rundep );
    reco_chain->SetBranchAddress("mu_sf_tracking_rundep", &mu_sf_tracking_rundep );
    reco_chain->SetBranchAddress("mu_sf_tracking_up_rundep", &mu_sf_tracking_up_rundep );
    reco_chain->SetBranchAddress("mu_sf_tracking_down_rundep", &mu_sf_tracking_down_rundep );
    reco_chain->SetBranchAddress("b_weight_jesnominal_nominal", &b_weight_jesnominal_nominal );
    reco_chain->SetBranchAddress("b_weight_jesnominal_hfup", &b_weight_jesnominal_hfup );
    reco_chain->SetBranchAddress("b_weight_jesnominal_hfdown", &b_weight_jesnominal_hfdown );
    reco_chain->SetBranchAddress("b_weight_jesnominal_hfstats1up", &b_weight_jesnominal_hfstats1up );
    reco_chain->SetBranchAddress("b_weight_jesnominal_hfstats1down", &b_weight_jesnominal_hfstats1down );
    reco_chain->SetBranchAddress("b_weight_jesnominal_hfstats2up", &b_weight_jesnominal_hfstats2up );
    reco_chain->SetBranchAddress("b_weight_jesnominal_hfstats2down", &b_weight_jesnominal_hfstats2down );
    reco_chain->SetBranchAddress("b_weight_jesnominal_lfup", &b_weight_jesnominal_lfup );
    reco_chain->SetBranchAddress("b_weight_jesnominal_lfdown", &b_weight_jesnominal_lfdown );
    reco_chain->SetBranchAddress("b_weight_jesnominal_lfstats1up", &b_weight_jesnominal_lfstats1up );
    reco_chain->SetBranchAddress("b_weight_jesnominal_lfstats1down", &b_weight_jesnominal_lfstats1down );
    reco_chain->SetBranchAddress("b_weight_jesnominal_lfstats2up", &b_weight_jesnominal_lfstats2up );
    reco_chain->SetBranchAddress("b_weight_jesnominal_lfstats2down", &b_weight_jesnominal_lfstats2down );
    reco_chain->SetBranchAddress("b_weight_jesnominal_cferr1up", &b_weight_jesnominal_cferr1up );
    reco_chain->SetBranchAddress("b_weight_jesnominal_cferr1down", &b_weight_jesnominal_cferr1down );
    reco_chain->SetBranchAddress("b_weight_jesnominal_cferr2up", &b_weight_jesnominal_cferr2up );
    reco_chain->SetBranchAddress("b_weight_jesnominal_cferr2down", &b_weight_jesnominal_cferr2down );
    reco_chain->SetBranchAddress("b_weight_jesup_nominal", &b_weight_jesup_nominal );
    reco_chain->SetBranchAddress("b_weight_jesdown_nominal", &b_weight_jesdown_nominal );
    reco_chain->SetBranchAddress("gen_weight", &gen_weight );
    reco_chain->SetBranchAddress("PU_weight", &PU_weight );
    reco_chain->SetBranchAddress("PU_weight_up", &PU_weight_up );
    reco_chain->SetBranchAddress("PU_weight_down", &PU_weight_down );
    reco_chain->SetBranchAddress("pdf_weight_up", &pdf_weight_up );
    reco_chain->SetBranchAddress("pdf_weight_down", &pdf_weight_down );
    reco_chain->SetBranchAddress("q2_weight_up", &q2_weight_up );
    reco_chain->SetBranchAddress("q2_weight_down", &q2_weight_down );
    reco_chain->SetBranchAddress("ps_weights", &ps_weights );
    */

    // For PU calculation
    int n_pu_size = 98;
    int npv_dist[n_pu_size];
    for (int i=0; i<n_pu_size; i++)
        npv_dist[i] = 0;
    ofstream fout_pu;
    fout_pu.open("PU_MC.txt");

    if(is_data_input==0){
        std::cout << "========  Starting Event Loop for Comm Tree ========" << std::endl;
        for (Long64_t ievt=0; ievt<comm_chain->GetEntries();ievt++) {

            if( ievt<firstEvent_comm ) continue;
            if( ievt==lastEvent_comm ) break;

            if( ievt==0 )        std::cout << "     Event " << ievt+1 << std::endl;
            if( ievt%10000==0 && ievt!=1) std::cout << "           " << ievt << "\t"
                << int(double(ievt-1)/double(nentries_comm)*100) << "% done" << std::endl;

            if( ievt==(maxNentries+1) && ievt!=0 ) break;

            comm_chain->GetEntry(ievt);

            N_total++;

            int nEvent_comm = comm_ntuple->nEvent;
            int npv_comm = comm_ntuple->npv;
            double gen_weight_comm = comm_ntuple->gen_weight;
            double PU_weight_comm = comm_ntuple->PU_weight;
            double PU_weight_up_comm = comm_ntuple->PU_weight_up;
            double PU_weight_down_comm = comm_ntuple->PU_weight_down;

            if(gen_weight_comm >= 0)
                sum_pos_gen_weights += gen_weight_comm;
            else if(gen_weight_comm < 0)
                sum_neg_gen_weights += gen_weight_comm;
            sum_gen_weights = sum_pos_gen_weights + sum_neg_gen_weights;
            prod_gen_weights *= gen_weight_comm;

            sum_gen_PU_weights += gen_weight_comm*PU_weight_comm;
            sum_gen_PU_up_weights += gen_weight_comm*PU_weight_up_comm;
            sum_gen_PU_down_weights += gen_weight_comm*PU_weight_down_comm;

            // For PU weight calculation
            for (int i=0; i<n_pu_size; i++){
                if ( npv_comm>=n_pu_size ){
                    npv_dist[n_pu_size-1]++;
                    break;
                }
                else if ( npv_comm>=i && npv_comm<(i+1) ){
                    npv_dist[i]++;
                    break;
                }
            }
        }
    }
    std::cout << "Comm Tree Done! \n\n";

    // PU weight calculation
    int PU_x[100];
    long  double PU_y[100], PU_y_up[100], PU_y_down[100];
    if (is_data_input == 0){
        std::cout<<"Starting PU weight calculation\n";
        for (int i=0; i<n_pu_size; i++)
            fout_pu<<(double)npv_dist[i]/(double)N_total<<"\n";
        fout_pu.close();
        /*
        system("cp Pile_Up_Calc/* .");
        system("./Pileup_calculation_script.sh");
        system("rm -rf Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt Pileup_calculation_script.sh PU_data_hist_prod.C pileupCalc.py pileup_latest.txt PU_hist_calc.cc");
        std::cout<<"PU weight calculation Done\n\n";
         */
        ifstream fin_pu;
        fin_pu.open("PU_weights.txt");
        for (int i = 0; i<n_pu_size; ++i) {
            fin_pu>>PU_x[i]>>PU_y[i]>>PU_y_up[i]>>PU_y_down[i];
        }
        fin_pu.close();
    }
    else{
        for (int i = 0; i<n_pu_size; ++i) {
            PU_x[i] = 1.0;
            PU_y[i] = 1.0;
            PU_y_up[i] = 1.0;
            PU_y_down[i] = 1.0;
        }
    }

    std::cout << "========  Starting Event Loop for Reco Tree ========" << std::endl;
     for (Long64_t ievt=0; ievt<reco_chain->GetEntries();ievt++) {

        if( ievt<firstEvent ) continue;
        if( ievt==lastEvent ) break;

          if( ievt==0 )        std::cout << "     Event " << ievt+1 << std::endl;
          if( ievt%10000==0 && ievt!=1) std::cout << "           " << ievt << "\t"
                           << int(double(ievt-1)/double(nentries)*100) << "% done" << std::endl;

         if( ievt==(maxNentries+1) && ievt!=0 ) break;

        reco_chain->GetEntry(ievt);
        if(is_data_input==0)
            gen_chain->GetEntry(ievt);

        int nEvent = reco_ntuple->nEvent;
        int ls = reco_ntuple->ls;
        int run = reco_ntuple->run;
        int is_data = reco_ntuple->is_data;
        int data_era = reco_ntuple->data_era;
        int save_gen_info = reco_ntuple->save_gen_info;
        int is_trigger_study = reco_ntuple->is_trigger_study;
        int is_tight_skim = reco_ntuple->is_tight_skim;
        int npv = reco_ntuple->npv;
        int ttHf_cat = reco_ntuple->ttHf_cat;
        int ttHFGenFilter = reco_ntuple->ttHFGenFilter;

        int pass_HLT_Ele35_WPTight_Gsf = reco_ntuple->pass_HLT_Ele35_WPTight_Gsf_;
        int pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned = reco_ntuple->pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned_;
        int pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150 = reco_ntuple->pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150_;
        int pass_HLT_IsoMu27 = reco_ntuple->pass_HLT_IsoMu27_;
        int pass_HLT_IsoMu24_eta2p1 = reco_ntuple->pass_HLT_IsoMu24_eta2p1_;
        int pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = reco_ntuple->pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_;
        int pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = reco_ntuple->pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
        int pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = reco_ntuple->pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_;
        int pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = reco_ntuple->pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
        int pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = reco_ntuple->pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
        int pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = reco_ntuple->pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
        int pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = reco_ntuple->pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_;
        int pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 = reco_ntuple->pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_;
        int pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 = reco_ntuple->pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_;

        vdouble mu_pt = reco_ntuple->mu_pt;
        vdouble mu_pt_uncorr = reco_ntuple->mu_pt_uncorr;
        vdouble mu_eta = reco_ntuple->mu_eta;
        vdouble mu_phi = reco_ntuple->mu_phi;
        vdouble mu_E = reco_ntuple->mu_E;
        vdouble mu_iso = reco_ntuple->mu_iso;
        vint mu_pdgid = reco_ntuple->mu_pdgid;

        vdouble ele_pt = reco_ntuple->ele_pt;
        vdouble ele_pt_uncorr = reco_ntuple->ele_pt_uncorr;
        vdouble ele_eta = reco_ntuple->ele_eta;
        vdouble ele_sc_eta = reco_ntuple->ele_sc_eta;
        vdouble ele_phi = reco_ntuple->ele_phi;
        vdouble ele_E = reco_ntuple->ele_E;
        vdouble ele_iso = reco_ntuple->ele_iso;
        vint ele_pdgid = reco_ntuple->ele_pdgid;

        vdouble jet_pt_uncorr = reco_ntuple->jet_pt_uncorr;
        vdouble jet_eta = reco_ntuple->jet_eta;
        vdouble jet_phi = reco_ntuple->jet_phi;
        vdouble jet_E = reco_ntuple->jet_E;
        vdouble jet_CSV = reco_ntuple->jet_CSV;
        vint jet_flavor = reco_ntuple->jet_flavor;
        vint jet_puid = reco_ntuple->jet_puid;
        vdouble jet_pudisc = reco_ntuple->jet_pudisc;

        double met_pt_phi_corr = reco_ntuple->met_pt_phi_corr;
        double met_phi_phi_corr = reco_ntuple->met_phi_phi_corr;
        double met_pt_jer_up = reco_ntuple->met_pt_jer_up;
        double met_phi_jer_up = reco_ntuple->met_phi_jer_up;
        double met_pt_jer_down = reco_ntuple->met_pt_jer_down;
        double met_phi_jer_down = reco_ntuple->met_phi_jer_down;

        vdouble jet_jecSF_nominal = reco_ntuple->jet_jecSF_nominal;
        vdouble jet_jecSF_nominal_up = reco_ntuple->jet_jecSF_nominal_up;
        vdouble jet_jecSF_nominal_down = reco_ntuple->jet_jecSF_nominal_down;
        vvdouble jet_jesSF_up = reco_ntuple->jet_jesSF_up;
        vvdouble jet_jesSF_down = reco_ntuple->jet_jesSF_down;
        vdouble jet_jerSF_jesnominal_nominal = reco_ntuple->jet_jerSF_jesnominal_nominal;
        vdouble jet_jerSF_jesnominal_up = reco_ntuple->jet_jerSF_jesnominal_up;
        vdouble jet_jerSF_jesnominal_down = reco_ntuple->jet_jerSF_jesnominal_down;
        vvdouble jet_jerSF_jesup_nominal = reco_ntuple->jet_jerSF_jesup_nominal;
        vvdouble jet_jerSF_jesdown_nominal = reco_ntuple->jet_jerSF_jesdown_nominal;

         vdouble ele_sf_id_combined = reco_ntuple->ele_sf_id_combined;
         vdouble ele_sf_id_up_combined = reco_ntuple->ele_sf_id_up_combined;
         vdouble ele_sf_id_down_combined = reco_ntuple->ele_sf_id_down_combined;
         vdouble ele_sf_iso_combined = reco_ntuple->ele_sf_iso_combined;
         vdouble ele_sf_iso_up_combined = reco_ntuple->ele_sf_iso_up_combined;
         vdouble ele_sf_iso_down_combined = reco_ntuple->ele_sf_iso_down_combined;
         vdouble ele_sf_id_rundep = reco_ntuple->ele_sf_id_rundep;
         vdouble ele_sf_id_up_rundep = reco_ntuple->ele_sf_id_up_rundep;
         vdouble ele_sf_id_down_rundep = reco_ntuple->ele_sf_id_down_rundep;
         vdouble ele_sf_iso_rundep = reco_ntuple->ele_sf_iso_rundep;
         vdouble ele_sf_iso_up_rundep = reco_ntuple->ele_sf_iso_up_rundep;
         vdouble ele_sf_iso_down_rundep = reco_ntuple->ele_sf_iso_down_rundep;

         vdouble mu_sf_id_combined = reco_ntuple->mu_sf_id_combined;
         vdouble mu_sf_id_up_combined = reco_ntuple->mu_sf_id_up_combined;
         vdouble mu_sf_id_down_combined = reco_ntuple->mu_sf_id_down_combined;
         vdouble mu_sf_iso_combined = reco_ntuple->mu_sf_iso_combined;
         vdouble mu_sf_iso_up_combined = reco_ntuple->mu_sf_iso_up_combined;
         vdouble mu_sf_iso_down_combined = reco_ntuple->mu_sf_iso_down_combined;
         vdouble mu_sf_tracking_combined = reco_ntuple->mu_sf_tracking_combined;
         vdouble mu_sf_tracking_up_combined = reco_ntuple->mu_sf_tracking_up_combined;
         vdouble mu_sf_tracking_down_combined = reco_ntuple->mu_sf_tracking_down_combined;
         vdouble mu_sf_id_rundep = reco_ntuple->mu_sf_id_rundep;
         vdouble mu_sf_id_up_rundep = reco_ntuple->mu_sf_id_up_rundep;
         vdouble mu_sf_id_down_rundep = reco_ntuple->mu_sf_id_down_rundep;
         vdouble mu_sf_iso_rundep = reco_ntuple->mu_sf_iso_rundep;
         vdouble mu_sf_iso_up_rundep = reco_ntuple->mu_sf_iso_up_rundep;
         vdouble mu_sf_iso_down_rundep = reco_ntuple->mu_sf_iso_down_rundep;
         vdouble mu_sf_tracking_rundep = reco_ntuple->mu_sf_tracking_rundep;
         vdouble mu_sf_tracking_up_rundep = reco_ntuple->mu_sf_tracking_up_rundep;
         vdouble mu_sf_tracking_down_rundep = reco_ntuple->mu_sf_tracking_down_rundep;

        vdouble b_weight_jesnominal_nominal = reco_ntuple->b_weight_jesnominal_nominal;
        vdouble b_weight_jesnominal_hfup = reco_ntuple->b_weight_jesnominal_hfup;
        vdouble b_weight_jesnominal_hfdown = reco_ntuple->b_weight_jesnominal_hfdown;
        vdouble b_weight_jesnominal_hfstats1up = reco_ntuple->b_weight_jesnominal_hfstats1up;
        vdouble b_weight_jesnominal_hfstats1down = reco_ntuple->b_weight_jesnominal_hfstats1down;
        vdouble b_weight_jesnominal_hfstats2up = reco_ntuple->b_weight_jesnominal_hfstats2up;
        vdouble b_weight_jesnominal_hfstats2down = reco_ntuple->b_weight_jesnominal_hfstats2down;
        vdouble b_weight_jesnominal_lfup = reco_ntuple->b_weight_jesnominal_lfup;
        vdouble b_weight_jesnominal_lfdown = reco_ntuple->b_weight_jesnominal_lfdown;
        vdouble b_weight_jesnominal_lfstats1up = reco_ntuple->b_weight_jesnominal_lfstats1up;
        vdouble b_weight_jesnominal_lfstats1down = reco_ntuple->b_weight_jesnominal_lfstats1down;
        vdouble b_weight_jesnominal_lfstats2up = reco_ntuple->b_weight_jesnominal_lfstats2up;
        vdouble b_weight_jesnominal_lfstats2down = reco_ntuple->b_weight_jesnominal_lfstats2down;
        vdouble b_weight_jesnominal_cferr1up = reco_ntuple->b_weight_jesnominal_cferr1up;
        vdouble b_weight_jesnominal_cferr1down = reco_ntuple->b_weight_jesnominal_cferr1down;
        vdouble b_weight_jesnominal_cferr2up = reco_ntuple->b_weight_jesnominal_cferr2up;
        vdouble b_weight_jesnominal_cferr2down = reco_ntuple->b_weight_jesnominal_cferr2down;
        vvdouble b_weight_jesup_nominal = reco_ntuple->b_weight_jesup_nominal;
        vvdouble b_weight_jesdown_nominal = reco_ntuple->b_weight_jesdown_nominal;

        double gen_weight = reco_ntuple->gen_weight;
        double PU_weight = reco_ntuple->PU_weight;
        double PU_weight_up = reco_ntuple->PU_weight_up;
        double PU_weight_down = reco_ntuple->PU_weight_down;
        double pdf_weight_up = reco_ntuple->pdf_weight_up;
        double pdf_weight_down = reco_ntuple->pdf_weight_down;
        double q2_weight_up = reco_ntuple->q2_weight_up;
        double q2_weight_down = reco_ntuple->q2_weight_down;
        vdouble ps_weights = reco_ntuple->ps_weights;

        if (is_data != is_data_input){
            std::cout<<"Mismatch in MC/DATA type between input and ntuple\n";
            return;
        }

        // Basic event selection already in ntuples
        N_basic_sel++;

        bool is_ttbb = 0;
        bool is_ttb = 0;
        bool is_tt2b = 0;
        bool is_ttcc = 0;
        bool is_ttlf = 0;

        // Checking ttjets category = ttbb, ttb, tt2b, ttcc, ttlf
        if(ttHf_cat != -1){
            double mod_ttHFcat = ttHf_cat%100;
            if( (mod_ttHFcat >= 53) && (mod_ttHFcat <= 55) )
                is_ttbb = 1;
            else if( mod_ttHFcat == 52  )
                is_tt2b = 1;
            else if( mod_ttHFcat == 51  )
                is_ttb = 1;
            else if( (mod_ttHFcat >= 41) && (mod_ttHFcat <= 45) )
                is_ttcc = 1;
            else if ( mod_ttHFcat == 0 )
                is_ttlf = 1;
        }

        if (process.find("ttbb")!=std::string::npos){
            if(!is_ttbb)
                continue;
        }
        else if (process.find("ttb")!=std::string::npos){
            if(!is_ttb)
                continue;
        }
        else if (process.find("tt2b")!=std::string::npos){
            if(!is_tt2b)
                continue;
        }
        else if (process.find("ttcc")!=std::string::npos){
            if(!is_ttcc)
                continue;
        }
        else if (process.find("ttlf")!=std::string::npos){
            if(!is_ttlf)
                continue;
        }

        if(ttHFGenFilter==-1)
            ttHFGenFilter = 0;

        // Object Selections

        vint sel_ele_sl_index;
        vint sel_ele_veto_sl_index;
        vint sel_ele_di_index;
        vint sel_ele_di_sorted_index;
        vint sel_mu_sl_index;
        vint sel_mu_veto_sl_index;
        vint sel_mu_di_index;
        vint sel_mu_di_sorted_index;
        vint sel_jet_sl_index;
        vint sel_jet_di_index;
        vint sel_jet_sl_sorted_index;
        vint sel_jet_di_sorted_index;
        vdouble jet_pt_corr;
        vdouble jet_E_corr;

        sel_ele_sl_index.clear();
        sel_ele_veto_sl_index.clear();
        sel_ele_di_index.clear();
        sel_ele_di_sorted_index.clear();
        sel_mu_sl_index.clear();
        sel_mu_veto_sl_index.clear();
        sel_mu_di_index.clear();
        sel_mu_di_sorted_index.clear();
        sel_jet_sl_index.clear();
        sel_jet_di_index.clear();
        sel_jet_sl_sorted_index.clear();
        sel_jet_di_sorted_index.clear();
        jet_pt_corr.clear();
        jet_E_corr.clear();

        int n_ele_sl = 0;
        int n_ele_veto_sl = 0;
        int n_mu_sl = 0;
        int n_mu_veto_sl = 0;
        int n_ele_di = 0;
        int n_mu_di = 0;
        int n_jet_sl = 0;
        int n_jet_di = 0;
        int n_jet_di_lead = 0;
        int n_btag_sl = 0;
        int n_btag_di = 0;


        // Applying JEC and JER (nominal)
        double jec, jer, jes;
        for (int i=0; i<(int)jet_pt_uncorr.size(); i++){
            jec = jer = jes = 1.0;
            if (jet_sys.find("Nominal")!=std::string::npos){
                jec = jet_jecSF_nominal[i];
                jer = jet_jerSF_jesnominal_nominal[i];
            }
            jes = jec*jer;
            jet_pt_corr.push_back(jet_pt_uncorr[i]*jes);
            jet_E_corr.push_back(jet_E[i]*jes);
        }

        // SL object selections
        // Electrons
        for (int i=0; i<(int)ele_pt.size(); i++){
            if (ele_pt[i] > min_sl_veto_ele_pt && fabs(ele_eta[i]) < max_sl_veto_ele_eta){
                sel_ele_veto_sl_index.push_back(i);
                n_ele_veto_sl++;
                if (ele_pt[i] > min_sl_ele_pt && fabs(ele_eta[i]) < max_sl_ele_eta){
                    sel_ele_sl_index.push_back(i);
                    n_ele_sl++;
                }
            }
        }
        // Muons
        for (int i=0; i<(int)mu_pt_uncorr.size(); i++){
            if (mu_pt_uncorr[i] > min_sl_veto_mu_pt && fabs(mu_eta[i]) < max_sl_veto_mu_eta && mu_iso[i] < max_mu_loose_iso){
                sel_mu_veto_sl_index.push_back(i);
                n_mu_veto_sl++;
                if (mu_pt_uncorr[i] > min_sl_mu_pt && fabs(mu_eta[i]) < max_sl_mu_eta && mu_iso[i] < max_mu_tight_iso){
                    sel_mu_sl_index.push_back(i);
                    n_mu_sl++;
                }
            }
        }
        // Jets
        for (int i=0; i<(int)jet_pt_corr.size(); i++){
            if (jet_pt_corr[i] > min_jet_pt && fabs(jet_eta[i]) < max_jet_eta && jet_puid[i] >= min_pujetid_sl ){

                // dR check with leptons
                bool dR_pass = 1;
                double dR;
                for(int j=0; j<(int)sel_ele_veto_sl_index.size(); j++){
                    dR = dR_calc(jet_eta[i], jet_phi[i], ele_eta[sel_ele_veto_sl_index[j]], ele_phi[sel_ele_veto_sl_index[j]]);
                    if (dR <= lep_jet_min_dR){
                        dR_pass = 0;
                        break;
                    }
                }
                if (!dR_pass)
                    continue;
                for(int j=0; j<(int)sel_mu_veto_sl_index.size(); j++){
                    dR = dR_calc(jet_eta[i], jet_phi[i], mu_eta[sel_mu_veto_sl_index[j]], mu_phi[sel_mu_veto_sl_index[j]]);
                    if (dR <= lep_jet_min_dR){
                        dR_pass = 0;
                        break;
                    }
                }
                if (!dR_pass)
                    continue;

                sel_jet_sl_index.push_back(i);
                n_jet_sl++;
                if (jet_CSV[i] > jet_csv_med_cut)
                    n_btag_sl++;

            }
        }

        // Sorting Jets
        vint temp = sel_jet_sl_index;
        for (int i=0; i<n_jet_sl; i++){

            double temp_max = 0;
            int index_max = 0;
            for(int j=0; j<(int)temp.size(); j++){
                if(jet_pt_corr[temp[j]] > temp_max){
                    temp_max = jet_pt_corr[temp[j]];
                    index_max = j;
                }
            }
            sel_jet_sl_sorted_index.push_back(temp[index_max]);
            temp.erase(temp.begin()+index_max);
        }

        // DL object selections (subleading)
        // Electrons
        for (int i=0; i<(int)ele_pt.size(); i++){
            if (ele_pt[i] > min_di_ele2_pt && fabs(ele_eta[i]) < max_di_ele2_eta){
                sel_ele_di_index.push_back(i);
                n_ele_di++;
            }
        }
        // Muons
        for (int i=0; i<(int)mu_pt_uncorr.size(); i++){
            if (mu_pt_uncorr[i] > min_di_mu2_pt && fabs(mu_eta[i]) < max_di_mu2_eta && mu_iso[i] < max_mu_loose_iso){
                sel_mu_di_index.push_back(i);
                n_mu_di++;
            }
        }
        // Jets
        for (int i=0; i<(int)jet_pt_corr.size(); i++){
            if (jet_pt_corr[i] > min_jet2_pt && fabs(jet_eta[i]) < max_jet_eta && jet_puid[i] >= min_pujetid_di ){

                // dR check with leptons
                bool dR_pass = 1;
                double dR;
                for(int j=0; j<(int)sel_ele_di_index.size(); j++){
                    dR = dR_calc(jet_eta[i], jet_phi[i], ele_eta[sel_ele_di_index[j]], ele_phi[sel_ele_di_index[j]]);
                    if (dR <= lep_jet_min_dR){
                        dR_pass = 0;
                        break;
                    }
                }
                if (!dR_pass)
                    continue;
                for(int j=0; j<(int)sel_mu_di_index.size(); j++){
                    dR = dR_calc(jet_eta[i], jet_phi[i], mu_eta[sel_mu_di_index[j]], mu_phi[sel_mu_di_index[j]]);
                    if (dR <= lep_jet_min_dR){
                        dR_pass = 0;
                        break;
                    }
                }
                if (!dR_pass)
                    continue;

                sel_jet_di_index.push_back(i);
                n_jet_di++;
                if (jet_CSV[i] > jet_csv_med_cut)
                    n_btag_di++;
                if (jet_pt_corr[i] > min_jet_pt)
                    n_jet_di_lead++;
            }
        }

        // Sorting Electrons
        vint temp3 = sel_ele_di_index;
        for (int i=0; i<n_ele_di; i++){

            double temp_max = 0;
            int index_max = 0;
            for(int j=0; j<(int)temp3.size(); j++){
                if(ele_pt[temp3[j]] > temp_max){
                    temp_max = ele_pt[temp3[j]];
                    index_max = j;
                }
            }
            sel_ele_di_sorted_index.push_back(temp3[index_max]);
            temp3.erase(temp3.begin()+index_max);
        }

        // Sorting Muons
        vint temp4 = sel_mu_di_index;
        for (int i=0; i<n_mu_di; i++){

            double temp_max = 0;
            int index_max = 0;
            for(int j=0; j<(int)temp4.size(); j++){
                if(mu_pt_uncorr[temp4[j]] > temp_max){
                    temp_max = mu_pt_uncorr[temp4[j]];
                    index_max = j;
                }
            }
            sel_mu_di_sorted_index.push_back(temp4[index_max]);
            temp4.erase(temp4.begin()+index_max);
        }

        // Sorting Jets
        vint temp2 = sel_jet_di_index;
        for (int i=0; i<n_jet_di; i++){

            double temp_max = 0;
            int index_max = 0;
            for(int j=0; j<(int)temp2.size(); j++){
                if(jet_pt_corr[temp2[j]] > temp_max){
                    temp_max = jet_pt_corr[temp2[j]];
                    index_max = j;
                }
            }
            sel_jet_di_sorted_index.push_back(temp2[index_max]);
            temp2.erase(temp2.begin()+index_max);
        }

        double mll = -1;

        // Trigger Selections

        bool trigger_pass_e = 0;
        bool trigger_pass_mu = 0;
        bool trigger_pass_ee = 0;
        bool trigger_pass_emu = 0;
        bool trigger_pass_mumu = 0;

        bool trig_e = (pass_HLT_Ele35_WPTight_Gsf==1) || (pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150==1);
        bool trig_mu_mc = (pass_HLT_IsoMu27==1) || (pass_HLT_IsoMu24_eta2p1==1);
        bool trig_mu_bcd = (pass_HLT_IsoMu27==1) || (pass_HLT_IsoMu24_eta2p1==1);
        bool trig_mu_ef = (pass_HLT_IsoMu27==1);
        bool trig_ee = (pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL==1) || (pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ==1) ;
        bool trig_emu = (pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL==1) || (pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ==1) || (pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ==1) || (pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ==1);
        bool trig_mumu_mc = (pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ==1) || (pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8==1) || (pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8==1);
        bool trig_mumu_b = (pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ==1);
        bool trig_mumu_cdef = (pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8==1) || (pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8==1);
        bool trig_mu;
        bool trig_mumu;

        if (is_data_input==1){
            if ((sample_dataset.find("2017B")!=std::string::npos) || (sample_dataset.find("2017C")!=std::string::npos) || (sample_dataset.find("2017D")!=std::string::npos))
                trig_mu = trig_mu_bcd;
            else
                trig_mu = trig_mu_ef;

            if ((sample_dataset.find("2017B")!=std::string::npos))
                trig_mumu = trig_mumu_b;
            else
                trig_mumu = trig_mumu_cdef;
        }
        else{
            trig_mu = trig_mu_mc;
            trig_mumu = trig_mumu_mc;
        }

        if (is_data_input==1){
            if (sample_dataset.find("se")!=std::string::npos){
                if (trig_e)
                    trigger_pass_e = 1;
                if (trig_e && !trig_ee)
                    trigger_pass_ee = 1;
                if (trig_e && !trig_mu && !trig_emu)
                    trigger_pass_emu = 1;
            }
            else if (sample_dataset.find("sm")!=std::string::npos){
                if (trig_mu)
                    trigger_pass_mu = 1;
                if (trig_mu && !trig_mumu)
                    trigger_pass_mumu = 1;
                if (trig_mu && !trig_e && !trig_emu)
                    trigger_pass_emu = 1;
            }
            else if (sample_dataset.find("de")!=std::string::npos){
                if (trig_ee)
                    trigger_pass_ee = 1;
            }
            else if (sample_dataset.find("em")!=std::string::npos){
                if (trig_emu)
                    trigger_pass_emu = 1;
            }
            else if (sample_dataset.find("dm")!=std::string::npos){
                if (trig_mumu)
                    trigger_pass_mumu = 1;
            }
        }
        else{
            if (trig_e)
                trigger_pass_e = 1;
            if (trig_mu)
                trigger_pass_mu = 1;
            if (trig_ee || trig_e)
                trigger_pass_ee = 1;
            if (trig_emu || trig_e || trig_mu)
                trigger_pass_emu = 1;
            if (trig_mumu || trig_mu)
                trigger_pass_mumu = 1;
        }

        // Full Event Selection

        bool is_e = 0;
        bool is_mu = 0;
        bool is_ee = 0;
        bool is_emu = 0;
        bool is_mumu = 0;
        bool is_SL = 0;
        bool is_DL = 0;

        int N_sel_count = 0;

        // SL event selection

        // selection for - e
        if (n_ele_sl==1){
            if (n_ele_veto_sl == 1 && n_mu_veto_sl == 0){
                if (trigger_pass_e){
                    if (n_jet_sl >= min_sl_njets && n_btag_sl >= min_sl_nbtags){
                        if (met_pt_phi_corr > min_sl_met){
                            is_e = 1;
                            N_e_raw++;
                            N_SL_raw++;
                            N_sel_count++;
                        }
                    }
                }
            }
        }

        // selection for - mu
        if (n_mu_sl==1){
            if (n_mu_veto_sl == 1 && n_ele_veto_sl == 0){
                if (trigger_pass_mu){
                    if (n_jet_sl >= min_sl_njets && n_btag_sl >= min_sl_nbtags){
                        if (met_pt_phi_corr > min_sl_met){
                            is_mu = 1;
                            N_mu_raw++;
                            N_SL_raw++;
                            N_sel_count++;
                        }
                    }
                }
            }
        }

        is_SL = is_e || is_mu;

        // DL event selection

        // selection for - ee
        if (n_ele_di==2 && n_mu_di==0){
            if ( (ele_pdgid[sel_ele_di_index[0]])*(ele_pdgid[sel_ele_di_index[1]]) < 0 ){
                if( (ele_pt[sel_ele_di_sorted_index[0]] > min_di_ele1_pt)){
                    if (trigger_pass_ee){
                        if (n_jet_di_lead >= min_di_njets && n_btag_di >= min_di_nbtags){
                            if (met_pt_phi_corr > min_di_met){
                                mll = dilepton_invariant_mass( ele_E[sel_ele_di_index[0]], ele_pt[sel_ele_di_index[0]], ele_eta[sel_ele_di_index[0]], ele_phi[sel_ele_di_index[0]], ele_E[sel_ele_di_index[1]], ele_pt[sel_ele_di_index[1]], ele_eta[sel_ele_di_index[1]], ele_phi[sel_ele_di_index[1]] );
                                if (mll > min_di_mll){
                                    if (mll <= 76 || mll >= 106){
                                        is_ee = 1;
                                        N_ee_raw++;
                                        N_DL_raw++;
                                        N_sel_count++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // selection for - emu
        if (n_ele_di==1 && n_mu_di==1){
            if ( (ele_pdgid[sel_ele_di_index[0]])*(mu_pdgid[sel_mu_di_index[0]]) < 0 ){
                if( (ele_pt[sel_ele_di_index[0]] > min_di_ele1_pt) || (mu_pt_uncorr[sel_mu_di_index[0]] > min_di_mu1_pt) ){
                    if (trigger_pass_emu){
                        if (n_jet_di_lead >= min_di_njets && n_btag_di >= min_di_nbtags){
                            mll = dilepton_invariant_mass( ele_E[sel_ele_di_index[0]], ele_pt[sel_ele_di_index[0]], ele_eta[sel_ele_di_index[0]], ele_phi[sel_ele_di_index[0]], mu_E[sel_mu_di_index[0]], mu_pt_uncorr[sel_mu_di_index[0]], mu_eta[sel_mu_di_index[0]], mu_phi[sel_mu_di_index[0]] );
                            if (mll > min_di_mll){
                                is_emu = 1;
                                N_emu_raw++;
                                N_DL_raw++;
                                N_sel_count++;
                            }
                        }
                    }
                }
            }
        }

        // selection for - mumu
        if (n_mu_di==2 && n_ele_di==0){
            if ( (mu_pdgid[sel_mu_di_index[0]])*(mu_pdgid[sel_mu_di_index[1]]) < 0 ){
                if( (mu_pt_uncorr[sel_mu_di_sorted_index[0]] > min_di_mu1_pt)){
                    if (trigger_pass_mumu){
                        if (n_jet_di_lead >= min_di_njets && n_btag_di >= min_di_nbtags){
                            if (met_pt_phi_corr > min_di_met){
                                mll = dilepton_invariant_mass( mu_E[sel_mu_di_index[0]], mu_pt_uncorr[sel_mu_di_index[0]], mu_eta[sel_mu_di_index[0]], mu_phi[sel_mu_di_index[0]], mu_E[sel_mu_di_index[1]], mu_pt_uncorr[sel_mu_di_index[1]], mu_eta[sel_mu_di_index[1]], mu_phi[sel_mu_di_index[1]] );
                                if (mll > min_di_mll){
                                    if (mll <= 76 || mll >= 106){
                                        is_mumu = 1;
                                        N_mumu_raw++;
                                        N_DL_raw++;
                                        N_sel_count++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        is_DL = is_ee || is_emu || is_mumu;

        if(N_sel_count>1){
            std::cout<<"Error in event selection : multiple selections\n";
            return;
        }

        if(!is_SL && !is_DL)
            continue;

        // Calculating CSV SFs
        double csv_sf_jesnominal_nominal = 1;
        double csv_sf_jesnominal_hfup = 1;
        double csv_sf_jesnominal_hfdown = 1;
        double csv_sf_jesnominal_hfstats1up = 1;
        double csv_sf_jesnominal_hfstats1down = 1;
        double csv_sf_jesnominal_hfstats2up = 1;
        double csv_sf_jesnominal_hfstats2down = 1;
        double csv_sf_jesnominal_lfup = 1;
        double csv_sf_jesnominal_lfdown = 1;
        double csv_sf_jesnominal_lfstats1up = 1;
        double csv_sf_jesnominal_lfstats1down = 1;
        double csv_sf_jesnominal_lfstats2up = 1;
        double csv_sf_jesnominal_lfstats2down = 1;
        double csv_sf_jesnominal_cferr1up = 1;
        double csv_sf_jesnominal_cferr1down = 1;
        double csv_sf_jesnominal_cferr2up = 1;
        double csv_sf_jesnominal_cferr2down = 1;
        double csv_sf_jesup_nominal[26];
        double csv_sf_jesdown_nominal[26];
        for(int i=0; i<26; i++){
            csv_sf_jesup_nominal[i]=1;
            csv_sf_jesdown_nominal[i]=1;
        }

        if (is_SL){
            for(int i=0; i<(int)sel_jet_sl_sorted_index.size(); i++){
                csv_sf_jesnominal_nominal *= b_weight_jesnominal_nominal[sel_jet_sl_sorted_index[i]];
                /*
                csv_sf_jesnominal_hfup *= b_weight_jesnominal_hfup[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_hfdown *= b_weight_jesnominal_hfdown[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_hfstats1up *= b_weight_jesnominal_hfstats1up[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_hfstats1down *= b_weight_jesnominal_hfstats1down[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_hfstats2up *= b_weight_jesnominal_hfstats2up[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_hfstats2down *= b_weight_jesnominal_hfstats2down[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_lfup *= b_weight_jesnominal_lfup[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_lfdown *= b_weight_jesnominal_lfdown[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_lfstats1up *= b_weight_jesnominal_lfstats1up[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_lfstats1down *= b_weight_jesnominal_lfstats1down[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_lfstats2up *= b_weight_jesnominal_lfstats2up[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_lfstats2down *= b_weight_jesnominal_lfstats2down[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_cferr1up *= b_weight_jesnominal_cferr1up[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_cferr1down *= b_weight_jesnominal_cferr1down[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_cferr2up *= b_weight_jesnominal_cferr2up[sel_jet_sl_sorted_index[i]];
                csv_sf_jesnominal_cferr2down *= b_weight_jesnominal_cferr2down[sel_jet_sl_sorted_index[i]];
                for(int j=0; j<26; j++){
                    csv_sf_jesup_nominal[j] *= b_weight_jesup_nominal[j][sel_jet_sl_sorted_index[i]];
                    csv_sf_jesdown_nominal[j] *= b_weight_jesdown_nominal[j][sel_jet_sl_sorted_index[i]];
                }
                */
            }
        }
        else if (is_DL){
            for(int i=0; i<(int)sel_jet_di_sorted_index.size(); i++){
                csv_sf_jesnominal_nominal *= b_weight_jesnominal_nominal[sel_jet_di_sorted_index[i]];
                /*
                csv_sf_jesnominal_hfup *= b_weight_jesnominal_hfup[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_hfdown *= b_weight_jesnominal_hfdown[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_hfstats1up *= b_weight_jesnominal_hfstats1up[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_hfstats1down *= b_weight_jesnominal_hfstats1down[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_hfstats2up *= b_weight_jesnominal_hfstats2up[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_hfstats2down *= b_weight_jesnominal_hfstats2down[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_lfup *= b_weight_jesnominal_lfup[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_lfdown *= b_weight_jesnominal_lfdown[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_lfstats1up *= b_weight_jesnominal_lfstats1up[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_lfstats1down *= b_weight_jesnominal_lfstats1down[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_lfstats2up *= b_weight_jesnominal_lfstats2up[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_lfstats2down *= b_weight_jesnominal_lfstats2down[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_cferr1up *= b_weight_jesnominal_cferr1up[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_cferr1down *= b_weight_jesnominal_cferr1down[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_cferr2up *= b_weight_jesnominal_cferr2up[sel_jet_di_sorted_index[i]];
                csv_sf_jesnominal_cferr2down *= b_weight_jesnominal_cferr2down[sel_jet_di_sorted_index[i]];
                for(int j=0; j<26; j++){
                    csv_sf_jesup_nominal[j] *= b_weight_jesup_nominal[j][sel_jet_di_sorted_index[i]];
                    csv_sf_jesdown_nominal[j] *= b_weight_jesdown_nominal[j][sel_jet_di_sorted_index[i]];
                }
                */
            }
        }

        // Calculating trigger SF
        double trigger_SF = 1.0;
        double trigger_SF_up = 1.0;
        double trigger_SF_down = 1.0;
        /*
        if(is_data_input==0){
            int thisBin=0;
            double searchEta;
            double searchEta1;
            double searchEta2;
            double searchPt;
            double nomval = 0;
            double error = 0;
            double upval = 0;
            double downval= 0;

            double electronMaxPt = 149.99;
            double muonMaxPt = 119.99;
            double electronMaxPt_High = 200.01;
            double muonMaxPt_High = 499.99;

            if (is_e){
                searchPt = TMath::Min( ele_pt_uncorr[sel_ele_sl_index[0]] , electronMaxPt_High );
                searchEta = ele_sc_eta[sel_ele_sl_index[0]];

                thisBin = h_ele_TRIGGER_abseta_pt_ratio->FindBin( searchPt, searchEta );
                nomval = h_ele_TRIGGER_abseta_pt_ratio->GetBinContent( thisBin );
                error = h_ele_TRIGGER_abseta_pt_ratio->GetBinError( thisBin );
                if(nomval==0) {
                    thisBin = h_ele_TRIGGER_abseta_pt_ratio->FindBin( 25.001, searchEta );
                    nomval = h_ele_TRIGGER_abseta_pt_ratio->GetBinContent( thisBin );
                    error = h_ele_TRIGGER_abseta_pt_ratio->GetBinError( thisBin );
                }
                upval = nomval + error;
                downval = nomval - error;
            }
            else if (is_mu){
                searchPt = searchPt=TMath::Min( mu_pt_uncorr[sel_mu_sl_index[0]] , muonMaxPt_High );
                searchEta = fabs(mu_eta[sel_mu_sl_index[0]]);

                thisBin = h_mu_TRIGGER_BF_abseta_pt_ratio->FindBin( searchPt, searchEta );
                double nomval_BF = h_mu_TRIGGER_BF_abseta_pt_ratio->GetBinContent(thisBin);
                double error_BF = h_mu_TRIGGER_BF_abseta_pt_ratio->GetBinError(thisBin);

                if(nomval_BF==0) {
                    thisBin = h_mu_TRIGGER_BF_abseta_pt_ratio->FindBin( 25.001, searchEta );
                    nomval_BF = h_mu_TRIGGER_BF_abseta_pt_ratio->GetBinContent( thisBin );
                    error_BF = h_mu_TRIGGER_BF_abseta_pt_ratio->GetBinError(thisBin);
                }
                double upval_BF = nomval_BF + error_BF;
                double downval_BF = nomval_BF - error_BF;

                thisBin = h_mu_TRIGGER_GH_abseta_pt_ratio->FindBin( searchPt, searchEta );
                double nomval_GH = h_mu_TRIGGER_GH_abseta_pt_ratio->GetBinContent(thisBin);
                double error_GH = h_mu_TRIGGER_GH_abseta_pt_ratio->GetBinError(thisBin);

                if(nomval_GH==0) {
                    thisBin = h_mu_TRIGGER_GH_abseta_pt_ratio->FindBin( 25.001, searchEta );
                    nomval_GH = h_mu_TRIGGER_GH_abseta_pt_ratio->GetBinContent( thisBin );
                    error_GH = h_mu_TRIGGER_GH_abseta_pt_ratio->GetBinError(thisBin);
                }
                double upval_GH = nomval_GH + error_GH;
                double downval_GH = nomval_GH - error_GH;

                nomval = (nomval_BF * 19.692 + nomval_GH * 16.226) / 35.918;
                upval = (upval_BF * 19.692 + upval_GH * 16.226) / 35.918;
                downval = (downval_BF * 19.692 + downval_GH * 16.226) / 35.918;
            }
            else if (is_ee){
                searchEta1 = fabs(ele_eta[sel_ele_di_sorted_index[0]]);
                searchEta2 = fabs(ele_eta[sel_ele_di_sorted_index[1]]);

                thisBin = h_ele_ele_TRIGGER_abseta_abseta->FindBin( searchEta1 , searchEta2 );
                nomval = h_ele_ele_TRIGGER_abseta_abseta->GetBinContent( thisBin );
                error = h_ele_ele_TRIGGER_abseta_abseta->GetBinError( thisBin );
                upval = nomval + error;
                downval = nomval - error;
            }
            else if (is_mumu){
                searchEta1 = fabs(mu_eta[sel_mu_di_sorted_index[0]]);
                searchEta2 = fabs(mu_eta[sel_mu_di_sorted_index[1]]);

                thisBin = h_mu_mu_TRIGGER_abseta_abseta->FindBin( searchEta1 , searchEta2 );
                nomval = h_mu_mu_TRIGGER_abseta_abseta->GetBinContent( thisBin );
                error = h_mu_mu_TRIGGER_abseta_abseta->GetBinError( thisBin );
                upval = nomval + error;
                downval = nomval - error;
            }
            else if (is_emu){
                searchEta1 = fabs(ele_eta[sel_ele_di_sorted_index[0]]);
                searchEta2 = fabs(mu_eta[sel_mu_di_sorted_index[0]]);

                thisBin = h_ele_mu_TRIGGER_abseta_abseta->FindBin( searchEta1 , searchEta2 );
                nomval = h_ele_mu_TRIGGER_abseta_abseta->GetBinContent( thisBin );
                error = h_ele_mu_TRIGGER_abseta_abseta->GetBinError( thisBin );
                upval = nomval + error;
                downval = nomval - error;
            }

            trigger_SF = nomval;
            trigger_SF_up = upval;
            trigger_SF_down = downval;
        }
        */

         // Reading out PU weights

         double PU_weight_mod, PU_weight_up_mod, PU_weight_down_mod;
         if (npv > (PU_x[n_pu_size-1]+1)){
             PU_weight_mod = PU_y[n_pu_size-1];
             PU_weight_up_mod = PU_y_up[n_pu_size-1];
             PU_weight_down_mod = PU_y_down[n_pu_size-1];
         }
         else {
             for (int i = 0; i < n_pu_size; ++i) {
                 if (npv < (PU_x[i] + 1)){
                     PU_weight_mod = PU_y[i];
                     PU_weight_up_mod = PU_y_up[i];
                     PU_weight_down_mod = PU_y_down[i];
                     break;
                 }
             }
         }

        // Printing sync output
        if (is_SL){
            fprintf(file_sync,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,",run,ls,nEvent,is_e,is_mu,is_ee,is_emu,is_mumu,n_jet_sl,n_btag_sl);
            if (is_e){
                fprintf(file_sync,"%.4f,%.4f,%.4f,%d,",ele_pt[sel_ele_sl_index[0]],ele_eta[sel_ele_sl_index[0]],ele_iso[sel_ele_sl_index[0]],ele_pdgid[sel_ele_sl_index[0]]);
                if (is_data_input==0)
                    fprintf(file_sync,"%.4f,%.4f,",ele_sf_id_combined[sel_ele_sl_index[0]],ele_sf_iso_combined[sel_ele_sl_index[0]]);
                else
                    fprintf(file_sync,"-1.0000,-1.0000,");
            }
            else if (is_mu){
                fprintf(file_sync,"%.4f,%.4f,%.4f,%d,",mu_pt_uncorr[sel_mu_sl_index[0]],mu_eta[sel_mu_sl_index[0]],mu_iso[sel_mu_sl_index[0]],mu_pdgid[sel_mu_sl_index[0]]);
                if (is_data_input==0)
                    fprintf(file_sync,"%.4f,%.4f,",mu_sf_id_combined[sel_mu_sl_index[0]],mu_sf_iso_combined[sel_mu_sl_index[0]]);
                else
                    fprintf(file_sync,"-1.0000,-1.0000,");
            }
            fprintf(file_sync,"-1,-1,-1,-1,-1,-1,");
            fprintf(file_sync,"%.4f,%.4f,%.4f,%.4f,",jet_pt_corr[sel_jet_sl_sorted_index[0]],jet_eta[sel_jet_sl_sorted_index[0]],jet_phi[sel_jet_sl_sorted_index[0]],jet_jecSF_nominal[sel_jet_sl_sorted_index[0]]);
            if (is_data_input==0)
                fprintf(file_sync,"%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%d,%.4f,",jet_jecSF_nominal_up[sel_jet_sl_sorted_index[0]],jet_jecSF_nominal_down[sel_jet_sl_sorted_index[0]],jet_jesSF_down[20][sel_jet_sl_sorted_index[0]],jet_jesSF_up[16][sel_jet_sl_sorted_index[0]],jet_jerSF_jesnominal_nominal[sel_jet_sl_sorted_index[0]],jet_CSV[sel_jet_sl_sorted_index[0]],jet_puid[sel_jet_sl_sorted_index[0]],jet_pudisc[sel_jet_sl_sorted_index[0]]);
            else
                fprintf(file_sync,"-1.0000,-1.0000,-1.0000,-1.0000,-1.0000,%.4f,%d,%.4f,",jet_CSV[sel_jet_sl_sorted_index[0]],jet_puid[sel_jet_sl_sorted_index[0]],jet_pudisc[sel_jet_sl_sorted_index[0]]);
            fprintf(file_sync,"%.4f,%.4f,%.4f,%.4f,",jet_pt_corr[sel_jet_sl_sorted_index[1]],jet_eta[sel_jet_sl_sorted_index[1]],jet_phi[sel_jet_sl_sorted_index[1]],jet_jecSF_nominal[sel_jet_sl_sorted_index[1]]);
            if (is_data_input==0)
                fprintf(file_sync,"%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%d,%.4f,",jet_jecSF_nominal_up[sel_jet_sl_sorted_index[1]],jet_jecSF_nominal_down[sel_jet_sl_sorted_index[1]],jet_jesSF_down[20][sel_jet_sl_sorted_index[1]],jet_jesSF_up[16][sel_jet_sl_sorted_index[1]],jet_jerSF_jesnominal_nominal[sel_jet_sl_sorted_index[1]],jet_CSV[sel_jet_sl_sorted_index[1]],jet_puid[sel_jet_sl_sorted_index[1]],jet_pudisc[sel_jet_sl_sorted_index[1]]);
            else
                fprintf(file_sync,"-1.0000,-1.0000,-1.0000,-1.0000,-1.0000,%.4f,%d,%.4f,",jet_CSV[sel_jet_sl_sorted_index[1]],jet_puid[sel_jet_sl_sorted_index[1]],jet_pudisc[sel_jet_sl_sorted_index[1]]);
            fprintf(file_sync,"%.4f,%.4f,-1,%d,%d,%d,",met_pt_phi_corr,met_phi_phi_corr,ttHf_cat,ttHFGenFilter,npv);
            if (is_data_input==0)
                fprintf(file_sync,"%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,-1,-1,%.4f,-1,-1,-1,-1,-1,-1,-1",PU_weight_mod,csv_sf_jesnominal_nominal,csv_sf_jesnominal_lfup,csv_sf_jesnominal_hfdown,csv_sf_jesnominal_cferr1down, pdf_weight_up,pdf_weight_down,trigger_SF);
            else
                fprintf(file_sync,"-1,-1,-1,-1,-1,-1,-1,-1,-1,-1.0000,-1,-1,-1,-1,-1,-1,-1");
            fprintf(file_sync,"\n");
        }
        else if (is_DL){
            fprintf(file_sync,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,",run,ls,nEvent,is_e,is_mu,is_ee,is_emu,is_mumu,n_jet_di,n_btag_di);
            if (is_ee){
                fprintf(file_sync,"%.4f,%.4f,%.4f,%d,",ele_pt[sel_ele_di_sorted_index[0]],ele_eta[sel_ele_di_sorted_index[0]],ele_iso[sel_ele_di_sorted_index[0]],ele_pdgid[sel_ele_di_sorted_index[0]]);
                if (is_data_input==0)
                    fprintf(file_sync,"%.4f,%.4f,",ele_sf_id_combined[sel_ele_di_sorted_index[0]],ele_sf_iso_combined[sel_ele_di_sorted_index[0]]);
                else
                    fprintf(file_sync,"-1.0000,-1.0000,");
                fprintf(file_sync,"%.4f,%.4f,%.4f,%d,",ele_pt[sel_ele_di_sorted_index[1]],ele_eta[sel_ele_di_sorted_index[1]],ele_iso[sel_ele_di_sorted_index[1]],ele_pdgid[sel_ele_di_sorted_index[1]]);
                if (is_data_input==0)
                    fprintf(file_sync,"%.4f,%.4f,",ele_sf_id_combined[sel_ele_di_sorted_index[1]],ele_sf_iso_combined[sel_ele_di_sorted_index[1]]);
                else
                    fprintf(file_sync,"-1.0000,-1.0000,");
            }
            else if (is_emu){
                if (ele_pt[sel_ele_di_sorted_index[0]] > mu_pt_uncorr[sel_mu_di_sorted_index[0]]){
                    fprintf(file_sync,"%.4f,%.4f,%.4f,%d,",ele_pt[sel_ele_di_sorted_index[0]],ele_eta[sel_ele_di_sorted_index[0]],ele_iso[sel_ele_di_sorted_index[0]],ele_pdgid[sel_ele_di_sorted_index[0]]);
                    if (is_data_input==0)
                        fprintf(file_sync,"%.4f,%.4f,",ele_sf_id_combined[sel_ele_di_sorted_index[0]],ele_sf_iso_combined[sel_ele_di_sorted_index[0]]);
                    else
                        fprintf(file_sync,"-1.0000,-1.0000,");
                    fprintf(file_sync,"%.4f,%.4f,%.4f,%d,",mu_pt_uncorr[sel_mu_di_sorted_index[0]],mu_eta[sel_mu_di_sorted_index[0]],mu_iso[sel_mu_di_sorted_index[0]],mu_pdgid[sel_mu_di_sorted_index[0]]);
                    if (is_data_input==0)
                        fprintf(file_sync,"%.4f,%.4f,",mu_sf_id_combined[sel_mu_di_sorted_index[0]],mu_sf_iso_combined[sel_mu_di_sorted_index[0]]);
                    else
                        fprintf(file_sync,"-1.0000,-1.0000,");
                }
                else{
                    fprintf(file_sync,"%.4f,%.4f,%.4f,%d,",mu_pt_uncorr[sel_mu_di_sorted_index[0]],mu_eta[sel_mu_di_sorted_index[0]],mu_iso[sel_mu_di_sorted_index[0]],mu_pdgid[sel_mu_di_sorted_index[0]]);
                    if (is_data_input==0)
                        fprintf(file_sync,"%.4f,%.4f,",mu_sf_id_combined[sel_mu_di_sorted_index[0]],mu_sf_iso_combined[sel_mu_di_sorted_index[0]]);
                    else
                        fprintf(file_sync,"-1.0000,-1.0000,");
                    fprintf(file_sync,"%.4f,%.4f,%.4f,%d,",ele_pt[sel_ele_di_sorted_index[0]],ele_eta[sel_ele_di_sorted_index[0]],ele_iso[sel_ele_di_sorted_index[0]],ele_pdgid[sel_ele_di_sorted_index[0]]);
                    if (is_data_input==0)
                        fprintf(file_sync,"%.4f,%.4f,",ele_sf_id_combined[sel_ele_di_sorted_index[0]],ele_sf_iso_combined[sel_ele_di_sorted_index[0]]);
                    else
                        fprintf(file_sync,"-1.0000,-1.0000,");
                }
            }
            else if (is_mumu){
                fprintf(file_sync,"%.4f,%.4f,%.4f,%d,",mu_pt_uncorr[sel_mu_di_sorted_index[0]],mu_eta[sel_mu_di_sorted_index[0]],mu_iso[sel_mu_di_sorted_index[0]],mu_pdgid[sel_mu_di_sorted_index[0]]);
                if (is_data_input==0)
                    fprintf(file_sync,"%.4f,%.4f,",mu_sf_id_combined[sel_mu_di_sorted_index[0]],mu_sf_iso_combined[sel_mu_di_sorted_index[0]]);
                else
                    fprintf(file_sync,"-1.0000,-1.0000,");
                fprintf(file_sync,"%.4f,%.4f,%.4f,%d,",mu_pt_uncorr[sel_mu_di_sorted_index[1]],mu_eta[sel_mu_di_sorted_index[1]],mu_iso[sel_mu_di_sorted_index[1]],mu_pdgid[sel_mu_di_sorted_index[1]]);
                if (is_data_input==0)
                    fprintf(file_sync,"%.4f,%.4f,",mu_sf_id_combined[sel_mu_di_sorted_index[1]],mu_sf_iso_combined[sel_mu_di_sorted_index[1]]);
                else
                    fprintf(file_sync,"-1.0000,-1.0000,");
            }
            fprintf(file_sync,"%.4f,%.4f,%.4f,%.4f,",jet_pt_corr[sel_jet_di_sorted_index[0]],jet_eta[sel_jet_di_sorted_index[0]],jet_phi[sel_jet_di_sorted_index[0]],jet_jecSF_nominal[sel_jet_di_sorted_index[0]]);
            if (is_data_input==0)
                fprintf(file_sync,"%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%d,%.4f,",jet_jecSF_nominal_up[sel_jet_di_sorted_index[0]],jet_jecSF_nominal_down[sel_jet_di_sorted_index[0]],jet_jesSF_down[20][sel_jet_di_sorted_index[0]],jet_jesSF_up[16][sel_jet_di_sorted_index[0]],jet_jerSF_jesnominal_nominal[sel_jet_di_sorted_index[0]],jet_CSV[sel_jet_di_sorted_index[0]],jet_puid[sel_jet_di_sorted_index[0]],jet_pudisc[sel_jet_di_sorted_index[0]]);
             else
                 fprintf(file_sync,"-1.0000,-1.0000,-1.0000,-1.0000,-1.0000,%.4f,%d,%.4f,",jet_CSV[sel_jet_di_sorted_index[0]],jet_puid[sel_jet_di_sorted_index[0]],jet_pudisc[sel_jet_di_sorted_index[0]]);
             fprintf(file_sync,"%.4f,%.4f,%.4f,%.4f,",jet_pt_corr[sel_jet_di_sorted_index[1]],jet_eta[sel_jet_di_sorted_index[1]],jet_phi[sel_jet_di_sorted_index[1]],jet_jecSF_nominal[sel_jet_di_sorted_index[1]]);
             if (is_data_input==0)
                 fprintf(file_sync,"%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%d,%.4f,",jet_jecSF_nominal_up[sel_jet_di_sorted_index[1]],jet_jecSF_nominal_down[sel_jet_di_sorted_index[1]],jet_jesSF_down[20][sel_jet_di_sorted_index[1]],jet_jesSF_up[16][sel_jet_di_sorted_index[1]],jet_jerSF_jesnominal_nominal[sel_jet_di_sorted_index[1]],jet_CSV[sel_jet_di_sorted_index[1]],jet_puid[sel_jet_di_sorted_index[1]],jet_pudisc[sel_jet_di_sorted_index[1]]);
             else
                 fprintf(file_sync,"-1.0000,-1.0000,-1.0000,-1.0000,-1.0000,%.4f,%d,%.4f,",jet_CSV[sel_jet_di_sorted_index[1]],jet_puid[sel_jet_di_sorted_index[1]],jet_pudisc[sel_jet_di_sorted_index[1]]);
            fprintf(file_sync,"%.4f,%.4f,%.4f,%d,%d,%d,",met_pt_phi_corr,met_phi_phi_corr,mll,ttHf_cat,ttHFGenFilter,npv);
            if (is_data_input==0)
                fprintf(file_sync,"%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f,-1,-1,%.4f,-1,-1,-1,-1,-1,-1,-1",PU_weight_mod,csv_sf_jesnominal_nominal,csv_sf_jesnominal_lfup,csv_sf_jesnominal_hfdown,csv_sf_jesnominal_cferr1down, pdf_weight_up,pdf_weight_down,trigger_SF);
             else
                 fprintf(file_sync,"-1,-1,-1,-1,-1,-1,-1,-1,-1,-1.0000,-1,-1,-1,-1,-1,-1,-1");
          fprintf(file_sync,"\n");
        }

    }

    N_sel_raw = N_SL_raw + N_DL_raw;

    // Calculating the yields in Z-region at L = 35.92 1/fb

    if(is_data_input==0){
        lumi_norm = (L*xs*1000)/((double) N_total);
        lumi_norm_genweighted = (L*xs*1000)/(sum_gen_weights);

        //N_Z_loose_0btag_norm = (N_Z_loose_0btag*lumi_norm);

    }

    // Scaling Histograms according to L = 35.92 1/fb

    //mll_Z_loose->Scale(lumi_norm);


    std::cout << "Reco and Gen Tree Done! " << std::endl;
    fout<<"**********************************************************************************************\n\n";
    fout<<"Total No. of Events : "<<N_total<<"\n";
    fout<<"No. of Events passing Basic Event Selection : "<<N_basic_sel<<"\n";
    fout<<"Total No. of Events passing Selection : "<<N_sel_raw<<"\n\n";
    fout<<"Sum of Positive Generator weights of all Events: "<<sum_pos_gen_weights<<"\n";
    fout<<"Sum of Negative Generator weights of all Events: "<<sum_neg_gen_weights<<"\n";
    fout<<"Sum of Generator weights of all Events: "<<sum_gen_weights<<"\n\n";
    fout<<"Product of Generator weights of all Events: "<<prod_gen_weights<<"\n\n";
    fout<<"Sum of Generator weights * PU weights of all Events: "<<sum_gen_PU_weights<<"\n\n";
    fout<<"**********************************************************************************************\n\n";
    fout<<"No. of Single Electron Events: "<<N_e_raw<<"\n";
    fout<<"No. of Single Muon Events: "<<N_mu_raw<<"\n";
    fout<<"No. of Double Electron Events: "<<N_ee_raw<<"\n";
    fout<<"No. of Electron Muon Events: "<<N_emu_raw<<"\n";
    fout<<"No. of Double Muon Events: "<<N_mumu_raw<<"\n";
    fout<<"Total No. of Single Lepton Events: "<<N_SL_raw<<"\n";
    fout<<"Total No. of Dilepton Events: "<<N_DL_raw<<"\n\n";
    fout<<"**********************************************************************************************\n\n";


    // Free memory
    delete reco_chain;
    delete gen_chain;
    delete comm_chain;

    // Close Trigger SF files
    /*
    f_TRIGGERSF_e->Close();
    f_TRIGGERSF_BF_mu->Close();
    f_TRIGGERSF_GH_mu->Close();
    f_TRIGGERSF_ee->Close();
    f_TRIGGERSF_mumu->Close();
    f_TRIGGERSF_emu->Close();
    */

    // CLose other files
    histofile.Write();
    histofile.Close();
    fout.close();
    std::fclose(file_sync);
    //system("rm -rf PU_MC.txt PU_weights.txt");

    return;
}


