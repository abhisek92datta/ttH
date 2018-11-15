#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TH1D.h"
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
#include "THStack.h"


void Compare_Efficiencies_distributions() {

    TH1::SetDefaultSumw2();
    TFile *file;

    // List of Files

    ifstream fin;
    fin.open("files_distributions.txt");
    char filenames[200][200];
    int nfiles = 0;

    while(!fin.eof()){
        fin>>filenames[nfiles];
        nfiles++;
    }
    fin.close();

    // List of Histos

    fin.open("histos.txt");
    char histonames[200][200];
    int nhistos = 0;

    while(!fin.eof()){
        fin>>histonames[nhistos];
        nhistos++;
    }
    fin.close();

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
     double x_etaBins[9] = {-2.1, -1.566, -1.444, -0.8, 0.0, 0.8, 1.444, 1.566, 2.1};

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

    //Looping over files
    for(int i=0; i<nfiles; i++ ){

        file = new TFile(filenames[i]);
        std::string fname = filenames[i];
        std::string type0, type1, type2;

		if(fname.find("Global_MET_data") != std::string::npos){
			type0 = "DATA";
            type1 = "Global_MET_Data";
		}
		else if(fname.find("Global_SM_data") != std::string::npos){
			type0 = "DATA";
			type1 = "Global_SM_Data";
		}
		else if(fname.find("Global_MET_mc") != std::string::npos){
			type0 = "MC";
			type1 = "Global_MET_MC";
		}
		else if(fname.find("Global_SM_mc") != std::string::npos){
			type0 = "MC";
			type1 = "Global_SM_MC";
		}
		else if(fname.find("JetHTLeg_EG_data") != std::string::npos){
			type0 = "DATA";
			type1 = "JetHTLeg_EG_Data";
		}
		else if(fname.find("JetHTLeg_EG_mc") != std::string::npos){
			type0 = "MC";
			type1 = "JetHTLeg_EG_MC";
		}
		else if(fname.find("EleLeg_JET_data") != std::string::npos){
			type0 = "DATA";
			type1 = "EleLeg_JET_Data";
		}
		else if(fname.find("EleLeg_JET_mc") != std::string::npos){
			type0 = "MC";
			type1 = "EleLeg_JET_MC";
		}
		else if(fname.find("EleLeg_HT_data") != std::string::npos){
			type0 = "DATA";
			type1 = "EleLeg_HT_Data";
		}
		else if(fname.find("EleLeg_HT_mc") != std::string::npos){
			type0 = "MC";
			type1 = "EleLeg_HT_MC";
		}
		else
			type1 = "";

        if(fname.find("2017BCDEF") != std::string::npos)
            type2 = "2017BCDEF";
		else if(fname.find("2017B") != std::string::npos)
			type2 = "2017B";
		else if(fname.find("2017C") != std::string::npos)
			type2 = "2017C";
		else if(fname.find("2017D") != std::string::npos)
			type2 = "2017D";
		else if(fname.find("2017E") != std::string::npos)
			type2 = "2017E";
		else if(fname.find("2017F") != std::string::npos)
			type2 = "2017F";
		else if(fname.find("ttjets_sl") != std::string::npos)
			type2 = "ttjets_sl";
        else if(fname.find("ttjets_dl") != std::string::npos)
            type2 = "ttjets_dl";
        else if(fname.find("ttjets_fh") != std::string::npos)
            type2 = "ttjets_fh";
        else if(fname.find("wjets") != std::string::npos)
            type2 = "wjets";
        else if(fname.find("zjets_mll10_50") != std::string::npos)
            type2 = "zjets_mll10_50";
        else if(fname.find("zjets_mll50_inf") != std::string::npos)
            type2 = "zjets_mll50_inf";
		else
			type2 = "combined";

        std::vector<TH1D*> hist_ele_pt;
		std::vector<TH1D*> hist_ele_eta;
        std::vector<TH1D*> hist_ele_sceta;
        std::vector<TH1D*> hist_jet_pt;
		std::vector<TH1D*> hist_jet_eta;
        std::vector<TH1D*> hist_ht;
        std::vector<TH1D*> hist_njets;
        std::vector<TH1D*> hist_npv;
        std::vector<TH2D*> hist_ele_pt_ele_eta;
        std::vector<TH2D*> hist_ele_pt_ele_sceta;
        std::vector<TH2D*> hist_ele_pt_jet_pt;
        std::vector<TH2D*> hist_ele_pt_ht;
        std::vector<std::string> name_ele_pt;
		std::vector<std::string> name_ele_eta;
        std::vector<std::string> name_ele_sceta;
        std::vector<std::string> name_jet_pt;
		std::vector<std::string> name_jet_eta;
        std::vector<std::string> name_ht;
        std::vector<std::string> name_njets;
        std::vector<std::string> name_npv;
        std::vector<std::string> name_ele_pt_ele_eta;
        std::vector<std::string> name_ele_pt_ele_sceta;
        std::vector<std::string> name_ele_pt_jet_pt;
        std::vector<std::string> name_ele_pt_ht;

        std::string name = "";

        for(int j=0; j<nhistos; j++){

            std::string hname = histonames[j];
            name = "";
            TH1D *hist1;
            TH2D *hist2;

            if ((hname.find("pass_ele_pt_ele_eta") != std::string::npos) || (hname.find("pass_ele_pt_ele_sceta") != std::string::npos) || (hname.find("pass_ele_pt_jet_pt") != std::string::npos) ||   (hname.find("pass_ele_pt_ht") != std::string::npos) || (hname.find("total_ele_pt_ele_eta") != std::string::npos) || (hname.find("total_ele_pt_ele_sceta") != std::string::npos) || (hname.find("total_ele_pt_jet_pt") != std::string::npos) ||   (hname.find("total_ele_pt_ht") != std::string::npos)){
                hist2 = (TH2D*)file->Get((hname).c_str());
                hist2->SetTitle((hname).c_str());
                hist2->SetName((hname).c_str());
            }
            else{
                hist1 = (TH1D*)file->Get((hname).c_str());
                hist1->SetTitle((hname).c_str());
                hist1->SetName((hname).c_str());
            }

            if( hname.find("total") != std::string::npos)
                name = "Only Reference Triggers";
            else if( (hname.find("ele30_jet35_OR_ele28_ht150_OR_ele35") != std::string::npos) && (type1.find("Global") != std::string::npos) )
                name = "Ele30_Jet35 OR Ele28_HT150 OR Ele35";
            else if( (hname.find("ele30_jet35_OR_ele28_ht150") != std::string::npos) && (type1.find("Global") != std::string::npos) )
                name = "Ele30_Jet35 OR Ele28_HT150";
            else if( (hname.find("ele30_jet35_OR_ele35") != std::string::npos) && (type1.find("Global") != std::string::npos) )
                name = "Ele30_Jet35 OR Ele35";
            else if( (hname.find("ele28_ht150_OR_ele35") != std::string::npos) && (type1.find("Global") != std::string::npos) )
                name = "Ele28_HT150 OR Ele35";
            else if( (hname.find("jet35") != std::string::npos) && (type1 != "EleLeg_HT_Data") && (type1 != "EleLeg_HT_MC") )
                name = "Ele30_Jet35";
            else if( (hname.find("ht150") != std::string::npos) && (type1 != "EleLeg_JET_Data") && (type1 != "EleLeg_JET_MC") )
                name = "Ele28_HT150";
            else if( (hname.find("ele35") != std::string::npos))
                name = "Ele35";

            if((hname.find("pass_ele_pt_ele_eta") != std::string::npos || hname.find("total_ele_pt_ele_eta") != std::string::npos) && name!=""){
                hist_ele_pt_ele_eta.push_back(hist2);
                name_ele_pt_ele_eta.push_back((name).c_str());
            }
            else if((hname.find("pass_ele_pt_ele_sceta") != std::string::npos || hname.find("total_ele_pt_ele_sceta") != std::string::npos) && name!=""){
                hist_ele_pt_ele_sceta.push_back(hist2);
                name_ele_pt_ele_sceta.push_back((name).c_str());
            }
            else if((hname.find("pass_ele_pt_jet_pt") != std::string::npos || hname.find("total_ele_pt_jet_pt") != std::string::npos) && name!=""){
                hist_ele_pt_jet_pt.push_back(hist2);
                name_ele_pt_jet_pt.push_back((name).c_str());
            }
            else if((hname.find("pass_ele_pt_ht") != std::string::npos || hname.find("total_ele_pt_ht") != std::string::npos) && name!=""){
                hist_ele_pt_ht.push_back(hist2);
                name_ele_pt_ht.push_back((name).c_str());
            }
            else if((hname.find("pass_ele_pt") != std::string::npos || hname.find("total_ele_pt") != std::string::npos) && name!=""){
                hist_ele_pt.push_back(hist1);
                name_ele_pt.push_back((name).c_str());
            }
            else if((hname.find("pass_ele_eta") != std::string::npos || hname.find("total_ele_eta") != std::string::npos) && name!=""){
                hist_ele_eta.push_back(hist1);
                name_ele_eta.push_back((name).c_str());
            }
            else if((hname.find("pass_ele_sceta") != std::string::npos || hname.find("total_ele_sceta") != std::string::npos) && name!=""){
                hist_ele_sceta.push_back(hist1);
                name_ele_sceta.push_back((name).c_str());
            }
            else if((hname.find("pass_jet_pt") != std::string::npos || hname.find("total_jet_pt") != std::string::npos) && name!=""){
                hist_jet_pt.push_back(hist1);
                name_jet_pt.push_back((name).c_str());
            }
            else if((hname.find("pass_jet_eta") != std::string::npos || hname.find("total_jet_eta") != std::string::npos) && name!=""){
                hist_jet_eta.push_back(hist1);
                name_jet_eta.push_back((name).c_str());
            }
            else if((hname.find("pass_ht") != std::string::npos || hname.find("total_ht") != std::string::npos) && name!=""){
                hist_ht.push_back(hist1);
                name_ht.push_back((name).c_str());
            }
            else if((hname.find("pass_njets") != std::string::npos || hname.find("total_njets") != std::string::npos) && name!=""){
                hist_njets.push_back(hist1);
                name_njets.push_back((name).c_str());
            }
            else if( ((hname.find("pass_npv") != std::string::npos || hname.find("total_npv") != std::string::npos) && name!="") && type0 == "MC"){
                hist_npv.push_back(hist1);
                name_npv.push_back((name).c_str());
            }
        }

        gStyle->SetLegendBorderSize(1);
        gStyle->SetLegendTextSize(0.025);

        // Efficiency vs Electron Pt
        if(hist_ele_pt.size() != 0){
            //double ll = *(x_eleptBins);
            double ll = 0;
            double ul = *(x_eleptBins+n_eleptBins);
            TCanvas *c1 = new TCanvas("c1","test",1100,650);
            c1->DrawFrame(ll,0,ul,6000,(type0 + " " + type1 + "_" + type2 + " : Nr. of Events vs Electron pT; pT (Electron) [GeV] ; Efficiency").c_str());
			c1->SetGrid();
			TLegend* leg1;
			leg1 = new TLegend(0.50,0.35,0.85,0.60);
            leg1->SetFillColor(kWhite);
            leg1->SetFillStyle(1001);
            for(unsigned int u=0; u<hist_ele_pt.size(); u++){
                leg1->AddEntry(hist_ele_pt[u],(name_ele_pt[u]).c_str(),"L");
                hist_ele_pt[u]->SetLineWidth(1);
                hist_ele_pt[u]->SetLineColor(u+1);
                hist_ele_pt[u]->Draw("L same");
            }
            leg1->Draw("same");
            c1->Print(("Distribution_" + type1 + "_" + type2 + "_" + "ele_pt.pdf").c_str());
            delete c1;
            delete leg1;
        }

		// Efficiency vs Electron Eta
		if(hist_ele_eta.size() != 0){
            double ll = *(x_eleetaBins);
            double ul = *(x_eleetaBins+n_eleetaBins);
			TCanvas *c1 = new TCanvas("c1","test",1100,650);
			c1->DrawFrame(ll,0,ul,2500,(type0 + " " + type1 + "_" + type2 + " : Nr. of Events vs Electron eta; eta (Electron) ; Efficiency").c_str());
			c1->SetGrid();
			TLegend* leg1;
			leg1 = new TLegend(0.30,0.15,0.65,0.40);
			leg1->SetFillColor(kWhite);
			leg1->SetFillStyle(1001);
			for(unsigned int u=0; u<hist_ele_eta.size(); u++){
				leg1->AddEntry(hist_ele_eta[u],(name_ele_eta[u]).c_str(),"L");
				hist_ele_eta[u]->SetLineWidth(1);
				hist_ele_eta[u]->SetLineColor(u+1);
				hist_ele_eta[u]->Draw("L same");
			}
			leg1->Draw("same");
			c1->Print(("Distribution_" + type1 + "_" + type2 + "_" + "ele_eta.pdf").c_str());
			delete c1;
			delete leg1;
        }

        // Efficiency vs Electron SuperCluster Eta
        if(hist_ele_eta.size() != 0){
            double ll = *(x_eleetaBins);
            double ul = *(x_eleetaBins+n_eleetaBins);
            TCanvas *c1 = new TCanvas("c1","test",1100,650);
            c1->DrawFrame(ll,0,ul,2500,(type0 + " " + type1 + "_" + type2 + " : Nr. of Events vs Electron SuperCluster eta; SuperCluster eta (Electron) ; Efficiency").c_str());
            c1->SetGrid();
            TLegend* leg1;
            leg1 = new TLegend(0.30,0.15,0.65,0.40);
            leg1->SetFillColor(kWhite);
            leg1->SetFillStyle(1001);
            for(unsigned int u=0; u<hist_ele_sceta.size(); u++){
                leg1->AddEntry(hist_ele_sceta[u],(name_ele_sceta[u]).c_str(),"L");
                hist_ele_sceta[u]->SetLineWidth(1);
                hist_ele_sceta[u]->SetLineColor(u+1);
                hist_ele_sceta[u]->Draw("L same");
            }
            leg1->Draw("same");
            c1->Print(("Distribution_" + type1 + "_" + type2 + "_" + "ele_sceta.pdf").c_str());
            delete c1;
            delete leg1;
        }

        // Efficiency vs Jet Pt
        if(hist_jet_pt.size() != 0){
            //double ll = *(x_jetptBins);
            double ll = 0;
            double ul = *(x_jetptBins+n_jetptBins);
            TCanvas *c1 = new TCanvas("c1","test",1100,650);
            c1->DrawFrame(ll,0,ul,5000,(type0 + " " + type1 + "_" + type2 + " : Nr. of Events vs Leading Jet pT; pT (Leading Jet) [GeV] ; Efficiency").c_str());
			c1->SetGrid();
			TLegend* leg1;
			leg1 = new TLegend(0.50,0.35,0.85,0.60);
            leg1->SetFillColor(kWhite);
            leg1->SetFillStyle(1001);
            for(unsigned int u=0; u<hist_jet_pt.size(); u++){
                leg1->AddEntry(hist_jet_pt[u],(name_jet_pt[u]).c_str(),"L");
                hist_jet_pt[u]->SetLineWidth(1);
                hist_jet_pt[u]->SetLineColor(u+1);
                hist_jet_pt[u]->Draw("L same");
            }
            leg1->Draw("same");
            c1->Print(("Distribution_" + type1 + "_" + type2 + "_" + "jet_pt.pdf").c_str());
            delete c1;
            delete leg1;
        }

		// Efficiency vs Jet Eta
		if(hist_jet_eta.size() != 0){
            double ll = *(x_jetetaBins);
            double ul = *(x_jetetaBins+n_jetetaBins);
			TCanvas *c1 = new TCanvas("c1","test",1100,650);
			c1->DrawFrame(ll,0,ul,2000,(type0 + " " + type1 + "_" + type2 + " : Nr. of Events vs Leading Jet eta; eta (Leading Jet) ; Efficiency").c_str());
			c1->SetGrid();
			TLegend* leg1;
			leg1 = new TLegend(0.3,0.15,0.65,0.40);
			leg1->SetFillColor(kWhite);
			leg1->SetFillStyle(1001);
			for(unsigned int u=0; u<hist_jet_eta.size(); u++){
				leg1->AddEntry(hist_jet_eta[u],(name_jet_eta[u]).c_str(),"L");
				hist_jet_eta[u]->SetLineWidth(1);
				hist_jet_eta[u]->SetLineColor(u+1);
				hist_jet_eta[u]->Draw("L same");
			}
			leg1->Draw("same");
			c1->Print(("Distribution_" + type1 + "_" + type2 + "_" + "jet_eta.pdf").c_str());
			delete c1;
			delete leg1;
		}

        // Efficiency vs HT
        if(hist_ht.size() != 0){
            double ll = *(x_htBins);
            double ul = *(x_htBins+n_htBins);
            TCanvas *c1 = new TCanvas("c1","test",1100,650);
            c1->DrawFrame(ll,0,ul,6000,(type0 + " " + type1 + "_" + type2 + " : Nr. of Events vs HT; HT [GeV] ; Efficiency").c_str());
			c1->SetGrid();
			TLegend* leg1;
			leg1 = new TLegend(0.50,0.55,0.85,0.80);
            leg1->SetFillColor(kWhite);
            leg1->SetFillStyle(1001);
            for(unsigned int u=0; u<hist_ht.size(); u++){
                leg1->AddEntry(hist_ht[u],(name_ht[u]).c_str(),"L");
                hist_ht[u]->SetLineWidth(1);
                hist_ht[u]->SetLineColor(u+1);
                hist_ht[u]->Draw("L same");
            }
            leg1->Draw("same");
            c1->Print(("Distribution_" + type1 + "_" + type2 + "_" + "ht.pdf").c_str());
            delete c1;
            delete leg1;
        }

        // Efficiency vs Nr. of jets
        if(hist_njets.size() != 0){
            double ll = *(x_njetBins);
            double ul = *(x_njetBins+n_njetBins);
            TCanvas *c1 = new TCanvas("c1","test",1100,650);
            c1->DrawFrame(ll,0,ul,21000,(type0 + " " + type1 + "_" + type2 + " : Nr. of Events vs Jet Multiplicity; Nr. of Jets ; Efficiency").c_str());
			c1->SetGrid();
			TLegend* leg1;
			leg1 = new TLegend(0.50,0.35,0.85,0.60);
            leg1->SetFillColor(kWhite);
            leg1->SetFillStyle(1001);
            for(unsigned int u=0; u<hist_njets.size(); u++){
                leg1->AddEntry(hist_njets[u],(name_njets[u]).c_str(),"L");
                hist_njets[u]->SetLineWidth(1);
                hist_njets[u]->SetLineColor(u+1);
                hist_njets[u]->Draw("L same");
            }
            leg1->Draw("same");
            c1->Print(("Distribution_" + type1 + "_" + type2 + "_" + "njets.pdf").c_str());
            delete c1;
            delete leg1;
        }

        // Efficiency vs Nr. of primary vertices
        if(hist_npv.size() != 0){
            double ll = 0;
            double ul = 75;
            TCanvas *c1 = new TCanvas("c1","test",1100,650);
            c1->DrawFrame(ll,0,ul,2500,(type0 + " " + type1 + "_" + type2 + " : Nr. of Events vs Jet Multiplicity; Nr. of Primary Vertices ; Efficiency").c_str());
            c1->SetGrid();
            TLegend* leg1;
            leg1 = new TLegend(0.50,0.55,0.85,0.80);
            leg1->SetFillColor(kWhite);
            leg1->SetFillStyle(1001);
            for(unsigned int u=0; u<hist_npv.size(); u++){
                leg1->AddEntry(hist_npv[u],(name_npv[u]).c_str(),"L");
                hist_npv[u]->SetLineWidth(1);
                hist_npv[u]->SetLineColor(u+1);
                hist_npv[u]->Draw("L same");
            }
            leg1->Draw("same");
            c1->Print(("Distribution_" + type1 + "_" + type2 + "_" + "npv.pdf").c_str());
            delete c1;
            delete leg1;
        }

        // Efficiency vs Electron Pt and Electron Eta
        if(hist_ele_pt_ele_eta.size() != 0){
            double ll1 = *(x_eleptBins);
            double ul1 = *(x_eleptBins+n_eleptBins);
            double ll2 = *(x_eleetaBins);
            double ul2 = *(x_eleetaBins+n_eleetaBins);
            TCanvas *c1 = new TCanvas("c1","test",1100,650);
            c1->DrawFrame(ll1,ll2,ul1,ul2,(type0 + " " + type1 + "_" + type2 + " : Nr. of Events vs Electron pT and Electron Eta; pT (Electron) [GeV]; Eta (Electron) ; Efficiency").c_str());
            c1->SetGrid();
            TLegend* leg1;
            leg1 = new TLegend(0.50,0.15,0.85,0.40);
            leg1->SetFillColor(kWhite);
            leg1->SetFillStyle(1001);
            for(unsigned int u=0; u<hist_ele_pt_ele_eta.size(); u++){
                leg1->AddEntry(hist_ele_pt_ele_eta[u],(name_ele_pt_ele_eta[u]).c_str(),"L");
                hist_ele_pt_ele_eta[u]->SetLineWidth(1);
                hist_ele_pt_ele_eta[u]->SetLineColor(u+1);
                hist_ele_pt_ele_eta[u]->Draw("same");
            }
            leg1->Draw("same");
            c1->Print(("Distribution_" + type1 + "_" + type2 + "_" + "ele_pt_ele_eta.pdf").c_str());
            delete c1;
            delete leg1;
        }

        // Efficiency vs Electron Pt and Electron SuperCluster Eta
        if(hist_ele_pt_ele_eta.size() != 0){
            double ll1 = *(x_eleptBins);
            double ul1 = *(x_eleptBins+n_eleptBins);
            double ll2 = *(x_eleetaBins);
            double ul2 = *(x_eleetaBins+n_eleetaBins);
            TCanvas *c1 = new TCanvas("c1","test",1100,650);
            c1->DrawFrame(ll1,ll2,ul1,ul2,(type0 + " " + type1 + "_" + type2 + " : Nr. of Events vs Electron pT and Electron SuperCluster Eta; pT (Electron) [GeV]; SuperCluster Eta (Electron) ; Efficiency").c_str());
            c1->SetGrid();
            TLegend* leg1;
            leg1 = new TLegend(0.50,0.15,0.85,0.40);
            leg1->SetFillColor(kWhite);
            leg1->SetFillStyle(1001);
            for(unsigned int u=0; u<hist_ele_pt_ele_sceta.size(); u++){
                leg1->AddEntry(hist_ele_pt_ele_sceta[u],(name_ele_pt_ele_sceta[u]).c_str(),"L");
                hist_ele_pt_ele_sceta[u]->SetLineWidth(1);
                hist_ele_pt_ele_sceta[u]->SetLineColor(u+1);
                hist_ele_pt_ele_sceta[u]->Draw("same");
            }
            leg1->Draw("same");
            c1->Print(("Distribution_" + type1 + "_" + type2 + "_" + "ele_pt_ele_sceta.pdf").c_str());
            delete c1;
            delete leg1;
        }

        // Efficiency vs Electron Pt and Leading Jet Pt
        if(hist_ele_pt_jet_pt.size() != 0){
            double ll1 = *(x_eleptBins);
            double ul1 = *(x_eleptBins+n_eleptBins);
            double ll2 = *(x_jetptBins);
            double ul2 = *(x_jetptBins+n_jetptBins);
            TCanvas *c1 = new TCanvas("c1","test",1100,650);
            c1->DrawFrame(ll1,ll2,ul1,ul2,(type0 + " " + type1 + "_" + type2 + " : Nr. of Events vs Electron pT and Leading Jet pT; pT (Electron) [GeV]; pT (Leading Jet) [GeV] ; Efficiency").c_str());
            c1->SetGrid();
            TLegend* leg1;
            leg1 = new TLegend(0.50,0.15,0.85,0.40);
            leg1->SetFillColor(kWhite);
            leg1->SetFillStyle(1001);
            for(unsigned int u=0; u<hist_ele_pt_jet_pt.size(); u++){
                leg1->AddEntry(hist_ele_pt_jet_pt[u],(name_ele_pt_jet_pt[u]).c_str(),"L");
                hist_ele_pt_jet_pt[u]->SetLineWidth(1);
                hist_ele_pt_jet_pt[u]->SetLineColor(u+1);
                hist_ele_pt_jet_pt[u]->Draw("same");
            }
            leg1->Draw("same");
            c1->Print(("Distribution_" + type1 + "_" + type2 + "_" + "ele_pt_jet_pt.pdf").c_str());
            delete c1;
            delete leg1;
        }

        // Efficiency vs Electron Pt and HT
        if(hist_ele_pt_ht.size() != 0){
            double ll1 = *(x_eleptBins);
            double ul1 = *(x_eleptBins+n_eleptBins);
            double ll2 = *(x_htBins);
            double ul2 = *(x_htBins+n_htBins);
            TCanvas *c1 = new TCanvas("c1","test",1100,650);
            c1->DrawFrame(ll1,ll2,ul1,ul2,(type0 + " " + type1 + "_" + type2 + " : Nr. of Events vs Electron pT and HT; pT (Electron) [GeV]; HT [GeV] ; Efficiency").c_str());
            c1->SetGrid();
            TLegend* leg1;
            leg1 = new TLegend(0.50,0.15,0.85,0.40);
            leg1->SetFillColor(kWhite);
            leg1->SetFillStyle(1001);
            for(unsigned int u=0; u<hist_ele_pt_ht.size(); u++){
                leg1->AddEntry(hist_ele_pt_ht[u],(name_ele_pt_ht[u]).c_str(),"L");
                hist_ele_pt_ht[u]->SetLineWidth(1);
                hist_ele_pt_ht[u]->SetLineColor(u+1);
                hist_ele_pt_ht[u]->Draw("same");
            }
            leg1->Draw("same");
            c1->Print(("Distribution_" + type1 + "_" + type2 + "_" + "ele_pt_ht.pdf").c_str());
            delete c1;
            delete leg1;
        }

        
        
    }

    delete file;
	return;
}


