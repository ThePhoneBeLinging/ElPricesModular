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
    int offsetX = 0;
    int offsetY = 0;
    //ToggleFullscreen();
    while (not WindowShouldClose())
    {

        if (IsGestureDetected(GESTURE_SWIPE_LEFT))
        {
            if (-1280 < offsetX && offsetX <= 1280)
            {
                offsetX -= 1280;
            }
        }
        if (IsGestureDetected(GESTURE_SWIPE_RIGHT))
        {
            if (-1280 <= offsetX && offsetX < 1280)
            {
                offsetX += 1280;
            }
        }



        BeginDrawing();
        ClearBackground(BLACK);
        drawMainScreen(offsetX,offsetY,40);
        drawConfigScreen(offsetX,offsetY,40);
        drawFeesOverview(offsetX,offsetY,40);
        DrawText(getCurrentTime().c_str(),50,50,40,WHITE);
        EndDrawing();
    }
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

void ElPricesModular::drawMainScreen(int offsetX, int offsetY, int fontSize)
{
    DrawText(TextFormat("Current Raw Price: %d", elPricesCollector_->getCurrentPrice()->getPriceWithoutFees()),offsetX + 350,offsetY + 15,40,WHITE);
    DrawText(TextFormat("Current Fees: %d", elPricesCollector_->getCurrentPrice()->getFees()),offsetX + 350,offsetY + 55,40,WHITE);
    drawPriceLastSeconds(offsetX + 500,offsetY + 50,40,5);
    drawPriceLastSeconds(offsetX + 500,offsetY + 150,40,20);
    drawPriceLastSeconds(offsetX + 500, offsetY + 250,40,60);
}

void ElPricesModular::drawConfigScreen(int offsetX, int offsetY, int fontSize)
{
    DrawText("Config Variables:",offsetX + -780,offsetY + 15,fontSize,WHITE);
}

void ElPricesModular::drawFeesOverview(int offsetX, int offsetY, int fontSize)
{
    DrawText("Fees:",offsetX + 1700,offsetY + 15,fontSize,WHITE);
}

void ElPricesModular::drawPriceLastSeconds(int x, int y, int fontSize, int seconds)
{
    const double dkkPrice = getUsageInDKKFromInterval(seconds);
    DrawText(TextFormat("DKK-CENT Used last: %d seconds: %.2f", seconds,dkkPrice/100), x - 40, y + 50, fontSize, WHITE);
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
