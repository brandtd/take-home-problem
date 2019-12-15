#include "calibration_point.h"

using namespace units::temperature;
using namespace units::voltage;

namespace TakeHomeProblem
{

void to_json(nlohmann::json &json, const CalibrationPoint &calibration_point)
{
   json =
   {
      units::unit_cast<double>(calibration_point.Temperature),
      units::unit_cast<double>(calibration_point.Voltage)
   };
}

void from_json(const nlohmann::json &json, CalibrationPoint &calibration_point)
{
   calibration_point.Temperature = kelvin_t(json[0]);
   calibration_point.Voltage = volt_t(json[1]);
}

}