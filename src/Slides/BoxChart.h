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
    BoxChart(Slide* slide);
    void setPrices(std::vector<double>&& prices);
    void setX(int x);
    void setY(int y);
    void setBoxWidth(int width);
    void setSpacing(int spacing);
    void setHeight(int height);
private:
    void recreateColumns();
    void markColumn(int column);
    std::vector<double> prices_;
    int firstHour_;
    std::vector<std::shared_ptr<RectangleElement>> columns_;
    std::vector<std::shared_ptr<RectangleElement>> columnClickHandler_;
    std::vector<std::shared_ptr<Text>> columnTimeTexts_;
    int x_;
    int y_;
    int spacing_;
    int boxWidth_;
    int height_;
    Slide* slide_;
};



#endif //BOXCHART_H
