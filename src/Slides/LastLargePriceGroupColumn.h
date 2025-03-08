//
// Created by eal on 08/03/25.
//

#ifndef LASTLARGEPRICEGROUPCOLUMN_H
#define LASTLARGEPRICEGROUPCOLUMN_H
#include <LeGUILib/GUIElements/Slide.h>

#include "LargePriceGroupColumn.h"


class LastLargePriceGroupColumn : public LargePriceGroupColumn
{
public:
    explicit LastLargePriceGroupColumn(Slide* slide);
    void update(const std::shared_ptr<LargePriceGroup>& largePriceGroup) override;
};



#endif //LASTLARGEPRICEGROUPCOLUMN_H
