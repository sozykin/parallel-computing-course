///
/// Example of deadlock
///
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <chrono>
using namespace std;

void stew(mutex& burner, mutex& mixer){
    cout << "[stew] Locking Burner and Mixer\n";
    // Create lock guards but not lock the mutexes
    unique_lock<mutex> bl(burner, defer_lock);
    unique_lock<mutex> ml(mixer, defer_lock);
    // Lock both mutexes simultaneously
    lock(bl,ml);
    cout << "[stew] Mixer and Burner are locked\n";
    cout << "[stew] Preparing\n";
}

void pudding(mutex& burner, mutex& mixer){
 
    cout << "[pudding] Locking Mixer and Burner\n";
    // Lock both mutexes simultaneously
    lock(mixer, burner);
    // Creating lock guards for already locked mutexes
    lock_guard<mutex> ml(mixer, adopt_lock);
    lock_guard<mutex> bl(burner, adopt_lock);
    cout << "[pudding] Burner and Mixer is locked\n";
    cout << "[pudding] Preparing\n";
}

int main(){
    mutex burner, mixer;
    thread stew_thread(stew, ref(burner), ref(mixer));
    thread pudding_thread(pudding, ref(burner), ref(mixer));
    stew_thread.join();
    pudding_thread.join();
}

