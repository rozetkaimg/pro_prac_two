#include "festival_scheduler.h"
#include <iomanip>

std::string genreToString(Genre g) {
    switch (g) {
        case Genre::FOLK:      return "Фолк";
        case Genre::CLASSICAL: return "Классика";
        case Genre::JAZZ:      return "Джаз";
        case Genre::ROCK:      return "Рок";
        default:               return "Неизвестный жанр";
    }
}

std::string eraToString(ClassicalEra e) {
    switch (e) {
        case ClassicalEra::BAROQUE:    return "Барокко";
        case ClassicalEra::CLASSICISM: return "Классицизм";
        case ClassicalEra::ROMANTICISM:return "Романтизм";
        case ClassicalEra::MODERN:     return "Современная";
        default:                       return "Неизвестная эпоха";
    }
}

int getGenreSortPriority(Genre g) {
    switch (g) {
        case Genre::FOLK:      return 0;
        case Genre::CLASSICAL: return 1;
        case Genre::JAZZ:      return 2;
        case Genre::ROCK:      return 3;
        default:               return 4;
    }
}
int getEraSortPriority(ClassicalEra e) {
    switch (e) {
        case ClassicalEra::BAROQUE:    return 0;
        case ClassicalEra::CLASSICISM: return 1;
        case ClassicalEra::ROMANTICISM:return 2;
        case ClassicalEra::MODERN:     return 3;
        default:                       return 4;
    }
}
std::ostream& operator<<(std::ostream& os, const ArtistF& artist) {
    os << "Имя: " << std::setw(25) << std::left << artist.name
       << " | Жанр: " << std::setw(10) << std::left << genreToString(artist.genre_enum);
    if (artist.genre_enum == Genre::CLASSICAL && artist.era_enum.has_value()) {
        os << " (" << std::setw(12) << std::left << eraToString(artist.era_enum.value()) << ")";
    } else {
        os << std::setw(15) << std::left << "";
    }
    os << " | Популярность: " << std::setw(3) << std::right << artist.popularity_score
       << " | Длительность: " << std::setw(3) << artist.performance_duration_minutes << " мин."
       << " (Заявка #" << artist.application_order_index + 1 << ")";
    return os;
}
void scheduleArtists(std::vector<ArtistF>& artists) {
    std::stable_sort(artists.begin(), artists.end(), [](const ArtistF& a, const ArtistF& b) {
        int genre_priority_a = getGenreSortPriority(a.genre_enum);
        int genre_priority_b = getGenreSortPriority(b.genre_enum);
        if (genre_priority_a != genre_priority_b) {
            return genre_priority_a < genre_priority_b;
        }

        switch (a.genre_enum) {
            case Genre::CLASSICAL: {
                if (!a.era_enum.has_value() || !b.era_enum.has_value()) {
                    if (a.era_enum.has_value() && !b.era_enum.has_value()) return true;
                    if (!a.era_enum.has_value() && b.era_enum.has_value()) return false;
                } else {
                    int era_priority_a = getEraSortPriority(a.era_enum.value());
                    int era_priority_b = getEraSortPriority(b.era_enum.value());
                    if (era_priority_a != era_priority_b) {
                        return era_priority_a < era_priority_b;
                    }
                }
                if (a.popularity_score != b.popularity_score) {
                    return a.popularity_score > b.popularity_score;
                }
                break;
            }
            case Genre::FOLK:
            case Genre::JAZZ:
            case Genre::ROCK: {
                if (a.popularity_score != b.popularity_score) {
                    return a.popularity_score > b.popularity_score;
                }
                break;
            }
        }
        return false;
    });
}