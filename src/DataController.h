//
// Created by eal on 08/06/25.
//

#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H
#include <mutex>
#include "nlohmann/json.hpp"

class DataController
{
public:
  static nlohmann::json getTimeJSONObject();
  static nlohmann::json getPriceJSONObject();
  static nlohmann::json getPowerJSONObject();

  static void setTimeJSONObject(const nlohmann::json& timeJSONObject);
  static void setPriceJSONObject(const nlohmann::json& priceJSONObject);
  static void setPowerJSONObject(const nlohmann::json& powerJSONObject);

private:
  static inline nlohmann::json timeJSONObject_;
  static inline nlohmann::json priceJSONObject_;
  static inline nlohmann::json powerJSONObject_;
  static inline std::mutex mutex_;
};



#endif //DATACONTROLLER_H
