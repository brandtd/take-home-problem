#pragma once

#include <nlohmann/json.hpp>
#include <units.h>

namespace ValueConvert
{
   struct DataPoint
   {
      units::temperature::kelvin_t Temperature;
      units::voltage::volt_t Voltage;
   };

   void to_json(nlohmann::json &json, const DataPoint &dataPoint);
   void from_json(const nlohmann::json &json, DataPoint &dataPoint);
}