//
// Created by Elias Aggergaard Larsen on 22/01/2025.
//

#include "BoxChart.h"

#include <iostream>

#include "Utility/TimeUtil.h"

BoxChart::BoxChart(Slide* slide) : firstHour_(0), x_(0), y_(0), spacing_(15), boxWidth_(15), height_(50),
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

    selectedPriceText_ = slide_->createElement<Text>();
    selectedPriceText_->setColor(0,255,0);
    selectedPriceText_->setFontSize(30);
}

void BoxChart::setPrices(std::vector<double>& prices)
{
    prices_ = prices;
    firstHour_ = TimeUtil::getCurrentTime().tm_hour;
    recreateColumns();
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
    int localX = x_;
    for (int i = 0; i < 34; i++)
    {
        columnClickHandler_[i]->setColor(0,0,0,0);
        columnClickHandler_[i]->setWidth(boxWidth_ + spacing_);
        columnClickHandler_[i]->setHeight(height_);
        columnClickHandler_[i]->setX(localX - spacing_/2);
        columnClickHandler_[i]->setY(y_);
        columns_[i]->setColor(0,0,255);
        columns_[i]->setWidth(boxWidth_);
        columns_[i]->setHeight(height_);
        columns_[i]->setX(localX);
        columns_[i]->setY(y_);

        columnTimeTexts_[i]->setX(localX - spacing_/2);
        columnTimeTexts_[i]->setWidth(boxWidth_ + spacing_);
        columnTimeTexts_[i]->setY(y_ + height_ + 5);
        columnTimeTexts_[i]->setText((firstHour_ + i) % 24);
        localX += spacing_ + boxWidth_;
    }
    selectedPriceText_->setX(localX - 80);
    selectedPriceText_->setY(y_ - 40);
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
    selectedPriceText_->setText(std::format("{:.2f}",prices_[column]));
}
