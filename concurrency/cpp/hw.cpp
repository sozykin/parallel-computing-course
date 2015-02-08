#include <iostream>
#include <thread>
using namespace std;

void thread_func(){
    cout << "Hello world from thread " << this_thread::get_id() << "!" << endl;
}

int main() {
    thread t(thread_func);
    t.join();
    cout << "Main thread id is " << this_thread::get_id() << endl;
}
