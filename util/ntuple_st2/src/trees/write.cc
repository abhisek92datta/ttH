#ifndef ttH__ntuple_st2__write_cc
#define ttH__ntuple_st2__write_cc

#include "ttH/ntuple_st2/definitions.h"
#include "ttH/ntuple_st2/trees_rw.h"
#include <iostream>
#include <string>

/*
 *
 * Set up branches for writing (SUBW)
 *
 */

/*
 * Reconstruction final status(es)
 */
inline void SUBW_status_(const unsigned int perm, ntuple_write &data_w,
                         unsigned int &ibr, TTree *&up, TBranch **br)
{
    up = new TTree("status", "status");
    auto &suceeded = data_w.suceeded[perm];
    br[ibr] = up->Branch("suceeded", &suceeded);
    ++ibr;

    auto &out = data_w.out[perm];
    br[ibr] = up->Branch("inner_min", &out.inner_min_status);
    ++ibr;
    br[ibr] = up->Branch("outer_min", &out.outer_min_status);
    ++ibr;
    br[ibr] = up->Branch("inner_edm", &out.inner_edm);
    ++ibr;
    br[ibr] = up->Branch("outer_edm", &out.outer_edm);
    ++ibr;
    br[ibr] = up->Branch("weight", &out.weight);
    ++ibr;
}

/*
 * input 4momenta
 */
