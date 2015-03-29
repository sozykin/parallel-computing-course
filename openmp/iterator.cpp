///
/// OpenMP example for C++ iterators
/// Requires OpenMP 3.0
///
#include<iostream>
#include<omp.h>
#include<chrono>
#include<random>
#include<vector>

const int N = 16;
const int MAX_VAL = 1024;


int main(){
    std::vector<double> vec;
    // Generating random numbers
    //
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_real_distribution<double> distribution(1,MAX_VAL);
    for (int i = 0; i < N; ++i) {
        vec.push_back(distribution(generator));
    }

    std::vector<double>::iterator it;
    #pragma omp parallel for shared(vec) 
    for (it = vec.begin(); it < vec.end(); ++it) {
        int thread_id = omp_get_thread_num();
        std::cout << "Thread id = " << thread_id <<
           ", vector element = " << *it << std::endl; 
    }
}
