#ifndef HDR_PLATFORM_H
#define HDR_PLATFORM_H

#if defined(WIN32) || defined(WIN64) || defined(__MINGW32__)
#define PLATFORM_WINDOWS
#endif

#ifdef __linux__
#define PLATFORM_LINUX
#endif

#ifdef __APPLE__
#define PLATFORM_APPLE
#endif

#endif