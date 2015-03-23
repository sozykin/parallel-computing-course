///
/// Vectorization example for C++ vector
///

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

// Vector size
const long SIZE = 100000000;
// Maximum value for vector
const int MAX_VAL = 65535;

std::vector<int> a(SIZE), b(SIZE), c(SIZE);

int main(){
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

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
    std::cout << "Last vector element =  " << a[SIZE - 1] << std::endl;
    std::cout << "Counting time is " << duration << std::endl;
}

