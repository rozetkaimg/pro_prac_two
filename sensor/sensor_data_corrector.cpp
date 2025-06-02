#include "sensor_data_corrector.h"

#include <iostream>

namespace DataCorrection {

    CorrectionResult correctSensorReadings(
        std::vector<float>& readings,
        const CorrectionParams& params
    ) {
        CorrectionResult result;
        auto outlier_predicate_and_counter =
            [&params, &result](float value) -> bool {
                bool is_outlier = false;

                if (params.treat_input_nan_as_outlier && std::isnan(value)) {
                    is_outlier = true;
                } else {

                    if (!std::isnan(value)) {
                        is_outlier = (value < params.lower_bound || value > params.upper_bound);
                    }
                }

                if (is_outlier) {
                    result.replacements_count++;
                    return true;
                }
                return false;
        };


        std::replace_if(readings.begin(), readings.end(),
                        outlier_predicate_and_counter,
                        params.marker_value);

        return result;
    }
    void printReadingsSensor(const std::string& title, const std::vector<float>& readings) {
        std::cout << title << ": [";
        bool first = true;
        for (float val : readings) {
            if (!first) {
                std::cout << ", ";
            }
            if (std::isnan(val)) {
                std::cout << "NaN";
            } else {
                std::cout << val;
            }
            first = false;
        }
        std::cout << "]" << std::endl;
    }

}


