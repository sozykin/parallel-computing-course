/// 
/// Example of false sharing
/// Counting the odd numbers in a matrix
/// 
#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <thread>

// Vector size
const long SIZE = 100000000;
// Maximum value for vector
const int MAX_VAL = 65535;

std::vector<int> values;

const int MAX_THREAD_NUM = 16;

// Odd number counter
int odds = 0;

// Array of odd number counters for threads
int odds_threads[MAX_THREAD_NUM] = {};

void sequential_odd_counting() {
    std::cout << "Counting odd numbers sequentially" << std::endl;
    odds = 0;
    std::chrono::high_resolution_clock::time_point t1 = 
        std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SIZE; ++i)
        if ( values[i] % 2 != 0 )
            ++odds;
    std::chrono::high_resolution_clock::time_point t2 = 
        std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    std::cout << "Odd number count is " << odds << std::endl;
    std::cout << "Counting time is " << duration << std::endl;
}

/// 
/// Function for counting odd number in the thread
void thread_odd_counter(int thread_id, int start_index, int end_index){
    odds_threads[thread_id] = 0;
    for (int i = start_index; i < end_index; ++i)
        if ( values[i] % 2 != 0 )
            // Increase thread's odd counter in the array
            ++odds_threads[thread_id]; 
}

void concurrent_odd_counting(int thread_num) {
    std::cout << "Counting odd numbers using " << thread_num << " threads"
        << std::endl;
    std::vector<std::thread> threads;
    // Assuming SIZE is divisible by THREAD_NUM
    const int part_size = SIZE / thread_num; 
    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();

    // Starting threads for counting odd numbers
    for (int i = 0; i < thread_num; ++i) {
        threads.push_back(std::thread(thread_odd_counter, i, part_size * i,
            part_size * (i + 1)));
    } 

    // Waiting for threads to finish
    for (std::thread& t : threads)
        t.join();

    // Summing up odd numbers count from different threads  sequentially
    odds = 0;
    for (int i = 0; i < thread_num; i++)
         odds += odds_threads[i];

    std::chrono::high_resolution_clock::time_point t2 = 
        std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    std::cout << "Odd number count is " << odds << std::endl;
    std::cout << "Counting time is " << duration << std::endl;

}

int main(){

    // Filling the vector with random numbers
    std::cout << "Generating random numbers" << std::endl;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,MAX_VAL);
    for (int i = 0; i < SIZE; ++i)
        values.push_back(distribution(generator));
    // Counting odd numbers sequentially
    sequential_odd_counting();
    // Counting odd numbers using several threads
    concurrent_odd_counting(2);
    concurrent_odd_counting(4);
    concurrent_odd_counting(8);
    return 0;    
}
