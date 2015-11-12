// =====================================================================================
//
//       Filename:  kernel.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  9.11.2015  9,14,45
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================

//used to describe a computational kernel
class IComputationalKernelDescribtor {
public:
   enum ISA {
      isa_SSE,
      isa_SSE2,
      isa_SSE3,
      isa_SSSE3,
      isa_SSE41,
      isa_SSE42
   };
   // returns the type os Instruction Set architecture
   // use by this kernel
   virtual int getISA() const = 0;
   // use to describe what this kernel does.
   virtual const char * getDefinition() const = 0;
};


//used to describe a computational kernel
class IComputationalKernelImplementation {
public:
   virtual int compute(const void * input, void * output) const = 0;
   virtual const IComputationalKernelDescribtor & getDescription() const = 0;
protected:
   virtual int initialize() = 0;
   virtual int finish() = 0;
   virtual ~IComputationalKernelImplementation(){}; 
   friend class ComputationalKernelFactory;
};


class ComputationalKernelFactory {
public:
   ComputationalKernelFactory();
   ~ComputationalKernelFactory();

   static ComputationalKernelFactory * getInstance();

   int registerComputationalKernel(
       IComputationalKernelImplementation &implementation);

private:
   static ComputationalKernelFactory * instance;
};

template <class ComputationalKernel> 
class ComputationalKernelRegister {
public:
   ComputationalKernelRegister() {
      ComputationalKernelFactory::getInstance()->registerComputationalKernel(kernel);
   }
private:
   ComputationalKernel kernel;
};
