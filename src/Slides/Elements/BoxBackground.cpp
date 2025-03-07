//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#include "BoxBackground.h"

std::shared_ptr<GUIElement> BoxBackground::clone() const
{
    return std::make_shared<BoxBackground>(*this);
}

void BoxBackground::compose()
{
    setX(0);
    setY(0);
    setZ(-10);
    setColor(38,38,38);
    setHeight(330);
    setWidth(400);
    setRoundedEdge(0.2);
}

bool BoxBackground::isPointInside(int x, int y) const
{
    return false;
}
