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
    //SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTargetFPS(10);
    InitWindow(1280, 720, "ElPricesModular");
    while (not WindowShouldClose())
    {
        const double currentPrice = elPricesCollector_->getCurrentPrice()->getPriceWithoutFees();
        const double pulses = elPriceUsageController_->getPulses();
        const double kwhUsed = pulses / 1000;
        const double currentIntervalPrice = currentPrice * kwhUsed;
        BeginDrawing();
        ClearBackground(BLACK);

        drawCurrentIntervalPrice(640,15,40,currentIntervalPrice);
        drawPriceGraph(80,400,80);

        EndDrawing();
    }
}

void ElPricesModular::drawCurrentIntervalPrice(const int x, const int y, const int fontSize, const double currentIntervalPrice)
{
    DrawText("Current Interval Price:", x - 270, y, fontSize,WHITE);
    DrawText(TextFormat("%.2f",currentIntervalPrice), x - 40, y + 50, fontSize, WHITE);
}

void ElPricesModular::drawPriceGraph(int x, int y, int spacing)
{
    auto elPrices = elPricesCollector_->getPricesAroundCurrentTime();

    auto lastPrice = elPrices.front();

    bool first = true;

    for (const auto& elPrice : elPrices)
    {
        if (first)
        {
            first = false;
            continue;
        }
        DrawLine(x, y + lastPrice->getPriceWithoutFees(), x + spacing, y + elPrice->getPriceWithoutFees(), WHITE);
        x += spacing;
        lastPrice = elPrice;
    }
}
