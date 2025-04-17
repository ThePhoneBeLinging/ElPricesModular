//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#ifndef MAINSLIDE_H
#define MAINSLIDE_H
#include <ElPricesCollector/ElPricesCollector.h>
#include <ElPricesUsageController/ElPricesUsageController.h>
#include "LargePriceGroupColumn.h"


class MainSlide : public Slide
{
public:
    MainSlide(const std::shared_ptr<ElPricesCollector>& collectorController, LeGUILib* guiLib);
    ~MainSlide();
private:
    std::shared_ptr<RectangleElement> closeAppButton_;
    std::shared_ptr<RectangleElement> reloadConfigButton_;
    std::unique_ptr<ElPricesUsageController> usageController_;
    std::function<void(int,double)> currentHourFunction_;
    std::shared_ptr<Text> hourUsageText_;
    std::shared_ptr<Text> hourKRUsage_;
    std::shared_ptr<Text> currentUsageWattageText_;
    std::shared_ptr<Text> currentKRUsage_;
    std::vector<std::shared_ptr<LargePriceGroupColumn>> largePriceGroupColumns_;
    std::vector<std::thread> threads_;
    std::atomic_bool keepRunning_;
    std::condition_variable condVar_;
    std::mutex mutex_;

};



#endif //MAINSLIDE_H
