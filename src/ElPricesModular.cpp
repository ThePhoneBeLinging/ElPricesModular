//
// Created by Elias Aggergaard Larsen on 25/12/2024.
//

#include "ElPricesModular.h"

#include <iostream>
#include <LeGUILib/GUIElements/ImageElement.h>
#include <LeGUILib/GUIElements/RectangleElement.h>
#include <LeGUILib/GUIElements/Text.h>
#include "LeGUILib/LeGUILib.h"
#include "Slides/MainSlide.h"
#include "Utility/TimeUtil.h"

ElPricesModular::ElPricesModular() : leGUILib_(std::make_unique<LeGUILib>()), elPricesCollector_(std::make_shared<ElPricesCollector>()),
                                     elPriceUsageController_(std::make_shared<ElPricesUsageController>())
{
}

void ElPricesModular::launch()
{
    int screenWidth = 1280;
    int screenHeight = 720;
    int margin = 15;
    bool keepRunning_ = true;
    auto mainSlide = std::make_shared<MainSlide>();
    leGUILib_->addSlide(mainSlide);

    auto update = [&keepRunning_, &mainSlide] () -> void
    {
        while (keepRunning_)
        {
            mainSlide->compose();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    };
    std::thread updateThread = std::thread(update);

    leGUILib_->launchGUI();
    keepRunning_ = false;
    updateThread.join();
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
