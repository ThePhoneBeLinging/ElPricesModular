//
// Created by Elias Aggergaard Larsen on 25/12/2024.
//

#include "ElPricesModular.h"

#include "LeGUILib/LeGUILib.h"
#include "Slides/MainSlide.h"
#include "Utility/TimeUtil.h"

ElPricesModular::ElPricesModular() : leGUILib_(std::make_unique<LeGUILib>()), elPricesCollector_(std::make_shared<ElPricesCollector>()),
                                     elPriceUsageController_(std::make_shared<ElPricesUsageController>())
{
}

void ElPricesModular::launch()
{
    int screenWidth = 1280;
    int screenHeight = 720;
    int margin = 15;
    bool keepRunning_ = true;
    auto mainSlide = std::make_shared<MainSlide>();
    leGUILib_->addSlide(mainSlide);

    auto update = [&keepRunning_, &mainSlide,this] () -> void
    {
        while (keepRunning_)
        {
            mainSlide->compose(elPricesCollector_,elPriceUsageController_);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    };
    std::thread updateThread = std::thread(update);

    leGUILib_->launchGUI();
    keepRunning_ = false;
    updateThread.join();
}
