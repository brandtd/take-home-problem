#include "DataPoint.h"

using namespace units::temperature;
using namespace units::voltage;

namespace TakeHomeProblem
{

void to_json(nlohmann::json &json, const DataPoint &dataPoint)
{
   json =
   {
      units::unit_cast<double>(dataPoint.Temperature),
      units::unit_cast<double>(dataPoint.Voltage)
   };
}

void from_json(const nlohmann::json &json, DataPoint &dataPoint)
{
   dataPoint.Temperature = kelvin_t(json[0]);
   dataPoint.Voltage = volt_t(json[1]);
}

}