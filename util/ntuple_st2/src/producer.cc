#ifndef ttH__ntuple_st2_producer_cc
#define ttH__ntuple_st2_producer_cc

#include "ttH/ntuple_st2/producer.h"
#include "ttH/ntuple_st2/data_structs.h"
#include "ttH/ntuple_st2/stage2.h"
#include "ttH/ntuple_st2/trees.h"
#include <iostream>

#include "TBranch.h"
#include "TFile.h"
#include "TTree.h"

#ifdef DEBUG
#include "ttH/ntuple_st2/debug.h"
#endif

using namespace std;

inline void Fill_trees_(ntupler_data &d)
{
    /*
     * if you are enhancing an original trees, you need lines below:
     * (otherwise, usual Fill() is broken as of R 6.10)
     */
    // for (unsigned int br = 0; br < nts2::n_branches; ++br)
    //     (d.write_here[br])->Fill();

    // 0th tree is a clone
    // d.out[0]->Fill(); // "should" do the same as loop, broken as of R 6.10
    // for totally new trees:
    for (unsigned int i = 1; i < nts2::n_trees; ++i)
        d.out[i]->Fill();
}

void Produce_new_ntuple_stage2(const string &fn_in, const string &fn_out)
{
    const string mth = "Produce_new_ntuple_stage2()";
    cout << mth << " input file: " << fn_in << endl;
    cout << mth << " target file: " << fn_out << endl;

    TFile in_f(fn_in.c_str(), "read");
    TFile out_f(fn_out.c_str(), "recreate");

    ntupler_data d = Prepare_IO_trees(in_f, out_f);
    if (d.in == nullptr || d.out == nullptr)
        return;

    stage2 prc;
#ifdef DEBUG
    const Long64_t n_entries = d.in->GetEntries() / 100;
#else
    const Long64_t n_entries = d.in->GetEntries();
#endif
    for (Long64_t i = 0; i < n_entries; ++i) {
        d.in->GetEntry(i);
        Transfer_ROOT_data(d.ROOT_r, d.tuple_r);
        prc.Process_event(i, d.tuple_r, d.tuple_w);
#ifdef DEBUG
        dbg::TEST_FILL(i, d);
#endif
        Fill_trees_(d);
    }

    // d.out->Print();
    out_f.Write();

    delete[] d.write_here;
}

#endif
