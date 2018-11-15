#ifndef ttH__ntuple_st2__definitions_h
#define ttH__ntuple_st2__definitions_h

#include <string>

namespace nts2
{
const std::string in_roodir = "ttHbb";
const std::string in_tree = "eventTree";

const unsigned int n_perm = 1;
const unsigned int n_new_tr = 6;
// way too little will give weird segfaults:
const unsigned int n_branches_perm = 80;

const unsigned int n_branches = n_branches_perm * n_perm;
const unsigned int n_trees = n_perm * n_new_tr + 1; // + 1 clone
}

#endif
