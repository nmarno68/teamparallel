#include <omp.h>
#include <iostream>

int main(){
    #pragma omp parallel
    {
        std::cout << "Hello world from thread " << omp_get_thread_num() << "!" << std::endl;
    };
    return 0;
}
