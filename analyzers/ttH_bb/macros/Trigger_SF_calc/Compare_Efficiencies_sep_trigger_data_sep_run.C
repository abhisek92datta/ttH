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


void Compare_Efficiencies_sep_trigger_data_sep_run() {

    TH1::SetDefaultSumw2();
    TFile *fileB;
    TFile *fileC;
    TFile *fileD;
    TFile *fileE;
    TFile *fileF;

    // List of Files

    ifstream fin;
    fin.open("files_sep_trigger_data_sep_run.txt");
    char file_runs[200][200];
    int nfiles = 0;

    while(!fin.eof()){
        fin>>file_runs[nfiles];
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

        char fnameB[200];
        char fnameC[200];
        char fnameD[200];
        char fnameE[200];
        char fnameF[200];
        std::sprintf(fnameB, "%sB.root", file_runs[i]);
        std::sprintf(fnameC, "%sC.root", file_runs[i]);
        std::sprintf(fnameD, "%sD.root", file_runs[i]);
        std::sprintf(fnameE, "%sE.root", file_runs[i]);
        std::sprintf(fnameF, "%sF.root", file_runs[i]);
        fileB = new TFile(fnameB);
        fileC = new TFile(fnameC);
        fileD = new TFile(fnameD);
        fileE = new TFile(fnameE);
        fileF = new TFile(fnameF);
        std::string type0, type1, type2;
        std::string fname = fnameB;

		if(fname.find("Global_MET_data") != std::string::npos){
			type0 = "DATA";
            type1 = "Global_MET_Data";
		}
		else if(fname.find("Global_SM_data") != std::string::npos){
			type0 = "DATA";
			type1 = "Global_SM_Data";
		}
		else if(fname.find("JetHTLeg_EG_data") != std::string::npos){
			type0 = "DATA";
			type1 = "JetHTLeg_EG_Data";
		}
		else if(fname.find("EleLeg_JET_data") != std::string::npos){
			type0 = "DATA";
			type1 = "EleLeg_JET_Data";
		}
		else if(fname.find("EleLeg_HT_data") != std::string::npos){
			type0 = "DATA";
			type1 = "EleLeg_HT_Data";
		}
		else
			type1 = "";

        type2 = "2017BCDEF";

        TH1D *N_total_ele_pt_B = (TH1D*)fileB->Get("N_total_ele_pt");
        TH1D *N_total_ele_eta_B = (TH1D*)fileB->Get("N_total_ele_eta");
        TH1D *N_total_ele_sceta_B = (TH1D*)fileB->Get("N_total_ele_sceta");
        TH1D *N_total_jet_pt_B = (TH1D*)fileB->Get("N_total_jet_pt");
        TH1D *N_total_jet_eta_B = (TH1D*)fileB->Get("N_total_jet_eta");
        TH1D *N_total_ht_B = (TH1D*)fileB->Get("N_total_ht");
        TH1D *N_total_njets_B = (TH1D*)fileB->Get("N_total_njets");
        TH1D *N_total_npv_B = (TH1D*)fileB->Get("N_total_npv");
        TH2D *N_total_ele_pt_ele_eta_B = (TH2D*)fileB->Get("N_total_ele_pt_ele_eta");
        TH2D *N_total_ele_pt_ele_sceta_B = (TH2D*)fileB->Get("N_total_ele_pt_ele_sceta");
        TH2D *N_total_ele_pt_jet_pt_B = (TH2D*)fileB->Get("N_total_ele_pt_jet_pt");
        TH2D *N_total_ele_pt_ht_B = (TH2D*)fileB->Get("N_total_ele_pt_ht");

        TH1D *N_total_ele_pt_C = (TH1D*)fileC->Get("N_total_ele_pt");
        TH1D *N_total_ele_eta_C = (TH1D*)fileC->Get("N_total_ele_eta");
        TH1D *N_total_ele_sceta_C = (TH1D*)fileC->Get("N_total_ele_sceta");
        TH1D *N_total_jet_pt_C = (TH1D*)fileC->Get("N_total_jet_pt");
        TH1D *N_total_jet_eta_C = (TH1D*)fileC->Get("N_total_jet_eta");
        TH1D *N_total_ht_C = (TH1D*)fileC->Get("N_total_ht");
        TH1D *N_total_njets_C = (TH1D*)fileC->Get("N_total_njets");
        TH1D *N_total_npv_C = (TH1D*)fileC->Get("N_total_npv");
        TH2D *N_total_ele_pt_ele_eta_C = (TH2D*)fileC->Get("N_total_ele_pt_ele_eta");
        TH2D *N_total_ele_pt_ele_sceta_C = (TH2D*)fileC->Get("N_total_ele_pt_ele_sceta");
        TH2D *N_total_ele_pt_jet_pt_C = (TH2D*)fileC->Get("N_total_ele_pt_jet_pt");
        TH2D *N_total_ele_pt_ht_C = (TH2D*)fileC->Get("N_total_ele_pt_ht");

        TH1D *N_total_ele_pt_D = (TH1D*)fileD->Get("N_total_ele_pt");
        TH1D *N_total_ele_eta_D = (TH1D*)fileD->Get("N_total_ele_eta");
        TH1D *N_total_ele_sceta_D = (TH1D*)fileD->Get("N_total_ele_sceta");
        TH1D *N_total_jet_pt_D = (TH1D*)fileD->Get("N_total_jet_pt");
        TH1D *N_total_jet_eta_D = (TH1D*)fileD->Get("N_total_jet_eta");
        TH1D *N_total_ht_D = (TH1D*)fileD->Get("N_total_ht");
        TH1D *N_total_njets_D = (TH1D*)fileD->Get("N_total_njets");
        TH1D *N_total_npv_D = (TH1D*)fileD->Get("N_total_npv");
        TH2D *N_total_ele_pt_ele_eta_D = (TH2D*)fileD->Get("N_total_ele_pt_ele_eta");
        TH2D *N_total_ele_pt_ele_sceta_D = (TH2D*)fileD->Get("N_total_ele_pt_ele_sceta");
        TH2D *N_total_ele_pt_jet_pt_D = (TH2D*)fileD->Get("N_total_ele_pt_jet_pt");
        TH2D *N_total_ele_pt_ht_D = (TH2D*)fileD->Get("N_total_ele_pt_ht");

        TH1D *N_total_ele_pt_E = (TH1D*)fileE->Get("N_total_ele_pt");
        TH1D *N_total_ele_eta_E = (TH1D*)fileE->Get("N_total_ele_eta");
        TH1D *N_total_ele_sceta_E = (TH1D*)fileE->Get("N_total_ele_sceta");
        TH1D *N_total_jet_pt_E = (TH1D*)fileE->Get("N_total_jet_pt");
        TH1D *N_total_jet_eta_E = (TH1D*)fileE->Get("N_total_jet_eta");
        TH1D *N_total_ht_E = (TH1D*)fileE->Get("N_total_ht");
        TH1D *N_total_njets_E = (TH1D*)fileE->Get("N_total_njets");
        TH1D *N_total_npv_E = (TH1D*)fileE->Get("N_total_npv");
        TH2D *N_total_ele_pt_ele_eta_E = (TH2D*)fileE->Get("N_total_ele_pt_ele_eta");
        TH2D *N_total_ele_pt_ele_sceta_E = (TH2D*)fileE->Get("N_total_ele_pt_ele_sceta");
        TH2D *N_total_ele_pt_jet_pt_E = (TH2D*)fileE->Get("N_total_ele_pt_jet_pt");
        TH2D *N_total_ele_pt_ht_E = (TH2D*)fileE->Get("N_total_ele_pt_ht");

        TH1D *N_total_ele_pt_F = (TH1D*)fileF->Get("N_total_ele_pt");
        TH1D *N_total_ele_eta_F = (TH1D*)fileF->Get("N_total_ele_eta");
        TH1D *N_total_ele_sceta_F = (TH1D*)fileF->Get("N_total_ele_sceta");
        TH1D *N_total_jet_pt_F = (TH1D*)fileF->Get("N_total_jet_pt");
        TH1D *N_total_jet_eta_F = (TH1D*)fileF->Get("N_total_jet_eta");
        TH1D *N_total_ht_F = (TH1D*)fileF->Get("N_total_ht");
        TH1D *N_total_njets_F = (TH1D*)fileF->Get("N_total_njets");
        TH1D *N_total_npv_F = (TH1D*)fileF->Get("N_total_npv");
        TH2D *N_total_ele_pt_ele_eta_F = (TH2D*)fileF->Get("N_total_ele_pt_ele_eta");
        TH2D *N_total_ele_pt_ele_sceta_F = (TH2D*)fileF->Get("N_total_ele_pt_ele_sceta");
        TH2D *N_total_ele_pt_jet_pt_F = (TH2D*)fileF->Get("N_total_ele_pt_jet_pt");
        TH2D *N_total_ele_pt_ht_F = (TH2D*)fileF->Get("N_total_ele_pt_ht");

        for(int j=0; j<nhistos; j++){

            std::string hname = histonames[j];
            if( hname.find("total") != std::string::npos)
                continue;
            TH1D *h_B1;
            TH1D *h_C1;
            TH1D *h_D1;
            TH1D *h_E1;
            TH1D *h_F1;
            TH2D *h_B2;
            TH2D *h_C2;
            TH2D *h_D2;
            TH2D *h_E2;
            TH2D *h_F2;
            TEfficiency  *effi_B1;
            TEfficiency  *effi_C1;
            TEfficiency  *effi_D1;
            TEfficiency  *effi_E1;
            TEfficiency  *effi_F1;
            TEfficiency  *effi_B2;
            TEfficiency  *effi_C2;
            TEfficiency  *effi_D2;
            TEfficiency  *effi_E2;
            TEfficiency  *effi_F2;
            bool pass_teffi = 0;
            bool total_teffi = 0;

            double ll1, ll2;
            double ul1, ul2;
            double leg_xl, leg_xu, leg_yl, leg_yu;
            std::string c_title1 = "";
            std::string c_title2 = "";
            std::string f_title1 = "";
            std::string f_title2 = "";

            if ((hname.find("pass_ele_pt_ele_eta_") != std::string::npos) || (hname.find("pass_ele_pt_ele_sceta_") != std::string::npos) || (hname.find("pass_ele_pt_jet_pt_") != std::string::npos) ||   (hname.find("pass_ele_pt_ht_") != std::string::npos)){
                h_B2 = (TH2D*)fileB->Get((hname).c_str());
                h_C2 = (TH2D*)fileC->Get((hname).c_str());
                h_D2 = (TH2D*)fileD->Get((hname).c_str());
                h_E2 = (TH2D*)fileE->Get((hname).c_str());
                h_F2 = (TH2D*)fileF->Get((hname).c_str());
            }
            else{
                h_B1 = (TH1D*)fileB->Get((hname).c_str());
                h_C1 = (TH1D*)fileC->Get((hname).c_str());
                h_D1 = (TH1D*)fileD->Get((hname).c_str());
                h_E1 = (TH1D*)fileE->Get((hname).c_str());
                h_F1 = (TH1D*)fileF->Get((hname).c_str());
            }

            if(hname.find("pass_ele_pt_ele_eta") != std::string::npos){
                effi_B2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
                effi_C2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
                effi_D2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
                effi_E2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
                effi_F2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
                pass_teffi = effi_B2->SetPassedHistogram(*h_B2, "f");
                total_teffi = effi_B2->SetTotalHistogram(*N_total_ele_pt_ele_eta_B, "f");
                pass_teffi = effi_C2->SetPassedHistogram(*h_C2, "f");
                total_teffi = effi_C2->SetTotalHistogram(*N_total_ele_pt_ele_eta_C, "f");
                pass_teffi = effi_D2->SetPassedHistogram(*h_D2, "f");
                total_teffi = effi_D2->SetTotalHistogram(*N_total_ele_pt_ele_eta_D, "f");
                pass_teffi = effi_E2->SetPassedHistogram(*h_E2, "f");
                total_teffi = effi_E2->SetTotalHistogram(*N_total_ele_pt_ele_eta_E, "f");
                pass_teffi = effi_F2->SetPassedHistogram(*h_F2, "f");
                total_teffi = effi_F2->SetTotalHistogram(*N_total_ele_pt_ele_eta_F, "f");
                ll1 = 0;
                ul1 = *(x_eleptBins+n_eleptBins);
                ll2 = *(x_eleetaBins);
                ul2 = *(x_eleetaBins+n_eleetaBins);
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.40;
                c_title2 = "Electron pT and Electron Eta; pT (Electron) [GeV] ;Eta (Electron) ";
                f_title2 = "ele_pt_ele_eta";
            }
            else if(hname.find("pass_ele_pt_ele_sceta") != std::string::npos){
                effi_B2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
                effi_C2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
                effi_D2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
                effi_E2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
                effi_F2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
                pass_teffi = effi_B2->SetPassedHistogram(*h_B2, "f");
                total_teffi = effi_B2->SetTotalHistogram(*N_total_ele_pt_ele_sceta_B, "f");
                pass_teffi = effi_C2->SetPassedHistogram(*h_C2, "f");
                total_teffi = effi_C2->SetTotalHistogram(*N_total_ele_pt_ele_sceta_C, "f");
                pass_teffi = effi_D2->SetPassedHistogram(*h_D2, "f");
                total_teffi = effi_D2->SetTotalHistogram(*N_total_ele_pt_ele_sceta_D, "f");
                pass_teffi = effi_E2->SetPassedHistogram(*h_E2, "f");
                total_teffi = effi_E2->SetTotalHistogram(*N_total_ele_pt_ele_sceta_E, "f");
                pass_teffi = effi_F2->SetPassedHistogram(*h_F2, "f");
                total_teffi = effi_F2->SetTotalHistogram(*N_total_ele_pt_ele_sceta_F, "f");
                ll1 = 0;
                ul1 = *(x_eleptBins+n_eleptBins);
                ll2 = *(x_eleetaBins);
                ul2 = *(x_eleetaBins+n_eleetaBins);
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.40;
                c_title2 = "Electron pT and Electron SuperCluster Eta; pT (Electron) [GeV] ;SuperCluster Eta (Electron) ";
                f_title2 = "ele_pt_ele_sceta";
            }
            else if(hname.find("pass_ele_pt_jet_pt") != std::string::npos){
                effi_B2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
                effi_C2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
                effi_D2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
                effi_E2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
                effi_F2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
                pass_teffi = effi_B2->SetPassedHistogram(*h_B2, "f");
                total_teffi = effi_B2->SetTotalHistogram(*N_total_ele_pt_jet_pt_B, "f");
                pass_teffi = effi_C2->SetPassedHistogram(*h_C2, "f");
                total_teffi = effi_C2->SetTotalHistogram(*N_total_ele_pt_jet_pt_C, "f");
                pass_teffi = effi_D2->SetPassedHistogram(*h_D2, "f");
                total_teffi = effi_D2->SetTotalHistogram(*N_total_ele_pt_jet_pt_D, "f");
                pass_teffi = effi_E2->SetPassedHistogram(*h_E2, "f");
                total_teffi = effi_E2->SetTotalHistogram(*N_total_ele_pt_jet_pt_E, "f");
                pass_teffi = effi_F2->SetPassedHistogram(*h_F2, "f");
                total_teffi = effi_F2->SetTotalHistogram(*N_total_ele_pt_jet_pt_F, "f");
                ll1 = 0;
                ul1 = *(x_eleptBins+n_eleptBins);
                ll2 = 0;
                ul2 = *(x_jetptBins+n_jetptBins);
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.40;
                c_title2 = "Electron pT and Leading Jet pT; pT (Electron) [GeV] ; pT (Leading Jet) [GeV] ";
                f_title2 = "ele_pt_jet_pt";
            }
            else if(hname.find("pass_ele_pt_ht") != std::string::npos){
                effi_B2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_htBins,x_htBins);
                effi_C2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_htBins,x_htBins);
                effi_D2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_htBins,x_htBins);
                effi_E2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_htBins,x_htBins);
                effi_F2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_htBins,x_htBins);
                pass_teffi = effi_B2->SetPassedHistogram(*h_B2, "f");
                total_teffi = effi_B2->SetTotalHistogram(*N_total_ele_pt_ht_B, "f");
                pass_teffi = effi_C2->SetPassedHistogram(*h_C2, "f");
                total_teffi = effi_C2->SetTotalHistogram(*N_total_ele_pt_ht_C, "f");
                pass_teffi = effi_D2->SetPassedHistogram(*h_D2, "f");
                total_teffi = effi_D2->SetTotalHistogram(*N_total_ele_pt_ht_D, "f");
                pass_teffi = effi_E2->SetPassedHistogram(*h_E2, "f");
                total_teffi = effi_E2->SetTotalHistogram(*N_total_ele_pt_ht_E, "f");
                pass_teffi = effi_F2->SetPassedHistogram(*h_F2, "f");
                total_teffi = effi_F2->SetTotalHistogram(*N_total_ele_pt_ht_F, "f");
                ll1 = 0;
                ul1 = *(x_eleptBins+n_eleptBins);
                ll2 = 0;
                ul2 = *(x_htBins+n_htBins);
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.40;
                c_title2 = "Electron pT and HT; pT (Electron) [GeV] ; HT [GeV]";
                f_title2 = "ele_pt_ht";
            }
            else if(hname.find("pass_ele_pt") != std::string::npos){
                effi_B1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins);
                effi_C1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins);
                effi_D1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins);
                effi_E1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins);
                effi_F1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins);
                pass_teffi = effi_B1->SetPassedHistogram(*h_B1, "f");
                total_teffi = effi_B1->SetTotalHistogram(*N_total_ele_pt_B, "f");
                pass_teffi = effi_C1->SetPassedHistogram(*h_C1, "f");
                total_teffi = effi_C1->SetTotalHistogram(*N_total_ele_pt_C, "f");
                pass_teffi = effi_D1->SetPassedHistogram(*h_D1, "f");
                total_teffi = effi_D1->SetTotalHistogram(*N_total_ele_pt_D, "f");
                pass_teffi = effi_E1->SetPassedHistogram(*h_E1, "f");
                total_teffi = effi_E1->SetTotalHistogram(*N_total_ele_pt_E, "f");
                pass_teffi = effi_F1->SetPassedHistogram(*h_F1, "f");
                total_teffi = effi_F1->SetTotalHistogram(*N_total_ele_pt_F, "f");
                ll1 = 0;
                ul1 = *(x_eleptBins+n_eleptBins);
                ll2 = 0;
                ul2 = 1.03;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.40;
                c_title2 = "Electron pT; pT (Electron) [GeV] ";
                f_title2 = "ele_pt";
            }
            else if(hname.find("pass_ele_eta") != std::string::npos){
                effi_B1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleetaBins,x_eleetaBins);
                effi_C1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleetaBins,x_eleetaBins);
                effi_D1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleetaBins,x_eleetaBins);
                effi_E1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleetaBins,x_eleetaBins);
                effi_F1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleetaBins,x_eleetaBins);
                pass_teffi = effi_B1->SetPassedHistogram(*h_B1, "f");
                total_teffi = effi_B1->SetTotalHistogram(*N_total_ele_eta_B, "f");
                pass_teffi = effi_C1->SetPassedHistogram(*h_C1, "f");
                total_teffi = effi_C1->SetTotalHistogram(*N_total_ele_eta_C, "f");
                pass_teffi = effi_D1->SetPassedHistogram(*h_D1, "f");
                total_teffi = effi_D1->SetTotalHistogram(*N_total_ele_eta_D, "f");
                pass_teffi = effi_E1->SetPassedHistogram(*h_E1, "f");
                total_teffi = effi_E1->SetTotalHistogram(*N_total_ele_eta_E, "f");
                pass_teffi = effi_F1->SetPassedHistogram(*h_F1, "f");
                total_teffi = effi_F1->SetTotalHistogram(*N_total_ele_eta_F, "f");
                ll1 = *(x_eleetaBins);
                ul1 = *(x_eleetaBins+n_eleetaBins);
                ll2 = 0;
                ul2 = 1.03;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.40;
                c_title2 = "Electron eta; eta (Electron) ";
                f_title2 = "ele_eta";
            }
            else if(hname.find("pass_ele_sceta") != std::string::npos){
                effi_B1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleetaBins,x_eleetaBins);
                effi_C1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleetaBins,x_eleetaBins);
                effi_D1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleetaBins,x_eleetaBins);
                effi_E1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleetaBins,x_eleetaBins);
                effi_F1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleetaBins,x_eleetaBins);
                pass_teffi = effi_B1->SetPassedHistogram(*h_B1, "f");
                total_teffi = effi_B1->SetTotalHistogram(*N_total_ele_sceta_B, "f");
                pass_teffi = effi_C1->SetPassedHistogram(*h_C1, "f");
                total_teffi = effi_C1->SetTotalHistogram(*N_total_ele_sceta_C, "f");
                pass_teffi = effi_D1->SetPassedHistogram(*h_D1, "f");
                total_teffi = effi_D1->SetTotalHistogram(*N_total_ele_sceta_D, "f");
                pass_teffi = effi_E1->SetPassedHistogram(*h_E1, "f");
                total_teffi = effi_E1->SetTotalHistogram(*N_total_ele_sceta_E, "f");
                pass_teffi = effi_F1->SetPassedHistogram(*h_F1, "f");
                total_teffi = effi_F1->SetTotalHistogram(*N_total_ele_sceta_F, "f");
                ll1 = *(x_eleetaBins);
                ul1 = *(x_eleetaBins+n_eleetaBins);
                ll2 = 0;
                ul2 = 1.03;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.40;
                c_title2 = "Electron SuperCluster Eta; SuperCluster Eta (Electron) ";
                f_title2 = "ele_sceta";
            }
            else if(hname.find("pass_jet_pt") != std::string::npos){
                effi_B1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_jetptBins,x_jetptBins);
                effi_C1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_jetptBins,x_jetptBins);
                effi_D1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_jetptBins,x_jetptBins);
                effi_E1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_jetptBins,x_jetptBins);
                effi_F1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_jetptBins,x_jetptBins);
                pass_teffi = effi_B1->SetPassedHistogram(*h_B1, "f");
                total_teffi = effi_B1->SetTotalHistogram(*N_total_jet_pt_B, "f");
                pass_teffi = effi_C1->SetPassedHistogram(*h_C1, "f");
                total_teffi = effi_C1->SetTotalHistogram(*N_total_jet_pt_C, "f");
                pass_teffi = effi_D1->SetPassedHistogram(*h_D1, "f");
                total_teffi = effi_D1->SetTotalHistogram(*N_total_jet_pt_D, "f");
                pass_teffi = effi_E1->SetPassedHistogram(*h_E1, "f");
                total_teffi = effi_E1->SetTotalHistogram(*N_total_jet_pt_E, "f");
                pass_teffi = effi_F1->SetPassedHistogram(*h_F1, "f");
                total_teffi = effi_F1->SetTotalHistogram(*N_total_jet_pt_F, "f");
                ll1 = 0;
                ul1 = *(x_jetptBins+n_jetptBins);
                ll2 = 0;
                ul2 = 1.03;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.40;
                c_title2 = "Leading Jet pT; pT (Leading Jet) [GeV] ";
                f_title2 = "jet_pt";
            }
            else if(hname.find("pass_jet_eta") != std::string::npos){
                effi_B1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_jetetaBins,x_jetetaBins);
                effi_C1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_jetetaBins,x_jetetaBins);
                effi_D1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_jetetaBins,x_jetetaBins);
                effi_E1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_jetetaBins,x_jetetaBins);
                effi_F1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_jetetaBins,x_jetetaBins);
                pass_teffi = effi_B1->SetPassedHistogram(*h_B1, "f");
                total_teffi = effi_B1->SetTotalHistogram(*N_total_jet_eta_B, "f");
                pass_teffi = effi_C1->SetPassedHistogram(*h_C1, "f");
                total_teffi = effi_C1->SetTotalHistogram(*N_total_jet_eta_C, "f");
                pass_teffi = effi_D1->SetPassedHistogram(*h_D1, "f");
                total_teffi = effi_D1->SetTotalHistogram(*N_total_jet_eta_D, "f");
                pass_teffi = effi_E1->SetPassedHistogram(*h_E1, "f");
                total_teffi = effi_E1->SetTotalHistogram(*N_total_jet_eta_E, "f");
                pass_teffi = effi_F1->SetPassedHistogram(*h_F1, "f");
                total_teffi = effi_F1->SetTotalHistogram(*N_total_jet_eta_F, "f");
                ll1 = *(x_jetetaBins);
                ul1 = *(x_jetetaBins+n_jetetaBins);
                ll2 = 0;
                ul2 = 1.03;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.40;
                c_title2 = "Leading Jet Eta; Eta (Leading Jet) ";
                f_title2 = "jet_eta";
            }
            else if(hname.find("pass_ht") != std::string::npos){
                effi_B1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_htBins,x_htBins);
                effi_C1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_htBins,x_htBins);
                effi_D1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_htBins,x_htBins);
                effi_E1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_htBins,x_htBins);
                effi_F1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_htBins,x_htBins);
                pass_teffi = effi_B1->SetPassedHistogram(*h_B1, "f");
                total_teffi = effi_B1->SetTotalHistogram(*N_total_ht_B, "f");
                pass_teffi = effi_C1->SetPassedHistogram(*h_C1, "f");
                total_teffi = effi_C1->SetTotalHistogram(*N_total_ht_C, "f");
                pass_teffi = effi_D1->SetPassedHistogram(*h_D1, "f");
                total_teffi = effi_D1->SetTotalHistogram(*N_total_ht_D, "f");
                pass_teffi = effi_E1->SetPassedHistogram(*h_E1, "f");
                total_teffi = effi_E1->SetTotalHistogram(*N_total_ht_E, "f");
                pass_teffi = effi_F1->SetPassedHistogram(*h_F1, "f");
                total_teffi = effi_F1->SetTotalHistogram(*N_total_ht_F, "f");
                ll1 = 0;
                ul1 = *(x_htBins+n_htBins);
                ll2 = 0;
                ul2 = 1.03;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.40;
                c_title2 = "HT; HT [GeV] ";
                f_title2 = "ht";
            }
            else if(hname.find("pass_njets") != std::string::npos){
                effi_B1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_njetBins,x_njetBins);
                effi_C1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_njetBins,x_njetBins);
                effi_D1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_njetBins,x_njetBins);
                effi_E1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_njetBins,x_njetBins);
                effi_F1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_njetBins,x_njetBins);
                pass_teffi = effi_B1->SetPassedHistogram(*h_B1, "f");
                total_teffi = effi_B1->SetTotalHistogram(*N_total_njets_B, "f");
                pass_teffi = effi_C1->SetPassedHistogram(*h_C1, "f");
                total_teffi = effi_C1->SetTotalHistogram(*N_total_njets_C, "f");
                pass_teffi = effi_D1->SetPassedHistogram(*h_D1, "f");
                total_teffi = effi_D1->SetTotalHistogram(*N_total_njets_D, "f");
                pass_teffi = effi_E1->SetPassedHistogram(*h_E1, "f");
                total_teffi = effi_E1->SetTotalHistogram(*N_total_njets_E, "f");
                pass_teffi = effi_F1->SetPassedHistogram(*h_F1, "f");
                total_teffi = effi_F1->SetTotalHistogram(*N_total_njets_F, "f");
                ll1 = *(x_njetBins);
                ul1 = *(x_njetBins+n_njetBins);
                ll2 = 0;
                ul2 = 1.03;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.40;
                c_title2 = "Jet Multiplicity; Nr. of Jets ";
                f_title2 = "njets";
            }
            else if(hname.find("pass_npv") != std::string::npos){
                effi_B1 = new TEfficiency((hname).c_str(), (hname).c_str(),75,0,75);
                effi_C1 = new TEfficiency((hname).c_str(), (hname).c_str(),75,0,75);
                effi_D1 = new TEfficiency((hname).c_str(), (hname).c_str(),75,0,75);
                effi_E1 = new TEfficiency((hname).c_str(), (hname).c_str(),75,0,75);
                effi_F1 = new TEfficiency((hname).c_str(), (hname).c_str(),75,0,75);
                pass_teffi = effi_B1->SetPassedHistogram(*h_B1, "f");
                total_teffi = effi_B1->SetTotalHistogram(*N_total_npv_B, "f");
                pass_teffi = effi_C1->SetPassedHistogram(*h_C1, "f");
                total_teffi = effi_C1->SetTotalHistogram(*N_total_npv_C, "f");
                pass_teffi = effi_D1->SetPassedHistogram(*h_D1, "f");
                total_teffi = effi_D1->SetTotalHistogram(*N_total_npv_D, "f");
                pass_teffi = effi_E1->SetPassedHistogram(*h_E1, "f");
                total_teffi = effi_E1->SetTotalHistogram(*N_total_npv_E, "f");
                pass_teffi = effi_F1->SetPassedHistogram(*h_F1, "f");
                total_teffi = effi_F1->SetTotalHistogram(*N_total_npv_F, "f");
                ll1 = 0;
                ul1 = 75;
                ll2 = 0;
                ul2 = 1.03;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.40;
                c_title2 = "Nr. of Primary Vertices; NPV ";
                f_title2 = "npv";
            }

            if(hname.find("ele30_jet35_OR_ele28_ht150_OR_ele35") != std::string::npos){
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

            TCanvas *c1 = new TCanvas("c1","test",1100,650);
            c1->DrawFrame(ll1,ll2,ul1,ul2,(type0 + " " + type1 + "_" + type2 + " : " + c_title1 + " Efficiency vs " + c_title2 + "; Efficiency").c_str());
            c1->SetGrid();
            TLegend* leg1;
            leg1 = new TLegend(leg_xl,leg_yl,leg_xu,leg_yu);
            TLine *line1 = new TLine(ll1,1,ul1,1);
            line1->SetLineStyle(kDashed);
            line1->SetLineWidth(1);
            leg1->SetFillColor(kWhite);
            leg1->SetFillStyle(1001);
            if ((hname.find("pass_ele_pt_ele_eta_") != std::string::npos) || (hname.find("pass_ele_pt_ele_sceta_") != std::string::npos) || (hname.find("pass_ele_pt_jet_pt_") != std::string::npos) ||   (hname.find("pass_ele_pt_ht_") != std::string::npos)){
                leg1->AddEntry(effi_B2,"2017_Data_B","L");
                effi_B2->SetLineWidth(1);
                effi_B2->SetLineColor(kRed);
                effi_B2->Draw("L same");
                leg1->AddEntry(effi_C2,"2017_Data_C","L");
                effi_C2->SetLineWidth(1);
                effi_C2->SetLineColor(kBlue);
                effi_C2->Draw("L same");
                leg1->AddEntry(effi_D2,"2017_Data_D","L");
                effi_D2->SetLineWidth(1);
                effi_D2->SetLineColor(kGreen);
                effi_D2->Draw("L same");
                leg1->AddEntry(effi_E2,"2017_Data_E","L");
                effi_E2->SetLineWidth(1);
                effi_E2->SetLineColor(kViolet);
                effi_E2->Draw("L same");
                leg1->AddEntry(effi_F2,"2017_Data_F","L");
                effi_F2->SetLineWidth(1);
                effi_F2->SetLineColor(kCyan);
                effi_F2->Draw("L same");
            }
            else{
                leg1->AddEntry(effi_B1,"2017_Data_B","L");
                effi_B1->SetLineWidth(1);
                effi_B1->SetLineColor(kRed);
                effi_B1->Draw("L same");
                leg1->AddEntry(effi_C1,"2017_Data_C","L");
                effi_C1->SetLineWidth(1);
                effi_C1->SetLineColor(kBlue);
                effi_C1->Draw("L same");
                leg1->AddEntry(effi_D1,"2017_Data_D","L");
                effi_D1->SetLineWidth(1);
                effi_D1->SetLineColor(kGreen);
                effi_D1->Draw("L same");
                leg1->AddEntry(effi_E1,"2017_Data_E","L");
                effi_E1->SetLineWidth(1);
                effi_E1->SetLineColor(kViolet);
                effi_E1->Draw("L same");
                leg1->AddEntry(effi_F1,"2017_Data_F","L");
                effi_F1->SetLineWidth(1);
                effi_F1->SetLineColor(kCyan);
                effi_F1->Draw("L same");
            }
            leg1->Draw("same");
            line1->Draw("same");
            c1->Print(("Efficiency_" + f_title1 + type1 + "_" + type2 + "_" + f_title2 + ".pdf").c_str());
            delete c1;
            delete leg1;
            delete line1;
        }
    }

    delete fileB;
    delete fileC;
    delete fileD;
    delete fileE;
    delete fileF;
	return;
}


