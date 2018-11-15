#ifndef ttH__ntuple_st2_IO_trees_h
#define ttH__ntuple_st2_IO_trees_h

#include "TFile.h"
#include "ttH/ntuple_st2/data_structs.h"

ntupler_data Prepare_IO_trees(TFile &in_f, TFile &out_f);
void Transfer_ROOT_data(const ntuple_ROOT_r &ROOT_r,
                        CU_ttH_EDA_Ntuple &tuple_r);

#endif
