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
#include <string>
#include <sstream>
#include "TGraphAsymmErrors.h"
#include "TVector.h"
#include "TLorentzVector.h"

void Data_MC_Control_Plots( int maxNentries=-1, int Njobs=1, int jobN=1 ) {

	// Reading from input file

	ifstream fin;
	std::string MC_Data;
	std::string sample;
	int n_input_files;
	std::string file;
	std::vector<std::string> treefilenames;
	std::string process;
	double xs;

	fin.open("input.txt");
	fin>>MC_Data;
	fin>>sample;
	fin>>n_input_files;
	for(int i=0; i<n_input_files; i++){
		fin>>file;
		treefilenames.push_back(file);
	}
	fin>>process;
	fin>>xs;
	fin.close();

	// Setting up output files

	std::string output_filename;
	std::string output_yields_filename;
	output_filename = ("Control_plots_" + MC_Data + "_" + sample + "_" + process + ".root").c_str();
	output_yields_filename = ("out_" + MC_Data + "_" + sample + "_" + process + ".txt").c_str();
	ofstream fout;
	fout.open(output_yields_filename);

	// Initializing counters

    double N_total = 0;
	int N_sel_raw = 0;
	int N_SL_raw = 0;
	int N_DL_raw = 0;
	int N_e_raw = 0;
	int N_mu_raw = 0;
	int N_ee_raw = 0;
	int N_emu_raw = 0;
	int N_mumu_raw = 0;
    double sum_gen_weights = 0;
	double product_gen_weights = 1.0;

	// Yields from MC

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

	// Yields at L

	double L = 35.92; // 1/fb
	double lumi_norm = 0;
	double lumi_norm_genweighted = 0;

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

	std::string histofilename = output_filename;

	TChain *reco_chain = new TChain("ttHbb/recoTree");

	for(int i=0; i<n_input_files; i++)
		reco_chain->Add(treefilenames[i].c_str());

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
    TH2D* njets_ht_2D_sl_e = new TH2D("njets_ht_2D_sl_e","Jet Multiplicity and HT 2D Distribution (Single Electron) ;Nr. of jets ;HT (GeV)",15,0,15,50,0,1000);
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
	TH2D* njets_ht_2D_sl_e_genweighted = new TH2D("njets_ht_2D_sl_e_genweighted","Gen_Weighted Jet Multiplicity and HT 2D Distribution (Single Electron) ;Nr. of jets ;HT (GeV)",15,0,15,50,0,1000);
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
    TH2D* njets_ht_2D_sl_mu = new TH2D("njets_ht_2D_sl_mu","Jet Multiplicity and HT 2D Distribution (Single Muon) ;Nr. of jets ;HT (GeV)",15,0,15,50,0,1000);
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
	TH2D* njets_ht_2D_sl_mu_genweighted = new TH2D("njets_ht_2D_sl_mu_genweighted","Gen_Weighted Jet Multiplicity and HT 2D Distribution (Single Muon) ;Nr. of jets ;HT (GeV)",15,0,15,50,0,1000);
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
    TH2D* njets_ht_2D_di_ee = new TH2D("njets_ht_2D_di_ee","Jet Multiplicity and HT 2D Distribution (Double Electron) ;Nr. of jets ;HT (GeV)",15,0,15,50,0,1000);
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
	TH2D* njets_ht_2D_di_ee_genweighted = new TH2D("njets_ht_2D_di_ee_genweighted","Gen_Weighted Jet Multiplicity and HT 2D Distribution (Double Electron) ;Nr. of jets ;HT (GeV)",15,0,15,50,0,1000);
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
    TH2D* njets_ht_2D_di_emu = new TH2D("njets_ht_2D_di_emu","Jet Multiplicity and HT 2D Distribution (Electron Muon) ;Nr. of jets ;HT (GeV)",15,0,15,50,0,1000);
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
	TH2D* njets_ht_2D_di_emu_genweighted = new TH2D("njets_ht_2D_di_emu_genweighted","Gen_Weighted Jet Multiplicity and HT 2D Distribution (Electron Muon) ;Nr. of jets ;HT (GeV)",15,0,15,50,0,1000);
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
    TH2D* njets_ht_2D_di_mumu = new TH2D("njets_ht_2D_di_mumu","Jet Multiplicity and HT 2D Distribution (Double Muon) ;Nr. of jets ;HT (GeV)",15,0,15,50,0,1000);
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
	TH2D* njets_ht_2D_di_mumu_genweighted = new TH2D("njets_ht_2D_di_mumu_genweighted","Gen_Weighted Jet Multiplicity and HT 2D Distribution (Double Muon) ;Nr. of jets ;HT (GeV)",15,0,15,50,0,1000);
	TH1D* njets_di_mumu_genweighted = new TH1D("njets_di_mumu_genweighted","Gen_Weighted Jet Multiplicity (Double Muon) ;Nr. of jets; Nr. of Events",15,0,15);
	TH1D* nbtags_di_mumu_genweighted = new TH1D("nbtags_di_mumu_genweighted","Gen_Weighted B-jet Multiplicity (Double Muon) ;Nr. of b-jets; Nr. of Events",8,0,8);
	TH1D* npv_di_mumu_genweighted = new TH1D("npv_di_mumu_genweighted","Gen_Weighted Nr. of Primary Vertices (Double Muon)  ;NPV; Nr. of Events",20,0,75);


	int nentries = reco_chain->GetEntries();
	int NeventsPerJob = int( double(nentries)/double(Njobs) + 0.000001 ) + 1;

  	int firstEvent = (jobN-1)*NeventsPerJob + 1;
  	int lastEvent  = firstEvent + NeventsPerJob;
 	if( jobN==Njobs ) lastEvent = -1;
  	if( jobN==1 ) firstEvent = 0;

	// Assigning variables for each branch from Tree in ntuple

	int nEvent, is_data;
	int pass_event_selection;
	int n_lep, n_ele, n_mu;
	int n_jets, n_btags;

    int npv;
    int ttHf_cat;
    int ttHFGenFilter;

    std::vector<double> * mu_pt = 0;
    std::vector<double> * mu_eta = 0;
    std::vector<double> * mu_phi = 0;
    std::vector<double> * mu_E = 0;
    std::vector<int> * mu_charge = 0;
    std::vector<double> * mu_iso = 0;

    std::vector<double> * ele_pt = 0;
    std::vector<double> * ele_eta = 0;
    std::vector<double> * ele_phi = 0;
    std::vector<double> * ele_E = 0;
    std::vector<int> * ele_charge = 0;
    std::vector<double> * ele_iso = 0;

    std::vector<double> * jet_pt = 0;
    std::vector<double> * jet_eta = 0;
    std::vector<double> * jet_phi = 0;
    std::vector<double> * jet_E = 0;
    std::vector<double> * jet_CSV = 0;

    std::vector<double> * bjet_pt = 0;
    std::vector<double> * bjet_eta = 0;
    std::vector<double> * bjet_phi = 0;
    std::vector<double> * bjet_E = 0;
    std::vector<double> * bjet_CSV = 0;

    double PFMETpt;
    double PFMETphi;
    double mll;
    double ht;

    std::vector<double> * lep_sf_id = 0;
    std::vector<double> * lep_sf_iso = 0;
	std::vector<double> * lep_sf_tracking = 0;
    double lep_sf_trig;

    double b_weight;
    double gen_weight;
    double PU_weight;
    double pdf_weight_up;
    double pdf_weight_down;
    double q2_weight_up;
    double q2_weight_down;
	double qcd_sf;
	double qcd_sf_up;
	double qcd_sf_down;

    reco_chain->SetBranchAddress("nEvent", &nEvent );
	reco_chain->SetBranchAddress("is_data", &is_data );
	reco_chain->SetBranchAddress("pass_event_selection", &pass_event_selection );
    reco_chain->SetBranchAddress("n_lep", &n_lep );
    reco_chain->SetBranchAddress("n_ele", &n_ele );
    reco_chain->SetBranchAddress("n_mu", &n_mu );
    reco_chain->SetBranchAddress("npv", &npv );
    reco_chain->SetBranchAddress("ttHf_cat", &ttHf_cat );
    reco_chain->SetBranchAddress("ttHFGenFilter", &ttHFGenFilter );
    reco_chain->SetBranchAddress("ele_pt", &ele_pt );
    reco_chain->SetBranchAddress("ele_eta", &ele_eta );
    reco_chain->SetBranchAddress("ele_phi", &ele_phi );
    reco_chain->SetBranchAddress("ele_charge", &ele_charge );
    reco_chain->SetBranchAddress("ele_iso", &ele_iso );
    reco_chain->SetBranchAddress("mu_pt", &mu_pt );
    reco_chain->SetBranchAddress("mu_eta", &mu_eta );
    reco_chain->SetBranchAddress("mu_phi", &mu_phi );
    reco_chain->SetBranchAddress("mu_charge", &mu_charge );
    reco_chain->SetBranchAddress("mu_iso", &mu_iso );
    reco_chain->SetBranchAddress("jet_pt", &jet_pt );
    reco_chain->SetBranchAddress("jet_eta", &jet_eta );
    reco_chain->SetBranchAddress("jet_phi", &jet_phi );
    reco_chain->SetBranchAddress("jet_CSV", &jet_CSV );
    reco_chain->SetBranchAddress("n_jets", &n_jets );
    reco_chain->SetBranchAddress("n_btags", &n_btags );
    reco_chain->SetBranchAddress("PFMETpt", &PFMETpt );
    reco_chain->SetBranchAddress("PFMETphi", &PFMETphi );
    reco_chain->SetBranchAddress("mll", &mll );
    reco_chain->SetBranchAddress("ht", &ht );
    reco_chain->SetBranchAddress("lep_sf_id", &lep_sf_id );
    reco_chain->SetBranchAddress("lep_sf_iso", &lep_sf_iso );
	reco_chain->SetBranchAddress("lep_sf_tracking", &lep_sf_tracking );
    reco_chain->SetBranchAddress("lep_sf_trig", &lep_sf_trig );
    reco_chain->SetBranchAddress("b_weight", &b_weight );
    reco_chain->SetBranchAddress("gen_weight", &gen_weight );
    reco_chain->SetBranchAddress("PU_weight", &PU_weight );
    reco_chain->SetBranchAddress("pdf_weight_up", &pdf_weight_up );
    reco_chain->SetBranchAddress("pdf_weight_down", &pdf_weight_down );
    reco_chain->SetBranchAddress("q2_weight_up", &q2_weight_up );
    reco_chain->SetBranchAddress("q2_weight_down", &q2_weight_down );
	reco_chain->SetBranchAddress("qcd_sf", &qcd_sf );
	reco_chain->SetBranchAddress("qcd_sf_up", &qcd_sf_up );
	reco_chain->SetBranchAddress("qcd_sf_down", &qcd_sf_down );


	std::cout << "========  Starting Event Loop  ========" << std::endl;
 	for (Long64_t ievt=0; ievt<reco_chain->GetEntries();ievt++) {

	    if( ievt<firstEvent ) continue;
	    if( ievt==lastEvent ) break;

      	if( ievt==0 )        std::cout << "     Event " << ievt+1 << std::endl;
      	if( ievt%10000==0 && ievt!=1) std::cout << "           " << ievt << "\t" 
  					     << int(double(ievt-1)/double(nentries)*100) << "% done" << std::endl;
	  
	 	if( ievt==(maxNentries+1) && ievt!=0 ) break;
		
		reco_chain->GetEntry(ievt);

		N_total++;
		sum_gen_weights += gen_weight;
		product_gen_weights *= gen_weight;

		// Event weight and SFs
		double tot_weight = 1;
		double tot_weight_gen = 1;
		if ( is_data != 1  && pass_event_selection == 1){
			double sf = (*lep_sf_id)[0] * (*lep_sf_id)[1] * (*lep_sf_iso)[0] * (*lep_sf_iso)[1] * (*lep_sf_tracking)[0] * (*lep_sf_tracking)[1];
			tot_weight = sf * lep_sf_trig * PU_weight * b_weight;
			tot_weight_gen = sf * lep_sf_trig * PU_weight * b_weight * gen_weight;
		}

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


        // Single Lepton events
		if (n_lep == 1) {

			++N_sel_raw;
			++N_SL_raw;
			N_SL += tot_weight;
			N_SL_genweighted += tot_weight_gen;

			// Yields by jet-tag categories

			if ( n_jets==4 && n_btags==3 ){
				N_SL_4j3b += tot_weight;
				N_SL_4j3b_genweighted += tot_weight_gen;
			}
			else if ( n_jets==4 && n_btags==4 ){
				N_SL_4j4b += tot_weight;
				N_SL_4j4b_genweighted += tot_weight_gen;
			}
			else if ( n_jets==5 && n_btags==3 ){
				N_SL_5j3b += tot_weight;
				N_SL_5j3b_genweighted += tot_weight_gen;
			}
			else if ( n_jets==5 && n_btags>=4 ){
				N_SL_5j4b += tot_weight;
				N_SL_5j4b_genweighted += tot_weight_gen;
			}
			else if ( n_jets>=6 && n_btags==2 ){
				N_SL_6j2b += tot_weight;
				N_SL_6j2b_genweighted += tot_weight_gen;
			}
			else if ( n_jets>=6 && n_btags==3 ){
				N_SL_6j3b += tot_weight;
				N_SL_6j3b_genweighted += tot_weight_gen;
			}
			else if ( n_jets>=6 && n_btags>=4 ){
				N_SL_6j4b += tot_weight;
				N_SL_6j4b_genweighted += tot_weight_gen;
			}

			if (n_ele == 1) {			// Single Electron events

				// Updating counters

				++N_e_raw;
				N_e += tot_weight;
				N_e_genweighted += tot_weight_gen;

				// Filling Histograms

				pt_e1_sl_e->Fill((*ele_pt)[0], tot_weight);
				eta_e1_sl_e->Fill((*ele_eta)[0], tot_weight);
                phi_e1_sl_e->Fill((*ele_phi)[0], tot_weight);
                pt_jet1_sl_e->Fill((*jet_pt)[0], tot_weight);
                pt_jet2_sl_e->Fill((*jet_pt)[1], tot_weight);
                pt_jet3_sl_e->Fill((*jet_pt)[2], tot_weight);
                pt_jet4_sl_e->Fill((*jet_pt)[3], tot_weight);
                pt_jet5_sl_e->Fill((*jet_pt)[4], tot_weight);
                pt_jet6_sl_e->Fill((*jet_pt)[5], tot_weight);
                for(int i=0; i<n_jets; i++){
                    pt_jet_all_sl_e->Fill((*jet_pt)[i], tot_weight);
                    csv_jet_all_sl_e->Fill((*jet_CSV)[i], tot_weight);
                }
                ht_sl_e->Fill(ht, tot_weight);
                njets_ht_2D_sl_e->Fill(n_jets, ht, tot_weight);
                njets_sl_e->Fill(n_jets, tot_weight);
                nbtags_sl_e->Fill(n_btags, tot_weight);
                npv_sl_e->Fill(npv, tot_weight);

				pt_e1_sl_e_genweighted->Fill((*ele_pt)[0], tot_weight_gen);
				eta_e1_sl_e_genweighted->Fill((*ele_eta)[0], tot_weight_gen);
				phi_e1_sl_e_genweighted->Fill((*ele_phi)[0], tot_weight_gen);
				pt_jet1_sl_e_genweighted->Fill((*jet_pt)[0], tot_weight_gen);
				pt_jet2_sl_e_genweighted->Fill((*jet_pt)[1], tot_weight_gen);
				pt_jet3_sl_e_genweighted->Fill((*jet_pt)[2], tot_weight_gen);
				pt_jet4_sl_e_genweighted->Fill((*jet_pt)[3], tot_weight_gen);
				pt_jet5_sl_e_genweighted->Fill((*jet_pt)[4], tot_weight_gen);
				pt_jet6_sl_e_genweighted->Fill((*jet_pt)[5], tot_weight_gen);
				for(int i=0; i<n_jets; i++){
					pt_jet_all_sl_e_genweighted->Fill((*jet_pt)[i], tot_weight_gen);
					csv_jet_all_sl_e_genweighted->Fill((*jet_CSV)[i], tot_weight_gen);
				}
				ht_sl_e_genweighted->Fill(ht, tot_weight_gen);
				njets_ht_2D_sl_e_genweighted->Fill(n_jets, ht, tot_weight_gen);
				njets_sl_e_genweighted->Fill(n_jets, tot_weight_gen);
				nbtags_sl_e_genweighted->Fill(n_btags, tot_weight_gen);
				npv_sl_e_genweighted->Fill(npv, tot_weight_gen);
			}
			else if (n_mu == 1) {				// Single Muon events

				// Updating counters

				++N_mu_raw;
				N_mu += tot_weight;
				N_mu_genweighted += tot_weight_gen;

				// Filling Histograms

                pt_mu1_sl_mu->Fill((*mu_pt)[0], tot_weight);
                eta_mu1_sl_mu->Fill((*mu_eta)[0], tot_weight);
                phi_mu1_sl_mu->Fill((*mu_phi)[0], tot_weight);
                pt_jet1_sl_mu->Fill((*jet_pt)[0], tot_weight);
                pt_jet2_sl_mu->Fill((*jet_pt)[1], tot_weight);
                pt_jet3_sl_mu->Fill((*jet_pt)[2], tot_weight);
                pt_jet4_sl_mu->Fill((*jet_pt)[3], tot_weight);
                pt_jet5_sl_mu->Fill((*jet_pt)[4], tot_weight);
                pt_jet6_sl_mu->Fill((*jet_pt)[5], tot_weight);
                for(int i=0; i<n_jets; i++){
                    pt_jet_all_sl_mu->Fill((*jet_pt)[i], tot_weight);
                    csv_jet_all_sl_mu->Fill((*jet_CSV)[i], tot_weight);
                }
                ht_sl_mu->Fill(ht, tot_weight);
                njets_ht_2D_sl_mu->Fill(n_jets, ht, tot_weight);
                njets_sl_mu->Fill(n_jets, tot_weight);
                nbtags_sl_mu->Fill(n_btags, tot_weight);
                npv_sl_mu->Fill(npv, tot_weight);

				pt_mu1_sl_mu_genweighted->Fill((*mu_pt)[0], tot_weight_gen);
				eta_mu1_sl_mu_genweighted->Fill((*mu_eta)[0], tot_weight_gen);
				phi_mu1_sl_mu_genweighted->Fill((*mu_phi)[0], tot_weight_gen);
				pt_jet1_sl_mu_genweighted->Fill((*jet_pt)[0], tot_weight_gen);
				pt_jet2_sl_mu_genweighted->Fill((*jet_pt)[1], tot_weight_gen);
				pt_jet3_sl_mu_genweighted->Fill((*jet_pt)[2], tot_weight_gen);
				pt_jet4_sl_mu_genweighted->Fill((*jet_pt)[3], tot_weight_gen);
				pt_jet5_sl_mu_genweighted->Fill((*jet_pt)[4], tot_weight_gen);
				pt_jet6_sl_mu_genweighted->Fill((*jet_pt)[5], tot_weight_gen);
				for(int i=0; i<n_jets; i++){
					pt_jet_all_sl_mu_genweighted->Fill((*jet_pt)[i], tot_weight_gen);
					csv_jet_all_sl_mu_genweighted->Fill((*jet_CSV)[i], tot_weight_gen);
				}
				ht_sl_mu_genweighted->Fill(ht, tot_weight_gen);
				njets_ht_2D_sl_mu_genweighted->Fill(n_jets, ht, tot_weight_gen);
				njets_sl_mu_genweighted->Fill(n_jets, tot_weight_gen);
				nbtags_sl_mu_genweighted->Fill(n_btags, tot_weight_gen);
			}
		}

        // Dilepton events
        else if (n_lep == 2) {

			++N_sel_raw;
            ++N_DL_raw;
			N_DL += tot_weight;
			N_DL_genweighted += tot_weight_gen;

			// Yields by jet-tag categories

			if ( n_jets==3 && n_btags==2 ){
				N_DL_3j2b += tot_weight;
				N_DL_3j2b_genweighted += tot_weight_gen;
			}
			else if ( n_jets==3 && n_btags==3 ){
				N_DL_3j3b += tot_weight;
				N_DL_3j3b_genweighted += tot_weight_gen;
			}
			else if ( n_jets>=4 && n_btags==2 ){
				N_DL_4j2b += tot_weight;
				N_DL_4j2b_genweighted += tot_weight_gen;
			}
			else if ( n_jets>=4 && n_btags==3 ){
				N_DL_4j3b += tot_weight;
				N_DL_4j3b_genweighted += tot_weight_gen;
			}
			else if ( n_jets>=4 && n_btags>=4 ){
				N_DL_4j4b += tot_weight;
				N_DL_4j4b_genweighted += tot_weight_gen;
			}

            if (n_ele == 2) {				// Di-Electron events

				// Updating counters

				++N_ee_raw;
				N_ee += tot_weight;
				N_ee_genweighted += tot_weight_gen;

				// Filling Histograms

                pt_e1_di_ee->Fill((*ele_pt)[0], tot_weight);
                eta_e1_di_ee->Fill((*ele_eta)[0], tot_weight);
                phi_e1_di_ee->Fill((*ele_phi)[0], tot_weight);
                pt_e2_di_ee->Fill((*ele_pt)[1], tot_weight);
                eta_e2_di_ee->Fill((*ele_eta)[1], tot_weight);
                phi_e2_di_ee->Fill((*ele_phi)[1], tot_weight);
                pt_jet1_di_ee->Fill((*jet_pt)[0], tot_weight);
                pt_jet2_di_ee->Fill((*jet_pt)[1], tot_weight);
                pt_jet3_di_ee->Fill((*jet_pt)[2], tot_weight);
                pt_jet4_di_ee->Fill((*jet_pt)[3], tot_weight);
                pt_jet5_di_ee->Fill((*jet_pt)[4], tot_weight);
                pt_jet6_di_ee->Fill((*jet_pt)[5], tot_weight);
                for(int i=0; i<n_jets; i++){
                    pt_jet_all_di_ee->Fill((*jet_pt)[i], tot_weight);
                    csv_jet_all_di_ee->Fill((*jet_CSV)[i], tot_weight);
                }
                ht_di_ee->Fill(ht, tot_weight);
                njets_ht_2D_di_ee->Fill(n_jets, ht, tot_weight);
                njets_di_ee->Fill(n_jets, tot_weight);
                nbtags_di_ee->Fill(n_btags, tot_weight);
                npv_di_ee->Fill(npv, tot_weight);

				pt_e1_di_ee_genweighted->Fill((*ele_pt)[0], tot_weight_gen);
				eta_e1_di_ee_genweighted->Fill((*ele_eta)[0], tot_weight_gen);
				phi_e1_di_ee_genweighted->Fill((*ele_phi)[0], tot_weight_gen);
				pt_e2_di_ee_genweighted->Fill((*ele_pt)[1], tot_weight_gen);
				eta_e2_di_ee_genweighted->Fill((*ele_eta)[1], tot_weight_gen);
				phi_e2_di_ee_genweighted->Fill((*ele_phi)[1], tot_weight_gen);
				pt_jet1_di_ee_genweighted->Fill((*jet_pt)[0], tot_weight_gen);
				pt_jet2_di_ee_genweighted->Fill((*jet_pt)[1], tot_weight_gen);
				pt_jet3_di_ee_genweighted->Fill((*jet_pt)[2], tot_weight_gen);
				pt_jet4_di_ee_genweighted->Fill((*jet_pt)[3], tot_weight_gen);
				pt_jet5_di_ee_genweighted->Fill((*jet_pt)[4], tot_weight_gen);
				pt_jet6_di_ee_genweighted->Fill((*jet_pt)[5], tot_weight_gen);
				for(int i=0; i<n_jets; i++){
					pt_jet_all_di_ee_genweighted->Fill((*jet_pt)[i], tot_weight_gen);
					csv_jet_all_di_ee_genweighted->Fill((*jet_CSV)[i], tot_weight_gen);
				}
				ht_di_ee_genweighted->Fill(ht, tot_weight_gen);
				njets_ht_2D_di_ee_genweighted->Fill(n_jets, ht, tot_weight_gen);
				njets_di_ee_genweighted->Fill(n_jets, tot_weight_gen);
				nbtags_di_ee_genweighted->Fill(n_btags, tot_weight_gen);
				npv_di_ee_genweighted->Fill(npv, tot_weight_gen);
            }
            else if (n_mu == 2){			// Di-Muon events

				// Updating counters

				++N_mumu_raw;
				N_mumu += tot_weight;
				N_mumu_genweighted += tot_weight_gen;

				// Filling Histograms

                pt_mu1_di_mumu->Fill((*mu_pt)[0], tot_weight);
                eta_mu1_di_mumu->Fill((*mu_eta)[0], tot_weight);
                phi_mu1_di_mumu->Fill((*mu_phi)[0], tot_weight);
                pt_mu2_di_mumu->Fill((*mu_pt)[1], tot_weight);
                eta_mu2_di_mumu->Fill((*mu_eta)[1], tot_weight);
                phi_mu2_di_mumu->Fill((*mu_phi)[1], tot_weight);
                pt_jet1_di_mumu->Fill((*jet_pt)[0], tot_weight);
                pt_jet2_di_mumu->Fill((*jet_pt)[1], tot_weight);
                pt_jet3_di_mumu->Fill((*jet_pt)[2], tot_weight);
                pt_jet4_di_mumu->Fill((*jet_pt)[3], tot_weight);
                pt_jet5_di_mumu->Fill((*jet_pt)[4], tot_weight);
                pt_jet6_di_mumu->Fill((*jet_pt)[5], tot_weight);
                for(int i=0; i<n_jets; i++){
                    pt_jet_all_di_mumu->Fill((*jet_pt)[i], tot_weight);
                    csv_jet_all_di_mumu->Fill((*jet_CSV)[i], tot_weight);
                }
                ht_di_mumu->Fill(ht, tot_weight);
                njets_ht_2D_di_mumu->Fill(n_jets, ht, tot_weight);
                njets_di_mumu->Fill(n_jets, tot_weight);
                nbtags_di_mumu->Fill(n_btags, tot_weight);
                npv_di_mumu->Fill(npv, tot_weight);

				pt_mu1_di_mumu_genweighted->Fill((*mu_pt)[0], tot_weight_gen);
				eta_mu1_di_mumu_genweighted->Fill((*mu_eta)[0], tot_weight_gen);
				phi_mu1_di_mumu_genweighted->Fill((*mu_phi)[0], tot_weight_gen);
				pt_mu2_di_mumu_genweighted->Fill((*mu_pt)[1], tot_weight_gen);
				eta_mu2_di_mumu_genweighted->Fill((*mu_eta)[1], tot_weight_gen);
				phi_mu2_di_mumu_genweighted->Fill((*mu_phi)[1], tot_weight_gen);
				pt_jet1_di_mumu_genweighted->Fill((*jet_pt)[0], tot_weight_gen);
				pt_jet2_di_mumu_genweighted->Fill((*jet_pt)[1], tot_weight_gen);
				pt_jet3_di_mumu_genweighted->Fill((*jet_pt)[2], tot_weight_gen);
				pt_jet4_di_mumu_genweighted->Fill((*jet_pt)[3], tot_weight_gen);
				pt_jet5_di_mumu_genweighted->Fill((*jet_pt)[4], tot_weight_gen);
				pt_jet6_di_mumu_genweighted->Fill((*jet_pt)[5], tot_weight_gen);
				for(int i=0; i<n_jets; i++){
					pt_jet_all_di_mumu_genweighted->Fill((*jet_pt)[i], tot_weight_gen);
					csv_jet_all_di_mumu_genweighted->Fill((*jet_CSV)[i], tot_weight_gen);
				}
				ht_di_mumu_genweighted->Fill(ht, tot_weight_gen);
				njets_ht_2D_di_mumu_genweighted->Fill(n_jets, ht, tot_weight_gen);
				njets_di_mumu_genweighted->Fill(n_jets, tot_weight_gen);
				nbtags_di_mumu_genweighted->Fill(n_btags, tot_weight_gen);
				npv_di_mumu_genweighted->Fill(npv, tot_weight_gen);
            }
            else {						// Electron-Muon events

				// Updating counters

				++N_emu_raw;
				N_emu += tot_weight;
				N_emu_genweighted += tot_weight_gen;

				// Filling Histograms

                pt_e1_di_emu->Fill((*ele_pt)[0], tot_weight);
                eta_e1_di_emu->Fill((*ele_eta)[0], tot_weight);
                phi_e1_di_emu->Fill((*ele_phi)[0], tot_weight);
                pt_mu1_di_emu->Fill((*mu_pt)[0], tot_weight);
                eta_mu1_di_emu->Fill((*mu_eta)[0], tot_weight);
                phi_mu1_di_emu->Fill((*mu_phi)[0], tot_weight);
                pt_jet1_di_emu->Fill((*jet_pt)[0], tot_weight);
                pt_jet2_di_emu->Fill((*jet_pt)[1], tot_weight);
                pt_jet3_di_emu->Fill((*jet_pt)[2], tot_weight);
                pt_jet4_di_emu->Fill((*jet_pt)[3], tot_weight);
                pt_jet5_di_emu->Fill((*jet_pt)[4], tot_weight);
                pt_jet6_di_emu->Fill((*jet_pt)[5], tot_weight);
                for(int i=0; i<n_jets; i++){
                    pt_jet_all_di_emu->Fill((*jet_pt)[i], tot_weight);
                    csv_jet_all_di_emu->Fill((*jet_CSV)[i], tot_weight);
                }
                ht_di_emu->Fill(ht, tot_weight);
                njets_ht_2D_di_emu->Fill(n_jets, ht, tot_weight);
                njets_di_emu->Fill(n_jets, tot_weight);
                nbtags_di_emu->Fill(n_btags, tot_weight);
                npv_di_emu->Fill(npv, tot_weight);

				pt_e1_di_emu_genweighted->Fill((*ele_pt)[0], tot_weight_gen);
				eta_e1_di_emu_genweighted->Fill((*ele_eta)[0], tot_weight_gen);
				phi_e1_di_emu_genweighted->Fill((*ele_phi)[0], tot_weight_gen);
				pt_mu1_di_emu_genweighted->Fill((*mu_pt)[0], tot_weight_gen);
				eta_mu1_di_emu_genweighted->Fill((*mu_eta)[0], tot_weight_gen);
				phi_mu1_di_emu_genweighted->Fill((*mu_phi)[0], tot_weight_gen);
				pt_jet1_di_emu_genweighted->Fill((*jet_pt)[0], tot_weight_gen);
				pt_jet2_di_emu_genweighted->Fill((*jet_pt)[1], tot_weight_gen);
				pt_jet3_di_emu_genweighted->Fill((*jet_pt)[2], tot_weight_gen);
				pt_jet4_di_emu_genweighted->Fill((*jet_pt)[3], tot_weight_gen);
				pt_jet5_di_emu_genweighted->Fill((*jet_pt)[4], tot_weight_gen);
				pt_jet6_di_emu_genweighted->Fill((*jet_pt)[5], tot_weight_gen);
				for(int i=0; i<n_jets; i++){
					pt_jet_all_di_emu_genweighted->Fill((*jet_pt)[i], tot_weight_gen);
					csv_jet_all_di_emu_genweighted->Fill((*jet_CSV)[i], tot_weight_gen);
				}
				ht_di_emu_genweighted->Fill(ht, tot_weight_gen);
				njets_ht_2D_di_emu_genweighted->Fill(n_jets, ht, tot_weight_gen);
				njets_di_emu_genweighted->Fill(n_jets, tot_weight_gen);
				nbtags_di_emu_genweighted->Fill(n_btags, tot_weight_gen);
				npv_di_emu_genweighted->Fill(npv, tot_weight_gen);
            }
        }
	}

	// Calculating the Normalization Factor

	if(is_data){
		lumi_norm = 1.0;
		lumi_norm_genweighted = 1.0;
	}
	else{
		lumi_norm = (L*xs*1000)/((double) N_total);
		lumi_norm_genweighted = (L*xs*1000)/(sum_gen_weights);
	}

	// Calculating the yields at L = 35.92 1/fb

	N_SL_norm = (N_SL*lumi_norm);
	N_DL_norm = (N_DL*lumi_norm);
	N_e_norm = (N_e*lumi_norm);
	N_mu_norm = (N_mu*lumi_norm);
	N_ee_norm = (N_ee*lumi_norm);
	N_emu_norm = (N_emu*lumi_norm);
	N_mumu_norm = (N_mumu*lumi_norm);
	N_SL_4j3b_norm = (N_SL_4j3b*lumi_norm);
	N_SL_4j4b_norm = (N_SL_4j4b*lumi_norm);
	N_SL_5j3b_norm = (N_SL_5j3b*lumi_norm);
	N_SL_5j4b_norm = (N_SL_5j4b*lumi_norm);
	N_SL_6j2b_norm = (N_SL_6j2b*lumi_norm);
	N_SL_6j3b_norm = (N_SL_6j3b*lumi_norm);
	N_SL_6j4b_norm = (N_SL_6j4b*lumi_norm);
	N_DL_3j2b_norm = (N_DL_3j2b*lumi_norm);
	N_DL_3j3b_norm = (N_DL_3j3b*lumi_norm);
	N_DL_4j2b_norm = (N_DL_4j2b*lumi_norm);
	N_DL_4j3b_norm = (N_DL_4j3b*lumi_norm);
	N_DL_4j4b_norm = (N_DL_4j4b*lumi_norm);

	N_SL_genweighted_norm = (N_SL_genweighted*lumi_norm_genweighted);
	N_DL_genweighted_norm = (N_DL_genweighted*lumi_norm_genweighted);
	N_e_genweighted_norm = (N_e_genweighted*lumi_norm_genweighted);
	N_mu_genweighted_norm = (N_mu_genweighted*lumi_norm_genweighted);
	N_ee_genweighted_norm = (N_ee_genweighted*lumi_norm_genweighted);
	N_emu_genweighted_norm = (N_emu_genweighted*lumi_norm_genweighted);
	N_mumu_genweighted_norm = (N_mumu_genweighted*lumi_norm_genweighted);
	N_SL_4j3b_genweighted_norm = (N_SL_4j3b_genweighted*lumi_norm_genweighted);
	N_SL_4j4b_genweighted_norm = (N_SL_4j4b_genweighted*lumi_norm_genweighted);
	N_SL_5j3b_genweighted_norm = (N_SL_5j3b_genweighted*lumi_norm_genweighted);
	N_SL_5j4b_genweighted_norm = (N_SL_5j4b_genweighted*lumi_norm_genweighted);
	N_SL_6j2b_genweighted_norm = (N_SL_6j2b_genweighted*lumi_norm_genweighted);
	N_SL_6j3b_genweighted_norm = (N_SL_6j3b_genweighted*lumi_norm_genweighted);
	N_SL_6j4b_genweighted_norm = (N_SL_6j4b_genweighted*lumi_norm_genweighted);
	N_DL_3j2b_genweighted_norm = (N_DL_3j2b_genweighted*lumi_norm_genweighted);
	N_DL_3j3b_genweighted_norm = (N_DL_3j3b_genweighted*lumi_norm_genweighted);
	N_DL_4j2b_genweighted_norm = (N_DL_4j2b_genweighted*lumi_norm_genweighted);
	N_DL_4j3b_genweighted_norm = (N_DL_4j3b_genweighted*lumi_norm_genweighted);
	N_DL_4j4b_genweighted_norm = (N_DL_4j4b_genweighted*lumi_norm_genweighted);

	// Scaling Histograms according to L = 35.92 1/fb

	pt_e1_sl_e->Scale(lumi_norm);
	eta_e1_sl_e->Scale(lumi_norm);
	phi_e1_sl_e->Scale(lumi_norm);
	pt_jet1_sl_e->Scale(lumi_norm);
	pt_jet2_sl_e->Scale(lumi_norm);
	pt_jet3_sl_e->Scale(lumi_norm);
	pt_jet4_sl_e->Scale(lumi_norm);
	pt_jet5_sl_e->Scale(lumi_norm);
	pt_jet6_sl_e->Scale(lumi_norm);
	pt_jet_all_sl_e->Scale(lumi_norm);
	csv_jet_all_sl_e->Scale(lumi_norm);
	ht_sl_e->Scale(lumi_norm);
	njets_ht_2D_sl_e->Scale(lumi_norm);
	njets_sl_e->Scale(lumi_norm);
	nbtags_sl_e->Scale(lumi_norm);
	npv_sl_e->Scale(lumi_norm);
	pt_mu1_sl_mu->Scale(lumi_norm);
	eta_mu1_sl_mu->Scale(lumi_norm);
	phi_mu1_sl_mu->Scale(lumi_norm);
	pt_jet1_sl_mu->Scale(lumi_norm);
	pt_jet2_sl_mu->Scale(lumi_norm);
	pt_jet3_sl_mu->Scale(lumi_norm);
	pt_jet4_sl_mu->Scale(lumi_norm);
	pt_jet5_sl_mu->Scale(lumi_norm);
	pt_jet6_sl_mu->Scale(lumi_norm);
	pt_jet_all_sl_mu->Scale(lumi_norm);
	csv_jet_all_sl_mu->Scale(lumi_norm);
	ht_sl_mu->Scale(lumi_norm);
	njets_ht_2D_sl_mu->Scale(lumi_norm);
	njets_sl_mu->Scale(lumi_norm);
	nbtags_sl_mu->Scale(lumi_norm);
	npv_sl_mu->Scale(lumi_norm);
	pt_e1_di_ee->Scale(lumi_norm);
	eta_e1_di_ee->Scale(lumi_norm);
	phi_e1_di_ee->Scale(lumi_norm);
	pt_e2_di_ee->Scale(lumi_norm);
	eta_e2_di_ee->Scale(lumi_norm);
	phi_e2_di_ee->Scale(lumi_norm);
	pt_jet1_di_ee->Scale(lumi_norm);
	pt_jet2_di_ee->Scale(lumi_norm);
	pt_jet3_di_ee->Scale(lumi_norm);
	pt_jet4_di_ee->Scale(lumi_norm);
	pt_jet5_di_ee->Scale(lumi_norm);
	pt_jet6_di_ee->Scale(lumi_norm);
	pt_jet_all_di_ee->Scale(lumi_norm);
	csv_jet_all_di_ee->Scale(lumi_norm);
	ht_di_ee->Scale(lumi_norm);
	njets_ht_2D_di_ee->Scale(lumi_norm);
	njets_di_ee->Scale(lumi_norm);
	nbtags_di_ee->Scale(lumi_norm);
	npv_di_ee->Scale(lumi_norm);
	pt_e1_di_emu->Scale(lumi_norm);
	eta_e1_di_emu->Scale(lumi_norm);
	phi_e1_di_emu->Scale(lumi_norm);
	pt_mu1_di_emu->Scale(lumi_norm);
	eta_mu1_di_emu->Scale(lumi_norm);
	phi_mu1_di_emu->Scale(lumi_norm);
	pt_jet1_di_emu->Scale(lumi_norm);
	pt_jet2_di_emu->Scale(lumi_norm);
	pt_jet3_di_emu->Scale(lumi_norm);
	pt_jet4_di_emu->Scale(lumi_norm);
	pt_jet5_di_emu->Scale(lumi_norm);
	pt_jet6_di_emu->Scale(lumi_norm);
	pt_jet_all_di_emu->Scale(lumi_norm);
	csv_jet_all_di_emu->Scale(lumi_norm);
	ht_di_emu->Scale(lumi_norm);
	njets_ht_2D_di_emu->Scale(lumi_norm);
	njets_di_emu->Scale(lumi_norm);
	nbtags_di_emu->Scale(lumi_norm);
	npv_di_emu->Scale(lumi_norm);
	pt_mu1_di_mumu->Scale(lumi_norm);
	eta_mu1_di_mumu->Scale(lumi_norm);
	phi_mu1_di_mumu->Scale(lumi_norm);
	pt_mu2_di_mumu->Scale(lumi_norm);
	eta_mu2_di_mumu->Scale(lumi_norm);
	phi_mu2_di_mumu->Scale(lumi_norm);
	pt_jet1_di_mumu->Scale(lumi_norm);
	pt_jet2_di_mumu->Scale(lumi_norm);
	pt_jet3_di_mumu->Scale(lumi_norm);
	pt_jet4_di_mumu->Scale(lumi_norm);
	pt_jet5_di_mumu->Scale(lumi_norm);
	pt_jet6_di_mumu->Scale(lumi_norm);
	pt_jet_all_di_mumu->Scale(lumi_norm);
	csv_jet_all_di_mumu->Scale(lumi_norm);
	ht_di_mumu->Scale(lumi_norm);
	njets_ht_2D_di_mumu->Scale(lumi_norm);
	njets_di_mumu->Scale(lumi_norm);
	nbtags_di_mumu->Scale(lumi_norm);
	npv_di_mumu->Scale(lumi_norm);

	pt_e1_sl_e_genweighted->Scale(lumi_norm_genweighted);
	eta_e1_sl_e_genweighted->Scale(lumi_norm_genweighted);
	phi_e1_sl_e_genweighted->Scale(lumi_norm_genweighted);
	pt_jet1_sl_e_genweighted->Scale(lumi_norm_genweighted);
	pt_jet2_sl_e_genweighted->Scale(lumi_norm_genweighted);
	pt_jet3_sl_e_genweighted->Scale(lumi_norm_genweighted);
	pt_jet4_sl_e_genweighted->Scale(lumi_norm_genweighted);
	pt_jet5_sl_e_genweighted->Scale(lumi_norm_genweighted);
	pt_jet6_sl_e_genweighted->Scale(lumi_norm_genweighted);
	pt_jet_all_sl_e_genweighted->Scale(lumi_norm_genweighted);
	csv_jet_all_sl_e_genweighted->Scale(lumi_norm_genweighted);
	ht_sl_e_genweighted->Scale(lumi_norm_genweighted);
	njets_ht_2D_sl_e_genweighted->Scale(lumi_norm_genweighted);
	njets_sl_e_genweighted->Scale(lumi_norm_genweighted);
	nbtags_sl_e_genweighted->Scale(lumi_norm_genweighted);
	npv_sl_e_genweighted->Scale(lumi_norm_genweighted);
	pt_mu1_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	eta_mu1_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	phi_mu1_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet1_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet2_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet3_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet4_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet5_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet6_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet_all_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	csv_jet_all_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	ht_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	njets_ht_2D_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	njets_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	nbtags_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	npv_sl_mu_genweighted->Scale(lumi_norm_genweighted);
	pt_e1_di_ee_genweighted->Scale(lumi_norm_genweighted);
	eta_e1_di_ee_genweighted->Scale(lumi_norm_genweighted);
	phi_e1_di_ee_genweighted->Scale(lumi_norm_genweighted);
	pt_e2_di_ee_genweighted->Scale(lumi_norm_genweighted);
	eta_e2_di_ee_genweighted->Scale(lumi_norm_genweighted);
	phi_e2_di_ee_genweighted->Scale(lumi_norm_genweighted);
	pt_jet1_di_ee_genweighted->Scale(lumi_norm_genweighted);
	pt_jet2_di_ee_genweighted->Scale(lumi_norm_genweighted);
	pt_jet3_di_ee_genweighted->Scale(lumi_norm_genweighted);
	pt_jet4_di_ee_genweighted->Scale(lumi_norm_genweighted);
	pt_jet5_di_ee_genweighted->Scale(lumi_norm_genweighted);
	pt_jet6_di_ee_genweighted->Scale(lumi_norm_genweighted);
	pt_jet_all_di_ee_genweighted->Scale(lumi_norm_genweighted);
	csv_jet_all_di_ee_genweighted->Scale(lumi_norm_genweighted);
	ht_di_ee_genweighted->Scale(lumi_norm_genweighted);
	njets_ht_2D_di_ee_genweighted->Scale(lumi_norm_genweighted);
	njets_di_ee_genweighted->Scale(lumi_norm_genweighted);
	nbtags_di_ee_genweighted->Scale(lumi_norm_genweighted);
	npv_di_ee_genweighted->Scale(lumi_norm_genweighted);
	pt_e1_di_emu_genweighted->Scale(lumi_norm_genweighted);
	eta_e1_di_emu_genweighted->Scale(lumi_norm_genweighted);
	phi_e1_di_emu_genweighted->Scale(lumi_norm_genweighted);
	pt_mu1_di_emu_genweighted->Scale(lumi_norm_genweighted);
	eta_mu1_di_emu_genweighted->Scale(lumi_norm_genweighted);
	phi_mu1_di_emu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet1_di_emu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet2_di_emu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet3_di_emu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet4_di_emu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet5_di_emu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet6_di_emu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet_all_di_emu_genweighted->Scale(lumi_norm_genweighted);
	csv_jet_all_di_emu_genweighted->Scale(lumi_norm_genweighted);
	ht_di_emu_genweighted->Scale(lumi_norm_genweighted);
	njets_ht_2D_di_emu_genweighted->Scale(lumi_norm_genweighted);
	njets_di_emu_genweighted->Scale(lumi_norm_genweighted);
	nbtags_di_emu_genweighted->Scale(lumi_norm_genweighted);
	npv_di_emu_genweighted->Scale(lumi_norm_genweighted);
	pt_mu1_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	eta_mu1_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	phi_mu1_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	pt_mu2_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	eta_mu2_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	phi_mu2_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet1_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet2_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet3_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet4_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet5_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet6_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	pt_jet_all_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	csv_jet_all_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	ht_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	njets_ht_2D_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	njets_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	nbtags_di_mumu_genweighted->Scale(lumi_norm_genweighted);
	npv_di_mumu_genweighted->Scale(lumi_norm_genweighted);


	// Printing out Yields

    std::cout<< " Done! " << std::endl;
 	fout<<"**********************************************************************************************\n\n";
	fout<<"Sample : "<<MC_Data<<"  "<<sample<<"\n";
	fout<<"tt+X Process : "<<process<<"\n\n";
    fout<<"Total No. of Events in sample : "<<N_total<<"\n";
	fout<<"Sum of Generator weights of all Events in sample : "<<sum_gen_weights<<"\n";
	fout<<"Product of Generator weights of all Events in sample : "<<product_gen_weights<<"\n\n";
    fout<<"**********************************************************************************************\n\n";
	fout<<"Raw numbers : \n\n";
	fout<<"Total No. of Selected Events: "<<N_sel_raw<<"\n";
	fout<<"Total No. of Single Lepton Events: "<<N_SL_raw<<"\n";
	fout<<"Total No. of Dilepton Events: "<<N_DL_raw<<"\n\n";
	fout<<"No. of Single Electron Events: "<<N_e_raw<<"\n";
    fout<<"No. of Single Muon Events: "<<N_mu_raw<<"\n";
    fout<<"No. of Double Electron Events: "<<N_ee_raw<<"\n";
    fout<<"No. of Electron Muon Events: "<<N_emu_raw<<"\n";
    fout<<"No. of Double Muon Events: "<<N_mumu_raw<<"\n\n";
    fout<<"**********************************************************************************************\n\n";
	fout<<"Single Lepton Event Yields Normalized to L = "<<L<<" 1/fb : \n\n";
	fout<<"Total No. of Single Lepton Events: "<<N_SL_norm<<"\n";
	fout<<"No. of Single Electron Events: "<<N_e_norm<<"\n";
	fout<<"No. of Single Muon Events: "<<N_mu_norm<<"\n\n";
	fout<<"Yields for SL jet-tag categories : \n\n";
	fout<<"4j + 3b  ,  4j + 4b  ,  5j + 3b  ,  5j + >=4b  ,  >=6j + 2b  ,  >=6j + 3b  ,  >=6j + >=4b \n";
	fout<<N_SL_4j3b_norm<<"    "<<N_SL_4j4b_norm<<"    "<<N_SL_5j3b_norm<<"    "<<N_SL_5j4b_norm<<"    "<<N_SL_6j2b_norm<<"    "<<N_SL_6j3b_norm<<"    "<<N_SL_6j4b_norm<<"\n\n";
    fout<<"**********************************************************************************************\n\n";
	fout<<"Di Lepton Event Yields Normalized to L = "<<L<<" 1/fb : \n\n";
	fout<<"Total No. of Di Lepton Events: "<<N_DL_norm<<"\n";
	fout<<"No. of Di Electron Events: "<<N_ee_norm<<"\n";
	fout<<"No. of Electron Muon Events: "<<N_emu_norm<<"\n";
	fout<<"No. of Di Muon Events: "<<N_mumu_norm<<"\n\n";
	fout<<"Yields for DL jet-tag categories : \n\n";
	fout<<"3j + 2b  ,  3j + 3b  ,  >=4j + 2b  ,  >=4j + 3b  ,  >=4j + >=4b \n";
	fout<<N_DL_3j2b_norm<<"    "<<N_DL_3j3b_norm<<"    "<<N_DL_4j2b_norm<<"    "<<N_DL_4j3b_norm<<"    "<<N_DL_4j4b_norm<<"\n\n";
	fout<<"**********************************************************************************************\n\n";
	fout<<"Single Lepton Event Yields Normalized to L = "<<L<<" 1/fb (Using Generator Weights) : \n\n";
	fout<<"Total No. of Single Lepton Events: "<<N_SL_genweighted_norm<<"\n";
	fout<<"No. of Single Electron Events: "<<N_e_genweighted_norm<<"\n";
	fout<<"No. of Single Muon Events: "<<N_mu_genweighted_norm<<"\n\n";
	fout<<"Yields for SL jet-tag categories : \n\n";
	fout<<"4j + 3b  ,  4j + 4b  ,  5j + 3b  ,  5j + >=4b  ,  >=6j + 2b  ,  >=6j + 3b  ,  >=6j + >=4b \n";
	fout<<N_SL_4j3b_genweighted_norm<<"    "<<N_SL_4j4b_genweighted_norm<<"    "<<N_SL_5j3b_genweighted_norm<<"    "<<N_SL_5j4b_genweighted_norm<<"    "<<N_SL_6j2b_genweighted_norm<<"    "<<N_SL_6j3b_genweighted_norm<<"    "<<N_SL_6j4b_genweighted_norm<<"\n\n";
	fout<<"**********************************************************************************************\n\n";
	fout<<"Di Lepton Event Yields Normalized to L = "<<L<<" 1/fb (Using Generator Weights) : \n\n";
	fout<<"Total No. of Di Lepton Events: "<<N_DL_genweighted_norm<<"\n";
	fout<<"No. of Di Electron Events: "<<N_ee_genweighted_norm<<"\n";
	fout<<"No. of Electron Muon Events: "<<N_emu_genweighted_norm<<"\n";
	fout<<"No. of Di Muon Events: "<<N_mumu_genweighted_norm<<"\n\n";
	fout<<"Yields for DL jet-tag categories : \n\n";
	fout<<"3j + 2b  ,  3j + 3b  ,  >=4j + 2b  ,  >=4j + 3b  ,  >=4j + >=4b \n";
	fout<<N_DL_3j2b_genweighted_norm<<"    "<<N_DL_3j3b_genweighted_norm<<"    "<<N_DL_4j2b_genweighted_norm<<"    "<<N_DL_4j3b_genweighted_norm<<"    "<<N_DL_4j4b_genweighted_norm<<"\n\n";
	fout<<"**********************************************************************************************\n\n";
    histofile.Write();
    histofile.Close();
	fout.close();

    return;
}


