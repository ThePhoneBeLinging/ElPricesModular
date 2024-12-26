//
// Created by Elias Aggergaard Larsen on 25/12/2024.
//

#include "ElPricesModular.h"

#include <iostream>

ElPricesModular::ElPricesModular() : elPricesCollector_(std::make_shared<ElPricesCollector>())
{
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << elPricesCollector_->getCurrentPrice()->getPriceWithoutFees() << std::endl;
}
