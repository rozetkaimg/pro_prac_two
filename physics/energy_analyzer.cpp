#include "energy_analyzer.h"
#include <algorithm>
#include <functional>
#include <iostream>

namespace ElectronCounter {
    long count_electrons_below_level(const std::vector<double> &energies, double ev_max) {
        return std::count_if(energies.begin(), energies.end(),
                             [ev_max](double energy) {
                                 return energy < ev_max;
                             });
    }

    long count_electrons_above_level(const std::vector<double> &energies, double ec_min) {
        return std::count_if(energies.begin(), energies.end(),
                             [ec_min](double energy) {
                                 return energy > ec_min;
                             });
    }

    long count_electrons_in_range(const std::vector<double> &energies, double e_min, double e_max) {
        if (e_min > e_max) {
            return 0;
        }
        return std::count_if(energies.begin(), energies.end(),
                             [e_min, e_max](double energy) {
                                 return energy >= e_min && energy <= e_max;
                             });
    }
}
void print_energies(const std::vector<double>& energies, const std::string& label) {
    std::cout << label << ": [";
    bool first = true;
    for (double energy : energies) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << energy;
        first = false;
    }
    std::cout << "]" << std::endl;
}