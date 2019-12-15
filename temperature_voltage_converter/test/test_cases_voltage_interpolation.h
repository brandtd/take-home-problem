#pragma once

#include <vector>
#include <units.h>

#include "calibration_point.h"

namespace TakeHomeProblemTests
{
   struct VoltageInterpolationTestCase
   {
      std::vector<TakeHomeProblem::CalibrationPoint> CalibrationPoints;
      units::voltage::volt_t TestVoltage;
      units::temperature::kelvin_t ExpectedTemperature;
   };
   
   class VoltageInterpolationTests : public ::testing::TestWithParam<VoltageInterpolationTestCase>
   {
   };
}