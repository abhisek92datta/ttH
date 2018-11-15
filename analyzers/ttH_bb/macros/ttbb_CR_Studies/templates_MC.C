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


void templates_MC() {

	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();

	// ttjets

    TFile *f1 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttjets_all.root");

    TH2D *njets_btags_Z_loose_total_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_total");
	TH2D *njets_btags_Z_loose_ttbb_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_ttbb");
	TH2D *njets_btags_Z_loose_ttb_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_ttb");
	TH2D *njets_btags_Z_loose_tt2b_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_tt2b");

	njets_btags_Z_loose_total_ttjets->SetName("njets_btags_Z_loose_total_ttjets");
	njets_btags_Z_loose_total_ttjets->SetTitle("MC ttjets : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_loose_ttbb_ttjets->SetName("njets_btags_Z_loose_ttbb_ttjets");
	njets_btags_Z_loose_ttbb_ttjets->SetTitle("MC ttjets : Nr. of ttbb Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_loose_ttb_ttjets->SetName("njets_btags_Z_loose_ttb_ttjets");
	njets_btags_Z_loose_ttb_ttjets->SetTitle("MC ttjets : Nr. of ttb Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_loose_tt2b_ttjets->SetName("njets_btags_Z_loose_tt2b_ttjets");
	njets_btags_Z_loose_tt2b_ttjets->SetTitle("MC ttjets : Nr. of tt2b Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// DY

	TFile *f2 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_dy_all.root");

	TH2D *njets_btags_Z_loose_total_DY = (TH2D*)f2->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_DY->SetName("njets_btags_Z_loose_total_DY");
	njets_btags_Z_loose_total_DY->SetTitle("MC DY : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ttZ_llnunu

	TFile *f3 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttz_llnunu_all.root");

	TH2D *njets_btags_Z_loose_total_ttZ_llnunu = (TH2D*)f3->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_ttZ_llnunu->SetName("njets_btags_Z_loose_total_ttZ_llnunu");
	njets_btags_Z_loose_total_ttZ_llnunu->SetTitle("MC ttZ_llnunu : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ST antitw

	TFile *f4 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_st_antitw_all.root");

	TH2D *njets_btags_Z_loose_total_st_antitw = (TH2D*)f4->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_st_antitw->SetName("njets_btags_Z_loose_total_st_antitw");
	njets_btags_Z_loose_total_st_antitw->SetTitle("MC st_antitw : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ST s

	TFile *f5 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_st_s_all.root");

	TH2D *njets_btags_Z_loose_total_st_s = (TH2D*)f5->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_st_s->SetName("njets_btags_Z_loose_total_st_s");
	njets_btags_Z_loose_total_st_s->SetTitle("MC st_s : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ST t

	TFile *f6 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_st_t_all.root");

	TH2D *njets_btags_Z_loose_total_st_t = (TH2D*)f6->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_st_t->SetName("njets_btags_Z_loose_total_st_t");
	njets_btags_Z_loose_total_st_t->SetTitle("MC st_t : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ST t anti

	TFile *f7 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_st_t_anti_all.root");

	TH2D *njets_btags_Z_loose_total_st_t_anti = (TH2D*)f7->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_st_t_anti->SetName("njets_btags_Z_loose_total_st_t_anti");
	njets_btags_Z_loose_total_st_t_anti->SetTitle("MC st_t_anti : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ST tw

	TFile *f8 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_st_tw_all.root");

	TH2D *njets_btags_Z_loose_total_st_tw = (TH2D*)f8->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_st_tw->SetName("njets_btags_Z_loose_total_st_tw");
	njets_btags_Z_loose_total_st_tw->SetTitle("MC st_tw : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ttHbb

	TFile *f9 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_tthbb_all.root");

	TH2D *njets_btags_Z_loose_total_ttHbb = (TH2D*)f9->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_ttHbb->SetName("njets_btags_Z_loose_total_ttHbb");
	njets_btags_Z_loose_total_ttHbb->SetTitle("MC ttHbb : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ttHnonbb

	TFile *f10 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_tthnonbb_all.root");

	TH2D *njets_btags_Z_loose_total_ttHnonbb = (TH2D*)f10->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_ttHnonbb->SetName("njets_btags_Z_loose_total_ttHnonbb");
	njets_btags_Z_loose_total_ttHnonbb->SetTitle("MC ttHnonbb : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ttZ_qq

	TFile *f11 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttz_qq_all.root");

	TH2D *njets_btags_Z_loose_total_ttZ_qq = (TH2D*)f11->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_ttZ_qq->SetName("njets_btags_Z_loose_total_ttZ_qq");
	njets_btags_Z_loose_total_ttZ_qq->SetTitle("MC ttZ_qq : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ttw_lnu

	TFile *f12 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttw_lnu_all.root");

	TH2D *njets_btags_Z_loose_total_ttw_lnu = (TH2D*)f12->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_ttw_lnu->SetName("njets_btags_Z_loose_total_ttw_lnu");
	njets_btags_Z_loose_total_ttw_lnu->SetTitle("MC ttw_lnu : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ttw_qq

	TFile *f13 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttw_qq_all.root");

	TH2D *njets_btags_Z_loose_total_ttw_qq = (TH2D*)f13->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_ttw_qq->SetName("njets_btags_Z_loose_total_ttw_qq");
	njets_btags_Z_loose_total_ttw_qq->SetTitle("MC ttw_qq : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// wjets

	TFile *f14 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_wjets_all.root");

	TH2D *njets_btags_Z_loose_total_wjets = (TH2D*)f14->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_wjets->SetName("njets_btags_Z_loose_total_wjets");
	njets_btags_Z_loose_total_wjets->SetTitle("MC wjets : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// WWjets

	TFile *f15 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_wwjets_all.root");

	TH2D *njets_btags_Z_loose_total_wwjets = (TH2D*)f15->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_wwjets->SetName("njets_btags_Z_loose_total_wwjets");
	njets_btags_Z_loose_total_wwjets->SetTitle("MC wwjets : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// WZ jets

	TFile *f16 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_wzjets_all.root");

	TH2D *njets_btags_Z_loose_total_wzjets = (TH2D*)f16->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_wzjets->SetName("njets_btags_Z_loose_total_wzjets");
	njets_btags_Z_loose_total_wzjets->SetTitle("MC wzjets : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ZZ jets

	TFile *f17 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_zzjets_all.root");

	TH2D *njets_btags_Z_loose_total_zzjets = (TH2D*)f17->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_zzjets->SetName("njets_btags_Z_loose_total_zzjets");
	njets_btags_Z_loose_total_zzjets->SetTitle("MC zzjets : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");


	// ttjets >= 4-bquarks with pt cut > 0 GeV

	TFile *f18 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttjets_4b_pt0.root");

	TH2D *njets_btags_Z_loose_total_ttjets_4b_pt0 = (TH2D*)f18->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_ttjets_4b_pt0->SetName("njets_btags_Z_loose_total_ttjets_4b_pt0");
	njets_btags_Z_loose_total_ttjets_4b_pt0->SetTitle("MC ttjets_4b_pt0 : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ttjets >= 4-bquarks with pt cut > 10 GeV

	TFile *f19 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttjets_4b_pt10.root");

	TH2D *njets_btags_Z_loose_total_ttjets_4b_pt10 = (TH2D*)f19->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_ttjets_4b_pt10->SetName("njets_btags_Z_loose_total_ttjets_4b_pt10");
	njets_btags_Z_loose_total_ttjets_4b_pt10->SetTitle("MC ttjets_4b_pt10 : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ttjets >= 4-bquarks with pt cut > 20 GeV

	TFile *f20 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttjets_4b_pt20.root");

	TH2D *njets_btags_Z_loose_total_ttjets_4b_pt20 = (TH2D*)f20->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_ttjets_4b_pt20->SetName("njets_btags_Z_loose_total_ttjets_4b_pt20");
	njets_btags_Z_loose_total_ttjets_4b_pt20->SetTitle("MC ttjets_4b_pt20 : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// ttjets >= 4-bquarks with pt cut > 30 GeV

	TFile *f21 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttjets_4b_pt30.root");

	TH2D *njets_btags_Z_loose_total_ttjets_4b_pt30 = (TH2D*)f21->Get("njets_btags_Z_loose_total");

	njets_btags_Z_loose_total_ttjets_4b_pt30->SetName("njets_btags_Z_loose_total_ttjets_4b_pt30");
	njets_btags_Z_loose_total_ttjets_4b_pt30->SetTitle("MC ttjets_4b_pt30 : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");


	// Adding all Backgrounds other than ttjets

	TH2D *njets_btags_Z_loose_total_rest_bkgd = (TH2D*) njets_btags_Z_loose_total_DY->Clone();
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_ttZ_llnunu);
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_st_antitw);
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_st_s);
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_st_t);
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_st_t_anti);
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_st_tw);
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_ttHbb);
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_ttHnonbb);
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_ttZ_qq);
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_ttw_lnu);
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_ttw_qq);
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_wjets);
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_wwjets);
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_wzjets);
	njets_btags_Z_loose_total_rest_bkgd->Add(njets_btags_Z_loose_total_zzjets);

	njets_btags_Z_loose_total_rest_bkgd->SetName("njets_btags_Z_loose_total_rest_bkgd");
	njets_btags_Z_loose_total_rest_bkgd->SetTitle("MC Rest Background : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//  Models for Signal and Background
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TFile histofile("MC_signal_background_models.root","recreate");
	histofile.cd();

	// Model 1
	// Signal 1 : ttbb , Signal 2 : ttb , Signal 3 : tt2b
	// Background : ttcc + ttlf + rest background

	TH2D *njets_btags_model1_signal1_ttbb = (TH2D*) njets_btags_Z_loose_ttbb_ttjets->Clone();
	njets_btags_model1_signal1_ttbb->SetName("njets_btags_model1_signal1_ttbb");
	njets_btags_model1_signal1_ttbb->SetTitle("Model 1 : Signal 1 - ttbb");
	TH2D *njets_btags_model1_signal2_ttb = (TH2D*) njets_btags_Z_loose_ttb_ttjets->Clone();
	njets_btags_model1_signal2_ttb->SetName("njets_btags_model1_signal2_ttb");
	njets_btags_model1_signal2_ttb->SetTitle("Model 1 : Signal 2 - ttb");
	TH2D *njets_btags_model1_signal3_tt2b = (TH2D*) njets_btags_Z_loose_tt2b_ttjets->Clone();
	njets_btags_model1_signal3_tt2b->SetName("njets_btags_model1_signal3_tt2b");
	njets_btags_model1_signal3_tt2b->SetTitle("Model 1 : Signal 3 - tt2b");

	TH2D *njets_btags_model1_background_ttcc_ttlf_rest = (TH2D*) njets_btags_Z_loose_total_ttjets->Clone();
	njets_btags_model1_background_ttcc_ttlf_rest->Add(njets_btags_Z_loose_ttbb_ttjets,-1);
	njets_btags_model1_background_ttcc_ttlf_rest->Add(njets_btags_Z_loose_ttb_ttjets,-1);
	njets_btags_model1_background_ttcc_ttlf_rest->Add(njets_btags_Z_loose_tt2b_ttjets,-1);
	njets_btags_model1_background_ttcc_ttlf_rest->Add(njets_btags_Z_loose_total_rest_bkgd,1);
	njets_btags_model1_background_ttcc_ttlf_rest->SetName("njets_btags_model1_background_ttcc_ttlf_rest");
	njets_btags_model1_background_ttcc_ttlf_rest->SetTitle("Model 1 : Background - ttcc + ttlf + rest");

	// Model 2
	// Signal : ttjets with >= 4 b-quarks (with pt > 0 GeV)
	// Background : rest ttjets + rest background

	TH2D *njets_btags_model2_signal_ttjets_4b_pt0 = (TH2D*) njets_btags_Z_loose_total_ttjets_4b_pt0->Clone();
	njets_btags_model2_signal_ttjets_4b_pt0->SetName("njets_btags_model2_signal_ttjets_4b_pt0");
	njets_btags_model2_signal_ttjets_4b_pt0->SetTitle("Model 2 : Signal - ttjets >= 4 b-quarks (with pt > 0 GeV)");

	TH2D *njets_btags_model2_background_ttjets_4b_pt0_rest = (TH2D*) njets_btags_Z_loose_total_ttjets->Clone();
	njets_btags_model2_background_ttjets_4b_pt0_rest->Add(njets_btags_Z_loose_total_ttjets_4b_pt0,-1);
	njets_btags_model2_background_ttjets_4b_pt0_rest->Add(njets_btags_Z_loose_total_rest_bkgd,1);
	njets_btags_model2_background_ttjets_4b_pt0_rest->SetName("njets_btags_model2_background_ttjets_4b_pt0_rest");
	njets_btags_model2_background_ttjets_4b_pt0_rest->SetTitle("Model 2 : Background - ttjets < 4 b-quarks (with pt > 0 GeV) + rest");

	// Model 3
	// Signal : ttjets with >= 4 b-quarks (with pt > 10 GeV)
	// Background : rest ttjets + rest background

	TH2D *njets_btags_model3_signal_ttjets_4b_pt10 = (TH2D*) njets_btags_Z_loose_total_ttjets_4b_pt10->Clone();
	njets_btags_model3_signal_ttjets_4b_pt10->SetName("njets_btags_model3_signal_ttjets_4b_pt10");
	njets_btags_model3_signal_ttjets_4b_pt10->SetTitle("Model 3 : Signal - ttjets >= 4 b-quarks (with pt > 10 GeV)");

	TH2D *njets_btags_model3_background_ttjets_4b_pt10_rest = (TH2D*) njets_btags_Z_loose_total_ttjets->Clone();
	njets_btags_model3_background_ttjets_4b_pt10_rest->Add(njets_btags_Z_loose_total_ttjets_4b_pt10,-1);
	njets_btags_model3_background_ttjets_4b_pt10_rest->Add(njets_btags_Z_loose_total_rest_bkgd,1);
	njets_btags_model3_background_ttjets_4b_pt10_rest->SetName("njets_btags_model3_background_ttjets_4b_pt10_rest");
	njets_btags_model3_background_ttjets_4b_pt10_rest->SetTitle("Model 3 : Background - ttjets < 4 b-quarks (with pt > 10 GeV) + rest");

	// Model 4
	// Signal : ttjets with >= 4 b-quarks (with pt > 20 GeV)
	// Background : rest ttjets + rest background

	TH2D *njets_btags_model4_signal_ttjets_4b_pt20 = (TH2D*) njets_btags_Z_loose_total_ttjets_4b_pt20->Clone();
	njets_btags_model4_signal_ttjets_4b_pt20->SetName("njets_btags_model4_signal_ttjets_4b_pt20");
	njets_btags_model4_signal_ttjets_4b_pt20->SetTitle("Model 4 : Signal - ttjets >= 4 b-quarks (with pt > 20 GeV)");

	TH2D *njets_btags_model4_background_ttjets_4b_pt20_rest = (TH2D*) njets_btags_Z_loose_total_ttjets->Clone();
	njets_btags_model4_background_ttjets_4b_pt20_rest->Add(njets_btags_Z_loose_total_ttjets_4b_pt20,-1);
	njets_btags_model4_background_ttjets_4b_pt20_rest->Add(njets_btags_Z_loose_total_rest_bkgd,1);
	njets_btags_model4_background_ttjets_4b_pt20_rest->SetName("njets_btags_model4_background_ttjets_4b_pt20_rest");
	njets_btags_model4_background_ttjets_4b_pt20_rest->SetTitle("Model 4 : Background - ttjets < 4 b-quarks (with pt > 20 GeV) + rest");

	// Model 5
	// Signal : ttjets with >= 4 b-quarks (with pt > 30 GeV)
	// Background : rest ttjets + rest background

	TH2D *njets_btags_model5_signal_ttjets_4b_pt30 = (TH2D*) njets_btags_Z_loose_total_ttjets_4b_pt30->Clone();
	njets_btags_model5_signal_ttjets_4b_pt30->SetName("njets_btags_model5_signal_ttjets_4b_pt30");
	njets_btags_model5_signal_ttjets_4b_pt30->SetTitle("Model 5 : Signal - ttjets >= 4 b-quarks (with pt > 30 GeV)");

	TH2D *njets_btags_model5_background_ttjets_4b_pt30_rest = (TH2D*) njets_btags_Z_loose_total_ttjets->Clone();
	njets_btags_model5_background_ttjets_4b_pt30_rest->Add(njets_btags_Z_loose_total_ttjets_4b_pt30,-1);
	njets_btags_model5_background_ttjets_4b_pt30_rest->Add(njets_btags_Z_loose_total_rest_bkgd,1);
	njets_btags_model5_background_ttjets_4b_pt30_rest->SetName("njets_btags_model5_background_ttjets_4b_pt30_rest->");
	njets_btags_model5_background_ttjets_4b_pt30_rest->SetTitle("Model 5 : Background - ttjets < 4 b-quarks (with pt > 30 GeV) + rest");


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
	delete f19;
	delete f20;
	delete f21;

	histofile.Write();
	histofile.Close();

	return;
}


