#ifndef _PROGRAM_MAP_H_
#define _PROGRAM_MAP_H_

struct pm_program_handler {
    void *ph_space;;
    size_t ph_size;
};

int pm_map_program (struct pm_program_handler *handler, const char *path);
int pm_unmap_program (struct pm_program_handler *handler);
const char* pm_get_error();

#endif
