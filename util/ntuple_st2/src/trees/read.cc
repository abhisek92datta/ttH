#ifndef ttH__ntuple_st2__read_cc
#define ttH__ntuple_st2__read_cc

#include "ttH/ntuple_st2/trees_rw.h"
#include <iostream>
#include <string>

void Set_up_branches_r(CU_ttH_EDA_Ntuple &tuple_r, ntuple_ROOT_r &ROOT_r,
                       TTree *data)
{
    // No questions to be asked on "trivial" ROOT usage
    // ROOT_r.bjet_E = nullptr;    // ROOT segfaults otherwise
    // ROOT_r.bjet_pt = nullptr;
    // ROOT_r.bjet_phi = nullptr;
    // ROOT_r.bjet_eta = nullptr;
    // ROOT_r.bjet_CSV = nullptr;
    ROOT_r.jet_E = nullptr;
    ROOT_r.jet_pt = nullptr;
    ROOT_r.jet_phi = nullptr;
    ROOT_r.jet_eta = nullptr;
    ROOT_r.jet_CSV = nullptr;
    ROOT_r.mu_E = nullptr;
    ROOT_r.mu_pt = nullptr;
    ROOT_r.mu_phi = nullptr;
    ROOT_r.mu_eta = nullptr;
    ROOT_r.mu_charge = nullptr;
    ROOT_r.ele_E = nullptr;
    ROOT_r.ele_pt = nullptr;
    ROOT_r.ele_phi = nullptr;
    ROOT_r.ele_eta = nullptr;
    ROOT_r.ele_charge = nullptr;

    // data->SetBranchAddress("n_btags", &tuple_r.n_btags);
    // data->SetBranchAddress("bjet_E", &ROOT_r.bjet_E);
    // data->SetBranchAddress("bjet_pt", &ROOT_r.bjet_pt);
    // data->SetBranchAddress("bjet_phi", &ROOT_r.bjet_phi);
    // data->SetBranchAddress("bjet_eta", &ROOT_r.bjet_eta);
    // data->SetBranchAddress("bjet_CSV", &ROOT_r.bjet_CSV);

    data->SetBranchAddress("n_jets", &tuple_r.n_jets);
    data->SetBranchAddress("jet_E", &ROOT_r.jet_E);
    data->SetBranchAddress("jet_pt", &ROOT_r.jet_pt);
    data->SetBranchAddress("jet_phi", &ROOT_r.jet_phi);
    data->SetBranchAddress("jet_eta", &ROOT_r.jet_eta);
    data->SetBranchAddress("jet_CSV", &ROOT_r.jet_CSV);

    data->SetBranchAddress("n_lep", &tuple_r.n_lep);
    data->SetBranchAddress("n_ele", &tuple_r.n_ele);
    data->SetBranchAddress("ele_E", &ROOT_r.ele_E);
    data->SetBranchAddress("ele_pt", &ROOT_r.ele_pt);
    data->SetBranchAddress("ele_phi", &ROOT_r.ele_phi);
    data->SetBranchAddress("ele_eta", &ROOT_r.ele_eta);
    data->SetBranchAddress("ele_charge", &ROOT_r.ele_charge);

    data->SetBranchAddress("n_mu", &tuple_r.n_mu);
    data->SetBranchAddress("mu_E", &ROOT_r.mu_E);
    data->SetBranchAddress("mu_pt", &ROOT_r.mu_pt);
    data->SetBranchAddress("mu_phi", &ROOT_r.mu_phi);
    data->SetBranchAddress("mu_eta", &ROOT_r.mu_eta);
    data->SetBranchAddress("mu_charge", &ROOT_r.mu_charge);

    data->SetBranchAddress("PFMETpt", &tuple_r.PFMETpt);
    data->SetBranchAddress("PFMETphi", &tuple_r.PFMETphi);
}

#endif
