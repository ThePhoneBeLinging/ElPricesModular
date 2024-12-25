#include <iostream>


#include <thread>

#include "ElPricesCollector/ElPricesCollector.h"

int main()
{
    auto collector = std::make_unique<ElPricesCollector>();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
