//
// Created by Elias Aggergaard Larsen on 25/12/2024.
//

#include "ElPricesModular.h"

#include <iostream>

#include "raylib.h"

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
    const int amountOfPulses = elPriceUsageController_->getAmountOfPulsesBasedOnSeconds(seconds);
    DrawText(TextFormat("Amount Of Pulses last %d: %d", seconds,amountOfPulses), x - 40, y + 50, fontSize, WHITE);
}
