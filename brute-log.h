/************************************************************************************************
 *  __                                          __                                              *
 * |  |                         __             |  |                                             *
 * |  |____  _______ __   __  _|  |_   ____    |  |      ______   ______                        *
 * |   __  \ |  ___/ | | | | /_    _\ / __  \  |  |     /  __  \ /  __  \                       *
 * |  |__|  || |     | |_| |   |  |_ |  ____/  |  |____ | |__| | | |__| |                       *
 * |_______/ |_|     \_____/   |___/  \____/   |______/ \______/ \____  |                       *
 *                                                                \_____/ithub.com/alexloser    *
 *                                                                                              *
 * A brute and crude logging/printing/debugging tool for C/C++                                  *
 * Only works on linux system with GCC4.8+ compiler                                             *
 * No functions or global variables. Only macros in one header file                             *
 * See https://github.com/alexloser/brute-log for more details                                  *
 *                                                                                              *
 ************************************************************************************************/
#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#ifndef BRUTE_SNIPPET_BEGIN
#define BRUTE_SNIPPET_BEGIN ({
#endif
#ifndef BRUTE_SNIPPET_END
#define BRUTE_SNIPPET_END   })
#endif


#ifndef BRUTE_SRC_LOCATE
#define BRUTE_SRC_LOCATE
#define BRUTE_SRC_POS    __FILE__,__LINE__
#define BRUTE_SRC_POSEX  __FILE__,__LINE__,__FUNCTION__
#endif


// Can be changed by user
#ifndef BRUTE_OSTREAM
#define BRUTE_OSTREAM stderr
#endif


#ifndef BRUTE_BUILTINS
#define BRUTE_BUILTINS
#define BRUTE_FASTER_SNPRINTF __builtin_snprintf
#define BRUTE_FASTER_STRFTIME __builtin_strftime
#define BRUTE_FASTEST_FPRINTF __builtin_fprintf
#define BRUTE_SAFER_LOCALTIME localtime_r
#endif


// Do not use this in user's code.
#ifndef  __BRUTE_GET_DT__
#define  __BRUTE_GET_DT__(__varbuf__)                                         \
    char __varbuf__[32] = { 0 };                                              \
    BRUTE_SNIPPET_BEGIN                                                       \
    struct tm       BRUTE_GET_DT_var_tm;                                      \
    struct timeval  BRUTE_GET_DT_var_timeval;                                       \
    (void)gettimeofday(&BRUTE_GET_DT_var_timeval, NULL);                            \
    BRUTE_SAFER_LOCALTIME(&BRUTE_GET_DT_var_timeval.tv_sec, &BRUTE_GET_DT_var_tm);  \
    BRUTE_FASTER_STRFTIME(__varbuf__, 20, "%m-%d %T",  &BRUTE_GET_DT_var_tm);       \
    BRUTE_FASTER_SNPRINTF(__varbuf__+14, 10, ".%05ld", BRUTE_GET_DT_var_timeval.tv_usec/10); \
    BRUTE_SNIPPET_END
#endif //__BRUTE_GET_DT__


#ifndef BRUTE_MAX_FMT
#define BRUTE_MAX_FMT (128)
#endif


//////////////////////////////////////////////////////////////////////////////
/////////// Debug macro defines, can close if BRUTE_NDEBUG defined ///////////
//////////////////////////////////////////////////////////////////////////////
#ifdef  BRUTE_NDEBUG

#define BRUTE_DEBUG_V0(fmt, ...)
#define BRUTE_DEBUG_V1(fmt, ...)
#define BRUTE_DEBUG_V2(fmt, ...)
#define BRUTE_DEBUG_V3(fmt, ...)
#define BRUTE_DEBUG_V4(fmt, ...)
#define BRUTE_DEBUG_V5(fmt, ...)
#define BRUTE_DEBUG(fmt, ...)

#else

#ifndef BRUTE_DEBUG_MACROS
#define BRUTE_DEBUG_MACROS

