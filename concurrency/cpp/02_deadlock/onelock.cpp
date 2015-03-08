///
/// Example of deadlock
/// Use only one lock at a time
///
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <chrono>
using namespace std;

void stew(mutex& burner, mutex& mixer){
    cout << "[stew] Locking Burner\n";
    unique_lock<mutex> bl(burner);
    cout << "[stew] Burner is locked\n";
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "[stew] Burning is finished\n";
    bl.unlock();

    cout << "[stew] Locking Mixer\n";
    unique_lock<mutex> ml(mixer);
    cout << "[stew] Mixer is locked\n";
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "[stew] Mixing is finished\n";
    ml.unlock();

    cout << "[stew] Stew is prepared\n";
}

void pudding(mutex& burner, mutex& mixer){
 
    cout << "[pudding] Locking Mixer\n";
    unique_lock<mutex> ml(mixer);
    cout << "[pudding] Mixer is locked\n";
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "[pudding] Mixing is finished\n";
    ml.unlock();

    cout << "[pudding] Locking Burner\n";
    unique_lock<mutex> bl(burner);
    cout << "[pudding] Burner is locked\n";
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "[pudding] Burning is finished\n";
    bl.unlock();

    cout << "[pudding] Pudding is prepared\n";
}

int main(){
    mutex burner, mixer;
    thread stew_thread(stew, ref(burner), ref(mixer));
    thread pudding_thread(pudding, ref(burner), ref(mixer));
    stew_thread.join();
    pudding_thread.join();
}

