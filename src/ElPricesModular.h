//
// Created by Elias Aggergaard Larsen on 25/12/2024.
//

#ifndef ELPRICESMODULAR_H
#define ELPRICESMODULAR_H
#include "ElPricesCollector/ElPricesCollector.h"


class ElPricesModular
{
public:
    ElPricesModular();
private:
    std::shared_ptr<ElPricesCollector> elPricesCollector_;
};



#endif //ELPRICESMODULAR_H
