//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#ifndef MAINSLIDE_H
#define MAINSLIDE_H
#include <LeGUILib/GUIElements/ImageElement.h>

#include "BoxWith3Texts.h"
#include "BoxWith4Texts.h"
#include "SlideTemplate.h"


class MainSlide : public Slide
{
public:
    MainSlide();
    void compose();
private:
    std::shared_ptr<ImageElement> background_;
    std::shared_ptr<BoxWith3Texts> topLeftBox_;
    std::shared_ptr<BoxWith3Texts> topRigthBox_;
    std::shared_ptr<BoxWith4Texts> bottomLeftBox_;
    std::shared_ptr<BoxWith4Texts> bottomRigthBox_;

};



#endif //MAINSLIDE_H
