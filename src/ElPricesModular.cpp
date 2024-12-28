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
    InitWindow(1280, 720, "ElPricesModular");
    SetTargetFPS(10);
    while (not WindowShouldClose())
    {
        const double currentPrice = elPricesCollector_->getCurrentPrice()->getPriceWithoutFees();
        const double pulses = elPriceUsageController_->getPulses();
        const double kwhUsed = pulses / 1000;
        const double currentIntervalPrice = currentPrice * kwhUsed;
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(TextFormat("%.2f",currentIntervalPrice), 560, 310, 50, BLUE);
        EndDrawing();
    }
}
