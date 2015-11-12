// =====================================================================================
//
//       Filename:  kernel_vectors.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  10.11.2015  8,30,55
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#include "kernel.h"
 
namespace 
#if   defined (__SSE4_2__)
      kernels_SSE42
#elif defined (__SSE4_1__)
      kernels_SSE41
#elif defined (__SSSE3__)
      kernels_SSSE3
#elif defined (__SSE3__)
      kernels_SSE3
#elif defined (__SSE2__)
      kernels_SSE2
#elif defined (__SSE__)
      kernels_SSE
#endif
{

class VectorsKernelDescribtor : public IComputationalKernelDescribtor {

   virtual int getISA() const override {
#if   defined (__SSE4_2__)
      return isa_SSE42;
#elif defined (__SSE4_1__)
      return isa_SSE41;
#elif defined (__SSSE3__)
      return isa_SSSE3;
#elif defined (__SSE3__)
      return isa_SSE3;
#elif defined (__SSE2__)
      return isa_SSE2;
#elif defined (__SSE__)
      return isa_SSE;
#else
   #error Instruction Set Architecture need to be defined
#endif
   }

   // use to describe what this kernel does.
   const char * getDefinition() const override {
      return "Multiply several vectors.";
   }

};
class VectorsKernelImplementation : public IComputationalKernelImplementation {
public:
   int compute(const void * input, void * output) const override;
   const IComputationalKernelDescribtor & getDescription() const override {
      return descriptor;
   }
   ~VectorsKernelImplementation(){};
private:
   VectorsKernelDescribtor descriptor;
   int initialize() override {
     return 0;
   };
   int finish() override {
     return 0;
   };
};
int VectorsKernelImplementation::compute(const void *input,
                                         void *output) const {
   return 0;
};

static ComputationalKernelRegister<VectorsKernelImplementation> registerVectorsKernel;

}
