#pragma once

#include <units.h>

#include "ResultCodeEnum.h"

namespace TakeHomeProblem
{
   class ITemperatureVoltageConverter
   {
   public:
      virtual ~ITemperatureVoltageConverter() {}

      virtual units::temperature::kelvin_t convert(const units::voltage::millivolt_t &voltage) = 0;
      virtual units::voltage::millivolt_t convert(const units::temperature::kelvin_t &temperature) = 0;
   };
}