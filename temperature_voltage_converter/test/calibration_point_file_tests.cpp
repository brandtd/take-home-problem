#include "gtest/gtest.h"

#include "calibration_point_file.h"
#include "test_file_locations.h"

using namespace TakeHomeProblem;
using namespace units::temperature;
using namespace units::voltage;

namespace TakeHomeProblem
{
   bool operator==(const CalibrationPoint &left, const CalibrationPoint &right)
   {
      return (left.Temperature == right.Temperature)
         && (left.Voltage == right.Voltage);
   }
}

namespace TakeHomeProblemTests
{

TEST(FileLoadTests, ReportsSuccessForFileThatExists)
{
   std::vector<CalibrationPoint> points;
   ResultCode result = CalibrationPointFile::LoadCalibrationPoints(TestFileLocations::kValidJsonFileName, points);

   ASSERT_EQ(result, ResultCode::Success);
}

TEST(FileLoadTests, ReportsErrorForFileThatDoesNotExist)
{
   std::vector<CalibrationPoint> points;
   ResultCode result = CalibrationPointFile::LoadCalibrationPoints("Non existent file", points);

   ASSERT_EQ(result, ResultCode::Error);
}

TEST(FileLoadTests, ReportsErrorForMalformedFile)
{
   std::vector<CalibrationPoint> points;
   ResultCode result = CalibrationPointFile::LoadCalibrationPoints(TestFileLocations::kInvalidJsonFileName, points);

   ASSERT_EQ(result, ResultCode::Error);
}

TEST(FileLoadTests, LoadsExpectedValues)
{
   std::vector<CalibrationPoint> loaded_points;
   ResultCode result = CalibrationPointFile::LoadCalibrationPoints(TestFileLocations::kValidJsonFileName, loaded_points);

   std::vector<CalibrationPoint> expected_points =
   {
      {kelvin_t(1), volt_t(2)},
      {kelvin_t(3), volt_t(4)},
      {kelvin_t(5), volt_t(6)},
   };

   ASSERT_EQ(loaded_points, expected_points);
}

}