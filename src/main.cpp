#include "ElPricesModular.h"
#include "Utility/ConfigController.h"

int main()
{
    ConfigController::loadConfig("../../Resources/config.json");
    auto elPricesModular = std::make_unique<ElPricesModular>();
    elPricesModular->launch();
    return 0;
}
