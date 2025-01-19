//
// Created by Elias Aggergaard Larsen on 19/01/2025.
//

#ifndef BOXWITH4TEXTS_H
#define BOXWITH4TEXTS_H
#include "BoxWith3Texts.h"


class BoxWith4Texts : public BoxWith3Texts
{
public:
    explicit BoxWith4Texts(Slide* slide);
    virtual ~BoxWith4Texts() = default;
    void setX(int x) const override;
    void setY(int y) const override;
    void setText5(const std::string& text);
private:
    std::shared_ptr<Text> text_;
};



#endif //BOXWITH4TEXTS_H
