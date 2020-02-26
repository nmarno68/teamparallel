#include <vector>
#include <list>
#include "common.h"

#ifndef TEAMPARALLEL_BIN_H
#define TEAMPARALLEL_BIN_H

class Bin{
    public:
        // Parameterized constructor for initializing
        //  Do we want to also pass it the initial list of particles?
        //  This will set all neighboring bins to NULL - those need to be set after all bins have been created?
        //      And will be somewhat annoying.
        // This needs:
        //      The dimensions of the bin
        //
        Bin(const double init_top_border,
            const double init_bottom_border,
            const double init_left_border,
            const double init_right_border);

        // Modifiers
        void set_neighbor(int bin_num, Bin* new_neighbor);
        void add_particle(particle_t* new_p);

        // Does the particle-particle interactions
        void interact();

        // Check if particles are out of the bin's bounds, and move them to a neighboring bin if they are
        void validate();

        double get_dmin();
        double get_davg();
        int get_navg();

//    private:
        // Vars for tracking dmin, davg and navg for each bin
        double local_dmin;
        double local_davg;
        int local_navg;

        // Borders of the world - need to know this so that particles bounce off the borders
        // of the world when interacting.
        // Not really necessary?
//        double min_horizontal;
//        double max_horizontal;
//        double min_vertical;
//        double max_vertical;

        // Borders of the bin - use this to track when particles are added or removed
        double top_border;
        double bottom_border;
        double left_border;
        double right_border;
        double center_x;
        double center_y;

        // For storing references to the particles in the bin
//        particle_t* particles;  // This would probably be better as a singly linked list - import from std?
//        int num_particles;
        std::list<particle_t*> particles;

        // References to neighboring bins
        // The interacted flag is whether or not the particles in the two bins have interacted
        // 0 = bottom left
        // 1 = bottom
        // 2 = bottom right
        // 3 = left
        // 4 = right
        // 5 = top left
        // 6 = top
        // 7 = top right
        std::vector<Bin*> neighbor_bins = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}; //
        std::vector<bool> interacted_flags = {false, false, false, false, false, false, false, false};
};

#endif //TEAMPARALLEL_BIN_H
