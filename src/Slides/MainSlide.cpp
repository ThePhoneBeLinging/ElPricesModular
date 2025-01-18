//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#include "MainSlide.h"
#include <LeGUILib/GUIElements/Text.h>
#include "BoxWith3Texts.h"

MainSlide::MainSlide()
{
    topLeftBox_ = std::make_shared<BoxWith3Texts>(this);
    topRigthBox_ = std::make_shared<BoxWith3Texts>(this);
    topRigthBox_->setX(860);
    topRigthBox_->setY(21);
    topLeftBox_->setX(20);
    topLeftBox_->setY(20);
    topLeftBox_->setTopText("Pris");
    topLeftBox_->setMiddleText("15.01");
    topLeftBox_->setBottomText("KR | KwH");
}

void MainSlide::compose()
{
}
