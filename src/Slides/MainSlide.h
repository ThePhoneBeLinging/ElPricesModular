//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#ifndef MAINSLIDE_H
#define MAINSLIDE_H
#include "BoxWith3Texts.h"
#include "SlideTemplate.h"


class MainSlide : public Slide
{
public:
    MainSlide();
    void compose();
private:
    std::shared_ptr<BoxWith3Texts> topLeftBox_;
    std::shared_ptr<BoxWith3Texts> topRigthBox_;

};



#endif //MAINSLIDE_H
