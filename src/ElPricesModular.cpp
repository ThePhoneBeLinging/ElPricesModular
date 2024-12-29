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
    while (not WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);

        drawCurrentIntervalPrice(640,15,40);

        EndDrawing();
    }
}

void ElPricesModular::drawCurrentIntervalPrice(const int x, const int y, const int fontSize)
{
    // TODO FIX FORMULA BELOW
    const double currentPrice = elPricesCollector_->getCurrentPrice()->getPriceWithoutFees();
    const double timeBetweenPulses = elPriceUsageController_->getTimeBetweenPulses();
    const double wattage = 1 / timeBetweenPulses;
    const double kwhUsed = (wattage * timeBetweenPulses) / 1000;
    const double currentIntervalPrice = currentPrice * kwhUsed;
    DrawText("Current Interval Price:", x - 270, y, fontSize, WHITE);
    DrawText(TextFormat("%.2f",currentIntervalPrice), x - 40, y + 50, fontSize, WHITE);
}
