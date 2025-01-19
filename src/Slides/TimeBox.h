//
// Created by Elias Aggergaard Larsen on 19/01/2025.
//

#ifndef TIMEBOX_H
#define TIMEBOX_H
#include <LeGUILib/GUIElements/Slide.h>
#include <LeGUILib/GUIElements/Text.h>

#include "BoxBackground.h"


class TimeBox
{
public:
    explicit TimeBox(Slide* slide);
    void compose();
    void setX(int x);
    void setY(int y);
    std::string getCurrentTime();
private:
    std::shared_ptr<Text> text_;
    std::shared_ptr<BoxBackground> background_;
};



#endif //TIMEBOX_H
