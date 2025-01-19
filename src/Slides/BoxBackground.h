//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#ifndef BOXBACKGROUND_H
#define BOXBACKGROUND_H
#include <LeGUILib/GUIElements/GUIElement.h>
#include <LeGUILib/GUIElements/RectangleElement.h>


class BoxBackground : public RectangleElement
{
public:
    BoxBackground();
    BoxBackground* clone() const override;
    void compose();
    bool isPointInside(int x, int y) const override;
};



#endif //BOXBACKGROUND_H
