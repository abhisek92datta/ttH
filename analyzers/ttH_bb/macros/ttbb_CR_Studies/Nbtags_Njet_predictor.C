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

// Probabilities for tagging and mis-tagging

double pb = 0.629087;
double pb_bar = 0.370913;
double pbbar = 0.0201374;
double pbbar_bar = 0.979863;

// Recursive Function to select the groups of given size

void select( int start, int end, std::vector<int> & prev, int group, int & count, std::vector< std::vector<int> > & group_list){

	int size = end - start + 1;

	if(group == size){
		std::vector<int> group_prelim;
		group_prelim.clear();
		for(unsigned int j=0; j<prev.size(); j++ ){
			group_prelim.push_back(prev[j]);
		}
		for(int i=start; i<=end; i++){
			group_prelim.push_back(i);
		}
		group_list.push_back(group_prelim);
		count++;
		return;
	}

	else if(group == 1){
		std::vector<int> group_prelim;
		for(int i=start; i<=end; i++){
			group_prelim.clear();
			for(unsigned int j=0; j<prev.size(); j++ ){
				group_prelim.push_back(prev[j]);
			}
			group_prelim.push_back(i);
			group_list.push_back(group_prelim);
			count++;
		}
		return;
	}

	prev.push_back(start);
	start++;
	select(start,end,prev,group-1, count, group_list);

	prev.pop_back();
	select(start, end, prev, group, count, group_list);

	return;
}

// Function to call select() and store the selected and un-selected groups in vectors

void group_maker( int N, int M, std::vector< std::vector<int> > & group_list, std::vector< std::vector<int> > & group_rest_list  ){

	int start = 0;
	std::vector<int> prev;
	prev.clear();
	int count = 0;

	if(M!=0)
		select(start,N-1,prev,M,count, group_list);

	if(group_list.size()==0){
		std::vector<int> group_rest_prelim;
		for(int z=0; z<N; z++){
			group_rest_prelim.push_back(z);
		}
		group_rest_list.push_back(group_rest_prelim);
	}

	for(unsigned int x=0; x<group_list.size(); x++){
		std::vector<int> group_rest_prelim;
		for(int z=0; z<N; z++){
			int match = 0;
			for(unsigned int y=0; y<group_list[x].size(); y++){
				if(z == group_list[x][y]){
					match = 1;
					break;
				}
			}
			if(match==0)
				group_rest_prelim.push_back(z);
		}
		group_rest_list.push_back(group_rest_prelim);
	}
}

// Function to call group_maker() and calculate the final coefficient for the bin

double coeff_calc( std::vector< std::vector<int> > & tagged_list, std::vector< std::vector<int> > & untagged_list , std::vector<int> b ){

	double coeff = 0;

	if(tagged_list.size()==0){
		double prod = 1;
		for( unsigned int j=0; j<untagged_list[0].size(); j++ ){
			if(b[untagged_list[0][j]] == 1)
				prod *= pb_bar;
			else
				prod *= pbbar_bar;
		}
		coeff += prod;
	}

	else if(tagged_list.size()!=0){
		for(unsigned int i=0; i<tagged_list.size(); i++){

			double prod = 1;
			for( unsigned int j=0; j<tagged_list[i].size(); j++ ){
				if(b[tagged_list[i][j]] == 1)
					prod *= pb;
				else
					prod *= pbbar;
			}
			for( unsigned int j=0; j<untagged_list[i].size(); j++ ){
				if(b[untagged_list[i][j]] == 1)
					prod *= pb_bar;
				else
					prod *= pbbar_bar;
			}
			coeff += prod;
		}
	}
	return coeff;
}


