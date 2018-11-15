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

void fill_acc_histo(TH2D* h, int xl, int xu, int yl, int yu, double weight){

	for(int i=xl; i<=xu; i++){
		for(int j=yl; j<=yu; j++){
			h->Fill(i,j,weight);
		}
	}
	return;
}

void Control_Region_Z_2D_jet_tag_yields_bprob( int maxNentries=-1, int Njobs=1, int jobN=1 ) {

	ifstream fin;
	ofstream fout;
	std::string sample;
	std::string type;
	double gen_b_pt_cut;
	int n_input_files;
	string file;
	std::vector<std::string> treefilenames;
	std::string output_hist_filename;
	std::string output_yields_filename;
	double xs;

	fin.open("input.txt");
	fin>>sample;
	fin>>type;
	fin>>gen_b_pt_cut;
	fin>>n_input_files;
	for(int i=0; i<n_input_files; i++){
		fin>>file;
		treefilenames.push_back(file);
	}
	fin>>xs;
	fin.close();

	std::string pt_cut = std::to_string((int)gen_b_pt_cut);
	if(type == "all"){
		output_hist_filename = ("Control_Region_Z_2D_jet_tag_yields_bprob_" + sample + "_" + type + ".root").c_str();
		output_yields_filename = ("output_" + sample + "_" + type + "_2d_bprob.txt").c_str();
	}
	else{
		output_hist_filename = ("Control_Region_Z_2D_jet_tag_yields_bprob_" + sample + "_" + type + "_pt" + pt_cut + ".root").c_str();
		output_yields_filename = ("output_" + sample + "_" + type + "_pt" + pt_cut + "_2d_bprob.txt").c_str();
	}
	fout.open(output_yields_filename);

	double L = 35.92; // 1/fb
	double jet_csv_med_cut = 0.8484;

    int N_total = 0;
	double sum_pos_gen_weights = 0;
	double sum_neg_gen_weights = 0;
	double sum_gen_weights = 0;
	double product_gen_weights = 1.0;

	int N_sel = 0;
	int N_SL = 0;
	int N_DL = 0;
	int N_e = 0;
	int N_mu = 0;
	int N_ee = 0;
	int N_emu = 0;
	int N_mumu = 0;

	// Yields from MC

	double N_Z_loose_0btag = 0;
	double N_Z_tight_0btag = 0;
	double N_Z_loose_0btag_weighted = 0;
	double N_Z_tight_0btag_weighted = 0;
	double N_Z_loose_1btag = 0;
	double N_Z_tight_1btag = 0;
	double N_Z_loose_1btag_weighted = 0;
	double N_Z_tight_1btag_weighted = 0;
	double N_Z_loose_2btag = 0;
	double N_Z_tight_2btag = 0;
	double N_Z_loose_2btag_weighted = 0;
	double N_Z_tight_2btag_weighted = 0;

	double N_Z_ttb_loose = 0;
	double N_Z_tt2b_loose = 0;
	double N_Z_ttbb_loose = 0;
	double N_Z_ttcc_loose = 0;
	double N_Z_ttlf_loose = 0;
	double N_Z_ttb_tight = 0;
	double N_Z_tt2b_tight = 0;
	double N_Z_ttbb_tight = 0;
	double N_Z_ttcc_tight = 0;
	double N_Z_ttlf_tight = 0;
	double N_Z_ttb_loose_weighted = 0;
	double N_Z_tt2b_loose_weighted = 0;
	double N_Z_ttbb_loose_weighted = 0;
	double N_Z_ttcc_loose_weighted = 0;
	double N_Z_ttlf_loose_weighted = 0;
	double N_Z_ttb_tight_weighted = 0;
	double N_Z_tt2b_tight_weighted = 0;
	double N_Z_ttbb_tight_weighted = 0;
	double N_Z_ttcc_tight_weighted = 0;
	double N_Z_ttlf_tight_weighted = 0;

	// Yields at L

	double lumi_norm = 0;
	double lumi_norm_weighted = 0;

	double N_Z_loose_0btag_norm = 0;
	double N_Z_tight_0btag_norm = 0;
	double N_Z_loose_0btag_weighted_norm = 0;
	double N_Z_tight_0btag_weighted_norm = 0;
	double N_Z_loose_1btag_norm = 0;
	double N_Z_tight_1btag_norm = 0;
	double N_Z_loose_1btag_weighted_norm = 0;
	double N_Z_tight_1btag_weighted_norm = 0;
	double N_Z_loose_2btag_norm = 0;
	double N_Z_tight_2btag_norm = 0;
	double N_Z_loose_2btag_weighted_norm = 0;
	double N_Z_tight_2btag_weighted_norm = 0;

	double N_Z_ttb_loose_norm = 0;
	double N_Z_tt2b_loose_norm = 0;
	double N_Z_ttbb_loose_norm = 0;
	double N_Z_ttcc_loose_norm = 0;
	double N_Z_ttlf_loose_norm = 0;
	double N_Z_ttb_tight_norm = 0;
	double N_Z_tt2b_tight_norm = 0;
	double N_Z_ttbb_tight_norm = 0;
	double N_Z_ttcc_tight_norm = 0;
	double N_Z_ttlf_tight_norm = 0;
	double N_Z_ttb_loose_weighted_norm = 0;
	double N_Z_tt2b_loose_weighted_norm = 0;
	double N_Z_ttbb_loose_weighted_norm = 0;
	double N_Z_ttcc_loose_weighted_norm = 0;
	double N_Z_ttlf_loose_weighted_norm = 0;
	double N_Z_ttb_tight_weighted_norm = 0;
	double N_Z_tt2b_tight_weighted_norm = 0;
	double N_Z_ttbb_tight_weighted_norm = 0;
	double N_Z_ttcc_tight_weighted_norm = 0;
	double N_Z_ttlf_tight_weighted_norm = 0;

	// For calculating b-tagging and mis-tagging efficiencies

	double N_jets_all = 0;
	double N_btags_all = 0;
	double N_jets_all_weighted = 0;
	double N_btags_all_weighted = 0;
	double N_jets_b = 0;
	double N_jets_c = 0;
	double N_jets_lf = 0;
	double N_jets_b_tag = 0;
	double N_jets_c_tag = 0;
	double N_jets_lf_tag = 0;
	double N_jets_b_weighted = 0;
	double N_jets_c_weighted = 0;
	double N_jets_lf_weighted = 0;
	double N_jets_b_tag_weighted = 0;
	double N_jets_c_tag_weighted = 0;
	double N_jets_lf_tag_weighted = 0;
	double N_nobtags_all = 0;
	double N_jets_b_notag = 0;

	double b_effi;
	double tag_effi;
	double no_b_effi;
	double no_tag_effi;
	double b_tag_effi;
	double b_no_tag_effi;
	double c_tag_effi;
	double c_no_tag_effi;
	double lf_tag_effi;
	double lf_no_tag_effi;
	double no_b_tag_effi;
	double no_b_no_tag_effi;
	double tag_b_effi;
	double tag_no_b_effi;
	double no_tag_b_effi;
	double no_tag_no_b_effi;
	double b_effi_weighted;
	double tag_effi_weighted;
	double no_b_effi_weighted;
	double no_tag_effi_weighted;
	double b_tag_effi_weighted;
	double b_no_tag_effi_weighted;
	double c_tag_effi_weighted;
	double c_no_tag_effi_weighted;
	double lf_tag_effi_weighted;
	double lf_no_tag_effi_weighted;
	double no_b_tag_effi_weighted;
	double no_b_no_tag_effi_weighted;
	double tag_b_effi_weighted;
	double tag_no_b_effi_weighted;
	double no_tag_b_effi_weighted;
	double no_tag_no_b_effi_weighted;
	double p_b_tag;
	double p_b_notag;

    // input filename

    //std::string treefilename = "/eos/uscms/store/user/adatta/ttH_Analysis/Z/ver2/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/ttH_Analyzer_ttjets_pp/170919_225737/0000/ttHbbNtuple*.root";

	std::string histofilename = output_hist_filename;

	TChain *reco_chain = new TChain("ttHbb/recoTree");
	TChain *gen_chain = new TChain("ttHbb/genTree");

	for(int i=0; i<n_input_files; i++){
    	reco_chain->Add(treefilenames[i].c_str());
		gen_chain->Add(treefilenames[i].c_str());
	}

    TFile histofile(histofilename.c_str(),"recreate");
    histofile.cd();
    
	TH1::SetDefaultSumw2();

	// mll Plot for Dilepton Z-Region events
	TH1D* mll_Z_loose = new TH1D("mll_Z_loose","M(ll) Distribution for 76 < M(ll) < 106 ;M(ll) (GeV);Nr. of Events",100,70,110);
	TH1D* mll_Z_tight = new TH1D("mll_Z_tight","M(ll) Distribution for 88 < M(ll) < 94 ;M(ll) (GeV);Nr. of Events",100,70,110);
	TH1D* mll_Z_loose_weighted = new TH1D("mll_Z_loose_weighted","M(ll) Weighted Distribution for 76 < M(ll) < 106 ;M(ll) (GeV);Nr. of Events",100,70,110);
	TH1D* mll_Z_tight_weighted = new TH1D("mll_Z_tight_weighted","M(ll) Weighted Distribution for 88 < M(ll) < 94 ;M(ll) (GeV);Nr. of Events",100,70,110);

	// 2D Plots vs Nr. of jets and b-tags
	TH2D* njets_btags_Z_loose_total = new TH2D("njets_btags_Z_loose_total","Total nr. of Events vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_total = new TH2D("njets_btags_Z_tight_total","Total nr. of Events vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_loose_ttbb = new TH2D("njets_btags_Z_loose_ttbb","Nr. of ttbb Events vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_ttbb = new TH2D("njets_btags_Z_tight_ttbb","Nr. of ttbb Events vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_loose_ttb = new TH2D("njets_btags_Z_loose_ttb","Nr. of ttb Events vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_ttb = new TH2D("njets_btags_Z_tight_ttb","Nr. of ttb Events vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_loose_tt2b = new TH2D("njets_btags_Z_loose_tt2b","Nr. of tt2b Events vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_tt2b = new TH2D("njets_btags_Z_tight_tt2b","Nr. of tt2b Events vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_loose_total = new TH2D("njets_bjets_Z_loose_total","Total nr. of Events vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_total = new TH2D("njets_bjets_Z_tight_total","Total nr. of Events vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_total = new TH2D("nbjets_btags_Z_loose_total","Total nr. of Events vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_total = new TH2D("nbjets_btags_Z_tight_total","Total nr. of Events vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* njets_bjets_Z_loose_ttbb = new TH2D("njets_bjets_Z_loose_ttbb","Nr. of ttbb Events vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_ttbb = new TH2D("njets_bjets_Z_tight_ttbb","Nr. of ttbb Events vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_ttbb = new TH2D("nbjets_btags_Z_loose_ttbb","Nr. of ttbb Events vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_ttbb = new TH2D("nbjets_btags_Z_tight_ttbb","Nr. of ttbb Events vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* njets_bjets_Z_loose_ttb = new TH2D("njets_bjets_Z_loose_ttb","Nr. of ttb Events vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_ttb = new TH2D("njets_bjets_Z_tight_ttb","Nr. of ttb Events vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_ttb = new TH2D("nbjets_btags_Z_loose_ttb","Nr. of ttb Events vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_ttb = new TH2D("nbjets_btags_Z_tight_ttb","Nr. of ttb Events vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* njets_bjets_Z_loose_tt2b = new TH2D("njets_bjets_Z_loose_tt2b","Nr. of tt2b Events vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_tt2b = new TH2D("njets_bjets_Z_tight_tt2b","Nr. of tt2b Events vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_tt2b = new TH2D("nbjets_btags_Z_loose_tt2b","Nr. of tt2b Events vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_tt2b = new TH2D("nbjets_btags_Z_tight_tt2b","Nr. of tt2b Events vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);

	TH2D* njets_btags_Z_loose_total_weighted = new TH2D("njets_btags_Z_loose_total_weighted","Total nr. of Weighted Events vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_total_weighted = new TH2D("njets_btags_Z_tight_total_weighted","Total nr. of Weighted Events vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_loose_ttbb_weighted = new TH2D("njets_btags_Z_loose_ttbb_weighted","Nr. of ttbb Weighted Events vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_ttbb_weighted = new TH2D("njets_btags_Z_tight_ttbb_weighted","Nr. of ttbb Weighted Events vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_loose_ttb_weighted = new TH2D("njets_btags_Z_loose_ttb_weighted","Nr. of ttb Weighted Events vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_ttb_weighted = new TH2D("njets_btags_Z_tight_ttb_weighted","Nr. of ttb Weighted Events vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_loose_tt2b_weighted = new TH2D("njets_btags_Z_loose_tt2b_weighted","Nr. of tt2b Weighted Events vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_tt2b_weighted = new TH2D("njets_btags_Z_tight_tt2b_weighted","Nr. of tt2b Weighted Events vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_loose_total_weighted = new TH2D("njets_bjets_Z_loose_total_weighted","Total nr. of Weighted Events vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_total_weighted = new TH2D("njets_bjets_Z_tight_total_weighted","Total nr. of Weighted Events vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_total_weighted = new TH2D("nbjets_btags_Z_loose_total_weighted","Total nr. of Weighted Events vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_total_weighted = new TH2D("nbjets_btags_Z_tight_total_weighted","Total nr. of Weighted Events vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* njets_bjets_Z_loose_ttbb_weighted = new TH2D("njets_bjets_Z_loose_ttbb_weighted","Nr. of ttbb Weighted Events vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_ttbb_weighted = new TH2D("njets_bjets_Z_tight_ttbb_weighted","Nr. of ttbb Weighted Events vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_ttbb_weighted = new TH2D("nbjets_btags_Z_loose_ttbb_weighted","Nr. of ttbb Weighted Events vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_ttbb_weighted = new TH2D("nbjets_btags_Z_tight_ttbb_weighted","Nr. of ttbb Weighted Events vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* njets_bjets_Z_loose_ttb_weighted = new TH2D("njets_bjets_Z_loose_ttb_weighted","Nr. of ttb Weighted Events vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_ttb_weighted = new TH2D("njets_bjets_Z_tight_ttb_weighted","Nr. of ttb Weighted Events vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_ttb_weighted = new TH2D("nbjets_btags_Z_loose_ttb_weighted","Nr. of ttb Weighted Events vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_ttb_weighted = new TH2D("nbjets_btags_Z_tight_ttb_weighted","Nr. of ttb Weighted Events vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* njets_bjets_Z_loose_tt2b_weighted = new TH2D("njets_bjets_Z_loose_tt2b_weighted","Nr. of tt2b Weighted Events vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_tt2b_weighted = new TH2D("njets_bjets_Z_tight_tt2b_weighted","Nr. of tt2b Weighted Events vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_tt2b_weighted = new TH2D("nbjets_btags_Z_loose_tt2b_weighted","Nr. of tt2b Weighted Events vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_tt2b_weighted = new TH2D("nbjets_btags_Z_tight_tt2b_weighted","Nr. of tt2b Weighted Events vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);

	// Accumulative 2D Histos
	TH2D* njets_btags_Z_loose_total_acc = new TH2D("njets_btags_Z_loose_total_acc","Total nr. of Events (Accumulative) vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_total_acc = new TH2D("njets_btags_Z_tight_total_acc","Total nr. of Events (Accumulative) vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_loose_ttbb_acc = new TH2D("njets_btags_Z_loose_ttbb_acc","Nr. of ttbb Events (Accumulative) vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_ttbb_acc = new TH2D("njets_btags_Z_tight_ttbb_acc","Nr. of ttbb Events (Accumulative) vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_loose_ttb_acc = new TH2D("njets_btags_Z_loose_ttb_acc","Nr. of ttb Events (Accumulative) vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_ttb_acc = new TH2D("njets_btags_Z_tight_ttb_acc","Nr. of ttb Events (Accumulative) vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_loose_tt2b_acc = new TH2D("njets_btags_Z_loose_tt2b_acc","Nr. of tt2b Events (Accumulative) vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_tt2b_acc = new TH2D("njets_btags_Z_tight_tt2b_acc","Nr. of tt2b Events (Accumulative) vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_loose_total_acc = new TH2D("njets_bjets_Z_loose_total_acc","Total nr. of Events (Accumulative) vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_total_acc = new TH2D("njets_bjets_Z_tight_total_acc","Total nr. of Events (Accumulative) vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_total_acc = new TH2D("nbjets_btags_Z_loose_total_acc","Total nr. of Events (Accumulative) vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_total_acc = new TH2D("nbjets_btags_Z_tight_total_acc","Total nr. of Events (Accumulative) vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* njets_bjets_Z_loose_ttbb_acc = new TH2D("njets_bjets_Z_loose_ttbb_acc","Nr. of ttbb Events (Accumulative) vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_ttbb_acc = new TH2D("njets_bjets_Z_tight_ttbb_acc","Nr. of ttbb Events (Accumulative) vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_ttbb_acc = new TH2D("nbjets_btags_Z_loose_ttbb_acc","Nr. of ttbb Events (Accumulative) vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_ttbb_acc = new TH2D("nbjets_btags_Z_tight_ttbb_acc","Nr. of ttbb Events (Accumulative) vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* njets_bjets_Z_loose_ttb_acc = new TH2D("njets_bjets_Z_loose_ttb_acc","Nr. of ttb Events (Accumulative) vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_ttb_acc = new TH2D("njets_bjets_Z_tight_ttb_acc","Nr. of ttb Events (Accumulative) vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_ttb_acc = new TH2D("nbjets_btags_Z_loose_ttb_acc","Nr. of ttb Events (Accumulative) vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_ttb_acc = new TH2D("nbjets_btags_Z_tight_ttb_acc","Nr. of ttb Events (Accumulative) vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* njets_bjets_Z_loose_tt2b_acc = new TH2D("njets_bjets_Z_loose_tt2b_acc","Nr. of tt2b Events (Accumulative) vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_tt2b_acc = new TH2D("njets_bjets_Z_tight_tt2b_acc","Nr. of tt2b Events (Accumulative) vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_tt2b_acc = new TH2D("nbjets_btags_Z_loose_tt2b_acc","Nr. of tt2b Events (Accumulative) vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_tt2b_acc = new TH2D("nbjets_btags_Z_tight_tt2b_acc","Nr. of tt2b Events (Accumulative) vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);

	TH2D* njets_btags_Z_loose_total_weighted_acc = new TH2D("njets_btags_Z_loose_total_weighted_acc","Total nr. of Weighted Events (Accumulative) vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_total_weighted_acc = new TH2D("njets_btags_Z_tight_total_weighted_acc","Total nr. of Weighted Events (Accumulative) vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_loose_ttbb_weighted_acc = new TH2D("njets_btags_Z_loose_ttbb_weighted_acc","Nr. of ttbb Weighted Events (Accumulative) vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_ttbb_weighted_acc = new TH2D("njets_btags_Z_tight_ttbb_weighted_acc","Nr. of ttbb Weighted Events (Accumulative) vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_loose_ttb_weighted_acc = new TH2D("njets_btags_Z_loose_ttb_weighted_acc","Nr. of ttb Weighted Events (Accumulative) vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_ttb_weighted_acc = new TH2D("njets_btags_Z_tight_ttb_weighted_acc","Nr. of ttb Weighted Events (Accumulative) vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_loose_tt2b_weighted_acc = new TH2D("njets_btags_Z_loose_tt2b_weighted_acc","Nr. of tt2b Weighted Events (Accumulative) vs Jet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_btags_Z_tight_tt2b_weighted_acc = new TH2D("njets_btags_Z_tight_tt2b_weighted_acc","Nr. of tt2b Weighted Events (Accumulative) vs Jet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of btags",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_loose_total_weighted_acc = new TH2D("njets_bjets_Z_loose_total_weighted_acc","Total nr. of Weighted Events (Accumulative) vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_total_weighted_acc = new TH2D("njets_bjets_Z_tight_total_weighted_acc","Total nr. of Weighted Events (Accumulative) vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_total_weighted_acc = new TH2D("nbjets_btags_Z_loose_total_weighted_acc","Total nr. of Weighted Events (Accumulative) vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_total_weighted_acc = new TH2D("nbjets_btags_Z_tight_total_weighted_acc","Total nr. of Weighted Events (Accumulative) vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* njets_bjets_Z_loose_ttbb_weighted_acc = new TH2D("njets_bjets_Z_loose_ttbb_weighted_acc","Nr. of ttbb Weighted Events (Accumulative) vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_ttbb_weighted_acc = new TH2D("njets_bjets_Z_tight_ttbb_weighted_acc","Nr. of ttbb Weighted Events (Accumulative) vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_ttbb_weighted_acc = new TH2D("nbjets_btags_Z_loose_ttbb_weighted_acc","Nr. of ttbb Weighted Events (Accumulative) vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_ttbb_weighted_acc = new TH2D("nbjets_btags_Z_tight_ttbb_weighted_acc","Nr. of ttbb Weighted Events (Accumulative) vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* njets_bjets_Z_loose_ttb_weighted_acc = new TH2D("njets_bjets_Z_loose_ttb_weighted_acc","Nr. of ttb Weighted Events (Accumulative) vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_ttb_weighted_acc = new TH2D("njets_bjets_Z_tight_ttb_weighted_acc","Nr. of ttb Weighted Events (Accumulative) vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_ttb_weighted_acc = new TH2D("nbjets_btags_Z_loose_ttb_weighted_acc","Nr. of ttb Weighted Events (Accumulative) vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_ttb_weighted_acc = new TH2D("nbjets_btags_Z_tight_ttb_weighted_acc","Nr. of ttb Weighted Events (Accumulative) vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* njets_bjets_Z_loose_tt2b_weighted_acc = new TH2D("njets_bjets_Z_loose_tt2b_weighted_acc","Nr. of tt2b Weighted Events (Accumulative) vs Jet and Bjet Multiplicity for 76 < M(ll) < 106 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* njets_bjets_Z_tight_tt2b_weighted_acc = new TH2D("njets_bjets_Z_tight_tt2b_weighted_acc","Nr. of tt2b Weighted Events (Accumulative) vs Jet and Bjet Multiplicity for 88 < M(ll) < 94 ;Nr. of jets ;Nr. of bjets",13,2,15,7,0,7);
	TH2D* nbjets_btags_Z_loose_tt2b_weighted_acc = new TH2D("nbjets_btags_Z_loose_tt2b_weighted_acc","Nr. of tt2b Weighted Events (Accumulative) vs Bjet and Btag Multiplicity for 76 < M(ll) < 106 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);
	TH2D* nbjets_btags_Z_tight_tt2b_weighted_acc = new TH2D("nbjets_btags_Z_tight_tt2b_weighted_acc","Nr. of tt2b Weighted Events (Accumulative) vs Bjet and Btag Multiplicity for 88 < M(ll) < 94 ;Nr. of bjets ;Nr. of btags",7,0,7,7,0,7);

	// B-tagging mis-tagging efficiencies vs Pt and Eta

	int n_ptBins = 13;
	double x_ptBins[14] = { 20, 30, 40, 50, 60, 70, 80, 90 , 100, 125, 150, 200, 300, 500 };

	int n_etaBins = 7;
	double x_etaBins[8]
		= {  -2.4, -2.1 + 0.6 * 1, -2.1 + 0.6 * 2, -2.1 + 0.6 * 3, -2.1 + 0.6 * 4, -2.1 + 0.6 * 5, -2.1 + 0.6 * 6, -2.1 + 0.6 * 7 + 0.3 };

	TEfficiency* b_tag_effi_pt = new TEfficiency("b_tag_effi_pt","B-Tagging Efficiency for b-jets vs Jet Pt ;Jet Pt (GeV);Efficiency", n_ptBins, x_ptBins );
	TEfficiency* b_tag_effi_eta = new TEfficiency("b_tag_effi_eta","B-Tagging Efficiency for b-jets vs Jet Eta ;Jet Eta ;Efficiency", n_etaBins, x_etaBins);
	TEfficiency* c_tag_effi_pt = new TEfficiency("c_tag_effi_pt","B-MisTagging Efficiency for c-jets vs Jet Pt ;Jet Pt (GeV);Efficiency", n_ptBins, x_ptBins);
	TEfficiency* c_tag_effi_eta = new TEfficiency("c_tag_effi_eta","B-Tagging Efficiency for c-jets vs Jet Eta ;Jet Eta ;Efficiency", n_etaBins, x_etaBins);
	TEfficiency* lf_tag_effi_pt = new TEfficiency("lf_tag_effi_pt","B-MisTagging Efficiency for lf-jets vs Jet Pt ;Jet Pt (GeV);Efficiency", n_ptBins, x_ptBins);
	TEfficiency* lf_tag_effi_eta = new TEfficiency("lf_tag_effi_eta","B-Tagging Efficiency for lf-jets vs Jet Eta ;Jet Eta ;Efficiency", n_etaBins, x_etaBins);
	TEfficiency* b_tag_effi_pt_weighted = new TEfficiency("b_tag_effi_pt_weighted","B-Tagging Efficiency for b-jets vs Jet Pt (Gen weight included) ;Jet Pt (GeV);Efficiency", n_ptBins, x_ptBins);
	TEfficiency* b_tag_effi_eta_weighted = new TEfficiency("b_tag_effi_eta_weighted","B-Tagging Efficiency for b-jets vs Jet Eta (Gen weight included) ;Jet Eta ;Efficiency", n_etaBins, x_etaBins);
	TEfficiency* c_tag_effi_pt_weighted = new TEfficiency("c_tag_effi_pt_weighted","B-MisTagging Efficiency for c-jets vs Jet Pt (Gen weight included) ;Jet Pt (GeV);Efficiency", n_ptBins, x_ptBins);
	TEfficiency* c_tag_effi_eta_weighted = new TEfficiency("c_tag_effi_eta_weighted","B-Tagging Efficiency for c-jets vs Jet Eta (Gen weight included) ;Jet Eta ;Efficiency", n_etaBins, x_etaBins);
	TEfficiency* lf_tag_effi_pt_weighted = new TEfficiency("lf_tag_effi_pt_weighted","B-MisTagging Efficiency for lf-jets vs Jet Pt (Gen weight included) ;Jet Pt (GeV);Efficiency", n_ptBins, x_ptBins);
	TEfficiency* lf_tag_effi_eta_weighted = new TEfficiency("lf_tag_effi_eta_weighted","B-Tagging Efficiency for lf-jets vs Jet Eta (Gen weight included) ;Jet Eta ;Efficiency", n_etaBins, x_etaBins);

	b_tag_effi_pt->SetUseWeightedEvents();
	b_tag_effi_eta->SetUseWeightedEvents();
	c_tag_effi_pt->SetUseWeightedEvents();
	c_tag_effi_eta->SetUseWeightedEvents();
	lf_tag_effi_pt->SetUseWeightedEvents();
	lf_tag_effi_eta->SetUseWeightedEvents();
	b_tag_effi_pt_weighted->SetUseWeightedEvents();
	b_tag_effi_eta_weighted->SetUseWeightedEvents();
	c_tag_effi_pt_weighted->SetUseWeightedEvents();
	c_tag_effi_eta_weighted->SetUseWeightedEvents();
	lf_tag_effi_pt_weighted->SetUseWeightedEvents();
	lf_tag_effi_eta_weighted->SetUseWeightedEvents();


	int nentries = reco_chain->GetEntries();
	int NeventsPerJob = int( double(nentries)/double(Njobs) + 0.000001 ) + 1;

  	int firstEvent = (jobN-1)*NeventsPerJob + 1;
  	int lastEvent  = firstEvent + NeventsPerJob;
 	if( jobN==Njobs ) lastEvent = -1;
  	if( jobN==1 ) firstEvent = 0;
 
	int nEvent;
	int pass_event_selection;
 	int n_lep, n_ele, n_mu;
	int n_jets, n_bjets, n_btags;

    int ttHf_cat;

    std::vector<double> * mu_pt = 0;
    std::vector<double> * mu_eta = 0;
    std::vector<double> * mu_phi = 0;

    std::vector<double> * ele_pt = 0;
    std::vector<double> * ele_eta = 0;
    std::vector<double> * ele_phi = 0;

    std::vector<double> * jet_pt = 0;
    std::vector<double> * jet_eta = 0;
    std::vector<double> * jet_phi = 0;
    std::vector<double> * jet_CSV = 0;
	std::vector<int> * jet_flavor = 0;

    double PFMETpt;
    double PFMETphi;
    double mll;
    double ht;

    std::vector<double> * lep_sf_id = 0;
    std::vector<double> * lep_sf_iso = 0;
    double lep_sf_trig;

    double b_weight;
    double gen_weight;
    double PU_weight;
    double pdf_weight_up;
    double pdf_weight_down;
    double q2_weight_up;
    double q2_weight_down;

	std::vector<double> * genbquarks_pt = 0;
	std::vector<double> * genbquarks_eta = 0;
	std::vector<double> * genbquarks_phi = 0;
	std::vector<int> * genbquarks_genid = 0;
	std::vector<int> * genbquarks_imm_parentid = 0;
	std::vector<int> * genbquarks_imm_daughterid = 0;
	std::vector<int> * genbquarks_parentid = 0;
	std::vector<int> * genbquarks_grandparentid = 0;
	std::vector<double> * genbhadrons_pt = 0;
	std::vector<double> * genbhadrons_eta = 0;
	std::vector<double> * genbhadrons_phi = 0;
	std::vector<int> * genbhadrons_genid = 0;
	std::vector<int> * genbhadrons_parentid = 0;
	std::vector<int> * genbhadrons_grandparentid = 0;

    reco_chain->SetBranchAddress("nEvent", &nEvent );
	reco_chain->SetBranchAddress("pass_event_selection", &pass_event_selection );
    reco_chain->SetBranchAddress("n_lep", &n_lep );
    reco_chain->SetBranchAddress("n_ele", &n_ele );
    reco_chain->SetBranchAddress("n_mu", &n_mu );
    reco_chain->SetBranchAddress("ttHf_cat", &ttHf_cat );
    reco_chain->SetBranchAddress("ele_pt", &ele_pt );
    reco_chain->SetBranchAddress("ele_eta", &ele_eta );
    reco_chain->SetBranchAddress("ele_phi", &ele_phi );
    reco_chain->SetBranchAddress("mu_pt", &mu_pt );
    reco_chain->SetBranchAddress("mu_eta", &mu_eta );
    reco_chain->SetBranchAddress("mu_phi", &mu_phi );
    reco_chain->SetBranchAddress("jet_pt", &jet_pt );
    reco_chain->SetBranchAddress("jet_eta", &jet_eta );
    reco_chain->SetBranchAddress("jet_phi", &jet_phi );
    reco_chain->SetBranchAddress("jet_CSV", &jet_CSV );
	reco_chain->SetBranchAddress("jet_flavor", &jet_flavor );
    reco_chain->SetBranchAddress("n_jets", &n_jets );
    reco_chain->SetBranchAddress("n_btags", &n_btags );
    reco_chain->SetBranchAddress("PFMETpt", &PFMETpt );
    reco_chain->SetBranchAddress("PFMETphi", &PFMETphi );
    reco_chain->SetBranchAddress("mll", &mll );
    reco_chain->SetBranchAddress("ht", &ht );
    reco_chain->SetBranchAddress("lep_sf_id", &lep_sf_id );
    reco_chain->SetBranchAddress("lep_sf_iso", &lep_sf_iso );
    reco_chain->SetBranchAddress("lep_sf_trig", &lep_sf_trig );
    reco_chain->SetBranchAddress("b_weight", &b_weight );
    reco_chain->SetBranchAddress("gen_weight", &gen_weight );
    reco_chain->SetBranchAddress("PU_weight", &PU_weight );
    reco_chain->SetBranchAddress("pdf_weight_up", &pdf_weight_up );
    reco_chain->SetBranchAddress("pdf_weight_down", &pdf_weight_down );
    reco_chain->SetBranchAddress("q2_weight_up", &q2_weight_up );
    reco_chain->SetBranchAddress("q2_weight_down", &q2_weight_down );
	gen_chain->SetBranchAddress("genbquarks_pt", &genbquarks_pt );
	gen_chain->SetBranchAddress("genbquarks_eta", &genbquarks_eta );
	gen_chain->SetBranchAddress("genbquarks_phi", &genbquarks_phi );
	gen_chain->SetBranchAddress("genbquarks_genid", &genbquarks_genid );
	gen_chain->SetBranchAddress("genbquarks_imm_parentid", &genbquarks_imm_parentid );
	gen_chain->SetBranchAddress("genbquarks_imm_daughterid", &genbquarks_imm_daughterid );
	gen_chain->SetBranchAddress("genbquarks_parentid", &genbquarks_parentid );
	gen_chain->SetBranchAddress("genbquarks_grandparentid", &genbquarks_grandparentid );
	gen_chain->SetBranchAddress("genbhadrons_pt", &genbhadrons_pt );
	gen_chain->SetBranchAddress("genbhadrons_eta", &genbhadrons_eta );
	gen_chain->SetBranchAddress("genbhadrons_phi", &genbhadrons_phi );
	gen_chain->SetBranchAddress("genbhadrons_genid", &genbhadrons_genid );
	gen_chain->SetBranchAddress("genbhadrons_parentid", &genbhadrons_parentid );
	gen_chain->SetBranchAddress("genbhadrons_grandparentid", &genbhadrons_grandparentid );


	std::cout << "========  Starting Event Loop  ========" << std::endl;
 	for (Long64_t ievt=0; ievt<reco_chain->GetEntries();ievt++) {

	    if( ievt<firstEvent ) continue;
	    if( ievt==lastEvent ) break;

      	if( ievt==0 )        std::cout << "     Event " << ievt+1 << std::endl;
      	if( ievt%10000==0 && ievt!=1) std::cout << "           " << ievt << "\t" 
  					     << int(double(ievt-1)/double(nentries)*100) << "% done" << std::endl;
	  
	 	if( ievt==(maxNentries+1) && ievt!=0 ) break;
		
		reco_chain->GetEntry(ievt);
		gen_chain->GetEntry(ievt);

		++N_total;

		if(gen_weight >= 0)
			sum_pos_gen_weights += gen_weight;
		else if(gen_weight < 0)
			sum_neg_gen_weights += gen_weight;
        sum_gen_weights += gen_weight;
		product_gen_weights = product_gen_weights * gen_weight;

		// Single Lepton events
		if (n_lep == 1) {
			++N_SL;
			if (n_ele == 1) {
				++N_e;
			}
			else if (n_mu == 1) {
				++N_mu;
			}
		}

		// Dilepton events
		else if (n_lep == 2) {
			++N_DL;
			if (n_ele == 2) {
				++N_ee;
			}
			else if (n_mu == 2){
				++N_mumu;
			}
			else {
				++N_emu;
			}
		}

		// Counting Loose Z events
		if(n_ele!=2 && n_mu!=2)
			continue;
		if( mll < 76 || mll > 106 )
			continue;

		// Calculating number of b-quarks at gen-level
		int n_bquarks = 0;
		for(unsigned int i=0; i<(*genbquarks_pt).size(); i++){
			if((*genbquarks_imm_parentid)[i] != -99 && (*genbquarks_imm_daughterid)[i] != -99){
				if((*genbquarks_imm_daughterid)[i] != 5 && (*genbquarks_imm_daughterid)[i] != -5){
					if( (*genbquarks_pt)[i] > gen_b_pt_cut )
						n_bquarks++;
				}
			}
		}
		// Checking if Number of b-quarks at gen-level = 4 for type = "4b"
		if(type == "4b"){
			if(n_bquarks < 4)
				continue;
		}

		// Event weight and SFs
		double tot_weight = 1;
		double tot_weight_gen = 1;
		if (pass_event_selection == 1){
			double sf = (*lep_sf_id)[0] * (*lep_sf_id)[1] * (*lep_sf_iso)[0] * (*lep_sf_iso)[1];
			tot_weight = sf * lep_sf_trig * PU_weight * b_weight;
			tot_weight_gen = sf * lep_sf_trig * PU_weight * b_weight * gen_weight;
		}

		double is_tag = 0;
	    n_bjets = 0;

		// for calculating B-tagging and mis-tagging efficiencies

		for(int i=0; i<n_jets; i++){
			N_jets_all += tot_weight;
			N_jets_all_weighted += tot_weight_gen;

			is_tag = 0;
			if((*jet_CSV)[i] > jet_csv_med_cut){
				is_tag = 1;
			}
			N_btags_all += is_tag*tot_weight;
			N_btags_all_weighted += is_tag*tot_weight_gen;
			N_nobtags_all += (1-is_tag)*tot_weight;

			if((*jet_flavor)[i] == 5){ // b
				n_bjets++;
				N_jets_b += tot_weight;
				N_jets_b_weighted += tot_weight_gen;
				N_jets_b_tag += is_tag*tot_weight;
				N_jets_b_notag += (1-is_tag)*tot_weight;
				N_jets_b_tag_weighted += is_tag*tot_weight_gen;
				b_tag_effi_pt->FillWeighted( is_tag, tot_weight, (*jet_pt)[i] );
				b_tag_effi_eta->FillWeighted( is_tag, tot_weight, (*jet_eta)[i] );
				b_tag_effi_pt_weighted->FillWeighted( is_tag, tot_weight_gen, (*jet_pt)[i] );
				b_tag_effi_eta_weighted->FillWeighted( is_tag, tot_weight_gen, (*jet_eta)[i] );
			}
			else if((*jet_flavor)[i] == 4){ // c
				N_jets_c += tot_weight;
				N_jets_c_weighted += tot_weight_gen;
				N_jets_c_tag += is_tag*tot_weight;
				N_jets_c_tag_weighted += is_tag*tot_weight_gen;
				c_tag_effi_pt->FillWeighted( is_tag, tot_weight, (*jet_pt)[i] );
				c_tag_effi_eta->FillWeighted( is_tag, tot_weight, (*jet_eta)[i] );
				c_tag_effi_pt_weighted->FillWeighted( is_tag, tot_weight_gen, (*jet_pt)[i] );
				c_tag_effi_eta_weighted->FillWeighted( is_tag, tot_weight_gen, (*jet_eta)[i] );
			}
			else if((*jet_flavor)[i] == 0){ // lf
				N_jets_lf += tot_weight;
				N_jets_lf_weighted += tot_weight_gen;
				N_jets_lf_tag += is_tag*tot_weight;
				N_jets_lf_tag_weighted += is_tag*tot_weight_gen;
				lf_tag_effi_pt->FillWeighted( is_tag, tot_weight, (*jet_pt)[i] );
				lf_tag_effi_eta->FillWeighted( is_tag, tot_weight, (*jet_eta)[i] );
				lf_tag_effi_pt_weighted->FillWeighted( is_tag, tot_weight_gen, (*jet_pt)[i] );
				lf_tag_effi_eta_weighted->FillWeighted( is_tag, tot_weight_gen, (*jet_eta)[i] );
			}
		}

		N_Z_loose_0btag += tot_weight;
		N_Z_loose_0btag_weighted += tot_weight_gen;
		if(n_btags >= 1){
			N_Z_loose_1btag += tot_weight;
			N_Z_loose_1btag_weighted += tot_weight_gen;
		}
		if(n_btags >= 2){
			N_Z_loose_2btag += tot_weight;
			N_Z_loose_2btag_weighted += tot_weight_gen;
		}

		bool is_ttbb = 0;
		bool is_ttb = 0;
		bool is_tt2b = 0;

		// Checking ttjets category = ttbb, ttb, tt2b, ttcc, ttlf
		if(ttHf_cat != -1){
			double mod_ttHFcat = ttHf_cat%100;
			if( (mod_ttHFcat >= 53) && (mod_ttHFcat <= 55) ){
				is_ttbb = 1;
				N_Z_ttbb_loose += tot_weight;
				N_Z_ttbb_loose_weighted += tot_weight_gen;
			}
			else if( mod_ttHFcat == 52  ){
				is_tt2b = 1;
				N_Z_tt2b_loose += tot_weight;
				N_Z_tt2b_loose_weighted += tot_weight_gen;
			}
			else if( mod_ttHFcat == 51  ){
				is_ttb = 1;
				N_Z_ttb_loose += tot_weight;
				N_Z_ttb_loose_weighted += tot_weight_gen;
			}
			else if( (mod_ttHFcat >= 41) && (mod_ttHFcat <= 45) ){
				N_Z_ttcc_loose += tot_weight;
				N_Z_ttcc_loose_weighted += tot_weight_gen;
			}
			else if ( mod_ttHFcat == 0 ){
				N_Z_ttlf_loose += tot_weight;
				N_Z_ttlf_loose_weighted += tot_weight_gen;
			}
		}

		// Filling Z_Loose Histograms
		mll_Z_loose->Fill(mll, tot_weight);
		mll_Z_loose_weighted->Fill(mll, tot_weight_gen);
		njets_btags_Z_loose_total->Fill(n_jets, n_btags, tot_weight);
		njets_btags_Z_loose_total_weighted->Fill(n_jets, n_btags, tot_weight_gen);
		njets_bjets_Z_loose_total->Fill(n_jets, n_bjets, tot_weight);
		njets_bjets_Z_loose_total_weighted->Fill(n_jets, n_bjets, tot_weight_gen);
		nbjets_btags_Z_loose_total->Fill(n_bjets, n_btags, tot_weight);
		nbjets_btags_Z_loose_total_weighted->Fill(n_bjets, n_btags, tot_weight_gen);
		fill_acc_histo(njets_btags_Z_loose_total_acc, 2, n_jets, 0, n_btags, tot_weight);
		fill_acc_histo(njets_btags_Z_loose_total_weighted_acc, 2, n_jets, 0, n_btags, tot_weight_gen);
		fill_acc_histo(njets_bjets_Z_loose_total_acc, 2, n_jets, 0, n_bjets, tot_weight);
		fill_acc_histo(njets_bjets_Z_loose_total_weighted_acc, 2, n_jets, 0, n_bjets, tot_weight_gen);
		fill_acc_histo(nbjets_btags_Z_loose_total_acc, 0, n_bjets, 0, n_btags, tot_weight);
		fill_acc_histo(nbjets_btags_Z_loose_total_weighted_acc, 0, n_bjets, 0, n_btags, tot_weight_gen);
		if(is_ttbb){
			njets_btags_Z_loose_ttbb->Fill(n_jets, n_btags, tot_weight);
			njets_btags_Z_loose_ttbb_weighted->Fill(n_jets, n_btags, tot_weight_gen);
			fill_acc_histo(njets_btags_Z_loose_ttbb_acc, 2, n_jets, 0, n_btags, tot_weight);
			fill_acc_histo(njets_btags_Z_loose_ttbb_weighted_acc, 2, n_jets, 0, n_btags, tot_weight_gen);
			njets_bjets_Z_loose_ttbb->Fill(n_jets, n_bjets, tot_weight);
			njets_bjets_Z_loose_ttbb_weighted->Fill(n_jets, n_bjets, tot_weight_gen);
			nbjets_btags_Z_loose_ttbb->Fill(n_bjets, n_btags, tot_weight);
			nbjets_btags_Z_loose_ttbb_weighted->Fill(n_bjets, n_btags, tot_weight_gen);
			fill_acc_histo(njets_bjets_Z_loose_ttbb_acc, 2, n_jets, 0, n_bjets, tot_weight);
			fill_acc_histo(njets_bjets_Z_loose_ttbb_weighted_acc, 2, n_jets, 0, n_bjets, tot_weight_gen);
			fill_acc_histo(nbjets_btags_Z_loose_ttbb_acc, 0, n_bjets, 0, n_btags, tot_weight);
			fill_acc_histo(nbjets_btags_Z_loose_ttbb_weighted_acc, 0, n_bjets, 0, n_btags, tot_weight_gen);
		}
		if(is_ttb){
			njets_btags_Z_loose_ttb->Fill(n_jets, n_btags, tot_weight);
			njets_btags_Z_loose_ttb_weighted->Fill(n_jets, n_btags, tot_weight_gen);
			fill_acc_histo(njets_btags_Z_loose_ttb_acc, 2, n_jets, 0, n_btags, tot_weight);
			fill_acc_histo(njets_btags_Z_loose_ttb_weighted_acc, 2, n_jets, 0, n_btags, tot_weight_gen);
			njets_bjets_Z_loose_ttb->Fill(n_jets, n_bjets, tot_weight);
			njets_bjets_Z_loose_ttb_weighted->Fill(n_jets, n_bjets, tot_weight_gen);
			nbjets_btags_Z_loose_ttb->Fill(n_bjets, n_btags, tot_weight);
			nbjets_btags_Z_loose_ttb_weighted->Fill(n_bjets, n_btags, tot_weight_gen);
			fill_acc_histo(njets_bjets_Z_loose_ttb_acc, 2, n_jets, 0, n_bjets, tot_weight);
			fill_acc_histo(njets_bjets_Z_loose_ttb_weighted_acc, 2, n_jets, 0, n_bjets, tot_weight_gen);
			fill_acc_histo(nbjets_btags_Z_loose_ttb_acc, 0, n_bjets, 0, n_btags, tot_weight);
			fill_acc_histo(nbjets_btags_Z_loose_ttb_weighted_acc, 0, n_bjets, 0, n_btags, tot_weight_gen);
		}
		if(is_tt2b){
			njets_btags_Z_loose_tt2b->Fill(n_jets, n_btags, tot_weight);
			njets_btags_Z_loose_tt2b_weighted->Fill(n_jets, n_btags, tot_weight_gen);
			fill_acc_histo(njets_btags_Z_loose_tt2b_acc, 2, n_jets, 0, n_btags, tot_weight);
			fill_acc_histo(njets_btags_Z_loose_tt2b_weighted_acc, 2, n_jets, 0, n_btags, tot_weight_gen);
			njets_bjets_Z_loose_tt2b->Fill(n_jets, n_bjets, tot_weight);
			njets_bjets_Z_loose_tt2b_weighted->Fill(n_jets, n_bjets, tot_weight_gen);
			nbjets_btags_Z_loose_tt2b->Fill(n_bjets, n_btags, tot_weight);
			nbjets_btags_Z_loose_tt2b_weighted->Fill(n_bjets, n_btags, tot_weight_gen);
			fill_acc_histo(njets_bjets_Z_loose_tt2b_acc, 2, n_jets, 0, n_bjets, tot_weight);
			fill_acc_histo(njets_bjets_Z_loose_tt2b_weighted_acc, 2, n_jets, 0, n_bjets, tot_weight_gen);
			fill_acc_histo(nbjets_btags_Z_loose_tt2b_acc, 0, n_bjets, 0, n_btags, tot_weight);
			fill_acc_histo(nbjets_btags_Z_loose_tt2b_weighted_acc, 0, n_bjets, 0, n_btags, tot_weight_gen);
		}

		// Counting Tight Z events
		if( mll < 88 || mll > 94 )
			continue;

		N_Z_tight_0btag += tot_weight;
		N_Z_tight_0btag_weighted += tot_weight_gen;
		if(n_btags >= 1){
			N_Z_tight_1btag += tot_weight;
			N_Z_tight_1btag_weighted += tot_weight_gen;
		}
		if(n_btags >= 2){
			N_Z_tight_2btag += tot_weight;
			N_Z_tight_2btag_weighted += tot_weight_gen;
		}

		is_ttbb = 0;
		is_ttb = 0;
		is_tt2b = 0;

		// Checking ttjets category = ttbb, ttb, tt2b, ttcc, ttlf
		if(ttHf_cat != -1){
			double mod_ttHFcat = ttHf_cat%100;
			if( (mod_ttHFcat >= 53) && (mod_ttHFcat <= 55) ){
				is_ttbb = 1;
				N_Z_ttbb_tight += tot_weight;
				N_Z_ttbb_tight_weighted += tot_weight_gen;
			}
			else if( mod_ttHFcat == 52  ){
				is_tt2b = 1;
				N_Z_tt2b_tight += tot_weight;
				N_Z_tt2b_tight_weighted += tot_weight_gen;
			}
			else if( mod_ttHFcat == 51  ){
				is_ttb = 1;
				N_Z_ttb_tight += tot_weight;
				N_Z_ttb_tight_weighted += tot_weight_gen;
			}
			else if( (mod_ttHFcat >= 41) && (mod_ttHFcat <= 45) ){
				N_Z_ttcc_tight += tot_weight;
				N_Z_ttcc_tight_weighted += tot_weight_gen;
			}
			else if ( mod_ttHFcat == 0 ){
				N_Z_ttlf_tight += tot_weight;
				N_Z_ttlf_tight_weighted += tot_weight_gen;
			}
		}

		// Filling Z_tight Histograms
		mll_Z_tight->Fill(mll, tot_weight);
		mll_Z_tight_weighted->Fill(mll, tot_weight_gen);
		njets_btags_Z_tight_total->Fill(n_jets, n_btags, tot_weight);
		njets_btags_Z_tight_total_weighted->Fill(n_jets, n_btags, tot_weight_gen);
		njets_bjets_Z_tight_total->Fill(n_jets, n_bjets, tot_weight);
		njets_bjets_Z_tight_total_weighted->Fill(n_jets, n_bjets, tot_weight_gen);
		nbjets_btags_Z_tight_total->Fill(n_bjets, n_btags, tot_weight);
		nbjets_btags_Z_tight_total_weighted->Fill(n_bjets, n_btags, tot_weight_gen);
		fill_acc_histo(njets_btags_Z_tight_total_acc, 2, n_jets, 0, n_btags, tot_weight);
		fill_acc_histo(njets_btags_Z_tight_total_weighted_acc, 2, n_jets, 0, n_btags, tot_weight_gen);
		fill_acc_histo(njets_bjets_Z_tight_total_acc, 2, n_jets, 0, n_bjets, tot_weight);
		fill_acc_histo(njets_bjets_Z_tight_total_weighted_acc, 2, n_jets, 0, n_bjets, tot_weight_gen);
		fill_acc_histo(nbjets_btags_Z_tight_total_acc, 0, n_bjets, 0, n_btags, tot_weight);
		fill_acc_histo(nbjets_btags_Z_tight_total_weighted_acc, 0, n_bjets, 0, n_btags, tot_weight_gen);
		if(is_ttbb){
			njets_btags_Z_tight_ttbb->Fill(n_jets, n_btags, tot_weight);
			njets_btags_Z_tight_ttbb_weighted->Fill(n_jets, n_btags, tot_weight_gen);
			fill_acc_histo(njets_btags_Z_tight_ttbb_acc, 2, n_jets, 0, n_btags, tot_weight);
			fill_acc_histo(njets_btags_Z_tight_ttbb_weighted_acc, 2, n_jets, 0, n_btags, tot_weight_gen);
			njets_bjets_Z_tight_ttbb->Fill(n_jets, n_bjets, tot_weight);
			njets_bjets_Z_tight_ttbb_weighted->Fill(n_jets, n_bjets, tot_weight_gen);
			nbjets_btags_Z_tight_ttbb->Fill(n_bjets, n_btags, tot_weight);
			nbjets_btags_Z_tight_ttbb_weighted->Fill(n_bjets, n_btags, tot_weight_gen);
			fill_acc_histo(njets_bjets_Z_tight_ttbb_acc, 2, n_jets, 0, n_bjets, tot_weight);
			fill_acc_histo(njets_bjets_Z_tight_ttbb_weighted_acc, 2, n_jets, 0, n_bjets, tot_weight_gen);
			fill_acc_histo(nbjets_btags_Z_tight_ttbb_acc, 0, n_bjets, 0, n_btags, tot_weight);
			fill_acc_histo(nbjets_btags_Z_tight_ttbb_weighted_acc, 0, n_bjets, 0, n_btags, tot_weight_gen);
		}
		if(is_ttb){
			njets_btags_Z_tight_ttb->Fill(n_jets, n_btags, tot_weight);
			njets_btags_Z_tight_ttb_weighted->Fill(n_jets, n_btags, tot_weight_gen);
			fill_acc_histo(njets_btags_Z_tight_ttb_acc, 2, n_jets, 0, n_btags, tot_weight);
			fill_acc_histo(njets_btags_Z_tight_ttb_weighted_acc, 2, n_jets, 0, n_btags, tot_weight_gen);
			njets_bjets_Z_tight_ttb->Fill(n_jets, n_bjets, tot_weight);
			njets_bjets_Z_tight_ttb_weighted->Fill(n_jets, n_bjets, tot_weight_gen);
			nbjets_btags_Z_tight_ttb->Fill(n_bjets, n_btags, tot_weight);
			nbjets_btags_Z_tight_ttb_weighted->Fill(n_bjets, n_btags, tot_weight_gen);
			fill_acc_histo(njets_bjets_Z_tight_ttb_acc, 2, n_jets, 0, n_bjets, tot_weight);
			fill_acc_histo(njets_bjets_Z_tight_ttb_weighted_acc, 2, n_jets, 0, n_bjets, tot_weight_gen);
			fill_acc_histo(nbjets_btags_Z_tight_ttb_acc, 0, n_bjets, 0, n_btags, tot_weight);
			fill_acc_histo(nbjets_btags_Z_tight_ttb_weighted_acc, 0, n_bjets, 0, n_btags, tot_weight_gen);
		}
		if(is_tt2b){
			njets_btags_Z_tight_tt2b->Fill(n_jets, n_btags, tot_weight);
			njets_btags_Z_tight_tt2b_weighted->Fill(n_jets, n_btags, tot_weight_gen);
			fill_acc_histo(njets_btags_Z_tight_tt2b_acc, 2, n_jets, 0, n_btags, tot_weight);
			fill_acc_histo(njets_btags_Z_tight_tt2b_weighted_acc, 2, n_jets, 0, n_btags, tot_weight_gen);
			njets_bjets_Z_tight_tt2b->Fill(n_jets, n_bjets, tot_weight);
			njets_bjets_Z_tight_tt2b_weighted->Fill(n_jets, n_bjets, tot_weight_gen);
			nbjets_btags_Z_tight_tt2b->Fill(n_bjets, n_btags, tot_weight);
			nbjets_btags_Z_tight_tt2b_weighted->Fill(n_bjets, n_btags, tot_weight_gen);
			fill_acc_histo(njets_bjets_Z_tight_tt2b_acc, 2, n_jets, 0, n_bjets, tot_weight);
			fill_acc_histo(njets_bjets_Z_tight_tt2b_weighted_acc, 2, n_jets, 0, n_bjets, tot_weight_gen);
			fill_acc_histo(nbjets_btags_Z_tight_tt2b_acc, 0, n_bjets, 0, n_btags, tot_weight);
			fill_acc_histo(nbjets_btags_Z_tight_tt2b_weighted_acc, 0, n_bjets, 0, n_btags, tot_weight_gen);
		}
		
	}   

    N_sel = N_SL + N_DL;

	// Calculating the yields in Z-region at L = 35.92 1/fb

	lumi_norm = (L*xs*1000)/((double) N_total);
	lumi_norm_weighted = (L*xs*1000)/(sum_gen_weights);

	N_Z_loose_0btag_norm = (N_Z_loose_0btag*lumi_norm);
	N_Z_tight_0btag_norm = (N_Z_tight_0btag*lumi_norm);
	N_Z_loose_1btag_norm = (N_Z_loose_1btag*lumi_norm);
	N_Z_tight_1btag_norm = (N_Z_tight_1btag*lumi_norm);
	N_Z_loose_2btag_norm = (N_Z_loose_2btag*lumi_norm);
	N_Z_tight_2btag_norm = (N_Z_tight_2btag*lumi_norm);
	N_Z_loose_0btag_weighted_norm = (N_Z_loose_0btag_weighted*lumi_norm_weighted);
	N_Z_tight_0btag_weighted_norm = (N_Z_tight_0btag_weighted*lumi_norm_weighted);
	N_Z_loose_1btag_weighted_norm = (N_Z_loose_1btag_weighted*lumi_norm_weighted);
	N_Z_tight_1btag_weighted_norm = (N_Z_tight_1btag_weighted*lumi_norm_weighted);
	N_Z_loose_2btag_weighted_norm = (N_Z_loose_2btag_weighted*lumi_norm_weighted);
	N_Z_tight_2btag_weighted_norm = (N_Z_tight_2btag_weighted*lumi_norm_weighted);

	N_Z_ttb_loose_norm = (N_Z_ttb_loose*lumi_norm);
    N_Z_tt2b_loose_norm = (N_Z_tt2b_loose*lumi_norm);
	N_Z_ttbb_loose_norm = (N_Z_ttbb_loose*lumi_norm);
	N_Z_ttcc_loose_norm = (N_Z_ttcc_loose*lumi_norm);
	N_Z_ttlf_loose_norm = (N_Z_ttlf_loose*lumi_norm);
	N_Z_ttb_tight_norm = (N_Z_ttb_tight*lumi_norm);
    N_Z_tt2b_tight_norm = (N_Z_tt2b_tight*lumi_norm);
	N_Z_ttbb_tight_norm = (N_Z_ttbb_tight*lumi_norm);
	N_Z_ttcc_tight_norm = (N_Z_ttcc_tight*lumi_norm);
	N_Z_ttlf_tight_norm = (N_Z_ttlf_tight*lumi_norm);
    N_Z_ttb_loose_weighted_norm = (N_Z_ttb_loose_weighted*lumi_norm_weighted);
    N_Z_tt2b_loose_weighted_norm = (N_Z_tt2b_loose_weighted*lumi_norm_weighted);
    N_Z_ttbb_loose_weighted_norm = (N_Z_ttbb_loose_weighted*lumi_norm_weighted);
    N_Z_ttcc_loose_weighted_norm = (N_Z_ttcc_loose_weighted*lumi_norm_weighted);
    N_Z_ttlf_loose_weighted_norm = (N_Z_ttlf_loose_weighted*lumi_norm_weighted);
    N_Z_ttb_tight_weighted_norm = (N_Z_ttb_tight_weighted*lumi_norm_weighted);
    N_Z_tt2b_tight_weighted_norm = (N_Z_tt2b_tight_weighted*lumi_norm_weighted);
    N_Z_ttbb_tight_weighted_norm = (N_Z_ttbb_tight_weighted*lumi_norm_weighted);
    N_Z_ttcc_tight_weighted_norm = (N_Z_ttcc_tight_weighted*lumi_norm_weighted);
    N_Z_ttlf_tight_weighted_norm = (N_Z_ttlf_tight_weighted*lumi_norm_weighted);

	// Scaling Histograms according to L = 35.92 1/fb

	mll_Z_loose->Scale(lumi_norm);
	mll_Z_tight->Scale(lumi_norm);
	mll_Z_loose_weighted->Scale(lumi_norm_weighted);
	mll_Z_tight_weighted->Scale(lumi_norm_weighted);

	njets_btags_Z_loose_total->Scale(lumi_norm);
	njets_btags_Z_tight_total->Scale(lumi_norm);
	njets_bjets_Z_loose_total->Scale(lumi_norm);
	njets_bjets_Z_tight_total->Scale(lumi_norm);
	nbjets_btags_Z_loose_total->Scale(lumi_norm);
	nbjets_btags_Z_tight_total->Scale(lumi_norm);
	njets_btags_Z_loose_ttbb->Scale(lumi_norm);
	njets_btags_Z_tight_ttbb->Scale(lumi_norm);
	njets_bjets_Z_loose_ttbb->Scale(lumi_norm);
	njets_bjets_Z_tight_ttbb->Scale(lumi_norm);
	nbjets_btags_Z_loose_ttbb->Scale(lumi_norm);
	nbjets_btags_Z_tight_ttbb->Scale(lumi_norm);
	njets_btags_Z_loose_tt2b->Scale(lumi_norm);
	njets_btags_Z_tight_tt2b->Scale(lumi_norm);
	njets_bjets_Z_loose_tt2b->Scale(lumi_norm);
	njets_bjets_Z_tight_tt2b->Scale(lumi_norm);
	nbjets_btags_Z_loose_tt2b->Scale(lumi_norm);
	nbjets_btags_Z_tight_tt2b->Scale(lumi_norm);
	njets_btags_Z_loose_ttb->Scale(lumi_norm);
	njets_btags_Z_tight_ttb->Scale(lumi_norm);
	njets_bjets_Z_loose_ttb->Scale(lumi_norm);
	njets_bjets_Z_tight_ttb->Scale(lumi_norm);
	nbjets_btags_Z_loose_ttb->Scale(lumi_norm);
	nbjets_btags_Z_tight_ttb->Scale(lumi_norm);
	njets_btags_Z_loose_total_weighted->Scale(lumi_norm_weighted);
	njets_btags_Z_tight_total_weighted->Scale(lumi_norm_weighted);
	njets_bjets_Z_loose_total_weighted->Scale(lumi_norm_weighted);
	njets_bjets_Z_tight_total_weighted->Scale(lumi_norm_weighted);
	nbjets_btags_Z_loose_total_weighted->Scale(lumi_norm_weighted);
	nbjets_btags_Z_tight_total_weighted->Scale(lumi_norm_weighted);
	njets_btags_Z_loose_ttbb_weighted->Scale(lumi_norm_weighted);
	njets_btags_Z_tight_ttbb_weighted->Scale(lumi_norm_weighted);
	njets_bjets_Z_loose_ttbb_weighted->Scale(lumi_norm_weighted);
	njets_bjets_Z_tight_ttbb_weighted->Scale(lumi_norm_weighted);
	nbjets_btags_Z_loose_ttbb_weighted->Scale(lumi_norm_weighted);
	nbjets_btags_Z_tight_ttbb_weighted->Scale(lumi_norm_weighted);
	njets_btags_Z_loose_tt2b_weighted->Scale(lumi_norm_weighted);
	njets_btags_Z_tight_tt2b_weighted->Scale(lumi_norm_weighted);
	njets_bjets_Z_loose_tt2b_weighted->Scale(lumi_norm_weighted);
	njets_bjets_Z_tight_tt2b_weighted->Scale(lumi_norm_weighted);
	nbjets_btags_Z_loose_tt2b_weighted->Scale(lumi_norm_weighted);
	nbjets_btags_Z_tight_tt2b_weighted->Scale(lumi_norm_weighted);
	njets_btags_Z_loose_ttb_weighted->Scale(lumi_norm_weighted);
	njets_btags_Z_tight_ttb_weighted->Scale(lumi_norm_weighted);
	njets_bjets_Z_loose_ttb_weighted->Scale(lumi_norm_weighted);
	njets_bjets_Z_tight_ttb_weighted->Scale(lumi_norm_weighted);
	nbjets_btags_Z_loose_ttb_weighted->Scale(lumi_norm_weighted);
	nbjets_btags_Z_tight_ttb_weighted->Scale(lumi_norm_weighted);
	njets_btags_Z_loose_total_acc->Scale(lumi_norm);
	njets_btags_Z_tight_total_acc->Scale(lumi_norm);
	njets_bjets_Z_loose_total_acc->Scale(lumi_norm);
	njets_bjets_Z_tight_total_acc->Scale(lumi_norm);
	nbjets_btags_Z_loose_total_acc->Scale(lumi_norm);
	nbjets_btags_Z_tight_total_acc->Scale(lumi_norm);
	njets_btags_Z_loose_ttbb_acc->Scale(lumi_norm);
	njets_btags_Z_tight_ttbb_acc->Scale(lumi_norm);
	njets_bjets_Z_loose_ttbb_acc->Scale(lumi_norm);
	njets_bjets_Z_tight_ttbb_acc->Scale(lumi_norm);
	nbjets_btags_Z_loose_ttbb_acc->Scale(lumi_norm);
	nbjets_btags_Z_tight_ttbb_acc->Scale(lumi_norm);
	njets_btags_Z_loose_tt2b_acc->Scale(lumi_norm);
	njets_btags_Z_tight_tt2b_acc->Scale(lumi_norm);
	njets_bjets_Z_loose_tt2b_acc->Scale(lumi_norm);
	njets_bjets_Z_tight_tt2b_acc->Scale(lumi_norm);
	nbjets_btags_Z_loose_tt2b_acc->Scale(lumi_norm);
	nbjets_btags_Z_tight_tt2b_acc->Scale(lumi_norm);
	njets_btags_Z_loose_ttb_acc->Scale(lumi_norm);
	njets_btags_Z_tight_ttb_acc->Scale(lumi_norm);
	njets_bjets_Z_loose_ttb_acc->Scale(lumi_norm);
	njets_bjets_Z_tight_ttb_acc->Scale(lumi_norm);
	nbjets_btags_Z_loose_ttb_acc->Scale(lumi_norm);
	nbjets_btags_Z_tight_ttb_acc->Scale(lumi_norm);
	njets_btags_Z_loose_total_weighted_acc->Scale(lumi_norm_weighted);
	njets_btags_Z_tight_total_weighted_acc->Scale(lumi_norm_weighted);
	njets_bjets_Z_loose_total_weighted_acc->Scale(lumi_norm_weighted);
	njets_bjets_Z_tight_total_weighted_acc->Scale(lumi_norm_weighted);
	nbjets_btags_Z_loose_total_weighted_acc->Scale(lumi_norm_weighted);
	nbjets_btags_Z_tight_total_weighted_acc->Scale(lumi_norm_weighted);
	njets_btags_Z_loose_ttbb_weighted_acc->Scale(lumi_norm_weighted);
	njets_btags_Z_tight_ttbb_weighted_acc->Scale(lumi_norm_weighted);
	njets_bjets_Z_loose_ttbb_weighted_acc->Scale(lumi_norm_weighted);
	njets_bjets_Z_tight_ttbb_weighted_acc->Scale(lumi_norm_weighted);
	nbjets_btags_Z_loose_ttbb_weighted_acc->Scale(lumi_norm_weighted);
	nbjets_btags_Z_tight_ttbb_weighted_acc->Scale(lumi_norm_weighted);
	njets_btags_Z_loose_tt2b_weighted_acc->Scale(lumi_norm_weighted);
	njets_btags_Z_tight_tt2b_weighted_acc->Scale(lumi_norm_weighted);
	njets_bjets_Z_loose_tt2b_weighted_acc->Scale(lumi_norm_weighted);
	njets_bjets_Z_tight_tt2b_weighted_acc->Scale(lumi_norm_weighted);
	nbjets_btags_Z_loose_tt2b_weighted_acc->Scale(lumi_norm_weighted);
	nbjets_btags_Z_tight_tt2b_weighted_acc->Scale(lumi_norm_weighted);
	njets_btags_Z_loose_ttb_weighted_acc->Scale(lumi_norm_weighted);
	njets_btags_Z_tight_ttb_weighted_acc->Scale(lumi_norm_weighted);
	njets_bjets_Z_loose_ttb_weighted_acc->Scale(lumi_norm_weighted);
	njets_bjets_Z_tight_ttb_weighted_acc->Scale(lumi_norm_weighted);
	nbjets_btags_Z_loose_ttb_weighted_acc->Scale(lumi_norm_weighted);
	nbjets_btags_Z_tight_ttb_weighted_acc->Scale(lumi_norm_weighted);


	// Calculating B-tagging and mis-tagging efficiencies

	b_effi = N_jets_b/N_jets_all;
	no_b_effi = 1 - b_effi;
	tag_effi = N_btags_all/N_jets_all;
	no_tag_effi = 1 - tag_effi;
	b_tag_effi = N_jets_b_tag/N_jets_b;
	b_no_tag_effi = 1 - b_tag_effi;
	c_tag_effi = N_jets_c_tag/N_jets_c;
	c_no_tag_effi = 1 - c_tag_effi;
	lf_tag_effi = N_jets_lf_tag/N_jets_lf;
	lf_no_tag_effi = 1 - lf_tag_effi;
	no_b_tag_effi = (N_jets_c_tag + N_jets_lf_tag ) / (N_jets_c + N_jets_lf );
	no_b_no_tag_effi = 1 - no_b_tag_effi;
	tag_b_effi = ( b_tag_effi * b_effi )/tag_effi;
	tag_no_b_effi = ( no_b_tag_effi * no_b_effi )/tag_effi;
	no_tag_b_effi = ( b_no_tag_effi * b_effi )/no_tag_effi;
	no_tag_no_b_effi = ( no_b_no_tag_effi * no_b_effi )/no_tag_effi;
	p_b_tag = N_jets_b_tag/N_btags_all;
	p_b_notag = N_jets_b_notag/N_nobtags_all;

	b_effi_weighted = N_jets_b_weighted/N_jets_all_weighted;
	no_b_effi_weighted = 1 - b_effi_weighted;
	tag_effi_weighted = N_btags_all_weighted/N_jets_all_weighted;
	no_tag_effi_weighted = 1 - tag_effi_weighted;
	b_tag_effi_weighted = N_jets_b_tag_weighted/N_jets_b_weighted;
	b_no_tag_effi_weighted = 1 - b_tag_effi_weighted;
	c_tag_effi_weighted = N_jets_c_tag_weighted/N_jets_c_weighted;
	c_no_tag_effi_weighted = 1 - c_tag_effi_weighted;
	lf_tag_effi_weighted = N_jets_lf_tag_weighted/N_jets_lf_weighted;
	lf_no_tag_effi_weighted = 1 - lf_tag_effi_weighted;
	no_b_tag_effi_weighted = (N_jets_c_tag_weighted + N_jets_lf_tag_weighted ) / (N_jets_c_weighted + N_jets_lf_weighted );
	no_b_no_tag_effi_weighted = 1 - no_b_tag_effi_weighted;
	tag_b_effi_weighted = ( b_tag_effi_weighted * b_effi_weighted )/tag_effi_weighted;
	tag_no_b_effi_weighted = ( no_b_tag_effi_weighted * no_b_effi_weighted )/tag_effi_weighted;
	no_tag_b_effi_weighted = ( b_no_tag_effi_weighted * b_effi_weighted )/no_tag_effi_weighted;
	no_tag_no_b_effi_weighted = ( no_b_no_tag_effi_weighted * no_b_effi_weighted )/no_tag_effi_weighted;

	std::cout << " Done! " << std::endl;
	fout<<"**********************************************************************************************\n\n";
	fout<<"Total No. of Events : "<<N_total<<"\n";
	fout<<"Total No. of Events passing Selection : "<<N_sel<<" , % :  "<<((double)N_sel/N_total)*100<<"\n\n";
	fout<<"Sum of Positive Generator weights of all Events: "<<sum_pos_gen_weights<<"\n";
	fout<<"Sum of Negative Generator weights of all Events: "<<sum_neg_gen_weights<<"\n";
	fout<<"Sum of Generator weights of all Events: "<<sum_gen_weights<<"\n\n";
	fout<<"Product of Generator weights of all Events: "<<product_gen_weights<<"\n\n";
	fout<<"**********************************************************************************************\n\n";
	fout<<"No. of Single Electron Events: "<<N_e<<"\n";
	fout<<"No. of Single Muon Events: "<<N_mu<<"\n";
	fout<<"No. of Double Electron Events: "<<N_ee<<"\n";
	fout<<"No. of Electron Muon Events: "<<N_emu<<"\n";
	fout<<"No. of Double Muon Events: "<<N_mumu<<"\n";
	fout<<"Total No. of Single Lepton Events: "<<N_SL<<"\n";
	fout<<"Total No. of Dilepton Events: "<<N_DL<<"\n\n";
	fout<<"**********************************************************************************************\n\n";
	fout<<"Total nr. of Z events in different categories : \n\n";
	fout<<"MC Yields only : \n\n";
	fout<<"Total weighted Loose Z-Events with >= 0 b-Tags : "<<N_Z_loose_0btag<<"\n";
	fout<<"Total gen-weighted Loose Z-Events with >= 0 b-Tags : "<<N_Z_loose_0btag_weighted<<"\n";
	fout<<"Total weighted Tight Z-Events with >= 0 b-Tags : "<<N_Z_tight_0btag<<"\n";
	fout<<"Total gen-weighted Tight Z-Events with >= 0 b-Tags : "<<N_Z_tight_0btag_weighted<<"\n\n";
	fout<<"Total weighted Loose Z-Events with >= 1 b-Tag : "<<N_Z_loose_1btag<<"\n";
	fout<<"Total gen-weighted Loose Z-Events with >= 1 b-Tag : "<<N_Z_loose_1btag_weighted<<"\n";
	fout<<"Total weighted Tight Z-Events with >= 1 b-Tag : "<<N_Z_tight_1btag<<"\n";
	fout<<"Total gen-weighted Tight Z-Events with >= 1 b-Tag : "<<N_Z_tight_1btag_weighted<<"\n\n";
	fout<<"Total weighted Loose Z-Events with >= 2 b-Tags : "<<N_Z_loose_2btag<<"\n";
	fout<<"Total gen-weighted Loose Z-Events with >= 2 b-Tags : "<<N_Z_loose_2btag_weighted<<"\n";
	fout<<"Total weighted Tight Z-Events with >= 2 b-Tags : "<<N_Z_tight_2btag<<"\n";
	fout<<"Total gen-weighted Tight Z-Events with >= 2 b-Tags : "<<N_Z_tight_2btag_weighted<<"\n\n";
	fout<<"MC Yields Normalized to L = "<<L<<" 1/fb : \n\n";
	fout<<"Total weighted Loose Z-Events with >= 0 b-Tags : "<<N_Z_loose_0btag_norm<<"\n";
	fout<<"Total gen-weighted Loose Z-Events with >= 0 b-Tags : "<<N_Z_loose_0btag_weighted_norm<<"\n";
	fout<<"Total weighted Tight Z-Events with >= 0 b-Tags : "<<N_Z_tight_0btag_norm<<"\n";
	fout<<"Total gen-weighted Tight Z-Events with >= 0 b-Tags : "<<N_Z_tight_0btag_weighted_norm<<"\n\n";
	fout<<"Total weighted Loose Z-Events with >= 1 b-Tag : "<<N_Z_loose_1btag_norm<<"\n";
	fout<<"Total gen-weighted Loose Z-Events with >= 1 b-Tag : "<<N_Z_loose_1btag_weighted_norm<<"\n";
	fout<<"Total weighted Tight Z-Events with >= 1 b-Tag : "<<N_Z_tight_1btag_norm<<"\n";
	fout<<"Total gen-weighted Tight Z-Events with >= 1 b-Tag : "<<N_Z_tight_1btag_weighted_norm<<"\n\n";
	fout<<"Total weighted Loose Z-Events with >= 2 b-Tags : "<<N_Z_loose_2btag_norm<<"\n";
	fout<<"Total gen-weighted Loose Z-Events with >= 2 b-Tags : "<<N_Z_loose_2btag_weighted_norm<<"\n";
	fout<<"Total weighted Tight Z-Events with >= 2 b-Tags : "<<N_Z_tight_2btag_norm<<"\n";
	fout<<"Total gen-weighted Tight Z-Events with >= 2 b-Tags : "<<N_Z_tight_2btag_weighted_norm<<"\n\n";
	fout<<"**********************************************************************************************\n\n";
	fout<<"Nr. of ttbb Z events with >= 0 b-Tags : \n\n";
	fout<<"MC Yields only : \n\n";
	fout<<"Total weighted Loose ttbb Z-Events : "<<N_Z_ttbb_loose<<"\n";
	fout<<"Total gen-weighted Loose ttbb Z-Events : "<<N_Z_ttbb_loose_weighted<<"\n";
	fout<<"Total weighted Tight ttbb Z-Events : "<<N_Z_ttbb_tight<<"\n";
	fout<<"Total gen-weighted Tight ttbb Z-Events : "<<N_Z_ttbb_tight_weighted<<"\n\n";
	fout<<"MC Yields Normalized to L = "<<L<<" 1/fb : \n\n";
	fout<<"Total weighted Loose ttbb Z-Events : "<<N_Z_ttbb_loose_norm<<"\n";
	fout<<"Total gen-weighted Loose ttbb Z-Events : "<<N_Z_ttbb_loose_weighted_norm<<"\n";
	fout<<"Total weighted Tight ttbb Z-Events : "<<N_Z_ttbb_tight_norm<<"\n";
	fout<<"Total gen-weighted Tight ttbb Z-Events : "<<N_Z_ttbb_tight_weighted_norm<<"\n\n";
	fout<<"**********************************************************************************************\n\n";
	fout<<"Probabilities/Efficiencies with b-Tagging and mis-Tagging : \n\n";
	fout<<"Probability of a jet being a b-jet (weighted), P(b) : "<<b_effi<<"\n";
	fout<<"Probability of a jet being not a b-jet (weighted), P(not b) : "<<no_b_effi<<"\n";
	fout<<"Probability of a jet being tagged (weighted), P(tag) : "<<tag_effi<<"\n";
	fout<<"Probability of a jet being not tagged (weighted), P(not tag) : "<<no_tag_effi<<"\n";
	fout<<"b-Jet b-Tagged Efficiency (weighted), P(tag|b) : "<<b_tag_effi<<"\n";
	fout<<"b-Jet not b-Tagged Efficiency (weighted), P(not tag|b) : "<<b_no_tag_effi<<"\n";
	fout<<"c-Jet b-Tagged Efficiency (weighted), P(tag|c) : "<<c_tag_effi<<"\n";
	fout<<"c-Jet not b-Tagged Efficiency (weighted), P(not tag|c) : "<<c_no_tag_effi<<"\n";
	fout<<"lf-Jet b-Tagged Efficiency (weighted), P(tag|lf) : "<<lf_tag_effi<<"\n";
	fout<<"lf-Jet not b-Tagged Efficiency (weighted), P(not tag|lf) : "<<lf_no_tag_effi<<"\n";
	fout<<"Not b-Jet b-Tagged Efficiency (weighted), P(tag|not b) : "<<no_b_tag_effi<<"\n";
	fout<<"Not b-Jet not b-Tagged Efficiency (weighted), P(not tag|not b) : "<<no_b_no_tag_effi<<"\n";
	fout<<"b-Tagged b-Jet Efficiency (weighted), P(b|tag) : "<<tag_b_effi<<"\n";
	fout<<"b-Tagged not b-Jet Efficiency (weighted), P(not b|tag) : "<<tag_no_b_effi<<"\n";
	fout<<"Not b-Tagged b-Jet Efficiency (weighted), P(b|not tag) : "<<no_tag_b_effi<<"\n";
	fout<<"Not b-Tagged not b-Jet Efficiency (weighted), P(not b|not tag) : "<<no_tag_no_b_effi<<"\n\n";

	fout<<"Probability of a jet being a b-jet (gen-weighted), P(b) : "<<b_effi_weighted<<"\n";
	fout<<"Probability of a jet being not a b-jet (gen-weighted), P(not b) : "<<no_b_effi_weighted<<"\n";
	fout<<"Probability of a jet being tagged (gen-weighted), P(tag) : "<<tag_effi_weighted<<"\n";
	fout<<"Probability of a jet being not tagged (gen-weighted), P(not tag) : "<<no_tag_effi_weighted<<"\n";
	fout<<"b-Jet b-Tagged Efficiency (gen-weighted), P(tag|b) : "<<b_tag_effi_weighted<<"\n";
	fout<<"b-Jet not b-Tagged Efficiency (gen-weighted), P(not tag|b) : "<<b_no_tag_effi_weighted<<"\n";
	fout<<"c-Jet b-Tagged Efficiency (gen-weighted), P(tag|c) : "<<c_tag_effi_weighted<<"\n";
	fout<<"c-Jet not b-Tagged Efficiency (gen-weighted), P(not tag|c) : "<<c_no_tag_effi_weighted<<"\n";
	fout<<"lf-Jet b-Tagged Efficiency (gen-weighted), P(tag|lf) : "<<lf_tag_effi_weighted<<"\n";
	fout<<"lf-Jet not b-Tagged Efficiency (gen-weighted), P(not tag|lf) : "<<lf_no_tag_effi_weighted<<"\n";
	fout<<"Not b-Jet b-Tagged Efficiency (gen-weighted), P(tag|not b) : "<<no_b_tag_effi_weighted<<"\n";
	fout<<"Not b-Jet not b-Tagged Efficiency (gen-weighted), P(not tag|not b) : "<<no_b_no_tag_effi_weighted<<"\n";
	fout<<"b-Tagged b-Jet Efficiency (gen-weighted), P(b|tag) : "<<tag_b_effi_weighted<<"\n";
	fout<<"b-Tagged not b-Jet Efficiency (gen-weighted), P(not b|tag) : "<<tag_no_b_effi_weighted<<"\n";
	fout<<"Not b-Tagged b-Jet Efficiency (gen-weighted), P(b|not tag) : "<<no_tag_b_effi_weighted<<"\n";
	fout<<"Not b-Tagged not b-Jet Efficiency (gen-weighted), P(not b|not tag) : "<<no_tag_no_b_effi_weighted<<"\n\n";
	fout<<"**********************************************************************************************\n\n";
	fout<<"p_b, P(tag|b) : "<<b_tag_effi<<"\n";
	fout<<"p_b_bar, P(tag|not b) : "<<no_b_tag_effi<<"\n\n";
	fout<<"P(b|tag) : "<<tag_b_effi<<"\n";
	fout<<"P(b|not tag) : "<<no_tag_b_effi<<"\n\n";
	fout<<"**********************************************************************************************\n\n";
	fout<<"Alternate way (Direct calculation) :\n\n";
	fout<<"P(b|tag) : "<<p_b_tag<<"\n";
	fout<<"P(b|not tag) : "<<p_b_notag<<"\n\n";
	fout<<"**********************************************************************************************\n\n";
	histofile.Write();
	histofile.Close();
	fout.close();

    return;
}


