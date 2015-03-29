///
/// OpenMP example of parallel for
///
#include<iostream>
#include<omp.h>
#include<chrono>
#include<random>

const int N = 10240;
double a[N], b[N], c[N];
const int MAX_VAL = 65535;

int main(){
    // Generating random numbers
    //
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_real_distribution<double> distribution(1,MAX_VAL);
    for (int i = 0; i < N; ++i) {
        b[i] = distribution(generator);
        c[i] = distribution(generator);
    }

    // Parallel sum of two vectors
    #pragma omp parallel for default (none) shared(a,b,c)
    for (int i = 0; i < N; ++i) {
        a[i] = b[i] + c[i];
    }

    std::cout << "a[N] = " << a[N-1] << std::endl;
}
