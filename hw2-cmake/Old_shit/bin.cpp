#include <iostream>
#include "bin.h"

#ifndef BOUNDS_CHECK
// 0 - No Bounds checking
// 1 - Bounds checking
#define BOUNDS_CHECK 0
#endif

Bin::Bin(const double init_top_border,
         const double init_bottom_border,
         const double init_left_border,
         const double init_right_border) {
    // Set bin borders & calculate center
    top_border = init_top_border;
    bottom_border = init_bottom_border;
    left_border = init_left_border;
    right_border = init_right_border;
    center_x = init_left_border + (init_right_border - init_left_border) / 2;
    center_y = init_top_border + (init_bottom_border - init_top_border) / 2;
}

void Bin::set_neighbor(int bin_num, Bin *new_neighbor) {
    neighbor_bins[bin_num] = new_neighbor;
}

void Bin::add_particle(particle_t *new_p) {
    particles.push_back(new_p);
}

// Does the particle / particle interactions to update acceleration values
void Bin::interact(double size) {
    // Zero out the local dmin, davg and navg
    local_davg = 0.0;
    local_dmin = 100.0;
    local_navg = 0;

    // Iterate through the particles in this bin, and interact with adjacent bins
    for(particle_t* particle : particles){
#if BOUNDS_CHECK == 1
        // Bounds check, so less things need to be compared
#else
        // Check every particle in every bin
        for(Bin* neighbor_bin : neighbor_bins){
            for(particle_t* neighbor_particle : neighbor_bin->particles){
                apply_force(*particle, *neighbor_particle, &local_dmin, &local_davg, &local_navg, size);
            }
        }
#endif
    }
}

void Bin::validate() {
    // Iterate over the particles in the particles list, check if they're still in bounds.
    // If they are, then great! If not, then move it to the proper bin
    // Flags to check if the thing is past a border
    bool past_left, past_right, past_top, past_bottom;
    for(auto particle : particles){
        // Check x axis
        if(particle->x < left_border){
            past_left = true;
            past_right = false;
        }
        else {
            past_left = false;
            past_right = particle->x > right_border;
        }

        // Check y axis
        if(particle->y < top_border){
            past_top = true;
            past_bottom = false;
        }
        else {
            past_top = false;
            past_bottom = particle->y > bottom_border;
        }

        // If appropriate, move the particle
        //  If particle is still in box, go to next particle
        if(!past_bottom && !past_top && !past_left && !past_right){
            continue;
        }
        // Check if above border
        else if(past_top){
            if(past_left){
                //5
            }
            else if (past_right){
                //7
            }
            else {
                //6
            }
        }
        // Check if below border
        else if(past_bottom){
            if(past_left){
                //0
            }
            else if (past_right){
                //2
            }
            else {
                //1
            }
        }
        // Must be out of bounds in middle - either 3 or 4
        else if(past_left){
            //3
        }
        else {
            //4
        }
    }
}

double Bin::get_dmin() {
    return local_dmin;
}
double Bin::get_davg() {
    return local_davg;
}
int Bin::get_navg() {
    return local_navg;
}

