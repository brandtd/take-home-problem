#pragma once

#include <vector>
#include <units.h>

#include "calibration_point.h"

namespace TakeHomeProblemTests
{
   struct TemperatureInterpolationTestCase
   {
      std::vector<TakeHomeProblem::CalibrationPoint> CalibrationPoints;
      units::temperature::kelvin_t TestTemperature;
      units::voltage::volt_t ExpectedVoltage;
   };
   
   class TemperatureInterpolationTests : public ::testing::TestWithParam<TemperatureInterpolationTestCase>
   {
   };
}