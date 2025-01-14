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

ElPricesModular::ElPricesModular() : leGUILib_(std::make_unique<LeGUILib>()), elPricesCollector_(std::make_shared<ElPricesCollector>()),
                                     elPriceUsageController_(std::make_shared<ElPricesUsageController>())
{
}

void ElPricesModular::launch()
{
    int screenWidth = 1280;
    int screenHeight = 720;
    int margin = 15;

    //
    // START OF CONFIG SLIDE
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

    auto configTitleText = configSlide->createElement<Text>();
    configTitleText->setX((screenWidth - reloadConfigButton->getWidth()) / 2 + 10);
    configTitleText->setText("Config Tab");
    configTitleText->setY(15);
    configTitleText->setColor(0,0,0); // SET COLOR
    configTitleText->setFontSize(40);

    //
    // END OF CONFIG SLIDE
    //

    //
    // START OF MAIN SLIDE
    //
    auto mainSlide = std::make_shared<Slide>();
    leGUILib_->addSlide(mainSlide);
    auto mainTitleText = mainSlide->createElement<Text>();
    mainTitleText->setX((screenWidth - reloadConfigButton->getWidth()) / 2 + 75);
    mainTitleText->setText(getCurrentTime());
    mainTitleText->setY(15);
    mainTitleText->setColor(0,0,0); // SET COLOR
    mainTitleText->setFontSize(40);

    auto currentPriceText = mainSlide->createElement<Text>();
    currentPriceText->setX((screenWidth - reloadConfigButton->getWidth()) / 2 - 170);
    currentPriceText->setY(75);
    currentPriceText->setColor(0,0,0); // SET COLOR
    currentPriceText->setFontSize(40);

    auto currentUsageText = mainSlide->createElement<Text>();
    currentUsageText->setX((screenWidth - reloadConfigButton->getWidth()) / 2 - 170);
    currentUsageText->setY(125);
    currentUsageText->setColor(0,0,0); // SET COLOR
    currentUsageText->setFontSize(40);

    //
    // END OF MAIN SLIDE
    //
    std::atomic_bool keepRunning = true;
    auto updateFunction = [mainTitleText, currentPriceText, currentUsageText, this, &keepRunning] ()
    {
        while (keepRunning)
        {
            mainTitleText->setText(getCurrentTime());
            currentPriceText->setText(TextFormat("Current Price: %.2f KR/KWH",static_cast<double>(elPricesCollector_->getCurrentPrice()->getTotalPrice()) / 10000));
            currentUsageText->setText(TextFormat("Current Usage: %.3f KW",elPriceUsageController_->getWattage()));
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    };
    auto updateThread = std::thread(updateFunction);


    leGUILib_->launchGUI();
    keepRunning = false;
    updateThread.join();
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
    time.append(":");
    if (timeNow.tm_sec < 10)
    {
        time.append("0");
    }
    time.append(std::to_string(timeNow.tm_sec));
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
