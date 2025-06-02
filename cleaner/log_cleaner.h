#ifndef LOG_CLEANER_H
#define LOG_CLEANER_H

#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>


struct LogEntry {
    std::string timestamp;
    int importanceLevel;
    std::string message;
    LogEntry(std::string ts, int level, std::string msg)
        : timestamp(std::move(ts)), importanceLevel(level), message(std::move(msg)) {}
    friend std::ostream& operator<<(std::ostream& os, const LogEntry& entry);
};

std::chrono::system_clock::time_point parseGlobalTimestamp(const std::string& timestamp_str);

void cleanLogEntries(
    std::vector<LogEntry>& logs,
    const std::string& cutoff_timestamp_str,
    int min_importance_threshold
);
void printFullLog(const std::string& title, const std::vector<LogEntry>& log_entries);
#endif // LOG_CLEANER_H