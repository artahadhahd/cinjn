#ifndef HDR_UTILS_H
#define HDR_UTILS_H
#include <platform.h>
#include <utils/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifdef PLATFORM_WINDOWS
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <tchar.h>
#endif

#ifndef PLATFORM_PATH_SEPERATOR
#ifdef PLATFORM_WINDOWS
#define PLATFORM_PATH_SEPERATOR '\\'
#else
#define PLATFORM_PATH_SEPERATOR '/'
#endif
#endif // PLATFORM_PATH_SEPERATOR

#ifndef JOIN_PATH
#ifdef PLATFORM_WINDOWS
#define JOIN_PATH(s1, s2) s1 "\\" s2
#else
#define JOIN_PATH(s1, s2) s1 "/" s2
#endif
#endif // PLATFORM_PATH_SEPERATOR

#define ALLOCATE_JOIN_PATH(path1, path2) (strlen(path1) + strlen(path2) + 2)


/** 
 * @brief read a file from `path`
 * @return `NULL` on failure, file's contents on success - make sure to `free()`
*/
char* read_file(const char* path);
void join_path(char* destination, const char* path, const char* other);
bool dir_exists(char* path);
#endif