#include "../include/thing.h"
#include "../include/common.h"
#include <iostream>
#include <list>

int main(int argc, char *argv[]){
    double x;
    x=1.1;
    std::cout << int(x) << std::endl;
    x=1.5;
    std::cout << int(x) << std::endl;
    x=1.9;
    std::cout << int(x) << std::endl;
    x=1.999;
    std::cout << int(x) << std::endl;

//    double size;
//    int num_bins = 5; // Number of bins
//    int n = 100000; //Number of particles
//    auto *particles = (particle_t*) malloc( n * sizeof(particle_t) );
//    set_size( n, size );
//    init_particles( n, particles, size );
//    std::list<particle_t*> x;
//    particles[0].x = 0;
//    particles[1].x = 1;
//    particles[2].x = 2;
//    particles[3].x = 3;
//    x.push_back(&particles[0]);
//    x.push_back(&particles[1]);
//    x.push_back(&particles[2]);
//    x.push_back(&particles[3]);
//    std::list<particle_t*>::const_iterator outer;
//    for(outer=x.begin(); outer != x.end(); ++outer){
//        std::cout << "\n" << (*outer)->x;
//    }
//    int x = 0;
//    int y = -1;
//    int z = 1;
//    if(x){
//        std::cout << "x is true\n";
//    }
//    if(!y){
//        std::cout << "y is true\n";
//    }
//    if(!z){
//        std::cout << "z is true\n";
//    }
//
//
//    std::cout << "Size: " << size << std::endl;
//    std::cout << "Bins: " << num_bins << std::endl;
//    int basic, cutoff_low, cutoff_high;
//    int count = 0;
//    for(int particle_index=0; particle_index<n; particle_index++){
////        std::cout << "\n";
////        std::cout << particles[particle_index].x << std::endl;
////        std::cout << particles[particle_index].x/size * num_bins << std::endl;
//        basic=int(particles[particle_index].x/size * num_bins);
//        cutoff_low=int((particles[particle_index].x-cutoff)/size * num_bins);
//        cutoff_high=int((particles[particle_index].x+cutoff)/size * num_bins);
//        if(cutoff_high!=cutoff_low){
////            std::cout << "Mismatch! Is this a ghost particle?\n";
////            std::cout << particles[particle_index].x << std::endl;
////            std::cout << "\tBasic: " << basic << std::endl;
////            std::cout << "\tLow: " << cutoff_low << std::endl;
////            std::cout << "\tHigh: " << cutoff_high << std::endl << std::endl;
//            count++;
//        }
////        std::cout << int(particles[particle_index].x/size * num_bins) << std::endl;
//    }
//    std::cout << "Number of ghost particles: " << count << std::endl;
    return 0;
}
