// =====================================================================================
//
//       Filename:  atomic.h
//
//    Description:  
//
//        Version:  1.0
//        Created:   5.11.2015  8,59,43
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================


////////////////////////////////////////////////////////////////////////////////
/// Unix atomics
////////////////////////////////////////////////////////////////////////////////



typedef int8 atomic8_t;

__forceinline int8 atomic_add( int8 volatile* value, int8 input ) {
  return __sync_fetch_and_add(value, input);
}

__forceinline int8 atomic_sub( int8 volatile* value, int8 input ) {
  return __sync_fetch_and_add(value, -input);
}

__forceinline int8 atomic_xchg( int8 volatile* value, int8 input ) {
  return __sync_lock_test_and_set(value, input);
}

__forceinline int8 atomic_cmpxchg( int8 volatile* value, int8 comparand, const int8 input ) {
  return __sync_val_compare_and_swap(value, comparand, input);
}

typedef int16 atomic16_t;

__forceinline int16 atomic_add( int16 volatile* value, int16 input ) {
  return __sync_fetch_and_add(value, input);
}

__forceinline int16 atomic_sub( int16 volatile* value, int16 input ) {
  return __sync_fetch_and_add(value, -input);
}

__forceinline int16 atomic_xchg( int16 volatile* value, int16 input ) {
  return __sync_lock_test_and_set(value, input);
}

__forceinline int16 atomic_cmpxchg( int16 volatile* value, int16 comparand, const int16 input ) {
  return __sync_val_compare_and_swap(value, comparand, input);
}

typedef int32 atomic32_t;

__forceinline int32 atomic_add( int32 volatile* value, int32 input ) {
  return __sync_fetch_and_add(value, input);
}

__forceinline int32 atomic_sub( int32 volatile* value, int32 input ) {
  return __sync_fetch_and_add(value, -input);
}

__forceinline int32 atomic_xchg( int32 volatile* value, int32 input ) {
  return __sync_lock_test_and_set(value, input);
}

__forceinline int32 atomic_cmpxchg( int32 volatile* value, int32 comparand, const int32 input ) {
  return __sync_val_compare_and_swap(value, comparand, input);
}

__forceinline int32 atomic_or(int32 volatile* value, int32 input) {
  return __sync_fetch_and_or(value, input);
}

__forceinline int32 atomic_and(int32 volatile* value, int32 input) {
  return __sync_fetch_and_and(value, input);
}


typedef int64 atomic64_t;

__forceinline int64 atomic_add( int64 volatile* value, int64 input ) {
  return __sync_fetch_and_add(value, input);
}

__forceinline int64 atomic_sub( int64 volatile* value, int64 input ) {
  return __sync_fetch_and_add(value, -input);
}

__forceinline int64 atomic_xchg( int64 volatile* value, int64 input ) {
  return __sync_lock_test_and_set(value, input);
}

__forceinline int64 atomic_cmpxchg( int64 volatile* value, int64 comparand, const int64 input) {
  return __sync_val_compare_and_swap(value, comparand, input);
}

__forceinline int64 atomic_or(int64 volatile* value, int64 input) {
  return __sync_fetch_and_or(value, input);
}

__forceinline int64 atomic_and(int64 volatile* value, int64 input) {
  return __sync_fetch_and_and(value, input);
}



////////////////////////////////////////////////////////////////////////////////
/// All Platforms
////////////////////////////////////////////////////////////////////////////////

 typedef atomic64_t atomic_t;


template<typename T>
__forceinline T* atomic_xchg_ptr( T* volatile* value, const T* input)
{  return (T*)atomic_xchg((int64*)value,(int64)input); }

template<typename T>
__forceinline T* atomic_cmpxchg_ptr( T* volatile* value, T* comparand, const T* input )
{  return (T*)atomic_cmpxchg((int64*)value,(int64)comparand,(int64)input); }


