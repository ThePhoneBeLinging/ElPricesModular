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
    background_ = createElement<ImageElement>();
    background_->setWidth(1280);
    background_->setHeight(720);
    background_->loadImage("../../Resources/bliss.png");
    background_->setZ(-100);
}

void MainSlide::compose()
{
}
