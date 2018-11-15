#ifndef ttH__ntuple_st2_data_stucts_h
#define ttH__ntuple_st2_data_stucts_h

#include "TTree.h"
#include "ttH/analyzers/ttH_bb/CU_ttH_EDA_Ntuple.h"
#include "ttH/ntuple_st2/definitions.h"
#include "ttHSW/core/reconc.h"
#include <string>

// copy cat of CU_ttH_EDA_Ntuple for ROOT reading
struct ntuple_ROOT_r {
    std::vector<double> *mu_pt;
    std::vector<double> *mu_eta;
    std::vector<double> *mu_phi;
    std::vector<double> *mu_E;
    std::vector<int> *mu_charge;
    std::vector<double> *mu_iso;

    std::vector<double> *ele_pt;
    std::vector<double> *ele_eta;
    std::vector<double> *ele_phi;
    std::vector<double> *ele_E;
    std::vector<int> *ele_charge;
    std::vector<double> *ele_iso;

    std::vector<double> *jet_pt;
    std::vector<double> *jet_eta;
    std::vector<double> *jet_phi;
    std::vector<double> *jet_E;
    std::vector<double> *jet_CSV;

    std::vector<double> *bjet_pt;
    std::vector<double> *bjet_eta;
    std::vector<double> *bjet_phi;
    std::vector<double> *bjet_E;
    std::vector<double> *bjet_CSV;
};

template <unsigned int sz> struct data_jets {
    double jet0[sz];
    double jet1[sz];
    double jet2[sz];
    double jet3[sz];
    double jet4[sz];
};

struct ntuple_write {
    bool suceeded[nts2::n_perm];

    recoc::input in[nts2::n_perm];
    data_jets<4> inj[nts2::n_perm]; // vector<double*> is too much for ROOT
    data_jets<3> inj_sd[nts2::n_perm];

    recoc::output out[nts2::n_perm];
    data_jets<4> outj[nts2::n_perm]; // vector<double*> is too much for ROOT
    data_jets<3> outj_sd[nts2::n_perm];
};

struct ntupler_data {
    CU_ttH_EDA_Ntuple tuple_r; // full struct, usually semiused
    ntuple_write tuple_w;

    // ROOT of Might & Magic
    TBranch **write_here; // = n_branches
    TTree *in;
    TTree **out; // = n_perm * n_new_tr + 1 (clone)
    ntuple_ROOT_r ROOT_r;
};

#endif
