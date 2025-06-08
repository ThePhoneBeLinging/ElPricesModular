//
// Created by eal on 3/4/25.
//

#include "LargePriceGroupColumn.h"

#include <fmt/format.h>

#include "Utility/TimeUtil.h"

LargePriceGroupColumn::LargePriceGroupColumn(Slide* slide)
    : x_(0),y_(0) ,slide_(slide)
{
    background_ = slide_->createElement<RectangleElement>();

    header_ = slide_->createElement<Text>();
    header_->setColor(0,0,0);
    header_->setAlignment(1);
    header_->setZ(5);
}

void LargePriceGroupColumn::setX(const int x)
{
    x_ = x;
}

void LargePriceGroupColumn::setY(const int y)
{
    y_ = y;
}

void LargePriceGroupColumn::update(const std::shared_ptr<LargePriceGroup>& largePriceGroup)
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
            text->setText(textString);
            text->setFontSize(40);
            sum += smallPrice->calcAveragePrice();
            size++;
            if (smallPrice->getStartTime() <= currentHour && currentHour < smallPrice->getEndTime() && not isNextDay)
            {
                text->setColor(0,200,0);
                idOfCurrentPrice_ = text->getID();
            }
        }
        text->setX(x_);
        text->setY(y);
        text->setZ(5);
        texts_.push_back(text);
        y+= 50;
    }
    double result = (static_cast<double>(sum) / static_cast<double>(size)) / 10000;
    std::string headerText = fmt::format("{:.2f}", result);
    header_->setText(headerText);
    header_->setX(x_);
    header_->setY(y_ + 5);
    header_->setFontSize(50);
    header_->setWidth(backgroundWidth);
}

std::vector<std::string> LargePriceGroupColumn::getTexts()
{
    std::vector<std::string> texts;
    texts.push_back(header_->getText());
    for (const auto& text : texts_)
    {
        if (idOfCurrentPrice_ == text->getID())
        {
            texts.push_back(text->getText() + "C");
        }
        else
        {
            texts.push_back(text->getText());
        }
    }
    return texts;
}


