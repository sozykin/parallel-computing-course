/// 
/// Example with race conditions
///
#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
using namespace std;

int const THREAD_NUM = 20;

void compute(double const x, double &result){
    ///
    /// Writing to shared variable
    /// Race conditions are possible
    ///
    result += (sin(x) + cos(x)) / exp (x / 2);
}

int main(){
    /// 
    /// sum is a shared variable
    ///
    double sum = 0;
    vector<thread> threads;
    for (int i = 0; i <= THREAD_NUM; i++)
        // Passing a reference to sum to the thread
        threads.push_back(thread(compute, i / 10, ref(sum)));
    
    for (thread& t : threads)
        t.join();

    cout << sum << endl;
}
