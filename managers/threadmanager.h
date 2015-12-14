// =====================================================================================
//
//       Filename:  threadmanager.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  30.11.2015  9,14,28
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#pragma once

#include <pthread.h>

class ThreadWorkerInterface {
public:
   virtual void * doWork(const unsigned int threadID) = 0;
};

// manages creation and destruction of threads
class ThreadManager {
public:
  ThreadManager(const unsigned int maxThreads);
  ~ThreadManager();
  void execute(const unsigned int numThreads,
               ThreadWorkerInterface &threadWorker);

private:
  pthread_t *threadIDs; //!< array with posix thread IDs
  unsigned int maxThreads;
  unsigned int numThreads;
};
