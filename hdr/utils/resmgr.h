#ifndef HDR_UTILS_RESMGR_H
#define HDR_UTILS_RESMGR_H
#include <stdlib.h>
#include <platform.h>
#include <types.h>
#include <utils/log.h>
#include <string.h>
#include <utils/fs.h>

#ifdef PLATFORM_WINDOWS
#include <direct.h>
#include <io.h>
#endif

#ifdef PLATFORM_LINUX
#include <unistd.h>
#define _access access
#endif

enum {
    DIR_FOUND,
    DIR_NOT_FOUND
};

struct resource_manager {
    char *cwd;
};

extern i8 DefaultSearchDepth;
struct resource_manager* create_resource_manager(void);
void delete_resource_manager(struct resource_manager*);
u8 find_dir(const char* dir_name, i8 search_depth, struct resource_manager*);
void move_path_down(struct resource_manager*);
#endif