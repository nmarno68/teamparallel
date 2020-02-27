#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <iostream>
#include "../include/common.h"
#include "../include/chunk.h"

//
//  benchmarking program
//
int main( int argc, char **argv )
{
    double avg_particles_per_chunk = 0;
    double avg_ghosts_per_chunk = 0;
    // Process command line arguments
    //      If option is help, show help menu
    if( find_option( argc, argv, "-h" ) >= 0 )
    {
        printf( "Options:\n" );
        printf( "-h to see this help\n" );
        printf( "-n <int> to set the number of particles.\n" );
        printf( "-v Verbose terminal output.\n" );
        printf( "-cutoff_scaling <double> scales size of chunks as a multiple of interaction range. Must be >=1.\n" );
        printf( "-o <filename> to specify the output file name\n" );
        printf( "-s <filename> to specify a summary file name\n" );
        printf( "-no turns off all correctness checks and particle output\n");
        return 0;
    }

    int num_particles = read_int( argc, argv, "-n", 1000 );
    double cutoff_scaling = read_double( argc, argv, "-nchunks", 5 );
    char *savename = read_string( argc, argv, "-o", NULL );
    char *sumname = read_string( argc, argv, "-s", NULL );
    FILE *fsave = savename ? fopen( savename, "w" ) : NULL;
    FILE *fsum = sumname ? fopen ( sumname, "a" ) : NULL;
    // Whether or not to do correctness checks and particle output
    bool opt_no = find_option(argc, argv, "-no") != -1;
    bool verbose = find_option(argc, argv, "-v") != -1;

    // Start the simulation time
    double simulation_time = read_timer();

    // Start doing stuff
    double field_size; // The size of the square particles exist in.

    // Create particles
    particle_t* particles = (particle_t*) malloc( num_particles * sizeof(particle_t) );
    set_size(num_particles, field_size);
    init_particles(num_particles, particles, field_size);

    // Bounds check on num_chunks based on field size
//    if (field_size / num_chunks < cutoff*4){
//        num_chunks = int(field_size / (cutoff*4));
//    }
    int num_chunks = int(field_size / (cutoff*cutoff_scaling));
    if(verbose){
        std::cout << "Number of chunks: " <<  num_chunks << std::endl;
        std::cout << "Size of field: " << field_size << std::endl;
        std::cout << "Size of chunk: " << field_size/num_chunks << std::endl;
    }

    // Initialize bins
    //      Create a 2d array of num_chunks x num_chunks chunks
    Chunk chunks[num_chunks*num_chunks];
    for(int i=0; i<num_chunks*num_chunks; i++){
        chunks[i].set_field_size(field_size);
        chunks[i].clear();
    }

    // Initialize vars
    int particle_index, chunk_x, chunk_y, x_lower, x_upper, y_lower, y_upper;
    bool x_mismatch, y_mismatch;
    int navg, nabsavg;
    double dmin, davg, absmin, absavg;

    // Loop!
    absmin = 1.0;
    absavg = 0.0;
    nabsavg = 0;
    for(int step=0; step<NSTEPS; step++){
        // Reset stats
	    navg = 0;
        davg = 0.0;
	    dmin = 1.0;

        // Assign particles to their chunks
        for(particle_index=0; particle_index<num_particles; particle_index++){
            // Calculate the chunk the particle belongs to and add it to that chunk
            chunk_x = int(particles[particle_index].x/field_size * num_chunks);
            chunk_y = int(particles[particle_index].y/field_size * num_chunks);
            chunks[chunk_x+chunk_y*num_chunks].add_particle(&particles[particle_index]);

            // Check if the particle is a ghost for any adjacent chunks
            //  If the chunk changes when x or y is changed by +- cutoff, then it is also a ghost for those chunks
            x_lower = max(int((particles[particle_index].x-cutoff)/field_size * num_chunks), 0);
            x_upper = min(int((particles[particle_index].x+cutoff)/field_size * num_chunks), num_chunks-1);
            y_lower = max(int((particles[particle_index].y-cutoff)/field_size * num_chunks), 0);
            y_upper = min(int((particles[particle_index].y+cutoff)/field_size * num_chunks), num_chunks-1);
            x_mismatch = x_lower != x_upper;
            y_mismatch = y_lower != y_upper; // If lower and upper are different, then there's a mismatch

            // Add ghosts as appropriate
            if(!x_mismatch && !y_mismatch) { // No mismatches, go to next particle
                continue;
            }
            if(x_mismatch) { // x is off
                if(x_lower != chunk_x){
                    chunks[x_lower+chunk_y*num_chunks].add_ghost(&particles[particle_index]);
                }
                if(x_upper != chunk_x){
                    chunks[x_upper+chunk_y*num_chunks].add_ghost(&particles[particle_index]);
                }
            }
            if(y_mismatch) { // y is off
                if(y_lower != chunk_y){
                    chunks[chunk_x+y_lower*num_chunks].add_ghost(&particles[particle_index]);
                }
                if(y_upper != chunk_y){
                    chunks[chunk_x+y_upper*num_chunks].add_ghost(&particles[particle_index]);
                }
            }
            if(x_mismatch && y_mismatch) { // Both are off
                if(x_lower != chunk_x){ // Using x_lower
                    if(y_lower != chunk_y){
                        chunks[x_lower+y_lower*num_chunks].add_ghost(&particles[particle_index]);
                    }
                    if(y_upper != chunk_y){
                        chunks[x_lower+y_upper*num_chunks].add_ghost(&particles[particle_index]);
                    }
                }
                if(x_upper != chunk_x){ // Using x_upper
                    if(y_lower != chunk_y){
                        chunks[x_upper+y_lower*num_chunks].add_ghost(&particles[particle_index]);
                    }
                    if(y_upper != chunk_y){
                        chunks[x_upper+y_upper*num_chunks].add_ghost(&particles[particle_index]);
                    }
                }
            }
        }

        // Apply forces
        for(int c=0; c<num_chunks*num_chunks; c++){
            chunks[c].apply_forces();
        }

        // Move particles & reset acceleration
        for(int i=0; i<num_particles; i++){
            move(particles[i], field_size);
            particles[i].ax = particles[i].ay = 0.0;
        }

        // Update stats & reset chunks
        int temp_num_ghosts = 0;
        int temp_num_particles = 0;
        for(int c=0; c<num_chunks*num_chunks; c++){
            temp_num_ghosts += chunks[c].get_num_ghosts();
            temp_num_particles += chunks[c].get_num_particles();
            navg += chunks[c].get_navg();
            davg += chunks[c].get_davg();
            double newmin = chunks[c].get_dmin();
            if(chunks[c].get_dmin() < 0.4){
                std::cout << "Step:" << step << "\n";
                std::cout << "Chunk is ##: " << c << std::endl;
            }
            if(newmin < dmin){
                dmin = newmin;
            }
            chunks[c].clear();
        }
        avg_ghosts_per_chunk += double(temp_num_ghosts) / (num_chunks*num_chunks);
        avg_particles_per_chunk += double(num_particles) / (num_chunks*num_chunks);

        // Update correctness output
        if (navg){
            absavg += davg/navg;
            nabsavg++;
            if (dmin < absmin){
                absmin = dmin;
            }
        }

        // Save snapshot if set to do so
        if(!opt_no && savename){
            if(step%SAVEFREQ==0){
                save( fsave, num_particles, particles, field_size);
            }
        }
    }

    if(nabsavg){
        absavg /= nabsavg;
    }

    // Get final simulation time
    simulation_time = read_timer() - simulation_time;

    // Perform correctness checks if set to do so
    if (!opt_no && absmin<0.4) {
        std::cout << "The minimum distance is below 0.4 meaning that some particle is not interacting.\n";
    }
    if (!opt_no && absavg<0.8) {
        std::cout << "The average distance is below 0.8 meaning that most particles are not interacting.\n";
    }

    // Save summary if set to do so
    if(fsum){
        fprintf(fsum, "%d %g\n", num_particles, simulation_time);
    }

    if(verbose){
        std::cout << "Sim time: " << simulation_time << std::endl;
        std::cout << "Absmin is: " << absmin << std::endl;
        std::cout << "Absavg is: " << absavg << std::endl;
        std::cout << "Avg Particles per chunk: " << avg_particles_per_chunk / NSTEPS << std::endl;
        std::cout << "Avg ghosts per chunk: " << avg_ghosts_per_chunk / NSTEPS << std::endl;
    }

}
