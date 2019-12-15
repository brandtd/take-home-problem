#pragma once

#include <string>
#include <vector>

#include "calibration_point.h"
#include "result_code_enum.h"

namespace TakeHomeProblem
{
   class CalibrationPointFile
   {
   public:
      static ResultCode LoadCalibrationPoints(const std::string &filename, std::vector<CalibrationPoint> &calibration_points);
      static ResultCode SaveCalibrationPoints(const std::string &filename, const std::vector<CalibrationPoint> &calibration_points);
   };
}