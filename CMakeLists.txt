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
        physics/energy_analyzer.h
        physics/energy_analyzer.cpp
        cars/parade_organizer.cpp
        cars/parade_organizer.h
        normalized/score_processor.h
        normalized/score_processor.cpp
)
