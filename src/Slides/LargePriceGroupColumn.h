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
    void update(const std::shared_ptr<LargePriceGroup>& largePriceGroup);
private:
    int x_;
    int y_;
    Slide* slide_;
    std::shared_ptr<RectangleElement> background_;
    std::shared_ptr<Text> header_;
    std::vector<std::shared_ptr<Text>> texts_;
};



#endif //LARGEPRICEGROUPCOLUMN_H
