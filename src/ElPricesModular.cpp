//
// Created by EAL on 25/12/2024.
//

#include "ElPricesModular.h"

#include "LeGUILib/LeGUILib.h"
#include "Slides/MainSlide.h"
#include "Utility/TimeUtil.h"

ElPricesModular::ElPricesModular() : leGUILib_(std::make_unique<LeGUILib>())
{
    leGUILib_->navigateTo(std::make_shared<Slide>());
    elPricesModularThread_ = std::thread(&ElPricesModular::launch, this);
    leGUILib_->launchGUI();
}

void ElPricesModular::launch()
{
    elPricesCollector_ = std::make_shared<ElPricesCollector>();
    elPriceUsageController_ = std::make_shared<ElPricesUsageController>();
    mainSlide_ = std::make_shared<MainSlide>(elPricesCollector_,elPriceUsageController_);
    leGUILib_->navigateTo(mainSlide_);
}
