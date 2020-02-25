#include "bin.h"
#include <iostream>

Bin::Bin() {
    std::cout << "This shouldn't be called." << std::endl;
    throw -1;
}

Bin::Bin(const double init_top_border,
         const double init_bottom_border,
         const double init_left_border,
         const double init_right_border) {
    // Set bin borders
    top_border = init_top_border;
    bottom_border = init_bottom_border;
    left_border = init_left_border;
    right_border = init_right_border;

    // Set neighbors to Null and their interacted_ flags to false
    bin1 = NULL;
    interacted_bin1 = false;
    bin2 = NULL;
    interacted_bin2 = false;
    bin3 = NULL;
    interacted_bin3 = false;
    bin4 = NULL;
    interacted_bin4 = false;
    bin6 = NULL;
    interacted_bin6 = false;
    bin7 = NULL;
    interacted_bin7 = false;
    bin8 = NULL;
    interacted_bin8 = false;
    bin9 = NULL;
    interacted_bin9 = false;
}

void Bin::set_neighbor(int bin_num, const bin *new_neighbor) {
    switch bin_num:
        case 1:
            bin1 = new_neighbor;
        case 2:
            bin2 = new_neighbor;
        case 3:
            bin3 = new_neighbor;
        case 4:
            bin4 = new_neighbor;
        case 6:
            bin6 = new_neighbor;
        case 7:
            bin7 = new_neighbor;
        case 8:
            bin8 = new_neighbor;
        case 9:
            bin9 = new_neighbor;
}


