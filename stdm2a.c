/**
 * Get meaning or explain of macros in std c library headers, eg:
 *    int n = ENOMEM;
 *    printf("error `%s` means %s!\n", errno_itoa(n, 0), errno_itoa(n, 1));
 * This will output:
 *    "error `ENOMEM` means Cannot allocate memory!"
 */
#include <stddef.h>
#include "stdm2a.h"


const char* signal_itoa(int signum, int explain)
{
    switch (signum) {
    case    SIGHUP: return explain ? "Hangup" : "SIGHUP";
    case    SIGINT: return explain ? "Interrupt" : "SIGINT";
    case   SIGQUIT: return explain ? "Quit" : "SIGQUIT";
    case    SIGILL: return explain ? "Illegal instruction" : "SIGILL";
    case   SIGTRAP: return explain ? "Trace trap" : "SIGTRAP";
    case   SIGABRT: return explain ? "Abort" : "SIGABRT";
    // case    SIGIOT: return explain ? "IOT trap" : "SIGIOT";
    case    SIGBUS: return explain ? "BUS error" : "SIGBUS";
    case    SIGFPE: return explain ? "Floating-point exception" : "SIGFPE";
    case   SIGKILL: return explain ? "Kill, unblockable" : "SIGKILL";
    case   SIGUSR1: return explain ? "User-defined signal 1" : "SIGUSR1";
    case   SIGSEGV: return explain ? "Segmentation violation" : "SIGSEGV";
    case   SIGUSR2: return explain ? "User-defined signal 2" : "SIGUSR2";
    case   SIGPIPE: return explain ? "Broken pipe" : "SIGPIPE";
    case   SIGALRM: return explain ? "Alarm clock" : "SIGALRM";
    case   SIGTERM: return explain ? "Termination" : "SIGTERM";
    case SIGSTKFLT: return explain ? "Signal 16 SIGSTKFLT: Stack fault" : "SIGSTKFLT";
    case   SIGCHLD: return explain ? "Child status has changed" : "SIGCHLD";
    // case    SIGCLD: return explain ? "Same as SIGCHLD" : "SIGCLD";
    case   SIGCONT: return explain ? "Continue" : "SIGCONT";
    case   SIGSTOP: return explain ? "Stop, unblockable" : "SIGSTOP";
    case   SIGTSTP: return explain ? "Keyboard stop" : "SIGTSTP";
    case   SIGTTIN: return explain ? "Background read from tty" : "SIGTTIN";
    case   SIGTTOU: return explain ? "Background write to tty" : "SIGTTOU";
    case    SIGURG: return explain ? "Urgent condition on socket" : "SIGURG";
    case   SIGXCPU: return explain ? "CPU limit exceeded" : "SIGXCPU";
    case   SIGXFSZ: return explain ? "File size limit exceeded" : "SIGXFSZ";
    case SIGVTALRM: return explain ? "Virtual alarm clock" : "SIGVTALRM";
    case   SIGPROF: return explain ? "Profiling alarm clock" : "SIGPROF";
    case  SIGWINCH: return explain ? "Window size change" : "SIGWINCH";
    case     SIGIO: return explain ? "I/O now possible" : "SIGIO";
    // case   SIGPOLL: return explain ? "Pollable event occurred" : "SIGPOLL";
    case    SIGPWR: return explain ? "Power failure restart" : "SIGPWR";
    case    SIGSYS: return explain ? "Bad system call" : "SIGSYS";
    default:
        return NULL;
    }
}


