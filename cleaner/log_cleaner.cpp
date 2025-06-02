#include "log_cleaner.h"
#include <algorithm>

std::ostream& operator<<(std::ostream& os, const LogEntry& entry) {
    os << "[" << entry.timestamp << "] Importance: " << entry.importanceLevel << " | Message: " << entry.message;
    return os;
}

std::chrono::system_clock::time_point parseGlobalTimestamp(const std::string& timestamp_str) {
    std::tm t{};
    std::istringstream ss(timestamp_str);
    ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
        std::cerr << "Ошибка парсинга времени: " << timestamp_str << std::endl;
        return std::chrono::system_clock::time_point::min();
    }
    t.tm_isdst = -1;
    std::time_t time_c = std::mktime(&t);
    if (time_c == -1) {
        std::cerr << "Ошибка конвертации std::tm в time_t для: " << timestamp_str << std::endl;
        return std::chrono::system_clock::time_point::min();
    }
    return std::chrono::system_clock::from_time_t(time_c);
}
void cleanLogEntries(
    std::vector<LogEntry>& logs,
    const std::string& cutoff_timestamp_str,
    int min_importance_threshold
) {
    std::chrono::system_clock::time_point cutoff_datetime = parseGlobalTimestamp(cutoff_timestamp_str);
    if (cutoff_datetime == std::chrono::system_clock::time_point::min() && !cutoff_timestamp_str.empty()) {
        std::cerr << "Внимание: не удалось корректно распознать время отсечки. Результаты могут быть неверными." << std::endl;
    }
    logs.erase(
        std::remove_if(logs.begin(), logs.end(),
            [&cutoff_datetime, min_importance_threshold](const LogEntry& entry) {
                std::chrono::system_clock::time_point entry_datetime = parseGlobalTimestamp(entry.timestamp);
                bool is_old = entry_datetime < cutoff_datetime;
                bool is_not_important = entry.importanceLevel < min_importance_threshold;
                return is_old || is_not_important;
            }
        ),
        logs.end()
    );
}

void printFullLog(const std::string& title, const std::vector<LogEntry>& log_entries) {
    std::cout << "--- " << title << " ---" << std::endl;
    if (log_entries.empty()) {
        std::cout << "(Журнал пуст)" << std::endl;
    } else {
        for (const auto& entry : log_entries) {
            std::cout << entry << std::endl;
        }
    }
    std::cout << "-----------------------------" << std::string(title.length(), '-') << std::endl;
}