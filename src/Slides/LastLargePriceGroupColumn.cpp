//
// Created by eal on 08/03/25.
//

#include "LastLargePriceGroupColumn.h"

#include <fmt/format.h>

LastLargePriceGroupColumn::LastLargePriceGroupColumn(Slide* slide) : LargePriceGroupColumn(slide)
{
}

void LastLargePriceGroupColumn::update(const std::shared_ptr<LargePriceGroup>& largePriceGroup)
{
    LargePriceGroupColumn::update(largePriceGroup);
    header_->setText("Rester");
    for (int i = 0; i < texts_.size(); i++)
    {
        if (largePriceGroup->getSmallPriceGroups()[i]->getStartTime() == -1)
        {
            continue;
        }
        std::string text = texts_[i]->getText();
        texts_[i]->setAlignment(1);
        text.append(" : ");
        double result = static_cast<double>(largePriceGroup->getSmallPriceGroups()[i]->calcAveragePrice()) / 10000.0;
        std::string formattedText = fmt::format("{:.2f}", result);
        text.append(formattedText);
        texts_[i]->setText(text);
    }
}
