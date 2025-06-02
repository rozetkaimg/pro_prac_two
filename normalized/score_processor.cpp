#include "score_processor.h"

namespace ScoreProcessing {

std::vector<std::string> generateNormalizedScoreReport(
    const std::map<std::string, int>& student_scores,
    const NormalizationParams& params
) {
    std::vector<std::string> report_lines;
    report_lines.reserve(student_scores.size());
    std::transform(
        student_scores.begin(), student_scores.end(),
        std::back_inserter(report_lines),
        [&params](const std::pair<const std::string, int>& student_data) {
            const std::string& name = student_data.first;
            int original_score = student_data.second;
            double calculated_score_double = 
                static_cast<double>(original_score) * (1.0 + params.percentage_increase_factor) 
                + params.flat_bonus;
            int potential_new_score_rounded = static_cast<int>(std::round(calculated_score_double));
            int new_score_after_min_cap = std::max(params.min_score, potential_new_score_rounded);
            int final_new_score = std::min(params.max_score, new_score_after_min_cap);
            int change = final_new_score - original_score;
            std::string status_message;
            if (final_new_score == params.max_score && new_score_after_min_cap > params.max_score) {
                status_message = "ограничен максимумом (" + std::to_string(params.max_score) + ")";
            } else if (final_new_score == params.min_score && potential_new_score_rounded < params.min_score) {
                status_message = "скорректирован до минимума (" + std::to_string(params.min_score) + ")";
            } else {
                status_message = "без спец. ограничений";
            }
            std::ostringstream oss;
            oss << name << ": [" << original_score << "] -> [" << final_new_score << "]";
            oss << " (Изменение: ";
            if (change >= 0) {
                oss << "+";
            }
            oss << change << ", Статус: " << status_message << ")";
            return oss.str();
        }
    );
    return report_lines;
}
}