//
// Created by eal on 08/03/25.
//

#include "LoadingSlide.h"

LoadingSlide::LoadingSlide() : Slide()
{
    pic_ = this->createElement<ImageElement>();
    pic_->setWidth(1280);
    pic_->setHeight(720);
    pic_->loadImage("../../Resources/lightning.png");
}
