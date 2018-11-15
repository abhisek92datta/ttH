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
#include "TTH/CommonClassifier/interface/BDTClassifier.h"

TLorentzVector p4(double pt, double eta, double phi, double energy) {
    TLorentzVector lv;
    lv.SetPtEtaPhiE(pt, eta, phi, energy);
    return lv;
}

void CommonClassifier_BDT(int maxNentries=-1, int Njobs=1, int jobN=1){

	// Reading from input file

	ifstream fin;
	std::string MC_Data;
	std::string sample;
	int n_input_files;
	std::string file;
	std::vector<std::string> treefilenames;
	std::string process;
	double xs;

	fin.open("input_BDT.txt");
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

	// Initializing counters
	int N_total = 0;
	int N_sel = 0;

	// Setting input file and Trees
	TFile* input_file = new TFile(treefilenames[0].c_str());
	TTree* recoTree_orig = (TTree*)input_file->Get("ttHbb/recoTree");
	TTree* genTree_orig = (TTree*)input_file->Get("ttHbb/genTree");

	// Setting output file and Trees
	std::string output_filename;
	output_filename = ("ttHbbNtuple_" + sample + "_BDT.root").c_str();
	TFile* output_ntuple_file = new TFile(output_filename.c_str(),"recreate");
	TTree* recoTree = recoTree_orig->CloneTree();
	TTree* genTree = genTree_orig->CloneTree();
	TTree* bdtTree = new TTree("bdtTree","bdtTree");

	int nentries = recoTree_orig->GetEntries();
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

	double PFMETpt;
	double PFMETphi;

	recoTree_orig->SetBranchAddress("nEvent", &nEvent );
	recoTree_orig->SetBranchAddress("is_data", &is_data );
	recoTree_orig->SetBranchAddress("pass_event_selection", &pass_event_selection );
	recoTree_orig->SetBranchAddress("n_lep", &n_lep );
	recoTree_orig->SetBranchAddress("n_ele", &n_ele );
	recoTree_orig->SetBranchAddress("n_mu", &n_mu );
	recoTree_orig->SetBranchAddress("ele_pt", &ele_pt );
	recoTree_orig->SetBranchAddress("ele_eta", &ele_eta );
	recoTree_orig->SetBranchAddress("ele_phi", &ele_phi );
	recoTree_orig->SetBranchAddress("ele_E", &ele_E );
	recoTree_orig->SetBranchAddress("ele_charge", &ele_charge );
	recoTree_orig->SetBranchAddress("ele_iso", &ele_iso );
	recoTree_orig->SetBranchAddress("mu_pt", &mu_pt );
	recoTree_orig->SetBranchAddress("mu_eta", &mu_eta );
	recoTree_orig->SetBranchAddress("mu_phi", &mu_phi );
	recoTree_orig->SetBranchAddress("mu_E", &mu_E );
	recoTree_orig->SetBranchAddress("mu_charge", &mu_charge );
	recoTree_orig->SetBranchAddress("mu_iso", &mu_iso );
	recoTree_orig->SetBranchAddress("jet_pt", &jet_pt );
	recoTree_orig->SetBranchAddress("jet_eta", &jet_eta );
	recoTree_orig->SetBranchAddress("jet_phi", &jet_phi );
	recoTree_orig->SetBranchAddress("jet_E", &jet_E );
	recoTree_orig->SetBranchAddress("jet_CSV", &jet_CSV );
	recoTree_orig->SetBranchAddress("n_jets", &n_jets );
	recoTree_orig->SetBranchAddress("n_btags", &n_btags );
	recoTree_orig->SetBranchAddress("PFMETpt", &PFMETpt );
	recoTree_orig->SetBranchAddress("PFMETphi", &PFMETphi );

	// Declaring BDT related variables and linking to new Tree

	double bdt_output;
	std::string bdt_cat;
	std::map<std::string,float> bdt_vars;

	double all_sum_pt_with_met;
	double aplanarity;
	double avg_btag_disc_btags;
	double avg_dr_tagged_jets;
	double best_higgs_mass;
	double closest_tagged_dijet_mass;
	double dEta_fn;
	double dev_from_avg_disc_btags;
	double dr_between_lep_and_closest_jet;
	double fifth_highest_CSV;
	double first_jet_pt;
	double fourth_highest_btag;
	double fourth_jet_pt;
	double h0;
	double h1;
	double h2;
	double h3;
	double HT;
	double invariant_mass_of_everything;
	double lowest_btag;
	double M3;
	double maxeta_jet_jet;
	double maxeta_jet_tag;
	double maxeta_tag_tag;
	double min_dr_tagged_jets;
	double MET;
	double MHT;
	double Mlb;
	double pt_all_jets_over_E_all_jets;
	double second_highest_btag;
	double second_jet_pt;
	double sphericity;
	double tagged_dijet_mass_closest_to_125;
	double third_highest_btag;
	double third_jet_pt;
	double Evt_CSV_Average;
	double Evt_Deta_JetsAverage;
	double blr_transformed;
	double cos_theta_l_bhad;
	double cos_theta_blep_bhad;
	double delta_eta_l_bhad;
	double delta_eta_blep_bhad;
	double delta_phi_l_bhad;
	double delta_phi_blep_bhad;
	double Evt_Deta_TaggedJetsAverage;
	double Evt_M2_TaggedJetsAverage;


	bdtTree->Branch("bdt_output",&bdt_output);
	bdtTree->Branch("bdt_cat",&bdt_cat);
	bdtTree->Branch("all_sum_pt_with_met",&all_sum_pt_with_met);
	bdtTree->Branch("aplanarity",&aplanarity);
	bdtTree->Branch("avg_btag_disc_btags",&avg_btag_disc_btags);
	bdtTree->Branch("avg_dr_tagged_jets",&avg_dr_tagged_jets);
	bdtTree->Branch("best_higgs_mass",&best_higgs_mass);
	bdtTree->Branch("closest_tagged_dijet_mass",&closest_tagged_dijet_mass);
	bdtTree->Branch("dEta_fn",&dEta_fn);
	bdtTree->Branch("dev_from_avg_disc_btags",&dev_from_avg_disc_btags);
	bdtTree->Branch("dr_between_lep_and_closest_jet",&dr_between_lep_and_closest_jet);
	bdtTree->Branch("fifth_highest_CSV",&fifth_highest_CSV);
	bdtTree->Branch("first_jet_pt",&first_jet_pt);
	bdtTree->Branch("fourth_highest_btag",&fourth_highest_btag);
	bdtTree->Branch("fourth_jet_pt",&fourth_jet_pt);
	bdtTree->Branch("h0",&h0);
	bdtTree->Branch("h1",&h1);
	bdtTree->Branch("h2",&h2);
	bdtTree->Branch("h3",&h3);
	bdtTree->Branch("HT",&HT);
	bdtTree->Branch("invariant_mass_of_everything",&invariant_mass_of_everything);
	bdtTree->Branch("lowest_btag",&lowest_btag);
	bdtTree->Branch("M3",&M3);
	bdtTree->Branch("maxeta_jet_jet",&maxeta_jet_jet);
	bdtTree->Branch("maxeta_jet_tag",&maxeta_jet_tag);
	bdtTree->Branch("maxeta_tag_tag",&maxeta_tag_tag);
	bdtTree->Branch("min_dr_tagged_jets",&min_dr_tagged_jets);
	bdtTree->Branch("MET",&MET);
	bdtTree->Branch("MHT",&MHT);
	bdtTree->Branch("Mlb",&Mlb);
	bdtTree->Branch("pt_all_jets_over_E_all_jets",&pt_all_jets_over_E_all_jets);
	bdtTree->Branch("second_highest_btag",&second_highest_btag);
	bdtTree->Branch("second_jet_pt",&second_jet_pt);
	bdtTree->Branch("sphericity",&sphericity);
	bdtTree->Branch("tagged_dijet_mass_closest_to_125",&tagged_dijet_mass_closest_to_125);
	bdtTree->Branch("third_highest_btag",&third_highest_btag);
	bdtTree->Branch("third_jet_pt",&third_jet_pt);
	bdtTree->Branch("Evt_CSV_Average",&Evt_CSV_Average);
	bdtTree->Branch("Evt_Deta_JetsAverage",&Evt_Deta_JetsAverage);
	bdtTree->Branch("blr_transformed",&blr_transformed);
	bdtTree->Branch("cos_theta_l_bhad",&cos_theta_l_bhad);
	bdtTree->Branch("cos_theta_blep_bhad",&cos_theta_blep_bhad);
	bdtTree->Branch("delta_eta_l_bhad",&delta_eta_l_bhad);
	bdtTree->Branch("delta_eta_blep_bhad",&delta_eta_blep_bhad);
	bdtTree->Branch("delta_phi_l_bhad",&delta_phi_l_bhad);
	bdtTree->Branch("delta_phi_blep_bhad",&delta_phi_blep_bhad);
	bdtTree->Branch("Evt_Deta_TaggedJetsAverage",&Evt_Deta_TaggedJetsAverage);
	bdtTree->Branch("Evt_M2_TaggedJetsAverage",&Evt_M2_TaggedJetsAverage);


  	//Setup the BDT
  	BDTClassifier bdt;

	std::cout << "========  Starting Event Loop  ========" << std::endl;
	for (Long64_t ievt=0; ievt<recoTree_orig->GetEntries();ievt++) {

		if( ievt<firstEvent ) continue;
		if( ievt==lastEvent ) break;

		if( ievt==0 )        std::cout << "     Event " << ievt+1 << std::endl;
		if( ievt%10000==0 && ievt!=1) std::cout << "           " << ievt << "\t"
			<< int(double(ievt-1)/double(nentries)*100) << "% done" << std::endl;

		if( ievt==(maxNentries+1) && ievt!=0 ) break;

		recoTree_orig->GetEntry(ievt);

		// Initialize BDT related variables for every event

		bdt_output = -999.;
		bdt_cat = "";

		all_sum_pt_with_met = -999.;
		aplanarity = -999.;
		avg_btag_disc_btags = -999.;
		avg_dr_tagged_jets = -999.;
		best_higgs_mass = -999.;
		closest_tagged_dijet_mass = -999.;
		dEta_fn = -999.;
		dev_from_avg_disc_btags = -999.;
		dr_between_lep_and_closest_jet = -999.;
		fifth_highest_CSV = -999.;
		first_jet_pt = -999.;
		fourth_highest_btag = -999.;
		fourth_jet_pt = -999.;
		h0 = -999.;
		h1 = -999.;
		h2 = -999.;
		h3 = -999.;
		HT = -999.;
		invariant_mass_of_everything = -999.;
		lowest_btag = -999.;
		M3 = -999.;
		maxeta_jet_jet = -999.;
		maxeta_jet_tag = -999.;
		maxeta_tag_tag = -999.;
		min_dr_tagged_jets = -999.;
		MET = -999.;
		MHT = -999.;
		Mlb = -999.;
		pt_all_jets_over_E_all_jets = -999.;
		second_highest_btag = -999.;
		second_jet_pt = -999.;
		sphericity = -999.;
		tagged_dijet_mass_closest_to_125 = -999.;
		third_highest_btag = -999.;
		third_jet_pt = -999.;
		Evt_CSV_Average = -999.;
		Evt_Deta_JetsAverage = -999.;
		blr_transformed = -999.;
		cos_theta_l_bhad = -999.;
		cos_theta_blep_bhad = -999.;
		delta_eta_l_bhad = -999.;
		delta_eta_blep_bhad = -999.;
		delta_phi_l_bhad = -999.;
		delta_phi_blep_bhad = -999.;
		Evt_Deta_TaggedJetsAverage = -999.;
		Evt_M2_TaggedJetsAverage = -999.;

		N_total++;
		//if(N_sel==1)
		//	break;

		// Only for events selected
		if( pass_event_selection == 1 ){

			N_sel++;

			// BDT output for Single Lepton events
			if(n_lep == 1){

				std::vector<TLorentzVector> jets_p4;
				std::vector<TLorentzVector> leps_p4;
				TLorentzVector met_p4;
				std::vector<double> jets_csv;

				// Setting the inputs for the BDT Common Classifier object

				for(int i=0; i<n_jets; i++){
					jets_p4.push_back(p4((*jet_pt)[i], (*jet_eta)[i], (*jet_phi)[i], (*jet_E)[i]));
					jets_csv.push_back((*jet_CSV)[i]);
				}

				if(n_ele == 1)
					leps_p4.push_back(p4((*ele_pt)[0], (*ele_eta)[0], (*ele_phi)[0], (*ele_E)[0]));
				else if(n_mu == 1)
					leps_p4.push_back(p4((*mu_pt)[0], (*mu_eta)[0], (*mu_phi)[0], (*mu_E)[0]));

				met_p4.SetPtEtaPhiM(PFMETpt, 0.0, PFMETphi, 0.0);

				// Getting the BDT output

				bdt_output = bdt.GetBDTOutput(leps_p4, jets_p4, jets_csv, met_p4);
				bdt_cat = bdt.GetCategoryOfLastEvaluation();
				bdt_vars = bdt.GetVariablesOfLastEvaluation();

				all_sum_pt_with_met = bdt_vars["all_sum_pt_with_met"];
				aplanarity = bdt_vars["aplanarity"];
				avg_btag_disc_btags = bdt_vars["avg_btag_disc_btags"];
				avg_dr_tagged_jets = bdt_vars["avg_dr_tagged_jets"];
				best_higgs_mass = bdt_vars["best_higgs_mass"];
				closest_tagged_dijet_mass = bdt_vars["closest_tagged_dijet_mass"];
				dEta_fn = bdt_vars["dEta_fn"];
				dev_from_avg_disc_btags = bdt_vars["dev_from_avg_disc_btags"];
				dr_between_lep_and_closest_jet = bdt_vars["dr_between_lep_and_closest_jet"];
				fifth_highest_CSV = bdt_vars["fifth_highest_CSV"];
				first_jet_pt = bdt_vars["first_jet_pt"];
				fourth_highest_btag = bdt_vars["fourth_highest_btag"];
				fourth_jet_pt = bdt_vars["fourth_jet_pt"];
				h0 = bdt_vars["h0"];
				h1 = bdt_vars["h1"];
				h2 = bdt_vars["h2"];
				h3 = bdt_vars["h3"];
				HT = bdt_vars["HT"];
				invariant_mass_of_everything = bdt_vars["invariant_mass_of_everything"];
				lowest_btag = bdt_vars["lowest_btag"];
				M3 = bdt_vars["M3"];
				maxeta_jet_jet = bdt_vars["maxeta_jet_jet"];
				maxeta_jet_jet = bdt_vars["maxeta_jet_jet"];
				maxeta_tag_tag = bdt_vars["maxeta_tag_tag"];
				min_dr_tagged_jets = bdt_vars["min_dr_tagged_jets"];
				MET = bdt_vars["MET"];
				MHT = bdt_vars["MHT"];
				Mlb = bdt_vars["Mlb"];
				pt_all_jets_over_E_all_jets = bdt_vars["pt_all_jets_over_E_all_jets"];
				second_highest_btag = bdt_vars["second_highest_btag"];
				second_jet_pt = bdt_vars["second_jet_pt"];
				sphericity = bdt_vars["sphericity"];
				tagged_dijet_mass_closest_to_125 = bdt_vars["tagged_dijet_mass_closest_to_125"];
				third_highest_btag = bdt_vars["third_highest_btag"];
				third_jet_pt = bdt_vars["third_jet_pt"];
				Evt_CSV_Average = bdt_vars["Evt_CSV_Average"];
				Evt_Deta_JetsAverage = bdt_vars["Evt_Deta_JetsAverage"];
				blr_transformed = bdt_vars["blr_transformed"];
				cos_theta_l_bhad = bdt_vars["cos_theta_l_bhad"];
				cos_theta_blep_bhad = bdt_vars["cos_theta_blep_bhad"];
				delta_eta_l_bhad = bdt_vars["delta_eta_l_bhad"];
				delta_eta_blep_bhad = bdt_vars["delta_eta_blep_bhad"];
				delta_phi_l_bhad = bdt_vars["delta_phi_l_bhad"];
				delta_phi_blep_bhad = bdt_vars["delta_phi_blep_bhad"];
				Evt_Deta_TaggedJetsAverage = bdt_vars["Evt_Deta_TaggedJetsAverage"];
				Evt_M2_TaggedJetsAverage = bdt_vars["Evt_M2_TaggedJetsAverage"];

				/*
				 int count = 0;
				 std::cout<<nEvent<<"  "<<bdt_output<<"  "<<bdt_cat<<"\n\n";
				 for(auto& i : bdt_vars){
				 std::cout << i.first << " : " << i.second <<"\n";
				 count++;
				 }
				 std::cout<<count<<"\n";
				 */
			}

			// BDT output for Di Lepton events
			//if(n_lep == 2){
			//}
		}

		bdtTree->Fill();
	}

	std::cout<< "\n Done! " << std::endl;
	cout<<"**********************************************************************************************\n\n";
	cout<<"Sample : "<<MC_Data<<"  "<<sample<<"\n";
	cout<<"Total No. of Events in sample : "<<N_total<<"\n";
	cout<<"No. of Selected Events in sample : "<<N_sel<<"\n\n";
	cout<<"**********************************************************************************************\n\n";
	output_ntuple_file->Write();
	delete input_file;
	delete output_ntuple_file;
}

