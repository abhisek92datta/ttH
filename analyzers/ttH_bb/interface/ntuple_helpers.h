#ifndef CU_ttH_ntuple_helpers_h
#define CU_ttH_ntuple_helpers_h

#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "TLorentzVector.h"
#include "analyzers/ttH_bb/interface/CU_ttH_EDA_Ntuple.h"
#include "analyzers/ttH_bb/interface/CU_ttH_EDA_event_vars.h"

#include "TTree.h"

namespace ntuple
{
void Initialize_reco(CU_ttH_EDA_Reco_Ntuple &ntup);
void Initialize_gen(CU_ttH_EDA_Gen_Ntuple &ntup);
void Initialize_comm(CU_ttH_EDA_Comm_Ntuple &ntup);
void set_up_reco_branches(TTree *, const int &, const bool &, CU_ttH_EDA_Reco_Ntuple &);
void set_up_gen_branches(TTree *, const int &, const bool &, CU_ttH_EDA_Gen_Ntuple &);
void set_up_comm_branches(TTree *, const int &, const bool &, CU_ttH_EDA_Comm_Ntuple &);
void write_ntuple(const CU_ttH_EDA_event_vars &, const MiniAODHelper &, CU_ttH_EDA_Reco_Ntuple &, CU_ttH_EDA_Gen_Ntuple &, CU_ttH_EDA_Comm_Ntuple &, bool &);
void fill_ntuple_gen_b(const CU_ttH_EDA_event_vars &, CU_ttH_EDA_Gen_Ntuple &);
void fill_ntuple_gen_nu(const CU_ttH_EDA_event_vars &, CU_ttH_EDA_Gen_Ntuple &);
}

#endif
