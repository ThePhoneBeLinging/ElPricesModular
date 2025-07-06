#include <iostream>

#include "ElPricesModular.h"
#include "Utility/ConfigController.h"
#include "Utility/DebugController.h"

int main()
{
    try
    {
        DebugController::initDebug(50);
        ConfigController::loadConfig("../../Resources/config.json");
        ElPricesModular();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    DebugController::dumpDebug("");
    return 200;
}
