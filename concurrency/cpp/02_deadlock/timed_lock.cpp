///
/// Example of deadlock
/// Locking for fixed time
///
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <chrono>
#include <random>
using namespace std;

const int MAX_PAUSE_TIME = 200;
const int LOCK_WAITING_TIME = 100;

void stew(timed_mutex& burner, timed_mutex& mixer){
    // Unique Locks for timed mutexes
    unique_lock<timed_mutex> bl(burner, defer_lock);
    unique_lock<timed_mutex> ml(mixer, defer_lock);
    // Random generator and distribution
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1,MAX_PAUSE_TIME);
    bool prepared = false;
    while (!prepared) {
        cout << "[stew] Locking Burner\n";
        if (bl.try_lock_for(chrono::milliseconds(LOCK_WAITING_TIME))) {
            cout << "[stew] Burner is locked\n";
            cout << "[stew] Locking Mixer\n";
            if (ml.try_lock_for(chrono::milliseconds(LOCK_WAITING_TIME))){
                cout << "[stew] Mixer is locked\n";
                cout << "[stew] Stew is prepared\n";
                prepared = true;
            } else {
                cout << "[stew] Can't lock Mixer\n";
                cout << "[stew] Unlocking Burner\n";
                bl.unlock();
            }
        } else {
            cout << "[stew] Can't lock Burner\n";
        }
        if (!prepared) {
            int pause_time = distribution(generator);
            cout << "[stew] Sleeping for " << pause_time << " milliseconds\n";
            this_thread::sleep_for(chrono::milliseconds(pause_time));
        }
    }

}

void pudding(timed_mutex& burner, timed_mutex& mixer){
 
    cout << "[pudding] Locking Mixer\n";
    unique_lock<timed_mutex> ml(mixer);
    cout << "[pudding] Mixer is locked\n";
   
    this_thread::sleep_for(chrono::milliseconds(500));

    cout << "[pudding] Locking Burner\n";
    unique_lock<timed_mutex> bl(burner);
    cout << "[pudding] Burner is locked\n";

    cout << "[pudding] Pudding is prepared\n";
}

int main(){
    timed_mutex burner, mixer;
    thread stew_thread(stew, ref(burner), ref(mixer));
    thread pudding_thread(pudding, ref(burner), ref(mixer));
    stew_thread.join();
    pudding_thread.join();
}

