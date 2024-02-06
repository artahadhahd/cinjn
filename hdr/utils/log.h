#ifndef INJN_LOG_H
#define INJN_LOG_H
#include <types.h>

#include <stddef.h>
#include <stdio.h>

extern u8 LOG_ERRORS;

enum log_mode_t {
    LOG_ERROR = 31,
    LOG_WARNING = 35,
    LOG_INFO = 36,
    LOG_SIMPLE = 37
};

void log_msg(const char*, enum log_mode_t, size_t, const char*);

#define LOG(c, m) log_msg(c, m, __LINE__, __FILE__)

#endif