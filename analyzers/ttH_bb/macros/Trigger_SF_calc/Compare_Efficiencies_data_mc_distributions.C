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


void Compare_Efficiencies_data_mc_distributions() {

    TH1::SetDefaultSumw2();
    TFile *file_data;
    TFile *file_mc_ttjets_sl;
    TFile *file_mc_ttjets_dl;
    TFile *file_mc_ttjets_fh;
    TFile *file_mc_wjets;
    TFile *file_mc_zjets_mll10_50;
    TFile *file_mc_zjets_mll50_inf;

    // List of Files

    ifstream fin;
    fin.open("files_distributions.txt");
    char filenames_data[200][200];
    char filenames_mc_ttjets_sl[200][200];
    char filenames_mc_ttjets_dl[200][200];
    char filenames_mc_ttjets_fh[200][200];
    char filenames_mc_wjets[200][200];
    char filenames_mc_zjets_mll10_50[200][200];
    char filenames_mc_zjets_mll50_inf[200][200];
    int nfiles = 0;

    while(!fin.eof()){
        fin>>filenames_data[nfiles];
        fin>>filenames_mc_ttjets_sl[nfiles];
        fin>>filenames_mc_ttjets_dl[nfiles];
        fin>>filenames_mc_ttjets_fh[nfiles];
        fin>>filenames_mc_wjets[nfiles];
        fin>>filenames_mc_zjets_mll10_50[nfiles];
        fin>>filenames_mc_zjets_mll50_inf[nfiles];
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

        std::string fname_data = filenames_data[i];
        std::string fname_mc_ttjets_sl = filenames_mc_ttjets_sl[i];
        std::string fname_mc_ttjets_dl = filenames_mc_ttjets_dl[i];
        std::string fname_mc_ttjets_fh = filenames_mc_ttjets_fh[i];
        std::string fname_mc_wjets = filenames_mc_wjets[i];
        std::string fname_mc_zjets_mll10_50 = filenames_mc_zjets_mll10_50[i];
        std::string fname_mc_zjets_mll50_inf = filenames_mc_zjets_mll50_inf[i];
        file_data = new TFile(filenames_data[i]);
        file_mc_ttjets_sl = new TFile(filenames_mc_ttjets_sl[i]);
        file_mc_ttjets_dl = new TFile(filenames_mc_ttjets_dl[i]);
        file_mc_ttjets_fh = new TFile(filenames_mc_ttjets_fh[i]);
        file_mc_wjets = new TFile(filenames_mc_wjets[i]);
        file_mc_zjets_mll10_50 = new TFile(filenames_mc_zjets_mll10_50[i]);
        file_mc_zjets_mll50_inf = new TFile(filenames_mc_zjets_mll50_inf[i]);
        std::string type0, type1, type2;

		if(fname_data.find("Global_MET_data") != std::string::npos){
			type0 = "DATA_MC";
            type1 = "Global_MET_Data";
		}
		else if(fname_data.find("Global_SM_data") != std::string::npos){
			type0 = "DATA_MC";
			type1 = "Global_SM_Data";
		}
		else if(fname_data.find("JetHTLeg_EG_data") != std::string::npos){
			type0 = "DATA_MC";
			type1 = "JetHTLeg_EG_Data";
		}
		else if(fname_data.find("EleLeg_JET_data") != std::string::npos){
			type0 = "DATA_MC";
			type1 = "EleLeg_JET_Data";
		}
		else if(fname_data.find("EleLeg_HT_data") != std::string::npos){
			type0 = "DATA_MC";
			type1 = "EleLeg_HT_Data";
		}
		else
			type1 = "";

        if(fname_data.find("2017BCDEF") != std::string::npos)
            type2 = "2017BCDEF";
		else if(fname_data.find("2017B") != std::string::npos)
			type2 = "2017B";
		else if(fname_data.find("2017C") != std::string::npos)
			type2 = "2017C";
		else if(fname_data.find("2017D") != std::string::npos)
			type2 = "2017D";
		else if(fname_data.find("2017E") != std::string::npos)
			type2 = "2017E";
		else if(fname_data.find("2017F") != std::string::npos)
			type2 = "2017F";
        else
            type2 = "";

        for(int j=0; j<nhistos; j++){

            std::string hname = histonames[j];
            TH1D *hist_data;
            TH1D *hist_mc_ttjets_sl;
            TH1D *hist_mc_ttjets_dl;
            TH1D *hist_mc_ttjets_fh;
            TH1D *hist_mc_wjets;
            TH1D *hist_mc_zjets_mll10_50;
            TH1D *hist_mc_zjets_mll50_inf;

            THStack *hist_mc = new THStack("hist_mc","Stacked Distributions for MC");
            double ll1, ll2;
            double ul1, ul2;
            double leg_xl, leg_xu, leg_yl, leg_yu;
            std::string c_title1 = "";
            std::string c_title2 = "";
            std::string f_title1 = "";
            std::string f_title2 = "";

            if ((hname.find("pass_ele_pt_ele_eta") != std::string::npos) || (hname.find("pass_ele_pt_ele_sceta") != std::string::npos) || (hname.find("pass_ele_pt_jet_pt") != std::string::npos) ||   (hname.find("pass_ele_pt_ht") != std::string::npos) || (hname.find("total_ele_pt_ele_eta") != std::string::npos) || (hname.find("total_ele_pt_ele_sceta") != std::string::npos) || (hname.find("total_ele_pt_jet_pt") != std::string::npos) ||   (hname.find("total_ele_pt_ht") != std::string::npos)){
                continue;
            }
            else{
                hist_data = (TH1D*)file_data->Get((hname).c_str());
                hist_mc_ttjets_sl = (TH1D*)file_mc_ttjets_sl->Get((hname).c_str());
                hist_mc_ttjets_dl = (TH1D*)file_mc_ttjets_dl->Get((hname).c_str());
                hist_mc_ttjets_fh = (TH1D*)file_mc_ttjets_fh->Get((hname).c_str());
                hist_mc_wjets = (TH1D*)file_mc_wjets->Get((hname).c_str());
                hist_mc_zjets_mll10_50 = (TH1D*)file_mc_zjets_mll10_50->Get((hname).c_str());
                hist_mc_zjets_mll50_inf = (TH1D*)file_mc_zjets_mll50_inf->Get((hname).c_str());

                hist_mc->Add(hist_mc_wjets);
                hist_mc->Add(hist_mc_zjets_mll10_50);
                hist_mc->Add(hist_mc_zjets_mll50_inf);
                hist_mc->Add(hist_mc_ttjets_fh);
                hist_mc->Add(hist_mc_ttjets_sl);
                hist_mc->Add(hist_mc_ttjets_dl);
            }

            if((hname.find("pass_ele_pt") != std::string::npos || hname.find("total_ele_pt") != std::string::npos)){
                ll1 = 0;
                ul1 = *(x_eleptBins+n_eleptBins);
                ll2 = 0;
                ul2 = 6000;
                leg_xl = 0.50;
                leg_yl = 0.55;
                leg_xu = 0.85;
                leg_yu = 0.80;
                c_title2 = "Electron pT; pT (Electron) [GeV] ";
                f_title2 = "ele_pt";
            }
            else if((hname.find("pass_ele_eta") != std::string::npos || hname.find("total_ele_eta") != std::string::npos)){
                ll1 = *(x_eleetaBins);
                ul1 = *(x_eleetaBins+n_eleetaBins);
                ll2 = 0;
                ul2 = 2500;
                leg_xl = 0.30;
                leg_yl = 0.15;
                leg_xu = 0.65;
                leg_yu = 0.40;
                c_title2 = "Electron eta; eta (Electron) ";
                f_title2 = "ele_eta";
            }
            else if((hname.find("pass_ele_sceta") != std::string::npos || hname.find("total_ele_sceta") != std::string::npos)){
                ll1 = *(x_eleetaBins);
                ul1 = *(x_eleetaBins+n_eleetaBins);
                ll2 = 0;
                ul2 = 2500;
                leg_xl = 0.30;
                leg_yl = 0.15;
                leg_xu = 0.65;
                leg_yu = 0.40;
                c_title2 = "Electron SuperCluster eta; eta SuperCluster (Electron) ";
                f_title2 = "ele_eta";
            }
            else if((hname.find("pass_jet_pt") != std::string::npos || hname.find("total_jet_pt") != std::string::npos)){
                ll1 = 0;
                ul1 = *(x_jetptBins+n_jetptBins);
                ll2 = 0;
                ul2 = 5000;
                leg_xl = 0.50;
                leg_yl = 0.55;
                leg_xu = 0.85;
                leg_yu = 0.80;
                c_title2 = "Leading Jet pT; pT (Leading Jet) [GeV] ";
                f_title2 = "jet_pt";
            }
            else if((hname.find("pass_jet_eta") != std::string::npos || hname.find("total_jet_eta") != std::string::npos)){
                ll1 = *(x_jetetaBins);
                ul1 = *(x_jetetaBins+n_jetetaBins);
                ll2 = 0;
                ul2 = 2000;
                leg_xl = 0.30;
                leg_yl = 0.15;
                leg_xu = 0.65;
                leg_yu = 0.40;
                c_title2 = "Leading Jet eta; eta (Leading Jet) ";
                f_title2 = "jet_eta";
            }
            else if((hname.find("pass_ht") != std::string::npos || hname.find("total_ht") != std::string::npos)){
                ll1 = 0;
                ul1 = *(x_htBins+n_htBins);
                ll2 = 0;
                ul2 = 6000;
                leg_xl = 0.50;
                leg_yl = 0.55;
                leg_xu = 0.85;
                leg_yu = 0.80;
                c_title2 = "HT; HT [GeV] ";
                f_title2 = "ht";
            }
            else if((hname.find("pass_njets") != std::string::npos || hname.find("total_njets") != std::string::npos)){
                ll1 = *(x_njetBins);
                ul1 = *(x_njetBins+n_njetBins);
                ll2 = 0;
                ul2 = 21000;
                leg_xl = 0.50;
                leg_yl = 0.55;
                leg_xu = 0.85;
                leg_yu = 0.80;
                c_title2 = "Jet Multiplicity; Nr. of Jets ";
                f_title2 = "njets";
            }
            else if((hname.find("pass_npv") != std::string::npos || hname.find("total_npv") != std::string::npos)){
                ll1 = 0;
                ul1 = 75;
                ll2 = 0;
                ul2 = 2500;
                leg_xl = 0.50;
                leg_yl = 0.55;
                leg_xu = 0.85;
                leg_yu = 0.80;
                c_title2 = "Nr. of Primary Vertices; NPV ";
                f_title2 = "npv";
            }

            if( hname.find("total") != std::string::npos){
                c_title1 = "Only Reference Triggers";
                f_title1 = "Ref_";
            }
            else if(hname.find("ele30_jet35_OR_ele28_ht150_OR_ele35") != std::string::npos){
                c_title1 = "Ele30 + Jet35 OR Ele28 + HT150 OR Ele35";
                f_title1 = "EleJet_OR_EleHT_OR_Ele35_";
            }
            else if(hname.find("ele30_jet35_OR_ele28_ht150") != std::string::npos){
                c_title1 = "Ele30 + Jet35 OR Ele28 + HT150";
                f_title1 = "EleJet_OR_EleHT_";
            }
            else if(hname.find("ele30_jet35_OR_ele35") != std::string::npos){
                c_title1 = "Ele30 + Jet35 OR Ele35";
                f_title1 = "EleJet_OR_Ele35_";
            }
            else if(hname.find("ele28_ht150_OR_ele35") != std::string::npos){
                c_title1 = "Ele28 + HT150 OR Ele35";
                f_title1 = "EleHT_OR_Ele35_";
            }
            else if(hname.find("jet35") != std::string::npos){
                c_title1 = "Ele30 + Jet35";
                f_title1 = "EleJet_";
            }
            else if(hname.find("ht150") != std::string::npos){
                c_title1 = "Ele28 + HT150";
                f_title1 = "EleHT_";
            }
            else if(hname.find("ele35") != std::string::npos){
                c_title1 = "Ele35";
                f_title1 = "Ele35_";
            }

            if (c_title1 == "")
                continue;

            // Plotting
            gStyle->SetLegendBorderSize(1);
            gStyle->SetLegendTextSize(0.025);
            gStyle->SetPalette(kOcean);

            TCanvas *c1 = new TCanvas("c1","test",1100,650);
            c1->DrawFrame(ll1,ll2,ul1,ul2,(type0 + " " + type1 + "_" + type2 + " : " + c_title1 + " Nr. of Events vs " + c_title2 + "; Nr. of Events").c_str());
            c1->SetGrid();
            TLegend* leg1;
            leg1 = new TLegend(leg_xl,leg_yl,leg_xu,leg_yu);
            leg1->SetFillColor(kWhite);
            leg1->SetFillStyle(3003);
            hist_mc_ttjets_sl->SetFillColor(kRed-7);
            hist_mc_ttjets_dl->SetFillColor(kYellow-7);
            hist_mc_ttjets_fh->SetFillColor(kOrange-7);
            hist_mc_wjets->SetFillColor(kGreen-7);
            hist_mc_zjets_mll10_50->SetFillColor(kCyan-7);
            hist_mc_zjets_mll50_inf->SetFillColor(kBlue-7);
            leg1->AddEntry(hist_mc_ttjets_sl,"2017_MC_ttjets_SL","F");
            leg1->AddEntry(hist_mc_ttjets_dl,"2017_MC_ttjets_DL","F");
            leg1->AddEntry(hist_mc_ttjets_fh,"2017_MC_ttjets_FH","F");
            leg1->AddEntry(hist_mc_wjets,"2017_MC_wjets","F");
            leg1->AddEntry(hist_mc_zjets_mll10_50,"2017_MC_zjets_mll10_50","F");
            leg1->AddEntry(hist_mc_zjets_mll50_inf,"2017_MC_zjets_mll50_inf","F");
            hist_mc->Draw("HIST same");
            leg1->AddEntry(hist_data,"2017_Data_BCDEF","L");
            hist_data->SetLineWidth(2);
            hist_data->SetLineColor(kRed);
            hist_data->Draw("same");
            leg1->Draw("same");
            c1->Print(("Data_MC_Distribution_" + f_title1 + type1 + "_" + type2 + "_" + f_title2 + ".pdf").c_str());
            delete c1;
            delete leg1;
        }
    }

    delete file_data;
    delete file_mc_ttjets_sl;
    delete file_mc_ttjets_dl;
    delete file_mc_ttjets_fh;
    delete file_mc_wjets;
    delete file_mc_zjets_mll10_50;
    delete file_mc_zjets_mll50_inf;
	return;
}


