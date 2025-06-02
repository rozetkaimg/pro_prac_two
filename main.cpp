#include <iostream>
#include <iomanip>
#include "menu_utils.h"
using namespace std;


enum class taskUnit {
    TRANSACTION = 1,
    CIRCUS,
    PHYSICS,
    CARS,
    FESTIVAL,
    NORMALIZATION
};

int main() {
    int taskId;
    cin >> taskId;
    switch (static_cast<taskUnit>(taskId)) {
        case taskUnit::TRANSACTION:
            finance_transaction();
        case taskUnit::CIRCUS:
            scheduler_circus();
            break;
        case taskUnit::PHYSICS:
            energy_analyzer();
            break;
        case taskUnit::CARS:
            organizer_parade();
            break;
        case taskUnit::FESTIVAL:
            scheduler_festival();
            break;
            case taskUnit::NORMALIZATION:

            break;
        default:
            cout << "Invalid Task ID" << endl;
    }
    return 0;
}
