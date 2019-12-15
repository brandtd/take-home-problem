#include "gtest/gtest.h"

#include "temperature_voltage_converter.h"
#include "calibration_point_file.h"
#include "calibration_file_location.h"
#include "requested_converter_interface.h"

using namespace TakeHomeProblem;
using namespace units::temperature;
using namespace units::voltage;

namespace TakeHomeProblemTests
{

struct TemperatureToVoltageTestCase
{
   double InputTemperatureInKelvin;
   double ExpectedOutputVoltageInMilliVolts;
};

struct VoltageToTemperatureTestCase
{
   double InputVoltageInMilliVolts;
   double ExpectedOutputTemperatureInKelvin;
};

std::vector<CalibrationPoint> LoadCalibrationPoints()
{
   std::vector<CalibrationPoint> calibration_points;
   CalibrationPointFile::LoadCalibrationPoints(CalibrationFileLocation::kJsonFileName, calibration_points);
   return calibration_points;
}

class TakeHomeTests : public ::testing::Test
{
public:
   TakeHomeTests()
   : converter_(LoadCalibrationPoints())
   , requested_object_(converter_)
   {
   }

protected:
   TakeHomeProblem::TemperatureVoltageConverter converter_;
   TakeHomeProblem::RequestedConverterInterface requested_object_;
};

class TakeHomeTests_VoltageToTemperature : public TakeHomeTests, public ::testing::WithParamInterface<VoltageToTemperatureTestCase>
{
};

class TakeHomeTests_TemperatureToVoltage : public TakeHomeTests, public ::testing::WithParamInterface<TemperatureToVoltageTestCase>
{
};

INSTANTIATE_TEST_SUITE_P(
   TakeHomeTestPoints,
   TakeHomeTests_VoltageToTemperature,
   ::testing::Values(
      VoltageToTemperatureTestCase({85.023, 502.6}),
      VoltageToTemperatureTestCase({628.302, 270.0}),
      VoltageToTemperatureTestCase({892.35, 148.4}),
      VoltageToTemperatureTestCase({1725.0, -4.8}),
      VoltageToTemperatureTestCase({1600.2, 3.5})
   )
);

INSTANTIATE_TEST_SUITE_P(
   TakeHomeTestPoints,
   TakeHomeTests_TemperatureToVoltage,
   ::testing::Values(
      TemperatureToVoltageTestCase({1.23, 1646.500}),
      TemperatureToVoltageTestCase({1.34, 1645.070}),
      TemperatureToVoltageTestCase({1.40, 1644.290}),
      TemperatureToVoltageTestCase({2.1, 1632.740}),
      TemperatureToVoltageTestCase({3.5, 1599.020}),
      TemperatureToVoltageTestCase({4.0125, 1584.264}),
      TemperatureToVoltageTestCase({40.125, 1088.825}),
      TemperatureToVoltageTestCase({401.25, 322.879}),
      TemperatureToVoltageTestCase({505.13, 79.461})
   )
);

TEST_P(TakeHomeTests_VoltageToTemperature, TestPoints)
{
   VoltageToTemperatureTestCase testCase = GetParam();
   double acceptable_error_in_kelvin(0.05);

   double calculated_temperature_in_kelvin = requested_object_.convertmvToK(testCase.InputVoltageInMilliVolts);
   ASSERT_NEAR(calculated_temperature_in_kelvin, testCase.ExpectedOutputTemperatureInKelvin, acceptable_error_in_kelvin);
}

TEST_P(TakeHomeTests_TemperatureToVoltage, TestPoints)
{
   TemperatureToVoltageTestCase testCase = GetParam();
   double acceptable_error_in_millivolts(0.0005);

   double calculated_voltage_in_millivolts = requested_object_.convertKtomV(testCase.InputTemperatureInKelvin);
   ASSERT_NEAR(calculated_voltage_in_millivolts, testCase.ExpectedOutputVoltageInMilliVolts, acceptable_error_in_millivolts);
}

}