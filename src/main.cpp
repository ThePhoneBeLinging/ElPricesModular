#include <iostream>


#include <thread>

#include "ElPricesModular.h"

int main()
{
    auto elPricesModular = std::make_unique<ElPricesModular>();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
