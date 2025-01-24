//
// Created by Elias Aggergaard Larsen on 22/01/2025.
//

#include "BoxChart.h"

#include <iostream>

#include "Utility/TimeUtil.h"

BoxChart::BoxChart(Slide* slide) : x_(0), y_(0), spacing_(15), boxWidth_(15), height_(50),
                                   slide_(slide)
{
    for (int i = 0; i < 34; i++)
    {
        columns_.push_back(slide_->createElement<RectangleElement>());
        columnClickHandler_.push_back(slide_->createElement<RectangleElement>());
        columnClickHandler_[i]->setZ(-1000);
        columnClickHandler_[i]->setOnClick([i,this] -> void { this->markColumn(i); });

        columnTimeTexts_.push_back(slide_->createElement<Text>());
        columnTimeTexts_[i]->setAlignment(1);
        columnTimeTexts_[i]->setFontSize(20);
        columnTimeTexts_[i]->setColor(0,0,0);
    }
    for (int i = 0; i < 4; i++)
    {
        linesAroundBoxes_.push_back(slide_->createElement<RectangleElement>());
    }

    selectedPriceText_ = slide_->createElement<Text>();
    selectedPriceText_->setText("");
    selectedPriceText_->setColor(0,0,0);
    selectedPriceText_->setFontSize(30);
    selectedPriceText_->setAlignment(2);

    currentDayText_ = slide_->createElement<Text>();
    currentDayText_->setText("");
    currentDayText_->setColor(0,0,0);
    currentDayText_->setFontSize(30);
    currentDayText_->setAlignment(0);

    tmrwDayText_ = slide_->createElement<Text>();
    tmrwDayText_->setText("");
    tmrwDayText_->setColor(0,0,0);
    tmrwDayText_->setFontSize(30);
    tmrwDayText_->setAlignment(0);

    highestPriceText_ = slide_->createElement<Text>();
    highestPriceText_->setText("");
    highestPriceText_->setColor(0,0,0);
    highestPriceText_->setFontSize(30);
    highestPriceText_->setAlignment(2);

    middlePriceText_ = slide_->createElement<Text>();
    middlePriceText_->setText("");
    middlePriceText_->setColor(0,0,0);
    middlePriceText_->setFontSize(30);
    middlePriceText_->setAlignment(2);

    lowestPriceText_ = slide_->createElement<Text>();
    lowestPriceText_->setText("");
    lowestPriceText_->setColor(0,0,0);
    lowestPriceText_->setFontSize(30);
    lowestPriceText_->setAlignment(2);

    middlePriceLine_ = slide_->createElement<RectangleElement>();

    // Init prices:
    for (int i = 0; i < 34; i++)
    {
        prices_.push_back(i);
    }

}

void BoxChart::setPrices(std::vector<double>& prices)
{
    prices_ = prices;
    recreateColumns();
    markColumn(-1);
}

void BoxChart::setX(int x)
{
    x_ = x;
    recreateColumns();
}

void BoxChart::setY(int y)
{
    y_ = y;
    recreateColumns();
}

void BoxChart::setBoxWidth(const int width)
{
    boxWidth_ = width;
    recreateColumns();
}

void BoxChart::setSpacing(const int spacing)
{
    spacing_ = spacing;
    recreateColumns();
}

void BoxChart::setHeight(const int height)
{
    height_ = height;
    recreateColumns();
}

