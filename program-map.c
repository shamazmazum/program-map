#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "program-map.h"

#define PM_CANNOT_OPEN 0
#define PM_CANNOT_STAT 1
#define PM_CANNOT_MAP 2
#define PM_CANNOT_UNMAP 3

struct {
    int code;
    const char *message;
} error_codes[] = {
    {PM_CANNOT_OPEN, "Cannot open() a file"},
    {PM_CANNOT_STAT, "Cannot stat() a file"},
    {PM_CANNOT_MAP, "Cannot mmap() a file"},
    {PM_CANNOT_UNMAP, "Cannot munmap() a file"}
};

static int error_code;

int pm_map_program (struct pm_program_handler *handler, const char *path)
{
    int fd, res;

    fd = open (path, O_RDONLY);
    if (fd == -1) {
        error_code = PM_CANNOT_OPEN;
        return 0;
    }

    struct stat st;
    res = fstat (fd, &st);
    if (res == -1) {
        error_code = PM_CANNOT_STAT;
        close (fd);
        return 0;
    }

    handler->ph_size = st.st_size;
    handler->ph_space = mmap (NULL, handler->ph_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close (fd);

    if (handler->ph_space == MAP_FAILED) {
        error_code = PM_CANNOT_MAP;
        return 0;
    }

    return 1;
}

int pm_unmap_program (struct pm_program_handler *handler)
{
    int res = munmap (handler->ph_space, handler->ph_size);
    if (res == -1) {
        error_code = PM_CANNOT_UNMAP;
        return 0;
    }
    return 1;
}

const char* pm_get_error ()
{
    int i;
    for (i=0; i<sizeof (error_codes)/sizeof(error_codes[0]); i++) {
        if (error_code == error_codes[i].code) return error_codes[i].message;
    }
    return "Unknown error";
}
