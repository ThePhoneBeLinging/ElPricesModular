//
// Created by Elias Aggergaard Larsen on 25/12/2024.
//

#include "ElPricesModular.h"

#include <iostream>
#include <LeGUILib/GUIElements/RectangleElement.h>
#include <LeGUILib/GUIElements/Text.h>


#include "LeGUILib/GUIElements/ImageElement.h"
#include "LeGUILib/LeGUILib.h"
#include "Utility/TimeUtil.h"

ElPricesModular::ElPricesModular() : elPricesCollector_(std::make_shared<ElPricesCollector>()),
                                     elPriceUsageController_(std::make_shared<ElPricesUsageController>())
{
}

void ElPricesModular::launch()
{
    auto lib = std::make_shared<LeGUILib>();
    auto text = lib->createElement<Text>();
    text->setText("ElPricesModular");
    text->setFontSize(40);
    text->setX(50);
    text->setY(50);
    text->setColor(255,0,0);

    auto rectangle = lib->createElement<RectangleElement>();
    rectangle->setColor(255,0,0);
    rectangle->setWidth(200);
    rectangle->setHeight(200);

    lib->launchGUI();
}

std::string ElPricesModular::getCurrentTime()
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

double ElPricesModular::getUsageInDKKFromInterval(const int seconds)
{
    double totalPrice = 0;
    int tempPulses = 0;
    double KwhToWhFactor = 1000;
    int pulsesFoundSoFar = 0;
    int secondsCounter = 0;

    const auto& currentTime = TimeUtil::getCurrentTime();


    if (seconds <= currentTime.tm_sec)
    {
        tempPulses = elPriceUsageController_->getAmountOfPulsesBasedOnSeconds(seconds);
        return tempPulses / KwhToWhFactor * static_cast<double>(elPricesCollector_->getCurrentPrice()->getTotalPrice());
    }


    tempPulses = elPriceUsageController_->getAmountOfPulsesBasedOnSeconds(currentTime.tm_sec);
    pulsesFoundSoFar += tempPulses;
    totalPrice += tempPulses / KwhToWhFactor * static_cast<double>(elPricesCollector_->getCurrentPrice()->getTotalPrice());
    secondsCounter += currentTime.tm_sec;

    while (secondsCounter < seconds)
    {
        if (seconds - secondsCounter > 60)
        {
            secondsCounter += 60;
        }
        else
        {
            secondsCounter = seconds;
        }

        tempPulses = elPriceUsageController_->getAmountOfPulsesBasedOnSeconds(secondsCounter);
        tempPulses -= pulsesFoundSoFar;
        pulsesFoundSoFar = tempPulses;
        totalPrice += tempPulses / KwhToWhFactor * static_cast<double>(elPricesCollector_->getCurrentPrice()->getTotalPrice());
    }

    return totalPrice;
}
