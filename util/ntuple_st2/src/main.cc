#include "ttH/ntuple_st2/producer.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>

using namespace std;

inline bool file_exists(const string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <in: ntuple stage 1> "
             << "<out: ntuple stage 2>\n";
        return 1;
    }

    const string in_fn(argv[1]);
    if (!file_exists(in_fn)) {
        cerr << "File " << in_fn << " not found.\n";
        return 1;
    }

    const string out_fn(argv[2]);
    Produce_new_ntuple_stage2(in_fn, out_fn);

    return 0;
}
