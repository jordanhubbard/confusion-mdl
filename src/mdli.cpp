#include <stdio.h>
#include <stdlib.h>
#include <gc/gc.h>
#include "macros.hpp"
#include "mdl_internal_defs.h"
#include <set>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    static const char *optstring = "r:";
    int optchar;
    FILE * restorefile = NULL;

    GC_INIT();
    mdl_interp_init();

    while ((optchar = getopt(argc, argv, optstring)) != -1)
    {
        switch (optchar)
        {
        case 'r':
            restorefile = fopen(optarg, "rb");
            if (!restorefile) 
            {
                fprintf(stderr, "Couldn't open restore file %s", optarg);
                exit(-1);
            }
            break;
        }
    }
        
//    mdl_rep_loop();
    mdl_toplevel(restorefile);
    
}
