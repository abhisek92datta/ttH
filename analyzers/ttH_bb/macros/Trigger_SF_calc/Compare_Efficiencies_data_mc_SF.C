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


void Compare_Efficiencies_data_mc_SF() {

    TH1::SetDefaultSumw2();
    TFile *file_data;
    TFile *file_mc;
    TFile histofile("SingleEG_JetHT_Trigger_Scale_Factors_ttHbb_Data_MC.root","recreate");
    std::vector<TH1D*> sfs_1;
    std::vector<TH2D*> sfs_2;

    ofstream fout;
    fout.open("Trigger_SF_Data_MC_table.txt");

    // List of Files

    ifstream fin;
    fin.open("files_data_mc_SF.txt");
    char filenames_data[200][200];
    char filenames_mc[200][200];
    int nfiles = 0;

    while(!fin.eof()){
        fin>>filenames_data[nfiles];
        fin>>filenames_mc[nfiles];
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
        std::string fname_mc = filenames_mc[i];
        file_data = new TFile(filenames_data[i]);
        file_mc = new TFile(filenames_mc[i]);
        std::string type0, type1, type2;

		if(fname_data.find("Global_MET_data") != std::string::npos){
			type0 = "DATA_MC";
            type1 = "Global_MET";
		}
		else if(fname_data.find("Global_SM_data") != std::string::npos){
			type0 = "DATA_MC";
			type1 = "Global_SM";
		}
		else if(fname_data.find("JetHTLeg_EG_data") != std::string::npos){
			type0 = "DATA_MC";
			type1 = "JetHTLeg_EG";
		}
		else if(fname_data.find("EleLeg_JET_data") != std::string::npos){
			type0 = "DATA_MC";
			type1 = "EleLeg_JET";
		}
		else if(fname_data.find("EleLeg_HT_data") != std::string::npos){
			type0 = "DATA_MC";
			type1 = "EleLeg_HT";
		}
		else
			type1 = "";

        if (fname_data.find("2017BCDEF") != std::string::npos)
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

        fout<<type0<<"  "<<type1<<"  "<<type2<<"\n\n\n";

        TH1D *N_total_ele_pt_data = (TH1D*)file_data->Get("N_total_ele_pt");
        TH1D *N_total_ele_eta_data = (TH1D*)file_data->Get("N_total_ele_eta");
        TH1D *N_total_ele_sceta_data = (TH1D*)file_data->Get("N_total_ele_sceta");
        TH1D *N_total_jet_pt_data = (TH1D*)file_data->Get("N_total_jet_pt");
        TH1D *N_total_jet_eta_data = (TH1D*)file_data->Get("N_total_jet_eta");
        TH1D *N_total_ht_data = (TH1D*)file_data->Get("N_total_ht");
        TH1D *N_total_njets_data = (TH1D*)file_data->Get("N_total_njets");
        TH1D *N_total_npv_data = (TH1D*)file_data->Get("N_total_npv");
        TH2D *N_total_ele_pt_ele_eta_data = (TH2D*)file_data->Get("N_total_ele_pt_ele_eta");
        TH2D *N_total_ele_pt_ele_sceta_data = (TH2D*)file_data->Get("N_total_ele_pt_ele_sceta");
        TH2D *N_total_ele_pt_jet_pt_data = (TH2D*)file_data->Get("N_total_ele_pt_jet_pt");
        TH2D *N_total_ele_pt_ht_data = (TH2D*)file_data->Get("N_total_ele_pt_ht");

        TH1D *N_total_ele_pt_mc = (TH1D*)file_mc->Get("N_total_ele_pt");
        TH1D *N_total_ele_eta_mc = (TH1D*)file_mc->Get("N_total_ele_eta");
        TH1D *N_total_ele_sceta_mc = (TH1D*)file_mc->Get("N_total_ele_sceta");
        TH1D *N_total_jet_pt_mc = (TH1D*)file_mc->Get("N_total_jet_pt");
        TH1D *N_total_jet_eta_mc = (TH1D*)file_mc->Get("N_total_jet_eta");
        TH1D *N_total_ht_mc = (TH1D*)file_mc->Get("N_total_ht");
        TH1D *N_total_njets_mc = (TH1D*)file_mc->Get("N_total_njets");
        TH1D *N_total_npv_mc = (TH1D*)file_mc->Get("N_total_npv");
        TH2D *N_total_ele_pt_ele_eta_mc = (TH2D*)file_mc->Get("N_total_ele_pt_ele_eta");
        TH2D *N_total_ele_pt_ele_sceta_mc = (TH2D*)file_mc->Get("N_total_ele_pt_ele_sceta");
        TH2D *N_total_ele_pt_jet_pt_mc = (TH2D*)file_mc->Get("N_total_ele_pt_jet_pt");
        TH2D *N_total_ele_pt_ht_mc = (TH2D*)file_mc->Get("N_total_ele_pt_ht");

        for(int j=0; j<nhistos; j++){

            std::string hname = histonames[j];
            if( hname.find("total") != std::string::npos)
                continue;
            TH1D *h_data1;
            TH1D *h_mc1;
            TH2D *h_data2;
            TH2D *h_mc2;
            TEfficiency *effi_data1;
            TEfficiency *effi_mc1;
            TEfficiency *effi_data2;
            TEfficiency *effi_mc2;
            bool pass_teffi = 0;
            bool total_teffi = 0;
            TH1D *sf_1, *sf_num1, *sf_den1;
            TH2D *sf_2, *sf_num2, *sf_den2;

            double ll1, ll2;
            double ul1, ul2;
            double leg_xl, leg_xu, leg_yl, leg_yu;
            std::string c_title1 = "";
            std::string c_title2 = "";
            std::string f_title1 = "";
            std::string f_title2 = "";
            int nxbins_print = 0;
            int nybins_print = 0;
            double *xbins_print;
            double *ybins_print;

            if ((hname.find("pass_ele_pt_ele_eta_") != std::string::npos) || (hname.find("pass_ele_pt_ele_sceta_") != std::string::npos) || (hname.find("pass_ele_pt_jet_pt_") != std::string::npos) ||   (hname.find("pass_ele_pt_ht_") != std::string::npos)){
                h_data2 = (TH2D*)file_data->Get((hname).c_str());
                h_mc2 = (TH2D*)file_mc->Get((hname).c_str());
            }
            else{
                h_data1 = (TH1D*)file_data->Get((hname).c_str());
                h_mc1 = (TH1D*)file_mc->Get((hname).c_str());
            }

            if(hname.find("pass_ele_pt_ele_eta") != std::string::npos){
                effi_data2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
                effi_mc2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
                pass_teffi = effi_data2->SetPassedHistogram(*h_data2, "f");
                total_teffi = effi_data2->SetTotalHistogram(*N_total_ele_pt_ele_eta_data, "f");
                pass_teffi = effi_mc2->SetPassedHistogram(*h_mc2, "f");
                total_teffi = effi_mc2->SetTotalHistogram(*N_total_ele_pt_ele_eta_mc, "f");
                ll1 = *(x_eleptBins);
                ul1 = *(x_eleptBins+n_eleptBins);
                ll2 = *(x_eleetaBins);
                ul2 = *(x_eleetaBins+n_eleetaBins);
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.25;
                c_title2 = "Electron pT and Electron Eta; pT (Electron) [GeV] ;Eta (Electron) ";
                f_title2 = "ele_pt_ele_eta";
                fout<<hname<<" : Electron pT and Electron Eta"<<"\n\n";
                nxbins_print = n_eleptBins;
                nybins_print = n_eleetaBins;
                xbins_print = x_eleptBins;
                ybins_print = x_eleetaBins;
            }
            else if(hname.find("pass_ele_pt_ele_sceta") != std::string::npos){
                effi_data2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
                effi_mc2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_eleetaBins,x_eleetaBins);
                pass_teffi = effi_data2->SetPassedHistogram(*h_data2, "f");
                total_teffi = effi_data2->SetTotalHistogram(*N_total_ele_pt_ele_sceta_data, "f");
                pass_teffi = effi_mc2->SetPassedHistogram(*h_mc2, "f");
                total_teffi = effi_mc2->SetTotalHistogram(*N_total_ele_pt_ele_sceta_mc, "f");
                ll1 = *(x_eleptBins);
                ul1 = *(x_eleptBins+n_eleptBins);
                ll2 = *(x_eleetaBins);
                ul2 = *(x_eleetaBins+n_eleetaBins);
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.25;
                c_title2 = "Electron pT and Electron SuperCluster Eta; pT (Electron) [GeV] ; SuperCluster Eta (Electron) ";
                f_title2 = "ele_pt_ele_sceta";
                fout<<hname<<" : Electron pT and Electron SuperCluster Eta"<<"\n\n";
                nxbins_print = n_eleptBins;
                nybins_print = n_eleetaBins;
                xbins_print = x_eleptBins;
                ybins_print = x_eleetaBins;
            }
            else if(hname.find("pass_ele_pt_jet_pt") != std::string::npos){
                effi_data2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
                effi_mc2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_jetptBins,x_jetptBins);
                pass_teffi = effi_data2->SetPassedHistogram(*h_data2, "f");
                total_teffi = effi_data2->SetTotalHistogram(*N_total_ele_pt_jet_pt_data, "f");
                pass_teffi = effi_mc2->SetPassedHistogram(*h_mc2, "f");
                total_teffi = effi_mc2->SetTotalHistogram(*N_total_ele_pt_jet_pt_mc, "f");
                ll1 = *(x_eleptBins);
                ul1 = *(x_eleptBins+n_eleptBins);
                ll2 = *(x_jetptBins);
                ul2 = *(x_jetptBins+n_jetptBins);
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.25;
                c_title2 = "Electron pT and Leading Jet pT; pT (Electron) [GeV] ; pT (Leading Jet) [GeV] ";
                f_title2 = "ele_pt_jet_pt";
                fout<<hname<<" : Electron pT and Leading Jet pT"<<"\n\n";
                nxbins_print = n_eleptBins;
                nybins_print = n_jetptBins;
                xbins_print = x_eleptBins;
                ybins_print = x_jetptBins;
            }
            else if(hname.find("pass_ele_pt_ht") != std::string::npos){
                effi_data2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_htBins,x_htBins);
                effi_mc2 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins,n_htBins,x_htBins);
                pass_teffi = effi_data2->SetPassedHistogram(*h_data2, "f");
                total_teffi = effi_data2->SetTotalHistogram(*N_total_ele_pt_ht_data, "f");
                pass_teffi = effi_mc2->SetPassedHistogram(*h_mc2, "f");
                total_teffi = effi_mc2->SetTotalHistogram(*N_total_ele_pt_ht_mc, "f");
                ll1 = *(x_eleptBins);
                ul1 = *(x_eleptBins+n_eleptBins);
                ll2 = *(x_htBins);
                ul2 = *(x_htBins+n_htBins);
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.25;
                c_title2 = "Electron pT and HT; pT (Electron) [GeV] ; HT [GeV]";
                f_title2 = "ele_pt_ht";
                fout<<hname<<" : Electron pT and HT"<<"\n\n";
                nxbins_print = n_eleptBins;
                nybins_print = n_htBins;
                xbins_print = x_eleptBins;
                ybins_print = x_htBins;
            }
            else if(hname.find("pass_ele_pt") != std::string::npos){
                effi_data1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins);
                effi_mc1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleptBins,x_eleptBins);
                pass_teffi = effi_data1->SetPassedHistogram(*h_data1, "f");
                total_teffi = effi_data1->SetTotalHistogram(*N_total_ele_pt_data, "f");
                pass_teffi = effi_mc1->SetPassedHistogram(*h_mc1, "f");
                total_teffi = effi_mc1->SetTotalHistogram(*N_total_ele_pt_mc, "f");
                ll1 = 0;
                ul1 = *(x_eleptBins+n_eleptBins);
                ll2 = 0;
                ul2 = 1.2;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.25;
                c_title2 = "Electron pT; pT (Electron) [GeV] ";
                f_title2 = "ele_pt";
                nxbins_print = n_eleptBins;
                xbins_print = x_eleptBins;
            }
            else if(hname.find("pass_ele_eta") != std::string::npos){
                effi_data1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleetaBins,x_eleetaBins);
                effi_mc1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleetaBins,x_eleetaBins);
                pass_teffi = effi_data1->SetPassedHistogram(*h_data1, "f");
                total_teffi = effi_data1->SetTotalHistogram(*N_total_ele_eta_data, "f");
                pass_teffi = effi_mc1->SetPassedHistogram(*h_mc1, "f");
                total_teffi = effi_mc1->SetTotalHistogram(*N_total_ele_eta_mc, "f");
                ll1 = *(x_eleetaBins);
                ul1 = *(x_eleetaBins+n_eleetaBins);
                ll2 = 0;
                ul2 = 1.2;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.25;
                c_title2 = "Electron eta; eta (Electron) ";
                f_title2 = "ele_eta";
                nxbins_print = n_eleetaBins;
                xbins_print = x_eleetaBins;
            }
            else if(hname.find("pass_ele_sceta") != std::string::npos){
                effi_data1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleetaBins,x_eleetaBins);
                effi_mc1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_eleetaBins,x_eleetaBins);
                pass_teffi = effi_data1->SetPassedHistogram(*h_data1, "f");
                total_teffi = effi_data1->SetTotalHistogram(*N_total_ele_sceta_data, "f");
                pass_teffi = effi_mc1->SetPassedHistogram(*h_mc1, "f");
                total_teffi = effi_mc1->SetTotalHistogram(*N_total_ele_sceta_mc, "f");
                ll1 = *(x_eleetaBins);
                ul1 = *(x_eleetaBins+n_eleetaBins);
                ll2 = 0;
                ul2 = 1.2;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.25;
                c_title2 = "Electron SuperCluster Eta; SuperCluster Eta (Electron) ";
                f_title2 = "ele_sceta";
                nxbins_print = n_eleetaBins;
                xbins_print = x_eleetaBins;
            }
            else if(hname.find("pass_jet_pt") != std::string::npos){
                effi_data1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_jetptBins,x_jetptBins);
                effi_mc1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_jetptBins,x_jetptBins);
                pass_teffi = effi_data1->SetPassedHistogram(*h_data1, "f");
                total_teffi = effi_data1->SetTotalHistogram(*N_total_jet_pt_data, "f");
                pass_teffi = effi_mc1->SetPassedHistogram(*h_mc1, "f");
                total_teffi = effi_mc1->SetTotalHistogram(*N_total_jet_pt_mc, "f");
                ll1 = 0;
                ul1 = *(x_jetptBins+n_jetptBins);
                ll2 = 0;
                ul2 = 1.2;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.25;
                c_title2 = "Leading Jet pT; pT (Leading Jet) [GeV] ";
                f_title2 = "jet_pt";
                nxbins_print = n_jetptBins;
                xbins_print = x_jetptBins;
            }
            else if(hname.find("pass_jet_eta") != std::string::npos){
                effi_data1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_jetetaBins,x_jetetaBins);
                effi_mc1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_jetetaBins,x_jetetaBins);
                pass_teffi = effi_data1->SetPassedHistogram(*h_data1, "f");
                total_teffi = effi_data1->SetTotalHistogram(*N_total_jet_eta_data, "f");
                pass_teffi = effi_mc1->SetPassedHistogram(*h_mc1, "f");
                total_teffi = effi_mc1->SetTotalHistogram(*N_total_jet_eta_mc, "f");
                ll1 = *(x_jetetaBins);
                ul1 = *(x_jetetaBins+n_jetetaBins);
                ll2 = 0;
                ul2 = 1.2;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.25;
                c_title2 = "Leading Jet Eta; Eta (Leading Jet) ";
                f_title2 = "jet_eta";
                nxbins_print = n_jetetaBins;
                xbins_print = x_jetetaBins;
            }
            else if(hname.find("pass_ht") != std::string::npos){
                effi_data1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_htBins,x_htBins);
                effi_mc1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_htBins,x_htBins);
                pass_teffi = effi_data1->SetPassedHistogram(*h_data1, "f");
                total_teffi = effi_data1->SetTotalHistogram(*N_total_ht_data, "f");
                pass_teffi = effi_mc1->SetPassedHistogram(*h_mc1, "f");
                total_teffi = effi_mc1->SetTotalHistogram(*N_total_ht_mc, "f");
                ll1 = 0;
                ul1 = *(x_htBins+n_htBins);
                ll2 = 0;
                ul2 = 1.2;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.25;
                c_title2 = "HT; HT [GeV] ";
                f_title2 = "ht";
                nxbins_print = n_htBins;
                xbins_print = x_htBins;
            }
            else if(hname.find("pass_njets") != std::string::npos){
                effi_data1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_njetBins,x_njetBins);
                effi_mc1 = new TEfficiency((hname).c_str(), (hname).c_str(),n_njetBins,x_njetBins);
                pass_teffi = effi_data1->SetPassedHistogram(*h_data1, "f");
                total_teffi = effi_data1->SetTotalHistogram(*N_total_njets_data, "f");
                pass_teffi = effi_mc1->SetPassedHistogram(*h_mc1, "f");
                total_teffi = effi_mc1->SetTotalHistogram(*N_total_njets_mc, "f");
                ll1 = *(x_njetBins);
                ul1 = *(x_njetBins+n_njetBins);
                ll2 = 0;
                ul2 = 1.2;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.25;
                c_title2 = "Jet Multiplicity; Nr. of Jets ";
                f_title2 = "njets";
                nxbins_print = n_njetBins;
                xbins_print = x_njetBins;
            }
            else if(hname.find("pass_npv") != std::string::npos){
                effi_data1 = new TEfficiency((hname).c_str(), (hname).c_str(),75,0,75);
                effi_mc1 = new TEfficiency((hname).c_str(), (hname).c_str(),75,0,75);
                pass_teffi = effi_data1->SetPassedHistogram(*h_data1, "f");
                total_teffi = effi_data1->SetTotalHistogram(*N_total_npv_data, "f");
                pass_teffi = effi_mc1->SetPassedHistogram(*h_mc1, "f");
                total_teffi = effi_mc1->SetTotalHistogram(*N_total_npv_mc, "f");
                ll1 = 0;
                ul1 = 75;
                ll2 = 0;
                ul2 = 1.2;
                leg_xl = 0.50;
                leg_yl = 0.15;
                leg_xu = 0.85;
                leg_yu = 0.25;
                c_title2 = "Nr. of Primary Vertices; NPV ";
                f_title2 = "npv";
                nxbins_print = 75;
            }

            std::string name = ("SF" + hname.substr(5)).c_str();
            int global_bin = 0;

            if ((hname.find("pass_ele_pt_ele_eta_") != std::string::npos) || (hname.find("pass_ele_pt_ele_sceta_") != std::string::npos) || (hname.find("pass_ele_pt_jet_pt_") != std::string::npos) ||   (hname.find("pass_ele_pt_ht_") != std::string::npos)){
                sf_num2 = new TH2D((name + "_" + type2 + "_num").c_str(), (name + "_" + type2 + "_num" + ";X;Y").c_str(),nxbins_print,xbins_print,nybins_print,ybins_print);
                sf_den2 = new TH2D((name + "_" + type2 + "_den").c_str(), (name + "_" + type2 + "_den" + ";X;Y").c_str(),nxbins_print,xbins_print,nybins_print,ybins_print);
                sf_2 = new TH2D((name + "_" + type2).c_str(), (name + "_" + type2 + ";X;Y").c_str(),nxbins_print,xbins_print,nybins_print,ybins_print);

                for (int i=1; i<=nxbins_print; i++){
                    for (int j=1; j<=nybins_print; j++){
                        global_bin = effi_data2->GetGlobalBin(i,j);
                        sf_num2->SetBinContent(i,j,effi_data2->GetEfficiency(global_bin));
                        sf_num2->SetBinError(i,j,(effi_data2->GetEfficiencyErrorUp(global_bin) + effi_data2->GetEfficiencyErrorLow(global_bin))/2.0);
                        global_bin = effi_mc2->GetGlobalBin(i,j);
                        sf_den2->SetBinContent(i,j,effi_mc2->GetEfficiency(global_bin));
                        sf_den2->SetBinError(i,j,(effi_mc2->GetEfficiencyErrorUp(global_bin) + effi_mc2->GetEfficiencyErrorLow(global_bin))/2.0);
                        sf_2->Divide(sf_num2,sf_den2);
                    }
                }

                sfs_2.push_back(sf_2);

                for (int i=nybins_print; i>0; i--){
                    fout<<"ybin : "<<i<<"   ";
                    for (int j=1; j<=nxbins_print; j++)
                        fout<<sf_2->GetBinContent(j,i)<<" + "<<sf_2->GetBinErrorUp(j,i)<<" - "<<sf_2->GetBinErrorLow(j,i)<<"   ";
                    fout<<"\n";
                }
                fout<<"                             ";
                for (int j=1; j<=nxbins_print; j++)
                    fout<<"xbin : "<<j<<"                           ";
                fout<<"\n\n";
            }
            else{
                if(hname.find("pass_npv") != std::string::npos){
                    sf_num1= new TH1D((name + "_" + type2 + "_num").c_str(), (name + "_" + type2 + "_num" + ";x;SF").c_str(),75,0,75);
                    sf_den1= new TH1D((name + "_" + type2 + "_den").c_str(), (name + "_" + type2 + "_den" + ";x;SF").c_str(),75,0,75);
                    sf_1= new TH1D((name + "_" + type2).c_str(), (name + "_" + type2 + ";x;SF").c_str(),75,0,75);
                }
                else{
                    sf_num1= new TH1D((name + "_" + type2 + "_num").c_str(), (name + "_" + type2 + "_num" + ";x;SF").c_str(),nxbins_print,xbins_print);
                    sf_den1= new TH1D((name + "_" + type2 + "_den").c_str(), (name + "_" + type2 + "_den" + ";x;SF").c_str(),nxbins_print,xbins_print);
                    sf_1= new TH1D((name + "_" + type2).c_str(), (name + "_" + type2 + ";x;SF").c_str(),nxbins_print,xbins_print);
                }

                for (int i=1; i<=nxbins_print; i++){
                    global_bin = effi_data1->GetGlobalBin(i);
                    sf_num1->SetBinContent(i,effi_data1->GetEfficiency(global_bin));
                    sf_num1->SetBinError(i,(effi_data1->GetEfficiencyErrorUp(global_bin) + effi_data1->GetEfficiencyErrorLow(global_bin))/2.0);
                    global_bin = effi_mc1->GetGlobalBin(i);
                    sf_den1->SetBinContent(i,effi_mc1->GetEfficiency(global_bin));
                    sf_den1->SetBinError(i,(effi_mc1->GetEfficiencyErrorUp(global_bin) + effi_mc1->GetEfficiencyErrorLow(global_bin))/2.0);
                    sf_1->Divide(sf_num1,sf_den1);
                }
                sfs_1.push_back(sf_1);
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
            gStyle->SetOptStat("ne");
            gStyle->SetPalette(kBird);

            TCanvas *c1 = new TCanvas("c1","test",1100,650);
            c1->DrawFrame(ll1,ll2,ul1,ul2,(type0 + " " + type1 + "_" + type2 + " : " + c_title1 + " Trigger SF vs " + c_title2 + "; Scale Factor").c_str());
            c1->SetGrid();
            //TLegend* leg1;
            //leg1 = new TLegend(leg_xl,leg_yl,leg_xu,leg_yu);
            TLine *line1 = new TLine(ll1,1,ul1,1);
            line1->SetLineStyle(kDashed);
            line1->SetLineWidth(1);
            //leg1->SetFillColor(kWhite);
            //leg1->SetFillStyle(1001);
            if ((hname.find("pass_ele_pt_ele_eta_") != std::string::npos) || (hname.find("pass_ele_pt_ele_sceta_") != std::string::npos) || (hname.find("pass_ele_pt_jet_pt_") != std::string::npos) ||   (hname.find("pass_ele_pt_ht_") != std::string::npos)){
                //leg1->AddEntry(effi_mc2,"2017_MC","L");
                sf_2->SetLineWidth(1);
                sf_2->SetLineColor(kRed);
                gPad->SetLogx(1);
                gStyle->SetPaintTextFormat("1.3f");
                sf_2->Draw("TEXTE COLZ same");
            }
            else{
                //leg1->AddEntry(effi_mc1,"2017_MC","L");
                sf_1->SetLineWidth(1);
                sf_1->SetLineColor(kRed);
                gPad->SetLogx(0);
                sf_1->Draw("L same");
                line1->Draw("same");
            }
            //leg1->Draw("same");
            c1->Print(("SF_" + f_title1 + type1 + "_" + type2 + "_" + f_title2 + ".pdf").c_str());
            delete c1;
            //delete leg1;
            delete line1;
        }
        fout<<"\n\n";
    }
    histofile.cd();
    for (int i=0; i<(int)sfs_1.size(); i++)
        sfs_1[i]->Write();
    for (int i=0; i<(int)sfs_2.size(); i++)
        sfs_2[i]->Write();
    histofile.Close();
    delete file_data;
    delete file_mc;
    fout.close();
	return;
}


