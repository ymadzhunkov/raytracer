// =====================================================================================
//
//       Filename:  lock.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  28.11.2015 17,27,21
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#pragma once
template <typename LockType>
class Lock {
public:
	Lock();
	~Lock();
	void lock(); 
	void unlock();
	bool tryLock();
protected:
   LockType l;
};

/***********  Mutex Lock *****************/
#include <pthread.h>
template <> Lock<pthread_mutex_t>::Lock() {
  pthread_mutex_init(&l, NULL);
};
template <> Lock<pthread_mutex_t>::~Lock() {
  pthread_mutex_destroy(&l);
}
template <> void Lock<pthread_mutex_t>::lock() {
  pthread_mutex_lock(&l);
}
template <> void Lock<pthread_mutex_t>::unlock() {
  pthread_mutex_unlock(&l);
}
template <> bool Lock<pthread_mutex_t>::tryLock() {
  return pthread_mutex_trylock(&l) == 0;
};
typedef Lock<pthread_mutex_t   > MutexLock;

/***********  Spin Lock *****************/
template <> Lock<pthread_spinlock_t>::Lock() {
  pthread_spin_init(&l, PTHREAD_PROCESS_PRIVATE);
}
template <> Lock<pthread_spinlock_t>::~Lock() {
  pthread_spin_destroy(&l);
}
template <> void Lock<pthread_spinlock_t>::lock() {
  pthread_spin_lock(&l);
}
template <> void Lock<pthread_spinlock_t>::unlock() {
  pthread_spin_unlock(&l);
}
template <> bool Lock<pthread_spinlock_t>::tryLock() {
  return pthread_spin_trylock(&l) == 0;
};

typedef Lock<pthread_spinlock_t> SpinLock;



template <class T> class RAIILock {
public:
  RAIILock(T &lock) : lock(lock) { lock.lock(); }
  ~RAIILock() { lock.unlock(); }

private:
  T &lock;
};
