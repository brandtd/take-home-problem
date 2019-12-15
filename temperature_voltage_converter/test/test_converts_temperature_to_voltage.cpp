#include "gtest/gtest.h"

#include "temperature_voltage_converter.h"
#include "test_cases_temperature_interpolation.h"

using namespace TakeHomeProblem;
using namespace units::temperature;
using namespace units::voltage;

namespace TakeHomeProblemTests
{

TEST_P(TemperatureInterpolationTests, ConvertsTemperatureToVoltage)
{
   TemperatureInterpolationTestCase testCase = GetParam();

   TemperatureVoltageConverter converter(testCase.CalibrationPoints);

   volt_t converted_temperature = converter.convert(testCase.TestTemperature);

   ASSERT_EQ(converted_temperature, testCase.ExpectedVoltage);
}

}