//
// Created by Elias Aggergaard Larsen on 25/12/2024.
//

#include "ElPricesModular.h"

#include <iostream>

#include "raylib.h"

ElPricesModular::ElPricesModular() : elPricesCollector_(std::make_shared<ElPricesCollector>())
{
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

void ElPricesModular::launch()
{
    InitWindow(1280, 720, "ElPricesModular");
    SetTargetFPS(10);
    while (not WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(std::to_string(elPricesCollector_->getCurrentPrice()->getPriceWithoutFees()).c_str(), 500, 360, 120, BLUE);
        EndDrawing();
    }
}
