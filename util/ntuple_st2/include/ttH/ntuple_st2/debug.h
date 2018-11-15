#ifndef ttH__ntuple_st2__debug_h
#define ttH__ntuple_st2__debug_h

#ifdef DEBUG
#include "ttH/ntuple_st2/data_structs.h"

namespace dbg
{
void TEST_FILL(const unsigned int ev_nr, ntupler_data &d);
}
#endif

#endif
