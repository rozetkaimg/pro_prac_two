#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "menu_utils.h"

using namespace std;

enum class TaskUnit {
    TRANSACTION = 1,
    CIRCUS,
    PHYSICS,
    CARS,
    FESTIVAL,
    NORMALIZATION,
    SENSORS,
    LOG,
    ANIMALS,
    PATIENT
};

std::string getTaskName(TaskUnit task) {
    switch (task) {
        case TaskUnit::TRANSACTION:   return "Обработка финансовых транзакций";
        case TaskUnit::CIRCUS:        return "Планирование цирковых выступлений";
        case TaskUnit::PHYSICS:       return "Анализ энергии электронов";
        case TaskUnit::CARS:          return "Формирование колонны автомобилей для парада";
        case TaskUnit::FESTIVAL:      return "Формирование программы музыкального фестиваля";
        case TaskUnit::NORMALIZATION: return "Нормализация и отчет по баллам студентов";
        case TaskUnit::SENSORS:       return "Коррекция данных датчиков";
        case TaskUnit::LOG:           return "Очистка журнала событий";
        case TaskUnit::ANIMALS:       return "Выбор лучших номеров с животными";
        case TaskUnit::PATIENT:       return "Формирование очереди пациентов на обследование";
        default:                      return "Неизвестная задача";
    }
}
void displayMenu() {
    cout << "\nПожалуйста, выберите задачу для запуска:" << endl;
    cout << static_cast<int>(TaskUnit::TRANSACTION)   << ". " << getTaskName(TaskUnit::TRANSACTION)   << endl;
    cout << static_cast<int>(TaskUnit::CIRCUS)        << ". " << getTaskName(TaskUnit::CIRCUS)        << endl;
    cout << static_cast<int>(TaskUnit::PHYSICS)       << ". " << getTaskName(TaskUnit::PHYSICS)       << endl;
    cout << static_cast<int>(TaskUnit::CARS)          << ". " << getTaskName(TaskUnit::CARS)          << endl;
    cout << static_cast<int>(TaskUnit::FESTIVAL)      << ". " << getTaskName(TaskUnit::FESTIVAL)      << endl;
    cout << static_cast<int>(TaskUnit::NORMALIZATION) << ". " << getTaskName(TaskUnit::NORMALIZATION) << endl;
    cout << static_cast<int>(TaskUnit::SENSORS)       << ". " << getTaskName(TaskUnit::SENSORS)       << endl;
    cout << static_cast<int>(TaskUnit::LOG)           << ". " << getTaskName(TaskUnit::LOG)           << endl;
    cout << static_cast<int>(TaskUnit::ANIMALS)       << ". " << getTaskName(TaskUnit::ANIMALS)       << endl;
    cout << static_cast<int>(TaskUnit::PATIENT)       << ". " << getTaskName(TaskUnit::PATIENT)       << endl;
    cout << "0. Выход" << endl;
    cout << "Введите номер задачи: ";
}

int main() {
    int taskId_int;
    TaskUnit taskId_enum;

    do {
        displayMenu();
        cin >> taskId_int;

        if (cin.fail()) {
            cout << "\nНекорректный ввод. Пожалуйста, введите число." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            taskId_int = -1;
        }
        if (taskId_int == 0) {
            cout << "\nВыход из программы..." << endl;
            break;
        }
        if (taskId_int != -1) {
            taskId_enum = static_cast<TaskUnit>(taskId_int);

            cout << "\nЗапуск задачи: " << getTaskName(taskId_enum) << "..." << endl;
            switch (taskId_enum) {
                case TaskUnit::TRANSACTION:
                    finance_transaction();
                    break;
                case TaskUnit::CIRCUS:
                    scheduler_circus();
                    break;
                case TaskUnit::PHYSICS:
                    energy_analyzer();
                    break;
                case TaskUnit::CARS:
                    organizer_parade();
                    break;
                case TaskUnit::FESTIVAL:
                    scheduler_festival();
                    break;
                case TaskUnit::NORMALIZATION:
                    processing_score();
                    break;
                case TaskUnit::SENSORS:
                    sensor_corrector();
                    break;
                case TaskUnit::LOG:
                    cleaner_log();
                    break;
                case TaskUnit::ANIMALS:
                    selector_animals();
                    break;
                case TaskUnit::PATIENT:
                    queue_patient();
                    break;
                default:
                    if (taskId_int != -1) {
                        cout << "\nНеверный ID задачи (" << taskId_int << "). Пожалуйста, выберите из списка." << endl;
                    }
            }
            cout << "\nЗадача завершена." << endl;
        }
        cout << "\nНажмите Enter для возврата в меню...";
        if(taskId_int != -1 && !cin.eof()) {
            if (cin.peek() == '\n') {
                cin.ignore();
            }
        } else if (cin.eof()){
            break;
        }
        cin.get();


    } while (true);

    return 0;
}