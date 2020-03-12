#ifndef WEX_PUBLIC_HEADER_H_INCLUDED
#define WEX_PUBLIC_HEADER_H_INCLUDED

/* Standard C header files included */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*============================================================================*/

typedef unsigned char uchar, byte, BYTE;

typedef unsigned short uint16, word_t, ushort;

typedef unsigned __int32 uint, uint32, dword_t, size_t;

typedef unsigned long    ulong;

typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64, longlong;

typedef    long    lresult;

typedef unsigned __int64 uint64, qword_t, ulonglong;

#ifndef BOOL
    typedef int     BOOL;
    #define TRUE  1
    #define FALSE 0
#endif

#ifndef RESULT
    #define RESULT        lresult
    #define _SUCCESS    0
    #define _ERROR        -1
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#define SIZE_BYTE    1
#define SIZE_ACHAR    1
#define SIZE_WCHAR    2
#define SIZE_SHORT    2
#define SIZE_INT    4
#define SIZE_LONG    4
#define SIZE_FLT    4
#define SIZE_DBL    8
#define SIZE_WORD    2
#define SIZE_DWORD    4
#define SIZE_QWORD    8
#define SIZE_LINT    8
#define SIZE_INT64    8
#define SIZE_UUID    16

#endif // WEX_PUBLIC_HEADER_H_INCLUDED
