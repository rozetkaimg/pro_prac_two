#ifndef ENERGY_ANALYZER_H
#define ENERGY_ANALYZER_H

#include <vector>

namespace ElectronCounter {
    long count_electrons_below_level(const std::vector<double> &energies, double ev_max);

    long count_electrons_above_level(const std::vector<double> &energies, double ec_min);

    long count_electrons_in_range(const std::vector<double> &energies, double e_min, double e_max);
}
void print_energies(const std::vector<double>& energies, const std::string& label);

#endif
