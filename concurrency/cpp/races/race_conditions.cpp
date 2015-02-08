#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
using namespace std;

int const THREAD_NUM = 20;

void compute(double const x, double &result){
    result += (sin(x) + cos(x)) / exp (x / 2);
}

int main(){
    double sum = 0;
    vector<thread> threads;
    for (int i = 0; i <= THREAD_NUM; i++)
        threads.push_back(thread(compute, i / 10, ref(sum)));
    
    for (thread& t : threads)
        t.join();

    cout << sum << endl;
}
