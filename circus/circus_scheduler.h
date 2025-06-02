#ifndef CIRCUS_SCHEDULER_H
#define CIRCUS_SCHEDULER_H

#include <vector>
#include <string>

struct Artist {
    std::string id;
    std::string name;
    std::vector<std::string> skills;
    int current_stamina;
    int max_stamina;
    int acts_performed_today;
    int max_acts_per_show;
};

struct ShowAct {
    std::string id;
    std::string description;
    std::vector<std::string> required_skills;
    int performers_needed;
    int difficulty;
    int stamina_cost;
    std::vector<std::string> assigned_artist_ids;
    std::string status;
};

bool artist_has_required_skills(const Artist &artist, const ShowAct &act);

void form_cast_for_evening_show(std::vector<Artist> &all_artists, std::vector<ShowAct> &show_program);

void print_artists_status(const std::vector<Artist> &artists);

void print_show_program_status(const std::vector<ShowAct> &show_program);

#endif // CIRCUS_SCHEDULER_H
