#include <iostream>

#include "ElPricesModular.h"
#include "Utility/ConfigController.h"
#include "Utility/DebugController.h"

int main()
{
    try
    {
        ConfigController::loadConfig("../../Resources/config.json");
        auto elPricesModular = std::make_unique<ElPricesModular>();
        elPricesModular->launch();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    DebugController::dumpDebug("../../debug.txt");
    return 0;
}
