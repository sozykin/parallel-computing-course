///
/// Hello world OpenMP example
///
#include<stdio.h>
#include<omp.h>

int main(){
    #pragma omp parallel
    {
        int nthread = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        printf("Hello, world from thread %i of %i\n!", thread_id, nthread);
    }
}
