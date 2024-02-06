#include <utils/resmgr.h>
i8 DefaultSearchDepth = 3;

struct resource_manager* create_resource_manager(void)
{
    struct resource_manager* mgr = malloc(sizeof(struct resource_manager));
#ifdef PLATFORM_WINDOWS
    mgr->cwd = _getcwd(NULL, 0);
    if (mgr->cwd == NULL) {
        LOG("Failed to create resource manager", LOG_WARNING);
        return NULL;
    }
#endif
#ifdef PLATFORM_LINUX
    char cwd[512];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        mgr->cwd = cwd;
    } else {
        mgr->cwd = NULL;
        LOG("Failed to create resource manager", LOG_WARNING);
        return NULL;
    }
    // if (_getcwd(mgr->cwd, sizeof()))
#endif
    return mgr;
}

void delete_resource_manager(struct resource_manager* mgr)
{
    if (mgr->cwd != NULL) {
        free(mgr->cwd);
        mgr->cwd = NULL;
    }
    if (mgr != NULL) {
        free(mgr);
        mgr = NULL;
    }
}

u8 find_dir(const char* dir_name, i8 search_depth, struct resource_manager* mgr)
{
    if (search_depth < 0) {
        return DIR_NOT_FOUND;
    }
    char* new_dir = malloc(ALLOCATE_JOIN_PATH(mgr->cwd, dir_name));
    join_path(new_dir, mgr->cwd, dir_name);
    if (!dir_exists(new_dir)) {
        free(new_dir);
        move_path_down(mgr);
        return find_dir(dir_name, search_depth - 1, mgr);
    } else {
        free(mgr->cwd);
        mgr->cwd = new_dir;
    }
    return DIR_FOUND;
}

void move_path_down(struct resource_manager* mgr)
{
    size_t i = strlen(mgr->cwd) - 1;
    do {
        mgr->cwd[i] = '\0';
        --i;
    } while (mgr->cwd[i] != PLATFORM_PATH_SEPERATOR);
}

#if 0
int main(void) {
    struct resource_manager* mgr = create_resource_manager();
    delete_resource_manager(mgr);
}
#endif