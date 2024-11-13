cmake_minimum_required(VERSION 3.8)
project(BudgetTracker)

set(CMAKE_CXX_STANDARD 14)

# Main executable with all necessary source files
add_executable(main.cpp Bank.cpp
        )

