#include <utils/fs.h>

char* read_file(const char* path) {
    FILE* fp = fopen(path, "rb");
    if (!fp) {
        LOG(path, LOG_WARNING);
        LOG("^^^^ couldn't find file", LOG_WARNING);
        return NULL;
    }
    if (fseek(fp, 0, SEEK_END) != 0) {
        LOG(path, LOG_WARNING);
        LOG("^^^^ fseek failed", LOG_WARNING);
    }
    long fsize = ftell(fp);
    rewind(fp);
    char* buffer = (char*)malloc(fsize + 1);
    if (!buffer) {
        LOG(path, LOG_WARNING);
        LOG("^^^^ couldn't allocate enough memory to read this file", LOG_WARNING);
        return NULL;
    }
    fread(buffer, fsize, 1, fp);
    fclose(fp);
    buffer[fsize] = '\0'; // this is actually required
    return buffer;
}

#ifdef PLATFORM_WINDOWS
// On windows, the compiler complains because we use strncpy
// but to use the safer functions, that means we would need
// cross-platform strncpy, strncpy etc.
// which is just too much work, so we disable the warnings for that.
#pragma warning(disable:4996)
#endif
void join_path(char* destination, const char* path1, const char* path2)
{
    size_t root_size = strlen(path1);
    size_t other_size = strlen(path2);
    if (path1 == NULL && path2 == NULL) {
        strncpy(destination, "", 1);
    } else if (path2 == NULL || other_size == 0) {
        strncpy(destination, path1, root_size + 1);
    } else if (path1 == NULL || root_size == 0) {
        strncpy(destination, path2, other_size + 1);
    } else {
#ifdef PLATFORM_WINDOWS
        const char* directory_separator = "\\";
#else
        const char* directory_separator = "/";
#endif
        const char* last_char = path1 + (root_size - 1);
        bool append_directory_separator = strcmp(last_char, directory_separator) != 0;
        strncpy(destination, path1, root_size + 1);
        if(append_directory_separator) {
            strncat(destination, directory_separator, strlen(directory_separator) + 1);
        }
        strncat(destination, path2, other_size + 1);
    }
}

bool dir_exists(char* path)
{
#ifdef PLATFORM_WINDOWS
    if (_taccess_s(path, 0) == 0) {
        struct _stat sts;
        _tstat(path, &sts);
        return (sts.st_mode & S_IFDIR) != 0;
    }
    return false;
#endif
    return false;
}
#ifdef PLATFORM_WINDOWS
#pragma warning(default:4996)
#endif