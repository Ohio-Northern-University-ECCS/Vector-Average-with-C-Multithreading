# Vector-Average-with-C-Multithreading
Computing the sum then the average of a large vector with C++ threads
Refactor your code from vector_add_thread.cpp to do the following:
1. Afer summing the two vectors, comput the average of the sum. 
2. Then, add average back to the sum vector.

You can accomplish the above by noting the following
1. Each thread can compute a local sum for its elements
2. Each thread can then enter a critical section to add its local sum to a global vector sum
3. All threads except the last one must wait before using the the global sum to compute the global vector average
4. The last thread to add its local sum to the global sum can compute the global average and then notify all other threads that the average is ready for access
5. All threads then can proceed to add the global average to their elements
Note: convert vectors elements from Exercise 2 to double, so that the sum as a double can accommodate large values for vectors with many elements. 

Create your new code in the file vector_avg_thread.cpp
<img width="1275" alt="image" src="https://user-images.githubusercontent.com/103138769/164582551-19bc1d2e-3082-49b7-a955-c0a79d6d645a.png">
