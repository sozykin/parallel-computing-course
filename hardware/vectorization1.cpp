///
/// Basic vectorization example
///

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

// Vector size
const int SIZE = 10240;
// Maximum value for vector
const int MAX_VAL = 65535;


int main(){
    int a[SIZE] __attribute__ ((aligned (32)));
    int b[SIZE] __attribute__ ((aligned (32)));
    int c[SIZE] __attribute__ ((aligned (32)));
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<int> distribution(1,MAX_VAL);
    for (int i = 0; i < SIZE; ++i) {
        b[i] = distribution(generator);
        c[i] = distribution(generator);
    }
    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SIZE; ++i)
        a[i] = b[i] + c[i];
    std::chrono::high_resolution_clock::time_point t2 =
                std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Last vector element =  " << a[SIZE - 1] << std::endl;
    std::cout << "Counting time is " << duration << std::endl;
}

