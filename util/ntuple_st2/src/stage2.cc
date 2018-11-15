#ifndef ttH__ntuple_st2_stage2_cc
#define ttH__ntuple_st2_stage2_cc

#include "ttH/ntuple_st2/stage2.h"
#include "ttHSW/sp/inl/container_help.h"
#include "ttHSW/sp/inl/transformations.h"
#include "ttHSW/sp/reconc/uncertainties.h"

// inline const double* Procuce_pTXYZ_(const ttHSW::Particle &p)
// {
//     const double p4[4] = {p.getE(), p.getPx(), p.getPy(), p.getPz()};
//     return p4;
// }

stage2::stage2()
    : chi2_rank(81.7, 11.3, 170.1, 20.5, 169.9, 26.8, 114.5, 17.0, "btag", 0, 1,
                6.0, 1.0)
{
    params.m_t = 173;
    params.m_W = 80.4;
    params.SD_m_t = 2.0;
    params.SD_m_W = 2.085;

    jets.reserve(10);
    leps.reserve(4);
    MET.resize(1); // should stay at 1

    // stats
    st_total = 0;
    st_considered = 0;
    st_reconstructed = 0;
}

stage2::~stage2()
{
    std::cout << "Total events: " << st_total << std::endl;
    std::cout << "Considered for reconstruction: " << st_considered << " ("
              << (100. * st_considered / st_total) << "%)" << std::endl;
    std::cout << "Reconstructed: " << st_reconstructed << " ("
              << (100. * st_reconstructed / st_considered) << "%)" << std::endl;

    for (auto p : in_2_RC.p.p_others)
        delete p;
    for (auto p : in_2_RC.SD.p_others)
        delete p;
}

inline void Update_(const double p[4], ttHSW::Particle &up)
{
    up.setE(p[0]);
    up.setPx(p[1]);
    up.setPy(p[2]);
    up.setPz(p[3]);
}

inline void stage2::Fill_buff1_bjets_(const CU_ttH_EDA_Ntuple &tuple_r,
                                      unsigned int &ip, unsigned int &iip)
{
    double p4[4]; // 4momentum buffer
    const unsigned int sz = static_cast<unsigned int>(tuple_r.n_btags);
    for (unsigned int i = 0; i < sz; ++i) {
        sp::Fill_p4_in_cartTXYZ(tuple_r.bjet_pt[i], tuple_r.bjet_phi[i],
                                tuple_r.bjet_eta[i], tuple_r.bjet_E[i], p4);
        ttHSW::Particle &pc = jets_MET_l[ip];
        Update_(p4, pc);
        pc.setDouble("btag", tuple_r.bjet_CSV[i]);
        pc.setCharge(0);
        jets[iip] = &pc;
        ++ip;
        ++iip;
    }
}

inline void stage2::Fill_buff1_jets_(const CU_ttH_EDA_Ntuple &tuple_r,
                                     unsigned int &ip, unsigned int &iip)
{
    double p4[4]; // 4momentum buffer
    const unsigned int sz = static_cast<unsigned int>(tuple_r.n_jets);
    for (unsigned int i = 0; i < sz; ++i) {
        sp::Fill_p4_in_cartTXYZ(tuple_r.jet_pt[i], tuple_r.jet_phi[i],
                                tuple_r.jet_eta[i], tuple_r.jet_E[i], p4);
        ttHSW::Particle &pc = jets_MET_l[ip];
        Update_(p4, pc);
        pc.setDouble("btag", tuple_r.jet_CSV[i]);
        pc.setCharge(0);
        jets[iip] = &pc;
        ++ip;
        ++iip;
    }
}

inline void stage2::Fill_buff1_ele_(const CU_ttH_EDA_Ntuple &tuple_r,
                                    unsigned int &ip, unsigned int &iip)
{
    double p4[4]; // 4momentum buffer
    const unsigned int sz = static_cast<unsigned int>(tuple_r.n_ele);
    for (unsigned int i = 0; i < sz; ++i) {
        sp::Fill_p4_in_cartTXYZ(tuple_r.ele_pt[i], tuple_r.ele_phi[i],
                                tuple_r.ele_eta[i], tuple_r.ele_E[i], p4);
        ttHSW::Particle &pc = jets_MET_l[ip];
        Update_(p4, pc);
        if (pc.hasDouble("btag"))
            pc.eraseDouble("btag");
        pc.setCharge(static_cast<double>(tuple_r.ele_charge[i]));
        leps[iip] = &pc;
        ++ip;
        ++iip;
    }
}

