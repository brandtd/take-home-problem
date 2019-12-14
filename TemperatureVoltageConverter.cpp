#include "TemperatureVoltageConverter.h"

#include <algorithm>

#include "DataPoint.h"

using namespace units::temperature;
using namespace units::voltage;

namespace
{
   bool dataPointLessThanVoltage(const TakeHomeProblem::DataPoint &dataPoint, const millivolt_t &voltage)
   {
      return dataPoint.Voltage < voltage;
   }

   bool voltageLessThanDataPoint(const millivolt_t &voltage, const TakeHomeProblem::DataPoint &dataPoint)
   {
      return voltage < dataPoint.Voltage;
   }

   double linearInterpolate(double x1, double y1, double x2, double y2, double x)
   {
      double m = (y2 - y1) / (x2 - x1);
      double b = x1;

      return m * (x - x1) + b;
   }

   kelvin_t interpolateTemperature(volt_t x1, kelvin_t y1, volt_t x2, kelvin_t y2, volt_t x)
   {
      return kelvin_t(linearInterpolate(
         units::unit_cast<double>(x1),
         units::unit_cast<double>(y1),
         units::unit_cast<double>(x2),
         units::unit_cast<double>(y2),
         units::unit_cast<double>(x)
      ));
   }

   volt_t interpolateVoltage(kelvin_t x1, volt_t y1, kelvin_t x2, volt_t y2, kelvin_t x)
   {
      return volt_t(linearInterpolate(
         units::unit_cast<double>(x1),
         units::unit_cast<double>(y1),
         units::unit_cast<double>(x2),
         units::unit_cast<double>(y2),
         units::unit_cast<double>(x)
      ));
   }
}

namespace TakeHomeProblem
{

TemperatureVoltageConverter::TemperatureVoltageConverter(const std::vector<DataPoint> &calibrationPoints)
   : calibration_points_(calibrationPoints)
{
   // TODO: sort calibration points
}

kelvin_t TemperatureVoltageConverter::convert(const millivolt_t &voltage)
{
   auto lower_calibration_point = std::lower_bound(
      calibration_points_.begin(),
      calibration_points_.end(),
      voltage,
      dataPointLessThanVoltage);
   auto upper_calibration_point = std::upper_bound(
      calibration_points_.begin(),
      calibration_points_.end(),
      voltage,
      voltageLessThanDataPoint);

   if (lower_calibration_point == upper_calibration_point)
   {
      if (lower_calibration_point == calibration_points_.begin())
      {
         upper_calibration_point = lower_calibration_point + 1;
      }
      else
      {
         lower_calibration_point = upper_calibration_point - 1;
      }
   }

   return interpolateTemperature(
      lower_calibration_point->Voltage,
      lower_calibration_point->Temperature,
      upper_calibration_point->Voltage,
      upper_calibration_point->Temperature,
      voltage);
}

millivolt_t TemperatureVoltageConverter::convert(const kelvin_t &temperature)
{
   return millivolt_t(units::unit_cast<double>(temperature));
}

}