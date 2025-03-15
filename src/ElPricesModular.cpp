//
// Created by EAL on 25/12/2024.
//

#include "ElPricesModular.h"

#include "LeGUILib/LeGUILib.h"
#include "Slides/LoadingSlide.h"
#include "Slides/MainSlide.h"
#include "Utility/TimeUtil.h"

ElPricesModular::ElPricesModular() : leGUILib_(std::make_unique<LeGUILib>())
{
    leGUILib_->navigateTo(std::make_shared<LoadingSlide>());
    elPricesModularThread_ = std::thread(&ElPricesModular::launch, this);
    leGUILib_->launchGUI();
    elPricesModularThread_.join();
}

void ElPricesModular::launch()
{
    elPricesCollector_ = std::make_shared<ElPricesCollector>();
    mainSlide_ = std::make_shared<MainSlide>(elPricesCollector_);
    leGUILib_->navigateTo(mainSlide_);
}
