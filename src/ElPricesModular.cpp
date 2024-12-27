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
    std::string currentUsageAsPrice;
    while (not WindowShouldClose())
    {
        double currentPrice = elPricesCollector_->getCurrentPrice()->getPriceWithoutFees();
        double pulses = elPriceUsageController_->getPulses();
        double kwhUsed = pulses / 1000;
        double currentIntervalPrice = currentPrice * kwhUsed;

        currentUsageAsPrice = std::to_string(currentIntervalPrice);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(currentUsageAsPrice.c_str(), 560, 310, 50, BLUE);
        EndDrawing();
    }
}
