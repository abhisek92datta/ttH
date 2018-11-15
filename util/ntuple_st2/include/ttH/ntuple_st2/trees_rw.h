#ifndef ttH__ntuple_st2__trees_rw_h
#define ttH__ntuple_st2__trees_rw_h

#include "TFile.h"
#include "ttH/ntuple_st2/data_structs.h"

void Set_up_branches_r(CU_ttH_EDA_Ntuple &tuple_r, ntuple_ROOT_r &ROOT_r,
                       TTree *data);
bool Set_up_branches_w(TFile &out_f, ntuple_write &data_w, TTree **trees,
                       TBranch **write_here);

#endif
