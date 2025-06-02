#include "menu_utils.h"
#include "circus/circus_scheduler.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <__ostream/basic_ostream.h>

#include "cars/parade_organizer.h"
#include "festival/festival_scheduler.h"
#include "finance/transaction_utils.h"
#include "normalized/score_processor.h"
#include "physics/energy_analyzer.h"

struct Transaction;
using namespace std;


int finance_transaction() {
    cout << fixed << setprecision(2);
    multimap<string, Transaction> transactions;
    transactions.insert({"Еда", {250.50, "2024-05-20", "Обед в ресторане"}});
    transactions.insert({"Транспорт", {75.00, "2024-05-20", "Такси"}});
    transactions.insert({"Еда", {120.00, "2024-05-21", "Продукты"}});
    transactions.insert({"Развлечения", {300.00, "2024-05-21", "Кино"}});
    transactions.insert({"Транспорт", {50.25, "2024-05-22", "Бензин"}});
    transactions.insert({"Еда", {85.75, "2024-05-22", "Кофе и выпечка"}});
    transactions.insert({"Еда", {150.00, "2024-05-23", "Ужин"}});
    transactions.insert({"Еда", {25.00, "2024-06-01", "Фрукты"}});
    transactions.insert({"Еда", {180.00, "2024-06-02", "Продукты на неделю"}});
    transactions.insert({"Транспорт", {220.00, "2024-06-03", "Билеты на поезд"}});


    cout << "Сумма с фильтром по дате" << endl;
    string categoryToSum = "Еда";

    double totalForCategoryAllTime = sumTransactionsInCategoryAndDateRange(transactions, categoryToSum);
    cout << "Общая сумма (все даты) в категории \"" << categoryToSum << "\": " << totalForCategoryAllTime << endl;

    double totalForCategoryMay = sumTransactionsInCategoryAndDateRange(transactions, categoryToSum, "2024-05-01",
                                                                       "2024-05-31");
    cout << "Общая сумма (май 2024) в категории \"" << categoryToSum << "\": " << totalForCategoryMay << endl;

    double totalForCategoryJune = sumTransactionsInCategoryAndDateRange(transactions, categoryToSum, "2024-06-01");
    cout << "Общая сумма (с июня 2024) в категории \"" << categoryToSum << "\": " << totalForCategoryJune << endl;

    categoryToSum = "Транспорт";
    double totalTransportJune = sumTransactionsInCategoryAndDateRange(transactions, categoryToSum, "2024-06-01",
                                                                      "2024-06-30");
    cout << "Общая сумма (июнь 2024) в категории \"" << categoryToSum << "\": " << totalTransportJune << endl;


    cout << "\n Комплексная статистика" << endl;
    string categoryForStats = "Еда";
    CategoryStats statsMay = getCategoryStatistics(transactions, categoryForStats, "2024-05-01", "2024-05-31");
    cout << "Статистика для категории \"" << categoryForStats << "\" (май 2024): " << statsMay << endl;

    CategoryStats statsJune = getCategoryStatistics(transactions, categoryForStats, "2024-06-01");
    cout << "Статистика для категории \"" << categoryForStats << "\" (с июня 2024): " << statsJune << endl;

    CategoryStats statsAllTime = getCategoryStatistics(transactions, categoryForStats);
    cout << "Статистика для категории \"" << categoryForStats << "\" (все время): " << statsAllTime << endl;

    categoryForStats = "Развлечения";
    CategoryStats statsEntertainment = getCategoryStatistics(transactions, categoryForStats);
    cout << "Статистика для категории \"" << categoryForStats << "\" (все время): " << statsEntertainment << endl;

    categoryForStats = "Одежда";
    CategoryStats statsEmpty = getCategoryStatistics(transactions, categoryForStats);
    cout << "Статистика для категории \"" << categoryForStats << "\" (все время): " << statsEmpty << endl;

    return 0;
}

