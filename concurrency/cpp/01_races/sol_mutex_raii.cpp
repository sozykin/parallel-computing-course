/// 
/// Example of using RAII idiom for mutex
///
#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <mutex>
using namespace std;

int const THREAD_NUM = 20;

void compute(int const x, int &result, mutex &result_mutex){
    int temp = x * x;
    // Creating lock guard for mutex
    lock_guard<std::mutex> lg(result_mutex);
    // Write to shared variable
    result += temp;
    // Lock guard going out of scope and unlocks mutex 
}

int main(){
    /// 
    /// Shared variable sum
    int sum = 0;
    ///
    /// Mutex for sum
    /// You have to lock mutex befor writing to sum
    mutex sum_mutex;
    vector<thread> threads;
    for (int i = 0; i <= THREAD_NUM; i++)
        threads.push_back(thread(compute, i, ref(sum), ref(sum_mutex)));
    
    for (thread& t : threads)
        t.join();

    cout << sum << endl;
}
