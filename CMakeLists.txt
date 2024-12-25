cmake_minimum_required(VERSION 3.28)
project(ElPricesModular)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(src)
add_subdirectory(dependencies/ElPricesCollector)
add_subdirectory(dependencies/Utility)

target_link_libraries(ElPricesModular PUBLIC ElPricesCollector)
target_link_libraries(ElPricesModular PUBLIC Utility)