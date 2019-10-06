/**
 * Get meaning or explain of macros in std c library headers, eg:
 *    int n = ENOMEM;
 *    printf("error `%s` means `%s`\n", errno_itoa(n, 0), errno_itoa(n, 1));
 * This will output:
 *    "error `ENOMEM` means `Cannot allocate memory`"
 */
#ifndef  __STD_CONSTANTS_DEBUG_HELPER__
#define  __STD_CONSTANTS_DEBUG_HELPER__
#include <signal.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif


const char* signal_itoa(int signum, int explain);

const char* errno_itoa(int errnum, int explain);


#ifdef __cplusplus
} // end extern "C"
#endif


#endif // __STD_CONSTANTS_DEBUG_HELPER__

