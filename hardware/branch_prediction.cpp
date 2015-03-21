///
/// Branch prediction example
/// Based on http://stackoverflow.com/questions/11227809/why-is-processing-a-sorted-array-faster-than-an-unsorted-array
///

#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

const int SIZE = 32768;
std::vector<int> values;
const int MAX_VAL = 256;
const int REPEAT_NUM = 100000;

void processing(bool sorting) {
    long sum = 0;
    // Start time measurement
    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();
    if (sorting)
        // Sorting data
        std::sort(values.begin(), values.end());
    // Processing data
    for (int j = 0; j < REPEAT_NUM; ++ j)
        for (int i = 0; i < SIZE; ++i)
            if (values[i] >= MAX_VAL / 2)
                sum += values[i];
    // Stop time measurement
    std::chrono::high_resolution_clock::time_point t2 =
                std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    std::cout << "Sum = " << sum << std::endl;
    std::cout << "Calculating time = " << duration << std::endl;
}

int main(){
    // Filling the vector with random numbers
    std::cout << "Generating random numbers" << std::endl;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,MAX_VAL);
    for (int i = 0; i < SIZE; ++i)
            values.push_back(distribution(generator));

    // Processing unsorted data 
    std::cout << "Processing unsorted data" << std::endl;

    processing(false);
    
    // Sorting data
    std::sort(values.begin(), values.end());
    // Processing sorted data 
    std::cout << "Processing sorted data" << std::endl;
   
    processing(true); 
}
    

