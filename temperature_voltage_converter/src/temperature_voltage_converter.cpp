#include "temperature_voltage_converter.h"

#include <algorithm>
#include <exception>

#include "calibration_point.h"

using namespace units::temperature;
using namespace units::voltage;

namespace
{
   bool voltageLessThanCalibrationPoint(const millivolt_t &voltage, const TakeHomeProblem::CalibrationPoint &data_point)
   {
      return voltage < data_point.Voltage;
   }

   bool temperatureLessThanCalibrationPoint(const kelvin_t &temperature, const TakeHomeProblem::CalibrationPoint &data_point)
   {
      return temperature < data_point.Temperature;
   }

   bool sortCalibrationPointByTemperature(const TakeHomeProblem::CalibrationPoint &left, const TakeHomeProblem::CalibrationPoint &right)
   {
      return left.Temperature < right.Temperature;
   }

   bool sortCalibrationPointByVoltage(const TakeHomeProblem::CalibrationPoint &left, const TakeHomeProblem::CalibrationPoint &right)
   {
      return left.Voltage < right.Voltage;
   }

   double linearInterpolate(double x1, double y1, double x2, double y2, double x)
   {
      double m = (y2 - y1) / (x2 - x1);
      double b = y1;

      return m * (x - x1) + b;
   }

   template<typename Tx, typename Ty>
   Ty interpolate(Tx x1, Ty y1, Tx x2, Ty y2, Tx x)
   {
      return Ty(linearInterpolate(
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

TemperatureVoltageConverter::TemperatureVoltageConverter(const std::vector<CalibrationPoint> &calibration_points)
   : calibration_points_sorted_by_voltage_(calibration_points)
   , calibration_points_sorted_by_temperature_(calibration_points)
{
   if (calibration_points.size() < 2)
   {
      throw std::exception("Need at least two calibration points");
   }

   std::sort(
      calibration_points_sorted_by_voltage_.begin()
      , calibration_points_sorted_by_voltage_.end()
      , sortCalibrationPointByVoltage);
   std::sort(
      calibration_points_sorted_by_temperature_.begin()
      , calibration_points_sorted_by_temperature_.end()
      , sortCalibrationPointByTemperature);
}

kelvin_t TemperatureVoltageConverter::convert(const millivolt_t &voltage) const
{
   auto nearest_calibration_point_with_larger_voltage = std::upper_bound(
      calibration_points_sorted_by_voltage_.begin(),
      calibration_points_sorted_by_voltage_.end(),
      voltage,
      voltageLessThanCalibrationPoint);

   if (nearest_calibration_point_with_larger_voltage == calibration_points_sorted_by_voltage_.end())
   {
      nearest_calibration_point_with_larger_voltage = calibration_points_sorted_by_voltage_.end() - 1;
   }
   else if (nearest_calibration_point_with_larger_voltage == calibration_points_sorted_by_voltage_.begin())
   {
      nearest_calibration_point_with_larger_voltage = calibration_points_sorted_by_voltage_.begin() + 1;
   }

   auto nearest_calibration_point_with_smaller_voltage = nearest_calibration_point_with_larger_voltage - 1;

   return interpolate<volt_t, kelvin_t>(
      nearest_calibration_point_with_smaller_voltage->Voltage,
      nearest_calibration_point_with_smaller_voltage->Temperature,
      nearest_calibration_point_with_larger_voltage->Voltage,
      nearest_calibration_point_with_larger_voltage->Temperature,
      voltage);
}

millivolt_t TemperatureVoltageConverter::convert(const kelvin_t &temperature) const
{
   auto nearest_calibration_point_with_larger_temperature = std::upper_bound(
      calibration_points_sorted_by_temperature_.begin(),
      calibration_points_sorted_by_temperature_.end(),
      temperature,
      temperatureLessThanCalibrationPoint);

   if (nearest_calibration_point_with_larger_temperature == calibration_points_sorted_by_temperature_.end())
   {
      nearest_calibration_point_with_larger_temperature = calibration_points_sorted_by_temperature_.end() - 1;
   }
   else if (nearest_calibration_point_with_larger_temperature == calibration_points_sorted_by_temperature_.begin())
   {
      nearest_calibration_point_with_larger_temperature = calibration_points_sorted_by_temperature_.begin() + 1;
   }

   auto nearest_calibration_point_with_smaller_temperature = nearest_calibration_point_with_larger_temperature - 1;

   return interpolate<kelvin_t, volt_t>(
      nearest_calibration_point_with_smaller_temperature->Temperature,
      nearest_calibration_point_with_smaller_temperature->Voltage,
      nearest_calibration_point_with_larger_temperature->Temperature,
      nearest_calibration_point_with_larger_temperature->Voltage,
      temperature);
}

}