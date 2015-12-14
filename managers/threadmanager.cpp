// =====================================================================================
//
//       Filename:  threadmanager.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  30.11.2015  9,15,56
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#include <pthread.h>
#include "threadmanager.h"
struct ThreadFuncInput {
   ThreadWorkerInterface * worker;
   unsigned int threadID;
};
void *threadFunc(void *input0) {
  ThreadFuncInput *input = reinterpret_cast<ThreadFuncInput *>(input0);
  return input != NULL && input->worker != NULL
             ? input->worker->doWork(input->threadID)
             : NULL;
}


ThreadManager::ThreadManager(const unsigned int maxThreads)
    : threadIDs(NULL), maxThreads(maxThreads), numThreads(0) {
  threadIDs = new pthread_t[maxThreads];
}
ThreadManager::~ThreadManager() {
   delete [] threadIDs; threadIDs = NULL;
}

void ThreadManager::execute(const unsigned int numThreads,
                            ThreadWorkerInterface &threadWorker) {

  if (numThreads == 1) {
    threadWorker.doWork(0);
  } else {
    ThreadFuncInput *threadFuncInput = new ThreadFuncInput[numThreads];
    threadIDs[0] = pthread_self();
    threadFuncInput[0].worker = &threadWorker;
    threadFuncInput[0].threadID = 0;

    for (unsigned int i = 1; i < numThreads; i++) {
      threadFuncInput[i].worker = &threadWorker;
      threadFuncInput[i].threadID = i;

      void *arg = &threadFuncInput[i];
      int info = pthread_create(&threadIDs[i], NULL, threadFunc, arg);
      if (info != 0) {
        threadIDs[i] = 0;
        //            	handle_error_en(info, "pthread_create");
      }
    }
    // execute the worker from the calling thread
    threadFunc(&threadFuncInput[0]);

    // Join all hreads
    for (int i = 1; i < numThreads; i++)
      if (threadIDs[i]) {
        void *exitPtr = NULL;
        int info = pthread_join(threadIDs[i], &exitPtr);
        threadIDs[i] = 0;
      }
    delete [] threadFuncInput;
  }
}
