//
// Created by eal on 08/06/25.
//

#include "DataController.h"

nlohmann::json DataController::getTimeJSONObject()
{
  std::lock_guard lock(mutex_);
  return timeJSONObject_;
}

nlohmann::json DataController::getPriceJSONObject()
{
  std::lock_guard lock(mutex_);
  return priceJSONObject_;
}

nlohmann::json DataController::getPowerJSONObject()
{
  std::lock_guard lock(mutex_);
  return powerJSONObject_;
}

void DataController::setTimeJSONObject(const nlohmann::json& timeJSONObject)
{
  std::lock_guard lock(mutex_);
  timeJSONObject_ = timeJSONObject;
}

void DataController::setPriceJSONObject(const nlohmann::json& priceJSONObject)
{
  std::lock_guard lock(mutex_);
  priceJSONObject_ = priceJSONObject;
}

void DataController::setPowerJSONObject(const nlohmann::json& powerJSONObject)
{
  std::lock_guard lock(mutex_);
  powerJSONObject_ = powerJSONObject;
}
