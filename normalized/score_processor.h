#ifndef SCORE_PROCESSOR_H
#define SCORE_PROCESSOR_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>
namespace ScoreProcessing {
struct NormalizationParams {
    double percentage_increase_factor;
    int flat_bonus;
    int max_score;
    int min_score;
    NormalizationParams(double p_factor, int f_bonus, int m_score = 100, int min_s = 0)
        : percentage_increase_factor(p_factor),
          flat_bonus(f_bonus),
          max_score(m_score),
          min_score(min_s) {}
};
std::vector<std::string> generateNormalizedScoreReport(
    const std::map<std::string, int>& student_scores,
    const NormalizationParams& params
);

}

#endif // SCORE_PROCESSOR_H
