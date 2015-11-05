
#pragma once
/* detect 32 or 64 platform */
#if defined(__x86_64__) || defined(__ia64__) || defined(_M_X64)
#define __X86_64__
#else
#error("Only 64 bit platforms are supported")
#endif

/* detect Linux platform */
#if defined(linux) || defined(__linux__) || defined(__LINUX__)
#  if !defined(__LINUX__)
#     define __LINUX__
#  endif
#  if !defined(__UNIX__)
#     define __UNIX__
#  endif
#endif

/* detect Windows 95/98/NT/2000/XP/Vista/7 platform */
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)) && !defined(__CYGWIN__)
#  if !defined(__WIN32__)
#     define __WIN32__
#  endif
#endif

//////////////////////////////////////////////////////
/// Basic Types
//////////////////////////////////////////////////////
/* detect compiler */
#if defined(__clang__) || defined (__GNUC__)
/*  clang compiler *//*  gcc compiler */
typedef __INT64_TYPE__  int64;
typedef __INT32_TYPE__  int32;
typedef __INT16_TYPE__  int16;
typedef __INT8_TYPE__   int8;

typedef __UINT64_TYPE__ uint64;
typedef __UINT32_TYPE__ uint32;
typedef __UINT16_TYPE__ uint16;
typedef __UINT8_TYPE__  uint8;

typedef __INTPTR_TYPE__ intptr;

#define PURE __attribute__ ((const))
#define restrict __restrict__
#endif
