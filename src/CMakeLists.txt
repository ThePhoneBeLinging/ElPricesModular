cmake_minimum_required(VERSION 3.25)
project(ElPricesModular)

set(CMAKE_CXX_STANDARD 20)
find_package(fmt)
add_executable(ElPricesModular main.cpp
        ElPricesModular.cpp
        ElPricesModular.h
        Slides/MainSlide.cpp
        Slides/MainSlide.h
        Slides/BoxChart.cpp
        Slides/BoxChart.h
        Slides/LargePriceGroupColumn.cpp
        Slides/LargePriceGroupColumn.h
        Slides/LastLargePriceGroupColumn.cpp
        Slides/LastLargePriceGroupColumn.h
        Slides/LoadingSlide.cpp
        Slides/LoadingSlide.h
)
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_include_directories(ElPricesModular PUBLIC src)

target_link_libraries(ElPricesModular PUBLIC ElPricesCollector)
target_link_libraries(ElPricesModular PUBLIC ElPricesUsageController)
target_link_libraries(ElPricesModular PUBLIC Utility)
target_link_libraries(ElPricesModular PUBLIC SQLiteCpp)
target_link_libraries(ElPricesModular PUBLIC LeGUILib)
target_link_libraries(ElPricesModular PUBLIC fmt::fmt)
target_link_libraries(ElPricesModular PUBLIC PriceGrouper)
target_link_libraries(ElPricesModular PUBLIC ElPricesWebServer)
target_link_libraries(ElPricesModular PUBLIC nlohmann_json)

