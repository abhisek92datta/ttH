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
#include "TEfficiency.h"


void yields_2D_bprob() {

	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();

	// ttjets

    TFile *f1 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttjets_all.root");

	TH1D *mll_Z_loose_ttjets = (TH1D*)f1->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_ttjets = (TH1D*)f1->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_ttjets = (TH1D*)f1->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_ttjets = (TH1D*)f1->Get("mll_Z_tight_weighted");
	TEfficiency *b_tag_effi_pt_ttjets = (TEfficiency*)f1->Get("b_tag_effi_pt");
	TEfficiency *b_tag_effi_eta_ttjets = (TEfficiency*)f1->Get("b_tag_effi_eta");
	TEfficiency *c_tag_effi_pt_ttjets = (TEfficiency*)f1->Get("c_tag_effi_pt");
	TEfficiency *c_tag_effi_eta_ttjets = (TEfficiency*)f1->Get("c_tag_effi_eta");
	TEfficiency *lf_tag_effi_pt_ttjets = (TEfficiency*)f1->Get("lf_tag_effi_pt");
	TEfficiency *lf_tag_effi_eta_ttjets = (TEfficiency*)f1->Get("lf_tag_effi_eta");

    TH2D *njets_btags_Z_loose_total_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_total_weighted_acc");
	TH2D *njets_bjets_Z_loose_total_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_total");
	TH2D *njets_bjets_Z_tight_total_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_total");
	TH2D *njets_bjets_Z_loose_total_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_total_acc");
	TH2D *njets_bjets_Z_tight_total_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_total_acc");
	TH2D *njets_bjets_Z_loose_total_weighted_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_total_weighted");
	TH2D *njets_bjets_Z_tight_total_weighted_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_total_weighted");
	TH2D *njets_bjets_Z_loose_total_weighted_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_total_weighted_acc");
	TH2D *njets_bjets_Z_tight_total_weighted_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_total_weighted_acc");
	TH2D *nbjets_btags_Z_loose_total_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_total");
	TH2D *nbjets_btags_Z_tight_total_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_total");
	TH2D *nbjets_btags_Z_loose_total_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_total_acc");
	TH2D *nbjets_btags_Z_tight_total_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_total_acc");
	TH2D *nbjets_btags_Z_loose_total_weighted_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_total_weighted");
	TH2D *nbjets_btags_Z_tight_total_weighted_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_total_weighted");
	TH2D *nbjets_btags_Z_loose_total_weighted_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_total_weighted_acc");
	TH2D *nbjets_btags_Z_tight_total_weighted_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_total_weighted_acc");
	TH2D *njets_bjets_Z_loose_ttbb_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_ttbb");
	TH2D *njets_bjets_Z_tight_ttbb_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_ttbb");
	TH2D *njets_bjets_Z_loose_ttbb_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_ttbb_acc");
	TH2D *njets_bjets_Z_tight_ttbb_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_ttbb_acc");
	TH2D *njets_bjets_Z_loose_ttbb_weighted_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_ttbb_weighted");
	TH2D *njets_bjets_Z_tight_ttbb_weighted_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_ttbb_weighted");
	TH2D *njets_bjets_Z_loose_ttbb_weighted_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_ttbb_weighted_acc");
	TH2D *njets_bjets_Z_tight_ttbb_weighted_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_ttbb_weighted_acc");
	TH2D *nbjets_btags_Z_loose_ttbb_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_ttbb");
	TH2D *nbjets_btags_Z_tight_ttbb_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_ttbb");
	TH2D *nbjets_btags_Z_loose_ttbb_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_ttbb_acc");
	TH2D *nbjets_btags_Z_tight_ttbb_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_ttbb_acc");
	TH2D *nbjets_btags_Z_loose_ttbb_weighted_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_ttbb_weighted");
	TH2D *nbjets_btags_Z_tight_ttbb_weighted_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_ttbb_weighted");
	TH2D *nbjets_btags_Z_loose_ttbb_weighted_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_ttbb_weighted_acc");
	TH2D *nbjets_btags_Z_tight_ttbb_weighted_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_ttbb_weighted_acc");
	TH2D *njets_bjets_Z_loose_ttb_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_ttb");
	TH2D *njets_bjets_Z_tight_ttb_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_ttb");
	TH2D *njets_bjets_Z_loose_ttb_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_ttb_acc");
	TH2D *njets_bjets_Z_tight_ttb_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_ttb_acc");
	TH2D *njets_bjets_Z_loose_ttb_weighted_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_ttb_weighted");
	TH2D *njets_bjets_Z_tight_ttb_weighted_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_ttb_weighted");
	TH2D *njets_bjets_Z_loose_ttb_weighted_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_ttb_weighted_acc");
	TH2D *njets_bjets_Z_tight_ttb_weighted_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_ttb_weighted_acc");
	TH2D *nbjets_btags_Z_loose_ttb_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_ttb");
	TH2D *nbjets_btags_Z_tight_ttb_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_ttb");
	TH2D *nbjets_btags_Z_loose_ttb_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_ttb_acc");
	TH2D *nbjets_btags_Z_tight_ttb_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_ttb_acc");
	TH2D *nbjets_btags_Z_loose_ttb_weighted_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_ttb_weighted");
	TH2D *nbjets_btags_Z_tight_ttb_weighted_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_ttb_weighted");
	TH2D *nbjets_btags_Z_loose_ttb_weighted_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_ttb_weighted_acc");
	TH2D *nbjets_btags_Z_tight_ttb_weighted_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_ttb_weighted_acc");
	TH2D *njets_bjets_Z_loose_tt2b_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_tt2b");
	TH2D *njets_bjets_Z_tight_tt2b_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_tt2b");
	TH2D *njets_bjets_Z_loose_tt2b_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_tt2b_acc");
	TH2D *njets_bjets_Z_tight_tt2b_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_tt2b_acc");
	TH2D *njets_bjets_Z_loose_tt2b_weighted_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_tt2b_weighted");
	TH2D *njets_bjets_Z_tight_tt2b_weighted_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_tt2b_weighted");
	TH2D *njets_bjets_Z_loose_tt2b_weighted_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_tt2b_weighted_acc");
	TH2D *njets_bjets_Z_tight_tt2b_weighted_acc_ttjets = (TH2D*)f1->Get("njets_bjets_Z_tight_tt2b_weighted_acc");
	TH2D *nbjets_btags_Z_loose_tt2b_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_tt2b");
	TH2D *nbjets_btags_Z_tight_tt2b_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_tt2b");
	TH2D *nbjets_btags_Z_loose_tt2b_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_tt2b_acc");
	TH2D *nbjets_btags_Z_tight_tt2b_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_tt2b_acc");
	TH2D *nbjets_btags_Z_loose_tt2b_weighted_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_tt2b_weighted");
	TH2D *nbjets_btags_Z_tight_tt2b_weighted_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_tt2b_weighted");
	TH2D *nbjets_btags_Z_loose_tt2b_weighted_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_loose_tt2b_weighted_acc");
	TH2D *nbjets_btags_Z_tight_tt2b_weighted_acc_ttjets = (TH2D*)f1->Get("nbjets_btags_Z_tight_tt2b_weighted_acc");
	TH2D *njets_btags_Z_loose_ttbb_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_ttbb");
	TH2D *njets_btags_Z_tight_ttbb_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_ttbb");
	TH2D *njets_btags_Z_loose_ttbb_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_ttbb_acc");
	TH2D *njets_btags_Z_tight_ttbb_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_ttbb_acc");
	TH2D *njets_btags_Z_loose_ttbb_weighted_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_ttbb_weighted");
	TH2D *njets_btags_Z_tight_ttbb_weighted_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_ttbb_weighted");
	TH2D *njets_btags_Z_loose_ttbb_weighted_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_ttbb_weighted_acc");
	TH2D *njets_btags_Z_tight_ttbb_weighted_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_ttbb_weighted_acc");
	TH2D *njets_btags_Z_loose_ttb_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_ttb");
	TH2D *njets_btags_Z_tight_ttb_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_ttb");
	TH2D *njets_btags_Z_loose_ttb_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_ttb_acc");
	TH2D *njets_btags_Z_tight_ttb_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_ttb_acc");
	TH2D *njets_btags_Z_loose_ttb_weighted_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_ttb_weighted");
	TH2D *njets_btags_Z_tight_ttb_weighted_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_ttb_weighted");
	TH2D *njets_btags_Z_loose_ttb_weighted_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_ttb_weighted_acc");
	TH2D *njets_btags_Z_tight_ttb_weighted_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_ttb_weighted_acc");
	TH2D *njets_btags_Z_loose_tt2b_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_tt2b");
	TH2D *njets_btags_Z_tight_tt2b_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_tt2b");
	TH2D *njets_btags_Z_loose_tt2b_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_tt2b_acc");
	TH2D *njets_btags_Z_tight_tt2b_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_tt2b_acc");
	TH2D *njets_btags_Z_loose_tt2b_weighted_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_tt2b_weighted");
	TH2D *njets_btags_Z_tight_tt2b_weighted_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_tt2b_weighted");
	TH2D *njets_btags_Z_loose_tt2b_weighted_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_tt2b_weighted_acc");
	TH2D *njets_btags_Z_tight_tt2b_weighted_acc_ttjets = (TH2D*)f1->Get("njets_btags_Z_tight_tt2b_weighted_acc");

	mll_Z_loose_ttjets->SetName("mll_Z_loose_ttjets");
	mll_Z_loose_ttjets->SetTitle("MC ttjets : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_ttjets->SetName("mll_Z_loose_weighted_ttjets");
	mll_Z_loose_weighted_ttjets->SetTitle("MC ttjets : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_ttjets->SetName("mll_Z_tight_ttjets");
	mll_Z_tight_ttjets->SetTitle("MC ttjets : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_ttjets->SetName("mll_Z_tight_weighted_ttjets");
	mll_Z_tight_weighted_ttjets->SetTitle("MC ttjets : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");
	b_tag_effi_pt_ttjets->SetName("b_tag_effi_pt_ttjets");
	b_tag_effi_pt_ttjets->SetTitle("MC ttjets : B-Tagging Efficiency for b-jets vs Jet Pt for 76 < M(ll) < 106");
	b_tag_effi_eta_ttjets->SetName("b_tag_effi_eta_ttjets");
	b_tag_effi_eta_ttjets->SetTitle("MC ttjets : B-Tagging Efficiency for b-jets vs Jet Eta for 76 < M(ll) < 106");
	c_tag_effi_pt_ttjets->SetName("c_tag_effi_pt_ttjets");
	c_tag_effi_pt_ttjets->SetTitle("MC ttjets : B-MisTagging Efficiency for c-jets vs Jet Pt for 76 < M(ll) < 106");
	c_tag_effi_eta_ttjets->SetName("c_tag_effi_eta_ttjets");
	c_tag_effi_eta_ttjets->SetTitle("MC ttjets : B-MisTagging Efficiency for c-jets vs Jet Eta for 76 < M(ll) < 106");
	lf_tag_effi_pt_ttjets->SetName("lf_tag_effi_pt_ttjets");
	lf_tag_effi_pt_ttjets->SetTitle("MC ttjets : B-MisTagging Efficiency for lf-jets vs Jet Pt for 76 < M(ll) < 106");
	lf_tag_effi_eta_ttjets->SetName("lf_tag_effi_eta_ttjets");
	lf_tag_effi_eta_ttjets->SetTitle("MC ttjets : B-MisTagging Efficiency for lf-jets vs Jet Eta for 76 < M(ll) < 106");

	njets_btags_Z_loose_total_ttjets->SetName("njets_btags_Z_loose_total_ttjets");
	njets_btags_Z_loose_total_ttjets->SetTitle("MC ttjets : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_ttjets->SetName("njets_btags_Z_tight_total_ttjets");
	njets_btags_Z_tight_total_ttjets->SetTitle("MC ttjets : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_ttjets->SetName("njets_btags_Z_loose_total_acc_ttjets");
	njets_btags_Z_loose_total_acc_ttjets->SetTitle("MC ttjets : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_ttjets->SetName("njets_btags_Z_tight_total_acc_ttjets");
	njets_btags_Z_tight_total_acc_ttjets->SetTitle("MC ttjets : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_ttjets->SetName("njets_btags_Z_loose_total_weighted_ttjets");
	njets_btags_Z_loose_total_weighted_ttjets->SetTitle("MC ttjets : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_ttjets->SetName("njets_btags_Z_tight_total_weighted_ttjets");
	njets_btags_Z_tight_total_weighted_ttjets->SetTitle("MC ttjets : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_ttjets->SetName("njets_btags_Z_loose_total_weighted_acc_ttjets");
	njets_btags_Z_loose_total_weighted_acc_ttjets->SetTitle("MC ttjets : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_ttjets->SetName("njets_btags_Z_tight_total_weighted_acc_ttjets");
	njets_btags_Z_tight_total_weighted_acc_ttjets->SetTitle("MC ttjets : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_total_ttjets->SetName("njets_bjets_Z_loose_total_ttjets");
	njets_bjets_Z_loose_total_ttjets->SetTitle("MC ttjets : Total Nr. of Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_total_ttjets->SetName("njets_bjets_Z_tight_total_ttjets");
	njets_bjets_Z_tight_total_ttjets->SetTitle("MC ttjets : Total Nr. of Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_total_acc_ttjets->SetName("njets_bjets_Z_loose_total_acc_ttjets");
	njets_bjets_Z_loose_total_acc_ttjets->SetTitle("MC ttjets : Total Nr. of Accumulative Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_total_acc_ttjets->SetName("njets_bjets_Z_tight_total_acc_ttjets");
	njets_bjets_Z_tight_total_acc_ttjets->SetTitle("MC ttjets : Total Nr. of Accumulative Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_total_weighted_ttjets->SetName("njets_bjets_Z_loose_total_weighted_ttjets");
	njets_bjets_Z_loose_total_weighted_ttjets->SetTitle("MC ttjets : Total Nr. of Weighted Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_total_weighted_ttjets->SetName("njets_bjets_Z_tight_total_weighted_ttjets");
	njets_bjets_Z_tight_total_weighted_ttjets->SetTitle("MC ttjets : Total Nr. of Weighted Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_total_weighted_acc_ttjets->SetName("njets_bjets_Z_loose_total_weighted_acc_ttjets");
	njets_bjets_Z_loose_total_weighted_acc_ttjets->SetTitle("MC ttjets : Total Nr. of Accumulative Weighted Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_total_weighted_acc_ttjets->SetName("njets_bjets_Z_tight_total_weighted_acc_ttjets");
	njets_bjets_Z_tight_total_weighted_acc_ttjets->SetTitle("MC ttjets : Total Nr. of Accumulative Weighted Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_total_ttjets->SetName("nbjets_btags_Z_loose_total_ttjets");
	nbjets_btags_Z_loose_total_ttjets->SetTitle("MC ttjets : Total Nr. of Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_total_ttjets->SetName("nbjets_btags_Z_tight_total_ttjets");
	nbjets_btags_Z_tight_total_ttjets->SetTitle("MC ttjets : Total Nr. of Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_total_acc_ttjets->SetName("nbjets_btags_Z_loose_total_acc_ttjets");
	nbjets_btags_Z_loose_total_acc_ttjets->SetTitle("MC ttjets : Total Nr. of Accumulative Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_total_acc_ttjets->SetName("nbjets_btags_Z_tight_total_acc_ttjets");
	nbjets_btags_Z_tight_total_acc_ttjets->SetTitle("MC ttjets : Total Nr. of Accumulative Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_total_weighted_ttjets->SetName("nbjets_btags_Z_loose_total_weighted_ttjets");
	nbjets_btags_Z_loose_total_weighted_ttjets->SetTitle("MC ttjets : Total Nr. of Weighted Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_total_weighted_ttjets->SetName("nbjets_btags_Z_tight_total_weighted_ttjets");
	nbjets_btags_Z_tight_total_weighted_ttjets->SetTitle("MC ttjets : Total Nr. of Weighted Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_total_weighted_acc_ttjets->SetName("nbjets_btags_Z_loose_total_weighted_acc_ttjets");
	nbjets_btags_Z_loose_total_weighted_acc_ttjets->SetTitle("MC ttjets : Total Nr. of Accumulative Weighted Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_total_weighted_acc_ttjets->SetName("nbjets_btags_Z_tight_total_weighted_acc_ttjets");
	nbjets_btags_Z_tight_total_weighted_acc_ttjets->SetTitle("MC ttjets : Total Nr. of Accumulative Weighted Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_ttbb_ttjets->SetName("njets_bjets_Z_loose_ttbb_ttjets");
	njets_bjets_Z_loose_ttbb_ttjets->SetTitle("MC ttjets : Nr. of ttbb Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_ttbb_ttjets->SetName("njets_bjets_Z_tight_ttbb_ttjets");
	njets_bjets_Z_tight_ttbb_ttjets->SetTitle("MC ttjets : Nr. of ttbb Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_ttbb_acc_ttjets->SetName("njets_bjets_Z_loose_ttbb_acc_ttjets");
	njets_bjets_Z_loose_ttbb_acc_ttjets->SetTitle("MC ttjets : Nr. of ttbb Accumulative Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_ttbb_acc_ttjets->SetName("njets_bjets_Z_tight_ttbb_acc_ttjets");
	njets_bjets_Z_tight_ttbb_acc_ttjets->SetTitle("MC ttjets : Nr. of ttbb Accumulative Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_ttbb_weighted_ttjets->SetName("njets_bjets_Z_loose_ttbb_weighted_ttjets");
	njets_bjets_Z_loose_ttbb_weighted_ttjets->SetTitle("MC ttjets : Nr. of ttbb Weighted Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_ttbb_weighted_ttjets->SetName("njets_bjets_Z_tight_ttbb_weighted_ttjets");
	njets_bjets_Z_tight_ttbb_weighted_ttjets->SetTitle("MC ttjets : Nr. of ttbb Weighted Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_ttbb_weighted_acc_ttjets->SetName("njets_bjets_Z_loose_ttbb_weighted_acc_ttjets");
	njets_bjets_Z_loose_ttbb_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of ttbb Accumulative Weighted Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_ttbb_weighted_acc_ttjets->SetName("njets_bjets_Z_tight_ttbb_weighted_acc_ttjets");
	njets_bjets_Z_tight_ttbb_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of ttbb Accumulative Weighted Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_ttbb_ttjets->SetName("nbjets_btags_Z_loose_ttbb_ttjets");
	nbjets_btags_Z_loose_ttbb_ttjets->SetTitle("MC ttjets : Nr. of ttbb Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_ttbb_ttjets->SetName("nbjets_btags_Z_tight_ttbb_ttjets");
	nbjets_btags_Z_tight_ttbb_ttjets->SetTitle("MC ttjets : Nr. of ttbb Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_ttbb_acc_ttjets->SetName("nbjets_btags_Z_loose_ttbb_acc_ttjets");
	nbjets_btags_Z_loose_ttbb_acc_ttjets->SetTitle("MC ttjets : Nr. of ttbb Accumulative Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_ttbb_acc_ttjets->SetName("nbjets_btags_Z_tight_ttbb_acc_ttjets");
	nbjets_btags_Z_tight_ttbb_acc_ttjets->SetTitle("MC ttjets : Nr. of ttbb Accumulative Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_ttbb_weighted_ttjets->SetName("nbjets_btags_Z_loose_ttbb_weighted_ttjets");
	nbjets_btags_Z_loose_ttbb_weighted_ttjets->SetTitle("MC ttjets : Nr. of ttbb Weighted Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_ttbb_weighted_ttjets->SetName("nbjets_btags_Z_tight_ttbb_weighted_ttjets");
	nbjets_btags_Z_tight_ttbb_weighted_ttjets->SetTitle("MC ttjets : Nr. of ttbb Weighted Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_ttbb_weighted_acc_ttjets->SetName("nbjets_btags_Z_loose_ttbb_weighted_acc_ttjets");
	nbjets_btags_Z_loose_ttbb_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of ttbb Accumulative Weighted Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_ttbb_weighted_acc_ttjets->SetName("nbjets_btags_Z_tight_ttbb_weighted_acc_ttjets");
	nbjets_btags_Z_tight_ttbb_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of ttbb Accumulative Weighted Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_ttb_ttjets->SetName("njets_bjets_Z_loose_ttb_ttjets");
	njets_bjets_Z_loose_ttb_ttjets->SetTitle("MC ttjets : Nr. of ttb Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_ttb_ttjets->SetName("njets_bjets_Z_tight_ttb_ttjets");
	njets_bjets_Z_tight_ttb_ttjets->SetTitle("MC ttjets : Nr. of ttb Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_ttb_acc_ttjets->SetName("njets_bjets_Z_loose_ttb_acc_ttjets");
	njets_bjets_Z_loose_ttb_acc_ttjets->SetTitle("MC ttjets : Nr. of ttb Accumulative Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_ttb_acc_ttjets->SetName("njets_bjets_Z_tight_ttb_acc_ttjets");
	njets_bjets_Z_tight_ttb_acc_ttjets->SetTitle("MC ttjets : Nr. of ttb Accumulative Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_ttb_weighted_ttjets->SetName("njets_bjets_Z_loose_ttb_weighted_ttjets");
	njets_bjets_Z_loose_ttb_weighted_ttjets->SetTitle("MC ttjets : Nr. of ttb Weighted Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_ttb_weighted_ttjets->SetName("njets_bjets_Z_tight_ttb_weighted_ttjets");
	njets_bjets_Z_tight_ttb_weighted_ttjets->SetTitle("MC ttjets : Nr. of ttb Weighted Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_ttb_weighted_acc_ttjets->SetName("njets_bjets_Z_loose_ttb_weighted_acc_ttjets");
	njets_bjets_Z_loose_ttb_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of ttb Accumulative Weighted Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_ttb_weighted_acc_ttjets->SetName("njets_bjets_Z_tight_ttb_weighted_acc_ttjets");
	njets_bjets_Z_tight_ttb_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of ttb Accumulative Weighted Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_ttb_ttjets->SetName("nbjets_btags_Z_loose_ttb_ttjets");
	nbjets_btags_Z_loose_ttb_ttjets->SetTitle("MC ttjets : Nr. of ttb Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_ttb_ttjets->SetName("nbjets_btags_Z_tight_ttb_ttjets");
	nbjets_btags_Z_tight_ttb_ttjets->SetTitle("MC ttjets : Nr. of ttb Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_ttb_acc_ttjets->SetName("nbjets_btags_Z_loose_ttb_acc_ttjets");
	nbjets_btags_Z_loose_ttb_acc_ttjets->SetTitle("MC ttjets : Nr. of ttb Accumulative Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_ttb_acc_ttjets->SetName("nbjets_btags_Z_tight_ttb_acc_ttjets");
	nbjets_btags_Z_tight_ttb_acc_ttjets->SetTitle("MC ttjets : Nr. of ttb Accumulative Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_ttb_weighted_ttjets->SetName("nbjets_btags_Z_loose_ttb_weighted_ttjets");
	nbjets_btags_Z_loose_ttb_weighted_ttjets->SetTitle("MC ttjets : Nr. of ttb Weighted Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_ttb_weighted_ttjets->SetName("nbjets_btags_Z_tight_ttb_weighted_ttjets");
	nbjets_btags_Z_tight_ttb_weighted_ttjets->SetTitle("MC ttjets : Nr. of ttb Weighted Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_ttb_weighted_acc_ttjets->SetName("nbjets_btags_Z_loose_ttb_weighted_acc_ttjets");
	nbjets_btags_Z_loose_ttb_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of ttb Accumulative Weighted Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_ttb_weighted_acc_ttjets->SetName("nbjets_btags_Z_tight_ttb_weighted_acc_ttjets");
	nbjets_btags_Z_tight_ttb_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of ttb Accumulative Weighted Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_tt2b_ttjets->SetName("njets_bjets_Z_loose_tt2b_ttjets");
	njets_bjets_Z_loose_tt2b_ttjets->SetTitle("MC ttjets : Nr. of tt2b Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_tt2b_ttjets->SetName("njets_bjets_Z_tight_tt2b_ttjets");
	njets_bjets_Z_tight_tt2b_ttjets->SetTitle("MC ttjets : Nr. of tt2b Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_tt2b_acc_ttjets->SetName("njets_bjets_Z_loose_tt2b_acc_ttjets");
	njets_bjets_Z_loose_tt2b_acc_ttjets->SetTitle("MC ttjets : Nr. of tt2b Accumulative Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_tt2b_acc_ttjets->SetName("njets_bjets_Z_tight_tt2b_acc_ttjets");
	njets_bjets_Z_tight_tt2b_acc_ttjets->SetTitle("MC ttjets : Nr. of tt2b Accumulative Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_tt2b_weighted_ttjets->SetName("njets_bjets_Z_loose_tt2b_weighted_ttjets");
	njets_bjets_Z_loose_tt2b_weighted_ttjets->SetTitle("MC ttjets : Nr. of tt2b Weighted Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_tt2b_weighted_ttjets->SetName("njets_bjets_Z_tight_tt2b_weighted_ttjets");
	njets_bjets_Z_tight_tt2b_weighted_ttjets->SetTitle("MC ttjets : Nr. of tt2b Weighted Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	njets_bjets_Z_loose_tt2b_weighted_acc_ttjets->SetName("njets_bjets_Z_loose_tt2b_weighted_acc_ttjets");
	njets_bjets_Z_loose_tt2b_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of tt2b Accumulative Weighted Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_tight_tt2b_weighted_acc_ttjets->SetName("njets_bjets_Z_tight_tt2b_weighted_acc_ttjets");
	njets_bjets_Z_tight_tt2b_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of tt2b Accumulative Weighted Events vs Jet and BJet Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_tt2b_ttjets->SetName("nbjets_btags_Z_loose_tt2b_ttjets");
	nbjets_btags_Z_loose_tt2b_ttjets->SetTitle("MC ttjets : Nr. of tt2b Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_tt2b_ttjets->SetName("nbjets_btags_Z_tight_tt2b_ttjets");
	nbjets_btags_Z_tight_tt2b_ttjets->SetTitle("MC ttjets : Nr. of tt2b Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_tt2b_acc_ttjets->SetName("nbjets_btags_Z_loose_tt2b_acc_ttjets");
	nbjets_btags_Z_loose_tt2b_acc_ttjets->SetTitle("MC ttjets : Nr. of tt2b Accumulative Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_tt2b_acc_ttjets->SetName("nbjets_btags_Z_tight_tt2b_acc_ttjets");
	nbjets_btags_Z_tight_tt2b_acc_ttjets->SetTitle("MC ttjets : Nr. of tt2b Accumulative Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_tt2b_weighted_ttjets->SetName("nbjets_btags_Z_loose_tt2b_weighted_ttjets");
	nbjets_btags_Z_loose_tt2b_weighted_ttjets->SetTitle("MC ttjets : Nr. of tt2b Weighted Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_tt2b_weighted_ttjets->SetName("nbjets_btags_Z_tight_tt2b_weighted_ttjets");
	nbjets_btags_Z_tight_tt2b_weighted_ttjets->SetTitle("MC ttjets : Nr. of tt2b Weighted Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	nbjets_btags_Z_loose_tt2b_weighted_acc_ttjets->SetName("nbjets_btags_Z_loose_tt2b_weighted_acc_ttjets");
	nbjets_btags_Z_loose_tt2b_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of tt2b Accumulative Weighted Events vs BJet and BTag Multiplicity for 76 < M(ll) < 106");
	nbjets_btags_Z_tight_tt2b_weighted_acc_ttjets->SetName("nbjets_btags_Z_tight_tt2b_weighted_acc_ttjets");
	nbjets_btags_Z_tight_tt2b_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of tt2b Accumulative Weighted Events vs BJet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_ttbb_ttjets->SetName("njets_btags_Z_loose_ttbb_ttjets");
	njets_btags_Z_loose_ttbb_ttjets->SetTitle("MC ttjets : Nr. of ttbb Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttbb_ttjets->SetName("njets_btags_Z_tight_ttbb_ttjets");
	njets_btags_Z_tight_ttbb_ttjets->SetTitle("MC ttjets : Nr. of ttbb Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_ttbb_acc_ttjets->SetName("njets_btags_Z_loose_ttbb_acc_ttjets");
	njets_btags_Z_loose_ttbb_acc_ttjets->SetTitle("MC ttjets : Nr. of ttbb Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttbb_acc_ttjets->SetName("njets_btags_Z_tight_ttbb_acc_ttjets");
	njets_btags_Z_tight_ttbb_acc_ttjets->SetTitle("MC ttjets : Nr. of ttbb Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_ttbb_weighted_ttjets->SetName("njets_btags_Z_loose_ttbb_weighted_ttjets");
	njets_btags_Z_loose_ttbb_weighted_ttjets->SetTitle("MC ttjets : Nr. of ttbb Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttbb_weighted_ttjets->SetName("njets_btags_Z_tight_ttbb_weighted_ttjets");
	njets_btags_Z_tight_ttbb_weighted_ttjets->SetTitle("MC ttjets : Nr. of ttbb Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_ttbb_weighted_acc_ttjets->SetName("njets_btags_Z_loose_ttbb_weighted_acc_ttjets");
	njets_btags_Z_loose_ttbb_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of ttbb Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttbb_weighted_acc_ttjets->SetName("njets_btags_Z_tight_ttbb_weighted_acc_ttjets");
	njets_btags_Z_tight_ttbb_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of ttbb Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_ttb_ttjets->SetName("njets_btags_Z_loose_ttb_ttjets");
	njets_btags_Z_loose_ttb_ttjets->SetTitle("MC ttjets : Nr. of ttb Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttb_ttjets->SetName("njets_btags_Z_tight_ttb_ttjets");
	njets_btags_Z_tight_ttb_ttjets->SetTitle("MC ttjets : Nr. of ttb Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_ttb_acc_ttjets->SetName("njets_btags_Z_loose_ttb_acc_ttjets");
	njets_btags_Z_loose_ttb_acc_ttjets->SetTitle("MC ttjets : Nr. of ttb Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttb_acc_ttjets->SetName("njets_btags_Z_tight_ttb_acc_ttjets");
	njets_btags_Z_tight_ttb_acc_ttjets->SetTitle("MC ttjets : Nr. of ttb Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_ttb_weighted_ttjets->SetName("njets_btags_Z_loose_ttb_weighted_ttjets");
	njets_btags_Z_loose_ttb_weighted_ttjets->SetTitle("MC ttjets : Nr. of ttb Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttb_weighted_ttjets->SetName("njets_btags_Z_tight_ttb_weighted_ttjets");
	njets_btags_Z_tight_ttb_weighted_ttjets->SetTitle("MC ttjets : Nr. of ttb Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_ttb_weighted_acc_ttjets->SetName("njets_btags_Z_loose_ttb_weighted_acc_ttjets");
	njets_btags_Z_loose_ttb_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of ttb Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttb_weighted_acc_ttjets->SetName("njets_btags_Z_tight_ttb_weighted_acc_ttjets");
	njets_btags_Z_tight_ttb_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of ttb Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_tt2b_ttjets->SetName("njets_btags_Z_loose_tt2b_ttjets");
	njets_btags_Z_loose_tt2b_ttjets->SetTitle("MC ttjets : Nr. of tt2b Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_tt2b_ttjets->SetName("njets_btags_Z_tight_tt2b_ttjets");
	njets_btags_Z_tight_tt2b_ttjets->SetTitle("MC ttjets : Nr. of tt2b Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_tt2b_acc_ttjets->SetName("njets_btags_Z_loose_tt2b_acc_ttjets");
	njets_btags_Z_loose_tt2b_acc_ttjets->SetTitle("MC ttjets : Nr. of tt2b Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_tt2b_acc_ttjets->SetName("njets_btags_Z_tight_tt2b_acc_ttjets");
	njets_btags_Z_tight_tt2b_acc_ttjets->SetTitle("MC ttjets : Nr. of tt2b Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_tt2b_weighted_ttjets->SetName("njets_btags_Z_loose_tt2b_weighted_ttjets");
	njets_btags_Z_loose_tt2b_weighted_ttjets->SetTitle("MC ttjets : Nr. of tt2b Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_tt2b_weighted_ttjets->SetName("njets_btags_Z_tight_tt2b_weighted_ttjets");
	njets_btags_Z_tight_tt2b_weighted_ttjets->SetTitle("MC ttjets : Nr. of tt2b Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_tt2b_weighted_acc_ttjets->SetName("njets_btags_Z_loose_tt2b_weighted_acc_ttjets");
	njets_btags_Z_loose_tt2b_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of tt2b Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_tt2b_weighted_acc_ttjets->SetName("njets_btags_Z_tight_tt2b_weighted_acc_ttjets");
	njets_btags_Z_tight_tt2b_weighted_acc_ttjets->SetTitle("MC ttjets : Nr. of tt2b Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// DY

	TFile *f2 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_dy_all.root");

	TH1D *mll_Z_loose_DY = (TH1D*)f2->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_DY = (TH1D*)f2->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_DY = (TH1D*)f2->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_DY = (TH1D*)f2->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_DY = (TH2D*)f2->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_DY = (TH2D*)f2->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_DY = (TH2D*)f2->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_DY = (TH2D*)f2->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_DY = (TH2D*)f2->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_DY = (TH2D*)f2->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_DY = (TH2D*)f2->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_DY = (TH2D*)f2->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_DY->SetName("mll_Z_loose_DY");
	mll_Z_loose_DY->SetTitle("MC DY : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_DY->SetName("mll_Z_loose_weighted_DY");
	mll_Z_loose_weighted_DY->SetTitle("MC DY : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_DY->SetName("mll_Z_tight_DY");
	mll_Z_tight_DY->SetTitle("MC DY : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_DY->SetName("mll_Z_tight_weighted_DY");
	mll_Z_tight_weighted_DY->SetTitle("MC DY : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_DY->SetName("njets_btags_Z_loose_total_DY");
	njets_btags_Z_loose_total_DY->SetTitle("MC DY : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_DY->SetName("njets_btags_Z_tight_total_DY");
	njets_btags_Z_tight_total_DY->SetTitle("MC DY : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_DY->SetName("njets_btags_Z_loose_total_acc_DY");
	njets_btags_Z_loose_total_acc_DY->SetTitle("MC DY : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_DY->SetName("njets_btags_Z_tight_total_acc_DY");
	njets_btags_Z_tight_total_acc_DY->SetTitle("MC DY : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_DY->SetName("njets_btags_Z_loose_total_weighted_DY");
	njets_btags_Z_loose_total_weighted_DY->SetTitle("MC DY : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_DY->SetName("njets_btags_Z_tight_total_weighted_DY");
	njets_btags_Z_tight_total_weighted_DY->SetTitle("MC DY : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_DY->SetName("njets_btags_Z_loose_total_weighted_acc_DY");
	njets_btags_Z_loose_total_weighted_acc_DY->SetTitle("MC DY : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_DY->SetName("njets_btags_Z_tight_total_weighted_acc_DY");
	njets_btags_Z_tight_total_weighted_acc_DY->SetTitle("MC DY : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// ttZ_llnunu

	TFile *f3 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttz_llnunu_all.root");

	TH1D *mll_Z_loose_ttZ_llnunu = (TH1D*)f3->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_ttZ_llnunu = (TH1D*)f3->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_ttZ_llnunu = (TH1D*)f3->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_ttZ_llnunu = (TH1D*)f3->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_ttZ_llnunu = (TH2D*)f3->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_ttZ_llnunu = (TH2D*)f3->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_ttZ_llnunu = (TH2D*)f3->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_ttZ_llnunu = (TH2D*)f3->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_ttZ_llnunu = (TH2D*)f3->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_ttZ_llnunu = (TH2D*)f3->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_ttZ_llnunu = (TH2D*)f3->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_ttZ_llnunu = (TH2D*)f3->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_ttZ_llnunu->SetName("mll_Z_loose_ttZ_llnunu");
	mll_Z_loose_ttZ_llnunu->SetTitle("MC ttZ_llnunu : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_ttZ_llnunu->SetName("mll_Z_loose_weighted_ttZ_llnunu");
	mll_Z_loose_weighted_ttZ_llnunu->SetTitle("MC ttZ_llnunu : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_ttZ_llnunu->SetName("mll_Z_tight_ttZ_llnunu");
	mll_Z_tight_ttZ_llnunu->SetTitle("MC ttZ_llnunu : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_ttZ_llnunu->SetName("mll_Z_tight_weighted_ttZ_llnunu");
	mll_Z_tight_weighted_ttZ_llnunu->SetTitle("MC ttZ_llnunu : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_ttZ_llnunu->SetName("njets_btags_Z_loose_total_ttZ_llnunu");
	njets_btags_Z_loose_total_ttZ_llnunu->SetTitle("MC ttZ_llnunu : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_ttZ_llnunu->SetName("njets_btags_Z_tight_total_ttZ_llnunu");
	njets_btags_Z_tight_total_ttZ_llnunu->SetTitle("MC ttZ_llnunu : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_ttZ_llnunu->SetName("njets_btags_Z_loose_total_acc_ttZ_llnunu");
	njets_btags_Z_loose_total_acc_ttZ_llnunu->SetTitle("MC ttZ_llnunu : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_ttZ_llnunu->SetName("njets_btags_Z_tight_total_acc_ttZ_llnunu");
	njets_btags_Z_tight_total_acc_ttZ_llnunu->SetTitle("MC ttZ_llnunu : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_ttZ_llnunu->SetName("njets_btags_Z_loose_total_weighted_ttZ_llnunu");
	njets_btags_Z_loose_total_weighted_ttZ_llnunu->SetTitle("MC ttZ_llnunu : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_ttZ_llnunu->SetName("njets_btags_Z_tight_total_weighted_ttZ_llnunu");
	njets_btags_Z_tight_total_weighted_ttZ_llnunu->SetTitle("MC ttZ_llnunu : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_ttZ_llnunu->SetName("njets_btags_Z_loose_total_weighted_acc_ttZ_llnunu");
	njets_btags_Z_loose_total_weighted_acc_ttZ_llnunu->SetTitle("MC ttZ_llnunu : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_ttZ_llnunu->SetName("njets_btags_Z_tight_total_weighted_acc_ttZ_llnunu");
	njets_btags_Z_tight_total_weighted_acc_ttZ_llnunu->SetTitle("MC ttZ_llnunu : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// ST antitw

	TFile *f4 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_st_antitw_all.root");

	TH1D *mll_Z_loose_st_antitw = (TH1D*)f4->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_st_antitw = (TH1D*)f4->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_st_antitw = (TH1D*)f4->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_st_antitw = (TH1D*)f4->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_st_antitw = (TH2D*)f4->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_st_antitw = (TH2D*)f4->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_st_antitw = (TH2D*)f4->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_st_antitw = (TH2D*)f4->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_st_antitw = (TH2D*)f4->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_st_antitw = (TH2D*)f4->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_st_antitw = (TH2D*)f4->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_st_antitw = (TH2D*)f4->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_st_antitw->SetName("mll_Z_loose_st_antitw");
	mll_Z_loose_st_antitw->SetTitle("MC st_antitw : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_st_antitw->SetName("mll_Z_loose_weighted_st_antitw");
	mll_Z_loose_weighted_st_antitw->SetTitle("MC st_antitw : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_st_antitw->SetName("mll_Z_tight_st_antitw");
	mll_Z_tight_st_antitw->SetTitle("MC st_antitw : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_st_antitw->SetName("mll_Z_tight_weighted_st_antitw");
	mll_Z_tight_weighted_st_antitw->SetTitle("MC st_antitw : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_st_antitw->SetName("njets_btags_Z_loose_total_st_antitw");
	njets_btags_Z_loose_total_st_antitw->SetTitle("MC st_antitw : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_st_antitw->SetName("njets_btags_Z_tight_total_st_antitw");
	njets_btags_Z_tight_total_st_antitw->SetTitle("MC st_antitw : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_st_antitw->SetName("njets_btags_Z_loose_total_acc_st_antitw");
	njets_btags_Z_loose_total_acc_st_antitw->SetTitle("MC st_antitw : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_st_antitw->SetName("njets_btags_Z_tight_total_acc_st_antitw");
	njets_btags_Z_tight_total_acc_st_antitw->SetTitle("MC st_antitw : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_st_antitw->SetName("njets_btags_Z_loose_total_weighted_st_antitw");
	njets_btags_Z_loose_total_weighted_st_antitw->SetTitle("MC st_antitw : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_st_antitw->SetName("njets_btags_Z_tight_total_weighted_st_antitw");
	njets_btags_Z_tight_total_weighted_st_antitw->SetTitle("MC st_antitw : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_st_antitw->SetName("njets_btags_Z_loose_total_weighted_acc_st_antitw");
	njets_btags_Z_loose_total_weighted_acc_st_antitw->SetTitle("MC st_antitw : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_st_antitw->SetName("njets_btags_Z_tight_total_weighted_acc_st_antitw");
	njets_btags_Z_tight_total_weighted_acc_st_antitw->SetTitle("MC st_antitw : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// ST s

	TFile *f5 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_st_s_all.root");

	TH1D *mll_Z_loose_st_s = (TH1D*)f5->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_st_s = (TH1D*)f5->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_st_s = (TH1D*)f5->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_st_s = (TH1D*)f5->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_st_s = (TH2D*)f5->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_st_s = (TH2D*)f5->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_st_s = (TH2D*)f5->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_st_s = (TH2D*)f5->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_st_s = (TH2D*)f5->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_st_s = (TH2D*)f5->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_st_s = (TH2D*)f5->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_st_s = (TH2D*)f5->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_st_s->SetName("mll_Z_loose_st_s");
	mll_Z_loose_st_s->SetTitle("MC st_s : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_st_s->SetName("mll_Z_loose_weighted_st_s");
	mll_Z_loose_weighted_st_s->SetTitle("MC st_s : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_st_s->SetName("mll_Z_tight_st_s");
	mll_Z_tight_st_s->SetTitle("MC st_s : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_st_s->SetName("mll_Z_tight_weighted_st_s");
	mll_Z_tight_weighted_st_s->SetTitle("MC st_s : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_st_s->SetName("njets_btags_Z_loose_total_st_s");
	njets_btags_Z_loose_total_st_s->SetTitle("MC st_s : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_st_s->SetName("njets_btags_Z_tight_total_st_s");
	njets_btags_Z_tight_total_st_s->SetTitle("MC st_s : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_st_s->SetName("njets_btags_Z_loose_total_acc_st_s");
	njets_btags_Z_loose_total_acc_st_s->SetTitle("MC st_s : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_st_s->SetName("njets_btags_Z_tight_total_acc_st_s");
	njets_btags_Z_tight_total_acc_st_s->SetTitle("MC st_s : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_st_s->SetName("njets_btags_Z_loose_total_weighted_st_s");
	njets_btags_Z_loose_total_weighted_st_s->SetTitle("MC st_s : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_st_s->SetName("njets_btags_Z_tight_total_weighted_st_s");
	njets_btags_Z_tight_total_weighted_st_s->SetTitle("MC st_s : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_st_s->SetName("njets_btags_Z_loose_total_weighted_acc_st_s");
	njets_btags_Z_loose_total_weighted_acc_st_s->SetTitle("MC st_s : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_st_s->SetName("njets_btags_Z_tight_total_weighted_acc_st_s");
	njets_btags_Z_tight_total_weighted_acc_st_s->SetTitle("MC st_s : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// ST t

	TFile *f6 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_st_t_all.root");

	TH1D *mll_Z_loose_st_t = (TH1D*)f6->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_st_t = (TH1D*)f6->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_st_t = (TH1D*)f6->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_st_t = (TH1D*)f6->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_st_t = (TH2D*)f6->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_st_t = (TH2D*)f6->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_st_t = (TH2D*)f6->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_st_t = (TH2D*)f6->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_st_t = (TH2D*)f6->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_st_t = (TH2D*)f6->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_st_t = (TH2D*)f6->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_st_t = (TH2D*)f6->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_st_t->SetName("mll_Z_loose_st_t");
	mll_Z_loose_st_t->SetTitle("MC st_t : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_st_t->SetName("mll_Z_loose_weighted_st_t");
	mll_Z_loose_weighted_st_t->SetTitle("MC st_t : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_st_t->SetName("mll_Z_tight_st_t");
	mll_Z_tight_st_t->SetTitle("MC st_t : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_st_t->SetName("mll_Z_tight_weighted_st_t");
	mll_Z_tight_weighted_st_t->SetTitle("MC st_t : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_st_t->SetName("njets_btags_Z_loose_total_st_t");
	njets_btags_Z_loose_total_st_t->SetTitle("MC st_t : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_st_t->SetName("njets_btags_Z_tight_total_st_t");
	njets_btags_Z_tight_total_st_t->SetTitle("MC st_t : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_st_t->SetName("njets_btags_Z_loose_total_acc_st_t");
	njets_btags_Z_loose_total_acc_st_t->SetTitle("MC st_t : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_st_t->SetName("njets_btags_Z_tight_total_acc_st_t");
	njets_btags_Z_tight_total_acc_st_t->SetTitle("MC st_t : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_st_t->SetName("njets_btags_Z_loose_total_weighted_st_t");
	njets_btags_Z_loose_total_weighted_st_t->SetTitle("MC st_t : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_st_t->SetName("njets_btags_Z_tight_total_weighted_st_t");
	njets_btags_Z_tight_total_weighted_st_t->SetTitle("MC st_t : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_st_t->SetName("njets_btags_Z_loose_total_weighted_acc_st_t");
	njets_btags_Z_loose_total_weighted_acc_st_t->SetTitle("MC st_t : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_st_t->SetName("njets_btags_Z_tight_total_weighted_acc_st_t");
	njets_btags_Z_tight_total_weighted_acc_st_t->SetTitle("MC st_t : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// ST t anti

	TFile *f7 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_st_t_anti_all.root");

	TH1D *mll_Z_loose_st_t_anti = (TH1D*)f7->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_st_t_anti = (TH1D*)f7->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_st_t_anti = (TH1D*)f7->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_st_t_anti = (TH1D*)f7->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_st_t_anti = (TH2D*)f7->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_st_t_anti = (TH2D*)f7->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_st_t_anti = (TH2D*)f7->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_st_t_anti = (TH2D*)f7->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_st_t_anti = (TH2D*)f7->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_st_t_anti = (TH2D*)f7->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_st_t_anti = (TH2D*)f7->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_st_t_anti = (TH2D*)f7->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_st_t_anti->SetName("mll_Z_loose_st_t_anti");
	mll_Z_loose_st_t_anti->SetTitle("MC st_t_anti : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_st_t_anti->SetName("mll_Z_loose_weighted_st_t_anti");
	mll_Z_loose_weighted_st_t_anti->SetTitle("MC st_t_anti : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_st_t_anti->SetName("mll_Z_tight_st_t_anti");
	mll_Z_tight_st_t_anti->SetTitle("MC st_t_anti : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_st_t_anti->SetName("mll_Z_tight_weighted_st_t_anti");
	mll_Z_tight_weighted_st_t_anti->SetTitle("MC st_t_anti : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_st_t_anti->SetName("njets_btags_Z_loose_total_st_t_anti");
	njets_btags_Z_loose_total_st_t_anti->SetTitle("MC st_t_anti : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_st_t_anti->SetName("njets_btags_Z_tight_total_st_t_anti");
	njets_btags_Z_tight_total_st_t_anti->SetTitle("MC st_t_anti : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_st_t_anti->SetName("njets_btags_Z_loose_total_acc_st_t_anti");
	njets_btags_Z_loose_total_acc_st_t_anti->SetTitle("MC st_t_anti : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_st_t_anti->SetName("njets_btags_Z_tight_total_acc_st_t_anti");
	njets_btags_Z_tight_total_acc_st_t_anti->SetTitle("MC st_t_anti : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_st_t_anti->SetName("njets_btags_Z_loose_total_weighted_st_t_anti");
	njets_btags_Z_loose_total_weighted_st_t_anti->SetTitle("MC st_t_anti : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_st_t_anti->SetName("njets_btags_Z_tight_total_weighted_st_t_anti");
	njets_btags_Z_tight_total_weighted_st_t_anti->SetTitle("MC st_t_anti : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_st_t_anti->SetName("njets_btags_Z_loose_total_weighted_acc_st_t_anti");
	njets_btags_Z_loose_total_weighted_acc_st_t_anti->SetTitle("MC st_t_anti : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_st_t_anti->SetName("njets_btags_Z_tight_total_weighted_acc_st_t_anti");
	njets_btags_Z_tight_total_weighted_acc_st_t_anti->SetTitle("MC st_t_anti : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// ST tw

	TFile *f8 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_st_tw_all.root");

	TH1D *mll_Z_loose_st_tw = (TH1D*)f8->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_st_tw = (TH1D*)f8->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_st_tw = (TH1D*)f8->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_st_tw = (TH1D*)f8->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_st_tw = (TH2D*)f8->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_st_tw = (TH2D*)f8->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_st_tw = (TH2D*)f8->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_st_tw = (TH2D*)f8->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_st_tw = (TH2D*)f8->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_st_tw = (TH2D*)f8->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_st_tw = (TH2D*)f8->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_st_tw = (TH2D*)f8->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_st_tw->SetName("mll_Z_loose_st_tw");
	mll_Z_loose_st_tw->SetTitle("MC st_tw : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_st_tw->SetName("mll_Z_loose_weighted_st_tw");
	mll_Z_loose_weighted_st_tw->SetTitle("MC st_tw : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_st_tw->SetName("mll_Z_tight_st_tw");
	mll_Z_tight_st_tw->SetTitle("MC st_tw : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_st_tw->SetName("mll_Z_tight_weighted_st_tw");
	mll_Z_tight_weighted_st_tw->SetTitle("MC st_tw : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_st_tw->SetName("njets_btags_Z_loose_total_st_tw");
	njets_btags_Z_loose_total_st_tw->SetTitle("MC st_tw : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_st_tw->SetName("njets_btags_Z_tight_total_st_tw");
	njets_btags_Z_tight_total_st_tw->SetTitle("MC st_tw : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_st_tw->SetName("njets_btags_Z_loose_total_acc_st_tw");
	njets_btags_Z_loose_total_acc_st_tw->SetTitle("MC st_tw : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_st_tw->SetName("njets_btags_Z_tight_total_acc_st_tw");
	njets_btags_Z_tight_total_acc_st_tw->SetTitle("MC st_tw : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_st_tw->SetName("njets_btags_Z_loose_total_weighted_st_tw");
	njets_btags_Z_loose_total_weighted_st_tw->SetTitle("MC st_tw : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_st_tw->SetName("njets_btags_Z_tight_total_weighted_st_tw");
	njets_btags_Z_tight_total_weighted_st_tw->SetTitle("MC st_tw : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_st_tw->SetName("njets_btags_Z_loose_total_weighted_acc_st_tw");
	njets_btags_Z_loose_total_weighted_acc_st_tw->SetTitle("MC st_tw : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_st_tw->SetName("njets_btags_Z_tight_total_weighted_acc_st_tw");
	njets_btags_Z_tight_total_weighted_acc_st_tw->SetTitle("MC st_tw : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// ttHbb

	TFile *f9 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_tthbb_all.root");

	TH1D *mll_Z_loose_ttHbb = (TH1D*)f9->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_ttHbb = (TH1D*)f9->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_ttHbb = (TH1D*)f9->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_ttHbb = (TH1D*)f9->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_ttHbb = (TH2D*)f9->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_ttHbb = (TH2D*)f9->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_ttHbb = (TH2D*)f9->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_ttHbb = (TH2D*)f9->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_ttHbb = (TH2D*)f9->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_ttHbb = (TH2D*)f9->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_ttHbb = (TH2D*)f9->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_ttHbb = (TH2D*)f9->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_ttHbb->SetName("mll_Z_loose_ttHbb");
	mll_Z_loose_ttHbb->SetTitle("MC ttHbb : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_ttHbb->SetName("mll_Z_loose_weighted_ttHbb");
	mll_Z_loose_weighted_ttHbb->SetTitle("MC ttHbb : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_ttHbb->SetName("mll_Z_tight_ttHbb");
	mll_Z_tight_ttHbb->SetTitle("MC ttHbb : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_ttHbb->SetName("mll_Z_tight_weighted_ttHbb");
	mll_Z_tight_weighted_ttHbb->SetTitle("MC ttHbb : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_ttHbb->SetName("njets_btags_Z_loose_total_ttHbb");
	njets_btags_Z_loose_total_ttHbb->SetTitle("MC ttHbb : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_ttHbb->SetName("njets_btags_Z_tight_total_ttHbb");
	njets_btags_Z_tight_total_ttHbb->SetTitle("MC ttHbb : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_ttHbb->SetName("njets_btags_Z_loose_total_acc_ttHbb");
	njets_btags_Z_loose_total_acc_ttHbb->SetTitle("MC ttHbb : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_ttHbb->SetName("njets_btags_Z_tight_total_acc_ttHbb");
	njets_btags_Z_tight_total_acc_ttHbb->SetTitle("MC ttHbb : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_ttHbb->SetName("njets_btags_Z_loose_total_weighted_ttHbb");
	njets_btags_Z_loose_total_weighted_ttHbb->SetTitle("MC ttHbb : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_ttHbb->SetName("njets_btags_Z_tight_total_weighted_ttHbb");
	njets_btags_Z_tight_total_weighted_ttHbb->SetTitle("MC ttHbb : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_ttHbb->SetName("njets_btags_Z_loose_total_weighted_acc_ttHbb");
	njets_btags_Z_loose_total_weighted_acc_ttHbb->SetTitle("MC ttHbb : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_ttHbb->SetName("njets_btags_Z_tight_total_weighted_acc_ttHbb");
	njets_btags_Z_tight_total_weighted_acc_ttHbb->SetTitle("MC ttHbb : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// ttHnonbb

	TFile *f10 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_tthnonbb_all.root");

	TH1D *mll_Z_loose_ttHnonbb = (TH1D*)f10->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_ttHnonbb = (TH1D*)f10->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_ttHnonbb = (TH1D*)f10->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_ttHnonbb = (TH1D*)f10->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_ttHnonbb = (TH2D*)f10->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_ttHnonbb = (TH2D*)f10->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_ttHnonbb = (TH2D*)f10->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_ttHnonbb = (TH2D*)f10->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_ttHnonbb = (TH2D*)f10->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_ttHnonbb = (TH2D*)f10->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_ttHnonbb = (TH2D*)f10->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_ttHnonbb = (TH2D*)f10->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_ttHnonbb->SetName("mll_Z_loose_ttHnonbb");
	mll_Z_loose_ttHnonbb->SetTitle("MC ttHnonbb : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_ttHnonbb->SetName("mll_Z_loose_weighted_ttHnonbb");
	mll_Z_loose_weighted_ttHnonbb->SetTitle("MC ttHnonbb : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_ttHnonbb->SetName("mll_Z_tight_ttHnonbb");
	mll_Z_tight_ttHnonbb->SetTitle("MC ttHnonbb : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_ttHnonbb->SetName("mll_Z_tight_weighted_ttHnonbb");
	mll_Z_tight_weighted_ttHnonbb->SetTitle("MC ttHnonbb : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_ttHnonbb->SetName("njets_btags_Z_loose_total_ttHnonbb");
	njets_btags_Z_loose_total_ttHnonbb->SetTitle("MC ttHnonbb : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_ttHnonbb->SetName("njets_btags_Z_tight_total_ttHnonbb");
	njets_btags_Z_tight_total_ttHnonbb->SetTitle("MC ttHnonbb : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_ttHnonbb->SetName("njets_btags_Z_loose_total_acc_ttHnonbb");
	njets_btags_Z_loose_total_acc_ttHnonbb->SetTitle("MC ttHnonbb : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_ttHnonbb->SetName("njets_btags_Z_tight_total_acc_ttHnonbb");
	njets_btags_Z_tight_total_acc_ttHnonbb->SetTitle("MC ttHnonbb : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_ttHnonbb->SetName("njets_btags_Z_loose_total_weighted_ttHnonbb");
	njets_btags_Z_loose_total_weighted_ttHnonbb->SetTitle("MC ttHnonbb : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_ttHnonbb->SetName("njets_btags_Z_tight_total_weighted_ttHnonbb");
	njets_btags_Z_tight_total_weighted_ttHnonbb->SetTitle("MC ttHnonbb : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_ttHnonbb->SetName("njets_btags_Z_loose_total_weighted_acc_ttHnonbb");
	njets_btags_Z_loose_total_weighted_acc_ttHnonbb->SetTitle("MC ttHnonbb : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_ttHnonbb->SetName("njets_btags_Z_tight_total_weighted_acc_ttHnonbb");
	njets_btags_Z_tight_total_weighted_acc_ttHnonbb->SetTitle("MC ttHnonbb : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// ttZ_qq

	TFile *f11 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttz_qq_all.root");

	TH1D *mll_Z_loose_ttZ_qq = (TH1D*)f11->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_ttZ_qq = (TH1D*)f11->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_ttZ_qq = (TH1D*)f11->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_ttZ_qq = (TH1D*)f11->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_ttZ_qq = (TH2D*)f11->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_ttZ_qq = (TH2D*)f11->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_ttZ_qq = (TH2D*)f11->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_ttZ_qq = (TH2D*)f11->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_ttZ_qq = (TH2D*)f11->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_ttZ_qq = (TH2D*)f11->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_ttZ_qq = (TH2D*)f11->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_ttZ_qq = (TH2D*)f11->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_ttZ_qq->SetName("mll_Z_loose_ttZ_qq");
	mll_Z_loose_ttZ_qq->SetTitle("MC ttZ_qq : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_ttZ_qq->SetName("mll_Z_loose_weighted_ttZ_qq");
	mll_Z_loose_weighted_ttZ_qq->SetTitle("MC ttZ_qq : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_ttZ_qq->SetName("mll_Z_tight_ttZ_qq");
	mll_Z_tight_ttZ_qq->SetTitle("MC ttZ_qq : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_ttZ_qq->SetName("mll_Z_tight_weighted_ttZ_qq");
	mll_Z_tight_weighted_ttZ_qq->SetTitle("MC ttZ_qq : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_ttZ_qq->SetName("njets_btags_Z_loose_total_ttZ_qq");
	njets_btags_Z_loose_total_ttZ_qq->SetTitle("MC ttZ_qq : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_ttZ_qq->SetName("njets_btags_Z_tight_total_ttZ_qq");
	njets_btags_Z_tight_total_ttZ_qq->SetTitle("MC ttZ_qq : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_ttZ_qq->SetName("njets_btags_Z_loose_total_acc_ttZ_qq");
	njets_btags_Z_loose_total_acc_ttZ_qq->SetTitle("MC ttZ_qq : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_ttZ_qq->SetName("njets_btags_Z_tight_total_acc_ttZ_qq");
	njets_btags_Z_tight_total_acc_ttZ_qq->SetTitle("MC ttZ_qq : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_ttZ_qq->SetName("njets_btags_Z_loose_total_weighted_ttZ_qq");
	njets_btags_Z_loose_total_weighted_ttZ_qq->SetTitle("MC ttZ_qq : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_ttZ_qq->SetName("njets_btags_Z_tight_total_weighted_ttZ_qq");
	njets_btags_Z_tight_total_weighted_ttZ_qq->SetTitle("MC ttZ_qq : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_ttZ_qq->SetName("njets_btags_Z_loose_total_weighted_acc_ttZ_qq");
	njets_btags_Z_loose_total_weighted_acc_ttZ_qq->SetTitle("MC ttZ_qq : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_ttZ_qq->SetName("njets_btags_Z_tight_total_weighted_acc_ttZ_qq");
	njets_btags_Z_tight_total_weighted_acc_ttZ_qq->SetTitle("MC ttZ_qq : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// ttw_lnu

	TFile *f12 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttw_lnu_all.root");

	TH1D *mll_Z_loose_ttw_lnu = (TH1D*)f12->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_ttw_lnu = (TH1D*)f12->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_ttw_lnu = (TH1D*)f12->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_ttw_lnu = (TH1D*)f12->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_ttw_lnu = (TH2D*)f12->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_ttw_lnu = (TH2D*)f12->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_ttw_lnu = (TH2D*)f12->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_ttw_lnu = (TH2D*)f12->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_ttw_lnu = (TH2D*)f12->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_ttw_lnu = (TH2D*)f12->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_ttw_lnu = (TH2D*)f12->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_ttw_lnu = (TH2D*)f12->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_ttw_lnu->SetName("mll_Z_loose_ttw_lnu");
	mll_Z_loose_ttw_lnu->SetTitle("MC ttw_lnu : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_ttw_lnu->SetName("mll_Z_loose_weighted_ttw_lnu");
	mll_Z_loose_weighted_ttw_lnu->SetTitle("MC ttw_lnu : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_ttw_lnu->SetName("mll_Z_tight_ttw_lnu");
	mll_Z_tight_ttw_lnu->SetTitle("MC ttw_lnu : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_ttw_lnu->SetName("mll_Z_tight_weighted_ttw_lnu");
	mll_Z_tight_weighted_ttw_lnu->SetTitle("MC ttw_lnu : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_ttw_lnu->SetName("njets_btags_Z_loose_total_ttw_lnu");
	njets_btags_Z_loose_total_ttw_lnu->SetTitle("MC ttw_lnu : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_ttw_lnu->SetName("njets_btags_Z_tight_total_ttw_lnu");
	njets_btags_Z_tight_total_ttw_lnu->SetTitle("MC ttw_lnu : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_ttw_lnu->SetName("njets_btags_Z_loose_total_acc_ttw_lnu");
	njets_btags_Z_loose_total_acc_ttw_lnu->SetTitle("MC ttw_lnu : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_ttw_lnu->SetName("njets_btags_Z_tight_total_acc_ttw_lnu");
	njets_btags_Z_tight_total_acc_ttw_lnu->SetTitle("MC ttw_lnu : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_ttw_lnu->SetName("njets_btags_Z_loose_total_weighted_ttw_lnu");
	njets_btags_Z_loose_total_weighted_ttw_lnu->SetTitle("MC ttw_lnu : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_ttw_lnu->SetName("njets_btags_Z_tight_total_weighted_ttw_lnu");
	njets_btags_Z_tight_total_weighted_ttw_lnu->SetTitle("MC ttw_lnu : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_ttw_lnu->SetName("njets_btags_Z_loose_total_weighted_acc_ttw_lnu");
	njets_btags_Z_loose_total_weighted_acc_ttw_lnu->SetTitle("MC ttw_lnu : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_ttw_lnu->SetName("njets_btags_Z_tight_total_weighted_acc_ttw_lnu");
	njets_btags_Z_tight_total_weighted_acc_ttw_lnu->SetTitle("MC ttw_lnu : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// ttw_qq

	TFile *f13 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttw_qq_all.root");

	TH1D *mll_Z_loose_ttw_qq = (TH1D*)f13->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_ttw_qq = (TH1D*)f13->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_ttw_qq = (TH1D*)f13->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_ttw_qq = (TH1D*)f13->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_ttw_qq = (TH2D*)f13->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_ttw_qq = (TH2D*)f13->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_ttw_qq = (TH2D*)f13->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_ttw_qq = (TH2D*)f13->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_ttw_qq = (TH2D*)f13->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_ttw_qq = (TH2D*)f13->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_ttw_qq = (TH2D*)f13->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_ttw_qq = (TH2D*)f13->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_ttw_qq->SetName("mll_Z_loose_ttw_qq");
	mll_Z_loose_ttw_qq->SetTitle("MC ttw_qq : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_ttw_qq->SetName("mll_Z_loose_weighted_ttw_qq");
	mll_Z_loose_weighted_ttw_qq->SetTitle("MC ttw_qq : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_ttw_qq->SetName("mll_Z_tight_ttw_qq");
	mll_Z_tight_ttw_qq->SetTitle("MC ttw_qq : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_ttw_qq->SetName("mll_Z_tight_weighted_ttw_qq");
	mll_Z_tight_weighted_ttw_qq->SetTitle("MC ttw_qq : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_ttw_qq->SetName("njets_btags_Z_loose_total_ttw_qq");
	njets_btags_Z_loose_total_ttw_qq->SetTitle("MC ttw_qq : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_ttw_qq->SetName("njets_btags_Z_tight_total_ttw_qq");
	njets_btags_Z_tight_total_ttw_qq->SetTitle("MC ttw_qq : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_ttw_qq->SetName("njets_btags_Z_loose_total_acc_ttw_qq");
	njets_btags_Z_loose_total_acc_ttw_qq->SetTitle("MC ttw_qq : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_ttw_qq->SetName("njets_btags_Z_tight_total_acc_ttw_qq");
	njets_btags_Z_tight_total_acc_ttw_qq->SetTitle("MC ttw_qq : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_ttw_qq->SetName("njets_btags_Z_loose_total_weighted_ttw_qq");
	njets_btags_Z_loose_total_weighted_ttw_qq->SetTitle("MC ttw_qq : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_ttw_qq->SetName("njets_btags_Z_tight_total_weighted_ttw_qq");
	njets_btags_Z_tight_total_weighted_ttw_qq->SetTitle("MC ttw_qq : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_ttw_qq->SetName("njets_btags_Z_loose_total_weighted_acc_ttw_qq");
	njets_btags_Z_loose_total_weighted_acc_ttw_qq->SetTitle("MC ttw_qq : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_ttw_qq->SetName("njets_btags_Z_tight_total_weighted_acc_ttw_qq");
	njets_btags_Z_tight_total_weighted_acc_ttw_qq->SetTitle("MC ttw_qq : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// wjets

	TFile *f14 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_wjets_all.root");

	TH1D *mll_Z_loose_wjets = (TH1D*)f14->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_wjets = (TH1D*)f14->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_wjets = (TH1D*)f14->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_wjets = (TH1D*)f14->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_wjets = (TH2D*)f14->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_wjets = (TH2D*)f14->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_wjets = (TH2D*)f14->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_wjets = (TH2D*)f14->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_wjets = (TH2D*)f14->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_wjets = (TH2D*)f14->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_wjets = (TH2D*)f14->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_wjets = (TH2D*)f14->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_wjets->SetName("mll_Z_loose_wjets");
	mll_Z_loose_wjets->SetTitle("MC wjets : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_wjets->SetName("mll_Z_loose_weighted_wjets");
	mll_Z_loose_weighted_wjets->SetTitle("MC wjets : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_wjets->SetName("mll_Z_tight_wjets");
	mll_Z_tight_wjets->SetTitle("MC wjets : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_wjets->SetName("mll_Z_tight_weighted_wjets");
	mll_Z_tight_weighted_wjets->SetTitle("MC wjets : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_wjets->SetName("njets_btags_Z_loose_total_wjets");
	njets_btags_Z_loose_total_wjets->SetTitle("MC wjets : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_wjets->SetName("njets_btags_Z_tight_total_wjets");
	njets_btags_Z_tight_total_wjets->SetTitle("MC wjets : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_wjets->SetName("njets_btags_Z_loose_total_acc_wjets");
	njets_btags_Z_loose_total_acc_wjets->SetTitle("MC wjets : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_wjets->SetName("njets_btags_Z_tight_total_acc_wjets");
	njets_btags_Z_tight_total_acc_wjets->SetTitle("MC wjets : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_wjets->SetName("njets_btags_Z_loose_total_weighted_wjets");
	njets_btags_Z_loose_total_weighted_wjets->SetTitle("MC wjets : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_wjets->SetName("njets_btags_Z_tight_total_weighted_wjets");
	njets_btags_Z_tight_total_weighted_wjets->SetTitle("MC wjets : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_wjets->SetName("njets_btags_Z_loose_total_weighted_acc_wjets");
	njets_btags_Z_loose_total_weighted_acc_wjets->SetTitle("MC wjets : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_wjets->SetName("njets_btags_Z_tight_total_weighted_acc_wjets");
	njets_btags_Z_tight_total_weighted_acc_wjets->SetTitle("MC wjets : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// WWjets

	TFile *f15 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_wwjets_all.root");

	TH1D *mll_Z_loose_wwjets = (TH1D*)f15->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_wwjets = (TH1D*)f15->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_wwjets = (TH1D*)f15->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_wwjets = (TH1D*)f15->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_wwjets = (TH2D*)f15->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_wwjets = (TH2D*)f15->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_wwjets = (TH2D*)f15->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_wwjets = (TH2D*)f15->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_wwjets = (TH2D*)f15->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_wwjets = (TH2D*)f15->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_wwjets = (TH2D*)f15->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_wwjets = (TH2D*)f15->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_wwjets->SetName("mll_Z_loose_wwjets");
	mll_Z_loose_wwjets->SetTitle("MC wwjets : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_wwjets->SetName("mll_Z_loose_weighted_wwjets");
	mll_Z_loose_weighted_wwjets->SetTitle("MC wwjets : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_wwjets->SetName("mll_Z_tight_wwjets");
	mll_Z_tight_wwjets->SetTitle("MC wwjets : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_wwjets->SetName("mll_Z_tight_weighted_wwjets");
	mll_Z_tight_weighted_wwjets->SetTitle("MC wwjets : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_wwjets->SetName("njets_btags_Z_loose_total_wwjets");
	njets_btags_Z_loose_total_wwjets->SetTitle("MC wwjets : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_wwjets->SetName("njets_btags_Z_tight_total_wwjets");
	njets_btags_Z_tight_total_wwjets->SetTitle("MC wwjets : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_wwjets->SetName("njets_btags_Z_loose_total_acc_wwjets");
	njets_btags_Z_loose_total_acc_wwjets->SetTitle("MC wwjets : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_wwjets->SetName("njets_btags_Z_tight_total_acc_wwjets");
	njets_btags_Z_tight_total_acc_wwjets->SetTitle("MC wwjets : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_wwjets->SetName("njets_btags_Z_loose_total_weighted_wwjets");
	njets_btags_Z_loose_total_weighted_wwjets->SetTitle("MC wwjets : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_wwjets->SetName("njets_btags_Z_tight_total_weighted_wwjets");
	njets_btags_Z_tight_total_weighted_wwjets->SetTitle("MC wwjets : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_wwjets->SetName("njets_btags_Z_loose_total_weighted_acc_wwjets");
	njets_btags_Z_loose_total_weighted_acc_wwjets->SetTitle("MC wwjets : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_wwjets->SetName("njets_btags_Z_tight_total_weighted_acc_wwjets");
	njets_btags_Z_tight_total_weighted_acc_wwjets->SetTitle("MC wwjets : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// WZ jets

	TFile *f16 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_wzjets_all.root");

	TH1D *mll_Z_loose_wzjets = (TH1D*)f16->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_wzjets = (TH1D*)f16->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_wzjets = (TH1D*)f16->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_wzjets = (TH1D*)f16->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_wzjets = (TH2D*)f16->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_wzjets = (TH2D*)f16->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_wzjets = (TH2D*)f16->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_wzjets = (TH2D*)f16->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_wzjets = (TH2D*)f16->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_wzjets = (TH2D*)f16->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_wzjets = (TH2D*)f16->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_wzjets = (TH2D*)f16->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_wzjets->SetName("mll_Z_loose_wzjets");
	mll_Z_loose_wzjets->SetTitle("MC wzjets : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_wzjets->SetName("mll_Z_loose_weighted_wzjets");
	mll_Z_loose_weighted_wzjets->SetTitle("MC wzjets : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_wzjets->SetName("mll_Z_tight_wzjets");
	mll_Z_tight_wzjets->SetTitle("MC wzjets : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_wzjets->SetName("mll_Z_tight_weighted_wzjets");
	mll_Z_tight_weighted_wzjets->SetTitle("MC wzjets : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_wzjets->SetName("njets_btags_Z_loose_total_wzjets");
	njets_btags_Z_loose_total_wzjets->SetTitle("MC wzjets : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_wzjets->SetName("njets_btags_Z_tight_total_wzjets");
	njets_btags_Z_tight_total_wzjets->SetTitle("MC wzjets : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_wzjets->SetName("njets_btags_Z_loose_total_acc_wzjets");
	njets_btags_Z_loose_total_acc_wzjets->SetTitle("MC wzjets : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_wzjets->SetName("njets_btags_Z_tight_total_acc_wzjets");
	njets_btags_Z_tight_total_acc_wzjets->SetTitle("MC wzjets : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_wzjets->SetName("njets_btags_Z_loose_total_weighted_wzjets");
	njets_btags_Z_loose_total_weighted_wzjets->SetTitle("MC wzjets : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_wzjets->SetName("njets_btags_Z_tight_total_weighted_wzjets");
	njets_btags_Z_tight_total_weighted_wzjets->SetTitle("MC wzjets : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_wzjets->SetName("njets_btags_Z_loose_total_weighted_acc_wzjets");
	njets_btags_Z_loose_total_weighted_acc_wzjets->SetTitle("MC wzjets : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_wzjets->SetName("njets_btags_Z_tight_total_weighted_acc_wzjets");
	njets_btags_Z_tight_total_weighted_acc_wzjets->SetTitle("MC wzjets : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// ZZ jets

	TFile *f17 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_zzjets_all.root");

	TH1D *mll_Z_loose_zzjets = (TH1D*)f17->Get("mll_Z_loose");
	TH1D *mll_Z_loose_weighted_zzjets = (TH1D*)f17->Get("mll_Z_loose_weighted");
	TH1D *mll_Z_tight_zzjets = (TH1D*)f17->Get("mll_Z_tight");
	TH1D *mll_Z_tight_weighted_zzjets = (TH1D*)f17->Get("mll_Z_tight_weighted");

	TH2D *njets_btags_Z_loose_total_zzjets = (TH2D*)f17->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_tight_total_zzjets = (TH2D*)f17->Get("njets_btags_Z_tight_total");
	TH2D *njets_btags_Z_loose_total_acc_zzjets = (TH2D*)f17->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_btags_Z_tight_total_acc_zzjets = (TH2D*)f17->Get("njets_btags_Z_tight_total_acc");
	TH2D *njets_btags_Z_loose_total_weighted_zzjets = (TH2D*)f17->Get("njets_btags_Z_loose_total_weighted");
	TH2D *njets_btags_Z_tight_total_weighted_zzjets = (TH2D*)f17->Get("njets_btags_Z_tight_total_weighted");
	TH2D *njets_btags_Z_loose_total_weighted_acc_zzjets = (TH2D*)f17->Get("njets_btags_Z_loose_total_weighted_acc");
	TH2D *njets_btags_Z_tight_total_weighted_acc_zzjets = (TH2D*)f17->Get("njets_btags_Z_tight_total_weighted_acc");

	mll_Z_loose_zzjets->SetName("mll_Z_loose_zzjets");
	mll_Z_loose_zzjets->SetTitle("MC zzjets : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_loose_weighted_zzjets->SetName("mll_Z_loose_weighted_zzjets");
	mll_Z_loose_weighted_zzjets->SetTitle("MC zzjets : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_zzjets->SetName("mll_Z_tight_zzjets");
	mll_Z_tight_zzjets->SetTitle("MC zzjets : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_tight_weighted_zzjets->SetName("mll_Z_tight_weighted_zzjets");
	mll_Z_tight_weighted_zzjets->SetTitle("MC zzjets : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	njets_btags_Z_loose_total_zzjets->SetName("njets_btags_Z_loose_total_zzjets");
	njets_btags_Z_loose_total_zzjets->SetTitle("MC zzjets : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_zzjets->SetName("njets_btags_Z_tight_total_zzjets");
	njets_btags_Z_tight_total_zzjets->SetTitle("MC zzjets : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_zzjets->SetName("njets_btags_Z_loose_total_acc_zzjets");
	njets_btags_Z_loose_total_acc_zzjets->SetTitle("MC zzjets : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_zzjets->SetName("njets_btags_Z_tight_total_acc_zzjets");
	njets_btags_Z_tight_total_acc_zzjets->SetTitle("MC zzjets : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_zzjets->SetName("njets_btags_Z_loose_total_weighted_zzjets");
	njets_btags_Z_loose_total_weighted_zzjets->SetTitle("MC zzjets : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_zzjets->SetName("njets_btags_Z_tight_total_weighted_zzjets");
	njets_btags_Z_tight_total_weighted_zzjets->SetTitle("MC zzjets : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_zzjets->SetName("njets_btags_Z_loose_total_weighted_acc_zzjets");
	njets_btags_Z_loose_total_weighted_acc_zzjets->SetTitle("MC zzjets : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_zzjets->SetName("njets_btags_Z_tight_total_weighted_acc_zzjets");
	njets_btags_Z_tight_total_weighted_acc_zzjets->SetTitle("MC zzjets : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");


	// ttjets >= 4-bquarks with pt cut > 20 GeV

	TFile *f18 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttjets_4b_pt20.root");

	TH2D *njets_btags_Z_loose_total_ttjets_4b_pt20 = (TH2D*)f18->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_loose_total_acc_ttjets_4b_pt20 = (TH2D*)f18->Get("njets_btags_Z_loose_total_acc");
	TH2D *njets_bjets_Z_loose_total_ttjets_4b_pt20 = (TH2D*)f18->Get("njets_bjets_Z_loose_total");
	TH2D *njets_bjets_Z_loose_total_acc_ttjets_4b_pt20 = (TH2D*)f18->Get("njets_bjets_Z_loose_total_acc");
	TH2D *njets_btags_Z_loose_ttbb_ttjets_4b_pt20 = (TH2D*)f18->Get("njets_btags_Z_loose_ttbb");
	TH2D *njets_btags_Z_loose_ttbb_acc_ttjets_4b_pt20 = (TH2D*)f18->Get("njets_btags_Z_loose_ttbb_acc");
	TH2D *njets_bjets_Z_loose_ttbb_ttjets_4b_pt20 = (TH2D*)f18->Get("njets_bjets_Z_loose_ttbb");
	TH2D *njets_bjets_Z_loose_ttbb_acc_ttjets_4b_pt20 = (TH2D*)f18->Get("njets_bjets_Z_loose_ttbb_acc");

	njets_btags_Z_loose_total_ttjets_4b_pt20->SetName("njets_btags_Z_loose_total_ttjets_4b_pt20");
	njets_btags_Z_loose_total_ttjets_4b_pt20->SetTitle("MC ttjets_4b_pt20 : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_loose_total_acc_ttjets_4b_pt20->SetName("njets_btags_Z_loose_total_acc_ttjets_4b_pt20");
	njets_btags_Z_loose_total_acc_ttjets_4b_pt20->SetTitle("MC ttjets_4b_pt20 : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_loose_total_ttjets_4b_pt20->SetName("njets_bjets_Z_loose_total_ttjets_4b_pt20");
	njets_bjets_Z_loose_total_ttjets_4b_pt20->SetTitle("MC ttjets_4b_pt20 : Total Nr. of Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_loose_total_acc_ttjets_4b_pt20->SetName("njets_bjets_Z_loose_total_acc_ttjets_4b_pt20");
	njets_bjets_Z_loose_total_acc_ttjets_4b_pt20->SetTitle("MC ttjets_4b_pt20 : Total Nr. of Accumulative Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_loose_ttbb_ttjets_4b_pt20->SetName("njets_btags_Z_loose_ttbb_ttjets_4b_pt20");
	njets_btags_Z_loose_ttbb_ttjets_4b_pt20->SetTitle("MC ttjets_4b_pt20 : Nr. of ttbb Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_loose_ttbb_acc_ttjets_4b_pt20->SetName("njets_btags_Z_loose_ttbb_acc_ttjets_4b_pt20");
	njets_btags_Z_loose_ttbb_acc_ttjets_4b_pt20->SetTitle("MC ttjets_4b_pt20 : Nr. of ttbb Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_loose_ttbb_ttjets_4b_pt20->SetName("njets_bjets_Z_loose_ttbb_ttjets_4b_pt20");
	njets_bjets_Z_loose_ttbb_ttjets_4b_pt20->SetTitle("MC ttjets_4b_pt20 : Nr. of ttbb Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_loose_ttbb_acc_ttjets_4b_pt20->SetName("njets_bjets_Z_loose_ttbb_acc_ttjets_4b_pt20");
	njets_bjets_Z_loose_ttbb_acc_ttjets_4b_pt20->SetTitle("MC ttjets_4b_pt20 : Nr. of ttbb Accumulative Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");


	// Adding M(ll) Distribution for all

	TH1D *mll_Z_loose_all = (TH1D*) mll_Z_loose_ttjets->Clone();
	mll_Z_loose_all->Add(mll_Z_loose_DY);
	mll_Z_loose_all->Add(mll_Z_loose_ttZ_llnunu);
	mll_Z_loose_all->Add(mll_Z_loose_st_antitw);
	mll_Z_loose_all->Add(mll_Z_loose_st_s);
	mll_Z_loose_all->Add(mll_Z_loose_st_t);
	mll_Z_loose_all->Add(mll_Z_loose_st_t_anti);
	mll_Z_loose_all->Add(mll_Z_loose_st_tw);
	mll_Z_loose_all->Add(mll_Z_loose_ttHbb);
	mll_Z_loose_all->Add(mll_Z_loose_ttHnonbb);
	mll_Z_loose_all->Add(mll_Z_loose_ttZ_qq);
	mll_Z_loose_all->Add(mll_Z_loose_ttw_lnu);
	mll_Z_loose_all->Add(mll_Z_loose_ttw_qq);
	mll_Z_loose_all->Add(mll_Z_loose_wjets);
	mll_Z_loose_all->Add(mll_Z_loose_wwjets);
	mll_Z_loose_all->Add(mll_Z_loose_wzjets);
	mll_Z_loose_all->Add(mll_Z_loose_zzjets);

	TH1D *mll_Z_tight_all = (TH1D*) mll_Z_tight_ttjets->Clone();
	mll_Z_tight_all->Add(mll_Z_tight_DY);
	mll_Z_tight_all->Add(mll_Z_tight_ttZ_llnunu);
	mll_Z_tight_all->Add(mll_Z_tight_st_antitw);
	mll_Z_tight_all->Add(mll_Z_tight_st_s);
	mll_Z_tight_all->Add(mll_Z_tight_st_t);
	mll_Z_tight_all->Add(mll_Z_tight_st_t_anti);
	mll_Z_tight_all->Add(mll_Z_tight_st_tw);
	mll_Z_tight_all->Add(mll_Z_tight_ttHbb);
	mll_Z_tight_all->Add(mll_Z_tight_ttHnonbb);
	mll_Z_tight_all->Add(mll_Z_tight_ttZ_qq);
	mll_Z_tight_all->Add(mll_Z_tight_ttw_lnu);
	mll_Z_tight_all->Add(mll_Z_tight_ttw_qq);
	mll_Z_tight_all->Add(mll_Z_tight_wjets);
	mll_Z_tight_all->Add(mll_Z_tight_wwjets);
	mll_Z_tight_all->Add(mll_Z_tight_wzjets);
	mll_Z_tight_all->Add(mll_Z_tight_zzjets);

	TH1D *mll_Z_loose_weighted_all = (TH1D*) mll_Z_loose_weighted_ttjets->Clone();
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_DY);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_ttZ_llnunu);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_st_antitw);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_st_s);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_st_t);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_st_t_anti);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_st_tw);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_ttHbb);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_ttHnonbb);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_ttZ_qq);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_ttw_lnu);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_ttw_qq);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_wjets);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_wwjets);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_wzjets);
	mll_Z_loose_weighted_all->Add(mll_Z_loose_weighted_zzjets);

	TH1D *mll_Z_tight_weighted_all = (TH1D*) mll_Z_tight_weighted_ttjets->Clone();
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_DY);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_ttZ_llnunu);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_st_antitw);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_st_s);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_st_t);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_st_t_anti);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_st_tw);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_ttHbb);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_ttHnonbb);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_ttZ_qq);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_ttw_lnu);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_ttw_qq);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_wjets);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_wwjets);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_wzjets);
	mll_Z_tight_weighted_all->Add(mll_Z_tight_weighted_zzjets);

	mll_Z_loose_all->SetName("mll_Z_loose_all");
	mll_Z_loose_all->SetTitle("MC All : Total Nr. of Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_all->SetName("mll_Z_tight_all");
	mll_Z_tight_all->SetTitle("MC All : Total Nr. of Events vs M(ll) for 88 < M(ll) < 94");
	mll_Z_loose_weighted_all->SetName("mll_Z_loose_weighted_all");
	mll_Z_loose_weighted_all->SetTitle("MC All : Total Nr. of Weighted Events vs M(ll) for 76 < M(ll) < 106");
	mll_Z_tight_weighted_all->SetName("mll_Z_tight_weighted_all");
	mll_Z_tight_weighted_all->SetTitle("MC All : Total Nr. of Weighted Events vs M(ll) for 88 < M(ll) < 94");

	// Histograms for ttbb, ttb and tt2b fraction in ttjets MC

	TH2D *njets_btags_Z_loose_ttbb_frac_ttjets = (TH2D*) njets_btags_Z_loose_ttbb_ttjets->Clone();
	njets_btags_Z_loose_ttbb_frac_ttjets->Divide(njets_btags_Z_loose_total_ttjets);
	TH2D *njets_btags_Z_tight_ttbb_frac_ttjets = (TH2D*) njets_btags_Z_tight_ttbb_ttjets->Clone();
	njets_btags_Z_tight_ttbb_frac_ttjets->Divide(njets_btags_Z_tight_total_ttjets);
	TH2D *njets_btags_Z_loose_ttbb_frac_acc_ttjets = (TH2D*) njets_btags_Z_loose_ttbb_acc_ttjets->Clone();
	njets_btags_Z_loose_ttbb_frac_acc_ttjets->Divide(njets_btags_Z_loose_total_acc_ttjets);
	TH2D *njets_btags_Z_tight_ttbb_frac_acc_ttjets = (TH2D*) njets_btags_Z_tight_ttbb_acc_ttjets->Clone();
	njets_btags_Z_tight_ttbb_frac_acc_ttjets->Divide(njets_btags_Z_tight_total_acc_ttjets);

	TH2D *njets_btags_Z_loose_ttb_frac_ttjets = (TH2D*) njets_btags_Z_loose_ttb_ttjets->Clone();
	njets_btags_Z_loose_ttb_frac_ttjets->Divide(njets_btags_Z_loose_total_ttjets);
	TH2D *njets_btags_Z_tight_ttb_frac_ttjets = (TH2D*) njets_btags_Z_tight_ttb_ttjets->Clone();
	njets_btags_Z_tight_ttb_frac_ttjets->Divide(njets_btags_Z_tight_total_ttjets);
	TH2D *njets_btags_Z_loose_ttb_frac_acc_ttjets = (TH2D*) njets_btags_Z_loose_ttb_acc_ttjets->Clone();
	njets_btags_Z_loose_ttb_frac_acc_ttjets->Divide(njets_btags_Z_loose_total_acc_ttjets);
	TH2D *njets_btags_Z_tight_ttb_frac_acc_ttjets = (TH2D*) njets_btags_Z_tight_ttb_acc_ttjets->Clone();
	njets_btags_Z_tight_ttb_frac_acc_ttjets->Divide(njets_btags_Z_tight_total_acc_ttjets);

	TH2D *njets_btags_Z_loose_tt2b_frac_ttjets = (TH2D*) njets_btags_Z_loose_tt2b_ttjets->Clone();
	njets_btags_Z_loose_tt2b_frac_ttjets->Divide(njets_btags_Z_loose_total_ttjets);
	TH2D *njets_btags_Z_tight_tt2b_frac_ttjets = (TH2D*) njets_btags_Z_tight_tt2b_ttjets->Clone();
	njets_btags_Z_tight_tt2b_frac_ttjets->Divide(njets_btags_Z_tight_total_ttjets);
	TH2D *njets_btags_Z_loose_tt2b_frac_acc_ttjets = (TH2D*) njets_btags_Z_loose_tt2b_acc_ttjets->Clone();
	njets_btags_Z_loose_tt2b_frac_acc_ttjets->Divide(njets_btags_Z_loose_total_acc_ttjets);
	TH2D *njets_btags_Z_tight_tt2b_frac_acc_ttjets = (TH2D*) njets_btags_Z_tight_tt2b_acc_ttjets->Clone();
	njets_btags_Z_tight_tt2b_frac_acc_ttjets->Divide(njets_btags_Z_tight_total_acc_ttjets);

	njets_btags_Z_loose_ttbb_frac_ttjets->SetName("njets_btags_Z_loose_ttbb_frac_ttjets");
	njets_btags_Z_loose_ttbb_frac_ttjets->SetTitle("MC ttjets : Fraction of ttbb Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttbb_frac_ttjets->SetName("njets_btags_Z_tight_ttbb_frac_ttjets");
	njets_btags_Z_tight_ttbb_frac_ttjets->SetTitle("MC ttjets : Fraction of ttbb Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_ttbb_frac_acc_ttjets->SetName("njets_btags_Z_loose_ttbb_frac_acc_ttjets");
	njets_btags_Z_loose_ttbb_frac_acc_ttjets->SetTitle("MC ttjets : Fraction of Accumulative ttbb Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttbb_frac_acc_ttjets->SetName("njets_btags_Z_tight_ttbb_frac_acc_ttjets");
	njets_btags_Z_tight_ttbb_frac_acc_ttjets->SetTitle("MC ttjets : Fraction of Accumulative ttbb Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	njets_btags_Z_loose_ttb_frac_ttjets->SetName("njets_btags_Z_loose_ttb_frac_ttjets");
	njets_btags_Z_loose_ttb_frac_ttjets->SetTitle("MC ttjets : Fraction of ttb Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttb_frac_ttjets->SetName("njets_btags_Z_tight_ttb_frac_ttjets");
	njets_btags_Z_tight_ttb_frac_ttjets->SetTitle("MC ttjets : Fraction of ttb Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_ttb_frac_acc_ttjets->SetName("njets_btags_Z_loose_ttb_frac_acc_ttjets");
	njets_btags_Z_loose_ttb_frac_acc_ttjets->SetTitle("MC ttjets : Fraction of Accumulative ttb Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttb_frac_acc_ttjets->SetName("njets_btags_Z_tight_ttb_frac_acc_ttjets");
	njets_btags_Z_tight_ttb_frac_acc_ttjets->SetTitle("MC ttjets : Fraction of Accumulative ttb Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	njets_btags_Z_loose_tt2b_frac_ttjets->SetName("njets_btags_Z_loose_tt2b_frac_ttjets");
	njets_btags_Z_loose_tt2b_frac_ttjets->SetTitle("MC ttjets : Fraction of tt2b Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_tt2b_frac_ttjets->SetName("njets_btags_Z_tight_tt2b_frac_ttjets");
	njets_btags_Z_tight_tt2b_frac_ttjets->SetTitle("MC ttjets : Fraction of tt2b Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_tt2b_frac_acc_ttjets->SetName("njets_btags_Z_loose_tt2b_frac_acc_ttjets");
	njets_btags_Z_loose_tt2b_frac_acc_ttjets->SetTitle("MC ttjets : Fraction of Accumulative tt2b Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_tt2b_frac_acc_ttjets->SetName("njets_btags_Z_tight_tt2b_frac_acc_ttjets");
	njets_btags_Z_tight_tt2b_frac_acc_ttjets->SetTitle("MC ttjets : Fraction of Accumulative tt2b Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	TH2D *njets_btags_Z_loose_ttbb_frac_weighted_ttjets = (TH2D*) njets_btags_Z_loose_ttbb_weighted_ttjets->Clone();
	njets_btags_Z_loose_ttbb_frac_weighted_ttjets->Divide(njets_btags_Z_loose_total_weighted_ttjets);
	TH2D *njets_btags_Z_tight_ttbb_frac_weighted_ttjets = (TH2D*) njets_btags_Z_tight_ttbb_weighted_ttjets->Clone();
	njets_btags_Z_tight_ttbb_frac_weighted_ttjets->Divide(njets_btags_Z_tight_total_weighted_ttjets);
	TH2D *njets_btags_Z_loose_ttbb_frac_weighted_acc_ttjets = (TH2D*) njets_btags_Z_loose_ttbb_weighted_acc_ttjets->Clone();
	njets_btags_Z_loose_ttbb_frac_weighted_acc_ttjets->Divide(njets_btags_Z_loose_total_weighted_acc_ttjets);
	TH2D *njets_btags_Z_tight_ttbb_frac_weighted_acc_ttjets = (TH2D*) njets_btags_Z_tight_ttbb_weighted_acc_ttjets->Clone();
	njets_btags_Z_tight_ttbb_frac_weighted_acc_ttjets->Divide(njets_btags_Z_tight_total_weighted_acc_ttjets);

	TH2D *njets_btags_Z_loose_ttb_frac_weighted_ttjets = (TH2D*) njets_btags_Z_loose_ttb_weighted_ttjets->Clone();
	njets_btags_Z_loose_ttb_frac_weighted_ttjets->Divide(njets_btags_Z_loose_total_weighted_ttjets);
	TH2D *njets_btags_Z_tight_ttb_frac_weighted_ttjets = (TH2D*) njets_btags_Z_tight_ttb_weighted_ttjets->Clone();
	njets_btags_Z_tight_ttb_frac_weighted_ttjets->Divide(njets_btags_Z_tight_total_weighted_ttjets);
	TH2D *njets_btags_Z_loose_ttb_frac_weighted_acc_ttjets = (TH2D*) njets_btags_Z_loose_ttb_weighted_acc_ttjets->Clone();
	njets_btags_Z_loose_ttb_frac_weighted_acc_ttjets->Divide(njets_btags_Z_loose_total_weighted_acc_ttjets);
	TH2D *njets_btags_Z_tight_ttb_frac_weighted_acc_ttjets = (TH2D*) njets_btags_Z_tight_ttb_weighted_acc_ttjets->Clone();
	njets_btags_Z_tight_ttb_frac_weighted_acc_ttjets->Divide(njets_btags_Z_tight_total_weighted_acc_ttjets);

	TH2D *njets_btags_Z_loose_tt2b_frac_weighted_ttjets = (TH2D*) njets_btags_Z_loose_tt2b_weighted_ttjets->Clone();
	njets_btags_Z_loose_tt2b_frac_weighted_ttjets->Divide(njets_btags_Z_loose_total_weighted_ttjets);
	TH2D *njets_btags_Z_tight_tt2b_frac_weighted_ttjets = (TH2D*) njets_btags_Z_tight_tt2b_weighted_ttjets->Clone();
	njets_btags_Z_tight_tt2b_frac_weighted_ttjets->Divide(njets_btags_Z_tight_total_weighted_ttjets);
	TH2D *njets_btags_Z_loose_tt2b_frac_weighted_acc_ttjets = (TH2D*) njets_btags_Z_loose_tt2b_weighted_acc_ttjets->Clone();
	njets_btags_Z_loose_tt2b_frac_weighted_acc_ttjets->Divide(njets_btags_Z_loose_total_weighted_acc_ttjets);
	TH2D *njets_btags_Z_tight_tt2b_frac_weighted_acc_ttjets = (TH2D*) njets_btags_Z_tight_tt2b_weighted_acc_ttjets->Clone();
	njets_btags_Z_tight_tt2b_frac_weighted_acc_ttjets->Divide(njets_btags_Z_tight_total_weighted_acc_ttjets);

	njets_btags_Z_loose_ttbb_frac_weighted_ttjets->SetName("njets_btags_Z_loose_ttbb_frac_weighted_ttjets");
	njets_btags_Z_loose_ttbb_frac_weighted_ttjets->SetTitle("MC ttjets : Fraction of Weighted ttbb Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttbb_frac_weighted_ttjets->SetName("njets_btags_Z_tight_ttbb_frac_weighted_ttjets");
	njets_btags_Z_tight_ttbb_frac_weighted_ttjets->SetTitle("MC ttjets : Fraction of Weighted ttbb Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_ttbb_frac_weighted_acc_ttjets->SetName("njets_btags_Z_loose_ttbb_frac_weighted_acc_ttjets");
	njets_btags_Z_loose_ttbb_frac_weighted_acc_ttjets->SetTitle("MC ttjets : Fraction of Accumulative Weighted ttbb Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttbb_frac_weighted_acc_ttjets->SetName("njets_btags_Z_tight_ttbb_frac_weighted_acc_ttjets");
	njets_btags_Z_tight_ttbb_frac_weighted_acc_ttjets->SetTitle("MC ttjets : Fraction of Accumulative Weighted ttbb Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	njets_btags_Z_loose_ttb_frac_weighted_ttjets->SetName("njets_btags_Z_loose_ttb_frac_weighted_ttjets");
	njets_btags_Z_loose_ttb_frac_weighted_ttjets->SetTitle("MC ttjets : Fraction of Weighted ttb Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttb_frac_weighted_ttjets->SetName("njets_btags_Z_tight_ttb_frac_weighted_ttjets");
	njets_btags_Z_tight_ttb_frac_weighted_ttjets->SetTitle("MC ttjets : Fraction of Weighted ttb Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_ttb_frac_weighted_acc_ttjets->SetName("njets_btags_Z_loose_ttb_frac_weighted_acc_ttjets");
	njets_btags_Z_loose_ttb_frac_weighted_acc_ttjets->SetTitle("MC ttjets : Fraction of Accumulative Weighted ttb Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_ttb_frac_weighted_acc_ttjets->SetName("njets_btags_Z_tight_ttb_frac_weighted_acc_ttjets");
	njets_btags_Z_tight_ttb_frac_weighted_acc_ttjets->SetTitle("MC ttjets : Fraction of Accumulative Weighted ttb Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	njets_btags_Z_loose_tt2b_frac_weighted_ttjets->SetName("njets_btags_Z_loose_tt2b_frac_weighted_ttjets");
	njets_btags_Z_loose_tt2b_frac_weighted_ttjets->SetTitle("MC ttjets : Fraction of Weighted tt2b Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_tt2b_frac_weighted_ttjets->SetName("njets_btags_Z_tight_tt2b_frac_weighted_ttjets");
	njets_btags_Z_tight_tt2b_frac_weighted_ttjets->SetTitle("MC ttjets : Fraction of Weighted tt2b Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_tt2b_frac_weighted_acc_ttjets->SetName("njets_btags_Z_loose_tt2b_frac_weighted_acc_ttjets");
	njets_btags_Z_loose_tt2b_frac_weighted_acc_ttjets->SetTitle("MC ttjets : Fraction of Accumulative Weighted tt2b Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_tt2b_frac_weighted_acc_ttjets->SetName("njets_btags_Z_tight_tt2b_frac_weighted_acc_ttjets");
	njets_btags_Z_tight_tt2b_frac_weighted_acc_ttjets->SetTitle("MC ttjets : Fraction of Accumulative Weighted tt2b Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");

	// Adding all Backgrounds

	TH2D *njets_btags_Z_loose_total_all_bkgd = (TH2D*) njets_btags_Z_loose_total_DY->Clone();
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_ttZ_llnunu);
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_st_antitw);
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_st_s);
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_st_t);
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_st_t_anti);
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_st_tw);
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_ttHbb);
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_ttHnonbb);
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_ttZ_qq);
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_ttw_lnu);
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_ttw_qq);
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_wjets);
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_wwjets);
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_wzjets);
	njets_btags_Z_loose_total_all_bkgd->Add(njets_btags_Z_loose_total_zzjets);

	TH2D *njets_btags_Z_tight_total_all_bkgd = (TH2D*) njets_btags_Z_tight_total_DY->Clone();
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_ttZ_llnunu);
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_st_antitw);
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_st_s);
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_st_t);
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_st_t_anti);
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_st_tw);
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_ttHbb);
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_ttHnonbb);
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_ttZ_qq);
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_ttw_lnu);
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_ttw_qq);
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_wjets);
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_wwjets);
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_wzjets);
	njets_btags_Z_tight_total_all_bkgd->Add(njets_btags_Z_tight_total_zzjets);

	TH2D *njets_btags_Z_loose_total_acc_all_bkgd = (TH2D*) njets_btags_Z_loose_total_acc_DY->Clone();
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_ttZ_llnunu);
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_st_antitw);
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_st_s);
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_st_t);
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_st_t_anti);
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_st_tw);
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_ttHbb);
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_ttHnonbb);
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_ttZ_qq);
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_ttw_lnu);
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_ttw_qq);
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_wjets);
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_wwjets);
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_wzjets);
	njets_btags_Z_loose_total_acc_all_bkgd->Add(njets_btags_Z_loose_total_acc_zzjets);

	TH2D *njets_btags_Z_tight_total_acc_all_bkgd = (TH2D*) njets_btags_Z_tight_total_acc_DY->Clone();
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_ttZ_llnunu);
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_st_antitw);
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_st_s);
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_st_t);
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_st_t_anti);
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_st_tw);
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_ttHbb);
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_ttHnonbb);
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_ttZ_qq);
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_ttw_lnu);
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_ttw_qq);
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_wjets);
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_wwjets);
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_wzjets);
	njets_btags_Z_tight_total_acc_all_bkgd->Add(njets_btags_Z_tight_total_acc_zzjets);

	TH2D *njets_btags_Z_loose_total_weighted_all_bkgd = (TH2D*) njets_btags_Z_loose_total_weighted_DY->Clone();
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_ttZ_llnunu);
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_st_antitw);
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_st_s);
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_st_t);
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_st_t_anti);
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_st_tw);
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_ttHbb);
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_ttHnonbb);
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_ttZ_qq);
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_ttw_lnu);
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_ttw_qq);
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_wjets);
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_wwjets);
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_wzjets);
	njets_btags_Z_loose_total_weighted_all_bkgd->Add(njets_btags_Z_loose_total_weighted_zzjets);

	TH2D *njets_btags_Z_tight_total_weighted_all_bkgd = (TH2D*) njets_btags_Z_tight_total_weighted_DY->Clone();
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_ttZ_llnunu);
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_st_antitw);
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_st_s);
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_st_t);
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_st_t_anti);
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_st_tw);
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_ttHbb);
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_ttHnonbb);
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_ttZ_qq);
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_ttw_lnu);
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_ttw_qq);
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_wjets);
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_wwjets);
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_wzjets);
	njets_btags_Z_tight_total_weighted_all_bkgd->Add(njets_btags_Z_tight_total_weighted_zzjets);

	TH2D *njets_btags_Z_loose_total_weighted_acc_all_bkgd = (TH2D*) njets_btags_Z_loose_total_weighted_acc_DY->Clone();
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_ttZ_llnunu);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_st_antitw);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_st_s);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_st_t);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_st_t_anti);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_st_tw);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_ttHbb);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_ttHnonbb);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_ttZ_qq);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_ttw_lnu);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_ttw_qq);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_wjets);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_wwjets);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_wzjets);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Add(njets_btags_Z_loose_total_weighted_acc_zzjets);

	TH2D *njets_btags_Z_tight_total_weighted_acc_all_bkgd = (TH2D*) njets_btags_Z_tight_total_weighted_acc_DY->Clone();
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_ttZ_llnunu);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_st_antitw);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_st_s);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_st_t);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_st_t_anti);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_st_tw);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_ttHbb);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_ttHnonbb);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_ttZ_qq);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_ttw_lnu);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_ttw_qq);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_wjets);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_wwjets);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_wzjets);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Add(njets_btags_Z_tight_total_weighted_acc_zzjets);



	njets_btags_Z_loose_total_all_bkgd->SetName("njets_btags_Z_loose_total_all_bkgd");
	njets_btags_Z_loose_total_all_bkgd->SetTitle("MC All Background : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_all_bkgd->SetName("njets_btags_Z_tight_total_all_bkgd");
	njets_btags_Z_tight_total_all_bkgd->SetTitle("MC All Background : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_all_bkgd->SetName("njets_btags_Z_loose_total_acc_all_bkgd");
	njets_btags_Z_loose_total_acc_all_bkgd->SetTitle("MC All Background : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_all_bkgd->SetName("njets_btags_Z_tight_total_acc_all_bkgd");
	njets_btags_Z_tight_total_acc_all_bkgd->SetTitle("MC All Background : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_all_bkgd->SetName("njets_btags_Z_loose_total_weighted_all_bkgd");
	njets_btags_Z_loose_total_weighted_all_bkgd->SetTitle("MC All Background : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_all_bkgd->SetName("njets_btags_Z_tight_total_weighted_all_bkgd");
	njets_btags_Z_tight_total_weighted_all_bkgd->SetTitle("MC All Background : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->SetName("njets_btags_Z_loose_total_weighted_acc_all_bkgd");
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->SetTitle("MC All Background : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->SetName("njets_btags_Z_tight_total_weighted_acc_all_bkgd");
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->SetTitle("MC All Background : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");



	// ttjets over Background ratio

	TH2D *njets_btags_Z_loose_total_sob = (TH2D*) njets_btags_Z_loose_total_ttjets->Clone();
	njets_btags_Z_loose_total_sob->Divide(njets_btags_Z_loose_total_all_bkgd);
	TH2D *njets_btags_Z_tight_total_sob = (TH2D*) njets_btags_Z_tight_total_ttjets->Clone();
	njets_btags_Z_tight_total_sob->Divide(njets_btags_Z_tight_total_all_bkgd);
	TH2D *njets_btags_Z_loose_total_acc_sob = (TH2D*) njets_btags_Z_loose_total_acc_ttjets->Clone();
	njets_btags_Z_loose_total_acc_sob->Divide(njets_btags_Z_loose_total_acc_all_bkgd);
	TH2D *njets_btags_Z_tight_total_acc_sob = (TH2D*) njets_btags_Z_tight_total_acc_ttjets->Clone();
	njets_btags_Z_tight_total_acc_sob->Divide(njets_btags_Z_tight_total_acc_all_bkgd);
	TH2D *njets_btags_Z_loose_total_weighted_sob = (TH2D*) njets_btags_Z_loose_total_weighted_ttjets->Clone();
	njets_btags_Z_loose_total_weighted_sob->Divide(njets_btags_Z_loose_total_weighted_all_bkgd);
	TH2D *njets_btags_Z_tight_total_weighted_sob = (TH2D*) njets_btags_Z_tight_total_weighted_ttjets->Clone();
	njets_btags_Z_tight_total_weighted_sob->Divide(njets_btags_Z_tight_total_weighted_all_bkgd);
	TH2D *njets_btags_Z_loose_total_weighted_acc_sob = (TH2D*) njets_btags_Z_loose_total_weighted_acc_ttjets->Clone();
	njets_btags_Z_loose_total_weighted_acc_sob->Divide(njets_btags_Z_loose_total_weighted_acc_all_bkgd);
	TH2D *njets_btags_Z_tight_total_weighted_acc_sob = (TH2D*) njets_btags_Z_tight_total_weighted_acc_ttjets->Clone();
	njets_btags_Z_tight_total_weighted_acc_sob->Divide(njets_btags_Z_tight_total_weighted_acc_all_bkgd);

	njets_btags_Z_loose_total_sob->SetName("njets_btags_Z_loose_total_sob");
	njets_btags_Z_loose_total_sob->SetTitle("MC ttjets/Background : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_sob->SetName("njets_btags_Z_tight_total_sob");
	njets_btags_Z_tight_total_sob->SetTitle("MC ttjets/Background : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_sob->SetName("njets_btags_Z_loose_total_acc_sob");
	njets_btags_Z_loose_total_acc_sob->SetTitle("MC ttjets/Background : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_sob->SetName("njets_btags_Z_tight_total_acc_sob");
	njets_btags_Z_tight_total_acc_sob->SetTitle("MC ttjets/Background : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_sob->SetName("njets_btags_Z_loose_total_weighted_sob");
	njets_btags_Z_loose_total_weighted_sob->SetTitle("MC ttjets/Background : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_sob->SetName("njets_btags_Z_tight_total_weighted_sob");
	njets_btags_Z_tight_total_weighted_sob->SetTitle("MC ttjets/Background : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_sob->SetName("njets_btags_Z_loose_total_weighted_acc_sob");
	njets_btags_Z_loose_total_weighted_acc_sob->SetTitle("MC ttjets/Background : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_sob->SetName("njets_btags_Z_tight_total_weighted_acc_sob");
	njets_btags_Z_tight_total_weighted_acc_sob->SetTitle("MC ttjets/Background : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");


	// All Background without DY

	TH2D *njets_btags_Z_loose_total_all_bkgd_no_dy = (TH2D*) njets_btags_Z_loose_total_all_bkgd->Clone();
	njets_btags_Z_loose_total_all_bkgd_no_dy->Add(njets_btags_Z_loose_total_DY, -1);
	TH2D *njets_btags_Z_tight_total_all_bkgd_no_dy = (TH2D*) njets_btags_Z_tight_total_all_bkgd->Clone();
	njets_btags_Z_tight_total_all_bkgd_no_dy->Add(njets_btags_Z_tight_total_DY, -1);
	TH2D *njets_btags_Z_loose_total_acc_all_bkgd_no_dy = (TH2D*) njets_btags_Z_loose_total_acc_all_bkgd->Clone();
	njets_btags_Z_loose_total_acc_all_bkgd_no_dy->Add(njets_btags_Z_loose_total_acc_DY, -1);
	TH2D *njets_btags_Z_tight_total_acc_all_bkgd_no_dy = (TH2D*) njets_btags_Z_tight_total_acc_all_bkgd->Clone();
	njets_btags_Z_tight_total_acc_all_bkgd_no_dy->Add(njets_btags_Z_tight_total_acc_DY, -1);
	TH2D *njets_btags_Z_loose_total_weighted_all_bkgd_no_dy = (TH2D*) njets_btags_Z_loose_total_weighted_all_bkgd->Clone();
	njets_btags_Z_loose_total_weighted_all_bkgd_no_dy->Add(njets_btags_Z_loose_total_weighted_DY, -1);
	TH2D *njets_btags_Z_tight_total_weighted_all_bkgd_no_dy = (TH2D*) njets_btags_Z_tight_total_weighted_all_bkgd->Clone();
	njets_btags_Z_tight_total_weighted_all_bkgd_no_dy->Add(njets_btags_Z_tight_total_weighted_DY, -1);
	TH2D *njets_btags_Z_loose_total_weighted_acc_all_bkgd_no_dy = (TH2D*) njets_btags_Z_loose_total_weighted_acc_all_bkgd->Clone();
	njets_btags_Z_loose_total_weighted_acc_all_bkgd_no_dy->Add(njets_btags_Z_loose_total_weighted_acc_DY, -1);
	TH2D *njets_btags_Z_tight_total_weighted_acc_all_bkgd_no_dy = (TH2D*) njets_btags_Z_tight_total_weighted_acc_all_bkgd->Clone();
	njets_btags_Z_tight_total_weighted_acc_all_bkgd_no_dy->Add(njets_btags_Z_tight_total_weighted_acc_DY, -1);

	njets_btags_Z_loose_total_all_bkgd_no_dy->SetName("njets_btags_Z_loose_total_all_bkgd_no_dy");
	njets_btags_Z_loose_total_all_bkgd_no_dy->SetTitle("MC All Background without DY : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_all_bkgd_no_dy->SetName("njets_btags_Z_tight_total_all_bkgd_no_dy");
	njets_btags_Z_tight_total_all_bkgd_no_dy->SetTitle("MC All Background without DY : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_all_bkgd_no_dy->SetName("njets_btags_Z_loose_total_acc_all_bkgd_no_dy");
	njets_btags_Z_loose_total_acc_all_bkgd_no_dy->SetTitle("MC All Background without DY : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_all_bkgd_no_dy->SetName("njets_btags_Z_tight_total_acc_all_bkgd_no_dy");
	njets_btags_Z_tight_total_acc_all_bkgd_no_dy->SetTitle("MC All Background without DY : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_all_bkgd_no_dy->SetName("njets_btags_Z_loose_total_weighted_all_bkgd_no_dy");
	njets_btags_Z_loose_total_weighted_all_bkgd_no_dy->SetTitle("MC All Background without DY : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_all_bkgd_no_dy->SetName("njets_btags_Z_tight_total_weighted_all_bkgd_no_dy");
	njets_btags_Z_tight_total_weighted_all_bkgd_no_dy->SetTitle("MC All Background without DY : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_all_bkgd_no_dy->SetName("njets_btags_Z_loose_total_weighted_acc_all_bkgd_no_dy");
	njets_btags_Z_loose_total_weighted_acc_all_bkgd_no_dy->SetTitle("MC All Background without DY : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_all_bkgd_no_dy->SetName("njets_btags_Z_tight_total_weighted_acc_all_bkgd_no_dy");
	njets_btags_Z_tight_total_weighted_acc_all_bkgd_no_dy->SetTitle("MC All Background without DY : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");


	// ttjets over All Background without DY ratio

	TH2D *njets_btags_Z_loose_total_sob_no_dy = (TH2D*) njets_btags_Z_loose_total_ttjets->Clone();
	njets_btags_Z_loose_total_sob_no_dy->Divide(njets_btags_Z_loose_total_all_bkgd_no_dy);
	TH2D *njets_btags_Z_tight_total_sob_no_dy = (TH2D*) njets_btags_Z_tight_total_ttjets->Clone();
	njets_btags_Z_tight_total_sob_no_dy->Divide(njets_btags_Z_tight_total_all_bkgd_no_dy);
	TH2D *njets_btags_Z_loose_total_acc_sob_no_dy = (TH2D*) njets_btags_Z_loose_total_acc_ttjets->Clone();
	njets_btags_Z_loose_total_acc_sob_no_dy->Divide(njets_btags_Z_loose_total_acc_all_bkgd_no_dy);
	TH2D *njets_btags_Z_tight_total_acc_sob_no_dy = (TH2D*) njets_btags_Z_tight_total_acc_ttjets->Clone();
	njets_btags_Z_tight_total_acc_sob_no_dy->Divide(njets_btags_Z_tight_total_acc_all_bkgd_no_dy);
	TH2D *njets_btags_Z_loose_total_weighted_sob_no_dy = (TH2D*) njets_btags_Z_loose_total_weighted_ttjets->Clone();
	njets_btags_Z_loose_total_weighted_sob_no_dy->Divide(njets_btags_Z_loose_total_weighted_all_bkgd_no_dy);
	TH2D *njets_btags_Z_tight_total_weighted_sob_no_dy = (TH2D*) njets_btags_Z_tight_total_weighted_ttjets->Clone();
	njets_btags_Z_tight_total_weighted_sob_no_dy->Divide(njets_btags_Z_tight_total_weighted_all_bkgd_no_dy);
	TH2D *njets_btags_Z_loose_total_weighted_acc_sob_no_dy = (TH2D*) njets_btags_Z_loose_total_weighted_acc_ttjets->Clone();
	njets_btags_Z_loose_total_weighted_acc_sob_no_dy->Divide(njets_btags_Z_loose_total_weighted_acc_all_bkgd_no_dy);
	TH2D *njets_btags_Z_tight_total_weighted_acc_sob_no_dy = (TH2D*) njets_btags_Z_tight_total_weighted_acc_ttjets->Clone();
	njets_btags_Z_tight_total_weighted_acc_sob_no_dy->Divide(njets_btags_Z_tight_total_weighted_acc_all_bkgd_no_dy);

	njets_btags_Z_loose_total_sob_no_dy->SetName("njets_btags_Z_loose_total_sob_no_dy");
	njets_btags_Z_loose_total_sob_no_dy->SetTitle("MC ttjets/Background without DY : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_sob_no_dy->SetName("njets_btags_Z_tight_total_sob_no_dy");
	njets_btags_Z_tight_total_sob_no_dy->SetTitle("MC ttjets/Background without DY : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_sob_no_dy->SetName("njets_btags_Z_loose_total_acc_sob_no_dy");
	njets_btags_Z_loose_total_acc_sob_no_dy->SetTitle("MC ttjets/Background without DY : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_sob_no_dy->SetName("njets_btags_Z_tight_total_acc_sob_no_dy");
	njets_btags_Z_tight_total_acc_sob_no_dy->SetTitle("MC ttjets/Background without DY : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_sob_no_dy->SetName("njets_btags_Z_loose_total_weighted_sob_no_dy");
	njets_btags_Z_loose_total_weighted_sob_no_dy->SetTitle("MC ttjets/Background without DY : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_sob_no_dy->SetName("njets_btags_Z_tight_total_weighted_sob_no_dy");
	njets_btags_Z_tight_total_weighted_sob_no_dy->SetTitle("MC ttjets/Background without DY : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_sob_no_dy->SetName("njets_btags_Z_loose_total_weighted_acc_sob_no_dy");
	njets_btags_Z_loose_total_weighted_acc_sob_no_dy->SetTitle("MC ttjets/Background without DY : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_sob_no_dy->SetName("njets_btags_Z_tight_total_weighted_acc_sob_no_dy");
	njets_btags_Z_tight_total_weighted_acc_sob_no_dy->SetTitle("MC ttjets/Background without DY : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");


	// All Background without DY over All Background ratio

	TH2D *njets_btags_Z_loose_total_bnody_ball = (TH2D*) njets_btags_Z_loose_total_all_bkgd_no_dy->Clone();
	njets_btags_Z_loose_total_bnody_ball->Divide(njets_btags_Z_loose_total_all_bkgd);
	TH2D *njets_btags_Z_tight_total_bnody_ball = (TH2D*) njets_btags_Z_tight_total_all_bkgd_no_dy->Clone();
	njets_btags_Z_tight_total_bnody_ball->Divide(njets_btags_Z_tight_total_all_bkgd);
	TH2D *njets_btags_Z_loose_total_acc_bnody_ball = (TH2D*) njets_btags_Z_loose_total_acc_all_bkgd_no_dy->Clone();
	njets_btags_Z_loose_total_acc_bnody_ball->Divide(njets_btags_Z_loose_total_acc_all_bkgd);
	TH2D *njets_btags_Z_tight_total_acc_bnody_ball = (TH2D*) njets_btags_Z_tight_total_acc_all_bkgd_no_dy->Clone();
	njets_btags_Z_tight_total_acc_bnody_ball->Divide(njets_btags_Z_tight_total_acc_all_bkgd);
	TH2D *njets_btags_Z_loose_total_weighted_bnody_ball = (TH2D*) njets_btags_Z_loose_total_weighted_all_bkgd_no_dy->Clone();
	njets_btags_Z_loose_total_weighted_bnody_ball->Divide(njets_btags_Z_loose_total_weighted_all_bkgd);
	TH2D *njets_btags_Z_tight_total_weighted_bnody_ball = (TH2D*) njets_btags_Z_tight_total_weighted_all_bkgd_no_dy->Clone();
	njets_btags_Z_tight_total_weighted_bnody_ball->Divide(njets_btags_Z_tight_total_weighted_all_bkgd);
	TH2D *njets_btags_Z_loose_total_weighted_acc_bnody_ball = (TH2D*) njets_btags_Z_loose_total_weighted_acc_all_bkgd_no_dy->Clone();
	njets_btags_Z_loose_total_weighted_acc_bnody_ball->Divide(njets_btags_Z_loose_total_weighted_acc_all_bkgd);
	TH2D *njets_btags_Z_tight_total_weighted_acc_bnody_ball = (TH2D*) njets_btags_Z_tight_total_weighted_acc_all_bkgd_no_dy->Clone();
	njets_btags_Z_tight_total_weighted_acc_bnody_ball->Divide(njets_btags_Z_tight_total_weighted_acc_all_bkgd);

	njets_btags_Z_loose_total_bnody_ball->SetName("njets_btags_Z_loose_total_bnody_ball");
	njets_btags_Z_loose_total_bnody_ball->SetTitle("MC Background without DY/All Background : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_bnody_ball->SetName("njets_btags_Z_tight_total_bnody_ball");
	njets_btags_Z_tight_total_bnody_ball->SetTitle("MC Background without DY/All Background : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_bnody_ball->SetName("njets_btags_Z_loose_total_acc_bnody_ball");
	njets_btags_Z_loose_total_acc_bnody_ball->SetTitle("MC Background without DY/All Background : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_bnody_ball->SetName("njets_btags_Z_tight_total_acc_bnody_ball");
	njets_btags_Z_tight_total_acc_bnody_ball->SetTitle("MC Background without DY/All Background : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_bnody_ball->SetName("njets_btags_Z_loose_total_weighted_bnody_ball");
	njets_btags_Z_loose_total_weighted_bnody_ball->SetTitle("MC Background without DY/All Background : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_bnody_ball->SetName("njets_btags_Z_tight_total_weighted_bnody_ball");
	njets_btags_Z_tight_total_weighted_bnody_ball->SetTitle("MC Background without DY/All Background : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_bnody_ball->SetName("njets_btags_Z_loose_total_weighted_acc_bnody_ball");
	njets_btags_Z_loose_total_weighted_acc_bnody_ball->SetTitle("MC Background without DY/All Background : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_bnody_ball->SetName("njets_btags_Z_tight_total_weighted_acc_bnody_ball");
	njets_btags_Z_tight_total_weighted_acc_bnody_ball->SetTitle("MC Background without DY/All Background : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");


	// ttjets over DY only ratio

	TH2D *njets_btags_Z_loose_total_sody = (TH2D*) njets_btags_Z_loose_total_ttjets->Clone();
	njets_btags_Z_loose_total_sody->Divide(njets_btags_Z_loose_total_DY);
	TH2D *njets_btags_Z_tight_total_sody = (TH2D*) njets_btags_Z_tight_total_ttjets->Clone();
	njets_btags_Z_tight_total_sody->Divide(njets_btags_Z_tight_total_DY);
	TH2D *njets_btags_Z_loose_total_acc_sody = (TH2D*) njets_btags_Z_loose_total_acc_ttjets->Clone();
	njets_btags_Z_loose_total_acc_sody->Divide(njets_btags_Z_loose_total_acc_DY);
	TH2D *njets_btags_Z_tight_total_acc_sody = (TH2D*) njets_btags_Z_tight_total_acc_ttjets->Clone();
	njets_btags_Z_tight_total_acc_sody->Divide(njets_btags_Z_tight_total_acc_DY);
	TH2D *njets_btags_Z_loose_total_weighted_sody = (TH2D*) njets_btags_Z_loose_total_weighted_ttjets->Clone();
	njets_btags_Z_loose_total_weighted_sody->Divide(njets_btags_Z_loose_total_weighted_DY);
	TH2D *njets_btags_Z_tight_total_weighted_sody = (TH2D*) njets_btags_Z_tight_total_weighted_ttjets->Clone();
	njets_btags_Z_tight_total_weighted_sody->Divide(njets_btags_Z_tight_total_weighted_DY);
	TH2D *njets_btags_Z_loose_total_weighted_acc_sody = (TH2D*) njets_btags_Z_loose_total_weighted_acc_ttjets->Clone();
	njets_btags_Z_loose_total_weighted_acc_sody->Divide(njets_btags_Z_loose_total_weighted_acc_DY);
	TH2D *njets_btags_Z_tight_total_weighted_acc_sody = (TH2D*) njets_btags_Z_tight_total_weighted_acc_ttjets->Clone();
	njets_btags_Z_tight_total_weighted_acc_sody->Divide(njets_btags_Z_tight_total_weighted_acc_DY);

	njets_btags_Z_loose_total_sody->SetName("njets_btags_Z_loose_total_sody");
	njets_btags_Z_loose_total_sody->SetTitle("MC ttjets/DY : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_sody->SetName("njets_btags_Z_tight_total_sody");
	njets_btags_Z_tight_total_sody->SetTitle("MC ttjets/DY : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_sody->SetName("njets_btags_Z_loose_total_acc_sody");
	njets_btags_Z_loose_total_acc_sody->SetTitle("MC ttjets/DY : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_sody->SetName("njets_btags_Z_tight_total_acc_sody");
	njets_btags_Z_tight_total_acc_sody->SetTitle("MC ttjets/DY : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_sody->SetName("njets_btags_Z_loose_total_weighted_sody");
	njets_btags_Z_loose_total_weighted_sody->SetTitle("MC ttjets/DY : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_sody->SetName("njets_btags_Z_tight_total_weighted_sody");
	njets_btags_Z_tight_total_weighted_sody->SetTitle("MC ttjets/DY : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_sody->SetName("njets_btags_Z_loose_total_weighted_acc_sody");
	njets_btags_Z_loose_total_weighted_acc_sody->SetTitle("MC ttjets/DY : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_sody->SetName("njets_btags_Z_tight_total_weighted_acc_sody");
	njets_btags_Z_tight_total_weighted_acc_sody->SetTitle("MC ttjets/DY : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");


	// ttjets over ttHbb only ratio

	TH2D *njets_btags_Z_loose_total_sottHbb = (TH2D*) njets_btags_Z_loose_total_ttjets->Clone();
	njets_btags_Z_loose_total_sottHbb->Divide(njets_btags_Z_loose_total_ttHbb);
	TH2D *njets_btags_Z_tight_total_sottHbb = (TH2D*) njets_btags_Z_tight_total_ttjets->Clone();
	njets_btags_Z_tight_total_sottHbb->Divide(njets_btags_Z_tight_total_ttHbb);
	TH2D *njets_btags_Z_loose_total_acc_sottHbb = (TH2D*) njets_btags_Z_loose_total_acc_ttjets->Clone();
	njets_btags_Z_loose_total_acc_sottHbb->Divide(njets_btags_Z_loose_total_acc_ttHbb);
	TH2D *njets_btags_Z_tight_total_acc_sottHbb = (TH2D*) njets_btags_Z_tight_total_acc_ttjets->Clone();
	njets_btags_Z_tight_total_acc_sottHbb->Divide(njets_btags_Z_tight_total_acc_ttHbb);
	TH2D *njets_btags_Z_loose_total_weighted_sottHbb = (TH2D*) njets_btags_Z_loose_total_weighted_ttjets->Clone();
	njets_btags_Z_loose_total_weighted_sottHbb->Divide(njets_btags_Z_loose_total_weighted_ttHbb);
	TH2D *njets_btags_Z_tight_total_weighted_sottHbb = (TH2D*) njets_btags_Z_tight_total_weighted_ttjets->Clone();
	njets_btags_Z_tight_total_weighted_sottHbb->Divide(njets_btags_Z_tight_total_weighted_ttHbb);
	TH2D *njets_btags_Z_loose_total_weighted_acc_sottHbb = (TH2D*) njets_btags_Z_loose_total_weighted_acc_ttjets->Clone();
	njets_btags_Z_loose_total_weighted_acc_sottHbb->Divide(njets_btags_Z_loose_total_weighted_acc_ttHbb);
	TH2D *njets_btags_Z_tight_total_weighted_acc_sottHbb = (TH2D*) njets_btags_Z_tight_total_weighted_acc_ttjets->Clone();
	njets_btags_Z_tight_total_weighted_acc_sottHbb->Divide(njets_btags_Z_tight_total_weighted_acc_ttHbb);

	njets_btags_Z_loose_total_sottHbb->SetName("njets_btags_Z_loose_total_sottHbb");
	njets_btags_Z_loose_total_sottHbb->SetTitle("MC ttjets/ttHbb : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_sottHbb->SetName("njets_btags_Z_tight_total_sottHbb");
	njets_btags_Z_tight_total_sottHbb->SetTitle("MC ttjets/ttHbb : Total Nr. of Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_acc_sottHbb->SetName("njets_btags_Z_loose_total_acc_sottHbb");
	njets_btags_Z_loose_total_acc_sottHbb->SetTitle("MC ttjets/ttHbb : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_acc_sottHbb->SetName("njets_btags_Z_tight_total_acc_sottHbb");
	njets_btags_Z_tight_total_acc_sottHbb->SetTitle("MC ttjets/ttHbb : Total Nr. of Accumulative Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_sottHbb->SetName("njets_btags_Z_loose_total_weighted_sottHbb");
	njets_btags_Z_loose_total_weighted_sottHbb->SetTitle("MC ttjets/ttHbb : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_sottHbb->SetName("njets_btags_Z_tight_total_weighted_sottHbb");
	njets_btags_Z_tight_total_weighted_sottHbb->SetTitle("MC ttjets/ttHbb : Total Nr. of Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");
	njets_btags_Z_loose_total_weighted_acc_sottHbb->SetName("njets_btags_Z_loose_total_weighted_acc_sottHbb");
	njets_btags_Z_loose_total_weighted_acc_sottHbb->SetTitle("MC ttjets/ttHbb : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_tight_total_weighted_acc_sottHbb->SetName("njets_btags_Z_tight_total_weighted_acc_sottHbb");
	njets_btags_Z_tight_total_weighted_acc_sottHbb->SetTitle("MC ttjets/ttHbb : Total Nr. of Accumulative Weighted Events vs Jet and BTag Multiplicity for 88 < M(ll) < 94");



	// Plotting Histograms

	gStyle->SetLegendBorderSize(0);
	gStyle->SetLegendTextSize(0.03);

	// M(ll) Distribution

	TCanvas *m1 = new TCanvas("m1","test",1100,650);
	mll_Z_loose_all->SetStats(0);
	mll_Z_loose_all->Draw("same");
	m1->Print("Mll_Z_loose_all.pdf");
	delete m1;

	TCanvas *m2 = new TCanvas("m2","test",1100,650);
	mll_Z_tight_all->SetStats(0);
	mll_Z_tight_all->Draw("same");
	m2->Print("Mll_Z_tight_all.pdf");
	delete m2;

	TCanvas *m3 = new TCanvas("m3","test",1100,650);
	mll_Z_loose_weighted_all->SetStats(0);
	mll_Z_loose_weighted_all->Draw("same");
	m3->Print("Mll_Z_loose_weighted_all.pdf");
	delete m3;

	TCanvas *m4 = new TCanvas("m4","test",1100,650);
	mll_Z_tight_weighted_all->SetStats(0);
	mll_Z_tight_weighted_all->Draw("same");
	m4->Print("Mll_Z_tight_weighted_all.pdf");
	delete m4;

	TCanvas *m5 = new TCanvas("m5","test",1100,650);
	mll_Z_loose_ttjets->SetStats(0);
	mll_Z_loose_ttjets->Draw("same");
	m5->Print("Mll_Z_loose_ttjets.pdf");
	delete m5;

	TCanvas *m6 = new TCanvas("m6","test",1100,650);
	mll_Z_tight_ttjets->SetStats(0);
	mll_Z_tight_ttjets->Draw("same");
	m6->Print("Mll_Z_tight_ttjets.pdf");
	delete m6;

	TCanvas *m7 = new TCanvas("m7","test",1100,650);
	mll_Z_loose_DY->SetStats(0);
	mll_Z_loose_DY->Draw("same");
	m7->Print("Mll_Z_loose_DY.pdf");
	delete m7;

	TCanvas *m8 = new TCanvas("m8","test",1100,650);
	mll_Z_tight_DY->SetStats(0);
	mll_Z_tight_DY->Draw("same");
	m8->Print("Mll_Z_tight_DY.pdf");
	delete m8;

	// B-tagging and mistagging efficiencies for ttjets MC sample

	TCanvas *bt1 = new TCanvas("bt1","test",1100,650);
	bt1->DrawFrame(0,0,500,1.03,"MC ttjets : B-Tagging and Mis-Tagging Efficiency vs Jet Pt; Jet Pt (GeV) ; Efficiency");
	TLegend* leg1;
	leg1 = new TLegend(0.65,0.65,0.85,0.85);
	TLine *line1 = new TLine(0,1,500,1);
	line1->SetLineStyle(kDashed);
	line1->SetLineWidth(1);
	leg1->SetFillColor(kWhite);
	leg1->SetFillStyle(1001);
	leg1->AddEntry(b_tag_effi_pt_ttjets,"Tag effi for b-jets","L");
	leg1->AddEntry(c_tag_effi_pt_ttjets,"MisTag effi for c-jets","L");
	leg1->AddEntry(lf_tag_effi_pt_ttjets,"MisTag effi for lf-jets","L");
	b_tag_effi_pt_ttjets->SetLineWidth(1);
	b_tag_effi_pt_ttjets->SetLineColor(1);
	b_tag_effi_pt_ttjets->Draw("same");
	c_tag_effi_pt_ttjets->SetLineWidth(1);
	c_tag_effi_pt_ttjets->SetLineColor(2);
	c_tag_effi_pt_ttjets->Draw("same");
	lf_tag_effi_pt_ttjets->SetLineWidth(1);
	lf_tag_effi_pt_ttjets->SetLineColor(6);
	lf_tag_effi_pt_ttjets->Draw("same");
	leg1->Draw("same");
	line1->Draw("same");
	bt1->Print("B_tag_mistag_effi_pt_ttjets.pdf");
	delete bt1;
	delete leg1;
	delete line1;

	TCanvas *bt2 = new TCanvas("bt2","test",1100,650);
	bt2->DrawFrame(-2.5,0,2.5,1.03,"MC ttjets : B-Tagging and Mis-Tagging Efficiency vs Jet Eta; Jet Eta ; Efficiency");
	TLegend* leg2;
	leg2 = new TLegend(0.65,0.65,0.85,0.85);
	TLine *line2 = new TLine(-2.5,1,2.5,1);
	line2->SetLineStyle(kDashed);
	line2->SetLineWidth(1);
	leg2->SetFillColor(kWhite);
	leg2->SetFillStyle(1001);
	leg2->AddEntry(b_tag_effi_eta_ttjets,"Tag effi for b-jets","L");
	leg2->AddEntry(c_tag_effi_eta_ttjets,"MisTag effi for c-jets","L");
	leg2->AddEntry(lf_tag_effi_eta_ttjets,"MisTag effi for lf-jets","L");
	b_tag_effi_eta_ttjets->SetLineWidth(1);
	b_tag_effi_eta_ttjets->SetLineColor(1);
	b_tag_effi_eta_ttjets->Draw("same");
	c_tag_effi_eta_ttjets->SetLineWidth(1);
	c_tag_effi_eta_ttjets->SetLineColor(2);
	c_tag_effi_eta_ttjets->Draw("same");
	lf_tag_effi_eta_ttjets->SetLineWidth(1);
	lf_tag_effi_eta_ttjets->SetLineColor(6);
	lf_tag_effi_eta_ttjets->Draw("same");
	leg2->Draw("same");
	line2->Draw("same");
	bt2->Print("B_tag_mistag_effi_eta_ttjets.pdf");
	delete bt2;
	delete leg2;
	delete line2;

	// 2D yields

	gStyle->SetOptStat("ne");
	gStyle->SetPalette(85,0);

	// ttjets MC sample only

	TCanvas *a1 = new TCanvas("a1","test",1100,650);
	njets_btags_Z_loose_total_ttjets->SetStats(0);
	njets_btags_Z_loose_total_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_ttjets->Draw("TEXTCOLZ");
	a1->Print("2D_loose_Z_total_ttjets.pdf");
	delete a1;

	TCanvas *a2 = new TCanvas("a2","test",1100,650);
	njets_btags_Z_loose_ttbb_ttjets->SetStats(0);
	njets_btags_Z_loose_ttbb_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttbb_ttjets->Draw("TEXTCOLZ");
	a2->Print("2D_loose_Z_ttbb_ttjets.pdf");
	delete a2;

	TCanvas *a3 = new TCanvas("a3","test",1100,650);
	njets_btags_Z_loose_ttbb_frac_ttjets->SetStats(0);
	njets_btags_Z_loose_ttbb_frac_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttbb_frac_ttjets->Draw("TEXTCOLZ");
	a3->Print("2D_loose_Z_ttbb_frac_ttjets.pdf");
	delete a3;

	TCanvas *a4 = new TCanvas("a4","test",1100,650);
	njets_btags_Z_loose_total_acc_ttjets->SetStats(0);
	njets_btags_Z_loose_total_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_acc_ttjets->Draw("TEXTCOLZ");
	a4->Print("2D_loose_Z_total_acc_ttjets.pdf");
	delete a4;

	TCanvas *a5 = new TCanvas("a5","test",1100,650);
	njets_btags_Z_loose_ttbb_acc_ttjets->SetStats(0);
	njets_btags_Z_loose_ttbb_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttbb_acc_ttjets->Draw("TEXTCOLZ");
	a5->Print("2D_loose_Z_ttbb_acc_ttjets.pdf");
	delete a5;

	TCanvas *a6 = new TCanvas("a6","test",1100,650);
	njets_btags_Z_loose_ttbb_frac_acc_ttjets->SetStats(0);
	njets_btags_Z_loose_ttbb_frac_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttbb_frac_acc_ttjets->Draw("TEXTCOLZ");
	a6->Print("2D_loose_Z_ttbb_frac_acc_ttjets.pdf");
	delete a6;

	TCanvas *a7 = new TCanvas("a7","test",1100,650);
	njets_btags_Z_tight_total_ttjets->SetStats(0);
	njets_btags_Z_tight_total_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_ttjets->Draw("TEXTCOLZ");
	a7->Print("2D_tight_Z_total_ttjets.pdf");
	delete a7;

	TCanvas *a8 = new TCanvas("a8","test",1100,650);
	njets_btags_Z_tight_ttbb_ttjets->SetStats(0);
	njets_btags_Z_tight_ttbb_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttbb_ttjets->Draw("TEXTCOLZ");
	a8->Print("2D_tight_Z_ttbb_ttjets.pdf");
	delete a8;

	TCanvas *a9 = new TCanvas("a9","test",1100,650);
	njets_btags_Z_tight_ttbb_frac_ttjets->SetStats(0);
	njets_btags_Z_tight_ttbb_frac_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttbb_frac_ttjets->Draw("TEXTCOLZ");
	a9->Print("2D_tight_Z_ttbb_frac_ttjets.pdf");
	delete a9;

	TCanvas *a10 = new TCanvas("a10","test",1100,650);
	njets_btags_Z_tight_total_acc_ttjets->SetStats(0);
	njets_btags_Z_tight_total_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_acc_ttjets->Draw("TEXTCOLZ");
	a10->Print("2D_tight_Z_total_acc_ttjets.pdf");
	delete a10;

	TCanvas *a11 = new TCanvas("a11","test",1100,650);
	njets_btags_Z_tight_ttbb_acc_ttjets->SetStats(0);
	njets_btags_Z_tight_ttbb_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttbb_acc_ttjets->Draw("TEXTCOLZ");
	a11->Print("2D_tight_Z_ttbb_acc_ttjets.pdf");
	delete a11;

	TCanvas *a12 = new TCanvas("a12","test",1100,650);
	njets_btags_Z_tight_ttbb_frac_acc_ttjets->SetStats(0);
	njets_btags_Z_tight_ttbb_frac_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttbb_frac_acc_ttjets->Draw("TEXTCOLZ");
	a12->Print("2D_tight_Z_ttbb_frac_acc_ttjets.pdf");
	delete a12;

	TCanvas *a13 = new TCanvas("a13","test",1100,650);
	njets_bjets_Z_loose_total_ttjets->SetStats(0);
	njets_bjets_Z_loose_total_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_total_ttjets->Draw("TEXTCOLZ");
	a13->Print("2D_loose_Z_total_njet_bjet_ttjets.pdf");
	delete a13;

	TCanvas *a14 = new TCanvas("a14","test",1100,650);
	njets_bjets_Z_tight_total_ttjets->SetStats(0);
	njets_bjets_Z_tight_total_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_total_ttjets->Draw("TEXTCOLZ");
	a14->Print("2D_tight_Z_total_njet_bjet_ttjets.pdf");
	delete a14;

	TCanvas *a15 = new TCanvas("a15","test",1100,650);
	njets_bjets_Z_loose_total_acc_ttjets->SetStats(0);
	njets_bjets_Z_loose_total_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_total_acc_ttjets->Draw("TEXTCOLZ");
	a15->Print("2D_loose_Z_total_njet_bjet_acc_ttjets.pdf");
	delete a15;

	TCanvas *a16 = new TCanvas("a16","test",1100,650);
	njets_bjets_Z_tight_total_acc_ttjets->SetStats(0);
	njets_bjets_Z_tight_total_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_total_acc_ttjets->Draw("TEXTCOLZ");
	a16->Print("2D_tight_Z_total_njet_bjet_acc_ttjets.pdf");
	delete a16;

	TCanvas *a17 = new TCanvas("a17","test",1100,650);
	nbjets_btags_Z_loose_total_ttjets->SetStats(0);
	nbjets_btags_Z_loose_total_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_total_ttjets->Draw("TEXTCOLZ");
	a17->Print("2D_loose_Z_total_nbjet_btag_ttjets.pdf");
	delete a17;

	TCanvas *a18 = new TCanvas("a18","test",1100,650);
	nbjets_btags_Z_tight_total_ttjets->SetStats(0);
	nbjets_btags_Z_tight_total_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_total_ttjets->Draw("TEXTCOLZ");
	a18->Print("2D_tight_Z_total_nbjet_btag_ttjets.pdf");
	delete a18;

	TCanvas *a19 = new TCanvas("a19","test",1100,650);
	nbjets_btags_Z_loose_total_acc_ttjets->SetStats(0);
	nbjets_btags_Z_loose_total_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_total_acc_ttjets->Draw("TEXTCOLZ");
	a19->Print("2D_loose_Z_total_nbjet_btag_acc_ttjets.pdf");
	delete a19;

	TCanvas *a20 = new TCanvas("a20","test",1100,650);
	nbjets_btags_Z_tight_total_acc_ttjets->SetStats(0);
	nbjets_btags_Z_tight_total_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_total_acc_ttjets->Draw("TEXTCOLZ");
	a20->Print("2D_tight_Z_total_nbjet_btag_acc_ttjets.pdf");
	delete a20;

	TCanvas *a21 = new TCanvas("a21","test",1100,650);
	njets_btags_Z_loose_ttb_frac_ttjets->SetStats(0);
	njets_btags_Z_loose_ttb_frac_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttb_frac_ttjets->Draw("TEXTCOLZ");
	a21->Print("2D_loose_Z_ttb_frac_ttjets.pdf");
	delete a21;

	TCanvas *a22 = new TCanvas("a22","test",1100,650);
	njets_btags_Z_loose_ttb_frac_acc_ttjets->SetStats(0);
	njets_btags_Z_loose_ttb_frac_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttb_frac_acc_ttjets->Draw("TEXTCOLZ");
	a22->Print("2D_loose_Z_ttb_frac_acc_ttjets.pdf");
	delete a22;

	TCanvas *a23 = new TCanvas("a23","test",1100,650);
	njets_btags_Z_loose_tt2b_frac_ttjets->SetStats(0);
	njets_btags_Z_loose_tt2b_frac_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_tt2b_frac_ttjets->Draw("TEXTCOLZ");
	a23->Print("2D_loose_Z_tt2b_frac_ttjets.pdf");
	delete a23;

	TCanvas *a24 = new TCanvas("a24","test",1100,650);
	njets_btags_Z_loose_tt2b_frac_acc_ttjets->SetStats(0);
	njets_btags_Z_loose_tt2b_frac_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_tt2b_frac_acc_ttjets->Draw("TEXTCOLZ");
	a24->Print("2D_loose_Z_tt2b_frac_acc_ttjets.pdf");
	delete a24;

	TCanvas *a25 = new TCanvas("a25","test",1100,650);
	njets_bjets_Z_loose_ttbb_ttjets->SetStats(0);
	njets_bjets_Z_loose_ttbb_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_ttbb_ttjets->Draw("TEXTCOLZ");
	a25->Print("2D_loose_Z_ttbb_njet_bjet_ttjets.pdf");
	delete a25;

	TCanvas *a26 = new TCanvas("a26","test",1100,650);
	njets_bjets_Z_tight_ttbb_ttjets->SetStats(0);
	njets_bjets_Z_tight_ttbb_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_ttbb_ttjets->Draw("TEXTCOLZ");
	a26->Print("2D_tight_Z_ttbb_njet_bjet_ttjets.pdf");
	delete a26;

	TCanvas *a27 = new TCanvas("a27","test",1100,650);
	njets_bjets_Z_loose_ttbb_acc_ttjets->SetStats(0);
	njets_bjets_Z_loose_ttbb_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_ttbb_acc_ttjets->Draw("TEXTCOLZ");
	a27->Print("2D_loose_Z_ttbb_njet_bjet_acc_ttjets.pdf");
	delete a27;

	TCanvas *a28 = new TCanvas("a28","test",1100,650);
	njets_bjets_Z_tight_ttbb_acc_ttjets->SetStats(0);
	njets_bjets_Z_tight_ttbb_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_ttbb_acc_ttjets->Draw("TEXTCOLZ");
	a28->Print("2D_tight_Z_ttbb_njet_bjet_acc_ttjets.pdf");
	delete a28;

	TCanvas *a29 = new TCanvas("a29","test",1100,650);
	nbjets_btags_Z_loose_ttbb_ttjets->SetStats(0);
	nbjets_btags_Z_loose_ttbb_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_ttbb_ttjets->Draw("TEXTCOLZ");
	a29->Print("2D_loose_Z_ttbb_nbjet_btag_ttjets.pdf");
	delete a29;

	TCanvas *a30 = new TCanvas("a30","test",1100,650);
	nbjets_btags_Z_tight_ttbb_ttjets->SetStats(0);
	nbjets_btags_Z_tight_ttbb_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_ttbb_ttjets->Draw("TEXTCOLZ");
	a30->Print("2D_tight_Z_ttbb_nbjet_btag_ttjets.pdf");
	delete a30;

	TCanvas *a31 = new TCanvas("a31","test",1100,650);
	nbjets_btags_Z_loose_ttbb_acc_ttjets->SetStats(0);
	nbjets_btags_Z_loose_ttbb_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_ttbb_acc_ttjets->Draw("TEXTCOLZ");
	a31->Print("2D_loose_Z_ttbb_nbjet_btag_acc_ttjets.pdf");
	delete a31;

	TCanvas *a32 = new TCanvas("a32","test",1100,650);
	nbjets_btags_Z_tight_ttbb_acc_ttjets->SetStats(0);
	nbjets_btags_Z_tight_ttbb_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_ttbb_acc_ttjets->Draw("TEXTCOLZ");
	a32->Print("2D_tight_Z_ttbb_nbjet_btag_acc_ttjets.pdf");
	delete a32;

	TCanvas *a33 = new TCanvas("a33","test",1100,650);
	njets_bjets_Z_loose_ttb_ttjets->SetStats(0);
	njets_bjets_Z_loose_ttb_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_ttb_ttjets->Draw("TEXTCOLZ");
	a33->Print("2D_loose_Z_ttb_njet_bjet_ttjets.pdf");
	delete a33;

	TCanvas *a34 = new TCanvas("a34","test",1100,650);
	njets_bjets_Z_tight_ttb_ttjets->SetStats(0);
	njets_bjets_Z_tight_ttb_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_ttb_ttjets->Draw("TEXTCOLZ");
	a34->Print("2D_tight_Z_ttb_njet_bjet_ttjets.pdf");
	delete a34;

	TCanvas *a35 = new TCanvas("a35","test",1100,650);
	njets_bjets_Z_loose_ttb_acc_ttjets->SetStats(0);
	njets_bjets_Z_loose_ttb_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_ttb_acc_ttjets->Draw("TEXTCOLZ");
	a35->Print("2D_loose_Z_ttb_njet_bjet_acc_ttjets.pdf");
	delete a35;

	TCanvas *a36 = new TCanvas("a36","test",1100,650);
	njets_bjets_Z_tight_ttb_acc_ttjets->SetStats(0);
	njets_bjets_Z_tight_ttb_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_ttb_acc_ttjets->Draw("TEXTCOLZ");
	a36->Print("2D_tight_Z_ttb_njet_bjet_acc_ttjets.pdf");
	delete a36;

	TCanvas *a37 = new TCanvas("a37","test",1100,650);
	nbjets_btags_Z_loose_ttb_ttjets->SetStats(0);
	nbjets_btags_Z_loose_ttb_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_ttb_ttjets->Draw("TEXTCOLZ");
	a37->Print("2D_loose_Z_ttb_nbjet_btag_ttjets.pdf");
	delete a37;

	TCanvas *a38 = new TCanvas("a38","test",1100,650);
	nbjets_btags_Z_tight_ttb_ttjets->SetStats(0);
	nbjets_btags_Z_tight_ttb_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_ttb_ttjets->Draw("TEXTCOLZ");
	a38->Print("2D_tight_Z_ttb_nbjet_btag_ttjets.pdf");
	delete a38;

	TCanvas *a39 = new TCanvas("a39","test",1100,650);
	nbjets_btags_Z_loose_ttb_acc_ttjets->SetStats(0);
	nbjets_btags_Z_loose_ttb_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_ttb_acc_ttjets->Draw("TEXTCOLZ");
	a39->Print("2D_loose_Z_ttb_nbjet_btag_acc_ttjets.pdf");
	delete a39;

	TCanvas *a40 = new TCanvas("a40","test",1100,650);
	nbjets_btags_Z_tight_ttb_acc_ttjets->SetStats(0);
	nbjets_btags_Z_tight_ttb_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_ttb_acc_ttjets->Draw("TEXTCOLZ");
	a40->Print("2D_tight_Z_ttb_nbjet_btag_acc_ttjets.pdf");
	delete a40;

	TCanvas *a41 = new TCanvas("a41","test",1100,650);
	njets_bjets_Z_loose_tt2b_ttjets->SetStats(0);
	njets_bjets_Z_loose_tt2b_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_tt2b_ttjets->Draw("TEXTCOLZ");
	a41->Print("2D_loose_Z_tt2b_njet_bjet_ttjets.pdf");
	delete a41;

	TCanvas *a42 = new TCanvas("a42","test",1100,650);
	njets_bjets_Z_tight_tt2b_ttjets->SetStats(0);
	njets_bjets_Z_tight_tt2b_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_tt2b_ttjets->Draw("TEXTCOLZ");
	a42->Print("2D_tight_Z_tt2b_njet_bjet_ttjets.pdf");
	delete a42;

	TCanvas *a43 = new TCanvas("a43","test",1100,650);
	njets_bjets_Z_loose_tt2b_acc_ttjets->SetStats(0);
	njets_bjets_Z_loose_tt2b_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_tt2b_acc_ttjets->Draw("TEXTCOLZ");
	a43->Print("2D_loose_Z_tt2b_njet_bjet_acc_ttjets.pdf");
	delete a43;

	TCanvas *a44 = new TCanvas("a44","test",1100,650);
	njets_bjets_Z_tight_tt2b_acc_ttjets->SetStats(0);
	njets_bjets_Z_tight_tt2b_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_tt2b_acc_ttjets->Draw("TEXTCOLZ");
	a44->Print("2D_tight_Z_tt2b_njet_bjet_acc_ttjets.pdf");
	delete a44;

	TCanvas *a45 = new TCanvas("a45","test",1100,650);
	nbjets_btags_Z_loose_tt2b_ttjets->SetStats(0);
	nbjets_btags_Z_loose_tt2b_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_tt2b_ttjets->Draw("TEXTCOLZ");
	a45->Print("2D_loose_Z_tt2b_nbjet_btag_ttjets.pdf");
	delete a45;

	TCanvas *a46 = new TCanvas("a46","test",1100,650);
	nbjets_btags_Z_tight_tt2b_ttjets->SetStats(0);
	nbjets_btags_Z_tight_tt2b_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_tt2b_ttjets->Draw("TEXTCOLZ");
	a46->Print("2D_tight_Z_tt2b_nbjet_btag_ttjets.pdf");
	delete a46;

	TCanvas *a47 = new TCanvas("a47","test",1100,650);
	nbjets_btags_Z_loose_tt2b_acc_ttjets->SetStats(0);
	nbjets_btags_Z_loose_tt2b_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_tt2b_acc_ttjets->Draw("TEXTCOLZ");
	a47->Print("2D_loose_Z_tt2b_nbjet_btag_acc_ttjets.pdf");
	delete a47;

	TCanvas *a48 = new TCanvas("a48","test",1100,650);
	nbjets_btags_Z_tight_tt2b_acc_ttjets->SetStats(0);
	nbjets_btags_Z_tight_tt2b_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_tt2b_acc_ttjets->Draw("TEXTCOLZ");
	a48->Print("2D_tight_Z_tt2b_nbjet_btag_acc_ttjets.pdf");
	delete a48;

	TCanvas *a49 = new TCanvas("a49","test",1100,650);
	njets_btags_Z_tight_ttb_frac_ttjets->SetStats(0);
	njets_btags_Z_tight_ttb_frac_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttb_frac_ttjets->Draw("TEXTCOLZ");
	a49->Print("2D_tight_Z_ttb_frac_ttjets.pdf");
	delete a49;

	TCanvas *a50 = new TCanvas("a50","test",1100,650);
	njets_btags_Z_tight_ttb_frac_acc_ttjets->SetStats(0);
	njets_btags_Z_tight_ttb_frac_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttb_frac_acc_ttjets->Draw("TEXTCOLZ");
	a50->Print("2D_tight_Z_ttb_frac_acc_ttjets.pdf");
	delete a50;

	TCanvas *a51 = new TCanvas("a51","test",1100,650);
	njets_btags_Z_tight_tt2b_frac_ttjets->SetStats(0);
	njets_btags_Z_tight_tt2b_frac_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_tt2b_frac_ttjets->Draw("TEXTCOLZ");
	a51->Print("2D_tight_Z_tt2b_frac_ttjets.pdf");
	delete a51;

	TCanvas *a52 = new TCanvas("a52","test",1100,650);
	njets_btags_Z_tight_tt2b_frac_acc_ttjets->SetStats(0);
	njets_btags_Z_tight_tt2b_frac_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_tt2b_frac_acc_ttjets->Draw("TEXTCOLZ");
	a52->Print("2D_tight_Z_tt2b_frac_acc_ttjets.pdf");
	delete a52;

	TCanvas *a53 = new TCanvas("a53","test",1100,650);
	njets_btags_Z_loose_ttb_ttjets->SetStats(0);
	njets_btags_Z_loose_ttb_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttb_ttjets->Draw("TEXTCOLZ");
	a53->Print("2D_loose_Z_ttb_ttjets.pdf");
	delete a53;

	TCanvas *a54 = new TCanvas("a54","test",1100,650);
	njets_btags_Z_loose_ttb_acc_ttjets->SetStats(0);
	njets_btags_Z_loose_ttb_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttb_acc_ttjets->Draw("TEXTCOLZ");
	a54->Print("2D_loose_Z_ttb_acc_ttjets.pdf");
	delete a54;

	TCanvas *a55 = new TCanvas("a55","test",1100,650);
	njets_btags_Z_loose_tt2b_ttjets->SetStats(0);
	njets_btags_Z_loose_tt2b_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_tt2b_ttjets->Draw("TEXTCOLZ");
	a55->Print("2D_loose_Z_tt2b_ttjets.pdf");
	delete a55;

	TCanvas *a56 = new TCanvas("a56","test",1100,650);
	njets_btags_Z_loose_tt2b_acc_ttjets->SetStats(0);
	njets_btags_Z_loose_tt2b_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_tt2b_acc_ttjets->Draw("TEXTCOLZ");
	a56->Print("2D_loose_Z_tt2b_acc_ttjets.pdf");
	delete a56;

	TCanvas *a57 = new TCanvas("a57","test",1100,650);
	njets_btags_Z_tight_ttb_ttjets->SetStats(0);
	njets_btags_Z_tight_ttb_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttb_ttjets->Draw("TEXTCOLZ");
	a57->Print("2D_tight_Z_ttb_ttjets.pdf");
	delete a57;

	TCanvas *a58 = new TCanvas("a58","test",1100,650);
	njets_btags_Z_tight_ttb_acc_ttjets->SetStats(0);
	njets_btags_Z_tight_ttb_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttb_acc_ttjets->Draw("TEXTCOLZ");
	a58->Print("2D_tight_Z_ttb_acc_ttjets.pdf");
	delete a58;

	TCanvas *a59 = new TCanvas("a59","test",1100,650);
	njets_btags_Z_tight_tt2b_ttjets->SetStats(0);
	njets_btags_Z_tight_tt2b_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_tt2b_ttjets->Draw("TEXTCOLZ");
	a59->Print("2D_tight_Z_tt2b_ttjets.pdf");
	delete a59;

	TCanvas *a60 = new TCanvas("a60","test",1100,650);
	njets_btags_Z_tight_tt2b_acc_ttjets->SetStats(0);
	njets_btags_Z_tight_tt2b_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_tt2b_acc_ttjets->Draw("TEXTCOLZ");
	a60->Print("2D_tight_Z_tt2b_acc_ttjets.pdf");
	delete a60;



	TCanvas *wa1 = new TCanvas("wa1","test",1100,650);
	njets_btags_Z_loose_total_weighted_ttjets->SetStats(0);
	njets_btags_Z_loose_total_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_ttjets->Draw("TEXTCOLZ");
	wa1->Print("2D_loose_Z_total_weighted_ttjets.pdf");
	delete wa1;

	TCanvas *wa2 = new TCanvas("wa2","test",1100,650);
	njets_btags_Z_loose_ttbb_weighted_ttjets->SetStats(0);
	njets_btags_Z_loose_ttbb_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttbb_weighted_ttjets->Draw("TEXTCOLZ");
	wa2->Print("2D_loose_Z_ttbb_weighted_ttjets.pdf");
	delete wa2;

	TCanvas *wa3 = new TCanvas("wa3","test",1100,650);
	njets_btags_Z_loose_ttbb_frac_weighted_ttjets->SetStats(0);
	njets_btags_Z_loose_ttbb_frac_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttbb_frac_weighted_ttjets->Draw("TEXTCOLZ");
	wa3->Print("2D_loose_Z_ttbb_frac_weighted_ttjets.pdf");
	delete wa3;

	TCanvas *wa4 = new TCanvas("wa4","test",1100,650);
	njets_btags_Z_loose_total_weighted_acc_ttjets->SetStats(0);
	njets_btags_Z_loose_total_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa4->Print("2D_loose_Z_total_weighted_acc_ttjets.pdf");
	delete wa4;

	TCanvas *wa5 = new TCanvas("wa5","test",1100,650);
	njets_btags_Z_loose_ttbb_weighted_acc_ttjets->SetStats(0);
	njets_btags_Z_loose_ttbb_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttbb_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa5->Print("2D_loose_Z_ttbb_weighted_acc_ttjets.pdf");
	delete wa5;

	TCanvas *wa6 = new TCanvas("wa6","test",1100,650);
	njets_btags_Z_loose_ttbb_frac_weighted_acc_ttjets->SetStats(0);
	njets_btags_Z_loose_ttbb_frac_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttbb_frac_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa6->Print("2D_loose_Z_ttbb_frac_weighted_acc_ttjets.pdf");
	delete wa6;

	TCanvas *wa7 = new TCanvas("wa7","test",1100,650);
	njets_btags_Z_tight_total_weighted_ttjets->SetStats(0);
	njets_btags_Z_tight_total_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_ttjets->Draw("TEXTCOLZ");
	wa7->Print("2D_tight_Z_total_weighted_ttjets.pdf");
	delete wa7;

	TCanvas *wa8 = new TCanvas("wa8","test",1100,650);
	njets_btags_Z_tight_ttbb_weighted_ttjets->SetStats(0);
	njets_btags_Z_tight_ttbb_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttbb_weighted_ttjets->Draw("TEXTCOLZ");
	wa8->Print("2D_tight_Z_ttbb_weighted_ttjets.pdf");
	delete wa8;

	TCanvas *wa9 = new TCanvas("wa9","test",1100,650);
	njets_btags_Z_tight_ttbb_frac_weighted_ttjets->SetStats(0);
	njets_btags_Z_tight_ttbb_frac_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttbb_frac_weighted_ttjets->Draw("TEXTCOLZ");
	wa9->Print("2D_tight_Z_ttbb_frac_weighted_ttjets.pdf");
	delete wa9;

	TCanvas *wa10 = new TCanvas("wa10","test",1100,650);
	njets_btags_Z_tight_total_weighted_acc_ttjets->SetStats(0);
	njets_btags_Z_tight_total_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa10->Print("2D_tight_Z_total_weighted_acc_ttjets.pdf");
	delete wa10;

	TCanvas *wa11 = new TCanvas("wa11","test",1100,650);
	njets_btags_Z_tight_ttbb_weighted_acc_ttjets->SetStats(0);
	njets_btags_Z_tight_ttbb_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttbb_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa11->Print("2D_tight_Z_ttbb_weighted_acc_ttjets.pdf");
	delete wa11;

	TCanvas *wa12 = new TCanvas("wa12","test",1100,650);
	njets_btags_Z_tight_ttbb_frac_weighted_acc_ttjets->SetStats(0);
	njets_btags_Z_tight_ttbb_frac_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttbb_frac_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa12->Print("2D_tight_Z_ttbb_frac_weighted_acc_ttjets.pdf");
	delete wa12;

	TCanvas *wa13 = new TCanvas("wa13","test",1100,650);
	njets_bjets_Z_loose_total_weighted_ttjets->SetStats(0);
	njets_bjets_Z_loose_total_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_total_weighted_ttjets->Draw("TEXTCOLZ");
	wa13->Print("2D_loose_Z_total_njet_bjet_weighted_ttjets.pdf");
	delete wa13;

	TCanvas *wa14 = new TCanvas("wa14","test",1100,650);
	njets_bjets_Z_tight_total_weighted_ttjets->SetStats(0);
	njets_bjets_Z_tight_total_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_total_weighted_ttjets->Draw("TEXTCOLZ");
	wa14->Print("2D_tight_Z_total_njet_bjet_weighted_ttjets.pdf");
	delete wa14;

	TCanvas *wa15 = new TCanvas("wa15","test",1100,650);
	njets_bjets_Z_loose_total_weighted_acc_ttjets->SetStats(0);
	njets_bjets_Z_loose_total_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_total_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa15->Print("2D_loose_Z_total_njet_bjet_weighted_acc_ttjets.pdf");
	delete wa15;

	TCanvas *wa16 = new TCanvas("wa16","test",1100,650);
	njets_bjets_Z_tight_total_weighted_acc_ttjets->SetStats(0);
	njets_bjets_Z_tight_total_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_total_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa16->Print("2D_tight_Z_total_njet_bjet_weighted_acc_ttjets.pdf");
	delete wa16;

	TCanvas *wa17 = new TCanvas("wa17","test",1100,650);
	nbjets_btags_Z_loose_total_weighted_ttjets->SetStats(0);
	nbjets_btags_Z_loose_total_weighted_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_total_weighted_ttjets->Draw("TEXTCOLZ");
	wa17->Print("2D_loose_Z_total_nbjet_btag_weighted_ttjets.pdf");
	delete wa17;

	TCanvas *wa18 = new TCanvas("wa18","test",1100,650);
	nbjets_btags_Z_tight_total_weighted_ttjets->SetStats(0);
	nbjets_btags_Z_tight_total_weighted_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_total_weighted_ttjets->Draw("TEXTCOLZ");
	wa18->Print("2D_tight_Z_total_nbjet_btag_weighted_ttjets.pdf");
	delete wa18;

	TCanvas *wa19 = new TCanvas("wa19","test",1100,650);
	nbjets_btags_Z_loose_total_weighted_acc_ttjets->SetStats(0);
	nbjets_btags_Z_loose_total_weighted_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_total_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa19->Print("2D_loose_Z_total_nbjet_btag_weighted_acc_ttjets.pdf");
	delete wa19;

	TCanvas *wa20 = new TCanvas("wa20","test",1100,650);
	nbjets_btags_Z_tight_total_weighted_acc_ttjets->SetStats(0);
	nbjets_btags_Z_tight_total_weighted_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_total_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa20->Print("2D_tight_Z_total_nbjet_btag_weighted_acc_ttjets.pdf");
	delete wa20;

	TCanvas *wa21 = new TCanvas("wa21","test",1100,650);
	njets_btags_Z_loose_ttb_frac_weighted_ttjets->SetStats(0);
	njets_btags_Z_loose_ttb_frac_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttb_frac_weighted_ttjets->Draw("TEXTCOLZ");
	wa21->Print("2D_loose_Z_ttb_frac_weighted_ttjets.pdf");
	delete wa21;

	TCanvas *wa22 = new TCanvas("wa22","test",1100,650);
	njets_btags_Z_loose_ttb_frac_weighted_acc_ttjets->SetStats(0);
	njets_btags_Z_loose_ttb_frac_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttb_frac_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa22->Print("2D_loose_Z_ttb_frac_weighted_acc_ttjets.pdf");
	delete wa22;

	TCanvas *wa23 = new TCanvas("wa23","test",1100,650);
	njets_btags_Z_loose_tt2b_frac_weighted_ttjets->SetStats(0);
	njets_btags_Z_loose_tt2b_frac_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_tt2b_frac_weighted_ttjets->Draw("TEXTCOLZ");
	wa23->Print("2D_loose_Z_tt2b_frac_weighted_ttjets.pdf");
	delete wa23;

	TCanvas *wa24 = new TCanvas("wa24","test",1100,650);
	njets_btags_Z_loose_tt2b_frac_weighted_acc_ttjets->SetStats(0);
	njets_btags_Z_loose_tt2b_frac_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_tt2b_frac_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa24->Print("2D_loose_Z_tt2b_frac_weighted_acc_ttjets.pdf");
	delete wa24;

	TCanvas *wa25 = new TCanvas("wa25","test",1100,650);
	njets_bjets_Z_loose_ttbb_weighted_ttjets->SetStats(0);
	njets_bjets_Z_loose_ttbb_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_ttbb_weighted_ttjets->Draw("TEXTCOLZ");
	wa25->Print("2D_loose_Z_ttbb_weighted_njet_bjet_ttjets.pdf");
	delete wa25;

	TCanvas *wa26 = new TCanvas("wa26","test",1100,650);
	njets_bjets_Z_tight_ttbb_weighted_ttjets->SetStats(0);
	njets_bjets_Z_tight_ttbb_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_ttbb_weighted_ttjets->Draw("TEXTCOLZ");
	wa26->Print("2D_tight_Z_ttbb_weighted_njet_bjet_ttjets.pdf");
	delete wa26;

	TCanvas *wa27 = new TCanvas("wa27","test",1100,650);
	njets_bjets_Z_loose_ttbb_weighted_acc_ttjets->SetStats(0);
	njets_bjets_Z_loose_ttbb_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_ttbb_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa27->Print("2D_loose_Z_ttbb_weighted_njet_bjet_acc_ttjets.pdf");
	delete wa27;

	TCanvas *wa28 = new TCanvas("wa28","test",1100,650);
	njets_bjets_Z_tight_ttbb_weighted_acc_ttjets->SetStats(0);
	njets_bjets_Z_tight_ttbb_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_ttbb_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa28->Print("2D_tight_Z_ttbb_weighted_njet_bjet_acc_ttjets.pdf");
	delete wa28;

	TCanvas *wa29 = new TCanvas("wa29","test",1100,650);
	nbjets_btags_Z_loose_ttbb_weighted_ttjets->SetStats(0);
	nbjets_btags_Z_loose_ttbb_weighted_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_ttbb_weighted_ttjets->Draw("TEXTCOLZ");
	wa29->Print("2D_loose_Z_ttbb_weighted_nbjet_btag_ttjets.pdf");
	delete wa29;

	TCanvas *wa30 = new TCanvas("wa30","test",1100,650);
	nbjets_btags_Z_tight_ttbb_weighted_ttjets->SetStats(0);
	nbjets_btags_Z_tight_ttbb_weighted_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_ttbb_weighted_ttjets->Draw("TEXTCOLZ");
	wa30->Print("2D_tight_Z_ttbb_weighted_nbjet_btag_ttjets.pdf");
	delete wa30;

	TCanvas *wa31 = new TCanvas("wa31","test",1100,650);
	nbjets_btags_Z_loose_ttbb_weighted_acc_ttjets->SetStats(0);
	nbjets_btags_Z_loose_ttbb_weighted_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_ttbb_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa31->Print("2D_loose_Z_ttbb_weighted_nbjet_btag_acc_ttjets.pdf");
	delete wa31;

	TCanvas *wa32 = new TCanvas("wa32","test",1100,650);
	nbjets_btags_Z_tight_ttbb_weighted_acc_ttjets->SetStats(0);
	nbjets_btags_Z_tight_ttbb_weighted_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_ttbb_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa32->Print("2D_tight_Z_ttbb_weighted_nbjet_btag_acc_ttjets.pdf");
	delete wa32;

	TCanvas *wa33 = new TCanvas("wa33","test",1100,650);
	njets_bjets_Z_loose_ttb_weighted_ttjets->SetStats(0);
	njets_bjets_Z_loose_ttb_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_ttb_weighted_ttjets->Draw("TEXTCOLZ");
	wa33->Print("2D_loose_Z_ttb_weighted_njet_bjet_ttjets.pdf");
	delete wa33;

	TCanvas *wa34 = new TCanvas("wa34","test",1100,650);
	njets_bjets_Z_tight_ttb_weighted_ttjets->SetStats(0);
	njets_bjets_Z_tight_ttb_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_ttb_weighted_ttjets->Draw("TEXTCOLZ");
	wa34->Print("2D_tight_Z_ttb_weighted_njet_bjet_ttjets.pdf");
	delete wa34;

	TCanvas *wa35 = new TCanvas("wa35","test",1100,650);
	njets_bjets_Z_loose_ttb_weighted_acc_ttjets->SetStats(0);
	njets_bjets_Z_loose_ttb_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_ttb_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa35->Print("2D_loose_Z_ttb_weighted_njet_bjet_acc_ttjets.pdf");
	delete wa35;

	TCanvas *wa36 = new TCanvas("wa36","test",1100,650);
	njets_bjets_Z_tight_ttb_weighted_acc_ttjets->SetStats(0);
	njets_bjets_Z_tight_ttb_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_ttb_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa36->Print("2D_tight_Z_ttb_weighted_njet_bjet_acc_ttjets.pdf");
	delete wa36;

	TCanvas *wa37 = new TCanvas("wa37","test",1100,650);
	nbjets_btags_Z_loose_ttb_weighted_ttjets->SetStats(0);
	nbjets_btags_Z_loose_ttb_weighted_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_ttb_weighted_ttjets->Draw("TEXTCOLZ");
	wa37->Print("2D_loose_Z_ttb_weighted_nbjet_btag_ttjets.pdf");
	delete wa37;

	TCanvas *wa38 = new TCanvas("wa38","test",1100,650);
	nbjets_btags_Z_tight_ttb_weighted_ttjets->SetStats(0);
	nbjets_btags_Z_tight_ttb_weighted_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_ttb_weighted_ttjets->Draw("TEXTCOLZ");
	wa38->Print("2D_tight_Z_ttb_weighted_nbjet_btag_ttjets.pdf");
	delete wa38;

	TCanvas *wa39 = new TCanvas("wa39","test",1100,650);
	nbjets_btags_Z_loose_ttb_weighted_acc_ttjets->SetStats(0);
	nbjets_btags_Z_loose_ttb_weighted_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_ttb_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa39->Print("2D_loose_Z_ttb_weighted_nbjet_btag_acc_ttjets.pdf");
	delete wa39;

	TCanvas *wa40 = new TCanvas("wa40","test",1100,650);
	nbjets_btags_Z_tight_ttb_weighted_acc_ttjets->SetStats(0);
	nbjets_btags_Z_tight_ttb_weighted_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_ttb_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa40->Print("2D_tight_Z_ttb_weighted_nbjet_btag_acc_ttjets.pdf");
	delete wa40;

	TCanvas *wa41 = new TCanvas("wa41","test",1100,650);
	njets_bjets_Z_loose_tt2b_weighted_ttjets->SetStats(0);
	njets_bjets_Z_loose_tt2b_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_tt2b_weighted_ttjets->Draw("TEXTCOLZ");
	wa41->Print("2D_loose_Z_tt2b_weighted_njet_bjet_ttjets.pdf");
	delete wa41;

	TCanvas *wa42 = new TCanvas("wa42","test",1100,650);
	njets_bjets_Z_tight_tt2b_weighted_ttjets->SetStats(0);
	njets_bjets_Z_tight_tt2b_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_tt2b_weighted_ttjets->Draw("TEXTCOLZ");
	wa42->Print("2D_tight_Z_tt2b_weighted_njet_bjet_ttjets.pdf");
	delete wa42;

	TCanvas *wa43 = new TCanvas("wa43","test",1100,650);
	njets_bjets_Z_loose_tt2b_weighted_acc_ttjets->SetStats(0);
	njets_bjets_Z_loose_tt2b_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_tt2b_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa43->Print("2D_loose_Z_tt2b_weighted_njet_bjet_acc_ttjets.pdf");
	delete wa43;

	TCanvas *wa44 = new TCanvas("wa44","test",1100,650);
	njets_bjets_Z_tight_tt2b_weighted_acc_ttjets->SetStats(0);
	njets_bjets_Z_tight_tt2b_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_tight_tt2b_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa44->Print("2D_tight_Z_tt2b_weighted_njet_bjet_acc_ttjets.pdf");
	delete wa44;

	TCanvas *wa45 = new TCanvas("wa45","test",1100,650);
	nbjets_btags_Z_loose_tt2b_weighted_ttjets->SetStats(0);
	nbjets_btags_Z_loose_tt2b_weighted_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_tt2b_weighted_ttjets->Draw("TEXTCOLZ");
	wa45->Print("2D_loose_Z_tt2b_weighted_nbjet_btag_ttjets.pdf");
	delete wa45;

	TCanvas *wa46 = new TCanvas("wa46","test",1100,650);
	nbjets_btags_Z_tight_tt2b_weighted_ttjets->SetStats(0);
	nbjets_btags_Z_tight_tt2b_weighted_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_tt2b_weighted_ttjets->Draw("TEXTCOLZ");
	wa46->Print("2D_tight_Z_tt2b_weighted_nbjet_btag_ttjets.pdf");
	delete wa46;

	TCanvas *wa47 = new TCanvas("wa47","test",1100,650);
	nbjets_btags_Z_loose_tt2b_weighted_acc_ttjets->SetStats(0);
	nbjets_btags_Z_loose_tt2b_weighted_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_loose_tt2b_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa47->Print("2D_loose_Z_tt2b_weighted_nbjet_btag_acc_ttjets.pdf");
	delete wa47;

	TCanvas *wa48 = new TCanvas("wa48","test",1100,650);
	nbjets_btags_Z_tight_tt2b_weighted_acc_ttjets->SetStats(0);
	nbjets_btags_Z_tight_tt2b_weighted_acc_ttjets->GetXaxis()->SetNdivisions(7);
	nbjets_btags_Z_tight_tt2b_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa48->Print("2D_tight_Z_tt2b_weighted_nbjet_btag_acc_ttjets.pdf");
	delete wa48;

	TCanvas *wa49 = new TCanvas("wa49","test",1100,650);
	njets_btags_Z_tight_ttb_frac_weighted_ttjets->SetStats(0);
	njets_btags_Z_tight_ttb_frac_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttb_frac_weighted_ttjets->Draw("TEXTCOLZ");
	wa49->Print("2D_tight_Z_ttb_frac_weighted_ttjets.pdf");
	delete wa49;

	TCanvas *wa50 = new TCanvas("wa50","test",1100,650);
	njets_btags_Z_tight_ttb_frac_weighted_acc_ttjets->SetStats(0);
	njets_btags_Z_tight_ttb_frac_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttb_frac_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa50->Print("2D_tight_Z_ttb_frac_weighted_acc_ttjets.pdf");
	delete wa50;

	TCanvas *wa51 = new TCanvas("wa51","test",1100,650);
	njets_btags_Z_tight_tt2b_frac_weighted_ttjets->SetStats(0);
	njets_btags_Z_tight_tt2b_frac_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_tt2b_frac_weighted_ttjets->Draw("TEXTCOLZ");
	wa51->Print("2D_tight_Z_tt2b_frac_weighted_ttjets.pdf");
	delete wa51;

	TCanvas *wa52 = new TCanvas("wa52","test",1100,650);
	njets_btags_Z_tight_tt2b_frac_weighted_acc_ttjets->SetStats(0);
	njets_btags_Z_tight_tt2b_frac_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_tt2b_frac_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa52->Print("2D_tight_Z_tt2b_frac_weighted_acc_ttjets.pdf");
	delete wa52;

	TCanvas *wa53 = new TCanvas("wa53","test",1100,650);
	njets_btags_Z_loose_ttb_weighted_ttjets->SetStats(0);
	njets_btags_Z_loose_ttb_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttb_weighted_ttjets->Draw("TEXTCOLZ");
	wa53->Print("2D_loose_Z_ttb_weighted_ttjets.pdf");
	delete wa53;

	TCanvas *wa54 = new TCanvas("wa54","test",1100,650);
	njets_btags_Z_loose_ttb_weighted_acc_ttjets->SetStats(0);
	njets_btags_Z_loose_ttb_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttb_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa54->Print("2D_loose_Z_ttb_weighted_acc_ttjets.pdf");
	delete wa54;

	TCanvas *wa55 = new TCanvas("wa55","test",1100,650);
	njets_btags_Z_loose_tt2b_weighted_ttjets->SetStats(0);
	njets_btags_Z_loose_tt2b_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_tt2b_weighted_ttjets->Draw("TEXTCOLZ");
	wa55->Print("2D_loose_Z_tt2b_weighted_ttjets.pdf");
	delete wa55;

	TCanvas *wa56 = new TCanvas("wa56","test",1100,650);
	njets_btags_Z_loose_tt2b_weighted_acc_ttjets->SetStats(0);
	njets_btags_Z_loose_tt2b_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_tt2b_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa56->Print("2D_loose_Z_tt2b_weighted_acc_ttjets.pdf");
	delete wa56;

	TCanvas *wa57 = new TCanvas("wa57","test",1100,650);
	njets_btags_Z_tight_ttb_weighted_ttjets->SetStats(0);
	njets_btags_Z_tight_ttb_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttb_weighted_ttjets->Draw("TEXTCOLZ");
	wa57->Print("2D_tight_Z_ttb_weighted_ttjets.pdf");
	delete wa57;

	TCanvas *wa58 = new TCanvas("wa58","test",1100,650);
	njets_btags_Z_tight_ttb_weighted_acc_ttjets->SetStats(0);
	njets_btags_Z_tight_ttb_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_ttb_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa58->Print("2D_tight_Z_ttb_weighted_acc_ttjets.pdf");
	delete wa58;

	TCanvas *wa59 = new TCanvas("wa59","test",1100,650);
	njets_btags_Z_tight_tt2b_weighted_ttjets->SetStats(0);
	njets_btags_Z_tight_tt2b_weighted_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_tt2b_weighted_ttjets->Draw("TEXTCOLZ");
	wa59->Print("2D_tight_Z_tt2b_weighted_ttjets.pdf");
	delete wa59;

	TCanvas *wa60 = new TCanvas("wa60","test",1100,650);
	njets_btags_Z_tight_tt2b_weighted_acc_ttjets->SetStats(0);
	njets_btags_Z_tight_tt2b_weighted_acc_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_tt2b_weighted_acc_ttjets->Draw("TEXTCOLZ");
	wa60->Print("2D_tight_Z_tt2b_weighted_acc_ttjets.pdf");
	delete wa60;

	// DY MC sample only

	TCanvas *b1 = new TCanvas("b1","test",1100,650);
	njets_btags_Z_loose_total_DY->SetStats(0);
	njets_btags_Z_loose_total_DY->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_DY->Draw("TEXTCOLZ");
	b1->Print("2D_loose_Z_total_DY.pdf");
	delete b1;

	TCanvas *b2 = new TCanvas("b2","test",1100,650);
	njets_btags_Z_loose_total_acc_DY->SetStats(0);
	njets_btags_Z_loose_total_acc_DY->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_acc_DY->Draw("TEXTCOLZ");
	b2->Print("2D_loose_Z_total_acc_DY.pdf");
	delete b2;

	TCanvas *b3 = new TCanvas("b3","test",1100,650);
	njets_btags_Z_tight_total_DY->SetStats(0);
	njets_btags_Z_tight_total_DY->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_DY->Draw("TEXTCOLZ");
	b3->Print("2D_tight_Z_total_DY.pdf");
	delete b3;

	TCanvas *b4 = new TCanvas("b4","test",1100,650);
	njets_btags_Z_tight_total_acc_DY->SetStats(0);
	njets_btags_Z_tight_total_acc_DY->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_acc_DY->Draw("TEXTCOLZ");
	b4->Print("2D_tight_Z_total_acc_DY.pdf");
	delete b4;

	TCanvas *wb1 = new TCanvas("wb1","test",1100,650);
	njets_btags_Z_loose_total_weighted_DY->SetStats(0);
	njets_btags_Z_loose_total_weighted_DY->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_DY->Draw("TEXTCOLZ");
	wb1->Print("2D_loose_Z_total_weighted_DY.pdf");
	delete wb1;

	TCanvas *wb2 = new TCanvas("wb2","test",1100,650);
	njets_btags_Z_loose_total_weighted_acc_DY->SetStats(0);
	njets_btags_Z_loose_total_weighted_acc_DY->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_acc_DY->Draw("TEXTCOLZ");
	wb2->Print("2D_loose_Z_total_weighted_acc_DY.pdf");
	delete wb2;

	TCanvas *wb3 = new TCanvas("wb3","test",1100,650);
	njets_btags_Z_tight_total_weighted_DY->SetStats(0);
	njets_btags_Z_tight_total_weighted_DY->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_DY->Draw("TEXTCOLZ");
	wb3->Print("2D_tight_Z_total_weighted_DY.pdf");
	delete wb3;

	TCanvas *wb4 = new TCanvas("wb4","test",1100,650);
	njets_btags_Z_tight_total_weighted_acc_DY->SetStats(0);
	njets_btags_Z_tight_total_weighted_acc_DY->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_acc_DY->Draw("TEXTCOLZ");
	wb4->Print("2D_tight_Z_total_weighted_acc_DY.pdf");
	delete wb4;


	// ttHbb MC sample only

	TCanvas *j1 = new TCanvas("j1","test",1100,650);
	njets_btags_Z_loose_total_ttHbb->SetStats(0);
	njets_btags_Z_loose_total_ttHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_ttHbb->Draw("TEXTCOLZ");
	j1->Print("2D_loose_Z_total_ttHbb.pdf");
	delete j1;

	TCanvas *j2 = new TCanvas("j2","test",1100,650);
	njets_btags_Z_loose_total_acc_ttHbb->SetStats(0);
	njets_btags_Z_loose_total_acc_ttHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_acc_ttHbb->Draw("TEXTCOLZ");
	j2->Print("2D_loose_Z_total_acc_ttHbb.pdf");
	delete j2;

	TCanvas *j3 = new TCanvas("j3","test",1100,650);
	njets_btags_Z_tight_total_ttHbb->SetStats(0);
	njets_btags_Z_tight_total_ttHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_ttHbb->Draw("TEXTCOLZ");
	j3->Print("2D_tight_Z_total_ttHbb.pdf");
	delete j3;

	TCanvas *j4 = new TCanvas("j4","test",1100,650);
	njets_btags_Z_tight_total_acc_ttHbb->SetStats(0);
	njets_btags_Z_tight_total_acc_ttHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_acc_ttHbb->Draw("TEXTCOLZ");
	j4->Print("2D_tight_Z_total_acc_ttHbb.pdf");
	delete j4;

	TCanvas *wj1 = new TCanvas("wj1","test",1100,650);
	njets_btags_Z_loose_total_weighted_ttHbb->SetStats(0);
	njets_btags_Z_loose_total_weighted_ttHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_ttHbb->Draw("TEXTCOLZ");
	wj1->Print("2D_loose_Z_total_weighted_ttHbb.pdf");
	delete wj1;

	TCanvas *wj2 = new TCanvas("wj2","test",1100,650);
	njets_btags_Z_loose_total_weighted_acc_ttHbb->SetStats(0);
	njets_btags_Z_loose_total_weighted_acc_ttHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_acc_ttHbb->Draw("TEXTCOLZ");
	wj2->Print("2D_loose_Z_total_weighted_acc_ttHbb.pdf");
	delete wj2;

	TCanvas *wj3 = new TCanvas("wj3","test",1100,650);
	njets_btags_Z_tight_total_weighted_ttHbb->SetStats(0);
	njets_btags_Z_tight_total_weighted_ttHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_ttHbb->Draw("TEXTCOLZ");
	wj3->Print("2D_tight_Z_total_weighted_ttHbb.pdf");
	delete wj3;

	TCanvas *wj4 = new TCanvas("wj4","test",1100,650);
	njets_btags_Z_tight_total_weighted_acc_ttHbb->SetStats(0);
	njets_btags_Z_tight_total_weighted_acc_ttHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_acc_ttHbb->Draw("TEXTCOLZ");
	wj4->Print("2D_tight_Z_total_weighted_acc_ttHbb.pdf");
	delete wj4;


	// All background

	TCanvas *c1 = new TCanvas("c1","test",1100,650);
	njets_btags_Z_loose_total_all_bkgd->SetStats(0);
	njets_btags_Z_loose_total_all_bkgd->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_all_bkgd->Draw("TEXTCOLZ");
	c1->Print("2D_loose_Z_total_all_bkgd.pdf");
	delete c1;

	TCanvas *c2 = new TCanvas("c2","test",1100,650);
	njets_btags_Z_tight_total_all_bkgd->SetStats(0);
	njets_btags_Z_tight_total_all_bkgd->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_all_bkgd->Draw("TEXTCOLZ");
	c2->Print("2D_tight_Z_total_all_bkgd.pdf");
	delete c2;

	TCanvas *c3 = new TCanvas("c3","test",1100,650);
	njets_btags_Z_loose_total_acc_all_bkgd->SetStats(0);
	njets_btags_Z_loose_total_acc_all_bkgd->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_acc_all_bkgd->Draw("TEXTCOLZ");
	c3->Print("2D_loose_Z_total_acc_all_bkgd.pdf");
	delete c3;

	TCanvas *c4 = new TCanvas("c4","test",1100,650);
	njets_btags_Z_tight_total_acc_all_bkgd->SetStats(0);
	njets_btags_Z_tight_total_acc_all_bkgd->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_acc_all_bkgd->Draw("TEXTCOLZ");
	c4->Print("2D_tight_Z_total_acc_all_bkgd.pdf");
	delete c4;

	TCanvas *wc1 = new TCanvas("wc1","test",1100,650);
	njets_btags_Z_loose_total_weighted_all_bkgd->SetStats(0);
	njets_btags_Z_loose_total_weighted_all_bkgd->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_all_bkgd->Draw("TEXTCOLZ");
	wc1->Print("2D_loose_Z_total_weighted_all_bkgd.pdf");
	delete wc1;

	TCanvas *wc2 = new TCanvas("wc2","test",1100,650);
	njets_btags_Z_tight_total_weighted_all_bkgd->SetStats(0);
	njets_btags_Z_tight_total_weighted_all_bkgd->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_all_bkgd->Draw("TEXTCOLZ");
	wc2->Print("2D_tight_Z_total_weighted_all_bkgd.pdf");
	delete wc2;

	TCanvas *wc3 = new TCanvas("wc3","test",1100,650);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->SetStats(0);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd->Draw("TEXTCOLZ");
	wc3->Print("2D_loose_Z_total_weighted_acc_all_bkgd.pdf");
	delete wc3;

	TCanvas *wc4 = new TCanvas("wc4","test",1100,650);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->SetStats(0);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd->Draw("TEXTCOLZ");
	wc4->Print("2D_tight_Z_total_weighted_acc_all_bkgd.pdf");
	delete wc4;

	// ttjets / All Background

	TCanvas *d1 = new TCanvas("d1","test",1100,650);
	njets_btags_Z_loose_total_sob->SetStats(0);
	njets_btags_Z_loose_total_sob->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_sob->Draw("TEXTCOLZ");
	d1->Print("2D_loose_Z_total_sob.pdf");
	delete d1;

	TCanvas *d2 = new TCanvas("d2","test",1100,650);
	njets_btags_Z_tight_total_sob->SetStats(0);
	njets_btags_Z_tight_total_sob->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_sob->Draw("TEXTCOLZ");
	d2->Print("2D_tight_Z_total_sob.pdf");
	delete d2;

	TCanvas *d3 = new TCanvas("d3","test",1100,650);
	njets_btags_Z_loose_total_acc_sob->SetStats(0);
	njets_btags_Z_loose_total_acc_sob->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_acc_sob->Draw("TEXTCOLZ");
	d3->Print("2D_loose_Z_total_acc_sob.pdf");
	delete d3;

	TCanvas *d4 = new TCanvas("d4","test",1100,650);
	njets_btags_Z_tight_total_acc_sob->SetStats(0);
	njets_btags_Z_tight_total_acc_sob->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_acc_sob->Draw("TEXTCOLZ");
	d4->Print("2D_tight_Z_total_acc_sob.pdf");
	delete d4;

	TCanvas *wd1 = new TCanvas("wd1","test",1100,650);
	njets_btags_Z_loose_total_weighted_sob->SetStats(0);
	njets_btags_Z_loose_total_weighted_sob->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_sob->Draw("TEXTCOLZ");
	wd1->Print("2D_loose_Z_total_weighted_sob.pdf");
	delete wd1;

	TCanvas *wd2 = new TCanvas("wd2","test",1100,650);
	njets_btags_Z_tight_total_weighted_sob->SetStats(0);
	njets_btags_Z_tight_total_weighted_sob->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_sob->Draw("TEXTCOLZ");
	wd2->Print("2D_tight_Z_total_weighted_sob.pdf");
	delete wd2;

	TCanvas *wd3 = new TCanvas("wd3","test",1100,650);
	njets_btags_Z_loose_total_weighted_acc_sob->SetStats(0);
	njets_btags_Z_loose_total_weighted_acc_sob->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_acc_sob->Draw("TEXTCOLZ");
	wd3->Print("2D_loose_Z_total_weighted_acc_sob.pdf");
	delete wd3;

	TCanvas *wd4 = new TCanvas("wd4","test",1100,650);
	njets_btags_Z_tight_total_weighted_acc_sob->SetStats(0);
	njets_btags_Z_tight_total_weighted_acc_sob->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_acc_sob->Draw("TEXTCOLZ");
	wd4->Print("2D_tight_Z_total_weighted_acc_sob.pdf");
	delete wd4;

	// All background without DY

	TCanvas *cc1 = new TCanvas("cc1","test",1100,650);
	njets_btags_Z_loose_total_all_bkgd_no_dy->SetStats(0);
	njets_btags_Z_loose_total_all_bkgd_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_all_bkgd_no_dy->Draw("TEXTCOLZ");
	cc1->Print("2D_loose_Z_total_all_bkgd_no_dy.pdf");
	delete cc1;

	TCanvas *cc2 = new TCanvas("cc2","test",1100,650);
	njets_btags_Z_tight_total_all_bkgd_no_dy->SetStats(0);
	njets_btags_Z_tight_total_all_bkgd_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_all_bkgd_no_dy->Draw("TEXTCOLZ");
	cc2->Print("2D_tight_Z_total_all_bkgd_no_dy.pdf");
	delete cc2;

	TCanvas *cc3 = new TCanvas("cc3","test",1100,650);
	njets_btags_Z_loose_total_acc_all_bkgd_no_dy->SetStats(0);
	njets_btags_Z_loose_total_acc_all_bkgd_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_acc_all_bkgd_no_dy->Draw("TEXTCOLZ");
	cc3->Print("2D_loose_Z_total_acc_all_bkgd_no_dy.pdf");
	delete cc3;

	TCanvas *cc4 = new TCanvas("cc4","test",1100,650);
	njets_btags_Z_tight_total_acc_all_bkgd_no_dy->SetStats(0);
	njets_btags_Z_tight_total_acc_all_bkgd_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_acc_all_bkgd_no_dy->Draw("TEXTCOLZ");
	cc4->Print("2D_tight_Z_total_acc_all_bkgd_no_dy.pdf");
	delete cc4;

	TCanvas *wcc1 = new TCanvas("wcc1","test",1100,650);
	njets_btags_Z_loose_total_weighted_all_bkgd_no_dy->SetStats(0);
	njets_btags_Z_loose_total_weighted_all_bkgd_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_all_bkgd_no_dy->Draw("TEXTCOLZ");
	wcc1->Print("2D_loose_Z_total_weighted_all_bkgd_no_dy.pdf");
	delete wcc1;

	TCanvas *wcc2 = new TCanvas("wcc2","test",1100,650);
	njets_btags_Z_tight_total_weighted_all_bkgd_no_dy->SetStats(0);
	njets_btags_Z_tight_total_weighted_all_bkgd_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_all_bkgd_no_dy->Draw("TEXTCOLZ");
	wcc2->Print("2D_tight_Z_total_weighted_all_bkgd_no_dy.pdf");
	delete wcc2;

	TCanvas *wcc3 = new TCanvas("wcc3","test",1100,650);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd_no_dy->SetStats(0);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_acc_all_bkgd_no_dy->Draw("TEXTCOLZ");
	wcc3->Print("2D_loose_Z_total_weighted_acc_all_bkgd_no_dy.pdf");
	delete wcc3;

	TCanvas *wcc4 = new TCanvas("wcc4","test",1100,650);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd_no_dy->SetStats(0);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_acc_all_bkgd_no_dy->Draw("TEXTCOLZ");
	wcc4->Print("2D_tight_Z_total_weighted_acc_all_bkgd_no_dy.pdf");
	delete wcc4;

	// ttjets / All Background without DY

	TCanvas *dd1 = new TCanvas("dd1","test",1100,650);
	njets_btags_Z_loose_total_sob_no_dy->SetStats(0);
	njets_btags_Z_loose_total_sob_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_sob_no_dy->Draw("TEXTCOLZ");
	dd1->Print("2D_loose_Z_total_sob_no_dy.pdf");
	delete dd1;

	TCanvas *dd2 = new TCanvas("dd2","test",1100,650);
	njets_btags_Z_tight_total_sob_no_dy->SetStats(0);
	njets_btags_Z_tight_total_sob_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_sob_no_dy->Draw("TEXTCOLZ");
	dd2->Print("2D_tight_Z_total_sob_no_dy.pdf");
	delete dd2;

	TCanvas *dd3 = new TCanvas("dd3","test",1100,650);
	njets_btags_Z_loose_total_acc_sob_no_dy->SetStats(0);
	njets_btags_Z_loose_total_acc_sob_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_acc_sob_no_dy->Draw("TEXTCOLZ");
	dd3->Print("2D_loose_Z_total_acc_sob_no_dy.pdf");
	delete dd3;

	TCanvas *dd4 = new TCanvas("dd4","test",1100,650);
	njets_btags_Z_tight_total_acc_sob_no_dy->SetStats(0);
	njets_btags_Z_tight_total_acc_sob_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_acc_sob_no_dy->Draw("TEXTCOLZ");
	dd4->Print("2D_tight_Z_total_acc_sob_no_dy.pdf");
	delete dd4;

	TCanvas *wdd1 = new TCanvas("wdd1","test",1100,650);
	njets_btags_Z_loose_total_weighted_sob_no_dy->SetStats(0);
	njets_btags_Z_loose_total_weighted_sob_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_sob_no_dy->Draw("TEXTCOLZ");
	wdd1->Print("2D_loose_Z_total_weighted_sob_no_dy.pdf");
	delete wdd1;

	TCanvas *wdd2 = new TCanvas("wdd2","test",1100,650);
	njets_btags_Z_tight_total_weighted_sob_no_dy->SetStats(0);
	njets_btags_Z_tight_total_weighted_sob_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_sob_no_dy->Draw("TEXTCOLZ");
	wdd2->Print("2D_tight_Z_total_weighted_sob_no_dy.pdf");
	delete wdd2;

	TCanvas *wdd3 = new TCanvas("wdd3","test",1100,650);
	njets_btags_Z_loose_total_weighted_acc_sob_no_dy->SetStats(0);
	njets_btags_Z_loose_total_weighted_acc_sob_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_acc_sob_no_dy->Draw("TEXTCOLZ");
	wdd3->Print("2D_loose_Z_total_weighted_acc_sob_no_dy.pdf");
	delete wdd3;

	TCanvas *wdd4 = new TCanvas("wdd4","test",1100,650);
	njets_btags_Z_tight_total_weighted_acc_sob_no_dy->SetStats(0);
	njets_btags_Z_tight_total_weighted_acc_sob_no_dy->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_acc_sob_no_dy->Draw("TEXTCOLZ");
	wdd4->Print("2D_tight_Z_total_weighted_acc_sob_no_dy.pdf");
	delete wdd4;

	// All Background without DY / All Background

	TCanvas *ee1 = new TCanvas("ee1","test",1100,650);
	njets_btags_Z_loose_total_bnody_ball->SetStats(0);
	njets_btags_Z_loose_total_bnody_ball->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_bnody_ball->Draw("TEXTCOLZ");
	ee1->Print("2D_loose_Z_total_bnody_ball.pdf");
	delete ee1;

	TCanvas *ee2 = new TCanvas("ee2","test",1100,650);
	njets_btags_Z_tight_total_bnody_ball->SetStats(0);
	njets_btags_Z_tight_total_bnody_ball->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_bnody_ball->Draw("TEXTCOLZ");
	ee2->Print("2D_tight_Z_total_bnody_ball.pdf");
	delete ee2;

	TCanvas *ee3 = new TCanvas("ee3","test",1100,650);
	njets_btags_Z_loose_total_acc_bnody_ball->SetStats(0);
	njets_btags_Z_loose_total_acc_bnody_ball->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_acc_bnody_ball->Draw("TEXTCOLZ");
	ee3->Print("2D_loose_Z_total_acc_bnody_ball.pdf");
	delete ee3;

	TCanvas *ee4 = new TCanvas("ee4","test",1100,650);
	njets_btags_Z_tight_total_acc_bnody_ball->SetStats(0);
	njets_btags_Z_tight_total_acc_bnody_ball->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_acc_bnody_ball->Draw("TEXTCOLZ");
	ee4->Print("2D_tight_Z_total_acc_bnody_ball.pdf");
	delete ee4;

	TCanvas *wee1 = new TCanvas("wee1","test",1100,650);
	njets_btags_Z_loose_total_weighted_bnody_ball->SetStats(0);
	njets_btags_Z_loose_total_weighted_bnody_ball->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_bnody_ball->Draw("TEXTCOLZ");
	wee1->Print("2D_loose_Z_total_weighted_bnody_ball.pdf");
	delete wee1;

	TCanvas *wee2 = new TCanvas("wee2","test",1100,650);
	njets_btags_Z_tight_total_weighted_bnody_ball->SetStats(0);
	njets_btags_Z_tight_total_weighted_bnody_ball->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_bnody_ball->Draw("TEXTCOLZ");
	wee2->Print("2D_tight_Z_total_weighted_bnody_ball.pdf");
	delete wee2;

	TCanvas *wee3 = new TCanvas("wee3","test",1100,650);
	njets_btags_Z_loose_total_weighted_acc_bnody_ball->SetStats(0);
	njets_btags_Z_loose_total_weighted_acc_bnody_ball->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_acc_bnody_ball->Draw("TEXTCOLZ");
	wee3->Print("2D_loose_Z_total_weighted_acc_bnody_ball.pdf");
	delete wee3;

	TCanvas *wee4 = new TCanvas("wee4","test",1100,650);
	njets_btags_Z_tight_total_weighted_acc_bnody_ball->SetStats(0);
	njets_btags_Z_tight_total_weighted_acc_bnody_ball->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_acc_bnody_ball->Draw("TEXTCOLZ");
	wee4->Print("2D_tight_Z_total_weighted_acc_bnody_ball.pdf");
	delete wee4;


	// ttjets / DY only

	TCanvas *e1 = new TCanvas("e1","test",1100,650);
	njets_btags_Z_loose_total_sody->SetStats(0);
	njets_btags_Z_loose_total_sody->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_sody->Draw("TEXTCOLZ");
	e1->Print("2D_loose_Z_total_sody.pdf");
	delete e1;

	TCanvas *e2 = new TCanvas("e2","test",1100,650);
	njets_btags_Z_tight_total_sody->SetStats(0);
	njets_btags_Z_tight_total_sody->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_sody->Draw("TEXTCOLZ");
	e2->Print("2D_tight_Z_total_sody.pdf");
	delete e2;

	TCanvas *e3 = new TCanvas("e3","test",1100,650);
	njets_btags_Z_loose_total_acc_sody->SetStats(0);
	njets_btags_Z_loose_total_acc_sody->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_acc_sody->Draw("TEXTCOLZ");
	e3->Print("2D_loose_Z_total_acc_sody.pdf");
	delete e3;

	TCanvas *e4 = new TCanvas("e4","test",1100,650);
	njets_btags_Z_tight_total_acc_sody->SetStats(0);
	njets_btags_Z_tight_total_acc_sody->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_acc_sody->Draw("TEXTCOLZ");
	e4->Print("2D_tight_Z_total_acc_sody.pdf");
	delete e4;

	TCanvas *we1 = new TCanvas("we1","test",1100,650);
	njets_btags_Z_loose_total_weighted_sody->SetStats(0);
	njets_btags_Z_loose_total_weighted_sody->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_sody->Draw("TEXTCOLZ");
	we1->Print("2D_loose_Z_total_weighted_sody.pdf");
	delete we1;

	TCanvas *we2 = new TCanvas("we2","test",1100,650);
	njets_btags_Z_tight_total_weighted_sody->SetStats(0);
	njets_btags_Z_tight_total_weighted_sody->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_sody->Draw("TEXTCOLZ");
	we2->Print("2D_tight_Z_total_weighted_sody.pdf");
	delete we2;

	TCanvas *we3 = new TCanvas("we3","test",1100,650);
	njets_btags_Z_loose_total_weighted_acc_sody->SetStats(0);
	njets_btags_Z_loose_total_weighted_acc_sody->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_acc_sody->Draw("TEXTCOLZ");
	we3->Print("2D_loose_Z_total_weighted_acc_sody.pdf");
	delete we3;

	TCanvas *we4 = new TCanvas("we4","test",1100,650);
	njets_btags_Z_tight_total_weighted_acc_sody->SetStats(0);
	njets_btags_Z_tight_total_weighted_acc_sody->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_acc_sody->Draw("TEXTCOLZ");
	we4->Print("2D_tight_Z_total_weighted_acc_sody.pdf");
	delete we4;


	// ttjets / ttHbb only

	TCanvas *g1 = new TCanvas("g1","test",1100,650);
	njets_btags_Z_loose_total_sottHbb->SetStats(0);
	njets_btags_Z_loose_total_sottHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_sottHbb->Draw("TEXTCOLZ");
	g1->Print("2D_loose_Z_total_sottHbb.pdf");
	delete g1;

	TCanvas *g2 = new TCanvas("g2","test",1100,650);
	njets_btags_Z_tight_total_sottHbb->SetStats(0);
	njets_btags_Z_tight_total_sottHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_sottHbb->Draw("TEXTCOLZ");
	g2->Print("2D_tight_Z_total_sottHbb.pdf");
	delete g2;

	TCanvas *g3 = new TCanvas("g3","test",1100,650);
	njets_btags_Z_loose_total_acc_sottHbb->SetStats(0);
	njets_btags_Z_loose_total_acc_sottHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_acc_sottHbb->Draw("TEXTCOLZ");
	g3->Print("2D_loose_Z_total_acc_sottHbb.pdf");
	delete g3;

	TCanvas *g4 = new TCanvas("g4","test",1100,650);
	njets_btags_Z_tight_total_acc_sottHbb->SetStats(0);
	njets_btags_Z_tight_total_acc_sottHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_acc_sottHbb->Draw("TEXTCOLZ");
	g4->Print("2D_tight_Z_total_acc_sottHbb.pdf");
	delete g4;

	TCanvas *wg1 = new TCanvas("wg1","test",1100,650);
	njets_btags_Z_loose_total_weighted_sottHbb->SetStats(0);
	njets_btags_Z_loose_total_weighted_sottHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_sottHbb->Draw("TEXTCOLZ");
	wg1->Print("2D_loose_Z_total_weighted_sottHbb.pdf");
	delete wg1;

	TCanvas *wg2 = new TCanvas("wg2","test",1100,650);
	njets_btags_Z_tight_total_weighted_sottHbb->SetStats(0);
	njets_btags_Z_tight_total_weighted_sottHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_sottHbb->Draw("TEXTCOLZ");
	wg2->Print("2D_tight_Z_total_weighted_sottHbb.pdf");
	delete wg2;

	TCanvas *wg3 = new TCanvas("wg3","test",1100,650);
	njets_btags_Z_loose_total_weighted_acc_sottHbb->SetStats(0);
	njets_btags_Z_loose_total_weighted_acc_sottHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_weighted_acc_sottHbb->Draw("TEXTCOLZ");
	wg3->Print("2D_loose_Z_total_weighted_acc_sottHbb.pdf");
	delete wg3;

	TCanvas *wg4 = new TCanvas("wg4","test",1100,650);
	njets_btags_Z_tight_total_weighted_acc_sottHbb->SetStats(0);
	njets_btags_Z_tight_total_weighted_acc_sottHbb->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_tight_total_weighted_acc_sottHbb->Draw("TEXTCOLZ");
	wg4->Print("2D_tight_Z_total_weighted_acc_sottHbb.pdf");
	delete wg4;


	// ttjets MC sample >=4 b-quarks with pt cut > 20 GeV

	TCanvas *h1 = new TCanvas("h1","test",1100,650);
	njets_btags_Z_loose_total_ttjets_4b_pt20->SetStats(0);
	njets_btags_Z_loose_total_ttjets_4b_pt20->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_ttjets_4b_pt20->Draw("TEXTCOLZ");
	h1->Print("2D_loose_Z_total_ttjets_4b_pt20.pdf");
	delete h1;

	TCanvas *h2 = new TCanvas("h2","test",1100,650);
	njets_btags_Z_loose_total_acc_ttjets_4b_pt20->SetStats(0);
	njets_btags_Z_loose_total_acc_ttjets_4b_pt20->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_acc_ttjets_4b_pt20->Draw("TEXTCOLZ");
	h2->Print("2D_loose_Z_total_acc_ttjets_4b_pt20.pdf");
	delete h2;

	TCanvas *h3 = new TCanvas("h3","test",1100,650);
	njets_bjets_Z_loose_total_ttjets_4b_pt20->SetStats(0);
	njets_bjets_Z_loose_total_ttjets_4b_pt20->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_total_ttjets_4b_pt20->Draw("TEXTCOLZ");
	h3->Print("2D_loose_Z_total_njet_bjet_ttjets_4b_pt20.pdf");
	delete h3;

	TCanvas *h4 = new TCanvas("h4","test",1100,650);
	njets_bjets_Z_loose_total_acc_ttjets_4b_pt20->SetStats(0);
	njets_bjets_Z_loose_total_acc_ttjets_4b_pt20->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_total_acc_ttjets_4b_pt20->Draw("TEXTCOLZ");
	h4->Print("2D_loose_Z_total_acc_njet_bjet_ttjets_4b_pt20.pdf");
	delete h4;

	TCanvas *h5 = new TCanvas("h5","test",1100,650);
	njets_btags_Z_loose_ttbb_ttjets_4b_pt20->SetStats(0);
	njets_btags_Z_loose_ttbb_ttjets_4b_pt20->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttbb_ttjets_4b_pt20->Draw("TEXTCOLZ");
	h5->Print("2D_loose_Z_ttbb_ttjets_4b_pt20.pdf");
	delete h5;

	TCanvas *h6 = new TCanvas("h6","test",1100,650);
	njets_btags_Z_loose_ttbb_acc_ttjets_4b_pt20->SetStats(0);
	njets_btags_Z_loose_ttbb_acc_ttjets_4b_pt20->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_ttbb_acc_ttjets_4b_pt20->Draw("TEXTCOLZ");
	h6->Print("2D_loose_Z_ttbb_acc_ttjets_4b_pt20.pdf");
	delete h6;

	TCanvas *h7 = new TCanvas("h7","test",1100,650);
	njets_bjets_Z_loose_ttbb_ttjets_4b_pt20->SetStats(0);
	njets_bjets_Z_loose_ttbb_ttjets_4b_pt20->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_ttbb_ttjets_4b_pt20->Draw("TEXTCOLZ");
	h7->Print("2D_loose_Z_ttbb_njet_bjet_ttjets_4b_pt20.pdf");
	delete h7;

	TCanvas *h8 = new TCanvas("h8","test",1100,650);
	njets_bjets_Z_loose_ttbb_acc_ttjets_4b_pt20->SetStats(0);
	njets_bjets_Z_loose_ttbb_acc_ttjets_4b_pt20->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_ttbb_acc_ttjets_4b_pt20->Draw("TEXTCOLZ");
	h8->Print("2D_loose_Z_ttbb_acc_njet_bjet_ttjets_4b_pt20.pdf");
	delete h8;


	delete f1;
	delete f2;
	delete f3;
	delete f4;
	delete f5;
	delete f6;
	delete f7;
	delete f8;
	delete f9;
	delete f10;
	delete f11;
	delete f12;
	delete f13;
	delete f14;
	delete f15;
	delete f16;
	delete f17;
	delete f18;
	return;
}


