#ifndef PARADE_ORGANIZER_H
#define PARADE_ORGANIZER_H

#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include <iostream>

enum class CarType {
    MILITARY,
    RETRO,
    SPORTS
};

struct Car;
std::string carTypeToString(CarType type);
int getCarTypeSortPriority(CarType type);


struct Car {
    std::string id;
    CarType type;
    std::optional<int> year;
    std::string sub_type;
    size_t original_order_index;

    Car(std::string car_id, CarType car_type, std::string car_sub_type, 
        std::optional<int> car_year, size_t original_idx)
        : id(std::move(car_id)), 
          type(car_type), 
          sub_type(std::move(car_sub_type)), 
          year(car_year), 
          original_order_index(original_idx) {}
    friend std::ostream& operator<<(std::ostream& os, const Car& car);
};
void organizeParade(std::vector<Car>& cars);

#endif // PARADE_ORGANIZER_H