#define BRUTE_DEBUG_V0(fmt, ...) \
BRUTE_SNIPPET_BEGIN              \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("[DEBUG] " fmt "\n"), ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_DEBUG_V1(fmt, ...) \
BRUTE_SNIPPET_BEGIN              \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("[DEBUG] %s> " fmt "\n"), __FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_DEBUG_V2(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [DEBUG] %s> " fmt "\n"), __brtlg_dt__, __FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_DEBUG_V3(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [DEBUG] %s> " fmt "\n"), __brtlg_dt__, __PRETTY_FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_DEBUG_V4(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [DEBUG] %s:%d> " fmt "\n"), __brtlg_dt__, BRUTE_SRC_POS, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_DEBUG_V5(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [DEBUG] %s:%d %s> " fmt "\n"), __brtlg_dt__, BRUTE_SRC_POSEX, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_DEBUG(fmt, ...)       \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [DEBUG] " fmt "\n"), __brtlg_dt__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#endif // BRUTE_DEBUG_MACROS
#endif // BRUTE_NDEBUG


//////////////////////////////////////////////////////////////////////////////
////////////////// Logging macro defines, can not be closed //////////////////
//////////////////////////////////////////////////////////////////////////////
#ifndef BRUTE_LOG_MACROS
#define BRUTE_LOG_MACROS

/////////////////////////////////// INFO /////////////////////////////////////
#define BRUTE_INFO_V0(fmt, ...)     \
BRUTE_SNIPPET_BEGIN                 \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("[INFO] " fmt "\n"), ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_INFO_V1(fmt, ...)     \
BRUTE_SNIPPET_BEGIN                 \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("[INFO] %s> " fmt "\n"), __FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_INFO_V2(fmt, ...)     \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [INFO] %s> " fmt "\n"), __brtlg_dt__, __FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_INFO_V3(fmt, ...)     \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [INFO] %s> " fmt "\n"), __brtlg_dt__, __PRETTY_FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_INFO_V4(fmt, ...)     \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [INFO] %s:%d> " fmt "\n"), __brtlg_dt__, BRUTE_SRC_POS, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_INFO_V5(fmt, ...)     \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [INFO] %s:%d %s> " fmt "\n"), __brtlg_dt__, BRUTE_SRC_POSEX, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_INFO(fmt, ...)        \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [INFO] " fmt "\n"), __brtlg_dt__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END


/////////////////////////////////// WARN /////////////////////////////////////
#define BRUTE_WARN_V0(fmt, ...)     \
BRUTE_SNIPPET_BEGIN                 \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("[WARN] " fmt "\n"), ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_WARN_V1(fmt, ...)     \
BRUTE_SNIPPET_BEGIN                 \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("[WARN] %s> " fmt "\n"), __FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_WARN_V2(fmt, ...)     \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [WARN] %s> " fmt "\n"), __brtlg_dt__, __FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_WARN_V3(fmt, ...)     \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [WARN] %s> " fmt "\n"), __brtlg_dt__, __PRETTY_FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_WARN_V4(fmt, ...)     \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [WARN] %s:%d> " fmt "\n"), __brtlg_dt__, BRUTE_SRC_POS, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_WARN_V5(fmt, ...)     \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [WARN] %s:%d %s> " fmt "\n"), __brtlg_dt__, BRUTE_SRC_POSEX, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_WARN(fmt, ...)        \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [WARN] " fmt "\n"), __brtlg_dt__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END


/////////////////////////////////// ERROR ////////////////////////////////////
#define BRUTE_ERROR_V0(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("[ERROR] " fmt "\n"), ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_ERROR_V1(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("[ERROR] %s> " fmt "\n"), __FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_ERROR_V2(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [ERROR] %s> " fmt "\n"), __brtlg_dt__, __FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_ERROR_V3(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [ERROR] %s> " fmt "\n"), __brtlg_dt__, __PRETTY_FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_ERROR_V4(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [ERROR] %s:%d> " fmt "\n"), __brtlg_dt__, BRUTE_SRC_POS, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_ERROR_V5(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [ERROR] %s:%d %s> " fmt "\n"), __brtlg_dt__, BRUTE_SRC_POSEX, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_ERROR(fmt, ...)       \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [ERROR] " fmt "\n"), __brtlg_dt__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END


/////////////////////////////////// FATAL /////////////////////////////////////
#define BRUTE_FATAL_V0(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("[FATAL] " fmt "\n"), ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_FATAL_V1(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("[FATAL] %s> " fmt "\n"), __FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_FATAL_V2(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [FATAL] %s> " fmt "\n"), __brtlg_dt__, __FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_FATAL_V3(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [FATAL] %s> " fmt "\n"), __brtlg_dt__, __PRETTY_FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_FATAL_V4(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [FATAL] %s:%d> " fmt "\n"), __brtlg_dt__, BRUTE_SRC_POS, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_FATAL_V5(fmt, ...)    \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [FATAL] %s:%d %s> " fmt "\n"), __brtlg_dt__, BRUTE_SRC_POSEX, ##__VA_ARGS__); \
BRUTE_SNIPPET_END

