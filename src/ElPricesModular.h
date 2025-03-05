//
// Created by EAL on 25/12/2024.
//

#ifndef ELPRICESMODULAR_H
#define ELPRICESMODULAR_H

#include <LeGUILib/LeGUILib.h>
#include <ElPricesUsageController/ElPricesUsageController.h>
#include "ElPricesCollector/ElPricesCollector.h"


class ElPricesModular
{
public:
    ElPricesModular();

private:
    void launch();
    std::thread elPricesModularThread_;
    std::unique_ptr<LeGUILib> leGUILib_;
    std::shared_ptr<ElPricesCollector> elPricesCollector_;
    std::shared_ptr<ElPricesUsageController> elPriceUsageController_;
};



#endif //ELPRICESMODULAR_H
