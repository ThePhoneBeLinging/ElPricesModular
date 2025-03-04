//
// Created by eal on 3/4/25.
//

#include "LargePriceGroupColumn.h"

#include <fmt/format.h>

LargePriceGroupColumn::LargePriceGroupColumn(Slide* slide)
    : x_(0),y_(0) ,slide_(slide)
{
    background_ = slide_->createElement<RectangleElement>();

    header_ = slide_->createElement<Text>();
    header_->setColor(255,0,0);
    header_->setAlignment(1);
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
    int backgroundWidth = 400;
    background_->setColor(0,0,0);
    background_->setWidth(backgroundWidth);
    background_->setHeight(400);
    background_->setRoundedEdge(0.2);
    background_->setX(x_);
    background_->setY(y_);
    int y = y_ + 50;
    auto smallPriceGroups = largePriceGroup->getSmallPriceGroups();
    int sum = 0;
    for (const auto& smallPrice : smallPriceGroups)
    {
        auto text = slide_->createElement<Text>();
        text->setColor(255,0,0);
        text->setWidth(400);
        text->setAlignment(1);
        std::string textString = std::to_string(smallPrice->getStartTime());
        textString.append(" -> ");
        textString.append(std::to_string(smallPrice->getEndTime()));
        text->setText(textString);
        text->setFontSize(30);
        text->setX(x_);
        text->setY(y);
        texts_.push_back(text);
        y+= 50;
        sum += smallPrice->calcAveragePrice();
    }
    double result = (static_cast<double>(sum) / static_cast<double>(smallPriceGroups.size())) / 10000;
    std::string headerText = fmt::format("{:.2f}", result);
    header_->setText(headerText);
    header_->setX(x_);
    header_->setY(y_);
    header_->setFontSize(30);
    header_->setWidth(backgroundWidth);
}


