/// 
/// Example with race conditions
///
#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
using namespace std;

int const THREAD_NUM = 20;

void compute(int const x, int &result){
    ///
    /// Writing to shared variable
    /// Race conditions are possible
    ///
    result += x * x;
}

int main(){
    /// 
    /// sum is a shared variable
    ///
    int sum = 0;
    vector<thread> threads;
    for (int i = 0; i <= THREAD_NUM; i++)
        // Passing a reference to sum to the thread
        threads.push_back(thread(compute, i, ref(sum)));
    
    for (thread& t : threads)
        t.join();

    cout << sum << endl;
}
