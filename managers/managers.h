// =====================================================================================
//
//       Filename:  managers.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  16.11.2015  8,07,28
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================

#include <new>  // ::operator new
template <typename T>
class Array;

class MemoryManager {
public:
    
   template<typename T> bool alloc(T * & res) {
      res = new (std::nothrow) T;
      if (res != NULL)
         bytesAllocated += sizeof(T);
      return res != NULL;
   }

   template <typename T> void dealloc(T *&res) {
     if (res != NULL) {
       bytesAllocated -= sizeof(T);
       delete res;
       res = NULL;
     }
   }

   template <typename T> bool alloc(const size_t count, T *&res) {
     res = new (std::nothrow) T[count];
     return res != NULL;
   }

   template<typename T>
   void dealloc(const size_t count, T * & res) {
      delete [] res;
      res = NULL;
   }

private:
   size_t bytesAllocated;
   
};

template <typename T>
class Array {
public:
   ~Array();
   T       * getData ()       { return data; }
   T const * getData () const { return data; }
   size_t    getCount() const { return count; }

private:
friend class MemoryManager;
private:
   Array(const T *data, const size_t count) : 
      data(data), 
      count(count) {}
   size_t count;
   T * data;
};




class ProgressManager {

};

class Managers {
  MemoryManager &getMemoryProxy() { return memProxy; }

private:
   MemoryManager memProxy;
};
