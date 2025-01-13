//
// Created by Elias Aggergaard Larsen on 25/12/2024.
//

#include "ElPricesModular.h"

#include <iostream>
#include <LeGUILib/GUIElements/RectangleElement.h>
#include <LeGUILib/GUIElements/Text.h>
#include "LeGUILib/LeGUILib.h"
#include "Utility/ConfigController.h"
#include "Utility/TimeUtil.h"

ElPricesModular::ElPricesModular() : leGUILib_(std::make_unique<LeGUILib>())// elPricesCollector_(std::make_shared<ElPricesCollector>()),
                                     //elPriceUsageController_(std::make_shared<ElPricesUsageController>())
{
}

void ElPricesModular::launch()
{
    int screenWidth = 1280;
    int screenHeight = 720;
    int margin = 15;
    //
    // Creating config slide:
    //
    auto configSlide = std::make_shared<Slide>();
    leGUILib_->addSlide(configSlide);

    std::vector<std::shared_ptr<Text>> configKeys;
    std::vector<std::shared_ptr<Text>> configValues;

    int y = 65;
    for (const auto& element : ConfigController::getConfigList())
    {
        auto keyText = configSlide->createElement<Text>();
        keyText->setX(margin);
        keyText->setY(y);
        keyText->setFontSize(40);
        keyText->setColor(0,0,0); // SET COLOR
        keyText->setText(element.first + ":");

        auto valueText = configSlide->createElement<Text>();
        valueText->setX(screenWidth - margin - 100);
        valueText->setY(y);
        valueText->setFontSize(40);
        valueText->setColor(0,0,0); // SET COLOR
        valueText->setText(element.second);

        configKeys.push_back(keyText);
        configValues.push_back(valueText);
        y += 50;
    }

    auto reloadConfigLambda =  [configValues]
    {
        ConfigController::loadConfig("../../Resources/config.json");
        const auto configList = ConfigController::getConfigList();
        for (int i = 0; i < configValues.size(); i++)
        {
            configValues[i]->setText(configList[i].second);
        }
    };
    auto reloadConfigButton = configSlide->createElement<RectangleElement>();
    reloadConfigButton->setHeight(75);
    reloadConfigButton->setWidth(250);
    reloadConfigButton->setX((screenWidth - reloadConfigButton->getWidth()) / 2);


    reloadConfigButton->setY(screenHeight - reloadConfigButton->getHeight() - margin);
    reloadConfigButton->setOnClick(reloadConfigLambda);
    reloadConfigButton->setRoundedEdge(0.25);

    auto reloadConfigButtonText = configSlide->createElement<Text>();
    reloadConfigButtonText->setX((screenWidth - reloadConfigButton->getWidth()) / 2 + 15);
    reloadConfigButtonText->setY(screenHeight - (reloadConfigButton->getHeight()/2) - margin - 13);
    reloadConfigButtonText->setText("Reload Config File");
    reloadConfigButtonText->setFontSize(25);
    reloadConfigButtonText->setColor(255,255,255); // SET COLOR
    reloadConfigButton->setColor(0, 0, 0);

    auto titleText = configSlide->createElement<Text>();
    titleText->setX((screenWidth - reloadConfigButton->getWidth()) / 2 + 10);
    titleText->setText("Config Tab");
    titleText->setY(15);
    titleText->setColor(0,0,0); // SET COLOR
    titleText->setFontSize(40);

    leGUILib_->launchGUI();
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
