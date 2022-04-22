#include <thread>
#include <iostream>
#include <vector>
#include <chrono> 
using namespace std::chrono;
using namespace std;

// Note: Assume for now that the number of elements in the vectors and the the number 
// of threads are both a power of 2; therefore, the number of elements is an 
// integer multiple of threads. 

#define NB_THREADS 4 

void initWith (float num, vector<float>& a) {
  for (unsigned int i = 0; i < a.size(); ++i) {
    a[i] = num;
  }
}

void addVectors (vector<float>& result, vector<float>& a, vector<float>& b) {
  for (int i = 0; i < result.size(); ++i) {
  	result[i] = a[i] + b[i];
  }
}

void addVectorsThread (vector<float>& result, vector<float>& a, vector<float>& b, int begin_index, int end_index) {
  for (int i = begin_index; i <= end_index; i++) {
    result[i] = a[i] + b[i];
  }   
}

void checkElements (float target, const vector<float>& a) {
  for(int i = 0; i < a.size(); i++)
  {
    if (a[i] != target)
    {
      cout << "FAIL: vector[" << i << "] = " << a[i] << " does not equal " << target << endl; 
     	exit(1);
    }
  }
  cout << "SUCCESS! ALL values added correctly" << endl;
}

void doNothing(vector<float>& a, int i) {
  cout << a[i];

}

int main() {
   // Number of elements in a vector is a power of 2^(x+1)
  const int N = 2 << 24;
  vector<float> a(N);
  vector<float> b(N);
  vector<float> c(N);

  initWith(3, a);
  initWith(4, b);
  initWith(0, c);

  unsigned int stride = N / NB_THREADS;   
  vector<int> begin_index(NB_THREADS);
  vector<int> end_index(NB_THREADS);

  for (int i = 0; i < NB_THREADS; i++) {
    begin_index[i] = i * stride;
    end_index[i] = begin_index[i] + stride - 1;
  }

    
  thread t[NB_THREADS];
  auto start = high_resolution_clock::now(); 
  for (int i = 0; i < NB_THREADS; i++) {
    t[i] = thread (addVectorsThread, ref(c), ref(a), ref(b), begin_index[i], end_index[i]);
    //t[i] = thread (doNothing, ref(a), i);
  }
  
  for (int i = 0; i < NB_THREADS; i++) {
    t[i].join();
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);

  cout << "Time taken by multithread function: " << duration.count() << " microseconds" << endl;
 
    
  auto start2 = high_resolution_clock::now();
  
  addVectors(ref(c), ref(a), ref(b));
  
  auto stop2 = high_resolution_clock::now();
  auto duration2 = duration_cast<microseconds>(stop2 - start2);
  cout << "Time taken by single thread function: " << duration2.count() << " microseconds" << endl;

  cout << "Speedup = " << (float)duration2.count() / duration.count() << endl; 

  checkElements(7, c);
}
