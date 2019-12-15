#include "gtest/gtest.h"

#include "test_cases_temperature_interpolation.h"

using namespace TakeHomeProblem;
using namespace units::temperature;
using namespace units::voltage;

namespace TakeHomeProblemTests
{

INSTANTIATE_TEST_SUITE_P(
   SimpleTwoPointInterpolationTests,
   TemperatureInterpolationTests,
   ::testing::Values(
      TemperatureInterpolationTestCase({
         {
            {kelvin_t(1), volt_t(1)},
            {kelvin_t(2), volt_t(2)},
         },
         kelvin_t(1.5),
         volt_t(1.5)
      }),
      
      TemperatureInterpolationTestCase({
         {
            {kelvin_t(1), volt_t(1)},
            {kelvin_t(2), volt_t(2)},
         },
         kelvin_t(1.0),
         volt_t(1.0)
      }),
      
      TemperatureInterpolationTestCase({
         {
            {kelvin_t(1), volt_t(1)},
            {kelvin_t(2), volt_t(2)},
         },
         kelvin_t(2.0),
         volt_t(2.0)
      }),
      
      TemperatureInterpolationTestCase({
         {
            {kelvin_t(1), volt_t(1)},
            {kelvin_t(2), volt_t(2)},
         },
         kelvin_t(0.5),
         volt_t(0.5)
      }),
      
      TemperatureInterpolationTestCase({
         {
            {kelvin_t(1), volt_t(1)},
            {kelvin_t(2), volt_t(2)},
         },
         kelvin_t(2.5),
         volt_t(2.5)
      })
   )
);

}