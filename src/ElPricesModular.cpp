//
// Created by Elias Aggergaard Larsen on 25/12/2024.
//

#include "ElPricesModular.h"

#include <iostream>

#include "raylib.h"

ElPricesModular::ElPricesModular() : elPricesCollector_(std::make_shared<ElPricesCollector>())
{
}

void ElPricesModular::launch()
{
    InitWindow(1280, 720, "ElPricesModular");
    SetTargetFPS(10);
    std::string currentUsageAsPrice;
    while (not WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(currentUsageAsPrice.c_str(), 560, 310, 50, BLUE);
        EndDrawing();
    }
}
