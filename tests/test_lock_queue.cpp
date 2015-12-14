// =====================================================================================
//
//       Filename:  test_lock_queue.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  28.11.2015 16,47,13
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#include <cstdlib>
#include <stdio.h>
#include "lock.h"
#include "threadmanager.h"
#include "managers.h"

class ThreadWorkerHelloWorld : public ThreadWorkerInterface {
	void *doWork(const unsigned int threadID) override {
		printf("Hello world from thread %d\n", threadID);
		return NULL;
	}
};

template <typename T> class LinkedList {
	struct Node {
		T data;
		Node *next;
	};

public:
	LinkedList() : head(NULL), tail(NULL) {}
	void init(Node *node) {
		head = tail = node;
		node->next = NULL;
	}
	void push(Node *node) {
		RAIILock<SpinLock> crit(taillock);
		tail->next = node;
		tail = node;
	}
	Node *pushArray(Node *node, const size_t count) {
		// assert count > 2
		for (size_t i = 1; i < count - 1; i++)
			node[i].next = &node[i + 1];
		node[count - 1].next = NULL;
		if (count > 2) {
			RAIILock<SpinLock> crit(taillock);
			tail->next = &node[1];
			tail = &node[count - 1];
		}
		return node;
	}
	Node *pop() {
		Node *node = NULL;
		RAIILock<SpinLock> crit(headlock);
		if (head->next != NULL) {
			node = head;
			head = node->next;
		}
		return node;
	}

private:
	Node *head;
	Node *tail;n
	SpinLock headlock;
	SpinLock taillock;
};

template <typename T> class NodeAllocator {
public:
	typedef typename LinkedList<T>::Node Node;
	NodeAllocator(MemoryManager &memoryManager)
	    : memoryManager(memoryManager) {}
	~NodeAllocator() {
		for (Node *alloc = allocated.pop(); alloc != NULL; alloc = allocated.pop())
			memoryManager.dealloc(128, alloc);
	}

	Node *allocNode() {
		Node *res = free.pop();
		if (!res) {
			if (memoryManager.alloc(128, res)) {
				allocated.push(res);
				res = free.pushArray(res, 128);
			}
		}
		return res;
	}
	void freeNode(Node *&node) {
		free.push(node);
		node = NULL;
	}

private:
	MemoryManager &memoryManager;
	LinkedList<T> allocated;
	LinkedList<T> free;
};

template <typename T> class Queue {
public:
	typedef typename NodeAllocator<T>::Node Node;
	Queue() {
		Node *newNode = nodeAllocator.allocNode();
		list.init(newNode);
	}

	/// thread safe push in Queue
	/// returns, false, if queue is full
	bool push(const T &val) {
		Node *const newNode = nodeAllocator.allocNode();
		if (newNode != NULL) {
			newNode->data = val;
			newNode->next = NULL;
			list.push(newNode);
		}
		return newNode != NULL;
	}
	bool pop(T &val) {
		Node *node = list.pop();
      const bool res = node != NULL;
		if (res) {
         val = node->data;
		   nodeAllocator.freeNode(node);
      }
		return res;
	}

private:
	NodeAllocator<T> nodeAllocator;
   LinkedList<T> list;
};

int main(const int argc, const char *argv[]) {
	MemoryManager memoryManageger;
	ThreadManager threadManager(16);
	int numThreads = 1;
	for (int i = 1; i < argc; i++) {
		if (sscanf(argv[i], "--numThreads=%d", &numThreads) == 1) {
			if (numThreads < 1 || numThreads > 16)
				numThreads = 0;
		}
	}

	ThreadWorkerHelloWorld helloWordWorker;
	threadManager.execute(numThreads, helloWordWorker);

	return numThreads == 2 ? 0 : -1;
}
