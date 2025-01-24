//
// Created by Elias Aggergaard Larsen on 22/01/2025.
//

#ifndef BOXCHART_H
#define BOXCHART_H
#include <LeGUILib/GUIElements/RectangleElement.h>
#include <LeGUILib/GUIElements/Slide.h>
#include <LeGUILib/GUIElements/Text.h>


class BoxChart
{
public:
    explicit BoxChart(Slide* slide);
    void setPrices(std::vector<double>& prices);
    void setX(int x);
    void setY(int y);
    void setBoxWidth(int width);
    void setSpacing(int spacing);
    void setHeight(int height);
private:
    void recreateColumns();
    void markColumn(int column);
    std::string timeToString(tm time);
    std::vector<double> prices_;
    std::vector<std::shared_ptr<RectangleElement>> columns_;
    std::vector<std::shared_ptr<RectangleElement>> columnClickHandler_;
    std::vector<std::shared_ptr<Text>> columnTimeTexts_;
    std::vector<std::shared_ptr<RectangleElement>> linesAroundBoxes_;
    std::shared_ptr<Text> selectedPriceText_;
    std::shared_ptr<Text> currentDayText_;
    std::shared_ptr<Text> tmrwDayText_;
    std::shared_ptr<Text> highestPriceText_;
    std::shared_ptr<Text> middlePriceText_;
    std::shared_ptr<Text> lowestPriceText_;

    std::shared_ptr<RectangleElement> middlePriceLine_;

    int x_;
    int y_;
    int spacing_;
    int boxWidth_;
    int height_;
    Slide* slide_;
};



#endif //BOXCHART_H
