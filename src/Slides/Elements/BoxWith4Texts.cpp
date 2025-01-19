//
// Created by Elias Aggergaard Larsen on 19/01/2025.
//

#include "BoxWith4Texts.h"

BoxWith4Texts::BoxWith4Texts(Slide* slide): BoxWith3Texts(slide)
{
    text_ = slide->createElement<Text>();
    text_->setFontSize(55);
    text_->setColor(255,255,255);
    text_->setAlignment(1);
    text_->setWidth(400);
    topText_->setFontSize(55);
    middleText_->setFontSize(120);
    bottomText_->setFontSize(55);
}

void BoxWith4Texts::setX(int x) const
{
    BoxWith3Texts::setX(x);
    text_->setX(x);
}

void BoxWith4Texts::setY(int y) const
{
    BoxWith3Texts::setY(y);
    text_->setY(y + 70);
    middleText_->setY(y + 130);
}

void BoxWith4Texts::setText5(const std::string& text)
{
    text_->setText(text);
}
