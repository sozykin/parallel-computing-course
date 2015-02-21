/// 
/// Using tasks to get rid of race conditions 
///
#include <iostream>
#include <vector>
#include <future>
using namespace std;

int const THREAD_NUM = 20;

int compute(int const x){
    return x * x;
}

int main(){
    int sum = 0; 
    vector<future<int>> futures;
    for (int i = 0; i <= THREAD_NUM; i++)
        futures.push_back(async(&compute, i));
    
    for (future<int>& f : futures)
        sum += f.get();

    cout << sum << endl;
}
