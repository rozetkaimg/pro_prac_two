#include "animal_act_selector.h"
std::ostream& operator<<(std::ostream& os, const AnimalAct& act) {
    os << "Вид животного: " << std::setw(15) << std::left << act.animal_species
       << " | Описание: " << std::setw(35) << std::left << act.act_description
       << " | Рейтинг: " << std::setw(2) << std::right << act.audience_rating
       << " | Дрессировщик: " << act.trainer_name;
    return os;
}
void selectTopActs(std::vector<AnimalAct>& acts, size_t count_to_select) {
    if (acts.empty() || count_to_select == 0) {
        return;
    }
    size_t middle_element_index = std::min(count_to_select, acts.size());
    std::partial_sort(
        acts.begin(),
        acts.begin() + middle_element_index,
        acts.end(),
        [](const AnimalAct& a, const AnimalAct& b) {
            return a.audience_rating > b.audience_rating;
        }
    );
}