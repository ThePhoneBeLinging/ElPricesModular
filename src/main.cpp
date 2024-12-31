#include <iostream>
#include "ElPricesModular.h"

int main()
{
    auto elPricesModular = std::make_unique<ElPricesModular>();
    elPricesModular->launch();
    return 0;
}
