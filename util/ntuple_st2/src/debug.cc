#ifndef ttH__ntuple_st2__debug_cc
#define ttH__ntuple_st2__debug_cc

#ifdef DEBUG
#include "ttH/ntuple_st2/debug.h"

namespace dbg
{
void TEST_FILL(const unsigned int ev_nr, ntupler_data &d)
{
    auto &b2 = d.tuple_w.in[0].p.b2;
    b2[0] = 1;
    b2[1] = ev_nr - ev_nr % 11111 + 11111;
    b2[2] = ev_nr - ev_nr % 30000 + 30000;
    b2[3] = ev_nr - ev_nr % 80000 + 80000;

    auto &bH1 = d.tuple_w.in[0].p.bH1;
    bH1[0] = 1;
    bH1[1] = ev_nr - ev_nr % 11111 + 11111;
    bH1[2] = ev_nr - ev_nr % 30000 + 30000;
    bH1[3] = ev_nr - ev_nr % 80000 + 80000;
}
}
#endif

#endif
