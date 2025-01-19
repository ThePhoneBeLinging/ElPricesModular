//
// Created by Elias Aggergaard Larsen on 18/01/2025.
//

#include "MainSlide.h"

#include <iostream>
#include <LeGUILib/GUIElements/Text.h>
#include "Elements/BoxWith3Texts.h"
#include "Utility/TimeUtil.h"

MainSlide::MainSlide()
{
    background_ = createElement<ImageElement>();
    background_->setWidth(1280);
    background_->setHeight(720);
    background_->loadImage("../../Resources/bliss.png");
    background_->setZ(-100);

    timeBox_ = std::make_shared<TimeBox>(this);

    topLeftBox_ = std::make_shared<BoxWith3Texts>(this);
    topRigthBox_ = std::make_shared<BoxWith3Texts>(this);
    bottomLeftBox_ = std::make_shared<BoxWith4Texts>(this);
    bottomRigthBox_ = std::make_shared<BoxWith4Texts>(this);

    timeBox_->setX(440);
    timeBox_->setY(20);

    topLeftBox_->setX(20);
    topLeftBox_->setY(20);
    topLeftBox_->setTopText("Pris");
    topLeftBox_->setBottomText("KR | KwH");

    topRigthBox_->setX(860);
    topRigthBox_->setY(20);
    topRigthBox_->setTopText("Forbrug");
    topRigthBox_->setBottomText("KW");

    bottomLeftBox_->setX(20);
    bottomLeftBox_->setY(370);
    bottomLeftBox_->setTopText("Forbrug");
    bottomLeftBox_->setText5("Sidste Time");
    bottomLeftBox_->setBottomText("Kr");

    bottomRigthBox_->setX(860);
    bottomRigthBox_->setY(370);
    bottomRigthBox_->setTopText("Forbrug");
    bottomRigthBox_->setText5("Sidste Døgn");

    bottomRigthBox_->setBottomText("Kr");


}

void MainSlide::compose(const std::shared_ptr<ElPricesCollector>& collectorController,
    const std::shared_ptr<ElPricesUsageController>& usageController) const
{
    double priceRN = static_cast<double>(collectorController->getCurrentPrice()->getTotalPrice()) / 10000;
    std::string priceRNString = std::format("{:.2f}",priceRN);

    topLeftBox_->setMiddleText(priceRNString);

    double usageRN = usageController->getWattage();
    std::string usageRNString = std::format("{:.3f}",usageRN);
    topRigthBox_->setMiddleText(usageRNString);

    double usageLastHour = getUsageInDKKFromInterval(3600,collectorController,usageController) / 10000;
    std::string usageLastHourString = std::format("{:.2f}",usageLastHour);
    bottomLeftBox_->setMiddleText(usageLastHourString);

    double usageLastDay = getUsageInDKKFromInterval(86400,collectorController,usageController) / 10000;
    std::string usageLastDayString = std::format("{:.2f}",usageLastDay);
    bottomRigthBox_->setMiddleText(usageLastDayString);
    timeBox_->compose();
}


double MainSlide::getUsageInDKKFromInterval(const int seconds,const std::shared_ptr<ElPricesCollector>& elPricesCollector, const std::shared_ptr<ElPricesUsageController>& elPricesUsageController) const
{
    double totalPrice = 0;
    int tempPulses = 0;
    double KwhToWhFactor = 1000;
    int pulsesFoundSoFar = 0;
    int secondsCounter = 0;

    const auto& currentTime = TimeUtil::getCurrentTime();


    if (seconds <= currentTime.tm_sec)
    {
        tempPulses = elPricesUsageController->getAmountOfPulsesBasedOnSeconds(seconds);
        return tempPulses / KwhToWhFactor * static_cast<double>(elPricesCollector->getCurrentPrice()->getTotalPrice());
    }


    tempPulses = elPricesUsageController->getAmountOfPulsesBasedOnSeconds(currentTime.tm_sec);
    pulsesFoundSoFar += tempPulses;
    totalPrice += tempPulses / KwhToWhFactor * static_cast<double>(elPricesCollector->getCurrentPrice()->getTotalPrice());
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

        tempPulses = elPricesUsageController->getAmountOfPulsesBasedOnSeconds(secondsCounter);
        tempPulses -= pulsesFoundSoFar;
        pulsesFoundSoFar = tempPulses + pulsesFoundSoFar;
        totalPrice += tempPulses / KwhToWhFactor * static_cast<double>(elPricesCollector->getCurrentPrice()->getTotalPrice());
    }

    return totalPrice;
}