#pragma once

#include <vector>

#include "calibration_point.h"
#include "i_temperature_voltage_converter.h"

namespace TakeHomeProblem
{
   class TemperatureVoltageConverter : ITemperatureVoltageConverter
   {
   public:
      TemperatureVoltageConverter(const std::vector<CalibrationPoint> &calibration_points);
   
      units::temperature::kelvin_t convert(const units::voltage::millivolt_t &voltage) const override;
      units::voltage::millivolt_t convert(const units::temperature::kelvin_t &temperature) const override;

   private:
      std::vector<CalibrationPoint> calibration_points_sorted_by_voltage_;
      std::vector<CalibrationPoint> calibration_points_sorted_by_temperature_;
   };
}