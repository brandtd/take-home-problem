#include "calibration_point_file.h"

#include <iomanip>
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

namespace TakeHomeProblem
{

ResultCode CalibrationPointFile::LoadCalibrationPoints(const std::string &filename, std::vector<CalibrationPoint> &calibration_points)
{
   ResultCode result = ResultCode::Success;

   try
   {
      std::ifstream calibration_points_file(filename);
      if (calibration_points_file.good())
      {
         nlohmann::json json;

         calibration_points_file >> json;
         calibration_points_file.close();

         json.at("calibrationPoints").get_to(calibration_points);
      }
      else
      {
         std::cerr << "Unable to open data points file (File: " << filename << ")" << std::endl;
         result = ResultCode::Error;
      }
   }
   catch (const nlohmann::detail::exception& e)
   {
      std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
      result = ResultCode::Error;
   }

   return result;
}

ResultCode CalibrationPointFile::SaveCalibrationPoints(const std::string &filename, const std::vector<CalibrationPoint> &calibration_points)
{
   ResultCode result = ResultCode::Success;

   try
   {
      std::ofstream calibration_points_file(filename);
      if (calibration_points_file.good())
      {
         nlohmann::json json;
         json["calibrationPoints"] = calibration_points;
         calibration_points_file << std::setw(2) << json << std::endl;
      }
      else
      {
         std::cerr << "Failed to open calibration points file for writing (File: " << filename << ")" << std::endl;
         result = ResultCode::Error;
      }
   }
   catch (const nlohmann::detail::exception& e)
   {
      std::cerr << "Failed to write JSON: " << e.what() << std::endl;
      result = ResultCode::Error;
   }
   
   return result;
}

}