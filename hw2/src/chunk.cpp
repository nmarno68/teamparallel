#include <iostream>
#include <cmath>
#include "../include/chunk.h"

void Chunk::set_field_size(double size){
    field_size=size;
}

void Chunk::add_particle(particle_t* new_particle) {
    particles.push_back(new_particle);
}

void Chunk::add_ghost(particle_t* new_particle) {
    ghost_particles.push_back(new_particle);
}

void Chunk::apply_forces() {
    // Make iterators
    std::list<particle_t*>::const_iterator outer;
    std::list<particle_t*>::const_iterator inner;

    // Iterate over all actual particles
    for(outer= particles.begin(); outer != particles.end(); outer++){
        // Iterate over ghost particles
        for(inner=ghost_particles.begin(); inner != ghost_particles.end(); inner++){
            apply_force(**outer, **inner, &dmin, &davg, &navg, field_size);
        }
        // Iterate over remaining local particles
        inner = outer;
        inner++;
        for(; inner != particles.end(); ++inner){
            apply_force(**outer, **inner, &dmin, &davg, &navg, field_size);
            apply_force(**inner, **outer, &dmin, &davg, &navg, field_size);
        }
//        // Iterate over remaining local particles
//        for(inner=particles.begin(); inner != particles.end(); inner++){
//            apply_force(**outer, **inner, &dmin, &davg, &navg, field_size);
//        }
    }
}

void Chunk::clear() {
    particles.clear();
    ghost_particles.clear();
    navg=0;
    dmin=1.0;
    davg=0.0;
}

int Chunk::get_num_particles(){
    return particles.size();
}

int Chunk::get_num_ghosts(){
    return ghost_particles.size();
}

int Chunk::get_navg() {
    return navg;
}

double Chunk::get_davg() {
    return davg;
}

double Chunk::get_dmin() {
    return dmin;
}