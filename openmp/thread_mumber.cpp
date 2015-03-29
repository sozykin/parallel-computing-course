///
/// Example of setting thread number in OpenMP
/// In production use OMP_NUM_THREADS environment variable instead
///
#include<iostream>
#include<omp.h>

const int NUM_THREADS_1 = 2;
const int NUM_THREADS_2 = 4;

int main(){
    #pragma omp parallel
    {
        int nthread = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        std::cout << "Hello, world from thread " << thread_id << " of " 
            << nthread << std::endl;
    }
    std::cout << "Setting thread number = " << NUM_THREADS_1
        << std::endl;
    #pragma omp parallel num_threads(NUM_THREADS_1)
    {
        int nthread = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        std::cout << "Hello, world from thread " << thread_id << " of " 
            << nthread << std::endl;
    }

    std::cout << "Setting thread number = " << NUM_THREADS_2
        << std::endl;
    omp_set_num_threads(NUM_THREADS_2);
    #pragma omp parallel 
    {
        int nthread = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        std::cout << "Hello, world from thread " << thread_id << " of " 
            << nthread << std::endl;
    }
}