int scheduler_circus() {
    std::vector<Artist> artists = {
        {"A01", "Иван", {"акробатика", "жонглирование"}, 100, 100, 0, 3},
        {"A02", "Мария", {"воздушная гимнастика", "акробатика"}, 90, 90, 0, 2},
        {"A03", "Петр", {"клоунада", "жонглирование"}, 120, 120, 0, 4},
        {"A04", "Анна", {"акробатика"}, 80, 80, 0, 3},
        {"A05", "Сергей", {"воздушная гимнастика"}, 110, 110, 0, 2}
    };
    std::vector<ShowAct> show_program = {
        {"S01", "Открытие: Акробаты", {"акробатика"}, 2, 1, 30, {}, "Ожидает"},
        {"S02", "Воздушный полет", {"воздушная гимнастика"}, 1, 2, 40, {}, "Ожидает"},
        {"S03", "Веселые жонглеры", {"жонглирование"}, 2, 1, 25, {}, "Ожидает"},
        {"S04", "Соло акробат", {"акробатика"}, 1, 3, 35, {}, "Ожидает"},
        {"S05", "Финал: Все звезды", {"акробатика", "жонглирование", "воздушная гимнастика"}, 3, 2, 20, {}, "Ожидает"}
    };

    std::cout << "--- Исходное состояние артистов ---" << std::endl;
    print_artists_status(artists);
    std::cout << "\n--- Исходная программа шоу ---" << std::endl;
    print_show_program_status(show_program);
    std::cout << "\n--- Формирование состава... ---" << std::endl;
    form_cast_for_evening_show(artists, show_program);
    print_artists_status(artists);
    print_show_program_status(show_program);

    return 0;
}

