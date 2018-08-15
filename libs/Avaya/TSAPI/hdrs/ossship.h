/*****************************************************************************/
/* Copyright (C) 1989-2004 OSS Nokalva, Inc.  All rights reserved.           */
/*****************************************************************************/

/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC., AND
 * MAY BE DISTRIBUTED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.
 */

/* @(#)ossship.h: stdtypes.c 10.3 01/09/27 */

#ifndef OSSSHIP
#define OSSSHIP

#ifdef ASN1CPLUSPLUS
#define MixedReal ossMixedReal
#define GeneralizedTime ossGeneralizedTime
#define UTCTime ossUTCTime
#endif



/*****************************************************************************/
/*                       COMPILER-GENERATED typedefs                         */
/*****************************************************************************/


#ifndef OSS_INT16
#define OSS_INT16 short
#endif

#define OSS_UINT16 unsigned OSS_INT16

#ifndef OSS_INT32
#define OSS_INT32 int
#endif

#define OSS_UINT32 unsigned OSS_INT32
typedef char ossBoolean;

#if !defined(__cplusplus) && !defined(_union)
#define _union
#endif

#ifndef LONG_LONG
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define LONG_LONG __int64
#define LLONG_FMT "%I64d"
#elif defined(__IBMC__)
#define LONG_LONG long long
#define LLONG_FMT "%lld"
#else
#define LONG_LONG long
#define LLONG_FMT "%ld"
#endif
#endif

#ifndef ULONG_LONG
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define ULONG_LONG unsigned __int64
#define ULLONG_FMT "%I64u"
#elif defined(__IBMC__)
#define ULONG_LONG unsigned long long
#define ULLONG_FMT "%llu"
#else
#define ULONG_LONG unsigned long
#define ULLONG_FMT "%lu"
#endif
#endif

#ifndef LLONG_MAX
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define LLONG_MAX _I64_MAX
#elif defined(__IBMC__)
#define LLONG_MAX LONGLONG_MAX
#else
#define LLONG_MAX LONG_MAX
#endif
#endif

#ifndef LLONG_MIN
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define LLONG_MIN _I64_MIN
#elif defined(__IBMC__)
#define LLONG_MIN LONGLONG_MIN
#else
#define LLONG_MIN LONG_MIN
#endif
#endif

#ifndef ULLONG_MAX
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define ULLONG_MAX _UI64_MAX
#elif defined(__IBMC__)
#define ULLONG_MAX ULONGLONG_MAX
#else
#define ULLONG_MAX ULONG_MAX
#endif
#endif

#ifndef LLONG_MIN
#define LLONG_MIN (-2147483647i64-1i64)
#endif
#ifndef LLONG_MAX
#define LLONG_MAX (2147483647i64)
#endif
#ifndef ULLONG_MAX
#define ULLONG_MAX (4294967295ui64)
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef _NULLTYPE_
#define _NULLTYPE_
typedef char Nulltype;
#endif

typedef struct {
  short          year;         /* YYYY format when used for GeneralizedTime */
                               /* YY format when used for UTCTime */
  short          month;
  short          day;
  short          hour;
  short          minute;
  short          second;
  short          millisec;
  short          mindiff;      /* UTC +/- minute differential     */  
  ossBoolean     utc;          /* TRUE means UTC time             */  
} GeneralizedTime; 

typedef GeneralizedTime UTCTime;

typedef struct {
  int            pduNum;
  long           length;       /* length of encoded */
  void          *encoded;
  void          *decoded;
#ifdef OSS_OPENTYPE_HAS_USERFIELD
  void          *userField;
#endif
} OpenType;

typedef struct {
  int            pduNum;
  long           length;       /* length of encoded */
  void          *encoded;
  void          *decoded;
  unsigned long  byteOffset;
  unsigned short bitOffset;    /* Used only for PER */
  unsigned short residualBits; /* Used only for PER */
#ifdef OSS_OPENTYPE_HAS_USERFIELD
  void          *userField;
#endif /* OSS_OPENTYPE_HAS_USERFIELD */
} OpenTypeExtended;

enum MixedReal_kind {OSS_BINARY, OSS_DECIMAL};

typedef struct {
  enum MixedReal_kind kind;
  union {
      double base2;
      char  *base10;
  } u;
} MixedReal;

typedef struct ObjectSetEntry {
  struct ObjectSetEntry *next;
  void                  *object;
  struct ObjectSetEntry *prev;
  char                  *object_name;
} ObjectSetEntry;

typedef struct {
  struct ObjectSetEntry *oset;
  struct ObjectSetEntry *xoset;
  unsigned char *        flags;
  unsigned int           count;
} XOSetInfoEntry;

#ifdef ASN1CPLUSPLUS
#undef MixedReal
#undef GeneralizedTime
#undef UTCTime
#endif

typedef double     ossReal;

typedef struct ossBitString {
    OSS_UINT32     length; /* number of significant bits */
    unsigned char  *value;
} ossBitString;

typedef struct ossOctetString {
    OSS_UINT32     length;
    unsigned char  *value;
} ossOctetString;

typedef struct ossCharString {
    OSS_UINT32     length;
    char           *value;
} ossCharString;

typedef struct ossBMPString {
    OSS_UINT32     length;
    OSS_UINT16     *value;
} ossBMPString;

typedef struct ossUniversalString {
    OSS_UINT32     length;
    OSS_INT32      *value;
} ossUniversalString;

typedef struct ossContentsConstr {
    ossOctetString encoded;
    void           *decoded;
} ossContentsConstr;

typedef struct ossHugeInt {
    OSS_UINT32     length;
    unsigned char  *value;
} ossHugeInt;

typedef struct ossObjectID {
    OSS_UINT32     length;
    unsigned char  *value;
} ossObjectID;

typedef struct ossAny {
    OSS_UINT32     length;
    unsigned char  *value;
} ossAny;

/* struct ossExtensions_ keeps unknown extension additions for -relaySafe *
 * in case of extensible SET or SEQUENCE                                  */

typedef struct ossExtensions_ {
    ossBitString      extMask;
    struct _ossExtList {
	OSS_UINT32       count;
	ossOctetString   *value;
    } extList;
} *ossExtensions;

/* struct ossExtAlternative keeps unknown extension additions for -relaySafe *
 * in case of extensible CHOICE                                              */

typedef struct ossExtAlternative {
    OSS_UINT32      idx;
    ossOctetString  data;
} ossExtAlternative;

#endif     /* #ifndef OSSSHIP */