void BoxChart::recreateColumns()
{
    double max = prices_[0];
    double min = prices_[0];
    for (auto price : prices_)
    {
        if (price > max)
        {
            max = price;
        }
        if (price < min)
        {
            min = price;
        }
    }

    int localX = x_;
    bool firstDayComplete = false;
    for (int i = 0; i < prices_.size(); i++)
    {
        columnClickHandler_[i]->setColor(0,0,0,0);
        columnClickHandler_[i]->setWidth(boxWidth_ + spacing_);
        columnClickHandler_[i]->setHeight(height_);
        columnClickHandler_[i]->setX(localX - spacing_/2);
        columnClickHandler_[i]->setY(y_ - height_);
        columns_[i]->setColor(0,0,255);
        columns_[i]->setWidth(boxWidth_);
        columns_[i]->setHeight(height_ * (prices_[i] / max));
        columns_[i]->setX(localX);
        columns_[i]->setY(y_ - height_ * (prices_[i] / max));

        columnTimeTexts_[i]->setX(localX - spacing_/2);
        columnTimeTexts_[i]->setWidth(boxWidth_ + spacing_);
        columnTimeTexts_[i]->setY(y_ + 10);
        columnTimeTexts_[i]->setText((TimeUtil::getCurrentTime().tm_hour + i) % 24);
        if (firstDayComplete && (TimeUtil::getCurrentTime().tm_hour + i) % 24 == 0)
        {
            tmrwDayText_->setText(timeToString(TimeUtil::getTommorowTime()));
            tmrwDayText_->setX(localX + 5);
            tmrwDayText_->setY(y_ + 30);
        }
        if ((TimeUtil::getCurrentTime().tm_hour + i) % 24 == 0)
        {
            firstDayComplete = true;
        }
        localX += spacing_ + boxWidth_;
    }
    for (int i = prices_.size(); i < 34; i++)
    {
        columnClickHandler_[i]->setHeight(0);
        columns_[i]->setHeight(0);
        columnTimeTexts_[i]->setText("");
    }
    selectedPriceText_->setX(prices_.size() * (spacing_ + boxWidth_) + x_);
    selectedPriceText_->setY(y_ - height_ - 50);

    currentDayText_->setX(x_);
    currentDayText_->setY(y_ - height_ - 50);
    currentDayText_->setText(timeToString(TimeUtil::getCurrentTime()));

    highestPriceText_->setX(x_ - 15);
    highestPriceText_->setY(y_ - height_ - 15);
    highestPriceText_->setText(std::format("{:.2f}",max));

    middlePriceText_->setX(x_ - 15);
    middlePriceText_->setY(y_ - height_/2 - 15);
    middlePriceText_->setText(std::format("{:.2f}",max - (max - min)/2));

    lowestPriceText_->setX(x_ - 15);
    lowestPriceText_->setY( y_ - 15);
    lowestPriceText_->setText(std::format("{:.2f}",min));



    for (const auto& rect : linesAroundBoxes_)
    {
        rect->setColor(0,0,0);
    }

    int lineWidth = 2;

    middlePriceLine_->setX(x_);
    middlePriceLine_->setY(y_ - height_/2);
    middlePriceLine_->setHeight(2);
    middlePriceLine_->setColor(0,0,0);
    middlePriceLine_->setZ(-1);
    middlePriceLine_->setWidth(prices_.size() * (spacing_ + boxWidth_));

    // Left line
    linesAroundBoxes_[0]->setX(x_ - 10);
    linesAroundBoxes_[0]->setY(y_ - height_ - 5);
    linesAroundBoxes_[0]->setWidth(lineWidth);
    linesAroundBoxes_[0]->setHeight(height_ + 5);

    // Bottom line
    linesAroundBoxes_[1]->setX(x_ - 10);
    linesAroundBoxes_[1]->setY(y_ - 1);
    linesAroundBoxes_[1]->setHeight(lineWidth);
    linesAroundBoxes_[1]->setWidth(prices_.size() * (spacing_ + boxWidth_) + 11);

    // Right line
    linesAroundBoxes_[2]->setX(x_ + prices_.size() * (spacing_ + boxWidth_));
    linesAroundBoxes_[2]->setY(y_ - height_ - 5);
    linesAroundBoxes_[2]->setWidth(lineWidth);
    linesAroundBoxes_[2]->setHeight(height_ + 5);

    // Top line
    linesAroundBoxes_[3]->setX(x_ - 10);
    linesAroundBoxes_[3]->setY(y_ - height_);
    linesAroundBoxes_[3]->setHeight(lineWidth);
    linesAroundBoxes_[3]->setWidth(prices_.size() * (spacing_ + boxWidth_) + 11);

}

void BoxChart::markColumn(int column)
{
    for (int i = 0; i < 34; i++)
    {
        if (i == column)
        {
            columns_[i]->setColor(100,100,255);
        }
        else
        {
            columns_[i]->setColor(0,0,255);
        }
    }
    if (column != -1)
    {
        selectedPriceText_->setText(std::format("{:.2f}",prices_[column]));
    }
}

std::string BoxChart::timeToString(tm time)
{
    std::string string;
    string.append(TimeUtil::intToWeekDayDanish(time.tm_wday));
    string.append(" d. ").append(std::to_string(time.tm_mday));
    return string;
}
