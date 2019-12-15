#include "gtest/gtest.h"

#include "temperature_voltage_converter.h"
#include "test_cases_voltage_interpolation.h"

using namespace TakeHomeProblem;
using namespace units::temperature;
using namespace units::voltage;

namespace TakeHomeProblemTests
{

TEST_P(VoltageInterpolationTests, ConvertsVoltageToTemperature)
{
   VoltageInterpolationTestCase testCase = GetParam();

   TemperatureVoltageConverter converter(testCase.CalibrationPoints);

   kelvin_t converted_temperature = converter.convert(millivolt_t(testCase.TestVoltage));

   ASSERT_EQ(converted_temperature, testCase.ExpectedTemperature);
}

}