inline void stage2::Fill_buff1_mu_(const CU_ttH_EDA_Ntuple &tuple_r,
                                   unsigned int &ip, unsigned int &iip)
{
    double p4[4]; // 4momentum buffer
    const unsigned int sz = static_cast<unsigned int>(tuple_r.n_mu);
    for (unsigned int i = 0; i < sz; ++i) {
        sp::Fill_p4_in_cartTXYZ(tuple_r.mu_pt[i], tuple_r.mu_phi[i],
                                tuple_r.mu_eta[i], tuple_r.mu_E[i], p4);
        ttHSW::Particle &pc = jets_MET_l[ip];
        Update_(p4, pc);
        if (pc.hasDouble("btag"))
            pc.eraseDouble("btag");
        pc.setCharge(static_cast<double>(tuple_r.mu_charge[i]));
        leps[iip] = &pc;
        ++ip;
        ++iip;
    }
}

inline void stage2::Fill_buff1_MET_(const CU_ttH_EDA_Ntuple &tuple_r,
                                    unsigned int &ip)
{
    double p4[4]; // 4momentum buffer

    sp::Fill_p4_in_cartTXYZ(tuple_r.PFMETpt, tuple_r.PFMETphi, 0,
                            tuple_r.PFMETpt, p4);
    ttHSW::Particle &pc = jets_MET_l[ip];
    Update_(p4, pc);
    if (pc.hasDouble("btag"))
        pc.eraseDouble("btag");
    pc.setCharge(0);
    MET[0] = &pc;
}

void stage2::Fill_buff1(const CU_ttH_EDA_Ntuple &tuple_r)
{
    unsigned int ip = 0; // per fill

    unsigned int iip = 0;        // per substorage unit
    jets.resize(tuple_r.n_jets); // + tuple_r.n_btags
    // Fill_buff1_bjets_(tuple_r, ip, iip);
    Fill_buff1_jets_(tuple_r, ip, iip);

    if (ip < 10)
        ip = 10; // much less likely erase is needed
    iip = 0;
    leps.resize(tuple_r.n_ele + tuple_r.n_mu);
    Fill_buff1_ele_(tuple_r, ip, iip);
    Fill_buff1_mu_(tuple_r, ip, iip);
    ip = buff_sz - 1; // put last
    Fill_buff1_MET_(tuple_r, ip);
}

inline void Produce_polar(const ttHSW::Particle *p, double pol[4])
{
    const double p4[4] = {p->getE(), p->getPx(), p->getPy(), p->getPz()};
    sp::CartTXYZ_to_pol(p4, pol);
}

void stage2::Fill_input(const ttHSW::sl::Permutation *perm,
                        const ttHSW::Particle *lepton,
                        const ttHSW::Particle *MET, recoc::input &out)
{
    const double empty[4] = {0, 0, 0, 0};
    out.p.t1_lep = false;
    Produce_polar(perm->bhad, out.p.b1);
    Produce_polar(perm->lj1, out.p.d11);
    Produce_polar(perm->lj2, out.p.d12);

    out.p.t2_lep = true;
    Produce_polar(perm->blep, out.p.b2);
    Produce_polar(lepton, out.p.d21);
    memcpy(out.p.d22, empty, sizeof(out.p.d22));

    Produce_polar(perm->bH, out.p.bH1);
    Produce_polar(perm->bbarH, out.p.bH2);

    out.MET_px = MET->getPx();
    out.MET_py = MET->getPy();

    unsigned int sz;
    if (jets.size() >= 6)
        sz = jets.size() - 6;
    else
        sz = 0;
    sp::P4_resize(out.p.p_others, sz);

    if (sz == 0)
        return;

    auto it1 = out.p.p_others.begin();
    for (const auto jet : jets) {
        if (jet == perm->bhad || jet == perm->lj1 || jet == perm->lj2 ||
            jet == perm->blep || jet == perm->bH || jet == perm->bbarH)
            continue;

        // "exotics" go in here
        Produce_polar(jet, *it1);
        ++it1;
    }
}

inline void Copy_input_p_(const recoc::input_x<4> &rp, recoc::input_x<4> &wp)
{
    wp.t1_lep = rp.t1_lep;
    memcpy(wp.b1, rp.b1, 4);
    memcpy(wp.d11, rp.d11, 4);
    memcpy(wp.d12, rp.d12, 4);

    wp.t2_lep = rp.t2_lep;
    memcpy(wp.b2, rp.b2, 4);
    memcpy(wp.d21, rp.d21, 4);
    memcpy(wp.d22, rp.d22, 4);

    memcpy(wp.bH1, rp.bH1, 4);
    memcpy(wp.bH2, rp.bH2, 4);
}

inline void Copy_input_SDs_(const recoc::input_x<3> &rs, recoc::input_x<3> &ws)
{
    ws.t1_lep = rs.t1_lep;
    memcpy(ws.b1, rs.b1, 3);
    memcpy(ws.d11, rs.d11, 3);
    memcpy(ws.d12, rs.d12, 3);

    ws.t2_lep = rs.t2_lep;
    memcpy(ws.b2, rs.b2, 3);
    memcpy(ws.d21, rs.d21, 3);
    memcpy(ws.d22, rs.d22, 3);

    memcpy(ws.bH1, rs.bH1, 3);
    memcpy(ws.bH2, rs.bH2, 3);
}

