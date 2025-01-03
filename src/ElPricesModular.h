//
// Created by Elias Aggergaard Larsen on 25/12/2024.
//

#ifndef ELPRICESMODULAR_H
#define ELPRICESMODULAR_H
#include <ElPricesUsageController/ElPricesUsageController.h>

#include "ElPricesCollector/ElPricesCollector.h"


class ElPricesModular
{
public:
    ElPricesModular();
    void launch();
private:
    void drawMainScreen(int offsetX, int offsetY, int fontSize);
    void drawConfigScreen(int offsetX, int offsetY, int fontSize);
    void drawFeesOverview(int offsetX, int offsetY, int fontSize);
    void drawPriceLastSeconds(int x, int y, int fontSize, int seconds);
    double getUsageInDKKFromInterval(int seconds);
    std::shared_ptr<ElPricesCollector> elPricesCollector_;
    std::shared_ptr<ElPricesUsageController> elPriceUsageController_;
};



#endif //ELPRICESMODULAR_H
