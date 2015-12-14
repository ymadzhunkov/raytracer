
add_executable(test_lock_queue test_lock_queue.cpp)
target_link_libraries(test_lock_queue pthread stdc++ managers)
add_test(NAME lock_queue_1 COMMAND ./test_lock_queue --numThreads=1)
add_test(NAME lock_queue_2 COMMAND ./test_lock_queue --numThreads=2)
add_test(NAME lock_queue_3 COMMAND ./test_lock_queue --numThreads=3)
add_test(NAME lock_queue_4 COMMAND ./test_lock_queue --numThreads=4)