void Nbtags_Njet_predictor() {

	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();

	// ttjets

    TFile *f1 = new TFile("Control_Region_Z_2D_jet_tag_yields_bprob_ttjets_all.root");

	// Readinh histograms

    TH2D *njets_btags_Z_loose_total_ttjets = (TH2D*)f1->Get("njets_btags_Z_loose_total");
	TH2D *njets_bjets_Z_loose_total_ttjets = (TH2D*)f1->Get("njets_bjets_Z_loose_total");
	TH2D *njets_btags_Z_loose_total_ttjets_predicted = (TH2D*) njets_btags_Z_loose_total_ttjets->Clone();
	TH2D *njets_btags_Z_loose_total_ttjets_actual_predicted_ratio = (TH2D*) njets_btags_Z_loose_total_ttjets->Clone();

	njets_btags_Z_loose_total_ttjets->SetName("njets_btags_Z_loose_total_ttjets");
	njets_btags_Z_loose_total_ttjets->SetTitle("MC ttjets : Total Nr. of Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_bjets_Z_loose_total_ttjets->SetName("njets_bjets_Z_loose_total_ttjets");
	njets_bjets_Z_loose_total_ttjets->SetTitle("MC ttjets : Total Nr. of Events vs Jet and BJet Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_loose_total_ttjets_predicted->SetName("njets_btags_Z_loose_total_ttjets_predicted");
	njets_btags_Z_loose_total_ttjets_predicted->SetTitle("MC ttjets : Total Nr. of Predicted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");
	njets_btags_Z_loose_total_ttjets_actual_predicted_ratio->SetName("njets_btags_Z_loose_total_ttjets_actual_predicted_ratio");
	njets_btags_Z_loose_total_ttjets_actual_predicted_ratio->SetTitle("MC ttjets : Ratio of Actual / Predicted Events vs Jet and BTag Multiplicity for 76 < M(ll) < 106");

	// Reading the 2D histogram of NBjets vs NJets

	std::vector< std::vector<double> > NA;
	std::vector< std::vector<double> > NB;

	for(int i=1; i<=13; i++){
		std::vector<double> events;
		for(int j=1; j<=7; j++){
			events.push_back(njets_bjets_Z_loose_total_ttjets->GetBinContent(i,j));
		}
		for(int j=7; j<=14; j++)
			events.push_back(0);
		NA.push_back(events);
	}

	/*
	for(unsigned int i=0; i<NA.size(); i++){
		int njets = i+2;
		for(int j=0; j<=njets; j++){
			std::cout<<NA[i][j]<<"  ";
		}
		std::cout<<"\n";
	}
	*/

	// Calculating coefficiencts for every bin and calculating the histogram NBtags vs NJets

	std::vector<int> b;

	for(unsigned int u=0; u<NA.size(); u++){
		int njets = u+2;
		std::vector<double> nbtags_njets_events;
		for(unsigned int i=0; i<=njets; i++){
			double sum = 0;
			int N = njets;
			int M = i;

			std::vector< std::vector<int> > tagged_list;
			std::vector< std::vector<int> > untagged_list;
			tagged_list.clear();
			untagged_list.clear();
			group_maker(N, M, tagged_list, untagged_list);

			for(unsigned int j=0; j<=njets; j++){
				b.clear();
				double coeff;

				for(int k=0; k<j; k++){
					b.push_back(1);
				}
				for(int k=j; k<N; k++){
					b.push_back(0);
				}

				coeff = coeff_calc( tagged_list, untagged_list, b );
				sum += NA[u][j]*coeff;
			}
			nbtags_njets_events.push_back(sum);
		}
		for(unsigned int i=njets+1; i<=14; i++){
			nbtags_njets_events.push_back(0);
		}
		NB.push_back(nbtags_njets_events);
	}


	/*
	std::cout<<"\n";
    for(unsigned int i=0; i<NB.size(); i++){
	   int njets = i+2;
	   for(int j=0; j<=njets; j++){
			std::cout<<NB[i][j]<<"  ";
	   }
   	   std::cout<<"\n";
    }
    */

	// Filling up the histogram with the calculated yields

	for(int i=1; i<=13; i++){
		for(int j=1; j<=7; j++){
			njets_btags_Z_loose_total_ttjets_predicted->SetBinContent(i,j,NB[i-1][j-1]);
		}
	}

	njets_btags_Z_loose_total_ttjets_actual_predicted_ratio->Divide(njets_btags_Z_loose_total_ttjets_predicted);
	

	// Plotting

	gStyle->SetOptStat("ne");
	gStyle->SetPalette(85,0);

	TCanvas *c1 = new TCanvas("c1","test",1100,650);
	njets_btags_Z_loose_total_ttjets->SetStats(0);
	njets_btags_Z_loose_total_ttjets->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_ttjets->Draw("TEXTCOLZ");
	c1->Print("2D_loose_Z_total_njets_nbtags_ttjets.pdf");
	delete c1;

	TCanvas *c2 = new TCanvas("c2","test",1100,650);
	njets_bjets_Z_loose_total_ttjets->SetStats(0);
	njets_bjets_Z_loose_total_ttjets->GetXaxis()->SetNdivisions(13);
	njets_bjets_Z_loose_total_ttjets->Draw("TEXTCOLZ");
	c2->Print("2D_loose_Z_total_njets_nbjets_ttjets.pdf");
	delete c2;

	TCanvas *c3 = new TCanvas("c3","test",1100,650);
	njets_btags_Z_loose_total_ttjets_predicted->SetStats(0);
	njets_btags_Z_loose_total_ttjets_predicted->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_ttjets_predicted->Draw("TEXTCOLZ");
	c3->Print("2D_loose_Z_total_njets_nbtags_predicted_ttjets.pdf");
	delete c3;

	TCanvas *c4 = new TCanvas("c4","test",1100,650);
	njets_btags_Z_loose_total_ttjets_actual_predicted_ratio->SetStats(0);
	njets_btags_Z_loose_total_ttjets_actual_predicted_ratio->GetXaxis()->SetNdivisions(13);
	njets_btags_Z_loose_total_ttjets_actual_predicted_ratio->Draw("TEXTCOLZ");
	c4->Print("2D_loose_Z_total_njets_nbtags_actual_predicted_ratio_ttjets.pdf");
	delete c4;

	delete f1;

	return;
}