inline void Copy_input_jets_(const recoc::input_x<4> &rp,
                             const recoc::input_x<3> &rs, data_jets<4> &wj,
                             data_jets<3> &wjs)
{
    const double empty[4] = {0, 0, 0, 0};
    if (rp.p_others.size() > 0) {
        memcpy(wj.jet0, rp.p_others[0], 4);
        memcpy(wjs.jet0, rs.p_others[0], 3);
    } else {
        memcpy(wj.jet0, empty, 4);
        memcpy(wjs.jet0, empty, 3);
    }
    if (rp.p_others.size() > 1) {
        memcpy(wj.jet1, rp.p_others[1], 4);
        memcpy(wjs.jet1, rs.p_others[1], 3);
    } else {
        memcpy(wj.jet1, empty, 4);
        memcpy(wjs.jet1, empty, 3);
    }
    if (rp.p_others.size() > 2) {
        memcpy(wj.jet2, rp.p_others[2], 4);
        memcpy(wjs.jet2, rs.p_others[2], 3);
    } else {
        memcpy(wj.jet2, empty, 4);
        memcpy(wjs.jet2, empty, 3);
    }
    if (rp.p_others.size() > 3) {
        memcpy(wj.jet3, rp.p_others[3], 4);
        memcpy(wjs.jet3, rs.p_others[3], 3);
    } else {
        memcpy(wj.jet3, empty, 4);
        memcpy(wjs.jet3, empty, 3);
    }
    if (rp.p_others.size() > 4) {
        memcpy(wj.jet4, rp.p_others[4], 4);
        memcpy(wjs.jet4, rs.p_others[4], 3);
    } else {
        memcpy(wj.jet4, empty, 4);
        memcpy(wjs.jet4, empty, 3);
    }
}

void Copy_input_(const recoc::input &in, const unsigned int &perm,
                 ntuple_write &tuple_w)
{
    tuple_w.in[perm].MET_px = in.MET_px;
    tuple_w.in[perm].MET_py = in.MET_py;

    Copy_input_p_(in.p, tuple_w.in[perm].p);
    Copy_input_SDs_(in.SD, tuple_w.in[perm].SD);
    Copy_input_jets_(in.p, in.SD, tuple_w.inj[perm], tuple_w.inj_sd[perm]);
}

inline void Copy_result_status_(const recoc::output &rst, recoc::output &wst)
{
    wst.inner_min_status = rst.inner_min_status;
    wst.outer_min_status = rst.outer_min_status;
    wst.inner_edm = rst.inner_edm;
    wst.outer_edm = rst.outer_edm;
    wst.weight = rst.weight;
}

void Copy_result_(const recoc::output &res, const unsigned int &perm,
                  ntuple_write &tuple_w)
{
    // Copy_input subfunctions can be recycled here
    Copy_input_p_(res.p, tuple_w.out[perm].p);
    Copy_input_SDs_(res.SD, tuple_w.out[perm].SD);
    Copy_input_jets_(res.p, res.SD, tuple_w.outj[perm], tuple_w.outj_sd[perm]);

    tuple_w.out[perm].chi2s = res.chi2s;
    Copy_result_status_(res, tuple_w.out[perm]);
}

void stage2::Process_event(const unsigned int ev_nr,
                           const CU_ttH_EDA_Ntuple &tuple_r,
                           ntuple_write &tuple_w)
{
    // FIXME: default values are needed?
    ++st_total;
    if (st_considered >= 10)
        return;
    // Consistency_check(tuple_r);
    if (tuple_r.n_lep != 1 && tuple_r.n_lep != 2) // FIXME old ntuple check
        return;
    if (tuple_r.n_lep != 1 || tuple_r.n_jets < 6) { // proceed only with SL
        // tuple_w.reconstructed = false;
        return;
    }
    ++st_considered;
    Fill_buff1(tuple_r);
#ifdef DEBUG
    std::cout << "ev nr: " << ev_nr << std::endl;
#endif

    auto PT = chi2_rank.createPermutationTable(ttHSW::sl::H_TLEP_H_THAD, jets,
                                               MET, leps[0]);
    for (unsigned int iperm = 0; iperm < nts2::n_perm; ++iperm) {
        // prepare input part
        auto perm = PT.get(ttHSW::sl::H_TLEP_H_THAD, iperm);
        Fill_input(perm, leps[0], MET[0], in_2_RC);
        sp::Fill_SDs(in_2_RC);
        Copy_input_(in_2_RC, iperm, tuple_w); // save
        // recoc::Print(in_2_RC);

        // deal with result/output part
        recoc::output result = reco_C.reco(in_2_RC, params);
        tuple_w.suceeded[iperm] = true; // FIXME get status from recoc::output
        Copy_result_(result, iperm, tuple_w); // save
        // recoc::Print(result);
        // recoc::Print_diff(result, in_2_RC);
    }

    ++st_reconstructed;
}

#endif