inline void SUBW_ip_(const unsigned int perm, ntuple_write &data_w,
                     unsigned int &ibr, TTree *&up, TBranch **br)
{
    up = new TTree("ip", "ip");
    auto &in = data_w.in[perm];
    br[ibr] = up->Branch("MET_px", &in.MET_px);
    ++ibr;
    br[ibr] = up->Branch("MET_py", &in.MET_py);
    ++ibr;

    auto &ip = data_w.in[perm].p;
    br[ibr] = up->Branch("t1_lep", &ip.t1_lep);
    ++ibr;
    br[ibr] = up->Branch("b1", ip.b1, "b1[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("d11", ip.d11, "d11[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("d12", ip.d12, "d12[4]/D", 4);
    ++ibr;

    br[ibr] = up->Branch("t2_lep", &ip.t1_lep);
    ++ibr;
    br[ibr] = up->Branch("b2", ip.b2, "b2[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("d21", ip.d21, "d21[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("d22", ip.d21, "d22[4]/D", 4);
    ++ibr;

    br[ibr] = up->Branch("bH1", ip.bH1, "bH1[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("bH2", ip.bH2, "bH2[4]/D", 4);
    ++ibr;

    auto &ij = data_w.inj[perm];
    br[ibr] = up->Branch("jet0", &ij.jet0, "jet0[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("jet1", &ij.jet1, "jet1[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("jet2", &ij.jet2, "jet2[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("jet3", &ij.jet3, "jet3[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("jet4", &ij.jet4, "jet4[4]/D", 4);
    ++ibr;
}

/*
 * output (resulting) 4momenta
 */
inline void SUBW_op_(const unsigned int perm, ntuple_write &data_w,
                     unsigned int &ibr, TTree *&up, TBranch **br)
{
    up = new TTree("op", "op");
    auto &ip = data_w.out[perm].p;
    br[ibr] = up->Branch("t1_lep", &ip.t1_lep);
    ++ibr;
    br[ibr] = up->Branch("b1", ip.b1, "b1[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("d11", ip.d11, "d11[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("d12", ip.d12, "d12[4]/D", 4);
    ++ibr;

    br[ibr] = up->Branch("t2_lep", &ip.t1_lep);
    ++ibr;
    br[ibr] = up->Branch("b2", ip.b2, "b2[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("d21", ip.d21, "d21[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("d22", ip.d21, "d22[4]/D", 4);
    ++ibr;

    br[ibr] = up->Branch("bH1", ip.bH1, "bH1[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("bH2", ip.bH2, "bH2[4]/D", 4);
    ++ibr;

    auto &ij = data_w.outj[perm];
    br[ibr] = up->Branch("jet0", &ij.jet0, "jet0[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("jet1", &ij.jet1, "jet1[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("jet2", &ij.jet2, "jet2[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("jet3", &ij.jet3, "jet3[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("jet4", &ij.jet4, "jet4[4]/D", 4);
    ++ibr;

    auto &ipp = data_w.out[perm].parents_p;
    br[ibr] = up->Branch("t1", &ipp.t1, "t1[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("w1", &ipp.w1, "w1[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("t2", &ipp.t2, "t2[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("w2", &ipp.w2, "w2[4]/D", 4);
    ++ibr;
    br[ibr] = up->Branch("h", &ipp.h, "h[4]/D", 4);
    ++ibr;
}

/*
 * input SDs
 */
inline void SUBW_iSD_(const unsigned int perm, ntuple_write &data_w,
                      unsigned int &ibr, TTree *&up, TBranch **br)
{
    up = new TTree("iSD", "iSD");
    auto &isd = data_w.in[perm].SD;
    br[ibr] = up->Branch("b1", isd.b1, "b1[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("d11", isd.d11, "d11[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("d12", isd.d12, "d12[3]/D", 3);
    ++ibr;

    br[ibr] = up->Branch("b2", isd.b2, "b2[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("d21", isd.d21, "d21[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("d22", isd.d21, "d22[3]/D", 3);
    ++ibr;

    br[ibr] = up->Branch("bH1", isd.bH1, "bH1[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("bH2", isd.bH2, "bH2[3]/D", 3);
    ++ibr;

    auto &ij = data_w.inj_sd[perm];
    br[ibr] = up->Branch("jet0", &ij.jet0, "jet0[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("jet1", &ij.jet1, "jet1[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("jet2", &ij.jet2, "jet2[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("jet3", &ij.jet3, "jet3[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("jet4", &ij.jet4, "jet4[3]/D", 3);
    ++ibr;
}

/*
 * output (resulting) SDs
 */
inline void SUBW_oSD_(const unsigned int perm, ntuple_write &data_w,
                      unsigned int &ibr, TTree *&up, TBranch **br)
{
    up = new TTree("oSD", "oSD");
    auto &isd = data_w.out[perm].SD;
    br[ibr] = up->Branch("b1", isd.b1, "b1[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("d11", isd.d11, "d11[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("d12", isd.d12, "d12[3]/D", 3);
    ++ibr;

    br[ibr] = up->Branch("b2", isd.b2, "b2[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("d21", isd.d21, "d21[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("d22", isd.d21, "d22[3]/D", 3);
    ++ibr;

    br[ibr] = up->Branch("bH1", isd.bH1, "bH1[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("bH2", isd.bH2, "bH2[3]/D", 3);
    ++ibr;

    auto &ij = data_w.outj_sd[perm];
    br[ibr] = up->Branch("jet0", &ij.jet0, "jet0[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("jet1", &ij.jet1, "jet1[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("jet2", &ij.jet2, "jet2[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("jet3", &ij.jet3, "jet3[3]/D", 3);
    ++ibr;
    br[ibr] = up->Branch("jet4", &ij.jet4, "jet4[3]/D", 3);
    ++ibr;
}

inline void SUBW_chi2_(const unsigned int perm, ntuple_write &data_w,
                       unsigned int &ibr, TTree *&up, TBranch **br)
{
    up = new TTree("chi2", "chi2");
    auto &ichi2 = data_w.out[perm].chi2s;
    br[ibr] = up->Branch("mt1", &ichi2.mt1);
    ++ibr;
    br[ibr] = up->Branch("mw1", &ichi2.mw1);
    ++ibr;
    br[ibr] = up->Branch("b1", &ichi2.b1);
    ++ibr;
    br[ibr] = up->Branch("d11", &ichi2.d11);
    ++ibr;
    br[ibr] = up->Branch("d12", &ichi2.d12);
    ++ibr;
    br[ibr] = up->Branch("mt2", &ichi2.mt2);
    ++ibr;
    br[ibr] = up->Branch("mw2", &ichi2.mw2);
    ++ibr;
    br[ibr] = up->Branch("b2", &ichi2.b2);
    ++ibr;
    br[ibr] = up->Branch("d21", &ichi2.d21);
    ++ibr;
    br[ibr] = up->Branch("d22", &ichi2.d22);
    ++ibr;
    br[ibr] = up->Branch("nontop_objs", &ichi2.nontop_objs);
    ++ibr;
}

/*
 * Core funtion: Set up branches for writing (SUBW)
 */
bool Set_up_branches_w(TFile &out_f, ntuple_write &data_w, TTree **trees,
                       TBranch **write_here)
{
    // out_f.mkdir("ttHbb");
    // out_f.cd("ttHbb");
    const std::string rdr1 = "reconstruction";

    unsigned int ibranch = 0;
    unsigned int itree = 1;
    for (unsigned int iperm = 0; iperm < nts2::n_perm; ++iperm) {
        const std::string rdr2 =
            static_cast<std::string>("perm") + std::to_string(iperm);
        const std::string path = nts2::in_roodir + "/" + rdr1 + "/" + rdr2;
        out_f.mkdir(path.c_str());
        out_f.cd(path.c_str());

        SUBW_ip_(iperm, data_w, ibranch, trees[itree], write_here);
        ++itree;
        SUBW_iSD_(iperm, data_w, ibranch, trees[itree], write_here);
        ++itree;
        SUBW_op_(iperm, data_w, ibranch, trees[itree], write_here);
        ++itree;
        SUBW_oSD_(iperm, data_w, ibranch, trees[itree], write_here);
        ++itree;
        SUBW_chi2_(iperm, data_w, ibranch, trees[itree], write_here);
        ++itree;
        SUBW_status_(iperm, data_w, ibranch, trees[itree], write_here);
        ++itree;
    }

    if (nts2::n_branches != ibranch) {
        std::cerr << "Set_up_branches_() Wrong nr. of branches\n"
                  << "Set_up_branches_() expected: " << nts2::n_branches
                  << ", created: " << ibranch << std::endl;
        return false;
    }

    if (nts2::n_trees != itree) {
        std::cerr << "Set_up_branches_() Wrong nr. of trees\n"
                  << "Set_up_branches_() expected: " << nts2::n_trees
                  << ", created: " << itree << std::endl;
        return false;
    }

    return true;
}

#endif
