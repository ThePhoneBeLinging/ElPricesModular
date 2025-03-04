cmake_minimum_required(VERSION 3.25)
project(ElPricesModular)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(dependencies/ElPricesCollector)
add_subdirectory(dependencies/Utility)
add_subdirectory(dependencies/ElPricesUsageController)
add_subdirectory(dependencies/SQLiteCpp)
add_subdirectory(dependencies/LeGUILib)
add_subdirectory(dependencies/TouchCore-CPP)
add_subdirectory(dependencies/PriceGrouper)