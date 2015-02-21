#include <iostream>
#include <thread>
using namespace std;

void thread_func(){
    // Pronting Hello world and ID of the thread
    cout << "Hello world from thread " << this_thread::get_id() << "!" << endl;
}

int main() {
    // Creating new thread which will run the thread_func function
    thread t(thread_func);
    // Waiting for thread to finish
    t.join();
    // Printing ID of main thread
    cout << "Main thread id is " << this_thread::get_id() << endl;
}
