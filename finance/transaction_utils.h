
#ifndef TRANSACTION_UTILS_H
#define TRANSACTION_UTILS_H

#include <string>
#include <map>
#include <iostream>


struct Transaction {
    double amount;
    std::string date;
    std::string description;
};

struct CategoryStats {
    double totalAmount = 0.0;
    int transactionCount = 0;
    double maxTransactionAmount = 0.0;
    Transaction maxTransactionDetails;
    bool firstTransactionProcessed = false;

    friend std::ostream &operator<<(std::ostream &os, const CategoryStats &stats);
};

double sumTransactionsInCategoryAndDateRange(
    const std::multimap<std::string, Transaction> &transactions,
    const std::string &category,
    const std::string &startDate = "",
    const std::string &endDate = ""
);

CategoryStats getCategoryStatistics(
    const std::multimap<std::string, Transaction> &transactions,
    const std::string &category,
    const std::string &startDate = "",
    const std::string &endDate = ""
);

#endif // TRANSACTION_UTILS_H
