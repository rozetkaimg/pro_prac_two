cmake_minimum_required(VERSION 3.31)
project(untitled7)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled7
        main.cpp
        finance/transaction_utils.cpp
        finance/transaction_utils.h
        menu_utils.cpp
        menu_utils.h
        circus/circus_scheduler.cpp
        circus/circus_scheduler.h
        festival/festival_scheduler.cpp
        festival/festival_scheduler.h
        cars/parade_organizer.cpp
        cars/parade_organizer.h
        normalized/score_processor.h
        normalized/score_processor.cpp
        animals/animal_act_selector.cpp
        animals/animal_act_selector.h
        cleaner/log_cleaner.cpp
        cleaner/log_cleaner.h
        patient/patient_queue.cpp
        patient/patient_queue.h
        physics/energy_analyzer.cpp
        physics/energy_analyzer.h
        sensor/sensor_data_corrector.cpp
        sensor/sensor_data_corrector.h
)
