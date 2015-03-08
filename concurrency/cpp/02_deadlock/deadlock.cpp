///
/// Example of deadlock
///
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <chrono>
using namespace std;

const string STEW_DESC = "[stew] ";
const string PUDDING_DESC = "[pudding] ";

void stew(mutex& burner, mutex& mixer){
    cout << "[stew] Locking Burner" << endl;
    lock_guard<mutex> bl(burner);
    cout << "[stew] Burner is locked" << endl;

    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "[stew] Locking Mixer" << endl;
    lock_guard<mutex> ml(mixer);
    cout << "[stew] Mixer is locked" << endl;

    cout << STEW_DESC << "[stew] Preparing" << endl;
}

void pudding(mutex& burner, mutex& mixer){
 
    cout << "[pudding] Locking Mixer" << endl;
    lock_guard<mutex> ml(mixer);
    cout << "[pudding] Mixer is locked" << endl;
   
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "[pudding] Locking Burner" << endl;
    lock_guard<mutex> bl(burner);
    cout << "[pudding] Burner is locked" << endl;

    cout << "[pudding] Preparing" << endl;
}

int main(){
    mutex burner, mixer;
    thread stew_thread(stew, ref(burner), ref(mixer));
    thread pudding_thread(pudding, ref(burner), ref(mixer));
    stew_thread.join();
    pudding_thread.join();
}

