#include "parade_organizer.h"

std::string carTypeToString(CarType type) {
    switch (type) {
        case CarType::MILITARY: return "Военный";
        case CarType::RETRO:    return "Ретро";
        case CarType::SPORTS:   return "Спортивный";
        default:                return "Неизвестный тип";
    }
}
int getCarTypeSortPriority(CarType type) {
    switch (type) {
        case CarType::MILITARY: return 0;
        case CarType::RETRO:    return 1;
        case CarType::SPORTS:   return 2;
        default:                return 3;
    }
}
std::ostream& operator<<(std::ostream& os, const Car& car) {
    os << "ID: " << car.id 
       << ", Тип: " << carTypeToString(car.type);
    if (!car.sub_type.empty()) {
        os << " (" << car.sub_type << ")";
    }
    if (car.type == CarType::RETRO && car.year.has_value()) {
        os << ", Год: " << car.year.value();
    }
    return os;
}

void organizeParade(std::vector<Car>& cars) {
    std::stable_sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
        int priority_a = getCarTypeSortPriority(a.type);
        int priority_b = getCarTypeSortPriority(b.type);
        if (priority_a != priority_b) {
            return priority_a < priority_b;
        }
        switch (a.type) {
            case CarType::MILITARY:
                if (a.sub_type != b.sub_type) {
                    return a.sub_type < b.sub_type;
                }
                break; 
            case CarType::RETRO:
                if (a.year.has_value() && b.year.has_value()) {
                    if (a.year.value() != b.year.value()) {
                        return a.year.value() < b.year.value();
                    }
                } else if (a.year.has_value()) {
                    return true;
                } else if (b.year.has_value()) {
                    return false;
                }
                break;
            case CarType::SPORTS:
                if (a.sub_type != b.sub_type) {
                    return a.sub_type < b.sub_type;
                }
                break;
        }
        return false;
    });
}