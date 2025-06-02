cmake_minimum_required(VERSION 3.31)
project(untitled7)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled7 main.cpp finance/transaction_utils.cpp finance/transaction_utils.h menu_utils.cpp menu_utils.h)
