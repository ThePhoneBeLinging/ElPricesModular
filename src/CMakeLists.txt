cmake_minimum_required(VERSION 3.25)
project(ElPricesModular)

set(CMAKE_CXX_STANDARD 20)

add_executable(ElPricesModular main.cpp
        ElPricesModular.cpp
        ElPricesModular.h)


target_link_libraries(ElPricesModular PUBLIC ElPricesCollector)
target_link_libraries(ElPricesModular PUBLIC ElPricesUsageController)
target_link_libraries(ElPricesModular PUBLIC Utility)
target_link_libraries(ElPricesModular PUBLIC raylib)
target_link_libraries(ElPricesModular PUBLIC SQLiteCpp)