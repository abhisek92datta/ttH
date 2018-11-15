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


void Final_Scale_Factor_Unc_Calc() {

    TH1::SetDefaultSumw2();
    TFile *file_nominal;
    TFile *file_htsystup;
    TFile *file_htsystdown;
    TFile *file_sl_dl;
    TFile histofile_total("SingleEG_JetHT_Trigger_Scale_Factors_ttHbb.root","recreate");
    TFile histofile_eghtor("SingleEG_HTOR_Trigger_Scale_Factors_ttHbb.root","recreate");
    std::vector<TH1D*> sfs_total_1;
    std::vector<TH2D*> sfs_total_2;
    std::vector<TH1D*> sfs_eghtor_1;
    std::vector<TH2D*> sfs_eghtor_2;

    // Input Files
    std::string filename_nominal = "Scale_Factors_nominal.root";
    std::string filename_htsystup = "Scale_Factors_htsystup.root";
    std::string filename_htsystdown = "Scale_Factors_htsystdown.root";
    std::string filename_sl_dl = "Scale_Factors_nominal_sl_dl.root";

    // List of Triggers
    ifstream fin1;
    fin1.open("triggers_final.txt");
    char triggernames[600][200];
    int ntriggers = 0;
    while(!fin1.eof()){
        fin1>>triggernames[ntriggers];
        ntriggers++;
    }
    fin1.close();

    // List of Histos
    ifstream fin2;
    fin2.open("histos_final.txt");
    char histonames[600][200];
    int nhistos = 0;
    while(!fin2.eof()){
        fin2>>histonames[nhistos];
        nhistos++;
    }
    fin2.close();

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

    file_nominal = new TFile((filename_nominal).c_str());
    file_htsystup = new TFile((filename_htsystup).c_str());
    file_htsystdown = new TFile((filename_htsystdown).c_str());
    file_sl_dl = new TFile((filename_sl_dl).c_str());

    // Looping over triggers
    for(int i=0; i<ntriggers; i++){
        std::string tname = triggernames[i];

        // Looping over histograms
        for(int j=0; j<nhistos; j++){
            std::string hname = histonames[j];
            std::string full_hname_BCDEF = (hname + "_" + tname + "_2017BCDEF").c_str();
            std::string full_hname_B = (hname + "_" + tname + "_2017B").c_str();
            std::string full_hname_C = (hname + "_" + tname + "_2017C").c_str();
            std::string full_hname_D = (hname + "_" + tname + "_2017D").c_str();
            std::string full_hname_E = (hname + "_" + tname + "_2017E").c_str();
            std::string full_hname_F = (hname + "_" + tname + "_2017F").c_str();
            TH1D* SFs_final_1d;
            TH2D* SFs_final_2d;
            TH1D* SFs_htup_1d;
            TH2D* SFs_htup_2d;
            TH1D* SFs_htdown_1d;
            TH2D* SFs_htdown_2d;
            TH1D* SFs_sl_dl_1d;
            TH2D* SFs_sl_dl_2d;
            TH1D* SFs_B_1d;
            TH1D* SFs_C_1d;
            TH1D* SFs_D_1d;
            TH1D* SFs_E_1d;
            TH1D* SFs_F_1d;
            TH2D* SFs_B_2d;
            TH2D* SFs_C_2d;
            TH2D* SFs_D_2d;
            TH2D* SFs_E_2d;
            TH2D* SFs_F_2d;

            if ((hname.find("SFs_ele_pt_ele_eta") != std::string::npos) || (hname.find("SFs_ele_pt_ele_sceta") != std::string::npos) || (hname.find("SFs_ele_pt_jet_pt") != std::string::npos) ||   (hname.find("SFs_ele_pt_ht") != std::string::npos)){
                SFs_final_2d = (TH2D*)file_nominal->Get((full_hname_BCDEF).c_str());
                SFs_htup_2d = (TH2D*)file_htsystup->Get((full_hname_BCDEF).c_str());
                SFs_htdown_2d = (TH2D*)file_htsystdown->Get((full_hname_BCDEF).c_str());
                SFs_sl_dl_2d = (TH2D*)file_sl_dl->Get((full_hname_BCDEF).c_str());
                SFs_B_2d = (TH2D*)file_nominal->Get((full_hname_B).c_str());
                SFs_C_2d = (TH2D*)file_nominal->Get((full_hname_C).c_str());
                SFs_D_2d = (TH2D*)file_nominal->Get((full_hname_D).c_str());
                SFs_E_2d = (TH2D*)file_nominal->Get((full_hname_E).c_str());
                SFs_F_2d = (TH2D*)file_nominal->Get((full_hname_F).c_str());
            }
            else{
                SFs_final_1d = (TH1D*)file_nominal->Get((full_hname_BCDEF).c_str());
                SFs_htup_1d = (TH1D*)file_htsystup->Get((full_hname_BCDEF).c_str());
                SFs_htdown_1d = (TH1D*)file_htsystdown->Get((full_hname_BCDEF).c_str());
                SFs_sl_dl_1d = (TH1D*)file_sl_dl->Get((full_hname_BCDEF).c_str());
                SFs_B_1d = (TH1D*)file_nominal->Get((full_hname_B).c_str());
                SFs_C_1d = (TH1D*)file_nominal->Get((full_hname_C).c_str());
                SFs_D_1d = (TH1D*)file_nominal->Get((full_hname_D).c_str());
                SFs_E_1d = (TH1D*)file_nominal->Get((full_hname_E).c_str());
                SFs_F_1d = (TH1D*)file_nominal->Get((full_hname_F).c_str());
            }

            // Preparation
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

            if(tname.find("ele30_jet35_OR_ele28_ht150_OR_ele35") != std::string::npos){
                c_title1 = "Ele30 + Jet35 OR Ele28 + HT150 OR Ele35";
                f_title1 = "EleJet_OR_EleHT_OR_Ele35_";
            }
            else if(tname.find("ele30_jet35_OR_ele28_ht150") != std::string::npos){
                c_title1 = "Ele30 + Jet35 OR Ele28 + HT150";
                f_title1 = "EleJet_OR_EleHT_";
            }
            else if(tname.find("ele30_jet35_OR_ele35") != std::string::npos){
                c_title1 = "Ele30 + Jet35 OR Ele35";
                f_title1 = "EleJet_OR_Ele35_";
            }
            else if(tname.find("ele28_ht150_OR_ele35") != std::string::npos){
                c_title1 = "Ele28 + HT150 OR Ele35";
                f_title1 = "EleHT_OR_Ele35_";
            }
            else if(tname.find("jet35") != std::string::npos){
                c_title1 = "Ele30 + Jet35";
                f_title1 = "EleJet_";
            }
            else if(tname.find("ht150") != std::string::npos){
                c_title1 = "Ele28 + HT150";
                f_title1 = "EleHT_";
            }
            else if(tname.find("ele35") != std::string::npos){
                c_title1 = "Ele35";
                f_title1 = "Ele35_";
            }
            if (c_title1 == "")
                continue;

            if(hname.find("SFs_ele_pt_ele_eta") != std::string::npos){
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
                nxbins_print = n_eleptBins;
                nybins_print = n_eleetaBins;
                xbins_print = x_eleptBins;
                ybins_print = x_eleetaBins;
            }
            else if(hname.find("SFs_ele_pt_ele_sceta") != std::string::npos){
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
                nxbins_print = n_eleptBins;
                nybins_print = n_eleetaBins;
                xbins_print = x_eleptBins;
                ybins_print = x_eleetaBins;
            }
            else if(hname.find("SFs_ele_pt_jet_pt") != std::string::npos){
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
                nxbins_print = n_eleptBins;
                nybins_print = n_jetptBins;
                xbins_print = x_eleptBins;
                ybins_print = x_jetptBins;
            }
            else if(hname.find("SFs_ele_pt_ht") != std::string::npos){
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
                nxbins_print = n_eleptBins;
                nybins_print = n_htBins;
                xbins_print = x_eleptBins;
                ybins_print = x_htBins;
            }
            else if(hname.find("SFs_ele_pt") != std::string::npos){
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
            else if(hname.find("SFs_ele_eta") != std::string::npos){
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
            else if(hname.find("SFs_ele_sceta") != std::string::npos){
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
            else if(hname.find("SFs_jet_pt") != std::string::npos){
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
            else if(hname.find("SFs_jet_eta") != std::string::npos){
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
            else if(hname.find("SFs_ht") != std::string::npos){
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
            else if(hname.find("SFs_njets") != std::string::npos){
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
            else if(hname.find("SFs_npv") != std::string::npos){
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

            double sf_nominal = 0;
            double sf_sl_dl = 0;
            double sf_htup = 0;
            double sf_htdown = 0;
            double sf_B = 0;
            double sf_C = 0;
            double sf_D = 0;
            double sf_E = 0;
            double sf_F = 0;
            double sf_lumi = 0;
            double stat_err = 0;
            double syst_err_ht = 0;
            double syst_err_lumi = 0;
            double syst_err_sl_dl = 0;
            double err_total = 0;

            if ((hname.find("SFs_ele_pt_ele_eta") != std::string::npos) || (hname.find("SFs_ele_pt_ele_sceta") != std::string::npos) || (hname.find("SFs_ele_pt_jet_pt") != std::string::npos) ||   (hname.find("SFs_ele_pt_ht") != std::string::npos)){
                for (int i=1; i<=nxbins_print; i++){
                    for (int j=1; j<=nybins_print; j++){
                        sf_nominal = SFs_final_2d->GetBinContent(i,j);
                        stat_err = SFs_final_2d->GetBinError(i,j);

                        // Calculation of Systematic Uncertainties from HT variation
                        sf_htup = SFs_htup_2d->GetBinContent(i,j);
                        sf_htdown = SFs_htdown_2d->GetBinContent(i,j);
                        syst_err_ht = fabs(sf_htup - sf_htdown)/2.0;

                        // Calculation of Systematic Uncertainties from Lumi weighting
                        sf_B = SFs_B_2d->GetBinContent(i,j);
                        sf_C = SFs_C_2d->GetBinContent(i,j);
                        sf_D = SFs_D_2d->GetBinContent(i,j);
                        sf_E = SFs_E_2d->GetBinContent(i,j);
                        sf_F = SFs_F_2d->GetBinContent(i,j);
                        sf_lumi = sf_B*0.115 + sf_C*0.232 + sf_D*0.102 + sf_E*0.224 + sf_F*0.326;
                        syst_err_lumi = fabs(sf_lumi - sf_nominal);

                        // Calculation of Systematic Uncertainties from SL+DL sample
                        sf_sl_dl = SFs_sl_dl_2d->GetBinContent(i,j);
                        syst_err_sl_dl = fabs(sf_sl_dl - sf_nominal);

                        // Total Uncertainty
                        err_total = sqrt(stat_err*stat_err + syst_err_ht*syst_err_ht + syst_err_lumi*syst_err_lumi + syst_err_sl_dl*syst_err_sl_dl);
                        SFs_final_2d->SetBinError(i,j,err_total);

                        /*
                        if (i==1 and j==1){
                            std::cout<<sf_nominal<<"\n";
                            std::cout<<sf_htup<<"  "<<sf_htdown<<"\n";
                            std::cout<<sf_lumi<<"\n";
                            std::cout<<sf_sl_dl<<"\n";
                            std::cout<<stat_err<<"  "<<syst_err_ht<<"  "<<syst_err_lumi<<"  "<<syst_err_sl_dl<<"\n";
                            std::cout<<err_total<<"\n";
                        }
                        */

                    }
                }
            }
            else{
                for (int i=1; i<=nxbins_print; i++){
                    sf_nominal = SFs_final_1d->GetBinContent(i);
                    stat_err = SFs_final_1d->GetBinError(i);

                    // Calculation of Systematic Uncertainties from HT variation
                    sf_htup = SFs_htup_1d->GetBinContent(i);
                    sf_htdown = SFs_htdown_1d->GetBinContent(i);
                    syst_err_ht = fabs(sf_htup - sf_htdown)/2.0;

                    // Calculation of Systematic Uncertainties from Lumi weighting
                    sf_B = SFs_B_1d->GetBinContent(i);
                    sf_C = SFs_C_1d->GetBinContent(i);
                    sf_D = SFs_D_1d->GetBinContent(i);
                    sf_E = SFs_E_1d->GetBinContent(i);
                    sf_F = SFs_F_1d->GetBinContent(i);
                    sf_lumi = sf_B*0.115 + sf_C*0.232 + sf_D*0.102 + sf_E*0.224 + sf_F*0.326;
                    syst_err_lumi = fabs(sf_lumi - sf_nominal);

                    // Calculation of Systematic Uncertainties from SL+DL sample
                    sf_sl_dl = SFs_sl_dl_1d->GetBinContent(i);
                    syst_err_sl_dl = fabs(sf_sl_dl - sf_nominal);

                    err_total = sqrt(stat_err*stat_err + syst_err_ht*syst_err_ht + syst_err_lumi*syst_err_lumi + syst_err_sl_dl*syst_err_sl_dl);
                    SFs_final_1d->SetBinError(i,err_total);
                }
            }

            // Plotting
            gStyle->SetLegendBorderSize(1);
            gStyle->SetLegendTextSize(0.025);
            gStyle->SetOptStat("ne");
            gStyle->SetPalette(kBird);
            TCanvas *c1 = new TCanvas("c1","test",1100,650);
            c1->DrawFrame(ll1,ll2,ul1,ul2,(c_title1 + " : 2017 Trigger SF vs " + c_title2 + "; Scale Factor").c_str());
            c1->SetGrid();
            //TLegend* leg1;
            //leg1 = new TLegend(leg_xl,leg_yl,leg_xu,leg_yu);
            TLine *line1 = new TLine(ll1,1,ul1,1);
            line1->SetLineStyle(kDashed);
            line1->SetLineWidth(1);
            //leg1->SetFillColor(kWhite);
            //leg1->SetFillStyle(1001);
            if ((hname.find("SFs_ele_pt_ele_eta") != std::string::npos) || (hname.find("SFs_ele_pt_ele_sceta") != std::string::npos) || (hname.find("SFs_ele_pt_jet_pt") != std::string::npos) ||   (hname.find("SFs_ele_pt_ht") != std::string::npos)){
                //leg1->AddEntry(effi_mc2,"2017_MC","L");
                SFs_final_2d->SetLineWidth(1);
                SFs_final_2d->SetLineColor(kRed);
                gPad->SetLogx(1);
                gStyle->SetPaintTextFormat("1.3f");
                SFs_final_2d->Draw("TEXTE COLZ same");
            }
            else{
                //leg1->AddEntry(effi_mc1,"2017_MC","L");
                SFs_final_1d->SetLineWidth(1);
                SFs_final_1d->SetLineColor(kRed);
                gPad->SetLogx(0);
                SFs_final_1d->Draw("L same");
                line1->Draw("same");
            }
            //leg1->Draw("same");
            c1->Print(("SF_2017_" + f_title1 + f_title2 + ".pdf").c_str());
            delete c1;
            //delete leg1;
            delete line1;

            // For writing to root files
            if ((hname.find("ele_pt_ele_eta") != std::string::npos) || (hname.find("ele_pt_ele_sceta") != std::string::npos) || (hname.find("ele_pt_jet_pt") != std::string::npos) ||   (hname.find("ele_pt_ht") != std::string::npos)){
                sfs_total_2.push_back(SFs_final_2d);
                if (tname.find("ele28_ht150_OR_ele35") != std::string::npos && tname.find("ele30_jet35") == std::string::npos){
                    sfs_eghtor_2.push_back(SFs_final_2d);
                }
            }
            else{
                sfs_total_1.push_back(SFs_final_1d);
                if (tname.find("ele28_ht150_OR_ele35") != std::string::npos && tname.find("ele30_jet35") == std::string::npos){
                    sfs_eghtor_1.push_back(SFs_final_1d);
                }
            }
            
        } // End of histogram loop
    } // End of trigger loop

    // Writing Histograms in root files
    histofile_total.cd();
    for (int i=0; i<(int)sfs_total_1.size(); i++)
        sfs_total_1[i]->Write();
    for (int i=0; i<(int)sfs_total_2.size(); i++)
        sfs_total_2[i]->Write();
    histofile_total.Close();
    histofile_eghtor.cd();
    for (int i=0; i<(int)sfs_eghtor_1.size(); i++)
        sfs_eghtor_1[i]->Write();
    for (int i=0; i<(int)sfs_eghtor_2.size(); i++)
        sfs_eghtor_2[i]->Write();
    histofile_eghtor.Close();

    delete file_nominal;
    delete file_htsystup;
    delete file_htsystdown;
    delete file_sl_dl;
    return;
}




