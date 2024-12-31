//
// Created by Elias Aggergaard Larsen on 25/12/2024.
//

#include "ElPricesModular.h"

#include <iostream>

#include "raylib.h"
#include "Utility/TimeUtil.h"

ElPricesModular::ElPricesModular() : elPricesCollector_(std::make_shared<ElPricesCollector>()),
                                     elPriceUsageController_(std::make_shared<ElPricesUsageController>())
{
}

void ElPricesModular::launch()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTargetFPS(10);
    InitWindow(1280, 720, "ElPricesModular");
    //ToggleFullscreen();
    while (not WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(TextFormat("Current Raw Price: %d", elPricesCollector_->getCurrentPrice()->getPriceWithoutFees()),350,15,40,WHITE);
        DrawText(TextFormat("Current Fees: %d", elPricesCollector_->getCurrentPrice()->getFees()),350,55,40,WHITE);
        drawPriceLastSeconds(500,50,40,5);
        drawPriceLastSeconds(500,150,40,20);
        drawPriceLastSeconds(500,250,40,60);
        EndDrawing();
    }
}

void ElPricesModular::drawCurrentIntervalPrice(const int x, const int y, const int fontSize)
{
    // TODO FIX FORMULA BELOW
    const double currentPrice = elPricesCollector_->getCurrentPrice()->getPriceWithoutFees();
    const double timeBetweenPulses = 0;
    const double wattage = 1 / timeBetweenPulses;
    const double kwhUsed = (wattage * timeBetweenPulses) / 1000;
    const double currentIntervalPrice = currentPrice * kwhUsed;
    DrawText("Current Interval Price:", x - 270, y, fontSize, WHITE);
    DrawText(TextFormat("%.2f",currentIntervalPrice), x - 40, y + 50, fontSize, WHITE);
}

void ElPricesModular::drawPriceLastSeconds(int x, int y, int fontSize, int seconds)
{
    const double dkkPrice = getUsageInDKKFromInterval(seconds);
    DrawText(TextFormat("DKK Used last: %d seconds: %.2f", seconds,dkkPrice), x - 40, y + 50, fontSize, WHITE);
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
