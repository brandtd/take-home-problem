#pragma once

#include <nlohmann/json.hpp>
#include <units.h>

namespace TakeHomeProblem
{
   struct CalibrationPoint
   {
      units::temperature::kelvin_t Temperature;
      units::voltage::volt_t Voltage;
   };

   void to_json(nlohmann::json &json, const CalibrationPoint &calibration_point);
   void from_json(const nlohmann::json &json, CalibrationPoint &calibration_point);
}