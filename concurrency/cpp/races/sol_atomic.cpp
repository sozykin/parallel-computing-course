/// 
/// Using atomic to get rid of race conditions 
///
#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
#include <atomic>
using namespace std;

int const THREAD_NUM = 20;

void compute(int const x, atomic<int> &result){
    // Atomic write to shared variable
    result += x * x;
}

int main(){
    /// 
    /// Atomic shared variable sum
    atomic<int> sum(0);
    vector<thread> threads;
    for (int i = 0; i <= THREAD_NUM; i++)
        threads.push_back(thread(compute, i, ref(sum)));
    
    for (thread& t : threads)
        t.join();

    cout << sum << endl;
}
