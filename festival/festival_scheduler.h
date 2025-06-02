#ifndef FESTIVAL_SCHEDULER_H
#define FESTIVAL_SCHEDULER_H

#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include <iostream>
enum class Genre {
    FOLK,
    CLASSICAL,
    JAZZ,
    ROCK
};
enum class ClassicalEra {
    BAROQUE,
    CLASSICISM,
    ROMANTICISM,
    MODERN
};

struct ArtistF;
std::string genreToString(Genre g);
std::string eraToString(ClassicalEra e);
int getGenreSortPriority(Genre g);
int getEraSortPriority(ClassicalEra e);
struct ArtistF {
    std::string name;
    Genre genre_enum;
    std::optional<ClassicalEra> era_enum;
    int popularity_score;
    int performance_duration_minutes;
    size_t application_order_index;
    ArtistF(std::string artist_name, Genre artist_genre, std::optional<ClassicalEra> artist_era,
           int artist_popularity, int artist_duration, size_t artist_app_idx)
        : name(std::move(artist_name)),
          genre_enum(artist_genre),
          era_enum(artist_era),
          popularity_score(artist_popularity),
          performance_duration_minutes(artist_duration),
          application_order_index(artist_app_idx) {}
    friend std::ostream& operator<<(std::ostream& os, const ArtistF& artist);
};
void scheduleArtists(std::vector<ArtistF>& artists);

#endif // FESTIVAL_SCHEDULER_H
