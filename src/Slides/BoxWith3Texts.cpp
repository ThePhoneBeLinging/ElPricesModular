//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#include "BoxWith3Texts.h"

BoxWith3Texts::BoxWith3Texts(Slide* slide)
{
    boxBackground_ = slide->createElement<BoxBackground>();
    boxBackground_->compose();
    topText_ = slide->createElement<Text>();
    topText_->setText("Title Text");
    topText_->setColor(255,255,255);
    topText_->setFontSize(64);
    topText_->setAlignment(1);
    topText_->setWidth(400);
    middleText_ = slide->createElement<Text>();
    middleText_->setText("Middle Text");
    middleText_->setColor(255,255,255);
    middleText_->setFontSize(170);
    middleText_->setAlignment(1);
    middleText_->setWidth(400);
    bottomText_ = slide->createElement<Text>();
    bottomText_->setText("Bottom Text");
    bottomText_->setColor(255,255,255);
    bottomText_->setFontSize(64);
    bottomText_->setAlignment(1);
    bottomText_->setWidth(400);
}

void BoxWith3Texts::setX(int x) const
{
    //TODO Do some offsetthig here
    boxBackground_->setX(x);
    topText_->setX(x);
    middleText_->setX(x);
    bottomText_->setX(x);
}

void BoxWith3Texts::setY(int y) const
{
    boxBackground_->setY(y);
    topText_->setY(y + 15);
    middleText_->setY(y + 100);
    bottomText_->setY(y + 270);
}

void BoxWith3Texts::setTopText(const std::string& text)
{
    topText_->setText(text);
}

void BoxWith3Texts::setMiddleText(const std::string& text)
{
    middleText_->setText(text);
}

void BoxWith3Texts::setBottomText(const std::string& text)
{
    bottomText_->setText(text);
}
