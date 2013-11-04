#ifndef __ITP_COM_ERROR_CODE_H__
#define __ITP_COM_ERROR_CODE_H__

//////////////  These error code value is compatible with socket standard  //////////////
#ifdef WIN32
	#define DJ_EINTR             10004     // Interrupted system call
	#define DJ_EBADF             10009     // Bad file number
	#define DJ_EACCES            10013     // Permission denied
	#define DJ_EFAULT            10014     // Bad address
	#define DJ_EINVAL            10022     // Invalid argument
	#define DJ_EMFILE            10024     // Too many open files
	#define DJ_EWOULDBLOCK       10035     // Resource temporarily unavailable
	#define DJ_EINPROGRESS       10036     // Operation now in progress
	#define DJ_EALREADY          10037     // Operation already in progress
	#define DJ_ENOTSOCK          10038     // Socket operation on nonsocket
	#define DJ_EDESTADDRREQ      10039     // Destination address required
	#define DJ_EMSGSIZE          10040     // Message too long
	#define DJ_EPROTOTYPE        10041     // Protocol wrong type for socket
	#define DJ_ENOPROTOOPT       10042     // Bad protocol option
	#define DJ_EPROTONOSUPPORT   10043     // Protocol not supported
	#define DJ_ESOCKTNOSUPPORT   10044     // Socket type not supported
	#define DJ_EOPNOTSUPPORT     10045     // Operation not supported on transport endpoint
	#define DJ_EPFNOSUPPORT      10046     // Protocol family not supported
	#define DJ_EAFNOSUPPORT      10047 	   // Address family not supported by protocol family
	#define DJ_EADDRINUSE        10048     // Address already in use
	#define DJ_EADDRNOTAVAIL     10049     // Cannot assign requested address
	#define DJ_ENETDOWN          10050     // Network is down
	#define DJ_ENETUNREACH       10051     // Network is unreachable
	#define DJ_ENETRESET         10052     // Network dropped connection on reset
	#define DJ_ECONNABORTED      10053     // Software caused connection abort
	#define DJ_ECONNRESET        10054     // Connection reset by peer
	#define DJ_ENOBUFS           10055     // No buffer space available
	#define DJ_EISCONN           10056     // Socket is already connected
	#define DJ_ENOTCONN          10057     // Socket is not connected
	#define DJ_ESHUTDOWN         10058     // Cannot send after socket shutdown
	#define DJ_ETIMEDOUT         10060     // Connection timed out
	#define DJ_ECONNREFUSED      10061     // Connection refused
	#define DJ_EHOSTDOWN         10064     // Host is down
	#define DJ_EHOSTUNREACH      10065     // No route to host
#else
	#define DJ_EINTR             4         // Interrupted system call
	#define DJ_EBADF             9         // Bad file number
	#define DJ_EACCES            13        // Permission denied
	#define DJ_EFAULT            14        // Bad address
	#define DJ_EINVAL            22        // Invalid argument
	#define DJ_EMFILE            24        // Too many open files
	#define DJ_EWOULDBLOCK       11        // Resource temporarily unavailable
	#define DJ_EINPROGRESS       115       // Operation now in progress
	#define DJ_EALREADY          114       // Operation already in progress
	#define DJ_ENOTSOCK          88        // Socket operation on nonsocket
	#define DJ_EDESTADDRREQ      89        // Destination address required
	#define DJ_EMSGSIZE          90        // Message too long
	#define DJ_EPROTOTYPE        91        // Protocol wrong type for socket
	#define DJ_ENOPROTOOPT       92        // Bad protocol option
	#define DJ_EPROTONOSUPPORT   93        // Protocol not supported	
	#define DJ_ESOCKTNOSUPPORT   94        // Socket type not supported
	#define DJ_EOPNOTSUPPORT     95        // Operation not supported on transport endpoint
	#define DJ_EPFNOSUPPORT      96        // Protocol family not supported
	#define DJ_EAFNOSUPPORT      97 	     // Address family not supported by protocol family
	#define DJ_EADDRINUSE        98        // Address already in use
	#define DJ_EADDRNOTAVAIL     99        // Cannot assign requested address
	#define DJ_ENETDOWN          100       // Network is down
	#define DJ_ENETUNREACH       101       // Network is unreachable
	#define DJ_ENETRESET         102       // Network dropped connection on reset
	#define DJ_ECONNABORTED      103       // Software caused connection abort
	#define DJ_ECONNRESET        104       // Connection reset by peer
	#define DJ_ENOBUFS           105       // No buffer space available
	#define DJ_EISCONN           106       // Socket is already connected
	#define DJ_ENOTCONN          107       // Socket is not connected
	#define DJ_ESHUTDOWN         108       // Cannot send after socket shutdown
	#define DJ_ETIMEDOUT         110       // Connection timed out
	#define DJ_ECONNREFUSED      111       // Connection refused
	#define DJ_EHOSTDOWN         112       // Host is down
	#define DJ_EHOSTUNREACH      113       // No route to host
#endif

////////////////////  These error code value of our own system  /////////////////////////
#define DJ_ITPCOM_ERRBASE    20000     // Start error code

#define DJ_EPARAMETER        (DJ_ITPCOM_ERRBASE + 1)  // Parameter error
#define DJ_ENODATA           (DJ_ITPCOM_ERRBASE + 2)  // Receive no data or enough data
#define DJ_EMEMALLOC         (DJ_ITPCOM_ERRBASE + 3)  // Allocate memory error
#define DJ_EMAXSOCKET        (DJ_ITPCOM_ERRBASE + 4)  // Have set up  128 socket (max)
#define DJ_EAUTHORIZE        (DJ_ITPCOM_ERRBASE + 5)  // Authorization not passed
#define DJ_EPKGFLAG          (DJ_ITPCOM_ERRBASE + 6)  // Package flag error
#define DJ_ESENDSELECT       (DJ_ITPCOM_ERRBASE + 7)  // Before send select error
#define DJ_EREMOTEDOWN       (DJ_ITPCOM_ERRBASE + 8)  // Remote connect gracefully closed
#define DJ_EPKGSIZE          (DJ_ITPCOM_ERRBASE + 9)  // Package size error(max size 8K)

#endif
