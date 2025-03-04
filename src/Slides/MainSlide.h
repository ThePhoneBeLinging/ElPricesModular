//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#ifndef MAINSLIDE_H
#define MAINSLIDE_H
#include <ElPricesCollector/ElPricesCollector.h>
#include <ElPricesUsageController/ElPricesUsageController.h>

#include "BoxChart.h"
#include "LargePriceGroupColumn.h"
#include "Elements/BoxWith3Texts.h"


class MainSlide : public Slide
{
public:
    MainSlide(const std::shared_ptr<ElPricesCollector>& collectorController, const std::shared_ptr<ElPricesUsageController>& usageController);
    ~MainSlide();
private:
    std::shared_ptr<LargePriceGroupColumn> largePriceGroupColumn_;
    std::vector<std::thread> threads_;
    std::atomic_bool keepRunning_;
    std::condition_variable condVar_;
    std::mutex mutex_;

};



#endif //MAINSLIDE_H
