//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#include "MainSlide.h"
#include <LeGUILib/GUIElements/Text.h>
#include "BoxWith3Texts.h"

MainSlide::MainSlide()
{
    background_ = createElement<ImageElement>();
    background_->setWidth(1280);
    background_->setHeight(720);
    background_->loadImage("../../Resources/bliss.png");
    background_->setZ(-100);

    timeBox_ = std::make_shared<TimeBox>(this);

    topLeftBox_ = std::make_shared<BoxWith3Texts>(this);
    topRigthBox_ = std::make_shared<BoxWith3Texts>(this);
    bottomLeftBox_ = std::make_shared<BoxWith4Texts>(this);
    bottomRigthBox_ = std::make_shared<BoxWith4Texts>(this);

    timeBox_->setX(440);
    timeBox_->setY(20);

    topLeftBox_->setX(20);
    topLeftBox_->setY(20);
    topLeftBox_->setTopText("Pris");
    topLeftBox_->setBottomText("KR | KwH");

    topRigthBox_->setX(860);
    topRigthBox_->setY(20);
    topRigthBox_->setTopText("Forbrug");
    topRigthBox_->setBottomText("KW");

    bottomLeftBox_->setX(20);
    bottomLeftBox_->setY(370);
    bottomLeftBox_->setTopText("Forbrug");
    bottomLeftBox_->setText5("Sidste Time");
    bottomLeftBox_->setBottomText("KW");

    bottomRigthBox_->setX(860);
    bottomRigthBox_->setY(370);
    bottomRigthBox_->setTopText("Forbrug");
    bottomRigthBox_->setText5("Sidste Døgn");

    bottomRigthBox_->setBottomText("KW");


}

void MainSlide::compose() const
{
    topLeftBox_->setMiddleText("15.01");
    topRigthBox_->setMiddleText("8.13");
    bottomLeftBox_->setMiddleText("8.13");
    bottomRigthBox_->setMiddleText("8.131");
    timeBox_->compose();
}
