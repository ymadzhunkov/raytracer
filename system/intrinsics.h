// ======================================================================== //
// Copyright 2009-2015 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#include "platform.h"

#if defined(__SSE__)
#include <xmmintrin.h>
#endif

#if defined(__SSE2__)
#include <emmintrin.h>
#endif

#if defined(__SSE3__)
#include <pmmintrin.h>
#endif

#if defined(__SSSE3__)
#include <tmmintrin.h>
#endif

#if defined (__SSE4_1__)
#include <smmintrin.h>
#endif

#if defined (__SSE4_2__)
#include <nmmintrin.h>
#endif

#if defined(__AVX__)
#include <immintrin.h>
#endif

#if defined(__BMI__) && defined(__GNUC__)
  #if !defined(_tzcnt_u32)
    #define _tzcnt_u32 __tzcnt_u32
  #endif
  #if !defined(_tzcnt_u64)
    #define _tzcnt_u64 __tzcnt_u64
  #endif
#endif

#if defined(__LZCNT__)
  #if !defined(_lzcnt_u32)
    #define _lzcnt_u32 __lzcnt32
  #endif
  #if !defined(_lzcnt_u64)
    #define _lzcnt_u64 __lzcnt64
  #endif
#endif



__forceinline void __cpuid(int out[4], int op) {
  asm volatile ("cpuid" : "=a"(out[0]), "=b"(out[1]), "=c"(out[2]), "=d"(out[3]) : "a"(op)); 
}

__forceinline void __cpuid_count(int out[4], int op1, int op2) {
  asm volatile ("cpuid" : "=a"(out[0]), "=b"(out[1]), "=c"(out[2]), "=d"(out[3]) : "a"(op1), "c"(op2)); 
}


__forceinline uint64 read_tsc()  {
  uint32 high,low;
  asm volatile ("rdtsc" : "=d"(high), "=a"(low));
  return (((uint64)high) << 32) + (uint64)low;
}


#if defined(__SSE4_2__)
__forceinline unsigned int __popcnt(unsigned int in) {
  int r = 0; asm ("popcnt %1,%0" : "=r"(r) : "r"(in)); return r;
}
#endif

__forceinline int __bsf(int v) {
#if defined(__AVX2__) 
  return _tzcnt_u32(v);
#else
  int r = 0; asm ("bsf %1,%0" : "=r"(r) : "r"(v)); return r;
#endif
}

__forceinline unsigned __bsf(unsigned v) 
{
#if defined(__AVX2__) 
  return _tzcnt_u32(v);
#else
  unsigned r = 0; asm ("bsf %1,%0" : "=r"(r) : "r"(v)); return r;
#endif
}

__forceinline size_t __bsf(size_t v) {
#if defined(__AVX2__)
  return _tzcnt_u64(v);
#else
  size_t r = 0; asm ("bsf %1,%0" : "=r"(r) : "r"(v)); return r;
#endif
}

__forceinline int __bscf(int& v) 
{
  int i = __bsf(v);
  v &= v-1;
  return i;
}

__forceinline unsigned int __bscf(unsigned int& v) 
{
  unsigned int i = __bsf(v);
  v &= v-1;
  return i;
}

__forceinline size_t __bscf(size_t& v) 
{
  size_t i = __bsf(v);
  v &= v-1;
  return i;
}

__forceinline int __bsr(int v) {
#if defined(__AVX2__) 
  return _lzcnt_u32(v);
#else
  int r = 0; asm ("bsr %1,%0" : "=r"(r) : "r"(v)); return r;
#endif
}

__forceinline unsigned __bsr(unsigned v) {
#if defined(__AVX2__) 
  return _lzcnt_u32(v);
#else
  unsigned r = 0; asm ("bsr %1,%0" : "=r"(r) : "r"(v)); return r;
#endif
}

__forceinline size_t __bsr(size_t v) {
#if defined(__AVX2__)
  return _lzcnt_u64(v);
#else
  size_t r = 0; asm ("bsr %1,%0" : "=r"(r) : "r"(v)); return r;
#endif
}

__forceinline int lzcnt(const int x)
{
#if defined(__AVX2__)
  return _lzcnt_u32(x);
#else
   return x == 0 ? 32 : 31 - __bsr(x);    
#endif
}

__forceinline int __btc(int v, int i) {
  int r = 0; asm ("btc %1,%0" : "=r"(r) : "r"(i), "0"(v) : "flags" ); return r;
}

__forceinline int __bts(int v, int i) {
  int r = 0; asm ("bts %1,%0" : "=r"(r) : "r"(i), "0"(v) : "flags"); return r;
}

__forceinline int __btr(int v, int i) {
  int r = 0; asm ("btr %1,%0" : "=r"(r) : "r"(i), "0"(v) : "flags"); return r;
}

__forceinline size_t __btc(size_t v, size_t i) {
  size_t r = 0; asm ("btc %1,%0" : "=r"(r) : "r"(i), "0"(v) : "flags" ); return r;
}

__forceinline size_t __bts(size_t v, size_t i) {
  size_t r = 0; asm ("bts %1,%0" : "=r"(r) : "r"(i), "0"(v) : "flags"); return r;
}

__forceinline size_t __btr(size_t v, size_t i) {
  size_t r = 0; asm ("btr %1,%0" : "=r"(r) : "r"(i), "0"(v) : "flags"); return r;
}
