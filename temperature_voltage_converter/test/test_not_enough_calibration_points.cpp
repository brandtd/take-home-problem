#include "gtest/gtest.h"

#include <exception>

#include "temperature_voltage_converter.h"

using namespace TakeHomeProblem;
using namespace units::temperature;
using namespace units::voltage;

namespace TakeHomeProblemTests
{

TEST(TemperatureVoltageConverterTests, ThrowsExceptionIfNotEnoughCalibrationPoints)
{
   std::vector<CalibrationPoint> calibration_points({
      {kelvin_t(1), volt_t(1)}
   });

   ASSERT_THROW(TemperatureVoltageConverter object(calibration_points), std::invalid_argument);
}

}