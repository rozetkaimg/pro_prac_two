//
// Created by Stanislav Klepikov on 03.06.2025.
//
#ifndef SENSOR_DATA_CORRECTOR_H
#define SENSOR_DATA_CORRECTOR_H

#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

namespace DataCorrection {


    struct CorrectionParams {
        float lower_bound;
        float upper_bound;
        float marker_value;
        bool treat_input_nan_as_outlier;

        CorrectionParams(float l_bound, float u_bound, float marker, bool nan_is_outlier = false)
            : lower_bound(l_bound),
              upper_bound(u_bound),
              marker_value(marker),
              treat_input_nan_as_outlier(nan_is_outlier) {}
    };

    struct CorrectionResult {
        size_t replacements_count;

        CorrectionResult() : replacements_count(0) {}
    };
    CorrectionResult correctSensorReadings(
        std::vector<float>& readings,
        const CorrectionParams& params
    );
    void printReadingsSensor(const std::string& title, const std::vector<float>& readings);
}

#endif // SENSOR_DATA_CORRECTOR_H
