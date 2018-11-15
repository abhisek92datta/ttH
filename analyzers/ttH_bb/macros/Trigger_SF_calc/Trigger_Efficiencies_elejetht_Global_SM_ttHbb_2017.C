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
typedef std::vector<std::vector<std::string> > vvstring;

double dR_calc( double eta1, double phi1, double eta2, double phi2){

    double deta = eta1 - eta2;
    double dphi = TVector2::Phi_mpi_pi(phi1 - phi2);
    double dR = sqrt(deta*deta + dphi*dphi);
    return dR;
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

double bias_error(double F, double A, double A_err, double B, double B_err, double C, double C_err){
// Assuming bias , F= A*B/C

    double F_err;
    double relA = A_err/A;
    double relB = B_err/B;
    double relC = C_err/C;
    F_err = fabs(F) * sqrt( relA*relA + relB*relB + relC*relC );
    return F_err;
}

void Trigger_Efficiencies_elejetht_Global_SM_ttHbb_2017( int maxNentries=-1, int Njobs=1, int jobN=1 ) {

    // Reading from input file

    ifstream fin;
    ofstream fout;
    std::string data_mc;
    std::string sample_dataset;
    int n_input_files;
    std::string file;
    std::vector<std::string> treefilenames;
    std::string output_hist_filename;
    std::string output_yields_filename;
    std::string sync_filename;
    int is_data_input = 0;
    int dataset_index = 0;
    double xs;
    std::string offline_sel;   // can be "normal", "emu", "pure_e", "tthbb"
    std::string syst_var; // can be "syst_up", "syst_down", "syst_nominal"

    fin.open("input.txt");
    fin>>data_mc;
    fin>>sample_dataset;
    fin>>n_input_files;
    for(int i=0; i<n_input_files; i++){
        fin>>file;
        treefilenames.push_back(file);
    }
    fin>>xs;
    fin>>offline_sel;
    fin>>syst_var;
    fin.close();

    if (data_mc == "data")
        is_data_input=1;

    // Setting up output files

    output_hist_filename = ("Trigger_Efficiencies_elejetht_Global_SM_"+ data_mc + "_" + sample_dataset + ".root").c_str();
    output_yields_filename = ("output_elejetht_global_sm_" + data_mc + "_" + sample_dataset + ".txt").c_str();
    fout.open(output_yields_filename);

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

    double HT_syst_cut = 400.0;

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
    int N_SL_tag = 0;
    int N_DL_tag = 0;
    int N_FH_tag = 0;

    double N_e = 0;
    double N_ref = 0;
    double N_e_ele27_only = 0;
    double N_e_ele35_only = 0;
    double N_e_ele30_jet35_only = 0;
    double N_e_ele28_ht150_only = 0;
    double N_e_ele30_jet35_OR_ele35_only = 0;
    double N_e_ele28_ht150_OR_ele35_only = 0;
    double N_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only = 0;
    double N_e_ele30_jet35_OR_ele28_ht150_only = 0;
    double N_e_den_ele30_jet35 = 0;
    double N_e_den_ele28_ht150 = 0;
    double N_e_den_ele27 = 0;
    double N_e_den_ele35 = 0;
    double N_e_den_ele30_jet35_OR_ele35 = 0;
    double N_e_den_ele28_ht150_OR_ele35 = 0;
    double N_e_den_ele30_jet35_OR_ele28_ht150_OR_ele35 = 0;
    double N_e_den_ele30_jet35_OR_ele28_ht150 = 0;
    double N_e_ele27 = 0;
    double N_e_ele35 = 0;
    double N_e_ele30_jet35 = 0;
    double N_e_ele28_ht150 = 0;
    double N_e_ele30_jet35_OR_ele35 = 0;
    double N_e_ele28_ht150_OR_ele35 = 0;
    double N_e_ele30_jet35_OR_ele28_ht150_OR_ele35 = 0;
    double N_e_ele30_jet35_OR_ele28_ht150 = 0;
    double effi_ref = 0;
    double effi_e_ele27_only = 0;
    double effi_e_ele35_only = 0;
    double effi_e_ele30_jet35_only = 0;
    double effi_e_ele28_ht150_only = 0;
    double effi_e_ele30_jet35_OR_ele35_only = 0;
    double effi_e_ele28_ht150_OR_ele35_only = 0;
    double effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only = 0;
    double effi_e_ele30_jet35_OR_ele28_ht150_only = 0;
    double effi_e_ele27_and_ref = 0;
    double effi_e_ele35_and_ref = 0;
    double effi_e_ele30_jet35_and_ref = 0;
    double effi_e_ele28_ht150_and_ref = 0;
    double effi_e_ele30_jet35_OR_ele35_and_ref = 0;
    double effi_e_ele28_ht150_OR_ele35_and_ref = 0;
    double effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref = 0;
    double effi_e_ele30_jet35_OR_ele28_ht150_and_ref = 0;
    double effi_ref_err = 0;
    double effi_e_ele27_only_err = 0;
    double effi_e_ele35_only_err = 0;
    double effi_e_ele30_jet35_only_err = 0;
    double effi_e_ele28_ht150_only_err = 0;
    double effi_e_ele30_jet35_OR_ele35_only_err = 0;
    double effi_e_ele28_ht150_OR_ele35_only_err = 0;
    double effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only_err = 0;
    double effi_e_ele30_jet35_OR_ele28_ht150_only_err = 0;
    double effi_e_ele27_and_ref_err = 0;
    double effi_e_ele35_and_ref_err = 0;
    double effi_e_ele30_jet35_and_ref_err = 0;
    double effi_e_ele28_ht150_and_ref_err = 0;
    double effi_e_ele30_jet35_OR_ele35_and_ref_err = 0;
    double effi_e_ele28_ht150_OR_ele35_and_ref_err = 0;
    double effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref_err = 0;
    double effi_e_ele30_jet35_OR_ele28_ht150_and_ref_err = 0;
    double effi_e_ele27 = 0;
    double effi_e_ele35 = 0;
    double effi_e_ele30_jet35 = 0;
    double effi_e_ele28_ht150 = 0;
    double effi_e_ele30_jet35_OR_ele35 = 0;
    double effi_e_ele28_ht150_OR_ele35 = 0;
    double effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35 = 0;
    double effi_e_ele30_jet35_OR_ele28_ht150 = 0;

    double bias_e_ele27 = 0;
    double bias_e_ele35 = 0;
    double bias_e_ele30_jet35 = 0;
    double bias_e_ele28_ht150 = 0;
    double bias_e_ele30_jet35_OR_ele35 = 0;
    double bias_e_ele28_ht150_OR_ele35 = 0;
    double bias_e_ele30_jet35_OR_ele28_ht150_OR_ele35 = 0;
    double bias_e_ele30_jet35_OR_ele28_ht150 = 0;
    double bias_e_ele27_err = 0;
    double bias_e_ele35_err = 0;
    double bias_e_ele30_jet35_err = 0;
    double bias_e_ele28_ht150_err = 0;
    double bias_e_ele30_jet35_OR_ele35_err = 0;
    double bias_e_ele28_ht150_OR_ele35_err = 0;
    double bias_e_ele30_jet35_OR_ele28_ht150_OR_ele35_err = 0;
    double bias_e_ele30_jet35_OR_ele28_ht150_err = 0;

    // Lumi Weighting
    double L_int = 41.298; // 1/fb
    double lumi_weight = 1.0;

    // Setting output file and input Trees

    std::string histofilename = output_hist_filename;

    TChain *reco_chain = new TChain("ttHbb/recoTree");
    TChain *comm_chain = new TChain("ttHbb/commTree");

    for(int i=0; i<n_input_files; i++){
        reco_chain->Add(treefilenames[i].c_str());
        if(is_data_input==0){
            comm_chain->Add(treefilenames[i].c_str());
        }
    }

    TFile histofile(histofilename.c_str(),"recreate");
    histofile.cd();

    // Setting up Histograms for Control Plots
    
    TH1::SetDefaultSumw2();

    /*
    // Fine Binning
    int n_eleptBins = 25;
    double x_eleptBins[26] = {30, 40, 50, 60, 70, 80, 90 , 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 220, 240, 260, 280, 300, 350, 400, 500};

    int n_jetptBins = 19;
    double x_jetptBins[20] = {30, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 300, 325, 350, 375, 400, 450, 500};

    int n_etaBins = 22;
    double x_etaBins[23] = {-2.2, -2.0, -1.8, -1.6, -1.4, -1.2, -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2 };

    int n_htBins = 17;
    double x_htBins[18] = {0, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 1000};

    int n_njetBins = 8;
    double x_njetBins[9] = {4,5,6,7,8,9,10,11,12};
    */

    /*
    // Bin Choice 1
    int n_eleptBins = 5;
    double x_eleptBins[6] = {30, 37, 45, 55, 200, 500};

    int n_jetptBins = 4;
    double x_jetptBins[5] = {30, 50, 100, 200, 500};

    int n_etaBins = 8;
    double x_etaBins[9] = {-2.1, -1.5660, -1.4442, -0.8, 0.0, 0.8, 1.444, 1.566, 2.1};

    int n_htBins = 4;
    double x_htBins[5] = {0, 150, 300, 500, 1000};

    int n_njetBins = 8;
    double x_njetBins[9] = {4,5,6,7,8,9,10,11,12};
    */
    /*
    // Bin Choice 2
    int n_eleptBins = 5;
    double x_eleptBins[6] = {30, 37, 45, 55, 200, 500};

    int n_jetptBins = 4;
    double x_jetptBins[5] = {30, 50, 100, 200, 500};

    int n_etaBins = 6;
    double x_etaBins[7] = {-2.1, -1.5, -0.8, 0.0, 0.8, 1.5, 2.1};

    int n_htBins = 4;
    double x_htBins[5] = {0, 150, 300, 500, 1000};

    int n_njetBins = 8;
    double x_njetBins[9] = {4,5,6,7,8,9,10,11,12};
    */
    /*
    // Bin Choice 3
    int n_eleptBins = 5;
    double x_eleptBins[6] = {30, 37, 45, 55, 100, 500};

    int n_jetptBins = 3;
    double x_jetptBins[4] = {30, 100, 200, 500};

    int n_etaBins = 6;
    double x_etaBins[7] = {-2.2, -1.5, -0.8, 0.0, 0.8, 1.5, 2.2};

    int n_htBins = 3;
    double x_htBins[4] = {0, 300, 500, 1000};

    int n_njetBins = 8;
    double x_njetBins[9] = {4,5,6,7,8,9,10,11,12};
    */

    // Bin Choice 4
    int n_eleptBins = 5;
    double x_eleptBins[6] = {30, 37, 45, 55, 100, 500};

    int n_eleetaBins = 8;
    double x_eleetaBins[9] = {-2.2, -1.5660, -1.4442, -0.8, 0.0, 0.8, 1.4442, 1.5660, 2.2};

    int n_jetptBins = 3;
    double x_jetptBins[4] = {30, 100, 200, 500};

    int n_jetetaBins = 6;
    double x_jetetaBins[7] = {-2.4, -1.6, -0.8, 0.0, 0.8, 1.6, 2.4};

    int n_htBins = 3;
    double x_htBins[4] = {0, 300, 500, 1000};

    int n_njetBins = 8;
    double x_njetBins[9] = {4,5,6,7,8,9,10,11,12};


    // Total Histograms
    TH1D* N_total_ele_pt = new TH1D("N_total_ele_pt","Nr. of Events vs Electron pT;Electron pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins);
    TH1D* N_total_ele_eta = new TH1D("N_total_ele_eta","Nr. of Events vs Electron eta;Electron eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_total_ele_sceta = new TH1D("N_total_ele_sceta","Nr. of Events vs Electron SuperCluster eta;Electron SuperCluster eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_total_jet_pt = new TH1D("N_total_jet_pt","Nr. of Events vs Leading Jet pT;Leading Jet pT (GeV);Nr. of Events",n_jetptBins,x_jetptBins);
    TH1D* N_total_jet_eta = new TH1D("N_total_jet_eta","Nr. of Events vs Leading Jet eta;Leading Jet eta;Nr. of Events",n_jetetaBins,x_jetetaBins);
    TH1D* N_total_ht = new TH1D("N_total_ht","Nr. of Events vs HT;HT (GeV);Nr. of Events",n_htBins,x_htBins);
    TH1D* N_total_njets = new TH1D("N_total_njets","Nr. of Events vs Nr. of Jets;Nr. of Jets;Nr. of Events",n_njetBins,x_njetBins);
    TH1D* N_total_npv = new TH1D("N_total_npv","Nr. of Events vs Nr. of Primary Vertices;NPV;Nr. of Events",75,0,75);
    TH2D* N_total_ele_pt_ele_eta = new TH2D("N_total_ele_pt_ele_eta","Nr. of Events vs Electron pT & Electron eta;Electron pT (GeV);Electron eta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_total_ele_pt_ele_sceta = new TH2D("N_total_ele_pt_ele_sceta","Nr. of Events vs Electron pT & Electron SuperClustereta;Electron pT (GeV);Electron SuperClustereta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_total_ele_pt_jet_pt = new TH2D("N_total_ele_pt_jet_pt","Nr. of Events vs Electron pT & Leading Jet pT;Electron pT (GeV);Leading Jet pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
    TH2D* N_total_ele_pt_ht = new TH2D("N_total_ele_pt_ht","Nr. of Events vs Electron pT & HT;Electron pT (GeV);HT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_htBins,x_htBins);

    // Pass Histograms
    TH1D* N_pass_ele_pt_ele27 = new TH1D("N_pass_ele_pt_ele27","Nr. of Events vs Electron pT for Ele27;Electron pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins);
    TH1D* N_pass_ele_eta_ele27 = new TH1D("N_pass_ele_eta_ele27","Nr. of Events vs Electron eta for Ele27;Electron eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_ele_sceta_ele27 = new TH1D("N_pass_ele_sceta_ele27","Nr. of Events vs Electron SuperCluster eta for Ele27;Electron SuperCluster eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_jet_pt_ele27 = new TH1D("N_pass_jet_pt_ele27","Nr. of Events vs Leading Jet pT for Ele27;Leading Jet pT (GeV);Nr. of Events",n_jetptBins,x_jetptBins);
    TH1D* N_pass_jet_eta_ele27 = new TH1D("N_pass_jet_eta_ele27","Nr. of Events vs Leading Jet eta for Ele27;Leading Jet eta;Nr. of Events",n_jetetaBins,x_jetetaBins);
    TH1D* N_pass_ht_ele27 = new TH1D("N_pass_ht_ele27","Nr. of Events vs HT for Ele27;HT (GeV);Nr. of Events",n_htBins,x_htBins);
    TH1D* N_pass_njets_ele27 = new TH1D("N_pass_njets_ele27","Nr. of Events vs Nr. of Jets for Ele27;Nr. of Jets;Nr. of Events",n_njetBins,x_njetBins);
    TH1D* N_pass_npv_ele27 = new TH1D("N_pass_npv_ele27","Nr. of Events vs Nr. of Primary Vertices for Ele27;NPV;Nr. of Events",75,0,75);
    TH2D* N_pass_ele_pt_ele_eta_ele27 = new TH2D("N_pass_ele_pt_ele_eta_ele27","Nr. of Events vs Electron pT & Electron eta for Ele27;Electron pT (GeV);Electron eta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_ele_sceta_ele27 = new TH2D("N_pass_ele_pt_ele_sceta_ele27","Nr. of Events vs Electron pT & Electron SuperClustereta for Ele27;Electron pT (GeV);Electron SuperClustereta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_jet_pt_ele27 = new TH2D("N_pass_ele_pt_jet_pt_ele27","Nr. of Events vs Electron pT & Leading Jet pT for Ele27;Electron pT (GeV);Leading Jet pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
    TH2D* N_pass_ele_pt_ht_ele27 = new TH2D("N_pass_ele_pt_ht_ele27","Nr. of Events vs Electron pT & HT for Ele27;Electron pT (GeV);HT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_htBins,x_htBins);
    TH1D* N_pass_ele_pt_ele35 = new TH1D("N_pass_ele_pt_ele35","Nr. of Events vs Electron pT for Ele35;Electron pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins);
    TH1D* N_pass_ele_eta_ele35 = new TH1D("N_pass_ele_eta_ele35","Nr. of Events vs Electron eta for Ele35;Electron eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_ele_sceta_ele35 = new TH1D("N_pass_ele_sceta_ele35","Nr. of Events vs Electron SuperCluster eta for Ele35;Electron SuperCluster eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_jet_pt_ele35 = new TH1D("N_pass_jet_pt_ele35","Nr. of Events vs Leading Jet pT for Ele35;Leading Jet pT (GeV);Nr. of Events",n_jetptBins,x_jetptBins);
    TH1D* N_pass_jet_eta_ele35 = new TH1D("N_pass_jet_eta_ele35","Nr. of Events vs Leading Jet eta for Ele35;Leading Jet eta;Nr. of Events",n_jetetaBins,x_jetetaBins);
    TH1D* N_pass_ht_ele35 = new TH1D("N_pass_ht_ele35","Nr. of Events vs HT for Ele35;HT (GeV);Nr. of Events",n_htBins,x_htBins);
    TH1D* N_pass_njets_ele35 = new TH1D("N_pass_njets_ele35","Nr. of Events vs Nr. of Jets for Ele35;Nr. of Jets;Nr. of Events",n_njetBins,x_njetBins);
    TH1D* N_pass_npv_ele35 = new TH1D("N_pass_npv_ele35","Nr. of Events vs Nr. of Primary Vertices for Ele35;NPV;Nr. of Events",75,0,75);
    TH2D* N_pass_ele_pt_ele_eta_ele35 = new TH2D("N_pass_ele_pt_ele_eta_ele35","Nr. of Events vs Electron pT & Electron eta for Ele35;Electron pT (GeV);Electron eta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_ele_sceta_ele35 = new TH2D("N_pass_ele_pt_ele_sceta_ele35","Nr. of Events vs Electron pT & Electron SuperClustereta for Ele35;Electron pT (GeV);Electron SuperClustereta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_jet_pt_ele35 = new TH2D("N_pass_ele_pt_jet_pt_ele35","Nr. of Events vs Electron pT & Leading Jet pT for Ele35;Electron pT (GeV);Leading Jet pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
    TH2D* N_pass_ele_pt_ht_ele35 = new TH2D("N_pass_ele_pt_ht_ele35","Nr. of Events vs Electron pT & HT for Ele35;Electron pT (GeV);HT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_htBins,x_htBins);
    TH1D* N_pass_ele_pt_ele30_jet35 = new TH1D("N_pass_ele_pt_ele30_jet35","Nr. of Events vs Electron pT for Ele30_Jet35;Electron pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins);
    TH1D* N_pass_ele_eta_ele30_jet35 = new TH1D("N_pass_ele_eta_ele30_jet35","Nr. of Events vs Electron eta for Ele30_Jet35;Electron eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_ele_sceta_ele30_jet35 = new TH1D("N_pass_ele_sceta_ele30_jet35","Nr. of Events vs Electron SuperCluster eta for Ele30_Jet35;Electron SuperCluster eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_jet_pt_ele30_jet35 = new TH1D("N_pass_jet_pt_ele30_jet35","Nr. of Events vs Leading Jet pT for Ele30_Jet35;Leading Jet pT (GeV);Nr. of Events",n_jetptBins,x_jetptBins);
    TH1D* N_pass_jet_eta_ele30_jet35 = new TH1D("N_pass_jet_eta_ele30_jet35","Nr. of Events vs Leading Jet eta for Ele30_Jet35;Leading Jet eta;Nr. of Events",n_jetetaBins,x_jetetaBins);
    TH1D* N_pass_ht_ele30_jet35 = new TH1D("N_pass_ht_ele30_jet35","Nr. of Events vs HT for Ele30_Jet35;HT (GeV);Nr. of Events",n_htBins,x_htBins);
    TH1D* N_pass_njets_ele30_jet35 = new TH1D("N_pass_njets_ele30_jet35","Nr. of Events vs Nr. of Jets for Ele30_Jet35;Nr. of Jets;Nr. of Events",n_njetBins,x_njetBins);
    TH1D* N_pass_npv_ele30_jet35 = new TH1D("N_pass_npv_ele30_jet35","Nr. of Events vs Nr. of Primary Vertices for Ele30_Jet35;NPV;Nr. of Events",75,0,75);
    TH2D* N_pass_ele_pt_ele_eta_ele30_jet35 = new TH2D("N_pass_ele_pt_ele_eta_ele30_jet35","Nr. of Events vs Electron pT & Electron eta for Ele30_Jet35;Electron pT (GeV);Electron eta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_ele_sceta_ele30_jet35 = new TH2D("N_pass_ele_pt_ele_sceta_ele30_jet35","Nr. of Events vs Electron pT & Electron SuperClustereta for Ele30_Jet35;Electron pT (GeV);Electron SuperClustereta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_jet_pt_ele30_jet35 = new TH2D("N_pass_ele_pt_jet_pt_ele30_jet35","Nr. of Events vs Electron pT & Leading Jet pT for Ele30_Jet35;Electron pT (GeV);Leading Jet pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
    TH2D* N_pass_ele_pt_ht_ele30_jet35 = new TH2D("N_pass_ele_pt_ht_ele30_jet35","Nr. of Events vs Electron pT & HT for Ele30_Jet35;Electron pT (GeV);HT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_htBins,x_htBins);
    TH1D* N_pass_ele_pt_ele28_ht150 = new TH1D("N_pass_ele_pt_ele28_ht150","Nr. of Events vs Electron pT for Ele28_HT150;Electron pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins);
    TH1D* N_pass_ele_eta_ele28_ht150 = new TH1D("N_pass_ele_eta_ele28_ht150","Nr. of Events vs Electron eta for Ele28_HT150;Electron eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_ele_sceta_ele28_ht150 = new TH1D("N_pass_ele_sceta_ele28_ht150","Nr. of Events vs Electron SuperCluster eta for Ele28_HT150;Electron SuperCluster eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_jet_pt_ele28_ht150 = new TH1D("N_pass_jet_pt_ele28_ht150","Nr. of Events vs Leading Jet pT for Ele28_HT150;Leading Jet pT (GeV);Nr. of Events",n_jetptBins,x_jetptBins);
    TH1D* N_pass_jet_eta_ele28_ht150 = new TH1D("N_pass_jet_eta_ele28_ht150","Nr. of Events vs Leading Jet eta for Ele28_HT150;Leading Jet eta;Nr. of Events",n_jetetaBins,x_jetetaBins);
    TH1D* N_pass_ht_ele28_ht150 = new TH1D("N_pass_ht_ele28_ht150","Nr. of Events vs HT for Ele28_HT150;HT (GeV);Nr. of Events",n_htBins,x_htBins);
    TH1D* N_pass_njets_ele28_ht150 = new TH1D("N_pass_njets_ele28_ht150","Nr. of Events vs Nr. of Jets for Ele28_HT150;Nr. of Jets;Nr. of Events",n_njetBins,x_njetBins);
    TH1D* N_pass_npv_ele28_ht150 = new TH1D("N_pass_npv_ele28_ht150","Nr. of Events vs Nr. of Primary Vertices for Ele28_HT150;NPV;Nr. of Events",75,0,75);
    TH2D* N_pass_ele_pt_ele_eta_ele28_ht150 = new TH2D("N_pass_ele_pt_ele_eta_ele28_ht150","Nr. of Events vs Electron pT & Electron eta for Ele28_HT150;Electron pT (GeV);Electron eta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_ele_sceta_ele28_ht150 = new TH2D("N_pass_ele_pt_ele_sceta_ele28_ht150","Nr. of Events vs Electron pT & Electron SuperClustereta for Ele28_HT150;Electron pT (GeV);Electron SuperClustereta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_jet_pt_ele28_ht150 = new TH2D("N_pass_ele_pt_jet_pt_ele28_ht150","Nr. of Events vs Electron pT & Leading Jet pT for Ele28_HT150;Electron pT (GeV);Leading Jet pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
    TH2D* N_pass_ele_pt_ht_ele28_ht150 = new TH2D("N_pass_ele_pt_ht_ele28_ht150","Nr. of Events vs Electron pT & HT for Ele28_HT150;Electron pT (GeV);HT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_htBins,x_htBins);
    TH1D* N_pass_ele_pt_ele30_jet35_OR_ele35 = new TH1D("N_pass_ele_pt_ele30_jet35_OR_ele35","Nr. of Events vs Electron pT for Ele30_Jet35 OR Ele35;Electron pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins);
    TH1D* N_pass_ele_eta_ele30_jet35_OR_ele35 = new TH1D("N_pass_ele_eta_ele30_jet35_OR_ele35","Nr. of Events vs Electron eta for Ele30_Jet35 OR Ele35;Electron eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_ele_sceta_ele30_jet35_OR_ele35 = new TH1D("N_pass_ele_sceta_ele30_jet35_OR_ele35","Nr. of Events vs Electron SuperCluster eta for Ele30_Jet35 OR Ele35;Electron SuperCluster eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_jet_pt_ele30_jet35_OR_ele35 = new TH1D("N_pass_jet_pt_ele30_jet35_OR_ele35","Nr. of Events vs Leading Jet pT for Ele30_Jet35 OR Ele35;Leading Jet pT (GeV);Nr. of Events",n_jetptBins,x_jetptBins);
    TH1D* N_pass_jet_eta_ele30_jet35_OR_ele35 = new TH1D("N_pass_jet_eta_ele30_jet35_OR_ele35","Nr. of Events vs Leading Jet eta for Ele30_Jet35 OR Ele35;Leading Jet eta;Nr. of Events",n_jetetaBins,x_jetetaBins);
    TH1D* N_pass_ht_ele30_jet35_OR_ele35 = new TH1D("N_pass_ht_ele30_jet35_OR_ele35","Nr. of Events vs HT for Ele30_Jet35 OR Ele35;HT (GeV);Nr. of Events",n_htBins,x_htBins);
    TH1D* N_pass_njets_ele30_jet35_OR_ele35 = new TH1D("N_pass_njets_ele30_jet35_OR_ele35","Nr. of Events vs Nr. of Jets for Ele30_Jet35 OR Ele35;Nr. of Jets;Nr. of Events",n_njetBins,x_njetBins);
    TH1D* N_pass_npv_ele30_jet35_OR_ele35 = new TH1D("N_pass_npv_ele30_jet35_OR_ele35","Nr. of Events vs Nr. of Primary Vertices for Ele30_Jet35 OR Ele35;NPV;Nr. of Events",75,0,75);
    TH2D* N_pass_ele_pt_ele_eta_ele30_jet35_OR_ele35 = new TH2D("N_pass_ele_pt_ele_eta_ele30_jet35_OR_ele35","Nr. of Events vs Electron pT & Electron eta for Ele30_Jet35 OR Ele35;Electron pT (GeV);Electron eta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_ele_sceta_ele30_jet35_OR_ele35 = new TH2D("N_pass_ele_pt_ele_sceta_ele30_jet35_OR_ele35","Nr. of Events vs Electron pT & Electron SuperClustereta for Ele30_Jet35 OR Ele35;Electron pT (GeV);Electron SuperClustereta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_jet_pt_ele30_jet35_OR_ele35 = new TH2D("N_pass_ele_pt_jet_pt_ele30_jet35_OR_ele35","Nr. of Events vs Electron pT & Leading Jet pT for Ele30_Jet35 OR Ele35;Electron pT (GeV);Leading Jet pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
    TH2D* N_pass_ele_pt_ht_ele30_jet35_OR_ele35 = new TH2D("N_pass_ele_pt_ht_ele30_jet35_OR_ele35","Nr. of Events vs Electron pT & HT for Ele30_Jet35 OR Ele35;Electron pT (GeV);HT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_htBins,x_htBins);
    TH1D* N_pass_ele_pt_ele28_ht150_OR_ele35 = new TH1D("N_pass_ele_pt_ele28_ht150_OR_ele35","Nr. of Events vs Electron pT for Ele28_HT150 OR Ele35;Electron pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins);
    TH1D* N_pass_ele_eta_ele28_ht150_OR_ele35 = new TH1D("N_pass_ele_eta_ele28_ht150_OR_ele35","Nr. of Events vs Electron eta for Ele28_HT150 OR Ele35;Electron eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_ele_sceta_ele28_ht150_OR_ele35 = new TH1D("N_pass_ele_sceta_ele28_ht150_OR_ele35","Nr. of Events vs Electron SuperCluster eta for Ele28_HT150 OR Ele35;Electron SuperCluster eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_jet_pt_ele28_ht150_OR_ele35 = new TH1D("N_pass_jet_pt_ele28_ht150_OR_ele35","Nr. of Events vs Leading Jet pT for Ele28_HT150 OR Ele35;Leading Jet pT (GeV);Nr. of Events",n_jetptBins,x_jetptBins);
    TH1D* N_pass_jet_eta_ele28_ht150_OR_ele35 = new TH1D("N_pass_jet_eta_ele28_ht150_OR_ele35","Nr. of Events vs Leading Jet eta for Ele28_HT150 OR Ele35;Leading Jet eta;Nr. of Events",n_jetetaBins,x_jetetaBins);
    TH1D* N_pass_ht_ele28_ht150_OR_ele35 = new TH1D("N_pass_ht_ele28_ht150_OR_ele35","Nr. of Events vs HT for Ele28_HT150 OR Ele35;HT (GeV);Nr. of Events",n_htBins,x_htBins);
    TH1D* N_pass_njets_ele28_ht150_OR_ele35 = new TH1D("N_pass_njets_ele28_ht150_OR_ele35","Nr. of Events vs Nr. of Jets for Ele28_HT150 OR Ele35;Nr. of Jets;Nr. of Events",n_njetBins,x_njetBins);
    TH1D* N_pass_npv_ele28_ht150_OR_ele35 = new TH1D("N_pass_npv_ele28_ht150_OR_ele35","Nr. of Events vs Nr. of Primary Vertices for Ele28_HT150 OR Ele35;NPV;Nr. of Events",75,0,75);
    TH2D* N_pass_ele_pt_ele_eta_ele28_ht150_OR_ele35 = new TH2D("N_pass_ele_pt_ele_eta_ele28_ht150_OR_ele35","Nr. of Events vs Electron pT & Electron eta for Ele28_HT150 OR Ele35;Electron pT (GeV);Electron eta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_ele_sceta_ele28_ht150_OR_ele35 = new TH2D("N_pass_ele_pt_ele_sceta_ele28_ht150_OR_ele35","Nr. of Events vs Electron pT & Electron SuperClustereta for Ele28_HT150 OR Ele35;Electron pT (GeV);Electron SuperClustereta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_jet_pt_ele28_ht150_OR_ele35 = new TH2D("N_pass_ele_pt_jet_pt_ele28_ht150_OR_ele35","Nr. of Events vs Electron pT & Leading Jet pT for Ele28_HT150 OR Ele35;Electron pT (GeV);Leading Jet pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
    TH2D* N_pass_ele_pt_ht_ele28_ht150_OR_ele35 = new TH2D("N_pass_ele_pt_ht_ele28_ht150_OR_ele35","Nr. of Events vs Electron pT & HT for Ele28_HT150 OR Ele35;Electron pT (GeV);HT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_htBins,x_htBins);
    TH1D* N_pass_ele_pt_ele30_jet35_OR_ele28_ht150_OR_ele35 = new TH1D("N_pass_ele_pt_ele30_jet35_OR_ele28_ht150_OR_ele35","Nr. of Events vs Electron pT for Ele30_Jet35 OR Ele28_HT150 OR Ele35;Electron pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins);
    TH1D* N_pass_ele_eta_ele30_jet35_OR_ele28_ht150_OR_ele35 = new TH1D("N_pass_ele_eta_ele30_jet35_OR_ele28_ht150_OR_ele35","Nr. of Events vs Electron eta for Ele30_Jet35 OR Ele28_HT150 OR Ele35;Electron eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_ele_sceta_ele30_jet35_OR_ele28_ht150_OR_ele35 = new TH1D("N_pass_ele_sceta_ele30_jet35_OR_ele28_ht150_OR_ele35","Nr. of Events vs Electron SuperCluster eta for Ele30_Jet35 OR Ele28_HT150 OR Ele35;Electron SuperCluster eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_jet_pt_ele30_jet35_OR_ele28_ht150_OR_ele35 = new TH1D("N_pass_jet_pt_ele30_jet35_OR_ele28_ht150_OR_ele35","Nr. of Events vs Leading Jet pT for Ele30_Jet35 OR Ele28_HT150 OR Ele35;Leading Jet pT (GeV);Nr. of Events",n_jetptBins,x_jetptBins);
    TH1D* N_pass_jet_eta_ele30_jet35_OR_ele28_ht150_OR_ele35 = new TH1D("N_pass_jet_eta_ele30_jet35_OR_ele28_ht150_OR_ele35","Nr. of Events vs Leading Jet eta for Ele30_Jet35 OR Ele28_HT150 OR Ele35;Leading Jet eta;Nr. of Events",n_jetetaBins,x_jetetaBins);
    TH1D* N_pass_ht_ele30_jet35_OR_ele28_ht150_OR_ele35 = new TH1D("N_pass_ht_ele30_jet35_OR_ele28_ht150_OR_ele35","Nr. of Events vs HT for Ele30_Jet35 OR Ele28_HT150 OR Ele35;HT (GeV);Nr. of Events",n_htBins,x_htBins);
    TH1D* N_pass_njets_ele30_jet35_OR_ele28_ht150_OR_ele35 = new TH1D("N_pass_njets_ele30_jet35_OR_ele28_ht150_OR_ele35","Nr. of Events vs Nr. of Jets for Ele30_Jet35 OR Ele28_HT150 OR Ele35;Nr. of Jets;Nr. of Events",n_njetBins,x_njetBins);
    TH1D* N_pass_npv_ele30_jet35_OR_ele28_ht150_OR_ele35 = new TH1D("N_pass_npv_ele30_jet35_OR_ele28_ht150_OR_ele35","Nr. of Events vs Nr. of Primary Vertices for Ele30_Jet35 OR Ele28_HT150 OR Ele35;NPV;Nr. of Events",75,0,75);
    TH2D* N_pass_ele_pt_ele_eta_ele30_jet35_OR_ele28_ht150_OR_ele35 = new TH2D("N_pass_ele_pt_ele_eta_ele30_jet35_OR_ele28_ht150_OR_ele35","Nr. of Events vs Electron pT & Electron eta for Ele30_Jet35 OR Ele28_HT150 OR Ele35;Electron pT (GeV);Electron eta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_ele_sceta_ele30_jet35_OR_ele28_ht150_OR_ele35 = new TH2D("N_pass_ele_pt_ele_sceta_ele30_jet35_OR_ele28_ht150_OR_ele35","Nr. of Events vs Electron pT & Electron SuperClustereta for Ele30_Jet35 OR Ele28_HT150 OR Ele35;Electron pT (GeV);Electron SuperClustereta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_jet_pt_ele30_jet35_OR_ele28_ht150_OR_ele35 = new TH2D("N_pass_ele_pt_jet_pt_ele30_jet35_OR_ele28_ht150_OR_ele35","Nr. of Events vs Electron pT & Leading Jet pT for Ele30_Jet35 OR Ele28_HT150 OR Ele35;Electron pT (GeV);Leading Jet pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
    TH2D* N_pass_ele_pt_ht_ele30_jet35_OR_ele28_ht150_OR_ele35 = new TH2D("N_pass_ele_pt_ht_ele30_jet35_OR_ele28_ht150_OR_ele35","Nr. of Events vs Electron pT & HT for Ele30_Jet35 OR Ele28_HT150 OR Ele35;Electron pT (GeV);HT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_htBins,x_htBins);
    TH1D* N_pass_ele_pt_ele30_jet35_OR_ele28_ht150 = new TH1D("N_pass_ele_pt_ele30_jet35_OR_ele28_ht150","Nr. of Events vs Electron pT for Ele30_Jet35 OR Ele28_HT150;Electron pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins);
    TH1D* N_pass_ele_eta_ele30_jet35_OR_ele28_ht150 = new TH1D("N_pass_ele_eta_ele30_jet35_OR_ele28_ht150","Nr. of Events vs Electron eta for Ele30_Jet35 OR Ele28_HT150;Electron eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_ele_sceta_ele30_jet35_OR_ele28_ht150 = new TH1D("N_pass_ele_sceta_ele30_jet35_OR_ele28_ht150","Nr. of Events vs Electron SuperCluster eta for Ele30_Jet35 OR Ele28_HT150;Electron SuperCluster eta;Nr. of Events",n_eleetaBins,x_eleetaBins);
    TH1D* N_pass_jet_pt_ele30_jet35_OR_ele28_ht150 = new TH1D("N_pass_jet_pt_ele30_jet35_OR_ele28_ht150","Nr. of Events vs Leading Jet pT for Ele30_Jet35 OR Ele28_HT150;Leading Jet pT (GeV);Nr. of Events",n_jetptBins,x_jetptBins);
    TH1D* N_pass_jet_eta_ele30_jet35_OR_ele28_ht150 = new TH1D("N_pass_jet_eta_ele30_jet35_OR_ele28_ht150","Nr. of Events vs Leading Jet eta for Ele30_Jet35 OR Ele28_HT150;Leading Jet eta;Nr. of Events",n_jetetaBins,x_jetetaBins);
    TH1D* N_pass_ht_ele30_jet35_OR_ele28_ht150 = new TH1D("N_pass_ht_ele30_jet35_OR_ele28_ht150","Nr. of Events vs HT for Ele30_Jet35 OR Ele28_HT150;HT (GeV);Nr. of Events",n_htBins,x_htBins);
    TH1D* N_pass_njets_ele30_jet35_OR_ele28_ht150 = new TH1D("N_pass_njets_ele30_jet35_OR_ele28_ht150","Nr. of Events vs Nr. of Jets for Ele30_Jet35 OR Ele28_HT150;Nr. of Jets;Nr. of Events",n_njetBins,x_njetBins);
    TH1D* N_pass_npv_ele30_jet35_OR_ele28_ht150 = new TH1D("N_pass_npv_ele30_jet35_OR_ele28_ht150","Nr. of Events vs Nr. of Primary Vertices for Ele30_Jet35 OR Ele28_HT150;NPV;Nr. of Events",75,0,75);
    TH2D* N_pass_ele_pt_ele_eta_ele30_jet35_OR_ele28_ht150 = new TH2D("N_pass_ele_pt_ele_eta_ele30_jet35_OR_ele28_ht150","Nr. of Events vs Electron pT & Electron eta for Ele30_Jet35 OR Ele28_HT150;Electron pT (GeV);Electron eta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_ele_sceta_ele30_jet35_OR_ele28_ht150 = new TH2D("N_pass_ele_pt_ele_sceta_ele30_jet35_OR_ele28_ht150","Nr. of Events vs Electron pT & Electron SuperClustereta for Ele30_Jet35 OR Ele28_HT150;;Electron pT (GeV);Electron SuperClustereta;Nr. of Events",n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
    TH2D* N_pass_ele_pt_jet_pt_ele30_jet35_OR_ele28_ht150 = new TH2D("N_pass_ele_pt_jet_pt_ele30_jet35_OR_ele28_ht150","Nr. of Events vs Electron pT & Leading Jet pT for Ele30_Jet35 OR Ele28_HT150;Electron pT (GeV);Leading Jet pT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
    TH2D* N_pass_ele_pt_ht_ele30_jet35_OR_ele28_ht150 = new TH2D("N_pass_ele_pt_ht_ele30_jet35_OR_ele28_ht150","Nr. of Events vs Electron pT & HT for Ele30_Jet35 OR Ele28_HT150;Electron pT (GeV);HT (GeV);Nr. of Events",n_eleptBins,x_eleptBins,n_htBins,x_htBins);

    // For correlation calculations
    TEfficiency *teffi_ref = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele27_only = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele35_only = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele30_jet35_only = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele28_ht150_only = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele30_jet35_OR_ele35_only = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele28_ht150_OR_ele35_only = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele30_jet35_OR_ele28_ht150_only = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele27_and_ref = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele35_and_ref = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele30_jet35_and_ref = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele28_ht150_and_ref = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele30_jet35_OR_ele35_and_ref = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele28_ht150_OR_ele35_and_ref = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref = new TEfficiency("","",2,0,2);
    TEfficiency *teffi_e_ele30_jet35_OR_ele28_ht150_and_ref = new TEfficiency("","",2,0,2);

    teffi_ref->SetUseWeightedEvents();
    teffi_e_ele27_only->SetUseWeightedEvents();
    teffi_e_ele35_only->SetUseWeightedEvents();
    teffi_e_ele30_jet35_only->SetUseWeightedEvents();
    teffi_e_ele28_ht150_only->SetUseWeightedEvents();
    teffi_e_ele30_jet35_OR_ele35_only->SetUseWeightedEvents();
    teffi_e_ele28_ht150_OR_ele35_only->SetUseWeightedEvents();
    teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only->SetUseWeightedEvents();
    teffi_e_ele30_jet35_OR_ele28_ht150_only->SetUseWeightedEvents();
    teffi_e_ele27_and_ref->SetUseWeightedEvents();
    teffi_e_ele35_and_ref->SetUseWeightedEvents();
    teffi_e_ele30_jet35_and_ref->SetUseWeightedEvents();
    teffi_e_ele28_ht150_and_ref->SetUseWeightedEvents();
    teffi_e_ele30_jet35_OR_ele35_and_ref->SetUseWeightedEvents();
    teffi_e_ele28_ht150_OR_ele35_and_ref->SetUseWeightedEvents();
    teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref->SetUseWeightedEvents();
    teffi_e_ele30_jet35_OR_ele28_ht150_and_ref->SetUseWeightedEvents();


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

    if(is_data_input==0){
        comm_chain->SetBranchAddress("comm_ntuple", &comm_ntuple );
    }

    reco_chain->SetBranchAddress("reco_ntuple", &reco_ntuple );

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
            int SL_tag_comm = comm_ntuple->SL_tag;
            int DL_tag_comm = comm_ntuple->DL_tag;
            int FH_tag_comm = comm_ntuple->FH_tag;

            N_SL_tag += SL_tag_comm;
            N_DL_tag += DL_tag_comm;
            N_FH_tag += FH_tag_comm;

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

        system("cp Pile_Up_Calc/* .");
        system("./Pileup_calculation_script.sh");
        system("rm -rf Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt Pileup_calculation_script.sh PU_data_hist_prod.C pileupCalc.py pileup_latest.txt PU_hist_calc.cc");
        std::cout<<"PU weight calculation Done\n\n";
        
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

        int nEvent = reco_ntuple->nEvent;
        int ls = reco_ntuple->ls;
        int run = reco_ntuple->run;
        int is_data = reco_ntuple->is_data;
        int data_era = reco_ntuple->data_era;
        int save_gen_info = reco_ntuple->save_gen_info;
        int is_trigger_study = reco_ntuple->is_trigger_study;
        int is_tight_skim = reco_ntuple->is_tight_skim;
        double npv = reco_ntuple->npv;

        int pass_HLT_Ele27_WPTight_Gsf = reco_ntuple->pass_HLT_Ele27_WPTight_Gsf_;
        int pass_HLT_Ele35_WPTight_Gsf = reco_ntuple->pass_HLT_Ele35_WPTight_Gsf_;
        int pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned = reco_ntuple->pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned_;
        int pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150 = reco_ntuple->pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150_;
        int pass_HLT_IsoMu27 = reco_ntuple->pass_HLT_IsoMu27_;
        int pass_HLT_IsoMu24_eta2p1 = reco_ntuple->pass_HLT_IsoMu24_eta2p1_;
        int pass_HLT_IsoMu24 = reco_ntuple->pass_HLT_IsoMu24_;
        int pass_HLT_IsoTkMu24 = reco_ntuple->pass_HLT_IsoTkMu24_;
        int pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = reco_ntuple->pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_;
        int pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = reco_ntuple->pass_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
        int pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = reco_ntuple->pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_;
        int pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = reco_ntuple->pass_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
        int pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = reco_ntuple->pass_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
        int pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = reco_ntuple->pass_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
        int pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = reco_ntuple->pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_;
        int pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 = reco_ntuple->pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_;
        int pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 = reco_ntuple->pass_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_;
        int pass_HLT_PFMET110_PFMHT110_IDTight = reco_ntuple->pass_HLT_PFMET110_PFMHT110_IDTight_;
        int pass_HLT_PFMET120_PFMHT120_IDTight = reco_ntuple->pass_HLT_PFMET120_PFMHT120_IDTight_;
        int pass_HLT_PFMET130_PFMHT130_IDTight = reco_ntuple->pass_HLT_PFMET130_PFMHT130_IDTight_;
        int pass_HLT_PFMET140_PFMHT140_IDTight = reco_ntuple->pass_HLT_PFMET140_PFMHT140_IDTight_;
        int pass_HLT_PFMETTypeOne120_PFMHT120_IDTight = reco_ntuple->pass_HLT_PFMETTypeOne120_PFMHT120_IDTight_;
        int pass_HLT_PFHT500_PFMET100_PFMHT100_IDTight = reco_ntuple->pass_HLT_PFHT500_PFMET100_PFMHT100_IDTight_;
        int pass_HLT_PFHT700_PFMET85_PFMHT85_IDTight = reco_ntuple->pass_HLT_PFHT700_PFMET85_PFMHT85_IDTight_;
        int pass_HLT_PFHT800_PFMET75_PFMHT75_IDTight = reco_ntuple->pass_HLT_PFHT800_PFMET75_PFMHT75_IDTight_;
        int pass_HLT_CaloMET250_HBHECleaned = reco_ntuple->pass_HLT_CaloMET250_HBHECleaned_;
        int pass_HLT_PFMET250_HBHECleaned = reco_ntuple->pass_HLT_PFMET250_HBHECleaned_;
        int pass_HLT_PFMET200_HBHE_BeamHaloCleaned = reco_ntuple->pass_HLT_PFMET200_HBHE_BeamHaloCleaned_;
        int pass_HLT_PFHT180 = reco_ntuple->pass_HLT_PFHT180_;
        int pass_HLT_PFHT250 = reco_ntuple->pass_HLT_PFHT250_;
        int pass_HLT_PFHT350 = reco_ntuple->pass_HLT_PFHT350_;
        int pass_HLT_PFHT370 = reco_ntuple->pass_HLT_PFHT370_;
        int pass_HLT_PFHT430 = reco_ntuple->pass_HLT_PFHT430_;
        int pass_HLT_PFHT510 = reco_ntuple->pass_HLT_PFHT510_;
        int pass_HLT_PFHT590 = reco_ntuple->pass_HLT_PFHT590_;
        int pass_HLT_PFHT680 = reco_ntuple->pass_HLT_PFHT680_;
        int pass_HLT_PFHT780 = reco_ntuple->pass_HLT_PFHT780_;
        int pass_HLT_PFHT890 = reco_ntuple->pass_HLT_PFHT890_;
        int pass_HLT_PFHT1050 = reco_ntuple->pass_HLT_PFHT1050_;
        int pass_HLT_PFJet40 = reco_ntuple->pass_HLT_PFJet40_;
        int pass_HLT_PFJet60 = reco_ntuple->pass_HLT_PFJet60_;
        int pass_HLT_PFJet80 = reco_ntuple->pass_HLT_PFJet80_;
        int pass_HLT_PFJet140 = reco_ntuple->pass_HLT_PFJet140_;
        int pass_HLT_PFJet200 = reco_ntuple->pass_HLT_PFJet200_;
        int pass_HLT_PFJet260 = reco_ntuple->pass_HLT_PFJet260_;
        int pass_HLT_PFJet320 = reco_ntuple->pass_HLT_PFJet320_;
        int pass_HLT_PFJet400 = reco_ntuple->pass_HLT_PFJet400_;
        int pass_HLT_PFJet450 = reco_ntuple->pass_HLT_PFJet450_;
        int pass_HLT_PFJet500 = reco_ntuple->pass_HLT_PFJet500_;
        int pass_HLT_PFJet550 = reco_ntuple->pass_HLT_PFJet550_;

        vdouble pt_trigger_object = reco_ntuple->pt_trigger_object_;
        vdouble eta_trigger_object = reco_ntuple->eta_trigger_object_;
        vdouble phi_trigger_object = reco_ntuple->phi_trigger_object_;
        vvstring filter_trigger_object = reco_ntuple->filter_trigger_object_;

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

        vdouble jet_jecSF_nominal = reco_ntuple->jet_jecSF_nominal;
        vdouble jet_jerSF_jesnominal_nominal = reco_ntuple->jet_jerSF_jesnominal_nominal;

        vdouble ele_sf_id_combined = reco_ntuple->ele_sf_id_combined;
        vdouble ele_sf_iso_combined = reco_ntuple->ele_sf_iso_combined;

        vdouble mu_sf_id_combined = reco_ntuple->mu_sf_id_combined;
        vdouble mu_sf_iso_combined = reco_ntuple->mu_sf_iso_combined;
        vdouble mu_sf_tracking_combined = reco_ntuple->mu_sf_tracking_combined;

        vdouble b_weight_jesnominal_nominal = reco_ntuple->b_weight_jesnominal_nominal;

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

        // Object Selections

        vint sel_ele_sl_index;
        vint sel_ele_veto_sl_index;
        vint sel_mu_sl_index;
        vint sel_mu_veto_sl_index;
        vint sel_jet_sl_index;
        vint sel_jet_sl_sorted_index;
        vdouble jet_pt_corr;
        vdouble jet_E_corr;

        sel_ele_sl_index.clear();
        sel_ele_veto_sl_index.clear();
        sel_mu_sl_index.clear();
        sel_mu_veto_sl_index.clear();
        sel_jet_sl_index.clear();
        sel_jet_sl_sorted_index.clear();
        jet_pt_corr.clear();
        jet_E_corr.clear();

        int n_ele_sl = 0;
        int n_ele_veto_sl = 0;
        int n_mu_sl = 0;
        int n_mu_veto_sl = 0;
        int n_jet_sl = 0;
        int n_btag_sl = 0;


        // Applying JEC and JER (nominal)
        double jec, jer, jes;
        for (int i=0; i<(int)jet_pt_uncorr.size(); i++){
            jec = jer = jes = 1.0;
            jec = jet_jecSF_nominal[i];
            jer = jet_jerSF_jesnominal_nominal[i];
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

        // Single Electron event selection
        bool is_e = 0;
        if (n_ele_sl == 1){
            if (n_ele_veto_sl == 1){
                if (n_jet_sl >= min_sl_njets){
                    //if (met_pt_phi_corr > min_sl_met){
                    is_e = 1;
                    //}
                }
            }
        }
        if (!is_e)
            continue;

        // Special Offline Selection
        // emu selection
        bool is_emu = 0;
        if (offline_sel == "emu"){
            if (n_mu_sl == 1){
                if (n_mu_veto_sl == 1)
                    is_emu = 1;
            }
            if (!is_emu)
                continue;
        }
        // Pure e selection
        bool is_pure_e = 0;
        if (offline_sel == "pure_e"){
            if (sample_dataset == "ttjets_dl")
                is_pure_e = 1;
            else{
                if (n_mu_veto_sl == 0)
                    is_pure_e = 1;
            }
            if (!is_pure_e)
                continue;
        }
        // ttHbb selection
        bool is_tthbb = 0;
        if (offline_sel == "tthbb"){
            if (n_mu_veto_sl == 0){
                if (n_btag_sl >= min_sl_nbtags){
                    if (met_pt_phi_corr > min_sl_met)
                        is_tthbb = 1;
                }
            }
            if (!is_tthbb)
                continue;
        }

        double electron_pt = ele_pt[sel_ele_sl_index[0]];
        double electron_eta = ele_eta[sel_ele_sl_index[0]];
        double electron_sceta = ele_sc_eta[sel_ele_sl_index[0]];
        double electron_phi = ele_phi[sel_ele_sl_index[0]];
        double leading_jet_pt = jet_pt_corr[sel_jet_sl_sorted_index[0]];
        double leading_jet_eta = jet_eta[sel_jet_sl_sorted_index[0]];
        double leading_jet_phi = jet_phi[sel_jet_sl_sorted_index[0]];
        double HT = 0;
        for (int i=0; i<(int)sel_jet_sl_sorted_index.size(); i++)
            HT += jet_pt_corr[sel_jet_sl_sorted_index[i]];
        int njets = n_jet_sl;

        // Systematic Variation
        bool syst_flag = 0;
        if (syst_var == "syst_nominal")
            syst_flag = 1;
        else if (syst_var == "syst_up"){
            if (HT > HT_syst_cut)
                syst_flag = 1;
        }
        else if (syst_var == "syst_down"){
            if (HT <= HT_syst_cut)
                syst_flag = 1;
        }
        if (!syst_flag)
            continue;

        // Calculating CSV SFs
        double csv_sf_jesnominal_nominal = 1;

        if (is_e){
            for(int i=0; i<(int)sel_jet_sl_sorted_index.size(); i++){
                csv_sf_jesnominal_nominal *= b_weight_jesnominal_nominal[sel_jet_sl_sorted_index[i]];
            }
        }

         // Reading out PU weights
         double PU_weight_mod, PU_weight_up_mod, PU_weight_down_mod;
         if (is_data_input==0){
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
         }
         else{
             PU_weight_mod = PU_weight_up_mod = PU_weight_down_mod = 1.0;
         }

         // Total Event weight
         double tot_weight = 1.0;
         tot_weight *= PU_weight_mod * ele_sf_id_combined[sel_ele_sl_index[0]] * ele_sf_iso_combined[sel_ele_sl_index[0]];
         if (is_emu)
             tot_weight *= mu_sf_id_combined[sel_mu_sl_index[0]] * mu_sf_iso_combined[sel_mu_sl_index[0]];

         N_e += tot_weight;

         // Reference Trigger pass selection
         int pass_ref = 0;
         if (offline_sel == "pure_e"){
            N_ref += tot_weight;
            pass_ref = 1;
         }
         else {
            if( pass_HLT_IsoTkMu24 == 1 || pass_HLT_IsoMu27 == 1 || pass_HLT_IsoMu24_eta2p1 == 1 || pass_HLT_IsoMu24 == 1 ){
                N_ref += tot_weight;
                pass_ref = 1;
            }
         }
         if (pass_ref == 1){
             N_total_ele_pt->Fill(electron_pt,tot_weight);
             N_total_ele_eta->Fill(electron_eta,tot_weight);
             N_total_ele_sceta->Fill(electron_sceta,tot_weight);
             N_total_jet_pt->Fill(leading_jet_pt,tot_weight);
             N_total_jet_eta->Fill(leading_jet_eta,tot_weight);
             N_total_ht->Fill(HT,tot_weight);
             N_total_njets->Fill(njets,tot_weight);
             N_total_npv->Fill(npv,tot_weight);
             N_total_ele_pt_ele_eta->Fill(electron_pt,electron_eta,tot_weight);
             N_total_ele_pt_ele_sceta->Fill(electron_pt,electron_sceta,tot_weight);
             N_total_ele_pt_jet_pt->Fill(electron_pt,leading_jet_pt,tot_weight);
             N_total_ele_pt_ht->Fill(electron_pt,HT,tot_weight);
         }

         /*
         // Matching of RECO objects with HLT Objects for signal trigger and reference triggers
         double dR_min1 = 9999;
         double dR_min2 = 9999;
         double dR_min11 = 9999;
         double dR_min22 = 9999;
         double dR_min3 = 9999;
         double dR_min4 = 9999;
         double dR = 9999;

         int ele_label1_match = 0;
         int ele_label2_match = 0;
         int ele_label11_match = 0;
         int ele_label22_match = 0;
         int ele_dR1_match_index = 0;
         int ele_dR2_match_index = 0;
         int ele_dR11_match_index = 0;
         int ele_dR22_match_index = 0;
         int ele_sig1_hlt_match = 0;
         int ele_sig2_hlt_match = 0;
         int ele_sig11_hlt_match = 0;
         int ele_sig22_hlt_match = 0;

         int jet_label1_match = 0;
         int jet_label2_match = 0;
         int jet_dR1_match_index = 0;
         int jet_dR2_match_index = 0;
         int jet_sig1_hlt_match = 0;
         int jet_sig2_hlt_match = 0;


         for(unsigned int l=0; l<eta_trigger_object.size(); l++){

             // Matching Electron
             ele_label1_match = check_filter_label( filter_trigger_object[l] , "hltEle30erJetC34WPTightGsfTrackIsoFilter" );
             if (ele_label1_match == 1){
                 dR = dR_calc(electron_eta, electron_phi, eta_trigger_object[l], phi_trigger_object[l]);
                 if( dR < 0.3 ){
                     if( dR < dR_min1){
                         ele_dR1_match_index = l;
                         ele_sig1_hlt_match = 1;
                         dR_min1 = dR;
                     }
                 }
             }

             ele_label2_match = check_filter_label( filter_trigger_object[l] , "hltEle28erHTT100WPTightGsfTrackIsoFilter" );
             if (ele_label2_match == 1){
                 dR = dR_calc(electron_eta, electron_phi, eta_trigger_object[l], phi_trigger_object[l]);
                 if( dR < 0.3 ){
                     if( dR < dR_min2){
                         ele_dR2_match_index = l;
                         ele_sig2_hlt_match = 1;
                         dR_min2 = dR;
                     }
                 }
             }

             ele_label11_match = check_filter_label( filter_trigger_object[l] , "hltEle27WPTightGsfTrackIsoFilter" );
             if (ele_label11_match == 1){
                 dR = dR_calc(electron_eta, electron_phi, eta_trigger_object[l], phi_trigger_object[l]);
                 if( dR < 0.3 ){
                     if( dR < dR_min11){
                         ele_dR11_match_index = l;
                         ele_sig11_hlt_match = 1;
                         dR_min11 = dR;
                     }
                 }
             }

             ele_label22_match = check_filter_label( filter_trigger_object[l] , "hltEle35noerWPTightGsfTrackIsoFilter" );
             if (ele_label22_match == 1){
                 dR = dR_calc(electron_eta, electron_phi, eta_trigger_object[l], phi_trigger_object[l]);
                 if( dR < 0.3 ){
                     if( dR < dR_min22){
                         ele_dR22_match_index = l;
                         ele_sig22_hlt_match = 1;
                         dR_min22 = dR;
                     }
                 }
             }

             // Matching Leading Jet
             jet_label1_match = check_filter_label( filter_trigger_object[l] , "hltEle30PFJet35EleCleaned" );
             if (jet_label1_match == 1){
                 dR = dR_calc(leading_jet_eta, leading_jet_phi, eta_trigger_object[l], phi_trigger_object[l]);
                 if( dR < 0.3 ){
                     if( dR < dR_min3){
                         jet_dR1_match_index = l;
                         jet_sig1_hlt_match = 1;
                         dR_min3 = dR;
                     }
                 }
             }
         }

         jet_label2_match = 1;
         jet_dR2_match_index = -1;
         jet_sig2_hlt_match = 1;
         */

         int no_overlap = 0;

         // Checking trigger passes
         int pass_ele27 = 0;
         int pass_ele35 = 0;
         int pass_ele30_jet35 = 0;
         int pass_ele28_ht150 = 0;
         int pass_ele30_jet35_OR_ele35 = 0;
         int pass_ele28_ht150_OR_ele35 = 0;
         int pass_ele30_jet35_OR_ele28_ht150_OR_ele35 = 0;
         int pass_ele30_jet35_OR_ele28_ht150 = 0;

         if(pass_HLT_Ele27_WPTight_Gsf != -1){
             no_overlap = 1;
             //pass_ele27 = pass_HLT_Ele27_WPTight_Gsf * ele_sig11_hlt_match * no_overlap;
             pass_ele27 = pass_HLT_Ele27_WPTight_Gsf;
             if(pass_ele27 == 1)
                N_e_ele27_only += tot_weight;

             if (pass_ref==1){
                 N_e_den_ele27 += tot_weight;

                 if(pass_ele27 == 1){
                    N_e_ele27 += tot_weight;
                    N_pass_ele_pt_ele27->Fill(electron_pt,tot_weight);
                    N_pass_ele_eta_ele27->Fill(electron_eta,tot_weight);
                    N_pass_ele_sceta_ele27->Fill(electron_sceta,tot_weight);
                    N_pass_jet_pt_ele27->Fill(leading_jet_pt,tot_weight);
                    N_pass_jet_eta_ele27->Fill(leading_jet_eta,tot_weight);
                    N_pass_ht_ele27->Fill(HT,tot_weight);
                    N_pass_njets_ele27->Fill(njets,tot_weight);
                    N_pass_npv_ele27->Fill(npv,tot_weight);
                    N_pass_ele_pt_ele_eta_ele27->Fill(electron_pt,electron_eta,tot_weight);
                    N_pass_ele_pt_ele_sceta_ele27->Fill(electron_pt,electron_sceta,tot_weight);
                    N_pass_ele_pt_jet_pt_ele27->Fill(electron_pt,leading_jet_pt,tot_weight);
                    N_pass_ele_pt_ht_ele27->Fill(electron_pt,HT,tot_weight);
                 }
             }
         }

         if(pass_HLT_Ele35_WPTight_Gsf != -1){
             no_overlap = 1;
             //pass_ele35 = pass_HLT_Ele35_WPTight_Gsf * ele_sig22_hlt_match * no_overlap;
             pass_ele35 = pass_HLT_Ele35_WPTight_Gsf;
             if(pass_ele35 == 1)
                N_e_ele35_only += tot_weight;

             if (pass_ref==1){
                 N_e_den_ele35 += tot_weight;

                 if(pass_ele35 == 1){
                    N_e_ele35 += tot_weight;
                    N_pass_ele_pt_ele35->Fill(electron_pt,tot_weight);
                    N_pass_ele_eta_ele35->Fill(electron_eta,tot_weight);
                    N_pass_ele_sceta_ele35->Fill(electron_sceta,tot_weight);
                    N_pass_jet_pt_ele35->Fill(leading_jet_pt,tot_weight);
                    N_pass_jet_eta_ele35->Fill(leading_jet_eta,tot_weight);
                    N_pass_ht_ele35->Fill(HT,tot_weight);
                    N_pass_njets_ele35->Fill(njets,tot_weight);
                    N_pass_npv_ele35->Fill(npv,tot_weight);
                    N_pass_ele_pt_ele_eta_ele35->Fill(electron_pt,electron_eta,tot_weight);
                    N_pass_ele_pt_ele_sceta_ele35->Fill(electron_pt,electron_sceta,tot_weight);
                    N_pass_ele_pt_jet_pt_ele35->Fill(electron_pt,leading_jet_pt,tot_weight);
                    N_pass_ele_pt_ht_ele35->Fill(electron_pt,HT,tot_weight);
                 }
             }
         }

         if(pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned != -1){
             /*
              if ( dR_calc( leading_jet_eta, leading_jet_phi, eta_trigger_object[ele_dR1_match_index], phi_trigger_object[ele_dR1_match_index]  ) > 0.3 ) {
              if ( dR_calc( electron_eta, electron_phi, eta_trigger_object[jet_dR1_match_index], phi_trigger_object[jet_dR1_match_index]  ) > 0.3 )
              no_overlap = 1;
              }
              */
             no_overlap = 1;
             //pass_ele30_jet35 = pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned * ele_sig1_hlt_match * jet_sig1_hlt_match * no_overlap;
             pass_ele30_jet35 = pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned;
             if(pass_ele30_jet35 == 1)
                N_e_ele30_jet35_only += tot_weight;

             if (pass_ref==1){
                 N_e_den_ele30_jet35 += tot_weight;

                 if(pass_ele30_jet35 == 1){
                    N_e_ele30_jet35 += tot_weight;
                    N_pass_ele_pt_ele30_jet35->Fill(electron_pt,tot_weight);
                    N_pass_ele_eta_ele30_jet35->Fill(electron_eta,tot_weight);
                    N_pass_ele_sceta_ele30_jet35->Fill(electron_sceta,tot_weight);
                    N_pass_jet_pt_ele30_jet35->Fill(leading_jet_pt,tot_weight);
                    N_pass_jet_eta_ele30_jet35->Fill(leading_jet_eta,tot_weight);
                    N_pass_ht_ele30_jet35->Fill(HT,tot_weight);
                    N_pass_njets_ele30_jet35->Fill(njets,tot_weight);
                    N_pass_npv_ele30_jet35->Fill(npv,tot_weight);
                    N_pass_ele_pt_ele_eta_ele30_jet35->Fill(electron_pt,electron_eta,tot_weight);
                    N_pass_ele_pt_ele_sceta_ele30_jet35->Fill(electron_pt,electron_sceta,tot_weight);
                    N_pass_ele_pt_jet_pt_ele30_jet35->Fill(electron_pt,leading_jet_pt,tot_weight);
                    N_pass_ele_pt_ht_ele30_jet35->Fill(electron_pt,HT,tot_weight);
                 }
             }
         }

         if(pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150 != -1){
             //pass_ele28_ht150 = pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150 * ele_sig2_hlt_match * jet_sig2_hlt_match;
             pass_ele28_ht150 = pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150;
             if(pass_ele28_ht150 == 1)
                N_e_ele28_ht150_only += tot_weight;

             if (pass_ref==1){
                 N_e_den_ele28_ht150 += tot_weight;

                 if(pass_ele28_ht150 == 1){
                    N_e_ele28_ht150 += tot_weight;
                    N_pass_ele_pt_ele28_ht150->Fill(electron_pt,tot_weight);
                    N_pass_ele_eta_ele28_ht150->Fill(electron_eta,tot_weight);
                    N_pass_ele_sceta_ele28_ht150->Fill(electron_sceta,tot_weight);
                    N_pass_jet_pt_ele28_ht150->Fill(leading_jet_pt,tot_weight);
                    N_pass_jet_eta_ele28_ht150->Fill(leading_jet_eta,tot_weight);
                    N_pass_ht_ele28_ht150->Fill(HT,tot_weight);
                    N_pass_njets_ele28_ht150->Fill(njets,tot_weight);
                    N_pass_npv_ele28_ht150->Fill(npv,tot_weight);
                    N_pass_ele_pt_ele_eta_ele28_ht150->Fill(electron_pt,electron_eta,tot_weight);
                    N_pass_ele_pt_ele_sceta_ele28_ht150->Fill(electron_pt,electron_sceta,tot_weight);
                    N_pass_ele_pt_jet_pt_ele28_ht150->Fill(electron_pt,leading_jet_pt,tot_weight);
                    N_pass_ele_pt_ht_ele28_ht150->Fill(electron_pt,HT,tot_weight);
                 }
             }
         }

         if(pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned != -1 || pass_HLT_Ele35_WPTight_Gsf !=-1){
             if (pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned==1 || pass_HLT_Ele35_WPTight_Gsf==1)
                 pass_ele30_jet35_OR_ele35 = 1;
             if(pass_ele30_jet35_OR_ele35 == 1)
                N_e_ele30_jet35_OR_ele35_only += tot_weight;

             if (pass_ref==1){
                 N_e_den_ele30_jet35_OR_ele35 += tot_weight;

                 if(pass_ele30_jet35_OR_ele35 == 1){
                    N_e_ele30_jet35_OR_ele35 += tot_weight;
                    N_pass_ele_pt_ele30_jet35_OR_ele35->Fill(electron_pt,tot_weight);
                    N_pass_ele_eta_ele30_jet35_OR_ele35->Fill(electron_eta,tot_weight);
                    N_pass_ele_sceta_ele30_jet35_OR_ele35->Fill(electron_sceta,tot_weight);
                    N_pass_jet_pt_ele30_jet35_OR_ele35->Fill(leading_jet_pt,tot_weight);
                    N_pass_jet_eta_ele30_jet35_OR_ele35->Fill(leading_jet_eta,tot_weight);
                    N_pass_ht_ele30_jet35_OR_ele35->Fill(HT,tot_weight);
                    N_pass_njets_ele30_jet35_OR_ele35->Fill(njets,tot_weight);
                    N_pass_npv_ele30_jet35_OR_ele35->Fill(npv,tot_weight);
                    N_pass_ele_pt_ele_eta_ele30_jet35_OR_ele35->Fill(electron_pt,electron_eta,tot_weight);
                    N_pass_ele_pt_ele_sceta_ele30_jet35_OR_ele35->Fill(electron_pt,electron_sceta,tot_weight);
                    N_pass_ele_pt_jet_pt_ele30_jet35_OR_ele35->Fill(electron_pt,leading_jet_pt,tot_weight);
                    N_pass_ele_pt_ht_ele30_jet35_OR_ele35->Fill(electron_pt,HT,tot_weight);
                 }
             }
         }

         if(pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150 != -1 || pass_HLT_Ele35_WPTight_Gsf !=-1){
             if (pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150==1 || pass_HLT_Ele35_WPTight_Gsf==1)
                pass_ele28_ht150_OR_ele35 = 1;
             if(pass_ele28_ht150_OR_ele35 == 1)
                N_e_ele28_ht150_OR_ele35_only += tot_weight;

             if (pass_ref==1){
                 N_e_den_ele28_ht150_OR_ele35 += tot_weight;

                 if(pass_ele28_ht150_OR_ele35 == 1){
                    N_e_ele28_ht150_OR_ele35 += tot_weight;
                    N_pass_ele_pt_ele28_ht150_OR_ele35->Fill(electron_pt,tot_weight);
                    N_pass_ele_eta_ele28_ht150_OR_ele35->Fill(electron_eta,tot_weight);
                    N_pass_ele_sceta_ele28_ht150_OR_ele35->Fill(electron_sceta,tot_weight);
                    N_pass_jet_pt_ele28_ht150_OR_ele35->Fill(leading_jet_pt,tot_weight);
                    N_pass_jet_eta_ele28_ht150_OR_ele35->Fill(leading_jet_eta,tot_weight);
                    N_pass_ht_ele28_ht150_OR_ele35->Fill(HT,tot_weight);
                    N_pass_njets_ele28_ht150_OR_ele35->Fill(njets,tot_weight);
                    N_pass_npv_ele28_ht150_OR_ele35->Fill(npv,tot_weight);
                    N_pass_ele_pt_ele_eta_ele28_ht150_OR_ele35->Fill(electron_pt,electron_eta,tot_weight);
                    N_pass_ele_pt_ele_sceta_ele28_ht150_OR_ele35->Fill(electron_pt,electron_sceta,tot_weight);
                    N_pass_ele_pt_jet_pt_ele28_ht150_OR_ele35->Fill(electron_pt,leading_jet_pt,tot_weight);
                    N_pass_ele_pt_ht_ele28_ht150_OR_ele35->Fill(electron_pt,HT,tot_weight);
                 }
             }
         }

         if(pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned != -1 || pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150 !=-1 || pass_HLT_Ele35_WPTight_Gsf !=-1){
             if (pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned==1 || pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150==1 || pass_HLT_Ele35_WPTight_Gsf==1)
                 pass_ele30_jet35_OR_ele28_ht150_OR_ele35 = 1;
             if(pass_ele30_jet35_OR_ele28_ht150_OR_ele35 == 1)
                N_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only += tot_weight;

             if (pass_ref==1){
                 N_e_den_ele30_jet35_OR_ele28_ht150_OR_ele35 += tot_weight;

                 if(pass_ele30_jet35_OR_ele28_ht150_OR_ele35 == 1){
                    N_e_ele30_jet35_OR_ele28_ht150_OR_ele35 += tot_weight;
                    N_pass_ele_pt_ele30_jet35_OR_ele28_ht150_OR_ele35->Fill(electron_pt,tot_weight);
                    N_pass_ele_eta_ele30_jet35_OR_ele28_ht150_OR_ele35->Fill(electron_eta,tot_weight);
                    N_pass_ele_sceta_ele30_jet35_OR_ele28_ht150_OR_ele35->Fill(electron_sceta,tot_weight);
                    N_pass_jet_pt_ele30_jet35_OR_ele28_ht150_OR_ele35->Fill(leading_jet_pt,tot_weight);
                    N_pass_jet_eta_ele30_jet35_OR_ele28_ht150_OR_ele35->Fill(leading_jet_eta,tot_weight);
                    N_pass_ht_ele30_jet35_OR_ele28_ht150_OR_ele35->Fill(HT,tot_weight);
                    N_pass_njets_ele30_jet35_OR_ele28_ht150_OR_ele35->Fill(njets,tot_weight);
                    N_pass_npv_ele30_jet35_OR_ele28_ht150_OR_ele35->Fill(npv,tot_weight);
                    N_pass_ele_pt_ele_eta_ele30_jet35_OR_ele28_ht150_OR_ele35->Fill(electron_pt,electron_eta,tot_weight);
                    N_pass_ele_pt_ele_sceta_ele30_jet35_OR_ele28_ht150_OR_ele35->Fill(electron_pt,electron_sceta,tot_weight);
                    N_pass_ele_pt_jet_pt_ele30_jet35_OR_ele28_ht150_OR_ele35->Fill(electron_pt,leading_jet_pt,tot_weight);
                    N_pass_ele_pt_ht_ele30_jet35_OR_ele28_ht150_OR_ele35->Fill(electron_pt,HT,tot_weight);
                 }
             }
         }

         if(pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned != -1 || pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150 !=-1){
             if (pass_HLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned==1 || pass_HLT_Ele28_eta2p1_WPTight_Gsf_HT150==1)
                 pass_ele30_jet35_OR_ele28_ht150 = 1;
             if(pass_ele30_jet35_OR_ele28_ht150 == 1)
                N_e_ele30_jet35_OR_ele28_ht150_only += tot_weight;

             if (pass_ref==1){
                 N_e_den_ele30_jet35_OR_ele28_ht150 += tot_weight;

                 if(pass_ele30_jet35_OR_ele28_ht150 == 1){
                    N_e_ele30_jet35_OR_ele28_ht150 += tot_weight;
                    N_pass_ele_pt_ele30_jet35_OR_ele28_ht150->Fill(electron_pt,tot_weight);
                    N_pass_ele_eta_ele30_jet35_OR_ele28_ht150->Fill(electron_eta,tot_weight);
                    N_pass_ele_sceta_ele30_jet35_OR_ele28_ht150->Fill(electron_sceta,tot_weight);
                    N_pass_jet_pt_ele30_jet35_OR_ele28_ht150->Fill(leading_jet_pt,tot_weight);
                    N_pass_jet_eta_ele30_jet35_OR_ele28_ht150->Fill(leading_jet_eta,tot_weight);
                    N_pass_ht_ele30_jet35_OR_ele28_ht150->Fill(HT,tot_weight);
                    N_pass_njets_ele30_jet35_OR_ele28_ht150->Fill(njets,tot_weight);
                    N_pass_npv_ele30_jet35_OR_ele28_ht150->Fill(npv,tot_weight);
                    N_pass_ele_pt_ele_eta_ele30_jet35_OR_ele28_ht150->Fill(electron_pt,electron_eta,tot_weight);
                    N_pass_ele_pt_ele_sceta_ele30_jet35_OR_ele28_ht150->Fill(electron_pt,electron_sceta,tot_weight);
                    N_pass_ele_pt_jet_pt_ele30_jet35_OR_ele28_ht150->Fill(electron_pt,leading_jet_pt,tot_weight);
                    N_pass_ele_pt_ht_ele30_jet35_OR_ele28_ht150->Fill(electron_pt,HT,tot_weight);
                 }
             }
         }

         // Filling TEfficiency objects for correlation calculation
         teffi_ref->FillWeighted((bool)pass_ref, tot_weight, 1.5);
         teffi_e_ele27_only->FillWeighted((bool)pass_ele27, tot_weight, 1.5);
         teffi_e_ele35_only->FillWeighted((bool)pass_ele35, tot_weight, 1.5);
         teffi_e_ele30_jet35_only->FillWeighted((bool)pass_ele30_jet35, tot_weight, 1.5);
         teffi_e_ele28_ht150_only->FillWeighted((bool)pass_ele28_ht150, tot_weight, 1.5);
         teffi_e_ele30_jet35_OR_ele35_only->FillWeighted((bool)pass_ele30_jet35_OR_ele35, tot_weight, 1.5);
         teffi_e_ele28_ht150_OR_ele35_only->FillWeighted((bool)pass_ele28_ht150_OR_ele35, tot_weight, 1.5);
         teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only->FillWeighted((bool)pass_ele30_jet35_OR_ele28_ht150_OR_ele35, tot_weight, 1.5);
         teffi_e_ele30_jet35_OR_ele28_ht150_only->FillWeighted((bool)pass_ele30_jet35_OR_ele28_ht150, tot_weight, 1.5);
         teffi_e_ele27_and_ref->FillWeighted((bool)(pass_ele27*pass_ref), tot_weight, 1.5);
         teffi_e_ele35_and_ref->FillWeighted((bool)(pass_ele35*pass_ref), tot_weight, 1.5);
         teffi_e_ele30_jet35_and_ref->FillWeighted((bool)(pass_ele30_jet35*pass_ref), tot_weight, 1.5);
         teffi_e_ele28_ht150_and_ref->FillWeighted((bool)(pass_ele28_ht150*pass_ref), tot_weight, 1.5);
         teffi_e_ele30_jet35_OR_ele35_and_ref->FillWeighted((bool)(pass_ele30_jet35_OR_ele35*pass_ref), tot_weight, 1.5);
         teffi_e_ele28_ht150_OR_ele35_and_ref->FillWeighted((bool)(pass_ele28_ht150_OR_ele35*pass_ref), tot_weight, 1.5);
         teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref->FillWeighted((bool)(pass_ele30_jet35_OR_ele28_ht150_OR_ele35*pass_ref), tot_weight, 1.5);
         teffi_e_ele30_jet35_OR_ele28_ht150_and_ref->FillWeighted((bool)(pass_ele30_jet35_OR_ele28_ht150*pass_ref), tot_weight, 1.5);
    }

    // Lumi Weighting
    if (is_data_input==0)
        lumi_weight = (xs*1000*L_int)/((double) N_total);

    N_e *= lumi_weight;
    N_ref *= lumi_weight;
    N_e_ele27_only *= lumi_weight;
    N_e_ele35_only *= lumi_weight;
    N_e_ele30_jet35_only *= lumi_weight;
    N_e_ele28_ht150_only *= lumi_weight;
    N_e_ele30_jet35_OR_ele35_only *= lumi_weight;
    N_e_ele28_ht150_OR_ele35_only *= lumi_weight;
    N_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only *= lumi_weight;
    N_e_ele30_jet35_OR_ele28_ht150_only *= lumi_weight;
    N_e_ele27 *= lumi_weight;
    N_e_ele35 *= lumi_weight;
    N_e_ele30_jet35 *= lumi_weight;
    N_e_ele28_ht150 *= lumi_weight;
    N_e_ele30_jet35_OR_ele35 *= lumi_weight;
    N_e_ele28_ht150_OR_ele35 *= lumi_weight;
    N_e_ele30_jet35_OR_ele28_ht150_OR_ele35 *= lumi_weight;
    N_e_ele30_jet35_OR_ele28_ht150 *= lumi_weight;
    N_e_den_ele27 *= lumi_weight;
    N_e_den_ele35 *= lumi_weight;
    N_e_den_ele30_jet35 *= lumi_weight;
    N_e_den_ele28_ht150 *= lumi_weight;
    N_e_den_ele30_jet35_OR_ele35 *= lumi_weight;
    N_e_den_ele28_ht150_OR_ele35 *= lumi_weight;
    N_e_den_ele30_jet35_OR_ele28_ht150_OR_ele35 *= lumi_weight;
    N_e_den_ele30_jet35_OR_ele28_ht150 *= lumi_weight;

    N_total_ele_pt->Scale(lumi_weight);
    N_total_ele_eta->Scale(lumi_weight);
    N_total_ele_sceta->Scale(lumi_weight);
    N_total_jet_pt->Scale(lumi_weight);
    N_total_jet_eta->Scale(lumi_weight);
    N_total_ht->Scale(lumi_weight);
    N_total_njets->Scale(lumi_weight);
    N_total_npv->Scale(lumi_weight);
    N_total_ele_pt_ele_eta->Scale(lumi_weight);
    N_total_ele_pt_ele_sceta->Scale(lumi_weight);
    N_total_ele_pt_jet_pt->Scale(lumi_weight);
    N_total_ele_pt_ht->Scale(lumi_weight);
    N_pass_ele_pt_ele27->Scale(lumi_weight);
    N_pass_ele_eta_ele27->Scale(lumi_weight);
    N_pass_ele_sceta_ele27->Scale(lumi_weight);
    N_pass_jet_pt_ele27->Scale(lumi_weight);
    N_pass_jet_eta_ele27->Scale(lumi_weight);
    N_pass_ht_ele27->Scale(lumi_weight);
    N_pass_njets_ele27->Scale(lumi_weight);
    N_pass_npv_ele27->Scale(lumi_weight);
    N_pass_ele_pt_ele_eta_ele27->Scale(lumi_weight);
    N_pass_ele_pt_ele_sceta_ele27->Scale(lumi_weight);
    N_pass_ele_pt_jet_pt_ele27->Scale(lumi_weight);
    N_pass_ele_pt_ht_ele27->Scale(lumi_weight);
    N_pass_ele_pt_ele35->Scale(lumi_weight);
    N_pass_ele_eta_ele35->Scale(lumi_weight);
    N_pass_ele_sceta_ele35->Scale(lumi_weight);
    N_pass_jet_pt_ele35->Scale(lumi_weight);
    N_pass_jet_eta_ele35->Scale(lumi_weight);
    N_pass_ht_ele35->Scale(lumi_weight);
    N_pass_njets_ele35->Scale(lumi_weight);
    N_pass_npv_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ele_eta_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ele_sceta_ele35->Scale(lumi_weight);
    N_pass_ele_pt_jet_pt_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ht_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ele30_jet35->Scale(lumi_weight);
    N_pass_ele_eta_ele30_jet35->Scale(lumi_weight);
    N_pass_ele_sceta_ele30_jet35->Scale(lumi_weight);
    N_pass_jet_pt_ele30_jet35->Scale(lumi_weight);
    N_pass_jet_eta_ele30_jet35->Scale(lumi_weight);
    N_pass_ht_ele30_jet35->Scale(lumi_weight);
    N_pass_njets_ele30_jet35->Scale(lumi_weight);
    N_pass_npv_ele30_jet35->Scale(lumi_weight);
    N_pass_ele_pt_ele_eta_ele30_jet35->Scale(lumi_weight);
    N_pass_ele_pt_ele_sceta_ele30_jet35->Scale(lumi_weight);
    N_pass_ele_pt_jet_pt_ele30_jet35->Scale(lumi_weight);
    N_pass_ele_pt_ht_ele30_jet35->Scale(lumi_weight);
    N_pass_ele_pt_ele28_ht150->Scale(lumi_weight);
    N_pass_ele_eta_ele28_ht150->Scale(lumi_weight);
    N_pass_ele_sceta_ele28_ht150->Scale(lumi_weight);
    N_pass_jet_pt_ele28_ht150->Scale(lumi_weight);
    N_pass_jet_eta_ele28_ht150->Scale(lumi_weight);
    N_pass_ht_ele28_ht150->Scale(lumi_weight);
    N_pass_njets_ele28_ht150->Scale(lumi_weight);
    N_pass_npv_ele28_ht150->Scale(lumi_weight);
    N_pass_ele_pt_ele_eta_ele28_ht150->Scale(lumi_weight);
    N_pass_ele_pt_ele_sceta_ele28_ht150->Scale(lumi_weight);
    N_pass_ele_pt_jet_pt_ele28_ht150->Scale(lumi_weight);
    N_pass_ele_pt_ht_ele28_ht150->Scale(lumi_weight);
    N_pass_ele_pt_ele30_jet35_OR_ele35->Scale(lumi_weight);
    N_pass_ele_eta_ele30_jet35_OR_ele35->Scale(lumi_weight);
    N_pass_ele_sceta_ele30_jet35_OR_ele35->Scale(lumi_weight);
    N_pass_jet_pt_ele30_jet35_OR_ele35->Scale(lumi_weight);
    N_pass_jet_eta_ele30_jet35_OR_ele35->Scale(lumi_weight);
    N_pass_ht_ele30_jet35_OR_ele35->Scale(lumi_weight);
    N_pass_njets_ele30_jet35_OR_ele35->Scale(lumi_weight);
    N_pass_npv_ele30_jet35_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ele_eta_ele30_jet35_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ele_sceta_ele30_jet35_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_jet_pt_ele30_jet35_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ht_ele30_jet35_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ele_eta_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ele_sceta_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_jet_pt_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_jet_eta_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ht_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_njets_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_npv_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ele_eta_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ele_sceta_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_jet_pt_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ht_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ele30_jet35_OR_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ele_eta_ele30_jet35_OR_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ele_sceta_ele30_jet35_OR_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_jet_pt_ele30_jet35_OR_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_jet_eta_ele30_jet35_OR_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ht_ele30_jet35_OR_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_njets_ele30_jet35_OR_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_npv_ele30_jet35_OR_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ele_eta_ele30_jet35_OR_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ele_sceta_ele30_jet35_OR_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_jet_pt_ele30_jet35_OR_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ht_ele30_jet35_OR_ele28_ht150_OR_ele35->Scale(lumi_weight);
    N_pass_ele_pt_ele30_jet35_OR_ele28_ht150->Scale(lumi_weight);
    N_pass_ele_eta_ele30_jet35_OR_ele28_ht150->Scale(lumi_weight);
    N_pass_ele_sceta_ele30_jet35_OR_ele28_ht150->Scale(lumi_weight);
    N_pass_jet_pt_ele30_jet35_OR_ele28_ht150->Scale(lumi_weight);
    N_pass_jet_eta_ele30_jet35_OR_ele28_ht150->Scale(lumi_weight);
    N_pass_ht_ele30_jet35_OR_ele28_ht150->Scale(lumi_weight);
    N_pass_njets_ele30_jet35_OR_ele28_ht150->Scale(lumi_weight);
    N_pass_npv_ele30_jet35_OR_ele28_ht150->Scale(lumi_weight);
    N_pass_ele_pt_ele_eta_ele30_jet35_OR_ele28_ht150->Scale(lumi_weight);
    N_pass_ele_pt_ele_sceta_ele30_jet35_OR_ele28_ht150->Scale(lumi_weight);
    N_pass_ele_pt_jet_pt_ele30_jet35_OR_ele28_ht150->Scale(lumi_weight);
    N_pass_ele_pt_ht_ele30_jet35_OR_ele28_ht150->Scale(lumi_weight);

    /*
    effi_ref = N_ref / N_e;
    effi_e_ele27_only = N_e_ele27_only / N_e;
    effi_e_ele35_only = N_e_ele35_only / N_e;
    effi_e_ele30_jet35_only = N_e_ele30_jet35_only / N_e;
    effi_e_ele28_ht150_only = N_e_ele28_ht150_only / N_e;
    effi_e_ele30_jet35_OR_ele35_only = N_e_ele30_jet35_OR_ele35_only / N_e;
    effi_e_ele28_ht150_OR_ele35_only = N_e_ele28_ht150_OR_ele35_only / N_e;
    effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only = N_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only / N_e;
    effi_e_ele30_jet35_OR_ele28_ht150_only = N_e_ele30_jet35_OR_ele28_ht150_only / N_e;
    effi_e_ele27_and_ref = N_e_ele27 / N_e;
    effi_e_ele35_and_ref = N_e_ele35 / N_e;
    effi_e_ele30_jet35_and_ref = N_e_ele30_jet35 / N_e;
    effi_e_ele28_ht150_and_ref = N_e_ele28_ht150 / N_e;
    effi_e_ele30_jet35_OR_ele35_and_ref = N_e_ele30_jet35_OR_ele35 / N_e;
    effi_e_ele28_ht150_OR_ele35_and_ref = N_e_ele28_ht150_OR_ele35 / N_e;
    effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref = N_e_ele30_jet35_OR_ele28_ht150_OR_ele35 / N_e;
    effi_e_ele30_jet35_OR_ele28_ht150_and_ref = N_e_ele30_jet35_OR_ele28_ht150 / N_e;
    */
    effi_ref = teffi_ref->GetEfficiency(teffi_ref->GetGlobalBin(2));
    effi_e_ele27_only = teffi_e_ele27_only->GetEfficiency(teffi_e_ele27_only->GetGlobalBin(2));
    effi_e_ele35_only = teffi_e_ele35_only->GetEfficiency(teffi_e_ele35_only->GetGlobalBin(2));
    effi_e_ele30_jet35_only = teffi_e_ele30_jet35_only->GetEfficiency(teffi_e_ele30_jet35_only->GetGlobalBin(2));
    effi_e_ele28_ht150_only = teffi_e_ele28_ht150_only->GetEfficiency(teffi_e_ele28_ht150_only->GetGlobalBin(2));
    effi_e_ele30_jet35_OR_ele35_only = teffi_e_ele30_jet35_OR_ele35_only->GetEfficiency(teffi_e_ele30_jet35_OR_ele35_only->GetGlobalBin(2));
    effi_e_ele28_ht150_OR_ele35_only = teffi_e_ele28_ht150_OR_ele35_only->GetEfficiency(teffi_e_ele28_ht150_OR_ele35_only->GetGlobalBin(2));
    effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only = teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only->GetEfficiency(teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only->GetGlobalBin(2));
    effi_e_ele30_jet35_OR_ele28_ht150_only = teffi_e_ele30_jet35_OR_ele28_ht150_only->GetEfficiency(teffi_e_ele30_jet35_OR_ele28_ht150_only->GetGlobalBin(2));
    effi_e_ele27_and_ref = teffi_e_ele27_and_ref->GetEfficiency(teffi_e_ele27_and_ref->GetGlobalBin(2));
    effi_e_ele35_and_ref = teffi_e_ele35_and_ref->GetEfficiency(teffi_e_ele35_and_ref->GetGlobalBin(2));
    effi_e_ele30_jet35_and_ref = teffi_e_ele30_jet35_and_ref->GetEfficiency(teffi_e_ele30_jet35_and_ref->GetGlobalBin(2));
    effi_e_ele28_ht150_and_ref = teffi_e_ele28_ht150_and_ref->GetEfficiency(teffi_e_ele28_ht150_and_ref->GetGlobalBin(2));
    effi_e_ele30_jet35_OR_ele35_and_ref = teffi_e_ele30_jet35_OR_ele35_and_ref->GetEfficiency(teffi_e_ele30_jet35_OR_ele35_and_ref->GetGlobalBin(2));
    effi_e_ele28_ht150_OR_ele35_and_ref = teffi_e_ele28_ht150_OR_ele35_and_ref->GetEfficiency(teffi_e_ele28_ht150_OR_ele35_and_ref->GetGlobalBin(2));
    effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref = teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref->GetEfficiency(teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref->GetGlobalBin(2));
    effi_e_ele30_jet35_OR_ele28_ht150_and_ref = teffi_e_ele30_jet35_OR_ele28_ht150_and_ref->GetEfficiency(teffi_e_ele30_jet35_OR_ele28_ht150_and_ref->GetGlobalBin(2));

    effi_ref_err = (teffi_ref->GetEfficiencyErrorUp(teffi_ref->GetGlobalBin(2))+teffi_ref->GetEfficiencyErrorLow(teffi_ref->GetGlobalBin(2)))/2.0;
    effi_e_ele27_only_err = (teffi_e_ele27_only->GetEfficiencyErrorUp(teffi_e_ele27_only->GetGlobalBin(2))+teffi_e_ele27_only->GetEfficiencyErrorLow(teffi_e_ele27_only->GetGlobalBin(2)))/2.0;
    effi_e_ele35_only_err = (teffi_e_ele35_only->GetEfficiencyErrorUp(teffi_e_ele35_only->GetGlobalBin(2))+teffi_e_ele35_only->GetEfficiencyErrorLow(teffi_e_ele35_only->GetGlobalBin(2)))/2.0;
    effi_e_ele30_jet35_only_err = (teffi_e_ele30_jet35_only->GetEfficiencyErrorUp(teffi_e_ele30_jet35_only->GetGlobalBin(2))+teffi_e_ele30_jet35_only->GetEfficiencyErrorLow(teffi_e_ele30_jet35_only->GetGlobalBin(2)))/2.0;
    effi_e_ele28_ht150_only_err = (teffi_e_ele28_ht150_only->GetEfficiencyErrorUp(teffi_e_ele28_ht150_only->GetGlobalBin(2))+teffi_e_ele28_ht150_only->GetEfficiencyErrorLow(teffi_e_ele28_ht150_only->GetGlobalBin(2)))/2.0;
    effi_e_ele30_jet35_OR_ele35_only_err = (teffi_e_ele30_jet35_OR_ele35_only->GetEfficiencyErrorUp(teffi_e_ele30_jet35_OR_ele35_only->GetGlobalBin(2))+teffi_e_ele30_jet35_OR_ele35_only->GetEfficiencyErrorLow(teffi_e_ele30_jet35_OR_ele35_only->GetGlobalBin(2)))/2.0;
    effi_e_ele28_ht150_OR_ele35_only_err = (teffi_e_ele28_ht150_OR_ele35_only->GetEfficiencyErrorUp(teffi_e_ele28_ht150_OR_ele35_only->GetGlobalBin(2))+teffi_e_ele28_ht150_OR_ele35_only->GetEfficiencyErrorLow(teffi_e_ele28_ht150_OR_ele35_only->GetGlobalBin(2)))/2.0;
    effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only_err = (teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only->GetEfficiencyErrorUp(teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only->GetGlobalBin(2))+teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only->GetEfficiencyErrorLow(teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only->GetGlobalBin(2)))/2.0;
    effi_e_ele30_jet35_OR_ele28_ht150_only_err = (teffi_e_ele30_jet35_OR_ele28_ht150_only->GetEfficiencyErrorUp(teffi_e_ele30_jet35_OR_ele28_ht150_only->GetGlobalBin(2))+teffi_e_ele30_jet35_OR_ele28_ht150_only->GetEfficiencyErrorLow(teffi_e_ele30_jet35_OR_ele28_ht150_only->GetGlobalBin(2)))/2.0;
    effi_e_ele27_and_ref_err = (teffi_e_ele27_and_ref->GetEfficiencyErrorUp(teffi_e_ele27_and_ref->GetGlobalBin(2))+teffi_e_ele27_and_ref->GetEfficiencyErrorLow(teffi_e_ele27_and_ref->GetGlobalBin(2)))/2.0;
    effi_e_ele35_and_ref_err = (teffi_e_ele35_and_ref->GetEfficiencyErrorUp(teffi_e_ele35_and_ref->GetGlobalBin(2))+teffi_e_ele35_and_ref->GetEfficiencyErrorLow(teffi_e_ele35_and_ref->GetGlobalBin(2)))/2.0;
    effi_e_ele30_jet35_and_ref_err = (teffi_e_ele30_jet35_and_ref->GetEfficiencyErrorUp(teffi_e_ele30_jet35_and_ref->GetGlobalBin(2))+teffi_e_ele30_jet35_and_ref->GetEfficiencyErrorLow(teffi_e_ele30_jet35_and_ref->GetGlobalBin(2)))/2.0;
    effi_e_ele28_ht150_and_ref_err = (teffi_e_ele28_ht150_and_ref->GetEfficiencyErrorUp(teffi_e_ele28_ht150_and_ref->GetGlobalBin(2))+teffi_e_ele28_ht150_and_ref->GetEfficiencyErrorLow(teffi_e_ele28_ht150_and_ref->GetGlobalBin(2)))/2.0;
    effi_e_ele30_jet35_OR_ele35_and_ref_err = (teffi_e_ele30_jet35_OR_ele35_and_ref->GetEfficiencyErrorUp(teffi_e_ele30_jet35_OR_ele35_and_ref->GetGlobalBin(2))+teffi_e_ele30_jet35_OR_ele35_and_ref->GetEfficiencyErrorLow(teffi_e_ele30_jet35_OR_ele35_and_ref->GetGlobalBin(2)))/2.0;
    effi_e_ele28_ht150_OR_ele35_and_ref_err = (teffi_e_ele28_ht150_OR_ele35_and_ref->GetEfficiencyErrorUp(teffi_e_ele28_ht150_OR_ele35_and_ref->GetGlobalBin(2))+teffi_e_ele28_ht150_OR_ele35_and_ref->GetEfficiencyErrorLow(teffi_e_ele28_ht150_OR_ele35_and_ref->GetGlobalBin(2)))/2.0;
    effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref_err = (teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref->GetEfficiencyErrorUp(teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref->GetGlobalBin(2))+teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref->GetEfficiencyErrorLow(teffi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref->GetGlobalBin(2)))/2.0;
    effi_e_ele30_jet35_OR_ele28_ht150_and_ref_err = (teffi_e_ele30_jet35_OR_ele28_ht150_and_ref->GetEfficiencyErrorUp(teffi_e_ele30_jet35_OR_ele28_ht150_and_ref->GetGlobalBin(2))+teffi_e_ele30_jet35_OR_ele28_ht150_and_ref->GetEfficiencyErrorLow(teffi_e_ele30_jet35_OR_ele28_ht150_and_ref->GetGlobalBin(2)))/2.0;

    effi_e_ele27 = N_e_ele27 / N_e_den_ele27;
    effi_e_ele35 = N_e_ele35 / N_e_den_ele35;
    effi_e_ele30_jet35 = N_e_ele30_jet35 / N_e_den_ele30_jet35;
    effi_e_ele28_ht150 = N_e_ele28_ht150 / N_e_den_ele28_ht150;
    effi_e_ele30_jet35_OR_ele35 = N_e_ele30_jet35_OR_ele35 / N_e_den_ele30_jet35_OR_ele35;
    effi_e_ele28_ht150_OR_ele35 = N_e_ele28_ht150_OR_ele35 / N_e_den_ele28_ht150_OR_ele35;
    effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35 = N_e_ele30_jet35_OR_ele28_ht150_OR_ele35 / N_e_den_ele30_jet35_OR_ele28_ht150_OR_ele35;
    effi_e_ele30_jet35_OR_ele28_ht150 = N_e_ele30_jet35_OR_ele28_ht150 / N_e_den_ele30_jet35_OR_ele28_ht150;

    bias_e_ele27 = (effi_ref*effi_e_ele27_only)/effi_e_ele27_and_ref;
    bias_e_ele35 = (effi_ref*effi_e_ele35_only)/effi_e_ele35_and_ref;
    bias_e_ele30_jet35 = (effi_ref*effi_e_ele30_jet35_only)/effi_e_ele30_jet35_and_ref;
    bias_e_ele28_ht150 = (effi_ref*effi_e_ele28_ht150_only)/effi_e_ele28_ht150_and_ref;
    bias_e_ele30_jet35_OR_ele35 = (effi_ref*effi_e_ele30_jet35_OR_ele35_only)/effi_e_ele30_jet35_OR_ele35_and_ref;
    bias_e_ele28_ht150_OR_ele35 = (effi_ref*effi_e_ele28_ht150_OR_ele35_only)/effi_e_ele28_ht150_OR_ele35_and_ref;
    bias_e_ele30_jet35_OR_ele28_ht150_OR_ele35 = (effi_ref*effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only)/effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref;
    bias_e_ele30_jet35_OR_ele28_ht150 = (effi_ref*effi_e_ele30_jet35_OR_ele28_ht150_only)/effi_e_ele30_jet35_OR_ele28_ht150_and_ref;

    bias_e_ele27_err = bias_error(bias_e_ele27, effi_ref, effi_ref_err, effi_e_ele27_only, effi_e_ele27_only_err, effi_e_ele27_and_ref, effi_e_ele27_and_ref_err);
    bias_e_ele35_err = bias_error(bias_e_ele35, effi_ref, effi_ref_err, effi_e_ele35_only, effi_e_ele35_only_err, effi_e_ele35_and_ref, effi_e_ele35_and_ref_err);
    bias_e_ele30_jet35_err = bias_error(bias_e_ele30_jet35, effi_ref, effi_ref_err, effi_e_ele30_jet35_only, effi_e_ele30_jet35_only_err, effi_e_ele30_jet35_and_ref, effi_e_ele30_jet35_and_ref_err);
    bias_e_ele28_ht150_err = bias_error(bias_e_ele28_ht150, effi_ref, effi_ref_err, effi_e_ele28_ht150_only, effi_e_ele28_ht150_only_err, effi_e_ele28_ht150_and_ref, effi_e_ele28_ht150_and_ref_err);
    bias_e_ele30_jet35_OR_ele35_err = bias_error(bias_e_ele30_jet35_OR_ele35, effi_ref, effi_ref_err, effi_e_ele30_jet35_OR_ele35_only, effi_e_ele30_jet35_OR_ele35_only_err, effi_e_ele30_jet35_OR_ele35_and_ref, effi_e_ele30_jet35_OR_ele35_and_ref_err);
    bias_e_ele28_ht150_OR_ele35_err = bias_error(bias_e_ele28_ht150_OR_ele35, effi_ref, effi_ref_err, effi_e_ele28_ht150_OR_ele35_only, effi_e_ele28_ht150_OR_ele35_only_err, effi_e_ele28_ht150_OR_ele35_and_ref, effi_e_ele28_ht150_OR_ele35_and_ref_err);
    bias_e_ele30_jet35_OR_ele28_ht150_OR_ele35_err = bias_error(bias_e_ele30_jet35_OR_ele28_ht150_OR_ele35, effi_ref, effi_ref_err, effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only, effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_only_err, effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref, effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35_and_ref_err);
    bias_e_ele30_jet35_OR_ele28_ht150_err = bias_error(bias_e_ele30_jet35_OR_ele28_ht150, effi_ref, effi_ref_err, effi_e_ele30_jet35_OR_ele28_ht150_only, effi_e_ele30_jet35_OR_ele28_ht150_only_err, effi_e_ele30_jet35_OR_ele28_ht150_and_ref, effi_e_ele30_jet35_OR_ele28_ht150_and_ref_err);


    std::cout << "Reco and Gen Tree Done! " << std::endl;
    fout<<"**********************************************************************************************\n\n";
    fout<<"Total No. of Events : "<<N_total<<"\n";
    fout<<"No. of Events passing Basic Event Selection : "<<N_basic_sel<<"\n";
    fout<<"Sum of Positive Generator weights of all Events: "<<sum_pos_gen_weights<<"\n";
    fout<<"Sum of Negative Generator weights of all Events: "<<sum_neg_gen_weights<<"\n";
    fout<<"Sum of Generator weights of all Events: "<<sum_gen_weights<<"\n\n";
    fout<<"Product of Generator weights of all Events: "<<prod_gen_weights<<"\n\n";
    fout<<"Sum of Generator weights * PU weights of all Events: "<<sum_gen_PU_weights<<"\n\n";
    fout<<"Sum of SL tags : "<<N_SL_tag<<"\n";
    fout<<"Sum of DL tags : "<<N_DL_tag<<"\n";
    fout<<"Sum of FH tags : "<<N_FH_tag<<"\n\n";
    fout<<"**********************************************************************************************\n\n";
    fout<<"No. of events passing Offline event selection only : "<<N_e<<"\n";
    fout<<"Denominator for Ele27 HLT Path : "<<N_e_den_ele27<<"\n";
    fout<<"No. of events and efficiency passing Offline event selection + reference triggers + Ele27 HLT Path : "<<N_e_ele27<<" ,  efficiency = "<<effi_e_ele27<<"\n";
    fout<<"Denominator for Ele35 HLT Path : "<<N_e_den_ele35<<"\n";
    fout<<"No. of events and efficiency passing Offline event selection + reference triggers + Ele35 HLT Path : "<<N_e_ele35<<" ,  efficiency = "<<effi_e_ele35<<"\n";
    fout<<"Denominator for Ele30_Jet35 HLT Path : "<<N_e_den_ele30_jet35<<"\n";
    fout<<"No. of events and efficiency passing Offline event selection + reference triggers + Ele30_Jet35 HLT Path : "<<N_e_ele30_jet35<<" ,  efficiency = "<<effi_e_ele30_jet35<<"\n";
    fout<<"Denominator for Ele28_HT150 HLT Path : "<<N_e_den_ele28_ht150<<"\n";
    fout<<"No. of events and efficiency passing Offline event selection + reference triggers + Ele28_HT150 HLT Path : "<<N_e_ele28_ht150<<" , efficiency = "<<effi_e_ele28_ht150<<"\n";
    fout<<"Denominator for Ele30_Jet35 OR Ele35 HLT Paths : "<<N_e_den_ele30_jet35_OR_ele35<<"\n";
    fout<<"No. of events and efficiency passing Offline event selection + reference triggers + Ele30_Jet35 OR Ele35 HLT Paths : "<<N_e_ele30_jet35_OR_ele35<<" , efficiency = "<<effi_e_ele30_jet35_OR_ele35<<"\n";
    fout<<"Denominator for Ele28_HT150 OR Ele35 HLT Paths : "<<N_e_den_ele28_ht150_OR_ele35<<"\n";
    fout<<"No. of events and efficiency passing Offline event selection + reference triggers + Ele28_HT150 OR Ele35 HLT Paths : "<<N_e_ele28_ht150_OR_ele35<<" , efficiency = "<<effi_e_ele28_ht150_OR_ele35<<"\n";
    fout<<"Denominator for Ele30_Jet35 OR Ele28_HT150 OR Ele35 HLT Paths : "<<N_e_den_ele30_jet35_OR_ele28_ht150_OR_ele35<<"\n";
    fout<<"No. of events and efficiency passing Offline event selection + reference triggers + Ele30_Jet35 OR Ele28_HT150 OR Ele35 HLT Paths : "<<N_e_ele30_jet35_OR_ele28_ht150_OR_ele35<<" , efficiency = "<<effi_e_ele30_jet35_OR_ele28_ht150_OR_ele35<<"\n";
    fout<<"Denominator for Ele30_Jet35 OR Ele28_HT150 HLT Paths : "<<N_e_den_ele30_jet35_OR_ele28_ht150<<"\n";
    fout<<"No. of events and efficiency passing Offline event selection + reference triggers + Ele30_Jet35 OR Ele28_HT150 HLT Paths : "<<N_e_ele30_jet35_OR_ele28_ht150<<" , efficiency = "<<effi_e_ele30_jet35_OR_ele28_ht150<<"\n";
    fout<<"**********************************************************************************************\n\n";
    fout<<"Bias for Ele27 HLT Path : "<<bias_e_ele27<<" +/- "<<bias_e_ele27_err<<"\n";
    fout<<"Bias for Ele35 HLT Path : "<<bias_e_ele35<<" +/- "<<bias_e_ele35_err<<"\n";
    fout<<"Bias for Ele30_Jet35 HLT Path : "<<bias_e_ele30_jet35<<" +/- "<<bias_e_ele30_jet35_err<<"\n";
    fout<<"Bias for Ele28_HT150 HLT Path : "<<bias_e_ele28_ht150<<" +/- "<<bias_e_ele28_ht150_err<<"\n";
    fout<<"Bias for Ele30_Jet35 OR Ele35 HLT Paths : "<<bias_e_ele30_jet35_OR_ele35<<" +/- "<<bias_e_ele30_jet35_OR_ele35_err<<"\n";
    fout<<"Bias for Ele28_HT150 OR Ele35 HLT Paths : "<<bias_e_ele28_ht150_OR_ele35<<" +/- "<<bias_e_ele28_ht150_OR_ele35_err<<"\n";
    fout<<"Bias for Ele30_Jet35 OR Ele28_HT150 OR Ele35 HLT Paths : "<<bias_e_ele30_jet35_OR_ele28_ht150_OR_ele35<<" +/- "<<bias_e_ele30_jet35_OR_ele28_ht150_OR_ele35_err<<"\n";
    fout<<"Bias for Ele30_Jet35 OR Ele28_HT150 HLT Paths : "<<bias_e_ele30_jet35_OR_ele28_ht150<<" +/- "<<bias_e_ele30_jet35_OR_ele28_ht150_err<<"\n";
    fout<<"**********************************************************************************************\n\n";

    // Free memory
    delete reco_chain;
    delete comm_chain;

    // CLose other files
    histofile.Write();
    histofile.Close();
    fout.close();
    system("rm -rf PU_MC.txt PU_weights.txt");

    return;
}


