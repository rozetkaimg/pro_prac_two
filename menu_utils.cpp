
#include "menu_utils.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <__ostream/basic_ostream.h>

#include "finance/transaction_utils.h"

struct Transaction;
using namespace std;

int finance_transaction() {
    cout << fixed << setprecision(2);
    multimap<string, Transaction> transactions;
    transactions.insert({"Еда", {250.50, "2024-05-20", "Обед в ресторане"}});
    transactions.insert({"Транспорт", {75.00, "2024-05-20", "Такси"}});
    transactions.insert({"Еда", {120.00, "2024-05-21", "Продукты"}});
    transactions.insert({"Развлечения", {300.00, "2024-05-21", "Кино"}});
    transactions.insert({"Транспорт", {50.25, "2024-05-22", "Бензин"}});
    transactions.insert({"Еда", {85.75, "2024-05-22", "Кофе и выпечка"}});
    transactions.insert({"Еда", {150.00, "2024-05-23", "Ужин"}});
    transactions.insert({"Еда", {25.00, "2024-06-01", "Фрукты"}});
    transactions.insert({"Еда", {180.00, "2024-06-02", "Продукты на неделю"}});
    transactions.insert({"Транспорт", {220.00, "2024-06-03", "Билеты на поезд"}});


    cout << "Сумма с фильтром по дате" << endl;
    string categoryToSum = "Еда";

    double totalForCategoryAllTime = sumTransactionsInCategoryAndDateRange(transactions, categoryToSum);
    cout << "Общая сумма (все даты) в категории \"" << categoryToSum << "\": " << totalForCategoryAllTime << endl;

    double totalForCategoryMay = sumTransactionsInCategoryAndDateRange(transactions, categoryToSum, "2024-05-01",
                                                                       "2024-05-31");
    cout << "Общая сумма (май 2024) в категории \"" << categoryToSum << "\": " << totalForCategoryMay << endl;

    double totalForCategoryJune = sumTransactionsInCategoryAndDateRange(transactions, categoryToSum, "2024-06-01");
    cout << "Общая сумма (с июня 2024) в категории \"" << categoryToSum << "\": " << totalForCategoryJune << endl;

    categoryToSum = "Транспорт";
    double totalTransportJune = sumTransactionsInCategoryAndDateRange(transactions, categoryToSum, "2024-06-01",
                                                                      "2024-06-30");
    cout << "Общая сумма (июнь 2024) в категории \"" << categoryToSum << "\": " << totalTransportJune << endl;


    cout << "\n Комплексная статистика" << endl;
    string categoryForStats = "Еда";
    CategoryStats statsMay = getCategoryStatistics(transactions, categoryForStats, "2024-05-01", "2024-05-31");
    cout << "Статистика для категории \"" << categoryForStats << "\" (май 2024): " << statsMay << endl;

    CategoryStats statsJune = getCategoryStatistics(transactions, categoryForStats, "2024-06-01");
    cout << "Статистика для категории \"" << categoryForStats << "\" (с июня 2024): " << statsJune << endl;

    CategoryStats statsAllTime = getCategoryStatistics(transactions, categoryForStats);
    cout << "Статистика для категории \"" << categoryForStats << "\" (все время): " << statsAllTime << endl;

    categoryForStats = "Развлечения";
    CategoryStats statsEntertainment = getCategoryStatistics(transactions, categoryForStats);
    cout << "Статистика для категории \"" << categoryForStats << "\" (все время): " << statsEntertainment << endl;

    categoryForStats = "Одежда"; // Категория без транзакций
    CategoryStats statsEmpty = getCategoryStatistics(transactions, categoryForStats);
    cout << "Статистика для категории \"" << categoryForStats << "\" (все время): " << statsEmpty << endl;

    return 0;
}