const char* errno_itoa(int errnum, int explain)
{
    switch (errnum) {
    case        EPERM:  return explain ? "Operation not permitted" : "EPERM";
    case       ENOENT:  return explain ? "No such file or directory" : "ENOENT";
    case        ESRCH:  return explain ? "No such process" : "ESRCH";
    case        EINTR:  return explain ? "Interrupted system call" : "EINTR";
    case          EIO:  return explain ? "Input/output error" : "EIO";
    case        ENXIO:  return explain ? "No such device or address" : "ENXIO";
    case        E2BIG:  return explain ? "Argument list too long" : "E2BIG";
    case      ENOEXEC:  return explain ? "Exec format error" : "ENOEXEC";
    case        EBADF:  return explain ? "Bad file descriptor" : "EBADF";
    case       ECHILD:  return explain ? "No child processes" : "ECHILD";
    case       EAGAIN:  return explain ? "Resource temporarily unavailable" : "EAGAIN";
    // case  EWOULDBLOCK:  return explain ? "Resource temporarily unavailable" : "EWOULDBLOCK";
    case       ENOMEM:  return explain ? "Cannot allocate memory" : "ENOMEM";
    case       EACCES:  return explain ? "Permission denied" : "EACCES";
    case       EFAULT:  return explain ? "Bad address" : "EFAULT";
    case      ENOTBLK:  return explain ? "Block device required" : "ENOTBLK";
    case        EBUSY:  return explain ? "Device or resource busy" : "EBUSY";
    case       EEXIST:  return explain ? "File exists" : "EEXIST";
    case        EXDEV:  return explain ? "Invalid cross-device link" : "EXDEV";
    case       ENODEV:  return explain ? "No such device" : "ENODEV";
    case      ENOTDIR:  return explain ? "Not a directory" : "ENOTDIR";
    case       EISDIR:  return explain ? "Is a directory" : "EISDIR";
    case       EINVAL:  return explain ? "Invalid argument" : "EINVAL";
    case       ENFILE:  return explain ? "Too many open files in system" : "ENFILE";
    case       EMFILE:  return explain ? "Too many open files" : "EMFILE";
    case       ENOTTY:  return explain ? "Inappropriate ioctl for device" : "ENOTTY";
    case      ETXTBSY:  return explain ? "Text file busy" : "ETXTBSY";
    case        EFBIG:  return explain ? "File too large" : "EFBIG";
    case       ENOSPC:  return explain ? "No space left on device" : "ENOSPC";
    case       ESPIPE:  return explain ? "Illegal seek" : "ESPIPE";
    case        EROFS:  return explain ? "Read-only file system" : "EROFS";
    case       EMLINK:  return explain ? "Too many links" : "EMLINK";
    case        EPIPE:  return explain ? "Broken pipe" : "EPIPE";
    case         EDOM:  return explain ? "Numerical argument out of domain" : "EDOM";
    case       ERANGE:  return explain ? "Numerical result out of range" : "ERANGE";
    case      EDEADLK:  return explain ? "Resource deadlock avoided" : "EDEADLK";
    // case    EDEADLOCK:  return explain ? "Resource deadlock avoided" : "EDEADLOCK";
    case ENAMETOOLONG:  return explain ? "File name too long" : "ENAMETOOLONG";
    case       ENOLCK:  return explain ? "No locks available" : "ENOLCK";
    case       ENOSYS:  return explain ? "Function not implemented" : "ENOSYS";
    case    ENOTEMPTY:  return explain ? "Directory not empty" : "ENOTEMPTY";
    case        ELOOP:  return explain ? "Too many levels of symbolic links" : "ELOOP";
    case       ENOMSG:  return explain ? "No message of desired type" : "ENOMSG";
    case        EIDRM:  return explain ? "Identifier removed" : "EIDRM";
    case       ECHRNG:  return explain ? "Channel number out of range" : "ECHRNG";
    case     EL2NSYNC:  return explain ? "Level 2 not synchronized" : "EL2NSYNC";
    case       EL3HLT:  return explain ? "Level 3 halted" : "EL3HLT";
    case       EL3RST:  return explain ? "Level 3 reset" : "EL3RST";
    case       ELNRNG:  return explain ? "Link number out of range" : "ELNRNG";
    case      EUNATCH:  return explain ? "Protocol driver not attached" : "EUNATCH";
    case       ENOCSI:  return explain ? "No CSI structure available" : "ENOCSI";
    case       EL2HLT:  return explain ? "Level 2 halted" : "EL2HLT";
    case        EBADE:  return explain ? "Invalid exchange" : "EBADE";
    case        EBADR:  return explain ? "Invalid request descriptor" : "EBADR";
    case       EXFULL:  return explain ? "Exchange full" : "EXFULL";
    case       ENOANO:  return explain ? "No anode" : "ENOANO";
    case      EBADRQC:  return explain ? "Invalid request code" : "EBADRQC";
    case      EBADSLT:  return explain ? "Invalid slot" : "EBADSLT";
    case       EBFONT:  return explain ? "Bad font file format" : "EBFONT";
    case       ENOSTR:  return explain ? "Device not a stream" : "ENOSTR";
    case      ENODATA:  return explain ? "No data available" : "ENODATA";
    case        ETIME:  return explain ? "Timer expired" : "ETIME";
    case        ENOSR:  return explain ? "Out of streams resources" : "ENOSR";
    case       ENONET:  return explain ? "Machine is not on the network" : "ENONET";
    case       ENOPKG:  return explain ? "Package not installed" : "ENOPKG";
    case      EREMOTE:  return explain ? "Object is remote" : "EREMOTE";
    case      ENOLINK:  return explain ? "Link has been severed" : "ENOLINK";
    case         EADV:  return explain ? "Advertise error" : "EADV";
    case       ESRMNT:  return explain ? "Srmount error" : "ESRMNT";
    case        ECOMM:  return explain ? "Communication error on send" : "ECOMM";
    case       EPROTO:  return explain ? "Protocol error" : "EPROTO";
    case    EMULTIHOP:  return explain ? "Multihop attempted" : "EMULTIHOP";
    case      EDOTDOT:  return explain ? "RFS specific error" : "EDOTDOT";
    case      EBADMSG:  return explain ? "Bad message" : "EBADMSG";
    case    EOVERFLOW:  return explain ? "Value too large for defined data type" : "EOVERFLOW";
    case     ENOTUNIQ:  return explain ? "Name not unique on network" : "ENOTUNIQ";
    case       EBADFD:  return explain ? "File descriptor in bad state" : "EBADFD";
    case      EREMCHG:  return explain ? "Remote address changed" : "EREMCHG";
    case      ELIBACC:  return explain ? "Can not access a needed shared library" : "ELIBACC";
    case      ELIBBAD:  return explain ? "Accessing a corrupted shared library" : "ELIBBAD";
    case      ELIBSCN:  return explain ? ".lib section in a.out corrupted" : "ELIBSCN";
    case      ELIBMAX:  return explain ? "Attempting to link in too many shared libraries" : "ELIBMAX";
    case     ELIBEXEC:  return explain ? "Cannot exec a shared library directly" : "ELIBEXEC";
    case       EILSEQ:  return explain ? "Invalid or incomplete multibyte or wide character" : "EILSEQ";
    case     ERESTART:  return explain ? "Interrupted system call should be restarted" : "ERESTART";
    case     ESTRPIPE:  return explain ? "Streams pipe error" : "ESTRPIPE";
    case       EUSERS:  return explain ? "Too many users" : "EUSERS";
    case     ENOTSOCK:  return explain ? "Socket operation on non-socket" : "ENOTSOCK";
    case EDESTADDRREQ:  return explain ? "Destination address required" : "EDESTADDRREQ";
    case     EMSGSIZE:  return explain ? "Message too long" : "EMSGSIZE";
    case   EPROTOTYPE:  return explain ? "Protocol wrong type for socket" : "EPROTOTYPE";
    case  ENOPROTOOPT:  return explain ? "Protocol not available" : "ENOPROTOOPT";
    case EPROTONOSUPPORT: return explain ? "Protocol not supported" : "EPROTONOSUPPORT";
    case ESOCKTNOSUPPORT: return explain ? "Socket type not supported" : "ESOCKTNOSUPPORT";
    case   EOPNOTSUPP:  return explain ? "Operation not supported" : "EOPNOTSUPP";
    // case      ENOTSUP:  return explain ? "Operation not supported" : "ENOTSUP";
    case EPFNOSUPPORT:  return explain ? "Protocol family not supported" : "EPFNOSUPPORT";
    case EAFNOSUPPORT:  return explain ? "Address family not supported by protocol" : "EAFNOSUPPORT";
    case   EADDRINUSE:  return explain ? "Address already in use" : "EADDRINUSE";
    case EADDRNOTAVAIL: return explain ? "Cannot assign requested address" : "EADDRNOTAVAIL";
    case     ENETDOWN:  return explain ? "Network is down" : "ENETDOWN";
    case  ENETUNREACH:  return explain ? "Network is unreachable" : "ENETUNREACH";
    case    ENETRESET:  return explain ? "Network dropped connection on reset" : "ENETRESET";
    case ECONNABORTED:  return explain ? "Software caused connection abort" : "ECONNABORTED";
    case   ECONNRESET:  return explain ? "Connection reset by peer" : "ECONNRESET";
    case      ENOBUFS:  return explain ? "No buffer space available" : "ENOBUFS";
    case      EISCONN:  return explain ? "Transport endpoint is already connected" : "EISCONN";
    case     ENOTCONN:  return explain ? "Transport endpoint is not connected" : "ENOTCONN";
    case    ESHUTDOWN:  return explain ? "Cannot send after transport endpoint shutdown" : "ESHUTDOWN";
    case ETOOMANYREFS:  return explain ? "Too many references: cannot splice" : "ETOOMANYREFS";
    case    ETIMEDOUT:  return explain ? "Connection timed out" : "ETIMEDOUT";
    case ECONNREFUSED:  return explain ? "Connection refused" : "ECONNREFUSED";
    case    EHOSTDOWN:  return explain ? "Host is down" : "EHOSTDOWN";
    case EHOSTUNREACH:  return explain ? "No route to host" : "EHOSTUNREACH";
    case     EALREADY:  return explain ? "Operation already in progress" : "EALREADY";
    case  EINPROGRESS:  return explain ? "Operation now in progress" : "EINPROGRESS";
    case       ESTALE:  return explain ? "Stale file handle" : "ESTALE";
    case      EUCLEAN:  return explain ? "Structure needs cleaning" : "EUCLEAN";
    case      ENOTNAM:  return explain ? "Not a XENIX named type file" : "ENOTNAM";
    case      ENAVAIL:  return explain ? "No XENIX semaphores available" : "ENAVAIL";
    case       EISNAM:  return explain ? "Is a named type file" : "EISNAM";
    case    EREMOTEIO:  return explain ? "Remote I/O error" : "EREMOTEIO";
    case       EDQUOT:  return explain ? "Disk quota exceeded" : "EDQUOT";
    case    ENOMEDIUM:  return explain ? "No medium found" : "ENOMEDIUM";
    case  EMEDIUMTYPE:  return explain ? "Wrong medium type" : "EMEDIUMTYPE";
    case    ECANCELED:  return explain ? "Operation canceled" : "ECANCELED";
    case       ENOKEY:  return explain ? "Required key not available" : "ENOKEY";
    case  EKEYEXPIRED:  return explain ? "Key has expired" : "EKEYEXPIRED";
    case  EKEYREVOKED:  return explain ? "Key has been revoked" : "EKEYREVOKED";
    case EKEYREJECTED:  return explain ? "Key was rejected by service" : "EKEYREJECTED";
    case   EOWNERDEAD:  return explain ? "Owner died" : "EOWNERDEAD";
    case ENOTRECOVERABLE: return explain ? "State not recoverable" : "ENOTRECOVERABLE";
    case      ERFKILL:  return explain ? "Operation not possible due to RF-kill" : "ERFKILL";
    case    EHWPOISON:  return explain ? "Memory page has hardware error" : "EHWPOISON";
    default:
        return NULL;
    }
}






