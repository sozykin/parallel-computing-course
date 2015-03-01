#include <iostream>
#include <thread>
using namespace std;

void thread_func(){
    cout << "Hello world from function!"  << endl;
}

class thread_functor{
    public:
        void operator()() const {
            cout << "Hello world from functor!"  << endl;
        }
};


int main() {
    // Creating new thread which will run the fuction thread_func
    thread t(thread_func);
    t.join();
    
    // Creating new thread which will run the supplied lambda expression
    thread t1([]{
        cout << "Hello world from lambda!" << endl;
    }); 
    t1.join();
    
    // Creating new thread which will run the fuction object 
    // Please notice the special syntax to deal with "most vexing parse"
    thread t2{thread_functor()};
    t2.join();
}
