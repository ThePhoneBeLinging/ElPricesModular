//
// Created by Elias Aggergaard Larsen on 19/01/2025.
//

#include "TimeBox.h"

#include "Utility/TimeUtil.h"

TimeBox::TimeBox(Slide* slide)
{
    background_ = slide->createElement<BoxBackground>();
    background_->compose();

    text_ = slide->createElement<Text>();
    text_->setColor(255,255,255);
    text_->setFontSize(170);
    text_->setAlignment(1);
    text_->setWidth(400);

}

void TimeBox::compose()
{
    text_->setText(getCurrentTime());
}

void TimeBox::setX(int x)
{
    text_->setX(x);
    background_->setX(x);
}

void TimeBox::setY(int y)
{
    background_->setY(y);
    text_->setY(y + 80);
}

std::string TimeBox::getCurrentTime()
{
    std::string time;
    auto timeNow = TimeUtil::getCurrentTime();
    if (timeNow.tm_hour < 10)
    {
        time.append("0");
    }
    time.append(std::to_string(timeNow.tm_hour));
    time.append(":");
    if (timeNow.tm_min < 10)
    {
        time.append("0");
    }
    time.append(std::to_string(timeNow.tm_min));
    return time;
}
