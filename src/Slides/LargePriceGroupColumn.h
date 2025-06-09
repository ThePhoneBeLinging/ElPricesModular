//
// Created by eal on 3/4/25.
//

#ifndef LARGEPRICEGROUPCOLUMN_H
#define LARGEPRICEGROUPCOLUMN_H
#include <LeGUILib/LeGUILib.h>
#include <LeGUILib/GUIElements/RectangleElement.h>
#include <LeGUILib/GUIElements/Text.h>

#include "PriceGrouper/LargePriceGroup.h"
class LargePriceGroupColumn
{
public:
    explicit LargePriceGroupColumn(Slide* slide);
    void setX(int x);
    void setY(int y);
    virtual void update(const std::shared_ptr<LargePriceGroup>& largePriceGroup);
    std::vector<std::string> getTexts();
protected:
    int x_;
    int y_;
    int idOfCurrentPrice_;
    Slide* slide_;
    std::shared_ptr<RectangleElement> background_;
    std::shared_ptr<Text> header_;
    std::vector<std::shared_ptr<Text>> texts_;
};



#endif //LARGEPRICEGROUPCOLUMN_H
