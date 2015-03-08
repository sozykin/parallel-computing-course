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
    cout << "[stew] Locking Burner\n";
    lock_guard<mutex> bl(burner);
    cout << "[stew] Burner is locked\n";

    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "[stew] Locking Mixer\n";
    lock_guard<mutex> ml(mixer);
    cout << "[stew] Mixer is locked\n";

    cout << "[stew] Preparing\n";
}

void pudding(mutex& burner, mutex& mixer){
 
    cout << "[pudding] Locking Mixer\n";
    lock_guard<mutex> ml(mixer);
    cout << "[pudding] Mixer is locked\n";
   
    this_thread::sleep_for(chrono::milliseconds(100));

    cout << "[pudding] Locking Burner\n";
    lock_guard<mutex> bl(burner);
    cout << "[pudding] Burner is locked\n";

    cout << "[pudding] Preparing\n";
}

int main(){
    mutex burner, mixer;
    thread stew_thread(stew, ref(burner), ref(mixer));
    thread pudding_thread(pudding, ref(burner), ref(mixer));
    stew_thread.join();
    pudding_thread.join();
}

