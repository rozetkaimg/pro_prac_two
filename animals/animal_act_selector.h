#ifndef ANIMAL_ACT_SELECTOR_H
#define ANIMAL_ACT_SELECTOR_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>

struct AnimalAct {
    std::string animal_species;
    std::string act_description;
    int audience_rating;
    std::string trainer_name;

    AnimalAct(std::string species, std::string description, int rating, std::string trainer)
        : animal_species(std::move(species)),
          act_description(std::move(description)),
          audience_rating(rating),
          trainer_name(std::move(trainer)) {}
    friend std::ostream& operator<<(std::ostream& os, const AnimalAct& act);
};
void selectTopActs(std::vector<AnimalAct>& acts, size_t count_to_select);

#endif // ANIMAL_ACT_SELECTOR_H
