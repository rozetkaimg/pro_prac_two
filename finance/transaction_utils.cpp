
#include "transaction_utils.h"
#include <numeric>
#include <iomanip>
using namespace  std;

double sumTransactionsInCategoryAndDateRange(
    const multimap<string, Transaction> &transactions,
    const string &category,
    const string &startDate,
    const string &endDate
) {
    const auto range = transactions.equal_range(category);

    double totalAmount = accumulate(range.first, range.second, 0.0,
                                         [&startDate, &endDate](double currentSum,
                                                                const std::pair<const std::string, Transaction> &pair) {
                                             const Transaction &t = pair.second;
                                             bool dateConditionMet = true;

                                             if (!startDate.empty() && t.date < startDate) {
                                                 dateConditionMet = false;
                                             }
                                             if (dateConditionMet && !endDate.empty() && t.date > endDate) {
                                                 dateConditionMet = false;
                                             }

                                             if (dateConditionMet) {
                                                 return currentSum + t.amount;
                                             }
                                             return currentSum;
                                         }
    );
    return totalAmount;
}

CategoryStats getCategoryStatistics(
    const std::multimap<std::string, Transaction> &transactions,
    const std::string &category,
    const std::string &startDate,
    const std::string &endDate
) {
    auto range = transactions.equal_range(category);
    CategoryStats initialStats;
    CategoryStats resultStats = std::accumulate(range.first, range.second, initialStats,
                                                [&startDate, &endDate](CategoryStats currentStats,
                                                                       const std::pair<const std::string, Transaction> &
                                                                       pair) {
                                                    const Transaction &t = pair.second;
                                                    bool dateConditionMet = true;

                                                    if (!startDate.empty() && t.date < startDate)
                                                        dateConditionMet = false;
                                                    if (dateConditionMet && !endDate.empty() && t.date > endDate)
                                                        dateConditionMet = false;

                                                    if (dateConditionMet) {
                                                        currentStats.totalAmount += t.amount;
                                                        currentStats.transactionCount++;
                                                        if (!currentStats.firstTransactionProcessed || t.amount >
                                                            currentStats.maxTransactionAmount) {
                                                            currentStats.maxTransactionAmount = t.amount;
                                                            currentStats.maxTransactionDetails = t;
                                                        }
                                                        currentStats.firstTransactionProcessed = true;
                                                    }
                                                    return currentStats;
                                                }
    );
    return resultStats;
}


std::ostream &operator<<(std::ostream &os, const CategoryStats &stats) {
    os << std::fixed << std::setprecision(2);
    os << "Total Amount: " << stats.totalAmount
            << ", Transaction Count: " << stats.transactionCount;
    if (stats.transactionCount > 0) {
        os << ", Average Amount: " << (stats.totalAmount / stats.transactionCount);
        if (stats.firstTransactionProcessed) {
            os << ", Max Transaction: " << stats.maxTransactionAmount
                    << " on " << stats.maxTransactionDetails.date
                    << " (" << stats.maxTransactionDetails.description << ")";
        } else {
            os << ", Max Transaction: N/A (no valid transactions processed for max)";
        }
    } else {
        os << ", Average Amount: N/A, Max Transaction: N/A";
    }
    return os;
}
