#pragma once

#include <vector>

#include "DataPoint.h"
#include "ITemperatureVoltageConverter.h"

namespace TakeHomeProblem
{
   class TemperatureVoltageConverter : ITemperatureVoltageConverter
   {
   public:
      TemperatureVoltageConverter(const std::vector<DataPoint> &calibrationPoints);
   
      units::temperature::kelvin_t convert(const units::voltage::millivolt_t &voltage) override;
      units::voltage::millivolt_t convert(const units::temperature::kelvin_t &temperature) override;

   private:
      std::vector<DataPoint> calibration_points_;
   };
}