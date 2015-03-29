///
/// Hello world OpenMP example
///
#include<iostream>
#include<omp.h>

int main(){
    #pragma omp parallel
    {
        int nthread = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        std::cout << "Hello, world from thread " << thread_id << " of " 
            << nthread << std::endl;
    }
}