#define BRUTE_FATAL(fmt, ...)       \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, ("%s [FATAL] " fmt "\n"), __brtlg_dt__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END


////////////////////////////////// Custom ////////////////////////////////////
#ifndef BRUTE_LOG_V0
#define BRUTE_LOG_V0(level, fmt, ...)   \
BRUTE_SNIPPET_BEGIN                     \
    char __crdlg_vfmt__[BRUTE_MAX_FMT<<1];           \
    strcat(strcat(strcpy(__crdlg_vfmt__, ("[" #level "] ")), (fmt)), "\n"); \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, __crdlg_vfmt__, ##__VA_ARGS__);    \
BRUTE_SNIPPET_END
#endif//BRUTE_LOG_V0

#ifndef BRUTE_LOG_V1
#define BRUTE_LOG_V1(level, fmt, ...)   \
BRUTE_SNIPPET_BEGIN                     \
    char __crdlg_vfmt__[BRUTE_MAX_FMT<<1];           \
    strcat(strcat(strcpy(__crdlg_vfmt__, ("[" #level "] %s> ")), (fmt)), "\n");        \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, __crdlg_vfmt__, __FUNCTION__, ##__VA_ARGS__);  \
BRUTE_SNIPPET_END
#endif//BRUTE_LOG_V1

#ifndef BRUTE_LOG_V2
#define BRUTE_LOG_V2(level, fmt, ...)   \
BRUTE_SNIPPET_BEGIN                     \
    __BRUTE_GET_DT__(__brtlg_dt__);     \
    char __crdlg_vfmt__[BRUTE_MAX_FMT<<1]; \
    strcat(strcat(strcpy(__crdlg_vfmt__, ("%s [" #level "] %s> ")), (fmt)), "\n");                  \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, __crdlg_vfmt__, __brtlg_dt__, __FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END
#endif//BRUTE_LOG_V2

#ifndef BRUTE_LOG_V3
#define BRUTE_LOG_V3(level, fmt, ...)   \
BRUTE_SNIPPET_BEGIN                     \
    __BRUTE_GET_DT__(__brtlg_dt__);     \
    char __crdlg_vfmt__[BRUTE_MAX_FMT<<1]; \
    strcat(strcat(strcpy(__crdlg_vfmt__, ("%s [" #level "] %s> ")), (fmt)), "\n");                         \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, __crdlg_vfmt__, __brtlg_dt__, __PRETTY_FUNCTION__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END
#endif//BRUTE_LOG_V3

#ifndef BRUTE_LOG_V4
#define BRUTE_LOG_V4(level, fmt, ...)   \
BRUTE_SNIPPET_BEGIN                     \
    __BRUTE_GET_DT__(__brtlg_dt__);     \
    char __crdlg_vfmt__[BRUTE_MAX_FMT<<1];           \
    strcat(strcat(strcpy(__crdlg_vfmt__, ("%s [" #level "] %s:%d> ")), (fmt)), "\n");           \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, __crdlg_vfmt__, __brtlg_dt__, BRUTE_SRC_POS, ##__VA_ARGS__); \
BRUTE_SNIPPET_END
#endif//BRUTE_LOG_V4

#ifndef BRUTE_LOG_V5
#define BRUTE_LOG_V5(level, fmt, ...)   \
BRUTE_SNIPPET_BEGIN                     \
    __BRUTE_GET_DT__(__brtlg_dt__);     \
    char __crdlg_vfmt__[BRUTE_MAX_FMT<<1];           \
    strcat(strcat(strcpy(__crdlg_vfmt__, ("%s [" #level "] %s:%d %s> ")), (fmt)), "\n");             \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, __crdlg_vfmt__, __brtlg_dt__, BRUTE_SRC_POSEX, ##__VA_ARGS__); \
BRUTE_SNIPPET_END
#endif//BRUTE_LOG_V5

#ifndef BRUTE_LOG
#define BRUTE_LOG(level, fmt, ...)  \
BRUTE_SNIPPET_BEGIN                 \
    __BRUTE_GET_DT__(__brtlg_dt__); \
    char __crdlg_vfmt__[BRUTE_MAX_FMT<<1];                                             \
    strcat(strcat(strcpy(__crdlg_vfmt__, ("%s [" #level "] ")), (fmt)), "\n");         \
    BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, __crdlg_vfmt__, __brtlg_dt__, ##__VA_ARGS__); \
BRUTE_SNIPPET_END
#endif//BRUTE_LOG


#endif // BRUTE_LOG_MACROS
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//////////////////////// Printing utils and helpers //////////////////////////
//////////////////////////////////////////////////////////////////////////////
#ifndef BRUTE_LF
#define BRUTE_LF() fputs("\n", BRUTE_OSTREAM)
#define BRUTE_LINEFEED BRUTE_LF
#endif


// Always used for output streams.
#ifndef BRUTE_FFLUSH
#define BRUTE_FFLUSH() fflush(BRUTE_OSTREAM)
#endif

// Do not use this if you don't understand what it means.
#ifndef BRUTE_BUFFERING_MODE
#define BRUTE_FULL_BUFFERED (_IOFBF)
#define BRUTE_LINE_BUFFERED (_IOLBF)
#define BRUTE_NONE_BUFFERED (_IONBF)
#endif

// Do not use this if you don't understand what it means.
#ifndef BRUTE_SET_BUFFERING_METHOD
#define BRUTE_SET_BUFFERING_METHOD(buf, size, mode) \
BRUTE_SNIPPET_BEGIN \
    switch (mode) { \
        case BRUTE_FULL_BUFFERED: \
        case BRUTE_LINE_BUFFERED: \
            setvbuf(BRUTE_OSTREAM, buf, mode, size); \
            break; \
        case BRUTE_NONE_BUFFERED: \
            BRUTE_WARN_V2("Using no-buffering mode will lead to worse performance!"); \
            setvbuf(BRUTE_OSTREAM, buf, mode, size); \
            break; \
        default: \
            BRUTE_ERROR_V2("Wrong buffering mode for std::setvbuf"); \
            break; \
    } \
BRUTE_SNIPPET_END
#endif // BRUTE_SET_BUFFERING_METHOD

// Nothing ...
#ifndef BRUTE_FPRINT
#define BRUTE_FPRINT(fmt, ...)   BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, (fmt), ##__VA_ARGS__)
#endif
#ifndef BRUTE_FPRINTLN
#define BRUTE_FPRINTLN(fmt, ...) BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, (fmt "\n"), ##__VA_ARGS__)
#endif

#ifndef BRUTE_PRINT
#define BRUTE_PRINT(cstr)   BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, "%s", (cstr))
#endif
#ifndef BRUTE_PRINTLN
#define BRUTE_PRINTLN(cstr) BRUTE_FASTEST_FPRINTF(BRUTE_OSTREAM, "%s\n", (cstr))
#endif


#ifndef BRUTE_ASFORMAT
#define BRUTE_ASFORMAT_BEGIN(output, format, ...) \
do { \
    char*  output = NULL; \
    size_t output##_size = (size_t)__asprintf(&output, format, ##__VA_ARGS__); \
    if (!output) output##_size = 0;
// User's code here ...
#define BRUTE_ASFORMAT_END(output) \
    if (output) free(output); \
} while(0)
#endif//BRUTE_ASFORMAT


#ifndef BRUTE_CLOSE
#define BRUTE_CLOSE()           \
BRUTE_SNIPPET_BEGIN             \
    if (!ferror(stdout))        \
        fflush(stdout);         \
    if (!ferror(stderr))        \
        fflush(stderr);         \
    if (BRUTE_OSTREAM) {        \
        fflush(BRUTE_OSTREAM);  \
        fclose(BRUTE_OSTREAM);  \
    }                           \
BRUTE_SNIPPET_END
#endif//BRUTE_CLOSE
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
////////////////////// Debugging(but can not be closed) //////////////////////
//////////////////////////////////////////////////////////////////////////////
#ifndef  BRUTE_ASSERT
#define  BRUTE_ASSERT(expr, ...) \
if (!(expr)) { \
    fprintf(BRUTE_OSTREAM, "[FATAL] %s:%d %s> Assertion: `" #expr "` failed!", BRUTE_SRC_POS); \
    __VA_ARGS__; \
    fflush(BRUTE_OSTREAM); \
    fclose(BRUTE_OSTREAM); \
    abort(); \
}
#endif// BRUTE_ASSERT

#ifndef  BRUTE_ASSERT_C
#define  BRUTE_ASSERT_C(expr, ...) \
if (!(expr)) { \
    BRUTE_ERROR_V4("Assertion: `" #expr "` failed!"); \
    __VA_ARGS__; \
}
#endif// BRUTE_ASSERT_C


#if    __cplusplus >= 201103L
#ifndef  BRUTE_STATIC_ASSERT
#define  BRUTE_STATIC_ASSERT(...) static_assert((__VA_ARGS__), #__VA_ARGS__)
#endif //BRUTE_STATIC_ASSERT
#endif //c++11

#ifndef  BRUTE_CHECK_PTR
#define  BRUTE_CHECK_PTR(ptr, ...)                      \
if (((void*)0) == (ptr)) {                              \
    BRUTE_ERROR_V4("Arg `" #ptr "` is null or zero!");  \
    __VA_ARGS__;                                        \
}
#endif// BRUTE_CHECK_PTR


// Print info every `interval` steps, when `total`=10000, `interval`=500:
// 500/10000   0.50%
// ...
// 7500/10000  75.00%
// 8000/10000  80.00%
// ...
// 10000/10000 100.0%
#ifndef  BRUTE_PROGRESS_RATE
#define  BRUTE_PROGRESS_RATE(current, total, interval, fmt, ...)                \
BRUTE_SNIPPET_BEGIN                                                             \
    __BRUTE_GET_DT__(__brtlg_dt__);                                             \
    if (((current) && !((current) % (interval))) || ((current) == (total))) {   \
        fprintf(stderr, "%s [INFO] %s> %zu/%zu %2.2f%% " fmt "\n",             \
                __brtlg_dt__, __FUNCTION__, size_t(current), size_t(total), ((current)*100.0/(total)), ##__VA_ARGS__); \
    } \
BRUTE_SNIPPET_END
#endif// BRUTE_PROGRESS_RATE


#ifndef BRUTE_EXIT
#define BRUTE_EXIT(fmt, ...)                \
BRUTE_SNIPPET_BEGIN                         \
    BRUTE_LOG(EXIT, fmt, ##__VA_ARGS__);    \
    BRUTE_CLOSE();                          \
    exit(0);                                \
BRUTE_SNIPPET_END
#endif//BRUTE_EXIT

#ifndef BRUTE_EXIT_IF
#define BRUTE_EXIT_IF(expr, fmt, ...)        \
BRUTE_SNIPPET_BEGIN                          \
    if (expr) {                              \
        BRUTE_LOG(EXIT, fmt, ##__VA_ARGS__); \
        BRUTE_CLOSE();                       \
        exit(0);                             \
    }                                        \
BRUTE_SNIPPET_END
#endif//BRUTE_EXIT_IF


#ifndef BRUTE_FATAL_EXIT
#define BRUTE_FATAL_EXIT(ecode, fmt, ...)        \
BRUTE_SNIPPET_BEGIN                              \
    BRUTE_LOG(FATAL] [EXIT, fmt, ##__VA_ARGS__); \
    BRUTE_CLOSE();                               \
    quick_exit(ecode);                           \
BRUTE_SNIPPET_END
#endif//BRUTE_FATAL_EXIT

#ifndef BRUTE_FATAL_EXIT_IF
#define BRUTE_FATAL_EXIT_IF(expr, ecode, fmt, ...)  \
BRUTE_SNIPPET_BEGIN                                 \
    if (expr) {                                     \
        BRUTE_LOG(FATAL] [EXIT, fmt, ##__VA_ARGS__);\
        BRUTE_CLOSE();                              \
        quick_exit(ecode);                          \
    }                                               \
BRUTE_SNIPPET_END
#endif//BRUTE_FATAL_EXIT_IF

#ifndef BRUTE_FATAL_ABORT
#define BRUTE_FATAL_ABORT(fmt, ...)              \
BRUTE_SNIPPET_BEGIN                              \
    BRUTE_LOG(FATAL] [ABORT, fmt, ##__VA_ARGS__);\
    BRUTE_CLOSE();                               \
    abort();                                     \
BRUTE_SNIPPET_END
#endif//BRUTE_FATAL_QUICK_EXIT



///////////////////////////////////////////////////////////////////////////////