__forceinline void atomic_min_f32(volatile float *__restrict__ ptr, const float b)
{
  const int int_b = *(int*)&b;
  while (1)
  {
    float a = *ptr;
    if (a <= b) break;
    const int int_a = *(int*)&a;
    const int result = atomic_cmpxchg((int*)ptr,int_a,int_b);
    if (result == int_a) break;
  }
}

__forceinline void atomic_max_f32(volatile float *__restrict__ ptr, const float b)
{
  const int int_b = *(int*)&b;
  while (1)
  {
    float a = *ptr;
    if (a >= b) break;
    const int int_a = *(int*)&a;
    const int result = atomic_cmpxchg((int*)ptr,int_a,int_b);
    if (result == int_a) break;
  }
}

__forceinline void atomic_min_i32(volatile int *__restrict__ ptr, const int b)
{
  while (1)
  {
    int a = *ptr;
    if (a <= b) break;
    const int int_a = *(int*)&a;
    const int result = atomic_cmpxchg((int*)ptr,int_a,b);
    if (result == int_a) break;
  }
}

__forceinline void atomic_max_i32(volatile int *__restrict__ ptr, const int b)
{
  while (1)
  {
    int a = *ptr;
    if (a >= b) break;
    const int int_a = *(int*)&a;
    const int result = atomic_cmpxchg((int*)ptr,int_a,b);
    if (result == int_a) break;
  }
}

__forceinline void atomic_min_ui32(volatile unsigned int *__restrict__ ptr, const unsigned int b)
{
  while (1)
  {
    unsigned int a = *ptr;
    if (a <= b) break;
    const unsigned int int_a = *(unsigned int*)&a;
    const unsigned int result = atomic_cmpxchg((int*)ptr,int_a,b);
    if (result == int_a) break;
  }
}

__forceinline void atomic_max_ui32(volatile unsigned int *__restrict__ ptr, const unsigned int b)
{
  while (1)
  {
    unsigned int a = *ptr;
    if (a >= b) break;
    const unsigned int int_a = *(unsigned int*)&a;
    const unsigned int result = atomic_cmpxchg((int*)ptr,int_a,b);
    if (result == int_a) break;
  }
}

__forceinline void atomic_add_f32(volatile float *__restrict__ ptr, const float b)
{
  while (1)
  {
    float a = *ptr;
    float ab = a + b;
    const int int_a = *(int*)&a;
    const int int_ab = *(int*)&ab;
    const int result = atomic_cmpxchg((int*)ptr,int_a,int_ab);
    if (result == int_a) break;
  }
}

__forceinline uint64 rdtsc()
{
  int dummy[4]; 
  __cpuid(dummy,0); 
  uint64 clock = read_tsc(); 
  __cpuid(dummy,0); 
  return clock;
}

__forceinline void __pause_cpu (const int cycles = 0) {
  for (size_t i=0; i<8; i++)
    _mm_pause();    
}

__forceinline void __pause_cpu_expfalloff(unsigned int &cycles, const unsigned int max_cycles) 
{ 
  __pause_cpu(cycles);
  cycles += cycles;
  if (cycles > max_cycles) 
    cycles = max_cycles;
}

/* prefetches */
__forceinline void prefetchL1 (const void* ptr) { _mm_prefetch((const char*)ptr,_MM_HINT_T0); }
__forceinline void prefetchL2 (const void* ptr) { _mm_prefetch((const char*)ptr,_MM_HINT_T1); }
__forceinline void prefetchL3 (const void* ptr) { _mm_prefetch((const char*)ptr,_MM_HINT_T2); }
__forceinline void prefetchNTA(const void* ptr) { _mm_prefetch((const char*)ptr,_MM_HINT_NTA); }

__forceinline void prefetchL1EX(const void* ptr) { 
  _mm_prefetch((const char*)ptr,_MM_HINT_T0); 
}

__forceinline void prefetchL2EX(const void* ptr) { 
  _mm_prefetch((const char*)ptr,_MM_HINT_T1); 
}


/* compiler memory barriers */
#ifdef __GNUC__
#  define __memory_barrier() asm volatile("" ::: "memory")
#endif
