#include "utils/log.h"

u8 LOG_ERRORS = 0;

void log_msg(const char* msg, enum log_mode_t log_mode, size_t line, const char* file) {
    switch (log_mode) {
    case LOG_WARNING:
        printf("warning: ");
        break;
    case LOG_ERROR:
        LOG_ERRORS++;
        printf("fatal runtime error: ");
        break;
    }
    fprintf(stderr, "\033[0;%dm%s:%zu: %s\n\033[0;37m", log_mode, file, line, msg);
}


#if 0
// tests

int main(void) {
    LOG("INFO", LOG_INFO);
    LOG("WARNING", LOG_WARNING);
    LOG("ERROR", LOG_ERROR);
    return 0;
}
#endif