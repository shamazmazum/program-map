#ifndef _PROGRAM_MAP_H_
#define _PROGRAM_MAP_H_

#define PM_EXPORT __attribute__((visibility("default")))

#ifdef __cplusplus
extern "C" {
#endif

struct pm_program_handler {
    void *ph_space;;
    size_t ph_size;
};

PM_EXPORT int pm_map_program (struct pm_program_handler *handler, const char *path);
PM_EXPORT int pm_unmap_program (struct pm_program_handler *handler);
PM_EXPORT const char* pm_get_error();

#ifdef __cplusplus
}
#endif

#endif
