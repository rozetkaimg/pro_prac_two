#include <iostream>
#include <iomanip>
#include "menu_utils.h"
using namespace std;


enum class taskUnit {
    TRANSACTION = 1,
};

int main() {
    int taskId;
    cin >> taskId;
    switch (static_cast<taskUnit>(taskId)) {
        case taskUnit::TRANSACTION:
            finance_transaction();
            break;
        default:
            cout << "Invalid Task ID" << endl;
    }
    return 0;
}
