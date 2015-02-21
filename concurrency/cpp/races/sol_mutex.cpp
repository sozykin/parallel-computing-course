/// 
/// Getting rid of race conditions using mutex
///
#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <mutex>
using namespace std;

int const THREAD_NUM = 20;

void compute(double const x, double &result, mutex &result_mutex){
    double temp = (sin(x) + cos(x)) / exp (x / 2);
    // Lock mutex
    result_mutex.lock();
    // Write to shared variable
    result += temp;
    result_mutex.unlock();
}

int main(){
    /// 
    /// Shared variable sum
    double sum = 0;
    ///
    /// Mutex for sum
    /// You have to lock mutex befor writing to sum
    mutex sum_mutex;
    vector<thread> threads;
    for (int i = 0; i <= THREAD_NUM; i++)
        threads.push_back(thread(compute, i / 10, ref(sum), ref(sum_mutex)));
    
    for (thread& t : threads)
        t.join();

    cout << sum << endl;
}
