//
// Created by Stanislav Klepikov on 02.06.2025.
//

#include "circus_scheduler.h"
#include <algorithm>
#include <iostream>
#include <iomanip>


bool artist_has_required_skills(const Artist &artist, const ShowAct &act) {
    if (act.required_skills.empty()) {
        return true;
    }
    return std::all_of(act.required_skills.begin(), act.required_skills.end(),
                       [&](const std::string &req_skill) {
                           return std::find(artist.skills.begin(), artist.skills.end(), req_skill) != artist.skills.
                                  end();
                       });
}


void form_cast_for_evening_show(std::vector<Artist> &all_artists, std::vector<ShowAct> &show_program) {
    for (ShowAct &act: show_program) {
        act.status = "Ожидает";
        act.assigned_artist_ids.clear();

        std::vector<std::string> temp_assigned_ids_for_this_act;

        for (size_t i = 0; i < all_artists.size(); ++i) {
            Artist &potential_artist = all_artists[i];

            if (temp_assigned_ids_for_this_act.size() == static_cast<size_t>(act.performers_needed)) {
                break;
            }

            bool already_in_temp_list = false;
            for (const std::string &temp_id: temp_assigned_ids_for_this_act) {
                if (potential_artist.id == temp_id) {
                    already_in_temp_list = true;
                    break;
                }
            }
            if (already_in_temp_list) {
                continue;
            }

            bool skills_ok = artist_has_required_skills(potential_artist, act);
            int actual_stamina_cost = act.stamina_cost;
            bool stamina_ok = potential_artist.current_stamina >= actual_stamina_cost;
            bool act_limit_ok = potential_artist.acts_performed_today < potential_artist.max_acts_per_show;

            if (skills_ok && stamina_ok && act_limit_ok) {
                temp_assigned_ids_for_this_act.push_back(potential_artist.id);
            }
        }

        if (temp_assigned_ids_for_this_act.size() == static_cast<size_t>(act.performers_needed)) {
            act.status = "Укомплектован";
            for (const std::string &assigned_id: temp_assigned_ids_for_this_act) {
                act.assigned_artist_ids.push_back(assigned_id);
                for (Artist &artist_to_update: all_artists) {
                    if (artist_to_update.id == assigned_id) {
                        // int actual_stamina_cost = act.stamina_cost * act.difficulty; (если difficulty - множитель)
                        int actual_stamina_cost = act.stamina_cost;
                        artist_to_update.current_stamina -= actual_stamina_cost;
                        artist_to_update.acts_performed_today++;
                        break;
                    }
                }
            }
        } else {
            act.status = "Невозможно укомплектовать";
        }
    }
}

void print_artists_status(const std::vector<Artist> &artists) {
    std::cout << "\n--- Статус артистов ---" << std::endl; // Изменено для соответствия выводу в main
    std::cout << std::left << std::setw(5) << "ID" << std::setw(15) << "Имя"
            << std::setw(15) << "Выносливость" << std::setw(20) << "Номера (тек/макс)"
            << "Навыки" << std::endl;
    std::cout << std::string(75, '-') << std::endl;
    for (const auto &artist: artists) {
        std::cout << std::left << std::setw(5) << artist.id
                << std::setw(15) << artist.name
                << std::setw(3) << artist.current_stamina << "/" << std::setw(11) << artist.max_stamina
                << std::setw(3) << artist.acts_performed_today << "/" << std::setw(16) << artist.max_acts_per_show;
        for (size_t i = 0; i < artist.skills.size(); ++i) {
            std::cout << artist.skills[i] << (i == artist.skills.size() - 1 ? "" : ", ");
        }
        std::cout << std::endl;
    }
}

void print_show_program_status(const std::vector<ShowAct> &show_program) {
    std::cout << "\n--- Статус программы шоу ---" << std::endl;
    std::cout << std::left << std::setw(8) << "НомерID" << std::setw(25) << "Описание"
            << std::setw(12) << "Требуется" << std::setw(30) << "Статус"
            << "Назначенные артисты (ID)" << std::endl;
    std::cout << std::string(100, '-') << std::endl;
    for (const auto &act: show_program) {
        std::cout << std::left << std::setw(8) << act.id
                << std::setw(25) << act.description
                << std::setw(12) << act.performers_needed
                << std::setw(30) << act.status;
        if (act.assigned_artist_ids.empty()) {
            std::cout << "Нет";
        } else {
            for (size_t i = 0; i < act.assigned_artist_ids.size(); ++i) {
                std::cout << act.assigned_artist_ids[i] << (i == act.assigned_artist_ids.size() - 1 ? "" : ", ");
            }
        }
        std::cout << std::endl;
    }
}
