//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#include "MainSlide.h"

#include <iostream>
#include <LeGUILib/GUIElements/Text.h>
#include "Elements/BoxWith3Texts.h"
#include "Utility/TimeUtil.h"

MainSlide::MainSlide(const std::shared_ptr<ElPricesCollector>& collectorController, const std::shared_ptr<ElPricesUsageController>& usageController)
{
    boxChart_ = std::make_shared<BoxChart>(this);
    boxChart_->setSpacing(15);
    boxChart_->setBoxWidth(15);
    boxChart_->setX(125);
    boxChart_->setY(650);
    boxChart_->setHeight(250);
    std::vector<double> values;
    for (const auto& val : collectorController->getCurrentAndFuturePrices())
    {
        values.push_back(static_cast<double>(val->getTotalPrice()) / 10000);
    }
    boxChart_->setPrices(values);
}

MainSlide::~MainSlide()
{
    condVar_.notify_all();
    for (auto& thread : threads_)
    {
        thread.join();
    }
}

void MainSlide::compose(const std::shared_ptr<ElPricesCollector>& collectorController,
                        const std::shared_ptr<ElPricesUsageController>& usageController) const
{
    double priceRN = static_cast<double>(collectorController->getCurrentPrice()->getTotalPrice()) / 10000;
    std::string priceRNString = std::format("{:.2f}",priceRN);

    double usageRN = usageController->getWattage();
    std::string usageRNString = std::format("{:.3f}",usageRN);

    double currentUsagePriceOutlook = collectorController->getCurrentPrice()->getTotalPrice() * usageRN;
    std::string currentUsagePriceOutlookString = std::format("{:.3f}",currentUsagePriceOutlook);
}
