//
// Created by eal on 08/03/25.
//

#ifndef LOADINGSLIDE_H
#define LOADINGSLIDE_H
#include <LeGUILib/GUIElements/ImageElement.h>
#include <LeGUILib/GUIElements/Slide.h>


class LoadingSlide : public Slide
{
public:
    LoadingSlide();
private:
    std::shared_ptr<ImageElement> pic_;
};



#endif //LOADINGSLIDE_H
