#include <iostream>


#include <thread>

#include "ElPricesModular.h"

int main()
{
    auto elPricesModular = std::make_unique<ElPricesModular>();
    elPricesModular->launch();
    return 0;
}
