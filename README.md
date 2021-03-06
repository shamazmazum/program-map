program-map
===========
[![Build Status](https://api.cirrus-ci.com/github/shamazmazum/program-map.svg)](https://cirrus-ci.com/github/shamazmazum/program-map)

**program-map** is a simple helper library for read-only mapping of files (like OpenCL
programs) into memory. Example of use:

~~~~~~~~{.c}
#include <program-map.h>

void do_something ()
{
    struct pm_program_handler ph;
    if (!pm_map_program (&ph, path_to_program)) {
        /*
         * pm_get_error() contains general information about an error. Detailed
         * information why this or another system call failed is in errno variable.
         */
        perror (pm_get_error ());
    }
    do_something_else_with_mapping (ph->space, ph->size);
    if (!pm_unmap_program (&ph)) {
        perror (pm_get_error ());
    }
}
~~~~~~~~
