#include "gtest/gtest.h"

#include "temperature_voltage_converter.h"
#include "calibration_point_file.h"
#include "test_file_locations.h"

using namespace TakeHomeProblem;
using namespace units::temperature;
using namespace units::voltage;

namespace TakeHomeProblemTests
{

struct TemperatureToVoltageTestCase
{
   kelvin_t InputTemperature;
   volt_t ExpectedOutputVoltage;
};

struct VoltageToTemperatureTestCase
{
   volt_t InputVoltage;
   kelvin_t ExpectedOutputTemperature;
};

std::vector<CalibrationPoint> LoadCalibrationPoints()
{
   std::vector<CalibrationPoint> calibration_points;
   CalibrationPointFile::LoadCalibrationPoints(TestFileLocations::kDataSheetCalibrationPointsFileName, calibration_points);
   return calibration_points;
}

class TakeHomeTests : public ::testing::Test
{
public:
   TakeHomeTests()
   : converter_(LoadCalibrationPoints())
   {
   }

protected:
   TakeHomeProblem::TemperatureVoltageConverter converter_;
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
      VoltageToTemperatureTestCase({millivolt_t(85.023), kelvin_t(502.6)}),
      VoltageToTemperatureTestCase({millivolt_t(628.302), kelvin_t(270.0)}),
      VoltageToTemperatureTestCase({millivolt_t(892.35), kelvin_t(148.4)}),
      VoltageToTemperatureTestCase({millivolt_t(1725.0), kelvin_t(-4.8)}),
      VoltageToTemperatureTestCase({millivolt_t(1600.2), kelvin_t(3.5)})
   )
);

INSTANTIATE_TEST_SUITE_P(
   TakeHomeTestPoints,
   TakeHomeTests_TemperatureToVoltage,
   ::testing::Values(
      TemperatureToVoltageTestCase({kelvin_t(1.23), volt_t(1.646500)}),
      TemperatureToVoltageTestCase({kelvin_t(1.34), volt_t(1.645070)}),
      TemperatureToVoltageTestCase({kelvin_t(1.40), volt_t(1.644290)}),
      TemperatureToVoltageTestCase({kelvin_t(2.1), volt_t(1.632740)}),
      TemperatureToVoltageTestCase({kelvin_t(3.5), volt_t(1.599020)}),
      TemperatureToVoltageTestCase({kelvin_t(4.0125), volt_t(1.584264)}),
      TemperatureToVoltageTestCase({kelvin_t(40.125), volt_t(1.088825)}),
      TemperatureToVoltageTestCase({kelvin_t(401.25), volt_t(0.322879)}),
      TemperatureToVoltageTestCase({kelvin_t(505.13), volt_t(0.079461)})
   )
);

TEST_P(TakeHomeTests_VoltageToTemperature, TestPoints)
{
   VoltageToTemperatureTestCase testCase = GetParam();
   kelvin_t acceptable_error(0.05);

   kelvin_t calculatedTemperature = converter_.convert(millivolt_t(testCase.InputVoltage));
   kelvin_t expectedTemperature = testCase.ExpectedOutputTemperature;
   ASSERT_NEAR(units::unit_cast<double>(calculatedTemperature), units::unit_cast<double>(expectedTemperature), units::unit_cast<double>(acceptable_error));
}

TEST_P(TakeHomeTests_TemperatureToVoltage, TestPoints)
{
   TemperatureToVoltageTestCase testCase = GetParam();
   volt_t acceptable_error(0.0000005);

   volt_t calculatedVoltage = converter_.convert(testCase.InputTemperature);
   volt_t expectedVoltage = testCase.ExpectedOutputVoltage;
   ASSERT_NEAR(units::unit_cast<double>(calculatedVoltage), units::unit_cast<double>(expectedVoltage), units::unit_cast<double>(acceptable_error));
}

}