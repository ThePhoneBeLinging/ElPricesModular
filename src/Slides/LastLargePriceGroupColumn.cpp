//
// Created by eal on 08/03/25.
//

#include "LastLargePriceGroupColumn.h"

#include <fmt/format.h>

#include "Utility/TimeUtil.h"

LastLargePriceGroupColumn::LastLargePriceGroupColumn(Slide* slide) : LargePriceGroupColumn(slide)
{
}

void LastLargePriceGroupColumn::update(const std::shared_ptr<LargePriceGroup>& largePriceGroup)
{
    texts_.clear();
    int currentHour = TimeUtil::getCurrentTime().tm_hour;
    int backgroundWidth = 300;
    background_->setColor(200,200,200);
    background_->setWidth(backgroundWidth);
    background_->setHeight(500);
    background_->setRoundedEdge(0.2);
    background_->setX(x_);
    background_->setY(y_);
    int y = y_ + 70;
    auto smallPriceGroups = largePriceGroup->getSmallPriceGroups();
    int sum = 0;
    int size = 0;
    bool dummyIsLast = smallPriceGroups.back()->getStartTime() == -1;
    bool isNextDay = false;
    for (const auto& smallPrice : smallPriceGroups)
    {
        if (not isNextDay && smallPrice->getEndTime() <= currentHour && smallPrice->getStartTime() != -1)
        {
            continue;
        }
        if (dummyIsLast && smallPrice->getStartTime() == -1)
        {
            break;
        }
        auto text = slide_->createElement<Text>();
        text->setColor(0,0,0);
        text->setWidth(backgroundWidth);
        text->setAlignment(1);
        if (smallPrice->getStartTime() == -1)
        {
            text->setText(TimeUtil::intToWeekDayDanish((TimeUtil::getCurrentTime().tm_wday + 1) % 7));
            text->setFontSize(40);
            isNextDay = true;
        }
        else
        {
            std::string textString = std::to_string(smallPrice->getStartTime());
            textString.append(" -> ");
            textString.append(std::to_string(smallPrice->getEndTime()));
            textString.append(" : ");
            double result = (static_cast<double>(smallPrice->calcAveragePrice()) / 10000.0);
            std::string price = fmt::format("{:.2f}", result);
            textString.append(price);
            text->setText(textString);
            text->setFontSize(40);
            sum += smallPrice->calcAveragePrice();
            size++;
            if (smallPrice->getStartTime() <= currentHour && currentHour < smallPrice->getEndTime() && not isNextDay)
            {
                text->setColor(255,0,0);
                idOfCurrentPrice_ = text->getID();
            }
        }
        text->setX(x_);
        text->setY(y);
        text->setZ(5);
        texts_.push_back(text);
        y+= 50;
    }

    header_->setText("Rester");
    header_->setX(x_);
    header_->setY(y_ + 5);
    header_->setFontSize(50);
    header_->setWidth(backgroundWidth);
}
