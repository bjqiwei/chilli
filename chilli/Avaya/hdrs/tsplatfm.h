/*******************************************************/
/* Copyright (C) 2008 Avaya Inc.  All rights reserved. */
/*******************************************************/
/*
 *  tsplatfm.h - TSAPI platform-dependent definitions
 */

#ifndef TSPLATFM_H
#define TSPLATFM_H

/* define the CONST_PARAM keyword for C++ compilers */
#if defined (__cplusplus)

#define CONST_PARAM const

#else

#define CONST_PARAM

#endif

/*
 * Figure out for which platform we're compiling.
 *
 * NOTE: Currently supported platforms are:
 *
 *      32-bit Windows (Intel)
 *      Linux (Intel and PowerPC)
 */
#if defined ( linux ) || defined ( __linux ) || defined ( __linux__ ) || \
	defined ( unix )

#define TSLIB_LINUX
#define TSLIB_UNIXWARE    // Not really, but keep this for backward
                          // compatibility

#elif defined (WIN32) || defined ( _WIN32 ) || \
	defined (__WIN32__) || defined ( __WINDOWS_386__ )

#define TSLIB_WINDOWS_32

#else
	#error I do not recognize your compilation environment
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

/*
 * On some platforms, sizeof(int) depends upon
 * the compiler and/or options used;
 * the "_Int" data type is defined according
 * to the size of "int" used in TSLIB
 */
#if defined ( TSLIB_WINDOWS_32 )

// Win32 Specific definitions for Windows

typedef unsigned long   ACSHandle_t;
typedef unsigned char   Boolean;

#define _Int            int
#define TSAPI           RetCode_t pascal

#ifndef FAR
#define FAR
#endif

#elif defined ( TSLIB_LINUX )

typedef unsigned long   ACSHandle_t;
typedef char            Boolean;

#define _Int            long
#define TSAPI           RetCode_t
#define FAR

#endif

#endif
