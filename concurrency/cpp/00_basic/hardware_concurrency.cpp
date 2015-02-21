///
/// Estimate the number of thread that can be run in parallel on your hardware
///
#include <thread>
#include <iostream>
using namespace std;

int main(){
    cout << "The maximum number of hardware parallel thread is " <<
        thread::hardware_concurrency() << endl;
}
