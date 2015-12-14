// =====================================================================================
//
//       Filename:  kernel.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  11.11.2015  9,15,11
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#include "kernel.h"
#include <stdlib.h>
#include <stdio.h>
ComputationalKernelFactory * ComputationalKernelFactory::instance = NULL;
ComputationalKernelFactory * ComputationalKernelFactory::getInstance() {
   if (!instance) 
      instance = new ComputationalKernelFactory();
   return instance;
};

ComputationalKernelFactory::ComputationalKernelFactory() {

}
ComputationalKernelFactory::~ComputationalKernelFactory() {
   printf("Destructing Computational Kernel Factory");
}
int ComputationalKernelFactory::registerComputationalKernel(
    IComputationalKernelImplementation &implementation) {
   const IComputationalKernelDescribtor & descriptor = implementation.getDescription();

   printf("registering %s isa = %d\n", descriptor.getDefinition(),
          descriptor.getISA());
   return 0;
}
int ComputationalKernelFactory::deregisterComputationalKernel(
    IComputationalKernelImplementation &implementation) {
   const IComputationalKernelDescribtor & descriptor = implementation.getDescription();
   printf("deregistering %s isa = %d\n", descriptor.getDefinition(),
          descriptor.getISA());
   return 0;
}
