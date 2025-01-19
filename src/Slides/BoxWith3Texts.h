//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#ifndef BOXWITH3TEXTS_H
#define BOXWITH3TEXTS_H
#include <LeGUILib/GUIElements/GUIElement.h>
#include <LeGUILib/GUIElements/Text.h>

#include "BoxBackground.h"
#include "SlideTemplate.h"


class BoxWith3Texts
{
public:
    explicit BoxWith3Texts(Slide* slide);
    virtual void setX(int x) const;
    virtual void setY(int y) const;
    void setTopText(const std::string& text);
    void setMiddleText(const std::string& text);
    void setBottomText(const std::string& text);
protected:
    std::shared_ptr<BoxBackground> boxBackground_;
    std::shared_ptr<Text> topText_;
    std::shared_ptr<Text> middleText_;
    std::shared_ptr<Text> bottomText_;

};



#endif //BOXWITH3TEXTS_H
