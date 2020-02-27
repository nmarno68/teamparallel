#include "common.h"
#include <list>
#include <vector>

#ifndef HW2_CHUNK_H
#define HW2_CHUNK_H

class Chunk{
public:
    void set_field_size(double size);

    void add_particle(particle_t* new_particle);
    void add_ghost(particle_t* new_particle);
    void apply_forces();
    void clear();

    int get_num_particles();
    int get_num_ghosts();
    int get_navg();
    double get_davg();
    double get_dmin();

private:
    std::list<particle_t*> particles;
    std::list<particle_t*> ghost_particles;
    double field_size;
    int navg;
    double davg;
    double dmin;
};

#endif //HW2_CHUNK_H
