//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#include "MainSlide.h"

#include <iostream>
#include <LeGUILib/GUIElements/Text.h>
#include "Elements/BoxWith3Texts.h"
#include "Utility/TimeUtil.h"

MainSlide::MainSlide()
{
    boxChart_ = std::make_shared<BoxChart>(this);
    boxChart_->setSpacing(15);
    boxChart_->setBoxWidth(15);
    boxChart_->setX(125);
    boxChart_->setY(400);
    boxChart_->setHeight(250);
}

void MainSlide::compose(const std::shared_ptr<ElPricesCollector>& collectorController,
    const std::shared_ptr<ElPricesUsageController>& usageController) const
{
    //double priceRN = static_cast<double>(collectorController->getCurrentPrice()->getTotalPrice()) / 10000;
    //int var = 2;
    //std::string priceRNString = std::format("{:.2f}",priceRN);

    double usageRN = usageController->getWattage();
    std::string usageRNString = std::format("{:.3f}",usageRN);
}
