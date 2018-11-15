#ifndef ttH__ntuple_st2_stage2_h
#define ttH__ntuple_st2_stage2_h

#include "ttH/ntuple_st2/data_structs.h"
#include "ttHSW/reco.h"
#include "ttHSW/reconstruction.h"

class stage2
{
  public:
    stage2();
    ~stage2();
    void Process_event(const unsigned int ev_nr,
                       const CU_ttH_EDA_Ntuple &tuple_r, ntuple_write &tuple_w);

    void Fill_buff1(const CU_ttH_EDA_Ntuple &tuple_r);

    recoc::input in_2_RC;
    recoc::parameters_ttRC params;
    recoc::ttRC reco_C;

    ttHSW::sl::Chi2Reconstructor chi2_rank;
    const static unsigned int buff_sz = 20;
    ttHSW::Particle jets_MET_l[buff_sz];
    ttHSW::Particles jets;
    ttHSW::Particles MET;
    ttHSW::Particles leps;

  private:
    inline void Fill_buff1_bjets_(const CU_ttH_EDA_Ntuple &tuple_r,
                                  unsigned int &ip, unsigned int &iip);
    inline void Fill_buff1_jets_(const CU_ttH_EDA_Ntuple &tuple_r,
                                 unsigned int &ip, unsigned int &iip);
    inline void Fill_buff1_ele_(const CU_ttH_EDA_Ntuple &tuple_r,
                                unsigned int &ip, unsigned int &iip);
    inline void Fill_buff1_mu_(const CU_ttH_EDA_Ntuple &tuple_r,
                               unsigned int &ip, unsigned int &iip);
    inline void Fill_buff1_MET_(const CU_ttH_EDA_Ntuple &tuple_r,
                                unsigned int &ip);
    void Fill_input(const ttHSW::sl::Permutation *perm,
                    const ttHSW::Particle *lepton, const ttHSW::Particle *MET,
                    recoc::input &out);

    unsigned long st_total;
    unsigned long st_considered;
    unsigned long st_reconstructed;
};

#endif
