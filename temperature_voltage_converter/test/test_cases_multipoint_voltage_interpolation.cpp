#include "gtest/gtest.h"

#include "test_cases_voltage_interpolation.h"

using namespace TakeHomeProblem;
using namespace units::temperature;
using namespace units::voltage;

namespace TakeHomeProblemTests
{

INSTANTIATE_TEST_SUITE_P(
   MultiPointInterpolationTests,
   VoltageInterpolationTests,
   ::testing::Values(
      VoltageInterpolationTestCase({
         {
            {kelvin_t(1), volt_t(1)},
            {kelvin_t(2), volt_t(2)},
            {kelvin_t(4), volt_t(3)},
         },
         volt_t(1.0),
         kelvin_t(1.0)
      }),
      
      VoltageInterpolationTestCase({
         {
            {kelvin_t(1), volt_t(1)},
            {kelvin_t(2), volt_t(2)},
            {kelvin_t(4), volt_t(3)},
         },
         volt_t(2.0),
         kelvin_t(2.0)
      }),
      
      VoltageInterpolationTestCase({
         {
            {kelvin_t(1), volt_t(1)},
            {kelvin_t(2), volt_t(2)},
            {kelvin_t(4), volt_t(3)},
         },
         volt_t(3.0),
         kelvin_t(4.0)
      }),
      
      VoltageInterpolationTestCase({
         {
            {kelvin_t(1), volt_t(1)},
            {kelvin_t(2), volt_t(2)},
            {kelvin_t(4), volt_t(3)},
         },
         volt_t(4.0),
         kelvin_t(6.0)
      }),
      
      VoltageInterpolationTestCase({
         {
            {kelvin_t(1), volt_t(1)},
            {kelvin_t(2), volt_t(2)},
            {kelvin_t(4), volt_t(3)},
         },
         volt_t(0.0),
         kelvin_t(0.0)
      }),
      
      VoltageInterpolationTestCase({
         {
            {kelvin_t(1), volt_t(1)},
            {kelvin_t(2), volt_t(2)},
            {kelvin_t(4), volt_t(3)},
         },
         volt_t(0.5),
         kelvin_t(0.5)
      })
   )
);

}