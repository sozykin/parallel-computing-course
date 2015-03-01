///
/// Example of passing arguments to the thread
/// 
#include <iostream>
#include <thread>
#include <string>
using namespace std;

// Thread function with 2 arguments
void thread_func(string const &question, string &answer){
    cout << "The question: " << question << endl;
    // Return value through reference 
    answer = "42";
}

int main(){
    string answer;
    string question("Life, the Universe and Everything");
    // Passing arguments to the thread function in the thread constructor
    // question is copied
    // answer is pased by reference
    thread t(thread_func, question, ref(answer));
    t.join();
    cout << "The answer: " << answer << endl;
}
