#ifndef ttH__ntuple_st2__io_cc
#define ttH__ntuple_st2__io_cc

#include "ttH/ntuple_st2/definitions.h"
#include "ttH/ntuple_st2/trees.h"
#include "ttH/ntuple_st2/trees_rw.h"
#include <iostream>
#include <string>

ntupler_data Prepare_IO_trees(TFile &in_f, TFile &out_f)
{
    ntupler_data d;
    const std::string tpath = nts2::in_roodir + "/" + nts2::in_tree;
    d.in = static_cast<TTree *>(in_f.Get(tpath.c_str()));

    d.out = new TTree *[nts2::n_trees];
    out_f.mkdir(nts2::in_roodir.c_str());
    out_f.cd(nts2::in_roodir.c_str());
    d.out[0] = d.in->CloneTree();

    Set_up_branches_r(d.tuple_r, d.ROOT_r, d.in); // d.out

    d.write_here = new TBranch *[nts2::n_branches];
    if (!Set_up_branches_w(out_f, d.tuple_w, d.out, d.write_here)) {
        delete d.write_here;
        delete[] d.out;
        d.in = nullptr;
        d.out = nullptr;
        return d;
    }

    return d;
}

void Transfer_ROOT_data(const ntuple_ROOT_r &ROOT_r, CU_ttH_EDA_Ntuple &tuple_r)
{
    // tuple_r.bjet_E = *(ROOT_r.bjet_E);
    // tuple_r.bjet_pt = *(ROOT_r.bjet_pt);
    // tuple_r.bjet_phi = *(ROOT_r.bjet_phi);
    // tuple_r.bjet_eta = *(ROOT_r.bjet_eta);
    // tuple_r.bjet_CSV = *(ROOT_r.bjet_CSV);

    tuple_r.jet_E = *(ROOT_r.jet_E);
    tuple_r.jet_pt = *(ROOT_r.jet_pt);
    tuple_r.jet_phi = *(ROOT_r.jet_phi);
    tuple_r.jet_eta = *(ROOT_r.jet_eta);
    tuple_r.jet_CSV = *(ROOT_r.jet_CSV);

    tuple_r.ele_E = *(ROOT_r.ele_E);
    tuple_r.ele_pt = *(ROOT_r.ele_pt);
    tuple_r.ele_phi = *(ROOT_r.ele_phi);
    tuple_r.ele_eta = *(ROOT_r.ele_eta);
    tuple_r.ele_charge = *(ROOT_r.ele_charge);

    tuple_r.mu_E = *(ROOT_r.mu_E);
    tuple_r.mu_pt = *(ROOT_r.mu_pt);
    tuple_r.mu_phi = *(ROOT_r.mu_phi);
    tuple_r.mu_eta = *(ROOT_r.mu_eta);
    tuple_r.mu_charge = *(ROOT_r.mu_charge);
}

#endif