int energy_analyzer() {
    std::cout << std::fixed << std::setprecision(2);

    std::vector<double> electron_energies = {
        -13.60, -3.40, -1.51, -0.85, 0.00, 0.50,
        1.00, 1.15, 1.70, 2.50, 3.00, 5.50, 7.00
    };
    print_energies(electron_energies, "Initial Electron Energies (eV)");
    std::cout << "------------------------------------------------------------" << std::endl;

    double Ev_material = 0.0;
    double Ec_material = 1.1;

    std::cout << "Scenario 1: Semiconductor Analysis (Ev = " << Ev_material
              << " eV, Ec = " << Ec_material << " eV)" << std::endl;

    long valence_band_electrons = ElectronCounter::count_electrons_below_level(electron_energies, Ev_material);
    std::cout << "Electrons in Valence Band (E < " << Ev_material << " eV): "
              << valence_band_electrons << std::endl;

    long conduction_band_electrons = ElectronCounter::count_electrons_above_level(electron_energies, Ec_material);
    std::cout << "Electrons in Conduction Band (E > " << Ec_material << " eV): "
              << conduction_band_electrons << std::endl;

    long forbidden_gap_electrons = ElectronCounter::count_electrons_in_range(electron_energies, Ev_material, Ec_material);
    std::cout << "Electrons in Forbidden Gap (" << Ev_material << " eV <= E <= " << Ec_material << " eV): "
              << forbidden_gap_electrons << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    double custom_min_E = -2.00;
    double custom_max_E = 0.75;
    std::cout << "Scenario 2: Custom Energy Window Search" << std::endl;
    std::cout << "Counting electrons in range [" << custom_min_E << " eV, " << custom_max_E << " eV]" << std::endl;
    long custom_range_count = ElectronCounter::count_electrons_in_range(electron_energies, custom_min_E, custom_max_E);
    std::cout << "Electrons found in custom range: " << custom_range_count << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    double fermi_level_example = -0.50;
    std::cout << "Scenario 3: Analysis Relative to Fermi Level (Ef = " << fermi_level_example << " eV)" << std::endl;

    long electrons_below_fermi = ElectronCounter::count_electrons_below_level(electron_energies, fermi_level_example);
    std::cout << "Electrons with energy E < " << fermi_level_example << " eV (below Fermi level): "
              << electrons_below_fermi << std::endl;

    long electrons_above_fermi = ElectronCounter::count_electrons_above_level(electron_energies, fermi_level_example);
    std::cout << "Electrons with energy E > " << fermi_level_example << " eV (above Fermi level): "
              << electrons_above_fermi << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    std::vector<double> empty_energies = {};
    std::cout << "Edge Case: Empty Electron Energy List" << std::endl;
    print_energies(empty_energies, "Empty electron energies list");
    long count_in_empty_below = ElectronCounter::count_electrons_below_level(empty_energies, 0.0);
    std::cout << "Electrons below 0.0 eV in empty list: " << count_in_empty_below << std::endl;
    long count_in_empty_range = ElectronCounter::count_electrons_in_range(empty_energies, -1.0, 1.0);
    std::cout << "Electrons in range [-1.0, 1.0] eV in empty list: " << count_in_empty_range << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    std::cout << "Edge Case: Invalid Range for count_electrons_in_range" << std::endl;
    double invalid_min_range = 1.0;
    double invalid_max_range = 0.0;
    long count_invalid_range = ElectronCounter::count_electrons_in_range(electron_energies, invalid_min_range, invalid_max_range);
    std::cout << "Electrons in range [" << invalid_min_range << " eV, " << invalid_max_range << " eV]: "
              << count_invalid_range << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    return 0;
}
int scheduler_festival() {
     vector<ArtistF> artists_applications;
    size_t app_idx_counter = 0;
    artists_applications.emplace_back("The Rolling Stones", Genre::ROCK, std::nullopt, 95, 60, app_idx_counter++);
    artists_applications.emplace_back("Ludwig van Beethoven Tribute", Genre::CLASSICAL, ClassicalEra::CLASSICISM, 90, 45, app_idx_counter++);
    artists_applications.emplace_back("Celtic Rovers", Genre::FOLK, std::nullopt, 80, 40, app_idx_counter++);
    artists_applications.emplace_back("Miles Davis Quartet", Genre::JAZZ, std::nullopt, 88, 50, app_idx_counter++);
    artists_applications.emplace_back("Bach Ensemble", Genre::CLASSICAL, ClassicalEra::BAROQUE, 85, 30, app_idx_counter++);
    artists_applications.emplace_back("Queen Revival", Genre::ROCK, std::nullopt, 92, 55, app_idx_counter++);
    artists_applications.emplace_back("Mountain Balladeers", Genre::FOLK, std::nullopt, 80, 35, app_idx_counter++);
    artists_applications.emplace_back("Modern Composers Showcase", Genre::CLASSICAL, ClassicalEra::MODERN, 70, 60, app_idx_counter++);
    artists_applications.emplace_back("Smooth Jazz Collective", Genre::JAZZ, std::nullopt, 88, 45, app_idx_counter++);
    artists_applications.emplace_back("Romantic Era Pianist", Genre::CLASSICAL, ClassicalEra::ROMANTICISM, 90, 50, app_idx_counter++);
    artists_applications.emplace_back("Vivaldi Strings", Genre::CLASSICAL, ClassicalEra::BAROQUE, 88, 30, app_idx_counter++);
    artists_applications.emplace_back("Indie Rock Newcomers", Genre::ROCK, std::nullopt, 75, 40, app_idx_counter++);
    artists_applications.emplace_back("Another Folk Group", Genre::FOLK, std::nullopt, 70, 30, app_idx_counter++);
    cout << "--- Исходный список заявок артистов ---" << std::endl;
    for (const auto& artist : artists_applications) {
       cout << artist << std::endl;
    }

  cout << "\n" << std::string(80, '-') << "\n" << std::endl;
    scheduleArtists(artists_applications);
    cout << "--- Сформированная программа фестиваля ---" << std::endl;
    for (const auto& artist : artists_applications) {
        std::cout << artist << std::endl;
    }
 cout << "\n" << string(80, '-') << std::endl;
    return 0;
}
int organizer_parade() {
    std::vector<Car> cars_to_organize;
    size_t current_index = 0;
    cars_to_organize.emplace_back("M001", CarType::MILITARY, "Танк", std::nullopt, current_index++);
    cars_to_organize.emplace_back("S001", CarType::SPORTS, "Купе", std::nullopt, current_index++);
    cars_to_organize.emplace_back("R001", CarType::RETRO, "", 1950, current_index++);
    cars_to_organize.emplace_back("M002", CarType::MILITARY, "Джип", std::nullopt, current_index++);
    cars_to_organize.emplace_back("R002", CarType::RETRO, "Седан", 1945, current_index++);
    cars_to_organize.emplace_back("S002", CarType::SPORTS, "Родстер", std::nullopt, current_index++);
    cars_to_organize.emplace_back("M003", CarType::MILITARY, "Танк", std::nullopt, current_index++);
    cars_to_organize.emplace_back("R003", CarType::RETRO, "", 1950, current_index++);
    cars_to_organize.emplace_back("S003", CarType::SPORTS, "Купе", std::nullopt, current_index++);
    cars_to_organize.emplace_back("M004", CarType::MILITARY, "БТР", std::nullopt, current_index++);
    cars_to_organize.emplace_back("R004", CarType::RETRO, "", 1965, current_index++);


    std::cout << "Исходный порядок автомобилей:" << std::endl;
    for (const auto& car : cars_to_organize) {
        std::cout << car << std::endl;
    }
    std::cout << "\n-------------------------------------------\n" << std::endl;

    organizeParade(cars_to_organize);

    std::cout << "Порядок автомобилей для парада:" << std::endl;
    for (const auto& car : cars_to_organize) {
        std::cout << car << std::endl;
    }

    return 0;
}
int processing_score(){
    std::map<std::string, int> student_scores = {
        {"Анна Иванова", 85},
        {"Петр Сидоров", 45},
        {"Мария Кузнецова", 98},
        {"Иван Попов", 60},
        {"Елена Смирнова", 30},
        {"Сергей Федоров", 92}
    };

    std::cout << "--- Первоначальные баллы студентов ---" << std::endl;
    for(const auto& pair : student_scores) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << "\n" << std::string(60, '-') << "\n" << std::endl;
    ScoreProcessing::NormalizationParams params(0.10, 5, 100, 0);
    std::cout << "--- Параметры нормирования ---" << std::endl;
    std::cout << "Процентное увеличение: " << params.percentage_increase_factor * 100 << "%" << std::endl;
    std::cout << "Плоский бонус: " << params.flat_bonus << " балла(ов)" << std::endl;
    std::cout << "Максимальный балл: " << params.max_score << std::endl;
    std::cout << "Минимальный балл: " << params.min_score << std::endl;
    std::cout << "\n" << std::string(60, '-') << "\n" << std::endl;
    std::vector<std::string> report = ScoreProcessing::generateNormalizedScoreReport(student_scores, params);
    std::cout << "--- Отчет об изменении баллов после нормирования ---" << std::endl;
    for (const std::string& line : report) {
        std::cout << line << std::endl;
    }
    std::cout << "\n" << std::string(60, '-') << std::endl;
    ScoreProcessing::NormalizationParams params_alt(0.05, 0, 100, 0);
    std::cout << "--- Отчет с альтернативными параметрами (+5%, 0 плоский бонус) ---" << std::endl;
    std::vector<std::string> report_alt = ScoreProcessing::generateNormalizedScoreReport(student_scores, params_alt);
     for (const std::string& line : report_alt) {
        std::cout << line << std::endl;
    }
    std::cout << "\n" << std::string(60, '-') << std::endl;
    return 0;
}