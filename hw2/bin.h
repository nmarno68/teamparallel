#include <list>
#include "common.h"

#ifndef TEAMPARALLEL_BIN_H
#define TEAMPARALLEL_BIN_H

class Bin{
    public:
        // Default constructor - This probably not exist - bin should be called with it's initial borders on creation
        Bin();

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

        // Destructor
        ~Bin();

        // Modifiers
        void set_neighbor(int bin_num, const bin* new_neighbor);
        void add_particle(const particle_t* new_p);

        // Does the particle-particle interactions
        void interact();

        // Check if particles are out of the bin's bounds, and move them to a neighboring bin if they are
        void validate();

//    private:
        // Borders of the world - need to know this so that particles bounce off the borders
        //  of the world when interacting.
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

        // For storing references to the particles in the bin
//        particle_t* particles;  // This would probably be better as a singly linked list - import from std?
//        int num_particles;
        std::list<particle_t> particles;

        // References to neighboring bins
        // The interacted flag is whether or not the particles in the two bins have interacted
        bin* bin1; // Diagonal Bottom Left
        bool interacted_bin1;
        bin* bin2; // Bottom
        bool interacted_bin2;
        bin* bin3; // Diagonal Bottom Right
        bool interacted_bin3;
        bin* bin4; // Left
        bool interacted_bin4;
        bin* bin6; // Right
        bool interacted_bin6;
        bin* bin7; // Diagonal Upper Left
        bool interacted_bin7;
        bin* bin8; // Up
        bool interacted_bin8;
        bin* bin9; // Diagonal Upper Right
        bool interacted_bin9;
};

#endif //TEAMPARALLEL_BIN_H
